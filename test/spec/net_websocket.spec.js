(function() {
    'use strict';
    if (!pdg.hasNetworkClient || (typeof process !== 'undefined' && process.versions && process.versions.jsc)) return;
    var browser = typeof document !== 'undefined';
    var endpoint = browser ? new URLSearchParams(location.search).get('webSocketEndpoint') : null;
    var server, client, connection, received, errors, ready, closed, clientInfo, nativeConnection, nativeReceived=[];
    var TestMessage = require('./fixtures/websocket/message_types').NetworkTestMessage;
    describe('WebSocket networking', function() {
        it('reports client and server capabilities', function() {
            expect(pdg.hasNetwork).toBe(true);
            expect(pdg.hasNetworkClient).toBe(true);
            expect(pdg.hasNetworkServer).toBe(!browser);
            if (browser) {
                expect(pdg.NetServer).toBeUndefined();
                var modules=FS.readdir('/js_modules');
                expect(modules.indexOf('netserver.js')).toBe(-1);
                expect(modules.indexOf('net_websocket_server.js')).toBe(-1);
                expect(modules.indexOf('net_ws_bundle.js')).toBe(-1);
                expect(FS.analyzePath('/spec/fixtures/websocket/localhost.key').exists).toBe(false);
                expect(FS.analyzePath('/spec/fixtures/websocket/echo_host.js').exists).toBe(false);
            }
        });
        it('authenticates using the PDG handshake over WSS', function() {
            received=[]; errors=[]; ready=false; closed=0;
            var started=Date.now();
            if(browser)window.PDG_NETWORK_TEST_RESULT={browser:navigator.userAgent,webTransportAPI:typeof WebTransport,requestedPolicy:'websocket-only',attemptedTransports:['websocket'],endpoint:endpoint};
            runs(function() {
                client = new pdg.NetClient({noDatagram:true});
                function connect() {
                    client.onError(function(error) { console.error('WSS test error:',error.code,error.message); errors.push(error);
                    if(browser)window.PDG_NETWORK_TEST_RESULT.finalErrorCode=error.code; }).connect(clientInfo, function(conn) {
                        connection=conn; ready=true;
                        if(browser)Object.assign(window.PDG_NETWORK_TEST_RESULT,{chosenTransport:conn.transport,secure:conn.secure,hasDgram:conn.hasDgram,attemptDurationMs:Date.now()-started,finalErrorCode:null});
                        conn.onMessage(function(message, _, carrier) { received.push({message:message,carrier:carrier}); });
                        conn.onClose(function() { closed++; });
                    }, 'websocket-test-key');
                }
                if (browser) {
                    if (!endpoint) { errors.push(new Error('Browser WebSocket endpoint missing from standalone harness')); return; }
                    clientInfo={webSocketUrl:endpoint,transportPolicy:'websocket-only'}; connect();
                } else {
                    var fs=require('fs'), path=require('path');
                    var fixtures=path.join(__dirname,'fixtures/websocket');
                    server=new pdg.NetServer({native:true,serverAddr:'127.0.0.1',serverPort:0,noDatagram:true,
                        reservationRequired:true,webSocket:{port:0,allowedOrigins:['https://game.test']},
                        tls:{certFile:path.join(fixtures,'localhost.crt'),keyFile:path.join(fixtures,'localhost.key')}});
                    server.expectClient('websocket-test-key');
                    server.onError(function(error) { console.error('WSS test error:',error.code,error.message); errors.push(error);
                    if(browser)window.PDG_NETWORK_TEST_RESULT.finalErrorCode=error.code; }).listen(function(conn) {
                        conn.onMessage(function(message) {
                            if (message==='broadcast-request') server.broadcast('broadcast-response');
                            else if (message==='close-request') conn.close(false);
                            else conn.send(message);
                        });
                        return true;
                    });
                    server.ready().then(function() {
                        clientInfo={webSocketUrl:'wss://127.0.0.1:'+server.listeners.websocket.port+'/pdg',
                            transportPolicy:'websocket-only',tls:{ca:fs.readFileSync(path.join(fixtures,'localhost.crt')),origin:'https://game.test'}};
                        connect();
                    }).catch(function(error) { console.error('WSS test error:',error.code,error.message); errors.push(error);
                    if(browser)window.PDG_NETWORK_TEST_RESULT.finalErrorCode=error.code; });
                }
            });
            waitsFor(function() {return ready || errors.length;},'WSS PDG handshake',10000);
            runs(function() {
                expect(errors.length).toBe(0); expect(ready).toBe(true);
                if (!connection) return;
                expect(connection.transport).toBe('websocket'); expect(connection.secure).toBe(true);
                expect(connection.hasDgram).toBe(false);
                if (browser) {expect(connection.localAddr).toBe('');expect(connection.remotePort).toBe(0);}
            });
        });
        if (!browser) it('accepts native and WebSocket clients on the same server', function() {
            runs(function() {
                new pdg.NetClient({noDatagram:true}).onError(function(error) { errors.push(error); })
                    .connect({host:'127.0.0.1',port:server.serverPort,transportPolicy:'native-only'},function(conn) {
                        nativeConnection=conn;
                        conn.onMessage(function(message) { nativeReceived.push(message); });
                    },'websocket-test-key');
            });
            waitsFor(function() { return nativeConnection || errors.length; },'native client alongside WSS',5000);
            runs(function() {
                expect(errors.length).toBe(0);
                expect(nativeConnection.transport).toBe('native');
                expect(server.connections.length).toBe(2);
            });
        });
        it('round trips every serialization tag and datagram fallback', function() {
            var mem=new pdg.Serializer();mem.serialize_1u(42);mem.serialize_1u(99);
            runs(function() {
                if (!connection) return;
                connection.send('Unicode: héllo 🌍');
                connection.send({score:42,players:['a','b']});
                connection.send(Uint8Array.from([0,127,255]));
                connection.send(mem.getDataPtr());
                connection.send(new TestMessage());
                connection.sendDgram('reliable fallback');
                connection.sendDgram(Uint8Array.from([0,127,255]));
                connection.sendDgram(new TestMessage());
            });
            waitsFor(function() {return received.length>=8 || errors.length;},'all WSS messages',10000);
            runs(function() {
                expect(errors.length).toBe(0);expect(received.length).toBe(8);
                if (received.length<8) return;
                expect(received[0].message).toBe('Unicode: héllo 🌍');
                expect(received[1].message).toEqual({score:42,players:['a','b']});
                expect(Array.from(received[2].message)).toEqual([0,127,255]);
                expect(received[3].message instanceof pdg.MemBlock).toBe(true);
                expect(Array.from(received[3].message.getData())).toEqual(Array.from(mem.getDataPtr().getData()));
                expect(received[4].message instanceof TestMessage).toBe(true);
                expect(received[4].message.one).toBe(15);expect(received[4].message.two).toBe(99);
                expect(received[5].message).toBe('reliable fallback');
                expect(Array.from(received[6].message)).toEqual([0,127,255]);
                expect(received[7].message instanceof TestMessage).toBe(true);
                expect(received[7].message.one).toBe(15);expect(received[7].message.two).toBe(99);
                received.forEach(function(item) {expect(item.carrier).toBe('tcp');});
            });
        });
        it('receives broadcasts and closes exactly once', function() {
            runs(function() {if(connection)connection.send('broadcast-request');});
            waitsFor(function() {return (received.length>=9 && (browser || nativeReceived.length)) || errors.length;},'WSS broadcast',5000);
            runs(function() {
                expect(errors.length).toBe(0);
                if(received[8])expect(received[8].message).toBe('broadcast-response');
                if (!browser) expect(nativeReceived[0]).toBe('broadcast-response');
                if(connection)connection.send('close-request');
            });
            waitsFor(function() {return closed || errors.length;},'WSS close',5000);
            runs(function() {expect(closed).toBe(1);});
        });
        it('reports rejected authentication once without reconnecting', function() {
            var reported=[], connected=0;
            runs(function() {
                if (!clientInfo) return;
                if (server) server.onError(function() {});
                new pdg.NetClient({noDatagram:true}).onError(function(err) {reported.push(err);})
                    .connect(clientInfo,function() {connected++;},'wrong-key');
            });
            waitsFor(function() {return reported.length;},'authentication rejection',7000);
            waits(100);
            runs(function() {expect(reported.length).toBe(1);expect(connected).toBe(0);if(server)server.shutdown(true,true);});
        });
    });
}());
