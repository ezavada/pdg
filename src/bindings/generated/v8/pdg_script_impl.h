// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/pdg_script_impl.h
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



#ifndef PDG_DEBUG_SCRIPTING

#define SCRIPT_DEBUG_ONLY(_expression)
#else
#define SCRIPT_DEBUG_ONLY DEBUG_ONLY
#endif

#ifndef PDG_SCRIPT_IMPL_H_INCLUDED
#define PDG_SCRIPT_IMPL_H_INCLUDED

#include "pdg_project.h"

#include "pdg_script.h"

#ifndef PDG_NO_APP_FRAMEWORK
#define PDG_NO_APP_FRAMEWORK
#endif
#include "pdg/framework.h"

#include <cstdlib>
#include <sstream>

namespace pdg
{

    extern bool s_HaveSavedError;
    extern v8::Persistent<v8::Value> s_SavedError;

    AnimationEvaluator MakeAnimationEvaluator(v8::Local<v8::Function> evaluator);
    AnimationEventHandler MakeAnimationEventHandler(v8::Local<v8::Function> handler);
#ifdef PDG_USING_V8
    void ClearAnimationEvaluatorCallbacks();
#endif

    v8::Local<v8::Value> MakeUint8Array(const void* data, size_t size);
    bool IsUint8Array(v8::Local<v8::Value> value);
    bool GetUint8ArrayData(v8::Local<v8::Value> value, const uint8*& data, size_t& size);

#ifdef PDG_USING_V8
    AnimatedBase* V8_GetAnimationTarget(v8::Isolate* isolate, v8::Local<v8::Value> value);
    ISerializable* V8_GetSerializable(v8::Isolate* isolate, v8::Local<v8::Value> value);
#endif

#ifdef PDG_USING_JAVASCRIPT_CORE
    AnimatedBase* JSC_GetAnimationTarget(JSContextRef ctx, JSValueRef value);
    ISerializable* JSC_GetSerializable(JSContextRef ctx, JSValueRef value);
#endif

    const bool kNoErrorOnFail = true;

    void CreateSingletons();

    class ScriptAnimationHelper : public pdg::IAnimationHelper
    {
        public:
            ScriptAnimationHelper();
            ScriptAnimationHelper(v8::Local<v8::Function> javascriptAnimateFunc);
            bool animate(AnimatedBase* what, double deltaSeconds) noexcept override;
            ~ScriptAnimationHelper() override;
            void initializeScriptObject();
            void retainForAnimation() override;
            void releaseForAnimation() override;
        protected:
            unsigned mAnimationRetains = 0;
            v8::Persistent<v8::Function> mScriptAnimateFunc;
    };

    class ScriptEventHandler : public pdg::RefCountedImpl< pdg::IEventHandler >
    {
        public:
            ScriptEventHandler();
            ScriptEventHandler(v8::Local<v8::Function> javascriptHandlerFunc);
            bool handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept;
        protected:
            v8::Persistent<v8::Function> mScriptHandlerFunc;
    };

    class ScriptAnimationEventHandler : public pdg::RefCountedImpl< pdg::IEventHandler >
    {
        public:
            ScriptAnimationEventHandler();
            ScriptAnimationEventHandler(v8::Local<v8::Function> javascriptHandlerFunc, long expectedAction);
            bool handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept;
        protected:
            v8::Persistent<v8::Function> mScriptHandlerFunc;
            long mExpectedAction;
    };

    class ScriptTouchEventHandler : public pdg::RefCountedImpl< pdg::IEventHandler >
    {
        public:
            ScriptTouchEventHandler();
            ScriptTouchEventHandler(v8::Local<v8::Function> javascriptHandlerFunc, long expectedAction);
            bool handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept;
        protected:
            v8::Persistent<v8::Function> mScriptHandlerFunc;
            long mExpectedAction;
    };

    class ScriptLayerEventHandler : public pdg::RefCountedImpl< pdg::IEventHandler >
    {
        public:
            ScriptLayerEventHandler();
            ScriptLayerEventHandler(v8::Local<v8::Function> javascriptHandlerFunc, long expectedAction);
            bool handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept;
        protected:
            v8::Persistent<v8::Function> mScriptHandlerFunc;
            long mExpectedAction;
    };

    class ScriptSerializable : public pdg::ISerializable
    {
        public:
            ScriptSerializable();
            ScriptSerializable(
                v8::Local<v8::Function> javascriptGetSerializedSizeFunc,
                v8::Local<v8::Function> javascriptSerializeFunc,
                v8::Local<v8::Function> javascriptDeserializeFunc,
                v8::Local<v8::Function> javascriptGetMyClassTagFunc
                );
            virtual uint32 getSerializedSize(ISerializer* serializer) const;
            virtual void serialize(ISerializer* serializer) const;
            virtual void deserialize(IDeserializer* deserializer);
            virtual uint32 getMyClassTag() const;
        protected:
            v8::Persistent<v8::Function> mScriptGetSerializedSizeFunc;
            v8::Persistent<v8::Function> mScriptSerializeFunc;
            v8::Persistent<v8::Function> mScriptDeserializeFunc;
            v8::Persistent<v8::Function> mScriptGetMyClassTagFunc;
    };

#ifndef PDG_NO_GUI

    class ScriptSpriteDrawHelper : public pdg::ISpriteDrawHelper
    {
        public:
            ScriptSpriteDrawHelper();
            ScriptSpriteDrawHelper(v8::Local<v8::Function> javascriptDrawFunc);
            bool draw(Sprite* sprite, Port* port) noexcept;
        protected:
            v8::Persistent<v8::Function> mScriptDrawFunc;
    };
#endif

    float CallScriptEasingFunc(int which, double ut, float b, float c, double ud);

    extern float customEasing0(double ut, float b, float c, double ud);
    extern float customEasing1(double ut, float b, float c, double ud);
    extern float customEasing2(double ut, float b, float c, double ud);
    extern float customEasing3(double ut, float b, float c, double ud);
    extern float customEasing4(double ut, float b, float c, double ud);
    extern float customEasing5(double ut, float b, float c, double ud);
    extern float customEasing6(double ut, float b, float c, double ud);
    extern float customEasing7(double ut, float b, float c, double ud);
    extern float customEasing8(double ut, float b, float c, double ud);
    extern float customEasing9(double ut, float b, float c, double ud);

    namespace EasingFuncRef
    {
        enum
        {
            EASING_FUNC_LIST
        };
    }

}
#endif
