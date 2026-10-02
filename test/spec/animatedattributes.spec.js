require('./SpecHelper');
describe('AnimatedAttributes', function() {
    it('keeps the proportional fit alias mapped to overflow', function() {
        expect(pdg.fit_FillKeepProportions).toBe(pdg.fit_Overflow);
        expect(new pdg.Attributes().fitType(pdg.fit_FillKeepProportions).getFitType()).toBe(pdg.fit_Overflow);
    });
    it('stores text styles without requiring a graphics backend', function() {
        const plain = new pdg.Attributes(), animated = new pdg.AnimatedAttributes();
        ['Plain', 'Bold', 'Italic', 'Underline', 'Centered', 'LeftJustified', 'RightJustified'].forEach(function(name) {
            const style = pdg['textStyle_' + name];
            expect(typeof style).toBe('number');
            [plain, animated].forEach(function(attributes) {
                expect(attributes.textStyle(style)).toBe(attributes);
                expect(attributes.getTextStyle()).toBe(style);
            });
        });
        const combined = pdg.textStyle_Bold | pdg.textStyle_Italic | pdg.textStyle_Centered;
        expect(plain.textStyle(combined).getTextStyle()).toBe(19);
        expect(animated.textStyle(combined).getTextStyle()).toBe(19);
        expect(animated.textStyle(pdg.textStyle_Plain).getTextStyle()).toBe(0);
    });
    it('combines both APIs, while excluding physics and discrete appearance tracks', function() {
        const a=new pdg.AnimatedAttributes();
        expect(a instanceof pdg.Animated).toBe(true);
        expect(a instanceof pdg.AnimatedAttributes).toBe(true);
        // JS has one prototype chain; native Attributes parameters accept both classes.
        expect(a instanceof pdg.Attributes).toBe(false);
        expect('physics' in a).toBe(false);
        for (const name of ['BlendMode','Font','ClipOverflow','LineStyle','TextStyle','Texture','FitType']) {
            expect(typeof a['animate'+name]).toBe('undefined');
        }
        const plain=new pdg.Attributes();
        for (const name of ['translation','rotation','scale']) {
            expect(typeof a[name]).toBe('function');
            expect(typeof plain[name]).toBe('function');
        }
        expect(a.getWidth()).toBe(1);expect(a.getHeight()).toBe(1);
        a.fitType(pdg.fit_Inside).lineStyle(pdg.lineStyle_Solid).clipOverflow(true);
        expect(a.getFitType()).toBe(pdg.fit_Inside);expect(a.getClipOverflow()).toBe(true);
    });
    function expectTransform(attributes, values) {
        const matrix=attributes.getTransform();
        [0,1,3,4,6,7].forEach(function(index,i) {
            expect(matrix[index]).toBeCloseTo(values[i],4);
        });
    }
    it('uses inherited transform methods and captures their results in Drawing attributes', function() {
        const a=new pdg.AnimatedAttributes(), d=pdg.createDrawing();
        for (const name of ['Translation','Rotation','Scale']) {
            expect(typeof a['animate'+name]).toBe('undefined');
        }
        expect(a.setLocation(new pdg.Point(10,20)).setSize(2,3).setScale(4,5)
            .setRotation(Math.PI/2)).toBe(a);
        // Drawing must receive the updated Attributes even before getTransform() is called.
        const element=d.addRect(new pdg.Rect(0,0,1,1),a);
        expectTransform(element.getAttributes(),[0,8,-15,0,10,20]);
        expect(a.moveBy(2,3).grow(2).stretch(.5,2).rotateBy(-Math.PI/2)).toBe(a);
        expectTransform(a,[8,0,0,60,12,23]);
        expectTransform(element.getAttributes(),[0,8,-15,0,10,20]);
        element.setAttributes(a);
        expectTransform(element.getAttributes(),[8,0,0,60,12,23]);
    });
    it('composes Attributes transforms while sharing Animated state', function() {
        const a=new pdg.AnimatedAttributes();
        a.setLocation(new pdg.Point(10,20)).rotateTo(Math.PI/2);
        expect(a.translation(new pdg.Offset(4,0))).toBe(a);
        expect(a.getLocation().x).toBeCloseTo(10,4);
        expect(a.getLocation().y).toBeCloseTo(24,4);
        expect(a.scale(2,3)).toBe(a);expectTransform(a,[0,2,-3,0,10,24]);
        expect(a.rotation(-Math.PI/2)).toBe(a);expectTransform(a,[3,0,0,2,10,24]);
        expect(a.getWidth()).toBe(1);expect(a.getHeight()).toBe(1);
        expect(a.getScale().x).toBeCloseTo(3,4);
        a.setLocation(new pdg.Point(5,6)).rotateTo(0).setScale(2,1);
        expectTransform(a,[2,0,0,1,5,6]);
        a.setTransform([1,0,0,0,1,0,0,0,1]);
        const plain=new pdg.Attributes();
        for (const style of [a,plain]) {
            style.translation(new pdg.Offset(4,7)).rotation(.3,new pdg.Point(2,3)).scale(2,3,new pdg.Point(1,2));
        }
        a.getTransform().forEach((value,i)=>expect(value).toBeCloseTo(plain.getTransform()[i],4));
        expect(a.scale(.5)).toBe(a);plain.scale(.5);
        a.getTransform().forEach((value,i)=>expect(value).toBeCloseTo(plain.getTransform()[i],4));
    });
    it('keeps logical dimensions separate when mixing component and matrix scaling', function() {
        const a=new pdg.AnimatedAttributes();
        a.setScale(2);a.scale(3);
        expect(a.getScale().x).toBe(6);expect(a.getScale().y).toBe(6);
        expect(a.getWidth()).toBe(1);expect(a.getHeight()).toBe(1);
        a.setSize(10,20).setScale(2,3);a.scale(3,4);
        expectTransform(a,[60,0,0,240,0,0]);
        a.grow(2);expect(a.getWidth()).toBe(20);expect(a.getHeight()).toBe(40);
        expect(a.getScale().x).toBe(6);expect(a.getScale().y).toBe(12);
        a.changeScaleTo(1,1,1,pdg.linearTween);a.animate(.5);
        expectTransform(a,[70,0,0,260,0,0]);
        a.translation(new pdg.Offset(2,3));
        expect(a.getScale().x).toBeCloseTo(3.5,5);expect(a.hasScheduledAnimations()).toBe(false);
        expect(a.getWidth()).toBe(20);expect(a.getHeight()).toBe(40);
        a.setSize(10,20).setScale(-2,3).setRotation(.4);
        a.translation(new pdg.Offset(1,2));
        expect(a.getRotation()).toBeCloseTo(.4,5);expect(a.getScale().x).toBe(-2);
        a.scale(-3,0).translation(new pdg.Offset(1,2));
        expect(a.getScale().x).toBe(6);expect(a.getScale().y).toBe(0);
        expect(a.getRotation()).toBeCloseTo(.4,5);
        a.setScale(1,2);
        expect(a.getWidth()).toBe(10);expect(a.getHeight()).toBe(20);
        const matrix=a.getTransform();expect(Math.hypot(matrix[3],matrix[4])).toBeCloseTo(40,4);
    });
    it('preserves reference size through affine replacement, matrix tweens, shear and singular matrices', function() {
        const a=new pdg.AnimatedAttributes();a.setSize(10,20);
        a.setTransform([2,0,0,3,0,0,0,0,1]);
        expectTransform(a,[2,0,3,0,0,0]);
        expect(a.getWidth()).toBe(10);expect(a.getHeight()).toBe(20);
        a.setScale(.4,.5);expectTransform(a,[4,0,10,0,0,0]);
        a.setTransform([20,0,0,0,60,0,0,0,1]);
        expect(a.getScale().x).toBe(2);expect(a.getScale().y).toBe(3);
        a.changeTransform([40,0,0,0,100,0,0,0,1],1);a.animate(.5);
        expect(a.getWidth()).toBe(10);expect(a.getHeight()).toBe(20);
        expect(a.getScale().x).toBeCloseTo(3,5);expect(a.getScale().y).toBeCloseTo(4,5);
        a.animate(.5);a.changeSkew(.5,.25,1);a.animate(1);
        expect(a.getWidth()).toBe(10);expect(a.getHeight()).toBe(20);
        a.setSize(0,20).setScale(2,3);a.scale(3,4);
        expect(a.getWidth()).toBe(0);expect(a.getScale().x).toBe(6);
        expect(()=>a.setTransform([1,0,0,0,1,0,0,0,1])).toThrow();
        expect(a.getWidth()).toBe(0);
        a.setSize(10,20);a.setTransform([1,0,0,0,1,0,0,0,1]);
        a.resizeTo(20,40,1,pdg.linearTween).andThen().changeTransform([40,0,0,0,100,0,0,0,1],1);
        a.animate(2);expect(a.getWidth()).toBe(20);expect(a.getScale().x).toBeCloseTo(2,5);
        const zero=new pdg.AnimatedAttributes();
        zero.resizeTo(0,1,.5,pdg.linearTween).andThen().changeTransform([1,0,0,0,1,0,0,0,1],.5);
        expect(()=>zero.animate(.5)).toThrow();expect(zero.hasScheduledAnimations()).toBe(false);
        zero.setSize(1,1).setScale(2);zero.scale(3);expect(zero.getScale().x).toBe(6);
        zero.setSize(0,1).resizeTo(2,1,.5,pdg.linearTween).andThen().changeTransform([1,0,0,0,1,0,0,0,1],.5);
        zero.animate(1);expect(zero.getWidth()).toBe(2);expect(zero.getScale().x).toBeCloseTo(.5,5);
    });
    it('updates the attribute matrix through timed inherited position, size, scale and rotation', function() {
        const a=new pdg.AnimatedAttributes();
        expect(a.moveTo(8,12,2,pdg.linearTween).resizeTo(4,6,2,pdg.linearTween)
            .changeScaleTo(3,5,2,pdg.linearTween)
            .rotateTo(Math.PI,2,pdg.linearTween,pdg.rotationDirection_Clockwise)).toBe(a);
        a.animate(1);
        expectTransform(a,[0,5,-10.5,0,4,6]);
        a.pauseSchedule();a.animate(1);
        expectTransform(a,[0,5,-10.5,0,4,6]);
        a.resumeSchedule();a.animate(1);
        expectTransform(a,[-12,0,0,-30,8,12]);
        // An appearance successor uses the same timing sequence and receiver.
        expect(a.rotateBy(-Math.PI,1,pdg.linearTween).andThen().changeFillOpacity(0,1)).toBe(a);
        a.animate(.5);expectTransform(a,[0,12,-30,0,8,12]);
        expect(a.getFillOpacity()).toBe(1);
        a.animate(1);expectTransform(a,[12,0,0,30,8,12]);
        expect(a.getFillOpacity()).toBeCloseTo(.5,5);
    });
    it('updates the attribute matrix from programmed movement, spin, growth and the pivot', function() {
        const a=new pdg.AnimatedAttributes();
        a.setMovement(4,6).setSpin(Math.PI).setStretching(2,4);a.animate(.5);
        expectTransform(a,[0,2,-3,0,2,3]);
        a.stopMovement().stopSpinning().stopStretching();a.animate(.5);
        expectTransform(a,[0,2,-3,0,2,3]);
        a.setSize(1,1);a.setTransform([1,0,0,0,1,0,0,0,1]);
        a.setCenterOffset(new pdg.Offset(1,2)).setRotation(Math.PI/2);
        expectTransform(a,[0,1,-1,0,3,1]);
        a.setScale(2,3);
        expectTransform(a,[0,2,-3,0,7,0]);
    });
    it('can start from a snapshot of ordinary or animated attributes without copying tracks', function() {
        const ordinary=new pdg.Attributes().fillOpacity(.25).translation(new pdg.Offset(10,20));
        const first=new pdg.AnimatedAttributes(ordinary);
        expect(first.getFillOpacity()).toBeCloseTo(.25,5);expect(first.getLocation().x).toBeCloseTo(10,5);
        first.changeFillOpacity(1,1);
        const copy=new pdg.AnimatedAttributes(first);first.animate(1);copy.animate(1);
        expect(copy.getFillOpacity()).toBeCloseTo(.25,5);
        expect(function(){new pdg.AnimatedAttributes({});}).toThrow();
        expect(function(){new pdg.AnimatedAttributes(ordinary,ordinary);}).toThrow();
    });
    it('reports appearance changes without reporting an unchanged wait as a redraw', function() {
        const a=new pdg.AnimatedAttributes();a.wait(1).changeFillOpacity(0,1);
        expect(a.animate(.25)).toBe(false);expect(a.animate(0)).toBe(false);
        expect(a.animate(1)).toBe(true);
    });
    it('samples appearance and movement in seconds and interrupts individual channels', function() {
        const a=new pdg.AnimatedAttributes();
        a.fillColor(new pdg.Color(1,0,0));
        expect(a.changeFillColor(new pdg.Color(0,0,1),2)).toBe(a);
        a.changeLineThickness(5,2).changeFillOpacity(0,2);
        a.moveTo(10,20,2,pdg.linearTween);
        expect(a.animate(1)).toBe(true);
        expect(a.getFillColor().red).toBeCloseTo(.5,5);
        expect(a.getLineThickness()).toBeCloseTo(3,5);
        expect(a.getTransform()[6]).toBeCloseTo(5,5);
        a.lineThickness(8);a.animate(1);
        expect(a.getLineThickness()).toBe(8);expect(a.getFillColor().blue).toBe(1);
        a.wait(.5).changeTextSize(20,.5);
        a.animate(.25);expect(a.getTextSize()).toBe(12);
        a.animate(.5);expect(a.getTextSize()).toBeCloseTo(16,5);
    });
    it('passes adjusted native Attributes pointers to Drawing and preserves snapshot semantics', function() {
        const a=new pdg.AnimatedAttributes(), d=pdg.createDrawing();
        a.fillColor(new pdg.Color(1,0,0)).ambientLight(new pdg.Color(.1,.2,.3,.4));
        a.setLocation(new pdg.Point(10,20));
        const e=d.addRect(new pdg.Rect(0,0,10,10),a);
        a.changeFillColor(new pdg.Color(0,0,1),1);a.animate(1);
        expect(e.getAttributes().getFillColor().red).toBe(1);
        expect(e.getAttributes().getAmbientLight().alpha).toBeCloseTo(.4,5);
        expect(e.getAttributes().getTransform()[6]).toBeCloseTo(10,5);
        e.setAttributes(a);expect(e.getAttributes().getFillColor().blue).toBe(1);
        expect(function(){d.addRect(new pdg.Rect(10,10),new pdg.Animated());}).toThrow();
        expect(function(){e.setAttributes({});}).toThrow();
        const ordinary=new pdg.Attributes().fillColor(new pdg.Color(0,1,0));
        e.setAttributes(ordinary);expect(e.getAttributes().getFillColor().green).toBe(1);
    });
    it('provides every continuous appearance channel and directed sphere rotation', function() {
        const a=new pdg.AnimatedAttributes();
        a.changeLineColor(new pdg.Color(1,1,1),2).changeLineOpacity(0,2);
        a.changeRoundedCorners(8,2).changeSubsection(new pdg.Rect(2,4,10,20),2);
        a.changePolarOffset(new pdg.Offset(2,4),2).changeLightOffset(new pdg.Offset(6,8),2);
        a.changeAmbientLight(new pdg.Color(1,1,1),2);
        a.sphereRotation(6).changeSphereRotation(.2,2,pdg.linearTween,pdg.rotationDirection_Clockwise);
        a.animate(1);
        expect(a.getLineColor().red).toBeCloseTo(.5,5);expect(a.getLineOpacity()).toBeCloseTo(.5,5);
        expect(a.getRoundedCornerRadius()).toBeCloseTo(4,5);expect(a.getSubsection().bottom).toBeCloseTo(10,5);
        expect(a.getPolarOffset().x).toBeCloseTo(1,5);expect(a.getLightOffset().y).toBeCloseTo(4,5);
        expect(a.getAmbientLight().red).toBeCloseTo(.75,5);expect(a.getSphereRotation()).toBeGreaterThan(6);
    });
    it('switches gradient modes discretely after waits and cancels competing fill tracks', function() {
        const a=new pdg.AnimatedAttributes();
        a.fillColor(new pdg.Color(1,1,1));
        a.wait(.5).changeFillGradient(new pdg.Point(0,0),new pdg.Color(1,0,0),new pdg.Point(10,20),new pdg.Color(0,0,1),1);
        a.animate(.25);expect(a.getGradientType()).toBe(pdg.gradientType_None);
        a.animate(.5);expect(a.getGradientType()).toBe(pdg.gradientType_Linear);expect(a.getGradientEnd().x).toBeCloseTo(2.5,5);
        a.fillColor(new pdg.Color(0,1,0));a.animate(1);
        expect(a.getGradientType()).toBe(pdg.gradientType_None);expect(a.getGradientEnd().x).toBeCloseTo(2.5,5);
        a.changeFillRadialGradient(new pdg.Point(4,8),new pdg.Color(1,1,1),10,new pdg.Color(0,0,0),2);
        a.animate(1);expect(a.getRadialGradientRadius()).toBeCloseTo(5,5);
    });
    it('uses integer frame sequences in either direction and respects immediate frame changes', function() {
        const a=new pdg.AnimatedAttributes();a.frame(8);
        a.wait(.5).changeFrames(2,5,1);a.animate(.25);expect(a.getFrame()).toBe(8);
        a.animate(.5);expect(a.getFrame()).toBe(3);
        a.animate(1);expect(a.getFrame()).toBe(5);
        a.changeFrames(4,1,1);a.animate(.5);expect(a.getFrame()).toBe(2);
        a.frame(7);a.animate(1);expect(a.getFrame()).toBe(7);
    });
    it('shares a transform between Attributes and Animated without cumulative drift', function() {
        const a=new pdg.AnimatedAttributes();
        a.setLocation(new pdg.Point(10,20));expect(a.getLocation().x).toBeCloseTo(10,5);
        a.moveTo(new pdg.Point(20,30),1,pdg.linearTween);a.animate(.5);expect(a.getTransform()[6]).toBeCloseTo(15,5);
        const matrix=a.getTransform();for(let i=0;i<20;++i)a.animate(0);expect(a.getTransform()).toEqual(matrix);
        a.setTransform([1,0,0,0,1,0,0,0,1]);
        a.changeTransform([3,0,0,0,1,0,20,0,1],2);a.animate(1);expect(a.getWidth()).toBe(1);expect(a.getScale().x).toBeCloseTo(2,5);expect(a.getLocation().x).toBeCloseTo(10,5);
        a.setLocation(new pdg.Point(4,5));a.animate(1);expect(a.getLocation().x).toBeCloseTo(4,5);
        a.changeScaleTo(2,3,1);a.animate(1);expect(a.getTransform()[4]).toBeCloseTo(3,5);
        a.rotateTo(1,1,pdg.linearTween,pdg.rotationDirection_Clockwise);a.animate(1);expect(a.getRotation()).toBeCloseTo(1,5);
        a.changeSkew(.2,.3,1);a.animate(1);expect(Number.isFinite(a.getTransform()[0])).toBe(true);
    });
    it('rejects invalid requests without losing the current appearance tween', function() {
        const a=new pdg.AnimatedAttributes();a.changeTextSize(20,1);
        expect(function(){a.changeTextSize(0,-1);}).toThrow();
        expect(function(){a.changeTextSize(Infinity,1);}).toThrow();
        expect(function(){a.changeTextSize(0,1,99999);}).toThrow();
        expect(function(){a.animate(Infinity);}).toThrow();
        expect(function(){a.setTransform([1,0,1,0,1,0,0,0,1]);}).toThrow();
        expect(function(){a.changeFrames(1.5,4,1);}).toThrow();
        expect(function(){a.changeFrames(1,Infinity,1);}).toThrow();
        expect(function(){a.changeTextSize(0,1,1.5);}).toThrow();
        expect(function(){a.rotateTo(1,1,pdg.linearTween,1.5);}).toThrow();
        a.animate(.5);expect(a.getTextSize()).toBeCloseTo(16,5);
    });
    it('shares scale and tween controls across transform, appearance and frames', function() {
        const a=new pdg.AnimatedAttributes();a.setSize(10,20);a.setScale(2,3);
        expect(a.getWidth()).toBe(10);expect(a.getTransform()[0]).toBeCloseTo(20,5);
        expect(a.getTransform()[4]).toBeCloseTo(60,5);
        a.changeFillOpacity(0,1);a.changeFrames(1,4,1);a.animate(.5);a.pauseSchedule();a.animate(1);
        expect(a.getFillOpacity()).toBeCloseTo(.5,5);expect(a.getFrame()).toBe(3);
        a.cancelSchedule();a.frame(8);a.resumeSchedule();a.animate(1);
        expect(a.getFillOpacity()).toBeCloseTo(.5,5);expect(a.getFrame()).toBe(8);
        a.changeScaleTo(.5,2,.5);a.animate(.5);expect(a.getWidth()).toBe(10);
        expect(a.getScale().x).toBeCloseTo(.5,5);expect(a.getTransform()[0]).toBeCloseTo(5,5);
    });

});


