// Renderer API Test Script
// This script tests the Renderer API with Attributes and chainable methods

console.log("=== Renderer API TEST SCRIPT ===");
console.log("Testing Renderer/Attributes API...");

// Check for --wait parameter
var waitForUser = false;
for (var i = 0; i < process.argv.length; i++) {
    if (process.argv[i] === '--wait') {
        waitForUser = true;
        break;
    }
}

if (waitForUser) {
    console.log("Manual mode: Press SPACE to advance to next test, ESC to quit");
} else {
    console.log("Auto mode: Tests will advance automatically, press any key to advance early, ESC to quit");
}

// Check how many screens are available
var numScreens = pdg.gfx.getNumScreens();
console.log("Number of screens detected:", numScreens);

// Store created ports for cleanup
var ports = [];
var currentTest = 0;
var frameCount = 0;

// Test configuration
var testDuration = 4000; // 4 seconds per test
var frameDelay = 100; // 100ms between frames for animation tests
var testTimeout = null;

var rocksTexture = new pdg.Image("data/rocks.png");
var yinYangTexture = new pdg.Image("data/test_image.png");
var earthTexture = new pdg.Image("./earthmap2.png");
var jupiterTexture = new pdg.Image("./jupitermap2.jpg");
var moonTexture = new pdg.Image("./moonmap2.jpg");
if (!rocksTexture || !yinYangTexture || !earthTexture || !jupiterTexture || !moonTexture) {
    console.log("ERROR: Could not load test textures");
    process.exit(1);
}

// Function to create ports on all screens simultaneously
function createAllPorts() {
    console.log("Creating ports on all screens simultaneously...");
    
    for (var screenNum = 0; screenNum < numScreens; screenNum++) {
        console.log("Creating port for screen", screenNum);
        
        // Get current screen mode info
        var screenMode = pdg.gfx.getCurrentScreenMode(screenNum);
        console.log("Screen", screenNum, "mode:", screenMode);
        
        // Get screen bounds (position and size)
        var screenBounds = pdg.gfx.getScreenBounds(screenNum);
        console.log("Screen", screenNum, "bounds:", screenBounds);
        
        // Calculate window position to center on this screen
        var windowWidth = 1000;
        var windowHeight = 800;
        var windowRect = new pdg.Rect(windowWidth, windowHeight);
        
        windowRect.center(screenBounds);
        console.log("Creating window on screen", screenNum, "at position:", windowRect);
        
        // Create window port on this screen
        var port = pdg.gfx.createWindowPort(windowRect, "Renderer API Test - Screen " + screenNum);
        
        if (!port) {
            console.log("ERROR: Could not create window port for screen", screenNum);
            continue;
        }
        
        var drawingArea = port.getDrawingArea();
        console.log("Window port drawing area: " + drawingArea.width() + "x" + drawingArea.height());
        
        // Store the port with its screen number
        ports.push({
            port: port,
            screenNum: screenNum,
            frameCount: 0
        });
    }
    
    console.log("Created", ports.length, "ports");
}

// Set up drawing through the PortDraw event for all ports
function setupDrawHandler() {
    var drawHandler = pdg.on(pdg.eventType_PortDraw, function(evt) {
        // Find which port this event is for
        var portInfo = null;
        for (var i = 0; i < ports.length; i++) {
            if (ports[i].port === evt.port) {
                portInfo = ports[i];
                break;
            }
        }
        
        if (!portInfo) {
            return false; // Not one of our ports, let other handlers process
        }
        
        portInfo.frameCount++;
        frameCount++;
        
        var port = portInfo.port;
        var screenNum = portInfo.screenNum;
        
        // Clear the background
        var portRect = port.getDrawingArea();
        var backgroundAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.1, 0.1, 0.2, 1.0));
        port.drawRect(portRect, backgroundAttrs); // Dark blue background
        
        // Calculate scaling factors for high DPI displays
        var actualWidth = portRect.width();
        var actualHeight = portRect.height();

        // Draw test title
        var titlePoint = new pdg.Point(actualWidth/2, 34);
        var titleAttrs = new pdg.Attributes().textSize(24).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("white");
        port.drawText("Renderer API Test - Screen " + screenNum, titlePoint, titleAttrs);
        
        // Draw frame counter
        var frameText = "Frame: " + portInfo.frameCount + " (Global: " + frameCount + ")";
        var framePoint = new pdg.Point(10, 20);
        var frameTextAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Plain).fillColor("yellow");
        port.drawText(frameText, framePoint, frameTextAttrs);
        
        // Draw current test info
        var testText = "Test: " + (currentTest + 1) + "/8";
        var testPoint = new pdg.Point(actualWidth/2, 80);
        var testAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Centered).fillColor("aqua");
        port.drawText(testText, testPoint, testAttrs);
        
        // Draw instructions based on mode
        var instructionText = waitForUser ? "Press SPACE to continue, ESC to quit" : "Press any key to advance early, ESC to quit";
        var instructionPoint = new pdg.Point(actualWidth/2, actualHeight - 30);
        var instructionAttrs = new pdg.Attributes().textSize(14).textStyle(pdg.textStyle_Centered).fillColor("yellow");
        port.drawText(instructionText, instructionPoint, instructionAttrs);
        
        // Run the appropriate test based on currentTest
        switch (currentTest) {
            case 0:
                runLineDrawingTest(port);
                break;
            case 1:
                runArcDrawingTest(port);
                break;
            case 2:
                runSplineDrawingTest(port);
                break;
            case 3:
                runRectangleDrawingTest(port);
                break;
            case 4:
                runCircleDrawingTest(port);
                break;
            case 5:
                runEllipseDrawingTest(port);
                break;
            case 6:
                runPolygonDrawingTest(port);
                break;
            case 7:
                runSphereDrawingTest(port);
                break;
        }
        
        return true; // We handled this event
    });
    
    return drawHandler;
}

function setupKeyHandler() {
    var keyHandler = pdg.on(pdg.eventType_KeyPress, function(evt) {
        if (evt.unicode == pdg.key_Escape) {
            console.log("ESC pressed - closing all ports and quitting...");
            ports.forEach(function(portInfo) {
                pdg.gfx.closeGraphicsPort(portInfo.port);
            });
            if (testTimeout) {
                clearTimeout(testTimeout);
                testTimeout = null;
            }
            pdg.quit();
        } else if (waitForUser) {
            // In wait mode, only advance on space key - space is ASCII 32
            if (evt.unicode == 32) { // Space key
                if (testTimeout) {
                    clearTimeout(testTimeout);
                    testTimeout = null;
                }
                currentTest++;
                runNextTest();
            }
        } else {
            // In auto mode, any key advances early
            if (testTimeout) {
                clearTimeout(testTimeout);
                testTimeout = null;
            }
            currentTest++;
            runNextTest();
        }
        return true; // We handled this event
    });
    return keyHandler;
}


