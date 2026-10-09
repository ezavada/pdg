// Shared visual catalog. The legacy smoke runners still consume every entry.
// Paths are relative to each test's working directory and to the root of the
// iOS test application bundle.

var UI_TESTS = [
    {
        id: 'port',
        name: 'Port test',
        scriptPath: 'ui_tests/port_test.js',
        workingDir: 'test'
    },
    {
        id: 'font',
        name: 'Font test',
        scriptPath: 'ui_tests/font_test.js',
        workingDir: 'test'
    },
    {
        id: 'drawing',
        name: 'Drawing test',
        scriptPath: 'ui_tests/drawing_test.js',
        workingDir: 'test'
    },
    {
        id: 'astra',
        name: 'Astra animated drawing',
        scriptPath: 'test/js/anime-character-demo.js',
        workingDir: 'repo',
        args: ['--ui-test']
    },
    {
        id: 'shape-fill',
        name: 'Shape fill test',
        scriptPath: 'ui_tests/shape_fill_test.js',
        workingDir: 'test'
    },
    {
        id: 'compositing',
        name: 'Stroke opacity and blend modes',
        scriptPath: 'ui_tests/compositing_test.js',
        workingDir: 'test'
    },
    {
        id: 'image',
        name: 'Image test',
        scriptPath: 'ui_tests/image_test.js',
        workingDir: 'test'
    },
    {
        id: 'offscreen',
        name: 'Offscreen ports',
        scriptPath: 'ui_tests/offscreen_test.js',
        workingDir: 'test'
    },
    {
        id: 'animation',
        name: 'Animation test',
        scriptPath: 'ui_tests/animation_test.js',
        workingDir: 'test'
    },
    {
        id: 'camera',
        name: 'Live camera transitions',
        // One handoff per transition/match option; wipe right and whip left only.
        smokeTimeoutMs: 240000,
        scriptPath: 'ui_tests/camera_test.js',
        workingDir: 'test'
    },
    {
        id: 'particles',
        name: 'Particle effects',
        scriptPath: 'ui_tests/particle_test.js',
        workingDir: 'test'
    },
    {
        id: 'animation-physics',
        name: 'Human animation rig',
        // Recovery advances on simulation time; software rendering can be slow.
        smokeTimeoutMs: 300000,
        scriptPath: 'ui_tests/animation_physics_test.js',
        workingDir: 'test'
    },
    {
        id: 'wheel-chains',
        name: 'Wheel and chains physics rig',
        scriptPath: 'ui_tests/wheel_chains_test.js',
        workingDir: 'test'
    },
    {
        id: 'spriter-sound',
        name: 'Spriter and sound test',
        scriptPath: 'ui_tests/spriter_sound_test.js',
        workingDir: 'test'
    },
    {
        id: 'mvc',
        name: 'MVC control gallery',
        scriptPath: 'test/js/app-control-gallery.js',
        workingDir: 'repo',
        args: ['--ui-test']
    }
];

var pageNames = {
    bones: ['controls'],
    port: ['ports'],
    font: ['comparison', 'styles', 'sizes', 'metrics', 'alignment', 'scaling'],
    drawing: ['lines', 'arcs', 'splines', 'rectangles', 'circles', 'ellipses', 'polygons', 'spheres'],
    'shape-fill': ['rect', 'quad', 'circle', 'ellipse', 'roundrect', 'pentagon', 'star', 'pentagram', 'complex', 'spiral', 'hourglass', 'selfintersect', 'transforms'],
    compositing: ['stroke-opacity', 'blend-modes'],
    image: ['images', 'scaling', 'animation', 'transparency', 'textures'],
    offscreen: ['live-and-snapshot'],
    animation: ['animation'],
    scene: ['pause-resume-hud'],
    camera: ['crossfade', 'wipe-left', 'wipe-right', 'wipe-up', 'wipe-down', 'luma-fade', 'whip-left', 'whip-right', 'whip-up', 'whip-down', 'cut', 'match-cut', 'match-cut-return', 'match-fade', 'match-fade-return'],
    'spriter-sound': ['spriter-sound']
};
UI_TESTS.push({id: 'spriter', name: 'Grey Guy and Wonky Skeleton',
    scriptPath: 'js/main.js', workingDir: 'test', args: ['--ui-test']});
UI_TESTS.push({id:'scene',name:'Scene pause/resume with animated HUD',scriptPath:'ui_tests/scene_test.js',workingDir:'test'});
UI_TESTS.push({id:'bones',smokeTimeoutMs:45000,name:'Animated bone controls',scriptPath:'ui_tests/bone_test.js',workingDir:'test'});
UI_TESTS.push({id:'bone-controls',smokeTimeoutMs:45000,name:'Interactive bone controls',scriptPath:'js/bone-controls-demo.js',workingDir:'test',args:['--ui-test']});
UI_TESTS.push({id: 'layer-serialization', name: 'Live layer serialization',
    scriptPath: 'test/js/layer-serialization-demo.js', workingDir: 'repo', args: ['--ui-test']});
UI_TESTS.push({id:'jiggle',name:'Spring tide: chain and IK target jiggle',scriptPath:'js/jiggle-demo.js',workingDir:'test',args:['--ui-test']});
UI_TESTS.push({id:'fabrik',smokeTimeoutMs:180000,name:'Abyssal reach: long-chain FABRIK',scriptPath:'js/fabrik-demo.js',workingDir:'test',args:['--ui-test']});
UI_TESTS.forEach(function(entry) {
    entry.kind = pageNames[entry.id] ? 'ui' : 'demo';
    entry.pages = pageNames[entry.id] || [entry.id];
});
if (typeof module !== 'undefined') module.exports = UI_TESTS;
else window.PDG_VISUAL_CATALOG = UI_TESTS;

if (typeof require !== 'undefined' && require.main === module) {
    UI_TESTS.forEach(function(testDef) {
        console.log(testDef.id + '\t' + testDef.name);
    });
}
