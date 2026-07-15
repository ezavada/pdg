console.log("=== PDG Node.js Test ===");
console.log("PDG version:", process.versions.pdg);
console.log("PDG module:", process.pdg);
console.log("Node version:", process.versions.node);
console.log("V8 version:", process.versions.v8);
console.log("PDG module type:", typeof process.pdg);
console.log("PDG module keys:", Object.keys(process.pdg || {}));
console.log("All process.versions:", Object.keys(process.versions));
console.log("=== Test Complete ==="); 