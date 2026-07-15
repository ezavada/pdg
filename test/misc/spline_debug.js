// Debug script to test spline drawing
console.log("=== SPLINE DEBUG TEST ===");

// Create a simple test
var numScreens = pdg.gfx.getNumScreens();
console.log("Number of screens:", numScreens);

var ports = [];
for (var i = 0; i < numScreens; i++) {
    var port = pdg.gfx.createWindowPort(new pdg.Rect(100, 100, 900, 700), "Spline Debug Test - Screen " + i);
    ports.push(port);
    console.log("Created port for screen", i);
}

var drawHandler = pdg.on(pdg.eventType_PortDraw, function(evt) {
    console.log("DRAW HANDLER CALLED!");
    var port = evt.port;
    var bounds = port.getDrawingArea();
    console.log("Drawing to port, bounds:", bounds);
    
    // Clear the background
    var backgroundAttrs = new pdg.Attributes().fillColor("black");
    port.drawRect(bounds, backgroundAttrs);
    
    // Test basic drawing first
    var textAttrs = new pdg.Attributes().textSize(50)).textStyle(20).fillColor(pdg.textStyle_Centered, "white");
        port.drawText("Spline Debug Test", new pdg.Point(bounds.width()/2, textAttrs);
    
    // Test a simple line first
    port.drawLine(new pdg.Point(100, 100), new pdg.Point(200, 200), "white");
    console.log("Drew test line from (100,100) to (200,200)");
    
    // Test spline creation
    try {
        console.log("Creating spline...");
        var spline = new pdg.Spline(pdg.spline_Hermite);
        console.log("Spline created successfully");
        
        console.log("Initializing spline...");
        spline.initialize(
            new pdg.Point(100, 150),
            new pdg.Point(200, 100),
            new pdg.Point(300, 200),
            new pdg.Point(400, 150)
        );
        console.log("Spline initialized successfully");
        
        // Test getFirstOrder
        var point1 = spline.getFirstOrder(0.0);
        var point2 = spline.getFirstOrder(0.5);
        var point3 = spline.getFirstOrder(1.0);
        console.log("Spline points - start:", point1, "middle:", point2, "end:", point3);
        
        // Draw the spline
        console.log("Drawing spline...");
        port.drawSpline(spline, 50, "red");
        console.log("Spline draw call completed");
        
        // Also try drawing individual line segments manually to test
        console.log("Testing manual line drawing...");
        for (var i = 0; i <= 10; i++) {
            var u = i / 10.0;
            var point = spline.getFirstOrder(u);
            console.log("Spline point at u=" + u + ":", point);
            if (i > 0) {
                var prevU = (i-1) / 10.0;
                var prevPoint = spline.getFirstOrder(prevU);
                port.drawLine(prevPoint, point, "cyan");
                console.log("Drew line from", prevPoint, "to", point);
            }
        }
        
        // Draw control points
        var cpAttrs = new pdg.Attributes().fillColor("yellow");
        port.drawEllipse(new pdg.Point(100, 150), 5, 5, cpAttrs);
        port.drawEllipse(new pdg.Point(200, 100), 5, 5, cpAttrs);
        port.drawEllipse(new pdg.Point(300, 200), 5, 5, cpAttrs);
        port.drawEllipse(new pdg.Point(400, 150), 5, 5, cpAttrs);
        console.log("Drew control points");
        
    } catch (e) {
        console.log("Error with spline:", e);
    }
    
    return true;
});

// Set up key handler to quit
var keyHandler = pdg.on(pdg.eventType_KeyPress, function(evt) {
    console.log("Key pressed, quitting...");
    ports.forEach(function(port) {
        pdg.gfx.closeGraphicsPort(port);
    });
    pdg.quit();
    return true;
});

console.log("Debug test setup complete. Press any key to quit.");

// Start the main event loop
pdg.run();
