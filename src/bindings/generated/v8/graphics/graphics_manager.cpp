// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/graphics_manager.cpp
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

#include "pdg_script_interface.h"
#include "pdg_script_impl.h"

#include "internals.h"
#include "pdg-lib.h"

#include <cstdlib>

namespace pdg
{

#ifndef PDG_NO_GUI

    static bool s_GraphicsManager_InNewFromCpp = false;

    void GraphicsManagerWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall() && !s_GraphicsManager_InNewFromCpp)
        {
            v8::Local<v8::String> error_msg = v8::String::NewFromUtf8(isolate,
                "GraphicsManager" " cannot be instantiated with 'new'. Use the singleton instance: require('pdg')." "gfx"
                ).ToLocalChecked();
            isolate->ThrowException(v8::Exception::TypeError(error_msg));
            return;
        }

        GraphicsManagerWrap* objWrapper = new GraphicsManagerWrap(args);
        objWrapper->Wrap(args.This());

        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    v8::Persistent<v8::Object> GraphicsManagerWrap::instance_;
    bool GraphicsManagerWrap::instanced_ = false;

    v8::Local<v8::Object> GraphicsManagerWrap::GetScriptSingletonInstance(v8::Isolate* isolate)
    {
        v8::EscapableHandleScope scope(isolate);
        if (!instanced_)
        {

            s_GraphicsManager_InNewFromCpp = true;
            v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
            v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
            if (maybeFunc.IsEmpty())
            {
                s_GraphicsManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
            v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
            if (maybeInstance.IsEmpty())
            {
                s_GraphicsManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
            s_GraphicsManager_InNewFromCpp = false;
            instance_.Reset(isolate, instance);
            instanced_ = true;
        }
        v8::Local<v8::Object> inst_ = v8::Local<v8::Object>::New(isolate, instance_);
        return scope.Escape(inst_);
    }

    GraphicsManager* GraphicsManagerWrap::getSingletonInstance()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Object> val = GetScriptSingletonInstance(isolate)->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(val);
        return dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);
    }

    v8::Persistent<v8::FunctionTemplate> GraphicsManagerWrap::constructorTpl_;

    void GraphicsManagerWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "GraphicsManager").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetNumScreens_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetNumScreens_Tpl =
            v8::FunctionTemplate::New(isolate, GetNumScreens, v8::Local<v8::Value>(), GetNumScreens_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""NumScreens").ToLocalChecked(), GetNumScreens_Tpl);
        v8::Local<v8::Signature> GetFPS_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFPS_Tpl =
            v8::FunctionTemplate::New(isolate, GetFPS, v8::Local<v8::Value>(), GetFPS_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""FPS").ToLocalChecked(), GetFPS_Tpl);
        v8::Local<v8::Signature> GetTargetFPS_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTargetFPS_Tpl =
            v8::FunctionTemplate::New(isolate, GetTargetFPS, v8::Local<v8::Value>(), GetTargetFPS_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""TargetFPS").ToLocalChecked(), GetTargetFPS_Tpl);
        v8::Local<v8::Signature> SetTargetFPS_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetTargetFPS_Tpl =
            v8::FunctionTemplate::New(isolate, SetTargetFPS, v8::Local<v8::Value>(), SetTargetFPS_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""TargetFPS").ToLocalChecked(), SetTargetFPS_Tpl);
        v8::Local<v8::Signature> GetMouse_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMouse_Tpl =
            v8::FunctionTemplate::New(isolate, GetMouse, v8::Local<v8::Value>(), GetMouse_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Mouse").ToLocalChecked(), GetMouse_Tpl);
        v8::Local<v8::Signature> GetCurrentScreenMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCurrentScreenMode_Tpl =
            v8::FunctionTemplate::New(isolate, GetCurrentScreenMode, v8::Local<v8::Value>(), GetCurrentScreenMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCurrentScreenMode").ToLocalChecked(), GetCurrentScreenMode_Tpl);
        v8::Local<v8::Signature> GetScreenBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetScreenBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetScreenBounds, v8::Local<v8::Value>(), GetScreenBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getScreenBounds").ToLocalChecked(), GetScreenBounds_Tpl);
        v8::Local<v8::Signature> GetNumSupportedScreenModes_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetNumSupportedScreenModes_Tpl =
            v8::FunctionTemplate::New(isolate, GetNumSupportedScreenModes, v8::Local<v8::Value>(), GetNumSupportedScreenModes_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getNumSupportedScreenModes").ToLocalChecked(), GetNumSupportedScreenModes_Tpl);
        v8::Local<v8::Signature> GetNthSupportedScreenMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetNthSupportedScreenMode_Tpl =
            v8::FunctionTemplate::New(isolate, GetNthSupportedScreenMode, v8::Local<v8::Value>(), GetNthSupportedScreenMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getNthSupportedScreenMode").ToLocalChecked(), GetNthSupportedScreenMode_Tpl);
        v8::Local<v8::Signature> SetScreenMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetScreenMode_Tpl =
            v8::FunctionTemplate::New(isolate, SetScreenMode, v8::Local<v8::Value>(), SetScreenMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setScreenMode").ToLocalChecked(), SetScreenMode_Tpl);
        v8::Local<v8::Signature> CreateWindowPort_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateWindowPort_Tpl =
            v8::FunctionTemplate::New(isolate, CreateWindowPort, v8::Local<v8::Value>(), CreateWindowPort_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createWindowPort").ToLocalChecked(), CreateWindowPort_Tpl);
        v8::Local<v8::Signature> CreateFullScreenPort_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateFullScreenPort_Tpl =
            v8::FunctionTemplate::New(isolate, CreateFullScreenPort, v8::Local<v8::Value>(), CreateFullScreenPort_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createFullScreenPort").ToLocalChecked(), CreateFullScreenPort_Tpl);
        v8::Local<v8::Signature> CloseGraphicsPort_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CloseGraphicsPort_Tpl =
            v8::FunctionTemplate::New(isolate, CloseGraphicsPort, v8::Local<v8::Value>(), CloseGraphicsPort_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "closeGraphicsPort").ToLocalChecked(), CloseGraphicsPort_Tpl);
        v8::Local<v8::Signature> CloseAllGraphicsPorts_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CloseAllGraphicsPorts_Tpl =
            v8::FunctionTemplate::New(isolate, CloseAllGraphicsPorts, v8::Local<v8::Value>(), CloseAllGraphicsPorts_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "closeAllGraphicsPorts").ToLocalChecked(), CloseAllGraphicsPorts_Tpl);
        v8::Local<v8::Signature> CreateFont_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateFont_Tpl =
            v8::FunctionTemplate::New(isolate, CreateFont, v8::Local<v8::Value>(), CreateFont_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createFont").ToLocalChecked(), CreateFont_Tpl);
        v8::Local<v8::Signature> GetMainPort_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMainPort_Tpl =
            v8::FunctionTemplate::New(isolate, GetMainPort, v8::Local<v8::Value>(), GetMainPort_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMainPort").ToLocalChecked(), GetMainPort_Tpl);
        v8::Local<v8::Signature> SwitchToFullScreenMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SwitchToFullScreenMode_Tpl =
            v8::FunctionTemplate::New(isolate, SwitchToFullScreenMode, v8::Local<v8::Value>(), SwitchToFullScreenMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "switchToFullScreenMode").ToLocalChecked(), SwitchToFullScreenMode_Tpl);
        v8::Local<v8::Signature> SwitchToWindowMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SwitchToWindowMode_Tpl =
            v8::FunctionTemplate::New(isolate, SwitchToWindowMode, v8::Local<v8::Value>(), SwitchToWindowMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "switchToWindowMode").ToLocalChecked(), SwitchToWindowMode_Tpl);
        v8::Local<v8::Signature> InFullScreenMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> InFullScreenMode_Tpl =
            v8::FunctionTemplate::New(isolate, InFullScreenMode, v8::Local<v8::Value>(), InFullScreenMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "inFullScreenMode").ToLocalChecked(), InFullScreenMode_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void GraphicsManagerWrap::GetNumScreens(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        int theNumScreens = self->getNumScreens();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, theNumScreens) ); return; };
    }

    void GraphicsManagerWrap::GetFPS(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theFPS = self->getFPS();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theFPS) ); return; };
    }

    void GraphicsManagerWrap::GetTargetFPS(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theTargetFPS = self->getTargetFPS();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theTargetFPS) ); return; };
    }

    void GraphicsManagerWrap::SetTargetFPS(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object GraphicsManager]" " function" "(number inTargetFPS)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theTargetFPS"")");
            return;
        }
        double theTargetFPS = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        self->setTargetFPS(theTargetFPS);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void GraphicsManagerWrap::GetMouse(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "([number int] mouseNumber = 0)").ToLocalChecked() ); return; };
        };
        if (args.Length() < 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0, true);
            return;
        };
        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""mouseNumber"")");
            return;
        }
        long mouseNumber = (args.Length()<1) ? 0 : args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;

        pdg::Point theMouse = self->getMouse(mouseNumber);
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, theMouse) ); return; };
    }

    void GraphicsManagerWrap::GetNumSupportedScreenModes(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "([number int] screen = PRIMARY_SCREEN)").ToLocalChecked() ); return; };
        };
        if (args.Length() < 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0, true);
            return;
        };
        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""screenNum"")");
            return;
        }
        long screenNum = (args.Length()<1) ? screenNum_PrimaryScreen : args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;

        int32 theNumSupportedScreenModes = self->getNumSupportedScreenModes(screenNum);
        { args.GetReturnValue().Set( v8::Integer::New(isolate, theNumSupportedScreenModes) ); return; };
    }

    void GraphicsManagerWrap::SetScreenMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);
        ;
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] width, [number int] height, [number int] screenNum = PRIMARY_SCREEN, [number int] bpp = 0)" " - " "changes specified screen to closest matching mode").ToLocalChecked() ); return; };
        };

        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""width"")");
            return;
        }
        long width = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""height"")");
            return;
        }
        long height = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""screenNum"")");
            return;
        }
        long screenNum = (args.Length()<3) ? screenNum_PrimaryScreen : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""bpp"")");
            return;
        }
        long bpp = (args.Length()<4) ? 0 : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->setScreenMode(width, height, screenNum, bpp);
        args.GetReturnValue().SetUndefined();
    }

    void GraphicsManagerWrap::CreateWindowPort(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Port]" " function" "([object Rect] rect, string windName = \"\", [number int] bpp = 0)" " - " "create windowed drawing port with given dimensions, title and depth").ToLocalChecked() ); return; };
        };

        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!v8_ValueIsRect(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
            return;
        }
        pdg::Rect rect = v8_ValueToRect(isolate, args[1 -1]);
        if (args.Length() >= 2 && !args[2 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 2, "a string  (""windName"")");
            return;
        }
        v8::String::Utf8Value _windName_String( isolate, (args.Length()<2) ? v8::String::NewFromUtf8(isolate, "").ToLocalChecked() : args[2 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked() );
        const char* windName = (args.Length()<2) ? "" : *_windName_String;;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""bpp"")");
            return;
        }
        long bpp = (args.Length()<3) ? 0 : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        Port* port = self->createWindowPort(rect, windName, bpp);
        if (!port) { args.GetReturnValue().SetNull(); return; };
        if (port->mPortScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( PortWrap::NewFromCpp(isolate, port) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, port->mPortScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void GraphicsManagerWrap::CreateFullScreenPort(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Port]" " function" "([object Rect] rect, [number int] screenNum = PRIMARY_SCREEN, boolean allowResChange = true, [number int] bpp = 0)" " - " "create full screen drawing port with given dimensions on given screen, optionally changing depth").ToLocalChecked() ); return; };
        };

        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!v8_ValueIsRect(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
            return;
        }
        pdg::Rect rect = v8_ValueToRect(isolate, args[1 -1]);
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""screenNum"")");
            return;
        }
        long screenNum = (args.Length()<2) ? screenNum_PrimaryScreen : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 3, "a boolean (""allowResChange"")");
            return;
        }
        bool allowResChange = (args.Length()<3) ? true : args[3 -1]->BooleanValue(isolate);;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""bpp"")");
            return;
        }
        long bpp = (args.Length()<4) ? 0 : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        Port* port = self->createFullScreenPort(rect, screenNum, allowResChange, bpp);
        if (!port) { args.GetReturnValue().SetNull(); return; };
        if (port->mPortScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( PortWrap::NewFromCpp(isolate, port) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, port->mPortScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void GraphicsManagerWrap::CloseGraphicsPort(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Port] port = MAIN_PORT)" " - " "close given port, along with its window and restore screen mode if changed").ToLocalChecked() ); return; };
        };

        Port* port = 0;
        if (args.Length() >= 1)
        {
            if (!args[1 -1]->IsObject())
            {
                v8_ThrowArgTypeException(isolate, 1, "an object of type ""Port"" (""port"")");
                return;
            }
            else
            {
                v8::Local<v8::Object> port_ = args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                PortWrap* port__ = jswrap::ObjectWrap::Unwrap<PortWrap>(port_);
                port = port__->getCppObject();
            }
        };
        self->closeGraphicsPort(port);
        args.GetReturnValue().SetUndefined();
    }

    void GraphicsManagerWrap::CloseAllGraphicsPorts(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "close all active graphics ports (e.g. for test cleanup)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->closeAllGraphicsPorts();
        args.GetReturnValue().SetUndefined();
    }

    void GraphicsManagerWrap::CreateFont(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Font]" " function" "(string fontName, number scalingFactor = 1.0)" " - " "get a font with optional scaling adjust").ToLocalChecked() ); return; };
        };

        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""fontName"")");
            return;
        }
        v8::String::Utf8Value fontName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* fontName = *fontName_Str;;
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""scalingFactor"")");
            return;
        }
        double scalingFactor = (args.Length()<2) ? 1.0f : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        Font* font = self->createFont(fontName, scalingFactor);
        if (!font) { args.GetReturnValue().SetNull(); return; };
        if (font->mFontScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( FontWrap::NewFromCpp(isolate, font) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, font->mFontScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void GraphicsManagerWrap::GetMainPort(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Port]" " function" "()" " - " "return the primary graphics port").ToLocalChecked() ); return; };
        };

        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Port* port = self->getMainPort();
        if (!port) { args.GetReturnValue().SetNull(); return; };
        if (port->mPortScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( PortWrap::NewFromCpp(isolate, port) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, port->mPortScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void GraphicsManagerWrap::SwitchToFullScreenMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "(boolean allowResChange = false, [object Port] port = MAIN_PORT)" " - " "change a port to fullscreen mode, return true on success").ToLocalChecked() ); return; };
        };

        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""allowResChange"")");
            return;
        }
        bool allowResChange = (args.Length()<1) ? 0 : args[1 -1]->BooleanValue(isolate);;
        Port* port = 0;
        if (args.Length() >= 2)
        {
            if (!args[2 -1]->IsObject())
            {
                v8_ThrowArgTypeException(isolate, 2, "an object of type ""Port"" (""port"")");
                return;
            }
            else
            {
                v8::Local<v8::Object> port_ = args[2 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                PortWrap* port__ = jswrap::ObjectWrap::Unwrap<PortWrap>(port_);
                port = port__->getCppObject();
            }
        };
        bool result = self->switchToFullScreenMode(allowResChange, port);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, result) ); return; };
    }

    void GraphicsManagerWrap::SwitchToWindowMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "([object Port] port = MAIN_PORT, string windName = \"\")" " - " "change a port to window mode, return true on success").ToLocalChecked() ); return; };
        };

        Port* port = 0;
        if (args.Length() >= 1)
        {
            if (!args[1 -1]->IsObject())
            {
                v8_ThrowArgTypeException(isolate, 1, "an object of type ""Port"" (""port"")");
                return;
            }
            else
            {
                v8::Local<v8::Object> port_ = args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                PortWrap* port__ = jswrap::ObjectWrap::Unwrap<PortWrap>(port_);
                port = port__->getCppObject();
            }
        };
        if (args.Length() >= 2 && !args[2 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 2, "a string  (""windName"")");
            return;
        }
        v8::String::Utf8Value _windName_String( isolate, (args.Length()<2) ? v8::String::NewFromUtf8(isolate, "").ToLocalChecked() : args[2 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked() );
        const char* windName = (args.Length()<2) ? "" : *_windName_String;;
        bool result = self->switchToWindowMode(port, windName);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, result) ); return; };
    }

    void GraphicsManagerWrap::InFullScreenMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "return whether primary graphics port is fullscreen or not").ToLocalChecked() ); return; };
        };

        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool fullscreen = self->inFullScreenMode();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, fullscreen) ); return; };
    }

    void GraphicsManagerWrap::GetScreenBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);
        ;
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object Rect" " function" "([number int] screenNum = PRIMARY_SCREEN)" " - " "returns the bounds (position and size) of a screen in the global coordinate space").ToLocalChecked() ); return; };
        };

        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""screenNum"")");
            return;
        }
        long screenNum = (args.Length()<1) ? screenNum_PrimaryScreen : args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        pdg::Rect bounds = self->getScreenBounds(screenNum);
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, bounds) ); return; };
    }

    GraphicsManagerWrap::GraphicsManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_GraphicsManager(args);
        if (!cppPtr_ && !s_GraphicsManager_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "GraphicsManager" " instance")));
            };
        }
    }

    GraphicsManagerWrap::~GraphicsManagerWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    GraphicsManager* New_GraphicsManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_GraphicsManager_InNewFromCpp)
        {
            return GraphicsManager::getSingletonInstance();
        }
        else
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Cannot construct " "GraphicsManager" " directly - use get" "GraphicsManager" "() instead")));
            };
            return nullptr;
        }
    }
#endif

}
