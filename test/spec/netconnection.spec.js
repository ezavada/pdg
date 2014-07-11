// -----------------------------------------------
// netconnection.spec.js
//
// test suite for NetConnection
//
// Written by Ed Zavada, 2013
// Copyright (c) 2012-2013, Dream Rock Studios, LLC
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

if (pdg.hasNetwork == false) {

	// non-network build (ie: current iOS build)
	describe("NetConnection", function() {
	  it("is not present", function() {
	  	expect(pdg.NetConnection).toBeUndefined();
	  });
	});

} else {

describe("NetConnection", function() {

  var client;
  var errorMsg;
  var errorCalled;
  var connectCalled;
  var netConnection;
  var myErrorHandler;
  var myMessageHandler;
  var myCloseHandler;
  var receiveCalled;
  var msgReceived;
  var closeCalled;

  beforeEach(function() {
  	client = new pdg.NetClient();
  	errorMsg = '';
  	errorCalled = false;
  	connectCalled = false;
  	netConnection = false;
  	msgReceived = undefined;
  	receiveCalled = false;
  	closeCalled = false;
 	myErrorHandler = function(error) {
			errorCalled = true;
		};
 	myMessageHandler = function(msg) {
			receiveCalled = true;
			msgReceived = msg;
//			console.log('GOT: '+msg);
		};
 	myCloseHandler = function() {	
// 			console.log('GOT CLOSE!!');
			closeCalled = true;
		};
  	
  	runs(function() {
  		client.onError(myErrorHandler);
		client.connect({ host: '127.0.0.1', port: 1337 }, function(connection) {
			connectCalled = true;
			netConnection = connection;
		});
	});
	
	waitsFor(function() {
		return errorCalled || connectCalled;
	}, "the connect callback to be called", 1000);
  });

  afterEach(function() {
    if (netConnection) {
    	netConnection.close();
    }
  });

  it("is created upon successful connection", function() {
	runs(function() {
		console.log('* Testing NetConnection...');
  		expect(connectCalled).toBeTruthy();
  		expect(errorCalled).toBeFalsy();
  		expect(netConnection).not.toBeFalsy();
  		expect(netConnection.remoteAddr).toBe('127.0.0.1');
  		expect(netConnection.remotePort).toBe(1337);
  		expect(netConnection.localAddr).toBe('127.0.0.1');
  		expect(netConnection.localPort).toBeDefined();
  		expect(netConnection.localPort).not.toBe(0);
  	});
  });

  it("can send and receive strings", function() {
  	runs(function() {
  		netConnection.onClose(myCloseHandler);
  		netConnection.onMessage(myMessageHandler);
  		netConnection.send("Test String 123 Blue 42");
  	});
  	waitsFor(function() {
  		return errorCalled || receiveCalled;
  	}, "the echo server to respond", 1000);
	runs(function() {
  		expect(receiveCalled).toBeTruthy();
  		expect(errorCalled).toBeFalsy();
//  		expect(closeCalled).toBeFalsy();
  		expect(msgReceived).toBe("Test String 123 Blue 42");
	});
  });

  it("can send and receive object data", function() {
  	var c = new pdg.Color(1.0, 0, 1.0);
  	runs(function() {
  		netConnection.onClose(myCloseHandler);
  		netConnection.onMessage(myMessageHandler);
  		netConnection.send(c);
  	});
  	waitsFor(function() {
  		return errorCalled || receiveCalled;
  	}, "the echo server to respond", 1000);
	runs(function() {
  		expect(receiveCalled).toBeTruthy();
  		expect(errorCalled).toBeFalsy();
//  		expect(closeCalled).toBeFalsy();
  		expect(typeof msgReceived).toBe("object");
  		expect(msgReceived.red).toBe(c.red);
  		expect(msgReceived.green).toBe(c.green);
  		expect(msgReceived.blue).toBe(c.blue);
//  		expect(msgReceived.__proto__).toBe(c.__proto__);
	});
  });
 
  xit("can send and receive pdg MemBlocks", function() {
  	var mem = new pdg.MemBlock();
  	runs(function() {
  		netConnection.onClose(myCloseHandler);
  		netConnection.onMessage(myMessageHandler);
  		netConnection.send();
  	});
  	waitsFor(function() {
  		return errorCalled || receiveCalled;
  	}, "the echo server to respond", 1000);
	runs(function() {
  		expect(receiveCalled).toBeTruthy();
  		expect(errorCalled).toBeFalsy();
//  		expect(closeCalled).toBeFalsy();
  		expect(msgReceived).toBe();
	});
  });

  it("can send and receive Node.js Buffers", function() {
  	var buf = new Buffer('A test of the Buffer sending');
  	runs(function() {
  		netConnection.onClose(myCloseHandler);
  		netConnection.onMessage(myMessageHandler);
  		netConnection.send(buf);
  	});
  	waitsFor(function() {
  		return errorCalled || receiveCalled;
  	}, "the echo server to respond", 1000);
	runs(function() {
  		expect(receiveCalled).toBeTruthy();
  		expect(errorCalled).toBeFalsy();
//  		expect(closeCalled).toBeFalsy();
  		expect(typeof msgReceived).toBe("object");
  		expect(Buffer.isBuffer(msgReceived)).toBeTruthy();
  		expect(msgReceived.length).toBe(buf.length);
  		expect(msgReceived.inspect()).toBe(buf.inspect());
	});
  });

  it("can send and receive pdg.ISerializable objects", function() {

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
	var obj = new MySerializableClass;
	pdg.registerSerializableClass(MySerializableClass);

  	runs(function() {
  		netConnection.onClose(myCloseHandler);
  		netConnection.onMessage(myMessageHandler);
  		netConnection.send(obj);
  	});
  	waitsFor(function() {
  		return errorCalled || receiveCalled;
  	}, "the echo server to respond", 1000);
	runs(function() {
  		expect(receiveCalled).toBeTruthy();
  		expect(errorCalled).toBeFalsy();
//  		expect(closeCalled).toBeFalsy();
  		expect(typeof msgReceived).toBe("object");
  		expect(msgReceived.one).toBe(15);
  		expect(msgReceived.two).toBe(99);
  		expect(msgReceived.__proto__).toBe(obj.__proto__);
	});
  });

});

}