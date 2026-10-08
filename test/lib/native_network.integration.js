// Run with tools/node. Exercises native C++ <-> PDG JavaScript in both directions.
'use strict';
const path=require('path'),assert=require('assert');
const role=process.env.PDG_CPP_NET_ROLE;
if(role){
    const Message=require('../spec/fixtures/websocket/message_types').NetworkTestMessage;
    const kind=process.env.PDG_CPP_NET_TRANSPORT;
    const tls={certFile:process.env.PDG_CPP_NET_CERT,keyFile:process.env.PDG_CPP_NET_KEY};
    let deadline;
    const quit=()=>{clearTimeout(deadline);pdg.quit();};
    const error=e=>{console.error(e.code,e.message);process.exitCode=1;quit();};
    if(role==='server'){
        const opts={native:kind==='native',serverAddr:'127.0.0.1',serverPort:0,noDatagram:true,reservationRequired:true};
        if(kind!=='native')opts[kind==='wt'?'webTransport':'webSocket']={port:0,secure:kind!=='ws',allowedOrigins:['*'],tls};
        const server=new pdg.NetServer(opts);server.expectClient('interop').onError(error).listen(c=>{
            c.onMessage(message=>{c.send(message);if(message==='done'){c.close(false);setTimeout(()=>{server.shutdown(true,true);quit();},100);}});return true;
        });
        server.ready().then(()=>console.log('PORT '+(kind==='native'?server.serverPort:server.listeners[kind==='wt'?'webtransport':'websocket'].port))).catch(error);
    }else{
        const port=Number(process.env.PDG_CPP_NET_PORT),opts={host:'127.0.0.1',port};
        if(kind!=='native'){
            opts[kind==='wt'?'webTransportUrl':'webSocketUrl']=(kind==='wt'?'https':kind==='ws'?'ws':'wss')+'://127.0.0.1:'+port+'/pdg';
            opts.secure=kind!=='ws';opts.transportPolicy=kind==='wt'?'webtransport-required':'websocket-only';opts.tls={caFile:tls.certFile,ca:require('fs').readFileSync(tls.certFile)};
        }
        const client=new pdg.NetClient({noDatagram:true});let count=0;
        client.onError(error).connect(opts,c=>{
            c.onMessage((m,_,carrier)=>{
                try{
                    assert.equal(carrier,'tcp');
                    switch(count++){
                    case 0:assert.equal(m,'Unicode: héllo 🌍');break;
                    case 1:assert.deepEqual(m,{score:42});break;
                    case 2:case 6:assert.deepEqual(Array.from(m),[0,127,255]);break;
                    case 3:assert(m instanceof pdg.MemBlock);assert.deepEqual(Array.from(m.getData()),[112,100,103,0,127,255]);break;
                    case 4:case 7:assert(m instanceof Message);assert.equal(m.one,15);assert.equal(m.two,99);break;
                    case 5:assert.equal(m,'reliable fallback');break;
                    case 8:assert.equal(m,'done');console.log('PASS JavaScript client '+kind);c.close(true);quit();return;
                    default:throw Error('Unexpected echo');
                    }
                    if(count===8)c.send('done');
                }catch(e){error(e);}
            });
            c.send('Unicode: héllo 🌍');c.send({score:42});c.send(Uint8Array.from([0,127,255]));
            const serializer=new pdg.Serializer();serializer.serialize_1u(0);serializer.serialize_1u(127);serializer.serialize_1u(255);
            c.send(serializer.getDataPtr());c.send(new Message());c.sendDgram('reliable fallback');c.sendDgram(Uint8Array.from([0,127,255]));c.sendDgram(new Message());
        },'interop');
    }
    deadline=setTimeout(()=>error(Error('JavaScript interoperability timeout')),10000);
}else{
    const cp=require('child_process'),readline=require('readline');
    const certificate=require('../spec/fixtures/webtransport/certificate').create();
    const driver=path.resolve(process.argv[2]||'build/darwin/arm64/pdg/src/pdg-native-network-tests');
    const runtime=path.resolve(process.argv[3]||'pdg');const children=new Set();
    function spawn(command,args,env={}){
        const child=cp.spawn(command,args,{env:{...process.env,...env},stdio:['ignore','pipe','pipe']});children.add(child);
        child.output='';child.stderr.on('data',d=>child.output+=d);child.stdout.on('data',d=>child.output+=d);
        child.completed=new Promise((resolve,reject)=>{child.on('error',reject);child.on('exit',(code)=>{children.delete(child);if(code===0)resolve();else reject(Error(command+' exited '+code+'\n'+child.output));});});
        // Attach a rejection handler while the caller is waiting for readiness.
        child.completed.catch(()=>{});return child;
    }
    function port(child){return new Promise((resolve,reject)=>{
        const timer=setTimeout(()=>reject(Error('Listener readiness timeout\n'+child.output)),8000);
        const lines=readline.createInterface({input:child.stdout});lines.on('line',line=>{const match=line.match(/^(?:PORT )?(\d+)$/);if(match){clearTimeout(timer);resolve(Number(match[1]));}});
        child.completed.then(()=>{clearTimeout(timer);reject(Error('Server exited before ready'));},e=>{clearTimeout(timer);reject(e);});
    });}
    const base={PDG_CPP_NET_CERT:certificate.tls.certFile,PDG_CPP_NET_KEY:certificate.tls.keyFile};
    (async()=>{try{
        for(const kind of ['native','ws','wss','wt']){
            const cppServer=spawn(driver,['--server',kind,base.PDG_CPP_NET_CERT,base.PDG_CPP_NET_KEY]);
            const cppPort=await port(cppServer);
            const jsClient=spawn(runtime,[__filename],{...base,PDG_CPP_NET_ROLE:'client',PDG_CPP_NET_TRANSPORT:kind,PDG_CPP_NET_PORT:String(cppPort)});
            await Promise.all([cppServer.completed,jsClient.completed]);
            const jsServer=spawn(runtime,[__filename],{...base,PDG_CPP_NET_ROLE:'server',PDG_CPP_NET_TRANSPORT:kind});
            const jsPort=await port(jsServer);
            const cppClient=spawn(driver,['--client',kind,String(jsPort),base.PDG_CPP_NET_CERT]);
            await Promise.all([cppClient.completed,jsServer.completed]);
            console.log('PASS C++ ↔ JavaScript '+kind+' strings, JSON, bytes, MemBlock, ISerializable, sendDgram fallback');
        }
        // Native servers must reject malformed/authentication-bypassing frames.
        const frame=(command,payload)=>{const length=Buffer.alloc(command==='A'?4:2);length.writeUIntBE(payload.length,0,length.length);return Buffer.concat([Buffer.from(command),length,payload]);};
        const handshake=Buffer.concat([frame('K',Buffer.from('interop')),frame('V',Buffer.from('1'))]);
        for(const [payload,code] of [
            [frame('V',Buffer.from('1')),'ERR_BAD_CLIENT_KEY'],
            [Buffer.from([90,0,0]),'ERR_REMOTE_BAD_DATA'],
            [Buffer.from([65,0,16,0,1]),'ERR_FRAME_TOO_LARGE'],
            [Buffer.concat([handshake,frame('A',Buffer.from('pdgx'))]),'ERR_REMOTE_BAD_DATA']
        ]){
            const host=spawn(driver,['--server','native']);const number=await port(host);
            const socket=require('net').connect(number,'127.0.0.1',()=>socket.write(payload));socket.on('error',()=>{});
            try{await host.completed;throw Error('Malformed frame was accepted');}catch(e){assert(host.output.includes(code),host.output);}finally{socket.destroy();}
        }
        console.log('PASS native C++ authentication and malformed frame rejection');
        for(const kind of ['wss','wt']){
            const server=spawn(runtime,[__filename],{...base,PDG_CPP_NET_ROLE:'server',PDG_CPP_NET_TRANSPORT:kind});const number=await port(server);
            const client=spawn(driver,['--client',kind==='wt'?'wt-auto':kind,String(number)]);
            try{await client.completed;throw Error('Untrusted certificate was accepted');}catch(e){assert(client.output.includes('ERR_TLS_CERTIFICATE'),client.output);}finally{server.kill();}
        }
        console.log('PASS native C++ certificate rejection without automatic downgrade');
        const blocked=require('dgram').createSocket('udp4');
        try{
            await new Promise(resolve=>blocked.bind(0,'127.0.0.1',resolve));
            const host=spawn(driver,['--server','native-blocked',String(blocked.address().port)]);const number=await port(host);
            const client=spawn(runtime,[__filename],{...base,PDG_CPP_NET_ROLE:'client',PDG_CPP_NET_TRANSPORT:'native',PDG_CPP_NET_PORT:String(number)});
            await Promise.all([host.completed,client.completed]);
            console.log('PASS native C++ TCP startup and reliable fallback with occupied UDP port');
        }finally{blocked.close();}
    }finally{for(const child of children)child.kill();certificate.remove();}})().catch(e=>{console.error(e);process.exitCode=1;});
}
