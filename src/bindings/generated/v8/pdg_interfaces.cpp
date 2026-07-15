// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/javascript/v8/pdg_js_classes.cpp
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

#include "pdg_script_interface.h"

#include "internals.h"
#include "pdg-lib.h"

#include "node.h"

#include <sstream>
#include <cmath>
#include <cstdlib>

#include "libplatform/libplatform.h"

#ifndef PDG_DEBUG_SCRIPTING

#define SCRIPT_DEBUG_ONLY(_expression)
#else
#define SCRIPT_DEBUG_ONLY DEBUG_ONLY
#endif

#ifndef PDG_DEBUG_SPRITE_EVENTS

#define SPRITE_EVENTS_DEBUG_ONLY(_expression)
#else
#define SPRITE_EVENTS_DEBUG_ONLY DEBUG_ONLY
#endif

namespace pdg
{

    extern bool s_IEventHandler_InNewFromCpp;
    extern bool s_ISerializable_InNewFromCpp;
    extern bool s_IAnimationHelper_InNewFromCpp;
    extern bool s_ISpriteCollideHelper_InNewFromCpp;
    extern bool s_ISpriteDrawHelper_InNewFromCpp;

    v8::Persistent<v8::Value> s_SavedError;

    static v8::Persistent<v8::Object> s_BindingTarget;

    void GetConfigManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ConfigManager]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        { args.GetReturnValue().Set( ConfigManagerWrap::GetScriptSingletonInstance(isolate) ); return; };
    }

    void GetLogManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object LogManager]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        { args.GetReturnValue().Set( LogManagerWrap::GetScriptSingletonInstance(isolate) ); return; };
    }

    IEventHandlerWrap::IEventHandlerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_IEventHandler(args);
        if (!cppPtr_ && !s_IEventHandler_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "IEventHandler" " instance")));
            };
        }
    }

    IEventHandlerWrap::~IEventHandlerWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    IEventHandler* New_IEventHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_IEventHandler_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        if ((args.Length() == 1 && args[0]->IsNull()))
        {
            ScriptEventHandler* handler = new ScriptEventHandler();
            handler->addRef();
            return handler;
        }
        else if (args.Length() != 1 || !args[0]->IsFunction())
        {
            s_HaveSavedError = true;
            {
                std::ostringstream excpt_;
                excpt_ << "EventHandler must be created with a function argument (handlerFunc)";
                v8::Isolate* isolate = v8::Isolate::GetCurrent();
                s_SavedError.Reset(isolate, v8::Exception::SyntaxError( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
            };
        }
        v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(args[0]);
        ScriptEventHandler* handler = new ScriptEventHandler(callback);
        handler->addRef();
        return handler;
    }

    void EventManagerWrap::IsKeyDown(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "({string unicodeChar|[number uint] utf16CharCode})" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (args[0]->IsString())
        {
            v8::Local<v8::String> keyCode_String = args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked();
            uint16 utf16Char = 0;
            keyCode_String->Write(isolate, &utf16Char, 0, 1, v8::String::NO_NULL_TERMINATION);
            { args.GetReturnValue().Set( v8::Boolean::New(isolate, OS::isKeyDown(utf16Char)) ); return; };
        }
        else
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""utf16CharCode"")");
                return;
            }
            unsigned long utf16CharCode = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
            { args.GetReturnValue().Set( v8::Boolean::New(isolate, OS::isKeyDown(utf16CharCode)) ); return; };
        }
    }
    void EventManagerWrap::GetDeviceOrientation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "(boolean absolute = false)" " - " "NOT IMPLEMENTED").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""absolute"")");
            return;
        }
        bool absolute = (args.Length()<1) ? false : args[1 -1]->BooleanValue(isolate);;
        float roll, pitch, yaw;
        OS::getDeviceOrientation(roll, pitch, yaw, absolute);
        v8::Local<v8::Object> jsOrientation = v8::Object::New(isolate);
        (void)jsOrientation->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "roll").ToLocalChecked(), v8::Number::New(isolate, roll));
        (void)jsOrientation->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "pitch").ToLocalChecked(), v8::Number::New(isolate, pitch));
        (void)jsOrientation->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "yaw").ToLocalChecked(), v8::Number::New(isolate, yaw));
        { args.GetReturnValue().Set( jsOrientation ); return; };
    }
    void GetEventManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object EventManager]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        v8::Local<v8::Object> jsInstance = EventManagerWrap::GetScriptSingletonInstance(isolate);
        EventManager* evtMgr = EventManager::getSingletonInstance();
        evtMgr->mEventEmitterScriptObj.Reset(isolate, jsInstance);
        { args.GetReturnValue().Set( jsInstance ); return; };
    }

    void ResourceManagerWrap::GetImage(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ResourceManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ResourceManagerWrap>(args.This());
        ResourceManager* self = dynamic_cast<ResourceManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Image]" " function" "(string imageName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""imageName"")");
            return;
        }
        v8::String::Utf8Value imageName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* imageName = *imageName_Str;;
        Image* img = self->getImage(imageName);
        if (img == NULL)
        {
            { args.GetReturnValue().SetNull(); return; };
        }
        v8::Local<v8::Object> obj = ImageWrap::NewFromCpp(isolate, img);

        (void)obj->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "name").ToLocalChecked(), v8::String::NewFromUtf8(isolate, imageName).ToLocalChecked());
        { args.GetReturnValue().Set( obj ); return; };
    }

    void ResourceManagerWrap::GetImageStrip(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ResourceManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ResourceManagerWrap>(args.This());
        ResourceManager* self = dynamic_cast<ResourceManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ImageStrip]" " function" "(string imageName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""imageName"")");
            return;
        }
        v8::String::Utf8Value imageName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* imageName = *imageName_Str;;
        ImageStrip* img = self->getImageStrip(imageName);
        if (img == NULL)
        {
            { args.GetReturnValue().SetNull(); return; };
        }
        v8::Local<v8::Object> obj = ImageStripWrap::NewFromCpp(isolate, img);

        (void)obj->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "name").ToLocalChecked(), v8::String::NewFromUtf8(isolate, imageName).ToLocalChecked());
        { args.GetReturnValue().Set( obj ); return; };
    }
#ifndef PDG_NO_SOUND

    void ResourceManagerWrap::GetSound(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ResourceManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ResourceManagerWrap>(args.This());
        ResourceManager* self = dynamic_cast<ResourceManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sound]" " function" "(string soundName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""soundName"")");
            return;
        }
        v8::String::Utf8Value soundName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* soundName = *soundName_Str;;
        Sound* snd = self->getSound(soundName);
        if (snd == NULL)
        {
            { args.GetReturnValue().SetNull(); return; };
        }
        v8::Local<v8::Object> obj = SoundWrap::NewFromCpp(isolate, snd);

        (void)obj->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "name").ToLocalChecked(), v8::String::NewFromUtf8(isolate, soundName).ToLocalChecked() );
        { args.GetReturnValue().Set( obj ); return; };
    }
#endif

    void GetResourceManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ResourceManager]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        { args.GetReturnValue().Set( ResourceManagerWrap::GetScriptSingletonInstance(isolate) ); return; };
    }

    ISerializableWrap::ISerializableWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_ISerializable(args);
        if (!cppPtr_ && !s_ISerializable_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "ISerializable" " instance")));
            };
        }
    }

    ISerializableWrap::~ISerializableWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    ISerializable* New_ISerializable(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_ISerializable_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        if ((args.Length() == 1 && args[0]->IsNull()))
        {
            ScriptSerializable* serializable = new ScriptSerializable();
            serializable->addRef();
            return serializable;
        }
        else
        {
            if (args.Length() != 4 || !args[0]->IsFunction() || !args[1]->IsFunction()
                || !args[2]->IsFunction() || !args[3]->IsFunction())
            {
                s_HaveSavedError = true;
                {
                    std::ostringstream excpt_;
                    excpt_ << "Serializable must be created with 4 function arguments " "(getSerializedSizeFunc, serializeFunc, deserializeFunc, getMyClassTagFunc)";
                    v8::Isolate* isolate = v8::Isolate::GetCurrent();
                    s_SavedError.Reset(isolate, v8::Exception::SyntaxError( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
                };

            }
            v8::Local<v8::Function> getSerializedSizeFunc = v8::Local<v8::Function>::Cast(args[0]);
            v8::Local<v8::Function> serializeFunc = v8::Local<v8::Function>::Cast(args[1]);
            v8::Local<v8::Function> deserializeFunc = v8::Local<v8::Function>::Cast(args[2]);
            v8::Local<v8::Function> getMyClassTagFunc = v8::Local<v8::Function>::Cast(args[3]);
            ScriptSerializable* serializable =
                new ScriptSerializable(getSerializedSizeFunc, serializeFunc,
                deserializeFunc, getMyClassTagFunc);
            serializable->addRef();
            return serializable;
        }
    }

    void SerializerWrap::Serialize_obj(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        self->mSerializerScriptObj.Reset(isolate, args.This());
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        ISerializable* obj = 0;
        if (args[1 -1]->IsObject())
        {
            v8::Local<v8::Object> obj_ = args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
            ISerializableWrap* obj__ = static_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
            if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                if (protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                    obj__ = static_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
            }
            if (obj__)
            {
                obj = obj__->getCppObject();
                obj->mISerializableScriptObj.Reset(isolate, args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked());
            }
        }
        if (!obj && !args[1 -1]->IsNull())
        {
            std::ostringstream excpt_;
            excpt_ << "argument ""1"" must be null or an object derived from ""ISerializable"" (""obj"")";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        };
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 257 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 257 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                ISerializableWrap* obj__ = dynamic_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 257 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""ISerializable""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 257 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""ISerializable""\n";
                }
            }
            else
            {
                ISerializable* obj = dynamic_cast<ISerializable*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 257 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""ISerializable"" ("<<(void*)obj<<")\n";
            }
        } );
        self->serialize_obj(obj);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::SerializedSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "({string|boolean|[number uint]|[object Color]|[object Offset]|[object Point]|[object Vector]|[object Rect]|[object RotatedRect]|[object Quad]|[object MemBlock]|[object ISerializable]} arg)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        uint32 dataSize = 0;
        if (args[0]->IsString())
        {
            v8::String::Utf8Value str_Str(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* str = *str_Str;;
            dataSize = self->sizeof_str(str);
        }
        else if (args[0]->IsBoolean())
        {
            bool val = args[0]->BooleanValue(isolate);
            dataSize = self->sizeof_bool(val);
        }
        else if (args[0]->IsNumber())
        {
            uint32 val = args[0]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
            dataSize = self->sizeof_uint(val);
        }
        else if (v8_ValueIsColor(isolate, args[0]))
        {
            Color c = v8_ValueToColor(isolate, args[0]);
            dataSize = self->sizeof_color(c);
        }
        else if (v8_ValueIsOffset(isolate, args[0]))
        {
            Offset o = v8_ValueToOffset(isolate, args[0]);
            dataSize = self->sizeof_offset(o);
        }
        else if (v8_ValueIsRect(isolate, args[0]))
        {
            Rect r = v8_ValueToRect(isolate, args[0]);
            dataSize = self->sizeof_rect(r);
        }
        else if (v8_ValueIsRotatedRect(isolate, args[0]))
        {
            RotatedRect rr = v8_ValueToRotatedRect(isolate, args[0]);
            dataSize = self->sizeof_rotr(rr);
        }
        else if (v8_ValueIsQuad(isolate, args[0]))
        {
            Quad q = v8_ValueToQuad(isolate, args[0]);
            dataSize = self->sizeof_quad(q);
        }
        else if (args[0]->IsObject())
        {
            v8::Local<v8::Object> obj = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
            MemBlockWrap* memBlock__ = ObjectWrap::Unwrap<MemBlockWrap>(obj);
            if (memBlock__)
            {
                MemBlock* memBlock = memBlock__->getCppObject();
                dataSize = self->sizeof_mem(memBlock->ptr, memBlock->bytes);
            }
            else
            {

                ISerializable* serializable = 0;
                if (args[1 -1]->IsObject())
                {
                    v8::Local<v8::Object> serializable_ = args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                    ISerializableWrap* serializable__ = static_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap(serializable_));
                    if (!serializable__)
                    {
                        v8::Local<v8::Value> protoVal_ = serializable_->GetPrototypeV2();
                        if (protoVal_->IsObject())
                        {
                            serializable_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                            serializable__ = static_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap(serializable_));
                        }
                    }
                    if (serializable__)
                    {
                        serializable = serializable__->getCppObject();
                        serializable->mISerializableScriptObj.Reset(isolate, args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked());
                    }
                };
                if (serializable)
                {
                    SCRIPT_DEBUG_ONLY( if (self->mSerializerScriptObj.IsEmpty())
                    {
                        std::cerr << __func__<<":"<< 299 << " - NIL JS Object (" "self->mSerializerScriptObj" "|"<<*((void**)&(self->mSerializerScriptObj))<<")\n";
                    }
                    else if (!self->mSerializerScriptObj->IsObject())
                    {
                        std::cerr << __func__<<":"<< 299 << " - NOT JS Object (" "self->mSerializerScriptObj" "|"<<*((void**)&(self->mSerializerScriptObj))<<") : " << (self->mSerializerScriptObj.IsEmpty() ? "empty" : self->mSerializerScriptObj->IsArray() ? "array" : self->mSerializerScriptObj->IsFunction() ? "function" : self->mSerializerScriptObj->IsStringObject() ? "string (object)" : self->mSerializerScriptObj->IsString() ? "string" : self->mSerializerScriptObj->IsNull() ? "null" : self->mSerializerScriptObj->IsUndefined() ? "undefined" : self->mSerializerScriptObj->IsNumberObject() ? "number (object)" : self->mSerializerScriptObj->IsNumber() ? "number" : self->mSerializerScriptObj->IsBoolean() ? "boolean" : self->mSerializerScriptObj->IsDate() ? "date" : self->mSerializerScriptObj->IsRegExp() ? "regexp" : self->mSerializerScriptObj->IsNativeError() ? "error" : self->mSerializerScriptObj->IsObject() ? "object" : "unknown") << "\n";
                    }
                    else
                    {
                        v8::Local<v8::Object> obj_ = self->mSerializerScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                            v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                            char* objName = *objNameStr;
                            SerializerWrap* obj__ = dynamic_cast<SerializerWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                            if (!obj__)
                        {
                            v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                                if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                            {
                                obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                                    obj__ = dynamic_cast<SerializerWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                            }
                            if (obj__)
                            {
                                std::cout << __func__<<":"<< 299 << " - JS Object (""self->mSerializerScriptObj""|"<<*((void**)&(self->mSerializerScriptObj))<<"): " << objName << " - is a subclass of C++ ""Serializer""\n";
                            }
                            else
                            {
                                std::cout << __func__<<":"<< 299 << " - JS Object (""self->mSerializerScriptObj""|"<<*((void**)&(self->mSerializerScriptObj))<<"): " << objName << " - does not wrap ""Serializer""\n";
                            }
                        }
                        else
                        {
                            Serializer* obj = dynamic_cast<Serializer*>(obj__->getCppObject());
                                std::cout << __func__<<":"<< 299 << " - JS Object (""self->mSerializerScriptObj""|" << *((void**)&(self->mSerializerScriptObj)) << "): " << objName<<" - wraps C++ ""Serializer"" ("<<(void*)obj<<")\n";
                        }
                    } )
                        SCRIPT_DEBUG_ONLY( if (serializable->mISerializableScriptObj.IsEmpty())
                    {
                        std::cerr << __func__<<":"<< 300 << " - NIL JS Object (" "serializable->mISerializableScriptObj" "|"<<*((void**)&(serializable->mISerializableScriptObj))<<")\n";
                    }
                    else if (!serializable->mISerializableScriptObj->IsObject())
                    {
                        std::cerr << __func__<<":"<< 300 << " - NOT JS Object (" "serializable->mISerializableScriptObj" "|"<<*((void**)&(serializable->mISerializableScriptObj))<<") : " << (serializable->mISerializableScriptObj.IsEmpty() ? "empty" : serializable->mISerializableScriptObj->IsArray() ? "array" : serializable->mISerializableScriptObj->IsFunction() ? "function" : serializable->mISerializableScriptObj->IsStringObject() ? "string (object)" : serializable->mISerializableScriptObj->IsString() ? "string" : serializable->mISerializableScriptObj->IsNull() ? "null" : serializable->mISerializableScriptObj->IsUndefined() ? "undefined" : serializable->mISerializableScriptObj->IsNumberObject() ? "number (object)" : serializable->mISerializableScriptObj->IsNumber() ? "number" : serializable->mISerializableScriptObj->IsBoolean() ? "boolean" : serializable->mISerializableScriptObj->IsDate() ? "date" : serializable->mISerializableScriptObj->IsRegExp() ? "regexp" : serializable->mISerializableScriptObj->IsNativeError() ? "error" : serializable->mISerializableScriptObj->IsObject() ? "object" : "unknown") << "\n";
                    }
                    else
                    {
                        v8::Local<v8::Object> obj_ = serializable->mISerializableScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                            v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                            char* objName = *objNameStr;
                            ISerializableWrap* obj__ = dynamic_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                            if (!obj__)
                        {
                            v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                                if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                            {
                                obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                                    obj__ = dynamic_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                            }
                            if (obj__)
                            {
                                std::cout << __func__<<":"<< 300 << " - JS Object (""serializable->mISerializableScriptObj""|"<<*((void**)&(serializable->mISerializableScriptObj))<<"): " << objName << " - is a subclass of C++ ""ISerializable""\n";
                            }
                            else
                            {
                                std::cout << __func__<<":"<< 300 << " - JS Object (""serializable->mISerializableScriptObj""|"<<*((void**)&(serializable->mISerializableScriptObj))<<"): " << objName << " - does not wrap ""ISerializable""\n";
                            }
                        }
                        else
                        {
                            ISerializable* obj = dynamic_cast<ISerializable*>(obj__->getCppObject());
                                std::cout << __func__<<":"<< 300 << " - JS Object (""serializable->mISerializableScriptObj""|" << *((void**)&(serializable->mISerializableScriptObj)) << "): " << objName<<" - wraps C++ ""ISerializable"" ("<<(void*)obj<<")\n";
                        }
                    } )
                        dataSize = self->sizeof_obj(serializable);
                }
                else
                {
                    std::ostringstream excpt_;
                    excpt_ << "argument 1 must be either an unsigned integer, " "a string, a MemBlock object, an ISerializable object";
                    isolate->ThrowException( v8::Exception::TypeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }())));

                }
            }
        }
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, dataSize) ); return; };
    }

    void RegisterSerializableObject(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(object obj, [number uint] uniqueId)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsObject())
        {
            std::ostringstream excpt_;
            excpt_ << "argument ""1"" must be an object (""obj"")";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        v8::Local<v8::Object> obj = args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();;
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""uniqueId"")");
            return;
        }
        unsigned long uniqueId = args[2 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();

        args.GetReturnValue().SetUndefined();
    }

