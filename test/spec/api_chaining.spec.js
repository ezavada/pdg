if (typeof document !== 'undefined') describe('Generated browser checked methods', function() {
    it('combines fluent drawing and borrowed attribute conversion without changing either input', function() {
        var port=pdg.gfx.createOffscreenPort(new pdg.Rect(64,64));
        var ordinary=new pdg.Attributes().fillColor('red').lineStyle(pdg.lineStyle_None);
        var animated=new pdg.AnimatedAttributes().fillColor('green').lineStyle(pdg.lineStyle_None).setLocation(20,0);
        var rect=new pdg.Rect(2,2,10,10), image;
        try {
            expect(port.clear().drawRect(rect,ordinary).drawRect(rect,animated)).toBe(port);
            image=new pdg.Image(port);
            expect(image.getPixel(6,6).red).toBeGreaterThan(.9);
            expect(image.getPixel(26,6).green).toBeGreaterThan(.4);
            expect(ordinary.getTransform()[6]).toBe(0);
            expect(animated.getLocation().x).toBe(20);
            expect(function(){port.drawRect(rect,{});}).toThrow();
            expect(function(){port.drawRect(rect,null);}).toThrow();
            animated.delete();
            expect(function(){port.drawRect(rect,animated);}).toThrow();
            expect(port.drawRect(rect,ordinary)).toBe(port);
        } finally {
            if(image) image.delete();
            if(!animated.isDeleted()) animated.delete();
            ordinary.delete();pdg.gfx.closeGraphicsPort(port);
        }
    });
    it('preserves retained class construction, scalar validation and default easing', function() {
        var camera = new pdg.Camera(), particle = new pdg.Particle(), emitter = new pdg.ParticleEmitter();
        try {
            expect(camera instanceof pdg.Animated).toBe(true);
            expect(particle instanceof pdg.Animated).toBe(true);
            expect(emitter instanceof pdg.Animated).toBe(true);
            expect(camera.setOpacity(.5).hide().show()).toBe(camera);
            expect(camera.getOpacity()).toBe(.5);
            expect(function() { camera.setOpacity('0.5'); }).toThrow();
            expect(function() { camera.setOpacity(true); }).toThrow();
            expect(camera.zoomTo(2, .2)).toBe(camera);
            camera.animate(.2);
            expect(camera.getZoom()).toBeCloseTo(2, 5);
            expect(camera.fadeOut(.2)).toBe(camera);
            camera.animate(.2);
            expect(camera.getOpacity()).toBeCloseTo(0, 5);
            expect(camera.worldToView(new pdg.Point(2,3)) instanceof pdg.Point).toBe(true);
            expect(camera.getViewport() instanceof pdg.Rect).toBe(true);
            particle.setLifetime(0).setOpacity(1).fadeTo(.25, .2);
            particle.animate(.2);
            expect(particle.getOpacity()).toBeCloseTo(.25, 5);
            expect(emitter.setEmissionRate(0).stopEmitting()).toBe(emitter);
        } finally { emitter.delete(); particle.delete(); camera.delete(); }
    });
    it('exposes generated scalar size queries and preserves serializer interface chaining', function() {
        var writer = new pdg.Serializer();
        try {
            var mode = writer.getResourceMode();
            expect(writer.setResourceMode(mode)).toBe(writer);
            expect(writer.getResourceMode()).toBe(mode);
            [['sizeof_1',1],['sizeof_1u',1],['sizeof_2',2],['sizeof_2u',2],
             ['sizeof_3u',3],['sizeof_4',4],['sizeof_4u',4],['sizeof_f',4],['sizeof_d',8]].forEach(function(entry) {
                expect(writer[entry[0]](1)).toBe(entry[1]);
            });
        } finally { writer.delete(); }
    });
    it('preserves the concrete receiver and effects of generated fluent controls', function() {
        var animated = new pdg.AnimatedAttributes();
        try {
            expect(animated.flipX()).toBe(animated);
            expect(animated.isFlippedX()).toBe(true);
            expect(animated.flipY()).toBe(animated);
            expect(animated.isFlippedY()).toBe(true);
            animated.setMovement(new pdg.Vector(3,4));
            expect(animated.stopMovement()).toBe(animated);
            expect(animated.getMovement().x).toBe(0);
            expect(animated.getMovement().y).toBe(0);
            expect(animated.stopSpinning().stopGrowing().stopStretching()
                .pauseSchedule().resumeSchedule().cancelSchedule()).toBe(animated);
            expect(animated.flipX().flipY()).toBe(animated);
            expect(animated.isFlippedX()).toBe(false);
            expect(animated.isFlippedY()).toBe(false);
        } finally { animated.delete(); }
    });
    it('returns public value types through native inheritance and the Attributes mixin', function() {
        var animated = new pdg.AnimatedAttributes();
        try {
            animated.setLocation(3,4).setSize(10,20).setRotation(.4).setCenterOffset(2,1)
                .fillColor(new pdg.Color(.2,.4,.6,.8));
            var point = animated.getLocation(), bounds = animated.getBoundingBox(), rotated = animated.getRotatedBounds();
            expect(point instanceof pdg.Point).toBe(true);
            expect(bounds instanceof pdg.Rect).toBe(true);
            expect(rotated instanceof pdg.RotatedRect).toBe(true);
            expect(rotated.radians).toBeCloseTo(.4,5);
            expect(rotated.centerOffset.x).toBe(2);
            expect(animated.getSize() instanceof pdg.Offset).toBe(true);
            expect(animated.getFillColor() instanceof pdg.Color).toBe(true);
            expect(animated.getFillColor().alpha).toBeCloseTo(.8,5);
            point.x=99;
            expect(animated.getLocation().x).toBe(3);
            expect(typeof animated.getWidth()).toBe('number');
        } finally { animated.delete(); }
    });
    it('preserves native error messages and allows fluent use after a rejected operation', function() {
        var animated = new pdg.Animated(), error;
        try {
            try { animated.endBatch(); } catch (caught) { error = caught; }
            expect(error instanceof Error).toBe(true);
            expect(error && error.message).toBe('endBatch requires the innermost open group');
            expect(animated.setWidth(10).moveTo(new pdg.Point(3,4))).toBe(animated);
            expect(animated.getWidth()).toBe(10);
            expect(animated.getLocation().x).toBe(3);
            expect(animated.getLocation().y).toBe(4);
        } finally { animated.delete(); }
    });
});
describe('Geometry receiver and value results', function() {
    it('mutates assign/add/sub while plus/minus produce independent rectangles', function() {
        var rect = new pdg.Rect(1,2,11,12), delta = new pdg.Point(3,4);
        var plus = rect.plus(delta), minus = rect.minus(delta);
        expect(plus).not.toBe(rect);
        expect(minus).not.toBe(rect);
        expect(rect.left).toBe(1);
        expect(plus.left).toBe(4);
        expect(minus.left).toBe(-2);
        expect(rect.add(delta)).toBe(rect);
        expect(rect.left).toBe(4);
        expect(rect.sub(delta)).toBe(rect);
        expect(rect.left).toBe(1);
        expect(rect.assign(plus)).toBe(rect);
        expect(rect.left).toBe(4);
        rect.left = 4.4;
        expect(rect.round()).toBe(rect);
        expect(rect.left).toBe(4);
    });
    it('chains quad and rotated rectangle transforms', function() {
        var quad = new pdg.Quad(new pdg.Rect(10,10));
        expect(quad.moveRight(3)).toBe(quad);
        expect(quad.rotate(0.1)).toBe(quad);
        var rect = new pdg.RotatedRect(new pdg.Rect(10,10));
        expect(rect.rotate(0.1)).toBe(rect);
    });
});
if (pdg.hasGraphics) describe('Graphics method chaining', function() {
    it('chains Polygon edits and preserves independent intersection results', function() {
        var poly = new pdg.Polygon([new pdg.Point(0,0),new pdg.Point(10,0),new pdg.Point(10,10),new pdg.Point(0,10)]);
        expect(poly.moveRight(3).moveUp(2)).toBe(poly);
        expect(poly.getBounds().left).toBe(3);
        var result = poly.intersection(new pdg.Polygon([new pdg.Point(0,0),new pdg.Point(20,0),new pdg.Point(20,20),new pdg.Point(0,20)]));
        expect(result).not.toBe(poly);
        expect(poly.clearPoints()).toBe(poly);
    });
    it('replaces Sprite frame artwork through native Image pointer arguments', function() {
        var oldPort = pdg.gfx.createOffscreenPort(new pdg.Rect(16,16));
        var newPort = pdg.gfx.createOffscreenPort(new pdg.Rect(24,32));
        var oldImage, newImage, sprite;
        try {
            oldImage = new pdg.Image(oldPort);
            newImage = new pdg.Image(newPort);
            sprite = new pdg.Sprite();
            sprite.addFramesImage(oldImage);
            expect(sprite.getFrameRotatedBounds().width()).toBe(16);
            sprite.changeFramesImage(oldImage, newImage);
            var bounds = sprite.getFrameRotatedBounds();
            expect(bounds instanceof pdg.RotatedRect).toBe(true);
            expect(bounds.width()).toBe(24);
            expect(bounds.height()).toBe(32);
            expect(sprite.getFrameCount()).toBe(1);
        } finally {
            [sprite, oldImage, newImage].forEach(function(value) {
                if (value && typeof value.delete === 'function') value.delete();
            });
            pdg.gfx.closeGraphicsPort(oldPort);
            pdg.gfx.closeGraphicsPort(newPort);
        }
    });
    it('chains Image appearance settings and Port replay without public Drawing.draw', function() {
        var port = pdg.gfx.createOffscreenPort(new pdg.Rect(16,16));
        try {
            expect(port.clear(new pdg.Color(0,0,0,1))).toBe(port);
            expect(port.resetClipRect()).toBe(port);
            var drawing = pdg.createDrawing();
            expect(drawing.draw).toBeUndefined();
            drawing.addRect(new pdg.Rect(2,2,12,12), new pdg.Attributes()
                .fillColor(new pdg.Color(1,0,0,1)).lineStyle(pdg.lineStyle_None));
            expect(port.drawDrawing(drawing, new pdg.Point(), new pdg.Attributes())).toBe(port);
            var image = new pdg.Image(port);
            expect(image.getPixel(5,5).red).toBe(1);
            expect(image.getPixel(5,5) instanceof pdg.Color).toBe(true);
            expect(image.getPixel(new pdg.Point(5,5)) instanceof pdg.Color).toBe(true);
            expect(image.setOpacity(0.5)).toBe(image);
            expect(image.setTransparentColor(new pdg.Color(0,1,0,1))).toBe(image);
            expect(image.setEdgeClamping(true)).toBe(image);
            expect(image.getOpacity()).toBeCloseTo(0.5, 2);
        } finally { pdg.gfx.closeGraphicsPort(port); }
    });
});
if (typeof pdg.NetConnection === 'function') describe('NetConnection send chaining', function() {
    it('returns its receiver for reliable, fallback and datagram sends', function() {
        var connection = Object.create(pdg.NetConnection.prototype), sent = [];
        connection.socket = {write:function(buf) { sent.push(buf.toString()); return true; }};
        connection._serializeMessage = function(message) {
            return message;
        };
        connection._frameTcpData = function(data) { return data; };
        expect(connection.send('a')).toBe(connection);
        expect(connection.sendDgram('b')).toBe(connection);
        connection._dgramAlive = connection.hasDgram = true;
        connection._dgramSock = {send:function(buf) { sent.push(buf.toString()); }};
        expect(connection.sendDgram('c')).toBe(connection);
        expect(sent).toEqual(['a','b','c']);
    });
});
