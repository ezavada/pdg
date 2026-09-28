if (typeof process !== 'undefined' && (process.ios || (process.versions && process.versions.node))) {
    describe('Native rectangle argument conversion', function() {
        function roundTrip(type, value) {
            var writer = new pdg.Serializer(), reader = new pdg.Deserializer();
            writer['serialize_' + type](value); reader.setDataPtr(writer.getDataPtr());
            return reader['deserialize_' + type]();
        }
        function edges(rect) { return [rect.left,rect.top,rect.right,rect.bottom]; }
        function accessor(fields, reads, prefix) {
            var value = {}; prefix = prefix || '';
            Object.keys(fields).forEach(function(key) {
                Object.defineProperty(value,key,{get:function() { reads.push(prefix+key); return fields[key]; }});
            });
            return value;
        }
        it('keeps object, array, inherited and nested-corner forms', function() {
            var forms = [new pdg.Rect(1,2,5,8), {left:1,top:2,right:5,bottom:8},
                Object.create({left:1,top:2,right:5,bottom:8}), [1,2,5,8],
                {topLeft:{x:1,y:2},bottomRight:{x:5,y:8}}, [{x:1,y:2},{x:5,y:8}],
                {topLeft:{x:1,y:2},width:4,height:6}];
            forms.forEach(function(value) { expect(edges(roundTrip('rect',value))).toEqual([1,2,5,8]); });
            [[4,6],{width:4,height:6}].forEach(function(value) {
                expect(edges(roundTrip('rect',value))).toEqual([0,0,4,6]);
            });
            if(process.ios) [{top:2,left:1,bottomRight:{x:5,y:8}},
                {topLeft:{x:1,y:2},right:5,bottom:8}, [{x:1,y:2},4,6], [4,6,{x:1,y:2}]].forEach(function(value) {
                    expect(edges(roundTrip('rect',value))).toEqual([1,2,5,8]);
                });
        });
        it('reads edges, nested points and optional rotation only once', function() {
            ['rect','rotr'].forEach(function(type) {
                var reads=[], value=accessor({left:1,top:2,right:5,bottom:8},reads);
                roundTrip(type,value); expect(reads.sort()).toEqual(['bottom','left','right','top']);
                reads=[];
                value=accessor({topLeft:accessor({x:1,y:2},reads,'a.'),
                    bottomRight:accessor({x:5,y:8},reads,'b.')},reads);
                expect(edges(roundTrip(type,value))).toEqual([1,2,5,8]);
                expect(reads.sort()).toEqual(['a.x','a.y','b.x','b.y','bottomRight','topLeft']);
            });
            var reads=[], center=accessor({x:3,y:4},reads,'center.');
            var value=accessor({left:1,top:2,right:5,bottom:8,radians:0.5,centerOffset:center},reads);
            var result=roundTrip('rotr',value);
            expect(result.radians).toBeCloseTo(0.5,5); expect(result.centerOffset.x).toBe(3);
            expect(reads.sort()).toEqual(['bottom','center.x','center.y','centerOffset','left','radians','right','top']);
            expect(roundTrip('rotr',{width:4,height:6}).radians).toBe(0);
        });
        it('preserves getter exceptions, including optional fields, without writing data', function() {
            ['rect','rotr'].forEach(function(type) {
                var failure=new Error('rectangle unavailable');
                var values=[{get left(){throw failure;},top:2,right:5,bottom:8},
                    {topLeft:{get x(){throw failure;},y:2},bottomRight:{x:5,y:8}},
                    {width:4,get height(){throw failure;}}];
                var array=[1,2,5,8];Object.defineProperty(array,2,{get:function(){throw failure;}});values.push(array);
                if(type==='rotr') {
                    values.push({left:1,top:2,right:5,bottom:8,get radians(){throw failure;}});
                    values.push({left:1,top:2,right:5,bottom:8,get centerOffset(){throw failure;}});
                    values.push({left:1,top:2,right:5,bottom:8,centerOffset:{x:3,get y(){throw failure;}}});
                }
                values.forEach(function(value) {
                    var writer=new pdg.Serializer(),caught;
                    try {writer['serialize_'+type](value);} catch(error){caught=error;}
                    expect(caught).toBe(failure);expect(writer.getDataSize()).toBe(0);
                });
            });
        });
        it('rejects invalid shapes and malformed optional centers', function() {
            [{},{left:1},{topLeft:{x:1},bottomRight:{x:5,y:8}},[1]].forEach(function(value) {
                expect(function(){roundTrip('rect',value);}).toThrow();
            });
            expect(function(){roundTrip('rotr',{left:1,top:2,right:5,bottom:8,centerOffset:{x:3}});}).toThrow();
        });
        if(!process.ios) it('preserves V8 numeric conversion order and errors', function() {
            var order=[],failure=new Error('numeric rectangle unavailable');
            var value={};
            ['left','top','right','bottom'].forEach(function(key,index) {
                Object.defineProperty(value,key,{get:function(){order.push(key);return {valueOf:function(){order.push('number '+key);return index;}};}});
            });
            roundTrip('rect',value);
            expect(order).toEqual(['left','number left','top','number top','right','number right','bottom','number bottom']);
            var caught;
            try {roundTrip('rect',{left:{valueOf:function(){throw failure;}},top:0,right:5,bottom:8});} catch(error){caught=error;}
            expect(caught).toBe(failure);
        });
    });
}
