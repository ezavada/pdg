// this C++ file contains all the code that adapts between the JavaScript and C++ classes, which
// do not always have identical method signatures

#include "pdg_em_adaptors.h"
#include "pdg-lib.h"

#ifndef PDG_NO_GUI
#include "glfw/internals-glfw.h"
#include "image-opengl.h"
#endif

#include <emscripten.h>

#include <algorithm>
#include <array>
#include <stdexcept>
#include <memory>
#include <unordered_map>
#include <vector>


namespace pdg {

namespace {

emscripten::val pointToVal(const Point& point) {
    emscripten::val result = emscripten::val::object();
    result.set("x", point.x);
    result.set("y", point.y);
    return result;
}

void setModifierKeys(emscripten::val& event, const ModifierKeyInfo& info) {
    event.set("shift", info.shift);
    event.set("ctrl", info.ctrl);
    event.set("alt", info.alt);
    event.set("meta", info.meta);
}

void setMouseInfo(emscripten::val& event, const MouseInfo& info) {
    setModifierKeys(event, info);
    event.set("mousePos", pointToVal(info.mousePos));
    event.set("leftButton", info.leftButton);
    event.set("rightButton", info.rightButton);
    event.set("buttonNumber", info.buttonNumber);
    event.set("lastClickPos", pointToVal(info.lastClickPos));
    event.set("lastClickElapsed", static_cast<double>(info.lastClickElapsed));
}

}  // namespace

class EmscriptenEventBridge : public IEventHandler {
public:
    explicit EmscriptenEventBridge(const emscripten::val& jsEmitter)
        : mJsEmitter(jsEmitter), mRefs(0) {}

    void addRef() const noexcept override { ++mRefs; }
    void release() const noexcept override {
        if (--mRefs == 0) delete this;
    }

