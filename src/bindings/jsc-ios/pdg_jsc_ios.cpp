// -----------------------------------------------
// pdg_jsc_ios.cpp
//
// support and bindings for pdg game engine as with
// a JavaScriptCore engine for JavaScript support
// running on iOS
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_project.h"
#include "pdg_ios_network.h"

#include "pdg_jsc_ios.h"
#include "pdg_javascript.h"
#include "pdg_jsc_support.h"
#include "../generated/jsc/pdg_script_interface.h"

#define PDG_JS_CHAR JSChar
#include "pdg_natives.h"

#include "zlib.h"
#include "pdg/version.h"
#include "pdg/sys/platform.h"

#ifdef PDG_USE_CHIPMUNK_PHYSICS
#include "chipmunk/chipmunk.h"
#endif

#ifdef PDG_USE_GLFW
#include "GLFW/glfw3.h"
#endif

#ifdef PDG_USE_LIBPNG
#include "png.h"
#endif

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

extern char** environ;

#define JSC_VERSION "534.27"  // couldn't find this defined anywhere

namespace pdg {
    extern void CreateSingletons();
    extern void initBindings(JSContextRef ctx, JSObjectRef exports);
	extern const char* ios_getExecPath();
    extern JSContextRef gMainContext;
}

static JSValueRef JSC_IOS_Binding(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static void JSC_IOS_SetupProcessObject(int argc, const char* argv[]);
static void JSC_IOS_InstallIntoApplication();
static void JSC_IOS_Load();
static char* JSC_IOS_CreateStringWithContentsOfFile(const char* fileName);
static void JSC_IOS_DefineConstants(JSObjectRef exports);

static JSValueRef JSC_IOS_Cwd(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_WriteStdOut(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_WriteStdErr(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_ReallyExit(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_RunInThisContext(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_ReadFileContents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_WriteFileContents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_Unlink(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_ReadLink(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_Stat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_LStat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_OpenFile(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_CloseFile(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_ReadFromFile(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
static JSValueRef JSC_IOS_WriteToFile(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);

static JSContextRef ctx = 0;
static JSObjectRef process = 0;

static JSObjectRef binding_cache = 0;
//static JSObjectRef module_load_list = 0;


using namespace pdg;

extern "C" bool WebCoreWebThreadIsLockedOrDisabled(void);

// this is needed for debug builds of the JavaScriptCore library
extern "C" bool WebCoreWebThreadIsLockedOrDisabled(void) {
	return false;
}

DECLARE_SYMBOL(_pdgScriptClasses);

DECLARE_SYMBOL(dev);
DECLARE_SYMBOL(ino);
DECLARE_SYMBOL(mode);

DECLARE_SYMBOL(nlink);
DECLARE_SYMBOL(uid);
DECLARE_SYMBOL(gid);
DECLARE_SYMBOL(rdev);

DECLARE_SYMBOL(size);
DECLARE_SYMBOL(blksize);
DECLARE_SYMBOL(blocks);

DECLARE_SYMBOL(atime);
DECLARE_SYMBOL(mtime);
DECLARE_SYMBOL(ctime);

extern "C" void scriptSetupCompleted() {
    SETUP_NON_SCRIPT_EXCEPTION;

	std::cerr << "scriptSetupCompleted() ENTER \n";
	// process._pdgScriptClasses
    JSValueRef propVal = JSObjectGetProperty(ctx, process, SYMBOL(_pdgScriptClasses), 0);
	if (!propVal || JSValueIsUndefined(ctx, propVal) || JSValueIsNull(ctx, propVal)) {
		std::cerr << "scriptSetupCompleted() already complete \n";
		return;
	}
	JSObjectRef obj = JSValueToObject(ctx, propVal, exception);
	JSPropertyNameArrayRef array = JSObjectCopyPropertyNames(ctx, obj);
	int length = (int)JSPropertyNameArrayGetCount(array);
	for (int i = 0; i < length; i++) {
		JSStringRef prop = JSPropertyNameArrayGetNameAtIndex(array, i);
		JSValueRef val = JSObjectGetProperty(ctx, obj, prop, exception);
		JSObjectRef proto = JSValueToObject(ctx, val, exception);
		JSValueProtect(ctx, proto);
		if (JSStringIsEqualToUTF8CString(prop, "Color")) {
			JSC_SetColorPrototype(proto);
		} else if (JSStringIsEqualToUTF8CString(prop, "Offset")) {
			JSC_SetOffsetPrototype(proto);
		} else if (JSStringIsEqualToUTF8CString(prop, "Point")) {
			JSC_SetPointPrototype(proto);
		} else if (JSStringIsEqualToUTF8CString(prop, "Vector")) {
			JSC_SetVectorPrototype(proto);
		} else if (JSStringIsEqualToUTF8CString(prop, "Rect")) {
			JSC_SetRectPrototype(proto);
		} else if (JSStringIsEqualToUTF8CString(prop, "RotatedRect")) {
			JSC_SetRotatedRectPrototype(proto);
		} else if (JSStringIsEqualToUTF8CString(prop, "Quad")) {
			JSC_SetQuadPrototype(proto);
		} else if (JSStringIsEqualToUTF8CString(prop, "MemBlock")) {
			JSC_SetMemBlockPrototype(proto);
		}
	}
	JSPropertyNameArrayRelease(array);
	JSObjectDeleteProperty(ctx, process, SYMBOL(_pdgScriptClasses), exception);
	std::cerr << "scriptSetupCompleted() EXIT \n";
}

// Sets up a process object in global namespace similar to the one provided
// by Node.js
static void JSC_IOS_SetupProcessObject(int argc, const char* argv[]) {
	JSValueRef* exception = 0;
	process = JSC_ObjectCreateEmpty(ctx);
	JSObjectSetProperty(ctx, process, _JSC_STR("version"), 
		STR2VAL("JavaScriptCore v" JSC_VERSION), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, process, _JSC_STR("title"), 
		STR2VAL("pdg-jsc-ios"), kJSPropertyAttributeNone, exception);

    // create stdout, stderr & stdin objects
    JSObjectRef stdoutObj = JSC_ObjectCreateEmpty(ctx);
    JSObjectSetProperty(ctx, process, _JSC_STR("stdout"),
                        OBJ2VAL(stdoutObj), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, stdoutObj, _JSC_STR("domain"),
                            NULL_VAL, kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, stdoutObj, _JSC_STR("isTTY"),
                            BOOL2VAL(false), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, stdoutObj, _JSC_STR("readable"),
                            BOOL2VAL(false), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, stdoutObj, _JSC_STR("writable"),
                            BOOL2VAL(true), kJSPropertyAttributeNone, exception);
    JSObjectRef stderrObj = JSC_ObjectCreateEmpty(ctx);
    JSObjectSetProperty(ctx, process, _JSC_STR("stderr"),
                        OBJ2VAL(stderrObj), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, stderrObj, _JSC_STR("domain"),
                            NULL_VAL, kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, stderrObj, _JSC_STR("isTTY"),
                            BOOL2VAL(false), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, stderrObj, _JSC_STR("readable"),
                            BOOL2VAL(false), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, stderrObj, _JSC_STR("writable"),
                            BOOL2VAL(true), kJSPropertyAttributeNone, exception);
    JSObjectRef stdinObj = JSC_ObjectCreateEmpty(ctx);
    JSObjectSetProperty(ctx, process, _JSC_STR("stdin"),
                        OBJ2VAL(stdinObj), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, stdinObj, _JSC_STR("domain"),
                            NULL_VAL, kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, stdinObj, _JSC_STR("isTTY"),
                            BOOL2VAL(false), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, stdinObj, _JSC_STR("readable"),
                            BOOL2VAL(true), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, stdinObj, _JSC_STR("writable"),
                            BOOL2VAL(false), kJSPropertyAttributeNone, exception);

	// create "versions" object for library versions
	JSObjectRef versionsObj = JSC_ObjectCreateEmpty(ctx);
	JSObjectSetProperty(ctx, process, _JSC_STR("versions"), 
		OBJ2VAL(versionsObj), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, versionsObj, _JSC_STR("jsc"), 
            STR2VAL(JSC_VERSION), kJSPropertyAttributeNone, exception);
	    JSObjectSetProperty(ctx, versionsObj, _JSC_STR("zlib"), 
		    STR2VAL(ZLIB_VERSION), kJSPropertyAttributeNone, exception);
	    JSObjectSetProperty(ctx, versionsObj, _JSC_STR("pdg"), 
		    STR2VAL(PDG_VERSION), kJSPropertyAttributeNone, exception);
	  #ifdef PDG_USE_CHIPMUNK_PHYSICS
	    JSObjectSetProperty(ctx, versionsObj, _JSC_STR("chipmunk"), 
		    STR2VAL(cpVersionString), kJSPropertyAttributeNone, exception);
	  #endif
	  #if defined( PDG_USE_GLFW )
	    JSObjectSetProperty(ctx, versionsObj, _JSC_STR("glfw"), 
		    STR2VAL(#GLFW_VERSION_MAJOR "." #GLFW_VERSION_MINOR "." #GLFW_VERSION_REVISION), 
		    kJSPropertyAttributeNone, exception);
	  #endif
	  #if defined( PDG_USE_LIBPNG )
	    JSObjectSetProperty(ctx, versionsObj, _JSC_STR("libpng"), 
		    STR2VAL(PNG_LIBPNG_VER_STRING), kJSPropertyAttributeNone, exception);
	  #endif

	// create "features" object for build features
	JSObjectRef featuresObj = JSC_ObjectCreateEmpty(ctx);
	JSObjectSetProperty(ctx, process, _JSC_STR("features"), 
		OBJ2VAL(featuresObj), kJSPropertyAttributeNone, exception);
	    JSObjectSetProperty(ctx, featuresObj, _JSC_STR("debug"), 
	    #if defined(DEBUG)
    		BOOL2VAL(true)
		#else
    		BOOL2VAL(false)
		#endif
		, kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, featuresObj, _JSC_STR("uv"), 
		BOOL2VAL(false), kJSPropertyAttributeNone, exception);

	// arch and platform
	JSObjectSetProperty(ctx, process, _JSC_STR("arch"), 
		#ifdef PLATFORM_ARM
			STR2VAL("arm")
		#else
			STR2VAL("i386")
		#endif
		, kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, process, _JSC_STR("platform"), 
		STR2VAL("darwin"), kJSPropertyAttributeNone, exception);
#ifdef PLATFORM_IOS
	JSObjectSetProperty(ctx, process, _JSC_STR("ios"), 
        BOOL2VAL(true), kJSPropertyAttributeNone, exception);
#endif

	// create empty "env" object
	JSObjectRef envObj = JSC_ObjectCreateEmpty(ctx);
	JSObjectSetProperty(ctx, process, _JSC_STR("env"), 
		OBJ2VAL(envObj), kJSPropertyAttributeNone, exception);
	// now add all the env variables
	  int env_size = 0;
	  while (environ[env_size]) env_size++;
	  for (int i = 0; i < env_size; ++i) {
		const char* var = environ[i];
		const char* s = strchr(var, '=');
		if (!s) {
			JSObjectSetProperty(ctx, envObj, _JSC_STR(var), STR2VAL(""), 
				kJSPropertyAttributeNone, exception);
		} else {
			int name_len = (int)(s - var);
			s++;
			char vname[256];
            std::strncpy(vname, var, name_len);
            vname[name_len] = 0;
			JSObjectSetProperty(ctx, envObj, _JSC_STR(vname), STR2VAL(s), 
				kJSPropertyAttributeNone, exception);
		}
	  }

	// setup process.binding
	JSObjectRef bindingRef = JSObjectMakeFunctionWithCallback(ctx, _JSC_STR("binding"), JSC_IOS_Binding);
	JSObjectSetProperty(ctx, process, _JSC_STR("binding"), bindingRef, kJSPropertyAttributeNone, exception);
    
	// setup process.cwd
	JSObjectRef cwdRef = JSObjectMakeFunctionWithCallback(ctx, _JSC_STR("cwd"), JSC_IOS_Cwd);
	JSObjectSetProperty(ctx, process, _JSC_STR("cwd"), cwdRef, kJSPropertyAttributeNone, exception);

	// setup process.execPath
	JSObjectSetProperty(ctx, process, _JSC_STR("execPath"), STR2VAL(ios_getExecPath()), kJSPropertyAttributeNone, exception);

	// Preserve the application arguments so simulator test runners can select a
	// suite or an individual spec without rebuilding the app.
	std::vector<JSValueRef> argumentValues;
	argumentValues.reserve(argc);
	for (int i = 0; i < argc; ++i) {
		argumentValues.push_back(STR2VAL(argv[i]));
	}
	JSObjectRef argumentArray = JSObjectMakeArray(ctx, argumentValues.size(),
		argumentValues.empty() ? 0 : argumentValues.data(), exception);
	JSObjectSetProperty(ctx, process, _JSC_STR("argv"), OBJ2VAL(argumentArray),
		kJSPropertyAttributeNone, exception);

    // The following are used to emulate some features of node.js in as simple a way as possible. _jsc_write_stdout|err
    // is used to implement the console object (see console.js) and _jsc_runInThisContext is used to execute a script
    // when invoked by require() or the module system
	// setup process._jsc_write_stdout and process.stdout.write()
	JSObjectRef writeStdOutRef = JSObjectMakeFunctionWithCallback(ctx, _JSC_STR("_jsc_write_stdout"), JSC_IOS_WriteStdOut);
	JSObjectSetProperty(ctx, process, _JSC_STR("_jsc_write_stdout"), writeStdOutRef, kJSPropertyAttributeDontEnum, exception);
    JSObjectSetProperty(ctx, stdoutObj, _JSC_STR("write"), writeStdOutRef, kJSPropertyAttributeNone, exception);

	// setup process._jsc_write_stderr and process.stderr.write()
	JSObjectRef writeStdErrRef = JSObjectMakeFunctionWithCallback(ctx, _JSC_STR("_jsc_write_stderr"), JSC_IOS_WriteStdErr);
	JSObjectSetProperty(ctx, process, _JSC_STR("_jsc_write_stderr"), writeStdErrRef, kJSPropertyAttributeDontEnum, exception);
	JSObjectSetProperty(ctx, stderrObj, _JSC_STR("write"), writeStdErrRef, kJSPropertyAttributeNone, exception);

	// Complete the minimal Node-compatible process lifecycle used by pdg.js.
	JSObjectRef reallyExitRef = JSObjectMakeFunctionWithCallback(ctx, _JSC_STR("reallyExit"), JSC_IOS_ReallyExit);
	JSObjectSetProperty(ctx, process, _JSC_STR("reallyExit"), reallyExitRef, kJSPropertyAttributeDontEnum, exception);

	// setup process._jsc_runInThisContext
	JSObjectRef runInThisContextRef = JSObjectMakeFunctionWithCallback(ctx, _JSC_STR("_jsc_runInThisContext"), JSC_IOS_RunInThisContext);
	JSObjectSetProperty(ctx, process, _JSC_STR("_jsc_runInThisContext"), runInThisContextRef, kJSPropertyAttributeDontEnum, exception);

	// setup process._jsc_stat
	JSObjectRef statRef = JSObjectMakeFunctionWithCallback(ctx, _JSC_STR("_jsc_stat"), JSC_IOS_Stat);
	JSObjectSetProperty(ctx, process, _JSC_STR("_jsc_stat"), statRef, kJSPropertyAttributeDontEnum, exception);

	// setup process._jsc_lstat
	JSObjectRef lstatRef = JSObjectMakeFunctionWithCallback(ctx, _JSC_STR("_jsc_lstat"), JSC_IOS_LStat);
	JSObjectSetProperty(ctx, process, _JSC_STR("_jsc_lstat"), lstatRef, kJSPropertyAttributeDontEnum, exception);

	// setup process._jsc_readlink
	JSObjectRef readlinkRef = JSObjectMakeFunctionWithCallback(ctx, _JSC_STR("_jsc_readlink"), JSC_IOS_ReadLink);
	JSObjectSetProperty(ctx, process, _JSC_STR("_jsc_readlink"), readlinkRef, kJSPropertyAttributeDontEnum, exception);

	// setup process._jsc_readFileContents
	JSObjectRef readFileContentsRef = JSObjectMakeFunctionWithCallback(ctx, _JSC_STR("_jsc_readFileContents"), JSC_IOS_ReadFileContents);
	JSObjectSetProperty(ctx, process, _JSC_STR("_jsc_readFileContents"), readFileContentsRef, kJSPropertyAttributeDontEnum, exception);

	// setup process._jsc_writeFileContents
	JSObjectRef writeFileContentsRef = JSObjectMakeFunctionWithCallback(ctx, _JSC_STR("_jsc_writeFileContents"), JSC_IOS_WriteFileContents);
	JSObjectSetProperty(ctx, process, _JSC_STR("_jsc_writeFileContents"), writeFileContentsRef, kJSPropertyAttributeDontEnum, exception);

	JSObjectRef unlinkRef = JSObjectMakeFunctionWithCallback(ctx, _JSC_STR("_jsc_unlink"), JSC_IOS_Unlink);
	JSObjectSetProperty(ctx, process, _JSC_STR("_jsc_unlink"), unlinkRef, kJSPropertyAttributeDontEnum, exception);
}

void JSC_IOS_Start(int argc, const char* argv[]) {
    SETUP_NON_SCRIPT_EXCEPTION;

	ctx = JSGlobalContextCreate(0);
    gMainContext = ctx;

	JSC_IOS_SetupProcessObject(argc, argv);
    JSC_IOS_NetworkInstall(ctx, process);

	// Call the process.binding("natives") function. We call it directly from C++ though
	// rather than through JavaScript
    JSValueRef myargv[4];
    myargv[0] = STR2VAL("natives");
	JSC_IOS_Binding(ctx, 0, 0, 1, myargv, exception);
	
	// install the pdg framework into the node.js application as a built-in
	// native module, accessable at process.pdg
	JSC_IOS_InstallIntoApplication();

	// next Node.js calls Load(), which executes "src/node.js" to finish initializing the
	// Node.js environment. That consists of setting up globals (including the console)
	// and then a bunch more stuff in the process object. Finally it would try to call
	// third party main, which in the pdg build is empty
	// We'll follow the same flow but call pdg_main.js which will be like node.js but
	// skip parts we don't care about
	JSC_IOS_Load();

	
}

DECLARE_SYMBOL(_needImmediateCallback);
DECLARE_SYMBOL(_immediateCallback);

void JSC_IOS_Idle() {
    JSValueRef networkException = JSC_IOS_NetworkIdle();
    if (networkException) FatalException(networkException, 0);
    // call into Javascript for any pending setImmediate() calls
    if (process) {
        JSValueRef propVal = JSObjectGetProperty(ctx, process, SYMBOL(_needImmediateCallback), 0);
        if (!VALUE_IS_UNDEFINED(propVal) && VAL2BOOL(propVal)) {
            // we need immediate callback(s)
            JSValueRef funcVal = JSObjectGetProperty(ctx, process, SYMBOL(_immediateCallback), 0);
            JSObjectRef processImmediateFunc = JSC_ValueToFunction(ctx, funcVal, 0);
            JSValueRef exception = 0;
            JSObjectCallAsFunction(ctx, processImmediateFunc, 0, 0, 0, &exception);
            if (exception) {
                FatalException(exception, processImmediateFunc);
            }
        }
    }
	// JavaScriptCore performs generational collection automatically. Forcing a
	// full collection on every display or timer tick turns short event-loop
	// yields into a major cost during client applications and test suites.
}

// this is called from Javascript via "process.binding"
static JSValueRef JSC_IOS_Binding(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
	*exception = 0;
	JSStringRef module = JSValueToStringCopy(ctx, arguments[0], exception);
	
	char module_v[1024];
	JSStringGetUTF8CString(module, module_v, 1024);

	// create the binding cache if it doesn't already exist
	if (!binding_cache) {
		binding_cache = JSC_ObjectCreateEmpty(ctx);
		JSValueProtect(ctx, binding_cache);
	}
	
	// check to see if the module is already cached, in which case
	// we can just return its cached exports
	if (JSObjectHasProperty(ctx, binding_cache, module)) {
		return JSObjectGetProperty(ctx, binding_cache, module, exception);
	}

// Append a string to process.moduleLoadList
    JSValueRef ignore;
    JS_EVAL(ignore, thisObject,
            "if (typeof process.moduleLoadList == 'undefined') { "
                "process.moduleLoadList = new Array();"
            "}"
            "process.moduleLoadList.push('Binding " << module_v << "');");

	JSObjectRef exports = 0;

	if (std::strcmp(module_v, "constants") == 0) {
		// define any constants
		exports = JSC_ObjectCreateEmpty(ctx);
    	JSC_IOS_DefineConstants(exports);
		JSObjectSetProperty(ctx, binding_cache, module, exports, kJSPropertyAttributeNone, exception);

	} else if (std::strcmp(module_v, "natives") == 0) {

		// go through all the pdg_natives (embedded js files) and add the source code
		// to the bindings_cache's "natives" object, which holds source code
		// for native modules that are included as strings
		exports = JSC_ObjectCreateEmpty(ctx);
		for (int i = 0; natives[i].name; i++) {
		
            int srclen =  (int)(natives[i].source_len / 2); // source_len is bytes, we want char count for 2 byte JSChar
			JSStringRef script = JSStringCreateWithCharacters(natives[i].source, srclen);
			
			if (natives[i].source == pdg_main_native) {
				// Skip dealing with pdg_main until after everything else has been added.
				// It will do final setup of environment and bootstap the user-land
				// javascript main.js
			} else {
				JSValueRef source = JSValueMakeString(ctx, script);
				JSObjectSetProperty(ctx, exports, _JSC_STR(natives[i].name), 
					source, kJSPropertyAttributeNone, exception);
			}
            JSStringRelease(script);
		}
		JSObjectSetProperty(ctx, binding_cache, module, OBJ2VAL(exports), kJSPropertyAttributeNone, exception);
	
	} else {
		// this wasn't any module we know about so we can't bind it
		THROW_ERR_LITERAL("No such module");
	}

	return OBJ2VAL(exports);
}

// install the pdg framework into the application as a built-in
// native module, accessable at process.pdg
static void JSC_IOS_InstallIntoApplication() {
    SETUP_NON_SCRIPT_EXCEPTION;
    
	// execute our C++ bindings and save the exports in process.pdg
	JSObjectRef exports = JSC_ObjectCreateEmpty(ctx);
    pdg::initBindings(ctx, exports);
	JSObjectSetProperty(ctx, process, _JSC_STR("pdg"), 
		OBJ2VAL(exports), kJSPropertyAttributeNone, exception);
    pdg::CreateSingletons();

}

static void JSC_IOS_DefineConstants(JSObjectRef exports) {
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("O_APPEND"), INT2VAL(O_APPEND), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("O_CREAT"), INT2VAL(O_CREAT), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("O_DIRECTORY"), INT2VAL(O_DIRECTORY), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("O_EXCL"), INT2VAL(O_EXCL), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("O_NOCTTY"), INT2VAL(O_NOCTTY), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("O_NOFOLLOW"), INT2VAL(O_NOFOLLOW), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("O_RDONLY"), INT2VAL(O_RDONLY), kJSPropertyAttributeNone, 0);
    JSObjectSetProperty(gMainContext, exports, _JSC_STR("O_RDWR"), INT2VAL(O_RDWR), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("O_SYMLINK"), INT2VAL(O_SYMLINK), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("O_SYNC"), INT2VAL(O_SYNC), kJSPropertyAttributeNone, 0);
    JSObjectSetProperty(gMainContext, exports, _JSC_STR("O_TRUNC"), INT2VAL(O_TRUNC), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("O_WRONLY"), INT2VAL(O_WRONLY), kJSPropertyAttributeNone, 0);

	JSObjectSetProperty(gMainContext, exports, _JSC_STR("S_IFMT"), INT2VAL(S_IFMT), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("S_IFDIR"), INT2VAL(S_IFDIR), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("S_IFREG"), INT2VAL(S_IFREG), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("S_IFBLK"), INT2VAL(S_IFBLK), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("S_IFCHR"), INT2VAL(S_IFCHR), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("S_IFLNK"), INT2VAL(S_IFLNK), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("S_IFIFO"), INT2VAL(S_IFIFO), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(gMainContext, exports, _JSC_STR("S_IFSOCK"), INT2VAL(S_IFSOCK), kJSPropertyAttributeNone, 0);
}


// In Node.js Load() executes "src/node.js" to finish initializing the
// Node.js environment. That consists of setting up globals (including the console)
// and then a bunch more stuff in the process object. Finally it would try to call
// third party main, which in the pdg build is empty
// We'll follow the same flow but call pdg_main.js which will be like node.js but
// skip parts we don't care about
static void JSC_IOS_Load() {
    SETUP_NON_SCRIPT_EXCEPTION;

  // Compile, execute the src/bindings/jsc-ios/pdg_main.js file. (Which was 
  // included as static C string in pdg_natives.h. 'pdg_main_native' is the string 
  // containing that source code.)

  // The pdg_main.js file returns a function 'f'
#if 0
	JSObjectRef exports = JSC_ObjectCreateEmpty(ctx);
	JSStringRef script = JSStringCreateWithCharacters(pdg_main_native, sizeof(pdg_main_native)/2 - 1);
    JSValueRef f_val = JSEvaluateScript(ctx, script, exports, NULL, 1, exception);
    JSStringRelease(script);
#else
    JSValueRef f_val = JSC_ExecuteScriptFile("pdg_main.js", exception);
#endif

	CATCH_EXCEPTION(f_val) {
    	FatalException(EXCEPTION_DATA);
	}

  // Now we call 'f' with the 'process' variable that we've built up with
  // all our bindings. Inside pdg_main.js we'll take care of assigning things to
  // their places.
    JSValueRef argv[1];
    argv[0] = OBJ2VAL(process);
  	JSObjectRef f = VAL2OBJ(f_val);
    JSValueRef resVal = CALL_SCRIPT(f, 0, 1, argv); // global this
    
	CATCH_EXCEPTION(resVal) {
    	FatalException(EXCEPTION_DATA);
	}
}

static JSValueRef JSC_IOS_Cwd(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
	char s[1024];
	JSValueRef result = STR2VAL( getcwd(s, 1024) );
    return result;
}

static JSValueRef JSC_IOS_WriteStdOut(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    if (argumentCount > 0) {
        VALUE_TO_CSTRING(msg, arguments[0]);
        std::cout << msg;
    }
    return JSValueMakeUndefined(ctx);
}

static JSValueRef JSC_IOS_WriteStdErr(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    if (argumentCount > 0) {
        VALUE_TO_CSTRING(msg, arguments[0]);
        std::cerr << msg;
    }
    return JSValueMakeUndefined(ctx);
}

static JSValueRef JSC_IOS_ReallyExit(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
	int exitCode = 0;
	if (argumentCount > 0 && JSValueIsNumber(ctx, arguments[0])) {
		exitCode = static_cast<int>(JSValueToNumber(ctx, arguments[0], exception));
	}
	JSC_IOS_NetworkShutdown();
	std::exit(exitCode);
	return JSValueMakeUndefined(ctx);
}

static JSValueRef JSC_IOS_RunInThisContext(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    JSStringRef filename = (argumentCount>1) ? JSValueToStringCopy(ctx, arguments[1], 0) : 0;
    JSObjectRef globalObj = JSContextGetGlobalObject(ctx);
    JSStringRef script = JSValueToStringCopy(ctx, arguments[0], exception);
    if (!script) return JSValueMakeNull(ctx);
    int startingLineNum = 1;
    JSValueRef result = JSEvaluateScript(ctx, script, globalObj, filename, startingLineNum, exception);
    JSStringRelease(script);
    JSStringRelease(filename);
    return result;
}

static JSValueRef JSC_IOS_ReadFileContents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
	VALUE_TO_CSTRING(filename, arguments[0]);
	std::string openMode("r");
	if (argumentCount > 1) {
		VALUE_TO_CSTRING(omParam, arguments[1]);
		openMode = omParam;
	}
	char* contentsUTF8 = JSC_CreateStringWithContentsOfFile(filename, openMode.c_str());
	if (!contentsUTF8) {
		return JSValueMakeUndefined(gMainContext);
	} else {
		JSStringRef result = JSStringCreateWithUTF8CString(contentsUTF8);
		free(contentsUTF8);
		JSValueRef value = JSValueMakeString(ctx, result);
		JSStringRelease(result);
		return value;
	}

}

static JSValueRef JSC_IOS_WriteFileContents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
	if (argumentCount < 2) {
		THROW_ERR_LITERAL("writeFile requires a path and data");
	}
	VALUE_TO_CSTRING(filename, arguments[0]);
	VALUE_TO_CSTRING(contents, arguments[1]);
	std::string openMode("w");
	if (argumentCount > 2 && JSValueIsString(ctx, arguments[2])) {
		VALUE_TO_CSTRING(flag, arguments[2]);
		if (flag[0] == 'a') {
			openMode = "a";
		}
	}

	FILE* outFile = std::fopen(filename, openMode.c_str());
	if (!outFile) {
		THROW_ERR_LITERAL("could not open file for writing: " << filename << " (errno: " << errno << ")");
	}
	size_t contentLength = std::strlen(contents);
	size_t written = std::fwrite(contents, 1, contentLength, outFile);
	int closeResult = std::fclose(outFile);
	if (written != contentLength || closeResult != 0) {
		THROW_ERR_LITERAL("could not write file: " << filename << " (errno: " << errno << ")");
	}
	return JSValueMakeUndefined(ctx);
}

static JSValueRef JSC_IOS_Unlink(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
	if (argumentCount < 1) {
		THROW_ERR_LITERAL("unlink requires a path");
	}
	VALUE_TO_CSTRING(path, arguments[0]);
	if (unlink(path) != 0) {
		THROW_ERR_LITERAL("could not unlink file: " << path << " (errno: " << errno << ")");
	}
	return JSValueMakeUndefined(ctx);
}

static JSValueRef JSC_IOS_ReadLink(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
	VALUE_TO_CSTRING(path, arguments[0]);
	char* buf = (char*) std::malloc(4068);
	size_t len = readlink(path, buf, 4068);
	if (len == -1) {
		std::free(buf);
		THROW_ERR_LITERAL("readlink error: " << path << " (errno: " << errno << ")");
 	}
 	buf[len] = 0;
 	VALUE result = STR2VAL(buf);
	std::free(buf);
	return result;
}

static JSValueRef JSC_IOS_Stat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
	VALUE_TO_CSTRING(path, arguments[0]);
	struct stat sb;
    if (stat(path, &sb) == -1) {
		THROW_ERR_LITERAL("file not found: " << path << " (errno: " << errno << ")");
    }
	JSObjectRef statObj = JSC_ObjectCreateEmpty(ctx);
	JSObjectSetProperty(ctx, statObj, SYMBOL(dev), INT2VAL(sb.st_dev), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(ino), INT2VAL(sb.st_ino), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(mode), INT2VAL(sb.st_mode), kJSPropertyAttributeNone, 0);

	JSObjectSetProperty(ctx, statObj, SYMBOL(nlink), INT2VAL(sb.st_nlink), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(uid), INT2VAL(sb.st_uid), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(gid), INT2VAL(sb.st_gid), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(rdev), INT2VAL(sb.st_rdev), kJSPropertyAttributeNone, 0);

	JSObjectSetProperty(ctx, statObj, SYMBOL(size), INT2VAL(sb.st_size), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(blksize), INT2VAL(sb.st_blksize), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(blocks), INT2VAL(sb.st_blocks), kJSPropertyAttributeNone, 0);

	JSObjectSetProperty(ctx, statObj, SYMBOL(atime), TIME_T_TO_VALUE(sb.st_atime), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(mtime), TIME_T_TO_VALUE(sb.st_mtime), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(ctime), TIME_T_TO_VALUE(sb.st_ctime), kJSPropertyAttributeNone, 0);

	return OBJ2VAL(statObj);
}

static JSValueRef JSC_IOS_LStat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
	VALUE_TO_CSTRING(path, arguments[0]);
	struct stat sb;
    if (lstat(path, &sb) == -1) {
		THROW_ERR_LITERAL("file not found: " << path << " (errno: " << errno << ")");
    }
	JSObjectRef statObj = JSC_ObjectCreateEmpty(ctx);
	JSObjectSetProperty(ctx, statObj, SYMBOL(dev), INT2VAL(sb.st_dev), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(ino), INT2VAL(sb.st_ino), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(mode), INT2VAL(sb.st_mode), kJSPropertyAttributeNone, 0);

	JSObjectSetProperty(ctx, statObj, SYMBOL(nlink), INT2VAL(sb.st_nlink), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(uid), INT2VAL(sb.st_uid), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(gid), INT2VAL(sb.st_gid), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(rdev), INT2VAL(sb.st_rdev), kJSPropertyAttributeNone, 0);

	JSObjectSetProperty(ctx, statObj, SYMBOL(size), INT2VAL(sb.st_size), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(blksize), INT2VAL(sb.st_blksize), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(blocks), INT2VAL(sb.st_blocks), kJSPropertyAttributeNone, 0);

	JSObjectSetProperty(ctx, statObj, SYMBOL(atime), TIME_T_TO_VALUE(sb.st_atime), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(mtime), TIME_T_TO_VALUE(sb.st_mtime), kJSPropertyAttributeNone, 0);
	JSObjectSetProperty(ctx, statObj, SYMBOL(ctime), TIME_T_TO_VALUE(sb.st_ctime), kJSPropertyAttributeNone, 0);

	return OBJ2VAL(statObj);
}

static JSValueRef JSC_IOS_OpenFile(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    return JSValueMakeUndefined(ctx);
}

static JSValueRef JSC_IOS_CloseFile(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    return JSValueMakeUndefined(ctx);
}

static JSValueRef JSC_IOS_ReadFromFile(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    return JSValueMakeUndefined(ctx);
}

static JSValueRef JSC_IOS_WriteToFile(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    return JSValueMakeUndefined(ctx);
}
