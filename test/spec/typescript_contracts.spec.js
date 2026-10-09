// Validate enriched declaration records against values from the real binding.
describe('TypeScript IDL contracts', function() {
    const api = pdg.getInterfaceMetadata();
    const schemas = api.schemas;
    function check(value, contract, label) {
        if (contract.nullable && value === null) return;
        if (contract.schema) {
            const schema = schemas[contract.schema];
            (schema.extends || []).forEach(base => check(value,{schema:base},label));
            Object.keys(schema.fields || {}).forEach(key => {
                const field = schema.fields[key];
                if (field.optional && value[key] === undefined) return;
                check(value[key],field,label+'.'+key);
            });
        } else if (contract.items) {
            expect(Array.isArray(value)).toBe(true);
            value.forEach((item,index) => check(item,contract.items,label+'['+index+']'));
        } else if (contract.type && contract.type.indexOf('object ') === 0) {
            const expected = contract.type.slice(7);
            function derives(name) {
                if (name === expected) return true;
                const klass = api.interface.find(item => item.name === name && item.type === 'class');
                return !!klass && (klass.implements || []).some(derives);
            }
            // Native wrapper prototypes need not mirror their C++ bases.
            expect(api.interface.some(item => item.type === 'class' &&
                typeof pdg[item.name] === 'function' && value instanceof pdg[item.name] && derives(item.name))).toBe(true);
        } else if (contract.type) {
            if (typeof value !== contract.type) throw new Error(label+' expected '+contract.type+', got '+typeof value);
            expect(typeof value).toBe(contract.type);
        }
    }
    it('captures the active runtime and build capabilities',function() {
        expect(api.runtime_profile.capabilities.graphics).toBe(pdg.hasGraphics);
        expect(api.runtime_profile.capabilities.sound).toBe(pdg.hasSound);
        expect(api.runtime_profile.capabilities.network).toBe(pdg.hasNetwork);
    });
    it('exposes public constructors and preserves geometry copies',function() {
        expect(new pdg.Animated() instanceof pdg.Animated).toBe(true);
        if (pdg.hasGraphics) {
            expect(new pdg.Attributes() instanceof pdg.Attributes).toBe(true);
            expect(new pdg.AnimatedAttributes() instanceof pdg.AnimatedAttributes).toBe(true);
        }
        const original = new pdg.Rect(1,2,3,4), copy = new pdg.Rect(original);
        expect(copy.equals(original)).toBe(true);
        expect(copy === original).toBe(false);
        ['Part','Collider','AnimationScript'].forEach(name => {
            expect(pdg.getInterfaceMetadata(name).construction.kind).toBe('factory');
        });
    });
    it('publishes pose, transform and physics records with their declared fields',function() {
        const layer = pdg.createSpriteLayer();
        try {
            layer.setUseChipmunkPhysics(false);
            const sprite = layer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');
            sprite.pauseAnimation();
            expect(sprite.enableAnimationPose('reference')).toBe(true);
            check(sprite.getAnimationPose(),{schema:'AnimationPose'},'pose');
            check(sprite.getAnimationBoneTransform('hand',pdg.animationSpace_Rig),{schema:'AnimationTransform'},'transform');
            const part = sprite.createPart('contract-part');
            check(part.getTransform(),{schema:'AffineTransform'},'part');
            const body = part.setupPhysicsBody(1,1);
            check(body.getState(),{schema:'PhysicsBodyState'},'body');
            check(body.getDriveState(),{schema:'PhysicsDriveState'},'drive');
        } finally { pdg.cleanupLayer(layer); }
    });
    it('delivers timer helper payloads matching the event schema',function() {
        let event;
        const subscription = pdg.tm.onTimeout(value => { event = value; },1);
        waitsFor(function() { return !!event; },'timer callback',2000);
        runs(function() {
            check(event,{schema:'TimerEvent'},'timer');
            expect(subscription.timer).toBe(event.id);
            subscription.cancel();
        });
    });
});