    bool handleEvent(EventEmitter*, long eventType, void* eventData) noexcept override {
        try {
            emscripten::val event = emscripten::val::object();
            event.set("emitter", mJsEmitter);
            if (eventData && eventType == eventType_Shutdown) {
                const ShutdownInfo* info = static_cast<const ShutdownInfo*>(eventData);
                event.set("exitReason", info->exitReason);
                event.set("exitCode", info->exitCode);
            } else if (eventData && eventType == eventType_Timer) {
                const TimerInfo* info = static_cast<const TimerInfo*>(eventData);
                if (info->id <= 0) return false;
                event.set("id", info->id);
                event.set("millisec", static_cast<double>(info->millisec));
                event.set("msElapsed", static_cast<double>(info->msElapsed));
            } else if (eventData &&
                       (eventType == eventType_KeyDown || eventType == eventType_KeyUp)) {
                event.set("keyCode", static_cast<const KeyInfo*>(eventData)->keyCode);
            } else if (eventData && eventType == eventType_KeyPress) {
                const KeyPressInfo* info = static_cast<const KeyPressInfo*>(eventData);
                setModifierKeys(event, *info);
                event.set("unicode", static_cast<int>(info->unicode));
                event.set("isRepeating", info->isRepeating);
            } else if (eventData &&
                       (eventType == eventType_MouseDown || eventType == eventType_MouseUp ||
                        eventType == eventType_MouseMove)) {
                setMouseInfo(event, *static_cast<const MouseInfo*>(eventData));
            } else if (eventData &&
                       (eventType == eventType_MouseEnter || eventType == eventType_MouseLeave)) {
                const MouseTrackingInfo* info =
                    static_cast<const MouseTrackingInfo*>(eventData);
                setMouseInfo(event, *info);
                event.set("entering", info->entering);
                event.set("trackingRef", info->trackingRef);
            } else if (eventData && eventType == eventType_ScrollWheel) {
                const ScrollWheelInfo* info = static_cast<const ScrollWheelInfo*>(eventData);
                setModifierKeys(event, *info);
                event.set("horizDelta", info->horizDelta);
                event.set("vertDelta", info->vertDelta);
            } else if (eventData && eventType == eventType_PortResized) {
                const PortResizeInfo* info = static_cast<const PortResizeInfo*>(eventData);
                event.set("portIdentity", reinterpret_cast<uintptr_t>(info->port));
                event.set("screenPos", info->screenPos);
                event.set("oldScreenPos", info->oldScreenPos);
                event.set("oldWidth", info->oldWidth);
                event.set("oldHeight", info->oldHeight);
            } else if (eventData && eventType == eventType_SpriteLayer) {
                const SpriteLayerInfo* info = static_cast<const SpriteLayerInfo*>(eventData);
                event.set("action", info->action);
                event.set("actingLayer", mJsEmitter);
                event.set("millisec", static_cast<double>(info->millisec));
            } else if (eventData && eventType == eventType_ColliderContact) {
                const auto* info = static_cast<const ColliderContact*>(eventData);
                auto handle=[](Collider* c) { c->addRef(); return std::shared_ptr<Collider>(c,[](Collider* p){p->release();}); };
                const auto canonical=emscripten::val::global("pdg")["_canonicalPhysicsOwner"];
                event.set("collider",canonical(emscripten::val(handle(info->collider))));
                event.set("other",canonical(emscripten::val(handle(info->other))));
                event.set("shape",info->shape);event.set("otherShape",info->otherShape);event.set("phase",info->phase);
                event.set("point",pointToVal(info->point));event.set("normal",pointToVal(Point(info->normal.x,info->normal.y)));
                event.set("impulse",pointToVal(Point(info->impulse.x,info->impulse.y)));
                event.set("penetration",info->penetration);event.set("sensor",info->sensor);
            } else if (eventData && eventType == eventType_ParticleBreak) {
                const auto* info = static_cast<const PhysicsBodyBreakInfo*>(eventData);
                const auto canonical=emscripten::val::global("pdg")["_canonicalPhysicsOwner"];
                auto handle=[&](PhysicsBody* value) {
                    if (!value) return emscripten::val::null();
                    value->addRef();
                    return canonical(emscripten::val(std::shared_ptr<PhysicsBody>(value,[](PhysicsBody* p){p->release();})));
                };
                event.set("body",handle(info->body)); event.set("referenceBody",handle(info->referenceBody));
                event.set("angularSpeed",info->angularSpeed); event.set("breakAngularSpeed",info->breakAngularSpeed);
            } else if (eventData && eventType == eventType_SpriteBreak) {
                const auto* info = static_cast<const SpriteJointBreakInfo*>(eventData);
                const auto canonical=emscripten::val::global("pdg")["_canonicalPhysicsOwner"];
                auto handle=[&](auto* value) {
                    using T = std::remove_pointer_t<decltype(value)>;
                    if (!value) return emscripten::val::null();
                    value->addRef();
                    return canonical(emscripten::val(std::shared_ptr<T>(value,[](T* p){p->release();})));
                };
                event.set("action",info->action); event.set("reason",info->reason);
                event.set("actingSprite",handle(info->actingSprite));
                event.set("inLayerIdentity",reinterpret_cast<uintptr_t>(info->inLayer));
                event.set("targetSprite",emscripten::val::null()); event.set("joint",emscripten::val::null());
                event.set("body",handle(info->body)); event.set("part",handle(info->part));
                event.set("referenceBody",handle(info->referenceBody));
                event.set("angularSpeed",info->angularSpeed); event.set("breakAngularSpeed",info->breakAngularSpeed);
                event.set("impulse",info->impulse); event.set("force",info->force); event.set("breakForce",info->breakForce);
            } else if (eventData && eventType == eventType_SpriteCollide) {
                const SpriteCollideInfo* info = static_cast<const SpriteCollideInfo*>(eventData);
                event.set("action", info->action);
                event.set("actingSprite", mJsEmitter);
                event.set("inLayerIdentity", reinterpret_cast<uintptr_t>(info->inLayer));
                event.set("targetSpriteIdentity", reinterpret_cast<uintptr_t>(info->targetSprite));
                event.set("normal", pointToVal(Point(info->normal.x, info->normal.y)));
                event.set("impulse", pointToVal(Point(info->impulse.x, info->impulse.y)));
                event.set("force", info->force);
                event.set("kineticEnergy", info->kineticEnergy);
                event.set("isFirstContact", info->isFirstContact);
                event.set("collisionName", info->collisionName
                    ? emscripten::val(info->collisionName) : emscripten::val::null());
                event.set("withCollisionName", info->withCollisionName
                    ? emscripten::val(info->withCollisionName) : emscripten::val::null());
            } else if (eventData && eventType == eventType_SpriteTriggerEvent) {
                const auto* info=static_cast<const SpriteTriggerEventInfo*>(eventData);
                event.set("triggerName",std::string(info->triggerName));event.set("clipName",std::string(info->clipName));event.set("entityName",std::string(info->entityName));
                event.set("timeSeconds",info->timeSeconds);event.set("offsetSeconds",info->offsetSeconds);
                event.set("actingSprite",mJsEmitter);event.set("inLayerIdentity",reinterpret_cast<uintptr_t>(info->inLayer));event.set("id",info->id);
            } else if (eventData && eventType == eventType_SpriteAnimate) {
                const SpriteAnimateInfo* info = static_cast<const SpriteAnimateInfo*>(eventData);
                event.set("action", info->action);
                event.set("actingSprite", mJsEmitter);
                event.set("inLayerIdentity",reinterpret_cast<uintptr_t>(info->inLayer));
                event.set("id", info->id);
                if(info->action==Sprite::action_AnimationPhysicsRecoveryComplete) {
                    const auto* recovery=static_cast<const SpriteAnimationPhysicsRecoveryInfo*>(info);
                    event.set("bone",recovery->bone);
                    event.set("wholeRig",recovery->wholeRig);
                    event.set("includeDescendants",recovery->includeDescendants);
                    event.set("mode",recovery->mode);
                    event.set("bodyCount",recovery->bodyCount);
                    event.set("disabled",recovery->disabled);
                }
            } else if (eventData && eventType == eventType_SoundEvent) {
                const SoundEventInfo* info = static_cast<const SoundEventInfo*>(eventData);
                event.set("eventCode", info->eventCode);
                event.set("sound", mJsEmitter);
            } else if (eventData && eventType == eventType_PortDraw) {
                const PortDrawInfo* info = static_cast<const PortDrawInfo*>(eventData);
                event.set("portIdentity", reinterpret_cast<uintptr_t>(info->port));
                event.set("frameNum", info->frameNum);
            }
            return mJsEmitter.call<bool>("__dispatchNativeEvent", eventType, event);
        } catch (...) {
            return false;
        }
    }

private:
    emscripten::val mJsEmitter;
    mutable int mRefs;
};

void emscriptenEventEmitterAddBridge(EventEmitter& emitter, long eventType,
                                     const emscripten::val& jsEmitter) {
    emitter.addHandler(new EmscriptenEventBridge(jsEmitter), eventType);
}

void emscriptenSpriteAddEventBridge(Sprite& emitter, long eventType,
                                    const emscripten::val& jsEmitter) {
    emitter.addHandler(new EmscriptenEventBridge(jsEmitter), eventType);
}

void emscriptenSpriteLayerAddEventBridge(SpriteLayer& emitter, long eventType,
                                         const emscripten::val& jsEmitter) {
    emitter.addHandler(new EmscriptenEventBridge(jsEmitter), eventType);
}

void emscriptenEventManagerAddEventBridge(EventManager& emitter, long eventType,
                                          const emscripten::val& jsEmitter) {
    emitter.addHandler(new EmscriptenEventBridge(jsEmitter), eventType);
}

SpriteLayer* emscriptenCreateSpriteLayer() {
#ifndef PDG_NO_GUI
    return createSpriteLayer(nullptr);
#else
    return createSpriteLayer();
#endif
}

TileLayer* emscriptenCreateTileLayer() {
#ifndef PDG_NO_GUI
    return createTileLayer(nullptr);
#else
    return createTileLayer();
#endif
}

SpriteLayer* emscriptenCreateSpriteLayerForPort(Port* port) {
#ifndef PDG_NO_GUI
    return createSpriteLayer(port);
#else
    return emscriptenCreateSpriteLayer();
#endif
}

TileLayer* emscriptenCreateTileLayerForPort(Port* port) {
#ifndef PDG_NO_GUI
    return createTileLayer(port);
#else
    return emscriptenCreateTileLayer();
#endif
}

#ifndef PDG_NO_GUI
emscripten::val emscriptenGraphicsGetCurrentScreenMode(GraphicsManager& manager, int screenNum) {
    Rect maxWindowRect;
    GraphicsManager::ScreenMode mode = manager.getCurrentScreenMode(screenNum, &maxWindowRect);
    emscripten::val result = emscripten::val::object();
    result.set("width", mode.width);
    result.set("height", mode.height);
    result.set("depth", mode.bpp);
    emscripten::val maxRect = emscripten::val::object();
    maxRect.set("left", maxWindowRect.left);
    maxRect.set("top", maxWindowRect.top);
    maxRect.set("right", maxWindowRect.right);
    maxRect.set("bottom", maxWindowRect.bottom);
    result.set("maxWindowRect", maxRect);
    return result;
}

emscripten::val emscriptenGraphicsGetNthSupportedScreenMode(GraphicsManager& manager, int n,
                                                            int screenNum) {
    GraphicsManager::ScreenMode mode = manager.getNthSupportedScreenMode(n, screenNum);
    emscripten::val result = emscripten::val::object();
    result.set("width", mode.width);
    result.set("height", mode.height);
    result.set("depth", mode.bpp);
    return result;
}

Port* emscriptenGraphicsCreateWindowPort(GraphicsManager& manager, const Rect& rect,
                                         const std::string& name, int bpp) {
    return manager.createWindowPort(rect, name.empty() ? nullptr : name.c_str(), bpp);
}

Port* emscriptenCreatePort(long width, long height) {
    return GraphicsManager::getSingletonInstance()->createWindowPort(
        Rect(0, 0, width, height), "PDG Emscripten Port", 0);
}

uintptr_t emscriptenPortGetIdentity(Port& port) {
    return reinterpret_cast<uintptr_t>(&port);
}

Font* emscriptenGraphicsCreateFont(GraphicsManager& manager, const std::string& name,
                                   float scalingFactor) {
    return manager.createFont(name.c_str(), scalingFactor);
}

static bool emscriptenReadDestinationRect(const emscripten::val& destination, Rect& rect) {
    const auto right = destination["right"];
    if (right.isUndefined()) return false;
    const auto bottom = destination["bottom"];
    if (bottom.isUndefined()) return false;
    // Retain value-object validation while reusing the dispatch reads.
    const auto readRequiredEdge = [](const emscripten::val& value) {
        if (value.isUndefined()) {
            emscripten::val::global("TypeError").new_(
                std::string("Rect requires left and top fields")).throw_();
        }
        return value.as<PDG_BASE_COORD_TYPE>();
    };
    const auto leftNumber = readRequiredEdge(destination["left"]);
    const auto topNumber = readRequiredEdge(destination["top"]);
    const auto rightNumber = right.as<PDG_BASE_COORD_TYPE>();
    const auto bottomNumber = bottom.as<PDG_BASE_COORD_TYPE>();
    rect = Rect(leftNumber, topNumber, rightNumber, bottomNumber);
    return true;
}

void emscriptenPortDrawImage(Port& port, Image* image, const emscripten::val& destination,
                             const Attributes& attributes) {
    const auto points = destination["points"];
    Rect rect;
    if (!points.isUndefined()) {
        const auto vertices = points.as<std::array<Point, 4>>();
        port.drawImage(image, Quad(vertices[0], vertices[1], vertices[2], vertices[3]), attributes);
    } else if (emscriptenReadDestinationRect(destination, rect)) {
        port.drawImage(image, rect, attributes);
    } else {
        port.drawImage(image, destination.as<Point>(), attributes);
    }
}

void emscriptenPortDrawDrawing(Port& port, const Drawing& drawing,
                               const emscripten::val& destination, const Attributes& attributes) {
    Rect rect;
    if (emscriptenReadDestinationRect(destination, rect)) {
        port.drawDrawing(drawing, rect, attributes);
    } else {
        port.drawDrawing(drawing, destination.as<Point>(), attributes);
    }
}

void emscriptenPortDrawText(Port& port, const std::string& text,
                            const emscripten::val& destination, const Attributes& attributes) {
    Rect rect;
    if (emscriptenReadDestinationRect(destination, rect)) {
        port.drawText(text.c_str(), rect, attributes);
    } else {
        port.drawText(text.c_str(), destination.as<Point>(), attributes);
    }
}

int emscriptenPortGetTextWidth(Port& port, const std::string& text, int size, uint32 style, int len) {
    return port.getTextWidth(text.c_str(), size, style, len);
}

int emscriptenPortStartTrackingMouse(Port& port, const Rect& rect) {
    return port.startTrackingMouse(rect, nullptr);
}

void emscriptenPortDrawCircle(Port& port, const Point& center, float radius,
                              const Attributes& attributes) {
    port.drawCircle(center, radius, attributes);
}

void emscriptenPortDrawQuad(Port& port, const emscripten::val& quad,
                            const Attributes& attributes) {
    const emscripten::val points = quad["points"];
    port.drawQuad(Quad(points[0].as<Point>(), points[1].as<Point>(),
                       points[2].as<Point>(), points[3].as<Point>()),
                  attributes);
}

std::string emscriptenFontGetName(Font& font) {
    return font.getFontName();
}

float emscriptenFontGetHeight(Font& font, int size, int style) {
    return font.getFontHeight(size, static_cast<uint32>(style));
}

float emscriptenFontGetLeading(Font& font, int size, int style) {
    return font.getFontLeading(size, static_cast<uint32>(style));
}

float emscriptenFontGetCapHeight(Font& font, int size, int style) {
    return font.getFontCapHeight(size, static_cast<uint32>(style));
}

float emscriptenFontGetAscent(Font& font, int size, int style) {
    return font.getFontAscent(size, static_cast<uint32>(style));
}

float emscriptenFontGetDescent(Font& font, int size, int style) {
    return font.getFontDescent(size, static_cast<uint32>(style));
}

void emscriptenDrawingDraw(Drawing& drawing, Port* port) {
    if (port) drawing.draw(port);
}

#ifdef PDG_SPRITER_SUPPORT

namespace {
using ScriptValue = emscripten::val;
ScriptValue poseTransformValue(const AnimationTransform& transform) {
    auto result = ScriptValue::object();
    result.set("x", transform.x); result.set("y", transform.y);
    result.set("rotation", transform.rotation);
    result.set("scaleX", transform.scaleX); result.set("scaleY", transform.scaleY);
    result.set("alpha", transform.alpha);
    return result;
}
ScriptValue poseNamesValue(const std::vector<std::string>& names) {
    auto result = ScriptValue::array();
    for (size_t i = 0; i < names.size(); ++i) result.set(i, names[i]);
    return result;
}
ScriptValue poseSnapshotValue(const AnimationPose& pose) {
    auto result = ScriptValue::object(), bones = ScriptValue::array(), bindings = ScriptValue::array();
    const auto& rig = pose.getRig();
    result.set("rigRevision", std::to_string(rig->getRevision()));
    for (AnimationBoneId id = 0; id < rig->getBoneCount(); ++id) {
        const auto& bone = rig->getBone(id);
        auto value = poseTransformValue(pose.getLocalTransform(id));
        value.set("name", bone.name);
        value.set("parent", bone.parent == animation_NoBone ? ScriptValue::null() : ScriptValue(bone.parent));
        bones.set(id, value);
    }
    for (AnimationBindingId id = 0; id < rig->getBindingCount(); ++id) {
        const auto& binding = rig->getBinding(id);
        auto value = poseTransformValue(pose.getBindingLocalTransform(id));
        value.set("name", binding.name);
        value.set("parent", binding.bone == animation_NoBone ? ScriptValue::null() : ScriptValue(binding.bone));
        value.set("kind", static_cast<int>(binding.kind));
        bindings.set(id, value);
    }
    auto variables = ScriptValue::array(), tags = ScriptValue::array();
    size_t id = 0;
    for (const auto& variable : pose.getMetadata().variables) {
        auto value = ScriptValue::object(); value.set("object", variable.object); value.set("name", variable.name);
        if (const auto* number = std::get_if<double>(&variable.value)) { value.set("type", static_cast<int>(animationVariable_Float)); value.set("value", *number); }
        else if (const auto* integer = std::get_if<int>(&variable.value)) { value.set("type", static_cast<int>(animationVariable_Int)); value.set("value", *integer); }
        else { value.set("type", static_cast<int>(animationVariable_String)); value.set("value", std::get<std::string>(variable.value)); }
        variables.set(id++, value);
    }
    id = 0;
    for (const auto& group : pose.getMetadata().tags) {
        auto value = ScriptValue::object(); value.set("object", group.object); value.set("tags", poseNamesValue(group.tags));
        tags.set(id++, value);
    }
    result.set("bones", bones); result.set("bindings", bindings);
    result.set("variables", variables); result.set("tags", tags);
    return result;
}
template<class Operation> auto poseScriptCall(Operation operation) -> decltype(operation()) {
    try { return operation(); }
    catch (const std::exception& error) { ScriptValue::global("Error").new_(std::string(error.what())).throw_(); }
}
}

void emscriptenSpriteSeekAnimation(Sprite& sprite,const std::string& clip,double seconds) {poseScriptCall([&]{sprite.seekAnimation(clip.c_str(),seconds);});}
void emscriptenSpriteTransitionToAnimation(Sprite& sprite,const std::string& clip,double seconds,double duration) {poseScriptCall([&]{sprite.transitionToAnimation(clip.c_str(),seconds,duration);});}
void emscriptenSpriteSetupAnimationPhysics(Sprite& sprite,emscripten::val values){poseScriptCall([&]{
    if(!ScriptValue::global("Array").call<bool>("isArray",values))throw std::invalid_argument("Invalid physical rig array");
    std::vector<double> numbers;const auto count=values["length"].as<unsigned>();if(count>1500000)throw std::invalid_argument("Invalid physical rig array length");
    for(unsigned i=0;i<count;++i){if(values[i].typeOf().as<std::string>()!="number")throw std::invalid_argument("Invalid physical rig number");numbers.push_back(values[i].as<double>());}
    sprite.setupAnimationPhysics(decodeAnimationPhysicsDefinition(numbers));});}
void emscriptenSpriteDisableAnimationPhysics(Sprite& sprite,double seconds,int direction){poseScriptCall([&]{sprite.disableAnimationPhysics(seconds,direction);});}
void emscriptenSpriteSetAnimationPhysicsMode(Sprite& sprite,int mode,double bone,bool descendants,double seconds,int direction){poseScriptCall([&]{if(bone<0)sprite.setAnimationPhysicsMode(mode,seconds,direction);else sprite.setAnimationPhysicsMode(mode,AnimationBoneId(bone),descendants,seconds,direction);});}
int emscriptenSpriteGetAnimationPhysicsMode(const Sprite& sprite,double bone,bool descendants){return poseScriptCall([&]{return bone<0?sprite.getAnimationPhysicsMode():sprite.getAnimationPhysicsMode(AnimationBoneId(bone),descendants);});}
void emscriptenSpriteSetAnimationPhysicsDriveSettings(Sprite& sprite,double force,double torque,double frequency,double damping,int direction,double bone,bool descendants){poseScriptCall([&]{AnimationPhysicsDriveSettings settings{force,torque,frequency,damping,direction};if(bone<0)sprite.setAnimationPhysicsDriveSettings(settings);else sprite.setAnimationPhysicsDriveSettings(settings,AnimationBoneId(bone),descendants);});}
emscripten::val emscriptenSpriteGetAnimationPhysicsDriveSettings(const Sprite& sprite,uint32_t bone){return poseScriptCall([&]{const auto settings=sprite.getAnimationPhysicsDriveSettings(bone);if(!settings)return emscripten::val::null();auto result=emscripten::val::array();int i=0;for(double value:{settings->maxForce,settings->maxTorque,settings->frequency,settings->dampingRatio,double(settings->direction)})result.set(i++,value);return result;});}
void emscriptenSpriteSetupPhysicsFromAnimationRig(Sprite& sprite,double mass,double units){poseScriptCall([&]{sprite.setupPhysicsFromAnimationRig(mass,units);});}
void emscriptenSpriteAttachAnimationPhysicsPart(Sprite& sprite,Part* part,Part* parent){poseScriptCall([&]{sprite.attachAnimationPhysicsPart(part,parent);});}
void emscriptenSpriteDetachAnimationPhysicsPart(Sprite& sprite,Part* part,bool descendants){poseScriptCall([&]{sprite.detachAnimationPhysicsPart(part,descendants);});}
void emscriptenSpriteSetAnimationPhysicsRoot(Sprite& sprite,uint32_t bone){poseScriptCall([&]{sprite.setAnimationPhysicsRoot(bone);});}
void emscriptenSpriteClearAnimationPhysicsRoot(Sprite& sprite){poseScriptCall([&]{sprite.clearAnimationPhysicsRoot();});}
uint32_t emscriptenSpriteGetAnimationPhysicsRoot(const Sprite& sprite){return poseScriptCall([&]{return sprite.getAnimationPhysicsRoot();});}

uint32_t emscriptenSpriteAddAnimationDrawable(Sprite& sprite,emscripten::val callback,emscripten::val values,const std::string& slot){return poseScriptCall([&]{
    if(!ScriptValue::global("Array").call<bool>("isArray",values)||values["length"].as<unsigned>()!=9)throw std::invalid_argument("Invalid drawing options");
    std::vector<double> numbers;for(unsigned i=0;i<9;++i){if(values[i].typeOf().as<std::string>()!="number")throw std::invalid_argument("Invalid drawing option");numbers.push_back(values[i].as<double>());}
    auto options=decodeAnimationDrawableOptions(numbers,slot);
    if(callback.typeOf().as<std::string>()!="function"){
        auto* drawing=callback.as<Drawing*>(emscripten::allow_raw_pointers());
        if(!drawing)throw std::invalid_argument("Expected a Drawing or callback");
        return sprite.addAnimationDrawable(options,*drawing);
    }
    return sprite.addAnimationDrawable(options,[callback](AnimationDrawingContext context)->std::shared_ptr<Drawing>{
        auto result=callback(poseSnapshotValue(context.copyPose()),poseTransformValue(context.getTransform(animationSpace_Local)),poseTransformValue(context.getTransform(animationSpace_Rig)),poseTransformValue(context.getTransform(animationSpace_World)));
        if(result.typeOf().as<std::string>()=="string")throw std::runtime_error(result.as<std::string>());
        if(result.isNull())return {};
        auto* drawing=result.as<Drawing*>(emscripten::allow_raw_pointers());
        if(!drawing)throw std::invalid_argument("Animation drawing callback must return a Drawing or null");
        return drawing->share();
    });});}
void emscriptenSpriteSetAnimationDrawableEnabled(Sprite& sprite,uint32_t id,bool enabled){poseScriptCall([&]{sprite.setAnimationDrawableEnabled(id,enabled);});}
std::string emscriptenSpriteGetAnimationDrawableError(const Sprite& sprite,uint32_t id){return poseScriptCall([&]{return sprite.getAnimationDrawableError(id);});}
emscripten::val emscriptenSpriteGetAnimationDrawBounds(const Sprite& sprite){return poseScriptCall([&]{const auto bounds=sprite.getAnimationDrawBounds();auto result=ScriptValue::object();result.set("left",bounds.left);result.set("top",bounds.top);result.set("right",bounds.right);result.set("bottom",bounds.bottom);result.set("uncullable",bounds.uncullable);return result;});}

uint32_t emscriptenSpriteAddAnimationIK(Sprite& sprite, emscripten::val object, int order) {
    return poseScriptCall([&]{AnimationTwoBoneIK config;
        config.root=object["root"].as<unsigned>();
        config.middle=object["middle"].as<unsigned>();
        config.tip=object["tip"].as<unsigned>();
        config.rootLength=object["rootLength"].as<double>();
        config.middleLength=object["middleLength"].as<double>();
        config.targetX=object["targetX"].as<double>();
        config.targetY=object["targetY"].as<double>();
        config.influence=object["influence"].as<double>();
        config.space=object["space"].as<int>();
        config.bendDirection=object["bendDirection"].as<int>();
        config.stretch=object["stretch"].as<int>();
        config.matchOrientation=object["matchOrientation"].as<int>();
        config.targetRotation=object["targetRotation"].as<double>();
        config.rootMin=object["rootMin"].as<double>();
        config.rootMax=object["rootMax"].as<double>();
        config.middleMin=object["middleMin"].as<double>();
        config.middleMax=object["middleMax"].as<double>();
        return sprite.addAnimationIK(config,order);});
}
void emscriptenSpriteSetAnimationIKTarget(Sprite& sprite,uint32_t id,double x,double y,int space) {poseScriptCall([&]{sprite.setAnimationIKTarget(id,x,y,space);});}
emscripten::val emscriptenSpriteGetAnimationIKResult(const Sprite& sprite,uint32_t id) {
    return poseScriptCall([&]{auto value=sprite.getAnimationIKResult(id);auto result=ScriptValue::object();
        result.set("reachError",value.reachError);
        result.set("reachable",value.reachable);
        result.set("clamped",value.clamped);
        result.set("limited",value.limited);
        result.set("stretched",value.stretched);
        return result;});
}

uint32_t emscriptenSpriteAddAnimationModifier(Sprite& sprite, emscripten::val callback, int stage, int order) {
    return poseScriptCall([&] { return sprite.addAnimationModifier([callback](AnimationPoseView view,const AnimationModifierContext& context) {
        auto info=ScriptValue::object();info.set("deltaSeconds",context.deltaSeconds);info.set("root",poseTransformValue(context.root));info.set("revision",std::to_string(context.revision));
        const auto snapshot=view.copy();auto edits=callback(poseSnapshotValue(snapshot),info);
        if (edits.typeOf().as<std::string>()=="string") throw std::runtime_error(edits.as<std::string>());
        if (!ScriptValue::global("Array").call<bool>("isArray",edits) || edits["length"].as<unsigned>()!=snapshot.getRig()->getBoneCount()) throw std::runtime_error("Wrong modifier bone count");
        const char* names[]={"x","y","rotation","scaleX","scaleY","alpha"};
        for (AnimationBoneId id=0;id<snapshot.getRig()->getBoneCount();++id) {
            AnimationTransform value;double* fields[]={&value.x,&value.y,&value.rotation,&value.scaleX,&value.scaleY,&value.alpha};
            for(int field=0;field<6;++field){auto number=edits[id][names[field]];if(number.typeOf().as<std::string>()!="number")throw std::invalid_argument("Invalid modifier transform");*fields[field]=number.as<double>();}
            view.setLocalTransform(id,value);
        }
    },stage,order); });
}
void emscriptenSpriteSetAnimationSource(Sprite& sprite,int source) { poseScriptCall([&]{sprite.setAnimationSource(source);}); }
std::string emscriptenSpriteGetAnimationModifierError(const Sprite& sprite,uint32_t id) { return poseScriptCall([&]{return sprite.getAnimationModifierError(id);}); }

void emscriptenSpriteSetAnimationDebugDraw(Sprite& sprite, int flags) {
    poseScriptCall([&] { sprite.setAnimationDebugDraw(flags); });
}
bool emscriptenSpriteEnableAnimationPose(Sprite& sprite, const std::string& clip) { return sprite.enableAnimationPose(clip.c_str()); }
emscripten::val emscriptenSpriteGetAnimationPose(const Sprite& sprite) {
    return poseScriptCall([&] { return poseSnapshotValue(sprite.getAnimationPose()); });
}
emscripten::val emscriptenSpriteSampleAnimationPose(const Sprite& sprite, const std::string& clip, double seconds) {
    return poseScriptCall([&] { return poseSnapshotValue(sprite.sampleAnimationPose(clip.c_str(), seconds)); });
}
emscripten::val emscriptenSpriteGetAnimationBoneNames(const Sprite& sprite) { return poseNamesValue(sprite.getAnimationBoneNames()); }
emscripten::val emscriptenSpriteGetAnimationPhysicsSetupWarnings(const Sprite& sprite) { return poseNamesValue(sprite.getAnimationPhysicsSetupWarnings()); }
emscripten::val emscriptenSpriteGetAnimationBindingNames(const Sprite& sprite) { return poseNamesValue(sprite.getAnimationBindingNames()); }
emscripten::val emscriptenSpriteGetAnimationBoneTransform(const Sprite& sprite, const std::string& name, int space) {
    return poseScriptCall([&] { return poseTransformValue(sprite.getAnimationBoneTransform(name.c_str(), space)); });
}
emscripten::val emscriptenSpriteGetAnimationBindingTransform(const Sprite& sprite, const std::string& name, int space) {
    return poseScriptCall([&] { return poseTransformValue(sprite.getAnimationBindingTransform(name.c_str(), space)); });
}
void emscriptenSpriteSetAnimationBoneTransform(Sprite& sprite, const std::string& name, const emscripten::val& transform) {
    poseScriptCall([&] {
        if (transform.isNull() || transform.typeOf().as<std::string>() != "object")
            throw std::invalid_argument("Animation transform must be an object");
        AnimationTransform value;
        const char* fields[] = {"x", "y", "rotation", "scaleX", "scaleY", "alpha"};
        double* values[] = {&value.x, &value.y, &value.rotation, &value.scaleX, &value.scaleY, &value.alpha};
        for (size_t i = 0; i < 6; ++i) {
            const auto property = transform[fields[i]];
            if (property.typeOf().as<std::string>() != "number") throw std::invalid_argument("Animation transform fields must be numbers");
            *values[i] = property.as<double>();
        }
        sprite.setAnimationBoneTransform(name.c_str(), value);
    });
}

bool emscriptenSpriteHasAnimation(Sprite& sprite, const emscripten::val& animation) {
    if (animation.typeOf().as<std::string>() == "number") {
        const double id = animation.as<double>();
        return std::isfinite(id) && id >= 0 && id <= 4294967295.0
            && id == std::floor(id) && sprite.hasAnimation(static_cast<uint32>(id));
    }
    return sprite.hasAnimation(animation.isNull() ? "" : animation.as<std::string>().c_str());
}

void emscriptenSpriteStartAnimation(Sprite& sprite, const emscripten::val& animation) {
    if (animation.typeOf().as<std::string>() == "number") sprite.startAnimation(animation.as<int>());
    else sprite.startAnimation(animation.isNull() ? "" : animation.as<std::string>().c_str());
}

void emscriptenSpriteBlendToAnimation(Sprite& sprite, const emscripten::val& animation, float blendTime) {
    if (animation.typeOf().as<std::string>() == "number") sprite.blendToAnimation(animation.as<int>(), blendTime);
    else sprite.blendToAnimation(animation.isNull() ? "" : animation.as<std::string>().c_str(), blendTime);
}

void emscriptenSpriteApplyCharacterMap(Sprite& sprite, const std::string& name) { sprite.applyCharacterMap(name.c_str()); }
void emscriptenSpriteRemoveCharacterMap(Sprite& sprite, const std::string& name) { sprite.removeCharacterMap(name.c_str()); }

emscripten::val emscriptenSpriteGetAppliedCharacterMaps(const Sprite& sprite) {
    emscripten::val result = emscripten::val::array();
    std::vector<std::string> maps = sprite.getAppliedCharacterMaps();
    for (size_t i = 0; i < maps.size(); ++i) result.set(i, maps[i]);
    return result;
}

bool emscriptenSpriteHasAttachPoint(const Sprite& sprite, const std::string& name) { return sprite.hasAttachPoint(name.c_str()); }
Offset emscriptenSpriteGetAttachPoint(const Sprite& sprite, const std::string& name) { return sprite.getAttachPoint(name.c_str()); }
void emscriptenSpriteAttachSprite(Sprite& sprite, Sprite* attached, const std::string& name) { sprite.attachSprite(attached, name.c_str()); }
Sprite* emscriptenSpriteGetAttachedSprite(const Sprite& sprite, const std::string& name) { return sprite.getAttachedSprite(name.c_str()); }
void emscriptenSpriteActivateSubEntity(Sprite& sprite, const std::string& entity, const std::string& animation) { sprite.activateSubEntity(entity.c_str(), animation.c_str()); }
bool emscriptenSpriteIsCollisionActive(const Sprite& sprite, const std::string& name) { return sprite.isSpriterCollisionActive(name.c_str()); }
emscripten::val emscriptenSpriteGetCollisionBox(const Sprite& sprite, const std::string& name) {
    RotatedRect box = sprite.getSpriterCollisionBox(name.c_str());
    emscripten::val result = emscripten::val::object();
    result.set("left", box.left);
    result.set("top", box.top);
    result.set("right", box.right);
    result.set("bottom", box.bottom);
    result.set("radians", box.radians);
    emscripten::val center = emscripten::val::object();
    center.set("x", box.centerOffset.x);
    center.set("y", box.centerOffset.y);
    result.set("centerOffset", center);
    return result;
}
emscripten::val emscriptenSpriteGetCollisionBoxName(const Sprite& sprite, int index) {
    const char* name = sprite.getSpriterCollisionBoxName(index);
    return name ? emscripten::val(name) : emscripten::val::null();
}

Sprite* emscriptenLayerCreateSpriteFromFile(SpriteLayer& layer, const std::string& path, const std::string& entity) {
    return layer.createSpriteFromSpriterFile(path.c_str(), entity.empty() ? nullptr : entity.c_str());
}
Sprite* emscriptenLayerCreateSpriteFromEntity(SpriteLayer& layer, const std::string& entity) { return layer.createSpriteFromSpriterEntity(entity.c_str()); }
void emscriptenLayerApplyCharacterMap(SpriteLayer& layer, const std::string& name) { layer.applyCharacterMapToAll(name.c_str()); }
void emscriptenLayerRemoveCharacterMap(SpriteLayer& layer, const std::string& name) { layer.removeCharacterMapFromAll(name.c_str()); }
#endif
#endif

#ifndef PDG_NO_SOUND
void emscriptenSoundPlay(Sound& sound, float volume, int32 offsetX, float pitch,
                         ms_time fromMs, ms_delta lengthMs) {
    sound.play(volume, offsetX, pitch, fromMs, lengthMs);
}
void emscriptenSoundChangePitch(Sound& sound, float target, ms_delta duration) {
    sound.changePitch(target, duration);
}
void emscriptenSoundChangeOffset(Sound& sound, int32 target, ms_delta duration) {
    sound.changeOffsetX(target, duration);
}
void emscriptenSoundFadeOut(Sound& sound, ms_delta duration) { sound.fadeOut(duration); }
void emscriptenSoundFadeIn(Sound& sound, ms_delta duration) { sound.fadeIn(duration); }
void emscriptenSoundChangeVolume(Sound& sound, float target, ms_delta duration) {
    sound.changeVolume(target, duration);
}
Sound* emscriptenResourceGetSound(ResourceManager& manager, const std::string& soundName) {
    return manager.getSound(soundName.c_str());
}
#endif

// extend the config manager to handle API differences between C++ and Javascript

std::string&  ConfigManagerWrap::getConfigString(std::string& arg0) {
    static std::string s = "";
    ConfigManagerUnix::getConfigString(arg0.c_str(), s);
    return s;
}

long ConfigManagerWrap::getConfigLong(std::string& arg0) {
    long n;
    ConfigManagerUnix::getConfigLong(arg0.c_str(), n);
    return n;
}

float ConfigManagerWrap::getConfigFloat(std::string& arg0) {
    float n;
    ConfigManagerUnix::getConfigFloat(arg0.c_str(), n);
    return n;
}

bool ConfigManagerWrap::getConfigBool(std::string& arg0) {
    bool n = false;
    ConfigManagerUnix::getConfigBool(arg0.c_str(), n);
    return n;
}

bool emscriptenConfigUseConfig(ConfigManager& manager, const std::string& name) {
    return manager.useConfig(name.c_str());
}

emscripten::val emscriptenConfigGetString(ConfigManager& manager, const std::string& key) {
    std::string value;
    if (!manager.getConfigString(key.c_str(), value)) return emscripten::val::undefined();
    return emscripten::val(value);
}

emscripten::val emscriptenConfigGetLong(ConfigManager& manager, const std::string& key) {
    long value = 0;
    if (!manager.getConfigLong(key.c_str(), value)) return emscripten::val::undefined();
    return emscripten::val(value);
}

emscripten::val emscriptenConfigGetFloat(ConfigManager& manager, const std::string& key) {
    float value = 0.0f;
    if (!manager.getConfigFloat(key.c_str(), value)) return emscripten::val::undefined();
    return emscripten::val(value);
}

emscripten::val emscriptenConfigGetBool(ConfigManager& manager, const std::string& key) {
    bool value = false;
    if (!manager.getConfigBool(key.c_str(), value)) return emscripten::val::undefined();
    return emscripten::val(value);
}

void emscriptenConfigSetString(ConfigManager& manager, const std::string& key, const std::string& value) {
    manager.setConfigString(key.c_str(), value);
}

void emscriptenConfigSetLong(ConfigManager& manager, const std::string& key, long value) {
    manager.setConfigLong(key.c_str(), value);
}

void emscriptenConfigSetFloat(ConfigManager& manager, const std::string& key, float value) {
    manager.setConfigFloat(key.c_str(), value);
}

void emscriptenConfigSetBool(ConfigManager& manager, const std::string& key, bool value) {
    manager.setConfigBool(key.c_str(), value);
}

MemBlock* emscriptenCreateEmptyMemBlock() {
    return new MemBlock(0);
}

Polygon* emscriptenPolygonIntersection(Polygon& polygon, const Polygon& other) {
    return new Polygon(polygon.intersection(other));
}

Polygon* emscriptenPolygonUnion(Polygon& polygon, const Polygon& other) {
    return new Polygon(polygon.unionWith(other));
}

static EasingFunc emscriptenAnimatedEasing(int easing, int fallback) {
    if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
        throw std::invalid_argument("Unknown easing constant");
    return gEasingFunctions[easing];
}

static emscripten::val rotatedBoundsValue(const RotatedRect& bounds) {
    emscripten::val result = emscripten::val::object();
    result.set("left", bounds.left);
    result.set("top", bounds.top);
    result.set("right", bounds.right);
    result.set("bottom", bounds.bottom);
    result.set("radians", bounds.radians);
    emscripten::val centerOffset = emscripten::val::object();
    centerOffset.set("x", bounds.centerOffset.x);
    centerOffset.set("y", bounds.centerOffset.y);
    result.set("centerOffset", centerOffset);
    return result;
}

emscripten::val emscriptenAnimatedGetRotatedBounds(AnimatedBase& animated) {
    return rotatedBoundsValue(animated.getRotatedBounds());
}
emscripten::val emscriptenSpriteGetFrameRotatedBounds(Sprite& sprite, int frame) {
    return rotatedBoundsValue(sprite.getFrameRotatedBounds(frame));
}

void emscriptenAnimatedMoveTo(AnimatedBase& animated, const Point& value, double seconds, int easing) {
    poseScriptCall([&] { animated.moveTo(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad)); });
}