// Test 1: Line drawing with Renderer API
function runLineDrawingTest(port) {
    var testTitle = "Renderer API Line Drawing Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var centerX = port.getDrawingArea().width() / 2;
    var centerY = port.getDrawingArea().height() / 2;
    var radius = 120;
    
    // Draw lines in a star pattern
    var colors = ["red", "green", "blue", "yellow", "cyan", "magenta"];
    var numLines = 12;
    
    for (var i = 0; i < numLines; i++) {
        var angle1 = (i / numLines) * 2 * Math.PI;
        var angle2 = ((i + numLines/2) / numLines) * 2 * Math.PI;
        
        var x1 = centerX + Math.cos(angle1) * radius;
        var y1 = centerY + Math.sin(angle1) * radius;
        var x2 = centerX + Math.cos(angle2) * radius;
        var y2 = centerY + Math.sin(angle2) * radius;
        
        var from = new pdg.Point(x1, y1);
        var to = new pdg.Point(x2, y2);
        
        // Use Renderer API with Attributes
        const thickness = i + 1;
        var lineAttrs = new pdg.Attributes()
            .lineColor(colors[i % colors.length])
            .lineThickness(thickness);
        port.drawLine(from, to, lineAttrs);
    }
    
    // Draw some horizontal and vertical lines
    var left = 50;
    var right = port.getDrawingArea().width() - 50;
    var top = 200;
    var bottom = port.getDrawingArea().height() - 100;
    
    var whiteLineAttrs = new pdg.Attributes().lineColor("white").lineThickness(2.0);
    port.drawLine(new pdg.Point(left, top), new pdg.Point(right, top), whiteLineAttrs);
    port.drawLine(new pdg.Point(left, bottom), new pdg.Point(right, bottom), whiteLineAttrs);
    port.drawLine(new pdg.Point(left, top), new pdg.Point(left, bottom), whiteLineAttrs);
    port.drawLine(new pdg.Point(right, top), new pdg.Point(right, bottom), whiteLineAttrs);
    
    // Draw labels
    var textAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Centered).fillColor("white");
    port.drawText("Star pattern and border lines", new pdg.Point(centerX, bottom + 30), textAttrs);
}

// Test 2: Arc drawing with Renderer API
function runArcDrawingTest(port) {
    var testTitle = "Renderer API Arc Drawing Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var colors = ["red", "green", "blue", "yellow", "cyan", "magenta"];
    var startX = 100;
    var startY = 150;
    var spacing = 120;
    var radius = 40;
    
    // 5x5 grid of arcs with different properties
    for (var row = 0; row < 5; row++) {
        for (var col = 0; col < 5; col++) {
            var x = startX + col * spacing;
            var y = startY + row * spacing;
            var center = new pdg.Point(x, y);
            
            var colorIndex = (row + col) % colors.length;
            var attrs = new pdg.Attributes().lineColor(colors[colorIndex]).lineThickness(2.0);
            
            if (row === 0) {
                // Row 0: Quarter circles in different orientations
                var angle = col * Math.PI / 2; // 0, 90, 180, 270, 360
                port.drawArc(center, radius, radius, angle, angle + Math.PI/2, attrs);
            } else if (row === 1) {
                // Row 1: Semi-circles in different orientations
                var angle = col * Math.PI / 4; // 0, 45, 90, 135, 180
                port.drawArc(center, radius, radius, angle, angle + Math.PI, attrs);
            } else if (row === 2) {
                // Row 2: Three-quarter circles
                var angle = col * Math.PI / 4;
                port.drawArc(center, radius, radius, angle, angle + Math.PI * 1.5, attrs);
            } else if (row === 3) {
                // Row 3: Varying radii, same angle
                var arcRadius = 20 + col * 8;
                port.drawArc(center, arcRadius, arcRadius, 0, Math.PI * 1.5, attrs);
            } else {
                // Row 4: Elliptical arcs
                var xRadius = 30 + col * 5;
                var yRadius = 50 - col * 5;
                port.drawArc(center, xRadius, Math.max(15, yRadius), 0, Math.PI * 1.5, attrs);
            }
        }
    }
    
    // Draw labels for each row
    var labelAttrs = new pdg.Attributes().textSize(14).textStyle(pdg.textStyle_Plain).fillColor("white");
    port.drawText("Quarter", new pdg.Point(startX - 90, startY), labelAttrs);
    port.drawText("Semi", new pdg.Point(startX - 90, startY + spacing), labelAttrs);
    port.drawText("3/4", new pdg.Point(startX - 90, startY + spacing * 2), labelAttrs);
    port.drawText("Radii", new pdg.Point(startX - 90, startY + spacing * 3), labelAttrs);
    port.drawText("Elliptical", new pdg.Point(startX - 90, startY + spacing * 4), labelAttrs);
    
    // Add description
    var descAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Centered).fillColor("lightgray");
    port.drawText("5x5 grid: columns vary rotation, rows vary arc types", 
                  new pdg.Point(port.getDrawingArea().width()/2, startY + spacing * 5), descAttrs);
}

