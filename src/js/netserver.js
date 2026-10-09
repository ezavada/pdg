// -----------------------------------------------
// netserver.js
//
// Server side implementation of pdg network interface
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

// this is one of the few javascript files that are built-in
// to the pdg standalone app but also part of the pure 
// javascript implementation


var net = require('net');
var dgram = require('dgram');

var NET_SERVER_LOG;

if ((process.env.PDG_DEBUG && process.env.PDG_DEBUG.indexOf('NET_') != -1)
  || (process.env.NODE_DEBUG && process.env.NODE_DEBUG.indexOf('NET_') != -1)) {
	console.log('Found NODE_DEBUG or PDG_DEBUG=NET_CONNECT (or NET_DATA) in environment. Logging network connections.');
	NET_SERVER_LOG = function(msg) {
		console.log(msg);
	};
} else {
 	NET_SERVER_LOG = function(msg) {};
}

// @pdg-class {"name":"NetServer"}
class NetServer {
	//! new NetServer(serverInfo): create a network server for your game
	//! /param opts the options for the server
// @pdg-member {"name":"NetServer.NetServer","type":"constructor","brief":"create a network server","returns":"object NetServer","params":[{"name":"opts","type":"object","optional":true,"default_value":"null"}]}
    constructor(opts) {
// @pdg-member {"name":"NetServer.serverInfo","type":"object"}
		this.serverInfo = opts || {};
        this._nativeEnabled = this.serverInfo.native !== false;
// @pdg-member {"name":"NetServer.listeners","type":"object"}
        this.listeners = {native:null, websocket:null, webtransport:null};
        this._pendingConnections = new Set();
// @pdg-member {"name":"NetServer.serverPort","type":"number"}
		this.serverPort = 5000;
// @pdg-member {"name":"NetServer.serverAddr","type":"string"}
		this.serverAddr = '0.0.0.0';
// @pdg-member {"name":"NetServer.handshakeTimeout","type":"number"}
		this.handshakeTimeout = 5000; // 5 second timeout on handshake
// @pdg-member {"name":"NetServer.reservationRequired","type":"boolean"}
		this.reservationRequired = false;
		this._fixedPort = false;
// @pdg-member {"name":"NetServer.allowDatagram","type":"boolean"}
		this.allowDatagram = true;
		if (typeof opts != 'undefined' && opts !== null) {
			if (typeof opts.serverAddr != 'undefined') {
				this.serverAddr = opts.serverAddr;
			}
			if (typeof opts.port != 'undefined') this.serverPort = opts.port;
			if (typeof opts.serverPort != 'undefined') {
				this.serverPort = opts.serverPort
			}
			if (typeof opts.fixedPort != 'undefined') {
				this._fixedPort = opts.fixedPort
			}
			if (typeof opts.noDatagram != 'undefined') {
				this.allowDatagram = !opts.noDatagram
			}
			if (typeof opts.reservationRequired != 'undefined') {
				this.reservationRequired = opts.reservationRequired;
			}
			if (typeof opts.handshakeTimeout != 'undefined') {
				this.handshakeTimeout = opts.handshakeTimeout;
			}
		}
		this._lastPort = this.serverPort + 100;
		this._listener = false;
// @pdg-member {"name":"NetServer.listening","type":"boolean"}
		this.listening = false;
// @pdg-member {"name":"NetServer.connections","type":"object NetConnection[]"}
		this.connections = [];
		this._connectCallback = false;
		this._errorCallback = false;
		this._reservations = [];
		this._dgramSock = false;
		this._dgramAlive = false;
	}

