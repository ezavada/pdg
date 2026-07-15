#!/usr/bin/env node
// Test linear gradient rendering

var pdg = require('pdg');

console.log("Linear Gradient Test");
console.log("===================");

// Create a window port
var screenBounds = pdg.gfx.getScreenBounds(0);
var windowRect = new pdg.Rect(
    screenBounds.left + 100, 
    screenBounds.top + 100, 
    screenBounds.left + 600, 
    screenBounds.top + 400
);
var port = pdg.gfx.createWindowPort(windowRect, "Linear Gradient Test");

pdg.on(pdg.eventType_PortDraw, function(evt) {
    if (evt.port !== port) return false; // Only handle our port
    
    port.drawRect(new pdg.Rect(0, 0, port.getDrawingArea().width(), port.getDrawingArea().height()), 
                  new pdg.Attributes().fillColor(new pdg.Color('black')));
    
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 30);
    var textAttrs = new pdg.Attributes()
        .textSize(24)
        .textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold)
        .fillColor("white");
    port.drawText("Linear Gradient Test", titlePoint, textAttrs);
    
    var startX = 50;
    var startY = 80;
    var rectSize = 100;
    var spacing = 20;
    
    // Test linear gradients
    var colors = [
        [new pdg.Color(1, 0, 0, 1), new pdg.Color(0, 0, 1, 1)],      // red to blue
        [new pdg.Color(0, 1, 0, 1), new pdg.Color(1, 1, 0, 1)],      // green to yellow
        [new pdg.Color(0, 0, 1, 1), new pdg.Color(1, 0, 1, 1)],      // blue to magenta
    ];
    
    for (var i = 0; i < colors.length; i++) {
        var x = startX + i * (rectSize + spacing);
        var y = startY;
        var rect = new pdg.Rect(x, y, x+rectSize, y+rectSize);
        var start = new pdg.Point(x, y);
        var end = new pdg.Point(x + rectSize, y + rectSize);
        
        var gradAttrs = new pdg.Attributes()
            .fillGradient(start, colors[i][0], end, colors[i][1]);
        port.drawRect(rect, gradAttrs);
    }
    
    // Instructions
    var instructAttrs = new pdg.Attributes().textSize(14).fillColor("gray");
    port.drawText("Press ESC or Q to exit", new pdg.Point(startX, port.getDrawingArea().height() - 40), instructAttrs);
    
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
