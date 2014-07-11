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

describe("Serializer", function() {

  var ser;
  var des;
  var mem;
  var obj;

  beforeEach(function() {
    ser = new pdg.Serializer();
	des = new pdg.Deserializer();
  });

  it("can serialize basic data types", function() {
	console.log('* Testing Serialization...');
	pdg.setSerializationDebugMode(true);
    var tststr = 'this is a test';
	ser.serialize_1(-32);
	ser.serialize_1u(244); // 2
	ser.serialize_2(-31031)
	ser.serialize_2u(60006);  // 6
	ser.serialize_3u(700700);  // 9
	ser.serialize_4(-1000010000);
	ser.serialize_4u(4000040000); // 17
	ser.serialize_uint(0);
	ser.serialize_uint(251); // 19 bytes here
	
	ser.serialize_uint(5001);
	ser.serialize_uint(700001);
	ser.serialize_uint(4000000001);
	ser.serialize_str(tststr);

	var c = ser.serializedSize(5001);
	expect(c).toBe(3);
	c = ser.serializedSize(700001);
	expect(c).toBe(5);
	c = ser.serializedSize(4000000001);
	expect(c).toBe(5);
	c = ser.serializedSize(tststr);
	expect(c).toBe(18);

	c = ser.serializedSize(true);
	expect(c).toBe(1);
	c = ser.serializedSize(false);
	expect(c).toBe(0);
	c = ser.serializedSize(true);
	expect(c).toBe(0);
	c = ser.serializedSize(false);
	expect(c).toBe(0);
	c = ser.serializedSize(false);
	expect(c).toBe(0);
	c = ser.serializedSize(true);
	expect(c).toBe(0);
	c = ser.serializedSize(true);
	expect(c).toBe(0);
	c = ser.serializedSize(true);
	expect(c).toBe(0);
	c = ser.serializedSize(false);
	expect(c).toBe(1);
	ser.serialize_bool(true);
	ser.serialize_bool(false);
	ser.serialize_bool(true);
	ser.serialize_bool(false);
	ser.serialize_bool(false);
	ser.serialize_bool(true);
	ser.serialize_bool(true);
	ser.serialize_bool(true);
	ser.serialize_bool(false);
	var black = new Color('black');
	var teal = new Color('teal');
	teal.alpha = 0.5;
	c = ser.serializedSize(black);
	expect(c).toBe(3);
	c = ser.serializedSize(teal);
	expect(c).toBe(4);
	ser.serialize_color(black);
	ser.serialize_color(teal);
	var o = new Offset;
	c = ser.serializedSize(o);
	expect(c).toBe(0);
	ser.serialize_offset(o);
	o.y = 0.5;
	c = ser.serializedSize(o);
	expect(c).toBe(5);
	ser.serialize_offset(o);
	o.x = 10;
	o.y = 20;
	c = ser.serializedSize(o);
	expect(c).toBe(3);	
	ser.serialize_offset(o);
	var p = new Point(-200000, -67.85);
	c = ser.serializedSize(p);
	expect(c).toBe(8);
	ser.serialize_point(p);
	var v = new Vector(0.45, -0.45);
	c = ser.serializedSize(v);
	expect(c).toBe(8);
	ser.serialize_vector(v);
	var r = new Rect(100.5, -67.85, 120.5, -60.85);
	c = ser.serializedSize(r);
	expect(c).toBe(11);
	ser.serialize_rect(r);
	var r = new Rect(0, 0, 30, 30);
	c = ser.serializedSize(r);
	expect(c).toBe(3);
	ser.serialize_rect(r);

	pdg.setSerializationDebugMode(false);
	mem = ser.getDataPtr();
	var dataSize = mem.getDataSize();
	expect(dataSize).toBe(19 + 3 + 5 + 5 + 18 + 1 + 1 + 3 + 4 + 0 + 5 + 3 + 8 + 8 + 11 + 3);
// 	console.log('Stream 1:');
// 	console.binaryDump(mem.getData(), mem.getDataSize());
  });

  it("can deserialize those basic data types correctly", function() {
    des.setDataPtr(mem);
	var dat = -1;
	dat = des.deserialize_1(); 
	expect(dat).toBe(-32);
	dat = des.deserialize_1u(); 
	expect(dat).toBe(244);
	dat = des.deserialize_2(); 
	expect(dat).toBe(-31031)
	dat = des.deserialize_2u(); 
	expect(dat).toBe(60006);
	dat = des.deserialize_3u(); 
	expect(dat).toBe(700700);
	dat = des.deserialize_4(); 
	expect(dat).toBe(-1000010000);
	dat = des.deserialize_4u(); 
	expect(dat).toBe(4000040000);
	dat = des.deserialize_uint(); 
	expect(dat).toBe(0);
	dat = des.deserialize_uint(); 
	expect(dat).toBe(251);
	dat = des.deserialize_uint(); 
	expect(dat).toBe(5001);
	dat = des.deserialize_uint(); 
	expect(dat).toBe(700001);
	dat = des.deserialize_uint(); 
	expect(dat).toBe(4000000001);
	dat = des.deserialize_str(); 
	expect(dat).toBe('this is a test');
	dat = des.deserialize_bool();
	expect(dat).toBe(true);
	dat = des.deserialize_bool();
	expect(dat).toBe(false);
	dat = des.deserialize_bool();
	expect(dat).toBe(true);
	dat = des.deserialize_bool();
	expect(dat).toBe(false);
	dat = des.deserialize_bool();
	expect(dat).toBe(false);
	dat = des.deserialize_bool();
	expect(dat).toBe(true);
	dat = des.deserialize_bool();
	expect(dat).toBe(true);
	dat = des.deserialize_bool();
	expect(dat).toBe(true);
	dat = des.deserialize_bool();
	expect(dat).toBe(false);	
	var black = new Color('black');
	var teal = new Color('teal');
	teal.alpha = 0.5;
	dat = des.deserialize_color();
	expect(black.equals(dat)).toBeTruthy();
	dat = des.deserialize_color();
	expect(dat.alpha).toBeCloseTo(teal.alpha);
	expect(dat.red).toBeCloseTo(teal.red);
	expect(dat.green).toBeCloseTo(teal.green);
	expect(dat.blue).toBeCloseTo(teal.blue);
	dat = des.deserialize_offset();
	expect(dat.x).toBe(0);
	expect(dat.y).toBe(0);
	dat = des.deserialize_offset();
	expect(dat.x).toBe(0);
	expect(dat.y).toBe(0.5);
	dat = des.deserialize_offset();
	expect(dat.x).toBe(10);
	expect(dat.y).toBe(20);
	var p = new Point(-200000, -67.85);
	dat = des.deserialize_point();
	expect(dat.x).toBe(p.x);
	expect(dat.y).toBeCloseTo(p.y)
	var v = new Vector(0.45, -0.45);
	dat = des.deserialize_vector();
	expect(dat.x).toBeCloseTo(v.x);
	expect(dat.y).toBeCloseTo(v.y)
	var r = new Rect(100.5, -67.85, 120.5, -60.85);
	dat = des.deserialize_rect();
	expect(dat.top).toBeCloseTo(r.top);
	expect(dat.left).toBeCloseTo(r.left);
	expect(dat.right).toBeCloseTo(r.right);
	expect(dat.bottom).toBeCloseTo(r.bottom);
	var r = new Rect(0, 0, 30, 30);
	dat = des.deserialize_rect();
	expect(dat.top).toBeCloseTo(r.top);
	expect(dat.left).toBeCloseTo(r.left);
	expect(dat.right).toBeCloseTo(r.right);
	expect(dat.bottom).toBeCloseTo(r.bottom);
	
  });

  it("can serialize pdg.ISerializable objects", function() {

	classify(pdg.ISerializable, 'MySerializableClass', function() {
		def('getSerializedSize', function(serializer) {
			return 3;
		});
		def('serialize', function(serializer) {
			serializer.serialize_1u(15);
			serializer.serialize_2u(99);
		});
		def('deserialize', function(deserializer) {
			this.one = deserializer.deserialize_1u();
			this.two = deserializer.deserialize_2u();
		});
		def('getMyClassTag', function() {
			return 4068;
		});
	});
	obj = new MySerializableClass;
	pdg.registerSerializableClass(MySerializableClass);

	var c = ser.serializedSize(obj);
	expect(c).toBe(13);  // serialized object, big
	ser.serialize_obj(obj);
	mem = ser.getDataPtr();
	expect(mem.getDataSize()).toBe(c);
	var d = ser.serializedSize(obj);
	expect(d).toBe(4);   // reference, small
	ser.serialize_obj(obj);
	mem = ser.getDataPtr();
	expect(mem.getDataSize()).toBe(c+d);
// 	console.log('Stream 2:');
// 	console.binaryDump(mem.getData(), mem.getDataSize());
  });

  it("can deserialize an object correctly", function() {
    des.setDataPtr(mem);
    var obj2 = des.deserialize_obj();
    var obj3 = des.deserialize_obj();
	expect(typeof obj2).toBe("object");
	expect(obj2.one).toBe(15);
	expect(obj2.two).toBe(99);
	expect(obj2.__proto__).toBe(obj.__proto__);
	expect(obj2).toBe(obj3);
  });
  
//  it("can serialize recursive pdg.ISerializable objects", function() {
//  });
});