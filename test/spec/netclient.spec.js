// -----------------------------------------------
// netclient.spec.js
//
// test suite for NetClient
//
// Written by Ed Zavada, 2012
// Copyright (c) 2012, Dream Rock Studios, LLC
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
	describe("NetClient", function() {
	  it("is not present", function() {
	  	expect(pdg.NetClient).toBeUndefined();
	  });
	});

} else {

describe("NetClient", function() {

  it("can be created with name and key", function() {
	console.log('* Testing NetClient...');
  	var client = new pdg.NetClient();
 	expect(client).toBeDefined();
  });

  it("can chain calls", function() {
  	var client = new pdg.NetClient();
	client.onError(function() {}).connect(function() {}, { addr: "localhost", port: 5454 });
  });

  it("can have an error handler assigned", function() {
  	var client = new pdg.NetClient();
  	var myHandler = function(error) {};
	expect(client._errorCallback).toBeFalsy();
 	client.onError(myHandler);
	expect(client._errorCallback).toBe(myHandler);
  });


if (typeof process != 'undefined') {
	// the net client connectivity can't be tested in the browser
	// at this point because it requires Node.js's net module

  it("returns an error if connection fails", function() {
  
  	var client = new pdg.NetClient();
	expect(client._errorCallback).toBeFalsy();
  	var errorMsg = '';
  	var errorCalled = false;
  	var connectCalled = false;
 	var myHandler = function(error) {
			errorCalled = true;
			errorMsg = error; 	
		};
  	
  	runs(function() {
  		client.onError(myHandler);
		expect(client._errorCallback).toBe(myHandler);
		client.connect({ host: '127.0.0.1', port: 9999 }, function() {
			connectCalled = true;
		});
	});
	
	waitsFor(function() {
		return errorCalled || connectCalled;
	}, "the error callback to be called", 1000);
	
	runs(function() {
  		expect(errorCalled).toBeTruthy();
  		expect(errorMsg.length).not.toBe(0);
  		expect(connectCalled).toBeFalsy();
  	});

  });

  it("returns a NetConnection on success", function() {
  
  	var client = new pdg.NetClient();
  	var errorMsg = '';
  	var errorCalled = false;
  	var connectCalled = false;
  	var netConnection = false;
 	var myHandler = function(error) {
			errorCalled = true;
		};
  	
  	runs(function() {
  		client.onError(myHandler);
		client.connect({ host: '127.0.0.1', port: 1337 }, function(connection) {
			connectCalled = true;
			netConnection = connection;
		});
	});
	
	waitsFor(function() {
		return errorCalled || connectCalled;
	}, "the connect callback to be called", 1000);
	
	runs(function() {
  		expect(connectCalled).toBeTruthy();
  		expect(errorCalled).toBeFalsy();
  		expect(netConnection).not.toBeFalsy();
  		expect(netConnection.remoteAddr).toBe('127.0.0.1');
  		expect(netConnection.remotePort).toBe(1337);
  		expect(netConnection.localAddr).toBe('127.0.0.1');
  		expect(netConnection.localPort).toBeDefined();
  		expect(netConnection.localPort).not.toBe(0);
  		netConnection.close();
  	});
  });

  xit("can do handshake to connect to a NetServer", function() {
  
  	var client = new pdg.NetClient();
  	var errorMsg = '';
  	var errorCalled = false;
  	var connectCalled = false;
  	var netConnection = false;
 	var myHandler = function(error) {
			errorCalled = true;
		};
  	
  	runs(function() {
  		client.onError(myHandler);
		client.connect(function(connection) {
			connectCalled = true;
			netConnection = connection;
		}, { ip: '127.0.0.1', port: 1337 });
	});
	
	waitsFor(function() {
		return errorCalled || connectCalled;
	}, "the connect callback to be called", 1000);
	
	runs(function() {
  		expect(connectCalled).toBeTruthy();
  		expect(errorCalled).toBeFalsy();
  		expect(netConnection).not.toBeFalsy();
  		expect(netConnection.remoteAddr).toBe('127.0.0.1');
  		expect(netConnection.remotePort).toBe(1337);
  		expect(netConnection.localAddr).toBe('127.0.0.1');
  		expect(netConnection.localPort).toBeDefined();
  		expect(netConnection.localPort).not.toBe(0);
  		netConnection.close();
  	});

  });

}

});

}