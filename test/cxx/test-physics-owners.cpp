// PhysicsBody ownership and snapshots must work independently of Spriter.
#include "pdg/sys/sprite.h"
#include "pdg/sys/particle.h"
#include "pdg/sys/particleemitter.h"
#include "pdg/sys/animationphysics.h"
#include "pdg/sys/initializer.h"
#include "pdg/sys/ieventhandler.h"
#include "pdg/sys/spritelayer.h"
#include "pdg/sys/serializer.h"
#include "pdg/sys/deserializer.h"
#include "pdg/sys/drawing.h"
#include "pdg/sys/image.h"
#ifndef PDG_NO_GUI
#include "image-opengl.h"
#include "drawing-snapshot.h"
#endif
#include "spritemanager.h"
#include "pdg-main.h"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <new>
#include "image-impl.h"

#ifdef _WIN32
#undef far
#undef near
#undef small
#endif

namespace {
static_assert(std::is_same_v<decltype(std::declval<pdg::Sprite&>().setLocation(1, 2).moveBy(1, 2, .5).andThen()), pdg::Sprite&>);
static_assert(std::is_same_v<decltype(std::declval<pdg::Part&>().setLocation(1, 2).rotateTo(1, .5).andThen()), pdg::Part&>);
static_assert(std::is_same_v<decltype(std::declval<pdg::SpriteLayer&>().setScale(2).grow(2, .5)), pdg::SpriteLayer&>);
int assertions = 0;
void expect(bool ok, const char* message) {
    ++assertions;
    if (!ok) throw std::runtime_error(message);
}
void near(double actual, double expected, const char* message) {
    if (!std::isfinite(actual) || std::abs(actual-expected) > .0001) {
        std::cerr << message << ": " << actual << " expected " << expected << '\n';
        expect(false, message);
    }
    ++assertions;
}
void step(pdg::Sprite& sprite, unsigned milliseconds) {
    sprite.doAnimate(milliseconds, false);
}

#include "particle-tests.inc"
#include "generated-rig-tests.inc"

uint32 snapshotBits(float value) { uint32 bits;std::memcpy(&bits,&value,sizeof(bits));return bits; }
uint64 snapshotBits(double value) { uint64 bits;std::memcpy(&bits,&value,sizeof(bits));return bits; }
std::unique_ptr<pdg::Deserializer> snapshotReader(pdg::Serializer& writer) {
    if (writer.getDataSize() > std::numeric_limits<uint32>::max()) throw std::length_error("snapshot exceeds Deserializer limit");
    auto* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
    return std::make_unique<pdg::Deserializer>(bytes,static_cast<uint32>(writer.getDataSize()));
}
struct SnapshotTestWriter : pdg::Serializer {
    std::function<void(uint8&)> onByte;
    std::function<void(uint32&)> onInteger,onWord;
    std::function<void(uint64&)> onDouble;
    std::function<void(const char*&)> onString;
    std::function<void()> afterString;
    uint32 lastInteger=0,previousInteger=0;
    int mutations=0;
    bool nextInteger=false,insideString=false;
    void replaceByte(uint32 offset,uint8 value) { const_cast<uint8*>(getDataPtr())[offset]=value; }
    void serialize_uint(uint32 n) override {
        if(!insideString){if(onInteger)onInteger(n);previousInteger=lastInteger;lastInteger=getDataSize();}
        Serializer::serialize_uint(n);
    }
    void serialize_1u(uint8 n) override {if(onByte)onByte(n);Serializer::serialize_1u(n);}
    void serialize_4u(uint32 n) override {if(onWord)onWord(n);Serializer::serialize_4u(n);}
    void serialize_8u(uint64 n) override {if(onDouble)onDouble(n);Serializer::serialize_8u(n);}
    void serialize_str(const char* name) override {
        if(onString)onString(name);insideString=true;Serializer::serialize_str(name);insideString=false;
        if(afterString)afterString();
    }
};

#include "angular-speed-break-tests.inc"
#include "capsule-tests.inc"
#include "physics-graph-snapshot-tests.inc"
#include "constraint-anchor-tests.inc"
#include "authored-snapshot-tests.inc"
#include "rig-snapshot-tests.inc"
#include "part-transfer-tests.inc"
#include "part-artwork-collider-tests.inc"

void colliderSourcesAndPolygons() {
    using namespace pdg;
    Sprite sprite;
    auto& c=sprite.setupCollider();
    const std::vector<pdg::Point> outline{{0,0},{6,0},{6,6},{4,6},{4,2},{2,2},{2,6},{0,6}};
    auto id=c.addPolygon(pdg::Polygon(outline));
    expect(c.getShapeCount()==1 && c.getShapeId(0)==id,"concave polygon has one logical shape ID");
    expect(c.contains(pdg::Point(1,4))&&!c.contains(pdg::Point(3,4)),"concave polygon preserves its open gap");
    auto reversed=outline;std::reverse(reversed.begin(),reversed.end());c.setPolygon(reversed);
    expect(c.contains(pdg::Point(5,4))&&!c.contains(pdg::Point(3,4)),"both polygon windings preserve concavity");
    bool rejected=false;try{c.setPolygon({{0,0},{3,3},{0,3},{3,0}});}catch(const std::exception&){rejected=true;}
    expect(rejected&&c.contains(pdg::Point(5,4)),"invalid replacement leaves previous polygon intact");
    sprite.setSize(4,6);sprite.setupFrameCollider(frameCollider_Bounds);
    auto source=c.getShapeId(0);auto extra=c.addPolygon(outline);
    expect(c.getGeometrySource()==colliderSource_Frame && c.getShapeCount()==2,"addPolygon preserves frame source");
    sprite.setSize(8,10);
    expect(c.contains(pdg::Point(-3,0))&&c.getShapeCount()==2&&c.getShapeId(0)==source,"source resize preserves source and additive IDs");
    expect(c.isSourceShape(source)&&!c.isSourceShape(extra),"shape ownership is queryable");
    rejected=false;try{c.removeShape(source);}catch(const std::logic_error&){rejected=true;}
    expect(rejected&&c.removeShape(extra),"only explicit additions can be individually removed");
    c.setSensor(true).setGroup(44);sprite.setupFrameCollider(frameCollider_Bounds);
    expect(&c==&static_cast<Collider&>(sprite.collider)&&c.isSensor()&&c.getGroup()==44,"source adapters preserve association and filter configuration");
    c.setPolygon(outline);sprite.setSize(100,100);
    expect(c.getGeometrySource()==colliderSource_Explicit&&!c.contains(pdg::Point(-20,0)),"setPolygon explicitly replaces source geometry");
#ifdef PDG_NO_GUI
    auto* image=new ImageImpl();
#else
    auto* image=new ImageOpenGL();
#endif
    image->addRef();image->initEmpty(5,5,32);std::memset(image->data,255,100);
    for(int y=1;y<4;++y)for(int x=1;x<4;++x)static_cast<uint8*>(image->data)[y*image->pitch+x*4+3]=0;
    c.setImageMask(*image,pdg::Rect(0,0,5,5));
    expect(c.getShapeCount()==1&&c.contains(pdg::Point(.5,.5))&&!c.contains(pdg::Point(2.5,2.5)),"image masks preserve transparent holes and one shape ID");
    Sprite frame;frame.addFramesImage(image);frame.setupFrameCollider();
    auto& followed=static_cast<Collider&>(frame.collider);auto addition=followed.addCircle(.25,pdg::Point(10,0));
    expect(followed.getShapeCount()==2&&!followed.contains(pdg::Point(0,0))&&followed.contains(pdg::Point(10,0)),"alpha frame source and explicit addition coexist");
    frame.setScale(-2,2).setLocation(20,10);
    expect(followed.contains(pdg::Point(0,10))&&!followed.contains(pdg::Point(20,10)),"source and additive geometry share reflected owner transforms");
    expect(followed.removeShape(addition)&&followed.getGeometrySource()==colliderSource_Frame,"removing addition leaves alpha source active");
    image->release();
    for(bool native:{false,true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if(native)continue;
#endif
        auto* layer=SpriteManager::createSpriteLayer();SpriteManager::getSingletonInstance()->addLayer(layer);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(native);
#endif
        layer->enableCollisions();auto* owner=layer->createSprite();auto& wall=owner->setupCollider().setPolygon(outline);
        auto* probe=layer->createSprite();probe->setLocation(3,4);probe->setupPhysicsBody().setMode(physicsBody_Kinematic);
        auto& sensor=probe->setupCollider().setCircle(.25).setSensor(true);
        int contacts=0;sensor.setContactHandler([&](const ColliderContact& event){if(event.phase==collision_Begin)++contacts;});
        auto tick=[&]{
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            if(native)SpriteManager::getSingletonInstance()->stepAnimationPhysics(10);
#endif
            layer->animateLayer(10);
        };
        tick();expect(contacts==0,"both solvers leave concave gap empty");
        probe->setLocation(1,1);tick();expect(contacts==1,"convex pieces aggregate one Begin per public shape");
        wall.setCollisionFilter([](const Collider&,const Collider&){return false;});tick();
        probe->setLocation(5,1);tick();expect(contacts==1,"shared predicate suppresses new contacts");
        wall.setCollisionFilter({});tick();expect(contacts==2,"clearing predicate restores contact detection");
        cleanupLayer(layer);
    }
}

// A rotating corner must transfer motion even when both centers start at rest.
// Fixed simulation steps keep this independent of rendering and wall-clock time.
void spinningBoxContacts() {
    using namespace pdg;
    for (bool chipmunk : {false, true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if (chipmunk) continue;
#endif
        for (double spin : {0.0, 1.0, -1.0}) {
            auto* layer = SpriteManager::createSpriteLayer();
            auto* manager = SpriteManager::getSingletonInstance();
            manager->addLayer(layer);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            layer->setUseChipmunkPhysics(chipmunk);
            layer->setGravity(0); layer->setDamping(1);
#endif
            layer->enableCollisions();
            auto* box = layer->createSprite();
            box->setSize(20, 20);
            box->setupFrameCollider(frameCollider_Bounds);
            box->setupPhysicsBody(5, 5.0 * (20 * 20 + 20 * 20) / 12)
                .setFriction(0).setRestitution(1).setAngularVelocity(spin);
            auto* ball = layer->createSprite();
            ball->setLocation(14.5, 0); // Clear of the edge, inside the corner's swept radius.
            auto& collider = ball->setupCollider().setCircle(2);
            auto& body = ball->setupPhysicsBody(1, 2);
            body.setFriction(0).setRestitution(1);
            int contacts = 0;
            double impulse = 0;
            collider.setContactHandler([&](const ColliderContact& event) {
                if (event.phase == collision_Begin) ++contacts;
                impulse = std::max(impulse, double(std::hypot(event.impulse.x, event.impulse.y)));
                expect(event.other == box->collider.operator->(), "spinning-box contact identifies the box");
            });
            expect(!collider.overlaps(box->collider), "spinning-box fixture starts with separated shapes");
            near(body.getSpeed(), 0, "ball starts at rest");
            for (int i = 0; i < 150; ++i) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
                if (chipmunk) manager->stepAnimationPhysics(10);
#endif
                layer->animateLayer(10);
            }
            if (spin == 0) {
                expect(contacts == 0, "stationary box does not contact the separated ball");
                near(body.getSpeed(), 0, "stationary control does not move the ball");
                near(ball->getLocation().x, 14.5, "stationary control preserves ball position");
            } else {
                expect(contacts > 0, "rotating box corner contacts the stationary ball in either direction");
                expect(impulse > .1, "rotating corner produces a physical contact impulse");
                expect(std::isfinite(body.getSpeed()) && body.getSpeed() > 1,
                    "rotating box transfers angular motion into ball velocity");
            }
            cleanupLayer(layer);
        }
    }
}

void collidersAndConstraints() {
    using namespace pdg;
    static_assert(sizeof(ColliderRef<Sprite>)==sizeof(void*));
    static_assert(!std::is_assignable_v<ColliderRef<Sprite>&,Collider&>);
    Sprite empty;
    expect(empty.collider==Collider::NoCollider,"colliders share absence without allocating a body");
    empty.collider.setCircle(2);
    expect(empty.collider.getShapeCount()==0,"NoCollider ignores geometry mutation");
    auto& geometry=empty.setupCollider();
    expect(&geometry==&empty.setupCollider(),"collider factory is idempotent");
    geometry.setCircle(2);empty.setLocation(10,20);
    expect(geometry.contains(pdg::Point(11,20))&&!geometry.contains(pdg::Point(13,20)),"circle queries follow Animated transforms");
    auto id=geometry.getShapeId(0);geometry.addBox(pdg::Rect(-1,-1,1,1));
    expect(geometry.getShapeId(0)==id&&geometry.getShapeCount()==2,"compound geometry preserves shape IDs");
    bool rejected=false;try{geometry.addPolygon({pdg::Point(0,0),pdg::Point(1,1),pdg::Point(0,1),pdg::Point(1,0)});}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected&&geometry.getShapeCount()==2,"invalid polygon leaves geometry unchanged");
    geometry.addRef();empty.removeCollider();
    expect(!geometry.isAttached()&&geometry.contains(pdg::Point(10,20)),"retained detached collider preserves final query transform");geometry.release();
    for(bool chipmunk:{false,true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if(chipmunk)continue;
#endif
        auto* layer=SpriteManager::createSpriteLayer();
        SpriteManager::getSingletonInstance()->addLayer(layer);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(chipmunk);
#endif
        layer->enableCollisions();auto* host=layer->createSprite();
        auto* part=host->createPart("colliding part");part->setLocation(0,0);
        auto& body=part->setupPhysicsBody(1,100);body.setVelocity(10,0);body.setRestitution(1);
        auto& moving=part->setupCollider().setCircle(1);
        auto* wall=layer->createSprite();wall->setLocation(3,0);auto& fixed=wall->setupCollider().setBox(pdg::Rect(-.5,-5,.5,5));
        int begin=0,stay=0,end=0;bool endpoint=false;double largestImpulse=0;
        moving.setContactHandler([&](const ColliderContact& c){largestImpulse=std::max(largestImpulse,double(std::hypot(c.impulse.x,c.impulse.y)));endpoint=c.collider==&moving&&c.other==&fixed&&c.shape!=0;
            if(c.phase==collision_Begin)++begin;else if(c.phase==collision_Stay)++stay;else if(c.phase==collision_End)++end;});
        auto tick=[&]{
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            if(chipmunk)SpriteManager::getSingletonInstance()->stepAnimationPhysics(10);
#endif
            layer->animateLayer(10);
        };
        for(int i=0;i<60;++i)tick();
        expect(body.getVelocity().x < -5,"Part collider bounces from a bodyless Sprite surface");
        expect(largestImpulse>10,"contact reports the impulse applied by either solver");
        expect(begin>=1&&end>=1&&endpoint,"contact events identify colliders and stable shape IDs");
        expect(wall->physics==PhysicsBody::NoPhysics,"bodyless obstacle does not instantiate PhysicsBody");
        moving.setSensor(true);part->setLocation(0,0);body.setVelocity(10,0);begin=stay=end=0;
        for(int i=0;i<60;++i)tick();
        near(body.getVelocity().x,10,"sensor detects without changing velocity");
        expect(begin==1&&stay>0&&end==1,"sensor delivers one begin, stays, one end");
        moving.setCollisionMask(0);part->setLocation(0,0);body.setVelocity(10,0);begin=0;
        for(int i=0;i<60;++i)tick();expect(begin==0,"collision mask suppresses contacts");
        moving.setCollisionMask(UINT32_MAX).setSensor(false);
        auto* mate=host->createPart("constraint mate");mate->setLocation(-4,0);auto& other=mate->setupPhysicsBody();other.setMode(physicsBody_Static);
        part->setLocation(-2,0);body.stopMoving();
        auto& joint=body.createPinJoint(other);joint.addRef();
        expect(body.getConstraintCount()==1&&other.getConstraintCount()==1,"both endpoints share the same constraint");
        body.applyImpulse(Vector(15,0));
        for(int i=0;i<200;++i)tick();
        expect(std::abs(body.getState().x-other.getState().x-2)<.08,"pin maintains distance in both solvers");
        part->removePhysicsBody();
        expect(!joint.isActive()&&joint.getBodyA()==PhysicsBody::NoPhysics&&other.getConstraintCount()==0,"body removal safely disconnects retained constraint");joint.release();
        // A Part can explicitly contribute geometry to another body's collider set.
        moving.setPhysicsBody(other);tick();
        part->removePhysicsBody();
        expect(&moving.getPhysicsBody()==&other,"removing an absent owner body preserves explicit compound association");
        mate->removePhysicsBody();tick(); // remove native shapes before freeing compound body
        expect(&moving.getPhysicsBody()==&PhysicsBody::NoPhysics,"compound body removal resets to owner association");
        moving.useOwnerPhysics();
        moving.setEnabled(false);
        auto* driver=layer->createSprite();auto& anchor=driver->setupPhysicsBody();anchor.setMode(physicsBody_Static);
        auto* driven=driver->createPart("driven");auto& drivenBody=driven->setupPhysicsBody(1,1);
        auto advance=[&](int count){for(int i=0;i<count;++i)tick();};
        auto reset=[&](double x,double y,double angle){anchor.disconnect();drivenBody.stopMoving().stopSpinning().teleport(pdg::Point(x,y),angle);};
        auto& rotary=anchor.createMotor(drivenBody,2,4);
        advance(100);near(drivenBody.getAngularVelocity(),2,"motor uses positive B-relative-to-A rate in both solvers");
        rotary.setMaxForce(1);drivenBody.stopSpinning();tick();
        expect(rotary.getForce()<=1.00001,"motor obeys updated torque cap");
        rotary.addRef();rotary.setBreakForce(.5);tick();
        expect(rotary.isBroken()&&!rotary.isActive(),"native and basic torque break safely disconnect");rotary.release();
        reset(4,0,0);anchor.createSpring(drivenBody,pdg::Point(),pdg::Point(),2,20,8);advance(300);
        expect(std::abs(drivenBody.getState().x-2)<.03,"linear spring converges to rest length");
        reset(0,0,1);anchor.createRotarySpring(drivenBody,.25,20,8);advance(300);
        expect(std::abs(drivenBody.getState().rotation-.25)<.03,"rotary spring uses B-relative-to-A rest angle");
        reset(0,0,1);anchor.createRotaryLimit(drivenBody,-.4,.4);advance(100);
        expect(drivenBody.getState().rotation<=.42&&drivenBody.getState().rotation>=-.42,"rotary limit constrains relative angle");
        reset(2,1,0);anchor.createPivotJoint(drivenBody);advance(100);
        expect(std::hypot(drivenBody.getState().x,drivenBody.getState().y)<.03,"pivot brings both anchors together");
        reset(0,1,0);anchor.createGrooveJoint(drivenBody,pdg::Point(-2,0),pdg::Point(2,0),pdg::Point());
        drivenBody.setVelocity(1,0);advance(100);
        expect(drivenBody.getState().x>.9&&std::abs(drivenBody.getState().y)<.04,"groove permits tangent motion while constraining its normal");
        reset(4,0,0);anchor.createSlideJoint(drivenBody,pdg::Point(),pdg::Point(),1,2);advance(100);
        expect(std::abs(drivenBody.getState().x)<=2.03&&std::abs(drivenBody.getState().x)>=.97,"slide honors minimum and maximum distance");
        reset(0,0,1);anchor.createGear(drivenBody,2,.5);advance(100);
        expect(std::abs(2*drivenBody.getState().rotation-.5)<.03,"gear honors its ratio and phase");
        reset(0,0,0);anchor.createRatchet(drivenBody,.5);drivenBody.setAngularVelocity(2);advance(50);
        const double allowed=drivenBody.getState().rotation;expect(allowed>.8,"ratchet permits forward rotation");
        drivenBody.setAngularVelocity(-2);advance(100);
        expect(drivenBody.getState().rotation>=allowed-.55,"ratchet blocks backward rotation at the previous tooth");
        reset(0,0,0);auto& transferJoint=anchor.createPinJoint(drivenBody);transferJoint.addRef();
        auto* target=SpriteManager::createSpriteLayer();SpriteManager::getSingletonInstance()->addLayer(target);
        target->addSprite(driver);expect(!transferJoint.isActive(),"layer transfer disconnects body constraints");transferJoint.release();
        rejected=false;try{host->setupPhysicsBody().createPinJoint(drivenBody);}catch(const std::invalid_argument&){rejected=true;}
        expect(rejected,"constraints reject endpoints in different layer worlds");
        auto* fresh=host->createPart("unstepped compound");
        rejected=false;try{fresh->setupCollider().setCircle(1).setPhysicsBody(drivenBody);}catch(const std::invalid_argument&){rejected=true;}
        expect(rejected,"compound association rejects another world before its first update");
        host->removePart(fresh->getId());
        cleanupLayer(target);
        // Layer links work for both new owner types, with one begin event per pair.
        target=SpriteManager::createSpriteLayer();SpriteManager::getSingletonInstance()->addLayer(target);
        auto* trigger=target->createSprite();auto& triggerCollider=trigger->setupCollider().setCircle(2).setSensor(true);
        part->setLocation(0,0);moving.setEnabled(true).setSensor(true);begin=0;
        int linkedBegins=0;moving.setContactHandler([&](const ColliderContact& c){if(c.other==&triggerCollider&&c.phase==collision_Begin)++linkedBegins;});
        target->enableCollisionsWithLayer(layer);tick();target->animateLayer(10);
        expect(linkedBegins==1,"cross-layer contacts dispatch once through either-direction link");
        cleanupLayer(target);tick();
        // EventEmitter must remain alive if a listener removes its owning Sprite.
        struct RemoveOwner : IEventHandler {
            SpriteLayer* layer = nullptr;
            Sprite* owner = nullptr;
            int calls = 0;
            bool handleEvent(EventEmitter*, long, void*) throw() override {
                ++calls; layer->removeSprite(owner); return true;
            }
        } removeOwner;
        auto* disposable=layer->createSprite();disposable->setLocation(40,0);
        auto* disposalPart=disposable->createPart("sensor");
        auto& disposableCollider=disposalPart->setupCollider().setCircle(1).setSensor(true).setWantsContactEvents(true);
        disposableCollider.addRef();
        auto* disposalSurface=layer->createSprite();disposalSurface->setLocation(40,0);disposalSurface->setupCollider().setCircle(1);
        removeOwner.layer=layer;removeOwner.owner=disposable;
        disposable->addHandler(&removeOwner,eventType_ColliderContact);
        tick();
        expect(removeOwner.calls==1&&!disposableCollider.isAttached(),"event listener can destroy its Part's Sprite safely");
        disposableCollider.release();layer->removeSprite(disposalSurface);
        // Destroying a layer in a native callback is deferred until traversal ends.
        bool removed=false;moving.setContactHandler([&](const ColliderContact& c){if(c.phase==collision_Begin){removed=true;cleanupLayer(layer);}});
        auto* overlapping=layer->createSprite();overlapping->setupCollider().setCircle(2);
        tick();expect(removed,"contact callback can safely request whole-layer cleanup");

    }
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    // A linked pair can use different solvers. Chipmunk cannot solve a shape
    // absent from its space; fallback response must still update both bodies.
    for (bool nativeMover : {false, true}) {
        auto* basic=SpriteManager::createSpriteLayer();auto* native=SpriteManager::createSpriteLayer();
        auto* manager=SpriteManager::getSingletonInstance();manager->addLayer(basic);manager->addLayer(native);
        basic->setUseChipmunkPhysics(false);native->setUseChipmunkPhysics(true);
        native->enableCollisionsWithLayer(basic);
        auto* mover=(nativeMover?native:basic)->createSprite();
        mover->setupPhysicsBody().setVelocity(10,0).setRestitution(1);mover->setupCollider().setCircle(1);
        auto* surface=(nativeMover?basic:native)->createSprite();surface->setLocation(3,0);
        surface->setupCollider().setBox(pdg::Rect(-.5,-5,.5,5));
        for(int i=0;i<60;++i){manager->stepAnimationPhysics(10);basic->animateLayer(10);native->animateLayer(10);}
        expect(mover->physics.getVelocity().x < -5,"linked basic/Chipmunk layers resolve physical contacts");
        cleanupLayer(basic);cleanupLayer(native);
    }
    int remainingBodies=0,remainingShapes=0,remainingJoints=0;
    auto* space=SpriteManager::getSingletonInstance()->mSpace;
    cpSpaceEachBody(space,[](cpBody*,void* n){++*static_cast<int*>(n);},&remainingBodies);
    cpSpaceEachShape(space,[](cpShape*,void* n){++*static_cast<int*>(n);},&remainingShapes);
    cpSpaceEachConstraint(space,[](cpConstraint*,void* n){++*static_cast<int*>(n);},&remainingJoints);
    expect(remainingBodies==0&&remainingShapes==0&&remainingJoints==0,"collider tests release all native solver objects");
#endif
    PhysicsBody a,b;a.setMode(physicsBody_Static);
    auto& motor=a.createMotor(b,2,3);motor.addRef();
    PhysicsBody::solveConstraints({&a,&b},.1);
    near(b.getAngularVelocity(),.3,"basic motor respects maximum torque and native rate convention");
    motor.setBreakForce(1);PhysicsBody::solveConstraints({&a,&b},.1);
    expect(motor.isBroken()&&!motor.isActive(),"break threshold preserves safe detached handle");motor.release();
    rejected=false;try{a.createPinJoint(PhysicsBody::NoPhysics);}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected,"constraint creation never materializes NoPhysics");
}

// Native contact events must reuse Chipmunk manifolds, including contacts that
// have no postSolve callback (sensors, kinematic pairs and sleeping bodies).
void nativeContactReuse() {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    using namespace pdg;
    auto* manager = SpriteManager::getSingletonInstance();
    auto* layer = SpriteManager::createSpriteLayer();
    manager->addLayer(layer);
    layer->setUseChipmunkPhysics(true);
    layer->enableCollisions();
    auto* first = layer->createSprite();
    auto* second = layer->createSprite();
    auto& body = first->setupPhysicsBody(1, 1);
    auto& a = first->setupCollider().setSensor(true);
    auto& b = second->setupCollider().setCircle(2);
    const auto left = a.addCircle(.5, pdg::Point(-.5, 0));
    const auto right = a.addCircle(.5, pdg::Point(.5, 0));
    CollisionWorld probe;
    std::vector<ColliderContact> observed;
    a.setContactHandler([&](const ColliderContact& c) { observed.push_back(c); });
    auto tick = [&] {
        manager->stepAnimationPhysics(10);
        layer->animateLayer(10);
        observed.clear(); // Inspect the independent event history of the probe.
        probe.step({&a, &b}, .01);
    };
    tick();
    expect(probe.getStepStatistics().nativeContacts == 2 &&
           probe.getStepStatistics().fallbackShapeTests == 0,
           "native compound sensor contacts need no second shape test");
    expect(observed.size() == 2 && observed[0].shape == left && observed[1].shape == right &&
           observed[0].otherShape == b.getShapeId(0) && observed[0].sensor,
           "native cache preserves every stable compound shape ID");
    near(observed[0].impulse.x, 0, "sensors report no response impulse");
    body.setMode(physicsBody_Kinematic);
    tick();
    expect(probe.getStepStatistics().nativeContacts == 2 && observed.size() == 2 &&
           observed[0].phase == collision_Stay,
           "kinematic/static sensors reuse preSolve contacts without postSolve");
    a.removeShape(left);
    tick();
    int ended = 0, stayed = 0;
    for (const auto& c : observed) {
        ended += c.shape == left && c.phase == collision_End;
        stayed += c.shape == right && c.phase == collision_Stay;
    }
    expect(ended == 1 && stayed == 1 && probe.getStepStatistics().nativeContacts == 1,
           "shape rebuild removes only the deleted shape's cached contact");
    a.setEnabled(false);
    tick();
    expect(observed.size() == 1 && observed[0].phase == collision_End,
           "disabling a native collider ends its cached contact once");
    a.setEnabled(true);
    tick();
    expect(observed.size() == 1 && observed[0].phase == collision_Begin,
           "re-enabling a native collider starts a fresh contact");
    // A mode change must retire old native arbiters before a pair becomes
    // static/static; Chipmunk otherwise preserves those cached pairs indefinitely.
    body.setMode(physicsBody_Static);
    tick();
    expect(probe.getStepStatistics().nativeContacts == 0 &&
           probe.getStepStatistics().fallbackShapeTests == 1,
           "changing body mode retires cached contacts for static/static fallback");
    first->setLocation(10, 0);
    tick();
    expect(observed.size() == 1 && observed[0].phase == collision_End,
           "former native static/static pair does not retain a stale contact");
    first->setLocation(0, 0);
    tick();
    // Both bodyless endpoints are static: Chipmunk deliberately skips them.
    first->removePhysicsBody();
    tick();
    expect(probe.getStepStatistics().nativeContacts == 0 &&
           probe.getStepStatistics().fallbackShapeTests == 1 && observed.size() == 1,
           "bodyless static/static sensors retain the geometry fallback");
    // A physical resting pair must keep Stay while sleeping, with zero new impulse.
    a.setSensor(false).setCircle(1);
    b.setCircle(1).setRestitution(0);
    first->setLocation(0, 0);
    second->setLocation(1.95, 0);
    auto& sleeper = first->setupPhysicsBody(1, 1);
    sleeper.setRestitution(0).setVelocity(1, 0);
    const auto oldSleep = cpSpaceGetSleepTimeThreshold(manager->mSpace);
    const auto oldIdle = cpSpaceGetIdleSpeedThreshold(manager->mSpace);
    cpSpaceSetIdleSpeedThreshold(manager->mSpace, .05);
    cpSpaceSetSleepTimeThreshold(manager->mSpace, .05);
    tick();
    expect(observed.size() >= 1 && observed[0].normal.x > .99 && observed[0].impulse.x > .9,
           "native normal and impulse point from collider toward the other endpoint");
    for (int i = 0; i < 50; ++i) tick();
    expect(cpBodyIsSleeping(static_cast<cpBody*>(sleeper.nativeBody())),
           "resting body actually sleeps in the native solver");
    expect(probe.getStepStatistics().nativeContacts == 1 &&
           probe.getStepStatistics().fallbackShapeTests == 0 && observed.size() == 1 &&
           observed[0].phase == collision_Stay,
           "sleeping contact stays active without repeated collision detection");
    near(observed[0].impulse.x, 0, "sleeping contact does not repeat its last solve impulse");
    sleeper.teleport(pdg::Point(-10, 0), 0);
    tick();
    expect(observed.size() == 1 && observed[0].phase == collision_End,
           "waking and teleporting a sleeping body ends its cached contact");
    tick();
    expect(observed.empty(), "separated native cache does not repeat End");
    cpSpaceSetSleepTimeThreshold(manager->mSpace, oldSleep);
    cpSpaceSetIdleSpeedThreshold(manager->mSpace, oldIdle);
    a.setContactHandler(nullptr);
    cleanupLayer(layer);
    // Reused native bounds must follow explicit moves of static Part bodies.
    layer = SpriteManager::createSpriteLayer();
    manager->addLayer(layer);
    layer->setUseChipmunkPhysics(true);
    layer->enableCollisions();
    auto* host = layer->createSprite();
    auto* surface = host->createPart("moving static surface");
    surface->setLocation(10, 0);
    surface->setupPhysicsBody().setMode(physicsBody_Static);
    surface->setupCollider().setCircle(1);
    auto* detector = layer->createSprite();
    detector->setupPhysicsBody().setMode(physicsBody_Kinematic);
    auto& sensor = detector->setupCollider().setCircle(1).setSensor(true);
    int began = 0; ended = 0;
    sensor.setContactHandler([&](const ColliderContact& c) {
        began += c.phase == collision_Begin; ended += c.phase == collision_End;
    });
    manager->stepAnimationPhysics(10); layer->animateLayer(10);
    expect(began == 0, "static Part starts outside sensor");
    surface->setLocation(1, 0);
    manager->stepAnimationPhysics(10); layer->animateLayer(10);
    expect(began == 1, "moving static Part reindexes native collision bounds");
    surface->physics.teleport(pdg::Point(10, 0), 0);
    manager->stepAnimationPhysics(10); layer->animateLayer(10);
    expect(ended == 1, "teleporting static Part ends its native sensor contact");
    sensor.setContactHandler(nullptr);
    cleanupLayer(layer);
#endif
}

void nativeRestingStacks() {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    using namespace pdg;
    auto* manager = SpriteManager::getSingletonInstance();
    const auto oldGravity = cpSpaceGetGravity(manager->mSpace);
    const auto oldSleep = cpSpaceGetSleepTimeThreshold(manager->mSpace);
    const auto oldIdle = cpSpaceGetIdleSpeedThreshold(manager->mSpace);
    for (bool parts : {false, true}) {
        auto* layer = SpriteManager::createSpriteLayer();
        manager->addLayer(layer);
        layer->setUseChipmunkPhysics(true);
        layer->setGravity(9.8);
        layer->enableCollisions();
        cpSpaceSetIdleSpeedThreshold(manager->mSpace, .05);
        cpSpaceSetSleepTimeThreshold(manager->mSpace, .5);
        auto* floor = layer->createSprite();
        floor->setLocation(2400, .5);
        floor->setupCollider().setBox(pdg::Rect(-4, -.5, 4, .5)).setRestitution(0);
        auto* host = parts ? layer->createSprite() : nullptr;
        std::vector<PhysicsBody*> bodies;
        auto add = [&](auto& owner, int i) {
            owner.setLocation(2400, -1-2*i);
            auto& body = owner.setupPhysicsBody(1, 2.0/3);
            body.setRestitution(0).setFriction(.6);
            owner.setupCollider().setBox(pdg::Rect(-1, -1, 1, 1));
            bodies.push_back(&body);
        };
        for (int i=0; i<10; ++i) {
            if (parts) add(*host->createPart("stack " + std::to_string(i)), i);
            else add(*layer->createSprite(), i);
        }
        for (int i=0; i<1000; ++i) {
            manager->stepAnimationPhysics(10);
            layer->animateLayer(10);
        }
        for (auto* body : bodies) {
            const auto state = body->getState();
            expect(std::abs(state.x-2400)<.2 && state.y<0,
                   "native stacks remain supported far from the world origin");
            expect(cpBodyIsSleeping(static_cast<cpBody*>(body->nativeBody())),
                   "float owner publication preserves warm starts and allows stack sleeping");
        }
        cleanupLayer(layer);
    }
    cpSpaceSetGravity(manager->mSpace, oldGravity);
    cpSpaceSetSleepTimeThreshold(manager->mSpace, oldSleep);
    cpSpaceSetIdleSpeedThreshold(manager->mSpace, oldIdle);
#endif
}

void physicalProperty() {
    using namespace pdg;
    // Construction must not rely on fresh allocator pages being zero-filled.
    alignas(Sprite) unsigned char storage[sizeof(Sprite)];
    std::memset(storage, 0xff, sizeof(storage));
    auto* dirty = new (storage) Sprite;
    near(dirty->setupPhysicsBody().getRestitution(), 1, "Sprite body initializes its restitution without Chipmunk");
    dirty->~Sprite();
    static_assert(!std::is_assignable<PhysicsBodyRef<Sprite>&, PhysicsBody&>::value,
                  "Sprite physics association must be read-only");
    static_assert(!std::is_assignable<PhysicsBodyRef<Part>&, PhysicsBody&>::value,
                  "Part physics association must be read-only");
    static_assert(!std::is_assignable<PhysicsBodyRef<Sprite>&, PhysicsBodyRef<Sprite>&>::value,
                  "Property copy assignment must not replace the association");
    static_assert(!std::is_assignable<PhysicsBodyRef<Part>&, PhysicsBodyRef<Sprite>&>::value,
                  "Cross-type property assignment must not replace the association");
    Sprite first, second;
    auto* part = second.createPart("body reference");
    PhysicsBody& absent = first.physics;
    expect(&absent == &PhysicsBody::NoPhysics, "absence is the singleton, not a per-owner body");
    expect(first.physics == PhysicsBody::NoPhysics && PhysicsBody::NoPhysics == part->physics,
           "Sprite and Part properties compare to the same singleton in either order");
    first.physics.applyImpulse(Vector(3,4));
    expect(first.physics.getSolver() == physicsSolver_None, "ignored calls never instantiate a solver");
    first.setLocation(pdg::Point(10,20));
    auto& body=first.setupPhysicsBody(2,4);body.addRef();
    expect(&static_cast<PhysicsBody&>(first.physics) == &body,"property returns the factory's body by reference");
    first.physics.applyImpulse(Vector(4,0));
    near(body.getVelocity().x,2,"dot access forwards to the instantiated body");
    first.removePhysicsBody();
    expect(first.physics == PhysicsBody::NoPhysics && !body.isAttached(),"removal restores the shared singleton");
    auto& replacement=first.setupPhysicsBody(3,5);
    expect(&replacement != &body && !body.isAttached(),"recreation leaves retained old bodies detached");
    expect(first.physics != second.physics,"live and absent associations have distinct identities");
    first.removePhysicsBody();body.release();
    expect(first.physics == second.physics && second.physics == part->physics,"all absent references share one object");
}

void physicsSetup() {
    using namespace pdg;
    for (bool native : {false, true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if (native) continue;
#endif
        auto* layer = SpriteManager::createSpriteLayer();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(native);
#endif
        auto* sprite = layer->createSprite();
        auto* part = sprite->createPart("setup");
        auto& anchor = layer->createSprite()->setupPhysicsBody();
        auto check = [&](auto& owner) {
            bool rejected = false;
            try { owner.setupPhysicsBody(2, 0); } catch (const std::invalid_argument&) { rejected = true; }
            expect(rejected && owner.physics == PhysicsBody::NoPhysics, "invalid setup leaves absent body untouched");
            auto& body = owner.setupPhysicsBody(2, 4);
            auto& joint = body.createPinJoint(anchor);
            body.setVelocity(3, 4).setAngularVelocity(2).setFriction(.7);
            const auto state = body.getState();
            const int solver = body.getSolver();
            expect(&owner.setupPhysicsBody(5, 10) == &body, "setup retains body identity");
            near(body.getMass(), 5, "setup applies supplied mass");
            near(body.getMomentOfInertia(), 10, "setup applies supplied inertia");
            for (double bad : {0.0, -1.0, std::nan(""), INFINITY * 1.0}) {
                rejected = false;
                try { owner.setupPhysicsBody(8, bad); } catch (const std::invalid_argument&) { rejected = true; }
                expect(rejected, "invalid inertia rejected on existing body");
                rejected = false;
                try { owner.setupPhysicsBody(bad, 8); } catch (const std::invalid_argument&) { rejected = true; }
                expect(rejected, "invalid mass rejected on existing body");
                near(body.getMass(), 5, "invalid setup preserves mass");
                near(body.getMomentOfInertia(), 10, "invalid setup preserves inertia");
            }
            owner.setupPhysicsBody(7);
            near(body.getMass(), 7, "one argument supplies mass");
            near(body.getMomentOfInertia(), 1, "omitted inertia uses default");
            owner.setupPhysicsBody(2, 4);
            expect(&owner.setupPhysicsBody() == &body, "default setup retains body identity");
            near(body.getMass(), 1, "no-argument setup applies default mass");
            near(body.getMomentOfInertia(), 1, "no-argument setup applies default inertia");
            expect(body.getSolver() == solver && joint.isActive() && &body.getConstraint(0) == &joint,
                   "setup retains solver and constraint associations");
            near(body.getState().x, state.x, "setup preserves position");
            near(body.getVelocity().x, 3, "setup preserves linear velocity");
            near(body.getAngularVelocity(), 2, "setup preserves angular velocity");
            near(body.getFriction(), .7, "setup preserves other body settings");
            body.applyImpulse(Vector(2, 0)); body.applyAngularImpulse(3);
            near(body.getVelocity().x, 5, "solver uses reset mass for impulses");
            near(body.getAngularVelocity(), 5, "solver uses reset inertia for angular impulses");
            body.setMode(physicsBody_Kinematic); owner.setupPhysicsBody(6, 9);
            expect(body.getMode() == physicsBody_Kinematic, "setup preserves body mode");
            near(body.getMass(), 6, "kinematic body stores configured mass");
            near(body.getMomentOfInertia(), 9, "kinematic body stores configured inertia");
        };
        check(*sprite); check(*part);
        cleanupLayer(layer);
    }
}

void physicalOwners() {
    using namespace pdg;
    Sprite a,b;
    expect((a.physics == PhysicsBody::NoPhysics) && &static_cast<PhysicsBody&>(a.physics)==&static_cast<PhysicsBody&>(b.physics),"body query returns shared absence without allocation");
    a.setLocation(pdg::Point(10,20));a.setMovement(100,0);
    auto& body=a.setupPhysicsBody(2,4);body.addRef();
    expect(&body==&static_cast<PhysicsBody&>(a.physics),"physics reads the existing body");
    near(a.getMovement().x,0,"body creation stops programmed movement");
    body.applyImpulse(Vector(4,0));body.applyAngularImpulse(4);
    body.applyForce(Vector(8,0),.25,.25);body.applyTorque(8,.25,.25);
    step(a,1000);
    near(body.getVelocity().x,3,"finite force contributes only its active duration");
    near(a.getLocation().x,12.625,"basic body publishes analytically integrated position");
    near(body.getAngularVelocity(),1.5,"torque uses inertia and finite seconds");
    near(a.getRotation(),1.3125,"body publishes angular integration once");
    bool rejected=false;try{a.moveTo(pdg::Point(0,0),1);}catch(const std::logic_error&){rejected=true;}
    expect(rejected,"dynamic body rejects a competing position tween");
    a.setLocation(pdg::Point(40,50));near(body.getState().x,40,"immediate location edit teleports physical state");
    a.setSize(10,20);a.setStretching(8,-4);step(a,250);near(a.getWidth(),12,"growth remains available with a body");
    a.removePhysicsBody();expect(!body.isAttached() && (a.physics == PhysicsBody::NoPhysics),"removal detaches retained body");
    const auto location=a.getLocation();body.step(1);near(a.getLocation().x,location.x,"detached body never updates old owner");
    body.release();
    a.setMovement(2,0);step(a,500);near(a.getLocation().x,location.x+1,"programming resumes after body removal");
    auto* part=a.createPart("physical");part->setLocation(pdg::Point(4,0));
    auto& partBody=part->setupPhysicsBody();partBody.addRef();
    const auto world=part->getTransform(partSpace_World);partBody.setVelocity(Vector(8,0));
    a.stopMovement();step(a,250);
    near(part->getTransform(partSpace_World).tx,world.tx+2,"unbound Part body publishes in world coordinates");
    const auto id=part->getId();a.removePart(id);
    expect(!partBody.isAttached(),"removing Part detaches retained body safely");partBody.step(.1);partBody.release();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
    layer->setUseChipmunkPhysics(true);layer->enableCollisions();layer->setGravity(0);layer->setDamping(1);
    auto* sprite=layer->createSprite();expect(!sprite->mBody,"new Chipmunk-layer Sprite has no implicit body");
    auto& chip=sprite->setupPhysicsBody(2,4);chip.addRef();
    expect(chip.getSolver()==physicsSolver_Chipmunk,"explicit body attaches Chipmunk solver");
    chip.applyForce(Vector(8,0),.25,.25);chip.applyTorque(8,.25,.25);
    auto* manager=SpriteManager::getSingletonInstance();
    for(int i=0;i<20;++i){manager->stepAnimationPhysics(50);layer->animateLayer(50);}
    near(chip.getVelocity().x,1,"Chipmunk timed force expires at the correct boundary");
    near(chip.getAngularVelocity(),.5,"Chipmunk timed torque uses inertia");
    const double before=chip.getState().x;
    manager->stepAnimationPhysics(100);layer->animateLayer(100);
    near(chip.getState().x-before,.1,"Chipmunk position is integrated once per step");
    chip.stopMoving().stopSpinning();
    cpSpaceSetSleepTimeThreshold(layer->getSpace(),.01);cpBodySleep(sprite->mBody);
    manager->stepAnimationPhysics(10);
    expect(cpBodyIsSleeping(sprite->mBody),"idle body synchronization preserves Chipmunk sleeping");
    cpSpaceSetSleepTimeThreshold(layer->getSpace(),INFINITY);
    cleanupLayer(layer);expect(chip.getSolver()==physicsSolver_Basic && !chip.isAttached(),"teardown detaches retained Chipmunk body");
    chip.step(.1);chip.release();
#endif
}

void physicalDrives() {
    using namespace pdg;
    for (bool chipmunk : {false,true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if (chipmunk) continue;
#endif
#ifdef PDG_NO_GUI
        auto* layer=createSpriteLayer();
#else
        auto* layer=createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(chipmunk);layer->setGravity(0);layer->setDamping(1);
#endif
        auto* sprite=layer->createSprite();
        auto* part=sprite->createPart("driven");
        auto& body=part->setupPhysicsBody(2,4);
        body.setDriveTarget(pdg::Point(4,3),.5,50,50,2,1);
        for(int i=0;i<300;++i) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            if(chipmunk)SpriteManager::getSingletonInstance()->stepAnimationPhysics(10);
#endif
            layer->animateLayer(10);
        }
        near(part->getTransform(partSpace_World).tx,4,"Part drive publishes solved x");
        near(part->getTransform(partSpace_World).ty,3,"Part drive publishes solved y");
        near(body.getState().rotation,.5,"Part drive publishes solved rotation");
        // The root body's record includes its drive; restoring must preserve the
        // unwrapped angular route instead of choosing a fresh shortest path.
        layer->setSerializationFlags(ser_Update & ~ser_Animations); // root physics only; receiver has no Parts
        auto& root=sprite->setupPhysicsBody();
        root.setDriveTarget(pdg::Point(8,2),7,15,3,3,.8,rotationDirection_AsSpecified);
        Serializer writer;writer.setSendTags(false);const auto size=sprite->getSerializedSize(&writer);sprite->serialize(&writer);
        expect(writer.getDataSize()==size,"drive snapshot byte count");
        void* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
        Deserializer reader(bytes,writer.getDataSize());auto* restored=layer->createSprite();restored->deserialize(&reader);
        expect(restored->physics.isDriveEnabled(),"snapshot reinstates drive");
        near(restored->physics.getDriveState().rotation,7,"snapshot preserves directed full-turn target");
        near(restored->physics.getDriveState().maxForce,15,"snapshot preserves physical limit");
        cleanupLayer(layer);
    }
#ifdef PDG_USE_CHIPMUNK_PHYSICS
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
    layer->setUseChipmunkPhysics(true);layer->enableCollisions();layer->setGravity(0);layer->setDamping(1);
    auto* driven=layer->createSprite();driven->setupPhysicsBody().setRestitution(0);driven->setupCollider().setCircle(1);
    auto* wall=layer->createSprite();wall->setLocation(pdg::Point(4,0));
    wall->setupPhysicsBody().setMode(physicsBody_Static).setRestitution(0);wall->setupCollider().setCircle(1);
    driven->physics.setDriveTarget(pdg::Point(10,0),0,20,0,3,1);
    for(int i=0;i<300;++i) {SpriteManager::getSingletonInstance()->stepAnimationPhysics(10);layer->animateLayer(10);}
    expect(driven->getLocation().x<2.2 && driven->getLocation().x>1.8,"contact blocks active drive without teleportation");
    expect(driven->physics.getDriveState().positionError>7,"blocked drive reports unreached goal");
    // Pull hard against an immovable wrist-like pivot. Continuous loads must
    // reach the velocity solver before they can stretch the joint's positions.
    auto* anchor=layer->createSprite();
    anchor->setupPhysicsBody().setMode(physicsBody_Static);
    auto* hand=anchor->createPart("hand");
    auto& handBody=hand->setupPhysicsBody(1,1);
    anchor->physics.createPivotJoint(handBody);
    handBody.setDriveTarget(pdg::Point(100,100),0,1000,0,4,1.5);
    for(int i=0;i<200;++i) {
        SpriteManager::getSingletonInstance()->stepAnimationPhysics(10);layer->animateLayer(10);
        const auto state=handBody.getState();
        expect(std::hypot(state.x,state.y)<.01,"manual drive must not stretch a constrained pivot");
    }
    handBody.clearDrive();handBody.applyForce(Vector(1000,0),.2,.05);
    for(int i=0;i<40;++i) {
        SpriteManager::getSingletonInstance()->stepAnimationPhysics(10);layer->animateLayer(10);
        const auto state=handBody.getState();
        expect(std::hypot(state.x,state.y)<.01,"timed force must not stretch a constrained pivot");
    }
    cleanupLayer(layer);
#endif
}

void physicalSnapshots() {
    using namespace pdg;
    auto restore = [](Sprite& sprite, Serializer& data) {
        // Native Deserializer takes ownership of its input allocation.
        void* bytes = std::malloc(data.getDataSize());
        if (!bytes) throw std::bad_alloc();
        std::memcpy(bytes, data.getDataPtr(), data.getDataSize());
        Deserializer reader(bytes, data.getDataSize());
        sprite.deserialize(&reader);
    };
    for (bool chipmunk : {false, true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if (chipmunk) continue;
#endif
#ifdef PDG_NO_GUI
        auto* layer = createSpriteLayer();
#else
        auto* layer = createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(chipmunk);
        layer->setGravity(0);layer->setDamping(1);
#endif
        auto* source = layer->createSprite();
        source->setLocation(pdg::Point(3,4));
        source->setCenterOffset(Offset(1,2));
        auto& body = source->setupPhysicsBody(2,4);
        body.setVelocity(8,-2).setAngularVelocity(.5);
        body.applyForce(Vector(4,0),.25,.25);
        Serializer full;
        full.setSendTags(false);
        const auto before = full.getDataSize();
        const auto size = source->getSerializedSize(&full);
        source->serialize(&full);
        expect(full.getDataSize()-before == size, "body snapshot size matches its bytes");
        auto* restored = layer->createSprite();
        restore(*restored, full);
        near(restored->physics.getVelocity().x,8,"fresh physical snapshot retains velocity");
        near(restored->physics.getMomentOfInertia(),4,"snapshot retains explicit inertia");
        expect(restored->physics.getSolver() == (chipmunk ? physicsSolver_Chipmunk : physicsSolver_Basic),
               "restored body attaches to the destination solver");

        layer->setSerializationFlags(ser_Positions);
        source->setLocation(pdg::Point(40,50));source->setRotation(1.25);
        Serializer positions;source->serialize(&positions);
        restore(*restored, positions);
        near(restored->physics.getState().x,41,"position update teleports body with pivot");
        near(restored->physics.getState().y,52,"position update preserves pivot y");
        near(restored->physics.getState().rotation,1.25,"position update reaches solver rotation");
        near(restored->physics.getVelocity().x,8,"position update preserves physical velocity");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        SpriteManager::getSingletonInstance()->stepAnimationPhysics(100);
#endif
        layer->animateLayer(100);
        near(restored->getLocation().x,40.8,"next solver tick keeps updated position");
        near(restored->getRotation(),1.3,"next solver tick keeps updated rotation");

        layer->setSerializationFlags(ser_Physics);
        body.setMomentOfInertia(9).setVelocity(6,0);
        Serializer settings;source->serialize(&settings);
        restore(*restored, settings);
        near(restored->physics.getMomentOfInertia(),9,"physics-only snapshot includes explicit inertia");
        near(restored->physics.getVelocity().x,6,"physics-only snapshot restores body state");

        layer->setSerializationFlags(ser_Full);
        source->removePhysicsBody();source->setMovement(4,0);source->setSpin(2);
        Serializer programmed;source->serialize(&programmed);
        restore(*restored, programmed);
        expect(restored->physics == PhysicsBody::NoPhysics,"absent snapshot removes old solver association");
        near(restored->getMovement().x,4,"absent snapshot retains programmed movement");
        near(restored->getSpin(),2,"absent snapshot retains programmed spin");
        const auto location = restored->getLocation();
        step(*restored,250);
        near(restored->getLocation().x,location.x+1,"restored programmed motion advances without physics");
        cleanupLayer(layer);
    }
}

void animatedOwners() {
    using namespace pdg;
    Sprite root;root.setLocation(pdg::Point(10,20));root.setScale(2,3);
    auto* parent=root.createPart("parent");parent->setLocation(pdg::Point(4,5));parent->setScale(.5,-2);
    auto* child=root.createPart("child");child->setParentPart(parent);child->setLocation(pdg::Point(6,7));
    auto transform=child->getTransform(partSpace_World);
    near(transform.tx,24,"Part scales compose through Sprite exactly once");
    near(transform.ty,-7,"signed ancestor scale composes into Part world position");
#ifndef PDG_NO_GUI
    {
        std::unique_ptr<Drawing> drawing(Drawing::create());
        std::unique_ptr<ElementRef> element(drawing->addRect(pdg::Rect(0,0,10,20),Attributes()));
        child->setDrawing(*drawing);
    }
    expect(child->hasContent(),"Part retains Drawing after caller destroys its wrapper");
    near(child->getContentBounds(partSpace_Local).right,10,"local content bounds");
    const auto artBounds=child->getContentBounds(partSpace_World);
    near(artBounds.right,34,"Part artwork inherits composed horizontal scale");
    near(artBounds.top,-127,"Part artwork bounds handle reflected vertical scale");
    child->clearContent();expect(!child->hasContent(),"content clear independent of Part lifetime");
#endif
    parent->changeScaleTo(1,1,.5,linearTween);step(root,250);
    near(parent->getScale().x,.75,"Sprite advances Part scale tween");
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
    layer->setScale(2,-3);layer->setLocation(pdg::Point(4,6));layer->setRotation(.3);
    const pdg::Point point(10,20);const auto roundtrip=layer->portToLayer(layer->layerToPort(point));
    near(roundtrip.x,point.x,"scaled layer point inverse x");near(roundtrip.y,point.y,"scaled layer point inverse y");
    const Quad quad(pdg::Rect(0,0,10,20));const auto q=layer->portToLayer(layer->layerToPort(quad));
    for(int i=0;i<4;++i) {near(q.points[i].x,quad.points[i].x,"layer quad roundtrip x");near(q.points[i].y,quad.points[i].y,"layer quad roundtrip y");}
#endif
    layer->setSerializationFlags(ser_Full);
    auto* source=layer->createSprite();source->setSize(10,20);source->setScale(.5,2);
    source->changeScaleTo(2,3,1,linearTween);source->changeStretchingTo(8,-4,1,linearTween);step(*source,250);source->pauseSchedule();source->wait(.125);
    Serializer data;data.setSendTags(false);const auto size=source->getSerializedSize(&data);source->serialize(&data);
    expect(data.getDataSize()==size,"animation snapshot byte count");
    void* bytes=std::malloc(data.getDataSize());std::memcpy(bytes,data.getDataPtr(),data.getDataSize());
    Deserializer reader(bytes,data.getDataSize());
    auto* restored=layer->createSprite();restored->deserialize(&reader);
    near(restored->getScale().x,.875,"snapshot current fractional scale");
    expect(restored->isSchedulePaused() && restored->hasScheduledAnimations(),"snapshot retains paused transitions");
    step(*restored,500);near(restored->getScale().x,.875,"restored paused scale held");
    near(restored->getStretching().x,2,"restored paused growth held");
    restored->resumeSchedule();step(*restored,750);near(restored->getScale().x,2,"restored scale target");
    near(restored->getStretching().x,8,"restored growth target");
    restored->changeScaleTo(4,4,.125,linearTween);step(*restored,100);near(restored->getScale().x,2,"restored pending wait");
    step(*restored,150);near(restored->getScale().x,4,"restored delayed timed target");
    cleanupLayer(layer);
}

void baseSnapshots() {
    using namespace pdg;
    struct Object:Animated<Object> { Object()=default; ~Object()=default; } source, restored;
    source.setLocation(pdg::Point(4,8));source.setSize(10,20);source.setScale(2,3);
    source.changeMovementTo(8,0,.5,linearTween);source.changeScaleTo(4,5,.5,linearTween);
    source.animate(.125);source.pauseSchedule();source.wait(.25);
    Serializer writer;writer.setSendTags(false);const auto size=source.getSerializedSize(&writer);source.serialize(&writer);
    expect(size==writer.getDataSize(),"Animated snapshot exact size");
    void* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
    Deserializer reader(bytes,writer.getDataSize());restored.deserialize(&reader);
    near(restored.getLocation().x,source.getLocation().x,"Animated restores fractional movement sample");
    near(restored.getScale().y,3.5,"Animated restores independent scale");
    expect(restored.isSchedulePaused() && restored.hasScheduledAnimations(),"Animated restores clock and tracks");
    restored.resumeSchedule();restored.animate(.375);near(restored.getScale().y,5,"Animated restored curve completes");
    near(restored.getMovement().x,8,"Animated restored rate completes");
    restored.changeScaleTo(6,6,.125,linearTween);restored.animate(.125);near(restored.getScale().x,4,"Animated retains pending wait");
    restored.animate(.25);near(restored.getScale().x,6,"Animated restored wait and tween complete");

}

// Mix packed flags with object records so size calculations and conditional
// reads are checked even when a flag pair crosses a boolean-byte boundary.
void compactTweenSnapshot(pdg::AnimatedBase& source, pdg::AnimatedBase& restored) {
    using namespace pdg;
    for (bool tags : {false, true}) for (int prefixBits : {0, 1, 6, 7})
        for (bool paused : {false, true}) {
        uint32 noWaitSize = 0;
        for (bool hasWait : {false, true}) {
            source.cancelSchedule().resumeSchedule().setLocation(pdg::Point(0,0)).setScale(1);
            source.moveTo(8,0,.5,linearTween);
            if (paused) source.pauseSchedule();
            if (hasWait) source.wait(.125);
            Serializer writer; writer.setSendTags(tags); writer.serialize_4u(0x12345678);
            for (int bit=0; bit<prefixBits; ++bit) writer.serialize_bool(bit%2==0);
            const auto before = writer.getDataSize();
            const auto size = source.getSerializedSize(&writer); source.serialize(&writer);
            expect(writer.getDataSize()-before == size, "compact tween snapshot exact size with packed prefix flags");
            if (hasWait) expect(size == noWaitSize+8, "only a present wait writes an eight-byte seconds value");
            else noWaitSize = size;
            for (int bit=0; bit<9; ++bit) writer.serialize_bool(bit%2!=0);
            writer.serialize_4u(0x87654321);
            void* bytes=std::malloc(writer.getDataSize()); std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
            Deserializer reader(bytes,writer.getDataSize());
            expect(reader.deserialize_4u()==0x12345678, "snapshot prefix preserved");
            for (int bit=0; bit<prefixBits; ++bit)
                expect(reader.deserialize_bool()==(bit%2==0), "prefix boolean preserved");
            restored.wait(9); // An absent wait must clear a previous pending wait.
            if (paused) restored.resumeSchedule(); else restored.pauseSchedule();
            restored.deserialize(&reader);
            expect(restored.isSchedulePaused()==paused && restored.hasScheduledAnimations(), "compact snapshot restores both pause states");
            for (int bit=0; bit<9; ++bit)
                expect(reader.deserialize_bool()==(bit%2!=0), "following booleans remain aligned");
            expect(reader.deserialize_4u()==0x87654321, "conditional wait read leaves following fields aligned");
            if (paused) {
                restored.animate(.125);
                near(restored.getLocation().x,0,"restored tween remains paused");
            }
            restored.resumeSchedule().animate(.25);
            near(restored.getLocation().x,4,"restored tween resumes at saved progress");
            restored.changeScaleTo(3,3,.0625,linearTween); restored.animate(.0625);
            near(restored.getScale().x,hasWait ? 1 : 3,"restored pending wait delays only when present");
            restored.animate(.125);
            near(restored.getScale().x,3,"restored fractional wait and timed operation complete");
        }
    }
}

void sequencedSnapshot(pdg::AnimatedBase& source,pdg::AnimatedBase& copy) {
    using namespace pdg;
    for (bool tags : {false,true}) for (bool pending : {false,true}) {
        source.cancelSchedule().resumeSchedule().setLocation(pdg::Point(0,0)).setScale(1);
        source.moveTo(10,0,.5,linearTween).andThen().moveBy(5,0,.5,linearTween);
        if (pending) source.andThen();
        Serializer writer;writer.setSendTags(tags);
        const auto size=source.getSerializedSize(&writer);source.serialize(&writer);
        expect(writer.getDataSize()==size+(tags ? 3 : 0),"sequenced snapshot size remains exact");
        void* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
        Deserializer reader(bytes,writer.getDataSize());copy.deserialize(&reader);
        if (!pending) copy.andThen();
        copy.changeScaleTo(2,2,.5,linearTween);
        copy.animate(.75);near(copy.getLocation().x,12.5,"snapshot keeps earlier move and relative successor");
        near(copy.getScale().x,1,"snapshot preserves pending sequence or latest-operation anchor");
        copy.animate(.5);near(copy.getLocation().x,15,"snapshot chain reaches final position");
        near(copy.getScale().x,1.5,"snapshot successor starts at saved completion time");
        copy.animate(.25);near(copy.getScale().x,2,"snapshot successor completes");
    }
    source.cancelSchedule().wait(0);
    Serializer zeroWait;source.serialize(&zeroWait);
    void* zeroBytes=std::malloc(zeroWait.getDataSize());std::memcpy(zeroBytes,zeroWait.getDataPtr(),zeroWait.getDataSize());
    Deserializer zeroReader(zeroBytes,zeroWait.getDataSize());copy.deserialize(&zeroReader);
    bool rejected=false;try{copy.setScale(3);}catch(const std::invalid_argument& error){
        rejected=std::string(error.what())=="Only operations with a duration can be part of a timed animation sequence.";
    }
    expect(rejected,"explicit wait zero remains a duration requirement after restore");
    copy.changeScaleTo(3,3,.25,linearTween);copy.animate(.25);
    near(copy.getScale().x,3,"positive duration consumes restored wait zero");

}

void sequencedSnapshots() {
    {
        pdg::Sprite sprite;
        sprite.fadeOut(.5,pdg::linearTween);sprite.andThen();sprite.fadeIn(.5,pdg::linearTween);
        near(sprite.getOpacity(),1,"queued fade-in leaves predecessor opacity intact");
        sprite.animate(.25);near(sprite.getOpacity(),.5,"fade-out midpoint");
        sprite.animate(.5);near(sprite.getOpacity(),.5,"fade-in midpoint");
        sprite.animate(.25);near(sprite.getOpacity(),1,"fade sequence endpoint");
#ifndef PDG_NO_GUI
        pdg::SpriteLayer layer;
        layer.zoomTo(2,.5,pdg::linearTween);layer.andThen();layer.zoomTo(3,.5,pdg::linearTween);
        layer.animate(.75);near(layer.getZoom(),2.5,"queued zoom midpoint");
#endif
    }
    using namespace pdg;
    struct Object:Animated<Object> {Object()=default;~Object()=default;} a,b;
    sequencedSnapshot(a,b);
    // Only the last operation's identity is needed on the wire; older queued
    // moves must still take ownership away from an overlapping earlier move.
    a.cancelSchedule().setLocation(pdg::Point(0,0));
    a.moveTo(40,0,4,linearTween).rotateTo(1,1,linearTween)
        .andThen().moveTo(20,0,1,linearTween).andThen().changeScaleTo(2,2,1,linearTween);
    Serializer overlap; a.serialize(&overlap);
    void* overlapBytes=std::malloc(overlap.getDataSize());std::memcpy(overlapBytes,overlap.getDataPtr(),overlap.getDataSize());
    Deserializer overlapReader(overlapBytes,overlap.getDataSize());b.deserialize(&overlapReader);
    b.animate(2.5);near(b.getLocation().x,20,"restored successor cancels an older overlapping move");
    struct FadeSprite:Sprite {
        std::vector<int> completed;
        void easingCompleted(const Animation& a) override {
            completed.push_back(a.completion);
            Sprite::easingCompleted(a);
        }
    } fade, restoredFade;
    fade.fadeOut(.5,linearTween);fade.andThen();fade.fadeIn(.5,linearTween);
    Serializer fadeWriter;fade.serialize(&fadeWriter);
    void* fadeBytes=std::malloc(fadeWriter.getDataSize());std::memcpy(fadeBytes,fadeWriter.getDataPtr(),fadeWriter.getDataSize());
    Deserializer fadeReader(fadeBytes,fadeWriter.getDataSize());restoredFade.deserialize(&fadeReader);
    restoredFade.animate(.75);near(restoredFade.getOpacity(),.5,"restored fade-in follows fade-out");
    restoredFade.animate(.25);
    expect(restoredFade.completed==std::vector<int>({3,2}),"each restored fade retains its completion kind");
    Sprite sprite,copy;sequencedSnapshot(sprite,copy);
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();auto* other=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);auto* other=createSpriteLayer(nullptr);
#endif
    layer->setSerializationFlags(ser_Update);sequencedSnapshot(*layer,*other);
    auto* owner=layer->createSprite();sequencedSnapshot(*owner->createPart("a"),*owner->createPart("b"));
    cleanupLayer(other);cleanupLayer(layer);
}

void compactTweenObjectStreams() {
    using namespace pdg;
    struct Reader : Deserializer {
        using Deserializer::Deserializer;
        size_t position() const { return p-mDataPtr; }
    };
    Sprite first, second;
    second.wait(.125).pauseSchedule();
    for (bool tags : {false,true}) for (bool preflight : {false,true}) {
        Serializer writer; writer.setSendTags(tags);
        uint32 size=0;
        if (preflight) {
            size += writer.sizeof_obj(&first);
            size += writer.sizeof_obj(&second);
        }
        writer.serialize_obj(&first); writer.serialize_obj(&second);
        if (preflight) expect(writer.getDataSize()==size+(tags ? 3 : 0), "packed object sizes match a separate preflight traversal");
        void* bytes=std::malloc(writer.getDataSize()); std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
        Reader reader(bytes,writer.getDataSize());
        // Read the object envelope explicitly, verifying the advertised length
        // against the actual payload, including booleans shared across records.
        for (int i=0; i<2; ++i) {
            reader.deserialize_3u(); reader.deserialize_4u();
            if (tags) reader.deserialize_2u();
            const auto length=reader.deserialize_uint();
            const auto before=reader.position();
            Sprite copy; copy.deserialize(&reader);
            expect(reader.position()-before==length,
                "object envelope length matches compact tween payload");
            expect(copy.isSchedulePaused()==(i==1), "object stream preserves compact pause flags");
        }
    }
    Serializer writer; writer.setSendTags(false); first.serialize(&writer);
    const std::vector<char> padding(1024*1024,'x');
    writer.serialize_mem(padding.data(),padding.size()); // move the allocation while its bool byte is still open
    second.serialize(&writer);
    void* bytes=std::malloc(writer.getDataSize()); std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
    Deserializer reader(bytes,writer.getDataSize());
    Sprite a,b; a.deserialize(&reader);
    std::vector<char> restoredPadding(padding.size());
    reader.deserialize_mem(restoredPadding.data(),restoredPadding.size()); b.deserialize(&reader);
    expect(restoredPadding==padding && b.isSchedulePaused(), "packed tween flags survive serialization buffer growth");
    b.changeScaleTo(3,3,.0625,linearTween).resumeSchedule().animate(.0625);
    near(b.getScale().x,1,"wait flag survives serialization buffer growth");
    b.animate(.125); near(b.getScale().x,3,"wait duration survives serialization buffer growth");
}

void compactTweenSnapshots() {
    using namespace pdg;
    struct Object:Animated<Object> { Object()=default; ~Object()=default; } source, restored;
    compactTweenSnapshot(source,restored);
    Sprite sprite, copy;
    compactTweenSnapshot(sprite,copy);
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer(); auto* destination=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr); auto* destination=createSpriteLayer(nullptr);
#endif
    layer->setSerializationFlags(ser_Update);
    compactTweenSnapshot(*layer,*destination);
    auto* owner=layer->createSprite();
    compactTweenSnapshot(*owner->createPart("source"),*owner->createPart("copy"));
    cleanupLayer(destination); cleanupLayer(layer);
}

void expectSnapshotColor(const pdg::Color& actual, const pdg::Color& source) {
    const float actualChannels[] = {actual.red, actual.green, actual.blue, actual.alpha};
    const float sourceChannels[] = {source.red, source.green, source.blue, source.alpha};
    for (int i = 0; i < 4; ++i) {
        expect(std::abs(actualChannels[i]-sourceChannels[i]) < 1.0/255.0 + 1e-7,
            "snapshot color stays within one eight-bit channel step");
        near(actualChannels[i]*255, std::floor(sourceChannels[i]*255),
            "snapshot color uses PDG's eight-bit channel encoding");
    }
}

void imageSnapshots() {
    using namespace pdg;
    using ImagePtr = std::unique_ptr<Image, void(*)(Image*)>;
    auto release=[](Image* p){ if(p) p->release(); };
    auto restore=[&](Serializer& writer) {
        void* bytes=std::malloc(writer.getDataSize());
        std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
        Deserializer reader(bytes,writer.getDataSize());
        auto* object=reader.deserialize_obj();
        auto* image=dynamic_cast<Image*>(object);
        if (!image && object) object->release();
        expect(image != nullptr,"Image class factory restores a native image");
        return ImagePtr(image,release);
    };
#ifdef PDG_NO_GUI
    auto* raw = new ImageImpl();
#else
    auto* raw = new ImageOpenGL();
#endif
    raw->addRef(); ImagePtr source(raw,release);
    raw->initEmpty(8,4,32);raw->setNumFrames(2);raw->setOpacity(123);raw->setEdgeClamping(false);
    for (unsigned i=0;i<128;++i) static_cast<uint8*>(raw->data)[i]=uint8(i);
    for (bool tags : {false,true}) for (int mode : {serialization_Complete,serialization_ExternalReferences}) {
        Serializer writer;writer.setSendTags(tags);writer.setResourceMode(mode);
        writer.serialize_obj(raw);
        auto copy=restore(writer);
        auto* image=dynamic_cast<ImageImpl*>(copy.get());
        expect(image && image->data,"runtime-only pixels embed in either save mode");
        expect(image->width==8 && image->height==4 && image->frames==2 && image->frameWidth==4,"strip layout round-trips");
        expect(image->getOpacity()==123 && !image->mUseEdgeClamp,"image settings round-trip");
        expect(std::memcmp(image->data,raw->data,128)==0,"complete RGB/alpha pixel payload round-trips");
        bool rejected=false;
        try { writer.setResourceMode(mode==serialization_Complete ? serialization_ExternalReferences : serialization_Complete); }
        catch(const std::logic_error&) { rejected=true; }
        expect(rejected,"changing policy after writing objects is rejected");
    }
    for (bool tags : {false,true}) {
        Serializer writer;writer.setSendTags(tags);
        const auto size=raw->getSerializedSize(&writer);raw->serialize(&writer);
        expect(writer.getDataSize()==size+(tags ? 3 : 0),"image size before first write accounts for selected tags, excluding stream header");
    }
    for (bool tags : {false,true}) for (int prefix = 0; prefix < 8; ++prefix)
        for (float alpha : {0.f, .37f, 1.f}) {
        raw->transparentColor = Color(.5f, .25f, .75f, alpha);
        Serializer writer; writer.setSendTags(tags); writer.serialize_4u(0x434f4c52);
        for (int i=0; i<prefix; ++i) writer.serialize_bool(i%2==0);
        const auto before=writer.getDataSize();
        const auto size=raw->getSerializedSize(&writer); raw->serialize(&writer);
        expect(writer.getDataSize()-before==size, "compact image color sizes follow the packed boolean cursor");
        writer.serialize_bool(true); writer.serialize_4u(0x454e4421);
        void* bytes=std::malloc(writer.getDataSize()); std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
        Deserializer reader(bytes,writer.getDataSize());
        expect(reader.deserialize_4u()==0x434f4c52,"image color prefix marker");
        for (int i=0; i<prefix; ++i) expect(reader.deserialize_bool()==(i%2==0),"image color prefix flags");
#ifdef PDG_NO_GUI
        ImageImpl copy;
#else
        ImageOpenGL copy;
#endif
        copy.deserialize(&reader);
        expectSnapshotColor(copy.transparentColor,raw->transparentColor);
        expect(reader.deserialize_bool()&&reader.deserialize_4u()==0x454e4421,"compact image color leaves following fields aligned");
    }
    raw->transparentColor=Color();
    // Multiple views retain a shared decoded source, including untagged streams.
    auto* first=raw->getFrame(0);first->addRef();ImagePtr firstOwner(first,release);
    auto* second=raw->getFrame(1);second->addRef();ImagePtr secondOwner(second,release);
    for (bool tags : {false,true}) {
        Serializer writer;writer.setSendTags(tags);writer.serialize_obj(first);writer.serialize_obj(second);
        void* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
        Deserializer reader(bytes,writer.getDataSize());
        ImagePtr a(dynamic_cast<Image*>(reader.deserialize_obj()),release), b(dynamic_cast<Image*>(reader.deserialize_obj()),release);
        auto* av=dynamic_cast<ImageImpl*>(a.get());auto* bv=dynamic_cast<ImageImpl*>(b.get());
        expect(av && bv && av->mFrameNum==0 && bv->mFrameNum==1,"frame selections survive a snapshot");
        expect(av->mSuperImage==bv->mSuperImage,"image references preserve sharing rather than duplicating pixels");
    }
    struct Images : Serializable<Images> {
        Image* first=nullptr; Image* second=nullptr;
        ~Images() override { if(first)first->release();if(second)second->release(); }
        uint32 getMyClassTag() const override { return 0x1234567; }
        uint32 getSerializedSize(ISerializer* s) const override { return s->sizeof_obj(first)+s->sizeof_obj(second); }
        void serialize(ISerializer* s) const override { s->serialize_obj(first);s->serialize_obj(second); }
        void deserialize(IDeserializer* d) override {
            first=dynamic_cast<Image*>(d->deserialize_obj());second=dynamic_cast<Image*>(d->deserialize_obj());
        }
    } images;
    images.first=first;first->addRef();images.second=second;second->addRef();
    IDeserializer::registerClass<Images>();
    for (bool tags : {false,true}) {
        Serializer writer;writer.setSendTags(tags);writer.serialize_obj(&images);
        void* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
        Deserializer reader(bytes,writer.getDataSize());
        auto* pair=dynamic_cast<Images*>(reader.deserialize_obj());
        expect(pair && pair->first && pair->second,"nested object sizes account for shared resource references");
        expect(dynamic_cast<ImageImpl*>(pair->first)->mSuperImage==dynamic_cast<ImageImpl*>(pair->second)->mSuperImage,"nested graph restores one shared source image");
        pair->release();
    }
    const auto fixture=std::filesystem::path(__FILE__).parent_path().parent_path()/"data/test_image.png";
    const auto path=std::filesystem::temp_directory_path()/("pdg-resource-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".png");
    struct Cleanup { std::filesystem::path path; ~Cleanup(){std::error_code ec;std::filesystem::remove(path,ec);} } cleanup{path};
    std::filesystem::copy_file(fixture,path);
    ImagePtr named(Image::createImageFromFile(path.string().c_str()),release);
    expect(named->getWidth()>0,"named snapshot fixture loads");
    Serializer complete, references;
    references.setResourceMode(serialization_ExternalReferences);
    complete.serialize_obj(named.get());references.serialize_obj(named.get());
    auto resolved=restore(references);
    expect(resolved->getWidth()==named->getWidth(),"external reference resolves its source");
    std::filesystem::remove(path);
    auto selfContained=restore(complete);
    expect(selfContained->getWidth()==named->getWidth(),"complete snapshot loads after original file is removed");
    expect(selfContained->getPixel(0,0)==named->getPixel(0,0),"complete snapshot preserves decoded colors");
    bool missing=false;
    try { restore(references); } catch(const std::exception& error) {
        missing=std::string(error.what()).find(path.string())!=std::string::npos;
    }
    expect(missing,"missing external resource error identifies the missing file");
    named->setTransparentColor(Color(1.f,1.f,1.f));
    Serializer modified;modified.setResourceMode(serialization_ExternalReferences);modified.serialize_obj(named.get());
    auto edited=restore(modified);
    expect(edited->getPixel(0,0)==named->getPixel(0,0),"modified named pixels embed even when references are allowed and original file is gone");

    Serializer invalid;
    bool rejected=false;try{invalid.setResourceMode(2);}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected && invalid.getResourceMode()==serialization_Complete,"invalid policy leaves complete default unchanged");
    // A short memory destination must not hide a truncated serialized payload.
    Serializer malformed;malformed.setSendTags(false);malformed.serialize_uint(100);malformed.serialize_4u(0);
    void* bytes=std::malloc(malformed.getDataSize());std::memcpy(bytes,malformed.getDataPtr(),malformed.getDataSize());
    Deserializer reader(bytes,malformed.getDataSize());char byte;
    rejected=false;try{reader.deserialize_mem(&byte,1);}catch(const std::exception&){rejected=true;}
    expect(rejected,"truncated memory payload rejects even when only its first byte is requested");
}


#ifndef PDG_NO_GUI
void drawingSnapshots() {
    using namespace pdg;
    auto release = [](Image* image) { image->release(); };
    auto* pixels = new ImageOpenGL(); pixels->addRef();
    std::unique_ptr<Image, decltype(release)> image(pixels, release);
    pixels->initEmpty(8, 4, 32); pixels->setNumFrames(2);
    std::memset(pixels->data, 173, 128);
    std::unique_ptr<Drawing> source(Drawing::create()), nested(Drawing::create());
    Attributes attrs;
    attrs.lineColor(Color(.5f, .25f, .75f, .4f)).lineStyle(lineStyle_Auto).fillColor(Color(.2f, .4f, .6f, 0.f))
        .fillGradient(pdg::Point(1, 2), Color(.1f, .2f, .3f, .25f), pdg::Point(5, 6), Color(.4f, .5f, .6f))
        .fillRadialGradient(pdg::Point(3, 4), Color(1.f, .5f, .25f, .6f), 9, Color(.2f, .3f, .4f))
        .lineThickness(2.5).lineOpacity(.4).fillOpacity(.6).roundedCorners(3)
        .texture(pixels).fitType(fit_Tile).clipOverflow(true).frame(1)
        .translation(Offset(13, 17)).rotation(.3).scale(2, 3)
        .subsection(pdg::Rect(1, 2, 3, 4)).sphereRotation(.7).polarOffset(Offset(5, 6))
        .lightOffset(Offset(7, 8)).ambientLight(Color(.3f, .4f, .5f));
    delete source->addLine(pdg::Point(1, 2), pdg::Point(10, 20), attrs);
    Spline spline(SPLINE_CARDINAL);
    for (pdg::Point point : {pdg::Point(0, 0), pdg::Point(5, 10), pdg::Point(12, 20), pdg::Point(30, 10)}) spline.addPoint(point);
    delete source->addSpline(std::move(spline), attrs);
    delete source->addArc(pdg::Point(4, 5), 7, 9, .2, 2.1, attrs);
    delete source->addRect(pdg::Rect(1, 2, 20, 30), attrs);
    delete source->addQuad(Quad(pdg::Rect(3, 4, 30, 40)), attrs);
    delete source->addPolygon(pdg::Polygon({pdg::Point(0, 0), pdg::Point(20, 0), pdg::Point(4, 30)}), attrs);
    delete source->addEllipse(pdg::Point(9, 12), 4, 7, attrs);
    delete source->addImage(pdg::Rect(0, 0, 8, 4), *pixels, attrs);
    delete source->addImageStrip(pdg::Rect(0, 0, 4, 4), *pixels, attrs);
    delete nested->addLine(pdg::Point(0, 0), pdg::Point(5, 6), Attributes());
    delete source->addDrawing(pdg::Rect(20, 30, 40, 50), *nested, attrs);
    auto sharedSource = source->share();
    for (bool tags : {false, true}) for (int mode : {serialization_Complete, serialization_ExternalReferences})
        for (int prefix=0; prefix<8; ++prefix) {
        Serializer writer; writer.setSendTags(tags); writer.setResourceMode(mode);
        auto writePrefix = [&](Serializer& out) {
            out.serialize_4u(0x434f4c52);
            for (int i=0; i<prefix; ++i) out.serialize_bool(i%2==0);
        };
        auto readPrefix = [&](Deserializer& in) {
            expect(in.deserialize_4u()==0x434f4c52,"Drawing color prefix marker");
            for (int i=0; i<prefix; ++i) expect(in.deserialize_bool()==(i%2==0),"Drawing color prefix flags");
        };
        writePrefix(writer);
        const auto before=writer.getDataSize();
        auto size = drawingSerializedSize(source.get(), &writer);
        size += drawingSerializedSize(sharedSource.get(), &writer);
        size += drawingSerializedSize(nested.get(), &writer);
        size += writer.sizeof_obj(pixels);
        serializeDrawing(source.get(), &writer); serializeDrawing(sharedSource.get(), &writer);
        serializeDrawing(nested.get(), &writer); writer.serialize_obj(pixels);
        expect(writer.getDataSize()-before == size, "Drawing graph size counts shared resources once");
        void* bytes = std::malloc(writer.getDataSize()); std::memcpy(bytes, writer.getDataPtr(), writer.getDataSize());
        Deserializer reader(bytes, writer.getDataSize());
        readPrefix(reader);
        auto copy = deserializeDrawing(&reader), sharedCopy = deserializeDrawing(&reader), nestedCopy = deserializeDrawing(&reader);
        std::unique_ptr<Image, decltype(release)> restoredImage(dynamic_cast<Image*>(reader.deserialize_obj()), release);
        expect(copy->getElementCount() == 10, "all Drawing primitive types survive");
        expect(restoredImage && restoredImage->getPixel(0, 0) == pixels->getPixel(0, 0), "Drawing pixels restored");
        for (size_t i = 0; i < copy->getElementCount(); ++i) {
            std::unique_ptr<ElementRef> original(source->getElement(i)), restored(copy->getElement(i));
            expect(original->type() == restored->type(), "Drawing element order and types preserved");
            expect(original->getControlPoints() == restored->getControlPoints(), "Drawing geometry preserved");
            Attributes a; restored->getAttributes(a);
            expect(a.getTexture() == restoredImage.get(), "Drawing attributes retain shared image identity");
            expect(a.getFitType() == fit_Tile && a.getClipOverflow() && a.getFrame() == 1, "Drawing attribute modes preserved");
            expect(a.getTransform() == attrs.getTransform() && pdg::Rect(a.getSubsection()) == attrs.getSubsection(), "Drawing transform and subsection preserved");
            expect(a.getGradientType() == gradientType_Radial && a.getRadialGradientCenter() == pdg::Point(3, 4), "Drawing gradients preserved");
            near(a.getRadialGradientRadius(), 9, "Drawing gradient radius");
            near(a.getFillOpacity(), .6, "Drawing fill opacity");
            for (auto getter : {&Attributes::getLineColor, &Attributes::getFillColor,
                    &Attributes::getGradientStartColor, &Attributes::getGradientEndColor,
                    &Attributes::getRadialGradientCenterColor, &Attributes::getRadialGradientEndColor,
                    &Attributes::getAmbientLight}) expectSnapshotColor((a.*getter)(), (attrs.*getter)());
            expect(!a.hasLine(), "Drawing automatic line style stays automatic");
        }
        std::unique_ptr<ElementRef> first(copy->getElement(0)), sharedFirst(sharedCopy->getElement(0));
        first->changeControlPoint(1, pdg::Point(111, 222));
        expect(sharedFirst->getControlPoint(1) == pdg::Point(111, 222), "restored Drawing handles share editable storage");
        // Re-encoding the whole graph also exercises nested Drawing/image identity and spline metadata.
        Serializer again; again.setSendTags(tags); again.setResourceMode(mode); writePrefix(again);
        first->changeControlPoint(1, pdg::Point(10, 20));
        serializeDrawing(copy.get(), &again); serializeDrawing(sharedCopy.get(), &again);
        serializeDrawing(nestedCopy.get(), &again); again.serialize_obj(restoredImage.get());
        expect(again.getDataSize() == writer.getDataSize() && std::memcmp(again.getDataPtr(), writer.getDataPtr(), writer.getDataSize()) == 0,
            "Drawing snapshots re-encode all attributes, geometry and nested references exactly");
        void* shortBytes = std::malloc(writer.getDataSize() / 2); std::memcpy(shortBytes, writer.getDataPtr(), writer.getDataSize() / 2);
        Deserializer truncated(shortBytes, writer.getDataSize() / 2);
        bool rejected = false; try { readPrefix(truncated); deserializeDrawing(&truncated); } catch (const std::exception&) { rejected = true; }
        expect(rejected, "truncated Drawing graph rejects");
    }
}
#endif



// Corrupt fields through the actual serializer traversal. Packed bool bytes can
// straddle records, so splicing a separately encoded tail is not a valid fixture.
void compactSnapshotRecords() {
    using namespace pdg;
    for(bool tags:{false,true}) for(int prefix=0;prefix<8;++prefix) for(bool populated:{false,true}) {
        PhysicsBody source,copy;
        copy.setMass(19).setMomentOfInertia(17).setLinearDamping(3).setAngularDamping(4).setVelocity(8,9);
        copy.addContinuousForce(Vector(2,3));copy.setDriveTarget(pdg::Point(8,9),.8,20,10);
        if(populated) {
            source.setMass(1.000000000001).setMomentOfInertia(2.000000000001)
                .setLinearDamping(.00000003125).setAngularDamping(.0000000625)
                .setAngularVelocity(.000000123456789).setFriction(.1234567890123).setRestitution(.2345678901234);
            source.applyImpulse(Vector(.0003125f,.000625f));
            source.applyForce(Vector(.0008125f,.0004125f),.123456789,.023456789);
            source.addContinuousTorque(.000000056789123);
            const auto removed=source.addContinuousForce(Vector(2,3));source.removeForce(removed);
            source.step(.034567891);
        }
        Serializer writer;writer.setSendTags(tags);uint32 expected=0;
        for(int n=0;n<prefix;++n){expected+=writer.sizeof_bool(n%2);writer.serialize_bool(n%2);}
        expected+=source.getSerializedSize(&writer);source.serialize(&writer);
        expected+=writer.sizeof_bool(true);writer.serialize_bool(true);
        expect(writer.getDataSize()==expected+(tags?3:0),"body byte size is exact at every bool offset");
        auto reader=snapshotReader(writer);
        for(int n=0;n<prefix;++n)expect(reader->deserialize_bool()==bool(n%2),"body prefix survives packing");
        copy.deserialize(reader.get());expect(reader->deserialize_bool(),"body suffix survives packing");
        expect(copy.getMass()==source.getMass() && copy.getMomentOfInertia()==source.getMomentOfInertia() &&
            copy.getLinearDamping()==source.getLinearDamping() && copy.getAngularDamping()==source.getAngularDamping() &&
            copy.getFriction()==source.getFriction() && copy.getRestitution()==source.getRestitution(),"physics properties retain every double bit");
        expect(!copy.isDriveEnabled(),"omitted drive clears previously enabled state");
        auto exactState=[&] {
            const auto a=source.getState(),b=copy.getState();
            for(auto member:{&PhysicsBodyState::x,&PhysicsBodyState::y,&PhysicsBodyState::rotation,&PhysicsBodyState::velocityX,&PhysicsBodyState::velocityY,&PhysicsBodyState::angularVelocity})
                expect(snapshotBits(a.*member)==snapshotBits(b.*member),"physics pose/velocity stays bit-exact");
        };
        exactState();source.step(.07654321);copy.step(.07654321);exactState();
        expect(source.addContinuousTorque(2)==copy.addContinuousTorque(2),"removed force IDs are not reused after a checkpoint");
    }
    for(bool tags:{false,true}) for(int prefix=0;prefix<8;++prefix) {
        Sprite source,copy;auto* first=source.createPart("first");auto* second=source.createPart("second");
        first->setLocation(.0005f,12.0005f).setMovement(.0008f,.0009f);
        first->setupPhysicsBody().setMode(physicsBody_Kinematic);
        second->setupPhysicsBody().setVelocity(.0004f,.0006f);
        second->physics.applyTorque(.000000123456,.7654321,.1234567);
#ifndef PDG_NO_GUI
        std::unique_ptr<Drawing> drawing(Drawing::create());delete drawing->addLine(pdg::Point(),pdg::Point(10,20),Attributes());
        first->setDrawing(*drawing);second->setDrawing(*drawing);
#endif
        Serializer writer;writer.setSendTags(tags);uint32 expected=0;
        for(int n=0;n<prefix;++n){expected+=writer.sizeof_bool(n%2);writer.serialize_bool(n%2);}
        expected+=source.getSerializedSize(&writer);source.serialize(&writer);
        expected+=writer.sizeof_bool(true);writer.serialize_bool(true);
        expect(writer.getDataSize()==expected+(tags?3:0),"Sprite/Part bodies and shared artwork size matches at every bool offset");
        auto reader=snapshotReader(writer);for(int n=0;n<prefix;++n)expect(reader->deserialize_bool()==bool(n%2),"Part graph prefix");
        copy.deserialize(reader.get());expect(reader->deserialize_bool(),"Part graph suffix");
        expect(copy.findPart("first")->getLocation()==first->getLocation(),"Part transforms that feed physics/IK retain exact floats");
        near(copy.findPart("second")->physics.getVelocity().x,second->physics.getVelocity().x,"small nonzero body velocity remains present");
    }
    PhysicsBody body;Serializer bytes;bytes.setSendTags(false);body.serialize(&bytes);
    std::cout<<"Compact wire sizes (untagged): default PhysicsBody="<<bytes.getDataSize();
    AnimatedBase animated;Serializer motion;motion.setSendTags(false);animated.serialize(&motion);
    std::cout<<", default Animated="<<motion.getDataSize();
#ifndef PDG_NO_GUI
    std::unique_ptr<Drawing> drawing(Drawing::create());delete drawing->addLine(pdg::Point(),pdg::Point(10,20),Attributes());
    Serializer artwork;artwork.setSendTags(false);serializeDrawing(drawing.get(),&artwork);const auto first=artwork.getDataSize();
    serializeDrawing(drawing.get(),&artwork);
    std::cout<<", default-attribute Drawing line="<<first<<", repeated Drawing reference="<<artwork.getDataSize()-first;
#endif
    std::cout<<" bytes\n";
}
#ifndef PDG_NO_GUI
void visualSnapshotCoordinates() {
    using namespace pdg;
    for(bool tags:{false,true}) for(int prefix=0;prefix<8;++prefix) {
        for(float value:{.0005f,12.0005f,-.0005f,-12.0005f,12.125f,65536.f}) {
            Attributes attrs;attrs.lineThickness(std::abs(value)).textSize(std::abs(value)).translation(Offset(value,value));
            std::unique_ptr<Drawing> drawing(Drawing::create());delete drawing->addLine(pdg::Point(value,value),pdg::Point(100,200),attrs);
            Serializer writer;writer.setSendTags(tags);uint32 expected=0;
            for(int n=0;n<prefix;++n){expected+=writer.sizeof_bool(n%2);writer.serialize_bool(n%2);}
            expected+=drawingSerializedSize(drawing.get(),&writer);serializeDrawing(drawing.get(),&writer);
            expected+=writer.sizeof_bool(true);writer.serialize_bool(true);
            expect(writer.getDataSize()==expected+(tags?3:0),"visual coordinate size matches all compact/raw branches");
            auto reader=snapshotReader(writer);for(int n=0;n<prefix;++n)expect(reader->deserialize_bool()==bool(n%2),"visual prefix");
            auto copy=deserializeDrawing(reader.get());expect(reader->deserialize_bool(),"visual suffix");
            std::unique_ptr<ElementRef> element(copy->getElement(0));
            auto close=[](float a,float b) {expect(std::abs(a-b)<.001f,"visual coordinates lose less than a thousandth per encoded component");};
            const auto point=element->getControlPoint(0);close(point.x,value);close(point.y,value);
            Attributes attributes;element->getAttributes(attributes);close(attributes.getLineThickness(),std::abs(value));close(attributes.getTextSize(),std::abs(value));
            close(attributes.getTransform()[2][0],value);close(attributes.getTransform()[2][1],value);
        }
    }
}
#endif

void invalidPartSnapshots() {
    using namespace pdg;
    Sprite source, destination;
    source.createPart("first");source.createPart("second");
    auto* existing=destination.createPart("keep");
    for(int invalid=0;invalid<=4;++invalid) {
        SnapshotTestWriter writer;writer.setSendTags(false);
        bool parent=false;uint32 parentValue=partId_None;
        writer.onString=[&](const char*& name) {
            if(std::string(name)=="first" || std::string(name)=="second") {
                const bool second=std::string(name)=="second";
                if(invalid==0 && second) { writer.replaceByte(writer.lastInteger,0);++writer.mutations; }
                if(invalid==1 && second) { name="first";++writer.mutations; }
                parent=invalid==2 || invalid==3;parentValue=invalid==2 ? 12 : second ? 0 : 1;
            }
        };
        writer.afterString=[&]{ writer.nextInteger=parent;parent=false; };
        writer.onInteger=[&](uint32& n) { if(writer.nextInteger){n=parentValue;writer.nextInteger=false;++writer.mutations;} };
        source.serialize(&writer);
        auto reader=snapshotReader(writer);bool rejected=false;
        try{destination.deserialize(reader.get());}catch(const std::exception&){rejected=true;}
        if(invalid<4) {
            expect(writer.mutations>0 && rejected,"duplicate Part IDs/names, missing parents and cycles reject");
            expect(destination.findPart("keep")==existing && existing->isAttached(),"invalid Part links leave existing Parts intact");
        } else expect(!rejected && destination.getPartCount()==2,"valid Part fixture remains readable");
    }
    Serializer strings;strings.serialize_str("part name");strings.serialize_str("");
    auto reader=snapshotReader(strings);std::string name;
    reader->deserialize_string(name);expect(name=="part name","native string reader excludes the terminator from string length");
    reader->deserialize_string(name);expect(name.empty(),"native string reader replaces a prior value with empty text");
}
void invalidControllerSnapshots() {
    using namespace pdg;
    Sprite source,destination;
    auto* root=source.createPart("root");auto* middle=source.createPart("middle");auto* tip=source.createPart("tip");
    middle->setParentPart(root).setLocation(8,0);tip->setParentPart(middle).setLocation(8,0);
    root->setIKTarget(middle,tip,pdg::Point(10.125f,8.375f),partSpace_World,1,.875);
    auto* keep=destination.createPart("keep");
    for(int invalid=0;invalid<=4;++invalid) {
        SnapshotTestWriter writer;writer.setSendTags(false);bool space=false;
        writer.onWord=[&](uint32& n) {
            if(n==snapshotBits(10.125f)) {
                if(invalid==0){writer.replaceByte(writer.previousInteger,99);++writer.mutations;}
                if(invalid==2){n=snapshotBits(float(NAN));++writer.mutations;}
            }
            if(n==snapshotBits(8.375f) && invalid==1)space=true;
        };
        writer.onByte=[&](uint8& n) {if(space){n=99;space=false;++writer.mutations;}};
        writer.onDouble=[&](uint64& n) {if(invalid==3 && n==snapshotBits(.875)){n=snapshotBits(double(NAN));++writer.mutations;}};
        source.serialize(&writer);auto reader=snapshotReader(writer);bool rejected=false;
        try{destination.deserialize(reader.get());}catch(const std::exception&){rejected=true;}
        if(invalid<4) {
            expect(writer.mutations==1 && rejected,"invalid controller reference, space, target and influence reject");
            expect(destination.findPart("keep")==keep && keep->isAttached(),"invalid controller leaves existing Part graph intact");
        } else expect(!rejected && destination.findPart("root")->hasIKTarget(),"valid controller fixture remains readable");
    }
}
void partSnapshots() {
    using namespace pdg;
    for (bool tags : {false, true}) for (int mode : {serialization_Complete, serialization_ExternalReferences})
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    for (bool chipmunk : {false, true})
#else
    for (bool chipmunk : {false})
#endif
    {
#ifdef PDG_NO_GUI
        auto* source = createSpriteLayer(); auto* copy = createSpriteLayer();
#else
        auto* source = createSpriteLayer(nullptr); auto* copy = createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        source->setUseChipmunkPhysics(chipmunk); source->setGravity(0); source->setDamping(1);
#endif
        auto* sprite = source->createSprite();
        sprite->setLocation(pdg::Point(10, 20)); sprite->setScale(2, 3); sprite->setFlipX(true);
        auto* child = sprite->createPart("child"); auto* parent = sprite->createPart("parent");
        auto* driven = sprite->createPart("driven");
        const auto removedId = sprite->createPart("removed")->getId(); sprite->removePart(removedId);
        parent->setLocation(pdg::Point(5, 6)); child->setParentPart(parent).setLocation(pdg::Point(3, 4));
        child->setupPhysicsBody(2, 5).setMode(physicsBody_Kinematic);
        child->moveTo(8, 9, 1, linearTween); child->animate(.25); child->pauseSchedule(); child->wait(.375);
        driven->setParentPart(parent).setLocation(pdg::Point(8, 3));
        driven->setupPhysicsBody(3, 7).setVelocity(2, 3).setAngularVelocity(.4)
            .setDriveTarget(pdg::Point(-10, 45), 1, 9, 4);
        driven->physics.applyForce(Vector(2, 0), .5, .25);
#ifndef PDG_NO_GUI
        std::unique_ptr<Drawing> drawing(Drawing::create());
        delete drawing->addRect(pdg::Rect(1, 2, 11, 22), Attributes().fillColor(Color(1.f, 0.f, 0.f)));
        parent->setDrawing(*drawing); child->setDrawing(*drawing);
        drawing.reset(); // Parts retain artwork after the authoring wrapper is gone.
#endif
        Serializer writer; writer.setSendTags(tags); writer.setResourceMode(mode);
        const auto size = source->getSerializedSize(&writer); source->serialize(&writer);
        expect(writer.getDataSize() == size + (tags ? 3 : 0), "Part graph byte count includes shared Drawing storage");
        auto load = [&](uint32 length) {
            void* bytes = std::malloc(length); std::memcpy(bytes, writer.getDataPtr(), length);
            Deserializer reader(bytes, length); copy->deserialize(&reader);
        };
        auto* oldSprite = copy->createSprite(); auto* oldPart = oldSprite->createPart("retained"); oldPart->addRef();
        bool rejected = false; try { load(writer.getDataSize() - 1); } catch (const std::exception&) { rejected = true; }
        expect(rejected && copy->getNthSprite(0) == oldSprite && oldPart->isAttached(), "invalid Part graph preserves live Layer membership");
        load(writer.getDataSize());
        auto* restored = copy->getNthSprite(0);
        expect(!oldPart->isAttached(), "successful graph replacement detaches retained old Parts"); oldPart->release();
        expect(restored->getPartNames() == sprite->getPartNames(), "Part names and creation order survive");
        auto* a = restored->getPart(child->getId()); auto* b = restored->getPart(parent->getId());
        auto* c = restored->getPart(driven->getId());
        expect(a && b && c && a->getParentPart() == b && c->getParentPart() == b, "Part IDs and forward parent references restored");
        expect(restored->createPart("next")->getId() > removedId, "Part IDs removed before saving are not reused");
        expect(b->physics == PhysicsBody::NoPhysics && b->getBoneId() == boneId_None, "nonphysical unbound Parts stay unbound");
        expect(a->physics.getMode() == physicsBody_Kinematic && a->hasScheduledAnimations() && a->isSchedulePaused(), "kinematic Part restores its paused programming");
        near(a->getLocation().x, child->getLocation().x, "Part sampled local position");
        near(a->getTransform(partSpace_World).tx, child->getTransform(partSpace_World).tx, "Part affine hierarchy world position");
        expect(c->physics.getSolver() == (chipmunk ? physicsSolver_Chipmunk : physicsSolver_Basic), "Part solver follows restored Layer");
        expect(c->physics.isDriveEnabled(), "Part drive survives graph restore");
        near(c->physics.getMomentOfInertia(), 7, "Part moment of inertia");
        near(c->physics.getDriveState().maxForce, 9, "Part drive force limit");
#ifndef PDG_NO_GUI
        expect(a->hasContent() && b->hasContent(), "shared Part Drawing retained after load");
        near(a->getContentBounds().width(), 10, "Part Drawing local bounds");
#endif
        a->resumeSchedule(); child->resumeSchedule();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        SpriteManager::getSingletonInstance()->stepAnimationPhysics(250);
#endif
        source->animateLayer(250); copy->animateLayer(250);
        near(a->getLocation().x, child->getLocation().x, "Part tween resumes from its saved clock");
        near(c->physics.getState().x, driven->physics.getState().x, "Part drive resumes identically");
        near(c->physics.getVelocity().x, driven->physics.getVelocity().x, "Part active loads continue identically");
        cleanupLayer(copy); cleanupLayer(source);
    }
}



void invalidMountSnapshots() {
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* source=createSpriteLayer();auto* destination=createSpriteLayer();
#else
    auto* source=createSpriteLayer(nullptr);auto* destination=createSpriteLayer(nullptr);
#endif
    auto* a=source->createSprite();auto* b=source->createSprite();auto* c=source->createSprite();
    a->iid=500001;b->iid=500002;c->iid=500003;
    auto* ap=a->createPart("a")->attachSprite(b);
    auto* bp=b->createPart("b")->attachSprite(c);
    auto* keep=destination->createSprite();
    for(int invalid=0;invalid<=4;++invalid) {
        SnapshotTestWriter writer;writer.setSendTags(false);uint32 previous=0,beforePrevious=0;
        writer.onInteger=[&](uint32& value) {
            const uint32 original=value;
            if(beforePrevious==a->iid && previous==ap->getId() && value==b->iid) {
                if(invalid==0){writer.replaceByte(writer.lastInteger,99);++writer.mutations;}
                if(invalid==1){value=UINT32_MAX;++writer.mutations;}
            }
            if(beforePrevious==b->iid && previous==bp->getId() && value==c->iid) {
                if(invalid==2){value=b->iid;++writer.mutations;}
                if(invalid==3){value=a->iid;++writer.mutations;}
            }
            beforePrevious=previous;previous=original;
        };
        source->serialize(&writer);auto reader=snapshotReader(writer);bool rejected=false;
        try{destination->deserialize(reader.get());}catch(const std::exception&){rejected=true;}
        if(invalid<4) expect(writer.mutations==1 && rejected && destination->getNthSprite(0)==keep,
            "missing endpoints, duplicate mounts and Sprite cycles preserve the live graph");
        else expect(!rejected && destination->getNthSprite(0)->getPart(ap->getId())->getAttachedSprite(),"valid mount mutation fixture remains readable");
    }
    cleanupLayer(destination);cleanupLayer(source);
}

void mountSnapshots() {
    using namespace pdg;
    for (bool tags : {false, true}) for (int mode : {serialization_Complete, serialization_ExternalReferences})
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    for (bool chipmunk : {false, true})
#else
    for (bool chipmunk : {false})
#endif
    {
#ifdef PDG_NO_GUI
        auto* source = createSpriteLayer(); auto* copy = createSpriteLayer();
#else
        auto* source = createSpriteLayer(nullptr); auto* copy = createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        source->setUseChipmunkPhysics(chipmunk); source->setGravity(0); source->setDamping(1);
#endif
        auto* child = source->createSprite(); auto* tip = source->createSprite(); auto* host = source->createSprite();
        child->spriteId = 100; tip->spriteId = 200; host->spriteId = 300;
        host->setLocation(pdg::Point(10, 20)); host->setScale(2); host->setRotation(.2);
        auto* hand = host->createPart("hand"); hand->setLocation(pdg::Point(4, 5));
        auto* grip = child->createPart("grip"); grip->setLocation(pdg::Point(3, 1));
        child->setupPhysicsBody().setMode(physicsBody_Kinematic);
        auto* mount = hand->attachSprite(child, partPlacement_Snap, grip);
        auto* nested = child->createPart("tip")->attachSprite(tip, partPlacement_PreserveWorld);
        mount->setMovement(2, 0); nested->setSpin(.3);
        Serializer writer; writer.setSendTags(tags); writer.setResourceMode(mode);
        const auto size = source->getSerializedSize(&writer); source->serialize(&writer);
        expect(writer.getDataSize() == size + (tags ? 3 : 0), "Layer mount snapshot byte count");
        auto load = [&](uint32 length) {
            void* bytes = std::malloc(length); std::memcpy(bytes, writer.getDataPtr(), length);
            Deserializer reader(bytes, length); copy->deserialize(&reader);
        };
        auto* old = copy->createSprite();
        bool rejected = false; try { load(writer.getDataSize() - 1); } catch (const std::exception&) { rejected = true; }
        expect(rejected && copy->getNthSprite(0) == old, "truncated mount table leaves live Layer untouched");
        load(writer.getDataSize());
        auto* a = copy->getNthSprite(0); auto* b = copy->getNthSprite(1); auto* c = copy->getNthSprite(2);
        expect(a->spriteId == 100 && b->spriteId == 200 && c->spriteId == 300, "mount restoration preserves child-before-host draw order");
        auto* m = c->getPart(mount->getId()); auto* n = a->getPart(nested->getId());
        expect(m->getAttachedSprite() == a && a->getAttachmentPart() == m, "restored mount links both owners");
        expect(n->getAttachedSprite() == b && b->getAttachmentPart() == n, "nested mount links survive");
        near(a->getLocation().x, child->getLocation().x, "restored grip offset retains child pose");
        near(b->getLocation().x, tip->getLocation().x, "preserve-world nested mount retains pose");
        expect(a->physics.getSolver() == (chipmunk ? physicsSolver_Chipmunk : physicsSolver_Basic), "mounted child joins restored Layer solver");
        rejected = false; try { a->physics.setVelocity(1, 0); } catch (const std::logic_error&) { rejected = true; }
        expect(rejected, "restored mount continues to reject competing physical commands");
        rejected = false; try { Serializer raw; c->serialize(&raw); } catch (const std::runtime_error&) { rejected = true; }
        expect(rejected, "standalone Sprite save rejects mounts outside a Layer graph record");
        hand->setLocation(pdg::Point(8, 9)); c->findPart("hand")->setLocation(pdg::Point(8, 9));
        mount->animate(.25); m->animate(.25); nested->animate(.25); n->animate(.25);
        near(a->getLocation().x, child->getLocation().x, "restored animated mount follows its host");
        near(a->getLocation().y, child->getLocation().y, "restored child grip frame stays aligned");
        near(b->getRotation(), tip->getRotation(), "restored nested mount programming continues");
        c->addRef(); copy->removeSprite(c);
        expect(copy->getNthSprite(0) == nullptr && a->getLayer() == nullptr, "restored mounted group detaches together");
        copy->addSprite(c); c->release();
        expect(copy->hasSprite(a) && copy->hasSprite(b), "restored mounted group transfers together");
        cleanupLayer(copy); cleanupLayer(source);
    }
}

void spriteFrameSnapshots() {
    using namespace pdg;
    Sprite unsupported;
    unsupported.createPart("unsupported mount")->attachSprite(new Sprite);
    for (int mode : {serialization_Complete,serialization_ExternalReferences}) {
        Serializer writer;writer.setResourceMode(mode);
        bool rejected=false;
        try { unsupported.serialize(&writer); } catch (const std::runtime_error&) { rejected=true; }
        expect(rejected && writer.getDataSize()==0,"unsupported Sprite graph rejects before writing a raw record");
    }
#ifdef PDG_NO_GUI
    auto* image=new ImageImpl();
#else
    auto* image=new ImageOpenGL();
#endif
    image->addRef();
    image->initEmpty(256,2,32);image->setNumFrames(256);
    std::memset(image->data,200,2048);
    Sprite source;
    source.addFramesImage(image);
    source.setFrameCollisionMask(image,image);
    image->release(); // source owns its images and masks
    source.setLocation(pdg::Point(12,34));source.setScale(2,3);
    source.startFrameAnimation(4,10,2);
    expect(source.mFirstFrame==10 && source.mLastFrame==11,"frame count selects an inclusive two-frame range");
    source.startFrameAnimation(4,10,1);
    expect(!source.mSpriteAnimating && source.getCurrentFrame()==10,"one-frame selection stops prior playback");
    source.startFrameAnimation(4);step(source,125);
    near(source.mCurrFramePrecise,.5,"source has a fractional frame cursor");
    for (bool tags : {false,true}) for (int mode : {serialization_Complete,serialization_ExternalReferences}) {
        Serializer writer;writer.setSendTags(tags);writer.setResourceMode(mode);
        const auto size=source.getSerializedSize(&writer);source.serialize(&writer);
        expect(writer.getDataSize()==size+(tags ? 3 : 0),"Sprite record sizes include shared image and mask references");
        void* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
        Deserializer reader(bytes,writer.getDataSize());
        Sprite copy;copy.deserialize(&reader);
        expect(copy.getFrameCount()==256,"maximum 256-frame Sprite snapshot does not wrap to zero");
        expect(copy.mFrames[0].image==copy.mFrames[255].image && copy.mFrames[255].collisionMask==copy.mFrames[0].image,"Sprite images and masks retain shared identity");
        expect(copy.mFrames[255].imageFrameNum==255,"strip frame selection round-trips");
        expect(copy.mFrames[0].image->getPixel(0,0)==image->getPixel(0,0),"Sprite snapshot restores embedded artwork");
        near(copy.getLocation().x,12,"Sprite transforms accompany restored artwork");
        near(copy.mCurrFramePrecise,.5,"fractional playback phase is preserved");
        step(copy,125);expect(copy.getCurrentFrame()==1,"restored frame playback continues from saved phase");
        // Replacing populated frames releases their prior images and masks.
        void* again=std::malloc(writer.getDataSize());std::memcpy(again,writer.getDataPtr(),writer.getDataSize());
        Deserializer second(again,writer.getDataSize());copy.deserialize(&second);
        expect(copy.getFrameCount()==256,"populated Sprite accepts a replacement frame snapshot");
    }
}


void layerPartMotionUpdates() {
    using namespace pdg;
    for(bool tags:{false,true}) for(int prefix=0;prefix<8;++prefix) {
#ifndef PDG_NO_GUI
        auto* source=createSpriteLayer(nullptr);auto* copy=createSpriteLayer(nullptr);
#else
        auto* source=createSpriteLayer();auto* copy=createSpriteLayer();
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        source->setUseChipmunkPhysics(false);copy->setUseChipmunkPhysics(false);
#endif
        auto* sprite=source->createSprite();
        auto* root=sprite->createPart("root");auto* middle=sprite->createPart("middle");
        auto* tip=sprite->createPart("tip");auto* tween=sprite->createPart("tween");
        middle->setParentPart(root).setLocation(10,0);tip->setParentPart(middle).setLocation(8,0);
#ifndef PDG_NO_GUI
        std::unique_ptr<Drawing> drawing(Drawing::create());
        delete drawing->addRect(pdg::Rect(0,-1,10,1),Attributes());
        root->setDrawing(*drawing);middle->setDrawing(*drawing);
#endif
        Serializer initial;initial.setSendTags(tags);source->serialize(&initial);
        auto reader=snapshotReader(initial);copy->deserialize(reader.get());
        auto* restored=copy->getNthSprite(0);
        auto* savedRoot=restored->findPart("root");auto* savedMiddle=restored->findPart("middle");
        auto* savedTip=restored->findPart("tip");auto* savedTween=restored->findPart("tween");
        source->setSerializationFlags(ser_Update);
        for(int frame=0;frame<3;++frame) {
            root->solveIK(middle,tip,pdg::Point(10+frame,6-frame));
            tween->cancelSchedule().setLocation(2,3).moveTo(12,13,1,linearTween).andThen().rotateBy(1,.5);
            tween->animate(.25);
            Serializer update;update.setSendTags(tags);uint32 expected=0;
            for(int i=0;i<prefix;++i){expected+=update.sizeof_bool(i%2);update.serialize_bool(i%2);}
            expected+=source->getSerializedSize(&update);source->serialize(&update);
            expected+=update.sizeof_bool(true);update.serialize_bool(true);
            expect(update.getDataSize()==expected+(tags?3:0),"Part updates have exact sizes at every packed boolean offset");
            auto input=snapshotReader(update);
            for(int i=0;i<prefix;++i)expect(input->deserialize_bool()==bool(i%2),"Part update prefix");
            copy->deserialize(input.get());expect(input->deserialize_bool(),"Part update suffix");
            expect(restored==copy->getNthSprite(0) && savedRoot==restored->findPart("root") &&
                savedMiddle==restored->findPart("middle") && savedTip==restored->findPart("tip"),"updates preserve Sprite and Part identity");
            expect(savedTip->getParentPart()==savedMiddle,"updates preserve parent relationships");
            const auto tipPose=tip->getTransform(partSpace_World),savedPose=savedTip->getTransform(partSpace_World);
            near(savedPose.tx,tipPose.tx,"incremental updates transfer solved IK x");
            near(savedPose.ty,tipPose.ty,"incremental updates transfer solved IK y");
            near(savedTween->getLocation().x,tween->getLocation().x,"sampled Part tween position transfers");
            savedTween->animate(.25);near(savedTween->getLocation().x,7,"restored tween points to receiving Part storage");
            near(tween->getLocation().x,4.5,"advancing receiving Part does not modify source");
            savedTween->animate(1.25);near(savedTween->getRotation(),1,"chained Part rotation resumes after update");
        }
        // Same count but different IDs must reject; no staged Part poses are adopted.
        const auto angle=savedRoot->getRotation();root->setRotation(angle+.25);
        const auto removed=tip->getId();sprite->removePart(removed);sprite->createPart("replacement");
        Serializer bad;source->serialize(&bad);auto input=snapshotReader(bad);bool rejected=false;
        try{copy->deserialize(input.get());}catch(const std::runtime_error&){rejected=true;}
        expect(rejected,"Part topology changes require another initial snapshot");
        near(savedRoot->getRotation(),angle,"bad Part identity does not partially install Part updates");
        cleanupLayer(copy);cleanupLayer(source);
    }
}

void layerInitialSnapshots() {
    using namespace pdg;
    // Reused allocator memory must not turn default event flags into physics
    // flags when an optimized headless build packs the snapshot bitfield.
    alignas(SpriteLayer) unsigned char storage[sizeof(SpriteLayer)];
    std::memset(storage, 0xff, sizeof(storage));
    auto* dirty = new (storage) SpriteLayer;
    Serializer writer; dirty->serialize(&writer); dirty->~SpriteLayer();
    auto input = snapshotReader(writer);
    SpriteLayer restored; restored.deserialize(input.get());
    expect(!restored.mWantsMouseOver && !restored.mWantsClicks,
        "default Layer event flags survive snapshots from reused memory");
    for (bool chipmunk : {false,true}) for (bool tags : {false,true})
    for (int mode : {serialization_Complete,serialization_ExternalReferences}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if (chipmunk) continue;
#endif
#ifdef PDG_NO_GUI
        auto* source=createSpriteLayer();auto* destination=createSpriteLayer();
        auto* image=new ImageImpl();
#else
        auto* source=createSpriteLayer(nullptr);auto* destination=createSpriteLayer(nullptr);
        auto* image=new ImageOpenGL();
        source->setOrigin(pdg::Point(40,50));source->setZoom(2);
        source->zoomTo(3,1,linearTween);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        source->setUseChipmunkPhysics(chipmunk);source->setGravity(0);source->setDamping(1);
#endif
        source->layerId=12345;
        source->mDoneFadingInAt=OS::getMilliseconds()+1000;
        source->setLocation(pdg::Point(12,34));source->setRotation(.3);source->setScale(2,3);
        source->changeScaleTo(4,5,1,linearTween);source->animate(.25);source->pauseSchedule();source->wait(.125);
        image->addRef();image->initEmpty(4,2,32);image->setNumFrames(2);std::memset(image->data,190,32);
        auto* first=source->createSprite();auto* second=source->createSprite();
        first->spriteId=101;second->spriteId=202;first->setFlipX(true);second->setFlipY(true);
        first->addFramesImage(image);second->addFramesImage(image);image->release();
        first->startFrameAnimation(1);step(*first,250);second->setLocation(pdg::Point(7,8));
        second->setupPhysicsBody(2,4).setDriveTarget(pdg::Point(20,8),.4,12,8);
        Serializer writer;writer.setSendTags(tags);writer.setResourceMode(mode);
        const auto size=source->getSerializedSize(&writer);source->serialize(&writer);
        expect(writer.getDataSize()==size+(tags ? 3 : 0),"initial Layer size includes shared Sprite artwork once");
        auto load=[&](size_t bytes) {
            void* data=std::malloc(bytes);std::memcpy(data,writer.getDataPtr(),bytes);
            Deserializer reader(data,bytes);destination->deserialize(&reader);
        };
        destination->setSerializationFlags(ser_Positions);
        auto* original=destination->createSprite();original->spriteId=303;
        destination->setScale(9);original->addRef();
        bool rejected=false;try{load(writer.getDataSize()-1);}catch(const std::exception&){rejected=true;}
        expect(rejected && destination->getNthSprite(0)==original,"truncated Layer snapshot preserves existing membership");
        near(destination->getScale().x,9,"invalid Layer leaves its transform intact");
        expect(destination->mSerFlags==ser_Positions,"failed Layer load preserves the selected update flags");
        load(writer.getDataSize());
        expect(original->getLayer()==nullptr,"replaced retained Sprite is detached");original->release();
        auto* a=destination->getNthSprite(0);auto* b=destination->getNthSprite(1);
        expect(a && b && !destination->getNthSprite(2),"initial Layer creates its complete ordered Sprite list");
        expect(a->spriteId==101 && b->spriteId==202 && destination->layerId==12345,"Layer and Sprite IDs round-trip");
        expect(a->mFrames[0].image==b->mFrames[0].image,"separate sprites retain one shared image");
        expect(a->isFlippedX() && b->isFlippedY(),"Sprite reflection flags survive Layer snapshots");
        near(a->mCurrFramePrecise,.25,"Layer snapshot preserves fractional frame phase");
        expect(b->physics.isDriveEnabled(),"Layer snapshot preserves an active drive");
        expect(b->physics.getSolver()==(chipmunk ? physicsSolver_Chipmunk : physicsSolver_Basic),"restored bodies join the destination solver after validation");
        near(b->physics.getDriveState().maxForce,12,"Layer drive preserves force limit");
        near(destination->getScale().x,2.5,"Layer snapshot restores sampled tween value");
        expect(destination->mDoneFadingInAt>OS::getMilliseconds() && destination->mDoneFadingOutAt==0,"Layer completion timers retain remaining time and inactive state");
        expect(destination->isSchedulePaused() && destination->hasScheduledAnimations(),"Layer snapshot preserves paused tween state");
#ifndef PDG_NO_GUI
        near(destination->getOrigin().x,40,"full Layer records include the draw origin");
        near(destination->getZoom(),2.25,"full Layer records include current zoom");
#endif
        destination->resumeSchedule();destination->animate(.75);
        near(destination->getScale().x,4,"restored tween pointers belong to the destination Layer");
#ifndef PDG_NO_GUI
        near(destination->getZoom(),3,"restored zoom tween completes on destination");
#endif
        expect(destination->mSerFlags==ser_Positions,"successful load preserves caller's update selection");
        // Loading into an empty layer must work as well as replacing membership.
        destination->removeAllSprites();load(writer.getDataSize());
        expect(destination->getNthSprite(1)!=nullptr,"empty Layer accepts initial data");
        cleanupLayer(destination);cleanupLayer(source);
    }
}

void layerTweenSnapshots() {
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
    layer->setSerializationFlags(ser_Update);
    layer->setScale(1,2);layer->changeScaleTo(3,4,1,linearTween);
    layer->changeMovementTo(8,0,1,linearTween);layer->rotateTo(1,1,linearTween,rotationDirection_Clockwise);
    layer->animate(.25);layer->pauseSchedule();layer->wait(.125);
    Serializer data;data.setSendTags(false);const auto size=layer->getSerializedSize(&data);layer->serialize(&data);
    expect(data.getDataSize()==size,"Layer tween snapshot byte count");
    void* bytes=std::malloc(data.getDataSize());std::memcpy(bytes,data.getDataPtr(),data.getDataSize());
    Deserializer reader(bytes,data.getDataSize());
    layer->cancelSchedule();layer->setScale(9);layer->resumeSchedule();layer->deserialize(&reader);
    expect(layer->hasScheduledAnimations() && layer->isSchedulePaused(),"Layer snapshot restores paused tracks");
    near(layer->getScale().x,1.5,"Layer restores sampled scale");
    layer->animate(.5);near(layer->getScale().x,1.5,"Layer paused snapshot holds scale");
    layer->resumeSchedule();layer->animate(.75);near(layer->getScale().x,3,"Layer resumes saved scale curve");
    near(layer->getMovement().x,8,"Layer resumes eased movement rate");near(layer->getRotation(),1,"Layer resumes rotation route");
    layer->changeScaleTo(5,5,.125,linearTween);layer->animate(.1);near(layer->getScale().x,3,"Layer restores pending wait");
    layer->animate(.15);near(layer->getScale().x,5,"Layer applies delayed scale target");
    cleanupLayer(layer);
}

void partWorld() {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
    layer->setUseChipmunkPhysics(true);layer->enableCollisions();layer->setGravity(0);layer->setDamping(1);
    auto* sprite=layer->createSprite();sprite->addRef();
    auto* part=sprite->createPart("world body");part->setLocation(pdg::Point(10,20));
    auto& body=part->setupPhysicsBody(2,3);body.addRef();
    expect(body.getSolver()==physicsSolver_Chipmunk,"unbound Part joins Chipmunk without a root body");
    expect(sprite->physics==PhysicsBody::NoPhysics,"Part world participation creates no root body");
    body.applyImpulse(Vector(8,0));
    SpriteManager::getSingletonInstance()->stepAnimationPhysics(250);step(*sprite,250);
    near(part->getTransform(partSpace_World).tx,11,"world alone integrates physical Part position");
    near(body.getVelocity().x,4,"Part impulse reaches world solver");
    layer->removeSprite(sprite);expect(body.getSolver()==physicsSolver_Basic,"layer removal detaches retained Part solver");
    part->animate(.25);near(part->getTransform(partSpace_World).tx,12,"detached Part resumes basic free motion");
    sprite->release();expect(!body.isAttached(),"owner destruction detaches retained Part body");
    body.step(.25);near(body.getState().x,13,"retained body safely outlives its Part");body.release();
    cleanupLayer(layer);
#endif
}
#include "part-ik-tests.inc"

void partIK() {
    using namespace pdg;
    Sprite sprite;sprite.setLocation(pdg::Point(10,20));sprite.setScale(2,-3);
    auto* root=sprite.createPart("root");auto* middle=sprite.createPart("middle");auto* tip=sprite.createPart("tip");
    middle->setParentPart(root);tip->setParentPart(middle);
    middle->setLocation(pdg::Point(10,0));tip->setLocation(pdg::Point(8,0));
    expect(root->solveIK(middle,tip,pdg::Point(30,-4)),"bone-free Part IK reaches world target through reflected nonuniform ancestor");
    auto end=tip->getTransform(partSpace_World);near(end.tx,30,"Part IK world x");near(end.ty,-4,"Part IK world y");
    expect(root->getBoneId()==boneId_None && middle->getBoneId()==boneId_None,"Part IK does not invent bones");
    expect(root->solveIK(middle,tip,pdg::Point(10,8),partSpace_Sprite,-1),"opposite elbow side reaches same target");
    expect(!root->solveIK(middle,tip,pdg::Point(100,0),partSpace_Local),"unreachable Part target clamps without stretching");
    root->setScale(-1,1);expect(root->solveIK(middle,tip,pdg::Point(8,8),partSpace_Local),"reflected root IK");
    const float angle=root->getRotation();bool rejected=false;
    try{root->solveIK(tip,middle,pdg::Point(1,2));}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected && root->getRotation()==angle,"invalid IK topology preserves current joints");
    auto& body=middle->setupPhysicsBody();rejected=false;
    try{root->solveIK(middle,tip,pdg::Point(1,2));}catch(const std::logic_error&){rejected=true;}
    expect(rejected && root->getRotation()==angle,"direct IK cannot overwrite dynamic physics");
    body.setMode(physicsBody_Kinematic);expect(root->solveIK(middle,tip,pdg::Point(8,8),partSpace_Local),"IK can target a kinematic Part");
}
void scheduledPartIK() {
    using namespace pdg;
    for (bool chipmunk : {false, true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if (chipmunk) continue;
#endif
#ifdef PDG_NO_GUI
        auto* layer = createSpriteLayer();
#else
        auto* layer = createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(chipmunk); layer->setGravity(0); layer->setDamping(1);
#endif
        auto* sprite = layer->createSprite();
        // Deliberately create the descendants first to exercise hierarchy ordering.
        auto* tip = sprite->createPart("tip");
        auto* middle = sprite->createPart("middle");
        auto* root = sprite->createPart("root");
        auto* end = sprite->createPart("end");
        middle->setParentPart(root); tip->setParentPart(middle); end->setParentPart(tip);
        middle->setLocation(pdg::Point(10,0)); tip->setLocation(pdg::Point(8,0)); end->setLocation(pdg::Point(2,0));
        middle->setupPhysicsBody().setMode(physicsBody_Kinematic);
        struct LocalPose : IAnimationHelper {
            int calls = 0;
            bool animate(AnimatedBase* owner, double) override { ++calls; owner->setRotation(.75f); return true; }
            bool ownedByAnimated() override { return false; }
        } helper;
        middle->addAnimationHelper(&helper);
        root->setIKTarget(middle, tip, pdg::Point(10,8));
        expect(root->hasIKTarget() && !root->isIKTargetReached(), "target registers without solving early");
        sprite->setMovement(2,0);
        for (int i=0;i<3;++i) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            if (chipmunk) SpriteManager::getSingletonInstance()->stepAnimationPhysics(100);
#endif
            step(*sprite,100);
            expect(root->isIKTargetReached() && root->getIKError().empty(), "scheduled controller reaches moving owner's fixed world target");
            near(tip->getTransform(partSpace_World).tx,10,"scheduled IK world x after physical publication");
            near(tip->getTransform(partSpace_World).ty,8,"scheduled IK world y after physical publication");
            near(middle->physics.getState().rotation,std::atan2(middle->getTransform(partSpace_World).b,middle->getTransform(partSpace_World).a),"kinematic body receives the final IK rotation");
        }
        expect(helper.calls==3,"local animation helpers execute once per tick before IK");
        bool rejected=false;
        try { middle->setIKTarget(tip,end,pdg::Point(10,8)); } catch (const std::logic_error&) { rejected=true; }
        expect(rejected && !middle->hasIKTarget(),"overlapping rotation writers reject atomically");
        const float angle=root->getRotation();
        rejected=false;
        try { root->setIKTarget(tip,middle,pdg::Point(1,2)); } catch (const std::invalid_argument&) { rejected=true; }
        expect(rejected && root->hasIKTarget() && root->getRotation()==angle,"invalid replacement preserves active controller and pose");
        middle->removeAnimationHelper(&helper);
        tip->setParentPart(root);step(*sprite,100);
        expect(!root->isIKTargetReached() && !root->getIKError().empty(),"invalid topology reports a held controller error");
        near(root->getRotation(),angle,"invalid solve preserves rotations");
        tip->setParentPart(middle);step(*sprite,100);
        expect(root->isIKTargetReached() && root->getIKError().empty(),"valid topology resumes the controller");
        layer->setSerializationFlags(ser_Full);
        root->setIKTarget(middle,tip,pdg::Point(10.00025f,8.000125f));root->animate(0);
        for (bool tags : {false,true}) for (int mode : {serialization_Complete,serialization_ExternalReferences}) {
            Serializer writer; writer.setSendTags(tags); writer.setResourceMode(mode);
            const auto expectedSize = sprite->getSerializedSize(&writer); sprite->serialize(&writer);
            expect(expectedSize + (tags ? 3 : 0) == writer.getDataSize(), "controller snapshot exact size including stream header");
            void* bytes = std::malloc(writer.getDataSize()); std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
            Deserializer reader(bytes,writer.getDataSize()); Sprite copy; copy.deserialize(&reader);
            auto* copiedRoot = copy.findPart("root"); auto* copiedTip = copy.findPart("tip");
            expect(copiedRoot->hasIKTarget() && copiedRoot->isIKTargetReached(), "controller record preserves active/reached state");
            copy.moveBy(1,1); step(copy,100);
            expect(copiedRoot->isIKTargetReached(), "restored controller resolves forward Part references and remains active");
            near(copiedTip->getTransform(partSpace_World).tx,10.00025,"restored controller preserves fractional target x");
            near(copiedTip->getTransform(partSpace_World).ty,8.000125,"restored controller preserves fractional target y");
        }
        root->clearIKTarget();expect(!root->hasIKTarget() && !root->isIKTargetReached(),"clear retires controller status");
        root->setRotation(.2f);step(*sprite,100);near(root->getRotation(),.2,"cleared controller no longer writes joints");
        root->setIKTarget(middle,tip,pdg::Point(10,8));
        sprite->removePart(tip->getId());step(*sprite,100);
        expect(!root->getIKError().empty(),"removed tip produces an error instead of a stale pointer");
        cleanupLayer(layer);
    }
}
void kinematicMounts() {
    using namespace pdg;
    for (bool chipmunk : {false, true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if (chipmunk) continue;
#endif
#ifdef PDG_NO_GUI
        auto* layer=createSpriteLayer();
#else
        auto* layer=createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(chipmunk);layer->setGravity(0);layer->setDamping(1);
#endif
        auto* child=layer->createSprite();auto* host=layer->createSprite();
        child->setupPhysicsBody().setMode(physicsBody_Kinematic);
        child->physics.setVelocity(100,0).setAngularVelocity(10);
        auto* socket=host->createPart("hand");socket->setLocation(pdg::Point(3,0));
        auto* mount=socket->attachSprite(child);
        near(child->physics.getVelocity().x,0,"mount clears competing physical velocity");
        near(child->physics.getAngularVelocity(),0,"mount clears competing angular velocity");
        near(child->physics.getState().x,3,"mount sets physical world placement");
        bool rejected=false;
        try{child->physics.setMode(physicsBody_Dynamic);}catch(const std::logic_error&){rejected=true;}
        expect(rejected && child->physics.getMode()==physicsBody_Kinematic,"mounted body cannot become a competing dynamic writer");
        rejected=false;try{child->physics.teleport(pdg::Point(99,0),0);}catch(const std::logic_error&){rejected=true;}
        expect(rejected,"mounted body rejects direct physical teleport");near(child->physics.getState().x,3,"rejected teleport is atomic");
        rejected=false;try{child->physics.setVelocity(10,0);}catch(const std::logic_error&){rejected=true;}
        expect(rejected,"mounted body rejects competing free velocity");
        struct Counter : IAnimationHelper {
            int count=0;double seconds=0;
            bool animate(AnimatedBase*,double elapsed) override {++count;seconds+=elapsed;return true;}
            bool ownedByAnimated() override {return false;}
        } counter;
        host->addAnimationHelper(&counter);
        host->setMovement(8,0);mount->setMovement(4,0);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        struct Probe {cpBody* body;double x=0,velocity=0;} probe{child->mBody};
        if(chipmunk)cpSpaceAddPostStepCallback(layer->getSpace(),[](cpSpace*,void* key,void*) {
            auto* probe=static_cast<Probe*>(key);probe->x=cpBodyGetPosition(probe->body).x;
            probe->velocity=cpBodyGetVelocity(probe->body).x;
        },&probe,nullptr);
        if(chipmunk)SpriteManager::getSingletonInstance()->stepAnimationPhysics(250);
#endif
        layer->animateLayer(250);
        near(child->getLocation().x,6,"mounted child follows root and Part motion once");
        near(child->physics.getState().x,6,"mounted body agrees with its final Sprite frame");
        expect(counter.count==1,"pre-solve preparation does not execute helpers twice");near(counter.seconds,.25,"helper receives seconds once per tick");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if(chipmunk){near(probe.x,6,"world solve reaches this tick's mounted target");near(probe.velocity,12,"world sees mounted sweep velocity for contacts");}
#endif
        host->stopMovement();mount->stopMovement();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if(chipmunk)SpriteManager::getSingletonInstance()->stepAnimationPhysics(250);
#endif
        layer->animateLayer(250);near(child->physics.getState().x,6,"stopped mounting target has no residual sweep velocity");
        expect(counter.count==2,"next step executes helpers once again");
        mount->detachSprite();child->physics.setMode(physicsBody_Dynamic).applyImpulse(Vector(2,0));
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if(chipmunk)SpriteManager::getSingletonInstance()->stepAnimationPhysics(250);
#endif
        layer->animateLayer(250);near(child->physics.getState().x,6.5,"detached mounted body resumes dynamic motion");
        host->removeAnimationHelper(&counter);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if (chipmunk) {
            child->physics.setMode(physicsBody_Kinematic);
            socket->attachSprite(child);host->setMovement(8,0);host->addRef();
            cpSpaceAddPostStepCallback(layer->getSpace(),[](cpSpace*,void* key,void*) {
                auto* host=static_cast<Sprite*>(key);host->getLayer()->removeSprite(host);
            },host,nullptr);
            SpriteManager::getSingletonInstance()->stepAnimationPhysics(250);
            expect(!host->getLayer() && child->physics.getSolver()==physicsSolver_Basic,
                   "post-step removal detaches a mounted kinematic group");
            near(child->physics.getVelocity().x,0,"post-step removal does not retain temporary sweep velocity");
            const auto x=host->getLocation().x;step(*host,250);
            near(host->getLocation().x,x+2,"off-layer stepping does not consume an obsolete prepared frame");
            host->release();
        }
#endif
        cleanupLayer(layer);
    }
}

void physicalHierarchy() {
    using namespace pdg;
    for (bool chipmunk : {false, true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if (chipmunk) continue;
#endif
#ifdef PDG_NO_GUI
        auto* layer = createSpriteLayer();
#else
        auto* layer = createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(chipmunk);layer->setGravity(0);layer->setDamping(1);
#endif
        auto* sprite = layer->createSprite();
        // Deliberately create children before their parents.
        auto* child = sprite->createPart("dynamic child");
        auto* parent = sprite->createPart("parent");
        child->setParentPart(parent);child->setLocation(pdg::Point(4,5));
        auto& body = child->setupPhysicsBody();body.setVelocity(2,0);
        auto* kinematic = sprite->createPart("kinematic");kinematic->setParentPart(parent);
        kinematic->setLocation(pdg::Point(2,3));kinematic->setupPhysicsBody().setMode(physicsBody_Kinematic);
        parent->setMovement(8,0);
        auto tick = [&](unsigned ms) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            if (chipmunk) SpriteManager::getSingletonInstance()->stepAnimationPhysics(ms);
#endif
            step(*sprite,ms);
        };
        tick(250);
        near(child->getTransform(partSpace_World).tx,4.5,"parent programming does not displace a dynamic child");
        near(body.getState().x,4.5,"dynamic body integrates exactly once");
        near(kinematic->physics.getState().x,4,"kinematic body follows changed parent frame");
        near(kinematic->getLocation().x,2,"kinematic child keeps its local offset");
        parent->stopMovement();sprite->setLocation(pdg::Point(100,200));
        near(child->getTransform(partSpace_World).tx,4.5,"immediate root movement preserves dynamic world position");
        near(child->getTransform(partSpace_World).ty,5,"immediate root movement preserves dynamic world height");
        near(kinematic->physics.getState().x,104,"immediate root movement updates kinematic world target");
        parent->setRotation(.5);parent->setScale(2,-3);
        near(child->getTransform(partSpace_World).tx,4.5,"rotated reflected ancestors preserve dynamic world position");
        near(child->getTransform(partSpace_World).ty,5,"rotated reflected ancestors preserve dynamic world height");
        auto* physicalParent = sprite->createPart("physical parent");
        child->removePhysicsBody();child->setParentPart(physicalParent);child->setLocation(pdg::Point(4,0));
        auto& childBody=child->setupPhysicsBody();childBody.setVelocity(2,0);
        physicalParent->setupPhysicsBody().setVelocity(8,0);
        tick(250);
        near(child->getTransform(partSpace_World).tx,104.5,"parent and child bodies publish in hierarchy order");
        near(physicalParent->getTransform(partSpace_World).tx,102,"physical parent integrates once");
        auto* collapsed=sprite->createPart("collapsed artwork");collapsed->setScale(0,1);collapsed->setRotation(.3);
        collapsed->setupPhysicsBody();near(collapsed->physics.getState().rotation,.3,"local zero artwork scale does not invalidate the parent physics frame");
        collapsed->setScale(-2,1);
        near(collapsed->physics.getState().rotation,.3-3.14159265358979323846,"reflected local axis updates physical orientation");
        auto* programmed=sprite->createPart("programmed");
        programmed->setMovement(20,0);programmed->wait(.5);
        programmed->setupPhysicsBody();
        near(programmed->getMovement().x,0,"body creation stops rates even with a pending wait");
        programmed->physics.setMode(physicsBody_Kinematic);
        programmed->moveTo(pdg::Point(20,0),1);programmed->setMovement(5,0);
        programmed->physics.setMode(physicsBody_Dynamic);
        expect(!programmed->hasScheduledAnimations(),"switch to dynamic cancels competing spatial targets");
        near(programmed->getMovement().x,0,"switch to dynamic cancels programmed movement");
        cleanupLayer(layer);
    }
}

void attachmentLayers() {
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* first = createSpriteLayer();
    auto* second = createSpriteLayer();
#else
    auto* first = createSpriteLayer(nullptr);
    auto* second = createSpriteLayer(nullptr);
#endif
    auto* child = first->createSprite();
    auto* host = first->createSprite();
    auto* grandchild = first->createSprite();
    host->addRef(); child->addRef(); grandchild->addRef();
    host->setLocation(pdg::Point(20,30));
    auto* socket = host->createPart("hand"); socket->setLocation(pdg::Point(4,5));
    auto* mount = socket->attachSprite(child);
    auto* tip = child->createPart("tip"); tip->setLocation(pdg::Point(7,0));
    auto* nested = tip->attachSprite(grandchild);
    auto* physical = child->createPart("free body");
    auto& body = physical->setupPhysicsBody();
    const auto solver = body.getSolver();
    child->moveBehind(host);
    expect(child->getAttachmentPart() == mount && body.getSolver() == solver,
           "draw-order change preserves mount and solver");
    expect(first->getNthSprite(0) == child, "attached child retains independent draw order");
    bool rejected = false;
    try { first->removeSprite(child); } catch (const std::logic_error&) { rejected = true; }
    expect(rejected && first->hasSprite(child), "independent removal rejects without changing membership");
    rejected = false;
    try { second->addSprite(grandchild); } catch (const std::logic_error&) { rejected = true; }
    expect(rejected && first->hasSprite(grandchild) && !second->hasSprite(grandchild),
           "independent nested transfer rejects atomically");
    first->removeSprite(host);
    expect(!first->getNthSprite(0) && !host->getLayer() && !child->getLayer() && !grandchild->getLayer(),
           "host removal removes its whole mounting tree");
    expect(mount->getAttachedSprite() == child && nested->getAttachedSprite() == grandchild,
           "off-layer mounts retain both levels");
    expect(body.getSolver() == physicsSolver_Basic, "off-layer Part body detaches to basic");
    host->setLocation(pdg::Point(100,200));
    near(grandchild->getLocation().x,111,"off-layer nested placement follows host immediately");
    second->addSprite(host);
    expect(second->hasSprite(child) && second->hasSprite(grandchild), "reentry inserts all descendants");
    expect(body.getSolver() == solver, "reentry reconnects Part solver before the next tick");
    near(grandchild->getLocation().x,111,"reentry preserves layer-coordinate placement");
    first->addSprite(host);
    expect(first->hasSprite(grandchild) && !second->getNthSprite(0), "direct host transfer carries its group");
    first->removeAllSprites();
    expect(!first->getNthSprite(0) && mount->getAttachedSprite()==child, "bulk removal preserves retained group");
    second->addSprite(host); child->moveBehind(host);
    cleanupLayer(second);
    expect(!host->getLayer() && !child->getLayer() && mount->getAttachedSprite()==child,
           "layer destruction handles child-before-host ordering and retained group");
    host->release();
    expect(child->getAttachmentPart()==nullptr && nested->getAttachedSprite()==grandchild,
           "host destruction releases only its own mounting relationship");
    child->release();
    expect(grandchild->getAttachmentPart()==nullptr,"nested owner destruction clears child backlink");
    grandchild->release(); cleanupLayer(first);
}

void partAttachments() {
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    layer->setUseChipmunkPhysics(false);
#endif
    auto* child=layer->createSprite();auto* host=layer->createSprite();
    host->setLocation(pdg::Point(10,20));host->setScale(2);
    auto* socket=host->createPart("socket");socket->setLocation(pdg::Point(4,5));
    auto* grip=child->createPart("grip");grip->setLocation(pdg::Point(3,0));
    auto* mount=socket->attachSprite(child,partPlacement_Snap,grip);
    expect(child->getAttachmentPart()==mount && mount->getAttachedSprite()==child,"attachment identity in both directions");
    near(child->getLocation().x,12,"snap aligns child mounting frame with host socket");
    near(child->getScale().x,2,"mount inherits host scale");
    mount->setMovement(4,0);step(*host,500);near(child->getLocation().x,16,"animated mounting Part drives child root");
    bool rejected=false;try{child->moveTo(pdg::Point(99,0));}catch(const std::logic_error&){rejected=true;}
    expect(rejected,"attached root rejects competing transform setter");near(child->getLocation().x,16,"rejected root edit has no partial effect");
    rejected=false;try{grip->attachSprite(host);}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected,"attachment graph rejects cross-Sprite cycles");
    rejected=false;try{child->setupPhysicsBody();}catch(const std::logic_error&){rejected=true;}
    expect(rejected,"rigid root rejects competing dynamic physics");
    mount->detachSprite();near(child->getLocation().x,16,"detach retains world placement");
    expect(child->getAttachmentPart()==nullptr,"detach removes weak child backlink");
    auto* preserved=socket->attachSprite(child,partPlacement_PreserveWorld,grip);
    near(child->getLocation().x,16,"preserve-world attachment does not jump");
    host->setScale(3);step(*host,0);near(child->getLocation().x,19,"preserved offset inherits subsequent host scale");
    preserved->addRef();host->removePart(socket->getId());
    expect(preserved->getAttachedSprite()==nullptr && child->getAttachmentPart()==nullptr,"removing host socket releases descendant attachment");
    near(child->getLocation().x,19,"host removal preserves final child pose");preserved->release();
    auto* singular=host->createPart("singular");singular->setScale(0,1);
    const auto count=host->getPartCount();rejected=false;
    try{singular->attachSprite(child);}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected && host->getPartCount()==count,"invalid attach creates no partial mounting Part");
    cleanupLayer(layer);
}

}
namespace pdg {
bool Initializer::allowHorizontalOrientation() throw() { return true; }
bool Initializer::allowVerticalOrientation() throw() { return true; }
const char* Initializer::getAppName(bool) throw() { return "PDG Physics Owner Tests"; }
const char* Initializer::getMainResourceFileName() throw() { return nullptr; }
bool Initializer::installGlobalHandlers() throw() { return false; }
bool Initializer::getGraphicsEnvironmentDimensions(Rect, Rect, long& width, long& height, uint8& depth) throw() {
    width = height = 1; depth = 32; return false;
}
}
int main() {
    generatedRigGeometry();
    try {
        expect(pdg::main_initManagers() == 0, "managers initialize");
        editableConstraintAnchors();
        spinningBoxContacts();
        partTransfers();rigPartTransfers();
        #ifndef PDG_NO_GUI
        drawingSnapshots();visualSnapshotCoordinates();
#endif
        partArtworkColliders();capsuleColliders();particles();angularSpeedBreaks();compactSnapshotRecords();compressedAuthoredAssets();authoredSnapshots();rigSnapshots();physicsGraphSnapshots();colliderSourcesAndPolygons();collidersAndConstraints();nativeContactReuse();nativeRestingStacks();physicalProperty();physicsSetup();physicalOwners();physicalDrives();physicalSnapshots();animatedOwners();kinematicMounts();physicalHierarchy();attachmentLayers();partAttachments();limitedPartIK();linkedPartIK();drivenPartIK();partIK();scheduledPartIK();partWorld();layerTweenSnapshots();baseSnapshots();compactTweenSnapshots();compactTweenObjectStreams();sequencedSnapshots();imageSnapshots();invalidPartSnapshots();invalidControllerSnapshots();partSnapshots();invalidMountSnapshots();mountSnapshots();spriteFrameSnapshots();layerInitialSnapshots();layerPartMotionUpdates();
        std::cout << "Physics owners: " << assertions << " assertions passed\n";
    } catch (const std::exception& error) {
        std::cerr << "Physics owner regression failed: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
