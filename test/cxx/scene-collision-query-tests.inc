void collisionQueryChecks() {
    using namespace pdg;
    for (bool physical : {false,true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if(physical) continue;
#endif
        Scene scene,other;scene.setManual(true);other.setManual(true);
        auto* world=scene.createSpriteLayer();auto* actors=scene.createSpriteLayer();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        world->setUseChipmunkPhysics(physical);actors->setUseChipmunkPhysics(physical);
#endif
        world->setQueryBits(1);actors->setQueryBits(2);
        auto* box=world->createSprite();auto& a=box->setupCollider().setBox(pdg::Rect(10,-1,12,1));
        auto* disk=actors->createSprite();auto& b=disk->setupCollider().setCircle(2,pdg::Point(20,0));
        auto* cap=world->createSprite();cap->setupCollider().setCapsule(pdg::Point(30,0),pdg::Point(34,0),1);
        CollisionQueryOptions options;CollisionQueryBuffer hits(2);
        options.maxHits=2;
        const auto& shared=scene.raycast(pdg::Point(),pdg::Point(40,0),options.maxHits,options);
        check(shared.size()==2 && shared[0].collider==&a,"Scene-owned capped results");
        auto* sharedAddress=&shared;
        options.maxHits=1;
        const auto& reused=scene.overlapCircle(pdg::Point(20,0),3,options);
        check(&reused==sharedAddress && reused.size()==1 && shared[0].collider==&b,"Scene-owned result vector reused");
        auto independent=scene.nearestPoint(pdg::Point(20,0),0);
        check(shared.empty() && independent->collider==&b,"Single query invalidates previous array");
        options.maxHits=0;check(scene.raycast(pdg::Point(),pdg::Point(40,0),options.maxHits,options).empty(),"Zero hit limit");
        options.maxHits=16;
        check(scene.raycast(pdg::Point(0,0),pdg::Point(40,0),options,hits)==2,"Ray hits bounded capacity");
        check(hits.isOverflowed(),"Ray overflow reported");check(hits.getCollider(0)==&a,"Earliest hit wins");
        checkNear(hits.getFraction(0),.25);checkNear(hits.getPoint(0).x,10);checkNear(hits.getNormal(0).x,-1);
        checkNear(hits.getDistance(1),18);
        scene.sweepCircle(pdg::Point(0,0),1,Vector(40,0),options,hits);
        checkNear(hits.getDistance(0),9);checkNear(hits.getPoint(0).x,10);checkNear(hits.getNormal(0).x,-1);
        scene.raycast(pdg::Point(11,0),pdg::Point(11,0),options,hits);
        check(hits.getCount()==1 && hits.getInitialOverlap(0),"Zero ray initial containment");
        checkNear(hits.getNormal(0).x,0);check(!hits.isOverflowed(),"Reuse resets overflow");
        auto nearest=scene.nearestPoint(pdg::Point(15,0),10,options);
        check(bool(nearest),"Nearest returns a hit");checkNear(nearest->distance,3);
        check(nearest->collider==&a,"Nearest tie uses collider ID");
        nearest=scene.nearestPoint(pdg::Point(20,0),0);checkNear(nearest->point.x,20);checkNear(nearest->distance,0);
        check(!scene.nearestPoint(pdg::Point(15,0),2),"Nearest respects distance limit");
        auto first=scene.raycast(pdg::Point(),pdg::Point(40,0));
        check(first && first->collider==&a,"Single ray returns earliest hit");
        auto swept=scene.sweepCircle(pdg::Point(),1,Vector(40,0));checkNear(swept->distance,9);
        check(!scene.raycast(pdg::Point(0,10),pdg::Point(40,10)),"Single ray miss is empty");
        options.layerMask=2;scene.raycast(pdg::Point(),pdg::Point(40,0),options,hits);
        check(hits.getCount()==1 && hits.getCollider(0)==&b,"Layer masks select actors");
        options.layers=std::vector<SpriteLayer*>{world};scene.raycast(pdg::Point(),pdg::Point(40,0),options,hits);
        check(!hits.getCount(),"Explicit selection intersects masks");
        options={};options.excludedColliders={&a};options.predicate=[&](const Collider& c){return &c==&b;};
        scene.raycast(pdg::Point(),pdg::Point(40,0),options,hits);check(hits.getCount()==1 && hits.getCollider(0)==&b,"Predicate precedes capacity selection");
        options.predicate=[](const Collider&)->bool{throw std::runtime_error("predicate");};
        bool rejected=false;try{scene.raycast(pdg::Point(),pdg::Point(40,0),options,hits);}catch(...){rejected=true;}
        check(rejected && hits.getCount()==0,"Predicate failure clears partial results");
        options={};b.setSensor(true);options.includeSensors=false;
        scene.overlapCircle(pdg::Point(20,0),3,options,hits);check(!hits.getCount(),"Sensor selection");
        options={};scene.overlapBox(RotatedRect(pdg::Rect(18,-.5,22,.5),.5),options,hits);check(hits.getCount()==1,"Oriented box overlap");
        scene.overlapCapsule(pdg::Point(15,0),pdg::Point(25,0),.5,options,hits);check(hits.getCount()==1,"Capsule overlap");
        scene.pause();scene.overlapPoint(pdg::Point(20,0),options,hits);check(hits.getCount()==1,"Paused scene queries");
        scene.setTimeScale(0);disk->setLocation(100,0);scene.overlapPoint(pdg::Point(20,0),options,hits);check(!hits.getCount(),"Teleports refresh paused queries");
        auto* concave=world->createSprite();concave->setLocation(50,0);
        auto& c=concave->setupCollider().setPolygon({pdg::Point(0,0),pdg::Point(4,0),pdg::Point(4,1),pdg::Point(1,1),pdg::Point(1,4),pdg::Point(0,4)});
        scene.overlapPoint(pdg::Point(53,3),options,hits);check(!hits.getCount(),"Concave empty region preserved");
        scene.raycast(pdg::Point(49,.5),pdg::Point(55,.5),options,hits);check(hits.getCount()==1 && hits.getCollider(0)==&c,"Decomposition yields one public shape hit");
        auto* part=concave->createPart("query");part->setLocation(10,0);part->setupCollider().setCircle(1);
        scene.overlapPoint(pdg::Point(60,0),options,hits);check(hits.getCount()==1 && hits.getCollider(0)==part->collider.operator->(),"Part collider membership");
        auto* particle=world->createParticle();particle->setLocation(70,0);particle->setupCollider().setCircle(1);
        scene.overlapPoint(pdg::Point(70,0),options,hits);check(hits.getCount()==1 && hits.getCollider(0)==particle->collider.operator->(),"Particle collider membership");
        options.predicate=[&](const Collider&)->bool{hits.clear();return true;};rejected=false;
        try{scene.overlapPoint(pdg::Point(70,0),options,hits);}catch(...){rejected=true;}
        check(rejected && !hits.getCount(),"Cannot clear a buffer during its query");options={};
#ifndef PDG_NO_GUI
        auto* image=new ImageOpenGL();image->addRef();image->initEmpty(3,3,32);
        std::memset(image->data,255,36);static_cast<uint8*>(image->data)[4*4+3]=0;
        auto* masked=world->createSprite();masked->setLocation(80,0);
        masked->setupCollider().setImageMask(*image,pdg::Rect(0,0,3,3));image->release();
        scene.overlapPoint(pdg::Point(81.5,1.5),options,hits);check(!hits.getCount(),"Image mask hole is empty");
        nearest=scene.nearestPoint(pdg::Point(81.5,1.5),1,options);checkNear(nearest->distance,.5);
        scene.raycast(pdg::Point(79,1.5),pdg::Point(84,1.5),options,hits);check(hits.getCount()==1,"Image mask pieces deduplicate");
#endif
        scene.removeLayer(actors);scene.overlapPoint(pdg::Point(120,0),options,hits);check(!hits.getCount(),"Detach updates query scope immediately");
        options.layers=std::vector<SpriteLayer*>{actors};rejected=false;
        try{scene.overlapPoint(pdg::Point(),options,hits);}catch(...){rejected=true;}check(rejected,"Detached layer selection rejected");
        other.addLayer(actors);options={};other.overlapPoint(pdg::Point(120,0),options,hits);check(hits.getCount()==1,"Transfer searchable before first step");
        auto singleRetained=other.raycast(pdg::Point(110,0),pdg::Point(130,0));
        auto copiedHit=singleRetained;
        singleRetained.reset();
        auto* retained=hits.getCollider(0);other.dispose();check(retained->isPresent() && !retained->isAttached(),"Buffer retains removed colliders");hits.clear();check(copiedHit->collider->isPresent(),"Copied single hit retains removed collider");copiedHit.reset();
        CollisionQueryBuffer empty(0);scene.raycast(pdg::Point(),pdg::Point(40,0),options,empty);check(empty.isOverflowed()&&!empty.getCount(),"Zero capacity reports matches");
        scene.dispose();rejected=false;try{scene.overlapPoint(pdg::Point(),options,hits);}catch(...){rejected=true;}check(rejected,"Disposed scene query rejected");
    }
}
