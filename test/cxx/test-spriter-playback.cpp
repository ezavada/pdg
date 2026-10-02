#include "pdg/sys/sprite.h"
#include "pdg/sys/animationpose.h"
#include "pdg/sys/drawing.h"
#include "pdg/sys/animationphysics.h"
#include "spritemanager.h"
#include "spriterengine/objectinfo/boneinstanceinfo.h"
#include "spriterengine/global/settings.h"
#include "spriterengine/objectref/transformprocessor.h"
#include "pdg/sys/spritelayer.h"
#include "pdg/sys/initializer.h"
#ifndef PDG_NO_GUI
#include "pdg/sys/ispritedrawhelper.h"
#include "pdg/sys/port.h"
#include "image-opengl.h"
#include "graphics-opengl.h"
#include "spriter/pdg_image_file.h"
#include "spriterengine/objectinfo/spriteobjectinfo.h"
#include <stdexcept>
#endif
#include "pdg-main.h"
#include "spriter/pdg_file_factory.h"
#include "spriter/pdg_object_factory.h"
#include "spriterengine/model/spritermodel.h"
#include "spriterengine/entity/entityinstance.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <optional>
#include <string>

#ifdef _WIN32
#undef far
#undef near
#undef small
#endif

namespace {
int assertions = 0;
void expect(bool value, const std::string& message) {
    ++assertions;
    if (!value) {
        std::cerr << "Spriter regression failed: " << message << '\n';
        std::exit(EXIT_FAILURE);
    }
}
void near(double actual, double expected, const std::string& message) {
    expect(std::isfinite(actual) && std::abs(actual - expected) < 0.001,
           message + " (actual " + std::to_string(actual) + ", expected " + std::to_string(expected) + ")");
}
void step(pdg::Sprite& sprite, unsigned milliseconds) {
    sprite.doAnimate(milliseconds, false);
}
void independentParts(SpriterEngine::SpriterModel& model) {
    pdg::Sprite sprite;
    auto* hand = sprite.createPart("hand");
    auto* socket = sprite.createPart("socket");
    hand->addRef(); socket->addRef();
    expect(sprite.getPartCount() == 2 && sprite.findPart("hand") == hand, "Part ownership and lookup");
    expect(hand->getBoneId() == pdg::boneId_None && !hand->isBoundToBone(), "unbound Part bone query safe");
    sprite.setLocation(pdg::Point(100,200)); sprite.setRotation(3.141592653589793/2);
    hand->setLocation(pdg::Point(10,0)); hand->setMovement(4,0);
    step(sprite,250);
    near(hand->getLocation().x,11,"Part advances exactly once with owner");
    near(hand->getTransform(pdg::partSpace_World).tx,100,"Part rotated world x");
    near(hand->getTransform(pdg::partSpace_World).ty,211,"Part rotated world y");
    socket->setParentPart(hand).setLocation(pdg::Point(2,0));
    near(socket->getTransform(pdg::partSpace_Sprite).tx,13,"Part parent composes local state");
    bool rejected=false;
    try { hand->setParentPart(socket); } catch(const std::invalid_argument&) { rejected=true; }
    expect(rejected && !hand->getParentPart(),"Part cycle rejected atomically");
    pdg::Sprite other;
    auto* foreign=other.createPart("other"); rejected=false;
    try { hand->setParentPart(foreign); } catch(const std::invalid_argument&) { rejected=true; }
    expect(rejected,"foreign parent rejected");
    const auto oldId=hand->getId();
    expect(sprite.removePart(oldId),"Part removal succeeds");
    expect(!hand->isAttached() && !hand->getSprite() && hand->getBoneId()==pdg::boneId_None,"retained removed Part is safe");
    expect(!socket->getParentPart(),"removed parent safely detaches children");
    auto* replacement=sprite.createPart("hand");
    expect(replacement->getId()!=oldId && !sprite.getPart(oldId),"Part identity never reused within Sprite");
    step(sprite,250);near(hand->getLocation().x,11,"removed Part not automatically advanced");
    sprite.clearParts(); hand->release(); socket->release();
    pdg::Part* retained;
    { pdg::Sprite temporary; retained=temporary.createPart("retained"); retained->addRef(); }
    expect(!retained->getSprite() && retained->getBoneId()==pdg::boneId_None,"owner destruction detaches retained Part");
    retained->release();
    pdg::Sprite skeletal(model.getNewEntityInstance(0), &model);
    expect(skeletal.enableAnimationPose("reference"),"Part fixture pose enabled");
    auto rig=skeletal.getAnimationRig();
    expect(rig && rig->getBoneCount()>0,"Part fixture has bones");
    auto* a=skeletal.createPart("a");auto* b=skeletal.createPart("b");
    a->bindToBone(0);b->bindToBone(0);a->moveTo(3,0);b->moveTo(7,0);
    expect(a->getBoneId()==0 && b->getBoneId()==0 && a->getId()!=b->getId(),"distinct Parts may share a bone");
    const auto transform=skeletal.getAnimationPose().getGlobalTransform(0);
    const auto frame=pdg::SpatialTransform::fromTRS(transform.x,transform.y,transform.rotation,transform.scaleX,transform.scaleY);
    near(a->getTransform(pdg::partSpace_Sprite).tx,frame.transformPoint(pdg::Point(3,0)).x,"bound local transform composed with published bone");
    a->setupPhysicsBody();
    const auto physicalPosition=a->getTransform(pdg::partSpace_World);
    a->unbindFromBone();
    near(a->getTransform(pdg::partSpace_World).tx,physicalPosition.tx,"unbinding keeps dynamic Part world position");
    near(a->getTransform(pdg::partSpace_World).ty,physicalPosition.ty,"unbinding keeps dynamic Part world height");
    skeletal.disableAnimationPose();
    expect(a->getBoneId()==pdg::boneId_None && b->getBoneId()==pdg::boneId_None,"disabled rig safely invalidates binding");
    expect(skeletal.enableAnimationPose("reference"),"Part fixture pose reenabled");
    expect(a->getBoneId()==pdg::boneId_None,"old binding never addresses replacement rig");
}

void repeatedWonkyPlayback(const std::string& path) {
    SpriterEngine::SpriterModel model(path, new pdg::PDGFileFactory(), new pdg::PDGObjectFactory());
    pdg::Sprite sprite(model.getNewEntityInstance(0), &model);
    // Use the original asset, including Crumble's changing hierarchy, through
    // ordinary Spriter playback. These are its authored nonlooping durations.
    struct Clip { const char* name; unsigned milliseconds; };
    const Clip clips[] = {{"Attack", 830}, {"Crumble", 1000}};
    for (int cycle = 0; cycle < 2; ++cycle) {
        sprite.startAnimation("Walk"); sprite.resumeAnimation(); step(sprite, 200);
        expect(sprite.isAnimationPlaying(), "Wonky Walk advances between nonlooping cycles");
        for (const auto& clip : clips) {
            const std::string label = std::string("Wonky ") + clip.name + " cycle " + std::to_string(cycle + 1);
            expect(sprite.hasAnimation(clip.name), label + " exists in the original asset");
            // Match main.js exactly: selection retains a clip's previous clock,
            // then resume must rewind it if that clip completed on the last pass.
            sprite.startAnimation(clip.name);
            sprite.resumeAnimation();
            near(sprite.getAnimationProgress(), 0, label + " starts at zero");
            expect(sprite.isAnimationPlaying() && !sprite.isAnimationPaused(), label + " starts playing");
            expect(!sprite.isAnimationPoseEnabled(), label + " stays on ordinary playback");
            unsigned elapsed = 0;
            for (unsigned quarter = 1; quarter <= 4; ++quarter) {
                const unsigned target = clip.milliseconds * quarter / 4;
                step(sprite, target - elapsed);
                elapsed = target;
                near(sprite.getAnimationProgress(), double(elapsed) / clip.milliseconds,
                    label + " advances to the expected progress");
                expect(!sprite.isAnimationPoseEnabled(), label + " never enables an editable pose");
                expect(sprite.isAnimationPlaying() == (quarter < 4), label + " plays until its endpoint");
                expect(!sprite.isAnimationPaused(), label + " completes naturally rather than pausing");
            }
            step(sprite, clip.milliseconds + 100);
            near(sprite.getAnimationProgress(), 1, label + " remains at its endpoint after extra time");
            expect(!sprite.isAnimationPlaying() && !sprite.isAnimationPaused(), label + " stays completed");
            expect(!sprite.isAnimationPoseEnabled(), label + " keeps ordinary playback after completion");
        }
        sprite.startAnimation("Idle"); sprite.resumeAnimation(); step(sprite, 200);
        expect(sprite.isAnimationPlaying(), "Wonky Idle plays after the completed nonlooping clips");
    }
}

void playback(SpriterEngine::SpriterModel& model) {
    pdg::Sprite sprite(model.getNewEntityInstance(0), &model);
    pdg::Sprite other(model.getNewEntityInstance(0), &model);
    step(sprite, 0);
    step(other, 0);
    near(sprite.getAttachPoint("socket").x, 10, "source pose");
    expect(sprite.hasAnimation("a") && sprite.hasAnimation("b"), "authored names exist");
    expect(!sprite.hasAnimation("missing") && !sprite.hasAnimation(nullptr), "missing names rejected");
    expect(sprite.hasAnimation(0) && !sprite.hasAnimation(-1) && !sprite.hasAnimation(999), "ID bounds");

    sprite.blendToAnimation("b", 0.5f);
    step(sprite, 125);
    near(sprite.getBlendProgress(), 0.25, "quarter progress for seconds API");
    near(sprite.getAttachPoint("socket").x, 35, "quarter pose");
    near(other.getAttachPoint("socket").x, 10, "other instance untouched");
    const auto phase = sprite.getAnimationProgress();
    sprite.pauseAnimation();
    step(sprite, 750);
    near(sprite.getAnimationProgress(), phase, "pause freezes source clock");
    near(sprite.getBlendProgress(), 0.25, "pause freezes blend clock");
    near(sprite.getAttachPoint("socket").x, 35, "pause retains blended pose");
    expect(sprite.isBlending() && sprite.isAnimationPaused() && !sprite.isAnimationPlaying(), "paused blend flags");
    sprite.resumeAnimation();
    step(sprite, 125);
    near(sprite.getBlendProgress(), 0.5, "resume half progress");
    near(sprite.getAttachPoint("socket").x, 60, "resume half pose");
    step(sprite, 250);
    near(sprite.getBlendProgress(), 1, "completion progress");
    near(sprite.getAttachPoint("socket").x, 110, "destination pose at completion");
    expect(!sprite.isBlending(), "completed state");
    step(sprite, 250);
    near(sprite.getBlendProgress(), 1, "completion progress retained");

    sprite.stopAnimation();
    expect(sprite.isAnimationPaused(), "stop preserves the documented pause behavior");
    sprite.startAnimation(0);
    expect(sprite.isAnimationPlaying() && !sprite.isAnimationPaused(), "ID start clears paused state");
    sprite.blendToAnimation(1, 2.0f);
    step(sprite, 500);
    near(sprite.getBlendProgress(), 0.25, "ID blend duration");
    near(sprite.getAttachPoint("socket").x, 35, "ID blend pose");
    sprite.startAnimation("a");
    step(sprite, 100);
    expect(!sprite.isBlending(), "start cancels blend");
    near(sprite.getBlendProgress(), 0, "start clears progress");
    near(sprite.getAttachPoint("socket").x, 10, "start clears native blend");

    sprite.blendToAnimation("b", 0.5f);
    step(sprite, 125);
    sprite.pauseAnimation();
    sprite.startAnimation("missing");
    sprite.startAnimation(-1);
    sprite.blendToAnimation("missing", 1);
    sprite.blendToAnimation(999, 1);
    sprite.blendToAnimation("a", std::numeric_limits<float>::infinity());
    sprite.blendToAnimation(0, std::numeric_limits<float>::quiet_NaN());
    expect(sprite.isAnimationPaused() && sprite.isBlending(), "invalid inputs preserve state");
    near(sprite.getBlendProgress(), 0.25, "invalid inputs preserve progress");
    near(sprite.getAttachPoint("socket").x, 35, "invalid inputs preserve pose");
    sprite.blendToAnimation("b", 0.5f);
    expect(!sprite.isAnimationPaused(), "new blend resumes playback");
    step(sprite, 750);
    expect(!sprite.isBlending(), "large step completes blend");
    near(sprite.getAttachPoint("socket").x, 110, "large step destination pose");
    sprite.startAnimation("once");
    step(sprite, 100);
    expect(!sprite.isAnimationPlaying() && !sprite.isAnimationPaused(), "natural finish is distinct from pause");
    sprite.resumeAnimation();
    near(sprite.getAnimationProgress(), 0, "resume restarts a finished clip");
    sprite.blendToAnimation("b", 0.5f);
    step(sprite, 125);
    near(sprite.getAttachPoint("socket").x, 35, "blend survives source end");
    sprite.pauseAnimation();
    step(sprite, 200);
    near(sprite.getAttachPoint("socket").x, 35, "ended source blend can pause");
    sprite.resumeAnimation();
    step(sprite, 125);
    near(sprite.getAttachPoint("socket").x, 60, "ended source blend can resume");
    step(sprite, 250);
    near(sprite.getAttachPoint("socket").x, 110, "long blend completes after source end");
    expect(!sprite.isBlending() && sprite.isAnimationPlaying(), "destination continues after nonlooping source");
    auto destinationPhase = sprite.getAnimationProgress();
    step(sprite, 50);
    expect(sprite.getAnimationProgress() != destinationPhase, "destination clock advances");
    for (float duration : {0.0f, -1.0f}) {
        sprite.startAnimation("a");
        sprite.blendToAnimation("b", duration);
        step(sprite, 0);
        expect(!sprite.isBlending(), "nonpositive duration completes on update");
        near(sprite.getAttachPoint("socket").x, 110, "nonpositive duration destination pose");
    }
}
void selection(SpriterEngine::SpriterModel& model) {
    pdg::Sprite sprite(model.getNewEntityInstance(0), &model);
    sprite.startAnimation("a"); step(sprite, 250);
    const double aTime = sprite.getAnimationProgress();
    sprite.startAnimation("b"); step(sprite, 125);
    const double bTime = sprite.getAnimationProgress();
    sprite.startAnimation("a");
    near(sprite.getAnimationProgress(), aTime, "clip selection retains source time");
    sprite.startAnimation("b");
    near(sprite.getAnimationProgress(), bTime, "clip selection retains destination time");
    const auto entity = sprite.mEntityInstance->currentEntityName();
    sprite.pauseAnimation();
    sprite.activateSubEntity(entity.c_str(), "missing");
    sprite.activateSubEntity("alternate", "missing");
    sprite.activateSubEntity("missing", "a");
    expect(sprite.mEntityInstance->currentEntityName() == entity && sprite.mEntityInstance->currentAnimationName() == "b", "invalid entity/clip combination preserves selection");
    expect(sprite.isAnimationPaused(), "invalid entity selection preserves pause");
    near(sprite.getAnimationProgress(), bTime, "invalid entity selection preserves time");
    sprite.activateSubEntity(entity.c_str(), "a");
    expect(sprite.isAnimationPlaying(), "same entity valid clip resumes");
    near(sprite.getAnimationProgress(), aTime, "same entity retains per-clip time");
    sprite.activateSubEntity("alternate", "a");
    expect(sprite.mEntityInstance->currentEntityName() == "alternate" && sprite.hasAnimation("a"), "valid new entity updates name lookup");
}



#ifdef PDG_USE_CHIPMUNK_PHYSICS
#include "generated-rig-sprite-tests.inc"
#include "animation-physics-control-tests.inc"
#include "rig-frame-tests.inc"
#include "human-rig-blocker-tests.inc"
void physicalRig(const std::string& path){
#ifdef PDG_NO_GUI
    auto* layer=pdg::createSpriteLayer();
#else
    auto* layer=pdg::createSpriteLayer(nullptr);
#endif
    layer->setUseChipmunkPhysics(true);
    auto* sprite=layer->createSpriteFromSpriterFile(path.c_str());sprite->pauseAnimation();
    expect(sprite->enableAnimationPose("reference"),"physical pose enables");
    auto desired=sprite->getAnimationPose();
    pdg::AnimationPhysicsDefinition def;
    for(unsigned i=0;i<3;++i){pdg::AnimationPhysicsBody b;b.bone=i;b.length=i==0?10:i==1?5:2;b.offsetX=b.length/2;b.radius=.25;def.bodies.push_back(b);}
    for(unsigned i=0;i<2;++i){pdg::AnimationPhysicsJoint j;j.parent=i;j.child=i+1;j.parentX=def.bodies[i].length/2;j.childX=-def.bodies[i+1].length/2;def.joints.push_back(j);}
    def.bodies[0].mode=pdg::animationBody_Kinematic;
    auto* space=cpSpaceNew();cpSpaceSetGravity(space,cpv(0,40));cpSpaceSetIterations(space,30);
    {
        pdg::AnimationPhysicsRig rig(space,def,desired,{});
        expect(pdg::AnimationPhysicsRig::find(rig.body(1))==&rig,"physical body has typed registry owner");
        near(rig.getBodyState(0).x,7,"body center includes authored offset");
        for(int i=0;i<120;++i){rig.prepare(desired,{},1.0/240);cpSpaceStep(space,1.0/240);}
        const auto final=rig.publish(desired,{});
        near(final.getWorldTransform(0,{}).y,3,"animated anchor holds under gravity");
        expect(final.getWorldTransform(2,{}).y>3,"dynamic descendants respond to gravity");
        const auto elbow=final.getWorldTransform(1,{});const auto hand=final.getWorldTransform(2,{});
        expect(std::abs(std::hypot(hand.x-elbow.x,hand.y-elbow.y)-5)<.03,"joint drift remains below 0.03 layer units");
        auto rotated=desired.copy();rotated.rotateLocal(0,.3);rig.prepare(rotated,{},.125);cpSpaceStep(space,.125);
        near(rig.getBodyState(0).rotation,.3,"kinematic anchor integrates to desired angle in seconds");
        auto copied=rig.publish(rotated,{});near(copied.getWorldBindingTransform(2,{}).x,copied.getWorldTransform(2,{}).x,"physical descendants drive artwork");
    }
    int bodies=0,shapes=0,joints=0;
    cpSpaceEachBody(space,[](cpBody*,void* n){++*static_cast<int*>(n);},&bodies);
    cpSpaceEachShape(space,[](cpShape*,void* n){++*static_cast<int*>(n);},&shapes);
    cpSpaceEachConstraint(space,[](cpConstraint*,void* n){++*static_cast<int*>(n);},&joints);
    expect(!bodies&&!shapes&&!joints,"rig destructor releases bodies, shapes and joints");
    def.bodies[0].mode=pdg::animationBody_Dynamic;def.rootMode=pdg::animationRoot_Follow;
    {
        auto rig=std::make_unique<pdg::AnimationPhysicsRig>(space,def,desired,pdg::AnimationTransform{},2,0,0);
        auto state=rig->getBodyState(0);cpBodyApplyImpulseAtWorldPoint(rig->body(0),cpv(3,0),cpv(state.x,state.y));near(rig->getBodyState(0).velocityX,5,"linear impulse has mass times units per second");
        for(int i=0;i<20;++i)cpSpaceStep(space,.005);
        auto root=rig->followingRoot(desired,{});auto final=rig->publish(desired,root);
        near(final.getLocalTransform(0).x,desired.getLocalTransform(0).x,"passive root transfer retains authored root offset");
        expect(root.y>0,"passive root follows gravity");
        struct LockedDestruction{std::unique_ptr<pdg::AnimationPhysicsRig>* rig;cpSpace* space;};LockedDestruction context{&rig,space};
        cpSpaceEachBody(space,[](cpBody*,void* data){auto& c=*static_cast<LockedDestruction*>(data);if(!*c.rig)return;
            auto* retained=(*c.rig)->body(0);c.rig->reset();
            expect(pdg::AnimationPhysicsRig::find(retained)==nullptr,"locked destruction removes collision dispatch ownership immediately");
            expect(cpSpaceContainsBody(c.space,retained),"locked destruction defers physical removal");
        },&context);
        bodies=0;cpSpaceEachBody(space,[](cpBody*,void* n){++*static_cast<int*>(n);},&bodies);expect(bodies==0,"post-step destruction releases bodies");
    }
    auto invalid=def;invalid.version=2;bool rejected=false;
    try{pdg::AnimationPhysicsRig rig(space,invalid,desired,{});}catch(const std::invalid_argument&){rejected=true;}expect(rejected,"definition version validation");
    invalid=def;invalid.bodies[0].mass=0;rejected=false;try{pdg::AnimationPhysicsRig rig(space,invalid,desired,{});}catch(const std::invalid_argument&){rejected=true;}expect(rejected,"zero mass validation");
    pdg::AnimationTransform reflected;reflected.scaleX=-1;rejected=false;try{pdg::AnimationPhysicsRig rig(space,def,desired,reflected);}catch(const std::invalid_argument&){rejected=true;}expect(rejected,"unsupported physical scale diagnosed");
    cpSpaceFree(space);
    layer->setGravity(40);layer->setDamping(1);
    auto* conflict=sprite->createPart("forearm");
    bool conflictRejected=false;
    try { sprite->setupAnimationPhysics(def); } catch (const std::logic_error&) { conflictRejected=true; }
    expect(conflictRejected && sprite->getPartCount()==1 && sprite->physics==pdg::PhysicsBody::NoPhysics,
        "named Part conflict rejects without creating bodies or other Parts");
    sprite->removePart(conflict->getId());
    sprite->setupPhysicsBody();sprite->setupAnimationPhysics(def);int updates=0;
    auto* physicalPart=sprite->findPart("hand");physicalPart->addRef();
    auto& retainedBody=static_cast<pdg::PhysicsBody&>(physicalPart->physics);retainedBody.addRef();
    expect(physicalPart->getBoneId()==2 && retainedBody.getSolver()==pdg::physicsSolver_Chipmunk,
        "named Part exposes the mapped bone's actual shared solver body");
    bool mutationRejected=false;
    try { physicalPart->removePhysicsBody(); } catch (const std::logic_error&) { mutationRejected=true; }
    expect(mutationRejected && physicalPart->physics==retainedBody,"mapped body cannot be removed while constrained");
    mutationRejected=false;
    try { sprite->removePart(physicalPart->getId()); } catch (const std::logic_error&) { mutationRejected=true; }
    expect(mutationRejected && sprite->findPart("hand")==physicalPart,"mapped Part removal preserves the rig");
    mutationRejected=false;
    try { physicalPart->unbindFromBone(); } catch (const std::logic_error&) { mutationRejected=true; }
    expect(mutationRejected && physicalPart->getBoneId()==2,"mapped binding cannot lose physical authority");
    mutationRejected=false;
    try { retainedBody.setMode(pdg::physicsBody_Kinematic); } catch (const std::logic_error&) { mutationRejected=true; }
    expect(!mutationRejected && sprite->getAnimationPhysicsMode("hand")==pdg::animationPhysics_Driven,"direct body Kinematic edit starts coordinated recovery");
    retainedBody.setMode(pdg::physicsBody_Dynamic);
    expect(sprite->getAnimationPhysicsMode("hand")==pdg::animationPhysics_Dynamic,"direct Dynamic edit cancels recovery");
    auto& rootBody=static_cast<pdg::PhysicsBody&>(sprite->findPart("shoulder")->physics);
    rootBody.setMass(2).setMomentOfInertia(4).setFriction(.2).setRestitution(.3);
    rootBody.applyImpulse(pdg::Vector(4,0));near(rootBody.getVelocity().x,2,"Part impulse uses its configured mass");
    rootBody.applyAngularImpulse(2);near(rootBody.getAngularVelocity(),.5,"Part angular impulse uses configured inertia");
    rootBody.setVelocity(0,0).setAngularVelocity(0);
    rootBody.applyForce(pdg::Vector(2,0),.1);
    rootBody.applyTorque(1,.1);
    const auto driveStart=rootBody.getState();
    rootBody.setDriveTarget(pdg::Point(driveStart.x+10,driveStart.y),driveStart.rotation,1,1);


    sprite->addAnimationModifier([&](auto,const auto&){++updates;});
    auto* manager=pdg::SpriteManager::getSingletonInstance();
    for(int i=0;i<20;++i){manager->stepAnimationPhysics(5);layer->animateLayer(5);}
    expect(updates==20,"one desired-pose callback per manager update");
    expect(rootBody.isDriveEnabled() && rootBody.getDriveState().forceX>0,
        "mapped Part physical drive participates in world load integration");

    const auto state=sprite->findPart("hand")->physics.getState();const auto hand=sprite->getAnimationBoneTransform("hand",pdg::animationSpace_World);
    near(hand.x,state.x-std::cos(state.rotation),"final bone matches physical body offset");
    near(sprite->mEntityInstance->getObjectInstance("hand_art")->getPosition().y,hand.y,"renderer receives post-physics publication");
    expect(sprite->getLocation().y>0,"passive physics owns Sprite root translation");
    const auto partTransform=physicalPart->getTransform(pdg::partSpace_World);
    near(partTransform.tx,retainedBody.getState().x,"Part world position is published once from the solved bone");
    near(partTransform.ty,retainedBody.getState().y,"Part world position includes the capsule offset");
    rootBody.clearDrive();sprite->disableAnimationPhysics(0);
    expect(physicalPart->physics==pdg::PhysicsBody::NoPhysics && !retainedBody.isAttached(),
        "disable removes owner associations without invalidating retained bodies");
    expect(retainedBody.getSolver()==pdg::physicsSolver_Basic,"retained body detaches before rig storage destruction");
    const auto retainedVelocity=retainedBody.getVelocity().x;
    retainedBody.applyImpulse(pdg::Vector(2,0));
    near(retainedBody.getVelocity().x,retainedVelocity+2/retainedBody.getMass(),"retained body remains usable after disable");
    retainedBody.release();physicalPart->release();
    expect(!sprite->isAnimationPhysicsEnabled(),"explicit zero recovery releases bodies immediately");
    sprite->pauseAnimation();sprite->seekAnimation("reference",0);sprite->setupPhysicsBody();sprite->setupAnimationPhysics(def);
    sprite->addRef();
    cpSpaceEachBody(layer->getSpace(),[](cpBody*,void* data){auto* s=static_cast<pdg::Sprite*>(data);if(!s->getLayer())return;
        s->getLayer()->removeSprite(s);expect(s->isAnimationPhysicsEnabled(),"locked removal keeps rig alive until post-step");
    },sprite);
    expect(!sprite->isAnimationPhysicsEnabled() && !sprite->getLayer(),"deferred removal releases physical ownership");sprite->release();
    pdg::cleanupLayer(layer);
}
#endif


#ifndef PDG_NO_EVENT_QUEUE
struct TriggerRecord{std::string name,clip,entity;double time,offset;long id;};
std::vector<TriggerRecord> takeTriggers(){
    std::vector<TriggerRecord> result;long type;pdg::UserData* data;pdg::EventEmitter* emitter;
    auto* manager=pdg::EventManager::getSingletonInstance();
    while(manager->getQueuedEvent(type,data,emitter)){
        if(type==pdg::eventType_SpriteTriggerEvent){const auto* e=static_cast<pdg::SpriteTriggerEventInfo*>(data->getData());result.push_back({e->triggerName,e->clipName,e->entityName,e->timeSeconds,e->offsetSeconds,e->id});}
        data->release();
    }return result;
}
void authoredTriggers(const std::string& path){
#ifdef PDG_NO_GUI
    auto* layer=pdg::createSpriteLayer();
#else
    auto* layer=pdg::createSpriteLayer(nullptr);
#endif
    auto* sprite=layer->createSpriteFromSpriterFile(path.c_str());expect(sprite->enableAnimationPose("reference"),"trigger fixture enables");
    takeTriggers();sprite->enableSpriterEvents();sprite->seekAnimation("reach",0);sprite->resumeAnimation();step(*sprite,2250);
    auto events=takeTriggers();expect(events.size()==9,"all authored crossings delivered over multiple loops");
    const char* order[]={"contact","release","contact","cycle","contact","release","contact","cycle","contact"};
    for(size_t i=0;i<events.size();++i){expect(events[i].name==order[i],"triggers ordered by occurrence");near(events[i].offset,(i+1)*.25,"trigger update offset in seconds");expect(events[i].clip=="reach"&&events[i].entity=="arm","owned clip/entity names");if(i)expect(events[i].id>events[i-1].id,"trigger IDs ordered");}
    sprite->pauseAnimation();step(*sprite,1000);sprite->sampleAnimationPose("reach",.75);sprite->getAnimationPose();sprite->getAttachPoint("grip");expect(takeTriggers().empty(),"paused/sample/query paths are silent");
    sprite->seekAnimation("reach",.5);expect(takeTriggers().empty(),"seek skips crossed triggers");sprite->resumeAnimation();step(*sprite,250);events=takeTriggers();expect(events.size()==1&&events[0].name=="contact","seek destination emits next crossing once");
    sprite->transitionToAnimation("reach",.2,.5);step(*sprite,100);events=takeTriggers();expect(events.size()==1&&events[0].name=="contact","independent crossfade owns destination events only");near(events[0].offset,.05,"destination event timestamp honors independent seek");
    sprite->seekAnimation("reach_once",.9);step(*sprite,250);events=takeTriggers();expect(events.size()==1&&events[0].name=="finished","nonloop endpoint trigger fires");near(events[0].time,1,"nonloop endpoint seconds");step(*sprite,250);expect(takeTriggers().empty(),"finished clip does not repeat endpoint trigger");
    sprite->seekAnimation("reach",0);sprite->resumeAnimation();sprite->disableAnimationPose();step(*sprite,250);expect(takeTriggers().size()==1,"authored triggers do not require pose opt-in");
    sprite->startAnimation("reference");sprite->startAnimation("reach");step(*sprite,250);
    pdg::cleanupLayer(layer);expect(takeTriggers().empty(),"layer teardown purges retained trigger events");
}
#endif


void fallbackCollisionUnits(){
    pdg::Sprite a,b;
    a.setupPhysicsBody(2);b.setupPhysicsBody(3);
    a.physics.setRestitution(.5);b.physics.setRestitution(.8);
    auto& ac=a.setupCollider().setCircle(1);auto& bc=b.setupCollider().setCircle(1);
    pdg::CollisionWorld world;pdg::Vector impulse;
    ac.setContactHandler([&](const pdg::ColliderContact& contact) { if(contact.phase!=pdg::collision_End)impulse=contact.impulse; });
    auto collide=[&] { impulse=pdg::Vector();world.step({&ac,&bc},.01); };
    a.setLocation(0,0);b.setLocation(1,0);a.physics.setVelocity(3,0);b.physics.setVelocity(-1,0);
    collide();
    near(a.physics.getVelocity().x,3-impulse.x/2,"collider payload reports impulse on other");
    near(b.physics.getVelocity().x,-1+impulse.x/3,"collider impulse is equal and opposite");
    near(2*a.physics.getVelocity().x+3*b.physics.getVelocity().x,3,"basic response conserves momentum with unequal restitution");
    expect(.5*2*std::pow(a.physics.getVelocity().x,2)+.5*3*std::pow(b.physics.getVelocity().x,2)<=10.5,"basic response does not add kinetic energy");
    a.setLocation(0,0);b.setLocation(0,0);a.physics.setVelocity(1,0);b.physics.setVelocity(-1,0);collide();
    expect(std::isfinite(impulse.x)&&std::isfinite(a.physics.getVelocity().x),"coincident centers have finite response");
    a.setLocation(0,0);b.setLocation(1,0);a.physics.setVelocity(-1,0);b.physics.setVelocity(1,0);collide();
    near(impulse.x,0,"separating bodies receive no impulse");
    a.setLocation(0,0);b.setLocation(1,0);
    a.physics.setVelocity(1,2).setFriction(1).setRestitution(0);
    b.physics.setMode(pdg::physicsBody_Static).setFriction(1).setRestitution(0);
    collide();
    near(a.physics.getVelocity().x,0,"basic static contact stops normal motion");
    expect(a.physics.getVelocity().y<2,"basic contact friction opposes tangent motion");
    near(b.physics.getSpeed(),0,"basic static contact remains stationary");
}

#if defined(PDG_USE_CHIPMUNK_PHYSICS) && !defined(PDG_NO_EVENT_QUEUE)
void physicalContacts(const std::string& path){
    for(unsigned elapsed:{5u,30u}){
#ifdef PDG_NO_GUI
        auto* layer=pdg::createSpriteLayer();
#else
        auto* layer=pdg::createSpriteLayer(nullptr);
#endif
        layer->setUseChipmunkPhysics(true);layer->setGravity(0);layer->setDamping(1);
        auto* sprite=layer->createSpriteFromSpriterFile(path.c_str());sprite->pauseAnimation();expect(sprite->enableAnimationPose("reference"),"contact pose enables");
        pdg::AnimationPhysicsDefinition def;def.rootMode=pdg::animationRoot_Follow;pdg::AnimationPhysicsBody b;b.bone=0;b.length=0;b.radius=1;b.mass=2;b.friction=0;def.bodies.push_back(b);
        auto* wall=layer->createSprite();wall->setLocation(pdg::Point(3.9,3));wall->setupPhysicsBody().setMode(pdg::physicsBody_Static);wall->setupCollider().setCircle(1);layer->enableCollisions();
        sprite->setupPhysicsBody();sprite->setupAnimationPhysics(def);
        auto* part=sprite->findPart("shoulder");bool collision=false;
        part->collider.setContactHandler([&](const pdg::ColliderContact& info){
            collision=true;expect(info.collider==part->collider.operator->() || info.other==part->collider.operator->(),"shared contact identifies physical Part");
        });
        const auto body=part->physics.getState();part->physics.applyImpulse(pdg::Vector(4,0),pdg::Point(body.x,body.y));
        pdg::SpriteManager::getSingletonInstance()->stepAnimationPhysics(elapsed);layer->animateLayer(elapsed);
        expect(collision,"physical bone makes contact with Sprite shape");
        const auto rootBefore=sprite->getLocation();layer->stopAnimations();
        pdg::SpriteManager::getSingletonInstance()->stepAnimationPhysics(elapsed);layer->animateLayer(elapsed);
        const auto final=sprite->getAnimationBoneTransform("shoulder",pdg::animationSpace_World);const auto state=sprite->findPart("shoulder")->physics.getState();
        near(final.x,state.x,"layer animation pause preserves body/pose agreement");
        auto* space=layer->getSpace();
        cpSpaceEachBody(space,[](cpBody*,void* data){pdg::cleanupLayer(static_cast<pdg::SpriteLayer*>(data));},layer);
        expect(pdg::SpriteManager::getSingletonInstance()->mFirstLayer==nullptr,"layer cleanup deferred safely from locked iteration");
    }
}
#endif

void transitionSprite(const std::string& path) {
#ifdef PDG_NO_GUI
    auto* layer=pdg::createSpriteLayer();
#else
    auto* layer=pdg::createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    layer->setUseChipmunkPhysics(false);
#endif
    auto* sprite=layer->createSpriteFromSpriterFile(path.c_str());sprite->pauseAnimation();
    expect(sprite->enableAnimationPose("reference"),"transition fixture enables");
    const double pi=3.14159265358979323846;
    sprite->seekAnimation("reach",0.25);
    near(sprite->getAnimationBoneTransform("shoulder").rotation,pi/4,"fractional-seconds seek");
    expect(sprite->isAnimationPaused(),"seek preserves pause");
    sprite->transitionToAnimation("reference",0,1);
    near(sprite->getAnimationBoneTransform("shoulder").rotation,pi/4,"transition starts continuously");
    sprite->resumeAnimation();step(*sprite,250);
    near(sprite->getAnimationTransitionProgress(),0.25,"transition progress uses seconds");
    near(sprite->getAnimationBoneTransform("shoulder").rotation,3*pi/8,"outgoing and destination clips advance independently");
    sprite->pauseAnimation();step(*sprite,250);
    near(sprite->getAnimationTransitionProgress(),0.25,"pause freezes independent transition");
    const auto before=sprite->getAnimationBoneTransform("shoulder");
    bool rejected=false;try{sprite->transitionToAnimation("missing",0,1);}catch(const std::exception&){rejected=true;}
    expect(rejected && sprite->isAnimationTransitioning(),"invalid transition preserves current transition");
    near(sprite->getAnimationBoneTransform("shoulder").rotation,before.rotation,"invalid transition preserves current pose");
    sprite->transitionToAnimation("reach_once",0.25,0.5);
    near(sprite->getAnimationBoneTransform("shoulder").rotation,3*pi/8,"interruption captures current base pose");
    sprite->resumeAnimation();step(*sprite,250);
    near(sprite->getAnimationBoneTransform("shoulder").rotation,7*pi/16,"interrupted source freezes while destination advances");
    step(*sprite,1000);
    expect(!sprite->isAnimationTransitioning() && !sprite->isAnimationPlaying(),"large step completes transition and nonloop destination");
    near(sprite->getAnimationTransitionProgress(),1,"completed transition progress is one");
    near(sprite->getAnimationBoneTransform("shoulder").rotation,pi/2,"transition publishes destination endpoint");
    sprite->seekAnimation("reach",-0.75);near(sprite->getAnimationProgress(),0.25,"negative seek wraps looping clips");
    sprite->transitionToAnimation("reference",0,0);
    expect(!sprite->isAnimationTransitioning(),"zero duration snaps immediately");near(sprite->getAnimationTransitionProgress(),1,"instant transition completed progress");
    sprite->seekAnimation("reach_once",3);near(sprite->getAnimationProgress(),1,"nonloop seek clamps endpoint");
    sprite->resumeAnimation();near(sprite->getAnimationProgress(),0,"resume restarts a sought nonloop endpoint");
    pdg::cleanupLayer(layer);
}

void modifierSprite(const std::string& path) {
#ifdef PDG_NO_GUI
    auto* layer=pdg::createSpriteLayer();
#else
    auto* layer=pdg::createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    layer->setUseChipmunkPhysics(false);
#endif
    auto* sprite=layer->createSpriteFromSpriterFile(path.c_str());sprite->pauseAnimation();
    expect(sprite->enableAnimationPose("reference"),"modifier fixture enables");
    double phase=0;auto token=std::make_shared<int>(1);std::weak_ptr<int> lifetime=token;
    auto id=sprite->addAnimationModifier([&,token](auto view,const auto& context){
        // Script GC can finalize an unrelated Sprite during pose evaluation.
        // Destroying one with no physical rig must remain a harmless no-op.
        { pdg::Sprite temporary; }
        phase+=context.deltaSeconds;auto shoulder=view.getLocalTransform(0);shoulder.rotation=phase;view.setLocalTransform(0,shoulder);
    });token.reset();
    sprite->startAnimation("reference");step(*sprite,250);
    near(phase,0.25,"Sprite supplies floating-point seconds exactly once");
    near(sprite->getAnimationBoneTransform("shoulder").rotation,0.25,"Sprite publishes procedural rotation");
    sprite->pauseAnimation();step(*sprite,250);near(phase,0.25,"paused modifier integration freezes");
    sprite->setAnimationSource(pdg::animationSource_Reference);
    sprite->getAnimationPose();near(phase,0.25,"manual query supplies zero elapsed seconds");
    expect(sprite->getAnimationModifierError(id).empty(),"successful modifier has no error");
    sprite->clearAnimationModifiers();expect(lifetime.expired(),"clear releases callback captures");
    const auto failing=sprite->addAnimationModifier([&](auto view,const auto&){view.rotateLocal(0,1);pdg::cleanupLayer(layer);});
    near(sprite->getAnimationBoneTransform("shoulder").rotation,0,"unsafe owner destruction rolls back modifier");
    expect(!sprite->getAnimationModifierError(failing).empty(),"unsafe lifecycle mutation diagnosed");
    sprite->clearAnimationModifiers();

    pdg::AnimationTwoBoneIK ik;ik.root=0;ik.middle=1;ik.tip=2;ik.rootLength=10;ik.middleLength=5;ik.targetX=10;ik.targetY=10;
    const auto ikId=sprite->addAnimationIK(ik);
    expect(sprite->getAnimationIKResult(ikId).reachable,"Sprite constraint reaches target");
    near(sprite->getAnimationBoneTransform("hand",pdg::animationSpace_Rig).x,10,"IK final bone publication");
    near(sprite->getAnimationBindingTransform("hand_art",pdg::animationSpace_Rig).y,10,"IK artwork publication");
    near(sprite->mEntityInstance->getObjectInstance("hand_art")->getPosition().x,10,"renderer consumes solved IK transform");
    sprite->setAnimationIKTarget(ikId,100,0,pdg::animationSpace_World);
    expect(sprite->getAnimationIKResult(ikId).clamped,"Sprite IK exposes unreachable diagnostics");
    sprite->removeAnimationModifier(ikId);
    near(sprite->getAnimationBoneTransform("hand",pdg::animationSpace_Rig).x,17,"IK removal restores source pose");

    token=std::make_shared<int>(2);lifetime=token;
    sprite->addAnimationModifier([token](auto,const auto&){});token.reset();
    auto* removed=layer->createSpriteFromSpriterFile(path.c_str());removed->addRef();
    expect(removed->enableAnimationPose("reference"),"removed fixture enables pose");
    layer->removeSprite(removed);
    sprite->addRef();pdg::cleanupLayer(layer);
    expect(removed->isAnimationPoseEnabled() && removed->isSpriterSprite(),"removed Sprite retains imported model after cache teardown");
    near(removed->getAnimationBoneTransform("hand",pdg::animationSpace_Rig).x,17,"retained removed Sprite still evaluates its rig");
    removed->release();
    expect(!lifetime.expired() && sprite->isAnimationPoseEnabled() && sprite->isSpriterSprite(),"retained Sprite keeps its callbacks and rig after Layer destruction");
    sprite->release();
    expect(lifetime.expired(),"last Sprite reference releases retained modifier callbacks");
}


void transferredModel(const std::string& path) {
#ifdef PDG_NO_GUI
    auto* source = pdg::createSpriteLayer(); auto* destination = pdg::createSpriteLayer();
#else
    auto* source = pdg::createSpriteLayer(nullptr); auto* destination = pdg::createSpriteLayer(nullptr);
#endif
    auto* sprite = source->createSpriteFromSpriterFile(path.c_str()); sprite->addRef();
    auto* removed = source->createSpriteFromSpriterFile(path.c_str()); removed->addRef();
    std::weak_ptr<SpriterEngine::SpriterModel> model = sprite->mSpriterModelOwner;
    expect(sprite->mSpriterModelOwner == removed->mSpriterModelOwner, "cached imported models share one owner");
    sprite->pauseAnimation(); expect(sprite->enableAnimationPose("reference"), "transferred model pose enables");
    auto rig = sprite->getAnimationRig();
    auto* hand = sprite->createPart("hand"); hand->bindToBone(rig->findBone("hand"));
    destination->addSprite(sprite); source->removeSprite(removed); pdg::cleanupLayer(source);
    expect(!model.expired() && sprite->getLayer() == destination, "transferred Sprite retains the source model independently");
    expect(hand->isBoundToBone() && hand->getBoneId() == rig->findBone("hand"), "source Layer destruction preserves Part bone identity");
    auto sample = sprite->sampleAnimationPose("reach", .25);
    near(sample.getLocalTransform(rig->findBone("shoulder")).rotation, 3.14159265358979323846/4, "pose sampling can instantiate model objects after source cache destruction");
    removed->activateSubEntity(removed->mEntityInstance->currentEntityName().c_str(), "reach");
    expect(removed->hasAnimation("reach"), "off-layer Sprite can still select and inspect clips");
    removed->release();
    pdg::cleanupLayer(destination);
    expect(sprite->isSpriterSprite() && sprite->isAnimationPoseEnabled(), "retained Sprite survives destination Layer destruction too");
    sprite->release();
    expect(model.expired(), "last Sprite and cache references release the imported model");
    expect(rig->getBoneCount() == 3, "owned rig descriptions remain usable after imported model destruction");
}

void editableArm(const std::string& path) {
    #ifdef PDG_NO_GUI
    auto* layer = pdg::createSpriteLayer();
    #else
    auto* layer = pdg::createSpriteLayer(nullptr);
    #endif
    #ifdef PDG_USE_CHIPMUNK_PHYSICS
    layer->setUseChipmunkPhysics(false);
    #endif
    auto* sprite = layer->createSpriteFromSpriterFile(path.c_str());
    auto* other = layer->createSpriteFromSpriterFile(path.c_str());
    expect(sprite && other, "arm fixtures load");
    sprite->pauseAnimation(); other->pauseAnimation();
    expect(sprite->enableAnimationPose("reference"), "fixed hierarchy pose enabled: " + sprite->getAnimationRigError());
    expect(other->enableAnimationPose("reference"), "second pose enabled");
    auto rig = sprite->getAnimationRig();
    expect(rig == other->getAnimationRig(), "shared model/reference yields shared immutable rig");
    expect(rig->getBoneCount() == 3 && rig->getBindingCount() == 5 && rig->getSocketCount() == 1, "bone/art/socket/box inventory");
    expect(sprite->getAnimationDebugDraw() == pdg::animationDebug_None, "debug drawing starts disabled");
#ifdef PDG_NO_GUI
    expect(!sprite->isAnimationDrawingSupported(), "headless drawing capability is false");
    bool drawingRejected = false;
    try { sprite->setAnimationDebugDraw(pdg::animationDebug_Bones); } catch (const std::logic_error&) { drawingRejected = true; }
    expect(drawingRejected && sprite->getAnimationDebugDraw() == 0, "headless debug drawing fails explicitly without changing state");
#else
    expect(sprite->isAnimationDrawingSupported(), "GUI drawing capability is true");
#endif
    near(rig->getBone(rig->findBone("forearm")).length, 0, "display bone width is not an inferred IK length");
    const auto snapshot = sprite->getAnimationPose();
    near(sprite->getAttachPoint("grip").x, 20, "reference hand socket");
    auto shoulder = sprite->getAnimationBoneTransform("shoulder"); shoulder.rotation = 3.14159265358979323846 / 2;
    auto* child = layer->createSprite();
    sprite->attachSprite(child, "grip");
    other->attachSprite(child, "grip");
    expect(other->getAttachedSprite("grip") == nullptr, "a Spriter child has only one attachment writer");
    auto* alternateMount=other->createPart("alternate_mount");
    bool mountRejected=false;
    try { alternateMount->attachSprite(child); } catch(const std::logic_error&) { mountRejected=true; }
    expect(mountRejected, "Part mounting rejects an existing Spriter attachment even outside a layer");
    other->removePart(alternateMount->getId());
    sprite->setAnimationBoneTransform("shoulder", shoulder);
    near(sprite->getAnimationBoneTransform("hand", pdg::animationSpace_Rig).y, 18, "bone edit rebuilds descendants");
    near(sprite->getAnimationBindingTransform("hand_art", pdg::animationSpace_Rig).y, 18, "art binding follows edited bone");
    near(sprite->mEntityInstance->getObjectInstance("hand_art")->getPosition().y, 18, "renderer object consumes published art transform");
    near(sprite->getAttachPoint("grip").x, 2, "edited socket x");
    near(sprite->getAttachPoint("grip").y, 21, "edited socket y");
    near(child->getLocation().y, 21, "attached child follows immediate pose edit");
    expect(sprite->checkSpriterCollisionBoxPointCollision({2, 20}), "box query consumes edited pose");
    expect(!sprite->checkSpriterCollisionBoxPointCollision({19, 3}), "original box location no longer hits");
    near(other->getAttachPoint("grip").x, 20, "pose edit does not affect shared model instance");
    near(snapshot.getSocketTransform(0).x, 20, "owned pose snapshot remains unchanged");
    for (int i = 0; i < 20; ++i) step(*sprite, 10);
    near(sprite->getAttachPoint("grip").y, 21, "paused reevaluation has no drift");
    sprite->setLocation({100, 50}); sprite->setScale(-2, 3);
    near(sprite->getAttachPoint("grip").x, -4, "reflected root applied once to final socket");
    near(sprite->getAttachPoint("grip").y, 45, "nonuniform root traverses full hierarchy");
    near(child->getLocation().y, 95, "root change updates attached child when pose refreshed");
    near(sprite->getAnimationBindingTransform("hand_art", pdg::animationSpace_World).y, 89, "world artwork hierarchy");
    const auto before = sprite->getAnimationBoneTransform("shoulder");
    bool rejected = false;
    auto invalid = before; invalid.x = std::numeric_limits<double>::infinity();
    try { sprite->setAnimationBoneTransform("shoulder", invalid); } catch (const std::exception&) { rejected = true; }
    expect(rejected, "invalid override rejected");
    near(sprite->getAnimationBoneTransform("shoulder").x, before.x, "invalid override is atomic");
    sprite->clearAnimationBoneTransforms();
    near(sprite->getAnimationBoneTransform("hand", pdg::animationSpace_Rig).x, 17, "clear returns to sampled pose");
    const auto time = sprite->getAnimationProgress();
    const auto sample = sprite->sampleAnimationPose("reach", 0.25);
    near(sample.getLocalTransform(rig->findBone("shoulder")).rotation, 3.14159265358979323846 / 4, "fractional seconds sample uses evaluator interpolation");
    near(sprite->getAnimationProgress(), time, "sampling does not seek live playback");
    expect(sprite->isAnimationPaused(), "sampling does not resume playback");
    near(sprite->getAnimationBoneTransform("shoulder").rotation, 0, "sampling does not change live pose");
    near(sprite->sampleAnimationPose("reach", 1.25).getLocalTransform(0).rotation, sample.getLocalTransform(0).rotation, "sample wraps looping seconds");
    near(sprite->sampleAnimationPose("reach", -0.75).getLocalTransform(0).rotation, sample.getLocalTransform(0).rotation, "negative samples wrap consistently");
    near(sprite->sampleAnimationPose("reach_once", -0.5).getLocalTransform(0).rotation, 0, "nonloop sample clamps before start");
    near(sprite->sampleAnimationPose("reach_once", 1.5).getLocalTransform(0).rotation, 3.14159265358979323846 / 2, "nonloop sample clamps beyond end");
    const auto& metadata = sample.getMetadata();
    expect(metadata.variables.size() == 5 && metadata.tags.size() == 9, "sample metadata inventory");
    for (const auto& value : metadata.variables) {
        if (value.name == "speed") near(std::get<double>(value.value), 5, "sample typed float variable");
        if (value.name == "phase") expect(std::get<int>(value.value) == 3, "sample typed integer variable");
        if (value.name == "mode") expect(std::get<std::string>(value.value) == "reach_start", "sample typed string variable");
    }
    rejected = false;
    try { sprite->sampleAnimationPose("reach", std::numeric_limits<double>::quiet_NaN()); } catch (const std::exception&) { rejected = true; }
    expect(rejected && sprite->isAnimationPaused(), "nonfinite sample rejected without side effects");
    expect(!sprite->enableAnimationPose("missing") && sprite->isAnimationPoseEnabled(), "invalid reference preserves enabled pose");
    sprite->setScale(1, 1); sprite->setLocation({0, 0});
    sprite->startAnimation("reference"); sprite->blendToAnimation("reach", 0.5);
    step(*sprite, 250);
    near(sprite->getAnimationBoneTransform("shoulder").rotation, 3.14159265358979323846 / 8, "phase blend sampled once into local pose");
    const auto blended = sprite->getAttachPoint("grip");
    sprite->pauseAnimation(); step(*sprite, 500);
    near(sprite->getAttachPoint("grip").x, blended.x, "paused blend preserves edited-pose path");
    sprite->resumeAnimation(); step(*sprite, 250);
    near(sprite->getAnimationBoneTransform("shoulder").rotation, 3.14159265358979323846 / 2, "pose adapter follows completed blend destination");
    sprite->disableAnimationPose();
    expect(!sprite->isAnimationPoseEnabled() && !sprite->getAnimationRig(), "disable releases pose access");
    near(sprite->getAttachPoint("grip").x, 2, "disable restores evaluator pose");
    // Structurally unsupported rigs retain their existing playback path.
    auto badPath = path.substr(0, path.find_last_of('/') + 1) + "changing-arm.scml";
    auto* unsupported = layer->createSpriteFromSpriterFile(badPath.c_str());
    expect(unsupported && !unsupported->enableAnimationPose("reference"), "changing hierarchy is rejected");
    expect(!unsupported->getAnimationRigError().empty() && unsupported->isAnimationPlaying(), "unsupported rig reports reason and retains playback");
    pdg::cleanupLayer(layer);
}

void coordinates(SpriterEngine::SpriterModel& model) {
    pdg::Sprite sprite(model.getNewEntityInstance(0), &model);
    sprite.startAnimation("a");
    sprite.pauseAnimation();
    sprite.setLocation(pdg::Point(100, 40));
    near(sprite.getAttachPoint("socket").x, 10, "query returns root-relative offset");
    auto box = sprite.getSpriterCollisionBox("hitbox");
    near(box.left, 110, "box applies root once");
    near(box.top, 30, "box includes converted authored pivot");
    expect(!sprite.isSpriterCollisionActive("socket"), "points are not boxes");
    expect(!sprite.isSpriterCollisionActive(nullptr), "null box name is safe");
    expect(sprite.checkSpriterCollisionBoxPointCollision(pdg::Point(120, 35)), "translated box point hit");
    sprite.setLocation(pdg::Point(200, 40));
    expect(!sprite.checkSpriterCollisionBoxPointCollision(pdg::Point(120, 35)), "root change invalidates cached bounds while paused");
    expect(sprite.checkSpriterCollisionBoxPointCollision(pdg::Point(220, 35)), "new root point hit without ticking");
    sprite.rotateTo(3.14159265358979323846 / 2);
    near(sprite.getAttachPoint("socket").x, 0, "rotated socket x");
    near(sprite.getAttachPoint("socket").y, 10, "rotated socket y");
    expect(sprite.checkSpriterCollisionBoxPointCollision(pdg::Point(205, 60)), "rotated box hit uses quad");
    expect(!sprite.checkSpriterCollisionBoxPointCollision(pdg::Point(220, 35)), "unrotated location no longer hits");
    sprite.rotateTo(0);
    sprite.setScale(-2, 3);
    near(sprite.getAttachPoint("socket").x, -20, "reflected scaled socket");
    box = sprite.getSpriterCollisionBox("hitbox");
    near(box.left, 140, "reflected box left");
    near(box.right, 180, "reflected box right");
    near(box.top, 10, "scaled pivot top");
    near(box.bottom, 40, "scaled pivot bottom");
    expect(sprite.checkSpriterCollisionBoxPointCollision(pdg::Point(160, 25)), "reflected scaled hit");
    sprite.flipX();
    near(sprite.getAttachPoint("socket").x, 20, "flip toggles existing scale");
    sprite.setFlipX(true);
    near(sprite.getAttachPoint("socket").x, 20, "setting an existing flip is idempotent");
    sprite.setFlipX(false);
    near(sprite.getAttachPoint("socket").x, -20, "clearing a flip restores the previous scale");
    sprite.startAnimation("empty");
    expect(sprite.getSpriterCollisionBoxCount() == 0, "empty clip has no active boxes");
    expect(!sprite.isSpriterCollisionActive("hitbox"), "inactive named box rejected");
    expect(std::isnan(sprite.getAttachPoint("socket").x), "inactive socket query is missing");
    expect(!sprite.checkSpriterCollisionBoxPointCollision(pdg::Point(160, 25)), "empty pose invalidates hit bounds");
}

void boxOverlaps(SpriterEngine::SpriterModel& model) {
    pdg::Sprite first(model.getNewEntityInstance(0), &model);
    pdg::Sprite second(model.getNewEntityInstance(0), &model);
    first.setupAnimationCollider();second.setupAnimationCollider();
    const auto source=second.collider.getShapeId(0);
    first.setLocation(pdg::Point(100, 0));
    second.setLocation(pdg::Point(300, 0));
    expect(!first.collider.overlaps(second.collider), "translated separated boxes miss");
    second.setLocation(pdg::Point(100, 0));
    expect(first.collider.overlaps(second.collider), "translated boxes overlap");
    second.setLocation(pdg::Point(110, -20));
    second.rotateTo(3.14159265358979323846 / 2);
    expect(first.collider.overlaps(second.collider), "rotated boxes overlap");
    second.setScale(0, 0);
    expect(!first.collider.overlaps(second.collider), "zero-scale box cannot overlap");
    second.setScale(1, 1);
    second.startAnimation("empty");
    expect(!first.collider.overlaps(second.collider), "inactive box cannot overlap");
    const auto extra=second.collider.addCircle(2,pdg::Point(1000,0));
    expect(second.collider.getShapeCount()==1,"inactive source preserves only explicit geometry");
    second.startAnimation("a");
    expect(second.collider.getShapeCount()==2,"reactivated source preserves explicit additions");
    expect(second.collider.getShapeId(0)==source,"authored box ID survives disappearance and reappearance");
    expect(second.collider.removeShape(extra),"explicit addition is independently removable");
}

void compareTransformsWithSpriter() {
    for (double sx : {-2.0, 0.0, 1.0, 2.0}) for (double sy : {-3.0, 1.0, 3.0})
    for (double angle : {-0.6, 0.0, 1.3}) {
        pdg::AnimationTransform parent{17, -12, angle, sx, sy, 0.6};
        pdg::AnimationTransform local{5, 7, -0.8, 0.7, -0.4, 0.8};
        pdg::AnimationTransform tip{2, -3, 0.4, 1.2, 0.6, 0.5};
        SpriterEngine::BoneInstanceInfo nativeParent({1, 1}), nativeChild({1, 1}), nativeTip({1, 1});
        auto assign = [](SpriterEngine::BoneInstanceInfo& object, const pdg::AnimationTransform& value) {
            object.setPosition({value.x, value.y}); object.setAngle(value.rotation);
            object.setScale({value.scaleX, value.scaleY}); object.setAlpha(value.alpha);
        };
        assign(nativeParent, parent); assign(nativeChild, local); assign(nativeTip, tip);
        SpriterEngine::TransformProcessor first(&nativeParent); first.setTrigFunctions(); first.transformChildObject(&nativeChild);
        SpriterEngine::TransformProcessor second(&nativeChild); second.setTrigFunctions(); second.transformChildObject(&nativeTip);
        auto rig = pdg::AnimationRig::create({{"bone", pdg::animation_NoBone, local}, {"tip", 0, tip}});
        pdg::AnimationPose pose(rig);
        const auto result = pose.getWorldTransform(1, parent);
        near(result.x, nativeTip.getPosition().x, "pose x matches Spriter hierarchy");
        near(result.y, nativeTip.getPosition().y, "pose y matches Spriter hierarchy");
        near(result.rotation, nativeTip.getAngle(), "pose angle matches Spriter reflection");
        near(result.scaleX, nativeTip.getScale().x, "pose x scale matches Spriter");
        near(result.scaleY, nativeTip.getScale().y, "pose y scale matches Spriter");
        near(result.alpha, nativeTip.getAlpha(), "pose alpha matches Spriter");
    }
}
#ifdef PDG_USE_CHIPMUNK_PHYSICS
void physicsRoot(const char* path) {
    #ifdef PDG_NO_GUI
    auto* layer = pdg::createSpriteLayer();
    #else
    auto* layer = pdg::createSpriteLayer(nullptr);
    #endif
    layer->setUseChipmunkPhysics(true);
    auto* sprite = layer->createSpriteFromSpriterFile(path);
    expect(sprite && (sprite->physics == pdg::PhysicsBody::NoPhysics), "physics is optional even on a Chipmunk layer");
    sprite->setupPhysicsBody();
    expect(sprite->mBody, "explicit physics-backed sprite created");
    sprite->pauseAnimation();
    cpBodySetPosition(sprite->mBody, cpv(100, 40));
    cpBodySetAngle(sprite->mBody, 3.14159265358979323846 / 2);
    step(*sprite, 0);
    near(sprite->getAttachPoint("socket").x, 0, "physics root updates socket x");
    near(sprite->getAttachPoint("socket").y, 10, "physics root updates socket y");
    expect(sprite->checkSpriterCollisionBoxPointCollision(pdg::Point(105, 60)), "physics root updates box bounds");
    pdg::cleanupLayer(layer);
}
#endif

struct TrackedSprite : pdg::Sprite {
    int& destroyed;
    TrackedSprite(SpriterEngine::SpriterModel& model, int& count)
        : pdg::Sprite(model.getNewEntityInstance(0), &model), destroyed(count) {}
    ~TrackedSprite() override { ++destroyed; }
};
void attachments(SpriterEngine::SpriterModel& model) {
    int destroyed = 0;
    {
        pdg::Sprite parent(model.getNewEntityInstance(0), &model);
        auto* child = new TrackedSprite(model, destroyed);
        parent.attachSprite(child, "socket");
        parent.attachSprite(child, "socket");
        parent.attachSprite(nullptr, "socket");
        parent.attachSprite(&parent, "hitbox");
        child->attachSprite(&parent, "socket");
        expect(child->getAttachedSprite("socket") == nullptr, "attachment cycles rejected");
        expect(parent.getAttachedSprite("hitbox") == nullptr, "self attachment rejected");
        parent.setLocation(pdg::Point(100, 40));
        step(parent, 0);
        near(child->getLocation().x, 110, "attached child root translation once");
        near(child->getLocation().y, 40, "attached child y");
        parent.rotateTo(3.14159265358979323846 / 2);
        step(parent, 0);
        near(child->getLocation().x, 100, "attached child rotated x");
        near(child->getLocation().y, 50, "attached child rotated y");
        near(child->getRotation(), parent.getRotation(), "attachment inherits angle");
        parent.attachSprite(new TrackedSprite(model, destroyed), "socket");
        expect(destroyed == 1, "replacement releases exactly one reference");
        parent.detachSprite(parent.getAttachedSprite("socket"));
        expect(destroyed == 2 && !parent.getAttachedSprite("socket"), "detach releases and removes entry");
        parent.attachSprite(new TrackedSprite(model, destroyed), "socket");
        parent.activateSubEntity("alternate", "a");
        expect(destroyed == 3 && !parent.getAttachedSprite("socket"), "entity change releases attachments");
        parent.attachSprite(new TrackedSprite(model, destroyed), "socket");
    }
    expect(destroyed == 4, "parent destruction releases attachment");
}
#ifndef PDG_NO_GUI
struct RecordingPort : pdg::Port {
    int calls = 0;
    std::string operations;
    pdg::Rect getDrawingArea() override{return pdg::Rect(-1000,-1000,1000,1000);}
    bool fail = false, failLine = false;
    struct Line { pdg::Point from, to; double alpha, width; };
    std::vector<Line> lines;
    std::vector<pdg::Quad> debugQuads;
    std::vector<double> debugAlpha;
    struct Ellipse { pdg::Point center; float xRadius, yRadius; };
    std::vector<Ellipse> ellipses;
    void drawEllipse(const pdg::Point& center, float xRadius, float yRadius,
                     const pdg::Attributes& style) override {
        const auto p = style.getTransform() * glm::vec3(center.x, center.y, 1);
        ellipses.push_back({pdg::Point(p.x, p.y), xRadius, yRadius});
    }
    void drawLine(const pdg::Point& from, const pdg::Point& to, const pdg::Attributes& style) override {
        operations+='L';
        auto transform = [&](const pdg::Point& point) {
            const auto p = style.getTransform() * glm::vec3(point.x,point.y,1);
            return pdg::Point(p.x,p.y);
        };
        lines.push_back({transform(from), transform(to), style.getLineOpacity(), style.getLineThickness()});
        if (failLine) throw std::runtime_error("intentional debug draw failure");
    }
    void drawQuad(const pdg::Quad& quad, const pdg::Attributes& style) override {
        operations+='Q';
        pdg::Quad transformed(quad);
        for(auto& point:transformed.points){const auto p=style.getTransform()*glm::vec3(point.x,point.y,1);point=pdg::Point(p.x,p.y);}
        debugQuads.push_back(transformed); debugAlpha.push_back(style.getLineOpacity());
    }
    pdg::Quad lastQuad;
    std::vector<pdg::Quad> quads;
    uint8 lastOpacity = 0;
    void drawImage(pdg::Image* image, const pdg::Quad& quad, const pdg::Attributes& style) override {
        operations+='I';
        ++calls; lastQuad = quad;
        for(auto& point:lastQuad.points){const auto p=style.getTransform()*glm::vec3(point.x,point.y,1);point=pdg::Point(p.x,p.y);}
        lastOpacity = static_cast<uint8>(image->getOpacity()*style.getFillOpacity()); quads.push_back(lastQuad);
        if (fail) throw std::runtime_error("intentional draw failure");
    }
};

std::shared_ptr<pdg::Drawing> lineDrawing(double alpha = .4) {
    std::shared_ptr<pdg::Drawing> drawing(pdg::Drawing::create());
    pdg::Attributes attrs; attrs.lineOpacity(alpha).lineThickness(2);
    delete drawing->addLine(pdg::Point(0,0),pdg::Point(2,0),attrs);
    return drawing;
}
void sharedDrawingReplay() {
    RecordingPort port;
    auto child=std::unique_ptr<pdg::Drawing>(pdg::Drawing::create());
    pdg::Attributes leaf;leaf.lineOpacity(.5).lineThickness(2);
    auto element=std::unique_ptr<pdg::ElementRef>(child->addLine(pdg::Point(0,0),pdg::Point(10,10),leaf));
    auto parent=std::unique_ptr<pdg::Drawing>(pdg::Drawing::create());
    pdg::Attributes nested;nested.translation(pdg::Offset(5,7)).lineOpacity(.5);
    delete parent->addDrawing(pdg::Rect(2,3,22,33),*child,nested);
    bool cycle=false;try{child->addDrawing(pdg::Rect(0,0,1,1),*parent,pdg::Attributes());}catch(const std::invalid_argument&){cycle=true;}
    expect(cycle,"nested drawing rejects indirect containment cycles");
    auto retained=parent->share();child.reset();parent.reset();
    pdg::Attributes outer;glm::mat3 matrix(1);matrix[0][0]=-2;matrix[1][1]=3;matrix[2]=glm::vec3(100,50,1);
    outer.setTransform(matrix).lineOpacity(.5);
    retained->drawTransformed(&port,outer,true);
    near(port.lines[0].from.x,86,"nested destination/element/parent transforms compose x");
    near(port.lines[0].from.y,80,"nested destination/element/parent transforms compose y");
    near(port.lines[0].to.x,46,"nested drawing preserves reflection");
    near(port.lines[0].to.y,170,"nested drawing preserves nonuniform scale");
    near(port.lines[0].alpha,.125,"nested opacity multiplies once per level");
    near(port.lines[0].width,12,"local stroke uses determinant of complete transform once");
    pdg::Attributes updated;updated.lineOpacity(.8);element->setAttributes(updated);
    port.lines.clear();retained->drawTransformed(&port,outer,false);
    near(port.lines[0].alpha,.2,"element remains editable after its original Drawing is destroyed");
    near(port.lines[0].width,1,"pixel stroke remains unscaled");
    auto drawable=lineDrawing();port.lines.clear();
    port.drawDrawing(*drawable,pdg::Point(20,30),pdg::Attributes());
    near(port.lines[0].from.x,20,"Port Drawing point destination translates artwork");
    near(port.lines[0].from.y,30,"Port Drawing point destination translates y");
    port.lines.clear();drawable->draw(&port,pdg::Rect(40,50,60,50));
    near(port.lines[0].from.x,40,"Drawing rect destination maps origin");
    near(port.lines[0].to.x,60,"Drawing rect destination maps scale");
}
void customDrawing(const std::string& path){
    sharedDrawingReplay();
    RecordingPort port;auto* layer=pdg::createSpriteLayer(nullptr);layer->setSpritePort(&port);
    auto* sprite=layer->createSpriteFromSpriterFile(path.c_str());sprite->pauseAnimation();expect(sprite->enableAnimationPose("reference"),"custom drawing pose enables");
    std::vector<int> order;std::optional<pdg::AnimationDrawingContext> retained;
    pdg::AnimationDrawableOptions options;options.bone=1;options.bounds={-1,-1,3,1,false};
    auto add=[&](int placement,const std::string& slot,int value){options.placement=placement;options.slot=slot;return sprite->addAnimationDrawable(options,[&,value](auto context){order.push_back(value);retained=context;return lineDrawing();});};
    add(pdg::animationDraw_BeforeAll,"",1);add(pdg::animationDraw_BeforeSlot,"forearm_art",2);
    add(pdg::animationDraw_ReplaceSlot,"forearm_art",3);add(pdg::animationDraw_AfterSlot,"forearm_art",4);add(pdg::animationDraw_AfterAll,"",5);
    sprite->draw();expect(order==std::vector<int>({1,2,3,4,5}),"custom drawing placements preserve traversal order");expect(port.operations=="LILLLIL","custom art inserts around and replaces the named image slot");
    bool expired=false;try{retained->getTransform();}catch(const std::logic_error&){expired=true;}expect(expired,"native drawing context expires after invocation");
    sprite->setLocation(pdg::Point(40,30));sprite->setScale(-2,3);sprite->rotateTo(.35);sprite->setOpacity(.5);
    auto forearm=sprite->getAnimationBoneTransform("forearm");forearm.alpha=.8;sprite->setAnimationBoneTransform("forearm",forearm);
    layer->moveTo(pdg::Point(20,10));layer->rotateTo(.2);layer->setZoom(1.5);
    const auto transform=sprite->getAnimationBoneTransform("forearm",pdg::animationSpace_World);
    const auto origin=layer->layerToPort(pdg::Point(transform.x,transform.y));pdg::AnimationTransform offset;offset.x=2;const auto endpoint=pdg::AnimationTransform::compose(transform,offset);
    const auto end=layer->layerToPort(pdg::Point(endpoint.x,endpoint.y));port.lines.clear();sprite->draw();
    near(port.lines[0].from.x,origin.x,"custom line root/layer x once");near(port.lines[0].from.y,origin.y,"custom line root/layer y once");near(port.lines[0].to.x,end.x,"custom line reflection once");near(port.lines[0].to.y,end.y,"custom line rotation once");near(port.lines[0].alpha,.16,"custom alpha includes bone and Sprite alpha once");near(port.lines[0].width,2,"port-pixel stroke unaffected by bone and layer scale");
    auto bounds=sprite->getAnimationDrawBounds();expect(!bounds.uncullable&&bounds.left<bounds.right,"known image/custom bounds are cullable");
    sprite->setLocation(pdg::Point(10000,10000));const auto count=order.size();port.operations.clear();sprite->draw();expect(order.size()==count&&port.operations.empty(),"offscreen bounded drawing callbacks and art are culled");
    options.placement=pdg::animationDraw_AfterAll;options.slot="";options.bounds.uncullable=true;auto unbounded=sprite->addAnimationDrawable(options,[&](auto context){order.push_back(6);return lineDrawing();});sprite->draw();expect(order.size()>count,"explicit uncullable registration preserves drawing");sprite->removeAnimationDrawable(unbounded);
    sprite->setLocation(pdg::Point(0,0));sprite->clearAnimationDrawables();options.bounds.uncullable=true;
    std::weak_ptr<int> lifetime;auto token=std::make_shared<int>(1);lifetime=token;
    pdg::AnimationDrawableId added=0;auto id=sprite->addAnimationDrawable(options,[&,token](auto context)->std::shared_ptr<pdg::Drawing>{auto candidate=lineDrawing();if(!added)added=sprite->addAnimationDrawable(options,[&](auto){order.push_back(9);return std::shared_ptr<pdg::Drawing>();});throw std::runtime_error("bad drawable");});token.reset();
    port.lines.clear();sprite->draw();expect(lifetime.expired(),"failed drawing callback releases its retained state");expect(port.lines.empty(),"failed callback rolls back buffered draw commands");expect(sprite->getAnimationDrawableError(id)=="bad drawable","drawing callback failure is diagnosable");expect(order.back()!=9,"registration during drawing waits until next frame");sprite->draw();expect(order.back()==9,"deferred drawing registration runs next frame");
    sprite->clearAnimationDrawables();options.bounds.uncullable=true;auto remove=sprite->addAnimationDrawable(options,[&](auto){sprite->clearAnimationDrawables();return std::shared_ptr<pdg::Drawing>();});sprite->draw();bool missing=false;try{sprite->getAnimationDrawableError(remove);}catch(const std::out_of_range&){missing=true;}expect(missing,"in-callback clear releases at frame end");
    auto* image=dynamic_cast<pdg::PDGImageFile*>(sprite->mEntityInstance->getObjectInstance("hand_art")->getImage())->getPDGImage();image->setOpacity(190);options.placement=pdg::animationDraw_BeforeAll;
    auto imageId=sprite->addAnimationDrawable(options,[&](auto context){
        std::shared_ptr<pdg::Drawing> drawing(pdg::Drawing::create());
        pdg::Attributes attrs;attrs.fillOpacity(.5);
        delete drawing->addImage(pdg::Rect(0,0,2,1),*image,attrs);return drawing;});
    port.fail=true;try{sprite->draw();}catch(const std::runtime_error&){}port.fail=false;
    expect(image->getOpacity()==190,"custom image restores shared opacity after port failure");expect(!sprite->getAnimationDrawableError(imageId).empty(),"port drawing failure disables responsible callback");
    sprite->clearAnimationDrawables();options.placement=pdg::animationDraw_AfterAll;auto held=std::make_shared<int>(2);lifetime=held;sprite->addAnimationDrawable(options,[held](auto){return std::shared_ptr<pdg::Drawing>();});held.reset();
    auto persistent=lineDrawing();auto element=std::unique_ptr<pdg::ElementRef>(persistent->getElement(0));
    auto persistentId=sprite->addAnimationDrawable(options,*persistent);persistent.reset();
    element->changeControlPoint(1,pdg::Point(5,0));port.lines.clear();sprite->draw();
    expect(!port.lines.empty() && sprite->getAnimationDrawableError(persistentId).empty(),"persistent Drawing survives owner release and element edit");
    sprite->disableAnimationPose();expect(lifetime.expired(),"rig disable releases drawing callbacks");
    pdg::cleanupLayer(layer);
}

void armDrawing(const std::string& path) {
    // The recording port captures images/debug lines without an OpenGL context.
    // Pose sprites must isolate their debug controls from global Spriter flags.
    const bool points = SpriterEngine::Settings::renderDebugPoints;
    const bool bones = SpriterEngine::Settings::renderDebugBones;
    const bool boxes = SpriterEngine::Settings::renderDebugBoxes;
    RecordingPort port;
    auto* layer = pdg::createSpriteLayer(nullptr);
    layer->setSpritePort(&port);
    auto* sprite = layer->createSpriteFromSpriterFile(path.c_str());
    sprite->pauseAnimation();
    expect(sprite->enableAnimationPose("reference"), "render fixture pose enabled");
    auto* movedLayer = pdg::createSpriteLayer(&port);
    movedLayer->addSprite(sprite); pdg::cleanupLayer(layer); layer = movedLayer;
    SpriterEngine::Settings::renderDebugPoints = true;
    SpriterEngine::Settings::renderDebugBones = true;
    SpriterEngine::Settings::renderDebugBoxes = true;
    sprite->draw();
    expect(port.lines.empty() && port.debugQuads.empty(), "pose sprites suppress global debug drawing by default");
    expect(port.quads.size() == 3, "three authored rigid parts submit image quads");
    const auto reference = port.quads; port.quads.clear();
    auto shoulder = sprite->getAnimationBoneTransform("shoulder"); shoulder.rotation = 3.14159265358979323846 / 2;
    sprite->setAnimationBoneTransform("shoulder", shoulder); sprite->draw();
    expect(port.quads.size() == 3, "edited arm renders all rigid parts");
    for (size_t part = 0; part < 3; ++part) for (int corner = 0; corner < 4; ++corner) {
        const auto before = reference[part].points[corner], after = port.quads[part].points[corner];
        near(after.x, 2 - (before.y - 3), "rendered corner rotates about shoulder x");
        near(after.y, 3 + (before.x - 2), "rendered corner rotates about shoulder y");
    }
    sprite->setAnimationDebugDraw(pdg::animationDebug_Bones | pdg::animationDebug_Sockets | pdg::animationDebug_Boxes);
    expect(sprite->getAnimationDebugDraw() == pdg::animationDebug_All, "debug flags combine as integers");
    sprite->setLocation({100, 50}); sprite->setScale(-2, 3); sprite->setOpacity(0.25);
    layer->setLocation({10, 20}); layer->setZoom(2); layer->rotateTo(3.14159265358979323846 / 2);
    sprite->draw();
    expect(port.lines.size() == 11 && port.debugQuads.size() == 1, "final pose produces bone links, origins, oriented socket and box");
    const auto shoulderPort = layer->layerToPort(pdg::Point(96, 59));
    near(port.lines[0].from.x, shoulderPort.x - 3, "reflected shoulder marker applies root/layer once x");
    near(port.lines[0].from.y, shoulderPort.y, "reflected shoulder marker applies root/layer once y");
    const auto gripPort = layer->layerToPort(pdg::Point(96, 95));
    near(port.lines[10].from.x, gripPort.x, "socket direction starts at final socket x");
    near(port.lines[10].from.y, gripPort.y, "socket direction starts at final socket y");
    for (const auto& line : port.lines) { near(line.alpha, 0.25, "debug alpha inherits once"); near(line.width, 1, "debug stroke stays one port pixel"); }
    near(port.debugAlpha[0], 0.25, "box debug inherits alpha once");
    const auto collisionQuad = layer->layerToPort(sprite->getSpriterCollisionBox("hitbox").getQuad());
    for (int corner = 0; corner < 4; ++corner) {
        near(port.debugQuads[0].points[corner].x, collisionQuad.points[corner].x, "debug box matches collision geometry x");
        near(port.debugQuads[0].points[corner].y, collisionQuad.points[corner].y, "debug box matches collision geometry y");
    }
    expect(SpriterEngine::Settings::renderDebugBones && SpriterEngine::Settings::renderDebugPoints &&
        SpriterEngine::Settings::renderDebugBoxes, "global debug state restored after instance rendering");
    auto* other = layer->createSpriteFromSpriterFile(path.c_str()); other->pauseAnimation();
    expect(other->enableAnimationPose("reference"), "independent debug instance enables pose");
    other->draw();
    expect(other->getAnimationDebugDraw() == 0 && port.lines.size() == 11, "debug controls are isolated between shared-model instances");
    bool rejected = false;
    try { sprite->setAnimationDebugDraw(8); } catch (const std::invalid_argument&) { rejected = true; }
    expect(rejected && sprite->getAnimationDebugDraw() == 7, "unknown debug bits rejected atomically");
    struct Helper : pdg::ISpriteDrawHelper {
        int count = 0; bool allow = true;
        bool draw(pdg::Sprite*, pdg::Port*) override { ++count; return allow; }
        bool ownedBySprite() override { return false; }
    } pre, post;
    pre.allow = false; sprite->setDrawHelper(&pre); sprite->setPostDrawHelper(&post);
    const auto imageCalls = port.calls;
    sprite->draw();
    expect(pre.count == 1 && post.count == 1 && imageCalls == port.calls && port.lines.size() == 11,
        "pre-helper suppresses art/debug while post-helper still runs");
    sprite->setDrawHelper(nullptr); sprite->setPostDrawHelper(nullptr);
    port.failLine = true; bool caught = false;
    try { sprite->draw(); } catch (const std::runtime_error&) { caught = true; }
    expect(caught && SpriterEngine::Settings::renderDebugPoints && SpriterEngine::Settings::renderDebugBones &&
        SpriterEngine::Settings::renderDebugBoxes, "render exception restores global debug state");
    port.failLine = false;
    sprite->disableAnimationPose();
    expect(sprite->getAnimationDebugDraw() == 0, "pose disable clears debug registrations");
    pdg::cleanupLayer(layer);
    SpriterEngine::Settings::renderDebugPoints = points;
    SpriterEngine::Settings::renderDebugBones = bones;
    SpriterEngine::Settings::renderDebugBoxes = boxes;
}
#ifdef PDG_USE_CHIPMUNK_PHYSICS
void physicalArmDebugDrawing(const std::string& path) {
    for (bool generated : {false, true}) {
        RecordingPort port;
        auto* layer = pdg::createSpriteLayer(&port);
        layer->setUseChipmunkPhysics(true);
        auto* sprite = layer->createSpriteFromSpriterFile(path.c_str());
        sprite->pauseAnimation();
        expect(sprite->enableAnimationPose("reference"), "physical debug fixture enables pose");
        if (generated) {
            sprite->setupPhysicsFromAnimationRig(30);
        } else {
            pdg::AnimationPhysicsDefinition definition;
            for (unsigned i = 0; i < 3; ++i) {
                pdg::AnimationPhysicsBody body;
                body.bone = i; body.length = i == 0 ? 10 : i == 1 ? 5 : 2;
                body.offsetX = body.length / 2; body.radius = .25;
                definition.bodies.push_back(body);
            }
            for (unsigned i = 0; i < 2; ++i) {
                pdg::AnimationPhysicsJoint joint;
                joint.parent = i; joint.child = i + 1;
                joint.parentX = definition.bodies[i].length / 2;
                joint.childX = -definition.bodies[i + 1].length / 2;
                definition.joints.push_back(joint);
            }
            sprite->setupAnimationPhysics(definition);
        }
        sprite->setAnimationDebugDraw(pdg::animationDebug_Bones);
        auto* upper = sprite->findPart("shoulder");
        auto* forearm = sprite->findPart("forearm");
        auto* hand = sprite->findPart("hand");
        const auto checkLinks = [&](bool elbow, bool wrist) {
            port.lines.clear(); sprite->draw();
            const auto hasLine = [&](pdg::Point from, pdg::Point to) {
                return std::any_of(port.lines.begin(), port.lines.end(), [&](const auto& line) {
                    return std::hypot(line.from.x - from.x, line.from.y - from.y) < .001 &&
                        std::hypot(line.to.x - to.x, line.to.y - to.y) < .001;
                });
            };
            const auto origin = [&](const char* name) {
                const auto bone = sprite->getAnimationBoneTransform(name, pdg::animationSpace_World);
                return layer->layerToPort(pdg::Point(bone.x, bone.y));
            };
            expect(hasLine(origin("shoulder"), origin("forearm")) == elbow,
                "debug elbow link follows the live physical connection");
            expect(hasLine(origin("forearm"), origin("hand")) == wrist,
                "debug wrist link follows the live physical connection");
            for (const char* name : {"shoulder", "forearm", "hand"}) {
                const auto p = origin(name);
                expect(hasLine(pdg::Point(p.x - 3, p.y), pdg::Point(p.x + 3, p.y)) &&
                    hasLine(pdg::Point(p.x, p.y - 3), pdg::Point(p.x, p.y + 3)),
                    "debug bone origin remains visible, including detached bodies");
            }
        };
        checkLinks(true, true);
        sprite->detachAnimationPhysicsPart(forearm);
        for (auto* part : {forearm, hand}) {
            const auto state = part->physics.getState();
            part->physics.teleport(pdg::Point(state.x, state.y + 50), state.rotation);
        }
        checkLinks(false, true); // Internal wrist joint survives subtree detachment.
        sprite->attachAnimationPhysicsPart(forearm).attachAnimationPhysicsPart(hand);
        checkLinks(false, true); // Mass membership alone does not recreate the elbow.
        forearm->physics.createRotaryLimit(upper->physics, -1, 1);
        checkLinks(false, true); // An angular limit does not join separated origins.
        auto& pivot = forearm->physics.createPivotJoint(upper->physics);
        checkLinks(true, true); // Endpoint order need not match the skeletal hierarchy.
        pivot.disconnect();
        checkLinks(false, true);
        forearm->physics.createPivotJoint(upper->physics);
        sprite->detachAnimationPhysicsPart(forearm, false);
        checkLinks(false, false); // Single-bone detachment severs both boundary joints.
        pdg::cleanupLayer(layer);
    }
}
#endif
void spriterDebugDrawing(const std::string& path) {
    // Ordinary Spriter playback uses its original debug objects, without the
    // opt-in PDG pose adapter. Those objects must share the artwork's frame.
    struct RestoreDebug {
        bool bones = SpriterEngine::Settings::renderDebugBones;
        bool points = SpriterEngine::Settings::renderDebugPoints;
        bool boxes = SpriterEngine::Settings::renderDebugBoxes;
        bool enabled = SpriterEngine::Settings::enableDebugBones;
        ~RestoreDebug() {
            SpriterEngine::Settings::renderDebugBones = bones;
            SpriterEngine::Settings::renderDebugPoints = points;
            SpriterEngine::Settings::renderDebugBoxes = boxes;
            SpriterEngine::Settings::enableDebugBones = enabled;
        }
    } restore;
    SpriterEngine::Settings::enableDebugBones = true;
    RecordingPort port, nextPort;
    auto* layer = pdg::createSpriteLayer(&port);
    layer->setUseChipmunkPhysics(false);
    layer->setLocation({10, 20}); layer->setOrigin({9, -11});
    layer->setCenterOffset({3, -7});
    layer->setZoom(.25); layer->rotateTo(.7);
    auto* sprite = layer->createSpriteFromSpriterFile(path.c_str());
    expect(sprite != nullptr, "ordinary debug fixture loads");
    sprite->pauseAnimation(); sprite->setLocation({100, 50});
    sprite->setScale(-2, 3); sprite->rotateTo(.3);
    SpriterEngine::Settings::renderDebugBones = true;
    SpriterEngine::Settings::renderDebugPoints = false;
    SpriterEngine::Settings::renderDebugBoxes = false;
    sprite->draw();
    expect(port.debugQuads.size() == 3 && port.quads.size() == 3,
        "ordinary playback renders three bones and three images");
    auto* shoulder = sprite->mEntityInstance->getObjectInstance("shoulder");
    const auto position = shoulder->getPosition();
    const auto origin = layer->layerToPort(pdg::Point(position.x, position.y));
    const auto& bone = port.debugQuads[0];
    near(bone.points[0].x, origin.x, "debug bone base shares artwork pivot x");
    near(bone.points[0].y, origin.y, "debug bone base shares artwork pivot y");
    const auto& image = port.quads[0];
    near((image.points[pdg::lftTop].x + image.points[pdg::lftBot].x) / 2,
        origin.x, "reflected image left edge contains bone origin x");
    near((image.points[pdg::lftTop].y + image.points[pdg::lftBot].y) / 2,
        origin.y, "reflected image left edge contains bone origin y");
    const double length = 10 * shoulder->getScale().x; // authored shoulder width
    const double angle = shoulder->getAngle();
    const auto tip = layer->layerToPort(pdg::Point(position.x + length * std::cos(angle),
                                                 position.y + length * std::sin(angle)));
    near(bone.points[2].x, tip.x, "bone length inherits entity reflection and layer zoom x");
    near(bone.points[2].y, tip.y, "bone length inherits entity reflection and layer zoom y");

    SpriterEngine::Settings::renderDebugBones = false;
    SpriterEngine::Settings::renderDebugPoints = true;
    sprite->draw();
    expect(port.ellipses.size() == 1 && port.lines.size() == 1, "socket draws marker and direction");
    const auto socket = sprite->getAttachPoint("grip") + sprite->getLocation();
    const auto socketPort = layer->layerToPort(pdg::Point(socket.x, socket.y));
    near(port.ellipses[0].center.x, socketPort.x, "socket debug matches queried position x");
    near(port.ellipses[0].center.y, socketPort.y, "socket debug matches queried position y");
    near(port.lines[0].from.x, socketPort.x, "socket direction starts at marker x");
    near(port.lines[0].from.y, socketPort.y, "socket direction starts at marker y");

    SpriterEngine::Settings::renderDebugPoints = false;
    SpriterEngine::Settings::renderDebugBoxes = true;
    port.debugQuads.clear(); sprite->draw();
    auto checkBox = [&](RecordingPort& destination, pdg::SpriteLayer* owner) {
        expect(destination.debugQuads.size() == 1, "one authored debug box");
        const auto expected = owner->layerToPort(sprite->getSpriterCollisionBox("hitbox").getQuad());
        for (int corner = 0; corner < 4; ++corner) {
            near(destination.debugQuads[0].points[corner].x, expected.points[corner].x,
                "ordinary debug box matches reflected collision geometry x");
            near(destination.debugQuads[0].points[corner].y, expected.points[corner].y,
                "ordinary debug box matches reflected collision geometry y");
        }
    };
    checkBox(port, layer);
    const auto oldDebugCount = port.debugQuads.size();
    const auto oldImageCount = port.calls;
    layer->setSpritePort(&nextPort); layer->setZoom(2); layer->rotateTo(-.4);
    sprite->draw();
    checkBox(nextPort, layer);
    expect(port.debugQuads.size() == oldDebugCount && port.calls == oldImageCount,
        "artwork and debug geometry follow a replaced layer port");

    auto* movedLayer = pdg::createSpriteLayer(&port);
    movedLayer->setUseChipmunkPhysics(false);
    movedLayer->setLocation({-5, 12}); movedLayer->setZoom(.5);
    sprite->addRef(); layer->removeSprite(sprite); movedLayer->addSprite(sprite); sprite->release();
    port.debugQuads.clear(); nextPort.debugQuads.clear();
    sprite->draw();
    checkBox(port, movedLayer);
    expect(nextPort.debugQuads.empty(), "moved sprite debug uses drawing layer, not model owner");
    pdg::cleanupLayer(movedLayer);
    pdg::cleanupLayer(layer);
}

void retainedImagePortLifetime() {
    auto* manager=pdg::GraphicsManager::getSingletonInstance();
    auto* previous=manager->getMainPort();
    auto* port=new pdg::PortImpl(manager);
    auto* image=new pdg::ImageOpenGL(port);image->addRef();image->initEmpty(4,4);
    image->getCachedTexture();
    expect(image->mCacheKey!=0,"image acquires a real port cache entry");
    auto* frame=image->getFrame(0);frame->addRef();
    manager->setMainPort(previous);delete port;
    expect(image->mPort==nullptr && image->mCacheKey==0,"closing port detaches retained image and cache key");
    expect(frame->mPort==nullptr,"closing port also detaches retained subimages");
    auto* replacement=new pdg::PortImpl(manager);
    expect(image->setPort(replacement)==nullptr,"retained image can select a new port safely");
    image->getCachedTexture();expect(image->mCacheKey!=0,"retained image acquires replacement cache entry");
    frame->release();image->release();
    manager->setMainPort(previous);delete replacement;
    // The base Port path must also detach images in custom/test renderers.
    auto* custom=new RecordingPort;
    auto* held=new pdg::ImageOpenGL(custom);held->addRef();delete custom;
    expect(held->mPort==nullptr,"custom Port destruction detaches retained image");held->release();
}

void imageDrawing() {
    RecordingPort port, nextPort;
    auto* layer = pdg::createSpriteLayer(nullptr);
    layer->setSpritePort(&port);
    layer->setLocation(pdg::Point(10, 20));
    layer->setZoom(2);
    layer->rotateTo(3.14159265358979323846 / 2);
    {
        auto* image = new pdg::ImageOpenGL();
        image->initEmpty(20, 10);
        image->setOpacity(200);
        pdg::PDGImageFile file("test-image", {0.25, 0.5}, image);
        pdg::PDGImageFile::LayerScope drawingLayer(layer);
        SpriterEngine::SpriteObjectInfo object;
        object.setPosition({100, 50}); object.setAngle(3.14159265358979323846 / 2);
        object.setScale({-2, 3}); object.setPivot({0.25, 0.5}); object.setAlpha(0.5);
        file.renderSprite(&object);
        expect(port.calls == 1 && port.lastOpacity == 100, "image inherits alpha");
        expect(image->getOpacity() == 200, "shared image opacity restored");
        near(port.lastQuad.points[pdg::lftTop].x, -100, "draw quad applies root pivot and layer x");
        near(port.lastQuad.points[pdg::lftTop].y, 270, "draw quad applies root pivot and layer y");
        near(port.lastQuad.points[pdg::rgtTop].x, -20, "signed texture corner order preserved");
        const auto roundTrip = layer->layerToPort(layer->portToLayer(port.lastQuad));
        for (int i = 0; i < 4; ++i) {
            near(roundTrip.points[i].x, port.lastQuad.points[i].x, "quad conversion round trip x");
            near(roundTrip.points[i].y, port.lastQuad.points[i].y, "quad conversion round trip y");
        }
        pdg::RotatedRect original(pdg::Rect(3, 5, 21, 17), 0.3, pdg::Offset(2, -1));
        const auto rectRoundTrip = layer->portToLayer(layer->layerToPort(original));
        near(rectRoundTrip.left, original.left, "rectangle conversion round trip left");
        near(rectRoundTrip.top, original.top, "rectangle conversion round trip top");
        near(rectRoundTrip.right, original.right, "rectangle conversion round trip right");
        near(rectRoundTrip.bottom, original.bottom, "rectangle conversion round trip bottom");
        near(rectRoundTrip.radians, original.radians, "rectangle conversion round trip rotation");
        near(rectRoundTrip.centerOffset.x, original.centerOffset.x, "rectangle conversion round trip pivot x");
        near(rectRoundTrip.centerOffset.y, original.centerOffset.y, "rectangle conversion round trip pivot y");
        layer->setSpritePort(&nextPort);
        object.setAlpha(1);
        file.renderSprite(&object);
        expect(nextPort.calls == 1 && nextPort.lastOpacity == 200, "image uses current layer port without state leakage");
        nextPort.fail = true;
        object.setAlpha(0.25);
        bool caught = false;
        try { file.renderSprite(&object); } catch (const std::runtime_error&) { caught = true; }
        expect(caught && image->getOpacity() == 200, "draw exception restores shared image opacity");
    }
    pdg::cleanupLayer(layer);
}
struct CountingDrawHelper : pdg::ISpriteDrawHelper {
    int count = 0;
    bool allow = true;
    bool draw(pdg::Sprite*, pdg::Port*) override { ++count; return allow; }
    bool ownedBySprite() override { return false; }
};
void drawLayerCleanup(const std::string& path) {
    RecordingPort port;
    auto* layer = pdg::createSpriteLayer(&port);
    layer->setUseChipmunkPhysics(false);
    auto* sprite = layer->createSpriteFromSpriterFile(path.c_str());
    sprite->pauseAnimation();
    expect(sprite->enableAnimationPose("reference"), "cleanup draw fixture uses per-instance debug controls");
    struct CleanupHelper : pdg::ISpriteDrawHelper {
        bool called = false, retainedDuringDraw = false;
        bool draw(pdg::Sprite* sprite, pdg::Port*) override {
            called = true;
            auto* layer = sprite->getLayer();
            pdg::cleanupLayer(layer);
            retainedDuringDraw = sprite->getLayer() == layer;
            return true;
        }
        bool ownedBySprite() override { return false; }
    } helper;
    sprite->setPostDrawHelper(&helper);
    auto* manager = pdg::SpriteManager::getSingletonInstance();
    pdg::PortDrawInfo event{}; event.port = &port;
    manager->handleEvent(nullptr, pdg::eventType_PortDraw, &event);
    expect(helper.called && helper.retainedDuringDraw, "draw cleanup waits for traversal to finish");
    expect(manager->mFirstLayer == nullptr && manager->mLayerUpdateDepth == 0,
        "draw traversal releases queued layers and clears its guard");
    auto* next = pdg::createSpriteLayer(&port);
    pdg::cleanupLayer(next);
    expect(manager->mFirstLayer == nullptr, "cleanup after drawing happens immediately");
}
void drawHelpers(SpriterEngine::SpriterModel& model) {
    CountingDrawHelper pre, post;
    pdg::Sprite sprite(model.getNewEntityInstance(0), &model);
    sprite.setDrawHelper(&pre);
    sprite.setPostDrawHelper(&post);
    sprite.setOpacity(0.25);
    sprite.draw();
    near(sprite.mEntityInstance->getAlpha(), 0.25, "sprite opacity reaches evaluator without a tick");
    expect(pre.count == 1 && post.count == 1, "Spriter calls both draw helpers");
    pre.allow = false;
    sprite.draw();
    expect(pre.count == 2 && post.count == 2, "suppressed Spriter drawing still calls post helper");
}
#endif

}

