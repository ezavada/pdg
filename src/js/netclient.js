// -----------------------------------------------
// netclient.js
//
// Client side implementation of pdg network interface
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


var browserNetwork = typeof document !== 'undefined';
var iosNetwork = typeof process !== 'undefined' && process.versions && !!process.versions.jsc;
var net = browserNetwork ? null : require(iosNetwork ? 'net_ios_transport' : 'net');

// @pdg-class {"name":"NetClient"}
class NetClient {
	//! new Client(): create a network client for your game
// @pdg-member {"name":"NetClient.NetClient","type":"constructor","brief":"create a network client","returns":"object NetClient","params":[{"name":"opt","type":"object","optional":true,"default_value":"null"}]}
    constructor(opt) {
// @pdg-member {"name":"NetClient.connection","type":"object"}
// @pdg-contract {"name":"NetClient.connection","value":{"optional_class":true,"property":{"one_of":[{"type":"object NetConnection"},{"type":"boolean","literal":false}]},"legacy_type":"object"}}
        this.connection = false;
        this._errorCallback = false;
        this._connectCallback = false;
        this._allowDatagram = true;
        if (typeof opt != 'undefined' && opt !== null) {
            if (typeof opt.noDatagram != 'undefined') {
                this._allowDatagram = !opt.noDatagram
            }
        }
    }

	//! attempt to connect to a server for your game
	//! /param serverInfo the info for the server you want to connect to. Should be an object with
	//! /param clientKey the private key that identifies this as an authorized client
	//!        addr and port members, ie: { host: "localhost", port: 5454 }
	// @pdg-member {"name":"NetClient.connect","type":"function","brief":"connect to a server for your game","params":[{"name":"serverInfo","type":"object"},{"name":"callback","type":"function"},{"name":"clientKey","type":"string","optional":true,"default_value":"\"\""}],"returns":"this"}
	connect(serverInfo, callback, clientKey) {
        serverInfo = serverInfo || {};
        var policy = serverInfo.transportPolicy || 'auto';
        this._connectCallback = callback;
        if (['auto', 'native-only', 'websocket-only', 'webtransport-required'].indexOf(policy) === -1) {
            throw new TypeError('Unknown transportPolicy: ' + policy);
        }
        if (browserNetwork && policy === 'native-only') {
            var error = Object.assign(new Error('Requested transport is unavailable'), {code:'ERR_TRANSPORT_UNAVAILABLE', transport:policy});
            if (this._errorCallback) this._errorCallback(error, this); else throw error;
            return this;
        }
        if (browserNetwork || policy === 'websocket-only' || policy === 'webtransport-required' || (policy === 'auto' && (serverInfo.webSocketUrl || serverInfo.webTransportUrl))) {
            var report = function(error) {
                if (this._errorCallback) this._errorCallback(error, this); else console.error(error);
            }.bind(this);
            try {
                var selector = require((browserNetwork || typeof require.resolve !== 'function') ? 'net_transport_selector' : './net_transport_selector');
                this._transport = selector.connect(serverInfo, function(adapter) {
                    this.connection = new pdg.NetConnection(adapter);
                    var conn = this.connection;
                    conn._handshakeTimer = setTimeout(function() {
                        if (!conn._handshakeComplete && !conn._closed) {
                            conn._handleError({code:'ERR_HANDSHAKE_TIMEOUT', transport:adapter.transport, message:'PDG handshake timed out'});
                            conn.close(true);
                        }
                    }, adapter._pdgHandshakeTimeout || serverInfo.handshakeTimeout || serverInfo.timeout || 5000);
                    conn._clientInit(this, clientKey);
                }.bind(this), report, iosNetwork ? net.connectWebSocket : null);
            } catch (error) { report(error); }
            return this;
        }
        // have serverInfo, try to connect to it via TCP
        this._connectCallback = callback;
        var connectFinished = false;
        var connectTimer = false;
        var finishConnect = function() {
            if (connectFinished) {
                return false;
            }
            connectFinished = true;
            if (connectTimer) {
                clearTimeout(connectTimer);
                connectTimer = false;
            }
            return true;
        };
        var reportConnectError = function(error, socket) {
            if (!finishConnect()) {
                return;
            }
            if (socket && !socket.destroyed) {
                socket.destroy();
            }
            if (this.connection) {
                this.connection._handleError(error);
            } else if (this._errorCallback) {
                this._errorCallback(error, this);
            }
        }.bind(this);
        var socket = net.connect({port: serverInfo.port, host: serverInfo.host, maxPendingBytes:serverInfo.maxPendingBytes, maxFrameSize:serverInfo.maxFrameSize, timeout:iosNetwork ? serverInfo.timeout : undefined},
            function() { //'connect' listener
              if (!finishConnect()) {
                return;
              }
              try {
                this.connection = new pdg.NetConnection(socket);
                if (iosNetwork) {
                    var conn = this.connection;
                    conn._handshakeTimer = setTimeout(function() {
                        if (!conn._handshakeComplete && !conn._closed) {
                            conn._handleError({code:'ERR_HANDSHAKE_TIMEOUT', transport:'native', message:'PDG handshake timed out'});
                            conn.close(true);
                        }
                    }, serverInfo.handshakeTimeout || serverInfo.timeout || 5000);
                }
                this.connection._clientInit(this, clientKey);
              } catch(e) { 
                if (this._errorCallback) {
                  this._errorCallback(e);
                } else {
                  console.error("NetClient Exception connecting to "+serverInfo.host+":"+serverInfo.port+": "+JSON.stringify(e)); 
                }
              }
            }.bind(this));
        var connectTimeout = serverInfo.timeout || (iosNetwork ? 5000 : 0);
        if (typeof connectTimeout === 'number' && connectTimeout > 0) {
          connectTimer = setTimeout(function() {
            reportConnectError({
              code: 'ERR_CONNECT_TIMEOUT',
              message: 'Timed out connecting to ' + serverInfo.host + ':' + serverInfo.port
            }, socket);
          }, connectTimeout);
        }
        socket.on('error', function(error) {
          reportConnectError(error, socket);
        }.bind(this));
        return this;
    }

