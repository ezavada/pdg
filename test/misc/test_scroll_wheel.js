// Simple test script for scroll wheel events
// Run with: ./pdg test/misc/test_scroll_wheel.js

var pdg = require('pdg');

console.log('Scroll Wheel Event Test');
console.log('========================');
console.log('Creating window...\n');

// Create a simple window
var windowRect = new pdg.Rect(0, 0, 640, 480);
var port = pdg.gfx.createWindowPort(windowRect, "Scroll Wheel Test - Move mouse here and scroll!");

console.log('Window created. Scroll your mouse wheel over the window.');
console.log('Events will be logged below. Press ESC to exit.\n');

// Listen for scroll wheel events
pdg.on(pdg.eventType_ScrollWheel, function(evt) {
    console.log('ScrollWheel Event:', {
        horizDelta: evt.horizDelta,
        vertDelta: evt.vertDelta,
        shift: evt.shift,
        ctrl: evt.ctrl,
        alt: evt.alt,
        meta: evt.meta
    });
    return true; // Event handlers must return boolean
});

// Handle ESC key to exit
pdg.on(pdg.eventType_KeyPress, function(evt) {
    if (evt.unicode == pdg.key_Escape) {
        console.log('\nESC pressed - exiting...');
        pdg.quit();
    }
    return true;
});

console.log('Ready! Waiting for scroll events...');

// Keep the app running
pdg.run();
