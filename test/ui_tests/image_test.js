// Standalone Image Drawing Test Script
// This script tests various image drawing capabilities in PDG

console.log("=== STANDALONE IMAGE DRAWING TEST SCRIPT ===");
console.log("Testing image drawing functionality...");

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
var testImages = [];
var currentTest = 0;
var frameCount = 0;

// Test configuration
var testDuration = 4000; // 4 seconds per test
var frameDelay = 100; // 100ms between frames for animation tests
var testTimeout = null;

// Function to load test images
function loadTestImages() {
    console.log("Loading test images...");
    
    try {
        // Load different image formats
        var yinyang = new pdg.Image("yinyang.png");
        var earthmap = new pdg.Image("earthmap.jpg");
        var rocks = new pdg.Image("data/rocks.png");
        var tiles = new pdg.Image("tiles.png");
        
        testImages = [yinyang, tiles, earthmap, rocks];
        
        console.log("Loaded images:");
        testImages.forEach(function(img, index) {
            console.log("  Image " + index + ": " + img.getWidth() + "x" + img.getHeight());
        });
        
        return true;
    } catch (e) {
        console.log("ERROR: Failed to load test images:", e);
        return false;
    }
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
        var port = pdg.gfx.createWindowPort(windowRect, "PDG Image Drawing Test - Screen " + screenNum);
        
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
        var textAttrs = new pdg.Attributes().textSize(24).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("white");
        port.drawText("PDG Image Drawing Test - Screen " + screenNum, titlePoint, textAttrs);
        
        // Draw frame counter
        var frameText = "Frame: " + portInfo.frameCount + " (Global: " + frameCount + ")";
        var framePoint = new pdg.Point(10, 20);
        var textAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Plain).fillColor("yellow");
        port.drawText(frameText, framePoint, textAttrs);
        
        // Draw current test info
        var testText = "Test: " + (currentTest + 1) + "/5";
        var testPoint = new pdg.Point(actualWidth/2, 80);
        var textAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Centered).fillColor("aqua");
        port.drawText(testText, testPoint, textAttrs);
        
        // Draw instructions based on mode
        var instructionText = waitForUser ? "Press SPACE to continue, ESC to quit" : "Press any key to advance early, ESC to quit";
        var instructionPoint = new pdg.Point(actualWidth/2, actualHeight - 30);
        var textAttrs = new pdg.Attributes().textSize(14).textStyle(pdg.textStyle_Centered).fillColor("yellow");
        port.drawText(instructionText, instructionPoint, textAttrs);
        
        // Run the appropriate test based on currentTest
        switch (currentTest) {
            case 0:
                runBasicImageTest(port);
                break;
            case 1:
                runScalingTest(port);
                break;
            case 2:
                runAnimationTest(port);
                break;
            case 3:
                runTransparencyTest(port);
                break;
            case 4:
                runTextureTest(port);
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

// Test 1: Basic image drawing
function runBasicImageTest(port) {
    var testTitle = "Basic Image Drawing";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    // Draw each image at its original size
    var startX = 50;
    var startY = 86;
    var spacing = 20;
    var infoPoint = new pdg.Point(startX, startY);
    var imagePoint = new pdg.Point(startX, startY + 10);
    var maxWidth = port.getDrawingArea().width()/4;
    
    testImages.forEach(function(img, index) {
        // Draw image info
        var width = img.getWidth();
        var height = img.getHeight();
        if (width > maxWidth) {
            width = maxWidth;
            height = height * (width / img.getWidth());
        }
        var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText("Image " + index + ": " + width + "x" + height, infoPoint, textAttrs);
        var frameAttrs = new pdg.Attributes().lineColor("silver").lineThickness(1.0);
        port.drawRect(new pdg.Rect(imagePoint, img.getWidth(), img.getHeight()), frameAttrs);
        // Draw image
        port.drawImage(img, imagePoint, new pdg.Attributes());

        // move to next image
        infoPoint.x += width + spacing;
        imagePoint.x += width + spacing;
    });
}

// Test 2: Image scaling
function runScalingTest(port) {
    var testTitle = "Image Scaling Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var img = testImages[0]; // Use yinyang image
    var startX = 50;
    var startY = 86;
    var interval = 100;
    var infoPoint = new pdg.Point(startX, startY);
    var targetRect = new pdg.Rect(0, 0, img.getWidth(), img.getHeight());
    
    // Draw original size
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText("Original", infoPoint, textAttrs);
    targetRect.moveTo(infoPoint.x, infoPoint.y + 10);
    var frameAttrs = new pdg.Attributes().lineColor("gray").lineThickness(1.0);
    port.drawRect(targetRect, frameAttrs);
    port.drawImage(img, targetRect, new pdg.Attributes());
    
    // Draw scaled down
    infoPoint.x += targetRect.width() + interval;
    targetRect.scale(0.5);
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText("Scaled Down", infoPoint, textAttrs);
    targetRect.moveTo(infoPoint.x, infoPoint.y + 10);
    var frameAttrs = new pdg.Attributes().lineColor("gray").lineThickness(1.0);
    port.drawRect(targetRect, frameAttrs);
    port.drawImage(img, targetRect, new pdg.Attributes());
    
    // Draw scaled up
    infoPoint.x += targetRect.width() + interval;
    targetRect.scale(4.5);
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText("Scaled Up", infoPoint, textAttrs);
    targetRect.moveTo(infoPoint.x, infoPoint.y + 10);
    var frameAttrs = new pdg.Attributes().lineColor("gray").lineThickness(1.0);
    port.drawRect(targetRect, frameAttrs);
    port.drawImage(img, targetRect, new pdg.Attributes());
 
    // Draw with different fit types
    infoPoint.x += targetRect.width() + interval;
    targetRect.setWidth(50);
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText("Fit Fill", infoPoint, textAttrs);
    targetRect.moveTo(infoPoint.x, infoPoint.y + 10);
    var imageAttrs = new pdg.Attributes().fitType(pdg.fit_Fill);
    port.drawImage(img, targetRect, imageAttrs);
    var frameAttrs = new pdg.Attributes().lineColor("gray").lineThickness(1.0);
    port.drawRect(targetRect, frameAttrs);

    infoPoint.x += targetRect.width() + interval;
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText("Fit Fill Keep Proportions", infoPoint, textAttrs);
    targetRect.moveTo(infoPoint.x, infoPoint.y + 10);
    var imageAttrs = new pdg.Attributes().fitType(pdg.fit_FillKeepProportions);
    port.drawImage(img, targetRect, imageAttrs);
    var frameAttrs = new pdg.Attributes().lineColor("gray").lineThickness(1.0);
    port.drawRect(targetRect, frameAttrs);

    infoPoint.x = startX;
    infoPoint.y += targetRect.height() + interval;
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText("Fit Height", infoPoint, textAttrs);
    targetRect.moveTo(infoPoint.x, infoPoint.y + 10);
    var imageAttrs = new pdg.Attributes().fitType(pdg.fit_Height);
    port.drawImage(img, targetRect, imageAttrs);
    var frameAttrs = new pdg.Attributes().lineColor("gray").lineThickness(1.0);
    port.drawRect(targetRect, frameAttrs);
    
    infoPoint.x += targetRect.width() + interval;
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText("Fit Height Clipped", infoPoint, textAttrs);
    targetRect.moveTo(infoPoint.x, infoPoint.y + 10);
    var imageAttrs = new pdg.Attributes().fitType(pdg.fit_Height).clipOverflow(true);
    port.drawImage(img, targetRect, imageAttrs);  // FIXME: clip overflow is not working as expected
    var frameAttrs = new pdg.Attributes().lineColor("gray").lineThickness(1.0);
    port.drawRect(targetRect, frameAttrs);

    infoPoint.x += targetRect.width() + interval;
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText("Fit Height w/Clip Rect", infoPoint, textAttrs);
    targetRect.moveTo(infoPoint.x, infoPoint.y + 10);
    port.setClipRect(targetRect);  // FIXME: clip rect not working as expected
    var imageAttrs = new pdg.Attributes().fitType(pdg.fit_Height);
    port.drawImage(img, targetRect, imageAttrs);
    var frameAttrs = new pdg.Attributes().lineColor("gray").lineThickness(1.0);
    port.drawRect(targetRect, frameAttrs);
    port.setClipRect(port.getDrawingArea());

    infoPoint.x += targetRect.width() + interval;
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText("Fit Width", infoPoint, textAttrs);
    targetRect.moveTo(infoPoint.x, infoPoint.y + 10);
    var imageAttrs = new pdg.Attributes().fitType(pdg.fit_Width);
    port.drawImage(img, targetRect, imageAttrs);
    var frameAttrs = new pdg.Attributes().lineColor("gray").lineThickness(1.0);
    port.drawRect(targetRect, frameAttrs);

    infoPoint.x += targetRect.width() + interval;
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText("Fit Inside", infoPoint, textAttrs);
    targetRect.moveTo(infoPoint.x, infoPoint.y + 10);
    var imageAttrs = new pdg.Attributes().fitType(pdg.fit_Inside);
    port.drawImage(img, targetRect, imageAttrs);
    var frameAttrs = new pdg.Attributes().lineColor("gray").lineThickness(1.0);
    port.drawRect(targetRect, frameAttrs);
}

// Test 3: Image positioning and rotation
function runAnimationTest(port) {
    var testTitle = "Image Animation & Movement";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var img = testImages[1]; // Use tiles image
    
    // Draw at different positions
    var positions = [
        { x: 50, y: 100, label: "" },
        { x: 150, y: 100, label: "Transparent" },
    ];
    
    positions.forEach(function(pos) {
        var x = pos.x;
        var y = pos.y;
        var rect = new pdg.Rect(x, y, x + 180, y + 180);
        
        port.drawImage(img, rect, new pdg.Attributes());
        var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText(pos.label, new pdg.Point(x, y), textAttrs);
    });
    
    var centerX = port.getDrawingArea().width()/2;
    var centerY = port.getDrawingArea().height()/2;
   
    var angle = (frameCount * 2) % 360; // Rotate over time
    var rad = angle * Math.PI / 180;

    var center = new pdg.Point(centerX, centerY);
    var topLeft = new pdg.Point(centerX - img.getWidth()/2, centerY - img.getHeight()/2);
    
    port.drawImage(img, topLeft, new pdg.Attributes().rotation(rad, center));
    port.drawText("Rotated: " + Math.round(angle) + "°", new pdg.Point(centerX - 40, centerY + size + 10), textAttrs);
}

// Test 4: Image opacity
function runTransparencyTest(port) {
    var testTitle = "Image Opacity Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
    port.drawText(testTitle, titlePoint, textAttrs);
    
    var img = testImages[2]; // Use rocks image
    var baseX = 50;
    var baseY = 120;
    
    // Draw background pattern
    for (var i = 0; i < 5; i++) {
        for (var j = 0; j < 3; j++) {
            var bgRect = new pdg.Rect(new pdg.Point(baseX + i * 120, baseY + j * 130), 100, 100);
            var bgAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.3 * j, 0.3 * j, 0.3 * j, 1.0));
            port.drawRect(bgRect, bgAttrs);
        }
    }
    
    // Draw with different opacity levels
    var opacities = [0.1, 0.25, 0.5, 0.75, 1.0];
    for (var j = 0; j < 3; j++) {
        opacities.forEach(function(opacity, index) {
            var x = baseX + index * 120;
            var y = baseY + j * 130;
            var rect = new pdg.Rect(new pdg.Point(x, y), 100, 100);
            
            port.drawImage(img, rect, new pdg.Attributes().fillOpacity(opacity));
            var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
            port.drawText("Opacity: " + opacity, new pdg.Point(x, y + rect.height() + 10), textAttrs);
        });
    }
}

