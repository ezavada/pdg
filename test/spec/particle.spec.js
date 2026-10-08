describe('Particles and particle emitters', function() {
    function assign(owner, name, value) { 'use strict'; owner[name] = value; }
    function withLayer(run) {
        const layer = pdg.createSpriteLayer();
        try { run(layer); } finally { pdg.cleanupLayer(layer); }
    }
    it('samples bounded ribbons and resets them on teleports', function() {
        const p=new pdg.Particle().setLifetime(0).setMovement(100,0);
        expect(p.hasTrail()).toBe(false);
        expect(p.setTrail({lifetime:.4,minDistance:0,sampleInterval:.01,maxPoints:8,color:'orange'})).toBe(p);
        p.animate(.1);expect(p.getTrailPointCount()).toBe(8);
        p.setLocation(500,100);expect(p.getTrailPointCount()).toBe(1);
        p.animate(.1);expect(p.breakTrail()).toBe(p);expect(p.getTrailPointCount()).toBe(1);
        expect(p.clearTrail()).toBe(p);expect(p.hasTrail()).toBe(false);
        [0xFF9900FF,new pdg.Color('orange')].forEach(function(color) {p.setTrail({color:color});});
        [{lifetime:0},{maxPoints:1},{maxPoints:2.5},{width:-1},{endOpacity:2},{sampleInterval:0},{breakDistance:Infinity},{minDistance:'2'},null].forEach(function(options) {
            expect(function(){p.setTrail(options);}).toThrow();
        });
    });
    it('records ribbon options for compatible playback targets', function() {
        pdg.Animated.defineScript('particle-ribbon-spec').setTrail({width:3,color:'orange'}).endScript();
        const p=new pdg.Particle().setLifetime(0).playScript('particle-ribbon-spec');
        p.animate(.01);expect(p.hasTrail()).toBe(true);
    });
    it('copies trail settings but never a template history', function() {
        withLayer(function(layer) {
            const p=new pdg.Particle().setLifetime(0).setMovement(100,0).setTrail({minDistance:0});p.animate(.1);
            layer.createParticleEmitter().setParticleTemplate(p).setLocation(300,200).emit(2);
            const a=layer.getNthParticle(0),b=layer.getNthParticle(1);
            expect(a.hasTrail()).toBe(true);expect(a.getTrailPointCount()).toBe(0);
            a.clearTrail();expect(b.hasTrail()).toBe(true);
            layer.removeAllParticles();expect(layer.getParticleTrailCount()).toBe(0);
        });
    });
    it('preserves factory identity and detached lifetime across layers', function() {
        const first = pdg.createSpriteLayer(), second = pdg.createSpriteLayer();
        let firstAlive = true, secondAlive = true;
        try {
            const particle = first.createParticle().setLifetime(0).setLocation(5,7);
            expect(first.getNthParticle(0)).toBe(particle);
            first.removeParticle(particle);
            expect(particle.getLayer()).toBe(null);
            second.addParticle(particle);
            expect(second.getNthParticle(0)).toBe(particle);
            expect(particle.getLayer()).toBe(second);
            pdg.cleanupLayer(first); firstAlive = false;
            expect(second.getNthParticle(0)).toBe(particle);
            pdg.cleanupLayer(second); secondAlive = false;
            expect(particle.getLayer()).toBe(null);
            particle.setLocation(11,13);
            expect(particle.getLocation().x).toBe(11);
            expect(particle.getLocation().y).toBe(13);
        } finally {
            if (firstAlive) pdg.cleanupLayer(first);
            if (secondAlive) pdg.cleanupLayer(second);
        }
    });
    it('replaces deleted browser handles while preserving the layer reference', function() {
        if (!pdg.Particle.prototype.delete) return; // Embind handle lifetime only.
        withLayer(function(layer) {
            const first = layer.createParticle().setLifetime(0).setLocation(9,4);
            expect(layer.getNthParticle(0)).toBe(first);
            first.delete();
            expect(first.isDeleted()).toBe(true);
            const replacement = layer.getNthParticle(0);
            expect(replacement === first).toBe(false);
            expect(replacement.getLocation().x).toBe(9);
            expect(layer.getNthParticle(0)).toBe(replacement);
            layer.removeParticle(replacement);
            expect(replacement.getLayer()).toBe(null);
            replacement.animate(.1);
            expect(replacement.isAlive()).toBe(true);
            replacement.delete();
        });
    });
    it('has whole-body animation and optional read-only components', function() {
        const p = new pdg.Particle();
        expect(p instanceof pdg.Particle).toBe(true);
        expect(p instanceof pdg.Sprite).toBe(false);
        ['createPart','findPart','setSubsection','getAnimationRig','setupPhysicsFromAnimationRig','attachSprite'].forEach(function(name) {
            expect(p[name]).toBeUndefined();
        });
        expect(p.physics).toBe(pdg.PhysicsBody.NoPhysics);
        expect(p.collider).toBe(pdg.Collider.NoCollider);
        expect(p.emitter).toBe(null);
        ['physics','collider','emitter'].forEach(function(name) { expect(function() { assign(p,name,null); }).toThrow(); });
        expect(p.setLocation(1,2).setMovement(4,0).setLifetime(0).fadeTo(0,1)).toBe(p);
        p.animate(.5);
        expect(p.getLocation().x).toBeCloseTo(3,5);
        expect(p.getOpacity()).toBeCloseTo(.5,5);
        expect(p.getAge()).toBe(.5);
    });
    it('expires on simulation time and leaves retained objects valid', function() {
        const p = new pdg.Particle().setLifetime(.5).setMovement(4,0);
        p.animate(2);
        expect(p.isAlive()).toBe(false);
        expect(p.getAge()).toBe(.5);
        expect(p.getLocation().x).toBeCloseTo(2,5);
        p.expire();p.animate(1);
        expect(p.getAge()).toBe(.5);
    });
    it('reuses existing physics and collider behavior', function() {
        const p = new pdg.Particle().setLifetime(0), body = p.setupPhysicsBody(2,4);
        expect(p.physics).toBe(body);
        expect(p.setupPhysicsBody(3,6)).toBe(body);
        body.setVelocity(10,0).setAngularVelocity(2);
        p.setupCollider().setCircle(1);
        expect(p.collider.getPhysicsBody()).toBe(body);
        expect(function() { p.moveBy(3,0,1); }).toThrow();
        p.fadeTo(0,1);p.animate(.5);
        expect(p.getLocation().x).toBeCloseTo(5,5);
        expect(p.getRotation()).toBeCloseTo(1,5);
        expect(p.getOpacity()).toBeCloseTo(.5,5);
        p.removePhysicsBody();expect(p.physics).toBe(pdg.PhysicsBody.NoPhysics);
        expect(body.isAttached()).toBe(false);
    });
    it('captures templates and creates independent schedules', function() {
        withLayer(function(layer) {
            const template = new pdg.Particle().setLifetime(1).fadeTo(0,1).moveBy(10,0,1,pdg.linearTween);
            const emitter = layer.createParticleEmitter().setParticleTemplate(template).setLocation(100,20);
            template.setLifetime(20).setOpacity(.2);
            expect(emitter.emit(2)).toBe(2);
            const a = layer.getNthParticle(0), b = layer.getNthParticle(1);
            expect(a).toBe(layer.getNthParticle(0));
            expect(a.getLayer()).toBe(layer);
            expect(a.getLifetime()).toBe(1);
            expect(a.getOpacity()).toBe(1);
            expect(function() { a.animate(.1); }).toThrow();
            layer.removeParticle(a);a.animate(.5);
            expect(a.getLocation().x).toBeCloseTo(105,5);
            expect(a.getOpacity()).toBeCloseTo(.5,5);
            expect(b.getAge()).toBe(0);
            expect(b.getOpacity()).toBe(1);
        });
    });
    // Headless builds support Drawing data, but not Particle artwork setters.
    (typeof pdg.Particle.prototype.setDrawing === 'function' ? it : xit)('accepts whole Drawing and Image artwork', function() {
        const drawing = pdg.createDrawing();
        drawing.addEllipse(new pdg.Point(0,0), 4, 3, new pdg.Attributes().fillColor('white'));
        const p = new pdg.Particle();
        expect(p.hasContent()).toBe(false);
        expect(p.setDrawing(drawing)).toBe(p);
        expect(p.getWidth()).toBe(8);expect(p.getHeight()).toBe(6);
        withLayer(function(layer) {
            const emitter = layer.createParticleEmitter().setParticleTemplate(p);
            p.clearContent();emitter.emit();
            expect(p.hasContent()).toBe(false);
            expect(layer.getNthParticle(0).hasContent()).toBe(true);
        });
        const image = new pdg.Image('data/test_image.png');
        expect(p.setImage(image)).toBe(p);
        expect(p.getWidth()).toBe(image.getWidth());
        expect(p.getHeight()).toBe(image.getHeight());
    });
    it('shares the layer budget and drops excess bursts', function() {
        withLayer(function(layer) {
            expect(layer.setMaxParticles(2)).toBe(layer);
            const emitter = layer.createParticleEmitter().setParticleTemplate(new pdg.Particle());
            expect(emitter.emit(5)).toBe(2);
            expect(layer.createParticle()).toBe(null);
            expect(layer.getParticleCount()).toBe(2);
            expect(emitter.emit()).toBe(0);
            const old = layer.getNthParticle(0);old.expire();
            expect(old.isAlive()).toBe(false);expect(old.getLayer()).toBe(null);
            expect(emitter.emit()).toBe(1);
            expect(old.isAlive()).toBe(false);
            expect(layer.getNthParticle(2)).toBe(null);
        });
    });
    it('owns a local emitter and keeps trails independent', function() {
        withLayer(function(layer) {
            const p = layer.createParticle().setLocation(10,20).setRotation(Math.PI/2).setMovement(0,20);
            const emitter = p.setupParticleEmitter();
            expect(p.emitter).toBe(emitter);expect(p.setupParticleEmitter()).toBe(emitter);
            expect(emitter.getParticle()).toBe(p);expect(emitter.getLayer()).toBe(layer);
            emitter.setParticleTemplate(new pdg.Particle()).setLocation(2,0).setRotation(Math.PI).setParticleSpeed(10).setVelocityInheritance(.5);
            emitter.emit();
            const child = layer.getNthParticle(1);
            expect(child.getLocation().x).toBeCloseTo(10,4);
            expect(child.getLocation().y).toBeCloseTo(22,4);
            expect(child.getMovement().y).toBeCloseTo(0,4);
            p.expire();expect(child.isAlive()).toBe(true);
            p.removeParticleEmitter();expect(p.emitter).toBe(null);
            expect(emitter.getParticle()).toBe(null);expect(emitter.isEmitting()).toBe(false);
        });
    });
    it('copies child emitter configuration with independent state', function() {
        withLayer(function(layer) {
            const template = new pdg.Particle();
            template.setupParticleEmitter().setParticleTemplate(new pdg.Particle()).setEmissionRate(5).startEmitting();
            const source = layer.createParticleEmitter().setParticleTemplate(template);source.emit(2);
            const a = layer.getNthParticle(0), b = layer.getNthParticle(1);
            expect(a.emitter === b.emitter).toBe(false);
            expect(a.emitter.isEmitting()).toBe(true);
            a.emitter.stopEmitting();expect(b.emitter.isEmitting()).toBe(true);
            b.emitter.emit();expect(layer.getParticleCount()).toBe(3);
        });
    });
    it('repeats random emissions from a seed', function() {
        withLayer(function(layer) {
            const emitter = layer.createParticleEmitter().setParticleTemplate(new pdg.Particle()).setParticleSpeed(5,15).setSpread(1);
            expect(emitter.getSeed()).toBe(1);expect(emitter.getMinParticleSpeed()).toBe(5);expect(emitter.getMaxParticleSpeed()).toBe(15);
            emitter.emit();const a=layer.getNthParticle(0).getMovement();
            layer.removeAllParticles();emitter.setSeed(emitter.getSeed()).emit();const b=layer.getNthParticle(0).getMovement();
            expect(a.x).toBe(b.x);expect(a.y).toBe(b.y);
        });
    });
    it('delivers body angular-speed events on the Particle', function() {
        const p = new pdg.Particle().setLifetime(0), body = p.setupPhysicsBody();
        let event;
        const handler = new pdg.IEventHandler(function(e) { event=e;return true; });
        p.addHandler(handler,pdg.eventType_ParticleBreak);
        body.setBreakAngularSpeed(1).setAngularVelocity(2);p.animate(.1);
        expect(event.emitter).toBe(p);expect(event.body).toBe(body);
        expect(event.angularSpeed).toBe(2);expect(event.breakAngularSpeed).toBe(1);
        expect(event.referenceBody).toBe(null);
        p.removeHandler(handler,pdg.eventType_ParticleBreak);
    });
    it('rebases independently copied relative script playback at emission', function() {
        const layer=pdg.createSpriteLayer();
        try {
            const template=new pdg.Particle().setLifetime(0); template.batch().moveBy(10,0,1,pdg.linearTween).yoyo().endBatch().animate(.5);
            const emitter=layer.createParticleEmitter().setParticleTemplate(template).setLocation(100,200); emitter.emit(2);
            const first=layer.getNthParticle(0), second=layer.getNthParticle(1);
            layer.removeParticle(first);layer.removeParticle(second);
            first.animate(.5); expect(first.getLocation().x).toBeCloseTo(105,5);expect(first.getLocation().y).toBeCloseTo(200,5);
            first.animate(1);expect(first.getLocation().x).toBeCloseTo(95,5);expect(second.getLocation().x).toBeCloseTo(100,5);
            expect(template.getLocation().x).toBeCloseTo(5,5);
        } finally {pdg.cleanupLayer(layer);}
    });
    it('rejects invalid emission parameters', function() {
        const emitter = new pdg.ParticleEmitter(), p = new pdg.Particle();
        [-1,NaN,Infinity].forEach(function(v) {
            expect(function() { p.setLifetime(v); }).toThrow();
            expect(function() { emitter.setEmissionRate(v); }).toThrow();
            expect(function() { emitter.setParticleSpeed(v); }).toThrow();
            expect(function() { emitter.setSpread(v); }).toThrow();
        });
        expect(function() { emitter.setParticleSpeed(5,2); }).toThrow();
        expect(function() { emitter.setSpread(7); }).toThrow();
        expect(function() { emitter.emit(); }).toThrow();
        expect(function() { emitter.emit(-1); }).toThrow();
        expect(function() { emitter.setSeed(.5); }).toThrow();
        expect(emitter.emit(0)).toBe(0);
    });
});
