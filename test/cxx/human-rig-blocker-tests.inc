// Exercise the real human asset: wrapped wrist angles, articulated contact,
// damped release, and delayed animation ticks must keep the arm connected.
void humanRigBlocker(const std::string& directory) {
    using namespace pdg;
    constexpr double scale=518.0/170,gravity=980*scale;
    for(int dt:{5,10,16,33,47}) {
#ifdef PDG_NO_GUI
        auto* layer=createSpriteLayer();
#else
        auto* layer=createSpriteLayer(nullptr);
#endif
        layer->setUseChipmunkPhysics(true);layer->enableCollisions();
        layer->setGravity(gravity);layer->setDamping(1);
        auto* sprite=layer->createSpriteFromSpriterFile((directory+"../human-rig/human.scml").c_str());
        sprite->setLocation(422,668);sprite->setScale(scale,scale);
        expect(sprite->enableAnimationPose("reference"),"human blocker reference pose enables");sprite->pauseAnimation();
        const auto reference=sprite->getAnimationPose();
        sprite->setupPhysicsFromAnimationRig(50,100*scale);
        sprite->setAnimationPhysicsMode(animationPhysics_Kinematic,0.0);
        const std::vector<std::string> arm={"left_upper_arm","left_forearm","left_hand"};
        std::vector<double> lengths,levers,masses;
        for(const auto& name:arm) {
            const auto center=sprite->findPart(name.c_str())->physics.getState();
            const auto pivot=sprite->getAnimationBoneTransform(name.c_str(),animationSpace_World);
            // SCML bone widths are display metadata, not physical lengths. Use
            // joint spacing, plus the traced wrist-to-fingertip length.
            const auto next=std::find(arm.begin(),arm.end(),name)+1;
            if(next==arm.end())lengths.push_back(10.874776291053095*scale);
            else {
                const auto local=reference.getLocalTransform(reference.getRig()->findBone(*next));
                lengths.push_back(std::hypot(local.x,local.y)*scale);
            }
            levers.push_back(std::hypot(center.x-pivot.x,center.y-pivot.y));
            masses.push_back(sprite->findPart(name.c_str())->physics.getMass());
        }
        for(AnimationBoneId id=0;id<reference.getRig()->getBoneCount();++id) {
            const auto name=reference.getRig()->getBone(id).name;
            auto* part=sprite->findPart(name.c_str());
            if(!part || !part->physics.isPresent())continue;
            const auto it=std::find(arm.begin(),arm.end(),name);
            const bool selected=it!=arm.end();
            part->collider.setCategory(selected?2:1).setCollisionMask(selected?4:0).setFriction(.4).setRestitution(0);
            if(selected) {
                const auto i=size_t(it-arm.begin());
                double reach=0,ownMoment=0;
                for(size_t j=i;j<arm.size();++j) {
                    ownMoment+=masses[j]*(reach+levers[j]);
                    reach+=lengths[j]*(j==arm.size()-1?.5:1);
                }
                const double torque=gravity*(16*reach+ownMoment);
                sprite->setAnimationPhysicsDriveSettings({torque*.5/levers[i],torque*.5,i==0?12.:i==1?9.:6.,3.5},name.c_str());
            }
        }
        for(const auto& side:{"left","right"}) {
            const std::string upperName=std::string(side)+"_upper_arm",forearmName=std::string(side)+"_forearm";
            auto& upper=sprite->findPart(upperName.c_str())->physics;
            auto& forearm=sprite->findPart(forearmName.c_str())->physics;
            const auto a=sprite->getAnimationBoneTransform(upperName.c_str(),animationSpace_World);
            const auto b=sprite->getAnimationBoneTransform(forearmName.c_str(),animationSpace_World);
            const double bend=std::atan2(std::sin(b.rotation-a.rotation),std::cos(b.rotation-a.rotation));
            const double straight=forearm.getState().rotation-upper.getState().rotation-bend,pi=3.14159265358979323846;
            const bool left=std::string(side)=="left";
            upper.createRotaryLimit(forearm,straight+(left?-pi:2*pi/180),straight+(left?-2*pi/180:pi));
        }
        auto* obstacle=layer->createSprite();obstacle->setupPhysicsBody().setMode(physicsBody_Static);
        int contacts=0;double penetration=0;
        obstacle->setupCollider().setBox(pdg::Rect(472,205,652,223)).setCategory(4).setCollisionMask(2).setFriction(.4).setRestitution(0)
            .setContactHandler([&](const ColliderContact& c){if(c.phase!=collision_End){++contacts;penetration=std::max(penetration,c.penetration);}});
        sprite->startAnimation("wave_hello");
        sprite->setAnimationPhysicsMode(animationPhysics_Driven,"left_upper_arm",true,0);
        double gap=0,speed=0,extension=-180;int simulated=0;
        auto tick=[&](int milliseconds){for(int t=0;t<milliseconds;t+=dt) {
            const int step=std::min(dt,milliseconds-t);
            SpriteManager::getSingletonInstance()->stepAnimationPhysics(step);layer->animateLayer(step);
            simulated+=step;
            if(simulated>100) {
                const auto a=sprite->getAnimationBoneTransform("left_upper_arm",animationSpace_World);
                const auto b=sprite->getAnimationBoneTransform("left_forearm",animationSpace_World);
                extension=std::max(extension,std::atan2(std::sin(b.rotation-a.rotation),std::cos(b.rotation-a.rotation))*180/3.14159265358979323846);
            }
            for(const auto& name:{"left_forearm","left_hand"}) {
                const auto id=reference.getRig()->findBone(name),parent=reference.getRig()->getBone(id).parent;
                const auto expected=AnimationTransform::compose(sprite->getAnimationBoneTransform(reference.getRig()->getBone(parent).name.c_str(),animationSpace_World),reference.getLocalTransform(id));
                const auto actual=sprite->getAnimationBoneTransform(name,animationSpace_World);
                expect(std::isfinite(actual.x+actual.y+actual.rotation),"driven human transform remains finite");
                gap=std::max(gap,std::hypot(expected.x-actual.x,expected.y-actual.y));
                const auto state=sprite->findPart(name)->physics.getState();
                speed=std::max(speed,std::hypot(state.velocityX,state.velocityY));
            }
        }};
        tick(2600);
        near(sprite->getAnimationProgress(),2.6/6,"substeps advance the clip exactly once");
        sprite->seekAnimation("wave_hello",2.6);sprite->pauseAnimation();tick(1000);
        const auto blocked=sprite->getAnimationBoneTransform("left_hand",animationSpace_World);
        expect(contacts>0 && blocked.y>223,"wrist remains below the contacted blocker: "+std::to_string(blocked.y));
        obstacle->collider.setEnabled(false);tick(2000);
        const auto released=sprite->getAnimationBoneTransform("left_hand",animationSpace_World);
        expect(blocked.y-released.y>40,"removing the blocker lets the driven hand rise");
        double settleMin=1e9,settleMax=-1e9;
        for(int t=0;t<1000;t+=dt) {
            tick(std::min(dt,1000-t));
            const auto y=sprite->getAnimationBoneTransform("left_hand",animationSpace_World).y;
            settleMin=std::min(settleMin,y);settleMax=std::max(settleMax,y);
        }
        expect(settleMax-settleMin<2,"released arm settles without persistent spring oscillation");
        expect(extension< -1.5,"elbow stops two degrees short of straight, allowing half-degree solver tolerance: "+std::to_string(extension));
        expect(gap<2 && penetration<5 && speed<1200,"arm contact stays bounded without torn joints or tunneling");
        near(sprite->physics.getMass(),50,"blocker control preserves the 50 kg rig mass");
        expect(sprite->getAnimationPhysicsMode("left_upper_arm",true)==animationPhysics_Driven &&
               sprite->getAnimationPhysicsMode("right_upper_arm",true)==animationPhysics_Kinematic,"only the waving arm becomes driven");
        std::cout<<"Human blocker ("<<dt<<" ms): joint gap "<<gap<<" px, release "<<blocked.y-released.y
                 <<" px, settled travel "<<settleMax-settleMin<<" px\n";
        cleanupLayer(layer);
    }
}