	//! list for incoming connections from your game clients
	//! /param callback function to call each time a new connection is made
	// @pdg-member {"name":"NetServer.listen","type":"function","brief":"listen and call a function when new connections are established","params":[{"name":"callback","type":"function"}],"returns":"this"}
	listen(callback) {
        if (this.listening || this._starting) throw new Error('Server already listening');
        this._starting = true;
        this._cancelListen = false;
        this._connectCallback = callback;
        var opts = this.serverInfo;
        this.listeners = {native:null, websocket:null, webtransport:null};
        var starts = [];
        this._readyPromise = Promise.resolve().then(function() {
            if (this._cancelListen) throw Object.assign(new Error('Listener startup cancelled'), {code:'ERR_LISTEN_CANCELLED'});
            if (!this._nativeEnabled && !opts.webSocket && !opts.webTransport) throw new TypeError('At least one listener must be enabled');
            // Validate and construct the web host before starting native TCP.
            if (opts.webSocket) {
                var web = Object.assign({port:opts.webPort, path:opts.webPath, tls:opts.tls, allowedOrigins:opts.allowedOrigins},
                    typeof opts.webSocket === 'object' ? opts.webSocket : {});
                try {
                    this._webListener = require(typeof require.resolve !== 'function' ? 'net_websocket_server' : './net_websocket_server').listen(this, web);
                    starts.push(this._webListener.ready.then(function(address) {
                        this.listeners.websocket = address;
                        return address;
                    }.bind(this)).catch(function(error) {
                        throw Object.assign(error, {transport:'websocket', host:web.host || this.serverAddr, port:web.port === undefined ? 5443 : web.port});
                    }.bind(this)));
                } catch (error) {
                    starts.push(Promise.reject(Object.assign(error, {code:error.code || 'ERR_LISTEN_CONFIG', transport:'websocket', host:web.host || this.serverAddr, port:web.port === undefined ? 5443 : web.port})));
                }
            }
            if (opts.webTransport) {
                var transport = Object.assign({port:opts.webPort, path:opts.webPath, tls:opts.tls, allowedOrigins:opts.allowedOrigins},
                    typeof opts.webTransport === 'object' ? opts.webTransport : {});
                try {
                    this._webTransportListener = require(typeof require.resolve !== 'function' ? 'net_webtransport_server' : './net_webtransport_server').listen(this, transport);
                    starts.push(this._webTransportListener.ready.then(function(address) {
                        this.listeners.webtransport = address; return address;
                    }.bind(this)).catch(function(error) {
                        throw Object.assign(error, {transport:'webtransport', host:transport.host || this.serverAddr, port:transport.port === undefined ? 5443 : transport.port});
                    }.bind(this)));
                } catch (error) {
                    starts.push(Promise.reject(Object.assign(error, {code:error.code || 'ERR_LISTEN_CONFIG', transport:'webtransport'})));
                }
            }
            if (this._nativeEnabled) {
                starts.push(new Promise(function(resolve, reject) {
                    this._nativeReady = resolve; this._nativeReject = reject;
                    this._listener = net.createServer();
                    this._listener.on('error', this._handleError.bind(this));
                    this._listener.on('close', this._handleClose.bind(this));
                    this._listener.on('connection', this._handleConnect.bind(this));
                    this._listener.on('listening', this._handleListening.bind(this));
                    this._tryListen();
                }.bind(this)));
            }
            if (opts.allowPartialListen) {
                return Promise.all(starts.map(function(start) {
                    return start.catch(function(error) { this._reportListenerError(error); return null; }.bind(this));
                }.bind(this))).then(function(addresses) {
                    if (!addresses.some(Boolean)) throw new Error('All requested listeners failed');
                    return addresses.filter(Boolean);
                });
            }
            return Promise.all(starts);
        }.bind(this)).then(function(addresses) {
            this._starting = false; this.listening = true;
            return addresses;
        }.bind(this)).catch(function(error) {
            this.shutdown(true, true);
            this._starting = false;
            this._handleError(error);
            throw error;
        }.bind(this));
        // Preserve callback-only callers without unhandled rejection warnings.
        this._readyPromise.catch(function() {});
        return this;
    }

    // @pdg-member {"name":"NetServer.ready","type":"function","brief":"wait for all requested listeners to start","params":[],"returns":"object"}
    ready() {
        return this._readyPromise || Promise.reject(new Error('Call listen() before ready()'));
    }

