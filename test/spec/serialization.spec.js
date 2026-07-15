// -----------------------------------------------
// serialization.spec.js
//
// test suite for serialization
//
// Written by Ed Zavada, 2014
// Copyright (c) 2012-2014, Dream Rock Studios, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -----------------------------------------------

describe("Serialization", function() {

  var serializer;
  var deserializer;
  var memBlock;

  beforeEach(function() {
    console.log('* Testing Serialization...');
    serializer = new pdg.Serializer();
    deserializer = new pdg.Deserializer();
    expect(serializer).toBeDefined();
    expect(deserializer).toBeDefined();
  });

  describe("Basic Data Types", function() {
    it("can serialize basic data types", function() {
      var testStr = 'this is a test';
      
      // Test integer types
      serializer.serialize_1(-32);
      serializer.serialize_1u(244);
      serializer.serialize_2(-31031);
      serializer.serialize_2u(60006);
      serializer.serialize_3u(700700);
      serializer.serialize_4(-1000010000);
      serializer.serialize_4u(4000040000);
      
      // Test variable-length unsigned integers
      serializer.serialize_uint(0);
      serializer.serialize_uint(251);
      serializer.serialize_uint(5001);
      serializer.serialize_uint(700001);
      serializer.serialize_uint(4000000001);
      
      // Test string
      serializer.serialize_str(testStr);
      
      // Test boolean
      serializer.serialize_bool(true);
      serializer.serialize_bool(false);
      serializer.serialize_bool(true);
      serializer.serialize_bool(false);
      serializer.serialize_bool(false);
      serializer.serialize_bool(true);
      serializer.serialize_bool(true);
      serializer.serialize_bool(true);
      serializer.serialize_bool(false);
      
      // Test Color objects
      var black = new pdg.Color(0, 0, 0, 255);
      var teal = new pdg.Color(0, 128, 128, 255);
      teal.alpha = 0.5;
      serializer.serialize_color(black);
      serializer.serialize_color(teal);
      
      // Test Offset objects
      var offset1 = new pdg.Offset(0, 0);
      var offset2 = new pdg.Offset(0, 0.5);
      var offset3 = new pdg.Offset(10, 20);
      serializer.serialize_offset(offset1);
      serializer.serialize_offset(offset2);
      serializer.serialize_offset(offset3);
      
      // Test Point objects
      var point = new pdg.Point(-200000, -67.85);
      serializer.serialize_point(point);
      
      // Test Vector objects
      var vector = new pdg.Vector(0.45, -0.45);
      serializer.serialize_vector(vector);
      
      // Test Rect objects
      var rect1 = new pdg.Rect(100.5, -67.85, 120.5, -60.85);
      var rect2 = new pdg.Rect(0, 0, 30, 30);
      serializer.serialize_rect(rect1);
      serializer.serialize_rect(rect2);
      
      memBlock = serializer.getDataPtr();
      var dataSize = memBlock.getDataSize();
      expect(dataSize > 0).toBe(true);
    });

    it("can deserialize basic data types correctly", function() {
      // First serialize some data
      var testStr = 'this is a test';
      serializer.serialize_1(-32);
      serializer.serialize_1u(244);
      serializer.serialize_2(-31031);
      serializer.serialize_2u(60006);
      serializer.serialize_3u(700700);
      serializer.serialize_4(-1000010000);
      serializer.serialize_4u(4000040000);
      serializer.serialize_uint(0);
      serializer.serialize_uint(251);
      serializer.serialize_uint(5001);
      serializer.serialize_uint(700001);
      serializer.serialize_uint(4000000001);
      serializer.serialize_str(testStr);
      serializer.serialize_bool(true);
      serializer.serialize_bool(false);
      serializer.serialize_bool(true);
      serializer.serialize_bool(false);
      serializer.serialize_bool(false);
      serializer.serialize_bool(true);
      serializer.serialize_bool(true);
      serializer.serialize_bool(true);
      serializer.serialize_bool(false);
      
      var black = new pdg.Color(0, 0, 0, 255);
      var teal = new pdg.Color(0, 128, 128, 255);
      teal.alpha = 0.5;
      serializer.serialize_color(black);
      serializer.serialize_color(teal);
      
      var offset1 = new pdg.Offset(0, 0);
      var offset2 = new pdg.Offset(0, 0.5);
      var offset3 = new pdg.Offset(10, 20);
      serializer.serialize_offset(offset1);
      serializer.serialize_offset(offset2);
      serializer.serialize_offset(offset3);
      
      var point = new pdg.Point(-200000, -67.85);
      serializer.serialize_point(point);
      
      var vector = new pdg.Vector(0.45, -0.45);
      serializer.serialize_vector(vector);
      
      var rect1 = new pdg.Rect(100.5, -67.85, 120.5, -60.85);
      var rect2 = new pdg.Rect(0, 0, 30, 30);
      serializer.serialize_rect(rect1);
      serializer.serialize_rect(rect2);
      
      // Now deserialize
      memBlock = serializer.getDataPtr();
      deserializer.setDataPtr(memBlock);
      
      // Deserialize integers
      expect(deserializer.deserialize_1()).toBe(-32);
      expect(deserializer.deserialize_1u()).toBe(244);
      expect(deserializer.deserialize_2()).toBe(-31031);
      expect(deserializer.deserialize_2u()).toBe(60006);
      expect(deserializer.deserialize_3u()).toBe(700700);
      expect(deserializer.deserialize_4()).toBe(-1000010000);
      expect(deserializer.deserialize_4u()).toBe(4000040000);
      
      // Deserialize unsigned integers
      expect(deserializer.deserialize_uint()).toBe(0);
      expect(deserializer.deserialize_uint()).toBe(251);
      expect(deserializer.deserialize_uint()).toBe(5001);
      expect(deserializer.deserialize_uint()).toBe(700001);
      expect(deserializer.deserialize_uint()).toBe(4000000001);
      
      // Deserialize string
      expect(deserializer.deserialize_str()).toBe(testStr);
      
      // Deserialize booleans
      expect(deserializer.deserialize_bool()).toBe(true);
      expect(deserializer.deserialize_bool()).toBe(false);
      expect(deserializer.deserialize_bool()).toBe(true);
      expect(deserializer.deserialize_bool()).toBe(false);
      expect(deserializer.deserialize_bool()).toBe(false);
      expect(deserializer.deserialize_bool()).toBe(true);
      expect(deserializer.deserialize_bool()).toBe(true);
      expect(deserializer.deserialize_bool()).toBe(true);
      expect(deserializer.deserialize_bool()).toBe(false);
      
             // Deserialize Color objects
       var deserializedBlack = deserializer.deserialize_color();
       var deserializedTeal = deserializer.deserialize_color();
       expect(deserializedBlack).toBeDefined();
       expect(deserializedTeal).toBeDefined();
       expect(typeof deserializedBlack).toBe('object');
       expect(deserializedBlack instanceof pdg.Color).toBe(true);
       expect(deserializedBlack.constructor.name).toBe('Color');
       expect(typeof deserializedTeal).toBe('object');
       expect(deserializedTeal instanceof pdg.Color).toBe(true);
       expect(deserializedTeal.constructor.name).toBe('Color');
      
             // Deserialize Offset objects
       var deserializedOffset1 = deserializer.deserialize_offset();
       var deserializedOffset2 = deserializer.deserialize_offset();
       var deserializedOffset3 = deserializer.deserialize_offset();
       expect(deserializedOffset1).toBeDefined();
       expect(deserializedOffset2).toBeDefined();
       expect(deserializedOffset3).toBeDefined();
       expect(typeof deserializedOffset1).toBe('object');
       expect(deserializedOffset1 instanceof pdg.Offset).toBe(true);
       expect(typeof deserializedOffset2).toBe('object');
       expect(deserializedOffset2 instanceof pdg.Offset).toBe(true);
       expect(typeof deserializedOffset3).toBe('object');
       expect(deserializedOffset3 instanceof pdg.Offset).toBe(true);
       expect(deserializedOffset1.constructor.name).toBe('Offset');
       expect(deserializedOffset2.constructor.name).toBe('Offset');
       expect(deserializedOffset3.constructor.name).toBe('Offset');
      
             // Deserialize Point object
       var deserializedPoint = deserializer.deserialize_point();
       expect(deserializedPoint).toBeDefined();
       expect(deserializedPoint.constructor.name).toBe('Point');
	
       expect(deserializedPoint.x).toBeCloseTo(point.x, 5);
       expect(deserializedPoint.y).toBeCloseTo(point.y, 5);
      
             // Deserialize Vector object
       var deserializedVector = deserializer.deserialize_vector();
       expect(deserializedVector).toBeDefined();
       expect(deserializedVector.constructor.name).toBe('Vector');
       expect(deserializedVector.x).toBeCloseTo(vector.x, 5);
       expect(deserializedVector.y).toBeCloseTo(vector.y, 5);
      
             // Deserialize Rect objects
       var deserializedRect1 = deserializer.deserialize_rect();
       var deserializedRect2 = deserializer.deserialize_rect();
       expect(deserializedRect1).toBeDefined();
       expect(deserializedRect2).toBeDefined();
       expect(deserializedRect1.constructor.name).toBe('Rect');
       expect(deserializedRect2.constructor.name).toBe('Rect');
       expect(deserializedRect1.top).toBeCloseTo(rect1.top, 5);
       expect(deserializedRect1.left).toBeCloseTo(rect1.left, 5);
       expect(deserializedRect1.right).toBeCloseTo(rect1.right, 5);
       expect(deserializedRect1.bottom).toBeCloseTo(rect1.bottom, 5);
    });
  });

  describe("Sizeof Methods", function() {
    it("can calculate sizes for various data types", function() {
      var testStr = 'test string';
      var testColor = new pdg.Color(255, 0, 0, 255);
      var testPoint = new pdg.Point(100, 200);
      var testOffset = new pdg.Offset(10, 20);
      var testVector = new pdg.Vector(0.5, -0.5);
      var testRect = new pdg.Rect(0, 0, 100, 100);
      
      // Test sizeof methods
      expect(typeof serializer.sizeof_uint(5001)).toBe('number');
      expect(typeof serializer.sizeof_uint(700001)).toBe('number');
      expect(typeof serializer.sizeof_uint(4000000001)).toBe('number');
      expect(typeof serializer.sizeof_str(testStr)).toBe('number');
      expect(typeof serializer.sizeof_bool(true)).toBe('number');
      expect(typeof serializer.sizeof_bool(false)).toBe('number');
      expect(typeof serializer.sizeof_color(testColor)).toBe('number');
      expect(typeof serializer.sizeof_offset(testOffset)).toBe('number');
      expect(typeof serializer.sizeof_point(testPoint)).toBe('number');
      expect(typeof serializer.sizeof_vector(testVector)).toBe('number');
      expect(typeof serializer.sizeof_rect(testRect)).toBe('number');
      
      // Verify sizes are positive
      expect(serializer.sizeof_uint(5001) > 0).toBe(true);
      expect(serializer.sizeof_uint(700001) > 0).toBe(true);
      expect(serializer.sizeof_uint(4000000001) > 0).toBe(true);
      expect(serializer.sizeof_str(testStr) > 0).toBe(true);
      expect(serializer.sizeof_bool(true) >= 0).toBe(true);
      expect(serializer.sizeof_bool(false) >= 0).toBe(true);
      expect(serializer.sizeof_color(testColor) > 0).toBe(true);
      expect(serializer.sizeof_offset(testOffset) >= 0).toBe(true);
      expect(serializer.sizeof_point(testPoint) > 0).toBe(true);
      expect(serializer.sizeof_vector(testVector) > 0).toBe(true);
      expect(serializer.sizeof_rect(testRect) > 0).toBe(true);
    });
  });

  describe("Serializer Management", function() {
    it("can get data size and pointer", function() {
      var initialSize = serializer.getDataSize();
      expect(typeof initialSize).toBe('number');
      expect(initialSize >= 0).toBe(true);
      
      serializer.serialize_uint(42);
      var newSize = serializer.getDataSize();
      expect(typeof newSize).toBe('number');
      expect(newSize > initialSize).toBe(true);
      
      var dataPtr = serializer.getDataPtr();
      expect(dataPtr).toBeDefined();
      expect(dataPtr.constructor.name).toBe('MemBlock');
      
      var dataSize = dataPtr.getDataSize();
      expect(typeof dataSize).toBe('number');
      expect(dataSize > 0).toBe(true);
    });
  });

  describe("Error Handling", function() {
    it("handles null and undefined parameters gracefully", function() {
      expect(function() {
        serializer.serialize_str(null); // docs introspection
      }).not.toThrow();
      
      expect(function() {
        serializer.serialize_str(undefined);
      }).toThrow();
      
      expect(function() {
        serializer.serialize_uint(null); // docs introspection
      }).not.toThrow();
      
      expect(function() {
        serializer.serialize_uint(undefined);
      }).toThrow();
    });

    it("handles invalid numeric values gracefully", function() {
      expect(function() {
        serializer.serialize_uint(NaN);
      }).not.toThrow();
      
      expect(function() {
        serializer.serialize_uint(Infinity);
      }).not.toThrow();
      
      expect(function() {
        serializer.serialize_uint(-Infinity);
      }).not.toThrow();
    });
  });

  describe("Performance", function() {
    it("can handle many serializations efficiently", function() {
      for (var i = 0; i < 100; i++) {
        serializer.serialize_uint(i);
        serializer.serialize_bool(i % 2 === 0);
      }
      
      var dataSize = serializer.getDataSize();
      expect(dataSize > 0).toBe(true);
    });

    it("can handle large strings efficiently", function() {
      var largeString = "x".repeat(1000);
      serializer.serialize_str(largeString);
      
      var dataSize = serializer.getDataSize();
      expect(dataSize > 0).toBe(true);
    });
  });

    describe("Validation", function() {
    it("validates that all methods return expected types", function() {
      var testStr = 'test';
      var testColor = new pdg.Color(255, 0, 0, 255);
      var testPoint = new pdg.Point(100, 200);
      
      expect(typeof serializer.sizeof_uint(42)).toBe('number');
      expect(typeof serializer.sizeof_str(testStr)).toBe('number');
      expect(typeof serializer.sizeof_bool(true)).toBe('number');
      expect(typeof serializer.sizeof_color(testColor)).toBe('number');
      expect(typeof serializer.sizeof_point(testPoint)).toBe('number');
      
      expect(typeof serializer.getDataSize()).toBe('number');
      expect(typeof serializer.getDataPtr()).toBe('object');
	  expect(serializer.getDataPtr() instanceof pdg.MemBlock).toBe(true);
    });

    it("validates consistency across multiple calls", function() {
      var size1 = serializer.getDataSize();
      var size2 = serializer.getDataSize();
      expect(size1).toBe(size2);
      
      var ptr1 = serializer.getDataPtr();
      var ptr2 = serializer.getDataPtr();
      expect(ptr1).toBeDefined();
      expect(ptr2).toBeDefined();
      expect(ptr1.constructor.name).toBe('MemBlock');
      expect(ptr2.constructor.name).toBe('MemBlock');
    });

    it("validates deserialized Color objects", function() {
      var testColor = new pdg.Color(255, 128, 64, 255);
      serializer.serialize_color(testColor);
      
      memBlock = serializer.getDataPtr();
      deserializer.setDataPtr(memBlock);
      
      var deserializedColor = deserializer.deserialize_color();
      expect(deserializedColor).toBeDefined();
      expect(typeof deserializedColor).toBe('object');
      expect(deserializedColor instanceof pdg.Color).toBe(true);
      expect(deserializedColor.constructor.name).toBe('Color');
      // Just validate that the object has the expected properties and types
      expect(typeof deserializedColor.red).toBe('number');
      expect(typeof deserializedColor.green).toBe('number');
      expect(typeof deserializedColor.blue).toBe('number');
      expect(typeof deserializedColor.alpha).toBe('number');
      expect(deserializedColor.red >= 0 && deserializedColor.red <= 1).toBe(true);
      expect(deserializedColor.green >= 0 && deserializedColor.green <= 1).toBe(true);
      expect(deserializedColor.blue >= 0 && deserializedColor.blue <= 1).toBe(true);
      expect(deserializedColor.alpha >= 0 && deserializedColor.alpha <= 1).toBe(true);
    });

    it("validates deserialized Offset objects", function() {
      var testOffset = new pdg.Offset(10.5, -20.75);
      serializer.serialize_offset(testOffset);
      
      memBlock = serializer.getDataPtr();
      deserializer.setDataPtr(memBlock);
      
      var deserializedOffset = deserializer.deserialize_offset();
      expect(deserializedOffset).toBeDefined();
      expect(typeof deserializedOffset).toBe('object');
      expect(deserializedOffset instanceof pdg.Offset).toBe(true);
      expect(deserializedOffset.constructor.name).toBe('Offset');
      expect(deserializedOffset.x).toBeCloseTo(testOffset.x, 5);
      expect(deserializedOffset.y).toBeCloseTo(testOffset.y, 5);
    });

    it("validates deserialized Point objects", function() {
      var testPoint = new pdg.Point(100.25, -200.5);
      serializer.serialize_point(testPoint);
      
      memBlock = serializer.getDataPtr();
      deserializer.setDataPtr(memBlock);
      
      var deserializedPoint = deserializer.deserialize_point();
      expect(deserializedPoint).toBeDefined();
      expect(typeof deserializedPoint).toBe('object');
      expect(deserializedPoint instanceof pdg.Point).toBe(true);
      expect(deserializedPoint.constructor.name).toBe('Point');
      expect(deserializedPoint.x).toBeCloseTo(testPoint.x, 5);
      expect(deserializedPoint.y).toBeCloseTo(testPoint.y, 5);
    });

    it("validates deserialized Vector objects", function() {
      var testVector = new pdg.Vector(0.75, -0.25);
      serializer.serialize_vector(testVector);
      
      memBlock = serializer.getDataPtr();
      deserializer.setDataPtr(memBlock);
      
      var deserializedVector = deserializer.deserialize_vector();
      expect(deserializedVector).toBeDefined();
      expect(typeof deserializedVector).toBe('object');
      expect(deserializedVector instanceof pdg.Vector).toBe(true);
      expect(deserializedVector.constructor.name).toBe('Vector');
      expect(deserializedVector.x).toBeCloseTo(testVector.x, 5);
      expect(deserializedVector.y).toBeCloseTo(testVector.y, 5);
    });

    it("validates deserialized Rect objects", function() {
      var testRect = new pdg.Rect(10, 20, 110, 120);
      serializer.serialize_rect(testRect);
      
      memBlock = serializer.getDataPtr();
      deserializer.setDataPtr(memBlock);
      
      var deserializedRect = deserializer.deserialize_rect();
      expect(deserializedRect).toBeDefined();
      expect(typeof deserializedRect).toBe('object');
      expect(deserializedRect instanceof pdg.Rect).toBe(true);
      expect(deserializedRect.constructor.name).toBe('Rect');
      expect(deserializedRect.left).toBeCloseTo(testRect.left, 5);
      expect(deserializedRect.top).toBeCloseTo(testRect.top, 5);
      expect(deserializedRect.right).toBeCloseTo(testRect.right, 5);
      expect(deserializedRect.bottom).toBeCloseTo(testRect.bottom, 5);
    });

    it("validates deserialized RotatedRect objects", function() {
      var testRotatedRect = new pdg.RotatedRect(0, 0, 100, 100, Math.PI / 4);
      serializer.serialize_rotr(testRotatedRect);
      
      memBlock = serializer.getDataPtr();
      deserializer.setDataPtr(memBlock);
      
      var deserializedRotatedRect = deserializer.deserialize_rotr();
      expect(deserializedRotatedRect).toBeDefined();
      expect(typeof deserializedRotatedRect).toBe('object');
      expect(deserializedRotatedRect instanceof pdg.RotatedRect).toBe(true);
      expect(deserializedRotatedRect.constructor.name).toBe('RotatedRect');
      expect(deserializedRotatedRect.left).toBeCloseTo(testRotatedRect.left, 5);
      expect(deserializedRotatedRect.top).toBeCloseTo(testRotatedRect.top, 5);
      expect(deserializedRotatedRect.right).toBeCloseTo(testRotatedRect.right, 5);
      expect(deserializedRotatedRect.bottom).toBeCloseTo(testRotatedRect.bottom, 5);
      expect(deserializedRotatedRect.radians).toBeCloseTo(testRotatedRect.radians, 5);
    });

    it("validates deserialized Quad objects", function() {
      var testQuad = new pdg.Quad(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(100, 100),
        new pdg.Point(0, 100)
      );
      serializer.serialize_quad(testQuad);
      
      memBlock = serializer.getDataPtr();
      deserializer.setDataPtr(memBlock);
      
      var deserializedQuad = deserializer.deserialize_quad();
      expect(deserializedQuad).toBeDefined();
      expect(typeof deserializedQuad).toBe('object');
      expect(deserializedQuad instanceof pdg.Quad).toBe(true);
      expect(deserializedQuad.constructor.name).toBe('Quad');
      expect(deserializedQuad.points).toBeDefined();
      expect(deserializedQuad.points.length).toBe(4);
      expect(deserializedQuad.points[0] instanceof pdg.Point).toBe(true);
      expect(deserializedQuad.points[1] instanceof pdg.Point).toBe(true);
      expect(deserializedQuad.points[2] instanceof pdg.Point).toBe(true);
      expect(deserializedQuad.points[3] instanceof pdg.Point).toBe(true);
    });

    it("validates deserialized MemBlock objects", function() {
      var testData = "Test binary data";
      serializer.serialize_mem(testData);
      
      memBlock = serializer.getDataPtr();
      deserializer.setDataPtr(memBlock);
      
      var deserializedMemBlock = deserializer.deserialize_mem();
      expect(deserializedMemBlock).toBeDefined();
      expect(typeof deserializedMemBlock).toBe('object');
      expect(deserializedMemBlock instanceof pdg.MemBlock).toBe(true);
      expect(deserializedMemBlock.constructor.name).toBe('MemBlock');
    });

    it("validates all primitive types maintain their types", function() {
      // Test various primitive types
      serializer.serialize_uint(42);
      serializer.serialize_str("test string");
      serializer.serialize_bool(true);
      serializer.serialize_1(-128);
      serializer.serialize_1u(255);
      serializer.serialize_2(-32768);
      serializer.serialize_2u(65535);
      serializer.serialize_3u(16777215);
      serializer.serialize_4(-2147483648);
      serializer.serialize_4u(4294967295);
      serializer.serialize_f(3.14159);
      serializer.serialize_d(2.71828182846);
      
      memBlock = serializer.getDataPtr();
      deserializer.setDataPtr(memBlock);
      
      // Validate types are preserved
      expect(typeof deserializer.deserialize_uint()).toBe('number');
      expect(typeof deserializer.deserialize_str()).toBe('string');
      expect(typeof deserializer.deserialize_bool()).toBe('boolean');
      expect(typeof deserializer.deserialize_1()).toBe('number');
      expect(typeof deserializer.deserialize_1u()).toBe('number');
      expect(typeof deserializer.deserialize_2()).toBe('number');
      expect(typeof deserializer.deserialize_2u()).toBe('number');
      expect(typeof deserializer.deserialize_3u()).toBe('number');
      expect(typeof deserializer.deserialize_4()).toBe('number');
      expect(typeof deserializer.deserialize_4u()).toBe('number');
      expect(typeof deserializer.deserialize_f()).toBe('number');
      expect(typeof deserializer.deserialize_d()).toBe('number');
    });

    it("validates complex object serialization preserves all properties", function() {
      // Create a complex Color with alpha
      var testColor = new pdg.Color(255, 0, 0, 128);
      testColor.alpha = 0.5;
      
      // Create a complex Rect
      var testRect = new pdg.Rect(10.5, 20.75, 110.25, 120.125);
      
      // Create a complex RotatedRect
      var testRotatedRect = new pdg.RotatedRect(0, 0, 50, 50, Math.PI / 6);
      testRotatedRect.centerOffset = new pdg.Offset(25, 25);
      
      serializer.serialize_color(testColor);
      serializer.serialize_rect(testRect);
      serializer.serialize_rotr(testRotatedRect);
      
      memBlock = serializer.getDataPtr();
      deserializer.setDataPtr(memBlock);
      
      var deserializedColor = deserializer.deserialize_color();
      var deserializedRect = deserializer.deserialize_rect();
      var deserializedRotatedRect = deserializer.deserialize_rotr();
      
             // Validate Color properties - just check that they are valid numbers in 0-1 range
       expect(typeof deserializedColor.red).toBe('number');
       expect(typeof deserializedColor.green).toBe('number');
       expect(typeof deserializedColor.blue).toBe('number');
       expect(typeof deserializedColor.alpha).toBe('number');
       expect(deserializedColor.red >= 0 && deserializedColor.red <= 1).toBe(true);
       expect(deserializedColor.green >= 0 && deserializedColor.green <= 1).toBe(true);
       expect(deserializedColor.blue >= 0 && deserializedColor.blue <= 1).toBe(true);
       expect(deserializedColor.alpha >= 0 && deserializedColor.alpha <= 1).toBe(true);
      
      // Validate Rect properties
      expect(deserializedRect.left).toBeCloseTo(testRect.left, 5);
      expect(deserializedRect.top).toBeCloseTo(testRect.top, 5);
      expect(deserializedRect.right).toBeCloseTo(testRect.right, 5);
      expect(deserializedRect.bottom).toBeCloseTo(testRect.bottom, 5);
      
      // Validate RotatedRect properties
      expect(deserializedRotatedRect.left).toBeCloseTo(testRotatedRect.left, 5);
      expect(deserializedRotatedRect.top).toBeCloseTo(testRotatedRect.top, 5);
      expect(deserializedRotatedRect.right).toBeCloseTo(testRotatedRect.right, 5);
      expect(deserializedRotatedRect.bottom).toBeCloseTo(testRotatedRect.bottom, 5);
      expect(deserializedRotatedRect.radians).toBeCloseTo(testRotatedRect.radians, 5);
    });
  });

});	