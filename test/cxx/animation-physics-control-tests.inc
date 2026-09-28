void animationPhysicsControl(const std::string& directory) {
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
    layer->setUseChipmunkPhysics(true);layer->setGravity(0);layer->setDamping(1);layer->enableCollisions();
    auto* manager=SpriteManager::getSingletonInstance();
    auto tick=[&](int count=1){for(int n=0;n<count;++n){manager->stepAnimationPhysics(10);layer->animateLayer(10);}};
    auto* sprite=layer->createSpriteFromSpriterFile((directory+"arm.scml").c_str());sprite->pauseAnimation();
    expect(sprite->enableAnimationPose("reference"),"control test pose enables");sprite->setupPhysicsFromAnimationRig(34);
    auto& shoulder=static_cast<PhysicsBody&>(sprite->findPart("shoulder")->physics);
    auto& forearm=static_cast<PhysicsBody&>(sprite->findPart("forearm")->physics);
    auto& hand=static_cast<PhysicsBody&>(sprite->findPart("hand")->physics);
    auto* joint=&forearm.getConstraint(0);
    auto rejects=[&](auto call,const char* message){bool rejected=false;try{call();}catch(const std::exception&){rejected=true;}expect(rejected,message);};
    expect(sprite->getAnimationPhysicsMode()==animationPhysics_Dynamic,"setup exposes Dynamic mode");
    rejects([&]{sprite->setAnimationPhysicsMode(animationPhysics_Driven);},"Driven requires settings atomically");
    expect(sprite->getAnimationPhysicsMode()==animationPhysics_Dynamic,"failed Driven selection preserves all modes");
    expect(!sprite->getAnimationPhysicsDriveSettings("forearm"),"unconfigured drive settings return optional empty");
    sprite->setAnimationPhysicsDriveSettings({100,30},"forearm",true);
    expect(sprite->getAnimationPhysicsDriveSettings("hand")->frequency==4,"subtree settings resolve default response");
    rejects([&]{sprite->setAnimationPhysicsMode(animationPhysics_Driven);},"unconfigured root prevents partial whole-rig mode change");
    sprite->setAnimationPhysicsMode(animationPhysics_Driven,"forearm",true,0);
    expect(sprite->getAnimationPhysicsMode()==animationPhysics_Mixed && sprite->getAnimationPhysicsMode("forearm",true)==animationPhysics_Driven,"whole query reports Mixed and subtree reports Driven");
    rejects([&]{forearm.setDriveTarget(pdg::Point(),0,1,1);},"manual drive cannot steal rig ownership");
    rejects([&]{forearm.clearDrive();},"raw clearDrive cannot steal rig ownership");
    rejects([&]{forearm.setMode(physicsBody_Static);},"Static is invalid on mapped bodies");
    forearm.setMode(physicsBody_Dynamic);
    expect(sprite->getAnimationPhysicsMode("forearm")==animationPhysics_Dynamic,"direct body mode releases rig drive");
    auto before=forearm.getState();
    forearm.setDriveTarget(pdg::Point(before.x+1,before.y),before.rotation,1,1);
    forearm.setDriveTarget(pdg::Point(before.x+2,before.y),before.rotation,2,3);
    near(forearm.getDriveState().x,before.x+2,"last successful manual setDriveTarget wins");
    rejects([&]{forearm.setDriveTarget(pdg::Point(),0,-1,1);},"invalid manual update rejects");
    near(forearm.getDriveState().x,before.x+2,"invalid target preserves previous manual drive");
    rejects([&]{sprite->setAnimationPhysicsMode(animationPhysics_Kinematic,0.0);},"manual ownership prevents whole-rig takeover");
    expect(shoulder.getMode()==physicsBody_Dynamic && sprite->getAnimationPhysicsMode("hand")==animationPhysics_Driven,"ownership rejection leaves the complete selection unchanged");
    rejects([&]{sprite->setAnimationPhysicsMode(animationPhysics_Kinematic,"forearm",true,0);},"manual ownership prevents subtree takeover");
    expect(forearm.isDriveEnabled() && sprite->getAnimationPhysicsMode("hand")==animationPhysics_Driven,"rejected subtree preserves manual target and child controller");
    forearm.clearDrive();
    const auto independent=forearm.applyForce(Vector(1,0),2);
    sprite->setAnimationPhysicsMode(animationPhysics_Kinematic,0.0);
    expect(forearm.removeForce(independent),"mode takeover preserves independent scheduled loads");
    tick();
    expect(sprite->getAnimationPhysicsMode()==animationPhysics_Kinematic,"zero-time recovery immediately takes kinematic control");
    expect(&forearm.getConstraint(0)==joint && joint->isActive(),"kinematic joints retain identity while dormant");
    auto desired=sprite->getAnimationPose().getLocalTransform(0);desired.x+=.2;
    sprite->setAnimationBoneTransform("shoulder",desired);tick();
    near(shoulder.getVelocity().x,20,"kinematic sweep samples desired pose velocity");
    sprite->setAnimationPhysicsMode(animationPhysics_Dynamic);
    near(shoulder.getVelocity().x,20,"dynamic release preserves sampled velocity");
    expect(&forearm.getConstraint(0)==joint && sprite->physics.getMass()==34,"control changes preserve graph and mass");
    // Relative drives cannot introduce a net force/torque into a freely falling subtree.
    sprite->setAnimationPhysicsDriveSettings({1000,1000});
    sprite->setAnimationPhysicsMode(animationPhysics_Kinematic,0.0);tick();
    sprite->setAnimationPhysicsMode(animationPhysics_Dynamic);
    for(auto* body:{&shoulder,&forearm,&hand})body->setVelocity(0,0).setAngularVelocity(0);
    sprite->setAnimationPhysicsMode(animationPhysics_Driven,"forearm",true,0);
    forearm.teleport(pdg::Point(forearm.getState().x,forearm.getState().y),forearm.getState().rotation+.3);
    tick();
    double px=0,py=0;for(auto* body:{&shoulder,&forearm,&hand}){px+=body->getMass()*body->getVelocity().x;py+=body->getMass()*body->getVelocity().y;}
    near(px,0,"relative drives preserve whole-rig linear momentum X");near(py,0,"relative drives preserve whole-rig linear momentum Y");
    expect(std::abs(forearm.getDriveState().torque)<=1000,"driven torque respects per-body cap");
    layer->setGravity(40);
    sprite->setAnimationPhysicsDriveSettings({100000,100000});
    sprite->setAnimationPhysicsMode(animationPhysics_Kinematic,.2);
    tick(1200);
    expect(sprite->getAnimationPhysicsMode()==animationPhysics_Kinematic,"recovery removes steady gravity error before kinematic handoff");
    layer->setGravity(0);
    sprite->disableAnimationPhysics(0);
    // A falling chain used to finish the children's local recovery
    // before the root's world recovery. Kinematic children then fought their
    // still-dynamic parent through the pivots and could launch the whole rig.
    auto* falling=layer->createSpriteFromSpriterFile((directory+"arm.scml").c_str());
    falling->setLocation(180,240);falling->setScale(18,18);falling->pauseAnimation();
    expect(falling->enableAnimationPose("reference"),"falling recovery pose enables");
    falling->setupPhysicsFromAnimationRig(12,100);
    falling->setAnimationPhysicsMode(animationPhysics_Kinematic,0.0);tick();
    std::vector<PhysicsBody*> chain;
    for(const char* name:{"shoulder","forearm","hand"}) {
        auto& b=static_cast<PhysicsBody&>(falling->findPart(name)->physics);chain.push_back(&b);
        falling->setAnimationPhysicsDriveSettings({b.getMass()*6000,b.getMomentOfInertia()*400,4,4},name);
    }
    auto* floor=layer->createSprite();floor->setupPhysicsBody().setMode(physicsBody_Static);
    floor->setupCollider().setBox(pdg::Rect(26,590,694,615));
    layer->setGravity(300);
    falling->setAnimationPhysicsMode(animationPhysics_Dynamic);
    falling->physics.applyImpulse(Vector(120,-900));tick(250);
    falling->setLocation(180,240); // Recover to a pose clear of the floor.
    falling->setAnimationPhysicsMode(animationPhysics_Kinematic,.5,rotationDirection_Shortest);
    bool prematureChild=false,escaped=false;
    for(int n=0;n<1200;++n) {
        tick();
        if(chain[0]->getMode()!=physicsBody_Kinematic &&
           (chain[1]->getMode()==physicsBody_Kinematic || chain[2]->getMode()==physicsBody_Kinematic))prematureChild=true;
        for(auto* b:chain) {
            const auto state=b->getState();
            if(!std::isfinite(state.x+state.y)||std::abs(state.x)>2000||std::abs(state.y)>2000)escaped=true;
        }
        if(escaped)break;
    }
    expect(!prematureChild,"children wait for recovering kinematic ancestors before handoff");
    expect(!escaped && falling->getAnimationPhysicsMode()==animationPhysics_Kinematic,"fallen whole-rig recovery remains bounded and completes");
    falling->disableAnimationPhysics(0);layer->removeSprite(floor);layer->setGravity(0);
    auto* angular=layer->createSpriteFromSpriterFile((directory+"physics-generation.scml").c_str());angular->pauseAnimation();
    expect(angular->enableAnimationPose("reference"),"angular control pose enables");angular->setupPhysicsFromAnimationRig(2,1000);
    auto& rotor=static_cast<PhysicsBody&>(angular->findPart("root")->physics);const auto rotorHome=rotor.getState();
    rotor.teleport(pdg::Point(rotorHome.x,rotorHome.y),rotorHome.rotation-4*3.14159265358979323846);
    angular->setAnimationPhysicsDriveSettings({0,10,4,1,rotationDirection_AsSpecified});
    angular->setAnimationPhysicsMode(animationPhysics_Driven,0.0);tick();
    expect(rotor.getDriveState().rotationError>6,"as-specified drive preserves authored full-turn distance");
    expect(rotor.getDriveState().forceX==0 && rotor.getDriveState().forceY==0,"zero force disables linear actuation");
    angular->setAnimationPhysicsDriveSettings({0,10});tick();
    expect(std::abs(rotor.getDriveState().rotationError)<3.14159265358979323846,"settings use shortest route by default");
    angular->setAnimationPhysicsMode(animationPhysics_Dynamic);
    rotor.teleport(pdg::Point(rotorHome.x,rotorHome.y),.25).setAngularVelocity(0);
    angular->setAnimationPhysicsDriveSettings({0,10,4,1,rotationDirection_Clockwise});
    angular->setAnimationPhysicsMode(animationPhysics_Driven,0.0);tick();
    const auto routed=rotor.getDriveState().rotation;expect(routed>6,"clockwise chooses positive full route");
    tick(5);near(rotor.getDriveState().rotation,routed,"resolved route remains stable across ticks");
    // A wrapped animation angle must not ask the drive for a full revolution
    // (or feed a full-turn velocity into its damper) at every zero crossing.
    constexpr double turn=6.28318530717958647692;
    auto wrapped=angular->getAnimationPose().getLocalTransform(0);
    for(int direction:{rotationDirection_Shortest,rotationDirection_Clockwise,rotationDirection_CounterClockwise}) {
        angular->setAnimationPhysicsMode(animationPhysics_Dynamic);
        wrapped.rotation=.02;angular->setAnimationBoneTransform("root",wrapped);
        rotor.teleport(pdg::Point(rotorHome.x,rotorHome.y),.02-2*turn).setAngularVelocity(0);
        angular->setAnimationPhysicsDriveSettings({0,10,4,2,direction});
        angular->setAnimationPhysicsMode(animationPhysics_Driven,0.0);tick();
        near(rotor.getDriveState().torque,0,"routed initial sample introduces no false target velocity");
        double previous=rotor.getDriveState().rotation;
        for(int n=0;n<12;++n) {
            wrapped.rotation=n%2?.02:turn-.02;
            angular->setAnimationBoneTransform("root",wrapped);tick();
            const double target=rotor.getDriveState().rotation;
            near(target-previous,n%2?.04:-.04,"wrapped target follows the selected route continuously");
            previous=target;
        }
    }
    angular->setAnimationPhysicsDriveSettings({0,10,4,2,rotationDirection_AsSpecified});
    wrapped.rotation=turn+.02;angular->setAnimationBoneTransform("root",wrapped);tick();
    near(rotor.getDriveState().rotation,turn+.02,"as-specified target retains authored full revolutions");
    // The implicit spring's velocity term must include k*dt. Without it a
    // high-frequency drive adds energy even with critical damping requested.
    angular->setAnimationPhysicsMode(animationPhysics_Dynamic);
    wrapped.rotation=0;angular->setAnimationBoneTransform("root",wrapped);
    rotor.teleport(pdg::Point(rotorHome.x,rotorHome.y),.2).setAngularVelocity(0);
    angular->setAnimationPhysicsDriveSettings({0,1000000,80,1});
    angular->setAnimationPhysicsMode(animationPhysics_Driven,0.0);
    double excursion=0;
    for(int n=0;n<200;++n) {tick();excursion=std::max(excursion,std::abs(rotor.getState().rotation));}
    expect(excursion<.25 && std::abs(rotor.getState().rotation)<1e-3,"stiff damped angular drive dissipates motion instead of amplifying it");
    angular->setAnimationPhysicsMode(animationPhysics_Dynamic);
    rotor.teleport(pdg::Point(rotorHome.x,rotorHome.y),.5).setAngularVelocity(0);
    angular->setAnimationPhysicsDriveSettings({0,20,4,1});
    angular->setAnimationPhysicsMode(animationPhysics_Kinematic,.2,rotationDirection_Shortest);
    double peakRecoveryTorque=0;
    for(int n=0;n<10;++n) {
        tick();peakRecoveryTorque=std::max(peakRecoveryTorque,std::abs(rotor.getDriveState().torque));
    }
    expect(peakRecoveryTorque>0 && peakRecoveryTorque<=20.000001,"recovery reports solved motor torque within its configured cap");
    angular->setAnimationPhysicsMode(animationPhysics_Dynamic);
    rotor.setAngularVelocity(1);tick(5);
    near(rotor.getAngularVelocity(),1,"interrupting recovery removes its angular motor");
    angular->disableAnimationPhysics(0);
    // Heavy damping must not reduce the load capacity below the force cap.
    // This body weighs 40 force units and has only 50 units of drive available.
    auto* loaded=layer->createSpriteFromSpriterFile((directory+"physics-generation.scml").c_str());loaded->pauseAnimation();
    expect(loaded->enableAnimationPose("reference"),"loaded recovery pose enables");loaded->setupPhysicsFromAnimationRig(2,1000);
    loaded->setAnimationPhysicsDriveSettings({50,50,4,8});layer->setGravity(20);
    loaded->setAnimationPhysicsMode(animationPhysics_Kinematic,.2);
    double peakForce=0;
    for(int n=0;n<1200;++n) {
        tick();const auto drive=loaded->findPart("root")->physics.getDriveState();
        peakForce=std::max(peakForce,std::hypot(drive.forceX,drive.forceY));
    }
    expect(loaded->getAnimationPhysicsMode()==animationPhysics_Kinematic,"damped recovery supports gravity within the configured force limit");
    expect(peakForce<=50.000001,"gravity compensation stays inside the caller's force cap");
    loaded->disableAnimationPhysics(0);layer->removeSprite(loaded);layer->setGravity(0);
    // A one-body rig makes blocked recovery and event completion deterministic.
    auto* simple=layer->createSpriteFromSpriterFile((directory+"physics-generation.scml").c_str());simple->pauseAnimation();
    expect(simple->enableAnimationPose("reference"),"recovery test pose enables");simple->setupPhysicsFromAnimationRig(2,1000);
    auto& body=static_cast<PhysicsBody&>(simple->findPart("root")->physics);
    struct Completion : IEventHandler {
        int count=0;SpriteAnimationPhysicsRecoveryInfo last{};
        bool handleEvent(EventEmitter*,long,void* data) throw() override {
            auto* info=static_cast<SpriteAnimateInfo*>(data);
            if(info->action!=Sprite::action_AnimationPhysicsRecoveryComplete)return false;
            ++count;last=*static_cast<SpriteAnimationPhysicsRecoveryInfo*>(data);return true;
        }
    } completion;
    simple->addHandler(&completion,eventType_SpriteAnimate);
    const auto home=body.getState();body.teleport(pdg::Point(home.x-5,home.y),home.rotation);
    auto* wall=layer->createSprite();wall->setLocation(home.x-2.5,home.y);wall->setupPhysicsBody().setMode(physicsBody_Static);
    wall->setupCollider().setBox(pdg::Rect(-.2,-10,.2,10));
    int recoveryContacts=0;
    simple->findPart("root")->collider.setWantsContactEvents(true).setContactHandler([&](const ColliderContact&){++recoveryContacts;});
    simple->setAnimationPhysicsMode(animationPhysics_Kinematic);
    expect(simple->getAnimationPhysicsMode()==animationPhysics_Driven && body.getMode()==physicsBody_Dynamic,"recovery exposes its actual temporary Driven state");
    tick(200);
    expect(completion.count==0 && simple->getAnimationPhysicsMode()==animationPhysics_Driven,"collision-blocked recovery does not complete at its deadline");
    expect(body.getState().x<home.x-2 && recoveryContacts>0,"recovery remains blocked and emits normal contact notifications");
    layer->removeSprite(wall);layer->stopAnimations();tick(400);layer->startAnimations();
    expect(completion.count==1 && simple->getAnimationPhysicsMode()==animationPhysics_Kinematic,"recovery completes with layer animation stopped after obstruction is removed");
    expect(completion.last.wholeRig && completion.last.bodyCount==1 && !completion.last.disabled,"completion carries source and whole-rig selection");
    simple->setAnimationPhysicsMode(animationPhysics_Dynamic);
    body.teleport(pdg::Point(home.x+2,home.y),home.rotation);
    simple->setAnimationPhysicsMode(animationPhysics_Kinematic,1.0);tick(10);
    simple->setAnimationPhysicsMode(animationPhysics_Dynamic);tick(120);
    expect(completion.count==1,"interrupted recovery emits no stale completion");
    simple->disableAnimationPhysics();
    expect(simple->isAnimationPhysicsEnabled(),"default disable retains rig through recovery");
    tick(400);
    expect(!simple->isAnimationPhysicsEnabled() && completion.count==2 && completion.last.disabled,"disable completion occurs after solver teardown");
    simple->removeHandler(&completion,eventType_SpriteAnimate);
    cleanupLayer(layer);
}

