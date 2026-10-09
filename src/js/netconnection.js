// -----------------------------------------------
// netconnection.js
//
// implementation of a connection as part of the pdg network interface
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

// HANDSHAKE:
//  client                    server
//  ------                    ------
//   [K]          --->     (checks key, disco if invalid)    
//    V (vers)    --->     (checks for match, disco if lower)   
//                <---          V (vers)
//  (adjusts vers
//   to what server
//   requires)
//   [V] (vers)   --->     (check for match, disco if not equal)


var browserNetwork = typeof document !== 'undefined';
var iosNetwork = typeof process !== 'undefined' && process.versions && !!process.versions.jsc;
var dgram = browserNetwork || iosNetwork ? null : require('dgram');
var netBytes = require((browserNetwork || iosNetwork || typeof require.resolve !== 'function') ? 'net_bytes' : './net_bytes');

var NET_CONN_LOG;

if ((typeof process !== 'undefined' && process.env && process.env.PDG_DEBUG && process.env.PDG_DEBUG.indexOf('NET_DATA') != -1)
  || (typeof process !== 'undefined' && process.env && process.env.NODE_DEBUG && process.env.NODE_DEBUG.indexOf('NET_DATA') != -1)) {
	console.log('Found NODE_DEBUG or PDG_DEBUG=NET_DATA in environment. Logging network data.');
    NET_CONN_LOG = function(msg, data, size) {
		console.log(msg);
		if (arguments.length > 2) {
			console.binaryDump(data, size);
		}
	};
} else {
 	NET_CONN_LOG = function(msg, data, size) {};
}

// @pdg-class {"name":"NetConnection"}
class NetConnection {
	//! new NetConnection(socket): handle communication on a socket
	//! /param socket the low level socket to manage
// @pdg-member {"name":"NetConnection.NetConnection","type":"constructor","brief":"create a NetConnection to manage a socket","returns":"object NetConnection","params":[{"name":"socket","type":"object"}]}
    constructor(socket) {
// @pdg-member {"name":"NetConnection.localAddr","type":"string"}
			this.localAddr = '';
// @pdg-member {"name":"NetConnection.localPort","type":"number"}
			this.localPort = 0;
// @pdg-member {"name":"NetConnection.remoteAddr","type":"string"}
			this.remoteAddr = '';
// @pdg-member {"name":"NetConnection.remotePort","type":"number"}
			this.remotePort = 0;
// @pdg-member {"name":"NetConnection.hasDgram","type":"boolean"}
			this.hasDgram = false;
// @pdg-member {"name":"NetConnection.transport","type":"string"}
			Object.defineProperty(this, 'transport', {value: socket && socket.transport || 'native', enumerable:true});
// @pdg-member {"name":"NetConnection.secure","type":"boolean"}
			Object.defineProperty(this, 'secure', {value: !!(socket && socket.secure), enumerable:true});
			this.maxFrameSize = socket && socket.maxFrameSize || 1024 * 1024;
			this.maxPendingBytes = socket && socket.maxPendingBytes || 4 * 1024 * 1024;
			if (typeof socket != 'undefined' && socket) {
				this.socket = socket;
				var info = socket.address();
				this.localAddr = info.address;
				this.localPort = info.port;
				this.remoteAddr = socket.remoteAddress;
				this.remotePort = socket.remotePort;
				socket.on('error', this._handleError.bind(this));
				socket.on('data', this._handleTcpData.bind(this));
                if (this.transport === 'webtransport') socket.on('datagram', function(bytes) {
                    if (this._handshakeComplete && this.hasDgram && this._alive) this._handleDgram(bytes, {address:this.remoteAddr, port:this.remotePort});
                }.bind(this));
				socket.on('close', this._handleClose.bind(this));
				socket.on('timeout', this._handleTimeout.bind(this));
				socket.on('drain', this._handleDrain.bind(this));
				socket.on('end', this._handleEnd.bind(this));
				socket.setKeepAlive(true, 2000); // every 2 seconds we will send keepalive
			}
			this._alive = false;
			this._closeCallback = false;
			this._messageCallback = false;
			this._pendingData = false;
			this._pendingDataOffset = 0;
			this._server = false;
			this._client = false;
			this._protocolVers = 1;
			this._remoteVers = 0;
			this._requireKey = false;
			this._errorCallback = false;
			this._handshakeComplete = false;
            this._remoteDatagramAllowed = false;
			this._dgramSock = false;
			this._dgramAlive = false;
			this._dgramStartsSent = 0;
			this._maxDgramStarts = 100;
			this._dgramStartInterval = 500; // try sending every 1/2 second
			this._dgramStartDelayFactor = 100; // wait an extra 10th of a second for each additional attempt
    }

