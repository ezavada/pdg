void editableConstraintAnchors() {
    using namespace pdg;
    const auto worldPoint = [](const PhysicsBody& body, pdg::Point p) {
        const auto s=body.getState();const auto c=std::cos(s.rotation),n=std::sin(s.rotation);
        return pdg::Point(s.x+c*p.x-n*p.y,s.y+n*p.x+c*p.y);
    };
    for(bool native:{false,true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if(native)continue;
#endif
        auto* layer=SpriteManager::createSpriteLayer();
        SpriteManager::getSingletonInstance()->addLayer(layer);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(native);
        layer->setGravity(0);layer->setDamping(1);
#endif
        auto* owner=layer->createSprite();auto* part=owner->createPart("moving");
        auto& a=owner->setupPhysicsBody().setMode(physicsBody_Static);
        auto& b=part->setupPhysicsBody(2,1000);
        auto& collider=part->setupCollider().setCapsule(pdg::Point(-1,0),pdg::Point(1,0),.25);
        const auto shape=collider.getShapeId(0);
        auto advance=[&](int ticks) { for(int i=0;i<ticks;++i) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            if(native)SpriteManager::getSingletonInstance()->stepAnimationPhysics(10);
#endif
            layer->animateLayer(10);
        }};
        for(int type=constraint_Pin;type<=constraint_Spring;++type) {
            b.teleport(pdg::Point(4,0),0).stopMoving().stopSpinning();
            PhysicsConstraint* joint=nullptr;
            switch(type) {
                case constraint_Pin:joint=&a.createPinJoint(b);break;
                case constraint_Slide:joint=&a.createSlideJoint(b,pdg::Point(),pdg::Point(),1,2);break;
                case constraint_Pivot:joint=&a.createPivotJoint(b);break;
                case constraint_Groove:joint=&a.createGrooveJoint(b,pdg::Point(-2,0),pdg::Point(2,0),pdg::Point());break;
                case constraint_Spring:joint=&a.createSpring(b,pdg::Point(),pdg::Point(),2,20,8);break;
            }
            joint->addRef();joint->setMaxForce(1000).setBreakForce(100000).setCollideBodies(true);
            advance(350); // Exercise editing an already-created native constraint.
            const auto before=b.getState();
            if(type==constraint_Groove) {
                expect(&joint->setGroove(pdg::Point(1,2),pdg::Point(5,2))==joint,"groove editing is fluent");
                near(joint->getGrooveStart().x,1,"groove start is body-local");
                near(joint->getGrooveEnd().x,5,"groove end is body-local");
                bool rejected=false;try{joint->setGroove(pdg::Point(9,9),pdg::Point(9,9));}catch(const std::invalid_argument&){rejected=true;}
                expect(rejected&&joint->getGrooveStart()==pdg::Point(1,2),"invalid groove edit preserves both endpoints");
                rejected=false;try{joint->setAnchors(pdg::Point(),pdg::Point());}catch(const std::logic_error&){rejected=true;}
                expect(rejected,"groove body A requires track endpoints, not a point anchor");
            } else {
                expect(&joint->setAnchors(pdg::Point(1,2),pdg::Point())==joint,"paired anchor editing is fluent");
                joint->setAnchorA(pdg::Point(1,2));
                bool rejected=false;try{joint->setAnchors(pdg::Point(9,9),pdg::Point(NAN,0));}catch(const std::invalid_argument&){rejected=true;}
                expect(rejected&&joint->getAnchorA()==pdg::Point(1,2)&&joint->getAnchorB()==pdg::Point(),
                    "invalid paired edit preserves both anchors");
            }
            expect(&joint->setAnchorB(pdg::Point(.5,0))==joint,"body B editing is fluent");
            auto point=joint->getAnchorB();point.x=99;
            near(joint->getAnchorB().x,.5,"anchor getter returns a copy");
            near(b.getState().x,before.x,"anchor edit does not teleport body x");
            near(b.getState().y,before.y,"anchor edit does not teleport body y");
            near(b.getState().velocityX,before.velocityX,"anchor edit does not inject velocity");
            advance(500);
            const auto pb=worldPoint(b,joint->getAnchorB());
            if(type==constraint_Groove) {
                expect(pb.x>=.95&&pb.x<=5.05&&std::abs(pb.y-2)<.05,"edited groove controls the next solve");
            } else {
                const auto pa=worldPoint(a,joint->getAnchorA());const auto d=std::hypot(pb.x-pa.x,pb.y-pa.y);
                if(type==constraint_Slide)expect(d>=.95&&d<=2.05,"anchor edit retains slide range");
                else expect(std::abs(d-(type==constraint_Pin?4:type==constraint_Spring?2:0))<.05,
                    "edited anchors solve while preserving pin distance or spring rest length");
            }
            expect(&a.getConstraint(0)==joint&&&b.getConstraint(0)==joint,"editing preserves shared constraint handles");
            expect(joint->getMaxForce()==1000&&joint->getBreakForce()==100000&&joint->getCollideBodies(),
                "anchor edits preserve force limits and collision policy");
            near(b.getMass(),2,"anchor edit preserves mass");near(b.getMomentOfInertia(),1000,"anchor edit preserves inertia");
            expect(collider.getShapeId(0)==shape&&collider.getCapsuleStart(shape)==pdg::Point(-1,0),"anchor edit preserves capsule geometry and ID");
            joint->disconnect();joint->setAnchorB(pdg::Point(3,4));
            expect(!joint->isActive()&&joint->getAnchorB()==pdg::Point(3,4),"retained disconnected anchors stay editable without reconnecting");
            joint->release();
        }
        // A zero-distance pin uses a native pivot, but keeps the pin API contract.
        b.teleport(pdg::Point(),0).stopMoving().stopSpinning();
        auto& pin=a.createPinJoint(b);advance(1);pin.setAnchorA(pdg::Point(0,3));advance(200);
        expect(std::abs(b.getState().y-3)<.05,"zero-distance pin adopts anchor edits");
        pin.disconnect();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if(native) {
            b.teleport(pdg::Point(),0).stopMoving().stopSpinning();
            auto& pivot=a.createPivotJoint(b);advance(1);
            struct Edit {PhysicsConstraint* joint;bool called=false;} edit{&pivot};
            cpSpaceEachBody(layer->getSpace(),[](cpBody*,void* data) {
                auto& edit=*static_cast<Edit*>(data);
                if(!edit.called){edit.joint->setAnchors(pdg::Point(0,4),pdg::Point());edit.called=true;}
            },&edit);
            expect(edit.called&&pivot.getAnchorA()==pdg::Point(0,4),"locked-space edits update public geometry without mutating native joints");
            advance(250);expect(std::abs(b.getState().y-4)<.05,"locked-space edits apply at the next safe solve");
            cpSpaceSetSleepTimeThreshold(layer->getSpace(),.1);
            auto* nativeBody=static_cast<cpBody*>(b.nativeBody());cpBodySleep(nativeBody);
            expect(cpBodyIsSleeping(nativeBody),"anchor wake fixture is asleep");
            pivot.setAnchorA(pdg::Point(0,6));advance(1);
            expect(!cpBodyIsSleeping(nativeBody),"anchor change wakes connected sleeping bodies");
        }
#endif
        cleanupLayer(layer);
    }
}
