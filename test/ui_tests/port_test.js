// Standalone Port Test Script
// This script creates windows on each available monitor simultaneously to test PDG's multi-monitor functionality

console.log("=== STANDALONE PORT TEST SCRIPT ===");
console.log("Testing multi-monitor support simultaneously...");

// Check for --wait parameter
var waitForUser = false;
for (var i = 0; i < process.argv.length; i++) {
    if (process.argv[i] === '--wait') {
        waitForUser = true;
        break;
    }
}

if (waitForUser) {
    console.log("Manual mode: Press SPACE or ESC to end test");
} else {
    console.log("Auto mode: Test will run for 10 seconds, press any key to end early");
}

// Check how many screens are available
var numScreens = pdg.gfx.getNumScreens();
console.log("Number of screens detected:", numScreens);

// Store created ports for cleanup
var ports = [];
var frameCount = 0;

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
        var windowWidth = 800;
        var windowHeight = 600;
        var windowRect = new pdg.Rect(windowWidth, windowHeight);
        
        windowRect.center(screenBounds);
        console.log("Creating window on screen", screenNum, "at position:", windowRect);
        
        // Create window port on this screen
        var port = pdg.gfx.createWindowPort(windowRect, "PDG UI Test - Screen " + screenNum);
        
        if (!port) {
            console.log("ERROR: Could not create window port for screen", screenNum);
            continue;
        }
        
        var drawingArea = port.getDrawingArea();
        console.log("Window port drawing area: " + drawingArea.width() + "x" + drawingArea.height());
        
        // Store the port with its screen number and bounds
        ports.push({
            port: port,
            screenNum: screenNum,
            screenBounds: screenBounds,
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
        var screenBounds = portInfo.screenBounds;
        
        //console.log("PortDraw event received for screen", screenNum, "frameNum:", evt.frameNum);
        
        // Clear the background
        var portRect = port.getDrawingArea();
        var backgroundAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.2, 0.2, 0.2, 1.0));
        port.drawRect(portRect, backgroundAttrs); // Dark gray background
        
        // Calculate scaling factors for high DPI displays
        var actualWidth = portRect.width();
        var actualHeight = portRect.height();

        // Define test regions within the window
        var testRegions = [
            { name: "RED REGION", 
                color: new pdg.Color(1.0, 0.0, 0.0, 1.0), 
                textColor: new pdg.Color(1.0, 1.0, 1.0, 1.0), 
                rect: new pdg.Rect(0, 0, actualWidth/2, actualHeight/2) },
            { name: "GREEN REGION", 
                color: new pdg.Color(0.0, 1.0, 0.0, 1.0), 
                textColor: new pdg.Color(0.0, 0.0, 0.0, 1.0), 
                rect: new pdg.Rect(actualWidth/2, 0, actualWidth, actualHeight/2) },
            { name: "BLUE REGION", 
                color: new pdg.Color(0.0, 0.0, 1.0, 1.0), 
                textColor: new pdg.Color(1.0, 1.0, 1.0, 1.0), 
                rect: new pdg.Rect(0, actualHeight/2, actualWidth/2, actualHeight) },
            { name: "YELLOW REGION", 
                color: new pdg.Color(1.0, 1.0, 0.0, 1.0), 
                textColor: new pdg.Color(0.0, 0.0, 0.0, 1.0), 
                rect: new pdg.Rect(actualWidth/2, actualHeight/2, actualWidth, actualHeight) }
        ];
        
        // Draw each test region
        testRegions.forEach(function(region, index) {
            // Fill the region with its color
            var regionAttrs = new pdg.Attributes().fillColor(region.color);
            port.drawRect(region.rect, regionAttrs);
            
            // Draw the region name
            var textPoint = new pdg.Point(region.rect.left + 10, region.rect.top + 30);
            var textAttrs = new pdg.Attributes().textSize(24).textStyle(pdg.textStyle_Bold).fillColor(region.textColor);
            port.drawText(region.name, textPoint, textAttrs);
            
            // Draw region info
            var infoPoint = new pdg.Point(region.rect.left + 10, region.rect.bottom - 20);
            var infoAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Plain).fillColor(region.textColor);
            port.drawText("Screen: " + screenNum + " Region: " + index, infoPoint, infoAttrs);
        });
    
        // Draw screen info at the top
        var screenInfoPoint = new pdg.Point(actualWidth/2, actualHeight/4);
        var screenInfoAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor(new pdg.Color(1.0, 1.0, 1.0, 1.0));
        port.drawText("Screen " + screenNum + " - Bounds: " + screenBounds.left 
            + "," + screenBounds.top + " " + screenBounds.width() 
            + "x" + screenBounds.height(), screenInfoPoint, screenInfoAttrs);
        
        // Draw frame counter
        var frameText = "Frame: " + portInfo.frameCount + " (Global: " + frameCount + ")";
        var framePoint = new pdg.Point(actualWidth/2, actualHeight - 50);
        var frameAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Centered).fillColor("black");
        port.drawText(frameText, framePoint, frameAttrs);
        
        // Draw instructions based on mode
        var instructionText = waitForUser ? "Press SPACE or ESC to end test" : "Press any key to end early";
        var instructionPoint = new pdg.Point(actualWidth/2, actualHeight - 100);
        var instructionAttrs = new pdg.Attributes().textSize(14).textStyle(pdg.textStyle_Centered).fillColor("black");
        port.drawText(instructionText, instructionPoint, instructionAttrs);
        
        return true; // We handled this event
    });
    
    return drawHandler;
}

function setupKeyHandler() {
    var keyHandler = pdg.on(pdg.eventType_KeyPress, function(evt) {
        if (waitForUser) {
            // In wait mode, only SPACE or ESC end the test
            if (evt.unicode == 32 || evt.unicode == pdg.key_Escape) { // Space or ESC
                console.log("Ending test - closing all ports...");
                ports.forEach(function(portInfo) {
                    pdg.gfx.closeGraphicsPort(portInfo.port);
                });
                pdg.quit();
            }
        } else {
            // In auto mode, any key ends the test early
            console.log("Ending test early - closing all ports...");
            ports.forEach(function(portInfo) {
                pdg.gfx.closeGraphicsPort(portInfo.port);
            });
            pdg.quit();
        }
        return true; // We handled this event
    });
    return keyHandler;
}


// Start testing
if (numScreens > 0) {
    createAllPorts();
    var drawHandler = setupDrawHandler();
    var keyHandler = setupKeyHandler();
    
    console.log("All windows created and event handlers set up");
    
    if (waitForUser) {
        console.log("Windows will stay open until you press SPACE or ESC...");
    } else {
        console.log("Windows will stay open for 10 seconds...");
        
        // Test all screens for 10 seconds, then close all
        setTimeout(function() {
            console.log("Closing all windows...");
            ports.forEach(function(portInfo) {
                console.log("Closing window on screen", portInfo.screenNum);
                pdg.gfx.closeGraphicsPort(portInfo.port);
            });
            console.log("All screens tested successfully!");
            console.log("Test completed.");
            pdg.quit();
        }, 10000);
    }
} else {
    console.log("No screens detected!");
}

pdg.run();