	//! close the connection
	// @pdg-member {"name":"NetConnection.close","type":"function","brief":"close the connection","params":[{"name":"kill","type":"boolean"}]}
	close(kill) {
        this.socket.end();
        NET_CONN_LOG((this._client ? 'Client ' : 'Server ') + this.localAddr+':'+this.localPort + ' close'+ ( kill ? ' and kill':''));
        if (kill) {
            this._alive = false;
            this.socket.destroy();
            if (this._client && this._dgramSock) {
                NET_CONN_LOG('Client ' + this.localAddr+':'+this.localPort + ' close dgram socket');
                // only do this on the client
                this._dgramSock.close();
            }
            this._dgramSock = false;
            this._dgramAlive = false;
        }
    }

	//! setup connection close handler
	// @pdg-member {"name":"NetConnection.onClose","type":"function","brief":"set callback to handle connection closing","params":[{"name":"callback","type":"function"}],"returns":"this"}
	onClose(callback) {
        this._closeCallback = callback;
        return this;
    }

	//! setup incoming message handler
	// @pdg-member {"name":"NetConnection.onMessage","type":"function","brief":"set callback to handle receipt of a network message","params":[{"name":"callback","type":"function"}],"returns":"this"}
	onMessage(callback) {
        this._messageCallback = callback;
        return this;
    }

	//! send a message via a reliable transport mechanism
	//! messages are received in the order they were sent
	//! delivery is guaranteed (or error if connection dropped)
	// @pdg-member {"name":"NetConnection.send","type":"function","brief":"send a serializable object to the remote endpoint","params":[[{"name":"message","type":"string"}],[{"name":"message","type":"object MemBlock"}],[{"name":"message","type":"object ISerializable"}],[{"name":"message","type":"object"}]],"returns":"this"}
	send(message) {
        var data = this._serializeMessage(message);
        var buf = this._frameTcpData(data);
        NET_CONN_LOG((this._client ? 'Client' : 'Server') + ' -> ' + this.remoteAddr+':'+this.remotePort + ' ['+buf.length+' bytes]', buf, buf.length);
        var flushed = this.socket.write(buf);  
        // if not flushed, then it didn't all fit in kernel buffer. May be useful
        // for flow control or throttling
        return this;
    }

	//! send a message via the fastest transport mechanism
	//! delivery and packet order not guaranteed
	//! if unreliable transport isn't available, or if the 
	//! message is larger than 1492 bytes, it will be sent over reliable transport instead
	// @pdg-member {"name":"NetConnection.sendDgram","type":"function","brief":"send a serializable object to the remote endpoint via UDP","params":[[{"name":"message","type":"string"}],[{"name":"message","type":"object MemBlock"}],[{"name":"message","type":"object ISerializable"}],[{"name":"message","type":"object"}]],"returns":"this"}
	sendDgram(message) {
        if (this.transport === 'webtransport') {
            if (!this.hasDgram || !this._handshakeComplete) return this.send(message);
            var bytes = this._serializeMessage(message);
            var fallbackDone = false;
            var fallback = function() {
                if (fallbackDone) return;
                fallbackDone = true;
                if (this._alive && !this._closed) this.socket.write(this._frameTcpData(bytes));
            }.bind(this);
            if (bytes.length > this.socket.maxDatagramSize || !this.socket.writeDatagram(bytes, fallback)) fallback();
            return this;
        }
		if (!this._dgramAlive || !this.hasDgram) {
			this.send(message);
		} else {
			var buf = this._serializeMessage(message);
			if (buf.length > 1492) this.send(message);
            else this._dgramSock.send(buf, 0, buf.length, this.remotePort, this.remoteAddr, this._dgramSendCallback.bind(this));
		}
		return this;
	}


// ==============================================================
// protected - you shouldn't need to call these directly

