// Offscreen drawing must behave the same in native and browser graphics builds.
if (pdg.hasGraphics) describe('Offscreen ports', function() {
    var ports;
    function create(width, height) {
        var port = pdg.gfx.createOffscreenPort(new pdg.Rect(width, height));
        expect(port).not.toBe(null);
        ports.push(port);
        return port;
    }
    function fill(port, color, bounds) {
        port.drawRect(bounds || port.getDrawingArea(), new pdg.Attributes()
            .fillColor(color).lineStyle(pdg.lineStyle_None));
    }
    function image(port, copy) {
        return copy === undefined ? new pdg.Image(port)
            : new pdg.Image(port, copy);
    }
    function pixel(img, x, y, rgba) {
        var actual = img.getPixel(x, y);
        ['red', 'green', 'blue', 'alpha'].forEach(function(channel, i) {
            expect(Math.abs(actual[channel] - rgba[i]) < 0.025).toBe(true);
        });
    }
    function close(port) {
        ports.splice(ports.indexOf(port), 1);
        pdg.gfx.closeGraphicsPort(port);
    }
    beforeEach(function() { ports = []; });
    afterEach(function() { ports.forEach(function(p) { pdg.gfx.closeGraphicsPort(p); }); });

    it('tints antialiased text once when compositing with partial opacity', function() {
        var target = create(64, 32);
        fill(target, 'blue');
        var attrs = new pdg.Attributes().textSize(20).fillColor(new pdg.Color(1, 0, 0, .5));
        target.drawText('MM', new pdg.Point(4, 24), attrs);
        var rendered = image(target), maximumRed = 0;
        for (var y = 0; y < 32; ++y) for (var x = 0; x < 64; ++x) {
            var value = rendered.getPixel(x, y);
            maximumRed = Math.max(maximumRed, value.red);
            expect(Math.abs(value.red + value.blue - 1) < .025).toBe(true);
            expect(value.green < .025 && value.alpha > .975).toBe(true);
        }
        expect(maximumRed > .45 && maximumRed < .525).toBe(true);
        if (typeof rendered.delete === 'function') rendered.delete();
        if (typeof attrs.delete === 'function') attrs.delete();
    });

    it('keeps changing numeric text aligned when a repeated label becomes a cached raster', function() {
        var target = create(64, 40), label = 'Score 123';
        var attrs = new pdg.Attributes().textSize(12).fillColor('white');
        var point = new pdg.Point(4, 30), width = target.getTextWidth(label, 12);
        fill(target, 'blue'); target.drawText(label, point, attrs);
        var first = image(target, true);
        fill(target, 'blue'); target.drawText(label, point, attrs);
        var repeated = image(target, true), error = 0, ink = 0;
        for (var y = 0; y < 40; ++y) for (var x = 0; x < 64; ++x) {
            var a = first.getPixel(x, y), b = repeated.getPixel(x, y);
            error += Math.abs(a.red - b.red);
            ink += a.red > .5;
        }
        expect(ink > 20).toBe(true);
        expect(error / (64 * 40) < .025).toBe(true);
        expect(target.getTextWidth(label, 12)).toBe(width);
        [first, repeated, attrs, point].forEach(function(value) {
            if (typeof value.delete === 'function') value.delete();
        });
    });

    // The browser shape-fill check already runs these shared pixel regressions.
    // Exercise them in the native suite too, without standalone misc launchers.
    if (typeof process !== 'undefined' && process.versions && process.versions.node) {
        it('decodes and renders the first, middle and last CanvasMark ship frames', function() {
            var path = require('node:path');
            expect(require('../lib/canvasmark_ship_check')(pdg, null,
                path.resolve(__dirname, '..') + path.sep))
                .toEqual({decodedPixels:72, renderedPixels:72});
        });

        it('renders CanvasMark projected texture corners with opacity and translation', function() {
            expect(require('../lib/canvasmark_texture_check')(pdg))
                .toEqual({cornerPixels:32, untexturedFallbacks:1});
        });

        it('invalidates polygon fill caches after geometry edits and transforms', function() {
            expect(require('../lib/polygon_cache_check')(pdg)).toEqual({renderComparisons:55});
        });
    }

    it('draws image Point, Rect and Quad destinations', function() {
        var source = create(4, 4), target = create(16, 16);
        fill(source, 'red');
        var img = image(source), attrs = new pdg.Attributes();
        [new pdg.Point(4, 4),
            new pdg.Rect(4, 4, 8, 8), new pdg.Quad(new pdg.Rect(4, 4, 8, 8))].forEach(function(loc) {
            fill(target, 'blue');
            target.drawImage(img, loc, attrs);
            pixel(image(target), 5, 5, [1, 0, 0, 1]);
            pixel(image(target), 1, 1, [0, 0, 1, 1]);
        });
    });

    if (typeof window !== 'undefined' && window.FS) {
        it('reads browser drawing destination edges and quad points once', function() {
            var source=create(4,4),target=create(16,16);fill(source,'red');
            var img=image(source),attrs=new pdg.Attributes(),drawing=pdg.createDrawing();
            drawing.addRect(new pdg.Rect(0,0,4,4),attrs);
            var calls=[function(value){target.drawImage(img,value,attrs);},
                function(value){target.drawDrawing(drawing,value,attrs);},
                function(value){target.drawText('a',value,attrs);}];
            calls.forEach(function(call){
                var reads={},rect={};
                ['left','top','right','bottom'].forEach(function(key,i){
                    Object.defineProperty(rect,key,{get:function(){reads[key]=(reads[key]||0)+1;return [4,4,8,8][i];}});
                });
                call(rect);expect(reads).toEqual({left:1,top:1,right:1,bottom:1});
            });
            var reads=0,quad=new pdg.Quad(new pdg.Rect(4,4,8,8));
            fill(target,'blue');
            target.drawImage(img,{get points(){++reads;return quad.points;}},attrs);
            expect(reads).toBe(1);var rendered=image(target);pixel(rendered,5,5,[1,0,0,1]);
            pixel(rendered,1,1,[0,0,1,1]);rendered.delete();
            drawing.delete();attrs.delete();img.delete();
        });
        it('preserves browser destination errors and malformed-shape validation', function() {
            var source=create(4,4),target=create(16,16);fill(source,'red');fill(target,'blue');
            var img=image(source),attrs=new pdg.Attributes(),failure=new Error('destination unavailable');
            var drawing=pdg.createDrawing();
            [function(value){target.drawImage(img,value,attrs);},
                function(value){target.drawDrawing(drawing,value,attrs);},
                function(value){target.drawText('a',value,attrs);}].forEach(function(call){
                    var caught;try{call({left:4,top:4,get right(){throw failure;},bottom:8});}catch(error){caught=error;}
                    expect(caught).toBe(failure);
                    expect(function(){call({top:4,right:8,bottom:8});}).toThrow();
                });
            var caught;try{target.drawImage(img,{get points(){throw failure;}},attrs);}catch(error){caught=error;}
            expect(caught).toBe(failure);
            expect(function(){target.drawImage(img,{points:[{x:1,y:2}]},attrs);}).toThrow();
            var rendered=image(target);pixel(rendered,5,5,[0,0,1,1]);rendered.delete();
            drawing.delete();attrs.delete();img.delete();
        });
    }

    // The V8 fast path must not repeat accessors or swallow their exceptions.
    if (typeof process !== 'undefined' && process.versions && process.versions.node) {
        it('converts drawImage coordinates once and propagates getter/conversion errors', function() {
            var source = create(4, 4), target = create(16, 16);
            fill(source, 'red');
            var img = image(source), attrs = new pdg.Attributes(), xReads = 0, yReads = 0;
            [[4, 4], Object.create({x:4, y:4})].forEach(function(location) {
                fill(target, 'blue');
                target.drawImage(img, location, attrs);
                pixel(image(target), 5, 5, [1, 0, 0, 1]);
                pixel(image(target), 1, 1, [0, 0, 1, 1]);
            });
            target.drawImage(img, {get x() { ++xReads; return 4; }, get y() { ++yReads; return 4; }}, attrs);
            expect(xReads).toBe(1); expect(yReads).toBe(1);
            pixel(image(target), 5, 5, [1, 0, 0, 1]);
            [{}, []].forEach(function(location) {
                var order = [], array = Array.isArray(location);
                ['x', 'y'].forEach(function(axis, index) {
                    Object.defineProperty(location, array ? index : axis, {get:function() {
                        order.push('get ' + axis);
                        return {valueOf:function() { order.push('convert ' + axis); return 4; }};
                    }});
                });
                target.drawImage(img, location, attrs);
                expect(order.join(',')).toBe('get x,convert x,get y,convert y');
            });
            var failure = new Error('coordinate failure');
            function throwsOriginal(location) {
                var caught;
                try { target.drawImage(img, location, attrs); } catch (error) { caught = error; }
                expect(caught).toBe(failure);
            }
            throwsOriginal({get x() { throw failure; }, y:0});
            throwsOriginal({x:0, get y() { throw failure; }});
            throwsOriginal({x:{valueOf:function() { throw failure; }}, y:0});
            throwsOriginal(new Proxy({}, {has:function() { throw failure; }}));
            target.drawImage(img, [0, 0], attrs);
            pixel(image(target), 1, 1, [1, 0, 0, 1]);
        });
    }

    it('falls back to solid fill for an image whose texture failed to load', function() {
        var missing = new pdg.Image('data/__pdg_missing_texture_fallback__.png');
        expect(missing.getWidth()).toBe(0);
        expect(missing.getHeight()).toBe(0);
        var actualPort = create(48, 48), referencePort = create(48, 48);
        var bounds = new pdg.Rect(8, 8, 40, 40), center = new pdg.Point(24, 24);
        var triangle = new pdg.Polygon(new pdg.Point(24, 8), new pdg.Point(40, 40), new pdg.Point(8, 40));
        var shapes = [
            function(p, a) { p.drawRect(bounds, a); },
            function(p, a) { p.drawQuad(new pdg.Quad(bounds), a); },
            function(p, a) { p.drawCircle(center, 16, a); },
            function(p, a) { p.drawEllipse(center, 16, 12, a); },
            function(p, a) { p.drawPolygon(triangle, a); },
            function(p, a) { p.drawRect(bounds, a.roundedCorners(6)); }
        ];
        shapes.forEach(function(draw, index) {
            actualPort.clear(new pdg.Color(0, 0, 1, 1));
            referencePort.clear(new pdg.Color(0, 0, 1, 1));
            function attrs() { return new pdg.Attributes().fillColor('red').lineStyle(pdg.lineStyle_None); }
            draw(referencePort, attrs());
            draw(actualPort, attrs().texture(missing));
            var actual = image(actualPort), reference = image(referencePort);
            // Check a known interior/exterior as well as comparing the complete
            // contour, so two empty renders cannot satisfy the regression.
            pixel(actual, 24, 24, [1, 0, 0, 1]);
            pixel(actual, 2, 2, [0, 0, 1, 1]);
            var mismatches = 0;
            for (var y = 2; y < 48; y += 3) for (var x = 2; x < 48; x += 3) {
                var a = actual.getPixel(x, y), b = reference.getPixel(x, y);
                ['red', 'green', 'blue', 'alpha'].forEach(function(channel) {
                    if (Math.abs(a[channel] - b[channel]) >= 0.025) mismatches++;
                });
            }
            var name = ['rectangle', 'quad', 'circle', 'ellipse', 'triangle', 'rounded rectangle'][index];
            expect({shape: name, mismatches: mismatches}).toEqual({shape: name, mismatches: 0});
        });
    });

    it('clears clipped pixels exactly and supports an offscreen coordinate origin', function() {
        const p=create(32,32);p.clear(new pdg.Color(1,0,0,.5));
        pixel(image(p),2,2,[1,0,0,.5]);
        p.setDrawingOrigin(new pdg.Point(-20,40));
        expect(p.getDrawingArea()).toEqual(new pdg.Rect(-20,40,12,72));
        p.setClipRect(new pdg.Rect(-18,42,-10,50));p.clear();
        pixel(image(p),4,4,[0,0,0,0]);pixel(image(p),15,15,[1,0,0,.5]);
        fill(p,'blue',p.getDrawingArea());pixel(image(p),4,4,[0,0,1,1]);
        p.resetClipRect();p.clear();pixel(image(p),15,15,[0,0,0,0]);
    });
    it('draws continuous thick rounded borders with symmetric corners', function() {
        const p=create(100,70);p.clear(new pdg.Color(1,1,1,1));
        p.drawRect(new pdg.Rect(10,10,90,60),new pdg.Attributes().lineStyle(pdg.lineStyle_Solid)
            .lineColor('black').lineThickness(5).roundedCorners(12));
        const result=image(p);
        // Four straight edges and the center of each quarter-circle stroke.
        for (const [x,y] of [[50,10],[50,59],[10,35],[89,35],[13,13],[86,13],[13,56],[86,56]])
            expect(result.getPixel(x,y).red).toBeLessThan(.1);
        // No spikes outside the round corners, and no fill across the center.
        for (const [x,y] of [[8,8],[91,8],[8,61],[91,61],[50,35]])
            expect(result.getPixel(x,y).red).toBeGreaterThan(.95);
    });
    it('draws a small circular outline without flattening it into a rounded box', function() {
        const p=create(32,32);p.clear(new pdg.Color(1,1,1,1));
        p.drawCircle(new pdg.Point(16,16),6,new pdg.Attributes().lineStyle(pdg.lineStyle_Solid)
            .lineColor('black').lineThickness(1));
        const result=image(p);
        for (const [x,y] of [[16,10],[16,21],[10,16],[21,16]])
            expect(result.getPixel(x,y).red).toBeLessThan(.6);
        for (const [x,y] of [[10,10],[21,10],[10,21],[21,21],[16,16]])
            expect(result.getPixel(x,y).red).toBeGreaterThan(.95);
    });
    it('creates a transparent surface without replacing the main port', function() {
        var main = pdg.gfx.getMainPort(), p = create(31, 47);
        expect(pdg.gfx.getMainPort()).toBe(main);
        expect(p.getDrawingArea().width()).toBe(31);
        expect(p.getDrawingArea().height()).toBe(47);
        pixel(image(p), 0, 0, [0,0,0,0]);
        pixel(image(p), 30, 46, [0,0,0,0]);
    });
    it('rejects empty, fractional, and oversized surfaces', function() {
        [new pdg.Rect(0,10), new pdg.Rect(4.5,10), new pdg.Rect(1e10,10)].forEach(function(rect) {
            expect(pdg.gfx.createOffscreenPort(rect)).toBe(null);
        });
        if (pdg.gfx.getMainPort()) {
            expect(function() { image(pdg.gfx.getMainPort()); }).toThrow();
        }
    });
    it('constructs shared images and independent copies with explicit constants', function() {
        const p=create(16,16);
        fill(p,'red');
        const shared=new pdg.Image(p,pdg.SharedSurface);
        const copy=new pdg.Image(p,pdg.CopyPixels);
        const defaultCopy=new pdg.Image(p);
        [shared,copy,defaultCopy].forEach(function(img) {
            expect(img instanceof pdg.Image).toBe(true);
            expect(img.getWidth()).toBe(16);expect(img.getHeight()).toBe(16);
        });
        fill(p,'blue');close(p);
        pixel(shared,4,4,[0,0,1,1]);
        pixel(copy,4,4,[1,0,0,1]);pixel(defaultCopy,4,4,[1,0,0,1]);
    });
    it('requires new and a boolean copy mode for Port construction', function() {
        const p=create(16,16);
        expect(function() { pdg.Image(p,pdg.SharedSurface); }).toThrow();
        [0,1,null,'SharedSurface',{}].forEach(function(mode) {
            expect(function() { new pdg.Image(p,mode); }).toThrow();
        });
        expect(function() { new pdg.Image(p,false,123); }).toThrow();
        fill(p,'red');const copy=new pdg.Image(p,undefined);fill(p,'blue');
        pixel(copy,4,4,[1,0,0,1]);
    });
    it('takes an independent snapshot with top-left pixel coordinates', function() {
        var p = create(31,47);
        fill(p, 'red', new pdg.Rect(0,0,13,9));
        var saved = image(p);
        fill(p, 'blue');
        pixel(saved, 2, 2, [1,0,0,1]);
        pixel(saved, 2, 45, [0,0,0,0]);
        pixel(image(p), 2, 2, [0,0,1,1]);
        close(p);
        pixel(saved, 2, 2, [1,0,0,1]);
    });
    it('keeps live images current before and after drawing them', function() {
        var p = create(16,16), destination = create(16,16), live = image(p,false);
        fill(p,'red');
        destination.drawImage(live, new pdg.Point(0,0),new pdg.Attributes());
        pixel(image(destination), 4,4,[1,0,0,1]);
        fill(p,'blue');
        destination.drawImage(live, new pdg.Point(0,0),new pdg.Attributes());
        pixel(image(destination), 4,4,[0,0,1,1]);
        pixel(live,4,4,[0,0,1,1]);
        fill(p,'green');
        pixel(live,4,4,[0,128/255,0,1]);
    });
    it('retains a live surface after closing its drawing port', function() {
        var p = create(16,16), destination = create(16,16), live = image(p,false);
        fill(p,'red'); close(p);
        destination.drawImage(live, new pdg.Point(0,0),new pdg.Attributes());
        pixel(image(destination), 4,4,[1,0,0,1]);
        pixel(live,4,4,[1,0,0,1]);
    });
    it('composites alpha correctly and renders live images without darkening', function() {
        var p = create(16,16), destination = create(16,16);
        fill(p,new pdg.Color(1,0,0,0.5));
        var live = image(p,false), copy = image(p);
        pixel(copy,4,4,[1,0,0,0.5]);
        fill(destination,'white');
        destination.drawImage(live,new pdg.Point(0,0),new pdg.Attributes());
        pixel(image(destination),4,4,[1,0.5,0.5,1]);
        fill(p,new pdg.Color(0,0,1,0.5));
        pixel(live,4,4,[1/3,0,2/3,0.75]);
        live.setOpacity(0.5);
        fill(destination,'white');
        destination.drawImage(live,new pdg.Point(0,0),new pdg.Attributes());
        pixel(image(destination),4,4,[0.75,0.625,0.875,1]);
    });
    it('preserves each port clip and contents when alternating drawing targets', function() {
        var a = create(32,32), b = create(17,23);
        a.setClipRect(new pdg.Rect(2,3,12,14));
        fill(a,'red'); fill(b,'blue'); fill(a,'green');
        pixel(image(a),4,4,[0,128/255,0,1]);
        pixel(image(a),0,0,[0,0,0,0]);
        pixel(image(b),4,4,[0,0,1,1]);
        a.resetClipRect(); fill(a,'red');
        pixel(image(a),0,0,[1,0,0,1]);
    });
    it('keeps snapshots with identical dimensions distinct in the texture cache', function() {
        var p=create(16,16), destination=create(32,16);
        fill(p,'red'); var red=image(p);
        fill(p,'blue'); var blue=image(p);
        destination.drawImage(red,new pdg.Point(0,0),new pdg.Attributes());
        destination.drawImage(blue,new pdg.Point(16,0),new pdg.Attributes());
        var result=image(destination);
        pixel(result,4,4,[1,0,0,1]); pixel(result,20,4,[0,0,1,1]);
    });
    it('supports text and retained drawings', function() {
        var p=create(128,64), drawing=pdg.createDrawing();
        drawing.addRect(new pdg.Rect(0,0,16,16), new pdg.Attributes().fillColor('red').lineStyle(pdg.lineStyle_None));
        p.drawDrawing(drawing,new pdg.Point(0,0),new pdg.Attributes());
        p.drawText('Hello',new pdg.Point(20,40),new pdg.Attributes().fillColor('white').textSize(20));
        var result=image(p), textPixels=0;
        pixel(result,4,4,[1,0,0,1]);
        for(var y=16;y<60;y++) for(var x=20;x<120;x++) if(result.getAlphaValue(x,y)>0) textPixels++;
        expect(textPixels).toBeGreaterThan(30);
    });
    it('uses live images as shape textures with transparency', function() {
        var p=create(16,16), destination=create(32,32), live=image(p,false);
        fill(p,new pdg.Color(1,0,0,0.5));
        destination.drawRect(new pdg.Rect(32,32),new pdg.Attributes().texture(live).lineStyle(pdg.lineStyle_None));
        pixel(image(destination),16,16,[1,0,0,0.5]);
        fill(p,'blue');
        destination.drawEllipse(new pdg.Point(16,16),12,12,new pdg.Attributes().texture(live).lineStyle(pdg.lineStyle_None));
        pixel(image(destination),16,16,[0,0,1,1]);
    });
    it('safely samples a live image back into its own port', function() {
        var p=create(32,16);
        fill(p,'red',new pdg.Rect(0,0,16,16));
        var live=image(p,false);
        p.drawImage(live,new pdg.Point(16,0),new pdg.Attributes());
        pixel(image(p),20,4,[1,0,0,1]);
        fill(p,'blue',new pdg.Rect(0,0,16,16));
        p.drawImage(live,new pdg.Point(16,0),new pdg.Attributes());
        pixel(image(p),20,4,[0,0,1,1]);
    });
    it('serializes a live image as an independent pixel snapshot', function() {
        var p=create(16,16), live=image(p,false);
        fill(p,'red');
        var writer=new pdg.Serializer();
        writer.serialize_obj(live);
        var reader=new pdg.Deserializer();
        reader.setDataPtr(writer.getDataPtr());
        var restored=reader.deserialize_obj();
        fill(p,'blue');
        pixel(restored,4,4,[1,0,0,1]);
        pixel(live,4,4,[0,0,1,1]);
    });
    // Focused runs start without a main port. Do not close windows owned by
    // other suites when this file is part of a larger run.
    if (!pdg.gfx.getMainPort()) it('renders across contexts and retains pixels after context shutdown', function() {
        var p=create(16,16), live=image(p,false), windowPort;
        fill(p,'red');
        try {
            windowPort=pdg.gfx.createWindowPort(new pdg.Rect(128,128),'Offscreen integration');
            expect(function() { new pdg.Image(windowPort,pdg.SharedSurface); }).toThrow();
            var destination=create(16,16);
            destination.drawImage(live,new pdg.Point(0,0),new pdg.Attributes());
            pixel(image(destination),4,4,[1,0,0,1]);
            fill(p,'blue');
            destination.drawImage(live,new pdg.Point(0,0),new pdg.Attributes());
            pixel(image(destination),4,4,[0,0,1,1]);
            close(destination);
            close(p);
            pdg.gfx.closeAllGraphicsPorts();
            windowPort=null;
            pixel(live,4,4,[0,0,1,1]);
            destination=create(16,16);
            destination.drawImage(live,new pdg.Point(0,0),new pdg.Attributes());
            pixel(image(destination),4,4,[0,0,1,1]);
        } finally {
            ports.forEach(function(port) { pdg.gfx.closeGraphicsPort(port); });
            ports=[];
            if(windowPort) pdg.gfx.closeGraphicsPort(windowPort);
        }
    });
});
