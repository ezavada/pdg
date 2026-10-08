(function() {
    'use strict';
    if (typeof process === 'undefined' || !process.versions || !process.versions.jsc) return;
    var endpoint = JSON.parse(process.env.PDG_TEST_IOS_NETWORK_ENDPOINT || '{}');
    var TestMessage = require('./fixtures/websocket/message_types').NetworkTestMessage;
    var connection, received = [], errors = [], closed = 0;
    function connect(options) {
        var client = new pdg.NetClient(options);
        client.onError(function(error) {errors.push(error);});
        client.connect({host:endpoint.host,port:endpoint.port,timeout:3000},function(conn) {
            connection=conn;
            conn.onMessage(function(message, _, carrier) {received.push({message:message,carrier:carrier});});
            conn.onClose(function() {closed++;});
        },'ios-test-key');
        return client;
    }
    describe('iOS TCP/UDP client', function() {
        it('exposes client-only networking',function() {
            expect(pdg.hasNetwork).toBe(true);expect(pdg.hasNetworkClient).toBe(true);
            expect(pdg.hasNetworkServer).toBe(false);expect(pdg.NetServer).toBeUndefined();
            expect(endpoint.port > 0).toBe(true);
        });
        it('authenticates and populates native endpoints',function() {
            runs(function() {connect();});
            waitsFor(function() {return connection || errors.length;},'TCP handshake',5000);
            runs(function() {
                expect(errors.length).toBe(0);expect(connection).toBeTruthy();
                if(!connection)return;
                expect(connection.transport).toBe('native');expect(connection.secure).toBe(false);
                expect(connection.localAddr).toBe('127.0.0.1');expect(connection.remoteAddr).toBe(endpoint.host);
                expect(connection.localPort > 0).toBe(true);expect(connection.remotePort).toBe(endpoint.port);
                connection.send('endpoint-request');
            });
            waitsFor(function() {return received.length || errors.length;},'server endpoint snapshot',5000);
            runs(function() {if(received.length)expect(received.shift().message).toEqual({clientPort:connection.localPort,serverPort:connection.remotePort});});
        });
        it('round trips Unicode, JSON, byte slices, MemBlock and ISerializable',function() {
            var serializer=new pdg.Serializer();serializer.serialize_1u(42);
            runs(function() {
                if(!connection)return;
                connection.send('héllo 🌍');connection.send({score:42});
                connection.send(new Uint8Array([99,0,127,255,99]).subarray(1,4));
                connection.send(serializer.getDataPtr());connection.send(new TestMessage());
            });
            waitsFor(function() {return received.length >= 5 || errors.length;},'serialized TCP messages',5000);
            runs(function() {
                expect(errors.length).toBe(0);expect(received.length).toBe(5);
                if(received.length<5)return;
                expect(received[0].message).toBe('héllo 🌍');expect(received[1].message).toEqual({score:42});
                expect(Array.from(received[2].message)).toEqual([0,127,255]);
                expect(received[3].message instanceof pdg.MemBlock).toBe(true);
                expect(Array.from(received[3].message.getData())).toEqual(Array.from(serializer.getDataPtr().getData()));
                expect(received[4].message instanceof TestMessage).toBe(true);
                expect(received[4].message.one).toBe(15);expect(received[4].message.two).toBe(99);
                received.forEach(function(item) {expect(item.carrier).toBe('tcp');});received=[];
            });
        });
        it('negotiates UDP on the TCP local port and reliably falls back for large datagrams',function() {
            waitsFor(function() {return (connection && connection.hasDgram) || errors.length;},'UDP negotiation',10000);
            runs(function() {
                expect(errors.length).toBe(0);expect(connection && connection.hasDgram).toBe(true);
                if(connection){connection.sendDgram('héllo UDP');connection.sendDgram(new Array(2001).join('x'));}
            });
            waitsFor(function() {return received.length >= 2 || errors.length;},'UDP echo and TCP fallback',5000);
            runs(function() {
                expect(errors.length).toBe(0);expect(received.length).toBe(2);
                var udp=received.filter(function(item) {return item.carrier==='udp';});
                var tcp=received.filter(function(item) {return item.carrier==='tcp';});
                expect(udp.length).toBe(1);expect(tcp.length).toBe(1);
                if(udp.length)expect(udp[0].message).toBe('héllo UDP');
                if(tcp.length)expect(tcp[0].message.length).toBe(2000);
                received=[];
            });
        });
        it('closes once and clears UDP capability',function() {
            runs(function() {if(connection)connection.send('close-request');});
            waitsFor(function() {return closed || errors.length;},'peer close',5000);
            waits(100);
            runs(function() {expect(closed).toBe(1);if(connection){expect(connection.hasDgram).toBe(false);connection.close(true);}});
        });
        it('supports noDatagram and reconnecting with a fresh client',function() {
            connection=null;received=[];errors=[];closed=0;
            runs(function() {connect({noDatagram:true});});
            waitsFor(function() {return connection || errors.length;},'second connection',5000);
            runs(function() {if(connection)connection.sendDgram('fallback');});
            waitsFor(function() {return received.length || errors.length;},'reliable fallback',5000);
            runs(function() {expect(errors.length).toBe(0);if(connection){expect(connection.hasDgram).toBe(false);connection.close(true);}if(received.length)expect(received[0].carrier).toBe('tcp');});
        });
        function fails(name, port, key, code) {
            it(name,function() {
                var reported=[],connected=0;
                runs(function() {
                    new pdg.NetClient({noDatagram:true}).onError(function(error) {reported.push(error);})
                        .connect({host:endpoint.host,port:port,timeout:1000,handshakeTimeout:150},function() {connected++;},key);
                });
                waitsFor(function() {return reported.length;},'connection failure',3000);
                waits(100);
                runs(function() {expect(connected).toBe(0);expect(reported.length).toBe(1);if(code && reported.length)expect(reported[0].code).toBe(code);});
            });
        }
        fails('reports reservation rejection once',endpoint.port,'wrong-key');
        fails('bounds a silent handshake',endpoint.silentPort,'','ERR_HANDSHAKE_TIMEOUT');
        fails('rejects a malformed handshake',endpoint.malformedPort,'','ERR_UNSUPPORTED_PROTOCOL');
        it('authenticates WebSocket and sends serialized messages with reliable datagram fallback',function() {
            var ws, messages=[], failures=[];
            runs(function() {
                new pdg.NetClient().onError(function(error) {failures.push(error);})
                    .connect({webSocketUrl:endpoint.webSocketUrl,secure:false,transportPolicy:'auto'},function(conn) {
                        ws=conn;conn.onMessage(function(message,_,carrier) {messages.push({message:message,carrier:carrier});});
                        conn.send('héllo 🌍');conn.send({score:42});conn.sendDgram(new Uint8Array([0,127,255]));
                    },'ios-test-key');
            });
            waitsFor(function() {return messages.length===3 || failures.length;},'WebSocket echo',5000);
            runs(function() {
                expect(failures.length).toBe(0);expect(ws).toBeTruthy();expect(messages.length).toBe(3);
                if(ws){expect(ws.transport).toBe('websocket');expect(ws.secure).toBe(false);expect(ws.hasDgram).toBe(false);ws.close(false);}
                if(messages.length===3){expect(messages[0].message).toBe('héllo 🌍');expect(messages[1].message).toEqual({score:42});expect(Array.from(messages[2].message)).toEqual([0,127,255]);}
            });
        });
        it('rejects an untrusted WSS certificate once',function() {
            var reported=[],connected=0;
            runs(function() {
                new pdg.NetClient().onError(function(error) {reported.push(error);})
                    .connect({webSocketUrl:endpoint.secureWebSocketUrl,transportPolicy:'websocket-only'},function() {connected++;});
            });
            waitsFor(function() {return reported.length;},'certificate rejection',6000);
            waits(100);
            runs(function() {expect(connected).toBe(0);expect(reported.length).toBe(1);if(reported.length)expect(reported[0].transport).toBe('websocket');});
        });
        it('requires explicit permission for insecure WebSockets',function() {
            var error;
            new pdg.NetClient().onError(function(value) {error=value;}).connect({webSocketUrl:endpoint.webSocketUrl},function() {});
            expect(error).toBeTruthy();
        });
    });
}());
