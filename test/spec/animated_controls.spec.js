require('./SpecHelper');
describe('Animated scale, growth and tween controls', function() {
    it('separates scale and logical size, and integrates eased growth rates', function() {
        const a=new pdg.Animated();a.setSize(10,20);expect(a.setScale(.5,2)).toBe(a);
        expect(a.getWidth()).toBe(10);expect(a.getBoundingBox().width()).toBe(5);
        a.changeScaleTo(-1,0,.5,pdg.linearTween);a.animate(.25);expect(a.getScale().x).toBeCloseTo(-.25,5);
        a.setScale(3);a.animate(1);expect(a.getScale().y).toBe(3);
        expect(a.changeStretchingTo(8,-4,.5,pdg.linearTween)).toBe(a);a.animate(.25);
        expect(a.getStretching().x).toBeCloseTo(4,5);expect(a.getWidth()).toBeCloseTo(10.5,5);
        a.animate(.5);expect(a.getWidth()).toBeCloseTo(14,5);
        a.changeGrowingTo(100,1);a.setWidth(20);a.animate(.25);expect(a.getWidth()).toBeCloseTo(24.875,5);
        a.resizeTo(30,40,.5,pdg.linearTween);a.animate(.5);expect(a.getHeight()).toBe(40);
        expect(a.getStretching().y).toBe(0);a.changeGrowingTo(100,1);a.stopGrowing();a.animate(1);
        expect(a.getWidth()).toBe(30);expect(()=>a.setScale(NaN)).toThrow();
        expect(()=>a.changeScaleTo(1,1,1,99999)).toThrow();expect(()=>a.changeGrowingTo(1,-1)).toThrow();
    });
    it('controls tween clocks independently from programmed motion', function() {
        const a=new pdg.Animated();expect(a.hasScheduledAnimations()).toBe(false);
        a.wait(.5).changeScaleTo(3,5,1,pdg.linearTween);a.animate(.25);expect(a.pauseSchedule()).toBe(a);
        a.animate(2);expect(a.getScale().x).toBe(1);expect(a.hasScheduledAnimations()).toBe(true);
        a.resumeSchedule();a.animate(.75);expect(a.getScale().x).toBeCloseTo(2,5);
        a.pauseSchedule();a.cancelSchedule();expect(a.hasScheduledAnimations()).toBe(false);expect(a.isSchedulePaused()).toBe(true);
        a.resumeSchedule();a.changeMovementTo(8,0,1,pdg.linearTween);a.animate(.5);a.pauseSchedule();
        const x=a.getLocation().x;a.animate(1);expect(a.getLocation().x).toBeCloseTo(x+4,5);
        expect(a.getMovement().x).toBeCloseTo(4,5);a.resumeSchedule();a.animate(.5);
        expect(a.getMovement().x).toBeCloseTo(8,5);a.wait(10);a.cancelSchedule();a.changeScaleTo(4,4,0);
        expect(a.getScale().x).toBe(4);
    });

    it('round-trips Camera tween updates and paused clock state', function() {
        const layer=pdg.createSpriteLayer(); const camera=new pdg.Camera(); layer.setCamera(camera);
        try {
            // Camera animation state travels with the layer drawing state.
            layer.setSerializationFlags(pdg.ser_Update | pdg.ser_LayerDraw);
            camera.setScale(1,2);camera.changeScaleTo(3,4,1,pdg.linearTween);camera.changeMovementTo(8,0,1,pdg.linearTween);
            camera.pauseSchedule();camera.wait(.125);
            const ser=new pdg.Serializer(), size=layer.getSerializedSize(ser);layer.serialize(ser);
            expect(ser.getDataPtr().getDataSize()).toBe(size+3);
            camera.cancelSchedule();camera.setScale(9);camera.resumeSchedule();
            const des=new pdg.Deserializer();des.setDataPtr(ser.getDataPtr());layer.deserialize(des);
            expect(layer.getCamera().isSchedulePaused()).toBe(true);expect(layer.getCamera().hasScheduledAnimations()).toBe(true);
            expect(layer.getCamera().getScale().x).toBeCloseTo(1,5);expect(layer.getCamera().getScale().y).toBeCloseTo(2,5);
            expect(layer.getCamera().getMovement().x).toBeCloseTo(0,5);
            layer.getCamera().resumeSchedule();expect(layer.getCamera().isSchedulePaused()).toBe(false);expect(layer.getCamera().hasScheduledAnimations()).toBe(true);
        } finally { pdg.cleanupLayer(layer); }
    });

});