	_serverInit(server) {
		this._server = server;
		this._errorCallback = this._server._errorCallback;
		this._alive = true;
		this._requireKey = server.reservationRequired;
		this._handshakeComplete = false;
		this._dgramSock = this.transport === 'native' ? server._dgramSock : false;
		this._dgramStartsSent = 0;
	}

	_clientInit(client, clientKey) {
		this._client = client;
		this._errorCallback = this._client._errorCallback;
		this._alive = true;
		this._requireKey = false;
		if (clientKey && (clientKey != '') && this._alive) {
			// we were given a client key, so send it
			var buf = this._frameTcpCommand('K', clientKey);
			this.socket.write(buf);
		}
		// version handshake starts immediately, or after key is received if key required
		this._dgramStartsSent = 0;
		this._startHandshake();
	}

	_serializeMessage(message) {
		var dataType = '';
		var ser = new pdg.Serializer();
		if (typeof message == 'string') {
			ser.serialize_1u('s'.charCodeAt(0));
			ser.serialize_str(message);
		} else if (typeof message == 'object') {
			if (message instanceof pdg.ISerializable) {
				ser.serialize_1u('o'.charCodeAt(0));
				ser.serialize_obj(message);
			} else if (message instanceof pdg.MemBlock) {
				ser.serialize_1u('m'.charCodeAt(0));
				ser.serialize_mem(message);
			} else if (message instanceof Uint8Array) {
				ser.serialize_1u('b'.charCodeAt(0));
				ser.serialize_mem(message);
			} else {
				var json = JSON.stringify(message);
				ser.serialize_1u('j'.charCodeAt(0));
				ser.serialize_str(json);
			}
		} else {
			var err = {
				code:"ERR_BAD_DATA",
				message:"message must be a string or an object"
			};
			this._handleError(err, true); // this can throw an exception
		}
		return ser.getDataPtr().getData();
	}

	_deserializeMessage(memBlock) {
		var ser = new pdg.Deserializer();
		ser.setDataPtr(memBlock);
		var dataType = String.fromCharCode(ser.deserialize_1u());
		var message;
		if (dataType == 's') {
			message = ser.deserialize_str();
		} else if (dataType == 'o') {
			message = ser.deserialize_obj();
		} else if (dataType == 'm') {
			message = ser.deserialize_mem();
		} else if (dataType == 'b') {
			var tmp = ser.deserialize_mem();
			var bytes = tmp.getData();
			// Share the owned snapshot; Buffer.from(bytes) would copy it again.
			message = typeof Buffer !== 'undefined' ? Buffer.from(bytes.buffer, bytes.byteOffset, bytes.byteLength) : bytes;
		} else if (dataType == 'j') {
			var str = ser.deserialize_str();
			message = JSON.parse(str);
		} else {
			var err = {
				code:"ERR_REMOTE_BAD_DATA",
				message:"Remote side sent unknown datatype "+dataType+". Newer protocol?"
			};
			this._handleError(err);
		}
		return message;
	}

	_frameTcpData(payload) {
		// save the packet type and number of bytes in the message
		var payloadSize = payload.byteLength;
        if (payloadSize > this.maxFrameSize) throw Object.assign(new Error('Reliable frame exceeds size limit'), {code:'ERR_FRAME_TOO_LARGE'});
		var bufSize = payloadSize + 5;
		var cmd = 'A';
		var outBuf = netBytes.alloc(bufSize);
		outBuf[0] = cmd.charCodeAt(0);
		netBytes.write(outBuf, 1, 4, payloadSize);
		outBuf.set(payload, 5);
		return outBuf;
	}

	// for internal use by the protocol
	_frameTcpCommand(cmd, cmdDataStr) {
		if (!this._isLegalForProtocolVersion(cmd)) {
			throw("tcp command "+cmd+" is not valid for protocol version "+this._protocolVers);
		}
		var payload = netBytes.encode(cmdDataStr);
		var payloadSize = payload.length;
		if (payloadSize >= 0x10000) {
			throw("tcp command data must be less than 64K");
		}
		if (netBytes.encode(cmd).length > 1) {
			throw("tcp command must be single ASCII character");
		}
		if (cmd == 'A') {
			throw("tcp command 'A' is reserved for serialized data");
		}
		var bufSize = payloadSize + 3;
		var outBuf = netBytes.alloc(bufSize);
		outBuf[0] = cmd.charCodeAt(0);
		netBytes.write(outBuf, 1, 2, payloadSize);
		outBuf.set(payload, 3);
		return outBuf;
	}

