// Independent segment-distance checks for the rounded separating-axis geometry.
void capsuleColliders() {
    using namespace pdg;
    using P = pdg::Point;
    auto distance=[](P p,P a,P b) {
        const double dx=double(b.x)-a.x,dy=double(b.y)-a.y,length=dx*dx+dy*dy;
        const double t=length?std::clamp(((double(p.x)-a.x)*dx+(double(p.y)-a.y)*dy)/length,0.,1.):0;
        return std::hypot(double(p.x)-a.x-t*dx,double(p.y)-a.y-t*dy);
    };
    auto segmentDistance=[&](P a,P b,P c,P d) {
        auto cross=[](P x,P y,P p){return (double(y.x)-x.x)*(double(p.y)-x.y)-(double(y.y)-x.y)*(double(p.x)-x.x);};
        if(cross(a,b,c)*cross(a,b,d)<0 && cross(c,d,a)*cross(c,d,b)<0)return 0.;
        return std::min({distance(a,c,d),distance(b,c,d),distance(c,a,b),distance(d,a,b)});
    };
    auto rejects=[](auto fn){try{fn();}catch(const std::exception&){return true;}return false;};
    Sprite owner;auto& capsule=owner.setupCollider();
    const auto id=capsule.addCapsule(P(-3,0),P(3,0),1);
    expect(capsule.getShapeCount()==1&&capsule.getShapeType(id)==collisionShape_Capsule,"capsule is one logical shape");
    near(capsule.getCapsuleStart(id).x,-3,"capsule start query");near(capsule.getCapsuleEnd(id).x,3,"capsule end query");
    near(capsule.getCapsuleRadius(id),1,"capsule radius query");
    near(capsule.getBounds().left,-4,"bounds include start cap");near(capsule.getBounds().right,4,"bounds include end cap");
    expect(capsule.contains(P(0,1))&&!capsule.contains(P(0,1.01)),"capsule straight boundary");
    for(int i=0;i<90;++i) {
        const double angle=i*.071;
        expect(capsule.contains(P(3+.999*std::cos(angle),.999*std::sin(angle))),"round end is not an inscribed polygon");
    }
    expect(!capsule.contains(P(3.8,.8)),"capsule excludes bounding-box corner");
    const auto circle=capsule.addCircle(.5,P(10,0));
    expect(capsule.getShapeId(0)==id&&capsule.getShapeId(1)==circle,"additions preserve stable sibling IDs");
    for(double radius:{0.,-1.,double(NAN),double(INFINITY)}) {
        expect(rejects([&]{capsule.setCapsule(P(),P(3,0),radius);}),"invalid capsule radius rejected");
        expect(capsule.getShapeId(0)==id&&capsule.getShapeCount()==2,"failed replacement is atomic");
    }
    expect(rejects([&]{capsule.addCapsule(P(NAN,0),P(),1);}),"nonfinite start rejected");
    expect(rejects([&]{capsule.addCapsule(P(),P(0,INFINITY),1);}),"nonfinite end rejected");
    expect(rejects([&]{capsule.getCapsuleRadius(circle);})&&rejects([&]{capsule.getCapsuleEnd(999);}),"getters reject wrong type and missing ID");
    expect(rejects([&]{capsule.getCircleRadius(id);}),"circle getter rejects capsules");
    expect(Collider::NoCollider.addCapsule(P(),P(1,0),1)==collisionShape_None,"NoCollider ignores capsule additions");
    expect(&Collider::NoCollider.setCapsule(P(),P(1,0),1)==&Collider::NoCollider,"NoCollider ignores capsule replacement");
    capsule.setCapsule(P(2,3),P(2,3),2);
    expect(capsule.getShapeType(capsule.getShapeId(0))==collisionShape_Capsule,"collapsed capsule retains its public type");
    expect(capsule.contains(P(4,3))&&!capsule.contains(P(4.01,3)),"coincident cap centers behave as a circle");
    owner.setSize(2,2);owner.setupFrameCollider(frameCollider_Bounds);
    const auto sourceId=capsule.getShapeId(0),extra=capsule.addCapsule(P(10,0),P(12,0),1);
    owner.setSize(6,6);
    expect(capsule.getShapeId(0)==sourceId&&capsule.getShapeId(1)==extra&&capsule.contains(P(12.9,0)),"capsule additions survive source updates");
    capsule.setCapsule(P(-3,0),P(3,0),1);
    expect(capsule.getGeometrySource()==colliderSource_Explicit,"setCapsule replaces a frame source");
    owner.setScale(-2,2).setRotation(.5).setLocation(20,30);
    const auto frame=SpatialTransform::fromTRS(20,30,.5,-2,2);
    expect(capsule.contains(frame.transformPoint(P(3.8,.4))),"uniformly reflected and rotated cap stays exact");
    expect(!capsule.contains(frame.transformPoint(P(3.8,.8))),"reflected cap preserves its boundary");
    owner.setLocation(0,0).setRotation(0).setScale(2,1);
    near(capsule.getBounds().right,8,"nonuniform capsule bound");
    expect(capsule.contains(P(7.5,.3))&&!capsule.contains(P(7.5,.9)),"nonuniform cap uses ellipse geometry");
    SpatialTransform shear;shear.c=.75;
    Collider deformed;deformed.attach([&]{return shear;},[]()->PhysicsBody&{return PhysicsBody::NoPhysics;});
    deformed.setCapsule(P(-3,0),P(3,0),1);
    expect(deformed.contains(shear.transformPoint(P(3.7,.4)))&&!deformed.contains(shear.transformPoint(P(3.8,.8))),"sheared capsule queries");
    owner.setScale(1,1);Sprite peer;auto& other=peer.setupCollider();
    uint32_t random=7;auto sample=[&]{random=1664525u*random+1013904223u;return float(double(random)/4294967296.*16-8);};
    for(int i=0;i<800;++i) {
        const P a(sample(),sample()),b(sample(),sample()),c(sample(),sample()),d(sample(),sample());
        capsule.setCapsule(a,b,.7);other.setCircle(.4,c);
        expect(capsule.overlaps(other)==(distance(c,a,b)<=1.1),"capsule/circle agrees with segment distance");
        other.setCapsule(c,d,.4);
        expect(capsule.overlaps(other)==(segmentDistance(a,b,c,d)<=1.1),"capsule/capsule agrees with segment distance");
        expect(capsule.overlaps(other)==other.overlaps(capsule),"capsule overlap is symmetric");
        const P corners[]={{-2,-1},{2,-1},{2,1},{-2,1}};double gap=INFINITY;
        for(int edge=0;edge<4;++edge)gap=std::min(gap,segmentDistance(a,b,corners[edge],corners[(edge+1)%4]));
        if((std::abs(a.x)<=2&&std::abs(a.y)<=1)||(std::abs(b.x)<=2&&std::abs(b.y)<=1))gap=0;
        other.setBox(pdg::Rect(-2,-1,2,1));
        expect(capsule.overlaps(other)==(gap<=.7),"capsule/polygon agrees with segment-to-box distance");
    }
    other.setPolygon({{0,0},{6,0},{6,6},{4,6},{4,2},{2,2},{2,6},{0,6}});capsule.setCapsule(P(3,3),P(3,5),.4);
    expect(!capsule.overlaps(other),"capsule fits inside concave gap");
    capsule.setCapsule(P(1,3),P(1,5),.4);expect(capsule.overlaps(other),"capsule meets concave solid region");
    for(bool native:{false,true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if(native)continue;
#endif
        auto* manager=SpriteManager::getSingletonInstance();auto* layer=SpriteManager::createSpriteLayer();manager->addLayer(layer);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(native);layer->setGravity(0);layer->setDamping(1);
#endif
        layer->enableCollisions();auto* wall=layer->createSprite();wall->setupPhysicsBody().setMode(physicsBody_Static);
        wall->setupCollider().setCapsule(P(10,-10),P(10,10),1);
        auto* mover=layer->createParticle();mover->setLifetime(0);mover->setupPhysicsBody(1,100).setVelocity(10,0).setRestitution(0);
        auto& moving=mover->setupCollider().setCapsule(P(0,0),P(4,0),1);int begins=0,ends=0;const auto movingId=moving.getShapeId(0);
        moving.setContactHandler([&](const ColliderContact& event){
            expect(event.shape==movingId,"contact preserves capsule ID");
            if(event.phase==collision_Begin)++begins;if(event.phase==collision_End)++ends;
            expect(std::isfinite(event.normal.x)&&std::isfinite(event.penetration),"finite capsule manifold");
        });
        auto tick=[&]{
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            if(native)manager->stepAnimationPhysics(10);
#endif
            layer->animateLayer(10);
        };
        for(int i=0;i<80;++i)tick();
        expect(begins==1&&mover->getLocation().x<4.5,"capsule bodies collide and retain resting contacts");
        expect(mover->physics.getVelocity().x<.1,"capsule collision stops forward movement");
        mover->setLocation(-20,0);tick();expect(ends==1,"separating capsule delivers End");
        moving.setContactHandler({});moving.setCapsule(P(),P(),1).setSensor(true);mover->setLocation(9,0);
        int touching=0;moving.setContactHandler([&](const ColliderContact&){++touching;});tick();
        expect(touching>0,"collapsed capsule participates in both solvers");
        moving.setContactHandler({});cleanupLayer(layer);
    }
    for(bool tags:{false,true})for(int mode:{serialization_Complete,serialization_ExternalReferences}) {
        Sprite original;auto* part=original.createPart("capsule");original.setupPhysicsBody();part->setupPhysicsBody();
        auto& c=part->setupCollider().setCapsule(P(-2.125,3.5),P(7.75,-4.25),.875).setPhysicsBody(original.physics);
        const auto saved=c.getShapeId(0);c.addCircle(2);Serializer writer;writer.setSendTags(tags);writer.setResourceMode(mode);
        const auto size=original.getSerializedSize(&writer);original.serialize(&writer);
        expect(writer.getDataSize()==size+(tags?3:0),"capsule snapshot byte count");
        auto reader=snapshotReader(writer);Sprite copy;copy.deserialize(reader.get());auto& restored=copy.findPart("capsule")->collider;
        expect(restored.getShapeId(0)==saved&&restored.getShapeType(saved)==collisionShape_Capsule,"capsule type/ID round-trip");
        near(restored.getCapsuleStart(saved).x,-2.125,"capsule start round-trip");near(restored.getCapsuleEnd(saved).y,-4.25,"capsule end round-trip");
        near(restored.getCapsuleRadius(saved),.875,"capsule radius round-trip");
        expect(&restored.getPhysicsBody()==copy.physics.operator->(),"capsule compound association round-trip");
    }
    auto* source=SpriteManager::createSpriteLayer();auto* destination=SpriteManager::createSpriteLayer();
    source->createSprite()->setupCollider().setCapsule(P(10.125,1),P(3,4),.875);auto* keep=destination->createSprite();
    for(int invalid=0;invalid<3;++invalid) {
        SnapshotTestWriter writer;writer.setSendTags(false);
        writer.onDouble=[&](uint64& value){if(value==snapshotBits(.875)&&invalid<2){value=snapshotBits(invalid?-1.:double(NAN));++writer.mutations;}};
        writer.onWord=[&](uint32& value){if(value==snapshotBits(10.125f)&&invalid==2){value=snapshotBits(float(INFINITY));++writer.mutations;}};
        source->serialize(&writer);auto reader=snapshotReader(writer);
        expect(writer.mutations==1&&rejects([&]{destination->deserialize(reader.get());}),"malformed capsule rejected");
        expect(destination->getNthSprite(0)==keep,"malformed capsule preserves live layer");
    }
    delete source;delete destination;
}
