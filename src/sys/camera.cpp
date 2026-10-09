#include "pdg/sys/camera.h"
#include "pdg/sys/image.h"
#include "pdg/sys/serializer.h"
#include "pdg/sys/events.h"
#include "pdg/sys/deserializer.h"
#ifndef PDG_NO_GUI
#include "pdg/sys/port.h"
#include "pdg/sys/graphics.h"
#include "pdg/sys/spritelayer.h"
#include "pdg/sys/sprite.h"
#include "spritemanager.h"
#include "pdg/sys/scene.h"
#endif
#include <algorithm>
#include <cmath>
#include <map>
#include <stdexcept>

namespace pdg {
namespace {
#ifndef PDG_NO_GUI
bool matchesSource(CameraMatchMode mode) { return mode==matchSource || mode==matchSourceAndSize; }
bool matchesSize(CameraMatchMode mode) { return mode==matchSourceAndSize || mode==matchTargetAndSize; }
#endif
std::vector<Camera*>& attachedCameras() { static std::vector<Camera*> cameras; return cameras; }
void validateRect(const Rect& r) {
    if (!std::isfinite(r.left) || !std::isfinite(r.top) || !std::isfinite(r.right) || !std::isfinite(r.bottom) || r.right < r.left || r.bottom < r.top)
        throw std::invalid_argument("Camera rectangle must be finite and ordered");
}
void validateZoom(float zoom) {
    if (!std::isfinite(zoom) || zoom <= 0) throw std::invalid_argument("Camera zoom must be finite and positive");
}
}
struct Camera::MatchState {
    CameraMatchOptions options;
    std::weak_ptr<AnimatedBase*> source, target;
    bool fade=false, fading=false, settling=false, sampled=false, velocitySampledFrame=false;
    Offset fadeShift, fadeVelocity;
    double fadeZoom=0, fadeZoomVelocity=0;
    double lastTime=0, frameSeconds=0;
    Point sourceBase, targetBase, sourceLocation;
    double sourceSize=1, targetSize=1;
    Offset sourceVelocity, targetVelocity, sourceAnchorVelocity, targetAnchorVelocity;
    SpatialTransform sourceTransform, sourceTransformVelocity{0,0,0,0,0,0};
    Point sourceAnchor;
    SpatialTransform targetTransform, targetTransformVelocity{0,0,0,0,0,0};
    Point targetAnchor;
    double sourceSizeVelocity=0, targetSizeVelocity=0;
    Offset startShift, velocity;
    double startZoom=0, zoomVelocity=0;
};
Camera::Camera() {
    if (!hasScriptDefinition("shake")) defineScript("shake").moveBy(6,0,.025,linearTween).yoyo().repeat(11).diminish(0,.6).endScript();
    if (!hasScriptDefinition("impulse")) defineScript("impulse").moveBy(0,-12,.04,easeOutQuad).yoyo().endScript();
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    INIT_SCRIPT_OBJECT(mCameraScriptObj);
#endif
}
Camera::~Camera() { finishTransition(false); stopFollowing(); if (mEffects) {mEffects->mEffectsOwned=false; mEffects->release();} }
namespace {
void validateOpacity(float opacity) {
    if (!std::isfinite(opacity) || opacity<0 || opacity>1) throw std::invalid_argument("Camera opacity must be from zero to one");
}
}
Camera& Camera::show() {
    if(recordOperation("show", captureAnimationArguments())) return *this;
    if (mEffectsOwned) throw std::logic_error("Camera effects have no composed output visibility");
    if (recordScriptAnimation({{animationChannel_CameraHidden,0}},0,linearTween,animationMode_Assign,rotationDirection_AsSpecified,0,CLASSTAG_CAMERA)) return *this;
    validateImmediateOperation(); prepareAnimation(&mHidden); mHidden=0; return *this;
}
Camera& Camera::hide() {
    if(recordOperation("hide", captureAnimationArguments())) return *this;
    if (mEffectsOwned) throw std::logic_error("Camera effects have no composed output visibility");
    if (recordScriptAnimation({{animationChannel_CameraHidden,1}},0,linearTween,animationMode_Assign,rotationDirection_AsSpecified,0,CLASSTAG_CAMERA)) return *this;
    validateImmediateOperation(); prepareAnimation(&mHidden); mHidden=1; return *this;
}
Camera& Camera::setOpacity(float opacity) {
    if(recordOperation("setOpacity", captureAnimationArguments(opacity))) return *this;
    validateOpacity(opacity);
    if (mEffectsOwned) throw std::logic_error("Camera effects have no composed output opacity");
    if (opacity!=1) validateSceneOrder();
    if (recordScriptAnimation({{animationChannel_CameraOpacity,opacity}},0,linearTween,animationMode_Assign,rotationDirection_AsSpecified,0,CLASSTAG_CAMERA)) return *this;
    validateImmediateOperation(); prepareAnimation(&mOpacity); mOpacity=opacity; return *this;
}
Camera& Camera::fadeTo(float opacity, double seconds, EasingFunc easing) {
    if(recordOperation("fadeTo", captureAnimationArguments(opacity, seconds, easing))) return *this;
    validateOpacity(opacity); validateAnimationDuration(seconds);
    if (!easing) throw std::invalid_argument("Camera fade easing must be valid");
    if (mEffectsOwned) throw std::logic_error("Camera effects have no composed output opacity");
    validateSceneOrder();
    if (recordScriptAnimation({{animationChannel_CameraOpacity,opacity}},seconds,easing,animationMode_Assign,rotationDirection_AsSpecified,0,CLASSTAG_CAMERA)) return *this;
    beginAnimationRequest(); scheduleAnimation(&mOpacity,opacity,seconds,easing); finishAnimationRequest(); return *this;
}
void Camera::validateTransitionDestination(const Camera& destination, bool cut) const {
    if (&destination==this || mEffectsOwned || destination.mEffectsOwned) throw std::invalid_argument("Camera transition requires two distinct output cameras");
    if (cut) return; // A visibility handoff needs no composed scene pair.
#ifndef PDG_NO_GUI
    if (!GraphicsManager::hasInstance()) throw std::invalid_argument("Transition cameras must be attached to a graphics Port");
    auto ports=GraphicsManager::instance().getAllActivePorts();
    if (mOwnerPort && std::find(ports.begin(),ports.end(),mOwnerPort)==ports.end()) ports.push_back(mOwnerPort);
    if (destination.mOwnerPort && std::find(ports.begin(),ports.end(),destination.mOwnerPort)==ports.end()) ports.push_back(destination.mOwnerPort);
    auto attached=[&](const Camera* camera) {
        std::vector<Port*> result;
        for (auto* port:ports) {
            if (port->mCamera==camera || std::any_of(port->mLayers.begin(),port->mLayers.end(),[&](SpriteLayer* layer){return layer->getEffectiveCamera()==camera;})) result.push_back(port);
        }
        return result;
    };
    const auto sourcePorts=attached(this), destinationPorts=attached(&destination);
    if (sourcePorts.size()!=1 || destinationPorts!=sourcePorts || getViewport().empty() || getViewport()!=destination.getViewport())
        throw std::invalid_argument("Transition cameras require one shared Port and identical nonempty viewports");
    validateSceneOrder(&destination);destination.validateSceneOrder();
#else
    throw std::logic_error("Camera transition requires graphics");
#endif
}
void Camera::validateSceneOrder(const Camera* destination) const {
#ifndef PDG_NO_GUI
    if (!SpriteManager::hasInstance()) return; // Detached cameras may precede all layers.
    std::map<Port*,std::vector<Camera*>> views;
    std::vector<SpriteLayer*> layers;
    for(auto* layer=SpriteManager::instance().mFirstLayer;layer;layer=layer->mNextLayer)layers.push_back(layer);
    auto managed=Scene::layersInDrawOrder();layers.insert(layers.end(),managed.begin(),managed.end());
    for (auto* layer:layers) {
        if (!layer->getSpritePort() || layer->isHidden()) continue;
        auto* camera=layer->getEffectiveCamera();
        if (camera && camera!=this && camera!=destination && camera->isHidden()) continue;
        auto& order=views[layer->getSpritePort()];
        if (order.empty() || order.back()!=camera) order.push_back(camera);
    }
    for (const auto& [port,order]:views) {
        (void)port;
        if (std::count(order.begin(),order.end(),this)>1)
            throw std::logic_error("A composited Camera's layers must be contiguous in drawing order");
        if (!destination) continue;
        const auto source=std::find(order.begin(),order.end(),this),target=std::find(order.begin(),order.end(),destination);
        if (source==order.end() || target==order.end()) continue;
        for (auto position=std::min(source,target)+1;position<std::max(source,target);++position)
            if (!*position || !(*position)->getViewport().intersection(getViewport()).empty())
                throw std::logic_error("Transition scenes cannot straddle another overlapping camera view");
    }
#else
    (void)destination;
#endif
}
Camera& Camera::cutTo(Camera& destination) {
    if (mTransitionDestination || mTransitionSource)
        throw std::logic_error("A Camera already owns a pending or active transition");
    if(recordOperation("cutTo", captureAnimationArguments(destination))) return *this;
    return transitionToImpl(destination,0,camera_Crossfade,linearTween,nullptr,.1f,false,0,true);
}
Camera& Camera::matchCutTo(Camera& destination, const CameraMatchOptions& options) {
    if(recordOperation("matchCutTo", captureAnimationArguments(destination, options))) return *this;
    return matchToImpl(destination,options,false);
}
Camera& Camera::matchFadeTo(Camera& destination, const CameraMatchOptions& options) {
    if(recordOperation("matchFadeTo", captureAnimationArguments(destination, options))) return *this;
    return matchToImpl(destination,options,true);
}
Camera& Camera::matchToImpl(Camera& destination, const CameraMatchOptions& options, bool fade) {
#ifndef PDG_NO_GUI
    validateDuration(options.approachSeconds); validateDuration(options.settleSeconds); validateScriptEdit();
    if (fade) {validateDuration(options.fadeSeconds);if (options.fadeSeconds<=0 || !options.fadeEasing) throw std::invalid_argument("Match fade requires positive fadeSeconds and a valid easing");}
    if (options.mode<matchSource || options.mode>matchTargetAndSize)
        throw std::invalid_argument("Invalid camera match mode");
    if (!options.matchSource || !options.matchTarget || options.matchSource==options.matchTarget)
        throw std::invalid_argument("Match cut requires two distinct Sprites");
    if (!options.approachEasing || !options.settleEasing || options.approachSeconds<=0 || options.settleSeconds<=0)
        throw std::invalid_argument("Match cut requires positive phase durations and valid easings");
    // Overshooting/reversing easings cannot provide a controlled alignment/stop.
    auto checkEasing=[](EasingFunc easing) {
        double previous=-1;
        for (int i=0;i<=128;++i) {
            const double value=easing(i/128.,0,1,1);
            if (!std::isfinite(value) || value<-.0001 || value>1.0001 || value+.0001<previous)
                throw std::invalid_argument("Match cut easing must be monotonic from zero to one");
            previous=value;
        }
        if (std::abs(easing(0,0,1,1))>.0001 || std::abs(easing(1,0,1,1)-1)>.0001)
            throw std::invalid_argument("Match cut easing must have zero/one endpoints");
    };
    checkEasing(options.approachEasing);checkEasing(options.settleEasing);
    if (fade) checkEasing(options.fadeEasing);
    validateTransitionDestination(destination,!fade);
    if (mTransitionDestination || mTransitionSource || destination.mTransitionSource || destination.mTransitionDestination)
        throw std::logic_error("A Camera already owns a pending or active transition");
    auto checkSubject=[&](Sprite* sprite,Camera* camera) {
        auto* layer=sprite->getLayer();
        if (!layer || !layer->getSpritePort() || layer->getEffectiveCamera()!=camera || layer->mCameraMoveRatio==0 ||
            (matchesSize(options.mode) && layer->mCameraZoomRatio==0) || camera->mPixelSnapping || camera->mHasViewBounds)
            throw std::invalid_argument("Match Sprite needs an invertible, unsnapped, unbounded camera layer");
        layer->getViewTransform().inverse();
        if (matchesSize(options.mode) && (sprite->getWidth()<=0 || sprite->getHeight()<=0))
            throw std::invalid_argument("Zoom matching requires nonempty Sprite bounds");
    };
    checkSubject(options.matchSource,this); checkSubject(options.matchTarget,&destination);
    if (options.matchSource->getLayer()->getSpritePort()!=options.matchTarget->getLayer()->getSpritePort() ||
        getViewport().empty() || getViewport()!=destination.getViewport())
        throw std::invalid_argument("Match cut requires one shared Port and identical viewports");
    auto state=std::make_unique<MatchState>();state->options=options;state->fade=fade;
    state->source=options.matchSource->animationLifetime();state->target=options.matchTarget->animationLifetime();
    // Scheduler boundaries guarantee the visibility cut even when a tick spans both phases.
    batch();
    recordScriptAnimation({{animationChannel_CameraTransition,0}},0,linearTween,animationMode_Assign,rotationDirection_AsSpecified,3,CLASSTAG_CAMERA);
    andThen();
    recordScriptAnimation({{animationChannel_CameraTransition,1}},options.approachSeconds,linearTween,animationMode_Assign,rotationDirection_AsSpecified,1,CLASSTAG_CAMERA);
    andThen();
    recordScriptAnimation({{animationChannel_CameraTransition,0}},0,linearTween,animationMode_Assign,rotationDirection_AsSpecified,0,CLASSTAG_CAMERA);
    andThen();
    if (fade) {
        recordScriptAnimation({{animationChannel_CameraTransition,1}},options.fadeSeconds,linearTween,animationMode_Assign,rotationDirection_AsSpecified,1,CLASSTAG_CAMERA);
        andThen();
        recordScriptAnimation({{animationChannel_CameraTransition,0}},0,linearTween,animationMode_Assign,rotationDirection_AsSpecified,0,CLASSTAG_CAMERA);
        andThen();
    }
    recordScriptAnimation({{animationChannel_CameraTransition,1}},options.settleSeconds,linearTween,animationMode_Assign,rotationDirection_AsSpecified,2,CLASSTAG_CAMERA);
    endBatch();
    destination.addRef();mTransitionDestination=&destination;destination.mTransitionSource=this;
    mTransitionIsCut=true;mTransitionStyle=camera_Crossfade;mTransitionActive=false;mTransitionProgress=-1;mMatch=std::move(state);
    return *this;
#else
    (void)destination;(void)options;(void)fade;
    throw std::logic_error("Sprite camera matching requires graphics");
#endif
}
void Camera::animationValuesChanged() {
    mOpacity=std::clamp(mOpacity,0.f,1.f);
    if (mMatch && mTransitionActive) updateMatch();
}
void Camera::updateMatch() {
#ifndef PDG_NO_GUI
    auto& state=*mMatch;auto sourceLife=state.source.lock(),targetLife=state.target.lock();
    auto* source=sourceLife?dynamic_cast<Sprite*>(*sourceLife):nullptr;
    auto* target=targetLife?dynamic_cast<Sprite*>(*targetLife):nullptr;
    auto* destination=mTransitionDestination;
    if (!source || !target || !source->getLayer() || !target->getLayer() ||
        source->getLayer()->getEffectiveCamera()!=this || target->getLayer()->getEffectiveCamera()!=destination ||
        source->getLayer()->getSpritePort()!=target->getLayer()->getSpritePort() || getViewport()!=destination->getViewport() ||
        source->getLayer()->mCameraMoveRatio==0 || target->getLayer()->mCameraMoveRatio==0 ||
        mPixelSnapping || destination->mPixelSnapping || mHasViewBounds || destination->mHasViewBounds ||
        (matchesSize(state.options.mode) && (source->getLayer()->mCameraZoomRatio==0 || target->getLayer()->mCameraZoomRatio==0))) {
        finishTransition(false);return;
    }
    if (mSchedulePaused) return;
    auto& options=state.options;
    const double progress=std::clamp(double(mTransitionProgress),0.,1.);
    // The scheduler can publish the next phase's zero before delivering the cut completion.
    // Keep the outgoing endpoint sample until that completion consumes its velocity.
    const double time=state.fading ? options.approachSeconds+progress*options.fadeSeconds : progress*options.approachSeconds;
    if (!state.settling && state.sampled && time<state.lastTime) return;
    if (state.settling) {
        // Integral of a decaying velocity preserves the inherited derivative at the cut.
        double area=0;const int samples=64;
        for (int i=0;i<=samples;++i) {
            const double u=progress*i/samples;
            const double value=1-options.settleEasing(u,0,1,1);
            area+=value*(i==0 || i==samples?1:(i%2?4:2));
        }
        area*=progress/(3*samples)*options.settleSeconds;
        const double restore=options.settleReturnsCamera ? 1-progress*progress*progress*(10+progress*(-15+6*progress)) : 1;
        destination->mMatchShift=Offset((state.startShift.x+state.velocity.x*area)*restore,
                                       (state.startShift.y+state.velocity.y*area)*restore);
        destination->mMatchLogZoom=(state.startZoom+state.zoomVelocity*area)*restore;
        return;
    }
    // Sample the uncorrected live views, including parallax and the effects stage.
    const Offset savedSource=mMatchShift,savedTarget=destination->mMatchShift;
    const double savedSourceZoom=mMatchLogZoom,savedTargetZoom=destination->mMatchLogZoom;
    mMatchShift=destination->mMatchShift=Offset();mMatchLogZoom=destination->mMatchLogZoom=0;
    auto measure=[](Sprite* sprite) {
        auto* layer=sprite->getLayer();
        const Quad bounds=layer->layerToPort(Quad(sprite->getRotatedBounds()));
        const Rect box=bounds.getBounds();
        return std::pair<Point,double>(layer->layerToPort(Quad(sprite->getRotatedBounds()).centerPoint()),std::max(box.width(),box.height()));
    };
    auto from=measure(source),to=measure(target);
    const auto targetTransform=target->getLayer()->getViewTransform();
    const auto sourceTransform=source->getLayer()->getViewTransform();
    Point sourceAnchor=mOwnerPort?mOwnerPort->getCameraAnchor():getViewport().centerPoint();
    if (mEffects) {auto effect=mEffects->getViewTransform();sourceAnchor.x+=effect.tx;sourceAnchor.y+=effect.ty;}
    Point targetAnchor=destination->mOwnerPort?destination->mOwnerPort->getCameraAnchor():destination->getViewport().centerPoint();
    if (destination->mEffects) {auto effect=destination->mEffects->getViewTransform();targetAnchor.x+=effect.tx;targetAnchor.y+=effect.ty;}
    mMatchShift=savedSource;destination->mMatchShift=savedTarget;mMatchLogZoom=savedSourceZoom;destination->mMatchLogZoom=savedTargetZoom;
    if (matchesSize(options.mode) && (from.second<=0 || to.second<=0)) throw std::invalid_argument("Match Sprite projected bounds became empty");
    // Sprites/following/effects are sampled once per runtime frame. A scheduler
    // boundary can consume only a small fraction of that frame; using that
    // fraction as the sample interval would magnify the inherited velocity.
    const double dt=time>state.lastTime ? std::max(time-state.lastTime,state.fade?state.frameSeconds:0.) : 0;
    if (state.sampled && dt>0 && !state.velocitySampledFrame) {
        state.velocitySampledFrame=true;
        state.sourceVelocity=Offset((from.first.x-state.sourceBase.x)/dt,(from.first.y-state.sourceBase.y)/dt);
        if (state.fade && !isFollowing() && time-state.lastTime<dt) {
            // Native source pans advance by the scheduler substep, unlike the
            // external Sprite sample. Preserve their actual translation rate.
            const Offset move=mLocation-state.sourceLocation;
            const double intervalCorrection=1/(time-state.lastTime)-1/dt;
            const double ratio=source->getLayer()->mCameraMoveRatio;
            state.sourceVelocity.x-=ratio*(sourceTransform.a*move.x+sourceTransform.c*move.y)*intervalCorrection;
            state.sourceVelocity.y-=ratio*(sourceTransform.b*move.x+sourceTransform.d*move.y)*intervalCorrection;
        }
        state.targetVelocity=Offset((to.first.x-state.targetBase.x)/dt,(to.first.y-state.targetBase.y)/dt);
        state.sourceAnchorVelocity=Offset((sourceAnchor.x-state.sourceAnchor.x)/dt,(sourceAnchor.y-state.sourceAnchor.y)/dt);
        state.sourceTransformVelocity={ (sourceTransform.a-state.sourceTransform.a)/dt,(sourceTransform.b-state.sourceTransform.b)/dt,
            (sourceTransform.c-state.sourceTransform.c)/dt,(sourceTransform.d-state.sourceTransform.d)/dt,0,0 };
        state.targetAnchorVelocity=Offset((targetAnchor.x-state.targetAnchor.x)/dt,(targetAnchor.y-state.targetAnchor.y)/dt);
        state.targetTransformVelocity={ (targetTransform.a-state.targetTransform.a)/dt,(targetTransform.b-state.targetTransform.b)/dt,
            (targetTransform.c-state.targetTransform.c)/dt,(targetTransform.d-state.targetTransform.d)/dt,0,0 };
        if (matchesSize(options.mode)) {
            state.sourceSizeVelocity=std::log(from.second/state.sourceSize)/dt;
            state.targetSizeVelocity=std::log(to.second/state.targetSize)/dt;
        }
    }
    if (!state.sampled || dt>0) {
        state.sourceTransform=sourceTransform;state.sourceAnchor=sourceAnchor;
        state.targetTransform=targetTransform;state.targetAnchor=targetAnchor;
        state.sourceBase=from.first;state.targetBase=to.first;state.sourceLocation=mLocation;state.sourceSize=from.second;state.targetSize=to.second;state.lastTime=time;state.sampled=true;
    }
    if (state.fading) {
        const double elapsed=progress*options.fadeSeconds;
        mMatchShift=Offset(state.fadeShift.x+state.fadeVelocity.x*elapsed,state.fadeShift.y+state.fadeVelocity.y*elapsed);
        mMatchLogZoom=state.fadeZoom+state.fadeZoomVelocity*elapsed;
        alignMatchDestination();
        return;
    }
    // The named match camera is the reference, not the camera we adjust.
    const bool adjustSource=!matchesSource(options.mode);
    Camera* moving=adjustSource?this:destination;Sprite* subject=adjustSource?source:target;
    const double weight=options.approachEasing(progress,0,1,1);
    const Point desired=adjustSource ? Point(from.first.x+(to.first.x-from.first.x)*weight,from.first.y+(to.first.y-from.first.y)*weight) : from.first;
    if (matchesSize(options.mode)) moving->mMatchLogZoom=std::log((adjustSource?to.second/from.second:from.second/to.second))/subject->getLayer()->mCameraZoomRatio*(adjustSource?weight:1);
    moving->mMatchShift=Offset();
    const auto transform=subject->getLayer()->getViewTransform();const auto current=measure(subject).first;
    const double ratio=subject->getLayer()->mCameraMoveRatio;
    const auto inverse=transform.inverse();
    const double dx=desired.x-current.x,dy=desired.y-current.y;
    moving->mMatchShift=Offset(-(inverse.a*dx+inverse.c*dy)/ratio,-(inverse.b*dx+inverse.d*dy)/ratio);
#endif
}
void Camera::cutMatch() {
#ifndef PDG_NO_GUI
    if (!mMatch || !mTransitionDestination) return;
    updateMatch();if (!mMatch) return;
    auto& state=*mMatch;auto& options=state.options;auto* destination=mTransitionDestination;
    auto life=state.target.lock();auto* target=dynamic_cast<Sprite*>(*life);
    auto* layer=target->getLayer();
    // Derivative of the outgoing alignment at its exact endpoint, in Port coordinates.
    const double derivative=(options.approachEasing(1,0,1,1)-options.approachEasing(1-1e-4,0,1,1))/(1e-4*options.approachSeconds);
    Offset screenVelocity=state.sourceVelocity;
    double sizeVelocity=state.sourceSizeVelocity;
    if (!matchesSource(options.mode)) {
        screenVelocity=Offset(state.targetVelocity.x+(state.targetBase.x-state.sourceBase.x)*derivative,
                              state.targetVelocity.y+(state.targetBase.y-state.sourceBase.y)*derivative);
        sizeVelocity=state.targetSizeVelocity+std::log(state.targetSize/state.sourceSize)*derivative;
    }
    if (state.fading) {
        auto sourceLife=state.source.lock();auto* source=dynamic_cast<Sprite*>(*sourceLife);auto* layer=source->getLayer();
        const double scale=std::exp(mMatchLogZoom*layer->mCameraZoomRatio),ratio=layer->mCameraMoveRatio;
        const auto& rate=state.sourceTransformVelocity;const auto transform=layer->getViewTransform();
        const Point before=layer->layerToPort(Quad(source->getRotatedBounds()).centerPoint());
        const double saved=mMatchLogZoom;mMatchLogZoom+=1e-4;
        const Point zoomed=layer->layerToPort(Quad(source->getRotatedBounds()).centerPoint());mMatchLogZoom=saved;
        screenVelocity=Offset(state.sourceVelocity.x*scale+(1-scale)*state.sourceAnchorVelocity.x-
            scale*ratio*(rate.a*mMatchShift.x+rate.c*mMatchShift.y)-ratio*(transform.a*state.fadeVelocity.x+transform.c*state.fadeVelocity.y)+(zoomed.x-before.x)/1e-4*state.fadeZoomVelocity,
            state.sourceVelocity.y*scale+(1-scale)*state.sourceAnchorVelocity.y-
            scale*ratio*(rate.b*mMatchShift.x+rate.d*mMatchShift.y)-ratio*(transform.b*state.fadeVelocity.x+transform.d*state.fadeVelocity.y)+(zoomed.y-before.y)/1e-4*state.fadeZoomVelocity);
        sizeVelocity=state.sourceSizeVelocity+state.fadeZoomVelocity*layer->mCameraZoomRatio;
    }
    alignMatchDestination();
    state.startShift=destination->mMatchShift;state.startZoom=destination->mMatchLogZoom;
    auto motion=[&](Camera* camera,Sprite* sprite,const Offset& rawVelocity,double rawSizeVelocity,
                    const SpatialTransform& rate,const Offset& anchorVelocity) {
        auto* subjectLayer=sprite->getLayer();const double movement=subjectLayer->mCameraMoveRatio;
        const auto inverse=subjectLayer->getViewTransform().inverse();
        const double zoomVelocity=matchesSize(options.mode)?(sizeVelocity-rawSizeVelocity)/subjectLayer->mCameraZoomRatio:0;
        const double saved=camera->mMatchLogZoom;
        const Point before=subjectLayer->layerToPort(Quad(sprite->getRotatedBounds()).centerPoint());
        camera->mMatchLogZoom+=1e-4;
        const Point zoomed=subjectLayer->layerToPort(Quad(sprite->getRotatedBounds()).centerPoint());camera->mMatchLogZoom=saved;
        const double scale=std::exp(saved*subjectLayer->mCameraZoomRatio);
        const auto& shift=camera->mMatchShift;
        const double naturalX=rawVelocity.x*scale+(1-scale)*anchorVelocity.x-scale*movement*(rate.a*shift.x+rate.c*shift.y);
        const double naturalY=rawVelocity.y*scale+(1-scale)*anchorVelocity.y-scale*movement*(rate.b*shift.x+rate.d*shift.y);
        const double vx=screenVelocity.x-naturalX-(zoomed.x-before.x)/1e-4*zoomVelocity;
        const double vy=screenVelocity.y-naturalY-(zoomed.y-before.y)/1e-4*zoomVelocity;
        return std::pair<Offset,double>(Offset(-(inverse.a*vx+inverse.c*vy)/movement,-(inverse.b*vx+inverse.d*vy)/movement),zoomVelocity);
    };
    if (state.fade && !state.fading) {
        validateTransitionDestination(*destination,false);
        auto sourceLife=state.source.lock();auto* source=dynamic_cast<Sprite*>(*sourceLife);
        const auto outgoing=motion(this,source,state.sourceVelocity,state.sourceSizeVelocity,state.sourceTransformVelocity,state.sourceAnchorVelocity);
        state.fadeShift=mMatchShift;state.fadeZoom=mMatchLogZoom;state.fadeVelocity=outgoing.first;state.fadeZoomVelocity=outgoing.second;
        state.fading=true;mTransitionIsCut=false;mHidden=destination->mHidden=0;
        return;
    }
    const auto incoming=motion(destination,target,state.targetVelocity,state.targetSizeVelocity,state.targetTransformVelocity,state.targetAnchorVelocity);
    state.velocity=incoming.first;state.zoomVelocity=incoming.second;
    mTransitionIsCut=true;
    state.settling=true;mHidden=1;destination->mHidden=0;
#endif
}
void Camera::alignMatchDestination() {
#ifndef PDG_NO_GUI
    auto& state=*mMatch;auto& options=state.options;auto* destination=mTransitionDestination;
    auto sourceLife=state.source.lock(),targetLife=state.target.lock();
    auto* source=dynamic_cast<Sprite*>(*sourceLife);auto* target=dynamic_cast<Sprite*>(*targetLife);auto* layer=target->getLayer();
    // Align the incoming view to the outgoing corrected composition before visibility changes.
    const Point position=source->getLayer()->layerToPort(Quad(source->getRotatedBounds()).centerPoint());
    auto size=[](Sprite* sprite){const auto box=sprite->getLayer()->layerToPort(Quad(sprite->getRotatedBounds())).getBounds();return std::max(box.width(),box.height());};
    destination->mMatchShift=Offset();destination->mMatchLogZoom=0;
    if (matchesSize(options.mode)) destination->mMatchLogZoom=std::log(size(source)/size(target))/layer->mCameraZoomRatio;
    auto transform=layer->getViewTransform();const auto inverse=transform.inverse();
    const Point unshifted=layer->layerToPort(Quad(target->getRotatedBounds()).centerPoint());
    const double ratio=layer->mCameraMoveRatio;
    destination->mMatchShift=Offset(-(inverse.a*(position.x-unshifted.x)+inverse.c*(position.y-unshifted.y))/ratio,
                                    -(inverse.b*(position.x-unshifted.x)+inverse.d*(position.y-unshifted.y))/ratio);
#endif
}
float Camera::transitionBlendProgress() const {
    const float progress=std::clamp(mTransitionProgress,0.f,1.f);
    return mMatch && mMatch->fading && !mMatch->settling ? mMatch->options.fadeEasing(progress,0,1,1) : progress;
}
void Camera::clearMatch(bool retain) {
    if (!mMatch) return;
    auto bake=[](Camera* camera,bool keep) {
        if (!camera) return;
        if (keep) {
            camera->mLocation.x+=camera->mMatchShift.x;camera->mLocation.y+=camera->mMatchShift.y;
            if (camera->isFollowing()) {camera->mFollowOffset.x+=camera->mMatchShift.x;camera->mFollowOffset.y+=camera->mMatchShift.y;}
            camera->mZoom*=std::exp(camera->mMatchLogZoom);
        }
        camera->mMatchShift=Offset();camera->mMatchLogZoom=0;
    };
    bake(this,false);bake(mTransitionDestination,retain && mMatch->settling);mMatch.reset();
}
Camera& Camera::transitionTo(Camera& destination, double seconds, int style, EasingFunc easing) {
    if(recordOperation("transitionTo", captureAnimationArguments(destination, seconds, style, easing))) return *this;
    return transitionToImpl(destination,seconds,style,easing,nullptr,.1f,false,0);
}
Camera& Camera::lumaFadeTo(Camera& destination, double seconds, Image* mask, float softness, bool darkFirst, EasingFunc easing) {
    if(recordOperation("lumaFadeTo", captureAnimationArguments(destination, seconds, mask, softness, darkFirst, easing))) return *this;
    if (!std::isfinite(softness) || softness<0 || softness>1) throw std::invalid_argument("Luma softness must be in [0,1]");
    if (mask && (mask->getWidth()<=0 || mask->getHeight()<=0)) throw std::invalid_argument("Luma mask must be nonempty");
    return transitionToImpl(destination,seconds,camera_LumaFade,easing,mask,softness,darkFirst,0);
}
Camera& Camera::whipPanTo(Camera& destination, double seconds, int style, float blur, EasingFunc easing) {
    if(recordOperation("whipPanTo", captureAnimationArguments(destination, seconds, style, blur, easing))) return *this;
    if (style<camera_WhipLeft || style>camera_WhipDown || !std::isfinite(blur) || blur<0 || blur>1) throw std::invalid_argument("Invalid whip direction or blur (expected [0,1])");
    return transitionToImpl(destination,seconds,style,easing,nullptr,.1f,false,blur);
}
Camera& Camera::transitionToImpl(Camera& destination, double seconds, int style, EasingFunc easing, Image* mask, float softness, bool darkFirst, float blur, bool cut) {
    validateDuration(seconds); validateScriptEdit();
    if (!easing || (style<camera_Crossfade || style>camera_WhipDown)) throw std::invalid_argument("Unsupported Camera transition style or easing");
    if (mTransitionDestination || mTransitionSource || destination.mTransitionSource || destination.mTransitionDestination)
        throw std::logic_error("A Camera already owns a pending or active transition");
    validateTransitionDestination(destination,cut);
    const bool immediate=seconds==0 && !mAppendAnimation && mDelaySeconds==0;
    batch();
    recordScriptAnimation({{animationChannel_CameraTransition,0}},0,linearTween,animationMode_Assign,rotationDirection_AsSpecified,3,CLASSTAG_CAMERA);
    andThen();
    recordScriptAnimation({{animationChannel_CameraTransition,1}},seconds,easing,animationMode_Assign,rotationDirection_AsSpecified,2,CLASSTAG_CAMERA);
    endBatch();
    destination.addRef(); mTransitionDestination=&destination; destination.mTransitionSource=this;
    mTransitionProgress=-1; mTransitionActive=false; mTransitionStyle=style; mTransitionIsCut=cut;
    mTransitionSoftness=softness; mTransitionDarkFirst=darkFirst; mTransitionBlur=blur; mTransitionSeconds=seconds;
    mTransitionMask=mask; if (mask) mask->addRef();
    mTransitionLuminance.clear(); mTransitionMaskWidth=mTransitionMaskHeight=0;
    // A recorded cut is materialized during animate(); its zero-time tracks
    // are consumed by that update without recursively entering it.
    if (immediate && !mAnimating) animate(0);
    return *this;
}
void Camera::startTransition() {
    if (!mTransitionDestination || mTransitionActive) return;
    validateTransitionDestination(*mTransitionDestination,mTransitionIsCut);
    mSourceWasHidden=isHidden(); mDestinationWasHidden=mTransitionDestination->isHidden();
    if (!mTransitionIsCut) mHidden=mTransitionDestination->mHidden=0;
    mTransitionActive=true;
    if (mMatch) updateMatch();
}
void Camera::finishTransition(bool completed) {
    if (!mTransitionDestination) return;
    if (!completed) stopAnimationChannel(&mTransitionProgress);
    auto* destination=mTransitionDestination;
    if (completed) {mHidden=1;destination->mHidden=0;}
    else if (mTransitionActive && !(mMatch && mMatch->settling)) {mHidden=mSourceWasHidden;destination->mHidden=mDestinationWasHidden;}
    clearMatch(completed || (mMatch && mMatch->settling));
    mTransitionDestination=nullptr; destination->mTransitionSource=nullptr;
    mTransitionActive=false; mTransitionProgress=-1;
    if (mTransitionMask) {mTransitionMask->release();mTransitionMask=nullptr;}
    mTransitionLuminance.clear(); mTransitionMaskWidth=mTransitionMaskHeight=0;
    destination->release();
}
void Camera::cancelScheduleImpl() { AnimatedBase::cancelScheduleImpl(); finishTransition(false); }
Camera& Camera::stopIt() {
    AnimatedBase::stopIt();
    if (mTransitionDestination && !animationChannelScheduled(&mTransitionProgress)) finishTransition(false);
    return *this;
}
Camera& Camera::restartIt() {
    if (!mTransitionDestination && animationChannelSelected(&mTransitionProgress)) throw std::logic_error("Completed or cancelled camera handoffs must be requested again");
    AnimatedBase::restartIt(); return *this;
}
bool Camera::canPick() const { return !isHidden() && !(mTransitionSource && mTransitionSource->mTransitionActive && !(mTransitionSource->mMatch && mTransitionSource->mMatch->settling)); }
AnimatedBase* Camera::followedTarget() const { auto lifetime=mFollowTarget.lock(); return lifetime?*lifetime:nullptr; }
void Camera::animationChannelAcquired(float* field) {
    if (field==&mLocation.x || field==&mLocation.y || field==&mDeltaXPerMs || field==&mDeltaYPerMs) stopFollowing();
}
Camera& Camera::getEffects() {
    if (mEffectsOwned) throw std::logic_error("Camera effects cannot own a nested effects stage");
    if (!mEffects) {mEffects=new Camera(); mEffects->addRef(); mEffects->mEffectsOwned=true;}
    return *mEffects;
}
Camera& Camera::flash(float opacity, double seconds, EasingFunc easing) {
    if(recordOperation("flash", captureAnimationArguments(opacity, seconds, easing))) return *this;
    if (!std::isfinite(opacity) || opacity<0 || opacity>1 || !easing)
        throw std::invalid_argument("Flash opacity must be from zero to one with valid easing");
    validateDuration(seconds);
    batch();
    recordScriptAnimation({{animationChannel_CameraFlashOpacity,opacity}},0,linearTween,animationMode_Assign,rotationDirection_AsSpecified,0,CLASSTAG_CAMERA);
    andThen();
    recordScriptAnimation({{animationChannel_CameraFlashOpacity,0}},seconds,easing,animationMode_Assign,rotationDirection_AsSpecified,0,CLASSTAG_CAMERA);
    endBatch();
    return *this;
}
Camera& Camera::setViewport(const Rect& viewport) {
    if(recordOperation("setViewport", captureAnimationArguments(viewport))) return *this;
    validateRect(viewport);
    if (viewport.empty()) throw std::invalid_argument("Camera viewport must be nonempty");
    if (mOwnerPort) throw std::logic_error("A Port camera viewport is controlled by its Port");
    mViewport=viewport; mHasViewport=true; return *this;
}
Rect Camera::getViewport() const {
#ifndef PDG_NO_GUI
    if (mOwnerPort) return mOwnerPort->getDrawingArea();
#endif
    return mViewport;
}
#ifndef PDG_NO_GUI
void Camera::ensureViewport(Port& port) {
    if (mOwnerPort && mOwnerPort!=&port) throw std::logic_error("A Port camera cannot be assigned to another Port's layers; follow it instead");
    if (!mHasViewport && !mOwnerPort) { mViewport=port.getDrawingArea(); mHasViewport=true; }
}
SpatialTransform Camera::viewportTransform(float movementRatio, float zoomRatio) const {
    const auto viewport=getViewport();
    const auto anchor=mOwnerPort ? mOwnerPort->getCameraAnchor() : viewport.centerPoint();
    return getViewTransform(anchor,movementRatio,zoomRatio,viewport);
}
#endif

Camera& Camera::follow(AnimatedBase& target) {
    if(recordOperation("follow", captureAnimationArguments(target))) return *this;
    validateImmediateOperation();
    for (auto* owner = &target; owner;) {
        if (owner == this) throw std::invalid_argument("Camera following cannot form a cycle");
        auto* camera = dynamic_cast<Camera*>(owner);
        owner = camera ? camera->followedTarget() : nullptr;
    }
    const Point targetPosition=target.getLocation();
    stopFollowing();
    cancelAnimation(&mLocation.x); cancelAnimation(&mLocation.y);
    cancelAnimation(&mDeltaXPerMs); cancelAnimation(&mDeltaYPerMs);
    mDeltaXPerMs = mDeltaYPerMs = 0;
    mFollowTarget = target.animationLifetime();
    mPreviousTarget = targetPosition; mHasPreviousTarget = true;
    return *this;
}
Camera& Camera::stopFollowing() {
    if(recordOperation("stopFollowing", captureAnimationArguments())) return *this;
    mFollowTarget.reset(); mHasPreviousTarget = false;
    return *this;
}
Camera& Camera::setSmoothing(double seconds) {
    if(recordOperation("setSmoothing", captureAnimationArguments(seconds))) return *this;
    validateDuration(seconds);
    mSmoothing = seconds;
    return *this;
}
Camera& Camera::setLookAhead(double seconds) {
    if(recordOperation("setLookAhead", captureAnimationArguments(seconds))) return *this;
    validateDuration(seconds);
    mLookAhead = seconds;
    return *this;
}
Camera& Camera::setDeadzone(const Rect& bounds) {
    if(recordOperation("setDeadzone", captureAnimationArguments(bounds))) return *this;
    validateRect(bounds);
    mDeadzone = bounds;
    return *this;
}
Camera& Camera::setFollowOffset(const Offset& offset) {
    if(recordOperation("setFollowOffset", captureAnimationArguments(offset))) return *this;
    if (!std::isfinite(offset.x) || !std::isfinite(offset.y)) throw std::invalid_argument("Camera follow offset must be finite");
    mFollowOffset = offset; return *this;
}
Camera& Camera::setViewBounds(const Rect& bounds) {
    if(recordOperation("setViewBounds", captureAnimationArguments(bounds))) return *this;
    validateRect(bounds);
    mViewBounds = bounds;
    mHasViewBounds = true;
    return *this;
}
bool Camera::animate(double seconds) {
    validateDuration(seconds);
    if (mMatch) {mMatch->velocitySampledFrame=false;mMatch->frameSeconds=seconds;}
    const bool matching=mMatch || (mTransitionSource && mTransitionSource->mMatch);
    bool changed=matching?advanceFollowing(seconds):false;
    bool effectsChanged=matching && mEffects?mEffects->animate(seconds):false;
    try {
        changed = AnimatedBase::animate(seconds) || changed;
        if (mTransitionDestination) {
            validateTransitionDestination(*mTransitionDestination,mTransitionIsCut);
            if (!animationChannelScheduled(&mTransitionProgress)) finishTransition(false);
        }
    } catch (...) {finishTransition(false);throw;}
    if (!matching) {
        effectsChanged=mEffects?mEffects->animate(seconds):false;
        changed=advanceFollowing(seconds) || changed;
    }
    return changed || effectsChanged;
}
bool Camera::advanceFollowing(double seconds) {
    if (mSchedulePaused || !followedTarget()) return false;
    const Point sample = followedTarget()->getLocation();
    const double prediction = seconds > 0 && mHasPreviousTarget ? mLookAhead / seconds : 0;
    const Point desired(sample.x + mFollowOffset.x + (sample.x-mPreviousTarget.x)*prediction,
                        sample.y + mFollowOffset.y + (sample.y-mPreviousTarget.y)*prediction);
    mPreviousTarget = sample; mHasPreviousTarget = true;
    const double dx = desired.x - mLocation.x - mCenterOffset.x;
    const double dy = desired.y - mLocation.y - mCenterOffset.y;
    const double weight = mSmoothing == 0 ? 1 : -std::expm1(-seconds/mSmoothing);
    const Point before = mLocation;
    mLocation.x += (dx-std::clamp(dx,double(mDeadzone.left),double(mDeadzone.right)))*weight;
    mLocation.y += (dy-std::clamp(dy,double(mDeadzone.top),double(mDeadzone.bottom)))*weight;
    return before != mLocation;
}
Point Camera::worldToView(const Point& point) const {
#ifndef PDG_NO_GUI
    return viewportTransform().transformPoint(point);
#else
    return getViewTransform(mViewport.centerPoint(),1,1,mViewport).transformPoint(point);
#endif
}
Point Camera::viewToWorld(const Point& point) const {
#ifndef PDG_NO_GUI
    return viewportTransform().inverse().transformPoint(point);
#else
    return getViewTransform(mViewport.centerPoint(),1,1,mViewport).inverse().transformPoint(point);
#endif
}
uint32 Camera::getSerializedSize(ISerializer* serializer) const {
    if (mTransitionDestination || mTransitionSource) throw std::runtime_error("Cancel Camera transitions before saving a snapshot");
    if (isFollowing()) throw std::runtime_error("Stop Camera following before saving a snapshot");
    if (!mHelpers.empty()) throw std::runtime_error("Camera snapshots cannot save callback helpers");
    return AnimatedBase::getSerializedSize(serializer)+serializer->sizeof_bool(mPixelSnapping)
        +serializer->sizeof_d(mSmoothing)+serializer->sizeof_d(mLookAhead)+serializer->sizeof_rect(mDeadzone)
        +serializer->sizeof_offset(mFollowOffset)+serializer->sizeof_bool(mHasViewBounds)+serializer->sizeof_rect(mViewBounds)
        +serializer->sizeof_bool(mHasViewport)+serializer->sizeof_rect(getViewport())+serializer->sizeof_obj(mEffects);
}
void Camera::serialize(ISerializer* serializer) const {
    if (mTransitionDestination || mTransitionSource) throw std::runtime_error("Cancel Camera transitions before saving a snapshot");
    if (isFollowing()) throw std::runtime_error("Stop Camera following before saving a snapshot");
    if (!mHelpers.empty()) throw std::runtime_error("Camera snapshots cannot save callback helpers");
    AnimatedBase::serialize(serializer); serializer->serialize_bool(mPixelSnapping);
    serializer->serialize_d(mSmoothing); serializer->serialize_d(mLookAhead); serializer->serialize_rect(mDeadzone);
    serializer->serialize_offset(mFollowOffset); serializer->serialize_bool(mHasViewBounds); serializer->serialize_rect(mViewBounds);
    serializer->serialize_bool(mHasViewport || mOwnerPort); serializer->serialize_rect(getViewport());
    serializer->serialize_obj(mEffects);
}
void Camera::deserialize(IDeserializer* deserializer) {
    if (mTransitionSource) mTransitionSource->finishTransition(false);
    finishTransition(false);
    stopFollowing(); AnimatedBase::deserialize(deserializer); mPixelSnapping=deserializer->deserialize_bool();
    setSmoothing(deserializer->deserialize_d()); setLookAhead(deserializer->deserialize_d()); setDeadzone(deserializer->deserialize_rect());
    setFollowOffset(deserializer->deserialize_offset()); mHasViewBounds=deserializer->deserialize_bool(); mViewBounds=deserializer->deserialize_rect(); validateRect(mViewBounds);
    mHasViewport=deserializer->deserialize_bool(); mViewport=deserializer->deserialize_rect(); validateRect(mViewport);
    if (mHasViewport && mViewport.empty()) throw std::runtime_error("Invalid Camera viewport snapshot");
    auto* restored=deserializer->deserialize_obj(); auto* effects=dynamic_cast<Camera*>(restored);
    if (restored && !effects) {restored->release();throw std::runtime_error("Invalid Camera effects snapshot");}
    if (effects==this || (effects && effects->mEffects)) throw std::runtime_error("Camera effects snapshot must not form a cycle");
    if (effects) effects->addRef();
    if (mEffects) {mEffects->mEffectsOwned=false;mEffects->release();} mEffects=effects;
    if (mEffects) mEffects->mEffectsOwned=true;
    getViewTransform();
    validateOpacity(mOpacity);
    if (mHidden!=0 && mHidden!=1) throw std::runtime_error("Invalid Camera visibility snapshot");
}
Camera& Camera::setZoom(float zoom) {
    if(recordOperation("setZoom", captureAnimationArguments(zoom))) return *this;
    validateZoom(zoom);
    if (recordScriptAnimation({{animationChannel_CameraZoom,zoom}},0,linearTween)) return *this;
    validateImmediateOperation();
    prepareAnimation(&mZoom);
    mZoom = zoom;
    return *this;
}
Camera& Camera::zoomTo(float zoom, double seconds, EasingFunc easing) {
    if(recordOperation("zoomTo", captureAnimationArguments(zoom, seconds, easing))) return *this;
    return zoomImpl(zoom, seconds, easing, false);
}
Camera& Camera::zoom(float factor, double seconds, EasingFunc easing) {
    if(recordOperation("zoom", captureAnimationArguments(factor, seconds, easing))) return *this;
    return zoomImpl(factor, seconds, easing, true);
}
Camera& Camera::zoomImpl(float value, double seconds, EasingFunc easing, bool relative) {
    validateZoom(value);
    if (recordScriptAnimation({{animationChannel_CameraZoom,value}},seconds,easing,relative?animationMode_Multiply:animationMode_Assign,rotationDirection_AsSpecified,1)) return *this;
    validateAnimationDuration(seconds);
    if (!easing) throw std::invalid_argument("Camera easing must be valid");
    const bool deferredFactor = relative && mAppendAnimation;
    const float target = relative && !deferredFactor ? mZoom * value : value;
    validateZoom(target);
    const bool immediate = !mAppendAnimation && seconds == 0 && mDelaySeconds == 0;
    beginAnimationRequest();
    scheduleAnimation(&mZoom, target, seconds, easing);
    if (!immediate) {
        mAnimations.back().completion = 1;
        if (deferredFactor) mAnimations.back().targetMode = animationMode_Multiply;
    }
    finishAnimationRequest();
    if (immediate) notifyZoomComplete(target);
    return *this;
}
void Camera::animationStarting(Animation& a) {
    if (a.value == &mZoom) validateZoom(a.targetVal);
    if (a.value==&mTransitionProgress && a.completion==1 && mMatch) {startTransition();updateMatch();}
}
void Camera::easingCompleted(const Animation& a) {
    if (a.value == &mZoom && a.completion) notifyZoomComplete(a.targetVal);
    if (a.value == &mTransitionProgress) {
        if (a.completion==3) startTransition();
        else if (a.completion==1) {const float progress=mTransitionProgress;mTransitionProgress=1;cutMatch();mTransitionProgress=progress;if (mMatch) updateMatch();}
        else if (a.completion==2) finishTransition(true);
    }
}
void Camera::notifyZoomComplete(float zoom) {
    CameraZoomInfo event{this, zoom};
    postEvent(eventType_ZoomComplete, &event);
}
std::vector<const float*> Camera::tweenFields() const {
    auto fields = AnimatedBase::tweenFields();
    fields.resize(animationChannel_CameraTransition + 1);
    fields[animationChannel_CameraZoom] = &mZoom;
    fields[animationChannel_CameraFlashOpacity] = &mFlashOpacity;
    fields[animationChannel_CameraOpacity] = &mOpacity;
    fields[animationChannel_CameraHidden] = &mHidden;
    fields[animationChannel_CameraTransition] = &mTransitionProgress;
    return fields;
}
SpatialTransform Camera::getViewTransform(const Point& anchor, float movementRatio, float zoomRatio, const Rect& viewport) const {
    const auto effect = mEffects ? mEffects->getViewTransform() : SpatialTransform();
    const ViewTransformInputs inputs{
        anchor, mLocation, mCenterOffset, mMatchShift,
        {viewport.left, viewport.top, viewport.right, viewport.bottom},
        {mViewBounds.left, mViewBounds.top, mViewBounds.right, mViewBounds.bottom},
        movementRatio, zoomRatio, mFacing, mScaleX, mScaleY, mZoom,
        mMatchLogZoom, mFlipX, mFlipY, mPixelSnapping, mHasViewBounds,
        {effect.a, effect.b, effect.c, effect.d, effect.tx, effect.ty}
    };
    if (mViewTransformValid && inputs == mViewTransformInputs) return mViewTransform;

    validateZoom(mZoom);
    auto view = SpatialTransform::fromTRS(0, 0, -mFacing);
    const double sx = std::pow(mZoom*std::exp(mMatchLogZoom),zoomRatio) * mScaleX * (mFlipX ? -1 : 1);
    const double sy = std::pow(mZoom*std::exp(mMatchLogZoom),zoomRatio) * mScaleY * (mFlipY ? -1 : 1);
    if (!std::isfinite(sx) || !std::isfinite(sy) || sx == 0 || sy == 0)
        throw std::invalid_argument("Camera scale must be finite and nonzero");
    view.a *= sx; view.c *= sx; view.b *= sy; view.d *= sy;
    view.tx = anchor.x - view.a*((mLocation.x+mMatchShift.x)*movementRatio+mCenterOffset.x) - view.c*((mLocation.y+mMatchShift.y)*movementRatio+mCenterOffset.y);
    view.ty = anchor.y - view.b*((mLocation.x+mMatchShift.x)*movementRatio+mCenterOffset.x) - view.d*((mLocation.y+mMatchShift.y)*movementRatio+mCenterOffset.y);
    if (!std::isfinite(view.a) || !std::isfinite(view.b) || !std::isfinite(view.c) ||
        !std::isfinite(view.d) || !std::isfinite(view.tx) || !std::isfinite(view.ty))
        throw std::invalid_argument("Camera transform must be finite");
    if (mEffects) {
        const auto aroundAnchor=SpatialTransform::compose(SpatialTransform::fromTRS(anchor.x,anchor.y,0),
            SpatialTransform::compose(effect,SpatialTransform::fromTRS(-anchor.x,-anchor.y,0)));
        view=SpatialTransform::compose(aroundAnchor,view);
    }
    if (mHasViewBounds && !viewport.empty()) {
        validateRect(viewport);
        Quad corners(viewport); const auto inverse = view.inverse();
        for (auto& point : corners.points) point = inverse.transformPoint(point);
        const Rect visible = corners.getBounds();
        auto shift = [](double left, double right, double minimum, double maximum) {
            if (right-left > maximum-minimum) return (minimum+maximum-left-right)/2;
            return std::clamp(0.0, minimum-left, maximum-right);
        };
        const double x = shift(visible.left,visible.right,mViewBounds.left,mViewBounds.right);
        const double y = shift(visible.top,visible.bottom,mViewBounds.top,mViewBounds.bottom);
        view.tx -= view.a*x+view.c*y; view.ty -= view.b*x+view.d*y;
    }
    if (mPixelSnapping) { view.tx = std::round(view.tx); view.ty = std::round(view.ty); }
    // Only publish a cache entry after validation and composition succeed.
    mViewTransformInputs = inputs;
    mViewTransform = view;
    mViewTransformValid = true;
    return view;
}
void Camera::attach() {
    if (mEffectsOwned) throw std::logic_error("Camera effects are advanced by their owning camera and cannot be attached");
    if (!mAttachments) attachedCameras().push_back(this);
    ++mAttachments; addRef();
}
void Camera::detach() {
    if (!mAttachments) throw std::logic_error("Camera has no attachment to detach");
    if (!--mAttachments) {
        finishTransition(false);
        if (mTransitionSource) mTransitionSource->finishTransition(false);
        auto& cameras = attachedCameras(); cameras.erase(std::remove(cameras.begin(), cameras.end(), this), cameras.end());
    }
    release();
}
void Camera::advanceAttached(double seconds) {
    // Helpers can replace attachments during animation; retain the tick snapshot.
    auto cameras = attachedCameras();
    for (auto* camera : cameras) camera->addRef();
    struct Release { std::vector<Camera*>& cameras; ~Release() { for (auto* camera : cameras) camera->release(); } } release{cameras};
    // Incoming base/follow/effects state must be current before the outgoing owner solves the cut.
    std::stable_sort(cameras.begin(),cameras.end(),[](Camera* a,Camera* b){
        const bool incomingA=a->mTransitionSource && a->mTransitionSource->mMatch;
        const bool incomingB=b->mTransitionSource && b->mTransitionSource->mMatch;
        return incomingA && !incomingB;
    });
    for (auto* camera : cameras) if (camera->mAttachments && !camera->mSceneOwner) camera->animate(seconds);
}
}

namespace pdg {
#include "animation-operations-camera.inc"
}
