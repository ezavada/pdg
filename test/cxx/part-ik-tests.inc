void linkedPartIK() {
    using namespace pdg;
    Sprite sprite;
    auto* root=sprite.createPart("root"),*middle=sprite.createPart("middle"),*tip=sprite.createPart("tip");
    middle->setParentPart(root).setLocation(10,0);tip->setParentPart(middle).setLocation(8,0);
    auto& a=root->setupPhysicsBody().setMode(physicsBody_Kinematic);
    auto& b=middle->setupPhysicsBody().setMode(physicsBody_Kinematic);
    auto& owner=sprite.setupPhysicsBody().setMode(physicsBody_Kinematic);
    auto& shoulder=owner.createRotaryLimit(a,0,0);
    root->setIKLimits(shoulder);
    auto& elbow=a.createRotaryLimit(b,0,.2);
    middle->setIKLimits(elbow);
    expect(!root->solveIK(middle,tip,pdg::Point(10,8)),"linked limits constrain direct IK");
    near(middle->getRotation(),.2,"direct IK reads the constraint range");
    expect(&elbow.setAngleLimits(.4,.4)==&elbow,"limit mutation chains");
    near(middle->getIKMinAngle(),.4,"linked queries see a change immediately");
    root->solveIK(middle,tip,pdg::Point(10,8));near(middle->getRotation(),.4,"IK sees live limit mutation");
    bool rejected=false;try{elbow.setAngleLimits(1,0);}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected,"inverted constraint interval rejects");near(elbow.getMaxAngle(),.4,"bad updates are transactional");
    for(double invalid:{std::numeric_limits<double>::quiet_NaN(),std::numeric_limits<double>::infinity()}) {
        rejected=false;try{elbow.setAngleLimits(0,invalid);}catch(const std::invalid_argument&){rejected=true;}
        expect(rejected,"nonfinite shared limits reject");
    }
    auto& pivot=a.createPivotJoint(b,pdg::Point(10,0));
    rejected=false;try{middle->setIKLimits(pivot);}catch(const std::logic_error&){rejected=true;}
    expect(rejected,"non-angular constraints cannot supply IK limits");
    rejected=false;try{pivot.getMinAngle();}catch(const std::logic_error&){rejected=true;}
    expect(rejected,"angle accessor rejects other constraint types");
    rejected=false;try{pivot.setAngleLimits(0,1);}catch(const std::logic_error&){rejected=true;}
    expect(rejected,"angle setter rejects other constraint types");
    rejected=false;try{root->setIKLimits(elbow);}catch(const std::logic_error&){rejected=true;}
    expect(rejected,"wrong parent-child endpoints reject");
    elbow.setAngleLimits(0,7);
    rejected=false;try{middle->getIKMaxAngle();}catch(const std::logic_error&){rejected=true;}
    expect(rejected,"multi-turn physical ranges remain legal but cannot drive pose IK");
    elbow.setAngleLimits(.4,.4);
    root->setIKTarget(middle,tip,pdg::Point(10,8));
    elbow.disconnect();step(sprite,10);
    expect(middle->hasIKLimits() && !root->getIKError().empty(),"disconnection retains invalid link and suspends IK");
    rejected=false;try{middle->getIKMinAngle();}catch(const std::logic_error&){rejected=true;}
    expect(rejected,"disconnected linked queries fail safely");
    near(elbow.getMinAngle(),.4,"Part retention keeps detached constraint queryable");
    auto& reverse=b.createRotaryLimit(a,-.8,-.1);middle->setIKLimits(reverse);
    near(middle->getIKMinAngle(),.1,"reversed endpoint minimum is negated maximum");
    near(middle->getIKMaxAngle(),.8,"reversed endpoint maximum is negated minimum");
    step(sprite,10);expect(root->getIKError().empty(),"replacing invalid link resumes the controller");
    root->setScale(2,1);step(sprite,10);
    expect(!root->getIKError().empty(),"nonuniform parent frame suspends linked IK");
    root->setScale(1);root->setFlipX(true);step(sprite,10);
    expect(!root->getIKError().empty(),"reflected parent frame suspends linked IK");
    root->setFlipX(false);step(sprite,10);expect(root->getIKError().empty(),"supported frame resumes IK");
    for(int mode:{serialization_Complete,serialization_ExternalReferences}) {
        Serializer writer;writer.setResourceMode(mode);sprite.serialize(&writer);
        auto* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
        Deserializer reader(bytes,writer.getDataSize());Sprite restored;restored.deserialize(&reader);
        auto* m=restored.findPart("middle");near(m->getIKMinAngle(),.1,"linked IK limit survives graph restoration");
        auto& limit=m->physics.getConstraint(m->physics.getConstraintCount()-1);
        limit.setAngleLimits(-.6,-.2);near(m->getIKMinAngle(),.2,"restored IK retains a live constraint reference");
    }
    middle->clearIKLimits();expect(reverse.isActive(),"clearing the IK link leaves physical constraints active");
    middle->setIKLimits(reverse);middle->removePhysicsBody();step(sprite,10);
    expect(!root->getIKError().empty(),"body removal invalidates the retained link safely");
    middle->setIKLimits(0,1);step(sprite,10);expect(root->getIKError().empty(),"numeric replacement releases the link");
    root->clearIKLimits();root->clearIKTarget();
}
void limitedPartIK() {
    using namespace pdg;
    Sprite sprite;
    auto* root=sprite.createPart("root"),*middle=sprite.createPart("middle"),*tip=sprite.createPart("tip");
    middle->setParentPart(root).setLocation(10,0);tip->setParentPart(middle).setLocation(8,0);
    root->setIKLimits(-.3,.7);middle->setIKLimits(.1,1.2);
    for(float x:{-12.f,0.f,10.f,18.f}) for(float y:{-8.f,0.f,12.f}) {
        root->solveIK(middle,tip,pdg::Point(x,y));
        expect(root->getRotation()>=-.300001 && root->getRotation()<=.700001,"root respects IK limits");
        expect(middle->getRotation()>=.099999 && middle->getRotation()<=1.200001,"middle respects IK limits");
        const auto actual=tip->getTransform(partSpace_World);
        const double error=std::hypot(actual.tx-x,actual.ty-y);
        double sampled=1e9;
        for(int a=0;a<=100;++a) for(int b=0;b<=100;++b) {
            const double r=-.3+a*.01,m=.1+b*.011;
            sampled=std::min(sampled,std::hypot(10*std::cos(r)+8*std::cos(r+m)-x,10*std::sin(r)+8*std::sin(r+m)-y));
        }
        expect(error<=sampled+1e-4,"constrained solution is at least as good as a dense joint-angle grid");
    }
    bool rejected=false;try{root->setIKLimits(1,-1);}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected && root->hasIKLimits(),"invalid limit update preserves existing range");
    near(root->getIKMinAngle(),-.3,"invalid limits preserve minimum");
    root->setIKLimits(6,6.5);middle->clearIKLimits();root->solveIK(middle,tip,pdg::Point(18,0));
    near(root->getRotation(),6.283185307,"wrapped equivalent angle respects absolute local limit interval");
    root->setIKLimits(0,0);middle->setIKLimits(0,0);
    expect(!root->solveIK(middle,tip,pdg::Point(10,8)),"limits can make a target unreachable");
    near(root->getRotation(),0,"locked root angle");near(middle->getRotation(),0,"locked middle angle");
    root->setIKTarget(middle,tip,pdg::Point(10,8));step(sprite,10);
    expect(!root->isIKTargetReached() && root->getIKError().empty(),"unreachable limited target is not a structural error");
    for(int mode:{serialization_Complete,serialization_ExternalReferences}) {
        Serializer writer;writer.setResourceMode(mode);
        const auto bytes=sprite.getSerializedSize(&writer);sprite.serialize(&writer);
        expect(writer.getDataSize()==bytes+3,"limited Part snapshot size accounts for ranges");
        void* copy=std::malloc(writer.getDataSize());std::memcpy(copy,writer.getDataPtr(),writer.getDataSize());
        Deserializer reader(copy,writer.getDataSize());Sprite restored;restored.deserialize(&reader);
        auto* r=restored.findPart("root"),*m=restored.findPart("middle");
        expect(r->hasIKLimits() && m->hasIKLimits() && r->hasIKTarget(),"limits restore before scheduled IK");
        near(r->getIKMaxAngle(),0,"locked range round trips");
    }
    root->clearIKLimits();middle->clearIKLimits();step(sprite,10);
    expect(root->isIKTargetReached(),"clearing limits resumes reaching the target");
}
void drivenPartIK() {
    using namespace pdg;
    for(bool native:{false,true}) for(bool tipBody:{false,true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if(native)continue;
#endif
        auto* layer=SpriteManager::createSpriteLayer();SpriteManager::getSingletonInstance()->addLayer(layer);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(native);layer->setGravity(0);layer->setDamping(1);
#endif
        auto* sprite=layer->createSprite();
        auto* tip=sprite->createPart("tip"),*middle=sprite->createPart("middle"),*root=sprite->createPart("root");
        middle->setParentPart(root).setLocation(10,0);tip->setParentPart(middle).setLocation(8,0);
        auto& a=root->setupPhysicsBody(1,20);auto& b=middle->setupPhysicsBody(1,20);
        auto& anchor=layer->createSprite()->setupPhysicsBody().setMode(physicsBody_Static);
        a.createPivotJoint(anchor);a.createPivotJoint(b,pdg::Point(10,0));
        if(tipBody){tip->setupPhysicsBody(1,5);b.createPivotJoint(tip->physics,pdg::Point(8,0));}
        root->setIKDriveTarget(middle,tip,pdg::Point(10,8),3000,3000,partSpace_World,1,1,2,1);
        expect(root->isIKDriven() && root->hasIKTarget(),"physical IK controller installs");
        near(tip->getTransform(partSpace_World).ty,0,"installing a drive does not teleport the chain");
        bool rejected=false;try{b.clearDrive();}catch(const std::logic_error&){rejected=true;}
        expect(rejected,"caller cannot silently clear a controller-owned drive");
        rejected=false;try{a.setDriveTarget(pdg::Point(),0,1,1);}catch(const std::logic_error&){rejected=true;}
        expect(rejected,"caller cannot replace a controller-owned drive");
        rejected=false;try{b.setMode(physicsBody_Kinematic);}catch(const std::logic_error&){rejected=true;}
        expect(rejected,"body mode changes require releasing the IK controller");
        auto tick=[&]{
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            if(native)SpriteManager::getSingletonInstance()->stepAnimationPhysics(5);
#endif
            layer->animateLayer(5);
        };
        tick();expect(root->getIKError().empty(),"physical IK updates without structural errors");
        expect(tip->getTransform(partSpace_World).ty<1,"physics advances gradually instead of copying the desired pose");
        for(int i=0;i<1200;++i)tick();
        const auto end=tip->getTransform(partSpace_World);
        near(end.tx,10,"physical IK reaches target x");near(end.ty,8,"physical IK reaches target y");
        expect(root->isIKTargetReached(),"reached status measures actual physical endpoint");
        const auto desired=b.getDriveState();b.applyImpulse(Vector(10,0));
        root->setIKDriveTarget(middle,tip,pdg::Point(10,8),3000,3000,partSpace_World,1,1,2,1);tick();
        near(b.getDriveState().x,desired.x,"repeated targets preserve captured joint offsets after an impulse");
        near(b.getDriveState().y,desired.y,"physical drift does not redefine segment lengths");
        const auto drive=b.getDriveState();
        expect(std::hypot(drive.forceX,drive.forceY)<=3000.00001 && std::abs(drive.torque)<=3000.00001,"drive respects force and torque bounds");
        rejected=false;try{root->setIKDriveTarget(tip,middle,pdg::Point(),1,1);}catch(const std::invalid_argument&){rejected=true;}
        expect(rejected && root->isIKDriven(),"invalid replacement preserves controller");
        rejected=false;try{Serializer writer;sprite->serialize(&writer);}catch(const std::runtime_error&){rejected=true;}
        expect(rejected,"standalone controller snapshot rejects its external anchor body");
        for(int mode:{serialization_Complete,serialization_ExternalReferences}) {
            Serializer writer;writer.setResourceMode(mode);const auto size=layer->getSerializedSize(&writer);layer->serialize(&writer);
            expect(writer.getDataSize()==size+3,"physical IK graph exact snapshot size");
            auto* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
            Deserializer reader(bytes,writer.getDataSize());auto* copy=SpriteManager::createSpriteLayer();SpriteManager::getSingletonInstance()->addLayer(copy);
            copy->deserialize(&reader);
            auto* rr=copy->getNthSprite(0)->findPart("root"),*mm=copy->getNthSprite(0)->findPart("middle");
            expect(rr->isIKDriven(),"active physical IK controller restores");
            near(mm->physics.getDriveState().x,b.getDriveState().x,"sampled drive target survives before the next update");
            rejected=false;try{mm->physics.clearDrive();}catch(const std::logic_error&){rejected=true;}
            expect(rejected,"restored controller exclusively owns its drives");
            copy->animateLayer(5);
            expect(rr->getIKError().empty(),"restored physical controller resumes");
            near(mm->physics.getDriveState().x,desired.x,"restoration preserves captured offsets instead of recapturing physical drift");
            near(mm->physics.getDriveState().y,desired.y,"captured segment geometry survives");
            rr->clearIKTarget();expect(!mm->physics.isDriveEnabled(),"clearing restored controller releases peer drives");
            cleanupLayer(copy);
        }
        root->setIKLimits(0,0);
        auto& elbow=a.createRotaryLimit(b,.2,.2);middle->setIKLimits(elbow);
        for(int i=0;i<1000;++i)tick();
        near(b.getDriveState().rotation,.2,"physical target respects joint limits");
        expect(!root->isIKTargetReached(),"limited physical target reports the actual unreached endpoint");
        near(b.getState().rotation-a.getState().rotation,.2,"both solvers enforce the shared physical interval");
        elbow.setAngleLimits(.6,.6);
        for(int i=0;i<1000;++i)tick();
        near(b.getDriveState().rotation-a.getDriveState().rotation,.6,"drive reads the changed relative interval");
        near(b.getState().rotation-a.getState().rotation,.6,"native/basic physical constraint updates too");
        elbow.setAngleLimits(6,6.5);
        for(int i=0;i<1200;++i)tick();
        expect(b.getDriveState().rotation-a.getDriveState().rotation>=6,"unwrapped shared target stays on the constraint branch");
        expect(b.getState().rotation-a.getState().rotation>5.999,"physical driver does not take a shortcut across the stop");
        elbow.setAngleLimits(0,0).setBreakForce(.000001);
        for(int i=0;i<4;++i)tick();
        expect(elbow.isBroken(),"a broken shared angular limit invalidates its retained IK link");
        elbow.disconnect();tick();
        expect(!root->getIKError().empty() && !a.isDriveEnabled() && !b.isDriveEnabled(),"disconnect stops physical IK drives");
        root->clearIKLimits();middle->clearIKLimits();
        auto& wrongPivot=a.createPivotJoint(b,pdg::Point(9,0));tick();
        expect(!root->getIKError().empty() && !a.isDriveEnabled(),"inconsistent physical joint anchors suspend IK");
        wrongPivot.disconnect();tick();expect(root->getIKError().empty(),"removing the conflicting pivot resumes IK");
        root->clearIKTarget();expect(!a.isDriveEnabled() && !b.isDriveEnabled(),"clear releases all owned drive commands");
        a.setDriveTarget(pdg::Point(),0,1,1);
        rejected=false;try{root->setIKDriveTarget(middle,tip,pdg::Point(10,8),1,1);}catch(const std::logic_error&){rejected=true;}
        expect(rejected && !root->isIKDriven() && a.isDriveEnabled() && !b.isDriveEnabled(),"manual-to-IK takeover rejects the whole chain before explicit release");
        near(a.getDriveState().x,0,"rejected IK takeover preserves manual command");
        a.clearDrive();
        // Reinstall captures a new chain: restore its declared pivot offsets first.
        middle->setLocation(10,0);tip->setLocation(8,0);
        root->setIKDriveTarget(middle,tip,pdg::Point(10,8),1,1);tick();
        b.addRef();middle->removePhysicsBody();
        expect(!a.isDriveEnabled() && !b.isDriveEnabled(),"body removal stops peer drives immediately even without an animation tick");
        tick();
        expect(!root->getIKError().empty() && !a.isDriveEnabled() && !b.isDriveEnabled(),"body removal stops the whole controller safely");
        root->clearIKTarget();b.release();cleanupLayer(layer);
    }
}
