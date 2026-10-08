if (typeof pdg.Polygon === 'function' && typeof process !== 'undefined' && (process.ios || (process.versions && process.versions.node))) {
    describe('Native Polygon constructor conversion', function() {
        it('validates null as an invalid move target without changing vertices', function() {
            var polygon = new pdg.Polygon({x:1,y:2});
            expect(function() { polygon.moveTo(null); }).toThrow();
            expect(polygon.getPoint(0).x).toBe(1);
            expect(polygon.getPoint(0).y).toBe(2);
        });
        it('moves to coordinates or a Point and returns the receiver', function() {
            var polygon = new pdg.Polygon({x:1,y:2}, {x:5,y:8});
            expect(polygon.moveTo(10,20)).toBe(polygon);
            expect(polygon.getBounds().left).toBe(10);
            expect(polygon.getBounds().top).toBe(20);
            expect(polygon.moveTo(new pdg.Point(30,40))).toBe(polygon);
            expect(polygon.getBounds().left).toBe(30);
            expect(polygon.getBounds().top).toBe(40);
        });
        it('accepts arrays and separate vertices while reading coordinates once', function() {
            [false,true].forEach(function(arrayForm){
                var reads=[],point={get x(){reads.push('x');return 3;},get y(){reads.push('y');return 4;}};
                var polygon=arrayForm ? new pdg.Polygon([point,{x:8,y:9}]) : new pdg.Polygon(point,{x:8,y:9});
                expect(reads).toEqual(['x','y']);expect(polygon.getPointCount()).toBe(2);
                expect(polygon.getPoint(0).x).toBe(3);expect(polygon.getPoint(0).y).toBe(4);
            });
        });
        it('returns original vertex and array getter exceptions without aborting', function() {
            var failure=new Error('vertex unavailable');
            var point={x:1,get y(){throw failure;}},array=[{x:1,y:2}];
            Object.defineProperty(array,0,{get:function(){throw failure;}});
            [function(){new pdg.Polygon(point);},function(){new pdg.Polygon([point]);},function(){new pdg.Polygon(array);}].forEach(function(call){
                var caught;try{call();}catch(error){caught=error;}expect(caught).toBe(failure);
            });
            expect(new pdg.Polygon([{x:1,y:2}]).getPointCount()).toBe(1);
        });
        it('rejects malformed vertices in both constructor forms', function() {
            [{},{x:1},3,null].forEach(function(value){
                expect(function(){new pdg.Polygon([value]);}).toThrow();
                expect(function(){new pdg.Polygon({x:0,y:0},value);}).toThrow();
            });
            expect(new pdg.Polygon().getPointCount()).toBe(0);
        });
        if(!process.ios) it('preserves errors raised by numeric coercion', function() {
            var failure=new Error('vertex number unavailable'),caught;
            try{new pdg.Polygon([{x:{valueOf:function(){throw failure;}},y:2}]);}catch(error){caught=error;}
            expect(caught).toBe(failure);
        });
    });
}