// Test 3: Spline drawing with Renderer API
function runSplineDrawingTest(port) {
    var testTitle = "Renderer API Spline Drawing Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var centerX = port.getDrawingArea().width() / 2;
    var centerY = port.getDrawingArea().height() / 2;
    
    // Multi-segment splines in lower half
    const labelAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Centered).fillColor("white");
    port.drawText("Single-Segment Splines", new pdg.Point(50, 150), labelAttrs.textStyle(pdg.textStyle_LeftJustified));

    // Create different types of splines
    var colors = ["red", "green", "blue", "yellow", "cyan", "magenta"];

    var p1 = new pdg.Point(50, 350);
    var p2 = new pdg.Point(150, 200);
    var p3 = new pdg.Point(500, 400);
    var p4 = new pdg.Point(650, 350);
    
    // Hermite spline
    var hermiteSpline = new pdg.Spline(pdg.spline_Hermite);
    hermiteSpline.addSegment(p1,p2,p3,p4);
    var hermiteAttrs = new pdg.Attributes().lineColor("red").lineThickness(1.0);
    port.drawSpline(hermiteSpline, hermiteAttrs);
    port.drawText("  Hermite Spline", new pdg.Point(p2.x, p2.y - 20), labelAttrs.fillColor("red"));

    // TCB spline
    var tcbSpline = new pdg.Spline(pdg.spline_TCB);
    tcbSpline.addSegment(p1,p2,p3,p4);
    var tcbAttrs = new pdg.Attributes().lineColor("magenta").lineThickness(1.0);
    port.drawSpline(tcbSpline, tcbAttrs);
    port.drawText("  TCB Spline", p2, labelAttrs.fillColor("magenta"));
        
    // Natural Cubic spline
    var naturalCubicSpline = new pdg.Spline(pdg.spline_NaturalCubic);
    naturalCubicSpline.addSegment(p1,p2,p3,p4);
    var naturalAttrs = new pdg.Attributes().lineColor("orange").lineThickness(1.0);
    port.drawSpline(naturalCubicSpline, naturalAttrs);
    port.drawText("  Natural Cubic Spline", new pdg.Point(p2.x, p2.y + 20), labelAttrs.fillColor("orange"));

    // Cardinal spline
    var cardinalSpline = new pdg.Spline(pdg.spline_Cardinal);
    cardinalSpline.addSegment(p1,p2,p3,p4);
    var cardinalAttrs = new pdg.Attributes().lineColor("cyan").lineThickness(1.0);
    port.drawSpline(cardinalSpline, cardinalAttrs);
    port.drawText("  Cardinal Spline", new pdg.Point(p3.x, p3.y - 10), labelAttrs.fillColor("cyan"));
    
    // Cubic Bezier spline
    var bezierSpline = new pdg.Spline(pdg.spline_CubicBezier);
    bezierSpline.addSegment(p1,p2,p3,p4);
    var bezierAttrs = new pdg.Attributes().lineColor("yellow").lineThickness(1.0);
    port.drawSpline(bezierSpline, bezierAttrs);
    var textAttrs = new pdg.Attributes().textSize(14).textStyle(pdg.textStyle_LeftJustified).fillColor("yellow");
        port.drawText("  Cubic Bezier Spline", p4, textAttrs);

    // Uniform B spline
    var uniformBSpline = new pdg.Spline(pdg.spline_UniformB);
    uniformBSpline.addSegment(p1,p2,p3,p4);
    var uniformBAttrs = new pdg.Attributes().lineColor("green").lineThickness(1.0);
    port.drawSpline(uniformBSpline, uniformBAttrs);
    //var textAttrs = new pdg.Attributes().textSize(p4.y - 40).textStyle(14).fillColor(pdg.textStyle_LeftJustified, "green");
    port.drawText("  Uniform B Spline", new pdg.Point(p4.x - 300, p4.y - 40), textAttrs.fillColor("green"));
    
    // Draw control points
    var controlPoints = [
        { point: p1, color: "grey" },
        { point: p2, color: "grey" },
        { point: p3, color: "grey" },
        { point: p4, color: "grey" },
   ];
    
    var i = 1;
    controlPoints.forEach(function(cp) {
        var pointAttrs = new pdg.Attributes().fillColor(cp.color);
        port.drawCircle(cp.point, 4, pointAttrs);
        var textAttrs = new pdg.Attributes().textSize(14).textStyle(pdg.textStyle_Centered).fillColor(cp.color);
        port.drawText("" + i++, new pdg.Point(cp.point.x, cp.point.y + 20), textAttrs.fillColor(cp.color));
    });
    
    // Multi-segment splines in lower half
    var textAttrs = new pdg.Attributes().textSize(18).textStyle(pdg.textStyle_Bold).fillColor("white");
    port.drawText("Multi-Segment Splines", new pdg.Point(50, 450), textAttrs);
    
    // 3-segment Bezier spline (wavy line)
    var multiBezier = new pdg.Spline(pdg.spline_CubicBezier);
    multiBezier.addSegment(
        new pdg.Point(50, 500),
        new pdg.Point(100, 480),
        new pdg.Point(150, 520),
        new pdg.Point(200, 500)
    );
    multiBezier.addSegment(
        new pdg.Point(200, 500),  // Should match endpoint of first segment
        new pdg.Point(250, 480),
        new pdg.Point(300, 520),
        new pdg.Point(350, 500)
    );
    multiBezier.addSegment(
        new pdg.Point(350, 500),  // Should match endpoint of second segment
        new pdg.Point(400, 480),
        new pdg.Point(450, 520),
        new pdg.Point(500, 500)
    );
    var multiBezierAttrs = new pdg.Attributes().lineColor("yellow").lineThickness(2.0);
    port.drawSpline(multiBezier, multiBezierAttrs);
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Centered).fillColor("yellow");
    port.drawText("3-segment Bezier (u: 0-3)", new pdg.Point(275, 540), textAttrs);
    
    // Draw control points for multi-segment Bezier
    for (var j = 0; j < multiBezier.getPointCount(); j++) {
        var cp = multiBezier.getPoint(j);
        var isEndpoint = (j % 3 == 0);
        var pointAttrs = new pdg.Attributes().fillColor(isEndpoint ? "orange" : "grey");
        port.drawCircle(cp, isEndpoint ? 5 : 3, pointAttrs);
    }
    
    // Multi-segment Cardinal spline (smooth curve through points)
    var multiCardinal = new pdg.Spline(pdg.spline_Cardinal);
    multiCardinal.addPoint(new pdg.Point(100, 600));
    multiCardinal.addPoint(new pdg.Point(150, 650));
    multiCardinal.addPoint(new pdg.Point(250, 580));
    multiCardinal.addPoint(new pdg.Point(350, 620));
    multiCardinal.addPoint(new pdg.Point(450, 590));
    multiCardinal.addPoint(new pdg.Point(550, 630));
    multiCardinal.addPoint(new pdg.Point(600, 650));
    var multiCardinalAttrs = new pdg.Attributes().lineColor("cyan").lineThickness(2.0);
    port.drawSpline(multiCardinal, multiCardinalAttrs);
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Centered).fillColor("cyan");
    port.drawText("Cardinal with 7 points (u: 0-4)", new pdg.Point(350, 670), textAttrs);
    
    // Draw control points for Cardinal
    for (var k = 0; k < multiCardinal.getPointCount(); k++) {
        var cp2 = multiCardinal.getPoint(k);
        var pointAttrs = new pdg.Attributes().fillColor("green");
        port.drawCircle(cp2, 4, pointAttrs);
    }
    
    // Show getMaxU() values
    port.drawText("Bezier maxU: " + multiBezier.getMaxU() + " (" + multiBezier.getPointCount() + " pts)", 
                  new pdg.Point(100, 560), textAttrs.fillColor("white"));
    port.drawText("Cardinal maxU: " + multiCardinal.getMaxU() + " (" + multiCardinal.getPointCount() + " pts)", 
                  new pdg.Point(100, 690), textAttrs.fillColor("white"));
}

