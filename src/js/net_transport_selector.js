'use strict';
var browser=typeof document!=='undefined',embedded=typeof require.resolve!=='function';
var limit=require((browser || embedded)?'net_transport':'./net_transport').positiveLimit;
var failures=new Map();
function moduleFor(name){return require((browser || embedded)?name:'./'+name);}
exports.connect=function(info,onOpen,onError,websocketConnect){
    var timeout=limit(info.timeout,5000,'timeout');
    var attemptTimeout=limit(info.webTransportTimeout,1500,'webTransportTimeout');
    var cacheTimeout=info.capabilityCacheTimeout===0?0:limit(info.capabilityCacheTimeout,30000,'capabilityCacheTimeout');
    var deadline=Date.now()+timeout,generation=0,finished=false,current=null;
    var policy=info.transportPolicy || 'auto';
    var allowFallback=policy==='auto';
    var useWT=policy==='webtransport-required' || (policy==='auto' && (browser || info.webTransportUrl));
    var wtInfo=Object.assign({},info);
    var wsInfo=Object.assign({},info);
    if(!wtInfo.webTransportUrl && wtInfo.webSocketUrl)wtInfo.webTransportUrl=wtInfo.webSocketUrl.replace(/^wss?:/, 'https:');
    if(!wsInfo.webSocketUrl && wsInfo.webTransportUrl)wsInfo.webSocketUrl=wsInfo.webTransportUrl.replace(/^https:/,'wss:');
    var pins=wtInfo.serverCertificateHashes && wtInfo.serverCertificateHashes.map(function(pin){
        return [pin.algorithm,Array.from(pin.value instanceof ArrayBuffer?new Uint8Array(pin.value):pin.value)];
    });
    var cacheKey=JSON.stringify([wtInfo.webTransportUrl || [wtInfo.host,wtInfo.webPort,wtInfo.webPath],pins,wtInfo.tls]);
    var controller={destroy:function(){if(finished){if(current)current.destroy();return;}finished=true;generation++;if(current)current.destroy();}};
    function report(error){if(finished)return;finished=true;generation++;if(current)current.destroy();onError(error);}
    function start(webtransport){
        var remaining=deadline-Date.now();if(remaining<=0)return report(Object.assign(new Error('Connection establishment timed out'),{code:'ERR_CONNECT_TIMEOUT',transport:webtransport?'webtransport':'websocket'}));
        var token=++generation,options=Object.assign({},webtransport?wtInfo:wsInfo,{timeout:webtransport && allowFallback?Math.min(attemptTimeout,remaining):remaining});
        function ready(socket){if(finished || token!==generation){socket.destroy();return;}finished=true;current=socket;socket._pdgHandshakeTimeout=Math.max(1,Math.min(info.handshakeTimeout || timeout,deadline-Date.now()));onOpen(socket);}
        function failed(error){
            if(finished || token!==generation)return;
            var fallback=webtransport && allowFallback && ['ERR_TRANSPORT_UNAVAILABLE','ERR_WEBTRANSPORT_UNSUPPORTED','ERR_CONNECT_TIMEOUT'].indexOf(error.code)!==-1;
            if(!fallback)return report(error);
            generation++;if(current)current.destroy();current=null;
            if(cacheTimeout && error.code!=='ERR_TRANSPORT_UNAVAILABLE'){
                failures.forEach(function(expiry,key){if(expiry<=Date.now())failures.delete(key);});
                if(failures.size>=128)failures.delete(failures.keys().next().value);
                failures.set(cacheKey,Date.now()+cacheTimeout);
            }
            start(false);
        }
        try{
            var connect=webtransport?moduleFor('net_webtransport_client').connect:(websocketConnect || moduleFor('net_websocket_client').connect);
            var socket=connect(options,ready,failed);
            if(token===generation)current=socket;else if(socket)socket.destroy();
        }catch(error){failed(error);}
    }
    if(useWT && allowFallback && failures.get(cacheKey)>Date.now())useWT=false;
    start(useWT);return controller;
};