void animationIKDrivenControl(const std::string& directory) {
    using namespace pdg;
#ifdef PDG_NO_GUI
    auto* layer=createSpriteLayer();
#else
    auto* layer=createSpriteLayer(nullptr);
#endif
    layer->setUseChipmunkPhysics(true);layer->setGravity(0);layer->setDamping(1);
    auto* sprite=layer->createSpriteFromSpriterFile((directory+"arm.scml").c_str());
    sprite->pauseAnimation();expect(sprite->enableAnimationPose("reference"),"IK drive fixture enables");
    sprite->setupPhysicsFromAnimationRig(12);
    sprite->setAnimationPhysicsDriveSettings({10000,10000,4,2});
    sprite->setAnimationPhysicsMode(animationPhysics_Driven,0.0);
    AnimationTwoBoneIK config;config.root=0;config.middle=1;config.tip=2;
    config.rootLength=10;config.middleLength=5;config.targetX=10;config.targetY=10;
    const auto ik=sprite->addAnimationIK(config);
    int samples=0;double sampledSeconds=0;
    sprite->addAnimationModifier([&](auto,const auto& context){++samples;sampledSeconds+=context.deltaSeconds;});
    sprite->startAnimation("reference");
    sprite->getAnimationPose();const auto initialSamples=samples;
    auto tick=[&]{SpriteManager::getSingletonInstance()->stepAnimationPhysics(5);layer->animateLayer(5);};
    auto actual=[&]{return sprite->getAnimationBoneTransform("hand",animationSpace_World);};
    expect(std::hypot(actual().x-10,actual().y-10)>1,"IK desired pose does not teleport Driven bones");
    for(int i=0;i<1200;++i) {
        tick();const auto sampled=samples;
        sprite->getAnimationIKResult(ik);sprite->getAnimationPose();actual();
        expect(samples==sampled,"pose/IK queries do not resample the controller after physics publication");
    }
    expect(samples-initialSamples>=1200,"each physics interval samples the desired pose, including speed-limited substeps");
    near(sampledSeconds,6,"animation plus IK plus drives integrates elapsed time exactly once");
    expect(sprite->getAnimationIKResult(ik).reachable,"IK reports a reachable desired target");
    expect(std::hypot(actual().x-10,actual().y-10)<.02,"Driven final physical endpoint converges to IK target");
    auto& body=static_cast<PhysicsBody&>(sprite->findPart("hand")->physics);
    body.applyImpulse(Vector(1,0));const auto load=body.applyForce(Vector(2,0),.1);
    tick();expect(body.isDriveEnabled(),"external force and impulse keep rig drive ownership");
    expect(body.removeForce(load),"external scheduled force remains independently removable");
    sprite->setAnimationIKTarget(ik,12,8,animationSpace_Rig);
    for(int i=0;i<1200;++i)tick();
    expect(std::hypot(actual().x-12,actual().y-8)<.02,"same controller updates IK target after physical disturbance");
    cleanupLayer(layer);
}