// Test 4: Rectangle drawing
function runRectangleDrawingTest(port) {
    var testTitle = "Renderer API Rectangle Drawing Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var startX = 50;
    var startY = 150;
    var spacing = 20;
    var rectSize = 80;
    var verticalInterval = rectSize + 40;
   
    // Draw filled rectangles
    var colors = ["red", "green", "blue", "yellow", "cyan", "magenta"];
    for (var i = 0; i < 8; i++) {
        var x = startX + i * (rectSize + spacing);
        var y = startY;
        var rect = new pdg.Rect(x, y, x+rectSize, y+rectSize);
        
        // Use Renderer API
        var fillAttrs = new pdg.Attributes();
        if (i == 6) {
            fillAttrs.texture(rocksTexture);
        } else if (i == 7) {
            fillAttrs.texture(yinYangTexture);
        } else {
            fillAttrs.fillColor(colors[i]);
        }
        port.drawRect(rect, fillAttrs);
    }
    
    // Draw framed rectangles
    startY += verticalInterval;
    for (var i = 0; i < 8; i++) {
        var x = startX + i * (rectSize + spacing);
        var y = startY;
        var rect = new pdg.Rect(x, y, x+rectSize, y+rectSize);
        
        // Use Renderer API
        var frameAttrs = new pdg.Attributes().lineThickness(1.0);
        if (i == 6) {
            frameAttrs.texture(rocksTexture);
        } else if (i == 7) {
            frameAttrs.texture(yinYangTexture);
        } else {
            frameAttrs.lineColor(colors[i]);
        }
        port.drawRect(rect, frameAttrs);
    }
    
    // Draw filled & framed rectangles
    startY += verticalInterval;
    for (var i = 0; i < 8; i++) {
        var x = startX + i * (rectSize + spacing);
        var y = startY;
        var rect = new pdg.Rect(x, y, x+rectSize, y+rectSize);
        
        // Use Renderer API
        var frameAttrs = new pdg.Attributes().lineThickness(3.0).lineColor("green");
        if (i == 6) {
            frameAttrs.texture(rocksTexture);
        } else if (i == 7) {
            frameAttrs.texture(yinYangTexture);
        } else {
            frameAttrs.lineColor(colors[i]).fillColor(colors[5-i]);
        }
        port.drawRect(rect, frameAttrs);
    }
    
    // Draw gradient filled rectangles
    startY += verticalInterval;
    for (var i = 0; i < 8; i++) {
        var x = startX + i * (rectSize + spacing);
        var y = startY;
        var rect = new pdg.Rect(x, y, x+rectSize, y+rectSize);
        
        // Use Renderer API
        var frameAttrs = new pdg.Attributes().lineColor(new pdg.Color('white')).lineThickness(1.0)
            .rotation(i * Math.PI/16, new pdg.Point(x + rectSize/2, y + rectSize/2));
        if (i == 6) {
            frameAttrs.texture(rocksTexture);
        } else if (i == 7) {
            frameAttrs.texture(yinYangTexture);
        } else {
            frameAttrs.fillGradient(new pdg.Point(x + 10 * i, y), colors[i], new pdg.Point(x+rectSize - 10 * i, y+rectSize), colors[5-i])
        }
        port.drawRect(rect, frameAttrs);
    }
    
    // Draw round rectangles
    startY += verticalInterval;
    for (var i = 0; i < 8; i++) {
        var x = startX + i * (rectSize + spacing);
        var y = startY;
        var rect = new pdg.Rect(x, y, x+rectSize, y+rectSize);
        var radius = 10 + i * 2;
        
        // Use Renderer API with rounded corners
        var roundedAttrs = new pdg.Attributes()
            .roundedCorners(radius)
            .rotation(i * Math.PI/16, new pdg.Point(x + rectSize/2, y + rectSize/2));
        if (i == 6) {
            roundedAttrs.texture(rocksTexture);
        } else if (i == 7) {
            roundedAttrs.texture(yinYangTexture);
        } else {
            roundedAttrs.fillColor(colors[i]);
        }
        port.drawRect(rect, roundedAttrs);
    }
    
    // Draw labels
    startY = 140;
    const labelAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Plain).fillColor("white");
    port.drawText("Filled Rectangles", new pdg.Point(startX, startY), labelAttrs);
    startY += verticalInterval;
    port.drawText("Framed Rectangles", new pdg.Point(startX, startY), labelAttrs);
    startY += verticalInterval;
    port.drawText("Framed & Filled Rectangles", new pdg.Point(startX, startY), labelAttrs);
    startY += verticalInterval;
    port.drawText("Gradient Filled Rectangles", new pdg.Point(startX, startY), labelAttrs);
    startY += verticalInterval;
    port.drawText("Round Rectangles", new pdg.Point(startX, startY), labelAttrs);
}

// Test 5: Circle drawing with Renderer API
function runCircleDrawingTest(port) {
    var testTitle = "Renderer API Circle Drawing Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var centerX = port.getDrawingArea().width() / 2 + 200;
    var centerY = port.getDrawingArea().height() / 2 - 50;
    
    // Draw concentric circles
    var colors = ["red", "green", "blue", "yellow", "cyan", "magenta"];
    var maxRadius = 100;
    var numCircles = 6;
    
    for (var i = numCircles - 1; i >= 0; i--) {
        var radius = (i + 1) * (maxRadius / numCircles);
        var center = new pdg.Point(centerX, centerY);
        
        // Alternate between filled and framed
        if (i % 2 === 0) {
            var fillAttrs = new pdg.Attributes().fillColor(colors[i % colors.length]);
            port.drawCircle(center, radius, fillAttrs);
        } else {
            var frameAttrs = new pdg.Attributes().lineColor(colors[i % colors.length]).lineThickness(2.0);
            port.drawCircle(center, radius, frameAttrs);
        }
    }
    
    // Draw circles in a grid
    var gridStartX = 50;
    var gridStartY = 200;
    var gridSpacing = 80;
    var gridRadius = 25;
    
    for (var row = 0; row < 3; row++) {
        for (var col = 0; col < 6; col++) {
            var x = gridStartX + col * gridSpacing;
            var y = gridStartY + row * gridSpacing;
            var center = new pdg.Point(x, y);
            
            if (row === 0) {
                var fillAttrs = new pdg.Attributes().fillColor(colors[col % colors.length]);
                port.drawCircle(center, gridRadius, fillAttrs);
            } else if (row === 1) {
                var frameAttrs = new pdg.Attributes().lineColor(colors[col % colors.length]).lineThickness(2.0);
                port.drawCircle(center, gridRadius, frameAttrs);
            } else {
                // Draw both filled and framed
                var fillAttrs = new pdg.Attributes().fillColor(colors[col % colors.length]);
                var frameAttrs = new pdg.Attributes().lineColor("white").lineThickness(1.0);
                port.drawCircle(center, gridRadius, fillAttrs);
                port.drawCircle(center, gridRadius, frameAttrs);
            }
        }
    }
    
    // Draw labels
    const labelAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Centered).fillColor("white");
    port.drawText("Concentric Circles (Center)", new pdg.Point(centerX, centerY + maxRadius + 20), labelAttrs);
    port.drawText("Filled | Framed | Filled+Framed", new pdg.Point(gridStartX + 150, gridStartY + 3 * gridSpacing + 20), labelAttrs);
}

