if (typeof process !== 'undefined' && (process.ios || (process.versions && process.versions.node))) {
    describe('Native Quad argument conversion', function() {
        function roundTrip(value) {
            var writer=new pdg.Serializer(),reader=new pdg.Deserializer();
            writer.serialize_quad(value);reader.setDataPtr(writer.getDataPtr());return reader.deserialize_quad();
        }
        function coords(value) { return value.points.map(function(p){return [p.x,p.y];}); }
        var expected=[[1,2],[5,2],[5,8],[1,8]];
        function points(){return expected.map(function(p){return {x:p[0],y:p[1]};});}
        it('distinguishes four Points from numeric rectangle arrays', function() {
            [points(), {points:points()},new pdg.Quad(new pdg.Rect(1,2,5,8)),[1,2,5,8],
                {left:1,top:2,right:5,bottom:8},[{x:1,y:2},{x:5,y:8}]].forEach(function(value){
                expect(coords(roundTrip(value))).toEqual(expected);
            });
            if(process.ios) expect(coords(roundTrip([1,2,5,2,5,8,1,8]))).toEqual(expected);
            var rotated=roundTrip({left:1,top:2,right:5,bottom:8,radians:0.5});
            expect(rotated.points[0].x).not.toBe(1);
        });
        it('reads points, array elements and coordinates once', function() {
            var reads=[],list=[];
            expected.forEach(function(p,i){
                var point={};
                ['x','y'].forEach(function(key,j){Object.defineProperty(point,key,{get:function(){reads.push(i+key);return p[j];}});});
                Object.defineProperty(list,i,{get:function(){reads.push('point'+i);return point;}});
            });
            expect(coords(roundTrip({get points(){reads.push('points');return list;}}))).toEqual(expected);
            expect(reads.sort()).toEqual(['0x','0y','1x','1y','2x','2y','3x','3y','point0','point1','point2','point3','points']);
            var edges=[],array=[];
            [1,2,5,8].forEach(function(v,i){Object.defineProperty(array,i,{get:function(){edges.push(i);return v;}});});
            expect(coords(roundTrip(array))).toEqual(expected);expect(edges).toEqual([0,1,2,3]);
        });
        it('preserves errors and leaves the serializer untouched', function() {
            var failure=new Error('quad unavailable'),list=points();
            list[2]={get x(){throw failure;},y:8};
            var array=points();Object.defineProperty(array,1,{get:function(){throw failure;}});
            [{get points(){throw failure;}},{points:list},array,
                {left:1,top:2,right:5,bottom:8,get radians(){throw failure;}},
                {left:1,top:2,right:5,bottom:8,centerOffset:{get x(){throw failure;},y:2}}].forEach(function(value){
                    var writer=new pdg.Serializer(),caught;
                    try {writer.serialize_quad(value);}catch(error){caught=error;}
                    expect(caught).toBe(failure);expect(writer.getDataSize()).toBe(0);
                });
        });
        it('rejects malformed point collections', function() {
            [{points:[{x:1,y:2}]}, {points:[{x:1,y:2},{x:3,y:4},{x:5},{x:7,y:8}]},{}].forEach(function(value){
                expect(function(){roundTrip(value);}).toThrow();
            });
        });
    });
}
