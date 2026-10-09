describe('Structured interface introspection', function() {
    it('reports defaults and contracts without constructing an engine object', function() {
        var find = pdg.getInterfaceMetadata('FileManager', 'findNext');
        expect(find.returns).toBe('boolean');
        expect(find.params[0].name).toBe('ioFindData');
        expect(pdg.getInterfaceMetadata('Rect', 'assign').returns_contract.type).toBe('this');
        expect(pdg.getInterfaceMetadata('Rect', 'plus').returns_contract.ownership).toBe('owned');
        expect(pdg.getInterfaceMetadata('Animated', 'when').params[0].contract.schema).toBe('AnimationEvaluator');
        expect(pdg.getInterfaceMetadata('AnimationSpringTarget', 'setState').params[0].contract.schema).toBe('AnimationSpringState');
        expect(pdg.getInterfaceMetadata('AnimationSpringTarget', 'getState').returns_contract.ownership).toBe('owned');
    });
    it('returns independent metadata and describes inherited methods', function() {
        var first = pdg.getInterfaceMetadata('Animated', 'moveTo');
        first.params[0][0].name = 'changed';
        expect(pdg.getInterfaceMetadata('Animated', 'moveTo').params[0][0].name).not.toBe('changed');
        expect(pdg.describeInterface('Animated', 'moveTo')).toContain('durationSeconds = 0');
        expect(pdg.getInterfaceMetadata().metadata_version).toBe(1);
    });
    if (typeof pdg.Polygon === 'function') {
        it('describes both Polygon overloads on every backend', function() {
            var move = pdg.getInterfaceMetadata('Polygon', 'moveTo');
            expect(move.params.length).toBe(2);
            expect(move.native_binding.overloads[1].binding_name).toBe('_moveToXY');
            expect(pdg.describeInterface('Polygon', 'moveTo')).toContain('object Point point');
            expect(pdg.describeInterface('Polygon', 'moveTo')).toContain('number x, number y');
        });
    }
    if (typeof pdg.Sprite === 'function') {
        it('resolves drawing classes and named record/callback schemas in overloads', function() {
            var variants = pdg.getInterfaceMetadata('Sprite', 'addAnimationDrawable').params;
            expect(variants[0][0].type).toBe('object Drawing');
            expect(variants[0][0].contract).toBeUndefined();
            expect(variants[1][0].type).toBe('function');
            expect(variants[1][0].contract.schema).toBe('AnimationDrawableCallback');
            variants.forEach(function(params) {
                expect(['object', 'object AnimationDrawableOptions'].indexOf(params[1].type)).not.toBe(-1);
                expect(params[1].contract.schema).toBe('AnimationDrawableOptions');
            });
        });
        it('declares callback setters through signatures while allowing null to clear them', function() {
            var collider = new pdg.Sprite().setupCollider();
            ['setContactHandler', 'setCollisionFilter'].forEach(function(name) {
                var metadata = pdg.getInterfaceMetadata('Collider', name);
                expect(metadata.returns).toBe('this');
                expect(metadata.params[0].type).toBe('function');
                expect(collider[name](function() { return true; })).toBe(collider);
                expect(collider[name](null)).toBe(collider);
            });
        });
    }
    it('uses JavaScript member hints without treating null as introspection', function() {
        var color = new pdg.Color(), rect = new pdg.Rect();
        expect(pdg.getInterfaceMetadata('Color', 'assign').returns).toBe('this');
        expect(pdg.getInterfaceMetadata('Rect', 'assign').returns).toBe('this');
        expect(function() { color.assign(null); }).toThrow();
        expect(function() { rect.assign(null); }).toThrow();
        expect(typeof console.dump).toBe('function');
    });
    it('rejects unknown interfaces and invalid selectors', function() {
        expect(function() { pdg.getInterfaceMetadata('Unknown'); }).toThrow();
        expect(function() { pdg.getInterfaceMetadata('Animated', 'Unknown'); }).toThrow();
        expect(function() { pdg.getInterfaceMetadata(null); }).toThrow();
    });
});

