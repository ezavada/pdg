(function(){
    'use strict';
    if(!pdg.hasNetworkClient)return;
    var browser=typeof document!=='undefined',ios=typeof process!=='undefined' && process.versions && process.versions.jsc;
    var endpoint=browser?JSON.parse(new URLSearchParams(location.search).get('webTransportEndpoint') || '{}'):(ios?JSON.parse(process.env.PDG_TEST_IOS_NETWORK_ENDPOINT || '{}'):{});
    var server,certificate,blocked,connection,received=[],errors=[],closes=0,accepts=0;
    var TestMessage=require('./fixtures/websocket/message_types').NetworkTestMessage;
    function info(extra){return Object.assign({webTransportUrl:endpoint.webTransportUrl,serverCertificateHashes:[{algorithm:'sha-256',value:new Uint8Array(endpoint.webTransportHash || [])}],transportPolicy:'webtransport-required',timeout:4000},extra || {});}
    function connect(options,extra,key){
        new pdg.NetClient(options).onError(function(error){errors.push(error);}).connect(info(extra),function(conn){connection=conn;conn.onMessage(function(message,_,carrier){received.push({message:message,carrier:carrier});}).onClose(function(){closes++;});},key || 'webtransport-test-key');
    }
    describe('WebTransport networking',function(){
        it('authenticates over a TLS WebTransport reliable stream',function(){
            runs(function(){
                if(browser || ios){connect();return;}
                certificate=require('./fixtures/webtransport/certificate').create();
                blocked=require('dgram').createSocket('udp4');blocked.bind(0,'127.0.0.1');
                endpoint.webTransportHash=certificate.digest;
                server=new pdg.NetServer({serverAddr:'127.0.0.1',serverPort:0,noDatagram:false,reservationRequired:true,
                    webSocket:{port:0,secure:false,allowedOrigins:['*']},webTransport:{port:0,allowedOrigins:['']},tls:certificate.tls});
                server.expectClient('webtransport-test-key');
                server.onError(function(error){if(error.code!=='ERR_BAD_CLIENT_KEY')errors.push(error);}).listen(function(conn){
                    accepts++;conn.onMessage(function(message,_,carrier){if(message==='close-request')conn.close(false);else if(carrier==='udp')conn.sendDgram(message);else conn.send(message);});return true;
                });
                server.ready().then(function(){
                    expect(server.listeners.native.port>0).toBe(true);expect(server.listeners.websocket.port>0).toBe(true);
                    endpoint.webTransportUrl='https://127.0.0.1:'+server.listeners.webtransport.port+'/pdg';
                    endpoint.webSocketUrl='ws://127.0.0.1:'+server.listeners.websocket.port+'/pdg';endpoint.blockedWebTransportUrl='https://127.0.0.1:'+blocked.address().port+'/pdg';connect();
                }).catch(function(error){errors.push(error);});
            });
            waitsFor(function(){return connection || errors.length;},'WebTransport PDG handshake',7000);
            runs(function(){expect(errors.map(function(error){return error.code+': '+error.message;})).toEqual([]);expect(connection).toBeTruthy();if(connection){expect(connection.transport).toBe('webtransport');expect(connection.secure).toBe(true);expect(connection.hasDgram).toBe(true);}});
        });
        it('round trips Unicode, JSON, byte slices, MemBlock and ISerializable reliably',function(){
            var serializer=new pdg.Serializer();serializer.serialize_1u(42);
            runs(function(){if(!connection)return;connection.send('héllo 🌍');connection.send({score:42});connection.send(new Uint8Array([99,0,127,255,99]).subarray(1,4));connection.send(serializer.getDataPtr());connection.send(new TestMessage());});
            waitsFor(function(){return received.length>=5 || errors.length;},'WebTransport reliable messages',6000);
            runs(function(){expect(errors.length).toBe(0);expect(received.length).toBe(5);if(received.length<5)return;
                expect(received[0].message).toBe('héllo 🌍');expect(received[1].message).toEqual({score:42});expect(Array.from(received[2].message)).toEqual([0,127,255]);
                expect(received[3].message instanceof pdg.MemBlock).toBe(true);expect(Array.from(received[3].message.getData())).toEqual(Array.from(serializer.getDataPtr().getData()));
                expect(received[4].message instanceof TestMessage).toBe(true);expect(received[4].message.one).toBe(15);expect(received[4].message.two).toBe(99);
                received.forEach(function(item){expect(item.carrier).toBe('tcp');});received=[];
            });
        });
        it('exchanges datagrams and falls back to the stream for oversized messages',function(){
            runs(function(){if(connection){connection.sendDgram('héllo datagram');connection.sendDgram(new Array(2001).join('x'));}});
            waitsFor(function(){return received.length>=2 || errors.length;},'WebTransport datagram and reliable fallback',6000);
            runs(function(){expect(errors.length).toBe(0);expect(received.length).toBe(2);var datagrams=received.filter(function(item){return item.carrier==='udp';}),streams=received.filter(function(item){return item.carrier==='tcp';});
                expect(datagrams.length).toBe(1);expect(streams.length).toBe(1);if(datagrams.length)expect(datagrams[0].message).toBe('héllo datagram');if(streams.length)expect(streams[0].message.length).toBe(2000);received=[];
            });
        });
        it('closes once and clears datagram capability',function(){
            runs(function(){if(connection)connection.send('close-request');});waitsFor(function(){return closes || errors.length;},'WebTransport peer close',6000);waits(100);
            runs(function(){expect(closes).toBe(1);if(connection){expect(connection.hasDgram).toBe(false);connection.close(true);}});
        });
        it('supports a fresh connection with noDatagram',function(){
            runs(function(){connection=null;received=[];errors=[];closes=0;connect({noDatagram:true});});waitsFor(function(){return connection || errors.length;},'fresh WebTransport connection',6000);
            runs(function(){expect(errors.length).toBe(0);if(connection){expect(connection.hasDgram).toBe(false);connection.sendDgram('reliable-only');}});
            waitsFor(function(){return received.length || errors.length;},'WebTransport noDatagram fallback',5000);
            runs(function(){expect(received.length).toBe(1);if(received.length)expect(received[0].carrier).toBe('tcp');if(connection)connection.close(true);});
        });
        it('rejects an incorrect certificate hash without opening a PDG connection',function(){
            var rejected=[],opened=0;
            runs(function(){new pdg.NetClient().onError(function(error){rejected.push(error);}).connect(info({serverCertificateHashes:[{algorithm:'sha-256',value:new Uint8Array(32)}]}),function(conn){opened++;conn.close(true);});});
            waitsFor(function(){return rejected.length || opened;},'WebTransport certificate rejection',6000);waits(100);
            runs(function(){expect(opened).toBe(0);expect(rejected.length).toBe(1);if(rejected.length)expect(rejected[0].code).toBe(browser?'ERR_WEBTRANSPORT_CONNECT':'ERR_TLS_CERTIFICATE');});
        });
        if(!browser && !ios)it('rejects bad PDG keys without falling back or accepting the client',function(){
            var rejected=[],opened=0,before=accepts;
            runs(function(){new pdg.NetClient().onError(function(error){rejected.push(error);}).connect(info({transportPolicy:'auto',webSocketUrl:'ws://127.0.0.1:'+server.listeners.websocket.port+'/pdg',secure:false}),function(conn){opened++;conn.close(true);},'wrong-key');});
            waitsFor(function(){return rejected.length || opened;},'PDG key rejection',6000);waits(100);
            runs(function(){expect(opened).toBe(0);expect(rejected.length).toBe(1);expect(accepts).toBe(before);});
        });
        it('falls back to WebSocket within the overall deadline when UDP is blocked',function(){
            var fallback,echo=[],failed=[],started;
            runs(function(){started=Date.now();new pdg.NetClient().onError(function(error){failed.push(error);}).connect(info({transportPolicy:'auto',webTransportUrl:endpoint.blockedWebTransportUrl,webSocketUrl:endpoint.webSocketUrl,secure:browser,timeout:3000,webTransportTimeout:200,capabilityCacheTimeout:0}),function(conn){fallback=conn;conn.onMessage(function(message,_,carrier){echo.push({message:message,carrier:carrier});});conn.send('automatic-fallback');},'webtransport-test-key');});
            waitsFor(function(){return echo.length || failed.length;},'bounded WebTransport fallback',5000);
            runs(function(){expect(failed.length).toBe(0);expect(fallback).toBeTruthy();if(fallback){expect(fallback.transport).toBe('websocket');expect(fallback.hasDgram).toBe(false);fallback.close(true);}expect(echo.length).toBe(1);if(echo.length){expect(echo[0].message).toBe('automatic-fallback');expect(echo[0].carrier).toBe('tcp');}expect(Date.now()-started<3000).toBe(true);});
        });
        if(!browser && !ios)it('keeps accepted sessions alive when only the listener stops',function(){
            var current,echo=[],failed=[];
            runs(function(){new pdg.NetClient().onError(function(error){failed.push(error);}).connect(info(),function(conn){current=conn;conn.onMessage(function(message){echo.push(message);});},'webtransport-test-key');});
            waitsFor(function(){return current || failed.length;},'connection before listener stop',5000);
            runs(function(){expect(failed.length).toBe(0);server.shutdown(false);expect(server.listening).toBe(false);if(current)current.send('after-listener-stop');});
            waitsFor(function(){return echo.length || failed.length;},'live session after listener stop',5000);
            runs(function(){expect(failed.length).toBe(0);expect(echo).toEqual(['after-listener-stop']);if(current)current.close(true);});
        });
        it('cleans up the test session and host',function(){runs(function(){if(connection)connection.close(true);if(server)server.shutdown(true,true);if(blocked)blocked.close();if(certificate)certificate.remove();});});
    });
})();
