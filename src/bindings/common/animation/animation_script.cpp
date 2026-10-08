// -----------------------------------------------
// animation_script.cpp
//
// Class-specific JavaScript bindings.
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "animation_impl_macros.h"
#include "../core/core_impl_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_impl.h"
%#include "pdg_script_interface.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>
%#include "pdg/sys/animationrecorder.h"
%#include "../../common/animation/particle_trail_options.h"

namespace pdg {

// The native script library owns builders; wrappers borrow that stable identity.
%#ifdef PDG_USING_JAVASCRIPT_CORE
AnimationScript* New_AnimationScript(SCRIPT_ARGS) { return nullptr; }
static void AnimationScript_finalize(JSObjectRef object) {
    auto* builder=static_cast<AnimationScript*>(JSObjectGetPrivate(object));
    if (builder) { builder->mAnimatedScriptObj=nullptr; builder->mAnimationScriptScriptObj=nullptr; builder->release(); }
    JSObjectSetPrivate(object,nullptr);
}
%#define SCRIPT_BUILDER_SAVE(cppObj, obj) cppObj->mAnimatedScriptObj=obj; cppObj->mAnimationScriptScriptObj=obj
%#else
%#define SCRIPT_BUILDER_SAVE(cppObj, obj) cppObj->mAnimatedScriptObj.Reset(isolate,obj); cppObj->mAnimatedScriptObj.SetWeak(); cppObj->mAnimationScriptScriptObj.Reset(isolate,obj); cppObj->mAnimationScriptScriptObj.SetWeak()
AnimationScript* New_AnimationScript(SCRIPT_ARGS) { return nullptr; }
AnimationScriptWrap::AnimationScriptWrap(SCRIPT_ARGS) : cppPtr_(nullptr) {}
AnimationScriptWrap::~AnimationScriptWrap() {
    if (cppPtr_) { cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->mAnimationScriptScriptObj.Reset(); cppPtr_->release(); }
}
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY(AnimationScript, "Animated.defineScript", SCRIPT_BUILDER_SAVE(cppObj,obj); cppObj->addRef())
    EXPORT_DERIVED_CLASS_SYMBOLS("AnimationScript", AnimationScript, AnimatedBase, AnimationScript_finalize, , ,
        HAS_ANIMATED_METHODS(AnimationScript)
        HAS_METHOD(AnimationScript, "_recordAnimationCommand", RecordCommand)
        HAS_METHOD(AnimationScript, "endScript", EndScript)
        );
END
ANIMATED_BASE_CLASS_IMPL(AnimationScript)
METHOD_IMPL(AnimationScript, RecordCommand)
#include "animation_recorder_body.inc"
END
METHOD_IMPL(AnimationScript, EndScript)
    METHOD_SIGNATURE("Validate and seal this definition.", [this], 0, ());
    REQUIRE_ARG_COUNT(0);
    try { self->endScript(); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
CLEANUP_IMPL(AnimationScript)
struct NativeScriptEvaluator {
%#ifdef PDG_USING_JAVASCRIPT_CORE
    JSGlobalContextRef context;
    JSObjectRef function;
    NativeScriptEvaluator(JSContextRef ctx, JSObjectRef callback)
        : context(JSGlobalContextRetain(JSContextGetGlobalContext(ctx))),function(callback) { JSValueProtect(context,function); }
    ~NativeScriptEvaluator() { JSValueUnprotect(context,function); JSGlobalContextRelease(context); }
%#else
    v8::Isolate* isolate;
    v8::Global<v8::Context> context;
    v8::Global<v8::Function> function;
    NativeScriptEvaluator(v8::Isolate* engine,v8::Local<v8::Function> callback)
        : isolate(engine),context(engine,engine->GetCurrentContext()),function(engine,callback) {}
    void clear() { context.Reset(); function.Reset(); }
%#endif
    bool invoke(const AnimationEvaluationContext& info, const AnimationEvent* event=nullptr) {
%#ifdef PDG_USING_JAVASCRIPT_CORE
        JSContextRef ctx=context; JSValueRef error=nullptr; JSValueRef* exception=&error;
        JSObjectRef target=info.target.mAnimatedScriptObj;
        if (!target) throw std::runtime_error("Animation evaluator target has no script wrapper");
        auto object=JSObjectMake(ctx,nullptr,nullptr);
        JSStringRef targetKey=JSStringCreateWithUTF8CString("target"),timeKey=JSStringCreateWithUTF8CString("elapsedSeconds");
        JSObjectSetProperty(ctx,object,targetKey,target,kJSPropertyAttributeNone,exception);
        JSObjectSetProperty(ctx,object,timeKey,NUM2VAL(info.elapsedSeconds),kJSPropertyAttributeNone,exception);
        JSStringRelease(targetKey); JSStringRelease(timeKey);
        if(event) {
            const auto set=[&](const char* name,JSValueRef value) {
                auto key=JSStringCreateWithUTF8CString(name); JSObjectSetProperty(ctx,object,key,value,kJSPropertyAttributeNone,exception); JSStringRelease(key);
            };
            const auto text=[&](const std::string& value) { auto str=JSStringCreateWithUTF8CString(value.c_str()); auto result=JSValueMakeString(ctx,str); JSStringRelease(str); return result; };
            set("type",text(event->type)); set("scriptName",text(event->scriptName)); set("markName",text(event->markName)); set("operationName",text(event->operationName));
            set("iteration",NUM2VAL(event->iteration)); set("reverse",JSValueMakeBoolean(ctx,event->reverse));
        }
        JSValueRef argument=object;
        auto result=JSObjectCallAsFunction(ctx,function,nullptr,1,&argument,exception);
        if (error) throw std::runtime_error("Animation script evaluator failed");
        if(event) return false;
        if (!JSValueIsBoolean(ctx,result)) throw std::runtime_error("Animation evaluator must return a boolean synchronously");
        return JSValueToBoolean(ctx,result);
%#else
        if (function.IsEmpty()) throw std::runtime_error("Animation script evaluator environment is closed");
        v8::HandleScope handles(isolate); auto ctx=context.Get(isolate); v8::Context::Scope scope(ctx); v8::TryCatch catcher(isolate);
        if (info.target.mAnimatedScriptObj.IsEmpty()) throw std::runtime_error("Animation evaluator target has no script wrapper");
        auto object=v8::Object::New(isolate);
        object->Set(ctx,v8::String::NewFromUtf8Literal(isolate,"target"),v8::Local<v8::Object>::New(isolate,info.target.mAnimatedScriptObj)).Check();
        object->Set(ctx,v8::String::NewFromUtf8Literal(isolate,"elapsedSeconds"),v8::Number::New(isolate,info.elapsedSeconds)).Check();
        if(event) {
            const auto set=[&](const char* name,v8::Local<v8::Value> value) { object->Set(ctx,v8::String::NewFromUtf8(isolate,name).ToLocalChecked(),value).Check(); };
            const auto text=[&](const std::string& value) { return v8::String::NewFromUtf8(isolate,value.c_str()).ToLocalChecked(); };
            set("type",text(event->type)); set("scriptName",text(event->scriptName)); set("markName",text(event->markName)); set("operationName",text(event->operationName));
            set("iteration",v8::Integer::NewFromUnsigned(isolate,event->iteration)); set("reverse",v8::Boolean::New(isolate,event->reverse));
        }
        v8::Local<v8::Value> argument=object,result;
        if (!function.Get(isolate)->Call(ctx,v8::Undefined(isolate),1,&argument).ToLocal(&result)) {
            v8::String::Utf8Value message(isolate,catcher.Exception());
            throw std::runtime_error(*message ? *message : "Animation script evaluator failed");
        }
        if(event) return false;
        if (!result->IsBoolean()) throw std::runtime_error("Animation evaluator must return a boolean synchronously");
        return result->BooleanValue(isolate);
%#endif
    }
};
%#ifndef PDG_USING_JAVASCRIPT_CORE
static std::vector<std::weak_ptr<NativeScriptEvaluator>> scriptEvaluators;
void ClearAnimationEvaluatorCallbacks() {
    for (auto& reference : scriptEvaluators) if (auto callback=reference.lock()) callback->clear();
    scriptEvaluators.clear();
    AnimatedBase::clearScriptLibrary();
}
%#endif
AnimationEvaluator MakeAnimationEvaluator(FUNCTION_REF function) {
%#ifdef PDG_USING_JAVASCRIPT_CORE
    auto callback=std::make_shared<NativeScriptEvaluator>(gMainContext,function);
%#else
    auto callback=std::make_shared<NativeScriptEvaluator>(v8::Isolate::GetCurrent(),function);
    std::erase_if(scriptEvaluators,[](const auto& reference){return reference.expired();});
    scriptEvaluators.push_back(callback);
%#endif
    return [callback](const AnimationEvaluationContext& info) { return callback->invoke(info); };
}
AnimationEventHandler MakeAnimationEventHandler(FUNCTION_REF function) {
%#ifdef PDG_USING_JAVASCRIPT_CORE
    auto callback=std::make_shared<NativeScriptEvaluator>(gMainContext,function);
%#else
    auto callback=std::make_shared<NativeScriptEvaluator>(v8::Isolate::GetCurrent(),function);
    std::erase_if(scriptEvaluators,[](const auto& reference){return reference.expired();});
    scriptEvaluators.push_back(callback);
%#endif
    return [callback](const AnimationEvent& event) { callback->invoke({event.target,event.elapsedSeconds},&event); };
}

} // namespace pdg