	//! send a message to all 
	//! returns number of connections the message was sent to
	//! filter - bool filter([object NetConnection] connection)
	// @pdg-member {"name":"NetServer.broadcast","type":"function","brief":"send a message to all connections, with optional filter","params":[{"name":"message","type":"object"},{"name":"filter","type":"function","optional":true,"default_value":"null"}],"returns":"number"}
	broadcast(message, filter) {
		var msgCount = 0;
		if (typeof filter != 'function') {
			// send the message to everyone, no exceptions
			for (var i = 0; i < this.connections.length; i++) {
				this.connections[i].send(message);
			}
			msgCount = this.connections.length;
		} else {
			// send the message only to connections for which the filter func returns true
			for (var i = 0; i < this.connections.length; i++) {
				var connection = this.connections[i];
				if (filter(connection)) {
					connection.send(message);
					msgCount++;
				}
			}
		}
		return msgCount;
	}

	//! expect a client with a particular key to connect
	//! /param clientKey the key the client should have
	//! /param clientIpAddr the IP address the client should be coming from
	//! /param reservationTTL the time in seconds for the reservation to last
	//! /param singleUse true if the reservation is cleared as soon as the client connects
	// @pdg-member {"name":"NetServer.expectClient","type":"function","brief":"make a connection reservation for a client","params":[{"name":"clientKey","type":"string"},{"name":"clientIpAddr","type":"string","optional":true,"default_value":"'*'"},{"name":"reservationTTL","type":"number int","optional":true,"default_value":"FOREVER"},{"name":"singleUse","type":"boolean","optional":true,"default_value":"false"}],"returns":"this"}
	expectClient(clientKey, clientIpAddr, reservationTTL, singleUse) {
		if (typeof(clientIpAddr) == 'undefined') {
			clientIpAddr = '*'; // accept any IP
		}
		if (typeof(reservationTTL) == 'undefined') {
			reservationTTL = -1; // never expires
		}
		if (typeof(singleUse) == 'undefined') {
			singleUse = false;
		}
		var t = pdg.tm.getMilliseconds();
		var reservation = { key: clientKey, ip: clientIpAddr, until: reservationTTL === -1 ? -1 : t + (reservationTTL*1000), once: singleUse };
		for (var i in this._reservations) {
			var rt = this._reservations[i].until;
			if ((rt != -1) && (rt < t)) {
				// expired reservation, replace it with this one
				this._reservations[i] = reservation;
				return this;
			}
		}
		this._reservations.push(reservation);
		return this;
	}

	//! setup error handler
	// @pdg-member {"name":"NetServer.onError","type":"function","brief":"set up callback for handling errors","params":[{"name":"callback","type":"function"}],"returns":"this"}
	onError(callback) {
		this._errorCallback = callback;
		return this;
	}

	//! close the connection
	// @pdg-member {"name":"NetServer.shutdown","type":"function","brief":"close the listener and don't accept new connections","params":[{"name":"closeExisting","type":"boolean","optional":true,"default_value":"true"},{"name":"kill","type":"boolean","optional":true,"default_value":"false"}]}
	shutdown(closeExisting, kill) {
		if (typeof kill == 'undefined') {
			kill = false;
		}
        this._cancelListen = true;
        if (this._starting && this._nativeReject) this._nativeReject(Object.assign(new Error('Listener startup cancelled'), {code:'ERR_LISTEN_CANCELLED', transport:'native'}));
        if (this._webListener) { this._webListener.close(); this._webListener = false; }
        if (this._webTransportListener) { this._webTransportListener.close(closeExisting !== false); this._webTransportListener = false; }
		if (this._listener) { this._listener.close(); }
        if (this._dgramSock) {
            try { this._dgramSock.close(); } catch (error) { if (error.code !== 'ERR_SOCKET_DGRAM_NOT_RUNNING') throw error; }
            this._dgramSock = false; this._dgramAlive = false;
        }
        this._pendingConnections.forEach(function(connection) { connection.close(true); });
        this.listeners = {native:null, websocket:null, webtransport:null};
		if (typeof(closeExisting) == 'undefined') {
			closeExisting = true;
		}
		if (closeExisting) {
			this._closeAllConnections(kill);
		}
		this.listening = false;
	}


// ==============================================================
// protected - you shouldn't need to call these directly