void emscriptenAnimatedMoveBy(AnimatedBase& animated, const Offset& value, double seconds, int easing) {
    poseScriptCall([&] { animated.moveBy(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad)); });
}

void emscriptenAnimatedChangeMovementTo(AnimatedBase& animated, const Vector& value, double seconds, int easing) {
    poseScriptCall([&] { animated.changeMovementTo(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::linearTween)); });
}

void emscriptenAnimatedChangeMovementBy(AnimatedBase& animated, const Vector& value, double seconds, int easing) {
    poseScriptCall([&] { animated.changeMovementBy(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::linearTween)); });
}

void emscriptenAnimatedChangeCenterOffsetTo(AnimatedBase& animated, const Offset& value, double seconds, int easing) {
    poseScriptCall([&] { animated.changeCenterOffsetTo(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad)); });
}

void emscriptenAnimatedChangeCenterOffsetBy(AnimatedBase& animated, const Offset& value, double seconds, int easing) {
    poseScriptCall([&] { animated.changeCenterOffsetBy(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad)); });
}

void emscriptenAnimatedGrow(AnimatedBase& animated, float value, double seconds, int easing) {
    poseScriptCall([&] { animated.grow(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad)); });
}

void emscriptenAnimatedRotateTo(AnimatedBase& animated, float value, double seconds, int easing, int direction) {
    poseScriptCall([&] { animated.rotateTo(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad), direction); });
}