describe('AnimatedAttributes explicit timing', function() {
    it('requires seconds on every appearance transition', function() {
        const a=new pdg.AnimatedAttributes(), point=new pdg.Point(0,0), color=new pdg.Color(0,0,0);
        const calls=[['changeLineColor',color],['changeLineThickness',2],['changeLineOpacity',.5],
            ['changeFillColor',color],['changeFillOpacity',.5],['changeRoundedCorners',4],['changeTextSize',16],
            ['changeSubsection',new pdg.Rect(10,10)],['changePolarOffset',new pdg.Offset(1,2)],
            ['changeLightOffset',new pdg.Offset(1,2)],['changeAmbientLight',color],
            ['changeFillGradient',point,color,new pdg.Point(10,0),color],
            ['changeFillRadialGradient',point,color,10,color],['changeSphereRotation',1],
            ['changeFrames',1,4],['changeSkew',.1,.2],['changeTransform',[1,0,0,0,1,0,0,0,1]]];
        calls.forEach(call=>expect(()=>a[call[0]].apply(a,call.slice(1))).toThrow());
        expect(a.hasScheduledAnimations()).toBe(false);
        a.fillOpacity(.5);expect(a.getFillOpacity()).toBeCloseTo(.5,5);
        if(a.delete)a.delete();
    });
});
