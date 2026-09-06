// Shared catalog for the interactive UI regression suite.
// Paths are relative to each test's working directory.

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
        id: 'shape-fill',
        name: 'Shape fill test',
        scriptPath: 'ui_tests/shape_fill_test.js',
        workingDir: 'test'
    },
    {
        id: 'image',
        name: 'Image test',
        scriptPath: 'ui_tests/image_test.js',
        workingDir: 'test'
    },
    {
        id: 'animation',
        name: 'Animation test',
        scriptPath: 'ui_tests/animation_test.js',
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
        name: 'MVC sample test',
        scriptPath: 'src/js/mvc-app/sample.js',
        workingDir: 'repo',
        args: ['--ui-test']
    }
];

module.exports = UI_TESTS;

if (typeof require !== 'undefined' && require.main === module) {
    UI_TESTS.forEach(function(testDef) {
        console.log(testDef.id + '\t' + testDef.name);
    });
}
