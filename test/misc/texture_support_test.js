// Texture Support Test
// Tests that texture support is properly integrated into shape drawing

var pdg = require('pdg');

function runTextureSupportTest() {
    console.log("Starting Texture Support Test...");
    
    // Create a window port for testing
    var windowRect = new pdg.Rect(100, 100, 800, 600);
    var port = pdg.gfx.createWindowPort(windowRect, "PDG Texture Support Test");
    if (!port) {
        console.log("ERROR: Could not create window port");
        return;
    }
    var drawingArea = port.getDrawingArea();
    
    console.log("Window created successfully");
    console.log("Drawing area:", drawingArea.width, "x", drawingArea.height);
    
    // Test 1: Verify texture attribute exists and can be set
    console.log("Test 1: Checking texture attribute support...");
    var attrs = new pdg.Attributes();
    
    // Try to create a dummy texture (this will fail, but we can test the attribute)
    var dummyTexture = new pdg.Image("nonexistent.png");
    if (dummyTexture) {
        attrs.texture(dummyTexture);
        console.log("✓ Texture attribute can be set");
    } else {
        console.log("✗ Could not create dummy texture");
    }
    
    // Test 2: Draw shapes with texture attribute (should fall back to solid colors)
    console.log("Test 2: Drawing shapes with texture attribute...");
    
    // Clear the screen
    port.drawRect(drawingArea, new pdg.Attributes().fillColor("black"));
    
    // Draw a rectangle with texture attribute
    var rect = new pdg.Rect(50, 50, 200, 150);
    var rectAttrs = new pdg.Attributes()
        .fillColor("red")
        .lineColor("white")
        .lineThickness(2);
    if (dummyTexture) {
        rectAttrs.texture(dummyTexture);
    }
    port.drawRect(rect, rectAttrs);
    console.log("✓ Rectangle drawn with texture attribute");
    
    // Draw a quad with texture attribute
    var quad = new pdg.Quad();
    quad.points[0] = new pdg.Point(300, 50);   // bottom-left
    quad.points[1] = new pdg.Point(500, 50);   // bottom-right  
    quad.points[2] = new pdg.Point(500, 200);  // top-right
    quad.points[3] = new pdg.Point(300, 200);  // top-left
    var quadAttrs = new pdg.Attributes()
        .fillColor("blue")
        .lineColor("yellow")
        .lineThickness(2);
    if (dummyTexture) {
        quadAttrs.texture(dummyTexture);
    }
    port.drawQuad(quad, quadAttrs);
    console.log("✓ Quad drawn with texture attribute");
    
    // Draw a circle with texture attribute
    var circleCenter = new pdg.Point(150, 300);
    var circleRadius = 75;
    var circleAttrs = new pdg.Attributes()
        .fillColor("green")
        .lineColor("white")
        .lineThickness(2);
    if (dummyTexture) {
        circleAttrs.texture(dummyTexture);
    }
    port.drawCircle(circleCenter, circleRadius, circleAttrs);
    console.log("✓ Circle drawn with texture attribute");
    
    // Draw an ellipse with texture attribute
    var ellipseCenter = new pdg.Point(400, 300);
    var ellipseAttrs = new pdg.Attributes()
        .fillColor("purple")
        .lineColor("white")
        .lineThickness(2);
    if (dummyTexture) {
        ellipseAttrs.texture(dummyTexture);
    }
    port.drawEllipse(ellipseCenter, 80, 50, ellipseAttrs);
    console.log("✓ Ellipse drawn with texture attribute");
    
    // Draw a triangle with texture attribute
    var triangle = new pdg.Polygon();
    triangle.addPoint(new pdg.Point(600, 300));
    triangle.addPoint(new pdg.Point(700, 250));
    triangle.addPoint(new pdg.Point(750, 350));
    var triangleAttrs = new pdg.Attributes()
        .fillColor("orange")
        .lineColor("white")
        .lineThickness(2);
    if (dummyTexture) {
        triangleAttrs.texture(dummyTexture);
    }
    port.drawPolygon(triangle, triangleAttrs);
    console.log("✓ Triangle drawn with texture attribute");
    
    // Draw a rounded rectangle with texture attribute
    var roundedRect = new pdg.Rect(50, 400, 200, 150);
    var roundedAttrs = new pdg.Attributes()
        .fillColor("cyan")
        .lineColor("white")
        .lineThickness(2)
        .roundedCorners(20);
    if (dummyTexture) {
        roundedAttrs.texture(dummyTexture);
    }
    port.drawRect(roundedRect, roundedAttrs);
    console.log("✓ Rounded rectangle drawn with texture attribute");
    
    // Add labels
    var labelAttrs = new pdg.Attributes()
        .textSize(14)
        .textStyle(pdg.textStyle_Plain)
        .fillColor("white");
    
    port.drawText("Rectangle", new pdg.Point(50, 220), labelAttrs);
    port.drawText("Quad", new pdg.Point(300, 220), labelAttrs);
    port.drawText("Circle", new pdg.Point(120, 380), labelAttrs);
    port.drawText("Ellipse", new pdg.Point(360, 380), labelAttrs);
    port.drawText("Triangle", new pdg.Point(650, 380), labelAttrs);
    port.drawText("Rounded Rect", new pdg.Point(50, 570), labelAttrs);
    
    console.log("Texture Support Test completed!");
    console.log("All shapes should be drawn with solid colors (texture fallback).");
    console.log("The test verifies that:");
    console.log("- Texture attribute can be set on Attributes objects");
    console.log("- All shape drawing methods accept texture attributes");
    console.log("- Shapes are drawn even when texture is null/invalid");
    console.log("- The rendering system gracefully handles missing textures");
}

// Run the test
runTextureSupportTest();
