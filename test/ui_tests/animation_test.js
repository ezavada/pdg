// This script tests advanced animation features with Renderer API

console.log("=== Renderer API ANIMATION TEST SCRIPT ===");
console.log("Testing advanced animation features with Renderer API...");

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
if (!rocksTexture || !yinYangTexture) {
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
        var testText = "Test: " + (currentTest + 1) + "/1";
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
                runColombianFlagTest(port);
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

// Test 1: Animated Colombian Flag with Renderer API
function runColombianFlagTest(port) {
    var testTitle = "Renderer API Animated Colombian Flag Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    // Flag dimensions (3:2 aspect ratio as per Colombian flag standards)
    var flagWidth = 360;
    var flagHeight = 240; // 3:2 ratio
    var flagX = (port.getDrawingArea().width() - flagWidth) / 2;
    var flagY = 150;
    
    // Animation parameters
    var time = frameCount * 0.1; // Time-based animation
    var waveAmplitude = 13; // How much the flag waves
    var waveFrequency = 2.5; // How fast the waves travel
    var waveSpeed = 2.7; // Overall animation speed

    var waveAmplitude2 = 11;
    var waveFrequency2 = 5.1;
    var waveSpeed2 = 1.7;

    // Create the flag as three separate polygons for the three stripes
    // Yellow stripe (top half)
    var yellowFlag = new pdg.Polygon();
    var blueFlag = new pdg.Polygon();
    var redFlag = new pdg.Polygon();
    
    // Define number of vertices for smooth waving
    var numVertices = 15;
    
    var extra = 0;
    var x;
    // Create yellow stripe (top half)
    for (var i = 0; i <= numVertices; i++) {
        var t = i / numVertices; // 0 to 1
        x = flagX + t * flagWidth;
        extra = Math.sin(t * waveFrequency2 * Math.PI + time * waveSpeed2) * waveAmplitude2 * i / numVertices;
        var y = flagY + Math.sin(t * waveFrequency * Math.PI + time * waveSpeed) * waveAmplitude + extra;
        yellowFlag.addPoint(new pdg.Point(x, y));
    }
    var adjustedTopCorner = yellowFlag.getPoint(0);
    var vertOffset = adjustedTopCorner.y - flagY;
    yellowFlag.addPoint(new pdg.Point(x - extra + 3, flagY + flagHeight/4));
    yellowFlag.moveUp(vertOffset);
     
    // Add bottom edge of yellow stripe (middle of flag)
    for (var i = numVertices; i >= 0; i--) {
        var t = i / numVertices; // 1 to 0
        x = 5 + flagX + t * flagWidth;
        extra = Math.sin(t * waveFrequency2 * Math.PI + time * waveSpeed2) * waveAmplitude2 * i / numVertices;
        var y = flagY + flagHeight/2 + Math.sin(t * waveFrequency * Math.PI + time * waveSpeed) * waveAmplitude * 0.7 + extra;
        if (i == numVertices) {
            x = x - extra * 0.7 + 5;
        }
        yellowFlag.addPoint(new pdg.Point(x, y - vertOffset * 0.7));
    }
    yellowFlag.addPoint(new pdg.Point(flagX + 3, flagY + flagHeight/4));
    
    
    // Create blue stripe (second quarter)
    for (var i = 0; i <= numVertices; i++) {
        var t = i / numVertices; // 0 to 1
        var x = 5 + flagX + t * flagWidth;
        extra = Math.sin(t * waveFrequency2 * Math.PI + time * waveSpeed2) * waveAmplitude2 * i / numVertices;
        var y = flagY + flagHeight/2 + Math.sin(t * waveFrequency * Math.PI + time * waveSpeed) * waveAmplitude * 0.7 + extra;
        if (i == numVertices) {
            x = x - extra * 0.7 + 5;
        }
        blueFlag.addPoint(new pdg.Point(x, y - (1 + vertOffset * 0.7)));
    }
    
    // Add bottom edge of blue stripe (third quarter)
    for (var i = numVertices; i >= 0; i--) {
        var t = i / numVertices; // 1 to 0
        var x = 3 + flagX + t * flagWidth;
        extra = Math.sin(t * waveFrequency2 * Math.PI + time * waveSpeed2) * waveAmplitude2 * i / numVertices;
        var y = flagY + flagHeight*3/4 + Math.sin(t * waveFrequency * Math.PI + time * waveSpeed) * waveAmplitude * 0.5 + extra;
        if (i == numVertices) {
            x = x - extra * 0.5 + 3;
        }
        blueFlag.addPoint(new pdg.Point(x, y - vertOffset * 0.5));
    }
    
    // Create red stripe (bottom quarter)
    for (var i = 0; i <= numVertices; i++) {
        var t = i / numVertices; // 0 to 1
        var x = 3 + flagX + t * flagWidth;
        extra = Math.sin(t * waveFrequency2 * Math.PI + time * waveSpeed2) * waveAmplitude2 * i / numVertices;
        var y = flagY + flagHeight*3/4 + Math.sin(t * waveFrequency * Math.PI + time * waveSpeed) * waveAmplitude * 0.5 + extra;
        if (i == numVertices) {
            x = x - extra * 0.5 + 3;
        }
        redFlag.addPoint(new pdg.Point(x, y - (1 + vertOffset * 0.5)));
    }
    
    // Add bottom edge of red stripe
    for (var i = numVertices; i >= 0; i--) {
        var t = i / numVertices; // 1 to 0
        var x = flagX + t * flagWidth;
        extra = Math.sin(t * waveFrequency2 * Math.PI + time * waveSpeed2) * waveAmplitude2 * i / numVertices;
        var y = flagY + flagHeight + Math.sin(t * waveFrequency * Math.PI + time * waveSpeed) * waveAmplitude * 0.3 + extra;
        redFlag.addPoint(new pdg.Point(x, y - vertOffset * 0.3));
    }
     
    // Draw the three stripes with Colombian flag colors
    var yellowAttrs = new pdg.Attributes().fillColor(new pdg.Color(1, 0.8, 0, 1)); // Golden yellow
    var blueAttrs = new pdg.Attributes().fillColor(new pdg.Color(0, 0.4, 0.8, 1)); // Colombian blue
    var redAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.8, 0.1, 0.1, 1)); // Colombian red
    port.drawPolygon(yellowFlag, yellowAttrs);
    port.drawPolygon(blueFlag, blueAttrs);
    port.drawPolygon(redFlag, redAttrs);
    
    // Add flagpole
    var poleStart = new pdg.Point(flagX - 10, flagY - 10);
    var poleEnd = new pdg.Point(flagX - 10, flagY + flagHeight + 40);
    var poleAttrs = new pdg.Attributes().lineColor(new pdg.Color(0.4, 0.2, 0.1, 1)).lineThickness(8.0); // Brown pole
    port.drawLine(poleStart, poleEnd, poleAttrs);

    const numPoints = yellowFlag.getPointCount() + blueFlag.getPointCount() + redFlag.getPointCount();
    var textAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Centered).fillColor("grey");
    port.drawText("num points: " + numPoints, new pdg.Point(flagX + flagWidth/2, flagY + flagHeight + 50), textAttrs);

}

function runNextTest() {
    if (currentTest >= 1) {
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
    console.log("Starting test " + (currentTest + 1) + "/1");
    
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