// Test 6: Ellipse drawing with Renderer API
function runEllipseDrawingTest(port) {
    var testTitle = "Renderer API Oval Drawing Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var centerX = port.getDrawingArea().width() / 2;
    var centerY = port.getDrawingArea().height() / 2;
    
    // Draw ovals with different aspect ratios
    var colors = ["red", "green", "blue", "yellow", "cyan", "magenta"];
    var center = new pdg.Point(centerX, centerY);
    
    // Horizontal ovals
    var yOffset = -60;
    for (var i = 0; i < 3; i++) {
        var xRadius = 60 + i * 20;
        var yRadius = 20 + i * 5;
        var ovalCenter = new pdg.Point(centerX + 150, centerY + yOffset);
        
        var fillAttrs = new pdg.Attributes().fillColor(colors[i % colors.length])
            .rotation(i * Math.PI/16, ovalCenter);
        port.drawEllipse(ovalCenter, xRadius, yRadius, fillAttrs);
        yOffset += 40;
    }
    
    // Vertical ovals
    yOffset = -60;
    for (var i = 0; i < 3; i++) {
        var xRadius = 20 + i * 5;
        var yRadius = 60 + i * 20;
        var ovalCenter = new pdg.Point(centerX + 350, centerY + yOffset);
        
        var frameAttrs = new pdg.Attributes().lineColor(colors[i % colors.length]).lineThickness(2.0);
        port.drawEllipse(ovalCenter, xRadius, yRadius, frameAttrs);
        yOffset += 40;
    }
    
    // Draw some ovals in a pattern
    var patternStartX = 50;
    var patternStartY = 300;
    var patternSpacing = 60;
    
    for (var row = 0; row < 3; row++) {
        for (var col = 0; col < 8; col++) {
            var x = patternStartX + col * patternSpacing;
            var y = patternStartY + row * patternSpacing;
            var ovalCenter = new pdg.Point(x, y);
            
            var xRadius = 15 + col * 2;
            var yRadius = 15 + row * 5;
            
            if (row === 0) {
                var fillAttrs = new pdg.Attributes().fillColor(colors[col % colors.length]);
                port.drawEllipse(ovalCenter, xRadius, yRadius, fillAttrs);
            } else if (row === 1) {
                var frameAttrs = new pdg.Attributes().lineColor(colors[col % colors.length]).lineThickness(1.5);
                port.drawEllipse(ovalCenter, xRadius, yRadius, frameAttrs);
            } else {
                var fillAttrs = new pdg.Attributes().fillColor(colors[col % colors.length]);
                var frameAttrs = new pdg.Attributes().lineColor("white").lineThickness(1.0);
                port.drawEllipse(ovalCenter, xRadius, yRadius, fillAttrs);
                port.drawEllipse(ovalCenter, xRadius, yRadius, frameAttrs);
            }
        }
    }
    
    // Draw labels
    const labelAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Centered).fillColor("white");
    port.drawText("Horizontal Ovals (Filled)", new pdg.Point(centerX + 150, centerY + 80), labelAttrs);
    port.drawText("Vertical Ovals (Framed)", new pdg.Point(centerX + 350, centerY + 80), labelAttrs);
    port.drawText("Pattern: Filled | Framed | Filled+Framed", new pdg.Point(patternStartX + 200, patternStartY + 2 * patternSpacing + 60), labelAttrs);
}

