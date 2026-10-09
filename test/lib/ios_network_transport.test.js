'use strict';
const assert = require('assert');
const fs = require('fs');
const vm = require('vm');
const EventEmitter = require('events');
const bytes = require('../../src/js/net_bytes');
const context = {exports:{}, Uint8Array, ArrayBuffer, DataView};
vm.runInNewContext(fs.readFileSync('src/js/net_bytes.js','utf8'), context);
for (const text of ['', 'ASCII', 'héllo 🌍', '\u0000\u07ff\u0800\uffff', '\ud800x\udc00', '\udbff\udfff']) {
    assert.deepEqual(context.exports.encode(text), bytes.encode(text));
    assert.equal(context.exports.decode(bytes.encode(text)), bytes.decode(bytes.encode(text)));
}
// Exercise every byte and malformed UTF-8 sequences without Node or Web codecs.
for (let first=0;first<256;first++) {
    for (const suffix of [[],[0],[128],[191],[255],[128,128,128]]) {
        const value = Uint8Array.from([first,...suffix]);
        assert.equal(context.exports.decode(value), Buffer.from(value).toString('utf8'));
    }
}
let deliver, opened, writes=[], closed=[], udpStarted=[];
const bridge = {
    open:(host,port,callback,limit)=>{opened={host,port,limit};deliver=callback;return 7;},
    write:(id,data,udp)=>{writes.push({id,data:Array.from(data),udp});return true;},
    udp:id=>udpStarted.push(id),close:(id,force)=>closed.push([id,force]),closeUDP:id=>closed.push([id,'udp'])
};
const sandbox={exports:{},process:{_iosNetwork:bridge},require:name=>{
    if(name==='events')return {EventEmitter};
    if(name==='net_transport')return require('../../src/js/net_transport');
    throw Error('Unexpected Node dependency: '+name);
}};
vm.runInNewContext(fs.readFileSync('src/bindings/jsc-ios/net_ios_transport.js','utf8'),sandbox);
let connected=0;
const socket=sandbox.exports.connect({host:'127.0.0.1',port:5000,maxFrameSize:4096,maxPendingBytes:8192},()=>connected++);
assert.deepEqual(opened,{host:'127.0.0.1',port:5000,limit:8192});
deliver('connect',{local:{address:'127.0.0.1',port:12345},remote:{address:'127.0.0.1',port:5000}});
assert.equal(connected,1);assert.equal(socket.address().port,12345);assert.equal(socket.remotePort,5000);
assert.equal(socket.maxFrameSize,4096);assert.equal(socket.transport,'native');assert.equal(socket.secure,false);
let tcpData,udpData,listening=0,closeCount=0,udpErrors=[];
socket.on('data',data=>tcpData=data).on('close',()=>closeCount++);
const udp=socket.createDatagramSocket();
udp.on('listening',()=>listening++).on('message',(data,peer)=>udpData={data,peer}).on('error',error=>udpErrors.push(error));
udp.bind();assert.deepEqual(udpStarted,[7]);deliver('udpReady',null);assert.equal(listening,1);
const data=new Uint8Array([99,1,2,3,99]);socket.write(data.subarray(1,4));
udp.send(data,1,3,5000,'127.0.0.1',()=>{});
assert.deepEqual(writes,[{id:7,data:[1,2,3],udp:false},{id:7,data:[1,2,3],udp:true}]);
deliver('data',data);deliver('datagram',data);
assert.equal(tcpData,data);assert.equal(udpData.data,data);assert.equal(udpData.peer.port,5000);
deliver('udpError',{code:'ERR_UDP_CONNECT'});assert.equal(udpErrors.length,1);
udp.close();socket.end();socket.destroy();deliver('close',null);
assert.deepEqual(closed,[[7,'udp'],[7,false],[7,true]]);assert.equal(closeCount,1);assert.equal(socket.destroyed,true);
assert.equal(socket.write(data),false);
console.log('PASS iOS socket facade and UTF-8 codecs');
if (process.platform === 'darwin') {
    const cp=require('child_process'),path=require('path'),net=require('net'),dgram=require('dgram');
    const folder=fs.mkdtempSync(path.join(process.env.PDG_TEST_TEMP_DIR || require('os').tmpdir(),'pdg-ios-network-'));
    const binary=path.join(folder,'bridge-test');
    cp.execFileSync('xcrun',['clang++','-std=c++17','-fobjc-arc','-framework','Foundation','-framework','Network','-framework','JavaScriptCore',
        '-Isrc/bindings/jsc-ios','src/bindings/jsc-ios/pdg_ios_network.mm','test/cxx/ios_network_bridge_test.mm','-o',binary],{stdio:'inherit'});
    const WS=require('../../src/js/net_ws_bundle').WebSocketServer;
    const ws=new WS({host:'127.0.0.1',port:0,handleProtocols:(protocols,request)=>request.url==='/no-protocol'?false:'pdg-net-v1'});
    ws.on('connection',(socket,request)=>{
        if(request.url==='/text')socket.send('invalid text');
        else socket.on('message',data=>socket.send(data));
    });
    const sockets=new Set();
    const echo=net.createServer(socket=>{sockets.add(socket);socket.on('data',data=>socket.write(data));socket.on('error',()=>{});socket.on('close',()=>sockets.delete(socket));});
    const flood=net.createServer(socket=>{sockets.add(socket);socket.on('error',()=>{});socket.on('close',()=>sockets.delete(socket));socket.write(Buffer.alloc(4096));});
    const udp=dgram.createSocket('udp4');
    udp.on('message',(data,peer)=>udp.send(data,peer.port,peer.address));
    (async()=>{
        try {
            await new Promise(resolve=>ws.address()?resolve():ws.on('listening',resolve));
            await new Promise(resolve=>echo.listen(0,'127.0.0.1',resolve));
            await new Promise(resolve=>flood.listen(0,'127.0.0.1',resolve));
            await new Promise(resolve=>udp.bind(echo.address().port,'127.0.0.1',resolve));
            await new Promise((resolve,reject)=>{
                const child=cp.spawn(binary,[String(echo.address().port),String(flood.address().port),String(ws.address().port)],{stdio:'inherit'});
                const deadline=setTimeout(()=>{child.kill('SIGKILL');reject(Error('Native bridge test timed out'));},20000);
                child.on('error',reject);child.on('exit',code=>{clearTimeout(deadline);code===0?resolve():reject(Error('Native bridge test failed: '+code));});
            });
        } finally {
            sockets.forEach(socket=>socket.destroy());echo.close();flood.close();udp.close();ws.close();fs.rmSync(folder,{recursive:true,force:true});
        }
    })().catch(error=>{console.error(error);process.exitCode=1;});
}
