// Out-of-process standalone host for outbound Emscripten networking tests.
'use strict';
const fs = require('fs');
const path = require('path');
require('./message_types');
const certificate=require('../webtransport/certificate').create();
const blocked=require('dgram').createSocket('udp4');
const blockedReady=new Promise(resolve=>blocked.bind(0,'127.0.0.1',resolve));
const server = new pdg.NetServer({native:false, reservationRequired:true,
    webSocket:{port:0, allowedOrigins:[process.env.PDG_TEST_NETWORK_ORIGIN]},
    webTransport:{port:0,allowedOrigins:[process.env.PDG_TEST_NETWORK_ORIGIN],tls:certificate.tls},
    tls:{certFile:path.join(__dirname,'localhost.crt'),keyFile:path.join(__dirname,'localhost.key')}});
server.expectClient('websocket-test-key');
server.expectClient('webtransport-test-key');
server.onError(error=>console.error('WebSocket test host:',error.code,error.message)).listen(connection=>{
    connection.onMessage((message,_,carrier)=>{
        if (message === 'broadcast-request') server.broadcast('broadcast-response');
        else if (message === 'close-request') connection.close(false);
        else if(carrier==='udp')connection.sendDgram(message);
        else connection.send(message);
    });
    return true;
});
Promise.all([server.ready(),blockedReady]).then(()=>{
    fs.writeFileSync(process.env.PDG_TEST_NETWORK_ENDPOINT_FILE, JSON.stringify({
        webSocketUrl:'wss://127.0.0.1:'+server.listeners.websocket.port+'/pdg',
        webTransportUrl:'https://127.0.0.1:'+server.listeners.webtransport.port+'/pdg',webTransportHash:certificate.digest,blockedWebTransportUrl:'https://127.0.0.1:'+blocked.address().port+'/pdg',
        transport:'websocket', secure:true, hasDgram:false}));
}).catch(error=>{console.error(error);pdg.quit();});
process.on('SIGTERM',()=>{server.shutdown(true,true);blocked.close();certificate.remove();pdg.quit();});