// Test 7: Polygon drawing with Renderer API
function runPolygonDrawingTest(port) {
    var testTitle = "Renderer API Polygon Drawing Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var colors = ["red", "green", "blue", "yellow", "cyan", "magenta", "orange", "purple"];
    
    // Triangle (filled)
    var triangle = new pdg.Polygon(
        new pdg.Point(100, 150),
        new pdg.Point(200, 150),
        new pdg.Point(150, 100)
    );
    var triangleFillAttrs = new pdg.Attributes().fillColor("red");
    var triangleFrameAttrs = new pdg.Attributes().lineColor("white").lineThickness(1.0);
    port.drawPolygon(triangle, triangleFillAttrs);
    port.drawPolygon(triangle, triangleFrameAttrs);
    var textAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Centered).fillColor("white");
        port.drawText("Triangle", new pdg.Point(150, 170), textAttrs);
    
    // Square (framed)
    var square = new pdg.Polygon(
        new pdg.Point(250, 100),
        new pdg.Point(350, 100),
        new pdg.Point(350, 200),
        new pdg.Point(250, 200)
    );
    var squareFrameAttrs = new pdg.Attributes().lineColor("green").lineThickness(2.0);
    port.drawPolygon(square, squareFrameAttrs);
    //var textAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Centered).fillColor("green");
    port.drawText("Square", new pdg.Point(300, 220), textAttrs);
    
    // Pentagon (filled)
    var pentagon = new pdg.Polygon();
    var centerX = 450;
    var centerY = 150;
    var radius = 50;
    for (var i = 0; i < 5; i++) {
        var angle = (i * 2 * Math.PI) / 5 - Math.PI / 2; // Start from top
        var x = centerX + Math.cos(angle) * radius;
        var y = centerY + Math.sin(angle) * radius;
        pentagon.addPoint(new pdg.Point(x, y));
    }
    var pentagonFillAttrs = new pdg.Attributes().fillColor("blue");
    var pentagonFrameAttrs = new pdg.Attributes().lineColor("white").lineThickness(1.0);
    port.drawPolygon(pentagon, pentagonFillAttrs);
    port.drawPolygon(pentagon, pentagonFrameAttrs);
    //var textAttrs = new pdg.Attributes().textSize(centerY + 80).textStyle(14).fillColor(pdg.textStyle_Centered, "blue");
    port.drawText("Pentagon", new pdg.Point(centerX, centerY + 80), textAttrs);
    
    // Star shape (filled)
    var star = new pdg.Polygon();
    centerX = 600;
    centerY = 150;
    var outerRadius = 50;
    var innerRadius = 25;
    for (var i = 0; i < 10; i++) {
        var angle = (i * Math.PI) / 5 - Math.PI / 2; // Start from top
        var radius = (i % 2 === 0) ? outerRadius : innerRadius;
        var x = centerX + Math.cos(angle) * radius;
        var y = centerY + Math.sin(angle) * radius;
        star.addPoint(new pdg.Point(x, y));
    }
    var starFillAttrs = new pdg.Attributes().fillColor("yellow");
    var starFrameAttrs = new pdg.Attributes().lineColor("black").lineThickness(1.0);
    port.drawPolygon(star, starFillAttrs);
    port.drawPolygon(star, starFrameAttrs);
    //var textAttrs = new pdg.Attributes().textSize(centerY + 80).textStyle(14).fillColor(pdg.textStyle_Centered, "yellow");
    port.drawText("Star", new pdg.Point(centerX, centerY + 80), textAttrs);
    
    // Irregular polygon (framed)
    var irregular = new pdg.Polygon(
        new pdg.Point(100, 300),
        new pdg.Point(180, 280),
        new pdg.Point(200, 320),
        new pdg.Point(170, 380),
        new pdg.Point(120, 360)
    );
    var irregularFrameAttrs = new pdg.Attributes().lineColor("cyan").lineThickness(2.0);
    port.drawPolygon(irregular, irregularFrameAttrs);
    //var textAttrs = new pdg.Attributes().textSize(400).textStyle(14).fillColor(pdg.textStyle_Centered, "cyan");
    port.drawText("Irregular", new pdg.Point(150, 400), textAttrs);
    
    // Irregular polygon with wavy top (using addSpline)
    var wavyIrregular = new pdg.Polygon();
    wavyIrregular.addPoint(new pdg.Point(240, 300)); // Start point
    
    // Create a wavy line for the top edge using a Bezier spline
    var topEdgeSpline = new pdg.Spline(pdg.spline_CubicBezier);
    topEdgeSpline.addSegment(
        new pdg.Point(240, 300),     // Start
        new pdg.Point(260, 230),     // Control point 1 (dip down)
        new pdg.Point(280, 290),     // Control point 2 (dip down)
        new pdg.Point(320, 280)      // End
    );
    wavyIrregular.addSpline(topEdgeSpline, 0.05); // smooth curve
    
    // Add the remaining points to complete the polygon
    wavyIrregular.addPoint(new pdg.Point(340, 320));
    wavyIrregular.addPoint(new pdg.Point(310, 380));
    wavyIrregular.addPoint(new pdg.Point(260, 360));
    
    var wavyFrameAttrs = new pdg.Attributes().lineColor("orange").lineThickness(2.0);
    port.drawPolygon(wavyIrregular, wavyFrameAttrs);
    //  var textAttrs = new pdg.Attributes().textSize(400).textStyle(14).fillColor(pdg.textStyle_Centered, "orange");
    port.drawText("Bezier Spline Top", new pdg.Point(290, 400), textAttrs);
    //var textAttrs = new pdg.Attributes().textSize(420).textStyle(14).fillColor(pdg.textStyle_Centered, "orange");
    port.drawText("num points: " + wavyIrregular.getPointCount(), new pdg.Point(290, 420), textAttrs.textSize(14));
    
    // Diamond (filled)
    var diamond = new pdg.Polygon(
        new pdg.Point(450, 280),
        new pdg.Point(500, 330),
        new pdg.Point(450, 380),
        new pdg.Point(400, 330)
    );
    var diamondFillAttrs = new pdg.Attributes().fillColor("orange");
    var diamondFrameAttrs = new pdg.Attributes().lineColor("black").lineThickness(1.0);
    port.drawPolygon(diamond, diamondFillAttrs);
    port.drawPolygon(diamond, diamondFrameAttrs);
    // var textAttrs = new pdg.Attributes().textSize(400).textStyle(14).fillColor(pdg.textStyle_Centered, "orange");
    port.drawText("Diamond", new pdg.Point(450, 400), textAttrs);
    
    // Hexagon (framed)
    var hexagon = new pdg.Polygon();
    centerX = 600;
    centerY = 330;
    radius = 40;
    for (var i = 0; i < 6; i++) {
        var angle = (i * 2 * Math.PI) / 6;
        var x = centerX + Math.cos(angle) * radius;
        var y = centerY + Math.sin(angle) * radius;
        hexagon.addPoint(new pdg.Point(x, y));
    }
    var hexagonFrameAttrs = new pdg.Attributes().lineColor("purple").lineThickness(2.0);
    port.drawPolygon(hexagon, hexagonFrameAttrs);
    // var textAttrs = new pdg.Attributes().textSize(centerY + 70).textStyle(14).fillColor(pdg.textStyle_Centered, "purple");
    port.drawText("Hexagon", new pdg.Point(centerX, centerY + 70), textAttrs);
    
    // Wavy Flag (concave polygon with wave effect)
    var flag = new pdg.Polygon();
    var flagStartX = 100;
    var flagStartY = 450;
    var flagWidth = 120;
    var flagHeight = 80;
    var waveAmplitude = 15;
    var waveFrequency = 3;
    
    // Create flag with wavy edge
    for (var i = 0; i <= 20; i++) {
        var t = i / 20; // 0 to 1
        var x = flagStartX + t * flagWidth;
        var y = flagStartY + Math.sin(t * waveFrequency * Math.PI) * waveAmplitude;
        flag.addPoint(new pdg.Point(x, y));
    }
    
    // Add bottom edge points
    for (var i = 20; i >= 0; i--) {
        var t = i / 20; // 1 to 0
        var x = flagStartX + t * flagWidth;
        var y = flagStartY + flagHeight + Math.sin(t * waveFrequency * Math.PI) * waveAmplitude * 0.5;
        flag.addPoint(new pdg.Point(x, y));
    }
    
    var flagFillAttrs = new pdg.Attributes().fillColor(new pdg.Color(1, 0, 0, 0.8)); // Red flag with transparency
    var flagFrameAttrs = new pdg.Attributes().lineColor(new pdg.Color(0.5, 0, 0, 1)).lineThickness(1.0); // Dark red frame
    port.drawPolygon(flag, flagFillAttrs);
    port.drawPolygon(flag, flagFrameAttrs);
    // var textAttrs = new pdg.Attributes().textSize(flagStartY + flagHeight + 20).textStyle(14).fillColor(pdg.textStyle_Centered, "red");
    port.drawText("Wavy Flag", new pdg.Point(flagStartX + flagWidth/2, flagStartY + flagHeight + 20), textAttrs);
    // var textAttrs = new pdg.Attributes().textSize(flagStartY + flagHeight + 40).textStyle(14).fillColor(pdg.textStyle_Centered, "red");
    port.drawText("num points: " + flag.getPointCount(), 
            new pdg.Point(flagStartX + flagWidth/2, flagStartY + flagHeight + 40), 
            textAttrs.textSize(14));
   
    // Demonstrate transformations
    var transformedTriangle = new pdg.Polygon(
        new pdg.Point(100, 500),
        new pdg.Point(150, 500),
        new pdg.Point(125, 450)
    );
    transformedTriangle.scale(2.0);
    transformedTriangle.moveRight(100);
    var transformedAttrs = new pdg.Attributes().fillColor(new pdg.Color(1, 0.5, 0, 1)); // Orange
    port.drawPolygon(transformedTriangle, transformedAttrs);
    //var textAttrs = new pdg.Attributes().textSize(520).textStyle(14).fillColor(pdg.textStyle_Centered, "orange");
    port.drawText("Scaled & Moved", new pdg.Point(300, 520), textAttrs);
    
    // Rotated square
    var rotatedSquare = new pdg.Polygon(
        new pdg.Point(400, 500),
        new pdg.Point(500, 500),
        new pdg.Point(500, 600),
        new pdg.Point(400, 600)
    );
    rotatedSquare.rotateAround(Math.PI / 4, new pdg.Point(450, 550)); // 45 degrees
    var rotatedFillAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.5, 0, 1, 1)); // Purple
    var rotatedFrameAttrs = new pdg.Attributes().lineColor("white").lineThickness(1.0);
    port.drawPolygon(rotatedSquare, rotatedFillAttrs);
    port.drawPolygon(rotatedSquare, rotatedFrameAttrs);
    //var textAttrs = new pdg.Attributes().textSize(620).textStyle(14).fillColor(pdg.textStyle_Centered, "purple");
    port.drawText("Rotated Square", new pdg.Point(450, 640), textAttrs);

    // Arrow shape (filled)
    var arrow = new pdg.Polygon(
        new pdg.Point(570, 480),
        new pdg.Point(630, 480),
        new pdg.Point(630, 520),
        new pdg.Point(670, 500),
        new pdg.Point(600, 580),
        new pdg.Point(530, 500),
        new pdg.Point(570, 520)
    );
    var arrowFillAttrs = new pdg.Attributes().fillColor("magenta");
    var arrowFrameAttrs = new pdg.Attributes().lineColor("white").lineThickness(1.0);
    port.drawPolygon(arrow, arrowFillAttrs);
    port.drawPolygon(arrow, arrowFrameAttrs);
    //var textAttrs = new pdg.Attributes().textSize(600).textStyle(14).fillColor(pdg.textStyle_Centered, "magenta");
    port.drawText("Arrow", new pdg.Point(600, 600), textAttrs);
    
}

