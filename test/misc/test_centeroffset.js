// Simple test to verify centerOffset property on RotatedRect
console.log("JS_DEBUG: Creating RotatedRect...");
var rotatedRect = new pdg.RotatedRect(0, 0, 50, 50, Math.PI/4);
console.log("JS_DEBUG: RotatedRect created, setting centerOffset...");
rotatedRect.centerOffset = new pdg.Offset(25, 25);
console.log("JS_DEBUG: centerOffset set");

console.log("Original RotatedRect:");
console.log("  left:", rotatedRect.left);
console.log("  top:", rotatedRect.top);
console.log("  width:", rotatedRect.width());
console.log("  height:", rotatedRect.height());
console.log("  radians:", rotatedRect.radians);
console.log("  centerOffset:", rotatedRect.centerOffset);
console.log("  centerOffset.x:", rotatedRect.centerOffset.x);
console.log("  centerOffset.y:", rotatedRect.centerOffset.y);

// Test serialization and deserialization
console.log("JS_DEBUG: Starting serialization...");
var serializer = new pdg.Serializer();
console.log("JS_DEBUG: Calling serialize_rotr...");
serializer.serialize_rotr(rotatedRect);
console.log("JS_DEBUG: Serialization complete, getting data pointer...");
var memBlock = serializer.getDataPtr();

console.log("JS_DEBUG: Starting deserialization...");
var deserializer = new pdg.Deserializer();
deserializer.setDataPtr(memBlock);
console.log("JS_DEBUG: Calling deserialize_rotr...");
var deserializedRotatedRect = deserializer.deserialize_rotr();
console.log("JS_DEBUG: Deserialization complete");

console.log("\nDeserialized RotatedRect:");
console.log("  left:", deserializedRotatedRect.left);
console.log("  top:", deserializedRotatedRect.top);
console.log("  width:", deserializedRotatedRect.width());
console.log("  height:", deserializedRotatedRect.height());
console.log("  radians:", deserializedRotatedRect.radians);
console.log("  centerOffset:", deserializedRotatedRect.centerOffset);
console.log("JS_DEBUG: Checking centerOffset property...");
if (deserializedRotatedRect.centerOffset) {
    console.log("  centerOffset.x:", deserializedRotatedRect.centerOffset.x);
    console.log("  centerOffset.y:", deserializedRotatedRect.centerOffset.y);
    console.log("JS_DEBUG: centerOffset is defined and accessible");
} else {
    console.log("  centerOffset is undefined!");
    console.log("JS_DEBUG: centerOffset is undefined - this is the bug!");
}
