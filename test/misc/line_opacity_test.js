// Test for lineOpacity and lineColor alpha interaction
// This test verifies that lineOpacity multiplies with lineColor alpha correctly

console.log("=== Line Opacity Test ===");
console.log("Testing lineOpacity and lineColor alpha interaction for polygons, circles, and ellipses");

var port = pdg.gfx.createWindowPort(new pdg.Rect(800, 600), "Line Opacity Test");
if (!port) {
    console.log("ERROR: Could not create window port");
    process.exit(1);
}

var drawingArea = port.getDrawingArea();
console.log("Drawing area: " + drawingArea.width() + "x" + drawingArea.height());

// Set up drawing handler
var drawHandler = pdg.on(pdg.eventType_PortDraw, function(evt) {
    if (evt.port !== port) return false;
    
    // Clear background
    var bgAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.1, 0.1, 0.1, 1.0));
    port.drawRect(drawingArea, bgAttrs);
    
    // Title
    var titleAttrs = new pdg.Attributes()
        .textSize(20)
        .textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold)
        .fillColor("white");
    port.drawText("Line Opacity & Line Color Alpha Test", 
        new pdg.Point(drawingArea.width()/2, 30), titleAttrs);
    
    var startY = 80;
    var spacing = 80;
    var shapeX = 100;
    
    // Test 1: lineColor with full alpha, varying lineOpacity
    var labelAttrs = new pdg.Attributes().textSize(14).fillColor("white");
    port.drawText("Test 1: lineColor alpha=1.0, varying lineOpacity", 
        new pdg.Point(20, startY), labelAttrs);
    
    var opacities = [1.0, 0.75, 0.5, 0.25, 0.0];
    for (var i = 0; i < opacities.length; i++) {
        var x = shapeX + i * 100;
        
        // Pentagon
        var pentagon = new pdg.Polygon();
        var centerX = x;
        var centerY = startY + 40;
        var radius = 30;
        for (var j = 0; j < 5; j++) {
            var angle = (j * 2 * Math.PI) / 5 - Math.PI / 2;
            var px = centerX + Math.cos(angle) * radius;
            var py = centerY + Math.sin(angle) * radius;
            pentagon.addPoint(new pdg.Point(px, py));
        }
        
        var attrs = new pdg.Attributes()
            .lineColor(new pdg.Color(1, 0, 0, 1.0))  // Red with alpha=1.0
            .lineOpacity(opacities[i])
            .lineThickness(2.0);
        port.drawPolygon(pentagon, attrs);
        
        // Label
        var labelText = "opacity=" + opacities[i].toFixed(2);
        port.drawText(labelText, new pdg.Point(x, startY + 75), labelAttrs.textSize(10));
    }
    
    // Test 2: lineColor with varying alpha, lineOpacity=1.0
    startY += spacing + 40;
    port.drawText("Test 2: varying lineColor alpha, lineOpacity=1.0", 
        new pdg.Point(20, startY), labelAttrs);
    
    var alphas = [1.0, 0.75, 0.5, 0.25, 0.0];
    for (var i = 0; i < alphas.length; i++) {
        var x = shapeX + i * 100;
        
        // Circle
        var attrs = new pdg.Attributes()
            .lineColor(new pdg.Color(0, 1, 0, alphas[i]))  // Green with varying alpha
            .lineOpacity(1.0)
            .lineThickness(2.0);
        port.drawCircle(new pdg.Point(x, startY + 40), 30, attrs);
        
        // Label
        var labelText = "alpha=" + alphas[i].toFixed(2);
        port.drawText(labelText, new pdg.Point(x, startY + 75), labelAttrs.textSize(10));
    }
    
    // Test 3: Both lineColor alpha and lineOpacity multiplied
    startY += spacing + 40;
    port.drawText("Test 3: Both lineColor alpha=0.5 and lineOpacity=0.5 (should be 0.25)", 
        new pdg.Point(20, startY), labelAttrs);
    
    // Ellipse with both
    var attrs1 = new pdg.Attributes()
        .lineColor(new pdg.Color(0, 0, 1, 0.5))  // Blue with alpha=0.5
        .lineOpacity(0.5)  // opacity=0.5
        .lineThickness(2.0);
    port.drawEllipse(new pdg.Point(shapeX, startY + 40), 50, 30, attrs1);
    port.drawText("alpha=0.5 * opacity=0.5 = 0.25", 
        new pdg.Point(shapeX, startY + 75), labelAttrs.textSize(10));
    
    // Reference: alpha=0.25 with opacity=1.0 (should look the same)
    var attrs2 = new pdg.Attributes()
        .lineColor(new pdg.Color(0, 0, 1, 0.25))  // Blue with alpha=0.25
        .lineOpacity(1.0)
        .lineThickness(2.0);
    port.drawEllipse(new pdg.Point(shapeX + 100, startY + 40), 50, 30, attrs2);
    port.drawText("alpha=0.25 * opacity=1.0 = 0.25", 
        new pdg.Point(shapeX + 100, startY + 75), labelAttrs.textSize(10));
    
    // Test 4: Edge case - alpha=0, should not draw
    startY += spacing + 40;
    port.drawText("Test 4: lineColor alpha=0 should not draw (left empty, right visible)", 
        new pdg.Point(20, startY), labelAttrs);
    
    // Should NOT draw (alpha=0)
    var attrs3 = new pdg.Attributes()
        .lineColor(new pdg.Color(1, 1, 0, 0.0))  // Yellow with alpha=0
        .lineOpacity(1.0)
        .lineThickness(2.0);
    port.drawPolygon(pentagon, attrs3);
    port.drawText("alpha=0 (invisible)", 
        new pdg.Point(shapeX, startY + 75), labelAttrs.textSize(10));
    
    // Should draw (alpha=1)
    var square = new pdg.Polygon(
        new pdg.Point(shapeX + 100 - 30, startY + 40 - 30),
        new pdg.Point(shapeX + 100 + 30, startY + 40 - 30),
        new pdg.Point(shapeX + 100 + 30, startY + 40 + 30),
        new pdg.Point(shapeX + 100 - 30, startY + 40 + 30)
    );
    var attrs4 = new pdg.Attributes()
        .lineColor(new pdg.Color(1, 1, 0, 1.0))  // Yellow with alpha=1
        .lineOpacity(1.0)
        .lineThickness(2.0);
    port.drawPolygon(square, attrs4);
    port.drawText("alpha=1 (visible)", 
        new pdg.Point(shapeX + 100, startY + 75), labelAttrs.textSize(10));
    
    // Instructions
    var instructionAttrs = new pdg.Attributes()
        .textSize(16)
        .textStyle(pdg.textStyle_Centered)
        .fillColor("yellow");
    port.drawText("Press ESC to quit", 
        new pdg.Point(drawingArea.width()/2, drawingArea.height() - 30), instructionAttrs);
    
    return true;
});

// Key handler
var keyHandler = pdg.on(pdg.eventType_KeyPress, function(evt) {
    if (evt.unicode == pdg.key_Escape) {
        console.log("ESC pressed - quitting...");
        pdg.gfx.closeGraphicsPort(port);
        pdg.quit();
    }
    return true;
});

console.log("Test running. Press ESC to quit.");
pdg.run();

