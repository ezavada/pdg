void particles() {
    using namespace pdg;
    static_assert(std::is_same_v<decltype(std::declval<Particle&>().setLocation(1,2).fadeTo(0,1)), Particle&>);
    static_assert(!std::is_base_of_v<Sprite, Particle>);
    Particle empty;
    expect(!empty.physics.isPresent() && !empty.collider.isPresent() && !empty.getParticleEmitter(), "particles allocate no optional components on read");
    near(empty.getLifetime(),1,"default lifetime is one second");
    empty.setLifetime(0).setMovement(10,0).animate(2);
    near(empty.getLocation().x,20,"bodyless constant movement");
    expect(empty.isAlive(),"zero lifetime is unlimited");
    bool rejected=false;
    try { empty.setLifetime(-1); } catch(const std::invalid_argument&) { rejected=true; }
    expect(rejected,"negative lifetime rejected");
    empty.setupPhysicsBody(2,3);
    rejected=false;try { empty.moveBy(1,2,.5); } catch(const std::logic_error&) { rejected=true; }
    expect(rejected,"dynamic ownership rejects scheduled movement");
    empty.physics.setVelocity(4,0);empty.fadeTo(0,.5);empty.animate(.5);
    near(empty.getLocation().x,22,"basic dynamic body advances once");near(empty.getOpacity(),0,"dynamic bodies still fade");
    empty.setupPhysicsBody(5,6);near(empty.physics.getMass(),5,"body setup reconfigures existing association");
    near(empty.physics.getVelocity().x,4,"body setup preserves velocity");
    { Serializer writer; rejected=false;
      try { writer.serialize_obj(&empty); } catch(const std::logic_error&) { rejected=true; }
      expect(rejected,"transient particles reject incomplete serialization"); }

    ParticleTrailOptions options;
    options.lifetime=.4;options.minDistance=0;options.sampleInterval=.01;options.maxPoints=16;
    ParticleTrail history(options);history.reset(pdg::Point(0,0),1);
    history.advance(.1,pdg::Point(10,0),1);
    expect(history.count==11,"fixed-interval trail samples include initial point");
    near(history.at(5).position.x,5,"coarse ticks interpolate sampling positions");
    history.advance(10,pdg::Point(20,0),1);
    expect(history.count<=16,"large steps keep bounded history and work");
    history.age(.41);expect(history.empty(),"retired history expires on simulation time");
    { auto o=options;o.maxPoints=128;ParticleTrail clipped(o);clipped.reset(pdg::Point(0,0),1);
      clipped.advance(1,pdg::Point(100,0),1);auto samples=clipped.samples();
      near(samples.front().position.x,60,"oldest ribbon segment clips at lifetime boundary");
      clipped.advance(.41,pdg::Point(100,0),1);expect(clipped.empty(),"stationary heads stop refreshing history"); }
    { Particle transient;transient.setLifetime(.1).setTrail(options).setMovement(100,0).animate(1);
      expect(!transient.hasTrail(),"detached expiry releases history"); }
    history.reset(pdg::Point(0,0),1);history.advance(1e200,pdg::Point(1,0),1);
    expect(history.count<=16,"extreme finite steps cannot spin the sampling loop");
    history.reset(pdg::Point(0,0),1);history.advance(.1,pdg::Point(1000,0),1);
    expect(history.count==1,"large discontinuities reset trail history");
    Particle traced;traced.setLifetime(0).setMovement(100,0).setTrail(options).animate(.1);
    expect(traced.getTrailPointCount()>1,"bodyless animation produces trail samples");
    traced.setLocation(100,100);expect(traced.getTrailPointCount()==1,"explicit teleports break trails");
    traced.animate(.1);traced.breakTrail();expect(traced.getTrailPointCount()==1,"explicit break preserves configuration");
    traced.clearTrail();expect(!traced.hasTrail(),"clear releases trail configuration");
    { Serializer writer;writer.setSendTags(false);auto arg=captureAnimationArgument(options);
      const auto size=serializeAnimationArgument(arg,&writer,false);serializeAnimationArgument(arg,&writer,true);
      expect(writer.getDataSize()==size,"trail option codec size matches write");
      void* bytes=std::malloc(writer.getDataSize());std::memcpy(bytes,writer.getDataPtr(),writer.getDataSize());
      Deserializer reader(bytes,writer.getDataSize());
      auto restored=std::any_cast<ParticleTrailOptions>(deserializeAnimationArgument(&reader));
      near(restored.lifetime,.4,"trail script options round trip");expect(restored.maxPoints==16,"trail capacity round trips"); }

    for(bool native : {false,true}) {
#ifndef PDG_USE_CHIPMUNK_PHYSICS
        if(native)continue;
#endif
        auto* manager=SpriteManager::getSingletonInstance();
        auto* layer=SpriteManager::createSpriteLayer();manager->addLayer(layer);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        layer->setUseChipmunkPhysics(native);layer->setGravity(0);layer->setDamping(1);
#endif
        auto tick=[&](unsigned milliseconds) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            if(native)manager->stepAnimationPhysics(milliseconds);
#endif
            layer->animateLayer(milliseconds);
        };
        auto* tracer=layer->createParticle();tracer->setLifetime(.2).setTrail(options);
        tracer->setupPhysicsBody().setVelocity(100,0);tracer->addRef();
        tick(100);expect(tracer->getTrailPointCount()>1,"physics trails sampled after body motion");
        layer->stopAnimations();tick(100);near(tracer->getAge(),.1,"paused layer freezes trail source");
        layer->startAnimations();tick(100);
        expect(!tracer->isAlive() && layer->getParticleCount()==0,"expired trail source releases particle slot");
        expect(layer->getParticleTrailCount()==1,"expired source leaves a fading visual tail");
        layer->stopAnimations();tick(1000);expect(layer->getParticleTrailCount()==1,"paused layer freezes retired tails");
        layer->startAnimations();tick(500);expect(layer->getParticleTrailCount()==0,"retired tails age out");tracer->release();
        Particle trailTemplate;trailTemplate.setLifetime(0).setMovement(100,0).setTrail(options).animate(.1);
        auto* trailEmitter=layer->createParticleEmitter();trailEmitter->setParticleTemplate(trailTemplate).setParticleSpeed(100).emit(2);
        auto* fresh=layer->getNthParticle(0);expect(fresh->hasTrail() && fresh->getTrailPointCount()==0,"emission copies configuration without template history");
        tick(100);expect(fresh->getTrailPointCount()>1,"fresh trails begin at spawn");
        fresh->expire();layer->removeAllParticles();expect(layer->getParticleTrailCount()==0,"explicit layer cleanup drops active and retired tails");
        layer->removeParticleEmitter(trailEmitter);
        tracer=layer->createParticle();tracer->setLifetime(.1).setTrail(options).setMovement(100,0);
        tick(1000);expect(layer->getParticleTrailCount()==0,"coarse expiry ticks age the remaining tail time");
        tracer=layer->createParticle();tracer->setLifetime(0).setTrail(options).setMovement(100,0);tracer->addRef();
        tick(100);layer->removeParticle(tracer);
        expect(layer->getParticleTrailCount()==0 && tracer->getTrailPointCount()==1,"explicit removal clears the trail without retiring it");tracer->release();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if(native) {
            auto* substepped=layer->createParticle();substepped->setLifetime(0).setTrail(options);
            substepped->setupPhysicsBody().setVelocity(100,0);
            for(int n=0;n<20;++n)manager->stepAnimationPhysics(10);
            layer->animateLayer(200);
            expect(substepped->getTrailPointCount()==16,"every physics substep contributes history exactly once");
            layer->removeAllParticles();
        }
#endif
        Particle prototype;prototype.setLifetime(1).setSize(4,6).fadeTo(0,1).grow(2,1,linearTween);
        auto* emitter=layer->createParticleEmitter();emitter->addRef();
        emitter->setParticleTemplate(prototype).setLocation(20,30).setRotation(0).setParticleSpeed(10).setEmissionRate(4).startEmitting();
        prototype.setLifetime(10).setOpacity(.2);
        tick(250);expect(layer->getParticleCount()==1,"continuous emission counts simulation time");
        auto* first=layer->getNthParticle(0);first->addRef();
        near(first->getAge(),0,"new particle begins at age zero");near(first->getOpacity(),1,"template settings are captured");
        tick(250);near(first->getAge(),.25,"layer advances each particle once");near(first->getLocation().x,22.5,"emission velocity advances independently");
        near(first->getOpacity(),.75,"template fade restarts at birth");near(first->getWidth(),5,"template growth is replayed");
        near(layer->getNthParticle(1)->getOpacity(),1,"particles do not share animation state");
        emitter->setLocation(200,300).stopEmitting();tick(250);near(first->getLocation().x,25,"moving emitter does not drag particles");
        expect(emitter->emit(2)==2,"bursts work while stopped");
        layer->removeParticleEmitter(emitter);tick(500);
        expect(!first->isAlive() && !first->getLayer(),"expiry removes layer association");
        expect(layer->getParticleCount()==3,"removing emitter leaves its emissions alive");
        first->release();emitter->release();layer->removeAllParticles();

        Particle relative;relative.setLifetime(0).moveBy(10,20,1,linearTween).andThen().moveBy(5,0,1,linearTween);
        emitter=layer->createParticleEmitter();emitter->setParticleTemplate(relative).setLocation(100,200);emitter->emit();
        first=layer->getNthParticle(0);tick(1000);near(first->getLocation().x,110,"relative template movement rebases at spawn");
        near(first->getLocation().y,220,"relative template y rebases at spawn");tick(1000);near(first->getLocation().x,115,"chained relative operations use predecessor pose");
        layer->removeAllParticles();

        Particle smoke;smoke.setLifetime(2);
        auto* spinning=layer->createParticle();spinning->setLifetime(0).setCenterOffset(Offset(2,0)).setSpin(2);
        spinning->setupParticleEmitter().setParticleTemplate(smoke).setLocation(4,0).setVelocityInheritance(1).emit();
        near(layer->getNthParticle(1)->getMovement().y,4,"burst inherits velocity around the particle rotation center");
        layer->removeAllParticles();
        auto* moving=layer->createParticle();moving->setLifetime(0).moveTo(100,0,1,linearTween);
        moving->setupParticleEmitter().setParticleTemplate(smoke).setEmissionRate(4).setVelocityInheritance(1).startEmitting();
        tick(250);near(layer->getNthParticle(1)->getMovement().x,100,"scheduled parent motion contributes inherited velocity");
        layer->removeAllParticles();
        Particle absolute;absolute.setLifetime(0).moveTo(10,20,1,linearTween);
        emitter->setParticleTemplate(absolute);emitter->emit();first=layer->getNthParticle(0);tick(1000);
        near(first->getLocation().x,10,"absolute template movement keeps its destination");
        layer->removeAllParticles();

        auto* rocket=layer->createParticle();rocket->addRef();rocket->setLifetime(.5).setRotation(float(3.14159265358979323846/2)).setMovement(0,20);
        auto& exhaust=rocket->setupParticleEmitter();exhaust.addRef();
        exhaust.setParticleTemplate(smoke).setLocation(2,0).setRotation(float(3.14159265358979323846)).setEmissionRate(4).setParticleSpeed(10);
        exhaust.startEmitting();tick(250);
        auto* trail=layer->getNthParticle(1);trail->addRef();
        near(trail->getLocation().x,0,"owned emitter local offset rotates with owner");near(trail->getLocation().y,7,"owned emitter uses current owner position");
        near(trail->getMovement().y,-10,"owned emitter facing is relative to owner");
        tick(250);expect(!rocket->isAlive() && !exhaust.isEmitting(),"expiry stops the owned emitter");
        expect(layer->getParticleCount()==2 && trail->isAlive(),"trails survive their parent");
        rocket->removeParticleEmitter();expect(!exhaust.getParticle() && !exhaust.getLayer(),"retained removed emitter safely detaches");
        rocket->release();exhaust.release();trail->release();layer->removeAllParticles();

        Particle nested;nested.setLifetime(0);nested.setupParticleEmitter().setParticleTemplate(smoke).setEmissionRate(100).startEmitting();
        emitter->setParticleTemplate(nested);layer->setMaxParticles(3);expect(emitter->emit(99)==3,"burst respects layer budget");
        expect(!layer->createParticle(),"manual creation reports full capacity");tick(100);
        expect(layer->getParticleCount()==3,"nested emitters share the layer budget");
        layer->removeAllParticles();layer->setMaxParticles(100);
        emitter->setParticleTemplate(smoke).setParticleSpeed(2,10).setSpread(1).setSeed(42);emitter->emit(2);
        auto a=layer->getNthParticle(0)->getMovement(),b=layer->getNthParticle(1)->getMovement();
        layer->removeAllParticles();emitter->setSeed(42);emitter->emit(2);
        near(layer->getNthParticle(0)->getMovement().x,a.x,"seed repeats initial velocity");near(layer->getNthParticle(1)->getMovement().y,b.y,"seed repeats subsequent velocity");
        layer->removeAllParticles();

        Particle physical;physical.setLifetime(1);physical.setupPhysicsBody(2,3).setAngularVelocity(2).setBreakAngularSpeed(1);
        physical.setupCollider().setCircle(1).setSensor(true);
        emitter->setParticleTemplate(physical).setLocation(0,0).setParticleSpeed(10).setSpread(0).setRotation(0);emitter->emit(2);
        first=layer->getNthParticle(0);auto* second=layer->getNthParticle(1);
        expect(first->physics.operator->()!=second->physics.operator->(),"emitted bodies are independent");
        expect(first->collider.operator->()!=second->collider.operator->(),"emitted colliders are independent");
        near(first->physics.getMass(),2,"physical template mass copied");near(first->physics.getMomentOfInertia(),3,"physical template inertia copied");
        struct Handler : IEventHandler {
            int breaks=0,contacts=0;
            bool handleEvent(EventEmitter*,long type,void*) throw() override { if(type==eventType_ParticleBreak)++breaks; if(type==eventType_ColliderContact)++contacts; return true; }
        } handler;
        first->addHandler(&handler,eventType_ParticleBreak);first->addHandler(&handler,eventType_ColliderContact);
        first->collider.setWantsContactEvents(true);layer->enableCollisions();tick(100);
        near(first->getLocation().x,1,"emitted physical body advances exactly once");
        expect(handler.breaks==1,"particle angular-speed Break event");expect(handler.contacts>0,"particle collision event routing");
        first->removeHandler(&handler,eventType_ParticleBreak);first->removeHandler(&handler,eventType_ColliderContact);
        first->collider.setContactHandler([first](const ColliderContact&) { first->expire(); });
        first->addRef();tick(10);
        expect(!first->isAlive() && !first->getLayer(),"contact callbacks may expire their own particle");
        first->release();
        first=second;
        auto& body=static_cast<PhysicsBody&>(first->physics);body.addRef();first->addRef();first->expire();
        expect(body.getSolver()==physicsSolver_Basic && !body.world(),"expiry detaches shared physics safely");
        first->release();body.release();
        cleanupLayer(layer);
    }
}
