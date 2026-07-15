// Standalone Font Drawing Test Script
// This script tests various font and text drawing capabilities in PDG

console.log("=== STANDALONE FONT DRAWING TEST SCRIPT ===");
console.log("Testing font and text drawing functionality...");

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
var testFonts = [];
var currentTest = 0;
var frameCount = 0;

// Test configuration
var testDuration = 4000; // 4 seconds per test
var frameDelay = 100; // 100ms between frames for animation tests
var testTimeout = null;

// Function to load test fonts
function loadTestFonts() {
    console.log("Loading test fonts...");
    
    try {
        // Load different font types
        var arial = pdg.gfx.createFont("Arial");
        var times = pdg.gfx.createFont("Times New Roman");
        var courier = pdg.gfx.createFont("Courier New");
        var helvetica = pdg.gfx.createFont("Helvetica");
        var arialScaled = pdg.gfx.createFont("Arial", 1.5); // 50% larger
        
        testFonts = [
            { font: arial, name: "Arial", scaling: 1.0 },
            { font: times, name: "Times New Roman", scaling: 1.0 },
            { font: courier, name: "Courier New", scaling: 1.0 },
            { font: helvetica, name: "Helvetica", scaling: 1.0 },
            { font: arialScaled, name: "Arial (1.5x)", scaling: 1.5 }
        ];
        
        console.log("Loaded fonts:");
        testFonts.forEach(function(fontInfo, index) {
            console.log("  Font " + index + ": " + fontInfo.name + " (scaling: " + fontInfo.scaling + ")");
        });
        
        return true;
    } catch (e) {
        console.log("ERROR: Failed to load test fonts:", e);
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
        var port = pdg.gfx.createWindowPort(windowRect, "PDG Font Drawing Test - Screen " + screenNum);
        
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
        port.drawText("PDG Font Drawing Test - Screen " + screenNum, titlePoint, textAttrs);
        
        // Draw frame counter
        var frameText = "Frame: " + portInfo.frameCount + " (Global: " + frameCount + ")";
        var framePoint = new pdg.Point(10, 20);
        var textAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Plain).fillColor("yellow");
        port.drawText(frameText, framePoint, textAttrs);
        
        // Draw current test info
        var testText = "Test: " + (currentTest + 1) + "/6";
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
                runFontComparisonTest(port);
                break;
            case 1:
                runTextStyleTest(port);
                break;
            case 2:
                runFontSizeTest(port);
                break;
            case 3:
                runFontMetricsTest(port);
                break;
            case 4:
                runTextAlignmentTest(port);
                break;
            case 5:
                runFontScalingTest(port);
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

// Test 1: Font comparison
function runFontComparisonTest(port) {
    var testTitle = "Font Comparison Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var startY = 100;
    var lineHeight = 30;
    var leftMargin = 50;
    
    testFonts.forEach(function(fontInfo, index) {
        var y = startY + index * lineHeight;
        var textPoint = new pdg.Point(leftMargin, y);
        
        // Set the font for this port
        port.setFont(fontInfo.font);
        
        // Draw font name and sample text
        var sampleText = fontInfo.name + " - The quick brown fox jumps over the lazy dog";
        var textAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText(sampleText, textPoint, textAttrs);
    });
    
    // Add Unicode character test section
    var unicodeY = startY + testFonts.length * lineHeight + 40;
    var unicodeTitlePoint = new pdg.Point(leftMargin, unicodeY);
    var textAttrs = new pdg.Attributes().textSize(18).textStyle(pdg.textStyle_Bold).fillColor("yellow");
    port.drawText("Unicode Character Test:", unicodeTitlePoint, textAttrs);
    
    var unicodeStrings = [
        "Math: ±5 ≈3.14 ≠0 ≤10 ≥5",
        "Symbols: ° © ® ™ § ¶ † € £ ¥ ¢",
        "Greek: α β γ δ ε θ λ π σ ω",
        "Accents: Café résumé naïve",
        "Cyrillic: Здравствуйте",
        "Arabic: السلام عليكم",
        "Hebrew: שלום עולם",
        "Japanese: こんにちは",
        "Korean: 안녕하세요",
        "Thai: สวัสดี",
        "Mandarin: 你好",
        "Mixed: Hello こんにちは 안녕하세요 สวัสดี 你好 Здравствуйте Hello",
        // Note: Emoji (😀 🌍 🚀 🎉 etc.) are not supported - they require:
        // 1. Apple Color Emoji font
        // 2. Color glyph rendering (current system uses grayscale)
    ];
    
    unicodeStrings.forEach(function(str, index) {
        var y = unicodeY + (index + 1) * 25 + 10;
        var textPoint = new pdg.Point(leftMargin + 20, y);
        var textAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText(str, textPoint, textAttrs);
    });
    
    // Reset to default font
    port.setFont();
}

// Test 2: Text styles
function runTextStyleTest(port) {
    var testTitle = "Text Style Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var font = testFonts[0].font; // Use Arial
    port.setFont(font);
    
    var startY = 100;
    var lineHeight = 40;
    var leftMargin = 50;
    
    var styles = [
        { style: pdg.textStyle_Plain, name: "Plain", color: "white" },
        { style: pdg.textStyle_Bold, name: "Bold", color: "yellow" },
        { style: pdg.textStyle_Italic, name: "Italic", color: "cyan" },
        { style: pdg.textStyle_Underline, name: "Underline", color: "lime" },
        { style: pdg.textStyle_Bold + pdg.textStyle_Italic, name: "Bold + Italic", color: "orange" },
        { style: pdg.textStyle_Bold + pdg.textStyle_Underline, name: "Bold + Underline", color: "magenta" },
        { style: pdg.textStyle_Italic + pdg.textStyle_Underline, name: "Italic + Underline", color: "aqua" },
        { style: pdg.textStyle_Bold + pdg.textStyle_Italic + pdg.textStyle_Underline, name: "Bold + Italic + Underline", color: "red" }
    ];
    
    styles.forEach(function(styleInfo, index) {
        var y = startY + index * lineHeight;
        var textPoint = new pdg.Point(leftMargin, y);
        
        var sampleText = styleInfo.name + " - Sample text with this style";
        var textAttrs = new pdg.Attributes().textSize(18).textStyle(styleInfo.style).fillColor(styleInfo.color);
        port.drawText(sampleText, textPoint, textAttrs);
    });
    
    // Reset to default font
    port.setFont();
}

// Test 3: Font sizes
function runFontSizeTest(port) {
    var testTitle = "Font Size Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var font = testFonts[0].font; // Use Arial
    port.setFont(font);
    
    var startY = 100;
    var leftMargin = 50;
    var currentY = startY;
    
    var sizes = [8, 12, 16, 20, 24, 32, 48, 64];
    
    sizes.forEach(function(size) {
        var textPoint = new pdg.Point(leftMargin, currentY);
        var sampleText = "Size " + size + " - The quick brown fox jumps over the lazy dog";
        var textAttrs = new pdg.Attributes().textSize(size).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText(sampleText, textPoint, textAttrs);
        
        // Calculate next Y position based on font height
        var fontHeight = font.getFontHeight(size);
        currentY += fontHeight + 5; // Add some spacing
    });
    
    // Reset to default font
    port.setFont();
}

// Test 4: Font metrics
function runFontMetricsTest(port) {
    var testTitle = "Font Metrics Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var font = testFonts[0].font; // Use Arial
    port.setFont(font);
    
    for (var i = 0; i < testFonts.length; i++) {
        var startY = 100 + i * 200;
        var leftMargin = 50;
        if (i > 2) {
            leftMargin = 500;
            startY -= 600;
        }
        var currentY = startY;
        var testSize = 24;
        font = testFonts[i].font;
        port.setFont(font);
                
        // Get font metrics
        var height = font.getFontHeight(testSize);
        var ascent = font.getFontAscent(testSize);
        var descent = font.getFontDescent(testSize);
        var leading = font.getFontLeading(testSize);
        
        // Draw metrics information
        var metricsText = [
            "Font: " + font.getFontName(),
            "Size: " + testSize,
            "Height: " + height.toFixed(1),
            "Ascent: " + ascent.toFixed(1),
            "Descent: " + descent.toFixed(1),
            "Leading: " + leading.toFixed(1)
        ];
        
        var j = 0;
        metricsText.forEach(function(text) {
            j++;
            var textPoint = new pdg.Point(leftMargin, currentY);
            var textAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText(text, textPoint, textAttrs);
            currentY += 25;
            if (j == 3) {
                currentY -= 75;
                leftMargin += 180;
            }
        });
        leftMargin -= 180;
        
        // Draw a visual representation of the metrics
        currentY += 20;
        var baselineY = currentY + ascent;
        var topY = currentY;
        var bottomY = currentY + height;
        
        // Draw baseline
        var attrs = new pdg.Attributes().lineStyle(pdg.lineStyle_Solid).lineColor(new pdg.Color("cyan"));
        port.drawLine(new pdg.Point(leftMargin, baselineY), new pdg.Point(leftMargin + 300, baselineY), attrs);

        var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("cyan");
        port.drawText("Baseline", new pdg.Point(leftMargin + 310, baselineY), textAttrs);
        
        // Draw ascent line
        port.drawLine(new pdg.Point(leftMargin, topY), new pdg.Point(leftMargin + 300, topY), attrs.lineColor(new pdg.Color("green")));
        var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("green");
        port.drawText("Ascent", new pdg.Point(leftMargin + 310, topY - 5), textAttrs);
        
        // Draw descent line
        port.drawLine(new pdg.Point(leftMargin, bottomY), new pdg.Point(leftMargin + 300, bottomY), attrs.lineColor(new pdg.Color("red")));
        var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor("red");
        port.drawText("Descent", new pdg.Point(leftMargin + 310, bottomY + 12), textAttrs);
        
        // Draw sample text on the baseline
        var textAttrs = new pdg.Attributes().textSize(testSize).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText("Sample Text", new pdg.Point(leftMargin, baselineY), textAttrs);
    }

    // Reset to default font
    port.setFont();

}

// Test 5: Text alignment
function runTextAlignmentTest(port) {
    var testTitle = "Text Alignment Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var font = testFonts[0].font; // Use Arial
    port.setFont(font);
    
    var centerX = port.getDrawingArea().width() / 2;
    var startY = 120;
    var lineHeight = 40;
    
    var alignments = [
        { style: pdg.textStyle_LeftJustified, name: "Left Justified", color: "white" },
        { style: pdg.textStyle_Centered, name: "Centered", color: "yellow" },
        { style: pdg.textStyle_RightJustified, name: "Right Justified", color: "cyan" }
    ];
    
    alignments.forEach(function(alignInfo, index) {
        var y = startY + index * lineHeight;
        var textPoint = new pdg.Point(centerX, y);
        
        var sampleText = alignInfo.name + " - This text is " + alignInfo.name.toLowerCase();
        var textAttrs = new pdg.Attributes().textSize(18).textStyle(alignInfo.style).fillColor(alignInfo.color);
        port.drawText(sampleText, textPoint, textAttrs);
    });
    
    // Draw alignment guide
    var guideY = startY - 10;
    var attrs = new pdg.Attributes().lineStyle(pdg.lineStyle_Solid).lineColor(new pdg.Color("gray"));
    port.drawLine(new pdg.Point(centerX, guideY - 20), new pdg.Point(centerX, guideY + 120), attrs);
    
    // Reset to default font
    port.setFont();
}

// Test 6: Font scaling
function runFontScalingTest(port) {
    var testTitle = "Font Scaling Test";
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 60);
    var textAttrs = new pdg.Attributes().textSize(20).textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold).fillColor("yellow");
        port.drawText(testTitle, titlePoint, textAttrs);
    
    var startY = 100;
    var lineHeight = 40;
    var leftMargin = 50;
    
    // Test different scaling factors
    var scalingFactors = [0.5, 0.75, 1.0, 1.25, 1.5, 2.0];
    
    scalingFactors.forEach(function(scale, index) {
        var y = startY + index * lineHeight;
        var textPoint = new pdg.Point(leftMargin, y);
        
        // Create a font with this scaling factor
        var scaledFont = pdg.gfx.createFont("Arial", scale);
        port.setFont(scaledFont);
        
        var sampleText = "Scaling " + scale + "x - The quick brown fox jumps over the lazy dog";
        var textAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Plain).fillColor("white");
        port.drawText(sampleText, textPoint, textAttrs);
    });
    
    // Reset to default font
    port.setFont();
}

function runNextTest() {
    if (currentTest >= 6) {
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
    console.log("Starting test " + (currentTest + 1) + "/6");
    
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
    if (loadTestFonts()) {
        var drawHandler = setupDrawHandler();
        var keyHandler = setupKeyHandler();
        startTestSequence();
    } else {
        console.log("Failed to load test fonts. Exiting.");
        pdg.quit();
    }
} else {
    console.log("No screens detected!");
    pdg.quit();
}

pdg.run();