#ifndef PDG_NO_GUI

    void GraphicsManagerWrap::GetCurrentScreenMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);
        ;
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "([number int] screenNum = PRIMARY_SCREEN)" " - " "returns object with width, height, depth and maxWindowRect for specified screen").ToLocalChecked() ); return; };
        };

        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""screenNum"")");
            return;
        }
        long screenNum = (args.Length()<1) ? screenNum_PrimaryScreen : args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        pdg::Rect maxWindowRect;
        pdg::GraphicsManager::ScreenMode mode;
        mode = self->getCurrentScreenMode(screenNum, &maxWindowRect);

        v8::Local<v8::Object> jsScreenMode = v8::Object::New(isolate);
        (void)jsScreenMode->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "width").ToLocalChecked(),v8::Integer::New(isolate, mode.width));
        (void)jsScreenMode->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "height").ToLocalChecked(),v8::Integer::New(isolate, mode.height));
        (void)jsScreenMode->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "depth").ToLocalChecked(),v8::Integer::New(isolate, mode.bpp));
        (void)jsScreenMode->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "maxWindowRect").ToLocalChecked(), v8_MakeJavascriptRect(isolate, maxWindowRect));
        { args.GetReturnValue().Set( jsScreenMode ); return; };
    }

    void GraphicsManagerWrap::GetNthSupportedScreenMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        GraphicsManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<GraphicsManagerWrap>(args.This());
        GraphicsManager* self = dynamic_cast<GraphicsManager*>(objWrapper->cppPtr_);
        ;
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "([number int] n, [number int] screenNum = PRIMARY_SCREEN)" " - " "returns object with width, height, depth and maxWindowRect for specified screen").ToLocalChecked() ); return; };
        };

        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""n"")");
            return;
        }
        long n = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""screenNum"")");
            return;
        }
        long screenNum = (args.Length()<2) ? screenNum_PrimaryScreen : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        pdg::GraphicsManager::ScreenMode mode;
        mode = self->getNthSupportedScreenMode(n, screenNum);

        v8::Local<v8::Object> jsScreenMode = v8::Object::New(isolate);
        (void)jsScreenMode->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "width").ToLocalChecked(),v8::Integer::New(isolate, mode.width));
        (void)jsScreenMode->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "height").ToLocalChecked(),v8::Integer::New(isolate, mode.height));
        (void)jsScreenMode->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "depth").ToLocalChecked(),v8::Integer::New(isolate, mode.bpp));
        { args.GetReturnValue().Set( jsScreenMode ); return; };
    }

    void GetGraphicsManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object GraphicsManager]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        { args.GetReturnValue().Set( GraphicsManagerWrap::GetScriptSingletonInstance(isolate) ); return; };
    }
#endif

#ifndef PDG_NO_SOUND

    void GetSoundManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object SoundManager]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        { args.GetReturnValue().Set( SoundManagerWrap::GetScriptSingletonInstance(isolate) ); return; };
    }
#endif

    void GetFileManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object FileManager]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        { args.GetReturnValue().Set( FileManagerWrap::GetScriptSingletonInstance(isolate) ); return; };
    }

    void GetTimerManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TimerManager]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        v8::Local<v8::Object> jsInstance = TimerManagerWrap::GetScriptSingletonInstance(isolate);
        TimerManager* timMgr = TimerManager::getSingletonInstance();
        timMgr->mEventEmitterScriptObj.Reset(isolate, jsInstance);
        { args.GetReturnValue().Set( jsInstance ); return; };
    }

    IAnimationHelperWrap::IAnimationHelperWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_IAnimationHelper(args);
        if (!cppPtr_ && !s_IAnimationHelper_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "IAnimationHelper" " instance")));
            };
        }
    }

    IAnimationHelperWrap::~IAnimationHelperWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    IAnimationHelper* New_IAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_IAnimationHelper_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        if ((args.Length() == 1 && args[0]->IsNull()))
        {
            ScriptAnimationHelper* helper = new ScriptAnimationHelper();
            return helper;
        }
        else if (args.Length() != 1 || !args[0]->IsFunction())
        {
            s_HaveSavedError = true;
            {
                std::ostringstream excpt_;
                excpt_ << "AnimationHelper must be created with a function argument (handlerFunc)";
                v8::Isolate* isolate = v8::Isolate::GetCurrent();
                s_SavedError.Reset(isolate, v8::Exception::SyntaxError( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
            };
            return 0;
        }
        v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(args[0]);
        ScriptAnimationHelper* helper = new ScriptAnimationHelper(callback);
        return helper;
    }

    static v8::Persistent<v8::Function> s_CustomScriptEasing[MAX_CUSTOM_EASINGS];

    ISpriteCollideHelperWrap::ISpriteCollideHelperWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_ISpriteCollideHelper(args);
        if (!cppPtr_ && !s_ISpriteCollideHelper_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "ISpriteCollideHelper" " instance")));
            };
        }
    }

    ISpriteCollideHelperWrap::~ISpriteCollideHelperWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    ISpriteCollideHelper* New_ISpriteCollideHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_ISpriteCollideHelper_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        if ((args.Length() == 1 && args[0]->IsNull()))
        {
            ScriptSpriteCollideHelper* helper = new ScriptSpriteCollideHelper();
            return helper;
        }
        else if (args.Length() != 1 || !args[0]->IsFunction())
        {
            s_HaveSavedError = true;
            {
                std::ostringstream excpt_;
                excpt_ << "SpriteCollideHelper must be created with a function argument (allowCollisionFunc)";
                v8::Isolate* isolate = v8::Isolate::GetCurrent();
                s_SavedError.Reset(isolate, v8::Exception::SyntaxError( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
            };
            return 0;
        }
        v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(args[0]);
        ScriptSpriteCollideHelper* helper = new ScriptSpriteCollideHelper(callback);
        return helper;
    }

#ifndef PDG_NO_GUI

    ISpriteDrawHelperWrap::ISpriteDrawHelperWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_ISpriteDrawHelper(args);
        if (!cppPtr_ && !s_ISpriteDrawHelper_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "ISpriteDrawHelper" " instance")));
            };
        }
    }

    ISpriteDrawHelperWrap::~ISpriteDrawHelperWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    ISpriteDrawHelper* New_ISpriteDrawHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_ISpriteDrawHelper_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        if ((args.Length() == 1 && args[0]->IsNull()))
        {
            ScriptSpriteDrawHelper* helper = new ScriptSpriteDrawHelper();
            return helper;
        }
        else if (args.Length() != 1 || !args[0]->IsFunction())
        {
            s_HaveSavedError = true;
            {
                std::ostringstream excpt_;
                excpt_ << "SpriteDrawHelper must be created with a function argument (drawFunc)";
                v8::Isolate* isolate = v8::Isolate::GetCurrent();
                s_SavedError.Reset(isolate, v8::Exception::SyntaxError( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
            };
            return 0;
        }
        v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(args[0]);
        ScriptSpriteDrawHelper* helper = new ScriptSpriteDrawHelper(callback);
        return helper;
    }
#endif

    ScriptSerializable::ScriptSerializable(
        v8::Local<v8::Function> javascriptGetSerializedSizeFunc,
        v8::Local<v8::Function> javascriptSerializeFunc,
        v8::Local<v8::Function> javascriptDeserializeFunc,
        v8::Local<v8::Function> javascriptGetMyClassTagFunc)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        mScriptGetSerializedSizeFunc.Reset(isolate, javascriptGetSerializedSizeFunc);
        mScriptSerializeFunc.Reset(isolate, javascriptSerializeFunc);
        mScriptDeserializeFunc.Reset(isolate, javascriptDeserializeFunc);
        mScriptGetMyClassTagFunc.Reset(isolate, javascriptGetMyClassTagFunc);

    }

    uint32
        ScriptSerializable::getSerializedSize(ISerializer* serializer) const
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();

        v8::Local<v8::Value> argv[1];
        Serializer* ser = dynamic_cast<Serializer*>(serializer);
        if (!ser)
        {
            DEBUG_ONLY(
                std::cerr << "Internal Error: getSerializedSize Function called with invalid Serializer\n";
                exit(1);
                )
        }

        argv[0] = v8::Local<v8::Object>::New(isolate, ser->mSerializerScriptObj);
        v8::Local<v8::Value> resVal;
        v8::Local<v8::Function> func;
        v8::Local<v8::Object> obj_ = v8::Local<v8::Object>::New(isolate, mISerializableScriptObj);
        if (!mScriptGetSerializedSizeFunc.IsEmpty())
        {
            func = v8::Local<v8::Function>::New(isolate, mScriptGetSerializedSizeFunc);
        }
        else if ((!obj_->IsNull() && obj_->Has(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getSerializedSize").ToLocalChecked()).ToChecked()))
        {
            func = v8::Local<v8::Function>::Cast(([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = obj_->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getSerializedSize").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }()));
        }
        else
        {
            DEBUG_ONLY(
                v8::String::Utf8Value objectNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                std::cerr << "fatal: ISerializable object " << *objectNameStr << " missing getSerializedSize() Function!!";
                exit(1);
                )
                return 0;
        }
        resVal = ([&]() -> v8::Local<v8::Value>
        {
            if (func.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::MaybeLocal<v8::Value> maybe = func->Call(isolate->GetCurrentContext(), obj_, 1, argv);
                if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());

        if (resVal.IsEmpty())
        {
            return 0;
        }
        if (!resVal->IsUint32())
        {
            DEBUG_ONLY(
                std::cerr << "result mismatch: return value from getSerializedSize Function must be an unsigned integer ("
                << v8_GetFunctionName(func) << " at " << v8_GetFunctionFileAndLine(func) << ")\n";
                exit(1);
                )
                return 0;
        }
        return resVal->Uint32Value(isolate->GetCurrentContext()).ToChecked();
    }

    void
        ScriptSerializable::serialize(ISerializer* serializer) const
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();

        v8::Local<v8::Value> argv[1];
        Serializer* ser = dynamic_cast<Serializer*>(serializer);
        if (!ser)
        {
            DEBUG_ONLY(
                std::cerr << "Internal Error: getSerializedSize Function called with invalid Serializer\n";
                exit(1);
                )
        }

        argv[0] = v8::Local<v8::Object>::New(isolate, ser->mSerializerScriptObj);
        v8::Local<v8::Value> resVal;
        v8::Local<v8::Function> func;
        v8::Local<v8::Object> obj_ = v8::Local<v8::Object>::New(isolate, mISerializableScriptObj);
        if (!mScriptSerializeFunc.IsEmpty())
        {
            func = v8::Local<v8::Function>::New(isolate, mScriptSerializeFunc);
        }
        else if ((!obj_->IsNull() && obj_->Has(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "serialize").ToLocalChecked()).ToChecked()))
        {
            func = v8::Local<v8::Function>::Cast(([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = obj_->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "serialize").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }()));
        }
        else
        {
            DEBUG_ONLY(
                v8::String::Utf8Value objectNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                std::cerr << "fatal: ISerializable object " << *objectNameStr << " missing serialize() Function!!";
                exit(1);
                )
                return;
        }
        resVal = ([&]() -> v8::Local<v8::Value>
        {
            if (func.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::MaybeLocal<v8::Value> maybe = func->Call(isolate->GetCurrentContext(), obj_, 1, argv);
                if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());

        if (resVal.IsEmpty())
        {
            return;
        }
    }

    void
        ScriptSerializable::deserialize(IDeserializer* deserializer)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();

        v8::Local<v8::Value> argv[1];
        Deserializer* deser = dynamic_cast<Deserializer*>(deserializer);
        if (!deser)
        {
            DEBUG_ONLY(
                std::cerr << "Internal Error: deserialize Function called with invalid Deserializer\n";
                exit(1);
                )
        }
        argv[0] = v8::Local<v8::Object>::New(isolate, deser->mDeserializerScriptObj);
        v8::Local<v8::Value> resVal;
        v8::Local<v8::Function> func;
        v8::Local<v8::Object> obj_ = v8::Local<v8::Object>::New(isolate, mISerializableScriptObj);
        if (!mScriptDeserializeFunc.IsEmpty())
        {
            func = v8::Local<v8::Function>::New(isolate, mScriptDeserializeFunc);
        }
        else if ((!obj_->IsNull() && obj_->Has(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "deserialize").ToLocalChecked()).ToChecked()))
        {
            func = v8::Local<v8::Function>::Cast(([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = obj_->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "deserialize").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }()));
        }
        else
        {
            DEBUG_ONLY(
                v8::String::Utf8Value objectNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                std::cerr << "fatal: ISerializable object " << *objectNameStr << " missing deserialize() Function!!";
                exit(1);
                )
                return;
        }
        resVal = ([&]() -> v8::Local<v8::Value>
        {
            if (func.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::MaybeLocal<v8::Value> maybe = func->Call(isolate->GetCurrentContext(), obj_, 1, argv);
                if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());

        if (resVal.IsEmpty())
        {
            return;
        }
    }

    uint32
        ScriptSerializable::getMyClassTag() const
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();

        v8::Local<v8::Value> resVal;
        v8::Local<v8::Function> func;
        v8::Local<v8::Object> obj_ = v8::Local<v8::Object>::New(isolate, mISerializableScriptObj);
        if (!mScriptGetMyClassTagFunc.IsEmpty())
        {
            func = v8::Local<v8::Function>::New(isolate, mScriptGetMyClassTagFunc);
        }
        else if ((!obj_->IsNull() && obj_->Has(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getMyClassTag").ToLocalChecked()).ToChecked()))
        {
            func = v8::Local<v8::Function>::Cast(([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = obj_->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getMyClassTag").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }()));
        }
        else
        {
            DEBUG_ONLY(
                v8::String::Utf8Value objectNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                std::cerr << "fatal: ISerializable object " << *objectNameStr << " missing getMyClassTag() Function!!";
                exit(1);
                )
                return 0;
        }
        resVal = ([&]() -> v8::Local<v8::Value>
        {
            if (func.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::MaybeLocal<v8::Value> maybe = func->Call(isolate->GetCurrentContext(), obj_, 0, 0);
                if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());

        if (resVal.IsEmpty())
        {
            return 0;
        }
        if (!resVal->IsUint32())
        {
            DEBUG_ONLY(
                std::cerr << "result mismatch: return value from getMyClassTag Function must be an unsigned integer ("
                << v8_GetFunctionName(func) << " at " << v8_GetFunctionFileAndLine(func) << ")\n";
                exit(1);
                )
                return 0;
        }
        return resVal->Uint32Value(isolate->GetCurrentContext()).ToChecked();
    }

    ScriptEventHandler::ScriptEventHandler(v8::Local<v8::Function> func)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        mScriptHandlerFunc.Reset(isolate, func);
    }

    bool ScriptEventHandler::handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) throw()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Object> jsEvent = v8::Object::New(isolate);
        v8::Local<v8::Object> emitter_ = v8::Local<v8::Object>::New(isolate, emitter->mEventEmitterScriptObj);
        v8::Local<v8::Object> obj1_;
        v8::Local<v8::Object> obj2_;
        SpriteAnimateInfo* sai = static_cast<SpriteAnimateInfo*>(inEventData);
        SpriteLayerInfo* sli = static_cast<SpriteLayerInfo*>(inEventData);
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "emitter").ToLocalChecked(), emitter_).ToChecked();
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType").ToLocalChecked(), v8::Integer::New(isolate, inEventType)).ToChecked();
        switch (inEventType)
        {
            case pdg::eventType_Startup:
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "startupReason").ToLocalChecked(), v8::Integer::New(isolate, static_cast<StartupInfo*>(inEventData)->startupReason)).ToChecked();

                break;
            case pdg::eventType_Shutdown:
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "exitReason").ToLocalChecked(), v8::Integer::New(isolate, static_cast<ShutdownInfo*>(inEventData)->exitReason)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "exitCode").ToLocalChecked(), v8::Integer::New(isolate, static_cast<ShutdownInfo*>(inEventData)->exitCode)).ToChecked();
                break;
            case pdg::eventType_Timer:
                if (static_cast<TimerInfo*>(inEventData)->id <= 0)
                {

                    return false;
                }
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "id").ToLocalChecked(), v8::Integer::New(isolate, static_cast<TimerInfo*>(inEventData)->id)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "millisec").ToLocalChecked(), v8::Integer::NewFromUnsigned(isolate, static_cast<TimerInfo*>(inEventData)->millisec)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "msElapsed").ToLocalChecked(), v8::Integer::NewFromUnsigned(isolate, static_cast<TimerInfo*>(inEventData)->msElapsed)).ToChecked();

                break;