void emscriptenAnimatedRotateBy(AnimatedBase& animated, float value, double seconds, int easing, int direction) {
    poseScriptCall([&] { animated.rotateBy(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad), direction); });
}

void emscriptenAnimatedChangeSpinTo(AnimatedBase& animated, float value, double seconds, int easing) {
    poseScriptCall([&] { animated.changeSpinTo(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::linearTween)); });
}

void emscriptenAnimatedChangeSpinBy(AnimatedBase& animated, float value, double seconds, int easing) {
    poseScriptCall([&] { animated.changeSpinBy(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::linearTween)); });
}

void emscriptenAnimatedChangeGrowingTo(AnimatedBase& animated, float value, double seconds, int easing) {
    poseScriptCall([&] { animated.changeGrowingTo(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::linearTween)); });
}

void emscriptenAnimatedChangeGrowingBy(AnimatedBase& animated, float value, double seconds, int easing) {
    poseScriptCall([&] { animated.changeGrowingBy(value, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::linearTween)); });
}

void emscriptenAnimatedStretch(AnimatedBase& animated, float x, float y, double seconds, int easing) {
    poseScriptCall([&] { animated.stretch(x, y, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad)); });
}

void emscriptenAnimatedResizeTo(AnimatedBase& animated, float x, float y, double seconds, int easing) {
    poseScriptCall([&] { animated.resizeTo(x, y, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad)); });
}

