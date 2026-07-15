#!/usr/bin/env pdg
// Test to demonstrate that scale and skew now work around the object's center
// instead of the origin (0,0)

var pdg = require('pdg');

var gPort = null;
var gFrameCount = 0;

function setup() {
    console.log("=== SCALE & SKEW CENTER TEST ===");
    console.log("This test demonstrates that scale and skew transformations");
    console.log("now correctly transform around the object's center point.");
    console.log("Press ESC to quit\n");
    
    // Create a window
    var gm = pdg.getGraphicsManager();
    gPort = gm.createWindowPort({
        title: "Scale & Skew Center Test",
        width: 800,
        height: 600
    });
    
    // Register event handlers
    pdg.onKeyDown(handleKeyDown);
    pdg.onUpdate(update);
    
    // Start the main loop
    pdg.run();
}

function handleKeyDown(evt) {
    if (evt.keyCode === pdg.key_Escape) {
        console.log("Exiting...");
        pdg.quit();
    }
}

function update(evt) {
    gFrameCount++;
    var time = gFrameCount / 60.0; // Assuming 60 FPS
    
    // Clear screen
    gPort.fillRect(new pdg.Rect(0, 0, 800, 600), 
                   new pdg.Attributes().fillColor(new pdg.Color(0.1, 0.1, 0.1)));
    
    // Draw title
    var titleAttrs = new pdg.Attributes()
        .fillColor(new pdg.Color(1, 1, 1))
        .textSize(20);
    gPort.drawText("Scale & Skew now transform around object center", 
                   new pdg.Point(400, 30), titleAttrs);
    
    // Test 1: Scale without center (OLD behavior - would scale from origin)
    var rect1Center = new pdg.Point(200, 200);
    var rect1 = new pdg.Rect(150, 150, 250, 250);
    
    var scale1 = 0.5 + 0.5 * Math.sin(time * 2);
    var attrs1 = new pdg.Attributes()
        .fillColor(new pdg.Color(0.8, 0.2, 0.2, 0.5))
        .lineColor(new pdg.Color(1, 0, 0))
        .lineThickness(2)
        .scale(scale1, scale1, rect1Center); // Now scales around center!
    
    gPort.drawRect(rect1, attrs1);
    
    // Draw center point marker
    var centerMarker1 = new pdg.Attributes()
        .fillColor(new pdg.Color(1, 1, 0));
    gPort.drawCircle(rect1Center, 5, centerMarker1);
    
    // Draw label
    var labelAttrs = new pdg.Attributes()
        .fillColor(new pdg.Color(1, 1, 1))
        .textSize(14);
    gPort.drawText("Scale around center", new pdg.Point(200, 280), labelAttrs);
    gPort.drawText("scale = " + scale1.toFixed(2), new pdg.Point(200, 300), labelAttrs);
    
    // Test 2: Skew (shear transformation - slants the shape)
    var rect2Center = new pdg.Point(500, 200);
    var rect2 = new pdg.Rect(450, 150, 550, 250);
    
    // Skew is a shear - it shifts parallel lines, creating a "leaning" effect
    // When applied relative to center, the shape leans but stays in place
    var skewX = Math.sin(time) * 0.5;  // Lean left/right
    var skewY = 0;  // No vertical skew for clarity
    var attrs2 = new pdg.Attributes()
        .fillColor(new pdg.Color(0.2, 0.8, 0.2, 0.5))
        .lineColor(new pdg.Color(0, 1, 0))
        .lineThickness(2)
        .skew(skewX, skewY, rect2Center); // Skew relative to center keeps shape in place
    
    gPort.drawRect(rect2, attrs2);
    
    // Draw center point marker
    var centerMarker2 = new pdg.Attributes()
        .fillColor(new pdg.Color(1, 1, 0));
    gPort.drawCircle(rect2Center, 5, centerMarker2);
    
    // Draw label
    gPort.drawText("Skew (shear) relative to center", new pdg.Point(500, 280), labelAttrs);
    gPort.drawText("Makes the shape lean - skewX = " + skewX.toFixed(2), 
                   new pdg.Point(500, 300), labelAttrs);
    
    // Test 3: Combined scale and rotation around center
    var rect3Center = new pdg.Point(350, 450);
    var rect3 = new pdg.Rect(300, 400, 400, 500);
    
    var scale3 = 0.7 + 0.3 * Math.sin(time);
    var rotation3 = time;
    var attrs3 = new pdg.Attributes()
        .fillColor(new pdg.Color(0.2, 0.2, 0.8, 0.5))
        .lineColor(new pdg.Color(0, 0, 1))
        .lineThickness(2)
        .scale(scale3, scale3, rect3Center)    // Scale around center
        .rotation(rotation3, rect3Center);      // Rotate around center
    
    gPort.drawRect(rect3, attrs3);
    
    // Draw center point marker
    var centerMarker3 = new pdg.Attributes()
        .fillColor(new pdg.Color(1, 1, 0));
    gPort.drawCircle(rect3Center, 5, centerMarker3);
    
    // Draw label
    gPort.drawText("Scale + Rotation around center", new pdg.Point(350, 530), labelAttrs);
    gPort.drawText("All transforms use same center point", new pdg.Point(350, 550), labelAttrs);
    
    // Instructions
    var instructionAttrs = new pdg.Attributes()
        .fillColor(new pdg.Color(0.7, 0.7, 0.7))
        .textSize(12);
    gPort.drawText("Yellow dots mark the center point for each transformation", 
                   new pdg.Point(400, 580), instructionAttrs);
}

// Start the application
setup();

