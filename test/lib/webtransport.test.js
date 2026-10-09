'use strict';
const assert=require('assert'),fs=require('fs'),vm=require('vm');
const facade=require('../../src/js/net_transport');
const {NetConnection}=require('../../src/js/netconnection');
const tick=()=>new Promise(resolve=>setImmediate(resolve));
function buildTargetTest() {
    const source=fs.readFileSync('tools/node-pdg/build-webtransport.js','utf8');
    for(const [platform,env,target] of [
        ['darwin',{},'13.5'],
        ['darwin',{MACOSX_DEPLOYMENT_TARGET:'14.0'},'14.0'],
        ['linux',{},null]
    ]) {
        const calls=[],exports={};
        vm.runInNewContext(source,{
            exports,process:{platform,arch:'arm64',env,cwd:()=>'/package'},
            require(name) {
                if(name==='fs')return {copyFileSync(){}};
                if(name==='path')return require('path');
                if(name==='child_process')return {spawnSync(command,args){calls.push(args);return {status:0};}};
                throw Error('Unexpected dependency: '+name);
            }
        });
        exports.build(2);
        const deployment=calls[0].filter(arg=>arg.startsWith('-DCMAKE_OSX_DEPLOYMENT_TARGET='));
        assert.deepEqual(deployment,target?['-DCMAKE_OSX_DEPLOYMENT_TARGET='+target]:[]);
    }
}
function load(name,context){context.exports={};vm.runInNewContext(fs.readFileSync('src/js/'+name+'.js','utf8'),context,{filename:name+'.js'});return context.exports;}
function selectorTest(){
    let wt=[],ws=[],now=1000;
    const context={document:{},Date:{now:()=>now},Map,JSON,Object,Error,require:name=>{
        if(name==='net_transport')return facade;
        return {connect:(opts,ready,failed)=>{const call={opts,ready,failed,closed:0};call.socket={destroy:()=>call.closed++};(name==='net_webtransport_client'?wt:ws).push(call);return call.socket;}};
    }};
    const selector=load('net_transport_selector',context);
    let opened=0,errors=[];
    selector.connect({host:'game.test',timeout:4000,handshakeTimeout:5000},()=>opened++,e=>errors.push(e));
    assert.equal(wt.length,1);assert.equal(wt[0].opts.timeout,1500);
    now+=1500;wt[0].failed({code:'ERR_CONNECT_TIMEOUT'});assert.equal(wt[0].closed,1);assert.equal(ws.length,1);assert.equal(ws[0].opts.timeout,2500);
    wt[0].ready(wt[0].socket);assert.equal(opened,0);assert.equal(wt[0].closed,2);
    now+=500;ws[0].ready(ws[0].socket);assert.equal(opened,1);assert.equal(ws[0].socket._pdgHandshakeTimeout,2000);
    // Capability cache is bounded and configuration-specific.
    selector.connect({host:'game.test'},()=>{},()=>{});assert.equal(wt.length,1);assert.equal(ws.length,2);
    now+=31000;selector.connect({host:'game.test'},()=>{},()=>{});assert.equal(wt.length,2);
    for(const code of ['ERR_TLS_CERTIFICATE','ERR_WEBTRANSPORT_CONNECT','ERR_BAD_CLIENT_KEY','ERR_PROTOCOL_VERSION','ERR_WEBTRANSPORT_REJECTED']){
        selector.connect({host:code},()=>assert.fail(),e=>errors.push(e));wt.at(-1).failed({code});assert.equal(ws.length,2);assert.equal(errors.at(-1).code,code);
    }
    selector.connect({transportPolicy:'webtransport-required',host:'required'},()=>{},e=>errors.push(e));wt.at(-1).failed({code:'ERR_TRANSPORT_UNAVAILABLE'});assert.equal(ws.length,2);
    selector.connect({transportPolicy:'websocket-only',host:'ws'},()=>{},()=>{});assert.equal(ws.length,3);
    const controller=selector.connect({host:'cancelled'},()=>assert.fail(),()=>assert.fail());controller.destroy();wt.at(-1).ready(wt.at(-1).socket);assert.equal(ws.length,3);
    selector.connect({host:'missing'},()=>{},()=>{});wt.at(-1).failed({code:'ERR_TRANSPORT_UNAVAILABLE'});assert.equal(ws.length,4);
    assert.throws(()=>selector.connect({timeout:0},()=>{},()=>{}),/positive integer/);
}
function nativeTest(){
    let intervals=[],requests=[],events=[],closed=[];
    const context={Uint8Array,ArrayBuffer,Array,Object,Error,TypeError,JSON,process:{_webTransportCommand:raw=>{
        const request=JSON.parse(raw);requests.push(request);
        if(request.action==='open')return '{"id":1}';
        if(request.action==='write')return '{"accepted":true}';
        if(request.action==='poll'){let result=events;events=[];return JSON.stringify(result);}
        return '{}';
    }},setInterval:fn=>{intervals.push(fn);return intervals.length;},clearInterval:id=>closed.push(id),setTimeout:()=>1,clearTimeout:()=>{},require:()=>facade};
    const native=load('net_webtransport_native',context);
    let ready=0,errors=0;
    const socket=native.connect({webTransportUrl:'https://[::1]:5443/pdg',serverCertificateHashes:[{algorithm:'sha-256',value:new Uint8Array(32)}]},()=>ready++,()=>errors++);
    assert.equal(requests[0].host,'::1');assert.equal(requests[0].certificateHashes[0],'00'.repeat(32));
    events=[{type:'ready',value:{remote:{address:'::1',port:5443},local:{address:'::1',port:1234},maxDatagramSize:1100}}];intervals[0]();
    assert.equal(ready,1);assert.equal(socket.transport,'webtransport');assert.equal(socket.address().port,1234);
    socket.write(new Uint8Array([99,1,2,99]).subarray(1,3));assert.deepEqual(requests.at(-1).data,[1,2]);
    assert.equal(socket.writeDatagram(new Uint8Array(1101)),false);
    assert.throws(()=>native.connect({webTransportUrl:'http://game.test'},()=>{},()=>{}),/HTTPS/);
    assert.throws(()=>native.connect({webTransportUrl:'https://game.test',serverCertificateHashes:[{algorithm:'sha-256',value:new Uint8Array(1)}]},()=>{},()=>{}),/32 bytes/);
    socket.on('close',()=>ready++);socket.end();socket.destroy();socket.destroy();
    assert.equal(requests.filter(r=>r.action==='close').length,2);assert.equal(requests.at(-1).force,true);
    events=[{type:'close'},{type:'close'}];intervals[0]();assert.equal(ready,2);assert.equal(errors,0);assert.equal(closed.length,1);
}
async function browserTest(){
    const context={document:{},globalThis:{},URL,Uint8Array,ArrayBuffer,Promise,Error,TypeError,Object,require:()=>facade,setTimeout,clearTimeout};
    const browser=load('net_webtransport_client',context);
    assert.throws(()=>browser.connect({host:'game.test'},()=>{},()=>{}),e=>e.code==='ERR_TRANSPORT_UNAVAILABLE');
    const session={close:()=>{}},adapter=new browser.BrowserTransport(session,{maxPendingBytes:3});
    let resolve,reject,received,errors=[];adapter.on('error',e=>errors.push(e.code));
    adapter._writer={write:data=>{received=data;return new Promise((yes,no)=>{resolve=yes;reject=no;});},abort:()=>Promise.resolve()};
    const bytes=new Uint8Array([99,1,2,99]).subarray(1,3);assert(adapter.write(bytes));bytes[0]=9;assert.deepEqual(Array.from(received),[1,2]);
    assert.equal(adapter.write(new Uint8Array(2)),false);assert.deepEqual(errors,['ERR_BACKPRESSURE']);assert.equal(adapter.destroyed,true);resolve();await tick();
    const dg=new browser.BrowserTransport(session,{});dg.maxDatagramSize=10;
    dg._datagramWriter={write:()=>Promise.reject(Error('datagram refused'))};let fallbacks=0;
    assert.equal(dg.writeDatagram(new Uint8Array(11),()=>fallbacks++),false);
    assert(dg.writeDatagram(new Uint8Array(2),()=>fallbacks++));await tick();assert.equal(fallbacks,1);assert.equal(dg.destroyed,false);
    const limited=new browser.BrowserTransport(session,{});limited.on('error',()=>{});limited._writer={write:()=>new Promise(()=>{}),abort:()=>Promise.resolve()};
    for(let i=0;i<256;i++)assert(limited.write(new Uint8Array(1)));assert.equal(limited.write(new Uint8Array(1)),false);
}
function connectionTest(){
    const {EventEmitter}=require('events');const socket=new EventEmitter();let reliable=[],datagrams=[],reject;
    Object.assign(socket,{transport:'webtransport',secure:true,maxDatagramSize:8,address:()=>({address:'',port:0}),setKeepAlive:()=>{},end:()=>{},destroy:()=>{},write:bytes=>{reliable.push(bytes);return true;},writeDatagram:(bytes,callback)=>{datagrams.push(bytes);reject=callback;return true;}});
    const connection=new NetConnection(socket);connection._alive=true;connection._client={_allowDatagram:true,_connectCallback:()=>{}};
    connection._serializeMessage=value=>new Uint8Array(value);connection._deserializeMessage=bytes=>Array.from(bytes);
    connection._handleTcpCommand('D','1');connection._finishedHandshake();assert(connection.hasDgram);assert(connection.secure);
    let incoming=[];connection.onMessage((value,_,carrier)=>incoming.push([value,carrier]));socket.emit('datagram',new Uint8Array([1]));assert.deepEqual(incoming,[[[1],'udp']]);
    const message=[1,2,3];connection.sendDgram(message);message[0]=9;reject(Error('refused'));reject(Error('duplicate'));assert.equal(reliable.length,1);assert.deepEqual(Array.from(reliable[0].subarray(5)),[1,2,3]);
    connection.sendDgram(new Array(9).fill(1));assert.equal(reliable.length,2);assert.equal(datagrams.length,1);
    connection._handshakeComplete=false;socket.emit('datagram',new Uint8Array([2]));assert.equal(incoming.length,1);
    connection._handshakeComplete=true;connection._handleClose();assert.equal(connection.hasDgram,false);
}
(async()=>{buildTargetTest();selectorTest();nativeTest();await browserTest();connectionTest();console.log('PASS WebTransport build targets, adapters, transport selection, buffers, datagrams, and lifecycle');})().catch(error=>{console.error(error);process.exitCode=1;});