#ifndef PDG_NO_GUI
            case pdg::eventType_KeyDown:
            case pdg::eventType_KeyUp:
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode").ToLocalChecked(), v8::Integer::New(isolate, static_cast<KeyInfo*>(inEventData)->keyCode)).ToChecked();
                break;
            case pdg::eventType_KeyPress:
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "shift").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<KeyPressInfo*>(inEventData)->shift)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ctrl").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<KeyPressInfo*>(inEventData)->ctrl)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "alt").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<KeyPressInfo*>(inEventData)->alt)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "meta").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<KeyPressInfo*>(inEventData)->meta)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "unicode").ToLocalChecked(), v8::Integer::New(isolate, static_cast<KeyPressInfo*>(inEventData)->unicode)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "isRepeating").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<KeyPressInfo*>(inEventData)->isRepeating)).ToChecked();
                break;
            case pdg::eventType_SpriteTouch:
                obj1_ = v8::Local<v8::Object>::New(isolate, static_cast<SpriteTouchInfo*>(inEventData)->touchedSprite->mSpriteScriptObj);
                obj2_ = v8::Local<v8::Object>::New(isolate, static_cast<SpriteTouchInfo*>(inEventData)->inLayer->mSpriteLayerScriptObj);
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "touchType").ToLocalChecked(), v8::Integer::New(isolate, static_cast<SpriteTouchInfo*>(inEventData)->touchType)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "touchedSprite").ToLocalChecked(), obj1_).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "inLayer").ToLocalChecked(), obj2_).ToChecked();

            case pdg::eventType_MouseDown:
            case pdg::eventType_MouseUp:
            case pdg::eventType_MouseMove:
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "shift").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<MouseInfo*>(inEventData)->shift)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ctrl").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<MouseInfo*>(inEventData)->ctrl)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "alt").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<MouseInfo*>(inEventData)->alt)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "meta").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<MouseInfo*>(inEventData)->meta)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "mousePos").ToLocalChecked(), v8_MakeJavascriptPoint(isolate, static_cast<MouseInfo*>(inEventData)->mousePos)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "leftButton").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<MouseInfo*>(inEventData)->leftButton)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "rightButton").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<MouseInfo*>(inEventData)->rightButton)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "buttonNumber").ToLocalChecked(), v8::Integer::NewFromUnsigned(isolate, static_cast<MouseInfo*>(inEventData)->buttonNumber)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "lastClickPos").ToLocalChecked(), v8_MakeJavascriptPoint(isolate, static_cast<MouseInfo*>(inEventData)->lastClickPos)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "lastClickElapsed").ToLocalChecked(), v8::Integer::NewFromUnsigned(isolate, static_cast<MouseInfo*>(inEventData)->lastClickElapsed)).ToChecked();
                break;
            case pdg::eventType_ScrollWheel:
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "shift").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<ScrollWheelInfo*>(inEventData)->shift)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ctrl").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<ScrollWheelInfo*>(inEventData)->ctrl)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "alt").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<ScrollWheelInfo*>(inEventData)->alt)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "meta").ToLocalChecked(), v8::Boolean::New(isolate, static_cast<ScrollWheelInfo*>(inEventData)->meta)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "horizDelta").ToLocalChecked(), v8::Integer::New(isolate, static_cast<ScrollWheelInfo*>(inEventData)->horizDelta)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "vertDelta").ToLocalChecked(), v8::Integer::New(isolate, static_cast<ScrollWheelInfo*>(inEventData)->vertDelta)).ToChecked();
                break;
#endif
#ifndef PDG_NO_NETWORK

            case pdg::eventType_NetConnect:
                return false;
                break;
            case pdg::eventType_NetDisconnect:
                return false;
                break;
            case pdg::eventType_NetData:
                return false;
                break;
            case pdg::eventType_NetError:
                return false;
                break;
#endif
#ifndef PDG_NO_SOUND
            case pdg::eventType_SoundEvent:
                obj1_ = v8::Local<v8::Object>::New(isolate, static_cast<SoundEventInfo*>(inEventData)->sound->mSoundScriptObj);
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventCode").ToLocalChecked(), v8::Integer::New(isolate, static_cast<SoundEventInfo*>(inEventData)->eventCode)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "sound").ToLocalChecked(), obj1_).ToChecked();
                break;
#endif
#ifndef PDG_NO_GUI
            case pdg::eventType_PortResized:
                obj1_ = v8::Local<v8::Object>::New(isolate, static_cast<PortResizeInfo*>(inEventData)->port->mPortScriptObj);
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "port").ToLocalChecked(), obj1_).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "screenPos").ToLocalChecked(), v8::Integer::New(isolate, static_cast<PortResizeInfo*>(inEventData)->screenPos)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "oldScreenPos").ToLocalChecked(), v8::Integer::New(isolate, static_cast<PortResizeInfo*>(inEventData)->oldScreenPos)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "oldWidth").ToLocalChecked(), v8::Integer::New(isolate, static_cast<PortResizeInfo*>(inEventData)->oldWidth)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "oldHeight").ToLocalChecked(), v8::Integer::New(isolate, static_cast<PortResizeInfo*>(inEventData)->oldHeight)).ToChecked();
                break;
            case pdg::eventType_PortDraw:
                obj1_ = v8::Local<v8::Object>::New(isolate, static_cast<PortDrawInfo*>(inEventData)->port->mPortScriptObj);
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "port").ToLocalChecked(), obj1_).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "frameNum").ToLocalChecked(), v8::Integer::New(isolate, static_cast<PortDrawInfo*>(inEventData)->frameNum)).ToChecked();
                break;
#endif
            case pdg::eventType_SpriteCollide:
            case pdg::eventType_SpriteBreak:
                if (inEventType == pdg::eventType_SpriteCollide)
                {
                    SpriteCollideInfo* sci = static_cast<SpriteCollideInfo*>(inEventData);
                    if (sci->targetSprite)
                    {
                        SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteCollideInfo* sci->targetSprite: %p", sci->targetSprite));
                        obj1_ = v8::Local<v8::Object>::New(isolate, sci->targetSprite->mSpriteScriptObj);
                        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "targetSprite").ToLocalChecked(), obj1_).ToChecked();
                    }
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "normal").ToLocalChecked(), v8_MakeJavascriptVector(isolate, sci->normal)).ToChecked();
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "impulse").ToLocalChecked(), v8_MakeJavascriptVector(isolate, sci->impulse)).ToChecked();
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "force").ToLocalChecked(), v8::Number::New(isolate, sci->force)).ToChecked();
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "kineticEnergy").ToLocalChecked(), v8::Number::New(isolate, sci->kineticEnergy)).ToChecked();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
                    if (sci->arbiter)
                    {
                        SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteCollideInfo* sci->arbiter: %p", sci->arbiter));
                        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "arbiter").ToLocalChecked(), cpArbiterWrap::NewFromCpp(isolate, sci->arbiter)).ToChecked();
                    }
