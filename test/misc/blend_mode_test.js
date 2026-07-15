#!/usr/bin/env pdg

// Simple test to verify blend modes are working with fills
// Run with: ./pdg test/misc/blend_mode_test.js

// Create window port
const windowRect = new pdg.Rect(0, 0, 800, 600);
const screenBounds = pdg.gfx.getScreenBounds(0);
windowRect.center(screenBounds);

const port = pdg.gfx.createWindowPort(windowRect, "Blend Mode Test");

if (!port) {
    console.log("ERROR: Could not create window port");
    process.exit(1);
}

const BACKGROUND_COLOR = new pdg.Color(0.2, 0.2, 0.2, 1.0);  // Dark gray
const BASE_COLOR = new pdg.Color(0.0, 0.5, 1.0, 1.0);        // Blue
const OVERLAY_COLOR = new pdg.Color(1.0, 0.5, 0.0, 1.0);     // Orange

console.log("Blend Mode Test");
console.log("==============");
console.log("This test draws blue base rectangles with orange overlapping rectangles");
console.log("using different blend modes. You should see different visual results for each.");
console.log("");
console.log("Expected results:");
console.log("1. Normal:      Orange overlaps blue (standard alpha blending)");
console.log("2. Additive:    Bright yellow-white where shapes overlap (colors add)");
console.log("3. Multiply:    Dark reddish-brown overlap (colors multiply, darkens)");
console.log("4. Screen:      Light yellow-cyan overlap (inverted multiply, lightens)");
console.log("5. Darken:      Keeps darker color components");
console.log("6. Lighten:     Similar to Additive but different alpha handling");
console.log("");

let testComplete = false;

// Draw function
function draw() {
    // Draw background
    var bgRect = new pdg.Rect(0, 0, 800, 600);
    var bgAttrs = new pdg.Attributes().fillColor(BACKGROUND_COLOR);
    port.drawRect(bgRect, bgAttrs);
    
    const startX = 50;
    const startY = 50;
    const rectWidth = 100;
    const rectHeight = 80;
    const spacing = 130;
    const overlapOffset = 50;
    
    const blendModes = [
        { mode: pdg.blendMode_Normal, label: "Normal" },
        { mode: pdg.blendMode_Additive, label: "Additive" },
        { mode: pdg.blendMode_Multiply, label: "Multiply" },
        { mode: pdg.blendMode_Screen, label: "Screen" },
        { mode: pdg.blendMode_Darken, label: "Darken" },
        { mode: pdg.blendMode_Lighten, label: "Lighten" }
    ];
    
    for (let i = 0; i < blendModes.length; i++) {
        const x = startX + (i % 3) * spacing;
        const y = startY + Math.floor(i / 3) * 250;
        
        // Draw label
        const labelAttrs = new pdg.Attributes()
            .fillColor(new pdg.Color(1, 1, 1, 1))
            .textSize(14);
        port.drawText(blendModes[i].label, new pdg.Point(x, y - 20), labelAttrs);
        
        // Draw base blue rectangle (using Normal blend mode)
        const baseAttrs = new pdg.Attributes()
            .fillColor(BASE_COLOR)
            .blendMode(pdg.blendMode_Normal);
        const baseRect = new pdg.Rect(x, y, x + rectWidth, y + rectHeight);
        port.drawRect(baseRect, baseAttrs);
        
        // Draw overlapping orange rectangle with test blend mode
        const overlayAttrs = new pdg.Attributes()
            .fillColor(OVERLAY_COLOR)
            .blendMode(blendModes[i].mode);
        const overlayRect = new pdg.Rect(
            x + overlapOffset, 
            y + overlapOffset/2, 
            x + overlapOffset + rectWidth, 
            y + overlapOffset/2 + rectHeight
        );
        port.drawRect(overlayRect, overlayAttrs);
    }
    
    // Add instructions
    const instrAttrs = new pdg.Attributes()
        .fillColor(new pdg.Color(1, 1, 1, 1))
        .textSize(16);
    port.drawText("Press any key to exit", new pdg.Point(300, 550), instrAttrs);
    
    testComplete = true;
}

// Set up event handling
pdg.on(pdg.eventType_PortDraw, function(evt) {
    if (evt.port !== port) return false;
    draw();
    return true;
});

pdg.on(pdg.eventType_KeyPress, function(evt) {
    console.log("Key pressed - exiting...");
    pdg.gfx.closeGraphicsPort(port);
    pdg.quit();
    return true;
});

// Start the event loop
console.log("Starting test... (press any key to exit)");
pdg.run();

if (testComplete) {
    console.log("\nTest completed successfully!");
} else {
    console.log("\nTest did not complete properly!");
}

