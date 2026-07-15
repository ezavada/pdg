// Simple test for Drawing JavaScript bindings
console.log("Testing Drawing JavaScript bindings...");

try {
    // Test createDrawing function
    console.log("Testing pdg.createDrawing()...");
    var drawing = pdg.createDrawing();
    console.log("✓ pdg.createDrawing() succeeded");
    
    // Test basic Drawing methods
    console.log("Testing getElementCount()...");
    var count = drawing.getElementCount();
    console.log("✓ getElementCount() succeeded, count:", count);
    
    console.log("Testing empty()...");
    var empty = drawing.empty();
    console.log("✓ empty() succeeded, empty:", empty);
    
    // Test adding a line
    console.log("Testing addLine()...");
    var point1 = {x: 10, y: 10};
    var point2 = {x: 50, y: 50};
    var elementRef = drawing.addLine(point1, point2);
    console.log("✓ addLine() succeeded");
    console.log("ElementRef object:", elementRef);
    
    // Test getElementCount again
    var newCount = drawing.getElementCount();
    console.log("New element count:", newCount);
    
    console.log("All Drawing binding tests passed! ✓");
    
} catch (error) {
    console.error("Drawing binding test failed:", error);
}