namespace pdg {
bool Initializer::allowHorizontalOrientation() throw() { return true; }
bool Initializer::allowVerticalOrientation() throw() { return true; }
const char* Initializer::getAppName(bool) throw() { return "PDG Spriter Regression Tests"; }
const char* Initializer::getMainResourceFileName() throw() { return nullptr; }
bool Initializer::installGlobalHandlers() throw() { return false; }
bool Initializer::getGraphicsEnvironmentDimensions(Rect, Rect, long& width, long& height, uint8& depth) throw() {
    width = height = 1; depth = 32; return false;
}
}
void greyGuyRockIK(const std::string& path) {
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* layer = pdg::createSpriteLayer();
#else
    auto* layer = pdg::createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    layer->setUseChipmunkPhysics(false);
#endif
    auto* sprite = layer->createSpriteFromSpriterFile(path.c_str());
    expect(sprite && sprite->enableAnimationPose("idle"), "Grey Guy idle supports editable pose");
    sprite->setLocation(pdg::Point(2080, 2240)); sprite->setScale(4, 4);
    sprite->seekAnimation("idle", 0);
    const auto rig = sprite->getAnimationPose().getRig();
    const auto foot = sprite->getAnimationBoneTransform("front_foot", animationSpace_World);
    const auto art = sprite->getAnimationBindingTransform("p_foot_idle_0", animationSpace_World);
    AnimationTwoBoneIK config;
    config.root = rig->findBone("front_thigh"); config.middle = rig->findBone("front_shin");
    config.tip = rig->findBone("front_foot");
    config.targetX = foot.x; config.targetY = foot.y - 128;
    config.space = animationSpace_World; config.matchOrientation = true;
    config.targetRotation = foot.rotation;
    const auto id = sprite->addAnimationIK(config);
    double firstKneeX = 0, maxKneeMotion = 0, minOffset = 1e10, maxOffset = 0;
    for (int sample = 0; sample <= 16; ++sample) {
        const double seconds = sample * .25;
        sprite->seekAnimation("idle", seconds);
        const auto base = sprite->sampleAnimationPose("idle", seconds);
        const auto pose = sprite->getAnimationPose();
        const auto result = sprite->getAnimationIKResult(id);
        expect(result.reachable && !result.clamped && !result.stretched,
               "Grey Guy ankle reaches rock without stretching through idle cycle");
        const auto ankle = sprite->getAnimationBoneTransform("front_foot", animationSpace_World);
        near(ankle.x, config.targetX, "Grey Guy planted ankle x");
        near(ankle.y, config.targetY, "Grey Guy planted ankle y");
        near(std::remainder(ankle.rotation - foot.rotation, 2 * 3.14159265358979323846), 0,
             "Grey Guy planted foot orientation");
        const auto drawnFoot = sprite->getAnimationBindingTransform("p_foot_idle_0", animationSpace_World);
        near(drawnFoot.x, art.x, "foot artwork follows constrained ankle x");
        near(drawnFoot.y, art.y - 128, "foot artwork lifted onto rock");
        const auto knee = sprite->getAnimationBoneTransform("front_shin", animationSpace_World);
        if (!sample) firstKneeX = knee.x;
        maxKneeMotion = std::max(maxKneeMotion, std::abs(knee.x - firstKneeX));
        const auto authored = base.getLocalTransform(config.middle);
        minOffset = std::min(minOffset, authored.x); maxOffset = std::max(maxOffset, authored.x);
        near(pose.getLocalTransform(config.middle).x, authored.x, "animated shin offset preserved");
        for (AnimationBoneId bone = 0; bone < rig->getBoneCount(); ++bone) {
            if (bone == config.root || bone == config.middle || bone == config.tip) continue;
            const auto original = base.getLocalTransform(bone), actual = pose.getLocalTransform(bone);
            near(actual.x, original.x, "unconstrained idle bone x unchanged");
            near(actual.y, original.y, "unconstrained idle bone y unchanged");
            near(actual.rotation, original.rotation, "unconstrained idle bone rotation unchanged");
        }
    }
    expect(maxKneeMotion > 1 && maxOffset - minOffset > 1, "idle animation continues underneath planted-foot IK");
    expect(sprite->getAnimationModifierError(id).empty(), "Grey Guy IK remains enabled");
    sprite->removeAnimationModifier(id);
    near(sprite->getAnimationBoneTransform("front_foot", animationSpace_World).y, foot.y,
         "disabling IK restores the current authored idle pose");
    cleanupLayer(layer);
}