#endif
#ifdef PDG_SPRITER_SUPPORT
                    if (sci->collisionName)
                    {
                        SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteCollideInfo* sci->collisionName: %s", sci->collisionName));
                        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "collisionName").ToLocalChecked(), v8::String::NewFromUtf8(isolate, sci->collisionName).ToLocalChecked()).ToChecked();
                    }
                    else
                    {
                        SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteCollideInfo* sci->collisionName is null"));
                        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "collisionName").ToLocalChecked(), v8::Null(isolate)).ToChecked();
                    }
                    if (sci->withCollisionName)
                    {
                        SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteCollideInfo* sci->withCollisionName: %s", sci->withCollisionName));
                        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "withCollisionName").ToLocalChecked(), v8::String::NewFromUtf8(isolate, sci->withCollisionName).ToLocalChecked()).ToChecked();
                    }
                    else
                    {
                        SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteCollideInfo* sci->withCollisionName is null"));
                        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "withCollisionName").ToLocalChecked(), v8::Null(isolate)).ToChecked();
                    }
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "isFirstContact").ToLocalChecked(), v8::Boolean::New(isolate, sci->isFirstContact)).ToChecked();
#endif
                }
                else
                {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
                    SpriteJointBreakInfo* sjb = static_cast<SpriteJointBreakInfo*>(inEventData);
                    if (sjb->targetSprite)
                    {
                        SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteJointBreakInfo* sjb->targetSprite: %p", sjb->targetSprite));
                        obj1_ = v8::Local<v8::Object>::New(isolate, sjb->targetSprite->mSpriteScriptObj);
                        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "targetSprite").ToLocalChecked(), obj1_).ToChecked();
                    }
                    else
                    {
                        SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteJointBreakInfo* sjb->targetSprite is null"));
                        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "targetSprite").ToLocalChecked(), v8::Null(isolate)).ToChecked();
                    }
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "impulse").ToLocalChecked(), v8::Number::New(isolate, sjb->impulse)).ToChecked();
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "force").ToLocalChecked(), v8::Number::New(isolate, sjb->force)).ToChecked();
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "breakForce").ToLocalChecked(), v8::Number::New(isolate, sjb->breakForce)).ToChecked();
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "joint").ToLocalChecked(), cpConstraintWrap::NewFromCpp(isolate, sjb->joint)).ToChecked();
#endif
                }

            case pdg::eventType_SpriteAnimate:
                SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteAnimateInfo* sai->id: %d", sai->id));
                if (sai->actingSprite)
                {
                    SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteAnimateInfo* sai->actingSprite: %p", sai->actingSprite));
                    obj1_ = v8::Local<v8::Object>::New(isolate, sai->actingSprite->mSpriteScriptObj);
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "actingSprite").ToLocalChecked(), obj1_).ToChecked();
                }
                else
                {
                    SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteAnimateInfo* sai->actingSprite is null"));
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "actingSprite").ToLocalChecked(), v8::Null(isolate)).ToChecked();
                }
                if (sai->inLayer)
                {
                    SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteAnimateInfo* sai->inLayer: %p", sai->inLayer));
                    obj2_ = v8::Local<v8::Object>::New(isolate, sai->inLayer->mSpriteLayerScriptObj);
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "inLayer").ToLocalChecked(), obj2_).ToChecked();
                }
                else
                {
                    SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteAnimateInfo* sai->inLayer is null"));
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "inLayer").ToLocalChecked(), v8::Null(isolate)).ToChecked();
                }
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action").ToLocalChecked(), v8::Integer::New(isolate, sai->action)).ToChecked();
                SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteAnimateInfo* done setting properties "));
                break;
            case pdg::eventType_SpriteLayer:
                if (sli->actingLayer)
                {
                    SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteLayerInfo* sli->actingLayer: %p", sli->actingLayer));
                    obj1_ = v8::Local<v8::Object>::New(isolate, sli->actingLayer->mSpriteLayerScriptObj);
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "actingLayer").ToLocalChecked(), obj1_).ToChecked();
                }
                else
                {
                    SPRITE_EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteLayerInfo* sli->actingLayer is null"));
                    (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "actingLayer").ToLocalChecked(), v8::Null(isolate)).ToChecked();
                }
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action").ToLocalChecked(), v8::Integer::New(isolate, sli->action)).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "actingLayer").ToLocalChecked(), obj1_).ToChecked();
                (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "millisec").ToLocalChecked(), v8::Integer::NewFromUnsigned(isolate, sli->millisec)).ToChecked();
                break;
            default:
            {
                std::ostringstream msg;
                msg << "unknown event (" << inEventType << ")";
                s_HaveSavedError = true;
                {
                    std::ostringstream excpt_;
                    excpt_ << msg.str().c_str();
                    v8::Isolate* isolate = v8::Isolate::GetCurrent();
                    s_SavedError.Reset(isolate, v8::Exception::TypeError( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
                };
                return false;
            }
            break;

        }

        v8::TryCatch try_catch(isolate);

        v8::Local<v8::Value> argv[1];
        argv[0] = v8::Local<v8::Value>::New(isolate, jsEvent);

        SCRIPT_DEBUG_ONLY( if (this->mIEventHandlerScriptObj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 879 << " - NIL JS Object (" "this->mIEventHandlerScriptObj" "|"<<*((void**)&(this->mIEventHandlerScriptObj))<<")\n";
        }
        else if (!this->mIEventHandlerScriptObj->IsObject())
        {
            std::cerr << __func__<<":"<< 879 << " - NOT JS Object (" "this->mIEventHandlerScriptObj" "|"<<*((void**)&(this->mIEventHandlerScriptObj))<<") : " << (this->mIEventHandlerScriptObj.IsEmpty() ? "empty" : this->mIEventHandlerScriptObj->IsArray() ? "array" : this->mIEventHandlerScriptObj->IsFunction() ? "function" : this->mIEventHandlerScriptObj->IsStringObject() ? "string (object)" : this->mIEventHandlerScriptObj->IsString() ? "string" : this->mIEventHandlerScriptObj->IsNull() ? "null" : this->mIEventHandlerScriptObj->IsUndefined() ? "undefined" : this->mIEventHandlerScriptObj->IsNumberObject() ? "number (object)" : this->mIEventHandlerScriptObj->IsNumber() ? "number" : this->mIEventHandlerScriptObj->IsBoolean() ? "boolean" : this->mIEventHandlerScriptObj->IsDate() ? "date" : this->mIEventHandlerScriptObj->IsRegExp() ? "regexp" : this->mIEventHandlerScriptObj->IsNativeError() ? "error" : this->mIEventHandlerScriptObj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = this->mIEventHandlerScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                IEventHandlerWrap* obj__ = dynamic_cast<IEventHandlerWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<IEventHandlerWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 879 << " - JS Object (""this->mIEventHandlerScriptObj""|"<<*((void**)&(this->mIEventHandlerScriptObj))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 879 << " - JS Object (""this->mIEventHandlerScriptObj""|"<<*((void**)&(this->mIEventHandlerScriptObj))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 879 << " - JS Object (""this->mIEventHandlerScriptObj""|" << *((void**)&(this->mIEventHandlerScriptObj)) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
            }
        } );

        v8::Local<v8::Value> resVal;
        v8::Local<v8::Function> func;
        v8::Local<v8::Object> obj_ = v8::Local<v8::Object>::New(isolate, mIEventHandlerScriptObj);
        if (!mScriptHandlerFunc.IsEmpty())
        {
            func = v8::Local<v8::Function>::New(isolate, mScriptHandlerFunc);
        }
        else if ((!obj_->IsNull() && obj_->Has(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "handleEvent").ToLocalChecked()).ToChecked()))
        {
            func = v8::Local<v8::Function>::Cast(obj_->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "handleEvent").ToLocalChecked()).ToLocalChecked());
        }
        else
        {
            DEBUG_ONLY(
                v8::String::Utf8Value objectNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                std::cerr << "fatal: IEventHandler object " << *objectNameStr << " missing handleEvent() Function!!\n";
                exit(1);
                )
                return false;
        }
        resVal = ([&]() -> v8::Local<v8::Value>
        {
            if (func.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::MaybeLocal<v8::Value> maybe = func->Call(isolate->GetCurrentContext(), obj_, 1, argv);
                if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());

        if (try_catch.HasCaught())
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling event Handler!!" ); )
                FatalException(try_catch);
            return false;
        }
        if (!resVal->IsBoolean())
        {
#ifdef DEBUG
            std::cerr << "result mismatch: return value from event handler Function must be a boolean ("
                << v8_GetFunctionName(func) << " at " << v8_GetFunctionFileAndLine(func) << ")\n";
            exit(1);
#else
            return false;
#endif
        }
        return resVal->BooleanValue(isolate);
    }

    ScriptAnimationEventHandler::ScriptAnimationEventHandler()
    {
        mExpectedAction = 0;
    }

    ScriptAnimationEventHandler::ScriptAnimationEventHandler(v8::Local<v8::Function> func, long expectedAction)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        mScriptHandlerFunc.Reset(isolate, func);
        mExpectedAction = expectedAction;
    }

    bool ScriptAnimationEventHandler::handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) throw()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();

        if (inEventType != pdg::eventType_SpriteAnimate)
        {
            return false;
        }

        SpriteAnimateInfo* animateInfo = static_cast<SpriteAnimateInfo*>(inEventData);
        if (animateInfo->action != mExpectedAction)
        {
            return false;
        }

        if (!animateInfo->actingSprite || !animateInfo->inLayer)
        {
            DEBUG_ONLY(
                std::cerr << "ScriptAnimationEventHandler: null sprite or layer" << std::endl;
                )
                return false;
        }

        v8::TryCatch try_catch(isolate);

        v8::Local<v8::Object> jsEvent = v8::Object::New(isolate);
        v8::Local<v8::Object> obj1_, obj2_;

        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "emitter").ToLocalChecked(), v8::Local<v8::Object>::New(isolate, emitter->mEventEmitterScriptObj)).ToChecked();
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType").ToLocalChecked(), v8::Integer::New(isolate, inEventType)).ToChecked();
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action").ToLocalChecked(), v8::Integer::New(isolate, animateInfo->action)).ToChecked();

        if (animateInfo->actingSprite->mSpriteScriptObj.IsEmpty())
        {
            DEBUG_ONLY(
                std::cerr << "ScriptAnimationEventHandler: null sprite script object" << std::endl;
                )
                return false;
        }
        if (animateInfo->inLayer->mSpriteLayerScriptObj.IsEmpty())
        {
            DEBUG_ONLY(
                std::cerr << "ScriptAnimationEventHandler: null layer script object" << std::endl;
                )
                return false;
        }

        obj1_ = v8::Local<v8::Object>::New(isolate, animateInfo->actingSprite->mSpriteScriptObj);
        obj2_ = v8::Local<v8::Object>::New(isolate, animateInfo->inLayer->mSpriteLayerScriptObj);
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "actingSprite").ToLocalChecked(), obj1_).ToChecked();
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "inLayer").ToLocalChecked(), obj2_).ToChecked();

        v8::Local<v8::Value> argv[1];
        argv[0] = v8::Local<v8::Value>::New(isolate, jsEvent);

        SCRIPT_DEBUG_ONLY( if (this->mIEventHandlerScriptObj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 983 << " - NIL JS Object (" "this->mIEventHandlerScriptObj" "|"<<*((void**)&(this->mIEventHandlerScriptObj))<<")\n";
        }
        else if (!this->mIEventHandlerScriptObj->IsObject())
        {
            std::cerr << __func__<<":"<< 983 << " - NOT JS Object (" "this->mIEventHandlerScriptObj" "|"<<*((void**)&(this->mIEventHandlerScriptObj))<<") : " << (this->mIEventHandlerScriptObj.IsEmpty() ? "empty" : this->mIEventHandlerScriptObj->IsArray() ? "array" : this->mIEventHandlerScriptObj->IsFunction() ? "function" : this->mIEventHandlerScriptObj->IsStringObject() ? "string (object)" : this->mIEventHandlerScriptObj->IsString() ? "string" : this->mIEventHandlerScriptObj->IsNull() ? "null" : this->mIEventHandlerScriptObj->IsUndefined() ? "undefined" : this->mIEventHandlerScriptObj->IsNumberObject() ? "number (object)" : this->mIEventHandlerScriptObj->IsNumber() ? "number" : this->mIEventHandlerScriptObj->IsBoolean() ? "boolean" : this->mIEventHandlerScriptObj->IsDate() ? "date" : this->mIEventHandlerScriptObj->IsRegExp() ? "regexp" : this->mIEventHandlerScriptObj->IsNativeError() ? "error" : this->mIEventHandlerScriptObj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = this->mIEventHandlerScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                IEventHandlerWrap* obj__ = dynamic_cast<IEventHandlerWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<IEventHandlerWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 983 << " - JS Object (""this->mIEventHandlerScriptObj""|"<<*((void**)&(this->mIEventHandlerScriptObj))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 983 << " - JS Object (""this->mIEventHandlerScriptObj""|"<<*((void**)&(this->mIEventHandlerScriptObj))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 983 << " - JS Object (""this->mIEventHandlerScriptObj""|" << *((void**)&(this->mIEventHandlerScriptObj)) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
            }
        } );

        v8::Local<v8::Value> resVal;
        v8::Local<v8::Function> func;
        v8::Local<v8::Object> obj_ = v8::Local<v8::Object>::New(isolate, mIEventHandlerScriptObj);
        if (!mScriptHandlerFunc.IsEmpty())
        {
            func = v8::Local<v8::Function>::New(isolate, mScriptHandlerFunc);
        }
        else if ((!obj_->IsNull() && obj_->Has(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "handleEvent").ToLocalChecked()).ToChecked()))
        {
            func = v8::Local<v8::Function>::Cast(obj_->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "handleEvent").ToLocalChecked()).ToLocalChecked());
        }
        else
        {
            DEBUG_ONLY(
                v8::String::Utf8Value objectNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                std::cerr << "fatal: IEventHandler object " << *objectNameStr << " missing handleEvent() Function!!\n";
                exit(1);
                )
                return false;
        }
        resVal = ([&]() -> v8::Local<v8::Value>
        {
            if (func.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::MaybeLocal<v8::Value> maybe = func->Call(isolate->GetCurrentContext(), obj_, 1, argv);
                if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());

        if (try_catch.HasCaught())
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling event Handler!!" ); )
                FatalException(try_catch);
            return false;
        }
        if (!resVal->IsBoolean())
        {
#ifdef DEBUG
            std::cerr << "result mismatch: return value from event handler Function must be a boolean ("
                << v8_GetFunctionName(func) << " at " << v8_GetFunctionFileAndLine(func) << ")\n";
            exit(1);
#else
            return false;
#endif
        }
        return resVal->BooleanValue(isolate);
    }

    ScriptTouchEventHandler::ScriptTouchEventHandler()
    {
        mExpectedAction = 0;
    }

    ScriptTouchEventHandler::ScriptTouchEventHandler(v8::Local<v8::Function> func, long expectedAction)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        mScriptHandlerFunc.Reset(isolate, func);
        mExpectedAction = expectedAction;
    }

    bool ScriptTouchEventHandler::handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) throw()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();

        if (inEventType != pdg::eventType_SpriteTouch)
        {
            return false;
        }

        SpriteTouchInfo* touchInfo = static_cast<SpriteTouchInfo*>(inEventData);
        if (touchInfo->touchType != mExpectedAction)
        {
            return false;
        }

        v8::TryCatch try_catch(isolate);

        v8::Local<v8::Object> jsEvent = v8::Object::New(isolate);
        v8::Local<v8::Object> obj1_, obj2_;

        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "emitter").ToLocalChecked(), v8::Local<v8::Object>::New(isolate, emitter->mEventEmitterScriptObj)).ToChecked();
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType").ToLocalChecked(), v8::Integer::New(isolate, inEventType)).ToChecked();
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "touchType").ToLocalChecked(), v8::Integer::New(isolate, touchInfo->touchType)).ToChecked();

        obj1_ = v8::Local<v8::Object>::New(isolate, touchInfo->touchedSprite->mSpriteScriptObj);
        obj2_ = v8::Local<v8::Object>::New(isolate, touchInfo->inLayer->mSpriteLayerScriptObj);
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "touchedSprite").ToLocalChecked(), obj1_).ToChecked();
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "inLayer").ToLocalChecked(), obj2_).ToChecked();

        v8::Local<v8::Value> argv[1];
        argv[0] = v8::Local<v8::Value>::New(isolate, jsEvent);

        SCRIPT_DEBUG_ONLY( if (this->mIEventHandlerScriptObj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 1065 << " - NIL JS Object (" "this->mIEventHandlerScriptObj" "|"<<*((void**)&(this->mIEventHandlerScriptObj))<<")\n";
        }
        else if (!this->mIEventHandlerScriptObj->IsObject())
        {
            std::cerr << __func__<<":"<< 1065 << " - NOT JS Object (" "this->mIEventHandlerScriptObj" "|"<<*((void**)&(this->mIEventHandlerScriptObj))<<") : " << (this->mIEventHandlerScriptObj.IsEmpty() ? "empty" : this->mIEventHandlerScriptObj->IsArray() ? "array" : this->mIEventHandlerScriptObj->IsFunction() ? "function" : this->mIEventHandlerScriptObj->IsStringObject() ? "string (object)" : this->mIEventHandlerScriptObj->IsString() ? "string" : this->mIEventHandlerScriptObj->IsNull() ? "null" : this->mIEventHandlerScriptObj->IsUndefined() ? "undefined" : this->mIEventHandlerScriptObj->IsNumberObject() ? "number (object)" : this->mIEventHandlerScriptObj->IsNumber() ? "number" : this->mIEventHandlerScriptObj->IsBoolean() ? "boolean" : this->mIEventHandlerScriptObj->IsDate() ? "date" : this->mIEventHandlerScriptObj->IsRegExp() ? "regexp" : this->mIEventHandlerScriptObj->IsNativeError() ? "error" : this->mIEventHandlerScriptObj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = this->mIEventHandlerScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                IEventHandlerWrap* obj__ = dynamic_cast<IEventHandlerWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<IEventHandlerWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 1065 << " - JS Object (""this->mIEventHandlerScriptObj""|"<<*((void**)&(this->mIEventHandlerScriptObj))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 1065 << " - JS Object (""this->mIEventHandlerScriptObj""|"<<*((void**)&(this->mIEventHandlerScriptObj))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 1065 << " - JS Object (""this->mIEventHandlerScriptObj""|" << *((void**)&(this->mIEventHandlerScriptObj)) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
            }
        } );

        v8::Local<v8::Value> resVal;
        v8::Local<v8::Function> func;
        v8::Local<v8::Object> obj_ = v8::Local<v8::Object>::New(isolate, mIEventHandlerScriptObj);
        if (!mScriptHandlerFunc.IsEmpty())
        {
            func = v8::Local<v8::Function>::New(isolate, mScriptHandlerFunc);
        }
        else if ((!obj_->IsNull() && obj_->Has(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "handleEvent").ToLocalChecked()).ToChecked()))
        {
            func = v8::Local<v8::Function>::Cast(obj_->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "handleEvent").ToLocalChecked()).ToLocalChecked());
        }
        else
        {
            DEBUG_ONLY(
                v8::String::Utf8Value objectNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                std::cerr << "fatal: IEventHandler object " << *objectNameStr << " missing handleEvent() Function!!\n";
                exit(1);
                )
                return false;
        }
        resVal = ([&]() -> v8::Local<v8::Value>
        {
            if (func.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::MaybeLocal<v8::Value> maybe = func->Call(isolate->GetCurrentContext(), obj_, 1, argv);
                if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());

        if (try_catch.HasCaught())
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling event Handler!!" ); )
                FatalException(try_catch);
            return false;
        }
        if (!resVal->IsBoolean())
        {
#ifdef DEBUG
            std::cerr << "result mismatch: return value from event handler Function must be a boolean ("
                << v8_GetFunctionName(func) << " at " << v8_GetFunctionFileAndLine(func) << ")\n";
            exit(1);
#else
            return false;
#endif
        }
        return resVal->BooleanValue(isolate);
    }

    ScriptLayerEventHandler::ScriptLayerEventHandler()
    {
        mExpectedAction = 0;
    }

    ScriptLayerEventHandler::ScriptLayerEventHandler(v8::Local<v8::Function> func, long expectedAction)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        mScriptHandlerFunc.Reset(isolate, func);
        mExpectedAction = expectedAction;
    }

    bool ScriptLayerEventHandler::handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) throw()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();

        if (inEventType != pdg::eventType_SpriteLayer)
        {
            return false;
        }

        SpriteLayerInfo* layerInfo = static_cast<SpriteLayerInfo*>(inEventData);
        if (layerInfo->action != mExpectedAction)
        {
            return false;
        }

        v8::TryCatch try_catch(isolate);

        v8::Local<v8::Object> jsEvent = v8::Object::New(isolate);
        v8::Local<v8::Object> obj1_;

        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "emitter").ToLocalChecked(), v8::Local<v8::Object>::New(isolate, emitter->mEventEmitterScriptObj)).ToChecked();
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType").ToLocalChecked(), v8::Integer::New(isolate, inEventType)).ToChecked();
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action").ToLocalChecked(), v8::Integer::New(isolate, layerInfo->action)).ToChecked();

        obj1_ = v8::Local<v8::Object>::New(isolate, layerInfo->actingLayer->mSpriteLayerScriptObj);
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "actingLayer").ToLocalChecked(), obj1_).ToChecked();
        (void)jsEvent->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "millisec").ToLocalChecked(), v8::Integer::NewFromUnsigned(isolate, layerInfo->millisec)).ToChecked();

        v8::Local<v8::Value> argv[1];
        argv[0] = v8::Local<v8::Value>::New(isolate, jsEvent);

        SCRIPT_DEBUG_ONLY( if (this->mIEventHandlerScriptObj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 1146 << " - NIL JS Object (" "this->mIEventHandlerScriptObj" "|"<<*((void**)&(this->mIEventHandlerScriptObj))<<")\n";
        }
        else if (!this->mIEventHandlerScriptObj->IsObject())
        {
            std::cerr << __func__<<":"<< 1146 << " - NOT JS Object (" "this->mIEventHandlerScriptObj" "|"<<*((void**)&(this->mIEventHandlerScriptObj))<<") : " << (this->mIEventHandlerScriptObj.IsEmpty() ? "empty" : this->mIEventHandlerScriptObj->IsArray() ? "array" : this->mIEventHandlerScriptObj->IsFunction() ? "function" : this->mIEventHandlerScriptObj->IsStringObject() ? "string (object)" : this->mIEventHandlerScriptObj->IsString() ? "string" : this->mIEventHandlerScriptObj->IsNull() ? "null" : this->mIEventHandlerScriptObj->IsUndefined() ? "undefined" : this->mIEventHandlerScriptObj->IsNumberObject() ? "number (object)" : this->mIEventHandlerScriptObj->IsNumber() ? "number" : this->mIEventHandlerScriptObj->IsBoolean() ? "boolean" : this->mIEventHandlerScriptObj->IsDate() ? "date" : this->mIEventHandlerScriptObj->IsRegExp() ? "regexp" : this->mIEventHandlerScriptObj->IsNativeError() ? "error" : this->mIEventHandlerScriptObj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = this->mIEventHandlerScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                IEventHandlerWrap* obj__ = dynamic_cast<IEventHandlerWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<IEventHandlerWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 1146 << " - JS Object (""this->mIEventHandlerScriptObj""|"<<*((void**)&(this->mIEventHandlerScriptObj))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 1146 << " - JS Object (""this->mIEventHandlerScriptObj""|"<<*((void**)&(this->mIEventHandlerScriptObj))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 1146 << " - JS Object (""this->mIEventHandlerScriptObj""|" << *((void**)&(this->mIEventHandlerScriptObj)) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
            }
        } );

        v8::Local<v8::Value> resVal;
        v8::Local<v8::Function> func;
        v8::Local<v8::Object> obj_ = v8::Local<v8::Object>::New(isolate, mIEventHandlerScriptObj);
        if (!mScriptHandlerFunc.IsEmpty())
        {
            func = v8::Local<v8::Function>::New(isolate, mScriptHandlerFunc);
        }
        else if ((!obj_->IsNull() && obj_->Has(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "handleEvent").ToLocalChecked()).ToChecked()))
        {
            func = v8::Local<v8::Function>::Cast(obj_->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "handleEvent").ToLocalChecked()).ToLocalChecked());
        }
        else
        {
            DEBUG_ONLY(
                v8::String::Utf8Value objectNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                std::cerr << "fatal: IEventHandler object " << *objectNameStr << " missing handleEvent() Function!!\n";
                exit(1);
                )
                return false;
        }
        resVal = ([&]() -> v8::Local<v8::Value>
        {
            if (func.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::MaybeLocal<v8::Value> maybe = func->Call(isolate->GetCurrentContext(), obj_, 1, argv);
                if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());

        if (try_catch.HasCaught())
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling event Handler!!" ); )
                FatalException(try_catch);
            return false;
        }
        if (!resVal->IsBoolean())
        {
#ifdef DEBUG
            std::cerr << "result mismatch: return value from event handler Function must be a boolean ("
                << v8_GetFunctionName(func) << " at " << v8_GetFunctionFileAndLine(func) << ")\n";
            exit(1);
#else
            return false;
#endif
        }
        return resVal->BooleanValue(isolate);
    }

    ScriptAnimationHelper::ScriptAnimationHelper(v8::Local<v8::Function> func)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        mScriptAnimateFunc.Reset(isolate, func);
    }

    bool ScriptAnimationHelper::animate(Animated* what, ms_delta msElapsed) throw()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();

        v8::TryCatch try_catch(isolate);

        v8::Local<v8::Value> argv[2];
        argv[0] = v8::Local<v8::Object>::New(isolate, what->mAnimatedScriptObj);
        argv[1] = v8::Local<v8::Value>::New(isolate, v8::Integer::NewFromUnsigned(isolate, msElapsed));

        SCRIPT_DEBUG_ONLY( if (what->mAnimatedScriptObj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 1200 << " - NIL JS Object (" "what->mAnimatedScriptObj" "|"<<*((void**)&(what->mAnimatedScriptObj))<<")\n";
        }
        else if (!what->mAnimatedScriptObj->IsObject())
        {
            std::cerr << __func__<<":"<< 1200 << " - NOT JS Object (" "what->mAnimatedScriptObj" "|"<<*((void**)&(what->mAnimatedScriptObj))<<") : " << (what->mAnimatedScriptObj.IsEmpty() ? "empty" : what->mAnimatedScriptObj->IsArray() ? "array" : what->mAnimatedScriptObj->IsFunction() ? "function" : what->mAnimatedScriptObj->IsStringObject() ? "string (object)" : what->mAnimatedScriptObj->IsString() ? "string" : what->mAnimatedScriptObj->IsNull() ? "null" : what->mAnimatedScriptObj->IsUndefined() ? "undefined" : what->mAnimatedScriptObj->IsNumberObject() ? "number (object)" : what->mAnimatedScriptObj->IsNumber() ? "number" : what->mAnimatedScriptObj->IsBoolean() ? "boolean" : what->mAnimatedScriptObj->IsDate() ? "date" : what->mAnimatedScriptObj->IsRegExp() ? "regexp" : what->mAnimatedScriptObj->IsNativeError() ? "error" : what->mAnimatedScriptObj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = what->mAnimatedScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                AnimatedWrap* obj__ = dynamic_cast<AnimatedWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<AnimatedWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 1200 << " - JS Object (""what->mAnimatedScriptObj""|"<<*((void**)&(what->mAnimatedScriptObj))<<"): " << objName << " - is a subclass of C++ ""Animated""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 1200 << " - JS Object (""what->mAnimatedScriptObj""|"<<*((void**)&(what->mAnimatedScriptObj))<<"): " << objName << " - does not wrap ""Animated""\n";
                }
            }
            else
            {
                Animated* obj = dynamic_cast<Animated*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 1200 << " - JS Object (""what->mAnimatedScriptObj""|" << *((void**)&(what->mAnimatedScriptObj)) << "): " << objName<<" - wraps C++ ""Animated"" ("<<(void*)obj<<")\n";
            }
        } );
        SCRIPT_DEBUG_ONLY( if (this->mIAnimationHelperScriptObj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 1201 << " - NIL JS Object (" "this->mIAnimationHelperScriptObj" "|"<<*((void**)&(this->mIAnimationHelperScriptObj))<<")\n";
        }
        else if (!this->mIAnimationHelperScriptObj->IsObject())
        {
            std::cerr << __func__<<":"<< 1201 << " - NOT JS Object (" "this->mIAnimationHelperScriptObj" "|"<<*((void**)&(this->mIAnimationHelperScriptObj))<<") : " << (this->mIAnimationHelperScriptObj.IsEmpty() ? "empty" : this->mIAnimationHelperScriptObj->IsArray() ? "array" : this->mIAnimationHelperScriptObj->IsFunction() ? "function" : this->mIAnimationHelperScriptObj->IsStringObject() ? "string (object)" : this->mIAnimationHelperScriptObj->IsString() ? "string" : this->mIAnimationHelperScriptObj->IsNull() ? "null" : this->mIAnimationHelperScriptObj->IsUndefined() ? "undefined" : this->mIAnimationHelperScriptObj->IsNumberObject() ? "number (object)" : this->mIAnimationHelperScriptObj->IsNumber() ? "number" : this->mIAnimationHelperScriptObj->IsBoolean() ? "boolean" : this->mIAnimationHelperScriptObj->IsDate() ? "date" : this->mIAnimationHelperScriptObj->IsRegExp() ? "regexp" : this->mIAnimationHelperScriptObj->IsNativeError() ? "error" : this->mIAnimationHelperScriptObj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = this->mIAnimationHelperScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                IAnimationHelperWrap* obj__ = dynamic_cast<IAnimationHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<IAnimationHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 1201 << " - JS Object (""this->mIAnimationHelperScriptObj""|"<<*((void**)&(this->mIAnimationHelperScriptObj))<<"): " << objName << " - is a subclass of C++ ""IAnimationHelper""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 1201 << " - JS Object (""this->mIAnimationHelperScriptObj""|"<<*((void**)&(this->mIAnimationHelperScriptObj))<<"): " << objName << " - does not wrap ""IAnimationHelper""\n";
                }
            }
            else
            {
                IAnimationHelper* obj = dynamic_cast<IAnimationHelper*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 1201 << " - JS Object (""this->mIAnimationHelperScriptObj""|" << *((void**)&(this->mIAnimationHelperScriptObj)) << "): " << objName<<" - wraps C++ ""IAnimationHelper"" ("<<(void*)obj<<")\n";
            }
        } );

        v8::Local<v8::Value> resVal;
        v8::Local<v8::Function> func;
        v8::Local<v8::Object> obj_ = v8::Local<v8::Object>::New(isolate, this->mIAnimationHelperScriptObj);
        if (!mScriptAnimateFunc.IsEmpty())
        {
            func = v8::Local<v8::Function>::New(isolate, mScriptAnimateFunc);
        }
        else if ((!obj_->IsNull() && obj_->Has(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "animate").ToLocalChecked()).ToChecked()))
        {
            func = v8::Local<v8::Function>::Cast(obj_->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "animate").ToLocalChecked()).ToLocalChecked());
        }
        else
        {
            DEBUG_ONLY(
                v8::String::Utf8Value objectNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                std::cerr << "fatal: IAnimationHelper object " << *objectNameStr << " missing animate() Function!!";
                exit(1);
                )
                return false;
        }
        resVal = ([&]() -> v8::Local<v8::Value>
        {
            if (func.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::MaybeLocal<v8::Value> maybe = func->Call(isolate->GetCurrentContext(), obj_, 2, argv);
                if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());

        if (try_catch.HasCaught())
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling Animation Helper!!" ); )
                FatalException(try_catch);
            return false;
        }
        if (!resVal->IsBoolean())
        {
#ifdef DEBUG
            std::cerr << "result mismatch: return value from animate helper Function must be a boolean ("
                << v8_GetFunctionName(func) << " at " << v8_GetFunctionFileAndLine(func) << ")\n";
            exit(1);
#else
            return false;
#endif
        }
        return resVal->BooleanValue(isolate);
    }

    ScriptSpriteCollideHelper::ScriptSpriteCollideHelper(v8::Local<v8::Function> func)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        mScriptAllowCollisionFunc.Reset(isolate, func);
    }

    bool ScriptSpriteCollideHelper::allowCollision(Sprite* sprite, Sprite* withSprite) throw()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();

        v8::TryCatch try_catch(isolate);

        v8::Local<v8::Value> argv[2];
        argv[0] = v8::Local<v8::Object>::New(isolate, sprite->mSpriteScriptObj);
        argv[1] = v8::Local<v8::Object>::New(isolate, withSprite->mSpriteScriptObj);

        SCRIPT_DEBUG_ONLY( if (sprite->mSpriteScriptObj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 1255 << " - NIL JS Object (" "sprite->mSpriteScriptObj" "|"<<*((void**)&(sprite->mSpriteScriptObj))<<")\n";
        }
        else if (!sprite->mSpriteScriptObj->IsObject())
        {
            std::cerr << __func__<<":"<< 1255 << " - NOT JS Object (" "sprite->mSpriteScriptObj" "|"<<*((void**)&(sprite->mSpriteScriptObj))<<") : " << (sprite->mSpriteScriptObj.IsEmpty() ? "empty" : sprite->mSpriteScriptObj->IsArray() ? "array" : sprite->mSpriteScriptObj->IsFunction() ? "function" : sprite->mSpriteScriptObj->IsStringObject() ? "string (object)" : sprite->mSpriteScriptObj->IsString() ? "string" : sprite->mSpriteScriptObj->IsNull() ? "null" : sprite->mSpriteScriptObj->IsUndefined() ? "undefined" : sprite->mSpriteScriptObj->IsNumberObject() ? "number (object)" : sprite->mSpriteScriptObj->IsNumber() ? "number" : sprite->mSpriteScriptObj->IsBoolean() ? "boolean" : sprite->mSpriteScriptObj->IsDate() ? "date" : sprite->mSpriteScriptObj->IsRegExp() ? "regexp" : sprite->mSpriteScriptObj->IsNativeError() ? "error" : sprite->mSpriteScriptObj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = sprite->mSpriteScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                SpriteWrap* obj__ = dynamic_cast<SpriteWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<SpriteWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 1255 << " - JS Object (""sprite->mSpriteScriptObj""|"<<*((void**)&(sprite->mSpriteScriptObj))<<"): " << objName << " - is a subclass of C++ ""Sprite""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 1255 << " - JS Object (""sprite->mSpriteScriptObj""|"<<*((void**)&(sprite->mSpriteScriptObj))<<"): " << objName << " - does not wrap ""Sprite""\n";
                }
            }
            else
            {
                Sprite* obj = dynamic_cast<Sprite*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 1255 << " - JS Object (""sprite->mSpriteScriptObj""|" << *((void**)&(sprite->mSpriteScriptObj)) << "): " << objName<<" - wraps C++ ""Sprite"" ("<<(void*)obj<<")\n";
            }
        } );
        SCRIPT_DEBUG_ONLY( if (withSprite->mSpriteScriptObj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 1256 << " - NIL JS Object (" "withSprite->mSpriteScriptObj" "|"<<*((void**)&(withSprite->mSpriteScriptObj))<<")\n";
        }
        else if (!withSprite->mSpriteScriptObj->IsObject())
        {
            std::cerr << __func__<<":"<< 1256 << " - NOT JS Object (" "withSprite->mSpriteScriptObj" "|"<<*((void**)&(withSprite->mSpriteScriptObj))<<") : " << (withSprite->mSpriteScriptObj.IsEmpty() ? "empty" : withSprite->mSpriteScriptObj->IsArray() ? "array" : withSprite->mSpriteScriptObj->IsFunction() ? "function" : withSprite->mSpriteScriptObj->IsStringObject() ? "string (object)" : withSprite->mSpriteScriptObj->IsString() ? "string" : withSprite->mSpriteScriptObj->IsNull() ? "null" : withSprite->mSpriteScriptObj->IsUndefined() ? "undefined" : withSprite->mSpriteScriptObj->IsNumberObject() ? "number (object)" : withSprite->mSpriteScriptObj->IsNumber() ? "number" : withSprite->mSpriteScriptObj->IsBoolean() ? "boolean" : withSprite->mSpriteScriptObj->IsDate() ? "date" : withSprite->mSpriteScriptObj->IsRegExp() ? "regexp" : withSprite->mSpriteScriptObj->IsNativeError() ? "error" : withSprite->mSpriteScriptObj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = withSprite->mSpriteScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                SpriteWrap* obj__ = dynamic_cast<SpriteWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<SpriteWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 1256 << " - JS Object (""withSprite->mSpriteScriptObj""|"<<*((void**)&(withSprite->mSpriteScriptObj))<<"): " << objName << " - is a subclass of C++ ""Sprite""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 1256 << " - JS Object (""withSprite->mSpriteScriptObj""|"<<*((void**)&(withSprite->mSpriteScriptObj))<<"): " << objName << " - does not wrap ""Sprite""\n";
                }
            }
            else
            {
                Sprite* obj = dynamic_cast<Sprite*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 1256 << " - JS Object (""withSprite->mSpriteScriptObj""|" << *((void**)&(withSprite->mSpriteScriptObj)) << "): " << objName<<" - wraps C++ ""Sprite"" ("<<(void*)obj<<")\n";
            }
        } );
        SCRIPT_DEBUG_ONLY( if (this->mISpriteCollideHelperScriptObj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 1257 << " - NIL JS Object (" "this->mISpriteCollideHelperScriptObj" "|"<<*((void**)&(this->mISpriteCollideHelperScriptObj))<<")\n";
        }
        else if (!this->mISpriteCollideHelperScriptObj->IsObject())
        {
            std::cerr << __func__<<":"<< 1257 << " - NOT JS Object (" "this->mISpriteCollideHelperScriptObj" "|"<<*((void**)&(this->mISpriteCollideHelperScriptObj))<<") : " << (this->mISpriteCollideHelperScriptObj.IsEmpty() ? "empty" : this->mISpriteCollideHelperScriptObj->IsArray() ? "array" : this->mISpriteCollideHelperScriptObj->IsFunction() ? "function" : this->mISpriteCollideHelperScriptObj->IsStringObject() ? "string (object)" : this->mISpriteCollideHelperScriptObj->IsString() ? "string" : this->mISpriteCollideHelperScriptObj->IsNull() ? "null" : this->mISpriteCollideHelperScriptObj->IsUndefined() ? "undefined" : this->mISpriteCollideHelperScriptObj->IsNumberObject() ? "number (object)" : this->mISpriteCollideHelperScriptObj->IsNumber() ? "number" : this->mISpriteCollideHelperScriptObj->IsBoolean() ? "boolean" : this->mISpriteCollideHelperScriptObj->IsDate() ? "date" : this->mISpriteCollideHelperScriptObj->IsRegExp() ? "regexp" : this->mISpriteCollideHelperScriptObj->IsNativeError() ? "error" : this->mISpriteCollideHelperScriptObj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = this->mISpriteCollideHelperScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                ISpriteCollideHelperWrap* obj__ = dynamic_cast<ISpriteCollideHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<ISpriteCollideHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 1257 << " - JS Object (""this->mISpriteCollideHelperScriptObj""|"<<*((void**)&(this->mISpriteCollideHelperScriptObj))<<"): " << objName << " - is a subclass of C++ ""ISpriteCollideHelper""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 1257 << " - JS Object (""this->mISpriteCollideHelperScriptObj""|"<<*((void**)&(this->mISpriteCollideHelperScriptObj))<<"): " << objName << " - does not wrap ""ISpriteCollideHelper""\n";
                }
            }
            else
            {
                ISpriteCollideHelper* obj = dynamic_cast<ISpriteCollideHelper*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 1257 << " - JS Object (""this->mISpriteCollideHelperScriptObj""|" << *((void**)&(this->mISpriteCollideHelperScriptObj)) << "): " << objName<<" - wraps C++ ""ISpriteCollideHelper"" ("<<(void*)obj<<")\n";
            }
        } );

        v8::Local<v8::Value> resVal;
        v8::Local<v8::Function> func;
        v8::Local<v8::Object> obj_ = v8::Local<v8::Object>::New(isolate, this->mISpriteCollideHelperScriptObj);
        if (!mScriptAllowCollisionFunc.IsEmpty())
        {
            func = v8::Local<v8::Function>::New(isolate, mScriptAllowCollisionFunc);
        }
        else if ((!obj_->IsNull() && obj_->Has(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "allowCollision").ToLocalChecked()).ToChecked()))
        {
            func = v8::Local<v8::Function>::Cast(obj_->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "allowCollision").ToLocalChecked()).ToLocalChecked());
        }
        else
        {
            DEBUG_ONLY(
                v8::String::Utf8Value objectNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                std::cerr << "fatal: ISpriteCollideHelper object " << *objectNameStr << " missing allowCollision() Function!!";
                exit(1);
                )
                return false;
        }
        resVal = ([&]() -> v8::Local<v8::Value>
        {
            if (func.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::MaybeLocal<v8::Value> maybe = func->Call(isolate->GetCurrentContext(), obj_, 2, argv);
                if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());

        if (try_catch.HasCaught())
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling Sprite Collide Helper!!" ); )
                FatalException(try_catch);
            return false;
        }

        return resVal->BooleanValue(isolate);
    }