	_isLegalForProtocolVersion(cmd) {
		var legalCmds = [ 
			'',   // v0: no legal commands
			'KV'  // v1: K - client key; V - protocol version
		];
		return (legalCmds[this._protocolVers].indexOf(cmd) != -1) || (this.transport === 'webtransport' && cmd === 'D');
	}

	_peekTcpCommand(data) {
		return String.fromCharCode(data[0]);
	}

	_getNextFrameStart(data) {
        if (!data.length) return Infinity;
        var frameSize = this._peekTcpCommand(data) === 'A' ? 5 : 3;
        if (data.length < frameSize) return Infinity;
        var payloadSize = netBytes.read(data, 1, frameSize - 1);
        if (payloadSize > this.maxFrameSize) {
            this.close(true);
            throw Object.assign(new Error('Reliable frame exceeds size limit'), {code:'ERR_FRAME_TOO_LARGE'});
        }
        return frameSize + payloadSize;
    }

	_deframeTcpData(data) {
		var payloadSize = netBytes.read(data, 1, 4);
		return data.slice(5, 5 + payloadSize);
	}

	_deframeTcpCmdData(data) {
		var payloadSize = netBytes.read(data, 1, 2);
		var cmdData = netBytes.decode(data.subarray(3, 3 + payloadSize));
		return cmdData;
	}

	_handleError(error, canThrow) {
        if (this._client && !this._handshakeComplete) {
            if (this._connectErrorReported) return;
            this._connectErrorReported = true;
        }
		if (typeof(canThrow) == 'undefined') {
			canThrow = (this._server === false);  // default to throwing errors on the client
		}
		try {
			// send to error callback, or throw if no callback
			if (this._errorCallback) {
				this._errorCallback(error, this);
			} else if (this._server) {
				if (this._server._errorCallback) {
					this._server._errorCallback(error, this);
				} else {
					console.error('Net Connection Server Error: ', JSON.stringify(error));
					if (canThrow) {
						throw(error);
					}
					// don't throw on the server because we don't want client errors
					// to be able to crash the server
				}
			} else if (this._client) {
				if (this._client._errorCallback) {
					this._client._errorCallback(error, this);
				} else {
					console.error('Net Connection Client Error: ', JSON.stringify(error));
					if (canThrow) {
						throw(error);
					}
				}
			}
		} 
		catch(e) {
			console.error('Net Connection Exception in Error Callback: ', JSON.stringify(e));
			if (canThrow) {
				throw(e);
			}
		}
	}