	_checkClientIP(clientIpAddr) {
		if (this.reservationRequired) {
			var t = pdg.tm.getMilliseconds();
			var foundExpired = false;
			var foundMatch = false;
			for (var i in this._reservations) {
				var rt = this._reservations[i].until;
				if ((rt != -1) && (rt < t)) {
					foundExpired = true;  // clean up later
					this._reservations[i].until = 0;
				} else if ((this._reservations[i].ip == '*') || (this._reservations[i].ip == clientIpAddr)) {
					NET_SERVER_LOG('IP match for '+clientIpAddr+' reservation '+i+' == '+this._reservations[i].ip);
					foundMatch = true;
					if (this._reservations[i].once && this._reservations[i].until !== -1) {
						// we have an IP match for this client, so give it extra time
						// to complete the handshake
						this._reservations[i].until += 2000;
					}
				}
			}
			if (foundExpired) {
				for (var i in this._reservations) {
					if (this._reservations[i].until == 0) {
						NET_SERVER_LOG('removed expired reservation '+i);
						this._reservations.splice(i, 1);
					}
				}
			}
			return foundMatch;
		} else {
			return true;
		}
	}

	_checkClientKey(clientKey, clientIpAddr) {
		if (this.reservationRequired) {
			var t = pdg.tm.getMilliseconds();
			var foundExpired = false;
			var foundMatch = false;
			for (var i in this._reservations) {
				var rt = this._reservations[i].until;
				if ((rt != -1) && (rt < t)) {
					foundExpired = true;  // clean up later
					this._reservations[i].until = 0;
				} else if (this._reservations[i].key == clientKey) {
					if ((this._reservations[i].ip == '*') || (this._reservations[i].ip == clientIpAddr)) {
						NET_SERVER_LOG('Key + IP match for '+clientKey+' @'+clientIpAddr+' reservation '+i+' == '+this._reservations[i].key+' @'+this._reservations[i].ip);
						foundMatch = true;
						if (this._reservations[i].once) {
							foundExpired = true;	// single use key, expire it now that it has been used
							this._reservations[i].until = 0;	
						}
					}
				}
			}
			if (foundExpired) {
				for (var i in this._reservations) {
					if (this._reservations[i].until == 0) {
						NET_SERVER_LOG('removed expired/used reservation '+i);
						this._reservations.splice(i, 1);
					}
				}
			}
			if (!foundMatch) {
				NET_SERVER_LOG('No Reservation Found for '+clientKey+' @'+clientIpAddr);
			}
			return foundMatch;
		} else {
			return true;
		}
	}


	_handleClose() {
        if (!this.listeners.websocket && !this.listeners.webtransport) this.listening = false;
    }

	_closeAllConnections(kill) {
		if (this._dgramSock) {
			this._dgramSock.close();
		}
		this._dgramSock = false;
		this._dgramAlive = false;
		var connectionsCopy = this.connections.slice();
		for (var i = 0; i < connectionsCopy.length; i++) {
			var connection = connectionsCopy[i];
			connection.close(kill);
			connection._dgramSock = false;
			connection._dgramAlive = false;
		}
	}
	
	_handleConnectionClose(connection) {
		var idx = this.connections.indexOf(connection);
		if (idx != -1) {
			this.connections.splice(idx, 1);
		}
	}
	
	_handleConnectionHandshakeClose(connection) {
		// if connection is not alive, it means we killed it, so just ignore this
		if (connection._alive) {
			NET_SERVER_LOG('Server got connection close during handshake from '+connection.remoteAddr);
			connection.close(true);
		}
	}
	
	_handleError(error) {
        if (typeof error !== 'object') error = new Error(String(error));
		NET_SERVER_LOG('Got error ' + error);
		if (this._starting && !this._cancelListen && this._listener && !this._listener.listening && (!error.transport || error.transport === 'native') && (error.code == 'EADDRINUSE') && (!this._fixedPort) && (this.serverPort < this._lastPort)) {
			NET_SERVER_LOG('Retrying on new port');
			this.serverPort++;
			this._tryListen();
		} else if (this._starting && this._nativeReject && (!error.transport || error.transport === 'native')) {
            this._nativeReject(Object.assign(error, {transport:'native', host:this.serverAddr, port:this.serverPort}));
		} else if (this._errorCallback) {
			try {
				NET_SERVER_LOG('Doing Error Callback');
				this._errorCallback(error, this);
			}
			catch(e) {
				console.error('NetServer Error Callback Exception: '+JSON.stringify(e));
			}
		} else {
			// make sure somebody knows what happened
			console.error('NetServer Error: '+String(error));
		}
	}
	
