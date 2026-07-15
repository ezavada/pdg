// Test script for Drawing JavaScript bindings
console.log("Testing Drawing JavaScript bindings...");

try {
    // First, let's see what functions are available
    console.log("Available global functions:");
    var globalFunctions = Object.getOwnPropertyNames(global).filter(name => 
        typeof global[name] === 'function' && name.includes('Drawing')
    );
    console.log("Functions containing 'Drawing':", globalFunctions);
    
    // Also check for createDrawing specifically
    console.log("createDrawing exists:", typeof createDrawing);
    
    // Test createDrawing function if it exists
    if (typeof createDrawing === 'function') {
        console.log("Testing createDrawing()...");
        var drawing = createDrawing();
        console.log("✓ createDrawing() succeeded");
        console.log("Drawing object:", drawing);
        
        // Test basic Drawing methods
        console.log("Testing getElementCount()...");
        var count = drawing.getElementCount();
        console.log("✓ getElementCount() succeeded, count:", count);
        
        console.log("Testing isEmpty()...");
        var empty = drawing.isEmpty();
        console.log("✓ isEmpty() succeeded, empty:", empty);
        
        console.log("All Drawing binding tests passed! ✓");
    } else {
        console.log("createDrawing function not found in global scope");
        console.log("Available global functions:", Object.getOwnPropertyNames(global).filter(name => 
            typeof global[name] === 'function'
        ));
    }
    
} catch (error) {
    console.error("Drawing binding test failed:", error);
    console.error("Error stack:", error.stack);
}