void emscriptenAnimatedResizeBy(AnimatedBase& animated, float x, float y, double seconds, int easing) {
    poseScriptCall([&] { animated.resizeBy(x, y, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad)); });
}

void emscriptenAnimatedChangeScaleTo(AnimatedBase& animated, float x, float y, double seconds, int easing) {
    poseScriptCall([&] { animated.changeScaleTo(x, y, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad)); });
}

void emscriptenAnimatedChangeScaleBy(AnimatedBase& animated, float x, float y, double seconds, int easing) {
    poseScriptCall([&] { animated.changeScaleBy(x, y, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad)); });
}

void emscriptenAnimatedChangeStretchingTo(AnimatedBase& animated, float x, float y, double seconds, int easing) {
    poseScriptCall([&] { animated.changeStretchingTo(x, y, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::linearTween)); });
}

void emscriptenAnimatedChangeStretchingBy(AnimatedBase& animated, float x, float y, double seconds, int easing) {
    poseScriptCall([&] { animated.changeStretchingBy(x, y, seconds, emscriptenAnimatedEasing(easing, EasingFuncIds::linearTween)); });
}

bool emscriptenAnimatedAnimate(AnimatedBase& animated, double elapsed) {
    return animated.animate(elapsed);
}

ImageStrip* emscriptenCreateSnapshotImage() {
    auto* image = new ImageOpenGL();
    image->addRef();
    return image;
}