	_handleListening() {
		var addr = this._listener.address().address;
		var port = this._listener.address().port;
		NET_SERVER_LOG('Server now listening on ' + addr +':'+ port+'/tcp');
        this.serverPort = port;
        if (this._cancelListen) { this._listener.close(); this._nativeReject(new Error('Listener startup cancelled')); return; }
		if (this.allowDatagram) {
			NET_SERVER_LOG('Server attempting to create Datagram socket on ' + addr +':'+ port);
			this._dgramSock = dgram.createSocket("udp4");
			this._dgramSock.on("message", this._handleDgram.bind(this));
			this._dgramSock.on("error", this._handleError.bind(this));
			this._dgramSock.on("listening", this._handleDgramListening.bind(this));
			this._dgramSock.bind(port, addr);
		} else { this._nativeListeningReady(); }
	}
	
	_handleDgramListening() {
		var addr = this._listener.address().address;
		var port = this._listener.address().port;
		NET_SERVER_LOG('Server now listening on ' + addr +':'+ port+'/udp');
		this._dgramAlive = true;
        this._nativeListeningReady();
	}
	
    _reportListenerError(error) {
        if (this._errorCallback) this._errorCallback(error, this);
        else console.error('NetServer Error:', error);
    }

    _nativeListeningReady() {
        this.listeners.native = Object.assign({transport:'native', secure:false}, this._listener.address());
        if (this._nativeReady) this._nativeReady(this.listeners.native);
    }

	// called by NetConnection once handshake is finished
	_handshakeComplete(connection) {
        this._pendingConnections.delete(connection);
		NET_SERVER_LOG('Server handshake complete for ' + connection.remoteAddr);
		try {
			if (this._connectCallback(connection)) {
				this.connections.push(connection);
				connection.socket.on('close', function() {
					this._handleConnectionClose(connection);
				}.bind(this)); // we need to be notified
			} else {
				// if we aren't going to accept this connection, then
				// immediately shutdown the socket and allow no further
				// communication
				NET_SERVER_LOG('Application layer refused connection from '+connection.remoteAddr);
				connection.close(true);
			}
		}
		catch(e) {
			console.error('NetServer Connect Callback Exception: '+JSON.stringify(e));
			NET_SERVER_LOG('Application layer exception on connect callback for connection from '+connection.remoteAddr);
			connection.close(true);
		}
	}
	
	_handleConnect(socket) {
        if (this._cancelListen) { socket.destroy(); return; }
		NET_SERVER_LOG('incoming connection from '+socket.remoteAddress);
		try {
			if (this._checkClientIP(socket.remoteAddress)) {
				var connection = new pdg.NetConnection(socket, this);
				connection._serverInit(this); // wait for handshake to complete
                this._pendingConnections.add(connection);
                connection.socket.on('close', function() { this._pendingConnections.delete(connection); }.bind(this));
				if (this.handshakeTimeout > 0) {
					connection._handshakeTimer = setTimeout(function() {
						// when called, connection will be "this"
						if (this._alive && !this._handshakeComplete) {
							NET_SERVER_LOG('Handshake Timeout ['+this._server.handshakeTimeout+'ms] for connection from '+this.remoteAddr);
							this.close(true); // dead client connection, kill it
						}
						return true;
					}.bind(connection), this.handshakeTimeout);
				}
				connection.socket.on('close', function() {
					this._handleConnectionHandshakeClose(connection);
				}.bind(this)); // we need to be notified
			} else {
				// IP not in our reservation list
				NET_SERVER_LOG('Dumping connection with no reservation from '+socket.remoteAddress);
				socket.destroy();
			}
		} catch(e) { 
			socket.destroy();
			this._handleError("Error handling incoming connection @"+this.serverAddr+":"+this.serverPort+" from "+socket.remoteAddress+": "+e); 
		}
	}