#ifndef PDG_NO_GUI

    ScriptSpriteDrawHelper::ScriptSpriteDrawHelper(v8::Local<v8::Function> func)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        mScriptDrawFunc.Reset(isolate, func);
    }

    bool ScriptSpriteDrawHelper::draw(Sprite* sprite, Port* port) throw()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::TryCatch try_catch(isolate);

        v8::Local<v8::Value> argv[2];
        argv[0] = v8::Local<v8::Object>::New(isolate, sprite->mSpriteScriptObj);
        argv[1] = v8::Local<v8::Object>::New(isolate, port->mPortScriptObj);

        SCRIPT_DEBUG_ONLY( if (sprite->mSpriteScriptObj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 1312 << " - NIL JS Object (" "sprite->mSpriteScriptObj" "|"<<*((void**)&(sprite->mSpriteScriptObj))<<")\n";
        }
        else if (!sprite->mSpriteScriptObj->IsObject())
        {
            std::cerr << __func__<<":"<< 1312 << " - NOT JS Object (" "sprite->mSpriteScriptObj" "|"<<*((void**)&(sprite->mSpriteScriptObj))<<") : " << (sprite->mSpriteScriptObj.IsEmpty() ? "empty" : sprite->mSpriteScriptObj->IsArray() ? "array" : sprite->mSpriteScriptObj->IsFunction() ? "function" : sprite->mSpriteScriptObj->IsStringObject() ? "string (object)" : sprite->mSpriteScriptObj->IsString() ? "string" : sprite->mSpriteScriptObj->IsNull() ? "null" : sprite->mSpriteScriptObj->IsUndefined() ? "undefined" : sprite->mSpriteScriptObj->IsNumberObject() ? "number (object)" : sprite->mSpriteScriptObj->IsNumber() ? "number" : sprite->mSpriteScriptObj->IsBoolean() ? "boolean" : sprite->mSpriteScriptObj->IsDate() ? "date" : sprite->mSpriteScriptObj->IsRegExp() ? "regexp" : sprite->mSpriteScriptObj->IsNativeError() ? "error" : sprite->mSpriteScriptObj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = sprite->mSpriteScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                SpriteWrap* obj__ = dynamic_cast<SpriteWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<SpriteWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 1312 << " - JS Object (""sprite->mSpriteScriptObj""|"<<*((void**)&(sprite->mSpriteScriptObj))<<"): " << objName << " - is a subclass of C++ ""Sprite""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 1312 << " - JS Object (""sprite->mSpriteScriptObj""|"<<*((void**)&(sprite->mSpriteScriptObj))<<"): " << objName << " - does not wrap ""Sprite""\n";
                }
            }
            else
            {
                Sprite* obj = dynamic_cast<Sprite*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 1312 << " - JS Object (""sprite->mSpriteScriptObj""|" << *((void**)&(sprite->mSpriteScriptObj)) << "): " << objName<<" - wraps C++ ""Sprite"" ("<<(void*)obj<<")\n";
            }
        } );
        SCRIPT_DEBUG_ONLY( if (port->mPortScriptObj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 1313 << " - NIL JS Object (" "port->mPortScriptObj" "|"<<*((void**)&(port->mPortScriptObj))<<")\n";
        }
        else if (!port->mPortScriptObj->IsObject())
        {
            std::cerr << __func__<<":"<< 1313 << " - NOT JS Object (" "port->mPortScriptObj" "|"<<*((void**)&(port->mPortScriptObj))<<") : " << (port->mPortScriptObj.IsEmpty() ? "empty" : port->mPortScriptObj->IsArray() ? "array" : port->mPortScriptObj->IsFunction() ? "function" : port->mPortScriptObj->IsStringObject() ? "string (object)" : port->mPortScriptObj->IsString() ? "string" : port->mPortScriptObj->IsNull() ? "null" : port->mPortScriptObj->IsUndefined() ? "undefined" : port->mPortScriptObj->IsNumberObject() ? "number (object)" : port->mPortScriptObj->IsNumber() ? "number" : port->mPortScriptObj->IsBoolean() ? "boolean" : port->mPortScriptObj->IsDate() ? "date" : port->mPortScriptObj->IsRegExp() ? "regexp" : port->mPortScriptObj->IsNativeError() ? "error" : port->mPortScriptObj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = port->mPortScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                PortWrap* obj__ = dynamic_cast<PortWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<PortWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 1313 << " - JS Object (""port->mPortScriptObj""|"<<*((void**)&(port->mPortScriptObj))<<"): " << objName << " - is a subclass of C++ ""Port""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 1313 << " - JS Object (""port->mPortScriptObj""|"<<*((void**)&(port->mPortScriptObj))<<"): " << objName << " - does not wrap ""Port""\n";
                }
            }
            else
            {
                Port* obj = dynamic_cast<Port*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 1313 << " - JS Object (""port->mPortScriptObj""|" << *((void**)&(port->mPortScriptObj)) << "): " << objName<<" - wraps C++ ""Port"" ("<<(void*)obj<<")\n";
            }
        } );
        SCRIPT_DEBUG_ONLY( if (this->mISpriteDrawHelperScriptObj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 1314 << " - NIL JS Object (" "this->mISpriteDrawHelperScriptObj" "|"<<*((void**)&(this->mISpriteDrawHelperScriptObj))<<")\n";
        }
        else if (!this->mISpriteDrawHelperScriptObj->IsObject())
        {
            std::cerr << __func__<<":"<< 1314 << " - NOT JS Object (" "this->mISpriteDrawHelperScriptObj" "|"<<*((void**)&(this->mISpriteDrawHelperScriptObj))<<") : " << (this->mISpriteDrawHelperScriptObj.IsEmpty() ? "empty" : this->mISpriteDrawHelperScriptObj->IsArray() ? "array" : this->mISpriteDrawHelperScriptObj->IsFunction() ? "function" : this->mISpriteDrawHelperScriptObj->IsStringObject() ? "string (object)" : this->mISpriteDrawHelperScriptObj->IsString() ? "string" : this->mISpriteDrawHelperScriptObj->IsNull() ? "null" : this->mISpriteDrawHelperScriptObj->IsUndefined() ? "undefined" : this->mISpriteDrawHelperScriptObj->IsNumberObject() ? "number (object)" : this->mISpriteDrawHelperScriptObj->IsNumber() ? "number" : this->mISpriteDrawHelperScriptObj->IsBoolean() ? "boolean" : this->mISpriteDrawHelperScriptObj->IsDate() ? "date" : this->mISpriteDrawHelperScriptObj->IsRegExp() ? "regexp" : this->mISpriteDrawHelperScriptObj->IsNativeError() ? "error" : this->mISpriteDrawHelperScriptObj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = this->mISpriteDrawHelperScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                ISpriteDrawHelperWrap* obj__ = dynamic_cast<ISpriteDrawHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<ISpriteDrawHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 1314 << " - JS Object (""this->mISpriteDrawHelperScriptObj""|"<<*((void**)&(this->mISpriteDrawHelperScriptObj))<<"): " << objName << " - is a subclass of C++ ""ISpriteDrawHelper""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 1314 << " - JS Object (""this->mISpriteDrawHelperScriptObj""|"<<*((void**)&(this->mISpriteDrawHelperScriptObj))<<"): " << objName << " - does not wrap ""ISpriteDrawHelper""\n";
                }
            }
            else
            {
                ISpriteDrawHelper* obj = dynamic_cast<ISpriteDrawHelper*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 1314 << " - JS Object (""this->mISpriteDrawHelperScriptObj""|" << *((void**)&(this->mISpriteDrawHelperScriptObj)) << "): " << objName<<" - wraps C++ ""ISpriteDrawHelper"" ("<<(void*)obj<<")\n";
            }
        } );

        v8::Local<v8::Value> resVal;
        v8::Local<v8::Function> func;
        v8::Local<v8::Object> obj_ = v8::Local<v8::Object>::New(isolate, this->mISpriteDrawHelperScriptObj);
        if (!mScriptDrawFunc.IsEmpty())
        {
            func = v8::Local<v8::Function>::New(isolate, mScriptDrawFunc);
        }
        else if ((!obj_->IsNull() && obj_->Has(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "draw").ToLocalChecked()).ToChecked()))
        {
            func = v8::Local<v8::Function>::Cast(obj_->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "draw").ToLocalChecked()).ToLocalChecked());
        }
        else
        {
            DEBUG_ONLY(
                v8::String::Utf8Value objectNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                std::cerr << "fatal: IDrawSpriteHelper object " << *objectNameStr << " missing draw() Function!!";
                exit(1);
                )
                return false;
        }
        resVal = ([&]() -> v8::Local<v8::Value>
        {
            if (func.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::MaybeLocal<v8::Value> maybe = func->Call(isolate->GetCurrentContext(), obj_, 2, argv);
                if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());

        if (try_catch.HasCaught())
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling Sprite Draw Helper!!" ); )
                FatalException(try_catch);
            return false;
        }

        return resVal->BooleanValue(isolate);
    }