// Test 5: Texture drawing
function runTextureTest(port) {
    var testTitle = "Image Texture Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var img = testImages[3]; // Use tiles image
    
    // Draw as texture filling different areas
    var textureAreas = [
        { rect: new pdg.Rect(50, 120, 200, 150), label: "Small Texture" },
        { rect: new pdg.Rect(300, 120, 300, 200), label: "Large Texture" },
        { rect: new pdg.Rect(650, 120, 150, 300), label: "Tall Texture" }
    ];
    
    textureAreas.forEach(function(area) {
        //port.drawTexture(img, area.rect);  // FIXME: texture drawing needs to be reimplemented
        var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText(area.label, new pdg.Point(area.rect.left, area.rect.bottom + 5), textAttrs);
    });
    
    // Draw some regular images for comparison
    var regularRect = new pdg.Rect(50, 350, 100, 100);
    port.drawImage(img, regularRect, new pdg.Attributes());
    var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("white");
    port.drawText("Regular Image", new pdg.Point(regularRect.left, regularRect.bottom + 5), textAttrs);
}

function runNextTest() {
    if (currentTest >= 5) {
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
    console.log("Starting test " + (currentTest + 1) + "/5");
    
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
if (loadTestImages()) {
    if (numScreens > 0) {
        createAllPorts();
        var drawHandler = setupDrawHandler();
        var keyHandler = setupKeyHandler();
        startTestSequence();
    } else {
        console.log("No screens detected!");
    }
} else {
    console.log("Failed to load test images. Exiting.");
    pdg.quit();
}

pdg.run();