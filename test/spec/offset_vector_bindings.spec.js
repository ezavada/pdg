// V8 and JavaScriptCore share these argument macros; Embind has its own converters.
if (typeof process !== 'undefined' && (process.ios || (process.versions && process.versions.node))) {
    describe('Native Offset and Vector conversion', function() {
        function callers() {
            var a = new pdg.Animated(), writer = new pdg.Serializer();
            return [function(v) { a.setSize(v); }, function(v) { a.setMovement(v); },
                function(v) { a.moveBy(v); }, function(v) { a.setCenterOffset(v); },
                function(v) { writer.serialize_offset(v); }, function(v) { writer.serialize_vector(v); }];
        }
        it('reads each coordinate once, including array and inherited coordinates', function() {
            callers().forEach(function(call) {
                [{}, []].forEach(function(value) {
                    var reads = [];
                    ['x','y'].forEach(function(axis, index) {
                        Object.defineProperty(value, Array.isArray(value) ? index : axis, {get:function() {
                            reads.push(axis); return index + 3;
                        }});
                    });
                    call(value); expect(reads).toEqual(['x','y']);
                });
                call(Object.create({x:3,y:4}));
            });
        });
        it('preserves original getter exceptions without mutating native state', function() {
            var failure = new Error('coordinate unavailable');
            callers().forEach(function(call) {
                ['x','y'].forEach(function(axis) {
                    var value = {x:3,y:4}, caught;
                    Object.defineProperty(value, axis, {get:function() { throw failure; }});
                    try { call(value); } catch(error) { caught = error; }
                    expect(caught).toBe(failure);
                });
                [{}, [3], {x:3}].forEach(function(value) { expect(function() { call(value); }).toThrow(); });
            });
            var a = new pdg.Animated(); a.setSize(7,8); a.setMovement(9,10);
            var bad = {get x() { throw failure; },y:4};
            try { a.setSize(bad); } catch(error) {}
            try { a.setMovement(bad); } catch(error) {}
            expect(a.getWidth()).toBe(7); expect(a.getHeight()).toBe(8);
            expect(a.getMovement().x).toBe(9); expect(a.getMovement().y).toBe(10);
        });
        if (!process.ios) it('coerces in coordinate order and propagates numeric/proxy exceptions', function() {
            callers().forEach(function(call) {
                var reads = [], failure = new Error('numeric conversion unavailable'), caught;
                call({get x() { reads.push('x'); return {valueOf:function() { reads.push('number x'); return 3; }}; },
                    get y() { reads.push('y'); return {valueOf:function() { reads.push('number y'); return 4; }}; }});
                expect(reads).toEqual(['x','number x','y','number y']);
                try { call({x:{valueOf:function() { throw failure; }},y:4}); } catch(error) { caught = error; }
                expect(caught).toBe(failure); caught = undefined;
                try { call(new Proxy({}, {has:function() { throw failure; }})); } catch(error) { caught = error; }
                expect(caught).toBe(failure);
            });
        });
    });
}
