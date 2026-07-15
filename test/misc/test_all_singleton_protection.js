// Test singleton protection for all manager classes
var pdg = require('pdg');

console.log("Testing singleton protection for all manager classes...");

// Test all singleton managers that should be protected
var protectedManagers = [
    { name: "ConfigManager", singleton: "cfg" },
    { name: "LogManager", singleton: "lm" },
    { name: "EventManager", singleton: "evt" },
    { name: "ResourceManager", singleton: "res" },
    { name: "TimerManager", singleton: "tm" },
    { name: "GraphicsManager", singleton: "gfx" },
    { name: "SoundManager", singleton: "snd" }
];

// Test managers that should still allow new (FACADE classes)
var facadeManagers = [
    { name: "FileManager", singleton: "fs" }
];

console.log("\n=== Testing Protected Singleton Managers ===");

var protectedCount = 0;
var protectedPassed = 0;

protectedManagers.forEach(function(manager) {
    protectedCount++;
    console.log("\nTesting " + manager.name + "...");
    
    var singletonWorks = false;
    var newBlocked = false;
    var instanceofWorks = false;
    
    // Test 1: Singleton access works
    try {
        var singleton = pdg[manager.singleton];
        if (singleton && typeof singleton === 'object') {
            singletonWorks = true;
            console.log("  ✓ Singleton pdg." + manager.singleton + " accessible");
            
            // Test instanceof for singletons
            if (singleton instanceof pdg[manager.name] && singleton.constructor === pdg[manager.name]) {
                instanceofWorks = true;
                console.log("  ✓ instanceof and constructor checks work");
            } else {
                console.log("  ✗ instanceof or constructor check failed");
            }
        } else {
            console.log("  ✗ Singleton pdg." + manager.singleton + " not accessible");
        }
    } catch (e) {
        console.log("  ✗ Singleton access failed:", e.message);
    }
    
    // Test 2: new Constructor() is blocked
    try {
        var newInstance = new pdg[manager.name]();
        console.log("  ✗ ERROR: new " + manager.name + "() should have been blocked!");
    } catch (e) {
        if (e.message.includes("cannot be instantiated with 'new'")) {
            newBlocked = true;
            console.log("  ✓ new " + manager.name + "() correctly blocked");
        } else {
            console.log("  ✗ Unexpected error for new " + manager.name + "():", e.message);
        }
    }
    
    if (singletonWorks && newBlocked && instanceofWorks) {
        protectedPassed++;
        console.log("  ✅ " + manager.name + " protection working correctly");
    } else {
        console.log("  ❌ " + manager.name + " protection has issues");
    }
});

console.log("\n=== Testing Facade Managers (Should Allow new) ===");

var facadeCount = 0;
var facadePassed = 0;

facadeManagers.forEach(function(manager) {
    facadeCount++;
    console.log("\nTesting " + manager.name + " (should allow new)...");
    
    var singletonWorks = false;
    var newAllowed = false;
    
    // Test 1: Singleton access works
    try {
        var singleton = pdg[manager.singleton];
        if (singleton && typeof singleton === 'object') {
            singletonWorks = true;
            console.log("  ✓ Singleton pdg." + manager.singleton + " accessible");
        } else {
            console.log("  ✗ Singleton pdg." + manager.singleton + " not accessible");
        }
    } catch (e) {
        console.log("  ✗ Singleton access failed:", e.message);
    }
    
    // Test 2: new Constructor() is allowed
    try {
        var newInstance = new pdg[manager.name]();
        if (newInstance && typeof newInstance === 'object') {
            newAllowed = true;
            console.log("  ✓ new " + manager.name + "() works as expected");
        } else {
            console.log("  ✗ new " + manager.name + "() returned invalid object");
        }
    } catch (e) {
        console.log("  ✗ new " + manager.name + "() failed:", e.message);
    }
    
    if (singletonWorks && newAllowed) {
        facadePassed++;
        console.log("  ✅ " + manager.name + " facade behavior working correctly");
    } else {
        console.log("  ❌ " + manager.name + " facade behavior has issues");
    }
});

console.log("\n=== SUMMARY ===");
console.log("Protected Singleton Managers: " + protectedPassed + "/" + protectedCount + " working correctly");
console.log("Facade Managers: " + facadePassed + "/" + facadeCount + " working correctly");

if (protectedPassed === protectedCount && facadePassed === facadeCount) {
    console.log("🎉 ALL TESTS PASSED! Singleton protection implemented successfully.");
} else {
    console.log("⚠️  Some tests failed. Review the output above.");
} 