	_handleTcpData(data) {
	    try {
// 			NET_CONN_LOG("got data on connection "+this.localAddr+":"+this.localPort+
// 				" from "+this.remoteAddr+":"+this.remotePort);
			// data should always be a buffer
			if (data instanceof Uint8Array || data instanceof ArrayBuffer) {
                data = netBytes.bytes(data);
                var retained = this._pendingData === false ? netBytes.alloc(0) : this._pendingData.subarray(this._pendingDataOffset);
                if (retained.length + data.length > this.maxPendingBytes) {
                    this.close(true);
                    throw Object.assign(new Error("Pending reliable byte limit exceeded"), {code:"ERR_BACKPRESSURE"});
                }
				NET_CONN_LOG((this._client ? 'Client' : 'Server') + ' <- ' + this.remoteAddr+':'+this.remotePort + ' ['+data.length+' bytes]', data, data.length);
				if (this._pendingData === false) {
					this._pendingData = data;
					this._pendingDataOffset = 0;
				} else {
					this._pendingData = netBytes.concat(retained, data);
                    this._pendingDataOffset = 0;
				}
				data = this._pendingData.subarray(this._pendingDataOffset);
				var nextFrameStart = this._getNextFrameStart(data);
				while ( nextFrameStart <= data.length && this._alive) {
					var packetLen = nextFrameStart;
					NET_CONN_LOG('(packet @ '+this._pendingDataOffset+' to '+(this._pendingDataOffset+nextFrameStart-1)+') ['+packetLen+' bytes]', data, packetLen);
					var cmd = this._peekTcpCommand(data);
					if (this._requireKey && (cmd != 'K') ) {
						// expected a key, but didn't get one.
						this.close(true); // kill the socket
						var err = {
							code:"ERR_MISSING_CLIENT_KEY",
							message:"Remote side did not send client key. Connection killed."
						}
						this._handleError(err);
                        return;
					}
                    if (cmd === 'A' && !this._handshakeComplete) {
                        this.close(true);
                        this._handleError({code:'ERR_HANDSHAKE_REQUIRED', message:'Application data arrived before the PDG handshake'});
                        return;
                    }
					if (cmd == 'A') {
						if (this._messageCallback) {
							var memBlock = this._deframeTcpData(data);
							var message = this._deserializeMessage(memBlock);
							try {
								this._messageCallback(message, this, 'tcp');
							} catch(e) {
 								console.error((this._client ? 'Client ' : 'Server ') + this.localAddr+':'+this.localPort+'/tcp'
 									+ ' message callback for message from '+this.remoteAddr+':'+this.remotePort+'/tcp'
 									+' threw Exception: '+JSON.stringify(e)
 								);
								if (this._client) {
									throw(e);
								}
							}
						}
					} else {
						var cmdData = this._deframeTcpCmdData(data);
						this._handleTcpCommand(cmd, cmdData);
					}
                    if (!this._alive || this._closed) return;
					this._pendingDataOffset += nextFrameStart;
					data = this._pendingData.subarray(this._pendingDataOffset);
					nextFrameStart = this._getNextFrameStart(data);
				}
				if (this._pendingDataOffset >= this._pendingData.length) {
					// all the data has been consumed, delete the Buffer
					this._pendingData = false;
					NET_CONN_LOG('(buffer empty)');
				}
			} else {
				NET_CONN_LOG((this._client ? 'Client' : 'Server') + ' <- ' + this.remoteAddr+':'+this.remotePort + ' ['+data.length+' bytes]', data.toString(), data.length);
				NET_CONN_LOG(' X - NO FRAME)');
				var err = {
					code:"ERR_REMOTE_BAD_FRAME",
					message:"Remote side sent unframed data. Must not be a NetConnection."
				};
				this._handleError(err);
			}
	    } catch(e) { 
	    	this._handleError(e); 
	    }
	}

	_startHandshake() {
        if (this.transport === 'webtransport' && !this._datagramAdvertised) {
            this._datagramAdvertised = true;
            var allowed = this._client ? this._client._allowDatagram : this._server && this._server.allowDatagram;
            this.socket.write(this._frameTcpCommand('D', allowed && this.socket.maxDatagramSize > 0 ? '1' : '0'));
        }
		var buf = this._frameTcpCommand('V', this._protocolVers.toString());
		this.socket.write(buf);
	}

	_finishedHandshake() {
		if (this._handshakeComplete || !this._alive) return;
		this._handshakeComplete = true;
        clearTimeout(this._handshakeTimer);
        if (this.transport === 'webtransport') {
            var allowed = this._client ? this._client._allowDatagram : this._server && this._server.allowDatagram;
            this.hasDgram = !!(allowed && this._remoteDatagramAllowed && this.socket.maxDatagramSize > 0 && this.socket.writeDatagram);
        }
		var startDgram = false;
		if (this._client) {
			// now that handshake is done we can let the client know that we are connected
			try {
				this._client._connectCallback(this);
			} catch(e) {
				console.error('Net Connection Exception in Connect Callback: ', JSON.stringify(e));
				throw(e);
			}
			if (!this._closed && this._alive && this.transport === 'native' && this._client._allowDatagram) {
				NET_CONN_LOG('Client attempting to open Datagram socket on ' + this.localAddr+':'+this.localPort);
				this._dgramSock = this.socket.createDatagramSocket ? this.socket.createDatagramSocket() : dgram.createSocket("udp4");
				this._dgramSock.on("message", this._handleDgram.bind(this));
				this._dgramSock.on("error", this._handleDgramError.bind(this));
				this._dgramSock.on("listening", this._handleDgramListening.bind(this));
				this._dgramSock.bind(this.localPort, this.localAddr); // Bind to same port as TCP socket
				
				// Add debug output when UDP socket is bound
				this._dgramSock.on("listening", function() {
					var udpAddr = this._dgramSock.address();
					NET_CONN_LOG('Client UDP socket bound to ' + udpAddr.address + ':' + udpAddr.port);
				}.bind(this));
			}
		} else if (this._server) {
			// let server know handshake is complete so it can accept or reject connection
			// based on app level criteria
			this._server._handshakeComplete(this);
			if (this.transport === 'native' && this._server.allowDatagram) {
				this._handleDgramListening();  // server already set up the dgram socket
			}
		}
	}

