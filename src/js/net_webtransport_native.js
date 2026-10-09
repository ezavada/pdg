// Native-only owned-buffer bridge; never embedded in browser builds.
'use strict';
var facade=require(typeof require.resolve!=='function'?'net_transport':'./net_transport');
function error(code,message){return Object.assign(new Error(message),{code:code,transport:'webtransport'});}
function bridge(){
    var bridge=typeof process!=='undefined' && process._webTransportCommand;
    if(!bridge && typeof pdg!=='undefined')bridge=pdg._webTransportCommand;
    if(typeof bridge!=='function')throw error('ERR_TRANSPORT_UNAVAILABLE','Native WebTransport backend unavailable');
    return bridge;
}
function command(value){
    var result=JSON.parse(bridge()(JSON.stringify(value)));
    if(result && result.code)throw Object.assign(new Error(result.message),result);
    return result;
}
function limits(info){
    ['maxFrameSize','maxPendingBytes','timeout','handshakeTimeout','idleTimeout','maxConnections','maxConnectionsPerIP','maxConnectionsPerOrigin','maxConnectionsPerMinute','maxIncompleteHandshakes'].forEach(function(name){if(info[name]!==undefined)facade.positiveLimit(info[name],1,name);});
}
function Socket(id,info,endpoint){
    this.id=id;this.transport='webtransport';this.secure=true;this.destroyed=false;this._handlers=Object.create(null);
    this.maxFrameSize=facade.positiveLimit(info.maxFrameSize,1024*1024,'maxFrameSize');
    this.maxPendingBytes=facade.positiveLimit(info.maxPendingBytes,4*1024*1024,'maxPendingBytes');
    this._endpoint(endpoint || {});this._timer=setInterval(this._poll.bind(this),5);
}
Socket.prototype.on=facade.WebSocketTransport.prototype.on;
Socket.prototype.emit=facade.WebSocketTransport.prototype.emit;
Socket.prototype.address=facade.WebSocketTransport.prototype.address;
Socket.prototype.setKeepAlive=function(){};
Socket.prototype._endpoint=function(value){this.remoteAddress=value.remote && value.remote.address || '';this.remotePort=value.remote && value.remote.port || 0;this._address=value.local || {address:'',port:0};this.maxDatagramSize=value.maxDatagramSize || 0;};
Socket.prototype._poll=function(){
    var events;try{events=command({action:'poll',id:this.id});}catch(e){this.fail(e);return;}
    var exception;
    events.forEach(function(event){
        try{
        if(this.destroyed)return;
        if(event.type==='ready'){this._endpoint(event.value);this.emit('ready',this);}
        else if(event.type==='data' || event.type==='datagram')this.emit(event.type,new Uint8Array(event.value));
        else if(event.type==='error')this.emit('error',Object.assign(new Error(event.value.message),event.value));
        else if(event.type==='close'){clearInterval(this._timer);this.destroyed=true;this.emit('close');}
        }catch(error){if(!exception)exception=error;}
    }.bind(this));
    if(exception)throw exception;
};
Socket.prototype.fail=function(e){if(this.destroyed)return;this.emit('error',e);this.destroy();};
Socket.prototype.write=function(bytes){
    if(this.destroyed || this._closing)return false;
    if(!(bytes instanceof Uint8Array))throw new TypeError('WebTransport writes require Uint8Array');
    var accepted=command({action:'write',id:this.id,data:Array.from(bytes)}).accepted;
    if(!accepted)this.fail(error('ERR_BACKPRESSURE','Native WebTransport write rejected'));
    return accepted;
};
Socket.prototype.writeDatagram=function(bytes){
    if(this.destroyed || this._closing || !this.maxDatagramSize || bytes.length>this.maxDatagramSize)return false;
    return command({action:'write',id:this.id,datagram:true,data:Array.from(bytes)}).accepted;
};
Socket.prototype.destroy=function(){if(this.destroyed || this._destroyQueued)return;this._destroyQueued=true;this._closing=true;command({action:'close',id:this.id,force:true});};
Socket.prototype.end=function(){if(this.destroyed || this._closing)return;this._closing=true;command({action:'close',id:this.id});};
function endpoint(info){
    var host=info.host || '';if(host.indexOf(':')>=0 && host[0]!=='[')host='['+host+']';
    var url=info.webTransportUrl || 'https://'+host+':'+(info.webPort===undefined?5443:info.webPort)+(info.webPath || '/pdg');
    var match=/^https:\/\/(\[[^\]]+\]|[^:/?#\s]+)(?::([0-9]+))?(\/[^#\s]*)?$/.exec(url);
    if(!match || match[1].indexOf('@')!==-1)throw new TypeError('WebTransport requires an HTTPS endpoint without credentials or fragments');
    var port=match[2]===undefined?443:Number(match[2]);
    if(!Number.isInteger(port) || port<1 || port>65535)throw new TypeError('Invalid WebTransport port');
    return {host:match[1].replace(/^\[|\]$/g,''),port:port,path:match[3] || '/'};
}
function hashes(values){
    if(values===undefined)return [];
    if(!Array.isArray(values) || !values.length)throw new TypeError('serverCertificateHashes must be a nonempty array');
    return values.map(function(pin){
        if(!pin || pin.algorithm!=='sha-256')throw new TypeError('WebTransport certificate hashes require sha-256');
        var bytes=pin.value instanceof ArrayBuffer?new Uint8Array(pin.value):pin.value;
        if(!(bytes instanceof Uint8Array) || bytes.length!==32)throw new TypeError('WebTransport SHA-256 hashes require 32 bytes');
        return Array.from(bytes,function(value){return ('0'+value.toString(16)).slice(-2);}).join('');
    });
}
exports.connect=function(info,onOpen,onError){
    bridge();limits(info);var opts=Object.assign({},info,endpoint(info),{action:'open',server:false,certificateHashes:hashes(info.serverCertificateHashes),caFile:info.tls && info.tls.caFile});
    var socket=new Socket(command(opts).id,info),finished=false;
    socket.on('ready',function(){if(finished)return;finished=true;clearTimeout(timer);onOpen(socket);});
    function fail(e){if(finished)return;finished=true;clearTimeout(timer);socket.destroy();onError(e);}
    socket.on('error',fail).on('close',function(){fail(error('ERR_CONNECT_CLOSED','WebTransport closed before connecting'));});
    var timer=setTimeout(function(){fail(error('ERR_CONNECT_TIMEOUT','WebTransport establishment timed out'));},info.timeout || 5000);
    return socket;
};

exports.Socket=Socket;

exports.command=command;
exports.limits=limits;
