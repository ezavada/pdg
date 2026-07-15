// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/pdg_script_impl.cpp
//    $PDG_ROOT/src/bindings/javascript/v8/pdg_script_macros.h
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
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
    }

    ScriptSpriteCollideHelper::ScriptSpriteCollideHelper()
    {
    }

#ifndef PDG_NO_GUI

    ScriptSpriteDrawHelper::ScriptSpriteDrawHelper()
    {
    }
#endif

    void Rand(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, OS::rand()) ); return; };
    }
    void GameCriticalRandom(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, OS::gameCriticalRandom()) ); return; };
    }
    void Srand(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] seed)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""seed"")");
            return;
        }
        unsigned long seed = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        OS::srand( seed );
        args.GetReturnValue().SetUndefined();
    }
    void SetSerializationDebugMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(bool debugMode)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""debugMode"")");
            return;
        }
        bool debugMode = args[1 -1]->BooleanValue(isolate);
        ISerializer::s_DebugMode = debugMode;
        args.GetReturnValue().SetUndefined();
    }

    bool Initializer::allowHorizontalOrientation() throw() { return true; }
    bool Initializer::allowVerticalOrientation() throw() { return true; }
    const char* Initializer::getAppName(bool haveMainResourceFile) throw() { return "pdg"; }
    const char* Initializer::getMainResourceFileName() throw() {return NULL;}
    bool Initializer::installGlobalHandlers() throw() {return true;}
    bool Initializer::getGraphicsEnvironmentDimensions(Rect maxWindowDim, Rect maxFullScreenDim,
        long& ioWidth, long& ioHeight, uint8& ioDepth) throw()
    {
        ioWidth = 640;
        ioHeight = 480;
        ioDepth = 32;
        return false;
    }

    void Idle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        pdg_LibIdle();
        args.GetReturnValue().SetUndefined();
    }

    void Run(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        pdg_LibRun();
        args.GetReturnValue().SetUndefined();
    }

    void Quit(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        pdg_LibQuit();
        args.GetReturnValue().SetUndefined();
    }

    void IsQuitting(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool isQuitting = pdg_LibIsQuitting();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, isQuitting) ); return; };
    }

}
