describe('Scene lifecycle and simulation time', function() {
    var scenes, detached;
    function scene() { var s=new pdg.Scene();s.setManual(true);scenes.push(s);return s; }
    function layer(s, physical) { var l=s.createSpriteLayer();l.setUseChipmunkPhysics(!!physical);return l; }
    beforeEach(function() { scenes=[];detached=[]; });
    afterEach(function() { scenes.forEach(function(s){s.dispose();});detached.forEach(function(l){pdg.cleanupLayer(l);}); });
    it('keeps HUD animation and timers running while gameplay freezes and resumes', function() {
        var game=scene(),ui=scene(),player=layer(game).createSprite(),hud=layer(ui).createSprite();
        player.setMovement(100,0);hud.setMovement(20,0);var ticks=0,uiTicks=0;
        game.onInterval(function(){++ticks;},100);ui.onInterval(function(){++uiTicks;},100);
        game.advance(.1);ui.advance(.1);game.pause();
        var x=player.getLocation().x;
        for(var i=0;i<5;++i){game.advance(.1);ui.advance(.1);}
        expect(player.getLocation().x).toBeCloseTo(x,5);expect(ticks).toBe(1);
        expect(hud.getLocation().x).toBeCloseTo(12,4);expect(uiTicks).toBe(6);
        game.resume();game.advance(.1);expect(player.getLocation().x).toBeCloseTo(x+10,4);expect(ticks).toBe(2);
    });
    it('pauses timers created while paused and preserves individually paused timers', function() {
        var s=scene(),first=0,second=0;
        var a=s.onTimeout(function(){++first;},100);s.advance(.04);s.pauseTimer(a.timer);s.pause();
        s.onTimeout(function(){++second;},100);s.advance(.2);s.resume();s.advance(.1);
        expect(first).toBe(0);expect(second).toBe(1);expect(s.isTimerPaused(a.timer)).toBe(true);
        s.unpauseTimer(a.timer);s.advance(.059);expect(first).toBe(0);s.advance(.001);expect(first).toBe(1);
    });
    it('cannot individually resume a timer out of scene suspension', function(){
        var s=scene(),count=0,t=s.onTimeout(function(){++count;},50);
        s.pauseTimer(t.timer);s.pause();s.unpauseTimer(t.timer);s.advance(.1);expect(count).toBe(0);
        s.resume();s.advance(.05);expect(count).toBe(1);
    });
    it('isolates caller timer IDs across scenes and scales timer time', function(){
        var a=scene(),b=scene(),counts=[0,0];
        a.on(pdg.eventType_Timer,function(e){expect(e.id).toBe(7);++counts[0];return true;});
        b.on(pdg.eventType_Timer,function(e){expect(e.id).toBe(7);++counts[1];return true;});
        a.startTimer(7,100);b.startTimer(7,100);a.setTimeScale(.5);a.advance(.1);b.advance(.1);
        expect(counts).toEqual([0,1]);a.advance(.1);expect(counts).toEqual([1,1]);
    });
    it('freezes scale zero and rejects invalid timing',function(){
        var s=scene();[-1,NaN,Infinity].forEach(function(value){expect(function(){s.setTimeScale(value);}).toThrow();expect(function(){s.setFixedStep(value);}).toThrow();expect(function(){s.advance(value);}).toThrow();});
        expect(function(){s.startTimer(0,10);}).toThrow();expect(function(){s.startTimer(1,0,false);}).toThrow();
        s.setTimeScale(0);s.advance(.2);expect(s.getSimulationTime()).toBe(0);expect(s.isPaused()).toBe(false);
        s.setTimeScale(1);s.advance(.1);expect(s.getSimulationTime()).toBeCloseTo(.1,6);
    });
    it('retains a detached layer and adopts it in another scene', function(){
        var a=scene(),b=scene(),l=layer(a),sprite=l.createSprite();sprite.setMovement(10,0);
        a.advance(.1);a.removeLayer(l);detached.push(l);a.dispose();
        expect(sprite.getLocation().x).toBeCloseTo(1,5);expect(l.getNthSprite(0)).toBe(sprite);
        b.addLayer(l);detached.pop();b.advance(.1);expect(sprite.getLocation().x).toBeCloseTo(2,5);
        expect(b.getLayerCount()).toBe(1);b.disposeLayer(l);expect(b.getLayerCount()).toBe(0);
    });
    it('keeps layer fade completion on scene time across pause and transfer',function(){
        var a=scene(),b=scene(),l=layer(a),count=0;
        l.onLayerFadeOutComplete(function(){++count;return true;});l.fadeOut(.2);
        a.advance(.1);a.pause();a.advance(1);expect(count).toBe(0);
        a.removeLayer(l);b.addLayer(l);b.advance(.05);expect(count).toBe(0);
        b.advance(.06);expect(count).toBe(1);
    });
    it('rejects double scene membership and adopts a legacy factory layer',function(){
        var a=scene(),b=scene(),l=pdg.createSpriteLayer();a.addLayer(l);
        expect(function(){b.addLayer(l);}).toThrow();expect(a.getLayer(0)).toBe(l);
        expect(function(){b.removeLayer(l);}).toThrow();
    });
    it('owns a default camera, retains layer overrides, and pauses both',function(){
        var s=scene(),l=layer(s),camera=s.getCamera(),override=new pdg.Camera();
        expect(l.getEffectiveCamera()).toBe(camera);l.setCamera(override);expect(l.getEffectiveCamera()).toBe(override);
        camera.setMovement(10,0);override.setMovement(20,0);s.advance(.1);s.pause();s.advance(.1);
        expect(camera.getLocation().x).toBeCloseTo(1,5);expect(override.getLocation().x).toBeCloseTo(2,5);
        s.resume();s.advance(.1);expect(camera.getLocation().x).toBeCloseTo(2,5);expect(override.getLocation().x).toBeCloseTo(4,5);
        var other=scene();expect(function(){other.setCamera(camera);}).toThrow();
        l.setCamera(null);expect(l.getEffectiveCamera()).toBe(camera);
    });
    it('runs exact fixed ticks across frame partitions and pauses without debt',function(){
        var a=scene(),b=scene();a.setFixedStep(1/60);b.setFixedStep(1/60);
        a.advance(.1);for(var i=0;i<10;++i)b.advance(.01);
        expect(a.getTick()).toBe(6);expect(b.getTick()).toBe(6);
        expect(a.getSimulationTime()).toBeCloseTo(b.getSimulationTime(),8);
        a.pause();a.advance(20);a.resume();a.advance(1/60);expect(a.getTick()).toBe(7);
    });
    it('bounds catch-up and reports discarded time without firing skipped timers',function(){
        var s=scene(),count=0;s.setFixedStep(.01);s.onTimeout(function(){++count;},200);
        s.advance(2);expect(s.getTick()).toBe(8);expect(s.getSimulationTime()).toBeCloseTo(.08,8);
        expect(s.getDroppedTime()).toBeGreaterThan(1.8);expect(count).toBe(0);
    });
    it('cancels selected callbacks and prevents timer creation from recursively firing',function(){
        var s=scene(),calls=[];s.startTimer(1,0);s.startTimer(2,0);
        s.on(pdg.eventType_Timer,function(e){calls.push(e.id);if(e.id===1){s.cancelTimer(2);s.startTimer(3,0);}return true;});
        s.advance(.01);expect(calls).toEqual([1]);s.advance(.01);expect(calls).toEqual([1,3]);
    });
    it('disposes inside a timer without calling other selected callbacks',function(){
        var s=scene(),count=0;s.onTimeout(function(){s.dispose();},0);s.onTimeout(function(){++count;},0);
        s.advance(.01);expect(s.isDisposed()).toBe(true);expect(count).toBe(0);s.dispose();
        expect(function(){s.onTimeout(function(){},1);}).toThrow();
    });
    it('disconnects exact external subscriptions on disposal',function(){
        var s=scene(),emitter=scene(),count=0;
        s.subscribe(emitter,pdg.eventType_Timer,function(){++count;return true;});
        emitter.startTimer(10,10,false);emitter.advance(.01);expect(count).toBe(1);s.dispose();
        emitter.advance(.01);expect(count).toBe(1);
    });
    it('isolates physics worlds and preserves bodies across detach/reattach',function(){
        var a=scene(),b=scene(),l=layer(a,true),player=l.createSprite();
        player.setupPhysicsBody().setVelocity(new pdg.Vector(20,0));a.advance(.1);var x=player.getLocation().x;
        a.pause();b.advance(.1);a.advance(.1);expect(player.getLocation().x).toBeCloseTo(x,5);
        a.removeLayer(l);detached.push(l);a.dispose();b.addLayer(l);detached.pop();b.advance(.1);
        expect(player.getLocation().x).toBeGreaterThan(x);expect(player.physics.getVelocity().x).toBeCloseTo(20,4);
    });
});
