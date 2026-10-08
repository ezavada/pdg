describe('Scene collision queries', function() {
    var scenes;
    function scene() { var s=new pdg.Scene();s.setManual(true);scenes.push(s);return s; }
    function point(x,y) { return new pdg.Point(x,y||0); }
    function disk(layer,x,r) { var s=layer.createSprite();s.setLocation(x,0);s.setupCollider().setCircle(r);return s; }
    beforeEach(function(){scenes=[];});
    afterEach(function(){scenes.forEach(function(s){s.dispose();});});
    it('returns single casts or null, and capped sorted arrays for multiple casts',function(){
        var s=scene(),l=s.createSpriteLayer(),far=disk(l,20,2),close=disk(l,10,1);
        expect(pdg.CollisionQueryBuffer).toBeUndefined();
        expect(pdg.getInterfaceMetadata().interface.some(function(m){return m.name==='CollisionQueryBuffer';})).toBe(false);
        expect(pdg.getInterfaceMetadata('Scene').interface.some(function(m){return m.name.charAt(0)==='_';})).toBe(false);
        expect(s.raycast(point(0),point(30)).collider).toBe(close.collider);
        expect(s.sweepCircle(point(0),1,new pdg.Vector(30,0)).distance).toBeCloseTo(8,5);
        var hits=s.raycast(point(0),point(30),1,{maxHits:1});
        expect(Array.isArray(hits)).toBe(true);expect(hits.length).toBe(1);
        expect(hits[0].collider).toBe(close.collider);expect(hits[0].distance).toBeCloseTo(9,5);
        expect(s.raycast(point(0),point(30),{maxHits:0}).collider).toBe(close.collider);
        expect(s.raycast(point(0),point(30),1,{excludedColliders:[close.collider]})[0].collider).toBe(far.collider);
        expect(s.sweepCircle(point(0),1,new pdg.Vector(30,0),1).length).toBe(1);
        hits=s.sweepCircle(point(0),1,new pdg.Vector(30,0),16);expect(hits.length).toBe(2);
        expect(hits[1].collider).toBe(far.collider);
        expect(s.raycast(point(0,10),point(30,10))).toBe(null);
        expect(s.sweepCircle(point(0,10),1,new pdg.Vector(30,0))).toBe(null);
    });
    it('reuses one array, hit records and coordinates per scene, growing only as needed',function(){
        var s=scene(),l=s.createSpriteLayer(),one=disk(l,10,1),two=disk(l,20,1),ui=scene();
        var hits=s.raycast(point(0),point(30),4,{maxHits:4}),first=hits[0],second=hits[1],position=first.point,normal=first.normal;
        expect(s.overlapPoint(point(20))).toBe(hits);expect(hits.length).toBe(1);
        expect(hits[0]).toBe(first);expect(first.collider).toBe(two.collider);
        expect(first.point).toBe(position);expect(first.normal).toBe(normal);expect(second.collider).toBe(null);
        expect(s.raycast(point(0),point(30),16)).toBe(hits);expect(hits[1]).toBe(second);
        expect(ui.overlapPoint(point(0))).not.toBe(hits);expect(hits.length).toBe(2);
        expect(s.raycast(point(0),point(30))).toBe(first);expect(hits.length).toBe(1);
        var saved={collider:first.collider,distance:first.distance,point:new pdg.Point(first.point.x,first.point.y)};
        expect(s.overlapPoint(point(100))).toBe(hits);expect(hits.length).toBe(0);expect(first.collider).toBe(null);
        expect(saved.collider).toBe(one.collider);expect(saved.distance).toBeCloseTo(9,5);
        s.raycast(point(0),point(30),16);s.dispose();expect(hits.length).toBe(0);expect(first.collider).toBe(null);
    });
    it('filters layers, categories, sensors, owners and predicates before limiting results',function(){
        var s=scene(),a=s.createSpriteLayer(),b=s.createSpriteLayer(),one=disk(a,10,1),two=disk(b,20,1);
        a.setQueryBits(1);b.setQueryBits(2);one.collider.setCategory(4).setCollisionMask(0);two.collider.setCategory(8);
        expect(s.raycast(point(0),point(30),{layerMask:1,categoryMask:4}).collider).toBe(one.collider);
        expect(s.raycast(point(0),point(30),16,{layerMask:1,layers:[b]}).length).toBe(0);
        expect(s.raycast(point(0),point(30),16,{layers:[]}).length).toBe(0);
        b.moveToBack();expect(s.raycast(point(0),point(30),{layerMask:2}).collider).toBe(two.collider);
        one.collider.setSensor(true);
        expect(s.raycast(point(0),point(30),{includeSensors:false}).collider).toBe(two.collider);
        expect(s.raycast(point(0),point(30),{excludedColliders:[one.collider]}).collider).toBe(two.collider);
        var body=one.setupPhysicsBody();expect(s.raycast(point(0),point(30),{excludedBodies:[body]}).collider).toBe(two.collider);
        var calls=0,hits=s.raycast(point(0),point(30),1,{maxHits:1,predicate:function(c){++calls;return c===two.collider;}});
        expect(calls).toBe(2);expect(hits[0].collider).toBe(two.collider);
    });
    it('clears reused results on failure and rejects recursive queries or scene mutation',function(){
        var s=scene(),l=s.createSpriteLayer();disk(l,10,1);var hits=s.raycast(point(0),point(20),16);
        [function(){throw new Error('failed');},function(){return 1;},function(){s.overlapPoint(point(10));return true;},function(){s.advance(.01);return true;},function(){s.createSpriteLayer();return true;},function(){s.dispose();return true;}].forEach(function(predicate){
            expect(function(){s.raycast(point(0),point(20),16,{predicate:predicate});}).toThrow();
            expect(hits.length).toBe(0);
        });
        expect(s.raycast(point(0),point(20)).distance).toBeCloseTo(9,5);
    });
    it('uses authoritative paused poses and immediate scene membership',function(){
        var s=scene(),l=s.createSpriteLayer(),owner=disk(l,0,1),ui=scene();
        s.setFixedStep(1/60);s.setInterpolation(true);owner.setMovement(60,0);s.advance(1/60+.5/60);
        expect(s.overlapPoint(point(1.75)).length).toBe(1);
        s.pause();owner.setLocation(10,0);s.setTimeScale(0);expect(s.overlapPoint(point(10)).length).toBe(1);
        s.removeLayer(l);expect(s.overlapPoint(point(10)).length).toBe(0);
        expect(function(){s.overlapPoint(point(10),{layers:[l]});}).toThrow();
        ui.addLayer(l);expect(ui.overlapPoint(point(10)).length).toBe(1);
        ui.dispose();expect(function(){ui.overlapPoint(point(10));}).toThrow();
    });
    it('preserves concave holes and returns nearest filled points or null',function(){
        var s=scene(),l=s.createSpriteLayer(),owner=l.createSprite();
        owner.setupCollider().setPolygon([point(0),point(4),point(4,1),point(1,1),point(1,4),point(0,4)]);
        expect(s.overlapPoint(point(3,3)).length).toBe(0);
        expect(s.raycast(point(-1,.5),point(5,.5),16).length).toBe(1);
        expect(s.nearestPoint(point(3,3),3).distance).toBeCloseTo(2,5);
        expect(s.nearestPoint(point(.5,.5),0).distance).toBe(0);expect(s.nearestPoint(point(3,3),1)).toBe(null);
        var hit=s.raycast(point(.5,.5),point(.5,.5));expect(hit.initialOverlap).toBe(true);expect(hit.normal.x).toBe(0);
    });
    it('queries capsule targets, polygon corner sweeps and region overlaps',function(){
        var s=scene(),l=s.createSpriteLayer(),owner=l.createSprite();owner.setupCollider().setCapsule(point(10),point(14),1);
        expect(s.raycast(point(0,1),point(20,1)).distance).toBeCloseTo(10,5);
        owner.collider.setBox(new pdg.Rect(10,0,12,2));
        expect(s.sweepCircle(point(0,-.5),1,new pdg.Vector(20,0)).distance).toBeCloseTo(10-Math.sqrt(.75),4);
        expect(s.overlapCircle(point(9),1).length).toBe(1);
        expect(s.overlapCapsule(point(9,-1),point(9,3),1).length).toBe(1);
        expect(s.overlapBox(new pdg.RotatedRect(new pdg.Rect(9,0,11,2),.2)).length).toBe(1);
    });
    it('validates hit limits and geometry and rejects queries during advance',function(){
        var s=scene(),l=s.createSpriteLayer();disk(l,10,1);
        expect(s.raycast(point(0),point(20),0,{maxHits:0}).length).toBe(0);
        [-1,1.5,NaN,Infinity,1048577].forEach(function(n){expect(function(){s.overlapPoint(point(10),{maxHits:n});}).toThrow();});
        [-1,1.5,NaN,Infinity,1048577].forEach(function(n){expect(function(){s.raycast(point(0),point(20),n);}).toThrow();});
        expect(function(){s.sweepCircle(point(0),-1,new pdg.Vector(1,0));}).toThrow();
        expect(function(){s.nearestPoint(point(0),Infinity);}).toThrow();
        expect(function(){s.overlapPoint(point(10),{layerMask:NaN});}).toThrow();
        expect(function(){s.raycast(point(0),point(20),{},{});}).toThrow();
        var called=false;s.onTimeout(function(){called=true;expect(function(){s.overlapPoint(point(10));}).toThrow();},1);
        s.advance(.01);expect(called).toBe(true);
    });
});
