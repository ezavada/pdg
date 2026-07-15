// Texture Shapes Test
// Tests texture support for all filled shape drawing methods

var pdg = require('pdg');

function runTextureShapesTest() {
    console.log("Starting Texture Shapes Test...");
    
    // Create a window port for testing
    var windowRect = new pdg.Rect(100, 100, 800, 600);
    var port = pdg.gfx.createWindowPort(windowRect, "PDG Texture Shapes Test");
    if (!port) {
        console.log("ERROR: Could not create window port");
        return;
    }
    var drawingArea = port.getDrawingArea();
    
    // Load a test texture (using yinyang.png which should be available)
    var texture = new pdg.Image("../yinyang.png");
    if (!texture) {
        console.log("ERROR: Could not load test texture 'tiles.png'");
        return;
    }
    
    console.log("Loaded texture:", texture.width, "x", texture.height);
    
    // Clear the screen
    port.drawRect(drawingArea, new pdg.Attributes().fillColor("black"));
    
    // Test 1: Textured Rectangle
    console.log("Test 1: Textured Rectangle");
    var rect = new pdg.Rect(50, 50, 200, 150);
    var rectAttrs = new pdg.Attributes()
        .fillColor("red")  // Fallback color if texture fails
        .texture(texture)
        .lineColor("white")
        .lineThickness(2);
    port.drawRect(rect, rectAttrs);
    
    // Test 2: Textured Quad
    console.log("Test 2: Textured Quad");
    var quad = new pdg.Quad();
    quad.points[0] = new pdg.Point(300, 50);   // bottom-left
    quad.points[1] = new pdg.Point(500, 50);   // bottom-right  
    quad.points[2] = new pdg.Point(500, 200);  // top-right
    quad.points[3] = new pdg.Point(300, 200);  // top-left
    var quadAttrs = new pdg.Attributes()
        .fillColor("blue")
        .texture(texture)
        .lineColor("yellow")
        .lineThickness(2);
    port.drawQuad(quad, quadAttrs);
    
    // Test 3: Textured Circle
    console.log("Test 3: Textured Circle");
    var circleCenter = new pdg.Point(150, 300);
    var circleRadius = 75;
    var circleAttrs = new pdg.Attributes()
        .fillColor("green")
        .texture(texture)
        .lineColor("white")
        .lineThickness(2);
    port.drawCircle(circleCenter, circleRadius, circleAttrs);
    
    // Test 4: Textured Ellipse
    console.log("Test 4: Textured Ellipse");
    var ellipseCenter = new pdg.Point(400, 300);
    var ellipseAttrs = new pdg.Attributes()
        .fillColor("purple")
        .texture(texture)
        .lineColor("white")
        .lineThickness(2);
    port.drawEllipse(ellipseCenter, 80, 50, ellipseAttrs);
    
    // Test 5: Textured Polygon (Triangle)
    console.log("Test 5: Textured Triangle");
    var triangle = new pdg.Polygon();
    triangle.addPoint(new pdg.Point(600, 300));
    triangle.addPoint(new pdg.Point(700, 250));
    triangle.addPoint(new pdg.Point(750, 350));
    var triangleAttrs = new pdg.Attributes()
        .fillColor("orange")
        .texture(texture)
        .lineColor("white")
        .lineThickness(2);
    port.drawPolygon(triangle, triangleAttrs);
    
    // Test 6: Textured Rounded Rectangle
    console.log("Test 6: Textured Rounded Rectangle");
    var roundedRect = new pdg.Rect(50, 400, 200, 150);
    var roundedAttrs = new pdg.Attributes()
        .fillColor("cyan")
        .texture(texture)
        .lineColor("white")
        .lineThickness(2)
        .roundedCorners(20);
    port.drawRect(roundedRect, roundedAttrs);
    
    // Test 7: Textured Complex Polygon (Star)
    console.log("Test 7: Textured Star");
    var star = new pdg.Polygon();
    var starCenter = new pdg.Point(400, 475);
    var outerRadius = 60;
    var innerRadius = 30;
    for (var i = 0; i < 10; i++) {
        var angle = (i * Math.PI) / 5;
        var radius = (i % 2 == 0) ? outerRadius : innerRadius;
        var x = starCenter.x + radius * Math.cos(angle - Math.PI/2);
        var y = starCenter.y + radius * Math.sin(angle - Math.PI/2);
        star.addPoint(new pdg.Point(x, y));
    }
    var starAttrs = new pdg.Attributes()
        .fillColor("magenta")
        .texture(texture)
        .lineColor("white")
        .lineThickness(2);
    port.drawPolygon(star, starAttrs);
    
    // Test 8: Texture with Opacity
    console.log("Test 8: Semi-transparent Textured Rectangle");
    var semiTransparentRect = new pdg.Rect(300, 400, 200, 150);
    var semiTransparentAttrs = new pdg.Attributes()
        .fillColor("red")
        .fillOpacity(0.5)
        .texture(texture)
        .lineColor("white")
        .lineThickness(2);
    port.drawRect(semiTransparentRect, semiTransparentAttrs);
    
    // Add labels for each test
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
    port.drawText("Star", new pdg.Point(360, 570), labelAttrs);
    port.drawText("Semi-transparent", new pdg.Point(300, 570), labelAttrs);
    
    console.log("Texture Shapes Test completed!");
    console.log("All shapes should display with the tile texture pattern.");
    console.log("Check that:");
    console.log("- Rectangle and Quad show texture mapping");
    console.log("- Circle and Ellipse show radial texture mapping");
    console.log("- Triangle and Star show texture mapped to polygon bounds");
    console.log("- Rounded rectangle shows texture on the rounded shape");
    console.log("- Semi-transparent rectangle shows texture with reduced opacity");
}

// Run the test
runTextureShapesTest();
