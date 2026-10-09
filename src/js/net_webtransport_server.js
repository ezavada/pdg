// Standalone-only listener. Native iOS and browser builds expose clients only.
'use strict';
var native=require(typeof require.resolve!=='function'?'net_webtransport_native':'./net_webtransport_native');
var command=native.command,limits=native.limits,Socket=native.Socket;
function error(code,message){return Object.assign(new Error(message),{code:code,transport:'webtransport'});}
exports.listen=function(owner,opts){
    limits(opts);var tls=opts.tls || {},origins=opts.allowedOrigins || [];
    if(opts.port!==undefined && (typeof opts.port!=='number' || !Number.isInteger(opts.port) || opts.port<0 || opts.port>65535))throw new TypeError('Invalid WebTransport port');
    if(opts.path!==undefined && (typeof opts.path!=='string' || opts.path[0]!=='/'))throw new TypeError('WebTransport path must start with /');
    if(!Array.isArray(origins) || origins.some(function(value){return typeof value!=='string';}))throw new TypeError('allowedOrigins must be an array of strings');
    if(opts.secure===false)throw new TypeError('WebTransport listeners require TLS');
    if(!tls.certFile || !tls.keyFile)throw new TypeError('WebTransport requires tls.certFile and tls.keyFile');
    var id=command(Object.assign({},opts,{action:'open',server:true,host:opts.host || owner.serverAddr,port:opts.port===undefined?5443:opts.port,path:opts.path || '/pdg',certFile:tls.certFile,keyFile:tls.keyFile,timeout:owner.handshakeTimeout || 5000,allowedOrigins:origins})).id;
    var closed=false,settled=false,resolveReady,rejectReady;
    var ready=new Promise(function(resolve,reject){resolveReady=resolve;rejectReady=reject;});
    var timer=setInterval(function(){
        var events;try{events=command({action:'poll',id:id});}catch(e){if(!settled){settled=true;rejectReady(e);}else owner._handleError(e);return;}
        events.forEach(function(event){
            if(event.type==='ready' && !closed){settled=true;resolveReady(Object.assign({path:opts.path || '/pdg'},event.value));}
            else if(event.type==='error'){var e=Object.assign(new Error(event.value.message),event.value);if(!settled){settled=true;rejectReady(e);}else if(!closed)owner._handleError(e);}
            else if(event.type==='close'){clearInterval(timer);if(!settled){settled=true;rejectReady(error('ERR_LISTEN_CANCELLED','WebTransport startup cancelled'));}}
            else if(event.type==='accept'){
                var socket=new Socket(event.value.id,opts,event.value);
                if(closed || !owner._checkClientIP(socket.remoteAddress) || owner._pendingConnections.size>=(opts.maxIncompleteHandshakes || 128))socket.destroy();
                else owner._handleConnect(socket);
            }
        });
    },5);
    return {ready:ready,close:function(closeExisting){if(closed)return;closed=true;command({action:closeExisting===false?'stop':'close',id:id});if(!settled){settled=true;rejectReady(error('ERR_LISTEN_CANCELLED','WebTransport startup cancelled'));}}};
};
