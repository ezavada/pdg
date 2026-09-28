// Graph restoration: owners precede shapes, compound links, joints and controllers.
void physicsGraphSnapshots() {
    using namespace pdg;
    auto makeLayer=[](bool native) {
        auto* layer=SpriteManager::createSpriteLayer();SpriteManager::getSingletonInstance()->addLayer(layer);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(native);layer->setGravity(0);layer->setDamping(1);
#endif
        return layer;
    };
    auto load=[](SpriteLayer* target,Serializer& writer,size_t size) {
        auto* bytes=std::malloc(size);std::memcpy(bytes,writer.getDataPtr(),size);
        Deserializer reader(bytes,size);target->deserialize(&reader);
    };
    for(bool native:{false,true}) for(bool tags:{false,true})
    for(int mode:{serialization_Complete,serialization_ExternalReferences}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if(native)continue;
#endif
        auto* source=makeLayer(native),*copy=makeLayer(native);
        source->enableCollisions();
        auto* box=source->createSprite();box->spriteId=100;box->setSize(4,8);
        auto& bc=box->setupFrameCollider(frameCollider_Bounds,37);
        const auto frameId=bc.getShapeId(0);const auto removed=bc.addCircle(.2,pdg::Point(100,0));bc.removeShape(removed);
        const auto extra=bc.addCircle(.5,pdg::Point(0,6));
        bc.setFriction(.2).setRestitution(1).setWantsContactEvents(true);
        box->setupPhysicsBody().setMode(physicsBody_Static);
        auto* ball=source->createSprite();ball->spriteId=200;ball->setLocation(-8,0);
        ball->setupPhysicsBody(2,3).setRestitution(1).setVelocity(Vector(10,0));
        ball->setupCollider().setCircle(1).setCategory(3).setCollisionMask(5).setGroup(9);
        auto* decoration=ball->createPart("compound");decoration->setLocation(0,30);
        auto& pc=decoration->setupCollider();
        const auto polygon=pc.addPolygon({{0,0},{6,0},{6,6},{4,6},{4,2},{2,2},{2,6},{0,6}});
        pc.setPhysicsBody(box->physics).setSensor(true).setEnabled(false);
        // Every constraint family has its own pair, including cross-Sprite endpoints.
        for(int type=constraint_Pin;type<=constraint_Motor;++type) {
            auto* a=source->createSprite(),*b=source->createSprite();
            a->spriteId=300+type*2;b->spriteId=301+type*2;a->setLocation(0,100+type*10);b->setLocation(3,100+type*10);
            auto& x=a->setupPhysicsBody();auto& y=b->setupPhysicsBody();PhysicsConstraint* joint=nullptr;
            switch(type) {
                case constraint_Pin:joint=&x.createPinJoint(y);break;
                case constraint_Slide:joint=&x.createSlideJoint(y,pdg::Point(),pdg::Point(),1,4);break;
                case constraint_Pivot:joint=&x.createPivotJoint(y,pdg::Point(3,0));break;
                case constraint_Groove:joint=&x.createGrooveJoint(y,pdg::Point(0,0),pdg::Point(5,0),pdg::Point());break;
                case constraint_Spring:joint=&x.createSpring(y,pdg::Point(),pdg::Point(),2,8,1);break;
                case constraint_RotarySpring:joint=&x.createRotarySpring(y,.2,8,1);break;
                case constraint_RotaryLimit:joint=&x.createRotaryLimit(y,-.3,.6);break;
                case constraint_Ratchet:joint=&x.createRatchet(y,.2,.1);break;
                case constraint_Gear:joint=&x.createGear(y,2,.1);break;
                case constraint_Motor:joint=&x.createMotor(y,.3,30);break;
            }
            joint->setMaxForce(300+type).setBreakForce(900+type).setCollideBodies(type%2);
            if(type==constraint_Groove)joint->setGroove(pdg::Point(-3,1),pdg::Point(6,2)).setAnchorB(pdg::Point(-.5,.75));
            else if(type<=constraint_Spring)joint->setAnchors(pdg::Point(1.25,2.5),pdg::Point(-.5,.75));
        }
        Serializer writer;writer.setSendTags(tags);writer.setResourceMode(mode);
        auto size=source->getSerializedSize(&writer);source->serialize(&writer);
        expect(size+(tags?3:0)==writer.getDataSize(),"physics graph size matches emitted records");
        auto* keep=copy->createSprite();keep->setupPhysicsBody().setVelocity(Vector(7,8));
        bool rejected=false;try{load(copy,writer,writer.getDataSize()-1);}catch(const std::exception&){rejected=true;}
        expect(rejected&&copy->getNthSprite(0)==keep,"truncated graph cannot replace the live layer");
        near(keep->physics.getVelocity().x,7,"failed graph load preserves live motion");
        load(copy,writer,writer.getDataSize());
        auto* copiedBox=copy->getNthSprite(0),*copiedBall=copy->getNthSprite(1);
        auto& c=static_cast<Collider&>(copiedBox->collider);
        expect(c.getId()!=bc.getId(),"restored colliders have distinct live identities");
        expect(c.getGeometrySource()==colliderSource_Frame&&c.getShapeId(0)==frameId&&c.getShapeId(1)==extra,"frame source and additive shape identities survive");
        near(c.getFriction(),.2,"collider material override survives");
        expect(c.getWantsContactEvents(),"contact event opt-in survives without callback closures");
        copiedBox->setSize(6,8);expect(c.getShapeId(0)==frameId&&c.contains(pdg::Point(2.8,0)),"restored source continues following owner size");copiedBox->setSize(4,8);
        expect(c.addCircle(.1,pdg::Point(100,0))>extra,"removed shape IDs are not recycled after load");
        auto& cc=static_cast<Collider&>(copiedBall->findPart("compound")->collider);
        expect(cc.getShapeId(0)==polygon&&cc.getShapeType(polygon)==collisionShape_Polygon,"concave Part geometry survives");
        expect(&cc.getPhysicsBody()==&static_cast<PhysicsBody&>(copiedBox->physics),"compound association resolves a forward body reference");
        expect(cc.isSensor()&&!cc.isEnabled(),"sensor and disabled state survive");
        expect(copiedBall->collider.getCategory()==3&&copiedBall->collider.getCollisionMask()==5&&copiedBall->collider.getGroup()==9,"collision filters survive");
        copiedBall->physics.setFriction(.4);near(copiedBall->collider.getFriction(),.4,"default material still follows body after loading");
        for(int type=constraint_Pin;type<=constraint_Motor;++type) {
            auto* a=copy->getNthSprite(2+(type-1)*2),*b=copy->getNthSprite(3+(type-1)*2);
            expect(a->physics.getConstraintCount()==1&&b->physics.getConstraintCount()==1,"one constraint shared by both restored endpoints");
            auto& j=a->physics.getConstraint(0);
            expect(&j==&b->physics.getConstraint(0)&&j.getType()==type&&&j.getBodyB()==&static_cast<PhysicsBody&>(b->physics),"constraint type and endpoint identity survive");
            near(j.getMaxForce(),300+type,"constraint force cap survives");near(j.getBreakForce(),900+type,"constraint break force survives");
            expect(j.getCollideBodies()==bool(type%2),"constraint collision policy survives");
            if(type<=constraint_Spring)expect(j.getAnchorB()==pdg::Point(-.5,.75),"edited B anchor survives snapshots before its first solve");
            if(type==constraint_Groove)expect(j.getGrooveStart()==pdg::Point(-3,1)&&j.getGrooveEnd()==pdg::Point(6,2),"edited groove track survives snapshots");
            else if(type<=constraint_Spring)expect(j.getAnchorA()==pdg::Point(1.25,2.5),"edited A anchor survives snapshots");
        }
        c.setWantsContactEvents(false);bc.setWantsContactEvents(false);
        int contacts=0;copiedBall->collider.setContactHandler([&](const ColliderContact&){++contacts;});
        for(int i=0;i<100;++i) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            SpriteManager::getSingletonInstance()->stepAnimationPhysics(10);
#endif
            copy->animateLayer(10);
        }
        expect(contacts>0&&copiedBall->physics.getVelocity().x<0,"restored balls collide and rebound from the restored box");
        cleanupLayer(copy);cleanupLayer(source);
    }
    // Reject invalid graph references/configuration before replacing a live Layer.
    {
        auto* source=makeLayer(false),*copy=makeLayer(false);
        auto* s=source->createSprite();s->setupPhysicsBody();s->createPart("part")->setupPhysicsBody();
        auto* keep=copy->createSprite();
        auto& joint=s->physics.createRotaryLimit(s->findPart("part")->physics,0,.875);
        joint.setMaxForce(123.375);
        for(int invalid=0;invalid<=4;++invalid) {
            SnapshotTestWriter writer;writer.setSendTags(false);
            writer.onDouble=[&](uint64& n) {
                if(n==snapshotBits(.875)) {
                    if(invalid==0){writer.replaceByte(writer.previousInteger-1,99);++writer.mutations;} // type
                    if(invalid==1){writer.replaceByte(writer.lastInteger,99);++writer.mutations;} // body B
                    if(invalid==2){n=snapshotBits(-1.);++writer.mutations;} // inverted limits
                }
                if(n==snapshotBits(123.375) && invalid==3){n=snapshotBits(double(NAN));++writer.mutations;}
            };
            source->serialize(&writer);auto reader=snapshotReader(writer);bool rejected=false;
            try{copy->deserialize(reader.get());}catch(const std::exception&){rejected=true;}
            if(invalid<4)expect(writer.mutations==1 && rejected && copy->getNthSprite(0)==keep,
                "invalid constraint types, endpoints, limits and force caps preserve live scene");
            else expect(!rejected && copy->getNthSprite(0)->physics.getConstraintCount()==1,"valid graph mutation fixture remains readable");
        }
        source->setSerializationFlags(ser_InitialData|ser_Positions);
        bool rejected=false;try{Serializer writer;source->serialize(&writer);}catch(const std::runtime_error&){rejected=true;}
        expect(rejected,"selected state must include bodies referenced by the graph");
        joint.disconnect();cleanupLayer(copy);cleanupLayer(source);
    }
    // Masks store decomposed geometry; frame sources still react to new frames.
    for(int mode:{serialization_Complete,serialization_ExternalReferences}) {
#ifdef PDG_NO_GUI
        auto* image=new ImageImpl();
#else
        auto* image=new ImageOpenGL();
#endif
        image->addRef();image->initEmpty(5,5,32);std::memset(image->data,255,100);
        for(int y=1;y<4;++y)for(int x=1;x<4;++x)static_cast<uint8*>(image->data)[y*image->pitch+x*4+3]=0;
        Sprite source;source.addFramesImage(image);source.setupFrameCollider(frameCollider_AlphaMask,200);
        auto* mask=source.createPart("mask");mask->setupCollider().setImageMask(*image,pdg::Rect(0,0,5,5));
        image->release();Serializer writer;writer.setResourceMode(mode);source.serialize(&writer);
        auto* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());Deserializer reader(bytes,writer.getDataSize());
        Sprite copy;copy.deserialize(&reader);auto& c=static_cast<Collider&>(copy.findPart("mask")->collider);
        expect(c.contains(pdg::Point(.5,.5))&&!c.contains(pdg::Point(2.5,2.5)),"explicit mask geometry preserves transparent holes");
        expect(!copy.collider.contains(pdg::Point(0,0)),"restored frame alpha mask preserves its transparent hole");
        copy.setScale(2);expect(copy.collider.contains(pdg::Point(4,0))&&!copy.collider.contains(pdg::Point(0,0)),"restored frame mask rebuilds from shared artwork after scaling");
    }
    {
        Sprite source;auto* a=source.createPart("a"),*b=source.createPart("b"),*c=source.createPart("c");
        a->setupPhysicsBody();b->setupPhysicsBody();c->setupPhysicsBody();
        c->physics.createPivotJoint(b->physics);a->physics.createRotaryLimit(b->physics,0,1);
        Serializer writer;source.serialize(&writer);auto* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
        Deserializer reader(bytes,writer.getDataSize());Sprite copy;copy.deserialize(&reader);
        auto& restored=static_cast<PhysicsBody&>(copy.findPart("b")->physics);
        expect(restored.getConstraint(0).getType()==constraint_Pivot&&restored.getConstraint(1).getType()==constraint_RotaryLimit,"per-body constraint ordering survives different owner creation order");
    }
    // Standalone graphs cannot silently discard references to other Sprites.
    Sprite a,b;auto& x=a.setupPhysicsBody();auto& y=b.setupPhysicsBody();x.createPivotJoint(y);
    Serializer outside;bool rejected=false;try{a.serialize(&outside);}catch(const std::runtime_error&){rejected=true;}
    expect(rejected&&outside.getDataSize()==0,"external runtime body link rejects before writing a standalone Sprite");
    x.disconnect();a.setupCollider().setCollisionFilter([](const Collider&,const Collider&){return true;});
    rejected=false;try{a.serialize(&outside);}catch(const std::runtime_error&){rejected=true;}
    expect(rejected&&outside.getDataSize()==0,"callback collision filters reject explicitly before writing");
}
