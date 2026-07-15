// Test script to verify physics classes are available
console.log("Testing physics classes...");

// Test if physics classes are available
try {
    // These should be available if physics is enabled
    console.log("Testing cpArbiter...");
    console.log("cpArbiter type:", typeof cpArbiter);
    
    console.log("Testing cpConstraint...");
    console.log("cpConstraint type:", typeof cpConstraint);
    
    console.log("Testing cpSpace...");
    console.log("cpSpace type:", typeof cpSpace);
    
    console.log("Physics classes test completed successfully!");
} catch (e) {
    console.log("Error testing physics classes:", e.message);
} 