// Test 8: Sphere drawing with Renderer API
function runSphereDrawingTest(port) {
    var testTitle = "Renderer API Sphere Drawing Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var colors = ["red", "green", "blue", "yellow", "cyan", "magenta"];
    var startX = 100;
    var startY = 150;
    var spacing = 120;
    var radius = 40;
    
    // 5x5 grid of spheres with different properties
    for (var row = 0; row < 5; row++) {
        for (var col = 0; col < 5; col++) {
            var x = startX + col * spacing;
            var y = startY + row * spacing;
            var center = new pdg.Point(x, y);
            
            var colorIndex = (row + col) % colors.length;
            var attrs = new pdg.Attributes();
            
            if (row === 0) {
                // Row 0: Different polar offsets (rotation around vertical axis)
                var polarAngle = col * Math.PI / 2.5; // Varying rotation angles
                attrs.fillColor(colors[colorIndex]).polarOffset(new pdg.Offset(polarAngle, 0));
                port.drawSphere(center, radius, attrs);
            } else if (row === 1) {
                // Row 1: Different lighting offsets (light direction)
                var lightAngle = col * Math.PI / 2.5; // Varying light angles (azimuth)
                attrs.fillColor(colors[colorIndex]).lightOffset(new pdg.Offset(lightAngle, 0));
                port.drawSphere(center, radius, attrs);
            } else if (row === 2) {
                // Row 2: Varying ambient light colors
                var ambientColors = [
                    new pdg.Color(1.0, 0.0, 0.0, 1.0),  // Red ambient
                    new pdg.Color(0.0, 1.0, 0.0, 1.0),  // Green ambient
                    new pdg.Color(0.0, 0.0, 1.0, 1.0),  // Blue ambient
                    new pdg.Color(1.0, 1.0, 0.0, 1.0),  // Yellow ambient
                    new pdg.Color(0.2, 0.2, 0.2, 1.0)   // Dark ambient
                ];
                attrs.fillColor(colors[colorIndex]).ambientLight(ambientColors[col]);
                port.drawSphere(center, radius, attrs);
            } else if (row === 3) {
                // Row 3: Textured spheres with different polar offsets
                if (col < 3) {
                    var polarAngle = col * Math.PI / 3;
                    attrs.texture(earthTexture).polarOffset(new pdg.Offset(polarAngle, 0));
                    port.drawSphere(center, radius, attrs);
                } else {
                    var polarAngle = (col - 3) * Math.PI / 3;
                    attrs.texture(jupiterTexture).polarOffset(new pdg.Offset(polarAngle, 0));
                    port.drawSphere(center, radius, attrs);
                }
            } else {
                // Row 4: Combined polar, lighting and ambient
                var polarAngle = col * Math.PI / 4;
                var lightAngle = (4 - col) * Math.PI / 4;
                var ambientIntensity = 0.2 + (col * 0.15);  // Vary from 0.2 to 0.8
                attrs.texture(moonTexture)
                    .polarOffset(new pdg.Offset(polarAngle, 0))
                    .lightOffset(new pdg.Offset(lightAngle, Math.PI / 6))
                    .ambientLight(new pdg.Color(ambientIntensity, ambientIntensity, ambientIntensity, 1.0));
                port.drawSphere(center, radius, attrs);
            }
        }
    }
    
    // Draw labels for each row
    var labelAttrs = new pdg.Attributes().textSize(14).textStyle(pdg.textStyle_Plain).fillColor("white");
    port.drawText("Polar", new pdg.Point(startX - 90, startY), labelAttrs);
    port.drawText("Lighting", new pdg.Point(startX - 90, startY + spacing), labelAttrs);
    port.drawText("Ambient", new pdg.Point(startX - 90, startY + spacing * 2), labelAttrs);
    port.drawText("Textured", new pdg.Point(startX - 90, startY + spacing * 3), labelAttrs);
    port.drawText("Combined", new pdg.Point(startX - 90, startY + spacing * 4), labelAttrs);
    
    // Add description
    var descAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Centered).fillColor("lightgray");
    port.drawText("5x5 grid: columns vary rotation/lighting, rows vary sphere types", 
                  new pdg.Point(port.getDrawingArea().width()/2, startY + spacing * 5), descAttrs);
}