// File iteration also exercises the native mutable search-object contract.
if (typeof process !== 'undefined' && !process.ios && typeof document === 'undefined') {
    describe('Native interface metadata', function() {
        it('reports boolean results for file iteration', function() {
            expect(pdg.getInterfaceMetadata('FileManager', 'findNext').returns).toBe('boolean');
            expect(function() { pdg.getFileManager().findNext(null); }).toThrow();
        });
        it('updates the original search object and returns a boolean', function() {
            var manager = pdg.getFileManager(), data = manager.findFirst('spec/*.js');
            expect(data.found).toBe(true);
            var first = data.nodeName;
            try {
                expect(manager.findNext(data)).toBe(true);
                expect(data.found).toBe(true);
                expect(data.nodeName).not.toBe(first);
                expect(typeof data.isDirectory).toBe('boolean');
                while (manager.findNext(data)) { expect(data.found).toBe(true); }
                expect(data.found).toBe(false);
            } finally { manager.findClose(data); }
        });
        it('includes the resource size limit and boolean debug flag', function() {
            expect(pdg.describeInterface('ResourceManager', 'getResource')).toContain('number int maxSize = -1');
            expect(pdg.getInterfaceMetadata('pdg', 'setSerializationDebugMode').params[0].type).toBe('boolean');
        });
        if (typeof pdg.Sound === 'function') {
            it('uses receiver metadata for chainable Sound methods', function() {
                ['setLooping','setPitch','setOffsetX','skip','skipTo'].forEach(function(name) {
                    expect(pdg.getInterfaceMetadata('Sound', name).returns.indexOf('this')).toBe(0);
                });
            });
        }
        if (typeof pdg.Sprite === 'function') {
            it('identifies the transferred Part as an object', function() {
                expect(pdg.describeInterface('Sprite', 'transferPart')).toContain('object Part part');
            });
        }
        if (typeof pdg.Attributes === 'function') {
            it('reports the actual receiver returned by appearance operations', function() {
                [pdg.Attributes, pdg.AnimatedAttributes].forEach(function(Type) {
                    var value = new Type();
                    ['lineColor','lineThickness','lineOpacity','lineStyle','fillColor','fillOpacity',
                        'fillGradient','fillRadialGradient','roundedCorners','translation','rotation',
                        'scale','skew','transform','blendMode','textSize','textStyle','frame','fitType',
                        'subsection','sphereRotation','polarOffset','lightOffset','ambientLight','texture']
                        .forEach(function(name) {
                            expect(pdg.getInterfaceMetadata(Type === pdg.Attributes ? 'Attributes' : 'AnimatedAttributes', name).returns.indexOf('this')).toBe(0);
                        });
                    expect(value.lineThickness(3)).toBe(value);
                    expect(value.getLineThickness()).toBe(3);
                    if (value.font) expect(pdg.describeInterface('Attributes', 'font')).toContain('font = null');
                });
            });
        }
        if (typeof pdg.Polygon === 'function') {
            it('reports receiver chaining for Polygon operations', function() {
                var polygon = new pdg.Polygon({x:1,y:2});
                ['move','moveRight','moveUp','moveDown'].forEach(function(name) {
                    expect(pdg.getInterfaceMetadata('Polygon', name).returns.indexOf('this')).toBe(0);
                });
                expect(polygon.moveRight(2)).toBe(polygon);
                expect(pdg.describeInterface('Polygon', 'addSpline')).toContain('number uStep = 0.01');
            });
            it('reports optional Image bounds and a void rasterization operation', function() {
                expect(pdg.describeInterface('Image', 'getImageBounds')).toContain('at = Point(0,0)');
                expect(pdg.getInterfaceMetadata('Image', 'prepareToRasterize').returns).toBeUndefined();
            });
        }
        if (typeof pdg.SpriteLayer === 'function') {
            it('reports chaining for layer fades and both repetition forms', function() {
                var layer = pdg.createSpriteLayer();
                try {
                    expect(pdg.getInterfaceMetadata('SpriteLayer', 'fadeIn').returns).toBe('this');
                    expect(pdg.getInterfaceMetadata('SpriteLayer', 'fadeOut').returns).toBe('this');
                    expect(layer.fadeIn(0)).toBe(layer);
                    expect(pdg.describeInterface('Animated', 'repeat')).toContain('number int additionalExecutions');
                } finally { pdg.cleanupLayer(layer); }
            });
            it('reports tile map offsets and the current-world-size defaults', function() {
                var layer = pdg.createTileLayer();
                try {
                    expect(pdg.describeInterface('TileLayer', 'loadMapData')).toContain('dstX = 0, number int dstY = 0');
                    expect(pdg.describeInterface('TileLayer', 'getMapData')).toContain('mapWidth = worldWidth');
                    expect(pdg.describeInterface('TileLayer', 'getMapData')).toContain('mapHeight = worldHeight');
                    expect(pdg.describeInterface('TileLayer', 'getMapData')).toContain('srcX = 0, number int srcY = 0');
                } finally { pdg.cleanupLayer(layer); }
            });
        }
    });
}