Image* emscriptenCreateImage(const std::string& path) {
    return Image::createImageFromFile(path.c_str());
}

ImageStrip* emscriptenCreateImageStrip(const std::string& path) {
    return ImageStrip::createImageStripFromFile(path.c_str());
}

Sound* emscriptenCreateSound(const std::string& path) {
    return Sound::createSoundFromFile(path.c_str());
}

Rect emscriptenImageGetBoundsAt(Image& image, const Point& point) {
    Point mutablePoint(point);
    return image.getImageBounds(mutablePoint);
}

Image* emscriptenImageGetSubsection(Image& image, const Rect& rect) {
    Rect mutableRect(rect);
    return image.getSubsection(mutableRect);
}

void emscriptenResourceSetLanguage(ResourceManager& manager, const std::string& language) {
    manager.setLanguage(language.c_str());
}

std::string emscriptenResourceGetLanguage(ResourceManager& manager) {
    return manager.getLanguage();
}

int emscriptenResourceOpenFile(ResourceManager& manager, const std::string& filename) {
    return manager.openResourceFile(filename.c_str());
}

std::string emscriptenResourceGetString(ResourceManager& manager, int id, int substring) {
    std::string value;
    manager.getString(value, static_cast<short>(id), static_cast<short>(substring));
    return value;
}

size_t emscriptenResourceGetSize(ResourceManager& manager, const std::string& resourceName) {
    return manager.getResourceSize(resourceName.c_str());
}

emscripten::val emscriptenResourceGet(ResourceManager& manager, const std::string& resourceName, int maxSize) {
    size_t resourceSize = manager.getResourceSize(resourceName.c_str());
    size_t bufferSize = maxSize < 0 ? resourceSize : std::min(resourceSize, static_cast<size_t>(maxSize));
    if (bufferSize == 0) return emscripten::val(false);

    std::string value(bufferSize, '\0');
    if (!manager.getResource(resourceName.c_str(), value.data(), bufferSize)) {
        return emscripten::val(false);
    }
    return emscripten::val(value);
}

Image* emscriptenResourceGetImage(ResourceManager& manager, const std::string& imageName) {
    return manager.getImage(imageName.c_str());
}

ImageStrip* emscriptenResourceGetImageStrip(ResourceManager& manager, const std::string& imageName) {
    return manager.getImageStrip(imageName.c_str());
}

void emscriptenAttributesSetLineStyle(Attributes& attributes, int style) {
    poseScriptCall([&] {
    attributes.lineStyle(static_cast<LineStyle>(style));
    });
}

void emscriptenAttributesSetFitType(Attributes& attributes, int fit) {
    poseScriptCall([&] {
    attributes.fitType(static_cast<FitType>(fit));
    });
}

void emscriptenAttributesSetBlendMode(Attributes& attributes, int mode) {
    poseScriptCall([&] {
    attributes.blendMode(static_cast<BlendMode>(mode));
    });
}

void emscriptenAttributesRotate(Attributes& attributes, float radians, const Point& center) {
    poseScriptCall([&] {
    attributes.rotation(radians, center);
    });
}

void emscriptenAttributesScale(Attributes& attributes, float xFactor, float yFactor, const Point& center) {
    poseScriptCall([&] {
    attributes.scale(xFactor, yFactor, center);
    });
}

void emscriptenAttributesSkew(Attributes& attributes, float xSkew, float ySkew, const Point& center) {
    poseScriptCall([&] {
    attributes.skew(xSkew, ySkew, center);
    });
}

static glm::mat3 attributesMatrix(const emscripten::val& matrix) {
    if (!emscripten::val::global("Array").call<bool>("isArray", matrix) || matrix["length"].as<int>() != 9) {
        throw std::invalid_argument("Attributes.transform requires an array of 9 numbers");
    }

    glm::mat3 nativeMatrix;
    for (int column = 0; column < 3; ++column) {
        for (int row = 0; row < 3; ++row) {
            emscripten::val value = matrix[column * 3 + row];
            if (value.typeOf().as<std::string>() != "number") {
                throw std::invalid_argument("Attributes.transform requires an array of 9 numbers");
            }
            nativeMatrix[column][row] = value.as<float>();
        }
    }
    return nativeMatrix;
}

void emscriptenAttributesTransform(Attributes& attributes, const emscripten::val& matrix) {
    poseScriptCall([&] {
    attributes.transform(attributesMatrix(matrix));
    });
}

void emscriptenAttributesSetTransform(Attributes& attributes, const emscripten::val& matrix) {
    poseScriptCall([&] {
    attributes.setTransform(attributesMatrix(matrix));
    });
}

