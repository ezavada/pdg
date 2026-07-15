#!/usr/bin/env node
// Test radial gradient rendering

var pdg = require('pdg');

console.log("Radial Gradient Test");
console.log("===================");
console.log("This test draws various shapes with radial gradients");
console.log("You should see:");
console.log("1. A row of rectangles with radial gradients");
console.log("2. A row of circles with radial gradients");
console.log("3. A row of polygons (hexagons) with radial gradients");

// Create a window port
var screenBounds = pdg.gfx.getScreenBounds(0);
var windowRect = new pdg.Rect(
    screenBounds.left + 100, 
    screenBounds.top + 100, 
    screenBounds.left + 900, 
    screenBounds.top + 700
);
var port = pdg.gfx.createWindowPort(windowRect, "Radial Gradient Test");

pdg.on(pdg.eventType_PortDraw, function(evt) {
    if (evt.port !== port) return false; // Only handle our port
    
    port.drawRect(new pdg.Rect(0, 0, port.getDrawingArea().width(), port.getDrawingArea().height()), 
                  new pdg.Attributes().fillColor(new pdg.Color('black')));
    
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 30);
    var textAttrs = new pdg.Attributes()
        .textSize(24)
        .textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold)
        .fillColor("white");
    port.drawText("Radial Gradient Test", titlePoint, textAttrs);
    
    var startX = 50;
    var startY = 80;
    var rectSize = 100;
    var spacing = 20;
    
    // Test 1: Rectangles with radial gradients
    var labelAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Plain).fillColor("white");
    port.drawText("Rectangles with Radial Gradients", new pdg.Point(startX, startY), labelAttrs);
    startY += 30;
    
    var colors = [
        [new pdg.Color(1, 0, 0, 1), new pdg.Color(0, 0, 1, 1)],      // red to blue
        [new pdg.Color(0, 1, 0, 1), new pdg.Color(1, 1, 0, 1)],      // green to yellow
        [new pdg.Color(0, 0, 1, 1), new pdg.Color(1, 0, 1, 1)],      // blue to magenta
        [new pdg.Color(1, 1, 0, 1), new pdg.Color(0, 1, 1, 1)],      // yellow to cyan
        [new pdg.Color(1, 1, 1, 1), new pdg.Color(0, 0, 0, 1)],      // white to black
    ];
    
    for (var i = 0; i < colors.length; i++) {
        var x = startX + i * (rectSize + spacing);
        var y = startY;
        var rect = new pdg.Rect(x, y, x+rectSize, y+rectSize);
        var center = new pdg.Point(x + rectSize/2, y + rectSize/2);
        var radius = rectSize / 2; // Use half the rectangle size as radius
        
        var gradAttrs = new pdg.Attributes()
            .fillRadialGradient(center, colors[i][0], radius, colors[i][1]);
        port.drawRect(rect, gradAttrs);
    }
    
    // Test 2: Circles with radial gradients
    startY += rectSize + 40;
    port.drawText("Circles with Radial Gradients", new pdg.Point(startX, startY), labelAttrs);
    startY += 30;
    
    for (var i = 0; i < colors.length; i++) {
        var centerX = startX + rectSize/2 + i * (rectSize + spacing);
        var centerY = startY + rectSize/2;
        var center = new pdg.Point(centerX, centerY);
        var radius = rectSize / 2; // Use half the rectangle size as radius
        
        var gradAttrs = new pdg.Attributes()
            .fillRadialGradient(center, colors[i][0], radius * 0.8, colors[i][1]);
        port.drawCircle(center, radius, gradAttrs);
    }
    
    // Test 3: Polygons (hexagons) with radial gradients
    startY += rectSize + 40;
    port.drawText("Hexagons with Radial Gradients", new pdg.Point(startX, startY), labelAttrs);
    startY += 30;
    
    for (var i = 0; i < colors.length; i++) {
        var centerX = startX + rectSize/2 + i * (rectSize + spacing);
        var centerY = startY + rectSize/2;
        var center = new pdg.Point(centerX, centerY);
        var radius = rectSize / 2; // Use half the rectangle size as radius
        
        // Create hexagon
        var hexagon = new pdg.Polygon();
        for (var j = 0; j < 6; j++) {
            var angle = (Math.PI / 3) * j;
            var px = centerX + radius * Math.cos(angle);
            var py = centerY + radius * Math.sin(angle);
            hexagon.addPoint(new pdg.Point(px, py));
        }
        
        var gradAttrs = new pdg.Attributes()
            .fillRadialGradient(center, colors[i][0], radius * 0.6, colors[i][1]);
        port.drawPolygon(hexagon, gradAttrs);
    }
    
    // Instructions
    startY = port.getDrawingArea().height() - 40;
    var instructAttrs = new pdg.Attributes().textSize(14).fillColor("gray");
    port.drawText("Press ESC or Q to exit", new pdg.Point(startX, startY), instructAttrs);
    
    return true; // Event handled
});

pdg.on(pdg.eventType_KeyDown, function(evt) {
    if (evt.keyCode == pdg.key_Escape || evt.keyChar == 'q' || evt.keyChar == 'Q') {
        pdg.gfx.closeGraphicsPort(port);
        pdg.tm.quit();
        return true;
    }
    return false;
});

// Keep the app running
pdg.run();

