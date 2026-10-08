#include "pdg/sys/scene.h"
#include "pdg/sys/sprite.h"
#include "pdg/sys/spritelayer.h"
#include "pdg/sys/camera.h"
#include "pdg/sys/particle.h"
#include "pdg/sys/animationphysics.h"
#include "pdg/sys/events.h"
#include "pdg/sys/ieventhandler.h"
#include "pdg/sys/eventmanager.h"
#include "pdg/sys/timermanager.h"
#include "spritemanager.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>
namespace pdg {
namespace {
std::vector<Scene*>& scenes(){static std::vector<Scene*> value;return value;}
double now(){return std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();}
void nonnegative(double value){if(!std::isfinite(value)||value<0)throw std::invalid_argument("Expected finite nonnegative time/scale");}
}
struct Scene::Timer {
    long id; double deadline,remaining=0,pausedAt=0,last,interval; bool oneShot,paused=false;
    std::uint64_t order; UserData* data;
    ~Timer(){if(data)data->release();}
};
struct Scene::Subscription {
    std::weak_ptr<EventEmitter*> emitter;
    IEventHandler* handler=nullptr;
    long type;
    ~Subscription(){auto life=emitter.lock();if(life && *life)(*life)->removeHandler(handler,type);if(handler)handler->release();}
};
namespace {
class SceneHandler : public IEventHandler {
    Scene* scene;IEventHandler* callback;
public:
    SceneHandler(Scene* owner,IEventHandler* handler):scene(owner),callback(handler){callback->addRef();}
    ~SceneHandler() override{callback->release();}
    bool handleEvent(EventEmitter* emitter,long type,void* data) noexcept override {
        addRef();bool handled=!scene->isDisposed() && callback->handleEvent(emitter,type,data);release();return handled;
    }
};
}
std::uint64_t Scene::subscribe(EventEmitter& emitter,IEventHandler* handler,long type){
    requireLive();if(!handler)throw std::invalid_argument("Expected a subscription handler");
    auto entry=std::make_shared<Subscription>();entry->emitter=emitter.eventLifetime();entry->handler=new SceneHandler(this,handler);entry->type=type;
    entry->handler->addRef();emitter.addHandler(entry->handler,type);auto id=++mSubscriptionOrder;mSubscriptions[id]=std::move(entry);return id;
}
void Scene::unsubscribe(std::uint64_t id){mSubscriptions.erase(id);}
Scene::Scene() {
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    INIT_SCRIPT_OBJECT(mSceneScriptObj);
#endif
    // Ensure the compatibility dispatcher exists even when there are no legacy layers.
    SpriteManager::instance();
    mManager=std::make_unique<SpriteManager>(&EventManager::instance(),&TimerManager::instance(),this);
    mLastHost=now();setCamera(new Camera());scenes().push_back(this);
}
Scene::~Scene(){dispose();finishDisposal();}
void Scene::requireLive()const{if(mDisposed)throw std::logic_error("Scene is disposed");}
uint32_t Scene::query(const CollisionQueryGeometry& geometry, const CollisionQueryOptions& options, CollisionQueryBuffer& results) {
    requireLive();
    if (mAdvancing || mQuerying || mManager->mLayerUpdateDepth || mDrawingSprite)
        throw std::logic_error("Query scenes outside update/draw traversal and query predicates");
    mQueryResults.clear();
    if (mQueryBuffer && mQueryBuffer.get()!=&results) mQueryBuffer->clear();
    if (options.maxHits>1048576) throw std::invalid_argument("maxHits exceeds 1048576");
    if (options.layers) for (auto* layer:*options.layers)
        if (!layer || layer->mManager!=mManager.get()) throw std::invalid_argument("Query layer is not in this scene");
    struct Guard { bool& flag; Guard(bool& f):flag(f){flag=true;} ~Guard(){flag=false;} } guard(mQuerying);
    std::vector<Collider*> colliders;
    for (auto* layer=mManager->mFirstLayer;layer;layer=layer->mNextLayer) {
        if (!(layer->getQueryBits() & options.layerMask)) continue;
        if (options.layers && std::find(options.layers->begin(),options.layers->end(),layer)==options.layers->end()) continue;
        layer->collectQueryColliders(colliders);
    }
    const auto selection=options;
    queryColliders(colliders,geometry,selection,results);
    return results.getCount();
}
uint32_t Scene::raycast(const Point& start,const Point& end,const CollisionQueryOptions& options,CollisionQueryBuffer& results) {
    CollisionQueryGeometry q{CollisionQueryKind::Cast}; q.start=start;q.end=end;return query(q,options,results);
}
uint32_t Scene::sweepCircle(const Point& center,double radius,const Vector& delta,const CollisionQueryOptions& options,CollisionQueryBuffer& results) {
    CollisionQueryGeometry q{CollisionQueryKind::Cast};q.start=center;q.end=center+delta;q.radius=radius;return query(q,options,results);
}
uint32_t Scene::overlapPoint(const Point& point,const CollisionQueryOptions& options,CollisionQueryBuffer& results) {
    CollisionQueryGeometry q{CollisionQueryKind::Point};q.start=point;return query(q,options,results);
}
uint32_t Scene::overlapCircle(const Point& center,double radius,const CollisionQueryOptions& options,CollisionQueryBuffer& results) {
    CollisionQueryGeometry q{CollisionQueryKind::Circle};q.start=center;q.radius=radius;return query(q,options,results);
}
uint32_t Scene::overlapBox(const RotatedRect& box,const CollisionQueryOptions& options,CollisionQueryBuffer& results) {
    CollisionQueryGeometry q{CollisionQueryKind::Box};q.box=box;return query(q,options,results);
}
uint32_t Scene::overlapCapsule(const Point& start,const Point& end,double radius,const CollisionQueryOptions& options,CollisionQueryBuffer& results) {
    CollisionQueryGeometry q{CollisionQueryKind::Capsule};q.start=start;q.end=end;q.radius=radius;return query(q,options,results);
}
const std::vector<CollisionQueryHit>& Scene::queryMany(const CollisionQueryGeometry& geometry,const CollisionQueryOptions& options) {
    requireLive();
    if (mAdvancing || mQuerying || mManager->mLayerUpdateDepth || mDrawingSprite)
        throw std::logic_error("Query scenes outside update/draw traversal and query predicates");
    if (options.maxHits>1048576) throw std::invalid_argument("maxHits exceeds 1048576");
    if (!mQueryBuffer) mQueryBuffer=std::make_unique<CollisionQueryBuffer>();
    mQueryBuffer->setCapacity(options.maxHits);
    query(geometry,options,*mQueryBuffer);
    const auto count=std::min(options.maxHits,mQueryBuffer->getCount());
    mQueryResults.reserve(options.maxHits);
    for (uint32_t i=0;i<count;++i) mQueryResults.push_back(mQueryBuffer->getHit(i));
    return mQueryResults;
}
const std::vector<CollisionQueryHit>& Scene::raycast(const Point& start,const Point& end,uint32_t maxHits,const CollisionQueryOptions& options) {
    CollisionQueryGeometry q{CollisionQueryKind::Cast};q.start=start;q.end=end;auto selection=options;selection.maxHits=maxHits;return queryMany(q,selection);
}
const std::vector<CollisionQueryHit>& Scene::sweepCircle(const Point& center,double radius,const Vector& delta,uint32_t maxHits,const CollisionQueryOptions& options) {
    CollisionQueryGeometry q{CollisionQueryKind::Cast};q.start=center;q.end=center+delta;q.radius=radius;auto selection=options;selection.maxHits=maxHits;return queryMany(q,selection);
}
const std::vector<CollisionQueryHit>& Scene::overlapPoint(const Point& point,const CollisionQueryOptions& options) {
    CollisionQueryGeometry q{CollisionQueryKind::Point};q.start=point;return queryMany(q,options);
}
const std::vector<CollisionQueryHit>& Scene::overlapCircle(const Point& center,double radius,const CollisionQueryOptions& options) {
    CollisionQueryGeometry q{CollisionQueryKind::Circle};q.start=center;q.radius=radius;return queryMany(q,options);
}
const std::vector<CollisionQueryHit>& Scene::overlapBox(const RotatedRect& box,const CollisionQueryOptions& options) {
    CollisionQueryGeometry q{CollisionQueryKind::Box};q.box=box;return queryMany(q,options);
}
const std::vector<CollisionQueryHit>& Scene::overlapCapsule(const Point& start,const Point& end,double radius,const CollisionQueryOptions& options) {
    CollisionQueryGeometry q{CollisionQueryKind::Capsule};q.start=start;q.end=end;q.radius=radius;return queryMany(q,options);
}
std::optional<CollisionQueryHit> Scene::raycast(const Point& start,const Point& end,const CollisionQueryOptions& options) {
    CollisionQueryBuffer results(1);
    raycast(start,end,options,results);
    if (!results.getCount()) return std::nullopt;
    auto hit=results.getHit(0); hit.retainCollider(); return hit;
}
std::optional<CollisionQueryHit> Scene::sweepCircle(const Point& center,double radius,const Vector& delta,const CollisionQueryOptions& options) {
    CollisionQueryBuffer results(1);
    sweepCircle(center,radius,delta,options,results);
    if (!results.getCount()) return std::nullopt;
    auto hit=results.getHit(0); hit.retainCollider(); return hit;
}
uint32_t Scene::queryNearestPoint(const Point& point,double maxDistance,CollisionQueryBuffer& results) {
    CollisionQueryGeometry q{CollisionQueryKind::Nearest};q.start=point;q.maxDistance=maxDistance;
    return query(q,results.scriptOptions,results);
}
std::optional<CollisionQueryHit> Scene::nearestPoint(const Point& point,double maxDistance,const CollisionQueryOptions& options) {
    CollisionQueryGeometry q{CollisionQueryKind::Nearest};q.start=point;q.maxDistance=maxDistance;
    CollisionQueryBuffer results(1);
    query(q,options,results);
    if (!results.getCount()) return std::nullopt;
    auto hit=results.getHit(0); hit.retainCollider(); return hit;
}
void Scene::claimCamera(Camera* camera,Scene* scene){
    if(!camera || !scene)return;
    if(camera->mSceneOwner && camera->mSceneOwner!=scene)throw std::logic_error("Camera is already advanced by another scene");
    camera->mSceneOwner=scene;++scene->mCameras[camera];
}
void Scene::releaseCamera(Camera* camera,Scene* scene){
    if(!camera || !scene)return;
    auto found=scene->mCameras.find(camera);if(found==scene->mCameras.end())return;
    if(!--found->second){scene->mCameras.erase(found);camera->mSceneOwner=nullptr;}
}
void Scene::setCamera(Camera* camera){
    requireLive();if(!camera)throw std::invalid_argument("Scene requires a camera");if(camera==mCamera)return;
    claimCamera(camera,this);camera->attach();auto* old=mCamera;mCamera=camera;
    if(old){releaseCamera(old,this);old->detach();}
}
void Scene::addLayer(SpriteLayer* layer){
    if(mQuerying)throw std::logic_error("Cannot change scene membership in a query predicate");
    requireLive();if(!layer)throw std::invalid_argument("Expected a layer");
    if(layer->mManager==mManager.get())return;
    if(mAdvancing || (layer->mManager && layer->mManager->mLayerUpdateDepth))throw std::logic_error("Attach layers outside scene traversal");
    // Legacy factories create layers in the default scene; adopt them conveniently.
    if(layer->mManager && layer->mManager->mScene)throw std::logic_error("Remove layer from its scene before attaching");
    if(layer->mCamera && layer->mCamera->mSceneOwner && layer->mCamera->mSceneOwner!=this)throw std::logic_error("Layer camera belongs to another scene");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    layer->movePhysicsTo(mManager->mSpace);
#endif
    if(layer->mManager)layer->mManager->removeLayer(layer);
    mManager->addLayer(layer);claimCamera(layer->mCamera,this);
    mHistory.clear();
}
void Scene::removeLayer(SpriteLayer* layer){
    if(mQuerying)throw std::logic_error("Cannot change scene membership in a query predicate");
    requireLive();if(!layer || layer->mManager!=mManager.get())throw std::invalid_argument("Layer is not in this scene");
    if(mAdvancing || mManager->mLayerUpdateDepth)throw std::logic_error("Detach layers outside scene traversal");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(!layer->mDetachedSpace)layer->mDetachedSpace=cpSpaceNew();
    layer->movePhysicsTo(layer->mDetachedSpace);
#endif
    releaseCamera(layer->mCamera,this);mManager->removeLayer(layer);mHistory.clear();
}
void Scene::disposeLayer(SpriteLayer* layer){requireLive();if(mQuerying)throw std::logic_error("Cannot dispose a layer in a query predicate");if(!layer || layer->mManager!=mManager.get())throw std::invalid_argument("Layer is not in this scene");SpriteManager::cleanupLayer(layer);}
SpriteLayer* Scene::createSpriteLayer(){requireLive();if(mQuerying)throw std::logic_error("Cannot create layers in a query predicate");auto* layer=SpriteManager::createSpriteLayer();mManager->addLayer(layer);return layer;}
#ifndef PDG_NO_GUI
SpriteLayer* Scene::createSpriteLayer(Port* port){requireLive();if(mQuerying)throw std::logic_error("Cannot create layers in a query predicate");auto* layer=SpriteManager::createSpriteLayer(port);mManager->addLayer(layer);return layer;}
#endif
int Scene::getLayerCount()const{if(!mManager)return 0;int n=0;for(auto* l=mManager->mFirstLayer;l;l=l->mNextLayer)++n;return n;}
SpriteLayer* Scene::getLayer(int index)const{if(index<0||!mManager)return nullptr;auto* l=mManager->mFirstLayer;while(l && index--)l=l->mNextLayer;return l;}
void Scene::pause(){requireLive();if(!mPaused){mFrozenAlpha=getInterpolationAlpha();mPaused=true;if(mFixedStep)mAccumulator=std::fmod(mAccumulator,mFixedStep);}}
void Scene::resume(){requireLive();mPaused=false;mLastHost=now();}
void Scene::setTimeScale(double scale){requireLive();nonnegative(scale);if(!scale && mScale)mFrozenAlpha=getInterpolationAlpha();mScale=scale;mLastHost=now();}
void Scene::setFixedStep(double seconds){requireLive();nonnegative(seconds);if(mAdvancing)throw std::logic_error("Change fixed step outside updates");mFixedStep=seconds;mAccumulator=0;mHistory.clear();}
void Scene::setInterpolation(bool enabled){requireLive();mInterpolate=enabled;mHistory.clear();}
void Scene::setManual(bool manual){requireLive();mManual=manual;mLastHost=now();}
double Scene::getInterpolationAlpha()const{return mPaused||!mScale?mFrozenAlpha:mFixedStep?std::clamp(mAccumulator/mFixedStep,0.0,1.0):1;}
void Scene::startTimer(long id,double delay,bool oneShot,UserData* data){
    requireLive();nonnegative(delay);if(id<=0 || (!oneShot && !delay))throw std::invalid_argument("Timer needs positive ID and positive repeating interval");
    auto timer=std::make_shared<Timer>();timer->id=id;timer->interval=delay/1000;timer->last=mTime;timer->deadline=mTime+timer->interval;timer->oneShot=oneShot;timer->order=++mTimerOrder;timer->data=data;mTimers[id]=std::move(timer);
}
void Scene::cancelTimer(long id){mTimers.erase(id);}
void Scene::cancelAllTimers(){mTimers.clear();}
void Scene::delayTimer(long id,double delay){requireLive();nonnegative(delay);auto f=mTimers.find(id);if(f==mTimers.end())return;auto& t=*f->second;if(t.paused)t.remaining+=delay/1000;else t.deadline+=delay/1000;}
void Scene::pauseTimer(long id){requireLive();auto f=mTimers.find(id);if(f!=mTimers.end()&&!f->second->paused){auto& t=*f->second;t.paused=true;t.pausedAt=mTime;t.remaining=std::max(0.0,t.deadline-mTime);}}
void Scene::unpauseTimer(long id){requireLive();auto f=mTimers.find(id);if(f!=mTimers.end()&&f->second->paused){auto& t=*f->second;t.paused=false;t.last+=mTime-t.pausedAt;t.deadline=mTime+t.remaining;}}
bool Scene::isTimerPaused(long id)const{auto f=mTimers.find(id);return f!=mTimers.end() && (mPaused || !mScale || f->second->paused);}
double Scene::getWhenTimerFiresNext(long id)const{auto f=mTimers.find(id);return f==mTimers.end()||isTimerPaused(id)?-1:f->second->deadline*1000;}
bool Scene::postEvent(long type,void* data,EventEmitter* from){
    if(mDisposed)return false;
    ++mEventDepth;bool result;
    try{result=emitEvent(from?from:this,type,data);}catch(...){--mEventDepth;finishDisposal();throw;}
    --mEventDepth;finishDisposal();return result;
}
Scene::Pose Scene::pose(Sprite* s){auto p=s->getLocation();auto scale=s->getScale();return {p.x,p.y,s->getRotation(),scale.x,scale.y};}
void Scene::capture(bool before){
    std::set<Sprite*> live;
    for(auto* l=mManager->mFirstLayer;l;l=l->mNextLayer)for(int i=0;auto* s=l->getNthSprite(i);++i){
        live.insert(s);auto p=pose(s);auto f=mHistory.find(s);
        auto life=f==mHistory.end()?std::shared_ptr<AnimatedBase*>():f->second.life.lock();
        if(!life || *life!=s)mHistory[s]={s->animationLifetime(),p,p};
        else if(before){if(!(p==f->second.current))f->second.previous=f->second.current=p;else f->second.previous=f->second.current;}
        else f->second.current=p;
    }
    std::erase_if(mHistory,[&](auto& pair){return !live.contains(pair.first);});
}
SpatialTransform Scene::presentationTransform(Sprite* sprite)const{
    if(!mInterpolate || !mFixedStep)return {};
    if(sprite->getAttachmentPart())if(auto* parent=sprite->getAttachmentPart()->getSprite())return presentationTransform(parent);
    auto f=mHistory.find(sprite);if(f==mHistory.end())return {};auto life=f->second.life.lock();if(!life || *life!=sprite)return {};
    auto p=pose(sprite);if(!(p==f->second.current))return {}; // out-of-step mutation/teleport
    auto& a=f->second.previous;auto& b=f->second.current;double alpha=getInterpolationAlpha();
    auto mix=[&](double x,double y){return x+(y-x)*alpha;};
    auto current=SpatialTransform::fromTRS(b.x,b.y,b.angle,b.sx,b.sy);
    if(!b.sx||!b.sy)return {};
    auto shown=SpatialTransform::fromTRS(mix(a.x,b.x),mix(a.y,b.y),a.angle+std::remainder(b.angle-a.angle,2*std::acos(-1.0))*alpha,mix(a.sx,b.sx),mix(a.sy,b.sy));
    return SpatialTransform::compose(shown,current.inverse());
}
void Scene::step(double seconds){
    const auto limit=mTimerOrder;mTime+=seconds;++mTick;
    std::vector<std::shared_ptr<Timer>> due;
    for(auto& [id,t]:mTimers)if(!t->paused && t->deadline<=mTime+1e-12 && t->order<=limit)due.push_back(t);
    std::stable_sort(due.begin(),due.end(),[](auto& a,auto& b){return a->deadline<b->deadline || (a->deadline==b->deadline && a->order<b->order);});
    for(auto& t:due){
        if(mDisposed || mPaused || !mScale)break;
        auto f=mTimers.find(t->id);if(f==mTimers.end() || f->second!=t || t->paused || t->deadline>mTime+1e-12)continue;
        TimerInfo info{t->id,ms_time(mTime*1000),ms_delta((mTime-t->last)*1000),t->data?t->data->getData():nullptr};
        if(t->oneShot)mTimers.erase(f);else{t->last=mTime;t->deadline=mTime+t->interval;}
        postEvent(eventType_Timer,&info);
    }
    if(mDisposed)return;
    if(mInterpolate)capture(true);
    mManager->advance(seconds*1000);
    if(mDisposed)return;
    if(mInterpolate)capture(false);
    std::vector<Camera*> cameras;for(auto& [c,count]:mCameras){c->addRef();cameras.push_back(c);}
    for(auto* c:cameras){if(!mDisposed && c->mSceneOwner==this)c->animate(seconds);c->release();}
}
void Scene::advance(double seconds){
    requireLive();nonnegative(seconds);if(mAdvancing || mQuerying)throw std::logic_error("Scene update cannot reenter or run in a query predicate");if(mPaused||!mScale)return;
    mAdvancing=true;
    try{
        double admitted=std::min(seconds,.25);mDropped+=(seconds-admitted)*mScale;
        if(!mFixedStep)step(admitted*mScale);
        else{mAccumulator+=admitted*mScale;unsigned count=0;while(mAccumulator+1e-12>=mFixedStep && count++<8 && !mPaused && mScale && !mDisposed){mAccumulator=std::max(0.0,mAccumulator-mFixedStep);step(mFixedStep);}if(mAccumulator>=mFixedStep){double remainder=std::fmod(mAccumulator,mFixedStep);mDropped+=mAccumulator-remainder;mAccumulator=remainder;}}
    }catch(...){mAdvancing=false;finishDisposal();throw;}
    mAdvancing=false;finishDisposal();
}
void Scene::advanceAll(){
    const double timestamp=now();auto snapshot=scenes();
    std::vector<bool> retained;for(auto* scene:snapshot){retained.push_back(scene->refs>0);if(retained.back())scene->addRef();}
    try{for(auto* scene:snapshot){double delta=std::max(0.0,timestamp-scene->mLastHost);scene->mLastHost=timestamp;if(!scene->mDisposed&&!scene->mManual)scene->advance(delta);}}
    catch(...){for(std::size_t i=0;i<snapshot.size();++i)if(retained[i])snapshot[i]->release();throw;}
    for(std::size_t i=0;i<snapshot.size();++i)if(retained[i])snapshot[i]->release();
}
std::vector<SpriteLayer*> Scene::layersInDrawOrder(){std::vector<SpriteLayer*> result;for(auto* s:scenes())for(auto* l=s->mManager->mFirstLayer;l;l=l->mNextLayer)result.push_back(l);return result;}
void Scene::disposeAll(){auto snapshot=scenes();for(auto* s:snapshot)s->dispose();}
SpriteLayer* Scene::findLayer(long id){for(auto* s:scenes())for(auto* l=s->mManager->mFirstLayer;l;l=l->mNextLayer)if(l->layerId==id)return l;return nullptr;}
void Scene::dispatch(EventEmitter* emitter,long type,void* data){
    auto snapshot=scenes();std::vector<bool> retained;for(auto* s:snapshot){retained.push_back(s->refs>0);if(retained.back())s->addRef();}
    for(auto* s:snapshot){if(!s->mDisposed)s->mManager->handleEvent(emitter,type,data);s->finishDisposal();}
    for(std::size_t i=0;i<snapshot.size();++i)if(retained[i])snapshot[i]->release();
}
void Scene::dispose(){if(mDisposed)return;if(mQuerying)throw std::logic_error("Cannot dispose a scene in a query predicate");mDisposed=true;mQueryResults.clear();if(mQueryBuffer)mQueryBuffer->clear();std::erase(scenes(),this);cancelAllTimers();mSubscriptions.clear();finishDisposal();}
void Scene::finishDisposal(){
    if(!mDisposed || mAdvancing || mEventDepth || !mManager || mManager->mLayerUpdateDepth)return;
    clear();
    while(mManager->mFirstLayer)SpriteManager::cleanupLayer(mManager->mFirstLayer);
    if(mCamera){auto* camera=mCamera;mCamera=nullptr;releaseCamera(camera,this);camera->detach();}
    mHistory.clear();mManager.reset();
}
#ifdef PDG_USE_CHIPMUNK_PHYSICS
void SpriteLayer::movePhysicsTo(cpSpace* destination){
    if(!mUseChipmunkPhysics)return;
    auto* source=getSpace();if(source==destination)return;
    if(cpSpaceIsLocked(source)||cpSpaceIsLocked(destination))throw std::logic_error("Move layers outside locked physics worlds");
    std::set<cpBody*> bodies;
    for(auto* s=mFirstSprite;s;s=s->mNextSprite){
        if(s->physics!=PhysicsBody::NoPhysics)if(auto* b=static_cast<cpBody*>(s->physics->nativeBody()))bodies.insert(b);
        for(auto* part:s->mParts)if(part->physics!=PhysicsBody::NoPhysics)if(auto* b=static_cast<cpBody*>(part->physics->nativeBody()))bodies.insert(b);
#ifdef PDG_SPRITER_SUPPORT
        if(s->mAnimationPhysics)for(std::uint32_t i=0;i<s->mAnimationPhysics->definition().bodies.size();++i)if(auto* b=s->mAnimationPhysics->body(i))bodies.insert(b);
#endif
    }
    for(auto* p:mParticles)if(p->physics.isPresent())if(auto* b=static_cast<cpBody*>(p->physics->nativeBody()))bodies.insert(b);
    std::set<cpConstraint*> joints;std::set<cpShape*> shapes;
    for(auto* b:bodies){cpBodyEachConstraint(b,[](cpBody*,cpConstraint* c,void* data){static_cast<std::set<cpConstraint*>*>(data)->insert(c);},&joints);cpBodyEachShape(b,[](cpBody*,cpShape* s,void* data){static_cast<std::set<cpShape*>*>(data)->insert(s);},&shapes);}
    for(auto* c:joints)if(!bodies.contains(cpConstraintGetBodyA(c))||!bodies.contains(cpConstraintGetBodyB(c)))throw std::logic_error("Disconnect cross-layer/world constraints before detaching");
    for(auto* c:joints)if(cpSpaceContainsConstraint(source,c))cpSpaceRemoveConstraint(source,c);
    for(auto* shape:shapes)if(cpSpaceContainsShape(source,shape))cpSpaceRemoveShape(source,shape);
    for(auto* b:bodies)if(cpSpaceContainsBody(source,b)){cpSpaceRemoveBody(source,b);cpSpaceAddBody(destination,b);}
    for(auto* shape:shapes)cpSpaceAddShape(destination,shape);
    for(auto* c:joints)cpSpaceAddConstraint(destination,c);
#ifdef PDG_SPRITER_SUPPORT
    for(auto* s=mFirstSprite;s;s=s->mNextSprite)if(s->mAnimationPhysics)s->mAnimationPhysics->adoptMovedSpace(destination);
#endif
}
#endif
}
