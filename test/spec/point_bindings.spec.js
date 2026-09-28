// Native V8/JSC binding macros; the browser uses separate Embind converters.
if (typeof process !== 'undefined' && (process.ios || (process.versions && process.versions.node))) {
    describe('Native Point argument conversion', function() {
        function callers() {
            var animated = new pdg.Animated(), writer = new pdg.Serializer();
            var owner = new pdg.Sprite(), collider = owner.setupCollider();
            var entries = [
                function(point) { animated.setLocation(point); },
                function(point) { animated.moveTo(point); },
                function(point) { writer.serialize_point(point); },
                function(point) { collider.setCircle(1, point); },
                function(point) { collider.contains(point); }
            ];
            if (pdg.Attributes) {
                var attrs = new pdg.Attributes();
                entries.push(function(point) { attrs.rotation(0, point); });
            }
            return entries;
        }
        function throwsOriginal(call, point, failure) {
            var caught;
            try { call(point); } catch (error) { caught = error; }
            expect(caught).toBe(failure);
        }
        it('reads coordinates once in overloaded, required and optional arguments', function() {
            callers().forEach(function(call) {
                [{}, []].forEach(function(point) {
                    var reads = [], array = Array.isArray(point);
                    ['x', 'y'].forEach(function(axis, index) {
                        Object.defineProperty(point, array ? index : axis, {get:function() {
                            reads.push(axis); return index + 3;
                        }});
                    });
                    call(point);
                    expect(reads).toEqual(['x', 'y']);
                });
                call(Object.create({x:3, y:4}));
                call(new pdg.Point(3, 4));
            });
        });
        it('preserves getter exceptions and stops before reading later coordinates', function() {
            callers().forEach(function(call) {
                ['x', 'y'].forEach(function(axis, index) {
                    [{x:3, y:4}, [3, 4]].forEach(function(point) {
                        var failure = new Error('coordinate unavailable'), reads = [];
                        var array = Array.isArray(point);
                        ['x', 'y'].forEach(function(name, i) {
                            Object.defineProperty(point, array ? i : name, {get:function() {
                                reads.push(name);
                                if (name === axis) throw failure;
                                return i + 3;
                            }});
                        });
                        throwsOriginal(call, point, failure);
                        expect(reads).toEqual(index === 0 ? ['x'] : ['x', 'y']);
                        call(new pdg.Point(3, 4));
                    });
                });
            });
        });
        it('does not mutate native state when conversion fails and supports reentrant getters', function() {
            var animated = new pdg.Animated(), writer = new pdg.Serializer();
            var failure = new Error('stop'), point = {x:7, get y() { throw failure; }};
            animated.setLocation(1, 2);
            throwsOriginal(function(p) { animated.setLocation(p); }, point, failure);
            expect(animated.getLocation()).toEqual(new pdg.Point(1, 2));
            var bytes = writer.getDataSize();
            throwsOriginal(function(p) { writer.serialize_point(p); }, point, failure);
            expect(writer.getDataSize()).toBe(bytes);
            animated.setLocation({get x() { animated.setLocation(8, 9); return 3; }, y:4});
            expect(animated.getLocation()).toEqual(new pdg.Point(3, 4));
        });
        it('retains invalid-shape checks and optional defaults', function() {
            callers().forEach(function(call) {
                [{}, [], [3], {x:3}, {y:4}].forEach(function(point) {
                    expect(function() { call(point); }).toThrow();
                });
            });
            var collider = new pdg.Sprite().setupCollider();
            collider.setCircle(1);
            expect(collider.contains(new pdg.Point(0, 0))).toBe(true);
            collider.setCircle(1, {x:3, y:4});
            expect(collider.contains(new pdg.Point(0, 0))).toBe(false);
            expect(collider.contains(new pdg.Point(3, 4))).toBe(true);
        });
        it('converts collider vertices once and leaves existing geometry intact on failure', function() {
            var collider = new pdg.Sprite().setupCollider(), reads = 0;
            collider.setPolygon([{get x() { ++reads; return 0; }, y:0}, {x:4,y:0}, {x:0,y:4}]);
            expect(reads).toBe(1);
            expect(collider.contains({x:1,y:1})).toBe(true);
            var failure = new Error('vertex unavailable');
            var vertices = [{x:9,y:9}, {get x() { throw failure; },y:0}, {x:0,y:4}];
            throwsOriginal(function(points) { collider.setPolygon(points); }, vertices, failure);
            expect(collider.contains({x:1,y:1})).toBe(true);
        });
        if (!process.ios) it('keeps V8 coercion order and propagates numeric and proxy exceptions', function() {
            callers().forEach(function(call) {
                var order = [];
                call({get x() { order.push('get x'); return {valueOf:function() { order.push('convert x'); return 3; }}; },
                    get y() { order.push('get y'); return {valueOf:function() { order.push('convert y'); return 4; }}; }});
                expect(order).toEqual(['get x','convert x','get y','convert y']);
                var failure = new Error('conversion unavailable');
                throwsOriginal(call, {x:{valueOf:function() { throw failure; }},y:4}, failure);
                throwsOriginal(call, new Proxy({}, {has:function() { throw failure; }}), failure);
            });
        });
        if (process.ios) it('retains JavaScriptCore numeric and indexed-object acceptance', function() {
            callers().forEach(function(call) {
                call({0:3, 1:4});
                expect(function() { call({x:'3', y:4}); }).toThrow();
            });
        });
        if (pdg.hasGraphics) it('shares single-read Point dispatch across image, drawing and text', function() {
            var source = pdg.gfx.createOffscreenPort(new pdg.Rect(4, 4));
            var target = pdg.gfx.createOffscreenPort(new pdg.Rect(16, 16));
            try {
                var image = new pdg.Image(source), drawing = pdg.createDrawing(), attrs = new pdg.Attributes();
                [function(point) { target.drawImage(image, point, attrs); },
                    function(point) { target.drawDrawing(drawing, point, attrs); },
                    function(point) { target.drawText('', point, attrs); }].forEach(function(call) {
                    var reads = [];
                    call({get x() { reads.push('x'); return 0; }, get y() { reads.push('y'); return 0; }});
                    expect(reads).toEqual(['x','y']);
                    var failure = new Error('drawing coordinate unavailable');
                    throwsOriginal(call, {get x() { throw failure; }, y:0}, failure);
                });
            } finally {
                pdg.gfx.closeGraphicsPort(target); pdg.gfx.closeGraphicsPort(source);
            }
        });
    });
}