	// for internal use by the protocol
	_handleTcpCommand(cmd, cmdDataStr) {
        if (cmd === 'D' && this.transport === 'webtransport' && !this._handshakeComplete && (cmdDataStr === '0' || cmdDataStr === '1')) {
            this._remoteDatagramAllowed = cmdDataStr === '1';
        } else if (cmd == 'K') {
			NET_CONN_LOG(' - Check client key: '+cmdDataStr);
			if (this._server) {
				if (this._server._checkClientKey(cmdDataStr, this.remoteAddr)) {
					this._requireKey = false;  // got a good key
				} else {
					this.close(true); // kill the socket
					var err = { 
						code:"ERR_BAD_CLIENT_KEY",
						message:"Remote side sent an invalid client key ["+cmdDataStr+"]. Connection killed."
					};
					this._handleError(err);
				}
			}
		} else if (cmd == 'V') {
			NET_CONN_LOG(' - Protocol version: '+cmdDataStr);
			var isServer = (this._server !== false);
			var isVersionAck = (this._remoteVers > 0); // if they've already told us their version before, this is an ACK
			var remoteVers = Number(cmdDataStr);
            if (!Number.isInteger(remoteVers) || remoteVers < 1) {
                this.close(true);
                this._handleError({code:'ERR_UNSUPPORTED_PROTOCOL', message:'Invalid PDG protocol version'});
                return;
            }
			var ourVers = this._protocolVers;
			var finishedHandshake = false;
			if (isServer) {
				// server side, handle the command once or twice, second time might be ack 
				if (!isVersionAck) {
					// first time, starting handshake on server side
					this._startHandshake();
					if (remoteVers < ourVers) {
						// client is older version, we can't support them because we don't
						// want to risk the app server trying to do things that the protocol doesn't
						// support and then dying because of an old/bad client
						this.close(false); // allow the socket to drain
						var err = { 
							code:"ERR_UNSUPPORTED_PROTOCOL",
							message:"Client has protocol v"+remoteVers+", we require support for v"+ourVers+". Client connection killed."
						};						
						this._handleError(err);
					} else if (remoteVers > ourVers) {
						// do nothing, they should send ack to adopt our older server protocol
					} else {
						// versions match, we are done
						finishedHandshake = true;						
					}
				} else {
					// second time, they must be ack'ing our protocol version or they get disconnected
					if (remoteVers == ourVers) {
						finishedHandshake = true;
					} else {
						this.close(true); // uncooperative client, kill immediately
						var err = { 
							code:"ERR_UNSUPPORTED_PROTOCOL",
							message:"Client refuses to support our protocol v"+ourVers+". Client connection killed."
						};
						this._handleError(err);
					}
				}
			} else {
				// client side, only handle the command once
				if (remoteVers > ourVers) { 
					// server has newer protocol
					this.close(true); // kill the socket
					var err = { 
						code:"ERR_UNSUPPORTED_PROTOCOL",
						message:"Server side requires protocol v"+remoteVers+", we only support v"+ourVers+". Connection killed."
					};
					this._handleError(err);
				} else if (remoteVers < ourVers) {
					// their version is older, no problem, just use their version
					// we'll throw on our side (the client side) if we try to do something not supported
					// by the protocol
					ourVers = remoteVers;
					// send ack that we are using their version
					var buf = this._frameTcpCommand('V', ourVers.toString());
					this.socket.write(buf);
					finishedHandshake = true;
				} else {
					// version match, we are done
					finishedHandshake = true;
				}
			}
			this._remoteVers = remoteVers;
			this._protocolVers = ourVers;
			if (finishedHandshake) {
				this._finishedHandshake();
			}
		} else {
            this.close(true);
			NET_CONN_LOG(' X - BAD TCP COMMAND');
			var err = {
				code:"ERR_REMOTE_BAD_TCP_COMMAND",
				message:"Remote side sent an unknown TCP Command ["+cmd+"]. Not a NetConnection or unsupported version."
			};
			this._handleError(err);
		}
	}

