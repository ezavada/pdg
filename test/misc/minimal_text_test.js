// Minimal test to isolate text rendering issue
console.log("=== MINIMAL TEXT RENDERING TEST ===");

// Create a window port
var port = pdg.gfx.createWindowPort(new pdg.Rect(100, 100, 800, 600), "Minimal Text Test");

if (!port) {
    console.log("ERROR: Could not create window port");
    pdg.quit();
} else {

console.log("Created port successfully");

// Create a font explicitly
var font = pdg.gfx.createFont("Arial");
console.log("Font created:", font);

// Set the font on the port
if (font) {
    port.setFont(font);
    console.log("Font set on port");
}

// Set up draw handler
var drawHandler = pdg.on(pdg.eventType_PortDraw, function(evt) {
    if (evt.port !== port) {
        return false;
    }
    
    // Clear background with a distinctive color
    var portRect = port.getDrawingArea();
    var backgroundAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.1, 0.1, 0.8, 1.0));
    port.drawRect(portRect, backgroundAttrs); // Dark blue background
    
    // Draw a simple shape first to verify basic rendering works
    var redAttrs = new pdg.Attributes().fillColor("red");
    port.drawRect(new pdg.Rect(50, 50, 150, 100), redAttrs);
    console.log("Drew red rectangle");
    
    // Try drawing text at a very obvious location with high contrast
    try {
        var textAttrs = new pdg.Attributes().textSize(100)).textStyle(32).fillColor(pdg.textStyle_Plain, "white");
        port.drawText("HELLO WORLD", new pdg.Point(200, textAttrs);
        console.log("Called drawText for HELLO WORLD");
        
        var textAttrs = new pdg.Attributes().textSize(150)).textStyle(24).fillColor(pdg.textStyle_Bold, "yellow");
        port.drawText("TEST TEXT", new pdg.Point(200, textAttrs);
        console.log("Called drawText for TEST TEXT");
        
        var textAttrs = new pdg.Attributes().textSize(200)).textStyle(16).fillColor(pdg.textStyle_Plain, "cyan");
        port.drawText("SMALL TEXT", new pdg.Point(200, textAttrs);
        console.log("Called drawText for SMALL TEXT");
        
        // Try with different positioning
        var textAttrs = new pdg.Attributes().textSize(30)).textStyle(20).fillColor(pdg.textStyle_Plain, "green");
        port.drawText("TOP LEFT", new pdg.Point(10, textAttrs);
        console.log("Called drawText for TOP LEFT");
        
        var textAttrs = new pdg.Attributes().textSize(550)).textStyle(18).fillColor(pdg.textStyle_Plain, "magenta");
        port.drawText("BOTTOM RIGHT", new pdg.Point(600, textAttrs);
        console.log("Called drawText for BOTTOM RIGHT");
        
    } catch (e) {
        console.log("ERROR in drawText:", e);
    }
    
    return true;
});

// Set up key handler to quit
var keyHandler = pdg.on(pdg.eventType_KeyPress, function(evt) {
    console.log("Key pressed, quitting...");
    pdg.gfx.closeGraphicsPort(port);
    pdg.quit();
    return true;
});

console.log("Starting test - press any key to quit");
pdg.run();
}
