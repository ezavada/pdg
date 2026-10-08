'use strict';
// Run with tools/node and a PDG_WEBTRANSPORT_TEST_DRIVER build.
const assert=require('assert'),cp=require('child_process'),path=require('path'),readline=require('readline');
const certificate=require('../spec/fixtures/webtransport/certificate').create();
const cert=certificate.tls.certFile,key=certificate.tls.keyFile;
const hash=Buffer.from(certificate.digest).toString('hex');
const driver=cp.spawn(process.argv[2]||path.resolve('build/webtransport/native/pdg_webtransport_test_driver'),[],{stdio:['pipe','pipe','inherit']});
const pending=[];
readline.createInterface({input:driver.stdout}).on('line',line=>{const next=pending.shift();if(!next)return;try{next.resolve(JSON.parse(line));}catch(error){next.reject(error);}});
driver.on('error',error=>{while(pending.length)pending.shift().reject(error);});
const command=value=>new Promise((resolve,reject)=>{pending.push({resolve,reject});driver.stdin.write(JSON.stringify(value)+'\n');});
const sleep=()=>new Promise(resolve=>setTimeout(resolve,5));
async function eventsUntil(id,predicate) {
    const events=[];const deadline=Date.now()+6000;
    while(Date.now()<deadline){events.push(...await command({action:'poll',id}));if(predicate(events))return events;await sleep();}
    throw Error('Native WebTransport event timeout: '+JSON.stringify(events));
}
async function open(options) {const result=await command(Object.assign({action:'open',host:'127.0.0.1'},options));assert(result.id,JSON.stringify(result));return result.id;}
(async()=>{try {
    for(const options of [{port:-1},{port:1.5},{maxPendingBytes:0},{maxConnectionsPerIP:-1},{idleTimeout:-1},{certificateHashes:['bad']}])
        assert.equal((await command(Object.assign({action:'open'},options))).code,'ERR_TRANSPORT_CONFIG');
    const server=await open({server:true,port:0,certFile:cert,keyFile:key,allowedOrigins:['*']});
    const port=(await eventsUntil(server,events=>events.some(e=>e.type==='ready'))).find(e=>e.type==='ready').value.port;
    for(const options of [{certificateHashes:['00'.repeat(32)]},{}]) {
        const client=await open(Object.assign({port,timeout:1500},options));
        const events=await eventsUntil(client,events=>events.some(e=>e.type==='close'));
        assert.equal(events.filter(e=>e.type==='error').length,1);assert.equal(events.find(e=>e.type==='error').value.code,'ERR_TLS_CERTIFICATE');
        assert.equal(events.filter(e=>e.type==='close').length,1);assert(!events.some(e=>e.type==='ready'));
    }
    const client=await open({port,certificateHashes:[hash]});
    const ready=(await eventsUntil(client,events=>events.some(e=>e.type==='ready'))).find(e=>e.type==='ready');
    assert.equal(ready.value.maxDatagramSize,1100);
    const payload=[0,1,255,128,42];assert((await command({action:'write',id:client,data:payload})).accepted);
    const peer=(await eventsUntil(server,events=>events.some(e=>e.type==='accept'))).find(e=>e.type==='accept').value.id;
    assert.deepEqual((await eventsUntil(peer,events=>events.some(e=>e.type==='data'))).find(e=>e.type==='data').value,payload);
    assert((await command({action:'write',id:peer,data:payload})).accepted);
    assert.deepEqual((await eventsUntil(client,events=>events.some(e=>e.type==='data'))).find(e=>e.type==='data').value,payload);
    assert(!(await command({action:'write',id:client,datagram:true,data:Array(1101).fill(1)})).accepted);
    assert((await command({action:'write',id:client,datagram:true,data:payload})).accepted);
    assert.deepEqual((await eventsUntil(peer,events=>events.some(e=>e.type==='datagram'))).find(e=>e.type==='datagram').value,payload);
    assert((await command({action:'write',id:peer,datagram:true,data:payload})).accepted);
    assert.deepEqual((await eventsUntil(client,events=>events.some(e=>e.type==='datagram'))).find(e=>e.type==='datagram').value,payload);
    await command({action:'close',id:client});await command({action:'close',id:client});
    assert.equal((await eventsUntil(client,events=>events.some(e=>e.type==='close'))).filter(e=>e.type==='close').length,1);
    assert.equal((await eventsUntil(peer,events=>events.some(e=>e.type==='close'))).filter(e=>e.type==='close').length,1);
    assert(!(await command({action:'write',id:client,data:payload})).accepted);
    // Verify private CA trust, server-initiated close, and draining a final write.
    const second=await open({port,caFile:cert});
    await eventsUntil(second,events=>events.some(e=>e.type==='ready'));
    assert((await command({action:'write',id:second,data:payload})).accepted);
    const secondPeer=(await eventsUntil(server,events=>events.some(e=>e.type==='accept'))).find(e=>e.type==='accept').value.id;
    await eventsUntil(secondPeer,events=>events.some(e=>e.type==='data'));
    assert((await command({action:'write',id:secondPeer,data:payload})).accepted);
    await command({action:'close',id:secondPeer});
    const final=await eventsUntil(second,events=>events.some(e=>e.type==='close'));
    assert.deepEqual(final.find(e=>e.type==='data').value,payload);assert.equal(final.filter(e=>e.type==='close').length,1);
    const unsupported=await open({port,path:'/unsupported',certificateHashes:[hash]});
    const refusal=await eventsUntil(unsupported,events=>events.some(e=>e.type==='close'));
    assert(!refusal.some(e=>e.type==='ready'));assert.equal(refusal.find(e=>e.type==='error').value.code,'ERR_WEBTRANSPORT_UNSUPPORTED');
    const deniedServer=await open({server:true,port:0,certFile:cert,keyFile:key,allowedOrigins:['https://allowed.example']});
    const deniedPort=(await eventsUntil(deniedServer,events=>events.some(e=>e.type==='ready'))).find(e=>e.type==='ready').value.port;
    const denied=await open({port:deniedPort,certificateHashes:[hash]});
    const deniedEvents=await eventsUntil(denied,events=>events.some(e=>e.type==='close'));
    assert(!deniedEvents.some(e=>e.type==='ready'));assert.equal(deniedEvents.find(e=>e.type==='error').value.code,'ERR_WEBTRANSPORT_REJECTED');
    await command({action:'close',id:deniedServer});
    const occupied=await open({server:true,port,certFile:cert,keyFile:key,allowedOrigins:['*']});
    const bindEvents=await eventsUntil(occupied,events=>events.some(e=>e.type==='close'));
    assert.equal(bindEvents.find(e=>e.type==='error').value.code,'ERR_LISTEN_BIND');
    await command({action:'close',id:server});
    console.log('PASS native WebTransport streams, datagrams, certificate rejection, limits, and shutdown');
}finally {driver.stdin.end();certificate.remove();}})().catch(error=>{console.error(error);driver.kill();process.exitCode=1;});