	_handleClose(had_error) {
        if (this._closed) return;
        this._closed = true;
        if (this._client && (this.transport !== 'native' || this.socket.ios) && !this._handshakeComplete) {
            this._handleError({code:'ERR_HANDSHAKE_CLOSED', transport:this.transport, message:'Connection closed before PDG handshake completed'}, false);
        }
        this._alive = false;
        this.hasDgram = false;
        clearTimeout(this._handshakeTimer);
        this._pendingData = false;
        if (this._dgramTimer && this._dgramTimer.cancel) this._dgramTimer.cancel();
		NET_CONN_LOG((this._client ? 'Client ' : 'Server ') + this.localAddr+':'+this.localPort + ' got close'+ ( had_error ? ' (error)':''));
		if (this._closeCallback) {
			try {
				this._closeCallback(this);
			} catch(e) {
				console.error('Net Connection Exception in Close Callback: ', JSON.stringify(e));
				if (this._client) {
					throw(e);
				}
			}
		}
		if (this._client && this._dgramSock) {
			NET_CONN_LOG('Client ' + this.localAddr+':'+this.localPort + ' close dgram socket');
			this._dgramSock.close();
		}
		this._dgramSock = false;
		this._dgramAlive = false;
	}

	_handleTimeout() {
		// timeout due to inactivity
		// close?
		this._alive = false;
	}

	_handleDrain() {
		// an early write which didn't get flushed to the kernel buffer
		// has now been completely written. May be useful for flow control
		// or throttling of some sort.
		// see also: socket.bufferSize, socket.pause() and socket.resume();
	}

	_handleEnd() {
		// other side has closed, but our pending write queue will still be
		// transmitted.
		this._alive = false;
	}

	_handleDgram(msg, rinfo) {
	    try {
			NET_CONN_LOG((this._client ? 'Client' : 'Server') + ' dgram from ' + rinfo.address+':'+rinfo.port);
			if (this.transport === 'native' && netBytes.decode(netBytes.bytes(msg)) == '_pdg-dgram-start') {
				NET_CONN_LOG((this._client ? 'Client' : 'Server') + ' got dgram start from ' + this.remoteAddr+':'+this.remotePort);
				this._dgramAlive = true;	// we got our Datagram start
				this.hasDgram = true;		// and now we know that Datagram communication is possible
			} else if (this._messageCallback) {
				try {
					var message = this._deserializeMessage(msg);
					this._messageCallback(message, this, 'udp');
				} catch(e) {
					console.error((this._client ? 'Client ' : 'Server ') + this.localAddr+':'+this.localPort+'/udp'
						+ ' message callback for message from '+this.remoteAddr+':'+this.remotePort+'/udp'
						+' threw Exception: '+JSON.stringify(e)
					);
					if (this._client) {
						throw(e);
					}
				}
			}
	    } catch(e) { 
	    	this._handleDgramError(e); 
	    }
	}

	_handleDgramListening() {
		// try to send a particular init packet to start the communications
		if ((this._dgramSock !== false) && (this._dgramStartsSent < this._maxDgramStarts)) {
			this._dgramStartsSent++;
			NET_CONN_LOG((this._client ? 'Client' : 'Server') + ' sending dgram start #'+this._dgramStartsSent+' to ' + this.remoteAddr+':'+this.remotePort);
			var buf = netBytes.encode('_pdg-dgram-start');
			this._dgramSock.send(buf, 0, buf.length, this.remotePort, this.remoteAddr, this._dgramSendCallback.bind(this));
			// do this at an interval until we get a response
			// at that point we can consider dgram as active
			this._dgramTimer = pdg.tm.onTimeout(function(evt) {
				this._handleDgramListening();
			}.bind(this), this._dgramStartInterval + (this._dgramStartsSent * this._dgramStartDelayFactor));
		}		
	}

	_handleDgramError(err) {
		// just mark it as closed
		NET_CONN_LOG((this._client ? 'Client ' : 'Server ') + this.localAddr+':'+this.localPort +' dgram Error: '+JSON.stringify(err));
		if (this._dgramSock) {
			this._dgramSock.close();
		}
		this._dgramSock = false;
		this._dgramAlive = false;
        this.hasDgram = false;
        if (this._dgramTimer && this._dgramTimer.cancel) this._dgramTimer.cancel();
	}