// Test 8: Advanced drawing features with Renderer API
function runAdvancedDrawingTest(port) {
    var testTitle = "Renderer API Advanced Drawing Features Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    // Test gradient rectangles
    var gradientRect = new pdg.Rect(100, 100, 200, 200); // left, top, right, bottom
    var gradientAttrs = new pdg.Attributes()
        .fillGradient(new pdg.Point(100, 200), new pdg.Color(1, 0, 0, 1), 
                     new pdg.Point(200, 200), new pdg.Color(0, 0, 1, 1));
    port.drawRect(gradientRect, gradientAttrs);
    var frameAttrs = new pdg.Attributes().lineColor("red").lineThickness(1.0);
    port.drawRect(gradientRect, frameAttrs);
    var textAttrs = new pdg.Attributes().textSize(14).textStyle(pdg.textStyle_Centered).fillColor("white");
    port.drawText("Gradient Rectangle", new pdg.Point(150, 220), textAttrs);
    
    // Test thick borders
    var thickBorderRect = new pdg.Rect(300, 100, 500, 200);
    var thickBorderAttrs = new pdg.Attributes().lineColor(new pdg.Color(0, 1, 0, 1)).lineThickness(3.0);
    port.drawRect(thickBorderRect, thickBorderAttrs);
    port.drawText("Thick Border", new pdg.Point(400, 220), textAttrs);
    
    // Test thick lines
    var thickLineRect = new pdg.Rect(550, 100, 650, 200); // left, top, right, bottom
    var thickLineAttrs = new pdg.Attributes().lineColor("orange").lineThickness(5.0);
    port.drawRect(thickLineRect, thickLineAttrs);
    port.drawText("Thick Border", new pdg.Point(650, 220), textAttrs);
    
    // Test rotated rectangles
    var centerX = port.getDrawingArea().width() / 2;
    var centerY = 350;
    
    // Create a rotated rectangle using Quad
    var size = 60;
    var angle = (frameCount * 2) % 360; // Rotate over time
    var rad = angle * Math.PI / 180;
    var cos = Math.cos(rad);
    var sin = Math.sin(rad);
    
    var quad = new pdg.Quad(
        new pdg.Point(centerX - size * cos + size * sin, centerY - size * sin - size * cos),
        new pdg.Point(centerX + size * cos + size * sin, centerY + size * sin - size * cos),
        new pdg.Point(centerX + size * cos - size * sin, centerY + size * sin + size * cos),
        new pdg.Point(centerX - size * cos - size * sin, centerY - size * sin + size * cos)
    );
    
    var quadAttrs = new pdg.Attributes().fillColor("magenta");
    port.drawQuad(quad, quadAttrs);
    port.drawText("Rotating Quad: " + Math.round(angle) + "°", new pdg.Point(centerX, centerY + size + 20), textAttrs);
    
    // Test clipping
    var clipRect = new pdg.Rect(50, 400, 350, 550); // left, top, right, bottom
    port.setClipRect(clipRect);
    
    // Draw a large circle that should be clipped
    var clippedCircleAttrs = new pdg.Attributes().fillColor(new pdg.Color(0, 1, 1, 1)); // Cyan
    port.drawCircle(new pdg.Point(200, 475), 100, clippedCircleAttrs);
    var clipFrameAttrs = new pdg.Attributes().lineColor("gray").lineThickness(1.0);
    port.drawRect(clipRect, clipFrameAttrs);
    
    // Reset clipping
    port.setClipRect(port.getDrawingArea());
    
    port.drawText("Clipped Circle", new pdg.Point(200, 590), textAttrs);
    
    // Test transparency
    var transparentRect = new pdg.Rect(400, 400, 500, 500); // left, top, right, bottom
    var transparentAttrs = new pdg.Attributes().fillColor(new pdg.Color(1, 0, 0, 0.5)); // Semi-transparent red
    port.drawRect(transparentRect, transparentAttrs);
    
    var overlayRect = new pdg.Rect(450, 475, 550, 575); // left, top, right, bottom
    var overlayAttrs = new pdg.Attributes().fillColor(new pdg.Color(0, 1, 0, 0.5)); // Semi-transparent green
    port.drawRect(overlayRect, overlayAttrs);
    
    port.drawText("Transparency Test", new pdg.Point(500, 600), textAttrs);
}


function runNextTest() {
    if (currentTest >= 8) {
        console.log("All tests completed for all screens.");
        console.log("Closing all ports...");
        ports.forEach(function(portInfo) {
            pdg.gfx.closeGraphicsPort(portInfo.port);
        });
        clearTimeout(testTimeout);
        testTimeout = null;
        pdg.quit();
        return;
    }
    console.log("Starting test " + (currentTest + 1) + "/8");
    
    if (waitForUser) {
        console.log("Press SPACE to continue to next test, ESC to quit");
    } else {
        testTimeout = setTimeout(function() {
            currentTest++;
            runNextTest();
        }, testDuration);
    }
}

// Function to start the test sequence
function startTestSequence() {
    currentTest = 0;
    frameCount = 0;
    runNextTest();
}

// Start testing
if (numScreens > 0) {
    createAllPorts();
    var drawHandler = setupDrawHandler();
    var keyHandler = setupKeyHandler();
    startTestSequence();
} else {
    console.log("No screens detected!");
}

pdg.run();
