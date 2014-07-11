// -----------------------------------------------
// netserver.spec.js
//
// test suite for NetServer
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

if ((process.env.PDG_DEBUG && process.env.PDG_DEBUG.indexOf('NET_') != -1)
  || (process.env.NODE_DEBUG && process.env.NODE_DEBUG.indexOf('NET_') != -1)) {
	console.log('Found NODE_DEBUG or PDG_DEBUG=NET_CONNECT (or NET_DATA) in environment. Logging network tests.');
	NET_TEST_LOG = function(msg) {
		console.log(msg);
	};
} else {
 	NET_TEST_LOG = function(msg) {};
}

if (pdg.hasNetwork == false) {

	// non-network build (ie: current iOS build)
	describe("NetServer", function() {
	  it("is not present", function() {
	  	expect(pdg.NetServer).toBeUndefined();
	  });
	});

} else {

describe("NetServer", function() {

  it("can be created with name and key and info", function() {
	console.log('* Testing NetServer... (export PDG_DEBUG=NET_DATA for verbose logging)');
  	var server = new pdg.NetServer({ port : 5757 } );
 	expect(server.serverInfo).toBeDefined();
 	expect(server.serverInfo.port).toBeDefined();
 	expect(server.serverInfo.port).toEqual(5757);
  });

  it("can chain calls", function() {
  	var server = new pdg.NetServer();
	server.onError(function() {}).shutdown();
  });

  it("can have an error handler assigned", function() {
  	var server = new pdg.NetServer();
  	var myHandler = function(error) {};
	expect(server._errorCallback).toBeFalsy();
 	server.onError(myHandler);
	expect(server._errorCallback).toBe(myHandler);
  });

  it("returns an error if opening the listen port fails", function() {
  
 	var server = new pdg.NetServer( { fixedPort : true } );
	expect(server._errorCallback).toBeFalsy();
  	var errorMsg = '';
  	var errorCalled = false;
  	var connectCalled = false;
 	var myHandler = function(error) {
			errorCalled = true;
			errorMsg = error; 	
		};
	
  	// attempt to connect to port 1337, which should already be in use by 
  	// the echo server that we use to test client connectivity
  	runs(function() {
  		server.onError(myHandler);
		expect(server._errorCallback).toBe(myHandler);
		server.serverPort = 1337;
		server.serverAddr = '127.0.0.1';
//		server._fixedPort = true;
		server.listen(function() {
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
 	
  }); // end of it returns an error if opening the port fails

  describe("when server is listening", function() {

	var server;
	var errorMsg;
	var errorCalled;
	var connectCalled;
	var myErrorHandler;
	var myConnectHandler;
	var connectCount;
	var serverErrCount;

	beforeEach(function() {
		myErrorHandler = function(error) {
			NET_TEST_LOG('got server error '+JSON.stringify(error));
			errorCalled = true;
			errorMsg = error;
			serverErrCount++;
		};
		myConnectHandler = function(connection) {
			connectCalled = true;
			connectCount++;
			return true; // allow the connection
		};
		server = new pdg.NetServer({noDatagram: true});
		server.onError(myErrorHandler);
		server.listen(myConnectHandler);
		connectCount = 0;
		connectCalled = false;
		serverErrCount = 0;
		errorCalled = false;
		errorMsg = false;
	});

	afterEach(function() {
	    runs(function() {
			NET_TEST_LOG('#### calling server shutdown');
			server.shutdown(true, true); // close connections and kill them
			NET_TEST_LOG('#### server shutdown called');
		});
		waitsFor(function() {
			var result = !server.listening && (server.connections.length == 0) && (server._dgramSock === false);
			if (result) {
				NET_TEST_LOG('#### server shutdown complete');
			}
			return result;
		}, "the server to shut down", 2000);
	});

		
	  it("sets the listening flag", function() {
		runs(function() {
			expect(server.listening).toBeFalsy();
			expect(server.allowDatagram).toBeFalsy();
		});
		waitsFor(function() {
			return errorCalled || connectCalled || server.listening;
		}, "the listening flag to be set", 1000);
		runs(function() {
			expect(server.listening).toBeTruthy();
			expect(errorCalled).toBeFalsy();
			expect(connectCalled).toBeFalsy();
		});
	  }); // end of it sets the listening flag
	
	  it("doesn't do connect callback until handshake complete", function() {
		NET_TEST_LOG('----------- waits for handshake check ----------');
	  	var clientTcpConnect = 0;
		waitsFor(function() {
			return server.listening;
		}, "the listening flag to be set", 1000);
		runs(function() {
			var client = require('net').connect({port: 5000}, function() {
			 //'connect' listener
				NET_TEST_LOG('client tcp connect');
				clientTcpConnect++;
			});
		});
		waitsFor(function() {
			return clientTcpConnect == 1;
		}, "the connection callback to be called", 1000);
		runs(function() {
			expect(server.listening).toBeTruthy();
			expect(errorCalled).toBeFalsy();
			expect(connectCalled).toBeFalsy();
			expect(clientTcpConnect).toBe(1);
			expect(server.connections.length).toBe(0);
		});
	  }); // doesn't do connect callback until handshake complete
	  

	  it("does timeout if handshake takes too long", function() {
		NET_TEST_LOG('----------- timeout check ----------');
	  	var clientTcpConnect = 0;
	  	var clientTcpClose = 0;
		waitsFor(function() {
			return server.listening;
		}, "the listening flag to be set", 1000);
		runs(function() {
			server.handshakeTimeout = 100; // 100ms timeout
			var client = require('net').connect({port: 5000}, function() {
			 //'connect' listener
				NET_TEST_LOG('client tcp connect');
				clientTcpConnect++;
			}).on('close', function() {
				NET_TEST_LOG('client tcp close');
				clientTcpClose++;
			});
		});
		waitsFor(function() {
			return ((clientTcpConnect >= 1) && (clientTcpClose >= 1));
		}, "the connection and close callbacks to be called", 1000);
		runs(function() {
			expect(server.listening).toBeTruthy();
			expect(errorCalled).toBeFalsy();
			expect(connectCalled).toBeFalsy();
			expect(clientTcpConnect).toBe(1);
			expect(server.connections.length).toBe(0);
		});
	  }); // does timeout if handshake takes too long


	  it("creates a NetConnection for each incoming connection after handshake", function() {
		NET_TEST_LOG('----------- handshake check ----------');
	  	var clientConnect = 0;
		waitsFor(function() {
			return server.listening;
		}, "the listening flag to be set", 1000);
		runs(function() {
			// create 5 connections
			for (var i = 0; i<5; i++) {
				var client = new pdg.NetClient();
				client.connect({port: 5000}, function() {
					NET_TEST_LOG('client connected');
					clientConnect++;
				});
			}
		});
		waitsFor(function() {
			return errorCalled || connectCount == 5;
		}, "the connection callback to be called", 1000);
		runs(function() {
			expect(server.listening).toBeTruthy();
			expect(errorCalled).toBeFalsy();
			expect(connectCalled).toBeTruthy();
			expect(server.connections.length).toBe(5);
		});
	  }); // creates a NetConnection for each incoming connection


	  it("can require reservations", function() {
		NET_TEST_LOG('----------- reservation require check ----------');
		var clientErr = 0;
		var clientClose = 0;
		var clientEnd = 0;
		var clientConnect = 0;
		waitsFor(function() {
			return server.listening;
		}, "the listening flag to be set", 1000);
		runs(function() {
			server.reservationRequired = true;
			// create 5 connections
			for (var i = 0; i<5; i++) {
				var client = require('net').connect({port: 5000}, function() {
				 //'connect' listener
					NET_TEST_LOG('client connected');
					clientConnect++;
				}).on('error', function(msg) {
					NET_TEST_LOG('client error '+JSON.stringify(msg));
					clientErr++;
				}).on('close', function(hasErr) {
					NET_TEST_LOG('client close '+( hasErr ? JSON.stringify(hasErr) : ''));
					clientClose++;
				}).on('end', function(msg) {
					NET_TEST_LOG('client end');
					clientEnd++;
				});
			}
		});
		waitsFor(function() {
			return ((clientClose + clientErr) == 5);
		}, "the client connections to succeed or fail", 1000);
		runs(function() {
			expect(server.listening).toBeTruthy();
			expect(errorCalled).toBeFalsy();
			expect(connectCalled).toBeFalsy();
			expect(clientErr).toEqual(0);
			expect(clientEnd).toEqual(5);
			expect(clientClose).toEqual(5);
			expect(connectCount).toEqual(0);
			expect(server.connections.length).toEqual(0);
		});
	  }); // creates a NetConnection for each incoming connection


	  it("can accept clients with reservations", function() {
		NET_TEST_LOG('----------- reservation accept check ----------');
		var clientErr = 0;
		var clientConnect = 0;
		var client;
		waitsFor(function() {
			return server.listening;
		}, "the listening flag to be set", 1000);
		runs(function() {
			server.reservationRequired = true;
			// create 6 connections
			for (var i = 0; i<6; i++) {
				if (i < 2) { // only the first 3 will succeed
					// expect a client with a particular key, from localhost
					// reservation ttl = 10 seconds and the reservation is single use
					server.expectClient('abc123'+i, '127.0.0.1', 10000, true);
				} else if (i == 2) {
					// test key-only reservation (not IP restricted)
					server.expectClient('abc123'+i, '*', 10000, true);
				} else if (i == 3) {
					// test expired reservation
					server.expectClient('abc123'+i, '127.0.0.1', -10, true);
				} else if (i == 4) {
					// test ip address mismatch
					server.expectClient('abc123'+i, '128.0.1.1', 10000, true);
				} else if (i == 5) {
					// test key mismatch
					server.expectClient('xyz987'+i, '127.0.0.1', 10000, true);
				}
				var clientKey = 'abc123'+i;
				client = new pdg.NetClient();
				client.connect({port: 5000}, function(nc) {
					NET_TEST_LOG('NetClient(2) connected');
					clientConnect++;
					nc.send('test');
				}, clientKey).onError(function(msg) {
					NET_TEST_LOG('NetClient(2) error '+JSON.stringify(msg));
					clientErr++;
				});
			}
		});
		waitsFor(function() {
			return ((clientConnect + serverErrCount + clientErr) >= 6);
		}, "the client connections to succeed or fail", 1000);
		runs(function() {
			expect(server.listening).toBeTruthy();
			expect(errorCalled).toBeTruthy();
			expect(serverErrCount).toEqual(3);
			expect(errorMsg.code).toBe('ERR_BAD_CLIENT_KEY');
			expect(connectCalled).toBeTruthy();
			expect(connectCount).toEqual(3);
			expect(clientConnect).toEqual(3);
			expect(clientErr).toEqual(0);
			expect(server.connections.length).toEqual(3);
		});
	  }); // creates a NetConnection for each incoming connection


	  it("can establish UDP communications with a NetClient", function() {
		var clientErr = 0;
		var clientConnect = 0;
		var client;
		var clientMessageCount = 0;
		var serverMessageCount = 0;
		var clientUdpCount = 0;
		runs(function() {
			NET_TEST_LOG('----------- udp check ----------');
			server.allowDatagram = true;
		});
		waitsFor(function() {
			return (server.listening && server._dgramAlive);
		}, "the listening flag and udp socket alive to be set", 1000);
		runs(function() {
			expect(server._dgramAlive).toBeTruthy();
			client = new pdg.NetClient();
			client.connect({port: 5000}, function(nc) {
				NET_TEST_LOG('NetClient(3) connected');
				clientConnect++;
				nc.send('test');
			}).onError(function(msg) {
				NET_TEST_LOG('NetClient(3) error '+JSON.stringify(msg));
				clientErr++;
			});
		});
		waitsFor(function() {
			return ((clientConnect + serverErrCount + clientErr) >= 1);
		}, "the client connections to succeed or fail", 1000);
		runs(function() {
			expect(server.listening).toBeTruthy();
			expect(errorCalled).toBeFalsy();
			expect(serverErrCount).toEqual(0);
			expect(connectCalled).toBeTruthy();
			expect(connectCount).toEqual(1);
			expect(clientConnect).toEqual(1);
			expect(clientErr).toEqual(0);
			expect(server.connections.length).toEqual(1);
		});
		waitsFor(function() {
			return (client.connection && client.connection.hasDgram && server.connections[0] && server.connections[0].hasDgram);
		}, "datagram communications to be established", 1000);
		runs(function() {
			expect(server.connections[0].hasDgram).toBeTruthy();
			expect(client.connection.hasDgram).toBeTruthy();
			server.connections[0].onMessage(function(data, conn, method) {
				NET_TEST_LOG('Server got message from '+conn.remoteAddr+' on '+conn.localPort+'/'+method+': '+JSON.stringify(data));
				serverMessageCount++;
				if (method == 'udp') {
					conn.sendDgram(data);
				} else {
					conn.send(data);
				}
			});
			client.connection.onMessage(function(data, conn, method) {
				NET_TEST_LOG('Client got message from '+conn.remoteAddr+' on '+conn.localPort+'/'+method+': '+JSON.stringify(data));
				clientMessageCount++;
				if (method == 'udp') {
					clientUdpCount++;
				}
			});
			client.connection.send('test tcp string');
			client.connection.sendDgram('test udp string');
		});
		waitsFor(function() {
			return (clientMessageCount == 2);
		}, "the server to echo what the client sends", 1000);
		runs(function() {
			expect(serverMessageCount).toEqual(2);
			expect(clientUdpCount).toEqual(1);
		});

	  }); // creates a NetConnection for each incoming connection

	}); // end describe when server is listening

});

}
