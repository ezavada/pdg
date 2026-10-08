#ifndef PDG_IOS_NETWORK_H
#define PDG_IOS_NETWORK_H
#include <JavaScriptCore/JavaScriptCore.h>
void JSC_IOS_NetworkInstall(JSContextRef context, JSObjectRef process);
// Called only on the PDG JavaScript thread. Returns a callback exception, if any.
JSValueRef JSC_IOS_NetworkIdle();
void JSC_IOS_NetworkSuspend();
void JSC_IOS_NetworkShutdown();
#endif
