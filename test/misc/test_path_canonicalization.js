var pdg = require('pdg');

console.log("Testing path canonicalization...");

// Test the path that's failing
var testPath = "../deps/scml-pp/samples/wonkyskeleton/wonkyskeleton.scml";
console.log("Original path:", testPath);

// Get the application directory
var appDir = pdg.getFileManager().getApplicationDirectory();
console.log("Application directory:", appDir);

// Get the application resource directory
var resDir = pdg.getFileManager().getApplicationResourceDirectory();
console.log("Application resource directory:", resDir);

// Test different path variations
var testPaths = [
    "../deps/scml-pp/samples/wonkyskeleton/wonkyskeleton.scml",
    "./deps/scml-pp/samples/wonkyskeleton/wonkyskeleton.scml",
    "deps/scml-pp/samples/wonkyskeleton/wonkyskeleton.scml",
    "/deps/scml-pp/samples/wonkyskeleton/wonkyskeleton.scml"
];

testPaths.forEach(function(path) {
    console.log("\nTesting path:", path);
    var resMgr = pdg.getResourceManager();
    var refNum = resMgr.openResourceFile(path);
    console.log("Resource file ref num:", refNum);
    
    // Get the resource paths
    var paths = resMgr.getResourcePaths();
    console.log("Resource paths:", paths);
    
    // Try to get the resource size
    var size = resMgr.getResourceSize("wonkyskeleton.scml");
    console.log("Resource size:", size);
});

console.log("\nTest complete.");
