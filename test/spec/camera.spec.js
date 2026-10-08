describe('Camera', function() {
    it('controls visibility and composed opacity independently of animation', function() {
        var camera=new pdg.Camera();
        expect(camera.isHidden()).toBe(false);expect(camera.getOpacity()).toBe(1);
        expect(camera.hide().setOpacity(.25)).toBe(camera);
        camera.moveBy(10,0,1,pdg.linearTween).animate(.5);
        expect(camera.isHidden()).toBe(true);expect(camera.getLocation().x).toBeCloseTo(5,5);
        expect(camera.show()).toBe(camera);expect(camera.getOpacity()).toBe(.25);
        [-1,2,NaN,Infinity,null,'0.5'].forEach(function(value){expect(function(){camera.setOpacity(value);}).toThrow();});
        expect(function(){camera.fadeOut(-1);}).toThrow();
        expect(function(){camera.fadeTo(.5,1,99999);}).toThrow();
    });
    it('schedules fades with playback controls and snapshot continuation', function() {
        var camera=new pdg.Camera();
        expect(camera.fadeOut(1,pdg.linearTween).andThen().fadeIn(1,pdg.linearTween)).toBe(camera);
        camera.animate(.5);expect(camera.getOpacity()).toBeCloseTo(.5,5);
        camera.pauseSchedule().animate(2);expect(camera.getOpacity()).toBeCloseTo(.5,5);
        var writer=new pdg.Serializer();writer.serialize_obj(camera);
        var reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());var restored=reader.deserialize_obj();
        restored.resumeSchedule().animate(1);expect(restored.getOpacity()).toBeCloseTo(.5,5);
        restored.animate(.5);expect(restored.getOpacity()).toBeCloseTo(1,5);
        camera.cancelSchedule().resumeSchedule().setOpacity(.25).fadeIn(1).pauseIt().animate(.5);
        expect(camera.getOpacity()).toBeCloseTo(.25,5);
        camera.resumeIt().animate(.5);expect(camera.getOpacity()).toBeCloseTo(.625,5);
        camera.stopIt().animate(1);expect(camera.getOpacity()).toBeCloseTo(.625,5);
        camera.cancelSchedule().fadeOut(0);expect(camera.getOpacity()).toBe(0);
        camera.hide();writer=new pdg.Serializer();writer.serialize_obj(camera);
        reader=new pdg.Deserializer();reader.setDataPtr(writer.getDataPtr());restored=reader.deserialize_obj();
        expect(restored.isHidden()).toBe(true);expect(restored.getOpacity()).toBe(0);
    });
    it('cuts immediately between independent cameras without changing pose or opacity',function(){
        var source=new pdg.Camera().setLocation(10,20).setOpacity(.4),destination=new pdg.Camera().hide().setLocation(30,40).setOpacity(.8);
        expect(source.cutTo(destination)).toBe(source);expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);
        expect(source.getLocation().x).toBe(10);expect(destination.getLocation().y).toBe(40);expect(source.getOpacity()).toBeCloseTo(.4,5);expect(destination.getOpacity()).toBeCloseTo(.8,5);
        expect(function(){source.cutTo(source);}).toThrow();expect(function(){source.cutTo(null);}).toThrow();expect(function(){source.cutTo();}).toThrow();
        expect(function(){source.getEffects().cutTo(destination);}).toThrow();
    });
    it('queues camera cuts and preserves visibility while paused or cancelled',function(){
        var source=new pdg.Camera(),destination=new pdg.Camera().hide();
        source.wait(1).cutTo(destination);source.animate(.5);
        expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(true);
        source.pauseSchedule().animate(2);expect(destination.isHidden()).toBe(true);
        source.resumeSchedule().animate(.49);expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(true);
        source.animate(.01);expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);
        source.show();destination.hide();source.wait(1).cutTo(destination);source.cancelSchedule().animate(2);
        expect(source.isHidden()).toBe(false);expect(destination.isHidden()).toBe(true);
        source.wait(1).cutTo(destination).stopIt();source.animate(2);expect(destination.isHidden()).toBe(true);
        expect(function(){source.restartIt();}).toThrow();source.cancelSchedule();
        expect(destination.cutTo(source)).toBe(destination);
    });
    it('reserves pending cut ownership and rejects snapshots until cancellation or completion',function(){
        var source=new pdg.Camera(),destination=new pdg.Camera().hide(),third=new pdg.Camera();
        source.wait(1).cutTo(destination);
        expect(function(){source.cutTo(third);}).toThrow();expect(function(){destination.cutTo(third);}).toThrow();
        expect(function(){third.cutTo(destination);}).toThrow();expect(function(){new pdg.Serializer().serialize_obj(source);}).toThrow();
        source.cancelSchedule();expect(function(){new pdg.Serializer().serialize_obj(source);}).not.toThrow();
        source.cutTo(destination);expect(function(){new pdg.Serializer().serialize_obj(source);}).not.toThrow();
        expect(destination.cutTo(third)).toBe(destination);
    });
    if (!pdg.hasGraphics) it('exposes matching with a clear graphics requirement in headless builds',function(){
        var source=new pdg.Camera(),destination=new pdg.Camera(),a=new pdg.Sprite(),b=new pdg.Sprite();
        expect(typeof source.matchCutTo).toBe('function');
        expect(typeof source.matchFadeTo).toBe('function');
        expect(function(){source.matchCutTo(destination,{matchSource:a,matchTarget:b});}).toThrow();
        expect(function(){source.matchFadeTo(destination,{matchSource:a,matchTarget:b});}).toThrow();
        expect(source.isHidden()).toBe(false);
    });
    it('continues a scheduled chain after the cut with destination already visible',function(){
        var source=new pdg.Camera(),destination=new pdg.Camera().hide(),completed=0;
        var listener=source.onZoomComplete(function(){expect(source.isHidden()).toBe(true);expect(destination.isHidden()).toBe(false);++completed;return false;});
        source.wait(.5).cutTo(destination).andThen().zoomTo(2,.5,pdg.linearTween);source.animate(1);
        expect(source.getZoom()).toBeCloseTo(2,5);expect(completed).toBe(1);listener.cancel();
    });
    it('uses Animated movement, zoom, and schedule controls', function() {
        var camera = new pdg.Camera();
        expect(camera.moveTo(10,20,1,pdg.linearTween)).toBe(camera);
        camera.zoomTo(3,1,pdg.linearTween); camera.animate(.5);
        expect(camera.getLocation().x).toBeCloseTo(5,4);
        expect(camera.getZoom()).toBeCloseTo(2,4);
        camera.pauseSchedule(); camera.animate(.5); expect(camera.getZoom()).toBeCloseTo(2,4);
        camera.resumeSchedule(); camera.animate(.5); expect(camera.getZoom()).toBeCloseTo(3,4);
        expect(function() { camera.zoomTo(2,-1); }).toThrow();
        expect(function() { camera.setZoom(0); }).toThrow();
        expect(function() { camera.zoomTo(2,1,99999); }).toThrow();
    });
    it('resolves relative zoom chains and emits completion on the camera', function() {
        var camera = new pdg.Camera(), values = [], generic = [];
        var subscription = camera.onZoomComplete(function(event) {
            expect(event.camera).toBe(camera);
            expect(event.emitter).toBe(camera);
            expect(event.eventType).toBe(pdg.eventType_ZoomComplete);
            values.push(event.zoom);
            return false;
        });
        var handler = new pdg.IEventHandler(function(event) { generic.push(event.zoom); return false; });
        camera.addHandler(handler, pdg.eventType_ZoomComplete);
        expect(camera.zoomTo(2,1,pdg.linearTween).andThen().zoom(3,1,pdg.linearTween)).toBe(camera);
        camera.animate(1); expect(values).toEqual([2]);
        camera.animate(.5); expect(camera.getZoom()).toBeCloseTo(4,4);
        camera.animate(.5); expect(values).toEqual([2,6]); expect(generic).toEqual(values);
        camera.wait(.5).zoomTo(3,.5,pdg.linearTween);
        camera.moveTo(10,0,.5,pdg.linearTween); camera.animate(.5);
        expect(camera.getLocation().x).toBeCloseTo(10,4); expect(values.length).toBe(2);
        camera.pauseSchedule(); camera.animate(1); expect(values.length).toBe(2);
        camera.resumeSchedule(); camera.animate(.5); expect(values).toEqual([2,6,3]);
        camera.zoomTo(9,1).cancelSchedule().animate(2); expect(values.length).toBe(3);
        camera.zoomTo(8,1).zoomTo(4,1,pdg.linearTween).animate(1); expect(values).toEqual([2,6,3,4]);
        camera.zoom(.5,0); expect(values).toEqual([2,6,3,4,2]);
        camera.setZoom(7); expect(values.length).toBe(5);
        subscription.cancel(); camera.removeHandler(handler,pdg.eventType_ZoomComplete);
        camera.zoomTo(1,0); expect(values.length).toBe(5);
        expect(function() { camera.zoom(0,1); }).toThrow();
    });
    it('restores relative zoom completion from a camera snapshot', function() {
        var source = new pdg.Camera(); source.zoomTo(2,.5,pdg.linearTween).andThen().zoom(3,.5,pdg.linearTween);
        var ser = new pdg.Serializer(); ser.serialize_obj(source);
        var des = new pdg.Deserializer(); des.setDataPtr(ser.getDataPtr());
        var restored = des.deserialize_obj();
        var values=[]; restored.onZoomComplete(function(event) { values.push(event.zoom); return false; });
        restored.animate(1); expect(restored.getZoom()).toBeCloseTo(6,4); expect(values).toEqual([2,6]);
    });
    it('restores shared layer camera identity and independent animation state', function() {
        var a=pdg.createSpriteLayer(), b=pdg.createSpriteLayer();
        try {
            var camera=new pdg.Camera(); camera.zoomTo(3,1,pdg.linearTween); camera.animate(.25); camera.pauseSchedule();
            a.setCamera(camera); b.setCamera(camera);
            a.setSerializationFlags(pdg.ser_LayerDraw); b.setSerializationFlags(pdg.ser_LayerDraw);
            var ser=new pdg.Serializer(); a.serialize(ser); b.serialize(ser);
            camera.cancelSchedule(); camera.setZoom(9); a.setCamera(null); b.setCamera(null);
            var des=new pdg.Deserializer(); des.setDataPtr(ser.getDataPtr()); a.deserialize(des); b.deserialize(des);
            expect(a.getCamera()).toBe(b.getCamera()); expect(a.getCamera()).not.toBe(camera);
            expect(a.getCamera().getZoom()).toBeCloseTo(1.5,4);
            expect(a.getCamera().isSchedulePaused()).toBe(true);
            a.getCamera().resumeSchedule(); a.getCamera().animate(.75);
            expect(b.getCamera().getZoom()).toBeCloseTo(3,4); expect(camera.getZoom()).toBe(9);
        } finally { pdg.cleanupLayer(a); pdg.cleanupLayer(b); }
    });
    if (pdg.hasGraphics) {
        describe('zoom animation', function() {
            var layer, camera, listener;
            afterEach(function() {
                if (listener && listener.cancel) listener.cancel();
                if (layer) pdg.cleanupLayer(layer);
                layer = camera = listener = null;
            });
            it('completes absolute and relative zooms through the engine animation loop', function() {
                var completions = 0;
                runs(function() {
                    layer = pdg.createSpriteLayer();
                    camera = new pdg.Camera().setZoom(2);
                    layer.setCamera(camera);
                    listener = camera.onZoomComplete(function() { ++completions; return false; });
                    expect(camera.zoomTo(4, .1, pdg.linearTween)).toBe(camera);
                });
                waitsFor(function() { return completions >= 1; }, 'absolute zoom completion', 2000);
                runs(function() {
                    expect(camera.getZoom()).toBeCloseTo(4, 5);
                    expect(camera.zoom(.5, .1)).toBe(camera);
                });
                waitsFor(function() { return completions >= 2; }, 'relative zoom completion', 2000);
                runs(function() { expect(camera.getZoom()).toBeCloseTo(2, 5); });
            });
        });
        it('owns a stable full-port camera and inherits it across layers', function() {
            var port=pdg.gfx.createOffscreenPort(new pdg.Rect(64,64));
            var next=pdg.gfx.createOffscreenPort(new pdg.Rect(80,40));
            var layer=pdg.createSpriteLayer(port), other=pdg.createSpriteLayer(port);
            try {
                var camera=port.getCamera(); expect(port.getCamera()).toBe(camera);
                expect(typeof port.setCamera).toBe('undefined');
                expect(camera.getViewport().width()).toBe(64);
                expect(function(){camera.setViewport(new pdg.Rect(0,0,32,32));}).toThrow();
                camera.setLocation(10,20).setZoom(2);port.setCameraAnchor(new pdg.Point(4,6));
                expect(layer.getEffectiveCamera()).toBe(camera);expect(other.getEffectiveCamera()).toBe(camera);
                var p=layer.layerToPortPoint(new pdg.Point(15,25));expect(p.x).toBeCloseTo(14,4);expect(p.y).toBeCloseTo(16,4);
                var own=new pdg.Camera();own.setViewport(new pdg.Rect(0,0,32,32)).setLocation(5,0);layer.setCamera(own);
                expect(layer.layerToPortPoint(new pdg.Point(15,25)).x).toBeCloseTo(26,4);
                expect(other.getEffectiveCamera()).toBe(camera);
                expect(function(){layer.setCamera(next.getCamera());}).toThrow();
                layer.setCamera(null);layer.setSpritePort(next);expect(layer.getEffectiveCamera()).toBe(next.getCamera());
                expect(layer.layerToPortPoint(new pdg.Point(15,25)).x).toBeCloseTo(15,4);
                next.getCamera().follow(camera).animate(0);expect(next.getCamera().getLocation().x).toBe(10);
                next.getCamera().stopFollowing();
                layer.setWorldBounds(new pdg.Rect(-100,-50,100,50));expect(layer.getWorldBounds().width()).toBe(200);
                expect(typeof layer.draw).toBe('undefined');expect(typeof layer.drawView).toBe('undefined');expect(typeof camera.drawEffects).toBe('undefined');
            } finally {pdg.cleanupLayer(layer);pdg.cleanupLayer(other);pdg.gfx.closeGraphicsPort(port);pdg.gfx.closeGraphicsPort(next);}
        });
        it('renders camera transforms once through nested Drawings and clips in port space', function() {
            var port=pdg.gfx.createOffscreenPort(new pdg.Rect(64,64));
            try {
                var camera=port.getCamera();camera.setLocation(10,0).setZoom(2);
                var red=new pdg.Attributes().fillColor(new pdg.Color(1,0,0,1)).lineStyle(pdg.lineStyle_None);
                var drawing=pdg.createDrawing();drawing.addRect(new pdg.Rect(12,2,20,10),red);
                port.clear();port.setClipRect(new pdg.Rect(0,0,12,64));port.drawDrawing(drawing,new pdg.Point(0,0),new pdg.Attributes());
                var image=new pdg.Image(port);expect(image.getPixel(6,6).red).toBeGreaterThan(.9);expect(image.getPixel(14,6).alpha).toBeLessThan(.1);
                var q=port.portToWorld(port.worldToPort(new pdg.Point(15,25)));expect(q.x).toBeCloseTo(15,4);expect(q.y).toBeCloseTo(25,4);
            } finally {pdg.gfx.closeGraphicsPort(port);}
        });
        it('borrows drawing attributes without changing pixels or retaining stale camera transforms', function() {
            var port=pdg.gfx.createOffscreenPort(new pdg.Rect(64,64));
            var source=pdg.gfx.createOffscreenPort(new pdg.Rect(8,8));
            try {
                source.clear();
                source.drawRect(new pdg.Rect(8,8),new pdg.Attributes().fillColor('red').lineStyle(pdg.lineStyle_None));
                var image=new pdg.Image(source),camera=port.getCamera();
                var attrs=new pdg.Attributes().setTransform([1,0,0,0,1,0,4,0,1]);
                var original=attrs.getTransform();
                function drawAndCheck(x,y) {
                    port.clear();
                    // Point -> Rect -> Quad must compose the camera only once.
                    port.drawImage(image,new pdg.Point(20,20),attrs);
                    var output=new pdg.Image(port);
                    expect(output.getPixel(x+2,y+2).red).toBeGreaterThan(.9);
                    expect(output.getPixel(x-2,y+2).alpha).toBeLessThan(.1);
                    expect(attrs.getTransform()).toEqual(original);
                    if (output.delete) output.delete();
                }
                drawAndCheck(24,20); // Identity camera, nonidentity caller attributes.
                camera.setLocation(10,0).setZoom(2);
                drawAndCheck(28,40);
                camera.setLocation(12,0); // No intervening frame/tick.
                drawAndCheck(24,40);
                port.setCameraDrawingEnabled(false);
                drawAndCheck(24,20);
                port.setCameraDrawingEnabled(true);
                drawAndCheck(24,40);
                camera.setLocation(0,0).setZoom(1);
                camera.getEffects().setLocation(4,0);
                drawAndCheck(20,20);
                camera.getEffects().setLocation(0,0);
                drawAndCheck(24,20);
                port.setCameraAnchor(new pdg.Point(3,2));
                drawAndCheck(27,22);
                camera.setScale(0,1);
                port.setCameraDrawingEnabled(false);
                drawAndCheck(24,20); // Disabled drawing must not query an invalid camera.
                camera.setScale(1,1);
                port.setCameraDrawingEnabled(true);
                drawAndCheck(27,22);
            } finally {
                if (image && image.delete) image.delete();
                if (attrs && attrs.delete) attrs.delete();
                pdg.gfx.closeGraphicsPort(source);pdg.gfx.closeGraphicsPort(port);
            }
        });
    }
});

describe('Camera retained reference results', function() {
    it('preserves effects identity and retains effects independently of the camera', function() {
        const camera = new pdg.Camera(), effects = camera.getEffects();
        expect(effects instanceof pdg.Camera).toBe(true);
        expect(camera.getEffects()).toBe(effects);
        expect(effects.moveTo(3, 4)).toBe(effects);
        expect(effects.getLocation().x).toBe(3);
        if (camera.delete) {
            camera.delete();
            expect(effects.isDeleted()).toBe(false);
            effects.moveTo(5, 6);
            expect(effects.getLocation().x).toBe(5);
            effects.delete();
        }
    });
});
