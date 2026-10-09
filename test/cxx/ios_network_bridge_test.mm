// Exercise the same iOS bridge against Network.framework on the macOS host.
// This covers lifecycle/buffer paths without exposing test hooks to applications.
#include "pdg_ios_network.h"
#import <Foundation/Foundation.h>
#include <cassert>
#include <cstdio>
#include <string>
static JSGlobalContextRef ctx;
static JSValueRef evaluate(const std::string &source) {
    JSStringRef script = JSStringCreateWithUTF8CString(source.c_str());
    JSValueRef exception = nullptr;
    JSValueRef result = JSEvaluateScript(ctx, script, nullptr, nullptr, 1, &exception);
    JSStringRelease(script);
    if (exception) {
        JSStringRef text = JSValueToStringCopy(ctx, exception, nullptr);
        char buffer[2048]; JSStringGetUTF8CString(text, buffer, sizeof(buffer)); JSStringRelease(text);
        fprintf(stderr, "%s\n", buffer); assert(!exception);
    }
    return result;
}
static void waitFor(const char *condition) {
    NSDate *deadline = [NSDate dateWithTimeIntervalSinceNow:5];
    while (!JSValueToBoolean(ctx, evaluate(condition))) {
        assert([deadline timeIntervalSinceNow] > 0);
        assert(!JSC_IOS_NetworkIdle());
        [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.005]];
    }
}
int main(int argc, char **argv) {
    @autoreleasepool {
        assert(argc == 4);
        ctx = JSGlobalContextCreate(nullptr);
        JSObjectRef process = JSObjectMake(ctx, nullptr, nullptr);
        JSStringRef name = JSStringCreateWithUTF8CString("process");
        JSObjectSetProperty(ctx, JSContextGetGlobalObject(ctx), name, process, 0, nullptr); JSStringRelease(name);
        JSC_IOS_NetworkInstall(ctx, process);
        evaluate("var port=" + std::string(argv[1]) + ", floodPort=" + argv[2] + ";");
        evaluate(R"JS(
            function check(ok) { if (!ok) throw new Error('Bridge assertion failed'); }
            var bridge=process._iosNetwork, ready=false, tcp=false, udp=false, closes=0, errors=[];
            var id=bridge.open('127.0.0.1',port,function(type,value) {
                if(type==='connect') { check(value.local.port>0);ready=true;bridge.udp(id); }
                if(type==='udpReady') bridge.write(id,new Uint8Array([55,66]),true);
                if(type==='datagram') {
                    check(value[0]===55 && value[1]===66);udp=true;
                    var original=new Uint8Array([99,1,2,3,99]);
                    bridge.write(id,original.subarray(1,4),false);original.fill(0);
                }
                if(type==='data') {check(value.length===3 && value[0]===1 && value[2]===3);tcp=true;}
                if(type==='error' || type==='udpError') errors.push(value.code);
                if(type==='close') closes++;
            },8192);
        )JS");
        waitFor("tcp && udp"); evaluate("check(errors.length===0);bridge.close(id,true);bridge.close(id,true);");
        waitFor("closes===1");
        evaluate(R"JS(
            ready=false;closes=0;errors=[];
            id=bridge.open('127.0.0.1',port,function(type,value) {
                if(type==='connect') ready=true;
                if(type==='error') errors.push(value.code);
                if(type==='close') closes++;
            },8192);
        )JS");
        waitFor("ready"); JSC_IOS_NetworkSuspend();waitFor("closes===1");
        evaluate("check(errors.length===1 && errors[0]==='ERR_NETWORK_BACKGROUND');");
        evaluate(R"JS(
            closes=0;errors=[];
            id=bridge.open('127.0.0.1',port,function(type,value) {
                if(type==='connect') check(bridge.write(id,new Uint8Array(2048),false)===false);
                if(type==='error') errors.push(value.code);
                if(type==='close') closes++;
            },1024);
        )JS");
        waitFor("closes===1");evaluate("check(errors.length===1 && errors[0]==='ERR_NETWORK_BACKPRESSURE');");
        evaluate(R"JS(
            closes=0;errors=[];
            id=bridge.open('127.0.0.1',floodPort,function(type,value) {
                if(type==='error') errors.push(value.code);
                if(type==='close') closes++;
            },1024);
        )JS");
        waitFor("closes===1");evaluate("check(errors.length===1 && errors[0]==='ERR_NETWORK_BACKPRESSURE');");
        evaluate("var wsPort="+std::string(argv[3])+";");
        evaluate(R"JS(
            closes=0;errors=[];var wsData=false;
            id=bridge.open('127.0.0.1',1,function(type,value) {
                if(type==='connect') bridge.write(id,new Uint8Array([1,2,3]),false);
                if(type==='data') {check(value.length===3 && value[2]===3);wsData=true;}
                if(type==='error') errors.push(value);
                if(type==='close') closes++;
            },8192,5000,'ws://127.0.0.1:'+wsPort+'/pdg');
        )JS");
        waitFor("wsData || errors.length");evaluate("check(wsData && errors.length===0);");
        JSC_IOS_NetworkSuspend();waitFor("closes===1");
        evaluate("check(errors.length===1 && errors[0].transport==='websocket');");
        for (const char *path : {"/text", "/no-protocol"}) {
            evaluate("closes=0;errors=[];id=bridge.open('127.0.0.1',1,function(type,value){if(type==='error')errors.push(value);if(type==='close')closes++;},8192,5000,'ws://127.0.0.1:'+wsPort+'"+std::string(path)+"');");
            waitFor("closes===1");
            evaluate(std::string("check(errors.length===1 && errors[0].transport==='websocket' && errors[0].code=== '") + (std::string(path)=="/text" ? "ERR_WEBSOCKET_TEXT" : "ERR_WEBSOCKET_PROTOCOL") + "');");
        }
        evaluate("id=bridge.open('127.0.0.1',port,function(){throw new Error('Expected callback exception');},8192);");
        bool threw=false;
        for (unsigned i=0;i<1000 && !threw;++i) {
            threw = !!JSC_IOS_NetworkIdle();
            [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.005]];
        }
        assert(threw);
        JSC_IOS_NetworkShutdown();
        JSGlobalContextRelease(ctx);
        puts("PASS native Network.framework bridge: TCP/UDP/WebSocket, subprotocol/text rejection, byte ownership, background cleanup, bounds, callback exceptions");
    }
}
