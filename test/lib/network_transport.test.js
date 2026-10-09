'use strict';
const assert = require('assert');
const fs = require('fs');
const vm = require('vm');
const path = require('path');
const {EventEmitter} = require('events');
const root = path.resolve(__dirname, '../..');
const bytes = require('../../src/js/net_bytes');
const {NetConnection} = require('../../src/js/netconnection');
const {NetServer} = require('../../src/js/netserver');
const {NetClient} = require('../../src/js/netclient');
const {WebSocketTransport} = require('../../src/js/net_transport');
const {WebSocket} = require('../../src/js/net_ws_bundle');
global.pdg = {NetConnection, tm:{getMilliseconds:Date.now}};
const delay = ms => new Promise(resolve => setTimeout(resolve, ms));
function connection() {
    const socket = new EventEmitter();
    Object.assign(socket, {transport:'websocket', secure:true, address:()=>({address:'',port:0}),
        write:()=>true, setKeepAlive:()=>{}, end:()=>{}, destroy:()=>socket.emit('close')});
    const conn = new NetConnection(socket);
    conn._alive = true;
    conn._handshakeComplete = true;
    return conn;
}
async function test() {
    require('child_process').execFileSync(process.execPath, ['tools/bundle-websocket.js', '--check'], {cwd:root});
    const browserBytes = {exports:{}, Uint8Array, ArrayBuffer, DataView, TextEncoder, TextDecoder};
    vm.runInNewContext(fs.readFileSync(path.join(root, 'src/js/net_bytes.js'), 'utf8'), browserBytes);
    assert.deepEqual(browserBytes.exports.encode('héllo'), bytes.encode('héllo'));
    assert.equal(browserBytes.exports.decode(bytes.encode('héllo')), 'héllo');
    const sub = Uint8Array.from([0, 1, 2, 3, 4, 5]).subarray(1, 5);
    assert.equal(bytes.read(sub, 0, 4), 0x01020304);
    // Every possible split through a header and payload, then coalesced commands.
    for (let split = 1; split < 12; split++) {
        const conn = connection(); const received = [];
        conn._handleTcpCommand = (cmd, value) => received.push([cmd, value]);
        const frame = bytes.concat(conn._frameTcpCommand('K', 'héllo'), conn._frameTcpCommand('V', '1'));
        conn._handleTcpData(frame.subarray(0, split));
        conn._handleTcpData(frame.subarray(split));
        assert.deepEqual(received, [['K','héllo'], ['V','1']]);
        assert.equal(conn._pendingData, false);
    }
    const conn = connection(); const frames = [];
    conn._deserializeMessage = value => Array.from(value);
    conn.onMessage((msg, _, carrier) => frames.push([msg,carrier]));
    const frame = conn._frameTcpData(Uint8Array.from([1,2,3]));
    for (const value of frame) conn._handleTcpData(Uint8Array.of(value));
    assert.deepEqual(frames, [[[1,2,3],'tcp']]);
    let closes=0; conn.onClose(()=>closes++); conn._handleClose(); conn._handleClose(); assert.equal(closes,1);
    const oversized = connection(); let errors=[];
    oversized._errorCallback = err=>errors.push(err.code); oversized.maxFrameSize=2;
    oversized._handleTcpData(frame.subarray(0,5)); assert.deepEqual(errors,['ERR_FRAME_TOO_LARGE']); assert.equal(oversized._alive,false);
    const premature = connection(); premature._handshakeComplete=false;
    premature._errorCallback=err=>errors.push(err.code); premature._handleTcpData(frame);
    assert.equal(errors[1],'ERR_HANDSHAKE_REQUIRED');
    const fakeWS = new EventEmitter(); Object.assign(fakeWS,{readyState:1,bufferedAmount:0,send:()=>{},close:()=>{},terminate:()=>{}});
    const adapter = new WebSocketTransport(fakeWS,{maxPendingBytes:2});
    let adapterErrors=[]; adapter.on('error',err=>adapterErrors.push(err.code));
    assert.equal(adapter.write(Uint8Array.of(1,2,3)),false);
    fakeWS.emit('message','text',false); assert.deepEqual(adapterErrors,['ERR_BACKPRESSURE']);
    const textWS = new EventEmitter(); Object.assign(textWS,{readyState:1,close:()=>{}});
    const textAdapter = new WebSocketTransport(textWS); textAdapter.on('error',err=>adapterErrors.push(err.code));
    textWS.emit('message','text',false); assert.equal(adapterErrors[1],'ERR_WEBSOCKET_TEXT');
    const policies = new NetClient().onError(err=>errors.push(err.code));
    policies.connect({transportPolicy:'webtransport-required'},()=>assert.fail());
    assert.equal(errors[errors.length-1],'ERR_TRANSPORT_UNAVAILABLE');
    const reservations=new NetServer({reservationRequired:true});
    reservations.expectClient('forever','*',undefined,true);
    assert.equal(reservations._reservations[0].until,-1);
    assert.equal(reservations._checkClientIP('127.0.0.1'),true);
    assert.equal(reservations._checkClientKey('forever','127.0.0.1'),true);
    assert.equal(reservations._checkClientKey('forever','127.0.0.1'),false);
    reservations.expectClient('expired','*',-10,true);
    assert.equal(reservations._checkClientKey('expired','127.0.0.1'),false);
    const server = new NetServer({serverPort:0, serverAddr:'127.0.0.1', noDatagram:true,
        webSocket:{port:0,secure:false,allowedOrigins:['https://game.example']}}).onError(()=>{});
    server.listen(()=>true);
    const addresses = await server.ready(); assert.equal(addresses.length,2);
    assert.equal(server.listeners.native.port,server.serverPort);
    const endpoint = 'ws://127.0.0.1:' + server.listeners.websocket.port + '/pdg';
    async function rejected(url, protocol, origin) {
        await new Promise((resolve,reject) => {
            const ws = new WebSocket(url,protocol,{origin});
            ws.on('open',()=>{ws.terminate();reject(Error('Unexpected upgrade acceptance'));});
            ws.on('error',()=>resolve());
        });
    }
    await rejected(endpoint,'pdg-net-v1','https://evil.example');
    await rejected(endpoint,'wrong','https://game.example');
    await rejected(endpoint.replace('/pdg','/wrong'),'pdg-net-v1','https://game.example');
    const client = new NetClient({noDatagram:true});
    const established = await new Promise((resolve,reject)=>client.onError(reject).connect({webSocketUrl:endpoint, secure:false,
        tls:{origin:'https://game.example'}},resolve));
    assert.equal(established.transport,'websocket'); assert.equal(established.secure,false); assert.equal(established.hasDgram,false);
    await delay(10); assert.equal(server.connections.length,1);
    server.shutdown(true,true); await delay(30); assert.equal(server.connections.length,0);
    server.shutdown(true,true);
    for (let cycle=0;cycle<3;cycle++) {
        server.listen(()=>true); await server.ready(); server.shutdown(true,true); await delay(20);
    }
    const rollback = new NetServer({serverAddr:'127.0.0.1',serverPort:0,noDatagram:true,
        webSocket:{port:0,secure:true}}).onError(()=>{}).listen(()=>true);
    await assert.rejects(rollback.ready()); await delay(30); assert.equal(rollback.listening,false);
    assert.equal(rollback._listener.listening,false);
    const conflict = new NetServer({serverPort:5443, webSocket:{port:5443,secure:false}}).onError(()=>{}).listen(()=>true);
    await assert.rejects(conflict.ready(),err=>err.code==='ERR_LISTENER_PORT_CONFLICT'); await delay(20);
    const partialErrors=[];
    const partial = new NetServer({serverAddr:'127.0.0.1',serverPort:0,noDatagram:true,allowPartialListen:true,
        webSocket:{port:0,secure:true}}).onError(err=>partialErrors.push(err)).listen(()=>true);
    const partialAddresses=await partial.ready(); assert.equal(partialAddresses.length,1);
    assert.equal(partialErrors.length,1); partial.shutdown(true,true); await delay(20);
    const cancelled = new NetServer({serverPort:0,noDatagram:true}).onError(()=>{}).listen(()=>true);
    cancelled.shutdown(); await assert.rejects(cancelled.ready());
    const secure = new NetServer({native:false,webSocket:{port:0,allowedOrigins:['https://game.example']},
        tls:{certFile:path.join(__dirname,'../spec/fixtures/websocket/localhost.crt'),keyFile:path.join(__dirname,'../spec/fixtures/websocket/localhost.key')}}).onError(()=>{}).listen(()=>true);
    await secure.ready();
    const secureConn = await new Promise((resolve,reject)=>new NetClient({noDatagram:true}).onError(reject).connect({
        webSocketUrl:'wss://127.0.0.1:'+secure.listeners.websocket.port+'/pdg',
        tls:{ca:fs.readFileSync(path.join(__dirname,'../spec/fixtures/websocket/localhost.crt')),origin:'https://game.example'}},resolve));
    assert.equal(secureConn.secure,true); secure.shutdown(true,true); await delay(30);
    // Inspect the actual list used by the Emscripten linker, not a duplicate manifest.
    const makefile = fs.readFileSync(path.join(root,'tools/pdg-js.mak'),'utf8');
    const embedded = makefile.split('RUNTIME_JS_FILES=')[1].split('# UI scripts')[0];
    assert(embedded.includes('/netclient.js@')); assert(embedded.includes('/netconnection.js@'));
    assert(!embedded.includes('netserver')); assert(!embedded.includes('net_websocket_server')); assert(!embedded.includes('net_ws_bundle'));
    console.log('Network transport checks passed (framing, limits, WSS, origins, listener rollback, browser packaging)');
}
test().catch(err=>{console.error(err);process.exit(1);});