int main(int argc, char** argv) {
    expect(argc == 2, "fixture path supplied");
    expect(pdg::main_initManagers() == 0, "managers initialize");
    #ifdef PDG_NO_GUI
    auto* layer = pdg::createSpriteLayer();
    #else
    auto* layer = pdg::createSpriteLayer(nullptr);
    #endif
    {
        SpriterEngine::SpriterModel model(argv[1], new pdg::PDGFileFactory(), new pdg::PDGObjectFactory());
        playback(model);
        selection(model);
        coordinates(model);
        boxOverlaps(model);
        attachments(model);
        #ifndef PDG_NO_GUI
        drawHelpers(model);
        imageDrawing();
        retainedImagePortLifetime();
        #endif
    }
    {
        const std::string path(argv[1]);
        const auto armPath=path.substr(0,path.find_last_of('/')+1)+"arm.scml";
        SpriterEngine::SpriterModel arm(armPath, new pdg::PDGFileFactory(), new pdg::PDGObjectFactory());
        independentParts(arm);
    }
    pdg::cleanupLayer(layer);
    compareTransformsWithSpriter();
    fallbackCollisionUnits();
    const std::string fixture(argv[1]);
    repeatedWonkyPlayback(fixture.substr(0, fixture.find_last_of('/') + 1) + "../spriter-samples/wonkyskeleton/wonkyskeleton.scml");
    greyGuyRockIK(fixture.substr(0, fixture.find_last_of('/') + 1) + "../spriter-samples/greyguy/player.scml");
#ifndef PDG_NO_EVENT_QUEUE
    authoredTriggers(fixture.substr(0,fixture.find_last_of('/')+1)+"arm.scml");
#endif
    transitionSprite(fixture.substr(0, fixture.find_last_of('/') + 1) + "arm.scml");
    modifierSprite(fixture.substr(0, fixture.find_last_of('/') + 1) + "arm.scml");
    transferredModel(fixture.substr(0, fixture.find_last_of('/') + 1) + "arm.scml");
    editableArm(fixture.substr(0, fixture.find_last_of('/') + 1) + "arm.scml");
#ifndef PDG_NO_GUI
    drawLayerCleanup(fixture.substr(0,fixture.find_last_of('/')+1)+"arm.scml");
    customDrawing(fixture.substr(0,fixture.find_last_of('/')+1)+"arm.scml");
    armDrawing(fixture.substr(0, fixture.find_last_of('/') + 1) + "arm.scml");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    physicalArmDebugDrawing(fixture.substr(0, fixture.find_last_of('/') + 1) + "arm.scml");
#endif
    spriterDebugDrawing(fixture.substr(0, fixture.find_last_of('/') + 1) + "arm.scml");
#endif
    #ifdef PDG_USE_CHIPMUNK_PHYSICS
#ifndef PDG_NO_EVENT_QUEUE
    physicalContacts(fixture.substr(0,fixture.find_last_of('/')+1)+"arm.scml");
#endif
    physicalRig(fixture.substr(0,fixture.find_last_of('/')+1)+"arm.scml");
    generatedPhysicalRig(fixture.substr(0,fixture.find_last_of('/')+1)+"arm.scml");
    animationPhysicsControl(fixture.substr(0,fixture.find_last_of('/')+1));
    animationIKDrivenControl(fixture.substr(0,fixture.find_last_of('/')+1));
    rigFrameMovement(fixture.substr(0,fixture.find_last_of('/')+1));
    rigLoadsAndReflection(fixture.substr(0,fixture.find_last_of('/')+1));
    humanRigBlocker(fixture.substr(0,fixture.find_last_of('/')+1));
    physicsRoot(argv[1]);
    #endif
    std::cout << "Spriter regression: " << assertions << " assertions passed\n";
}
