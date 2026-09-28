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
    port: ['ports'],
    font: ['comparison', 'styles', 'sizes', 'metrics', 'alignment', 'scaling'],
    drawing: ['lines', 'arcs', 'splines', 'rectangles', 'circles', 'ellipses', 'polygons', 'spheres'],
    'shape-fill': ['rect', 'quad', 'circle', 'ellipse', 'roundrect', 'pentagon', 'star', 'pentagram', 'complex', 'spiral', 'hourglass', 'selfintersect', 'transforms'],
    compositing: ['stroke-opacity', 'blend-modes'],
    image: ['images', 'scaling', 'animation', 'transparency', 'textures'],
    offscreen: ['live-and-snapshot'],
    animation: ['animation'],
    'spriter-sound': ['spriter-sound']
};
UI_TESTS.push({id: 'spriter', name: 'Grey Guy and Wonky Skeleton',
    scriptPath: 'js/main.js', workingDir: 'test', args: ['--ui-test']});
UI_TESTS.push({id: 'layer-serialization', name: 'Live layer serialization',
    scriptPath: 'test/js/layer-serialization-demo.js', workingDir: 'repo', args: ['--ui-test']});
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
