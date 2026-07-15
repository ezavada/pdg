// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/core/core_bindings.h
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



#ifndef PDG_CORE_BINDINGS_H_INCLUDED
#define PDG_CORE_BINDINGS_H_INCLUDED

#include "pdg_project.h"

#include "pdg_script_impl.h"
#include "pdg_script_interface.h"

#ifndef PDG_NO_APP_FRAMEWORK
#define PDG_NO_APP_FRAMEWORK
#endif
#include "pdg/framework.h"

#include <cstdlib>

namespace pdg
{

    IEventHandler* New_IEventHandler(const v8::FunctionCallbackInfo<v8::Value>& args);

    class IEventHandlerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            IEventHandler* getCppObject() { return cppPtr_; }
        protected:
            IEventHandler* cppPtr_;

            IEventHandlerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~IEventHandlerWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, IEventHandler* cppObj);
            IEventHandlerWrap(IEventHandler* obj) : cppPtr_(obj) {}

    };

    EventEmitter* New_EventEmitter(const v8::FunctionCallbackInfo<v8::Value>& args);

    class EventEmitterWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            EventEmitter* getCppObject() { return cppPtr_; }
        protected:
            EventEmitter* cppPtr_;

            EventEmitterWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~EventEmitterWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, EventEmitter* cppObj);
            EventEmitterWrap(EventEmitter* obj) : cppPtr_(obj) {}

            static void AddHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Clear (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BlockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UnblockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);

    };

    ConfigManager* New_ConfigManager(const v8::FunctionCallbackInfo<v8::Value>& args);

    class ConfigManagerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            ConfigManager* getCppObject() { return cppPtr_; }
        protected:
            ConfigManager* cppPtr_;

            ConfigManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~ConfigManagerWrap();

        public:
            static ConfigManager* getSingletonInstance();
        public:
            static v8::Local<v8::Object> GetScriptSingletonInstance(v8::Isolate* isolate);
        protected:
            static v8::Persistent<v8::Object> instance_;
            static bool instanced_;

            static void UseConfig (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetConfigString (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetConfigLong (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetConfigFloat (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetConfigBool (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetConfigString (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetConfigLong (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetConfigFloat (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetConfigBool (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    LogManager* New_LogManager(const v8::FunctionCallbackInfo<v8::Value>& args);

    class LogManagerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            LogManager* getCppObject() { return cppPtr_; }
        protected:
            LogManager* cppPtr_;

            LogManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~LogManagerWrap();

        public:
            static LogManager* getSingletonInstance();
        public:
            static v8::Local<v8::Object> GetScriptSingletonInstance(v8::Isolate* isolate);
        protected:
            static v8::Persistent<v8::Object> instance_;
            static bool instanced_;

            static void GetLogLevel (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLogLevel (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Initialize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void WriteLogEntry (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BinaryDump (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    EventManager* New_EventManager(const v8::FunctionCallbackInfo<v8::Value>& args);

    class EventManagerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            EventManager* getCppObject() { return cppPtr_; }
        protected:
            EventManager* cppPtr_;

            EventManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~EventManagerWrap();

        public:
            static EventManager* getSingletonInstance();
        public:
            static v8::Local<v8::Object> GetScriptSingletonInstance(v8::Isolate* isolate);
        protected:
            static v8::Persistent<v8::Object> instance_;
            static bool instanced_;

            static void AddHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Clear (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BlockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UnblockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsKeyDown (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsRawKeyDown (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsButtonDown (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetDeviceOrientation (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    TimerManager* New_TimerManager(const v8::FunctionCallbackInfo<v8::Value>& args);

    class TimerManagerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            TimerManager* getCppObject() { return cppPtr_; }
        protected:
            TimerManager* cppPtr_;

            TimerManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~TimerManagerWrap();

        public:
            static TimerManager* getSingletonInstance();
        public:
            static v8::Local<v8::Object> GetScriptSingletonInstance(v8::Isolate* isolate);
        protected:
            static v8::Persistent<v8::Object> instance_;
            static bool instanced_;

            static void AddHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Clear (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BlockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UnblockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartTimer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CancelTimer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CancelAllTimers (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DelayTimer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DelayTimerUntil (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Pause (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Unpause (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsPaused (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PauseTimer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UnpauseTimer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsTimerPaused (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWhenTimerFiresNext (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMilliseconds (const v8::FunctionCallbackInfo<v8::Value>& args);
    };
#endif

}
