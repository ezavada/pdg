if (typeof process !== 'undefined' && (process.ios || (process.versions && process.versions.node))) {
    describe('Native Color argument conversion', function() {
        function roundTrip(value) {
            var writer=new pdg.Serializer(),reader=new pdg.Deserializer();
            writer.serialize_color(value);reader.setDataPtr(writer.getDataPtr());return reader.deserialize_color();
        }
        function channels(value) {return [value.red,value.green,value.blue,value.alpha];}
        function expectChannels(value,expected) {
            channels(roundTrip(value)).forEach(function(v,i){expect(v).toBeCloseTo(expected[i],2);});
        }
        it('parses short and long hex strings, names and opaque black',function(){
            ['#abc','#AbC','#aabbcc'].forEach(function(value){expectChannels(value,[170/255,187/255,204/255,1]);});
            expectChannels('#f00',[1,0,0,1]);expectChannels('yellowgreen',[154/255,205/255,50/255,1]);
            ['black','#000','#000000'].forEach(function(value){expectChannels(value,[0,0,0,1]);});
        });
        it('rejects incomplete or invalid CSS strings before writing data',function(){
            ['','#','#0','#00','#0000','#00000','#0000000','#ggg','#gggggg','#ff00gg','#12 345','notacolor','black\0junk','#abc\0junk'].forEach(function(value){
                var writer=new pdg.Serializer();expect(function(){writer.serialize_color(value);}).toThrow();
                expect(writer.getDataSize()).toBe(0);
            });
        });
        it('reads RGB and optional alpha once for objects and arrays',function(){
            [false,true].forEach(function(arrayForm){
                var reads=[],value=arrayForm?[]:{};
                ['red','green','blue','alpha'].forEach(function(key,i){Object.defineProperty(value,arrayForm?i:key,{get:function(){reads.push(key);return [0.2,0.4,0.6,0.8][i];}});});
                expectChannels(value,[0.2,0.4,0.6,0.8]);expect(reads).toEqual(['red','green','blue','alpha']);
            });
            expectChannels({red:0.2,green:0.4,blue:0.6},[0.2,0.4,0.6,1]);
            expectChannels([0.2,0.4,0.6],[0.2,0.4,0.6,1]);
            expectChannels(0xff336699,[0.2,0.4,0.6,1]);
        });
        it('preserves getter exceptions without serializing partial data',function(){
            var failure=new Error('color unavailable'),array=[0.2,0.4,0.6];
            Object.defineProperty(array,1,{get:function(){throw failure;}});
            [array,{red:0.2,get green(){throw failure;},blue:0.6},
                {red:0.2,green:0.4,blue:0.6,get alpha(){throw failure;}}].forEach(function(value){
                    var writer=new pdg.Serializer(),caught;
                    try{writer.serialize_color(value);}catch(error){caught=error;}
                    expect(caught).toBe(failure);expect(writer.getDataSize()).toBe(0);
                });
        });
        if(process.ios) it('initializes byte channels, including optional alpha',function(){
            expectChannels([255,128,64],[1,128/255,64/255,1]);
            expectChannels({red:255,green:128,blue:64,alpha:128},[1,128/255,64/255,128/255]);
            expectChannels([255,0,0,0],[1,0,0,0]);
        });
        else it('preserves V8 numeric coercion and proxy errors',function(){
            expectChannels({red:'0.2',green:'0.4',blue:'0.6'},[0.2,0.4,0.6,1]);
            var failure=new Error('color number unavailable');
            [{red:{valueOf:function(){throw failure;}},green:0,blue:0},
                new Proxy({},{has:function(){throw failure;}})].forEach(function(value){
                    var caught;try{roundTrip(value);}catch(error){caught=error;}expect(caught).toBe(failure);
                });
        });
    });
}