#endif

    v8::Local<v8::Value> EncodeBinary(const void *buf, size_t len)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::EscapableHandleScope scope(isolate);
        const uint8 *cbuf = static_cast<const uint8*>(buf);
        uint16* twobytebuf = new uint16[len];
        for (size_t i = 0; i < len; i++)
        {
            twobytebuf[i] = cbuf[i];
        }
        v8::Local<v8::String> chunk = v8::String::NewFromTwoByte(isolate, twobytebuf, v8::NewStringType::kNormal, len).ToLocalChecked();
        delete [] twobytebuf;
        return scope.Escape(chunk);
    }

    void* DecodeBinary(v8::Local<v8::Value> val, size_t* outLen)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::String> str = val->ToString(isolate->GetCurrentContext()).ToLocalChecked();
        size_t buflen = str->Length();
        if (outLen)
        {
            *outLen = buflen;
        }

        uint16_t * twobytebuf = new uint16_t[buflen];
        str->Write(isolate, twobytebuf, 0, buflen);

        char* buf = (char*)std::malloc(buflen);
        for (size_t i = 0; i < buflen; i++)
        {
            unsigned char* bp = reinterpret_cast<unsigned char*>(&twobytebuf[i]);
            buf[i] = *bp;
        }
        delete [] twobytebuf;
        return buf;
    }

    float CallScriptEasingFunc(int which, ms_delta ut, float b, float c, ms_delta ud)
    {
        if (which > gNumCustomEasings)
        {
#ifdef DEBUG
            std::cerr << "logic error: attempting to call an unregistered easing function #"
                << which << "(only "<< gNumCustomEasings <<" custom easings have been"
                " registered via registerEasingFunction())\n";
            exit(1);
#else
            return 0.0f;
#endif
        }
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::TryCatch try_catch(isolate);

        v8::Local<v8::Value> argv[4];
        argv[0] = v8::Local<v8::Value>::New(isolate, v8::Integer::NewFromUnsigned(isolate, ut));
        argv[1] = v8::Local<v8::Value>::New(isolate, v8::Number::New(isolate, b));
        argv[2] = v8::Local<v8::Value>::New(isolate, v8::Number::New(isolate, c));
        argv[3] = v8::Local<v8::Value>::New(isolate, v8::Integer::NewFromUnsigned(isolate, ud));
        v8::Local<v8::Function> easingfunc_ = v8::Local<v8::Function>::New(isolate, s_CustomScriptEasing[which]);

        v8::Local<v8::Value> resVal = ([&]() -> v8::Local<v8::Value>
        {
            if (easingfunc_.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::MaybeLocal<v8::Value> maybe = easingfunc_->Call(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 4, argv);
                if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());

        if (try_catch.HasCaught())
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling Easing Function!!" ); )
                FatalException(try_catch);
            return 0.0f;
        }
        if (!resVal->IsNumber())
        {

#ifdef DEBUG
            std::cerr << "result mismatch: return value from easing Function must be a Number ("
                << v8_GetFunctionName(easingfunc_) << " at "
                << v8_GetFunctionFileAndLine(easingfunc_) << ")\n";
            exit(1);
#else
            return 0.0f;
#endif
        }
        return resVal->NumberValue(isolate->GetCurrentContext()).FromMaybe(0.0);
    }

    void RegisterEasingFunction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(function easingFunc)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""easingFunc"")");
            return;
        }
        v8::Local<v8::Function> easingFunc = v8::Local<v8::Function>::Cast(args[1 -1]);;
        v8::Local<v8::Function> jsEasingFunc = v8::Local<v8::Function>::New(isolate, easingFunc);
        if (gNumCustomEasings >= MAX_CUSTOM_EASINGS)
        {
            std::ostringstream excpt_;
            excpt_ << "Can't register any more custom easing functions!!";
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        else
        {
            s_CustomScriptEasing[gNumCustomEasings].Reset(isolate, jsEasingFunc);
            v8::String::Utf8Value funcNameStr(isolate, easingFunc->GetName()->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            int funcId = NUM_BUILTIN_EASINGS + gNumCustomEasings;
            CallScriptEasingFunc(gNumCustomEasings, 0, 0.0f, 0.0f, 1);
            gNumCustomEasings++;
            v8::Local<v8::Object> bind_ = v8::Local<v8::Object>::New(isolate, s_BindingTarget);
            (void)bind_->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "*funcNameStr").ToLocalChecked(), v8::Integer::New(isolate, funcId)).ToChecked();
            DEBUG_ONLY( OS::_DOUT( "Registered custom easing Function %d as constant name %s [%d]",
                gNumCustomEasings, *funcNameStr, funcId); )
        }
        args.GetReturnValue().SetUndefined();
    }

    void FinishedScriptSetup(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        scriptSetupCompleted();
        args.GetReturnValue().SetUndefined();
    }

    SCRIPT_DEBUG_ONLY(
        static size_t sLastHeapUsed = 0;
        static long sIdleLastHeapReport = OS::getMilliseconds();
        )

        void initBindings(v8::Local<v8::Object> target);

    void initBindings(v8::Local<v8::Object> target)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();

        easingFuncToId(customEasing0);
        easingFuncToId(customEasing1);
        easingFuncToId(customEasing2);
        easingFuncToId(customEasing3);
        easingFuncToId(customEasing4);
        easingFuncToId(customEasing5);
        easingFuncToId(customEasing6);
        easingFuncToId(customEasing7);
        easingFuncToId(customEasing8);
        easingFuncToId(customEasing9);

        s_BindingTarget.Reset(isolate, target);

        MemBlockWrap::Init(isolate, target);;
        FileManagerWrap::Init(isolate, target);;
        LogManagerWrap::Init(isolate, target);;
        ConfigManagerWrap::Init(isolate, target);;
        ResourceManagerWrap::Init(isolate, target);;
        SerializerWrap::Init(isolate, target);;
        DeserializerWrap::Init(isolate, target);;
        ISerializableWrap::Init(isolate, target);;
        IEventHandlerWrap::Init(isolate, target);;
        EventEmitterWrap::Init(isolate, target);;
        EventManagerWrap::Init(isolate, target);;
        TimerManagerWrap::Init(isolate, target);;
        IAnimationHelperWrap::Init(isolate, target);;
        AnimatedWrap::Init(isolate, target);;
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        cpArbiterWrap::Init(isolate, target);;
        cpConstraintWrap::Init(isolate, target);;
        cpSpaceWrap::Init(isolate, target);;
