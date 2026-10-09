// Desktop counterpart for the iOS Simulator's outbound TCP/UDP tests.
'use strict';
pdg.run(); // Drive the engine timers used by UDP negotiation.
const fs = require('fs');
const net = require('net');
require('../websocket/message_types');
const certificate=require('../webtransport/certificate').create();
const blocked=require('dgram').createSocket('udp4');
const blockedReady=new Promise(resolve=>blocked.bind(0,'127.0.0.1',resolve));
const sockets = new Set();
const silent = net.createServer(socket=>{sockets.add(socket);socket.on('close',()=>sockets.delete(socket));socket.on('error',()=>{});});
const malformed = net.createServer(socket=>{socket.on('error',()=>{});socket.end(Buffer.from([86,0,3,98,97,100]));});
const path = require('path');
const secureServer = new pdg.NetServer({serverAddr:'127.0.0.1',native:false,webSocket:{port:0,allowedOrigins:['*']},
    tls:{certFile:path.join(__dirname,'../websocket/localhost.crt'),keyFile:path.join(__dirname,'../websocket/localhost.key')}});
secureServer.onError(()=>{}).listen(()=>true);
const server = new pdg.NetServer({serverAddr:'127.0.0.1',serverPort:0,reservationRequired:true,webSocket:{port:0,secure:false,allowedOrigins:['*']},webTransport:{port:0,allowedOrigins:['']},tls:certificate.tls});
server.expectClient('ios-test-key');
server.expectClient('webtransport-test-key');
server.onError(()=>{}).listen(connection=>{
    connection.onMessage((message, _, carrier)=>{
        if(message === 'close-request') connection.close(false);
        else if(message === 'endpoint-request') connection.send({clientPort:connection.remotePort,serverPort:connection.localPort});
        else if(carrier === 'udp') connection.sendDgram(message);
        else connection.send(message);
    });
    return true;
});
Promise.all([blockedReady,server.ready(),secureServer.ready(),new Promise(resolve=>silent.listen(0,'127.0.0.1',resolve)),new Promise(resolve=>malformed.listen(0,'127.0.0.1',resolve))]).then(()=>{
    fs.writeFileSync(process.env.PDG_TEST_NETWORK_ENDPOINT_FILE,JSON.stringify({host:'127.0.0.1',port:server.listeners.native.port,
        webTransportUrl:'https://127.0.0.1:'+server.listeners.webtransport.port+'/pdg',webTransportHash:certificate.digest,blockedWebTransportUrl:'https://127.0.0.1:'+blocked.address().port+'/pdg',
        secureWebSocketUrl:'wss://127.0.0.1:'+secureServer.listeners.websocket.port+'/pdg',webSocketUrl:'ws://127.0.0.1:'+server.listeners.websocket.port+'/pdg',silentPort:silent.address().port,malformedPort:malformed.address().port}));
}).catch(error=>{console.error(error);pdg.quit();});
process.on('SIGTERM',()=>{sockets.forEach(socket=>socket.destroy());silent.close();malformed.close();server.shutdown(true,true);secureServer.shutdown(true,true);blocked.close();certificate.remove();pdg.quit();});
