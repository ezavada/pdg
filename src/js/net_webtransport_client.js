'use strict';
var embedded = typeof require.resolve !== 'function';
var browser = typeof document !== 'undefined';
var facade = require((browser || embedded) ? 'net_transport' : './net_transport');
function failure(code, message) { return Object.assign(new Error(message), {code:code, transport:'webtransport'}); }
function BrowserTransport(session, info) {
    this.session=session;this.transport='webtransport';this.secure=true;this.destroyed=false;
    this._handlers=Object.create(null);this._address={address:'',port:0};this.remoteAddress='';this.remotePort=0;
    this.maxFrameSize=facade.positiveLimit(info.maxFrameSize,1024*1024,'maxFrameSize');
    this.maxPendingBytes=facade.positiveLimit(info.maxPendingBytes,4*1024*1024,'maxPendingBytes');
    this.maxDatagramSize=0;this._bytes=0;this._writes=0;
}
BrowserTransport.prototype.on=facade.WebSocketTransport.prototype.on;
BrowserTransport.prototype.emit=facade.WebSocketTransport.prototype.emit;
BrowserTransport.prototype.address=facade.WebSocketTransport.prototype.address;
BrowserTransport.prototype.setKeepAlive=function() {};
BrowserTransport.prototype._closed=function() {
    if(this.destroyed)return;this.destroyed=true;clearTimeout(this._endTimer);
    [this._reader,this._datagrams,this._extra,this._unidirectional].forEach(function(reader){if(reader)reader.cancel().catch(function(){});});
    this.emit('close',!!this._failed);
};
BrowserTransport.prototype.fail=function(error) {if(this.destroyed || this._failed)return;this._failed=true;this.emit('error',error);this.destroy();};
BrowserTransport.prototype.destroy=function() {
    if(this.destroyed)return;
    try{this.session.close();}catch(error){}
    if(this._reader)this._reader.cancel().catch(function(){});
    if(this._datagrams)this._datagrams.cancel().catch(function(){});
    if(this._writer)this._writer.abort().catch(function(){});
    if(this._datagramWriter)this._datagramWriter.abort().catch(function(){});
    this._closed();
};
BrowserTransport.prototype.end=function(){
    if(this.destroyed || this._ending)return;this._ending=true;
    this._endTimer=setTimeout(this.destroy.bind(this),2000);
    if(this._writer)Promise.resolve(this._writer.close()).then(this.destroy.bind(this),this.destroy.bind(this));
    else this.destroy();
};
BrowserTransport.prototype._write=function(writer,bytes,rejected) {
    if(this.destroyed || this._ending || !writer)return false;
    if(!(bytes instanceof Uint8Array))throw new TypeError('WebTransport writes require Uint8Array');
    if(bytes.length>this.maxPendingBytes-this._bytes || this._writes>=256){
        if(!rejected)this.fail(failure('ERR_BACKPRESSURE','WebTransport pending byte limit exceeded'));
        return false;
    }
    var copy=new Uint8Array(bytes);this._bytes+=copy.length;this._writes++;
    var complete=function(){this._bytes-=copy.length;this._writes--;if(!this.destroyed && this._writes===0)this.emit('drain');}.bind(this);
    try{Promise.resolve(writer.write(copy)).then(complete,function(error){complete();if(!this.destroyed){if(rejected)rejected(error);else this.fail(failure('ERR_WEBTRANSPORT_WRITE',error.message));}}.bind(this));}
    catch(error){complete();if(rejected)rejected(error);else this.fail(error);return false;}
    return true;
};
BrowserTransport.prototype.write=function(bytes){return this._write(this._writer,bytes);};
BrowserTransport.prototype.writeDatagram=function(bytes,rejected){
    if(!this.maxDatagramSize || bytes.length>this.maxDatagramSize)return false;
    return this._write(this._datagramWriter,bytes,rejected || function(){});
};
BrowserTransport.prototype._read=async function(reader,event) {
    try{while(!this.destroyed){var result=await reader.read();if(result.done){if(event==='data')this.destroy();break;}
        if(result.value.byteLength>this.maxPendingBytes){this.fail(failure('ERR_BACKPRESSURE','WebTransport incoming byte limit exceeded'));break;}
        this.emit(event,result.value);
    }}catch(error){if(!this.destroyed)this.fail(failure('ERR_WEBTRANSPORT_READ',error.message));}
};
exports.connect=function(info,onOpen,onError) {
    if(!browser)return require(embedded?'net_webtransport_native':'./net_webtransport_native').connect(info,onOpen,onError);
    ['maxFrameSize','maxPendingBytes','timeout','handshakeTimeout'].forEach(function(name){if(info[name]!==undefined)facade.positiveLimit(info[name],1,name);});
    if(typeof globalThis.WebTransport!=='function')throw failure('ERR_TRANSPORT_UNAVAILABLE','WebTransport unavailable');
    var host=info.host || '';if(host.indexOf(':')>=0 && host[0]!=='[')host='['+host+']';
    var url=info.webTransportUrl || ('https://'+host+':'+(info.webPort===undefined?5443:info.webPort)+(info.webPath || '/pdg'));
    var parsed=new URL(url);if(parsed.protocol!=='https:' || parsed.username || parsed.password || parsed.hash)throw new TypeError('WebTransport requires an HTTPS endpoint without credentials or fragments');
    var options={protocols:['pdg-net-v1']};if(info.serverCertificateHashes)options.serverCertificateHashes=info.serverCertificateHashes;
    var session=new globalThis.WebTransport(url,options),adapter=new BrowserTransport(session,info),finished=false;
    function fail(error){if(finished)return;finished=true;clearTimeout(timer);adapter.destroy();onError(error);}
    var timer=setTimeout(function(){fail(failure('ERR_CONNECT_TIMEOUT','WebTransport establishment timed out'));},info.timeout || 5000);
    session.closed.then(function(){adapter._closed();if(!finished)fail(failure('ERR_CONNECT_CLOSED','WebTransport closed before establishment'));},function(error){
        // Browsers do not reliably distinguish TLS rejection from other ready failures.
        // Keep opaque failures terminal so fallback cannot hide certificate failures.
        if(!finished)fail(failure('ERR_WEBTRANSPORT_CONNECT',error.message));else adapter.fail(failure('ERR_WEBTRANSPORT_CONNECT',error.message));
    });
    session.ready.then(function(){return session.createBidirectionalStream();}).then(function(stream){
        if(finished){stream.readable.cancel().catch(function(){});stream.writable.abort().catch(function(){});return;}
        if(session.protocol && session.protocol!=='pdg-net-v1'){fail(failure('ERR_WEBTRANSPORT_PROTOCOL','PDG WebTransport protocol required'));return;}
        adapter._writer=stream.writable.getWriter();adapter._reader=stream.readable.getReader();
        adapter.maxDatagramSize=Math.min(session.datagrams.maxDatagramSize || 0,1100);
        if(adapter.maxDatagramSize){adapter._datagramWriter=session.datagrams.writable.getWriter();adapter._datagrams=session.datagrams.readable.getReader();}
        finished=true;clearTimeout(timer);onOpen(adapter);adapter._read(adapter._reader,'data');
        if(adapter._datagrams)adapter._read(adapter._datagrams,'datagram');
        var extra=adapter._extra=session.incomingBidirectionalStreams.getReader();
        (async function(){try{while(!adapter.destroyed){var next=await extra.read();if(next.done)break;next.value.readable.cancel().catch(function(){});next.value.writable.abort().catch(function(){});}}catch(error){if(!adapter.destroyed)adapter.fail(error);}})();
        var incoming=adapter._unidirectional=session.incomingUnidirectionalStreams.getReader();
        (async function(){try{while(!adapter.destroyed){var next=await incoming.read();if(next.done)break;next.value.cancel().catch(function(){});}}catch(error){if(!adapter.destroyed)adapter.fail(error);}})();
    }).catch(function(error){if(!finished)fail(failure('ERR_WEBTRANSPORT_CONNECT',error.message));else if(!adapter.destroyed)adapter.fail(error);});
    return adapter;
};
exports.BrowserTransport=BrowserTransport;