#endif
#ifndef PDG_NO_GUI
        ISpriteDrawHelperWrap::Init(isolate, target);;
#endif
        ISpriteCollideHelperWrap::Init(isolate, target);;
        SpriteWrap::Init(isolate, target);;
        SpriteLayerWrap::Init(isolate, target);;
        TileLayerWrap::Init(isolate, target);;
        ImageWrap::Init(isolate, target);;
        ImageStripWrap::Init(isolate, target);;
        SplineWrap::Init(isolate, target);;
        PolygonWrap::Init(isolate, target);;
        AttributesWrap::Init(isolate, target);;
        ElementRefWrap::Init(isolate, target);;
        DrawingWrap::Init(isolate, target);;
#ifndef PDG_NO_GUI
        FontWrap::Init(isolate, target);;
        PortWrap::Init(isolate, target);;
        GraphicsManagerWrap::Init(isolate, target);;
#endif
#ifndef PDG_NO_SOUND
        SoundWrap::Init(isolate, target);;
        SoundManagerWrap::Init(isolate, target);;
#endif

        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "_idle").ToLocalChecked(), v8::FunctionTemplate::New(isolate, Idle)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "_run").ToLocalChecked(), v8::FunctionTemplate::New(isolate, Run)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "_quit").ToLocalChecked(), v8::FunctionTemplate::New(isolate, Quit)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "_isQuitting").ToLocalChecked(), v8::FunctionTemplate::New(isolate, IsQuitting)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "_finishedScriptSetup").ToLocalChecked(), v8::FunctionTemplate::New(isolate, FinishedScriptSetup)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;

        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "rand").ToLocalChecked(), v8::FunctionTemplate::New(isolate, GameCriticalRandom)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "srand").ToLocalChecked(), v8::FunctionTemplate::New(isolate, Srand)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;

        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "setSerializationDebugMode").ToLocalChecked(), v8::FunctionTemplate::New(isolate, SetSerializationDebugMode)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;

        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "registerEasingFunction").ToLocalChecked(), v8::FunctionTemplate::New(isolate, RegisterEasingFunction)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;

        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getFileManager").ToLocalChecked(), v8::FunctionTemplate::New(isolate, GetFileManager)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getLogManager").ToLocalChecked(), v8::FunctionTemplate::New(isolate, GetLogManager)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getConfigManager").ToLocalChecked(), v8::FunctionTemplate::New(isolate, GetConfigManager)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getResourceManager").ToLocalChecked(), v8::FunctionTemplate::New(isolate, GetResourceManager)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getEventManager").ToLocalChecked(), v8::FunctionTemplate::New(isolate, GetEventManager)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getTimerManager").ToLocalChecked(), v8::FunctionTemplate::New(isolate, GetTimerManager)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "registerSerializableClass").ToLocalChecked(), v8::FunctionTemplate::New(isolate, RegisterSerializableClass)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;

#ifndef PDG_NO_GUI
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getGraphicsManager").ToLocalChecked(), v8::FunctionTemplate::New(isolate, GetGraphicsManager)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
#endif
#ifndef PDG_NO_SOUND
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getSoundManager").ToLocalChecked(), v8::FunctionTemplate::New(isolate, GetSoundManager)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
#endif

        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "createSpriteLayer").ToLocalChecked(), v8::FunctionTemplate::New(isolate, CreateSpriteLayer)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
#ifdef PDG_SPRITER_SUPPORT
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "createSpriteLayerFromSpriterFile").ToLocalChecked(), v8::FunctionTemplate::New(isolate, CreateSpriteLayerFromSpriterFile)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
#endif
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "cleanupLayer").ToLocalChecked(), v8::FunctionTemplate::New(isolate, CleanupLayer)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "createTileLayer").ToLocalChecked(), v8::FunctionTemplate::New(isolate, CreateTileLayer)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "createDrawing").ToLocalChecked(), v8::FunctionTemplate::New(isolate, CreateDrawing)->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();;

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "all_events").ToLocalChecked(), v8::Integer::New(isolate, all_events), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_Shutdown").ToLocalChecked(), v8::Integer::New(isolate, eventType_Shutdown), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_Timer").ToLocalChecked(), v8::Integer::New(isolate, eventType_Timer), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_KeyDown").ToLocalChecked(), v8::Integer::New(isolate, eventType_KeyDown), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_KeyUp").ToLocalChecked(), v8::Integer::New(isolate, eventType_KeyUp), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_KeyPress").ToLocalChecked(), v8::Integer::New(isolate, eventType_KeyPress), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_MouseDown").ToLocalChecked(), v8::Integer::New(isolate, eventType_MouseDown), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_MouseUp").ToLocalChecked(), v8::Integer::New(isolate, eventType_MouseUp), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_MouseMove").ToLocalChecked(), v8::Integer::New(isolate, eventType_MouseMove), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_MouseEnter").ToLocalChecked(), v8::Integer::New(isolate, eventType_MouseEnter), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_MouseLeave").ToLocalChecked(), v8::Integer::New(isolate, eventType_MouseLeave), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_PortResized").ToLocalChecked(), v8::Integer::New(isolate, eventType_PortResized), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_ScrollWheel").ToLocalChecked(), v8::Integer::New(isolate, eventType_ScrollWheel), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_SpriteTouch").ToLocalChecked(), v8::Integer::New(isolate, eventType_SpriteTouch), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_SpriteAnimate").ToLocalChecked(), v8::Integer::New(isolate, eventType_SpriteAnimate), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_SpriteLayer").ToLocalChecked(), v8::Integer::New(isolate, eventType_SpriteLayer), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_SpriteCollide").ToLocalChecked(), v8::Integer::New(isolate, eventType_SpriteCollide), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_SpriteBreak").ToLocalChecked(), v8::Integer::New(isolate, eventType_SpriteBreak), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_SoundEvent").ToLocalChecked(), v8::Integer::New(isolate, eventType_SoundEvent), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "eventType_PortDraw").ToLocalChecked(), v8::Integer::New(isolate, eventType_PortDraw), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "soundEvent_DonePlaying").ToLocalChecked(), v8::Integer::New(isolate, soundEvent_DonePlaying), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "soundEvent_Looping").ToLocalChecked(), v8::Integer::New(isolate, soundEvent_Looping), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "soundEvent_FailedToPlay").ToLocalChecked(), v8::Integer::New(isolate, soundEvent_FailedToPlay), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Break").ToLocalChecked(), v8::Integer::New(isolate, key_Break), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Home").ToLocalChecked(), v8::Integer::New(isolate, key_Home), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_End").ToLocalChecked(), v8::Integer::New(isolate, key_End), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Clear").ToLocalChecked(), v8::Integer::New(isolate, key_Clear), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Help").ToLocalChecked(), v8::Integer::New(isolate, key_Help), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Pause").ToLocalChecked(), v8::Integer::New(isolate, key_Pause), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Mute").ToLocalChecked(), v8::Integer::New(isolate, key_Mute), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Backspace").ToLocalChecked(), v8::Integer::New(isolate, key_Backspace), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Delete").ToLocalChecked(), v8::Integer::New(isolate, key_Delete), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Tab").ToLocalChecked(), v8::Integer::New(isolate, key_Tab), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_PageUp").ToLocalChecked(), v8::Integer::New(isolate, key_PageUp), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_PageDown").ToLocalChecked(), v8::Integer::New(isolate, key_PageDown), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Return").ToLocalChecked(), v8::Integer::New(isolate, key_Return), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Enter").ToLocalChecked(), v8::Integer::New(isolate, key_Enter), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_F1").ToLocalChecked(), v8::Integer::New(isolate, key_F1), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_F2").ToLocalChecked(), v8::Integer::New(isolate, key_F2), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_F3").ToLocalChecked(), v8::Integer::New(isolate, key_F3), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_F4").ToLocalChecked(), v8::Integer::New(isolate, key_F4), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_F5").ToLocalChecked(), v8::Integer::New(isolate, key_F5), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_F6").ToLocalChecked(), v8::Integer::New(isolate, key_F6), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_F7").ToLocalChecked(), v8::Integer::New(isolate, key_F7), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_F8").ToLocalChecked(), v8::Integer::New(isolate, key_F8), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_F9").ToLocalChecked(), v8::Integer::New(isolate, key_F9), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_F10").ToLocalChecked(), v8::Integer::New(isolate, key_F10), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_F11").ToLocalChecked(), v8::Integer::New(isolate, key_F11), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_F12").ToLocalChecked(), v8::Integer::New(isolate, key_F12), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_FirstF").ToLocalChecked(), v8::Integer::New(isolate, key_FirstF), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_LastF").ToLocalChecked(), v8::Integer::New(isolate, key_LastF), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Insert").ToLocalChecked(), v8::Integer::New(isolate, key_Insert), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_Escape").ToLocalChecked(), v8::Integer::New(isolate, key_Escape), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_LeftArrow").ToLocalChecked(), v8::Integer::New(isolate, key_LeftArrow), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_RightArrow").ToLocalChecked(), v8::Integer::New(isolate, key_RightArrow), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_UpArrow").ToLocalChecked(), v8::Integer::New(isolate, key_UpArrow), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_DownArrow").ToLocalChecked(), v8::Integer::New(isolate, key_DownArrow), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "key_FirstPrintable").ToLocalChecked(), v8::Integer::New(isolate, key_FirstPrintable), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode_LeftShift").ToLocalChecked(), v8::Integer::New(isolate, keyCode_LeftShift), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode_RightShift").ToLocalChecked(), v8::Integer::New(isolate, keyCode_RightShift), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode_LeftControl").ToLocalChecked(), v8::Integer::New(isolate, keyCode_LeftControl), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode_RightControl").ToLocalChecked(), v8::Integer::New(isolate, keyCode_RightControl), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode_LeftAlt").ToLocalChecked(), v8::Integer::New(isolate, keyCode_LeftAlt), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode_RightAlt").ToLocalChecked(), v8::Integer::New(isolate, keyCode_RightAlt), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode_LeftMeta").ToLocalChecked(), v8::Integer::New(isolate, keyCode_LeftMeta), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode_RightMeta").ToLocalChecked(), v8::Integer::New(isolate, keyCode_RightMeta), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode_Shift").ToLocalChecked(), v8::Integer::New(isolate, keyCode_Shift), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode_Control").ToLocalChecked(), v8::Integer::New(isolate, keyCode_Control), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode_Alt").ToLocalChecked(), v8::Integer::New(isolate, keyCode_Alt), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "keyCode_Meta").ToLocalChecked(), v8::Integer::New(isolate, keyCode_Meta), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "screenPos_Normal").ToLocalChecked(), v8::Integer::New(isolate, screenPos_Normal), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "screenPos_Rotated180").ToLocalChecked(), v8::Integer::New(isolate, screenPos_Rotated180), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "screenPos_Rotated90Clockwise").ToLocalChecked(), v8::Integer::New(isolate, screenPos_Rotated90Clockwise), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "screenPos_Rotated90CounterClockwise").ToLocalChecked(), v8::Integer::New(isolate, screenPos_Rotated90CounterClockwise), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "screenPos_FaceUp").ToLocalChecked(), v8::Integer::New(isolate, screenPos_FaceUp), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "screenPos_FaceDown").ToLocalChecked(), v8::Integer::New(isolate, screenPos_FaceDown), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

