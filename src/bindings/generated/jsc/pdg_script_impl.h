// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/pdg_script_impl.h
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
    extern std::ostringstream s_SavedError;

    AnimationEvaluator MakeAnimationEvaluator(JSObjectRef evaluator);
    AnimationEventHandler MakeAnimationEventHandler(JSObjectRef handler);
#ifdef PDG_USING_V8
    void ClearAnimationEvaluatorCallbacks();
#endif

    JSValueRef MakeUint8Array(const void* data, size_t size);
    bool IsUint8Array(JSValueRef value);
    bool GetUint8ArrayData(JSValueRef value, const uint8*& data, size_t& size);

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
            ScriptAnimationHelper(JSObjectRef javascriptAnimateFunc);
            bool animate(AnimatedBase* what, double deltaSeconds) noexcept override;
            ~ScriptAnimationHelper() override;
            void initializeScriptObject();
            void retainForAnimation() override;
            void releaseForAnimation() override;
        protected:
            unsigned mAnimationRetains = 0;
            JSObjectRef mScriptAnimateFunc;
    };

    class ScriptEventHandler : public pdg::RefCountedImpl< pdg::IEventHandler >
    {
        public:
            ScriptEventHandler();
            ScriptEventHandler(JSObjectRef javascriptHandlerFunc);
            bool handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept;
        protected:
            JSObjectRef mScriptHandlerFunc;
    };

    class ScriptAnimationEventHandler : public pdg::RefCountedImpl< pdg::IEventHandler >
    {
        public:
            ScriptAnimationEventHandler();
            ScriptAnimationEventHandler(JSObjectRef javascriptHandlerFunc, long expectedAction);
            bool handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept;
        protected:
            JSObjectRef mScriptHandlerFunc;
            long mExpectedAction;
    };

    class ScriptTouchEventHandler : public pdg::RefCountedImpl< pdg::IEventHandler >
    {
        public:
            ScriptTouchEventHandler();
            ScriptTouchEventHandler(JSObjectRef javascriptHandlerFunc, long expectedAction);
            bool handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept;
        protected:
            JSObjectRef mScriptHandlerFunc;
            long mExpectedAction;
    };

    class ScriptLayerEventHandler : public pdg::RefCountedImpl< pdg::IEventHandler >
    {
        public:
            ScriptLayerEventHandler();
            ScriptLayerEventHandler(JSObjectRef javascriptHandlerFunc, long expectedAction);
            bool handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept;
        protected:
            JSObjectRef mScriptHandlerFunc;
            long mExpectedAction;
    };

    class ScriptSerializable : public pdg::ISerializable
    {
        public:
            ScriptSerializable();
            ScriptSerializable(
                JSObjectRef javascriptGetSerializedSizeFunc,
                JSObjectRef javascriptSerializeFunc,
                JSObjectRef javascriptDeserializeFunc,
                JSObjectRef javascriptGetMyClassTagFunc
                );
            virtual uint32 getSerializedSize(ISerializer* serializer) const;
            virtual void serialize(ISerializer* serializer) const;
            virtual void deserialize(IDeserializer* deserializer);
            virtual uint32 getMyClassTag() const;
        protected:
            JSObjectRef mScriptGetSerializedSizeFunc;
            JSObjectRef mScriptSerializeFunc;
            JSObjectRef mScriptDeserializeFunc;
            JSObjectRef mScriptGetMyClassTagFunc;
    };

#ifndef PDG_NO_GUI

    class ScriptSpriteDrawHelper : public pdg::ISpriteDrawHelper
    {
        public:
            ScriptSpriteDrawHelper();
            ScriptSpriteDrawHelper(JSObjectRef javascriptDrawFunc);
            bool draw(Sprite* sprite, Port* port) noexcept;
        protected:
            JSObjectRef mScriptDrawFunc;
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