	_dgramSendCallback(err, bytes) {
		NET_CONN_LOG((this._client ? 'Client' : 'Server') + ' sent '+bytes+' byte dgram to ' + this.remoteAddr+':'+this.remotePort);
		if (err) {
			this._handleDgramError(err);
		}
	}
}

if(!(typeof exports === 'undefined')) {
    exports.NetConnection = NetConnection;
}

/* @pdg-schema
{
  "name": "NetworkSocket",
  "value": {
    "kind": "external",
    "module": "node:net",
    "export": "Socket",
    "types_package": "node"
  }
}
*/

/* @pdg-contract
{
  "name": "NetConnection.NetConnection",
  "value": {
    "params": {
      "socket": {
        "schema": "NetworkSocket"
      }
    },
    "optional_class": true
  }
}
*/

/* @pdg-schema
{
  "name": "NetworkError",
  "value": {
    "kind": "record",
    "fields": {
      "message": {
        "type": "string"
      },
      "code": {
        "type": "string",
        "optional": true
      },
      "transport": {
        "type": "string",
        "optional": true
      },
      "host": {
        "type": "string",
        "optional": true
      },
      "port": {
        "type": "number",
        "optional": true
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "JSONValue",
  "value": {
    "kind": "alias",
    "value": {
      "one_of": [
        {
          "type": "string"
        },
        {
          "type": "number"
        },
        {
          "type": "boolean"
        },
        {
          "type": "null"
        },
        {
          "items": {
            "schema": "JSONValue"
          }
        },
        {
          "values": {
            "schema": "JSONValue"
          }
        }
      ]
    }
  }
}
*/

/* @pdg-schema
{
  "name": "NetworkMessage",
  "value": {
    "kind": "alias",
    "value": {
      "one_of": [
        {
          "schema": "JSONValue"
        },
        {
          "type": "object MemBlock"
        },
        {
          "type": "object ISerializable"
        },
        {
          "schema": "ByteArray"
        }
      ]
    }
  }
}
*/

/* @pdg-contract
{
  "name": "NetConnection.send",
  "value": {
    "optional_class": true,
    "params": {
      "message": {
        "schema": "NetworkData",
        "when_type": "object"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "NetConnection.sendDgram",
  "value": {
    "optional_class": true,
    "params": {
      "message": {
        "schema": "NetworkData",
        "when_type": "object"
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "NetMessageCallback",
  "value": {
    "kind": "callback",
    "params": [
      {
        "name": "message",
        "schema": "NetworkMessage"
      },
      {
        "name": "connection",
        "type": "object NetConnection"
      },
      {
        "name": "transport",
        "one_of": [
          {
            "literal": "tcp"
          },
          {
            "literal": "udp"
          }
        ]
      }
    ],
    "returns": {
      "type": "void"
    }
  }
}
*/

/* @pdg-schema
{
  "name": "NetCloseCallback",
  "value": {
    "kind": "callback",
    "params": [
      {
        "name": "connection",
        "type": "object NetConnection"
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
  "name": "NetConnection.onMessage",
  "value": {
    "params": {
      "callback": {
        "schema": "NetMessageCallback"
      }
    },
    "optional_class": true
  }
}
*/

/* @pdg-contract
{
  "name": "NetConnection.onClose",
  "value": {
    "params": {
      "callback": {
        "schema": "NetCloseCallback"
      }
    },
    "optional_class": true
  }
}
*/

/* @pdg-schema
{
  "name": "NetworkData",
  "value": {
    "kind": "alias",
    "value": {
      "one_of": [
        {
          "type": "null"
        },
        {
          "items": {
            "schema": "JSONValue"
          }
        },
        {
          "values": {
            "schema": "JSONValue"
          }
        },
        {
          "schema": "ByteArray"
        }
      ]
    }
  }
}
*/

/* @pdg-schema
{
  "name": "NetworkSendable",
  "value": {
    "kind": "alias",
    "value": {
      "one_of": [
        {
          "type": "string"
        },
        {
          "schema": "NetworkData"
        },
        {
          "type": "object MemBlock"
        },
        {
          "type": "object ISerializable"
        }
      ]
    }
  }
}
*/
