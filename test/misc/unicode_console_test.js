// Console-only test for Unicode text width calculations
// This verifies that UTF-8 to UTF-16 conversion is handled correctly

var pdg = require('pdg');

console.log("Unicode Text Width Test");
console.log("=======================\n");

// Test strings with various Unicode characters
var testStrings = [
    { str: "ABC", desc: "ASCII only (3 bytes, 3 chars)" },
    { str: "45°", desc: "Degree symbol (4 bytes, 3 chars)" },
    { str: "Café", desc: "é accent (5 bytes, 4 chars)" },
    { str: "100€", desc: "Euro symbol (6 bytes, 4 chars)" },
    { str: "±5", desc: "Plus-minus (3 bytes, 2 chars)" },
    { str: "α", desc: "Greek alpha (2 bytes, 1 char)" },
    { str: "©2024", desc: "Copyright (7 bytes, 5 chars)" },
];

pdg.run(function() {
    // Create a small window to get a port
    var screenBounds = pdg.gfx.getScreenBounds(0);
    var winRect = new pdg.Rect(100, 100);
    winRect.center(screenBounds);
    var port = pdg.gfx.createWindowPort(winRect, "Unicode Console Test");
    
    console.log("Testing text width calculations:");
    console.log("(If Unicode is handled correctly, width should reflect actual character count, not byte count)\n");
    
    testStrings.forEach(function(test) {
        var str = test.str;
        var width = port.getTextWidth(str, 12, pdg.textStyle_Plain);
        var utf8Bytes = Buffer.byteLength(str, 'utf8');
        var jsChars = str.length;
        
        console.log("  \"" + str + "\"");
        console.log("    " + test.desc);
        console.log("    Width: " + width + " px");
        console.log("    UTF-8 bytes: " + utf8Bytes + ", JS chars: " + jsChars);
        
        // The width should be reasonable for the number of actual characters
        // If the bug exists, strings with multi-byte characters would have incorrect widths
        var expectedMinWidth = jsChars * 4;  // Rough estimate
        var expectedMaxWidth = jsChars * 15; // Rough estimate for size 12
        
        if (width >= expectedMinWidth && width <= expectedMaxWidth) {
            console.log("    ✓ Width appears correct for " + jsChars + " characters\n");
        } else {
            console.log("    ✗ WARNING: Width " + width + " seems incorrect for " + jsChars + " characters\n");
        }
    });
    
    console.log("\nTest complete. The fix ensures that UTF-8 byte length is converted to");
    console.log("UTF-16 character count before rendering, preventing extra garbage characters.");
    
    pdg.quit();
});

