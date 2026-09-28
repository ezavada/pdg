// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/pdg_script_impl.cpp
//    $PDG_ROOT/src/bindings/javascript/jsc/pdg_script_macros.h
//
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
//
// This is the Proprietary and Confidential intellectual
// property of Dream Rock Studios, LLC and its authors
// 
// Copying, Redistribution, or Use of this file without
// license from Dream Rock Studios, LLC is prohibited
// -----------------------------------------------



#include "pdg_project.h"

#define PDG_COMPILING_SCRIPT_IMPL

#include "pdg_script_impl.h"
#include "pdg_script_interface.h"

#include "internals.h"
#include "pdg-lib.h"

#include <sstream>
#include <cmath>
#include <cstdlib>

#ifndef PDG_DEBUG_SCRIPTING

#define SCRIPT_DEBUG_ONLY(_expression)
#else
#define SCRIPT_DEBUG_ONLY DEBUG_ONLY
#endif

namespace pdg
{

    bool s_HaveSavedError = false;

    ScriptSerializable::ScriptSerializable()
    {
    }

    ScriptEventHandler::ScriptEventHandler()
    {
    }

    ScriptAnimationHelper::ScriptAnimationHelper()
    {
#ifdef PDG_USING_JAVASCRIPT_CORE
        mScriptAnimateFunc = nullptr;
#endif
    }

#ifndef PDG_NO_GUI

    ScriptSpriteDrawHelper::ScriptSpriteDrawHelper()
    {
    }
#endif

    JSValueRef Rand(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSValueMakeNumber(ctx, OS::rand());
    }
    JSValueRef GameCriticalRandom(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSValueMakeNumber(ctx, OS::gameCriticalRandom());
    }
    JSValueRef Srand(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""seed"")");
        uint32 seed = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
        OS::srand( seed );
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SetSerializationDebugMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""debugMode"")");
        bool debugMode = JSValueToBoolean(ctx, arguments[1 -1]);
        ISerializer::s_DebugMode = debugMode;
        return JSValueMakeUndefined(ctx);
    }

    bool Initializer::allowHorizontalOrientation() noexcept { return true; }
    bool Initializer::allowVerticalOrientation() noexcept { return true; }
    const char* Initializer::getAppName(bool haveMainResourceFile) noexcept { return "pdg"; }
    const char* Initializer::getMainResourceFileName() noexcept {return NULL;}
    bool Initializer::installGlobalHandlers() noexcept {return true;}
    bool Initializer::getGraphicsEnvironmentDimensions(Rect maxWindowDim, Rect maxFullScreenDim,
        long& ioWidth, long& ioHeight, uint8& ioDepth) noexcept
    {
        ioWidth = 640;
        ioHeight = 480;
        ioDepth = 32;
        return false;
    }

    JSValueRef Idle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg_LibIdle();
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Run(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg_LibRun();
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Quit(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg_LibQuit();
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef IsQuitting(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool isQuitting = pdg_LibIsQuitting();
        return JSValueMakeBoolean(ctx, isQuitting);
    }

}