	_tryListen() {
		if (!this.listening) {
			NET_SERVER_LOG('Server trying to listen @'+this.serverAddr+":"+this.serverPort+"/tcp");
			this._listener.listen(this.serverPort, this.serverAddr);
		} else {
			NET_SERVER_LOG('ignoring _tryListen(), already listening');
		}
	}	

	_handleDgram(msg, rinfo) {
		try {
			// find which connection based on remoteAddr and port
			for (var i = 0; i < this.connections.length; i++) {
				if ((rinfo.address == this.connections[i].remoteAddr) && (rinfo.port == this.connections[i].remotePort)) {
					this.connections[i]._handleDgram(msg, rinfo);
					return;
				}
			}
			NET_SERVER_LOG('Server ignoring dgram from unknown client ' + rinfo.address+':'+rinfo.port);
	    } catch(e) { 
	    	this._handleError(e); 
	    }
    }
}

if(!(typeof exports === 'undefined')) {
    exports.NetServer = NetServer;
}

/* @pdg-schema
{
  "name": "NetServerOptions",
  "value": {
    "kind": "record",
    "fields": {
      "serverAddr": {
        "type": "string",
        "optional": true
      },
      "serverPort": {
        "type": "number",
        "optional": true
      },
      "handshakeTimeout": {
        "type": "number",
        "optional": true
      },
      "fixedPort": {
        "type": "boolean",
        "optional": true
      },
      "noDatagram": {
        "type": "boolean",
        "optional": true
      },
      "reservationRequired": {
        "type": "boolean",
        "optional": true
      },
      "port": {
        "type": "number",
        "optional": true
      },
      "native": {
        "type": "boolean",
        "optional": true
      },
      "webSocket": {
        "one_of": [
          {
            "type": "boolean"
          },
          {
            "type": "object"
          }
        ],
        "optional": true
      },
      "webPort": {
        "type": "number",
        "optional": true
      },
      "webPath": {
        "type": "string",
        "optional": true
      },
      "allowedOrigins": {
        "items": {
          "type": "string"
        },
        "optional": true
      },
      "tls": {
        "type": "object",
        "optional": true
      },
      "allowPartialListen": {
        "type": "boolean",
        "optional": true
      },
      "webTransport": {
        "one_of": [
          {
            "type": "boolean"
          },
          {
            "type": "object"
          }
        ],
        "optional": true
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "NetServer.NetServer",
  "value": {
    "params": {
      "opts": {
        "schema": "NetServerOptions",
        "nullable": true
      }
    },
    "optional_class": true
  }
}
*/

/* @pdg-contract
{
  "name": "NetServer.serverInfo",
  "value": {
    "property": {
      "one_of": [
        {
          "schema": "NetServerOptions"
        },
        {
          "type": "null"
        },
        {
          "type": "undefined"
        }
      ]
    },
    "optional_class": true
  }
}
*/

/* @pdg-schema
{
  "name": "NetAcceptCallback",
  "value": {
    "kind": "callback",
    "params": [
      {
        "name": "connection",
        "type": "object NetConnection"
      }
    ],
    "returns": {
      "type": "boolean"
    },
    "synchronous": true
  }
}
*/

/* @pdg-schema
{
  "name": "NetServerErrorCallback",
  "value": {
    "kind": "callback",
    "params": [
      {
        "name": "error",
        "schema": "NetworkError"
      },
      {
        "name": "endpoint",
        "type": "object NetServer",
        "optional": true
      }
    ],
    "returns": {
      "type": "void"
    }
  }
}
*/

/* @pdg-contract
{
  "name": "NetServer.onError",
  "value": {
    "params": {
      "callback": {
        "schema": "NetServerErrorCallback"
      }
    },
    "optional_class": true
  }
}
*/

/* @pdg-contract
{
  "name": "NetServer.listen",
  "value": {
    "params": {
      "callback": {
        "schema": "NetAcceptCallback"
      }
    },
    "optional_class": true
  }
}
*/

/* @pdg-contract
{
  "name": "NetServer.broadcast",
  "value": {
    "optional_class": true,
    "params": {
      "message": {
        "schema": "NetworkSendable"
      },
      "filter": {
        "schema": "NetAcceptCallback",
        "nullable": true
      }
    }
  }
}
*/