// Embind has one registered base per class. Adjust to the Attributes subobject
// here; the returned handle borrows storage from its AnimatedAttributesBase owner.
Attributes* emscriptenAnimatedAttributesBase(AnimatedAttributesBase& self) {
    return static_cast<Attributes*>(&self);
}

static EasingFunc animatedAttributesEasing(int easing) {
    if (easing < 0 || easing >= NUM_EASING_FUNCTIONS)
        throw std::invalid_argument("Invalid appearance easing constant");
    return gEasingFunctions[easing];
}

void emscriptenAnimatedAttributesChangeLineColor(AnimatedAttributesBase& self, const Color& target, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeLineColor(target, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeLineThickness(AnimatedAttributesBase& self, float target, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeLineThickness(target, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeLineOpacity(AnimatedAttributesBase& self, float target, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeLineOpacity(target, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeFillColor(AnimatedAttributesBase& self, const Color& target, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeFillColor(target, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeFillOpacity(AnimatedAttributesBase& self, float target, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeFillOpacity(target, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeRoundedCorners(AnimatedAttributesBase& self, float target, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeRoundedCorners(target, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeTextSize(AnimatedAttributesBase& self, float target, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeTextSize(target, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeSubsection(AnimatedAttributesBase& self, const Rect& target, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeSubsection(target, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangePolarOffset(AnimatedAttributesBase& self, const Offset& target, double seconds, int easing) {
    poseScriptCall([&] {
    self.changePolarOffset(target, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeLightOffset(AnimatedAttributesBase& self, const Offset& target, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeLightOffset(target, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeAmbientLight(AnimatedAttributesBase& self, const Color& target, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeAmbientLight(target, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeSkew(AnimatedAttributesBase& self, float x, float y, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeSkew(x, y, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeSphereRotation(AnimatedAttributesBase& self, float radians, double seconds, int easing, int direction) {
    poseScriptCall([&] {
    self.changeSphereRotation(radians, seconds, animatedAttributesEasing(easing), direction);
    });
}

void emscriptenAnimatedAttributesChangeFrames(AnimatedAttributesBase& self, int first, int last, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeFrames(first, last, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeFillGradient(AnimatedAttributesBase& self, const Point& start, const Color& startColor, const Point& end, const Color& endColor, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeFillGradient(start, startColor, end, endColor, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeFillRadialGradient(AnimatedAttributesBase& self, const Point& center, const Color& centerColor, float radius, const Color& endColor, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeFillRadialGradient(center, centerColor, radius, endColor, seconds, animatedAttributesEasing(easing));
    });
}

void emscriptenAnimatedAttributesChangeTransform(AnimatedAttributesBase& self, const emscripten::val& matrix, double seconds, int easing) {
    poseScriptCall([&] {
    self.changeTransform(attributesMatrix(matrix), seconds, animatedAttributesEasing(easing));
    });
}

emscripten::val emscriptenAttributesGetTransform(Attributes& attributes) {
    const glm::mat3& matrix = attributes.getTransform();
    emscripten::val result = emscripten::val::array();
    for (int column = 0; column < 3; ++column) {
        for (int row = 0; row < 3; ++row) {
            result.set(column * 3 + row, matrix[column][row]);
        }
    }
    return result;
}

int emscriptenAttributesGetLineStyle(Attributes& attributes) {
    return static_cast<int>(attributes.getLineStyle());
}

int emscriptenAttributesGetGradientType(Attributes& attributes) {
    return static_cast<int>(attributes.getGradientType());
}

int emscriptenAttributesGetFitType(Attributes& attributes) {
    return static_cast<int>(attributes.getFitType());
}

int emscriptenAttributesGetBlendMode(Attributes& attributes) {
    return static_cast<int>(attributes.getBlendMode());
}

Drawing* emscriptenCreateDrawing() {
    return Drawing::create();
}

ElementRef* emscriptenDrawingAddSpline(Drawing& drawing, Spline& spline, const Attributes& attributes) {
    return drawing.addSpline(std::move(spline), attributes);
}

ElementRef* emscriptenDrawingAddPolygon(Drawing& drawing, Polygon& polygon, const Attributes& attributes) {
    return drawing.addPolygon(std::move(polygon), attributes);
}

emscripten::val emscriptenElementGetControlPoints(ElementRef& element) {
    emscripten::val result = emscripten::val::array();
    const std::vector<Point>& points = element.getControlPoints();
    for (size_t i = 0; i < points.size(); ++i) {
        emscripten::val point = emscripten::val::object();
        point.set("x", points[i].x);
        point.set("y", points[i].y);
        result.set(i, point);
    }
    return result;
}

Attributes* emscriptenElementGetAttributes(ElementRef& element) {
    Attributes* attributes = new Attributes();
    element.getAttributes(*attributes);
    return attributes;
}

int emscriptenElementGetType(ElementRef& element) {
    return static_cast<int>(element.type());
}

static std::unordered_map<int, std::unique_ptr<FindDataT>> sEmscriptenFindData;
static int sEmscriptenNextFindId = 1;

static void emscriptenUpdateFindObject(emscripten::val& object, int id, const FindDataT& data, bool found) {
    object.set("_pdgFindId", id);
    object.set("nodeName", found ? data.nodeName : "");
    object.set("isDirectory", found && data.isDirectory);
    object.set("found", found);
}

emscripten::val emscriptenFileFindFirst(FileManager&, const std::string& pattern) {
    std::unique_ptr<FindDataT> data(new FindDataT());
    data->privateData = nullptr;
    bool found = OS::findFirst(pattern.c_str(), *data);
    emscripten::val result = emscripten::val::object();
    if (!found) {
        OS::findClose(*data);
        emscriptenUpdateFindObject(result, 0, *data, false);
        return result;
    }

    int id = sEmscriptenNextFindId++;
    emscriptenUpdateFindObject(result, id, *data, true);
    sEmscriptenFindData.emplace(id, std::move(data));
    return result;
}

bool emscriptenFileFindNext(FileManager&, emscripten::val findData) {
    int id = findData["_pdgFindId"].as<int>();
    auto foundData = sEmscriptenFindData.find(id);
    if (foundData == sEmscriptenFindData.end()) return false;
    bool found = OS::findNext(*foundData->second);
    emscriptenUpdateFindObject(findData, id, *foundData->second, found);
    return found;
}

void emscriptenFileFindClose(FileManager&, const emscripten::val& findData) {
    int id = findData["_pdgFindId"].as<int>();
    auto foundData = sEmscriptenFindData.find(id);
    if (foundData == sEmscriptenFindData.end()) return;
    OS::findClose(*foundData->second);
    sEmscriptenFindData.erase(foundData);
}

void emscriptenLogInitialize(LogManager& manager, const std::string& baseName, int mode) {
    manager.initialize(baseName.c_str(), mode);
}

void emscriptenLogWrite(LogManager& manager, int level, const std::string& category, const std::string& message) {
    manager.writeLogEntry(static_cast<int8>(level), category.c_str(), message.c_str());
}

void emscriptenLogSetLevel(LogManager& manager, int level) {
    manager.setLogLevel(static_cast<int8>(level));
}

int emscriptenLogGetLevel(LogManager& manager) {
    return manager.getLogLevel();
}

void emscriptenTileDefineSet(TileLayer& layer, int tileWidth, int tileHeight, Image* tiles) {
    layer.defineTileSet(tileWidth, tileHeight, tiles);
}

void emscriptenTileSetWorldSize(TileLayer& layer, long width, long height) {
    layer.setWorldSize(width, height);
}

int emscriptenTileGetType(TileLayer& layer, long x, long y) {
    return layer.getTileTypeAt(x, y);
}

void emscriptenTileSetType(TileLayer& layer, long x, long y, int tileType, int facing) {
    layer.setTileTypeAt(x, y, static_cast<uint8>(tileType), static_cast<TileLayer::TFacing>(facing));
}

emscripten::val emscriptenTileGetTypeAndFacing(TileLayer& layer, long x, long y) {
    TileLayer::TFacing facing;
    int tileType = layer.getTileTypeAt(x, y, &facing);
    emscripten::val result = emscripten::val::object();
    result.set("tileType", tileType - static_cast<int>(facing));
    result.set("facing", static_cast<int>(facing));
    return result;
}

static RotatedRect emscriptenRotatedRectFromVal(const emscripten::val& value) {
    RotatedRect result(Rect(
        value["left"].as<float>(), value["top"].as<float>(),
        value["right"].as<float>(), value["bottom"].as<float>()),
        value["radians"].as<float>());
    emscripten::val center = value["centerOffset"];
    if (!center.isUndefined() && !center.isNull()) {
        result.centerOffset = Offset(center["x"].as<float>(), center["y"].as<float>());
    }
    return result;
}

static Quad emscriptenQuadFromVal(const emscripten::val& value) {
    emscripten::val points = value["points"];
    return Quad(
        Point(points[0]["x"].as<float>(), points[0]["y"].as<float>()),
        Point(points[1]["x"].as<float>(), points[1]["y"].as<float>()),
        Point(points[2]["x"].as<float>(), points[2]["y"].as<float>()),
        Point(points[3]["x"].as<float>(), points[3]["y"].as<float>()));
}

void emscriptenSerializerSerialize8(Serializer& serializer, double value) {
    serializer.serialize_8(static_cast<int64>(value));
}

void emscriptenSerializerSerialize4(Serializer& serializer, int value) {
    serializer.serialize_4(static_cast<int32>(value));
}

void emscriptenSerializerSerialize2(Serializer& serializer, int value) {
    serializer.serialize_2(static_cast<int16>(value));
}

void emscriptenSerializerSerialize1(Serializer& serializer, int value) {
    serializer.serialize_1(static_cast<int8>(value));
}

void emscriptenSerializerSerializeFloat(Serializer& serializer, double value) {
    serializer.serialize_f(static_cast<float>(value));
}

void emscriptenSerializerSerializeDouble(Serializer& serializer, double value) {
    serializer.serialize_d(value);
}

void emscriptenSerializerSerializePoint(Serializer& serializer, const Point& value) {
    serializer.serialize_point(value);
}

void emscriptenSerializerSerializeVector(Serializer& serializer, const Vector& value) {
    serializer.serialize_vector(value);
}

void emscriptenSerializerSerializeString(Serializer& serializer, const std::string& value) {
    serializer.serialize_str(value.c_str());
}

void emscriptenSerializerSerializeMem(Serializer& serializer, const std::string& value) {
    serializer.serialize_mem(value.data(), static_cast<uint32>(value.size()));
}

void emscriptenSerializerSerializeRotatedRect(Serializer& serializer, const emscripten::val& value) {
    serializer.serialize_rotr(emscriptenRotatedRectFromVal(value));
}

void emscriptenSerializerSerializeQuad(Serializer& serializer, const emscripten::val& value) {
    serializer.serialize_quad(emscriptenQuadFromVal(value));
}

uint32 emscriptenSerializerSizeofString(Serializer& serializer, const std::string& value) {
    return serializer.sizeof_str(value.c_str());
}

uint32 emscriptenSerializerSizeofPoint(Serializer& serializer, const Point& value) {
    return serializer.sizeof_point(value);
}

uint32 emscriptenSerializerSizeofVector(Serializer& serializer, const Vector& value) {
    return serializer.sizeof_vector(value);
}

uint32 emscriptenSerializerSizeofMem(Serializer& serializer, const std::string& value) {
    return serializer.sizeof_mem(value.data(), static_cast<uint32>(value.size()));
}

uint32 emscriptenSerializerSizeofRotatedRect(Serializer& serializer, const emscripten::val& value) {
    return serializer.sizeof_rotr(emscriptenRotatedRectFromVal(value));
}

uint32 emscriptenSerializerSizeofQuad(Serializer& serializer, const emscripten::val& value) {
    return serializer.sizeof_quad(emscriptenQuadFromVal(value));
}

MemBlock* emscriptenSerializerGetData(Serializer& serializer) {
    return new MemBlock(reinterpret_cast<char*>(serializer.getDataPtr()), serializer.getDataSize(), false);
}

double emscriptenDeserializerDeserialize8(Deserializer& deserializer) {
    return static_cast<double>(deserializer.deserialize_8());
}

int emscriptenDeserializerDeserialize4(Deserializer& deserializer) {
    return deserializer.deserialize_4();
}

int emscriptenDeserializerDeserialize2(Deserializer& deserializer) {
    return deserializer.deserialize_2();
}

int emscriptenDeserializerDeserialize1(Deserializer& deserializer) {
    return deserializer.deserialize_1();
}

double emscriptenDeserializerDeserializeFloat(Deserializer& deserializer) {
    return deserializer.deserialize_f();
}

double emscriptenDeserializerDeserializeDouble(Deserializer& deserializer) {
    return deserializer.deserialize_d();
}

Point emscriptenDeserializerDeserializePoint(Deserializer& deserializer) {
    return deserializer.deserialize_point();
}

Vector emscriptenDeserializerDeserializeVector(Deserializer& deserializer) {
    return deserializer.deserialize_vector();
}

std::string emscriptenDeserializerDeserializeString(Deserializer& deserializer) {
    std::string result;
    deserializer.deserialize_string(result);
    if (!result.empty() && result.back() == '\0') result.pop_back();
    return result;
}

MemBlock* emscriptenDeserializerDeserializeMem(Deserializer& deserializer) {
    uint32 size = deserializer.deserialize_memGetLen();
    MemBlock* result = new MemBlock(size);
    deserializer.deserialize_mem(result->ptr, size);
    return result;
}

emscripten::val emscriptenDeserializerDeserializeRotatedRect(Deserializer& deserializer) {
    RotatedRect value = deserializer.deserialize_rotr();
    emscripten::val result = emscripten::val::object();
    result.set("left", value.left);
    result.set("top", value.top);
    result.set("right", value.right);
    result.set("bottom", value.bottom);
    result.set("radians", value.radians);
    emscripten::val center = emscripten::val::object();
    center.set("x", value.centerOffset.x);
    center.set("y", value.centerOffset.y);
    result.set("centerOffset", center);
    return result;
}

emscripten::val emscriptenDeserializerDeserializeQuad(Deserializer& deserializer) {
    Quad value = deserializer.deserialize_quad();
    emscripten::val points = emscripten::val::array();
    for (int i = 0; i < 4; ++i) {
        emscripten::val point = emscripten::val::object();
        point.set("x", value.points[i].x);
        point.set("y", value.points[i].y);
        points.call<void>("push", point);
    }
    emscripten::val result = emscripten::val::object();
    result.set("points", points);
    return result;
}

void emscriptenDeserializerSetData(Deserializer& deserializer, MemBlock& data) {
    deserializer.setDataPtr(data.ptr, static_cast<uint32>(data.bytes));
}

uint32 emscriptenSpriteLayerGetSerializedSize(SpriteLayer& layer, Serializer& serializer) {
    return layer.getSerializedSize(&serializer);
}

void emscriptenSpriteLayerSerialize(SpriteLayer& layer, Serializer& serializer) {
    layer.serialize(&serializer);
}

void emscriptenSpriteLayerDeserialize(SpriteLayer& layer, Deserializer& deserializer) {
    layer.deserialize(&deserializer);
}

void setSerializationDebugMode(bool mode) {
    ISerializer::s_DebugMode = mode;
}

void emscriptenInit() {
    static const char* argv[] = { "pdg-wasm" };
    pdg_LibSaveArgs(1, argv);
    pdg_LibInit();
}

void emscriptenIdle() {
    pdg_LibIdle();
}

void emscriptenQuit() {
    pdg_LibQuit();
}

bool emscriptenIsQuitting() {
    return pdg_LibIsQuitting();
}


// end stuff to add to C++ API

FileManager* FileManager::createSingletonInstance() {
    return new FileManager();
}
std::string& FileManager::getApplicationDataDirectory() {
    static std::string _wdstr;
    _wdstr.assign( OS::getApplicationDataDirectory() );
    return _wdstr;
}
std::string& FileManager::getApplicationDirectory() {
    static std::string _wdstr;
    _wdstr.assign( OS::getApplicationDirectory() );
    return _wdstr;
}
std::string& FileManager::getApplicationResourceDirectory() {
    static std::string _wdstr;
    _wdstr.assign( OS::getApplicationResourceDirectory() );
    return _wdstr;
}

static bool sEmscriptenGlfwInitialized = false;

void platform_cleanup() 
{
#ifndef PDG_NO_GUI
  if (sEmscriptenGlfwInitialized) {
    glfwTerminate();
    sEmscriptenGlfwInitialized = false;
  }
#endif
  EM_ASM(
     pdg_em_platform_cleanup();
  );
}

void platform_init(int argc, const char* argv[])
{
#ifndef PDG_NO_GUI
  if (EM_ASM_INT({
      return typeof window !== 'undefined' &&
             typeof window.addEventListener === 'function' &&
             typeof document !== 'undefined';
  })) {
    glfwInitIfNeeded();
    sEmscriptenGlfwInitialized = true;
  }
#endif
  EM_ASM({
     pdg_em_platform_init($0, $1);
  }, argc, argv);
}

void platform_pollEvents()
{
#ifndef PDG_NO_GUI
  if (sEmscriptenGlfwInitialized) glfwPollEvents();
#endif
  EM_ASM(
     pdg_em_platform_pollEvents();
  );
}

} // end namespace pdg