#ifndef PDG_NO_GUI
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "textStyle_Plain").ToLocalChecked(), v8::Integer::New(isolate, textStyle_Plain), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "textStyle_Bold").ToLocalChecked(), v8::Integer::New(isolate, textStyle_Bold), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "textStyle_Italic").ToLocalChecked(), v8::Integer::New(isolate, textStyle_Italic), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "textStyle_Underline").ToLocalChecked(), v8::Integer::New(isolate, textStyle_Underline), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "textStyle_Centered").ToLocalChecked(), v8::Integer::New(isolate, textStyle_Centered), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "textStyle_LeftJustified").ToLocalChecked(), v8::Integer::New(isolate, textStyle_LeftJustified), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "textStyle_RightJustified").ToLocalChecked(), v8::Integer::New(isolate, textStyle_RightJustified), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
#endif

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "lineStyle_Auto").ToLocalChecked(), v8::Integer::New(isolate, lineStyle_Auto), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "lineStyle_None").ToLocalChecked(), v8::Integer::New(isolate, lineStyle_None), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "lineStyle_Solid").ToLocalChecked(), v8::Integer::New(isolate, lineStyle_Solid), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "lineStyle_Dashed").ToLocalChecked(), v8::Integer::New(isolate, lineStyle_Dashed), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "lineStyle_Dotted").ToLocalChecked(), v8::Integer::New(isolate, lineStyle_Dotted), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "lineStyle_DashDot").ToLocalChecked(), v8::Integer::New(isolate, lineStyle_DashDot), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "lineStyle_DashDotDot").ToLocalChecked(), v8::Integer::New(isolate, lineStyle_DashDotDot), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "blendMode_Normal").ToLocalChecked(), v8::Integer::New(isolate, blendMode_Normal), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "blendMode_Additive").ToLocalChecked(), v8::Integer::New(isolate, blendMode_Additive), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "blendMode_Multiply").ToLocalChecked(), v8::Integer::New(isolate, blendMode_Multiply), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "blendMode_Screen").ToLocalChecked(), v8::Integer::New(isolate, blendMode_Screen), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "blendMode_Darken").ToLocalChecked(), v8::Integer::New(isolate, blendMode_Darken), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "blendMode_Lighten").ToLocalChecked(), v8::Integer::New(isolate, blendMode_Lighten), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type_Line").ToLocalChecked(), v8::Integer::New(isolate, type_Line), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type_Spline").ToLocalChecked(), v8::Integer::New(isolate, type_Spline), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type_Arc").ToLocalChecked(), v8::Integer::New(isolate, type_Arc), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type_Rect").ToLocalChecked(), v8::Integer::New(isolate, type_Rect), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type_Quad").ToLocalChecked(), v8::Integer::New(isolate, type_Quad), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type_Polygon").ToLocalChecked(), v8::Integer::New(isolate, type_Polygon), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type_Ellipse").ToLocalChecked(), v8::Integer::New(isolate, type_Ellipse), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type_Image").ToLocalChecked(), v8::Integer::New(isolate, type_Image), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type_ImageStrip").ToLocalChecked(), v8::Integer::New(isolate, type_ImageStrip), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type_Drawing").ToLocalChecked(), v8::Integer::New(isolate, type_Drawing), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "gradientType_None").ToLocalChecked(), v8::Integer::New(isolate, gradientType_None), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "gradientType_Linear").ToLocalChecked(), v8::Integer::New(isolate, gradientType_Linear), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "gradientType_Radial").ToLocalChecked(), v8::Integer::New(isolate, gradientType_Radial), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "fit_None").ToLocalChecked(), v8::Integer::New(isolate, fit_None), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "fit_Fill").ToLocalChecked(), v8::Integer::New(isolate, fit_Fill), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "fit_Height").ToLocalChecked(), v8::Integer::New(isolate, fit_Height), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "fit_Width").ToLocalChecked(), v8::Integer::New(isolate, fit_Width), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "fit_Inside").ToLocalChecked(), v8::Integer::New(isolate, fit_Inside), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "fit_Overflow").ToLocalChecked(), v8::Integer::New(isolate, fit_Overflow), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "fit_Clipped").ToLocalChecked(), v8::Integer::New(isolate, fit_Clipped), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "fit_TileX").ToLocalChecked(), v8::Integer::New(isolate, fit_TileX), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "fit_TileY").ToLocalChecked(), v8::Integer::New(isolate, fit_TileY), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "fit_Tile").ToLocalChecked(), v8::Integer::New(isolate, fit_Tile), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "init_CreateUniqueNewFile").ToLocalChecked(), v8::Integer::New(isolate, LogManager::init_CreateUniqueNewFile), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "init_OverwriteExisting").ToLocalChecked(), v8::Integer::New(isolate, LogManager::init_OverwriteExisting), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "init_AppendToExisting").ToLocalChecked(), v8::Integer::New(isolate, LogManager::init_AppendToExisting), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "init_StdOut").ToLocalChecked(), v8::Integer::New(isolate, LogManager::init_StdOut), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "init_StdErr").ToLocalChecked(), v8::Integer::New(isolate, LogManager::init_StdErr), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "duration_Constant").ToLocalChecked(), v8::Integer::New(isolate, duration_Constant), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "duration_Instantaneous").ToLocalChecked(), v8::Integer::New(isolate, duration_Instantaneous), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "animate_StartToEnd").ToLocalChecked(), v8::Integer::New(isolate, Sprite::animate_StartToEnd), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "animate_EndToStart").ToLocalChecked(), v8::Integer::New(isolate, Sprite::animate_EndToStart), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "animate_Unidirectional").ToLocalChecked(), v8::Integer::New(isolate, Sprite::animate_Unidirectional), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "animate_Bidirectional").ToLocalChecked(), v8::Integer::New(isolate, Sprite::animate_Bidirectional), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "animate_NoLooping").ToLocalChecked(), v8::Integer::New(isolate, Sprite::animate_NoLooping), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "animate_Looping").ToLocalChecked(), v8::Integer::New(isolate, Sprite::animate_Looping), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "start_FromFirstFrame").ToLocalChecked(), v8::Integer::New(isolate, Sprite::start_FromFirstFrame), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "start_FromLastFrame").ToLocalChecked(), v8::Integer::New(isolate, Sprite::start_FromLastFrame), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "all_Frames").ToLocalChecked(), v8::Integer::New(isolate, Sprite::all_Frames), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_CollideSprite").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_CollideSprite), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_CollideWall").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_CollideWall), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_Offscreen").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_Offscreen), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_Onscreen").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_Onscreen), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_ExitLayer").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_ExitLayer), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_AnimationLoop").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_AnimationLoop), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_AnimationEnd").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_AnimationEnd), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_FadeComplete").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_FadeComplete), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_FadeInComplete").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_FadeInComplete), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_FadeOutComplete").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_FadeOutComplete), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_JointBreak").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_JointBreak), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_SpriterTrigger").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_SpriterTrigger), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_AnimationBlendComplete").ToLocalChecked(), v8::Integer::New(isolate, Sprite::action_AnimationBlendComplete), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "touch_MouseEnter").ToLocalChecked(), v8::Integer::New(isolate, Sprite::touch_MouseEnter), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "touch_MouseLeave").ToLocalChecked(), v8::Integer::New(isolate, Sprite::touch_MouseLeave), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "touch_MouseDown").ToLocalChecked(), v8::Integer::New(isolate, Sprite::touch_MouseDown), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "touch_MouseUp").ToLocalChecked(), v8::Integer::New(isolate, Sprite::touch_MouseUp), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "touch_MouseClick").ToLocalChecked(), v8::Integer::New(isolate, Sprite::touch_MouseClick), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "collide_None").ToLocalChecked(), v8::Integer::New(isolate, Sprite::collide_None), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "collide_Point").ToLocalChecked(), v8::Integer::New(isolate, Sprite::collide_Point), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "collide_BoundingBox").ToLocalChecked(), v8::Integer::New(isolate, Sprite::collide_BoundingBox), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "collide_CollisionRadius").ToLocalChecked(), v8::Integer::New(isolate, Sprite::collide_CollisionRadius), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "collide_AlphaChannel").ToLocalChecked(), v8::Integer::New(isolate, Sprite::collide_AlphaChannel), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "collide_SpriterCollisionBox").ToLocalChecked(), v8::Integer::New(isolate, Sprite::collide_SpriterCollisionBox), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "collide_Last").ToLocalChecked(), v8::Integer::New(isolate, Sprite::collide_Last), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_ErasePort").ToLocalChecked(), v8::Integer::New(isolate, SpriteLayer::action_ErasePort), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_PreDrawLayer").ToLocalChecked(), v8::Integer::New(isolate, SpriteLayer::action_PreDrawLayer), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_PostDrawLayer").ToLocalChecked(), v8::Integer::New(isolate, SpriteLayer::action_PostDrawLayer), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_DrawPortComplete").ToLocalChecked(), v8::Integer::New(isolate, SpriteLayer::action_DrawPortComplete), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_AnimationStart").ToLocalChecked(), v8::Integer::New(isolate, SpriteLayer::action_AnimationStart), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_PreAnimateLayer").ToLocalChecked(), v8::Integer::New(isolate, SpriteLayer::action_PreAnimateLayer), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_PostAnimateLayer").ToLocalChecked(), v8::Integer::New(isolate, SpriteLayer::action_PostAnimateLayer), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_AnimationComplete").ToLocalChecked(), v8::Integer::New(isolate, SpriteLayer::action_AnimationComplete), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_ZoomComplete").ToLocalChecked(), v8::Integer::New(isolate, SpriteLayer::action_ZoomComplete), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_LayerFadeInComplete").ToLocalChecked(), v8::Integer::New(isolate, SpriteLayer::action_FadeInComplete), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "action_LayerFadeOutComplete").ToLocalChecked(), v8::Integer::New(isolate, SpriteLayer::action_FadeOutComplete), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "facing_North").ToLocalChecked(), v8::Integer::New(isolate, TileLayer::facing_North), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "facing_East").ToLocalChecked(), v8::Integer::New(isolate, TileLayer::facing_East), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "facing_South").ToLocalChecked(), v8::Integer::New(isolate, TileLayer::facing_South), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "facing_West").ToLocalChecked(), v8::Integer::New(isolate, TileLayer::facing_West), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "facing_Ignore").ToLocalChecked(), v8::Integer::New(isolate, TileLayer::facing_Ignore), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "flipped_None").ToLocalChecked(), v8::Integer::New(isolate, TileLayer::flipped_None), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "flipped_Horizontal").ToLocalChecked(), v8::Integer::New(isolate, TileLayer::flipped_Horizontal), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "flipped_Vertical").ToLocalChecked(), v8::Integer::New(isolate, TileLayer::flipped_Vertical), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "flipped_Both").ToLocalChecked(), v8::Integer::New(isolate, TileLayer::flipped_Both), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "flipped_Ignore").ToLocalChecked(), v8::Integer::New(isolate, TileLayer::flipped_Ignore), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "timer_OneShot").ToLocalChecked(), v8::Boolean::New(isolate, timer_OneShot), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "timer_Repeating").ToLocalChecked(), v8::Boolean::New(isolate, timer_Repeating), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "timer_Never").ToLocalChecked(), v8::Integer::New(isolate, timer_Never), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "linearTween").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::linearTween), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInQuad").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInQuad), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeOutQuad").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeOutQuad), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInOutQuad").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInOutQuad), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInCubic").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInCubic), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeOutCubic").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeOutCubic), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInOutCubic").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInOutCubic), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInQuart").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInQuart), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeOutQuart").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeOutQuart), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInOutCubic").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInOutCubic), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInQuint").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInQuint), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeOutQuint").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeOutQuint), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInOutQuint").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInOutQuint), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInSine").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInSine), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeOutSine").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeOutSine), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInOutSine").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInOutSine), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInExpo").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInExpo), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeOutExpo").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeOutExpo), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInOutExpo").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInOutExpo), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInCirc").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInCirc), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeOutCirc").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeOutCirc), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInOutCirc").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInOutCirc), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInBounce").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInBounce), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeOutBounce").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeOutBounce), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInOutBounce").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInOutBounce), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInBack").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInBack), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeOutBack").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeOutBack), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "easeInOutBack").ToLocalChecked(), v8::Integer::New(isolate, EasingFuncRef::easeInOutBack), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_Positions").ToLocalChecked(), v8::Integer::New(isolate, ser_Positions), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_ZOrder").ToLocalChecked(), v8::Integer::New(isolate, ser_ZOrder), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_Sizes").ToLocalChecked(), v8::Integer::New(isolate, ser_Sizes), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_Animations").ToLocalChecked(), v8::Integer::New(isolate, ser_Animations), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_Motion").ToLocalChecked(), v8::Integer::New(isolate, ser_Motion), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_Forces").ToLocalChecked(), v8::Integer::New(isolate, ser_Forces), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_Physics").ToLocalChecked(), v8::Integer::New(isolate, ser_Physics), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_LayerDraw").ToLocalChecked(), v8::Integer::New(isolate, ser_LayerDraw), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_ImageRefs").ToLocalChecked(), v8::Integer::New(isolate, ser_ImageRefs), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_SCMLRefs").ToLocalChecked(), v8::Integer::New(isolate, ser_SCMLRefs), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_HelperRefs").ToLocalChecked(), v8::Integer::New(isolate, ser_HelperRefs), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_HelperObjs").ToLocalChecked(), v8::Integer::New(isolate, ser_HelperObjs), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_InitialData").ToLocalChecked(), v8::Integer::New(isolate, ser_InitialData), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_Micro").ToLocalChecked(), v8::Integer::New(isolate, ser_Micro), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_Update").ToLocalChecked(), v8::Integer::New(isolate, ser_Update), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "ser_Full").ToLocalChecked(), v8::Integer::New(isolate, ser_Full), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "spline_Hermite").ToLocalChecked(), v8::Integer::New(isolate, 1), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "spline_Cardinal").ToLocalChecked(), v8::Integer::New(isolate, 2), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "spline_UniformB").ToLocalChecked(), v8::Integer::New(isolate, 3), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "spline_CubicBezier").ToLocalChecked(), v8::Integer::New(isolate, 4), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "spline_TCB").ToLocalChecked(), v8::Integer::New(isolate, 5), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();
        target->DefineOwnProperty(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "spline_NaturalCubic").ToLocalChecked(), v8::Integer::New(isolate, 6), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete)).ToChecked();

#ifdef PDG_USE_CHIPMUNK_PHYSICS
        cpArbiterWrap::Init(isolate, target);;
        cpConstraintWrap::Init(isolate, target);;
        cpSpaceWrap::Init(isolate, target);;
#endif
    }

    void CreateSingletons()
    {

        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        FileManagerWrap::GetScriptSingletonInstance(isolate);

        LogManagerWrap::getSingletonInstance();
        ConfigManagerWrap::getSingletonInstance();
        ResourceManagerWrap::getSingletonInstance();
        EventManagerWrap::getSingletonInstance();
        TimerManagerWrap::getSingletonInstance();
#ifndef PDG_NO_GUI
        GraphicsManagerWrap::getSingletonInstance();
#endif
#ifndef PDG_NO_SOUND
        SoundManagerWrap::getSingletonInstance();
#endif
#ifndef PDG_NO_NETWORK
        NetworkManager::getSingletonInstance();
#endif
    }

}


extern "C" void pdg_LibContainerDoIdle()
{

    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Platform* platform = pdg::v8_GetPlatform();
    if (platform && platform->IdleTasksEnabled(isolate))
    {
        v8::platform::RunIdleTasks(platform, isolate, 0.01);
    }

    SCRIPT_DEBUG_ONLY(
        if ((sIdleLastHeapReport + 1000) < OS::getMilliseconds())
    {
        v8::HeapStatistics hs;
            v8::V8::GetHeapStatistics(&hs);
            long deltaUsed = hs.used_heap_size() - sLastHeapUsed;
            sLastHeapUsed = hs.used_heap_size();
            if (deltaUsed != 0)
        {
            std::cout << "heap: delta ["<<deltaUsed<<"] used ["<<sLastHeapUsed<<"] total ["<<hs.total_heap_size()
                <<"] executable ["<<hs.total_heap_size_executable()
                <<"]  limit ["<<hs.heap_size_limit()<<"]\n";
                sIdleLastHeapReport = OS::getMilliseconds();
        }
    }
    )
}