	//! setup error handler
	// @pdg-member {"name":"NetClient.onError","type":"function","brief":"set the callback function that will handle errors","params":[{"name":"callback","type":"function"}],"returns":"this"}
	onError(callback) {
        this._errorCallback = callback;
        return this;
    }
}

if(!(typeof exports === 'undefined')) {
    exports.NetClient = NetClient;
}

/* @pdg-schema
{
  "name": "NetClientOptions",
  "value": {
    "kind": "record",
    "fields": {
      "noDatagram": {
        "type": "boolean",
        "optional": true
      }
    }
  }
}
*/

/* @pdg-schema
{"name":"NodeTLSConnectionOptions","value":{"kind":"external","module":"node:tls","export":"ConnectionOptions","types_package":"node"}}
*/

/* @pdg-schema
{"name":"NativeWebTransportTLSOptions","value":{"kind":"record","fields":{"caFile":{"type":"string","optional":true}}}}
*/

/* @pdg-schema
{"name":"NetCertificateHash","value":{"kind":"record","fields":{"algorithm":{"literal":"sha-256"},"value":{"one_of":[{"builtin":"Uint8Array"},{"builtin":"ArrayBuffer"}]}}}}
*/

/* @pdg-schema
{
  "name": "NetServerAddress",
  "value": {
    "kind": "record",
    "fields": {
      "host": {
        "type": "string",
        "optional": true
      },
      "port": {
        "type": "number",
        "optional": true
      },
      "timeout": {
        "type": "number",
        "optional": true
      },
      "webSocketUrl": {
        "type": "string",
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
      "secure": {
        "type": "boolean",
        "optional": true
      },
      "handshakeTimeout": {
        "type": "number",
        "optional": true
      },
      "transportPolicy": {
        "type": "string",
        "optional": true
      },
      "tls": {
        "one_of": [{"schema":"NodeTLSConnectionOptions"},{"schema":"NativeWebTransportTLSOptions"}],
        "optional": true
      },
      "maxFrameSize": {
        "type": "number",
        "optional": true
      },
      "maxPendingBytes": {
        "type": "number",
        "optional": true
      },
      "webTransportUrl": {
        "type": "string",
        "optional": true
      },
      "webTransportTimeout": {
        "type": "number",
        "optional": true
      },
      "capabilityCacheTimeout": {
        "type": "number",
        "optional": true
      },
      "serverCertificateHashes": {
        "items": {
          "schema": "NetCertificateHash"
        },
        "optional": true
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "NetClient.NetClient",
  "value": {
    "params": {
      "opt": {
        "schema": "NetClientOptions",
        "nullable": true
      }
    },
    "optional_class": true
  }
}
*/

/* @pdg-schema
{
  "name": "NetConnectCallback",
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

/* @pdg-schema
{
  "name": "NetClientErrorCallback",
  "value": {
    "kind": "callback",
    "params": [
      {
        "name": "error",
        "schema": "NetworkError"
      },
      {
        "name": "endpoint",
        "type": "object NetClient",
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
  "name": "NetClient.onError",
  "value": {
    "params": {
      "callback": {
        "schema": "NetClientErrorCallback"
      }
    },
    "optional_class": true
  }
}
*/

/* @pdg-contract
{
  "name": "NetClient.connect",
  "value": {
    "params": {
      "serverInfo": {
        "schema": "NetServerAddress"
      },
      "callback": {
        "schema": "NetConnectCallback"
      }
    },
    "optional_class": true
  }
}
*/
