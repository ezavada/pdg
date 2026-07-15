// Test singleton protection for all protected managers
var pdg = require('pdg');

console.log("Testing singleton protection for ALL protected managers...");

var protectedManagers = [
    { name: "TimerManager", singleton: "tm" },
    { name: "ConfigManager", singleton: "cfg" },
    { name: "ResourceManager", singleton: "res" },
    { name: "LogManager", singleton: "lm" },
    { name: "GraphicsManager", singleton: "gfx" },
    { name: "SoundManager", singleton: "snd" }
];

var passedCount = 0;

protectedManagers.forEach(function(manager) {
    console.log("\n=== " + manager.name + " ===");
    
    var singletonWorks = false;
    var newBlocked = false;
    var instanceofWorks = false;
    
    // Test 1: Singleton access works
    try {
        var singleton = pdg[manager.singleton];
        if (singleton && typeof singleton === 'object') {
            singletonWorks = true;
            console.log("✓ pdg." + manager.singleton + " accessible");
            
            // Test instanceof
            if (singleton instanceof pdg[manager.name] && singleton.constructor === pdg[manager.name]) {
                instanceofWorks = true;
                console.log("✓ instanceof and constructor checks work");
            } else {
                console.log("✗ instanceof or constructor check failed");
            }
        } else {
            console.log("✗ pdg." + manager.singleton + " not accessible");
        }
    } catch (e) {
        console.log("✗ Singleton access failed:", e.message);
    }
    
    // Test 2: new Constructor() is blocked
    try {
        var newInstance = new pdg[manager.name]();
        console.log("✗ ERROR: new " + manager.name + "() should have been blocked!");
    } catch (e) {
        if (e.message.includes("cannot be instantiated with 'new'")) {
            newBlocked = true;
            console.log("✓ new " + manager.name + "() correctly blocked");
        } else {
            console.log("✗ Unexpected error:", e.message);
        }
    }
    
    if (singletonWorks && newBlocked && instanceofWorks) {
        passedCount++;
        console.log("✅ " + manager.name + " protection working correctly");
    } else {
        console.log("❌ " + manager.name + " protection has issues");
    }
});

// Test that EventManager still allows new (known incompatible manager)
console.log("\n=== EventManager (known incompatible - should still allow new) ===");
try {
    var evt = pdg.evt;
    console.log("✓ pdg.evt accessible");
    
    var newEvt = new pdg.EventManager();
    console.log("✓ new EventManager() still works (incompatible with protection)");
} catch (e) {
    console.log("✗ EventManager test failed:", e.message);
}

// Test that FileManager still allows new (FACADE class)
console.log("\n=== FileManager (FACADE class - should still allow new) ===");
try {
    var fs = pdg.fs;
    console.log("✓ pdg.fs accessible");
    
    var newFs = new pdg.FileManager();
    console.log("✓ new FileManager() still works (FACADE class)");
} catch (e) {
    console.log("✗ FileManager test failed:", e.message);
}

console.log("\n🎯 === FINAL SUMMARY ===");
console.log("Protected singleton managers: " + passedCount + "/" + protectedManagers.length + " working correctly");
console.log("Unprotected managers:");
console.log("  - EventManager: Known incompatible with protection (allows new)");
console.log("  - FileManager: FACADE class (allows new)");

if (passedCount === protectedManagers.length) {
    console.log("\n🎉 SUCCESS! All compatible singleton managers are protected!");
    console.log("Singleton pattern enforcement successfully implemented!");
} else {
    console.log("\n⚠️  Some singleton managers failed protection tests.");
} 