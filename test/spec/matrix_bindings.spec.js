if (typeof pdg.Attributes === 'function' && typeof process !== 'undefined' && (process.ios || (process.versions && process.versions.node))) {
    describe('Native matrix argument conversion', function() {
        var identity=[1,0,0,0,1,0,0,0,1];
        function eachMethod(test) {
            [pdg.Attributes,pdg.AnimatedAttributes].forEach(function(Class){
                ['transform','setTransform','changeTransform'].forEach(function(method){
                    var attrs=new Class();if(typeof attrs[method]!=='function')return;
                    if(attrs.setSize)attrs.setSize(1,1);
                    test(attrs,function(matrix){return method==='changeTransform' ? attrs[method](matrix,0) : attrs[method](matrix);});
                });
            });
        }
        it('reads each numeric matrix element once', function() {
            eachMethod(function(attrs,call){
                var matrix=[],reads=[];
                identity.forEach(function(value,i){Object.defineProperty(matrix,i,{get:function(){reads.push(i);return value;}});});
                expect(call(matrix)).toBe(attrs);expect(reads).toEqual([0,1,2,3,4,5,6,7,8]);
            });
        });
        it('preserves element getter exceptions and stops before mutation', function() {
            eachMethod(function(attrs,call){
                var before=attrs.getTransform(),matrix=identity.slice(),failure=new Error('matrix unavailable'),caught,reads=[];
                Object.defineProperty(matrix,4,{get:function(){throw failure;}});
                Object.defineProperty(matrix,5,{get:function(){reads.push(5);return 0;}});
                try{call(matrix);}catch(error){caught=error;}
                expect(caught).toBe(failure);expect(reads).toEqual([]);expect(attrs.getTransform()).toEqual(before);
            });
        });
        it('rejects invalid lengths and nonnumeric elements without mutation', function() {
            eachMethod(function(attrs,call){
                var before=attrs.getTransform();
                [[],identity.slice(0,8),identity.concat(0),identity.map(function(v,i){return i===4 ? '1' : v;})].forEach(function(matrix){
                    expect(function(){call(matrix);}).toThrow();expect(attrs.getTransform()).toEqual(before);
                });
            });
        });
    });
}
