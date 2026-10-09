// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/sprite.cpp
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

#include "pdg_script_interface.h"
#include "pdg_script_impl.h"

#include "internals.h"
#include "pdg-lib.h"

#include <cstdlib>
#include <cmath>

namespace pdg
{
#ifdef PDG_USING_JAVASCRIPT_CORE
#define PROCEDURAL_PARAMETERS JSContextRef ctx, JSValueRef* exception
#define PROCEDURAL_ARGUMENTS ctx, exception
#else
#define PROCEDURAL_PARAMETERS v8::Isolate* isolate
#define PROCEDURAL_ARGUMENTS isolate
#endif

    static std::vector<double> proceduralBindingValues(PROCEDURAL_PARAMETERS, JSValueRef input)
    {
        std::vector<double> values;
#ifdef PDG_USING_JAVASCRIPT_CORE
        if(!JSValueIsArray(ctx,input)) { throw std::invalid_argument("Expected procedural array"); }
        auto a=JSValueToObject(ctx,input,exception);auto key=JSStringCreateWithUTF8CString("length");
        double n=JSValueToNumber(ctx,JSObjectGetProperty(ctx,a,key,exception),exception);JSStringRelease(key);
        if(*exception||n>50000) { throw std::invalid_argument("Invalid procedural array"); }
        for(unsigned i=0;i<n;++i)
        {
            auto item=JSObjectGetPropertyAtIndex(ctx,a,i,exception);if(*exception||!JSValueIsNumber(ctx,item))
            {
                throw std::invalid_argument("Invalid procedural number");
            }
            values.push_back(JSValueToNumber(ctx,item,exception));
        }
#else
        if(!input->IsArray()) { throw std::invalid_argument("Expected procedural array"); }
        auto a=input.As<v8::Array>();if(a->Length()>50000)
        {
            throw std::invalid_argument("Procedural array too long");
        }
        for(unsigned i=0;i<a->Length();++i)
        {
            v8::Local<v8::Value> item;if(!a->Get(isolate->GetCurrentContext(),i).ToLocal(&item)||!item->IsNumber())
            {
                throw std::invalid_argument("Invalid procedural number");
            }
            values.push_back(item.As<v8::Number>()->Value());
        }
#endif
        return values;
    }

#ifndef PDG_NO_GUI

    JSObjectRef ISpriteDrawHelper_newFromCpp(JSContextRef ctx, ISpriteDrawHelper* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, ISpriteDrawHelper_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, ISpriteDrawHelper_class());
        cppObj->mISpriteDrawHelperScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSObjectRef ISpriteDrawHelper_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ISpriteDrawHelper* cppObj = New_ISpriteDrawHelper(argumentCount, arguments, exception);
        if (exception && *exception) return nullptr;
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            std::ostringstream excpt_;
            excpt_ << "throw '" << s_SavedError.str().c_str() << "'";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        };
        if (!cppObj)
        {
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "ISpriteDrawHelper" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, ISpriteDrawHelper_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, ISpriteDrawHelper_class());
        cppObj->mISpriteDrawHelperScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSClassRef ISpriteDrawHelper_class()
    {
        static JSStaticValue ISpriteDrawHelper_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction ISpriteDrawHelper_staticFunctions[] =
        {
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "ISpriteDrawHelper";
            definition.staticFunctions = ISpriteDrawHelper_staticFunctions;
            definition.staticValues = ISpriteDrawHelper_staticValues;
            definition.callAsConstructor = ISpriteDrawHelper_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;
    }

    void CleanupISpriteDrawHelperScriptObject(JSObjectRef obj) { }
#endif

#ifdef PDG_SPRITER_SUPPORT
#ifdef PDG_USING_JAVASCRIPT_CORE
#define PDG_POSE_SCRIPT_PARAMETERS JSContextRef ctx, JSValueRef* exception
#define PDG_POSE_SCRIPT_ARGUMENTS ctx, exception
#else
#define PDG_POSE_SCRIPT_PARAMETERS v8::Isolate* isolate
#define PDG_POSE_SCRIPT_ARGUMENTS isolate
#endif
    static JSStringRef symbol_x = 0;
    static JSStringRef symbol_y = 0;
    static JSStringRef symbol_rotation = 0;
    static JSStringRef symbol_scaleX = 0;
    static JSStringRef symbol_scaleY = 0;
    static JSStringRef symbol_alpha = 0;
    static JSStringRef symbol_name = 0;
    static JSStringRef symbol_parent = 0;
    static JSStringRef symbol_kind = 0;
    static JSStringRef symbol_bones = 0;
    static JSStringRef symbol_bindings = 0;
    static JSStringRef symbol_rigRevision = 0;
    static JSStringRef symbol_object = 0;
    static JSStringRef symbol_type = 0;
    static JSStringRef symbol_value = 0;
    static JSStringRef symbol_variables = 0;
    static JSStringRef symbol_tags = 0;

    static JSObjectRef animationTransformValue(PDG_POSE_SCRIPT_PARAMETERS, const AnimationTransform& transform)
    {
        JSObjectRef result = JSC_ObjectCreateEmpty(ctx, 0);
        JSObjectSetProperty(ctx, result, ((symbol_x) ? symbol_x : symbol_x = JSStringCreateWithUTF8CString("x")), JSValueMakeNumber(ctx, transform.x), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_y) ? symbol_y : symbol_y = JSStringCreateWithUTF8CString("y")), JSValueMakeNumber(ctx, transform.y), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_rotation) ? symbol_rotation : symbol_rotation = JSStringCreateWithUTF8CString("rotation")), JSValueMakeNumber(ctx, transform.rotation), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_scaleX) ? symbol_scaleX : symbol_scaleX = JSStringCreateWithUTF8CString("scaleX")), JSValueMakeNumber(ctx, transform.scaleX), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_scaleY) ? symbol_scaleY : symbol_scaleY = JSStringCreateWithUTF8CString("scaleY")), JSValueMakeNumber(ctx, transform.scaleY), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_alpha) ? symbol_alpha : symbol_alpha = JSStringCreateWithUTF8CString("alpha")), JSValueMakeNumber(ctx, transform.alpha), kJSPropertyAttributeNone, exception);
        return result;
    }
    static JSObjectRef animationSnapshotValue(PDG_POSE_SCRIPT_PARAMETERS, const AnimationPose& pose)
    {
        JSObjectRef result = JSC_ObjectCreateEmpty(ctx, 0);
        JSObjectSetProperty(ctx, result, ((symbol_rigRevision) ? symbol_rigRevision : symbol_rigRevision = JSStringCreateWithUTF8CString("rigRevision")), JSC_MakeValueFromCString(ctx, std::to_string(pose.getRig()->getRevision()).c_str()), kJSPropertyAttributeNone, exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto bones = JSObjectMakeArray(ctx, 0, nullptr, exception);
#else
        auto bones = v8::Array::New(isolate);
#endif
        for (uint32_t id = 0; id < pose.getRig()->getBoneCount(); ++id)
        {
            const auto& definition = pose.getRig()->getBone(id);
            JSObjectRef item = animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS, pose.getLocalTransform(id));
            JSObjectSetProperty(ctx, item, ((symbol_name) ? symbol_name : symbol_name = JSStringCreateWithUTF8CString("name")), JSC_MakeValueFromCString(ctx, definition.name.c_str()), kJSPropertyAttributeNone, exception);
            JSValueRef parentValue = JSValueMakeNumber(ctx, definition.parent);
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (definition.parent == animation_NoBone) parentValue = JSValueMakeNull(ctx);
#else
            if (definition.parent == animation_NoBone) parentValue = v8::Null(isolate);
#endif
            JSObjectSetProperty(ctx, item, ((symbol_parent) ? symbol_parent : symbol_parent = JSStringCreateWithUTF8CString("parent")), parentValue, kJSPropertyAttributeNone, exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
            JSObjectSetPropertyAtIndex(ctx, bones, id, item, exception);
#else
            (void)bones->Set(isolate->GetCurrentContext(), id, item).ToChecked();
#endif
        }
        JSObjectSetProperty(ctx, result, ((symbol_bones) ? symbol_bones : symbol_bones = JSStringCreateWithUTF8CString("bones")), bones, kJSPropertyAttributeNone, exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto bindings = JSObjectMakeArray(ctx, 0, nullptr, exception);
#else
        auto bindings = v8::Array::New(isolate);
#endif
        for (uint32_t id = 0; id < pose.getRig()->getBindingCount(); ++id)
        {
            const auto& definition = pose.getRig()->getBinding(id);
            JSObjectRef item = animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS, pose.getBindingLocalTransform(id));
            JSObjectSetProperty(ctx, item, ((symbol_name) ? symbol_name : symbol_name = JSStringCreateWithUTF8CString("name")), JSC_MakeValueFromCString(ctx, definition.name.c_str()), kJSPropertyAttributeNone, exception);
            JSValueRef parentValue = JSValueMakeNumber(ctx, definition.bone);
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (definition.bone == animation_NoBone) parentValue = JSValueMakeNull(ctx);
#else
            if (definition.bone == animation_NoBone) parentValue = v8::Null(isolate);
#endif
            JSObjectSetProperty(ctx, item, ((symbol_parent) ? symbol_parent : symbol_parent = JSStringCreateWithUTF8CString("parent")), parentValue, kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, item, ((symbol_kind) ? symbol_kind : symbol_kind = JSStringCreateWithUTF8CString("kind")), JSValueMakeNumber(ctx, static_cast<int>(definition.kind)), kJSPropertyAttributeNone, exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
            JSObjectSetPropertyAtIndex(ctx, bindings, id, item, exception);
#else
            (void)bindings->Set(isolate->GetCurrentContext(), id, item).ToChecked();
#endif
        }
        JSObjectSetProperty(ctx, result, ((symbol_bindings) ? symbol_bindings : symbol_bindings = JSStringCreateWithUTF8CString("bindings")), bindings, kJSPropertyAttributeNone, exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto variables = JSObjectMakeArray(ctx, 0, nullptr, exception);
#else
        auto variables = v8::Array::New(isolate);
#endif
        for (size_t id = 0; id < pose.getMetadata().variables.size(); ++id)
        {
            const auto& definition = pose.getMetadata().variables[id];
            JSObjectRef item = JSC_ObjectCreateEmpty(ctx, 0);
            JSObjectSetProperty(ctx, item, ((symbol_object) ? symbol_object : symbol_object = JSStringCreateWithUTF8CString("object")), JSC_MakeValueFromCString(ctx, definition.object.c_str()), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, item, ((symbol_name) ? symbol_name : symbol_name = JSStringCreateWithUTF8CString("name")), JSC_MakeValueFromCString(ctx, definition.name.c_str()), kJSPropertyAttributeNone, exception);
            if (const auto* number = std::get_if<double>(&definition.value))
            {
                JSObjectSetProperty(ctx, item, ((symbol_type) ? symbol_type : symbol_type = JSStringCreateWithUTF8CString("type")), JSValueMakeNumber(ctx, animationVariable_Float), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, item, ((symbol_value) ? symbol_value : symbol_value = JSStringCreateWithUTF8CString("value")), JSValueMakeNumber(ctx, *number), kJSPropertyAttributeNone, exception);
            }
            else if (const auto* integer = std::get_if<int>(&definition.value))
            {
                JSObjectSetProperty(ctx, item, ((symbol_type) ? symbol_type : symbol_type = JSStringCreateWithUTF8CString("type")), JSValueMakeNumber(ctx, animationVariable_Int), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, item, ((symbol_value) ? symbol_value : symbol_value = JSStringCreateWithUTF8CString("value")), JSValueMakeNumber(ctx, *integer), kJSPropertyAttributeNone, exception);
            }
            else
            {
                JSObjectSetProperty(ctx, item, ((symbol_type) ? symbol_type : symbol_type = JSStringCreateWithUTF8CString("type")), JSValueMakeNumber(ctx, animationVariable_String), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, item, ((symbol_value) ? symbol_value : symbol_value = JSStringCreateWithUTF8CString("value")), JSC_MakeValueFromCString(ctx, std::get<std::string>(definition.value).c_str()), kJSPropertyAttributeNone, exception);
            }
#ifdef PDG_USING_JAVASCRIPT_CORE
            JSObjectSetPropertyAtIndex(ctx, variables, id, item, exception);
#else
            (void)variables->Set(isolate->GetCurrentContext(), id, item).ToChecked();
#endif
        }
        JSObjectSetProperty(ctx, result, ((symbol_variables) ? symbol_variables : symbol_variables = JSStringCreateWithUTF8CString("variables")), variables, kJSPropertyAttributeNone, exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto tags = JSObjectMakeArray(ctx, 0, nullptr, exception);
#else
        auto tags = v8::Array::New(isolate);
#endif
        for (size_t id = 0; id < pose.getMetadata().tags.size(); ++id)
        {
            const auto& definition = pose.getMetadata().tags[id];
            JSObjectRef item = JSC_ObjectCreateEmpty(ctx, 0);
            JSObjectSetProperty(ctx, item, ((symbol_object) ? symbol_object : symbol_object = JSStringCreateWithUTF8CString("object")), JSC_MakeValueFromCString(ctx, definition.object.c_str()), kJSPropertyAttributeNone, exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto names = JSObjectMakeArray(ctx, 0, nullptr, exception);
            for (size_t n = 0; n < definition.tags.size(); ++n) JSObjectSetPropertyAtIndex(ctx, names, n, JSC_MakeValueFromCString(ctx, definition.tags[n].c_str()), exception);
#else
            auto names = v8::Array::New(isolate);
            for (size_t n = 0; n < definition.tags.size(); ++n) (void)names->Set(isolate->GetCurrentContext(), n, JSC_MakeValueFromCString(ctx, definition.tags[n].c_str())).ToChecked();
#endif
            JSObjectSetProperty(ctx, item, ((symbol_tags) ? symbol_tags : symbol_tags = JSStringCreateWithUTF8CString("tags")), names, kJSPropertyAttributeNone, exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
            JSObjectSetPropertyAtIndex(ctx, tags, id, item, exception);
#else
            (void)tags->Set(isolate->GetCurrentContext(), id, item).ToChecked();
#endif
        }
        JSObjectSetProperty(ctx, result, ((symbol_tags) ? symbol_tags : symbol_tags = JSStringCreateWithUTF8CString("tags")), tags, kJSPropertyAttributeNone, exception);
        return result;
    }

    static std::vector<double> animationPhysicsValues(PDG_POSE_SCRIPT_PARAMETERS,JSValueRef input)
    {
        std::vector<double> result;
#ifdef PDG_USING_JAVASCRIPT_CORE
        if(!JSValueIsArray(ctx,input)) { throw std::invalid_argument("Expected physical rig array"); }
        auto array=JSValueToObject(ctx,input,exception);auto key=JSStringCreateWithUTF8CString("length");
        const auto length=JSValueToNumber(ctx,JSObjectGetProperty(ctx,array,key,exception),exception);JSStringRelease(key);
        if(*exception||length>1500000) { throw std::invalid_argument("Invalid physical rig array length"); }
        for(unsigned i=0;i<length;++i)
        {
            auto value=JSObjectGetPropertyAtIndex(ctx,array,i,exception);if(*exception||!JSValueIsNumber(ctx,value))
            {
                throw std::invalid_argument("Invalid physical rig number");
            }
            result.push_back(JSValueToNumber(ctx,value,exception));
        }
#else
        if(!input->IsArray()) { throw std::invalid_argument("Expected physical rig array"); }
        auto array=input.As<v8::Array>();if(array->Length()>1500000) { throw std::invalid_argument("Invalid physical rig array length"); }
        for(unsigned i=0;i<array->Length();++i)
        {
            v8::Local<v8::Value> value;if(!array->Get(isolate->GetCurrentContext(),i).ToLocal(&value)||!value->IsNumber())
            {
                throw std::invalid_argument("Invalid physical rig number");
            }
            result.push_back(value.As<v8::Number>()->Value());
        }
#endif
        return result;
    }

    static AnimationTwoBoneIK animationScriptIKConfig(PDG_POSE_SCRIPT_PARAMETERS, JSValueRef value)
    {
        AnimationTwoBoneIK config;
        if (!JSValueIsObject(ctx, value)) { throw std::invalid_argument("Expected IK configuration"); }
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto object=JSValueToObject(ctx,value,exception);
#else
        auto object=value.As<v8::Object>();
#endif
        auto read=[&](const char* name)
        {
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto key=JSStringCreateWithUTF8CString(name);auto item=JSObjectGetProperty(ctx,object,key,exception);JSStringRelease(key);
            if (*exception || !JSValueIsNumber(ctx,item)) { throw std::invalid_argument("Invalid IK configuration field"); }
            double number=JSValueToNumber(ctx,item,exception);
#else
            v8::Local<v8::Value> item;
            if (!object->Get(isolate->GetCurrentContext(),v8::String::NewFromUtf8(isolate,name).ToLocalChecked()).ToLocal(&item) || !item->IsNumber()) { throw std::invalid_argument("Invalid IK configuration field"); }
            double number=item.As<v8::Number>()->Value();
#endif
            if (!std::isfinite(number)) { throw std::invalid_argument("Nonfinite IK configuration field"); }
            return number;
        };
        {
            double n=read("root");if(n<0 || n>=animation_NoBone || n!=std::floor(n))
            {
                throw std::invalid_argument("Invalid IK bone ID");
            }
            config.root=static_cast<AnimationBoneId>(n);
        }
        {
            double n=read("middle");if(n<0 || n>=animation_NoBone || n!=std::floor(n))
            {
                throw std::invalid_argument("Invalid IK bone ID");
            }
            config.middle=static_cast<AnimationBoneId>(n);
        }
        {
            double n=read("tip");if(n<0 || n>=animation_NoBone || n!=std::floor(n))
            {
                throw std::invalid_argument("Invalid IK bone ID");
            }
            config.tip=static_cast<AnimationBoneId>(n);
        }
        config.rootLength=read("rootLength");
        config.middleLength=read("middleLength");
        config.targetX=read("targetX");
        config.targetY=read("targetY");
        config.influence=read("influence");
        {
            double n=read("space");if(n<-1 || n>2 || n!=std::floor(n))
            {
                throw std::invalid_argument("Invalid IK enum");
            }
            config.space=static_cast<int>(n);
        }
        {
            double n=read("bendDirection");if(n<-1 || n>2 || n!=std::floor(n))
            {
                throw std::invalid_argument("Invalid IK enum");
            }
            config.bendDirection=static_cast<int>(n);
        }
        {
            double n=read("stretch");if(n<-1 || n>2 || n!=std::floor(n))
            {
                throw std::invalid_argument("Invalid IK enum");
            }
            config.stretch=static_cast<int>(n);
        }
        {
            double n=read("matchOrientation");if(n<-1 || n>2 || n!=std::floor(n))
            {
                throw std::invalid_argument("Invalid IK enum");
            }
            config.matchOrientation=static_cast<int>(n);
        }
        config.targetRotation=read("targetRotation");
        config.rootMin=read("rootMin");
        config.rootMax=read("rootMax");
        config.middleMin=read("middleMin");
        config.middleMax=read("middleMax");
        return config;
    }
    static JSStringRef symbol_reachError = 0;
    static JSStringRef symbol_reachable = 0;
    static JSStringRef symbol_clamped = 0;
    static JSStringRef symbol_limited = 0;
    static JSStringRef symbol_stretched = 0;
    static JSObjectRef animationIKResultValue(PDG_POSE_SCRIPT_PARAMETERS, const AnimationIKResult& value)
    {
        JSObjectRef result=JSC_ObjectCreateEmpty(ctx, 0);
        JSObjectSetProperty(ctx, result, ((symbol_reachError) ? symbol_reachError : symbol_reachError = JSStringCreateWithUTF8CString("reachError")), JSValueMakeNumber(ctx, value.reachError), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_reachable) ? symbol_reachable : symbol_reachable = JSStringCreateWithUTF8CString("reachable")), JSValueMakeBoolean(ctx, value.reachable), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_clamped) ? symbol_clamped : symbol_clamped = JSStringCreateWithUTF8CString("clamped")), JSValueMakeBoolean(ctx, value.clamped), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_limited) ? symbol_limited : symbol_limited = JSStringCreateWithUTF8CString("limited")), JSValueMakeBoolean(ctx, value.limited), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_stretched) ? symbol_stretched : symbol_stretched = JSStringCreateWithUTF8CString("stretched")), JSValueMakeBoolean(ctx, value.stretched), kJSPropertyAttributeNone, exception);
        return result;
    }

    static JSStringRef symbol_deltaSeconds = 0;
    static JSStringRef symbol_simulationDeltaSeconds = 0;
    static JSStringRef symbol_root = 0;
    static JSStringRef symbol_revision = 0;
    static JSObjectRef animationModifierContextValue(PDG_POSE_SCRIPT_PARAMETERS, const AnimationModifierContext& context)
    {
        JSObjectRef result = JSC_ObjectCreateEmpty(ctx, 0);
        JSObjectSetProperty(ctx, result, ((symbol_deltaSeconds) ? symbol_deltaSeconds : symbol_deltaSeconds = JSStringCreateWithUTF8CString("deltaSeconds")), JSValueMakeNumber(ctx, context.deltaSeconds), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_simulationDeltaSeconds) ? symbol_simulationDeltaSeconds : symbol_simulationDeltaSeconds = JSStringCreateWithUTF8CString("simulationDeltaSeconds")), JSValueMakeNumber(ctx, context.simulationDeltaSeconds), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_root) ? symbol_root : symbol_root = JSStringCreateWithUTF8CString("root")), animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS,context.root), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_revision) ? symbol_revision : symbol_revision = JSStringCreateWithUTF8CString("revision")), JSC_MakeValueFromCString(ctx, std::to_string(context.revision).c_str()), kJSPropertyAttributeNone, exception);
        return result;
    }
    static void applyAnimationScriptEdits(PDG_POSE_SCRIPT_PARAMETERS, AnimationPoseView view, JSValueRef edits)
    {
#ifdef PDG_USING_JAVASCRIPT_CORE
        if (edits && JSValueIsString(ctx,edits))
        {
            auto text=JSValueToStringCopy(ctx,edits,exception);std::vector<char> message(JSStringGetMaximumUTF8CStringSize(text));
            JSStringGetUTF8CString(text,message.data(),message.size());JSStringRelease(text);throw std::runtime_error(message.data());
        }
#else
        if (!edits.IsEmpty() && edits->IsString()) {v8::String::Utf8Value message(isolate,edits);throw std::runtime_error(*message ? *message : "Animation modifier failed");}
#endif
        const auto count = view.copy().getRig()->getBoneCount();
        const char* fields[] = {"x","y","rotation","scaleX","scaleY","alpha"};
#ifdef PDG_USING_JAVASCRIPT_CORE
        if (!edits || !JSValueIsArray(ctx,edits)) { throw std::invalid_argument("Modifier bridge must return bone transforms"); }
        auto array = JSValueToObject(ctx,edits,exception);
        auto lengthKey = JSStringCreateWithUTF8CString("length");
        auto lengthValue = JSObjectGetProperty(ctx,array,lengthKey,exception); JSStringRelease(lengthKey);
        if (*exception || JSValueToNumber(ctx,lengthValue,exception) != count) { throw std::invalid_argument("Wrong modifier bone count"); }
#else
        if (edits.IsEmpty() || !edits->IsArray() || edits.As<v8::Array>()->Length() != count) { throw std::invalid_argument("Wrong modifier bone count"); }
        auto array = edits.As<v8::Array>();
#endif
        for (uint32_t id=0;id<count;++id)
        {
            AnimationTransform transform;
            double* values[] = {&transform.x,&transform.y,&transform.rotation,&transform.scaleX,&transform.scaleY,&transform.alpha};
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto item=JSObjectGetPropertyAtIndex(ctx,array,id,exception);
            if (*exception || !JSValueIsObject(ctx,item)) { throw std::invalid_argument("Invalid modifier transform"); }
            auto object=JSValueToObject(ctx,item,exception);
#else
            v8::Local<v8::Value> item;
            if (!array->Get(isolate->GetCurrentContext(),id).ToLocal(&item) || !item->IsObject()) { throw std::invalid_argument("Invalid modifier transform"); }
            auto object=item.As<v8::Object>();
#endif
            for (int field=0;field<6;++field)
            {
#ifdef PDG_USING_JAVASCRIPT_CORE
                auto key=JSStringCreateWithUTF8CString(fields[field]);
                auto value=JSObjectGetProperty(ctx,object,key,exception);JSStringRelease(key);
                if (*exception || !JSValueIsNumber(ctx,value)) { throw std::invalid_argument("Modifier transform fields must be numbers"); }
                *values[field]=JSValueToNumber(ctx,value,exception);
#else
                v8::Local<v8::Value> value;
                if (!object->Get(isolate->GetCurrentContext(),v8::String::NewFromUtf8(isolate,fields[field]).ToLocalChecked()).ToLocal(&value) || !value->IsNumber()) { throw std::invalid_argument("Modifier transform fields must be numbers"); }
                *values[field]=value.As<v8::Number>()->Value();
#endif
            }
            view.setLocalTransform(id,transform);
        }
    }
    struct AnimationScriptModifier
    {
#ifdef PDG_USING_JAVASCRIPT_CORE
        JSGlobalContextRef context;
        JSObjectRef function;
        AnimationScriptModifier(JSContextRef ctx,JSObjectRef callback) : context(JSGlobalContextRetain(JSContextGetGlobalContext(ctx))), function(callback) { JSValueProtect(context,function); }
        ~AnimationScriptModifier() { JSValueUnprotect(context,function); JSGlobalContextRelease(context); }
        void invoke(AnimationPoseView view,const AnimationModifierContext& info)
        {
            JSContextRef ctx=context;JSValueRef error=nullptr;JSValueRef* exception=&error;
            JSValueRef argv[]={animationSnapshotValue(ctx,exception,view.copy()),animationModifierContextValue(ctx,exception,info)};
            auto result=JSObjectCallAsFunction(ctx,function,nullptr,2,argv,exception);
            if (error) throw std::runtime_error("Animation modifier script failed");
            applyAnimationScriptEdits(ctx,exception,view,result);
        }
#else
        v8::Isolate* isolate;
        v8::Global<v8::Context> context;
        v8::Global<v8::Function> function;
        AnimationScriptModifier(v8::Isolate* engine,v8::Local<v8::Function> callback) : isolate(engine),context(engine,engine->GetCurrentContext()),function(engine,callback) {}
        void invoke(AnimationPoseView view,const AnimationModifierContext& info)
        {
            v8::HandleScope handles(isolate);auto ctx=context.Get(isolate);v8::Context::Scope scope(ctx);v8::TryCatch catcher(isolate);
            v8::Local<v8::Value> argv[]={animationSnapshotValue(isolate,view.copy()),animationModifierContextValue(isolate,info)},
            result;
            if (!function.Get(isolate)->Call(ctx,v8::Undefined(isolate),2,argv).ToLocal(&result))
            {
                v8::String::Utf8Value message(isolate,catcher.Exception());
                throw std::runtime_error(*message ? *message : "Animation modifier script failed");
            }
            applyAnimationScriptEdits(isolate,view,result);
        }
#endif
    };

    static std::shared_ptr<Drawing> animationScriptDrawingValue(PDG_POSE_SCRIPT_PARAMETERS,JSValueRef input)
    {
        if(JSValueIsString(ctx, input))
        {
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto value=JSValueToStringCopy(ctx,input,exception);std::string message(JSStringGetMaximumUTF8CStringSize(value),'\0');JSStringGetUTF8CString(value,&message[0],message.size());JSStringRelease(value);throw std::runtime_error(message.c_str());
#else
            v8::String::Utf8Value message(isolate,input);throw std::runtime_error(*message?*message:"Drawing callback failed");
#endif
        }
        if(JSValueIsNull(ctx, input))return {};
        Drawing* result = 0;
        if (JSValueIsObject(ctx, input))
        {
            JSObjectRef result_obj_ = JSValueToObject(ctx, input, exception);
            result = Drawing_getCppObject(result_obj_);
            if (!result)
            {
                JSValueRef protoVal_ = JSObjectGetPrototype(ctx, result_obj_);
                if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                {
                    JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                    result = Drawing_getCppObject(protoObj_);
                }
            }
        };
        if(!result) { throw std::invalid_argument("Animation drawing callback must return a Drawing or null"); }
        return result->share();
    }
    struct AnimationScriptDrawing : AnimationScriptModifier
    {
        using AnimationScriptModifier::AnimationScriptModifier;
        std::shared_ptr<Drawing> draw(AnimationDrawingContext drawing)
        {
#ifdef PDG_USING_JAVASCRIPT_CORE
            JSValueRef exceptionValue=nullptr;JSValueRef* exception=&exceptionValue;JSContextRef ctx=context;
            JSValueRef args[]={animationSnapshotValue(ctx,exception,drawing.copyPose()),animationTransformValue(ctx,exception,drawing.getTransform(animationSpace_Local)),animationTransformValue(ctx,exception,drawing.getTransform(animationSpace_Rig)),animationTransformValue(ctx,exception,drawing.getTransform(animationSpace_World))};
            auto result=JSObjectCallAsFunction(ctx,function,nullptr,4,args,exception);
            if(exceptionValue)throw std::runtime_error("Animation drawing script failed");return animationScriptDrawingValue(ctx,exception,result);
#else
            v8::HandleScope handles(isolate);auto ctx=context.Get(isolate);v8::Context::Scope scope(ctx);v8::TryCatch catcher(isolate);
            v8::Local<v8::Value> args[]={animationSnapshotValue(isolate,drawing.copyPose()),animationTransformValue(isolate,drawing.getTransform(animationSpace_Local)),animationTransformValue(isolate,drawing.getTransform(animationSpace_Rig)),animationTransformValue(isolate,drawing.getTransform(animationSpace_World))},
            result;
            if(!function.Get(isolate)->Call(ctx,v8::Undefined(isolate),4,args).ToLocal(&result)){v8::String::Utf8Value message(isolate,catcher.Exception());throw std::runtime_error(*message?*message:"Animation drawing script failed");}
            return animationScriptDrawingValue(isolate,result);
#endif
        }
    };
    static JSStringRef symbol_left = 0;
    static JSStringRef symbol_top = 0;
    static JSStringRef symbol_right = 0;
    static JSStringRef symbol_bottom = 0;
    static JSStringRef symbol_uncullable = 0;
    static JSObjectRef animationDrawingBoundsValue(PDG_POSE_SCRIPT_PARAMETERS,const AnimationDrawBounds& bounds)
    {
        auto result=JSC_ObjectCreateEmpty(ctx, 0);
        JSObjectSetProperty(ctx, result, ((symbol_left) ? symbol_left : symbol_left = JSStringCreateWithUTF8CString("left")), JSValueMakeNumber(ctx, bounds.left), kJSPropertyAttributeNone, exception);JSObjectSetProperty(ctx, result, ((symbol_top) ? symbol_top : symbol_top = JSStringCreateWithUTF8CString("top")), JSValueMakeNumber(ctx, bounds.top), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_right) ? symbol_right : symbol_right = JSStringCreateWithUTF8CString("right")), JSValueMakeNumber(ctx, bounds.right), kJSPropertyAttributeNone, exception);JSObjectSetProperty(ctx, result, ((symbol_bottom) ? symbol_bottom : symbol_bottom = JSStringCreateWithUTF8CString("bottom")), JSValueMakeNumber(ctx, bounds.bottom), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, result, ((symbol_uncullable) ? symbol_uncullable : symbol_uncullable = JSStringCreateWithUTF8CString("uncullable")), JSValueMakeBoolean(ctx, bounds.uncullable), kJSPropertyAttributeNone, exception);return result;
    }
#endif

#ifdef PDG_USING_JAVASCRIPT_CORE
    static void Sprite_finalize(JSObjectRef object)
    {
        auto* sprite = static_cast<Sprite*>(JSObjectGetPrivate(object));
        if (!sprite) return;
        sprite->mSpriteScriptObj = sprite->mAnimatedScriptObj = nullptr;
        sprite->mEventEmitterScriptObj = sprite->mISerializableScriptObj = nullptr;
        JSObjectSetPrivate(object, nullptr);
        sprite->release();
    }
#define SPRITE_SAVE_WEAK(sprite, obj) sprite->mSpriteScriptObj=obj; sprite->mAnimatedScriptObj=obj; sprite->mEventEmitterScriptObj=obj; sprite->mISerializableScriptObj=obj
#else
#define SPRITE_SAVE_WEAK(sprite, obj) sprite->mSpriteScriptObj.Reset(isolate,obj); sprite->mSpriteScriptObj.SetWeak(); sprite->mAnimatedScriptObj.Reset(isolate,obj); sprite->mAnimatedScriptObj.SetWeak(); sprite->mEventEmitterScriptObj.Reset(isolate,obj); sprite->mEventEmitterScriptObj.SetWeak(); sprite->mISerializableScriptObj.Reset(isolate,obj); sprite->mISerializableScriptObj.SetWeak()
#endif

    JSObjectRef Sprite_newFromCpp(JSContextRef ctx, Sprite* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Sprite_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Sprite_class());
        SPRITE_SAVE_WEAK(cppObj, obj); cppObj->addRef();
        return obj;
    }

    JSObjectRef Sprite_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* cppObj = New_Sprite(argumentCount, arguments, exception);
        if (exception && *exception) return nullptr;
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            std::ostringstream excpt_;
            excpt_ << "throw '" << s_SavedError.str().c_str() << "'";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        };
        if (!cppObj)
        {
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Sprite" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Sprite_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Sprite_class());
        SPRITE_SAVE_WEAK(cppObj, obj); cppObj->addRef();
        return obj;
    }

    JSClassRef Sprite_class()
    {

        static JSStaticValue Sprite_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Sprite_staticFunctions[] =
        {
            { "getAttachmentPart", Sprite_GetAttachmentPart, kJSPropertyAttributeDontDelete },
            { "createPart", Sprite_CreatePart, kJSPropertyAttributeDontDelete },
            { "transferPart", Sprite_TransferPart, kJSPropertyAttributeDontDelete },
            { "setupFrameCollider", Sprite_SetupFrameCollider, kJSPropertyAttributeDontDelete },
            { "setupAnimationCollider", Sprite_SetupAnimationCollider, kJSPropertyAttributeDontDelete },
            { "setFrameCollisionMask", Sprite_SetFrameCollisionMask, kJSPropertyAttributeDontDelete },
            { "getPart", Sprite_GetPart, kJSPropertyAttributeDontDelete },
            { "findPart", Sprite_FindPart, kJSPropertyAttributeDontDelete },
            { "getPartCount", Sprite_GetPartCount, kJSPropertyAttributeDontDelete },
            { "getPartNames", Sprite_GetPartNames, kJSPropertyAttributeDontDelete },
            { "removePart", Sprite_RemovePart, kJSPropertyAttributeDontDelete },
            { "clearParts", Sprite_ClearParts, kJSPropertyAttributeDontDelete },
            { "addHandler", Sprite_AddHandler, kJSPropertyAttributeDontDelete },
            { "removeHandler", Sprite_RemoveHandler, kJSPropertyAttributeDontDelete },
            { "clear", Sprite_Clear, kJSPropertyAttributeDontDelete },
            { "blockEvent", Sprite_BlockEvent, kJSPropertyAttributeDontDelete },
            { "unblockEvent", Sprite_UnblockEvent, kJSPropertyAttributeDontDelete },
            { "playScript", Sprite_PlayScript, kJSPropertyAttributeDontDelete },
            { "batch", Sprite_Batch, kJSPropertyAttributeDontDelete },
            { "endBatch", Sprite_EndBatch, kJSPropertyAttributeDontDelete },
            { "series", Sprite_Series, kJSPropertyAttributeDontDelete },
            { "endSeries", Sprite_EndSeries, kJSPropertyAttributeDontDelete },
            { "andAlso", Sprite_AndAlso, kJSPropertyAttributeDontDelete },
            { "stagger", Sprite_Stagger, kJSPropertyAttributeDontDelete },
            { "mark", Sprite_Mark, kJSPropertyAttributeDontDelete },
            { "jumpToMark", Sprite_JumpToMark, kJSPropertyAttributeDontDelete },
            { "on", Sprite_ScriptOn, kJSPropertyAttributeDontDelete },
            { "triggerEvent", Sprite_TriggerEvent, kJSPropertyAttributeDontDelete },
            { "onStarted", Sprite_OnStarted, kJSPropertyAttributeDontDelete },
            { "onFinished", Sprite_OnFinished, kJSPropertyAttributeDontDelete },
            { "onScriptFinished", Sprite_OnScriptFinished, kJSPropertyAttributeDontDelete },
            { "onMark", Sprite_OnMark, kJSPropertyAttributeDontDelete },
            { "onYoyo", Sprite_OnYoyo, kJSPropertyAttributeDontDelete },
            { "onRepeat", Sprite_OnRepeat, kJSPropertyAttributeDontDelete },
            { "onUntilFired", Sprite_OnUntilFired, kJSPropertyAttributeDontDelete },
            { "when", Sprite_When, kJSPropertyAttributeDontDelete },
            { "otherwise", Sprite_Otherwise, kJSPropertyAttributeDontDelete },
            { "endWhen", Sprite_EndWhen, kJSPropertyAttributeDontDelete },
            { "endOtherwise", Sprite_EndOtherwise, kJSPropertyAttributeDontDelete },
            { "until", Sprite_Until, kJSPropertyAttributeDontDelete },
            { "yoyo", Sprite_Yoyo, kJSPropertyAttributeDontDelete },
            { "repeat", Sprite_Repeat, kJSPropertyAttributeDontDelete },
            { "diminish", Sprite_Diminish, kJSPropertyAttributeDontDelete },
            { "increase", Sprite_Increase, kJSPropertyAttributeDontDelete },
            { "slowDown", Sprite_SlowDown, kJSPropertyAttributeDontDelete },
            { "speedUp", Sprite_SpeedUp, kJSPropertyAttributeDontDelete },
            { "stopIt", Sprite_StopIt, kJSPropertyAttributeDontDelete },
            { "restartIt", Sprite_RestartIt, kJSPropertyAttributeDontDelete },
            { "pauseIt", Sprite_PauseIt, kJSPropertyAttributeDontDelete },
            { "resumeIt", Sprite_ResumeIt, kJSPropertyAttributeDontDelete },
            { "getBoundingBox", Sprite_GetBoundingBox, kJSPropertyAttributeDontDelete },
            { "getRotatedBounds", Sprite_GetRotatedBounds, kJSPropertyAttributeDontDelete },
            { "getLocation", Sprite_GetLocation, kJSPropertyAttributeDontDelete },
            { "getMovement", Sprite_GetMovement, kJSPropertyAttributeDontDelete },
            { "getSize", Sprite_GetSize, kJSPropertyAttributeDontDelete },
            { "getWidth", Sprite_GetWidth, kJSPropertyAttributeDontDelete },
            { "getHeight", Sprite_GetHeight, kJSPropertyAttributeDontDelete },
            { "getScale", Sprite_GetScale, kJSPropertyAttributeDontDelete },
            { "getStretching", Sprite_GetStretching, kJSPropertyAttributeDontDelete },
            { "getRotation", Sprite_GetRotation, kJSPropertyAttributeDontDelete },
            { "getCenterOffset", Sprite_GetCenterOffset, kJSPropertyAttributeDontDelete },
            { "getSpin", Sprite_GetSpin, kJSPropertyAttributeDontDelete },
            { "setLocation", Sprite_SetLocation, kJSPropertyAttributeDontDelete },
            { "moveTo", Sprite_MoveTo, kJSPropertyAttributeDontDelete },
            { "moveBy", Sprite_MoveBy, kJSPropertyAttributeDontDelete },
            { "setMovement", Sprite_SetMovement, kJSPropertyAttributeDontDelete },
            { "changeMovementTo", Sprite_ChangeMovementTo, kJSPropertyAttributeDontDelete },
            { "changeMovementBy", Sprite_ChangeMovementBy, kJSPropertyAttributeDontDelete },
            { "setSize", Sprite_SetSize, kJSPropertyAttributeDontDelete },
            { "changeCenterOffsetTo", Sprite_ChangeCenterOffsetTo, kJSPropertyAttributeDontDelete },
            { "changeCenterOffsetBy", Sprite_ChangeCenterOffsetBy, kJSPropertyAttributeDontDelete },
            { "setWidth", Sprite_SetWidth, kJSPropertyAttributeDontDelete },
            { "setHeight", Sprite_SetHeight, kJSPropertyAttributeDontDelete },
            { "setRotation", Sprite_SetRotation, kJSPropertyAttributeDontDelete },
            { "setSpin", Sprite_SetSpin, kJSPropertyAttributeDontDelete },
            { "setGrowing", Sprite_SetGrowing, kJSPropertyAttributeDontDelete },
            { "setStretching", Sprite_SetStretching, kJSPropertyAttributeDontDelete },
            { "setScale", Sprite_SetScale, kJSPropertyAttributeDontDelete },
            { "changeSpinTo", Sprite_ChangeSpinTo, kJSPropertyAttributeDontDelete },
            { "changeSpinBy", Sprite_ChangeSpinBy, kJSPropertyAttributeDontDelete },
            { "changeGrowingTo", Sprite_ChangeGrowingTo, kJSPropertyAttributeDontDelete },
            { "changeGrowingBy", Sprite_ChangeGrowingBy, kJSPropertyAttributeDontDelete },
            { "changeStretchingTo", Sprite_ChangeStretchingTo, kJSPropertyAttributeDontDelete },
            { "changeStretchingBy", Sprite_ChangeStretchingBy, kJSPropertyAttributeDontDelete },
            { "changeScaleTo", Sprite_ChangeScaleTo, kJSPropertyAttributeDontDelete },
            { "changeScaleBy", Sprite_ChangeScaleBy, kJSPropertyAttributeDontDelete },
            { "grow", Sprite_Grow, kJSPropertyAttributeDontDelete },
            { "stretch", Sprite_Stretch, kJSPropertyAttributeDontDelete },
            { "resizeBy", Sprite_ResizeBy, kJSPropertyAttributeDontDelete },
            { "resizeTo", Sprite_ResizeTo, kJSPropertyAttributeDontDelete },
            { "rotateBy", Sprite_RotateBy, kJSPropertyAttributeDontDelete },
            { "rotateTo", Sprite_RotateTo, kJSPropertyAttributeDontDelete },
            { "setCenterOffset", Sprite_SetCenterOffset, kJSPropertyAttributeDontDelete },
            { "setFlipX", Sprite_SetFlipX, kJSPropertyAttributeDontDelete },
            { "setFlipY", Sprite_SetFlipY, kJSPropertyAttributeDontDelete },
            { "stopMovement", Sprite_StopMovement, kJSPropertyAttributeDontDelete },
            { "stopSpinning", Sprite_StopSpinning, kJSPropertyAttributeDontDelete },
            { "stopGrowing", Sprite_StopGrowing, kJSPropertyAttributeDontDelete },
            { "stopStretching", Sprite_StopStretching, kJSPropertyAttributeDontDelete },
            { "pauseSchedule", Sprite_PauseSchedule, kJSPropertyAttributeDontDelete },
            { "resumeSchedule", Sprite_ResumeSchedule, kJSPropertyAttributeDontDelete },
            { "cancelSchedule", Sprite_CancelSchedule, kJSPropertyAttributeDontDelete },
            { "flipX", Sprite_FlipX, kJSPropertyAttributeDontDelete },
            { "flipY", Sprite_FlipY, kJSPropertyAttributeDontDelete },
            { "andThen", Sprite_AndThen, kJSPropertyAttributeDontDelete },
            { "isFlippedX", Sprite_IsFlippedX, kJSPropertyAttributeDontDelete },
            { "isFlippedY", Sprite_IsFlippedY, kJSPropertyAttributeDontDelete },
            { "isSchedulePaused", Sprite_IsSchedulePaused, kJSPropertyAttributeDontDelete },
            { "hasScheduledAnimations", Sprite_HasScheduledAnimations, kJSPropertyAttributeDontDelete },
            { "wait", Sprite_Wait, kJSPropertyAttributeDontDelete },
            { "addAnimationHelper", Sprite_AddAnimationHelper, kJSPropertyAttributeDontDelete },
            { "removeAnimationHelper", Sprite_RemoveAnimationHelper, kJSPropertyAttributeDontDelete },
            { "clearAnimationHelpers", Sprite_ClearAnimationHelpers, kJSPropertyAttributeDontDelete },
            { "_readCollider", Sprite_ReadCollider, kJSPropertyAttributeDontDelete },
            { "setupCollider", Sprite_SetupCollider, kJSPropertyAttributeDontDelete },
            { "removeCollider", Sprite_RemoveCollider, kJSPropertyAttributeDontDelete },
            { "_readPhysics", Sprite_ReadPhysics, kJSPropertyAttributeDontDelete },
            { "setupPhysicsBody", Sprite_SetupPhysicsBody, kJSPropertyAttributeDontDelete },
            { "removePhysicsBody", Sprite_RemovePhysicsBody, kJSPropertyAttributeDontDelete },
            { "get""MyClassTag", Sprite_GetMyClassTag, kJSPropertyAttributeDontDelete },
            { "get""SerializedSize", Sprite_GetSerializedSize, kJSPropertyAttributeDontDelete },
            { "serialize", Sprite_Serialize, kJSPropertyAttributeDontDelete },
            { "deserialize", Sprite_Deserialize, kJSPropertyAttributeDontDelete },
            { "getFrameRotatedBounds", Sprite_GetFrameRotatedBounds, kJSPropertyAttributeDontDelete },
            { "setFrame", Sprite_SetFrame, kJSPropertyAttributeDontDelete },
            { "getCurrentFrame", Sprite_GetCurrentFrame, kJSPropertyAttributeDontDelete },
            { "getFrameCount", Sprite_GetFrameCount, kJSPropertyAttributeDontDelete },
            { "startFrameAnimation", Sprite_StartFrameAnimation, kJSPropertyAttributeDontDelete },
            { "stopFrameAnimation", Sprite_StopFrameAnimation, kJSPropertyAttributeDontDelete },
            { "get""WantsAnimLoopEvents", Sprite_GetWantsAnimLoopEvents, kJSPropertyAttributeDontDelete },
            { "set""WantsAnimLoopEvents", Sprite_SetWantsAnimLoopEvents, kJSPropertyAttributeDontDelete },
            { "get""WantsAnimEndEvents", Sprite_GetWantsAnimEndEvents, kJSPropertyAttributeDontDelete },
            { "set""WantsAnimEndEvents", Sprite_SetWantsAnimEndEvents, kJSPropertyAttributeDontDelete },
            { "get""WantsCollideWallEvents", Sprite_GetWantsCollideWallEvents, kJSPropertyAttributeDontDelete },
            { "set""WantsCollideWallEvents", Sprite_SetWantsCollideWallEvents, kJSPropertyAttributeDontDelete },
            { "addFramesImage", Sprite_AddFramesImage, kJSPropertyAttributeDontDelete },
#ifdef PDG_SPRITER_SUPPORT
            { "seekAnimation", Sprite_SeekAnimation, kJSPropertyAttributeDontDelete },
            { "transitionToAnimation", Sprite_TransitionToAnimation, kJSPropertyAttributeDontDelete },
            { "isAnimationTransitioning", Sprite_IsAnimationTransitioning, kJSPropertyAttributeDontDelete },
            { "getAnimationTransitionProgress", Sprite_GetAnimationTransitionProgress, kJSPropertyAttributeDontDelete },
            { "supportsAnimationPhysics", Sprite_SupportsAnimationPhysics, kJSPropertyAttributeDontDelete },
            { "setupAnimationPhysics", Sprite_SetupAnimationPhysics, kJSPropertyAttributeDontDelete },
            { "setupPhysicsFromAnimationRig", Sprite_SetupPhysicsFromAnimationRig, kJSPropertyAttributeDontDelete },
            { "attachAnimationPhysicsPart", Sprite_AttachAnimationPhysicsPart, kJSPropertyAttributeDontDelete },
            { "detachAnimationPhysicsPart", Sprite_DetachAnimationPhysicsPart, kJSPropertyAttributeDontDelete },
            { "isAnimationPhysicsPartAttached", Sprite_IsAnimationPhysicsPartAttached, kJSPropertyAttributeDontDelete },
            { "setAnimationPhysicsRoot", Sprite_SetAnimationPhysicsRoot, kJSPropertyAttributeDontDelete },
            { "getAnimationPhysicsRoot", Sprite_GetAnimationPhysicsRoot, kJSPropertyAttributeDontDelete },
            { "clearAnimationPhysicsRoot", Sprite_ClearAnimationPhysicsRoot, kJSPropertyAttributeDontDelete },
            { "getAnimationPhysicsSetupWarnings", Sprite_GetAnimationPhysicsSetupWarnings, kJSPropertyAttributeDontDelete },
            { "setAnimationPhysicsMode", Sprite_SetAnimationPhysicsMode, kJSPropertyAttributeDontDelete },
            { "getAnimationPhysicsMode", Sprite_GetAnimationPhysicsMode, kJSPropertyAttributeDontDelete },
            { "setAnimationPhysicsDriveSettings", Sprite_SetAnimationPhysicsDriveSettings, kJSPropertyAttributeDontDelete },
            { "getAnimationPhysicsDriveSettings", Sprite_GetAnimationPhysicsDriveSettings, kJSPropertyAttributeDontDelete },
            { "disableAnimationPhysics", Sprite_DisableAnimationPhysics, kJSPropertyAttributeDontDelete },
            { "isAnimationPhysicsEnabled", Sprite_IsAnimationPhysicsEnabled, kJSPropertyAttributeDontDelete },
            { "addAnimationDrawable", Sprite_AddAnimationDrawable, kJSPropertyAttributeDontDelete },
            { "removeAnimationDrawable", Sprite_RemoveAnimationDrawable, kJSPropertyAttributeDontDelete },
            { "clearAnimationDrawables", Sprite_ClearAnimationDrawables, kJSPropertyAttributeDontDelete },
            { "setAnimationDrawableEnabled", Sprite_SetAnimationDrawableEnabled, kJSPropertyAttributeDontDelete },
            { "getAnimationDrawableError", Sprite_GetAnimationDrawableError, kJSPropertyAttributeDontDelete },
            { "getAnimationDrawBounds", Sprite_GetAnimationDrawBounds, kJSPropertyAttributeDontDelete },
            { "_procedural", Sprite_ProceduralControl, kJSPropertyAttributeDontDelete },
            { "addAnimationIK", Sprite_AddAnimationIK, kJSPropertyAttributeDontDelete },
            { "setAnimationIKTarget", Sprite_SetAnimationIKTarget, kJSPropertyAttributeDontDelete },
            { "getAnimationIKResult", Sprite_GetAnimationIKResult, kJSPropertyAttributeDontDelete },
            { "addAnimationModifier", Sprite_AddAnimationModifier, kJSPropertyAttributeDontDelete },
            { "removeAnimationModifier", Sprite_RemoveAnimationModifier, kJSPropertyAttributeDontDelete },
            { "clearAnimationModifiers", Sprite_ClearAnimationModifiers, kJSPropertyAttributeDontDelete },
            { "getAnimationModifierError", Sprite_GetAnimationModifierError, kJSPropertyAttributeDontDelete },
            { "setAnimationSource", Sprite_SetAnimationSource, kJSPropertyAttributeDontDelete },
            { "getAnimationSource", Sprite_GetAnimationSource, kJSPropertyAttributeDontDelete },
            { "isAnimationDrawingSupported", Sprite_IsAnimationDrawingSupported, kJSPropertyAttributeDontDelete },
            { "setAnimationDebugDraw", Sprite_SetAnimationDebugDraw, kJSPropertyAttributeDontDelete },
            { "getAnimationDebugDraw", Sprite_GetAnimationDebugDraw, kJSPropertyAttributeDontDelete },
            { "enableAnimationPose", Sprite_EnableAnimationPose, kJSPropertyAttributeDontDelete },
            { "disableAnimationPose", Sprite_DisableAnimationPose, kJSPropertyAttributeDontDelete },
            { "isAnimationPoseEnabled", Sprite_IsAnimationPoseEnabled, kJSPropertyAttributeDontDelete },
            { "getAnimationRigError", Sprite_GetAnimationRigError, kJSPropertyAttributeDontDelete },
            { "getBone", Sprite_GetBone, kJSPropertyAttributeDontDelete },
            { "getAnimationBoneNames", Sprite_GetAnimationBoneNames, kJSPropertyAttributeDontDelete },
            { "getAnimationBindingNames", Sprite_GetAnimationBindingNames, kJSPropertyAttributeDontDelete },
            { "getAnimationBoneTransform", Sprite_GetAnimationBoneTransform, kJSPropertyAttributeDontDelete },
            { "getAnimationBindingTransform", Sprite_GetAnimationBindingTransform, kJSPropertyAttributeDontDelete },
            { "setAnimationBoneTransform", Sprite_SetAnimationBoneTransform, kJSPropertyAttributeDontDelete },
            { "clearAnimationBoneTransforms", Sprite_ClearAnimationBoneTransforms, kJSPropertyAttributeDontDelete },
            { "getAnimationPose", Sprite_GetAnimationPose, kJSPropertyAttributeDontDelete },
            { "sampleAnimationPose", Sprite_SampleAnimationPose, kJSPropertyAttributeDontDelete },
            { "hasAnimation", Sprite_HasAnimation, kJSPropertyAttributeDontDelete },
            { "startAnimation", Sprite_StartAnimation, kJSPropertyAttributeDontDelete },
            { "applyCharacterMap", Sprite_ApplyCharacterMap, kJSPropertyAttributeDontDelete },
            { "removeCharacterMap", Sprite_RemoveCharacterMap, kJSPropertyAttributeDontDelete },
            { "removeAllCharacterMaps", Sprite_RemoveAllCharacterMaps, kJSPropertyAttributeDontDelete },
            { "getAppliedCharacterMaps", Sprite_GetAppliedCharacterMaps, kJSPropertyAttributeDontDelete },
            { "enableSpriterEvents", Sprite_EnableSpriterEvents, kJSPropertyAttributeDontDelete },
            { "areSpriterEventsEnabled", Sprite_AreSpriterEventsEnabled, kJSPropertyAttributeDontDelete },
            { "blendToAnimation", Sprite_BlendToAnimation, kJSPropertyAttributeDontDelete },
            { "isBlending", Sprite_IsBlending, kJSPropertyAttributeDontDelete },
            { "getBlendProgress", Sprite_GetBlendProgress, kJSPropertyAttributeDontDelete },
            { "pauseAnimation", Sprite_PauseAnimation, kJSPropertyAttributeDontDelete },
            { "resumeAnimation", Sprite_ResumeAnimation, kJSPropertyAttributeDontDelete },
            { "stopAnimation", Sprite_StopAnimation, kJSPropertyAttributeDontDelete },
            { "isAnimationPlaying", Sprite_IsAnimationPlaying, kJSPropertyAttributeDontDelete },
            { "isAnimationPaused", Sprite_IsAnimationPaused, kJSPropertyAttributeDontDelete },
            { "getAnimationProgress", Sprite_GetAnimationProgress, kJSPropertyAttributeDontDelete },
            { "hasAttachPoint", Sprite_HasAttachPoint, kJSPropertyAttributeDontDelete },
            { "getAttachPoint", Sprite_GetAttachPoint, kJSPropertyAttributeDontDelete },
            { "attachSprite", Sprite_AttachSprite, kJSPropertyAttributeDontDelete },
            { "activateSubEntity", Sprite_ActivateSubEntity, kJSPropertyAttributeDontDelete },
            { "detachSprite", Sprite_DetachSprite, kJSPropertyAttributeDontDelete },
            { "getAttachedSprite", Sprite_GetAttachedSprite, kJSPropertyAttributeDontDelete },
            { "getSpriterCollisionBox", Sprite_GetSpriterCollisionBox, kJSPropertyAttributeDontDelete },
            { "isSpriterCollisionActive", Sprite_IsSpriterCollisionActive, kJSPropertyAttributeDontDelete },
            { "getSpriterCollisionBoxCount", Sprite_GetSpriterCollisionBoxCount, kJSPropertyAttributeDontDelete },
            { "getSpriterCollisionBoxName", Sprite_GetSpriterCollisionBoxName, kJSPropertyAttributeDontDelete },
#endif
            { "changeFramesImage", Sprite_ChangeFramesImage, kJSPropertyAttributeDontDelete },
            { "offsetFrameCenters", Sprite_OffsetFrameCenters, kJSPropertyAttributeDontDelete },
            { "getFrameCenterOffset", Sprite_GetFrameCenterOffset, kJSPropertyAttributeDontDelete },
            { "get""Opacity", Sprite_GetOpacity, kJSPropertyAttributeDontDelete },
            { "set""Opacity", Sprite_SetOpacity, kJSPropertyAttributeDontDelete },
            { "fadeTo", Sprite_FadeTo, kJSPropertyAttributeDontDelete },
            { "fadeIn", Sprite_FadeIn, kJSPropertyAttributeDontDelete },
            { "fadeOut", Sprite_FadeOut, kJSPropertyAttributeDontDelete },
            { "isBehind", Sprite_IsBehind, kJSPropertyAttributeDontDelete },
            { "getZOrder", Sprite_GetZOrder, kJSPropertyAttributeDontDelete },
            { "moveBehind", Sprite_MoveBehind, kJSPropertyAttributeDontDelete },
            { "moveInFrontOf", Sprite_MoveInFrontOf, kJSPropertyAttributeDontDelete },
            { "moveToFront", Sprite_MoveToFront, kJSPropertyAttributeDontDelete },
            { "moveToBack", Sprite_MoveToBack, kJSPropertyAttributeDontDelete },
            { "getLayer", Sprite_GetLayer, kJSPropertyAttributeDontDelete },
#ifndef PDG_NO_GUI
            { "setDrawHelper", Sprite_SetDrawHelper, kJSPropertyAttributeDontDelete },
            { "setPostDrawHelper", Sprite_SetPostDrawHelper, kJSPropertyAttributeDontDelete },
            { "get""WantsMouseOverEvents", Sprite_GetWantsMouseOverEvents, kJSPropertyAttributeDontDelete },
            { "set""WantsMouseOverEvents", Sprite_SetWantsMouseOverEvents, kJSPropertyAttributeDontDelete },
            { "get""WantsClickEvents", Sprite_GetWantsClickEvents, kJSPropertyAttributeDontDelete },
            { "set""WantsClickEvents", Sprite_SetWantsClickEvents, kJSPropertyAttributeDontDelete },
            { "get""MouseDetectMode", Sprite_GetMouseDetectMode, kJSPropertyAttributeDontDelete },
            { "set""MouseDetectMode", Sprite_SetMouseDetectMode, kJSPropertyAttributeDontDelete },
            { "get""WantsOffscreenEvents", Sprite_GetWantsOffscreenEvents, kJSPropertyAttributeDontDelete },
            { "set""WantsOffscreenEvents", Sprite_SetWantsOffscreenEvents, kJSPropertyAttributeDontDelete },
#endif
            { "on", Sprite_On, kJSPropertyAttributeDontDelete },
            { "onCollideSprite", Sprite_OnCollideSprite, kJSPropertyAttributeDontDelete },
            { "onCollideWall", Sprite_OnCollideWall, kJSPropertyAttributeDontDelete },
            { "onOffscreen", Sprite_OnOffscreen, kJSPropertyAttributeDontDelete },
            { "onOnscreen", Sprite_OnOnscreen, kJSPropertyAttributeDontDelete },
            { "onExitLayer", Sprite_OnExitLayer, kJSPropertyAttributeDontDelete },
            { "onAnimationLoop", Sprite_OnAnimationLoop, kJSPropertyAttributeDontDelete },
            { "onAnimationEnd", Sprite_OnAnimationEnd, kJSPropertyAttributeDontDelete },
            { "onAnimationPhysicsRecoveryComplete", Sprite_OnAnimationPhysicsRecoveryComplete, kJSPropertyAttributeDontDelete },
            { "onAnimationBlendComplete", Sprite_OnAnimationBlendComplete, kJSPropertyAttributeDontDelete },
            { "onFadeComplete", Sprite_OnFadeComplete, kJSPropertyAttributeDontDelete },
            { "onFadeInComplete", Sprite_OnFadeInComplete, kJSPropertyAttributeDontDelete },
            { "onFadeOutComplete", Sprite_OnFadeOutComplete, kJSPropertyAttributeDontDelete },
            { "onMouseEnter", Sprite_OnMouseEnter, kJSPropertyAttributeDontDelete },
            { "onMouseLeave", Sprite_OnMouseLeave, kJSPropertyAttributeDontDelete },
            { "onMouseDown", Sprite_OnMouseDown, kJSPropertyAttributeDontDelete },
            { "onMouseUp", Sprite_OnMouseUp, kJSPropertyAttributeDontDelete },
            { "onMouseClick", Sprite_OnMouseClick, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.finalize = Sprite_finalize;
            definition.className = "Sprite";
            definition.staticFunctions = Sprite_staticFunctions;
            definition.staticValues = Sprite_staticValues;
            definition.callAsConstructor = Sprite_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef Sprite_AddHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        IEventHandler* inHandler = 0;
        if (JSValueIsObjectOfClass(ctx, arguments[1 -1], IEventHandler_class()))
        {
            JSObjectRef inHandler_ = JSValueToObject(ctx, arguments[1 -1], exception);
            inHandler = IEventHandler_getCppObject(inHandler_);
        }
        if (!inHandler)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object derived from ""IEventHandler"" (""inHandler"")");
        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, arguments[0], "Dumping " "IEventHandler" " object:") );
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""inType"")");
        long inType = (argumentCount<2) ? pdg::all_events : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->addHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_RemoveHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        IEventHandler* inHandler = 0;
        if (JSValueIsObjectOfClass(ctx, arguments[1 -1], IEventHandler_class()))
        {
            JSObjectRef inHandler_ = JSValueToObject(ctx, arguments[1 -1], exception);
            inHandler = IEventHandler_getCppObject(inHandler_);
        }
        if (!inHandler)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object derived from ""IEventHandler"" (""inHandler"")");
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""inType"")");
        long inType = (argumentCount<2) ? pdg::all_events : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->removeHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->clear();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_BlockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->blockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_UnblockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->unblockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_PlayScript(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
            JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
            JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
            const char* name = (const char*)name_Mem.ptr;
            JSStringRelease(name_Str);
            self->playScript(name); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Batch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->batch(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_EndBatch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->endBatch(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Series(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->series(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_EndSeries(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->endSeries(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_AndAlso(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->andAlso(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Stagger(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""intervalSeconds"")");
            double intervalSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->stagger(intervalSeconds); return thisObject;
        }
        catch(const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Mark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if(argumentCount>2)
            {
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            }
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
            JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
            JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
            const char* name = (const char*)name_Mem.ptr;
            JSStringRelease(name_Str);
            if (argumentCount >= 2 && !JSValueIsBoolean(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""saveState"")");
            bool saveState = (argumentCount<2) ? true : JSValueToBoolean(ctx, arguments[2 -1]);
            self->mark(name, saveState); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_JumpToMark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if(argumentCount>2)
            {
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            }
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
            JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
            JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
            const char* name = (const char*)name_Mem.ptr;
            JSStringRelease(name_Str);
            if (argumentCount >= 2 && !JSValueIsBoolean(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""restoreState"")");
            bool restoreState = (argumentCount<2) ? true : JSValueToBoolean(ctx, arguments[2 -1]);
            self->jumpToMark(name, restoreState); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_When(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef evaluator = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!evaluator || !JSObjectIsFunction(ctx, evaluator) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""evaluator"")");
            self->when(MakeAnimationEvaluator(evaluator)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ScriptOn(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""event"")");
            JSStringRef event_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock event_Mem(JSStringGetMaximumUTF8CStringSize(event_Str));
            JSStringGetUTF8CString(event_Str, event_Mem.ptr, event_Mem.bytes);
            const char* event = (const char*)event_Mem.ptr;
            JSStringRelease(event_Str);
            JSObjectRef handler = JSValueToObject(ctx, arguments[2 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a function (""handler"")");
            self->on(event, MakeAnimationEventHandler(handler)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_OnStarted(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onStarted(MakeAnimationEventHandler(handler)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_TriggerEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
            JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
            JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
            const char* name = (const char*)name_Mem.ptr;
            JSStringRelease(name_Str);
            self->triggerEvent(name); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_OnFinished(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onFinished(MakeAnimationEventHandler(handler)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_OnScriptFinished(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onScriptFinished(MakeAnimationEventHandler(handler)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_OnMark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onMark(MakeAnimationEventHandler(handler)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_OnYoyo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onYoyo(MakeAnimationEventHandler(handler)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_OnRepeat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onRepeat(MakeAnimationEventHandler(handler)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_OnUntilFired(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onUntilFired(MakeAnimationEventHandler(handler)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Otherwise(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->otherwise(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_EndWhen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->endWhen(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_EndOtherwise(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->endOtherwise(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Until(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef evaluator = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!evaluator || !JSObjectIsFunction(ctx, evaluator) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""evaluator"")");
            self->until(MakeAnimationEvaluator(evaluator)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Yoyo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->yoyo(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Repeat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0, true);
            if (argumentCount>1)
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            }
            if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""countValue"")");
            double countValue = (argumentCount<1) ? -1 : JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount && (!std::isfinite(countValue) || countValue<0 || countValue>INT32_MAX || std::floor(countValue)!=countValue)) throw std::invalid_argument("Repeat count must be a nonnegative integer");
            self->repeat(static_cast<int>(countValue)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Diminish(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount>3)
            {
                if (argumentCount != 3)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
            }
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
            long easing = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
            self->diminish(factor, seconds, easingIdToFunc(easing)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Increase(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount>3)
            {
                if (argumentCount != 3)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
            }
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
            long easing = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
            self->increase(factor, seconds, easingIdToFunc(easing)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SlowDown(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount>3)
            {
                if (argumentCount != 3)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
            }
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
            long easing = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
            self->slowDown(factor, seconds, easingIdToFunc(easing)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SpeedUp(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount>3)
            {
                if (argumentCount != 3)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
            }
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
            long easing = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
            self->speedUp(factor, seconds, easingIdToFunc(easing)); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_StopIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopIt(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_RestartIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->restartIt(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_PauseIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->pauseIt(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ResumeIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->resumeIt(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetBoundingBox(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Rect value=self->getBoundingBox(); return JSC_RectToValue(ctx, value, exception);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetRotatedBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::RotatedRect value=self->getRotatedBounds(); return JSC_RectToValue(ctx, value, exception);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Point value=self->getLocation(); return JSC_PointToValue(ctx, value, exception);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Offset value=self->getMovement(); return JSC_OffsetToValue(ctx, value, exception);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Offset value=self->getSize(); return JSC_OffsetToValue(ctx, value, exception);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            double value=self->getWidth(); return JSValueMakeNumber(ctx, value);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            double value=self->getHeight(); return JSValueMakeNumber(ctx, value);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Offset value=self->getScale(); return JSC_OffsetToValue(ctx, value, exception);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Offset value=self->getStretching(); return JSC_OffsetToValue(ctx, value, exception);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            double value=self->getRotation(); return JSValueMakeNumber(ctx, value);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Offset value=self->getCenterOffset(); return JSC_OffsetToValue(ctx, value, exception);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            double value=self->getSpin(); return JSValueMakeNumber(ctx, value);
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Point value;
            auto isPoint = JSC_ValueIsPoint(ctx, arguments[0], value, exception);
            if (!isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (*isPoint)
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                self->setLocation(value); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                self->setLocation(x, y); return thisObject;
            }
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_MoveTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Point value;
            auto isPoint = JSC_ValueIsPoint(ctx, arguments[0], value, exception);
            if (!isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (*isPoint)
            {
                if (argumentCount == 1) { self->moveTo(value); return thisObject; }
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->moveTo(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount == 2) { self->moveTo(x, y); return thisObject; }
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->moveTo(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_MoveBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Offset value;
            auto converted = JSC_ValueIsOffset(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount == 1) { self->moveBy(value); return thisObject; }
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->moveBy(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount == 2) { self->moveBy(x, y); return thisObject; }
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->moveBy(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Vector value;
            auto converted = JSC_ValueIsVector(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                self->setMovement(value); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""xPerSecond"")");
                double xPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""yPerSecond"")");
                double yPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                self->setMovement(xPerSecond, yPerSecond); return thisObject;
            }
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ChangeMovementTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Vector value;
            auto converted = JSC_ValueIsVector(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeMovementTo(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""xPerSecond"")");
                double xPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""yPerSecond"")");
                double yPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeMovementTo(xPerSecond, yPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ChangeMovementBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Vector value;
            auto converted = JSC_ValueIsVector(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeMovementBy(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""xPerSecond"")");
                double xPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""yPerSecond"")");
                double yPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeMovementBy(xPerSecond, yPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Offset value;
            auto converted = JSC_ValueIsOffset(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                self->setSize(value); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""width"")");
                double width = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""height"")");
                double height = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                self->setSize(width, height); return thisObject;
            }
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ChangeCenterOffsetTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Offset value;
            auto converted = JSC_ValueIsOffset(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeCenterOffsetTo(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeCenterOffsetTo(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ChangeCenterOffsetBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Offset value;
            auto converted = JSC_ValueIsOffset(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeCenterOffsetBy(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeCenterOffsetBy(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setWidth(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setHeight(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setRotation(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setSpin(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setGrowing(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""widthPerSecond"")");
            double widthPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""heightPerSecond"")");
            double heightPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            self->setStretching(widthPerSecond, heightPerSecond); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            double y = (argumentCount<2) ? x : JSValueToNumber(ctx, arguments[2 -1], exception);
            self->setScale(x, y); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ChangeSpinTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radiansPerSecond"")");
            double radiansPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeSpinTo(radiansPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ChangeSpinBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radiansPerSecond"")");
            double radiansPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeSpinBy(radiansPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ChangeGrowingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""amountPerSecond"")");
            double amountPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeGrowingTo(amountPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ChangeGrowingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""amountPerSecond"")");
            double amountPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeGrowingBy(amountPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ChangeStretchingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""widthPerSecond"")");
            double widthPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""heightPerSecond"")");
            double heightPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeStretchingTo(widthPerSecond, heightPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ChangeStretchingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""widthPerSecond"")");
            double widthPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""heightPerSecond"")");
            double heightPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeStretchingBy(widthPerSecond, heightPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ChangeScaleTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            double x = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            double y = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeScaleTo(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ChangeScaleBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            double x = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            double y = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeScaleBy(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Grow(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount == 1) { self->grow(factor); return thisObject; }
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->grow(factor, durationSeconds, gEasingFunctions[easing]); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Stretch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""widthFactor"")");
            double widthFactor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""heightFactor"")");
            double heightFactor = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount == 2) { self->stretch(widthFactor, heightFactor); return thisObject; }
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->stretch(widthFactor, heightFactor, durationSeconds, gEasingFunctions[easing]); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ResizeBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""deltaWidth"")");
            double deltaWidth = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""deltaHeight"")");
            double deltaHeight = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount == 2) { self->resizeBy(deltaWidth, deltaHeight); return thisObject; }
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->resizeBy(deltaWidth, deltaHeight, durationSeconds, gEasingFunctions[easing]); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ResizeTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""width"")");
            double width = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""height"")");
            double height = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->resizeTo(width, height, durationSeconds, gEasingFunctions[easing]); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_RotateBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radians"")");
            double radians = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount == 1) { self->rotateBy(radians); return thisObject; }
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""directionValue"")");
            double directionValue = (argumentCount<4) ? static_cast<int>(rotationDirection_AsSpecified) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue || directionValue < 0 || directionValue > 3)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer rotation direction" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int direction = static_cast<int>(directionValue);
            self->rotateBy(radians, durationSeconds, gEasingFunctions[easing], direction); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_RotateTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radians"")");
            double radians = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount == 1) { self->rotateTo(radians); return thisObject; }
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""directionValue"")");
            double directionValue = (argumentCount<4) ? static_cast<int>(rotationDirection_AsSpecified) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue || directionValue < 0 || directionValue > 3)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer rotation direction" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int direction = static_cast<int>(directionValue);
            self->rotateTo(radians, durationSeconds, gEasingFunctions[easing], direction); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Offset offset;
            auto offset_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], offset, exception);
            if (!offset_isOffset.has_value()) { return JSValueMakeNull(ctx); }
            if (!*offset_isOffset)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
            };
            self->setCenterOffset(offset); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetFlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""flip"")");
            bool flip = JSValueToBoolean(ctx, arguments[1 -1]);
            self->setFlipX(flip); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_SetFlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""flip"")");
            bool flip = JSValueToBoolean(ctx, arguments[1 -1]);
            self->setFlipY(flip); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_StopMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopMovement(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_StopSpinning(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopSpinning(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_StopGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopGrowing(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_StopStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopStretching(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_PauseSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->pauseSchedule(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ResumeSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->resumeSchedule(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_CancelSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->cancelSchedule(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_FlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->flipX(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_FlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->flipY(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_AndThen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->andThen(); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_IsFlippedX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            try
            {
                ;
                if (argumentCount != 0)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                return JSValueMakeBoolean(ctx, self->isFlippedX());
            }
            catch (const std::exception& error)
            {
                {
                    JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                    JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                    JSStringRelease(errorMessage);
                    *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                    return JSValueMakeNull(ctx);
                };
            }
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_IsFlippedY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            try
            {
                ;
                if (argumentCount != 0)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                return JSValueMakeBoolean(ctx, self->isFlippedY());
            }
            catch (const std::exception& error)
            {
                {
                    JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                    JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                    JSStringRelease(errorMessage);
                    *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                    return JSValueMakeNull(ctx);
                };
            }
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_IsSchedulePaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            return JSValueMakeBoolean(ctx, self->isSchedulePaused());
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_HasScheduledAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            return JSValueMakeBoolean(ctx, self->hasScheduledAnimations());
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_Wait(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->wait(durationSeconds); return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_AddAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            self->mAnimatedScriptObj = thisObject;
            SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, arguments[0], "Dumping " "IAnimationHelper" " object:") );
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            IAnimationHelper* helper = 0;
            if (JSValueIsObjectOfClass(ctx, arguments[1 -1], IAnimationHelper_class()))
            {
                JSObjectRef helper_ = JSValueToObject(ctx, arguments[1 -1], exception);
                helper = IAnimationHelper_getCppObject(helper_);
            }
            if (!helper)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object derived from ""IAnimationHelper"" (""helper"")");
            self->addAnimationHelper(helper);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_RemoveAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            IAnimationHelper* helper = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef helper_ = JSValueToObject(ctx, arguments[1 -1], exception);
                helper = IAnimationHelper_getCppObject(helper_);
            }
            if (!helper)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""IAnimationHelper"" (""helper"")");
            self->removeAnimationHelper(helper);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Sprite_ClearAnimationHelpers(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->clearAnimationHelpers();
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }

    JSValueRef Sprite_GetMyClassTag(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        uint32 theMyClassTag = self->getMyClassTag();
        return JSValueMakeNumber(ctx, theMyClassTag);
    }
    JSValueRef Sprite_GetSerializedSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        Serializer* serializer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef serializer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            serializer = Serializer_getCppObject(serializer_);
        }
        if (!serializer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Serializer"" (""serializer"")");
        try
        {
            uint32 dataSize = self->getSerializedSize(serializer);
            return JSValueMakeNumber(ctx, dataSize);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_Serialize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        Serializer* serializer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef serializer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            serializer = Serializer_getCppObject(serializer_);
        }
        if (!serializer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Serializer"" (""serializer"")");
        try { self->serialize(serializer); return JSValueMakeUndefined(ctx); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_Deserialize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        Deserializer* deserializer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef deserializer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            deserializer = Deserializer_getCppObject(deserializer_);
        }
        if (!deserializer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Deserializer"" (""deserializer"")");
        try
        {
            self->deserialize(deserializer);
            return JSValueMakeUndefined(ctx);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(bad_tag& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(sync_error& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(unknown_object& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Sprite_GetWantsAnimLoopEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool theWantsAnimLoopEvents = self->getWantsAnimLoopEvents();
        return JSValueMakeBoolean(ctx, theWantsAnimLoopEvents);
    }
    JSValueRef Sprite_GetWantsAnimEndEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool theWantsAnimEndEvents = self->getWantsAnimEndEvents();
        return JSValueMakeBoolean(ctx, theWantsAnimEndEvents);
    }
    JSValueRef Sprite_GetWantsCollideWallEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool theWantsCollideWallEvents = self->getWantsCollideWallEvents();
        return JSValueMakeBoolean(ctx, theWantsCollideWallEvents);
    }
#ifndef PDG_NO_GUI

    JSValueRef Sprite_GetWantsMouseOverEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool theWantsMouseOverEvents = self->getWantsMouseOverEvents();
        return JSValueMakeBoolean(ctx, theWantsMouseOverEvents);
    }
    JSValueRef Sprite_GetWantsClickEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool theWantsClickEvents = self->getWantsClickEvents();
        return JSValueMakeBoolean(ctx, theWantsClickEvents);
    }
    JSValueRef Sprite_GetMouseDetectMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int theMouseDetectMode = self->getMouseDetectMode();
        return JSValueMakeNumber(ctx, theMouseDetectMode);
    }
    JSValueRef Sprite_GetWantsOffscreenEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool theWantsOffscreenEvents = self->getWantsOffscreenEvents();
        return JSValueMakeBoolean(ctx, theWantsOffscreenEvents);
    }
#endif

    JSValueRef Sprite_GetFrameRotatedBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""frameNum"")");
        long frameNum = (argumentCount<1) ? -1 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        pdg::RotatedRect r = self->getFrameRotatedBounds(frameNum);
        return JSC_RectToValue(ctx, r, exception);
    }
    JSValueRef Sprite_SetFrame(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""frame"")");
        int32 frame = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->setFrame(frame);
        return thisObject;
    }
    JSValueRef Sprite_GetCurrentFrame(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int frame = self->getCurrentFrame();
        return JSValueMakeNumber(ctx, frame);
    }
    JSValueRef Sprite_GetFrameCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int count = self->getFrameCount();
        return JSValueMakeNumber(ctx, count);
    }
    JSValueRef Sprite_StartFrameAnimation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""fps"")");
        double fps = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""startingFrame"")");
        long startingFrame = (argumentCount<2) ? Sprite::start_FromFirstFrame : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""numFrames"")");
        long numFrames = (argumentCount<3) ? Sprite::all_Frames : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
        if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""animateFlags"")");
        long animateFlags = (argumentCount<4) ? Sprite::animate_Looping : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[4 -1], exception));
        self->startFrameAnimation(fps, startingFrame, numFrames, animateFlags);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_StopFrameAnimation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->stopFrameAnimation();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_SetWantsAnimLoopEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""wantsThem"")");
        bool wantsThem = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setWantsAnimLoopEvents(wantsThem);
        return thisObject;
    }
    JSValueRef Sprite_SetWantsAnimEndEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""wantsThem"")");
        bool wantsThem = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setWantsAnimEndEvents(wantsThem);
        return thisObject;
    }
    JSValueRef Sprite_SetWantsCollideWallEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""wantsThem"")");
        bool wantsThem = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setWantsCollideWallEvents(wantsThem);
        return thisObject;
    }
    JSValueRef Sprite_AddFramesImage(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        Image* image = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef image_ = JSValueToObject(ctx, arguments[1 -1], exception);
            image = Image_getCppObject(image_);
        }
        if (!image)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Image"" (""image"")");
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""startingFrame"")");
        long startingFrame = (argumentCount<2) ? Sprite::start_FromFirstFrame : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""numFrames"")");
        long numFrames = (argumentCount<3) ? Sprite::all_Frames : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
        self->addFramesImage(image, startingFrame, numFrames);
        return JSValueMakeUndefined(ctx);
    }
#ifdef PDG_SPRITER_SUPPORT
    JSValueRef Sprite_HasAnimation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        bool hasIt = false;
        if (JSValueIsString(ctx, arguments[0]))
        {
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""animationName"")");
            JSStringRef animationName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock animationName_Mem(JSStringGetMaximumUTF8CStringSize(animationName_Str));
            JSStringGetUTF8CString(animationName_Str, animationName_Mem.ptr, animationName_Mem.bytes);
            const char* animationName = (const char*)animationName_Mem.ptr;
            JSStringRelease(animationName_Str);
            hasIt = self->hasAnimation(animationName);
        }
        else
        {
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""animationId"")");
            double animationId = JSValueToNumber(ctx, arguments[1 -1], exception);
            hasIt = std::isfinite(animationId) && animationId >= 0 && animationId <= 4294967295.0
                && animationId == std::floor(animationId) && self->hasAnimation(static_cast<uint32>(animationId));
        }
        return JSValueMakeBoolean(ctx, hasIt);
    }
    JSValueRef Sprite_StartAnimation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (JSValueIsString(ctx, arguments[0]))
        {
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""animationName"")");
            JSStringRef animationName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock animationName_Mem(JSStringGetMaximumUTF8CStringSize(animationName_Str));
            JSStringGetUTF8CString(animationName_Str, animationName_Mem.ptr, animationName_Mem.bytes);
            const char* animationName = (const char*)animationName_Mem.ptr;
            JSStringRelease(animationName_Str);
            self->startAnimation(animationName);
        }
        else
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""animationId"")");
            uint32 animationId = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
            self->startAnimation(animationId);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_ApplyCharacterMap(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""mapName"")");
        JSStringRef mapName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock mapName_Mem(JSStringGetMaximumUTF8CStringSize(mapName_Str));
        JSStringGetUTF8CString(mapName_Str, mapName_Mem.ptr, mapName_Mem.bytes);
        const char* mapName = (const char*)mapName_Mem.ptr;
        JSStringRelease(mapName_Str);
        self->applyCharacterMap(mapName);
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_RemoveCharacterMap(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""mapName"")");
        JSStringRef mapName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock mapName_Mem(JSStringGetMaximumUTF8CStringSize(mapName_Str));
        JSStringGetUTF8CString(mapName_Str, mapName_Mem.ptr, mapName_Mem.bytes);
        const char* mapName = (const char*)mapName_Mem.ptr;
        JSStringRelease(mapName_Str);
        self->removeCharacterMap(mapName);
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_RemoveAllCharacterMaps(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->removeAllCharacterMaps();
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_GetAppliedCharacterMaps(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        std::vector<std::string> maps = self->getAppliedCharacterMaps();

#ifdef PDG_USING_JAVASCRIPT_CORE
        JSObjectRef arr = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t i = 0; i < maps.size(); i++)
        {
            JSObjectSetPropertyAtIndex(ctx, arr, (unsigned)i, JSC_MakeValueFromCString(ctx, maps[i].c_str()), exception);
        }
#else
        v8::Local<v8::Array> arr = v8::Array::New(isolate);
        for (size_t i = 0; i < maps.size(); i++)
        {
            arr->Set(isolate->GetCurrentContext(), v8::Integer::New(isolate, i),
                v8::String::NewFromUtf8(isolate, maps[i].c_str()).ToLocalChecked()).ToChecked();
        }
#endif
        return arr;
    }

    JSValueRef Sprite_EnableSpriterEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""enable"")");
        bool enable = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->enableSpriterEvents(enable);
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_AreSpriterEventsEnabled(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool enabled = self->areSpriterEventsEnabled();
        return JSValueMakeBoolean(ctx, enabled);
    }

    JSValueRef Sprite_BlendToAnimation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""blendTime"")");
        double blendTime = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (JSValueIsString(ctx, arguments[0]))
        {
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""animationName"")");
            JSStringRef animationName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock animationName_Mem(JSStringGetMaximumUTF8CStringSize(animationName_Str));
            JSStringGetUTF8CString(animationName_Str, animationName_Mem.ptr, animationName_Mem.bytes);
            const char* animationName = (const char*)animationName_Mem.ptr;
            JSStringRelease(animationName_Str);
            self->blendToAnimation(animationName, blendTime);
        }
        else
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""animationId"")");
            uint32 animationId = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
            self->blendToAnimation(animationId, blendTime);
        }
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_IsBlending(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool blending = self->isBlending();
        return JSValueMakeBoolean(ctx, blending);
    }

    JSValueRef Sprite_GetBlendProgress(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float progress = self->getBlendProgress();
        return JSValueMakeNumber(ctx, progress);
    }

    JSValueRef Sprite_PauseAnimation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->pauseAnimation();
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_ResumeAnimation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->resumeAnimation();
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_StopAnimation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->stopAnimation();
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_IsAnimationPlaying(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool playing = self->isAnimationPlaying();
        return JSValueMakeBoolean(ctx, playing);
    }

    JSValueRef Sprite_IsAnimationPaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool paused = self->isAnimationPaused();
        return JSValueMakeBoolean(ctx, paused);
    }

    JSValueRef Sprite_GetAnimationProgress(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float progress = self->getAnimationProgress();
        return JSValueMakeNumber(ctx, progress);
    }

    JSValueRef Sprite_HasAttachPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""attachPointName"")");
        JSStringRef attachPointName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock attachPointName_Mem(JSStringGetMaximumUTF8CStringSize(attachPointName_Str));
        JSStringGetUTF8CString(attachPointName_Str, attachPointName_Mem.ptr, attachPointName_Mem.bytes);
        const char* attachPointName = (const char*)attachPointName_Mem.ptr;
        JSStringRelease(attachPointName_Str);
        bool hasPoint = self->hasAttachPoint(attachPointName);
        return JSValueMakeBoolean(ctx, hasPoint);
    }

    JSValueRef Sprite_GetAttachPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""attachPointName"")");
        JSStringRef attachPointName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock attachPointName_Mem(JSStringGetMaximumUTF8CStringSize(attachPointName_Str));
        JSStringGetUTF8CString(attachPointName_Str, attachPointName_Mem.ptr, attachPointName_Mem.bytes);
        const char* attachPointName = (const char*)attachPointName_Mem.ptr;
        JSStringRelease(attachPointName_Str);
        pdg::Offset offset = self->getAttachPoint(attachPointName);
        return JSC_OffsetToValue(ctx, offset, exception);
    }

    JSValueRef Sprite_AttachSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        Sprite* sprite = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef sprite_ = JSValueToObject(ctx, arguments[1 -1], exception);
            sprite = Sprite_getCppObject(sprite_);
        }
        if (!sprite)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Sprite"" (""sprite"")");
        if (!JSValueIsString(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a string (""attachPointName"")");
        JSStringRef attachPointName_Str = JSValueToStringCopy(ctx, arguments[2 -1], exception);
        MemBlock attachPointName_Mem(JSStringGetMaximumUTF8CStringSize(attachPointName_Str));
        JSStringGetUTF8CString(attachPointName_Str, attachPointName_Mem.ptr, attachPointName_Mem.bytes);
        const char* attachPointName = (const char*)attachPointName_Mem.ptr;
        JSStringRelease(attachPointName_Str);
        self->attachSprite(sprite, attachPointName);
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_DetachSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        Sprite* sprite = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef sprite_ = JSValueToObject(ctx, arguments[1 -1], exception);
            sprite = Sprite_getCppObject(sprite_);
        }
        if (!sprite)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Sprite"" (""sprite"")");
        self->detachSprite(sprite);
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_GetAttachedSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""attachPointName"")");
        JSStringRef attachPointName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock attachPointName_Mem(JSStringGetMaximumUTF8CStringSize(attachPointName_Str));
        JSStringGetUTF8CString(attachPointName_Str, attachPointName_Mem.ptr, attachPointName_Mem.bytes);
        const char* attachPointName = (const char*)attachPointName_Mem.ptr;
        JSStringRelease(attachPointName_Str);
        pdg::Sprite* attached = self->getAttachedSprite(attachPointName);
        if (attached)
        {
            if (!attached) return JSValueMakeNull(ctx);
            return Sprite_newFromCpp(ctx, attached);;
        }
        else
        {
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Sprite_ActivateSubEntity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""entityName"")");
        JSStringRef entityName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock entityName_Mem(JSStringGetMaximumUTF8CStringSize(entityName_Str));
        JSStringGetUTF8CString(entityName_Str, entityName_Mem.ptr, entityName_Mem.bytes);
        const char* entityName = (const char*)entityName_Mem.ptr;
        JSStringRelease(entityName_Str);
        if (argumentCount >= 2 && !JSValueIsString(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a string (""animationName"")");
        JSStringRef animationName_Str = (argumentCount >= 2) ? JSValueToStringCopy(ctx, arguments[2 -1], exception) : 0;
        MemBlock animationName_Mem((argumentCount >= 2) ? JSStringGetMaximumUTF8CStringSize(animationName_Str) : 0);
        if (argumentCount >= 2)
        {
            JSStringGetUTF8CString(animationName_Str, animationName_Mem.ptr, animationName_Mem.bytes); JSStringRelease(animationName_Str);
        }
        const char* animationName = (argumentCount < 2) ? "idle" : (const char*)animationName_Mem.ptr;
        self->activateSubEntity(entityName, animationName);
        return JSValueMakeUndefined(ctx);
    }
#endif
#ifndef PDG_NO_GUI
    JSValueRef Sprite_SetWantsOffscreenEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""wantsThem"")");
        bool wantsThem = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setWantsOffscreenEvents(wantsThem);
        return thisObject;
    }
    JSValueRef Sprite_SetDrawHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        self->mSpriteScriptObj = thisObject;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        ISpriteDrawHelper* helper = 0;
        if (JSValueIsObjectOfClass(ctx, arguments[1 -1], ISpriteDrawHelper_class()))
        {
            JSObjectRef helper_ = JSValueToObject(ctx, arguments[1 -1], exception);
            helper = ISpriteDrawHelper_getCppObject(helper_);
        }
        if (!helper && !JSValueIsNull(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "null or an object derived from ""ISpriteDrawHelper"" (""helper"")");
        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, arguments[0], "Dumping " "ISpriteDrawHelper" " object:") )
            self->setDrawHelper(helper);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_SetPostDrawHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        self->mSpriteScriptObj = thisObject;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        ISpriteDrawHelper* helper = 0;
        if (JSValueIsObjectOfClass(ctx, arguments[1 -1], ISpriteDrawHelper_class()))
        {
            JSObjectRef helper_ = JSValueToObject(ctx, arguments[1 -1], exception);
            helper = ISpriteDrawHelper_getCppObject(helper_);
        }
        if (!helper && !JSValueIsNull(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "null or an object derived from ""ISpriteDrawHelper"" (""helper"")");
        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, arguments[0], "Dumping " "ISpriteDrawHelper" " object:") )
            self->setPostDrawHelper(helper);
        return JSValueMakeUndefined(ctx);
    }
#endif
    JSValueRef Sprite_ChangeFramesImage(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        Image* oldImage = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef oldImage_ = JSValueToObject(ctx, arguments[1 -1], exception);
            oldImage = Image_getCppObject(oldImage_);
        }
        if (!oldImage)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Image"" (""oldImage"")");
        Image* newImage = 0;
        if (JSValueIsObject(ctx, arguments[2 -1]))
        {
            JSObjectRef newImage_ = JSValueToObject(ctx, arguments[2 -1], exception);
            newImage = Image_getCppObject(newImage_);
        }
        if (!newImage)
            return JSC_ThrowArgTypeException(ctx, exception, 2, "an object of type ""Image"" (""newImage"")");
        self->changeFramesImage(oldImage, newImage);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_OffsetFrameCenters(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""offsetX"")");
        int32 offsetX = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""offsetY"")");
        int32 offsetY = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        Image* image = 0;
        if (argumentCount >= 3)
        {
            if (!JSValueIsObjectOfClass(ctx, arguments[3 -1], Image_class()))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 3, "an object of type ""Image"" (""image"")");
            }
            else
            {
                JSObjectRef image_ = JSValueToObject(ctx, arguments[3 -1], exception);
                image = Image_getCppObject(image_);
            }
        };
        if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""startingFrame"")");
        long startingFrame = (argumentCount<4) ? Sprite::start_FromFirstFrame : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[4 -1], exception));
        if (argumentCount >= 5 && !JSValueIsNumber(ctx, arguments[5 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""numFrames"")");
        long numFrames = (argumentCount<5) ? Sprite::all_Frames : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[5 -1], exception));
        self->offsetFrameCenters(offsetX, offsetY, image, startingFrame, numFrames);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_GetFrameCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        Image* image = 0;
        if (argumentCount >= 1)
        {
            if (!JSValueIsObjectOfClass(ctx, arguments[1 -1], Image_class()))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Image"" (""image"")");
            }
            else
            {
                JSObjectRef image_ = JSValueToObject(ctx, arguments[1 -1], exception);
                image = Image_getCppObject(image_);
            }
        };
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""frameNum"")");
        long frameNum = (argumentCount<2) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        pdg::Offset offset = self->getFrameCenterOffset(image, frameNum);
        return JSC_OffsetToValue(ctx, offset, exception);
    }
    JSValueRef Sprite_SetOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""opacity"")");
        double opacity = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->setOpacity(opacity);
        return thisObject;
    }
    JSValueRef Sprite_GetOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float opacity = self->getOpacity();
        return JSValueMakeNumber(ctx, opacity);
    }
    JSValueRef Sprite_FadeTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""targetOpacity"")");
        double targetOpacity = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
        double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
        long easing = (argumentCount<3) ? EasingFuncRef::linearTween : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeTo(targetOpacity, durationSeconds, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeTo(targetOpacity, durationSeconds);
        }
        return thisObject;
    }
    JSValueRef Sprite_FadeIn(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""durationSeconds"")");
        double durationSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""easing"")");
        long easing = (argumentCount<2) ? EasingFuncRef::linearTween : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeIn(durationSeconds, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeIn(durationSeconds);
        }
        return thisObject;
    }
    JSValueRef Sprite_FadeOut(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""durationSeconds"")");
        double durationSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""easing"")");
        long easing = (argumentCount<2) ? EasingFuncRef::linearTween : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeOut(durationSeconds, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeOut(durationSeconds);
        }
        return thisObject;
    }
    JSValueRef Sprite_IsBehind(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        Sprite* sprite = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef sprite_ = JSValueToObject(ctx, arguments[1 -1], exception);
            sprite = Sprite_getCppObject(sprite_);
        }
        if (!sprite)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Sprite"" (""sprite"")");
        bool behind = self->isBehind(sprite);
        return JSValueMakeBoolean(ctx, behind);
    }
    JSValueRef Sprite_GetZOrder(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int zorder = self->getZOrder();
        return JSValueMakeNumber(ctx, zorder);
    }
    JSValueRef Sprite_MoveBehind(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        Sprite* sprite = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef sprite_ = JSValueToObject(ctx, arguments[1 -1], exception);
            sprite = Sprite_getCppObject(sprite_);
        }
        if (!sprite)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Sprite"" (""sprite"")");
        self->moveBehind(sprite);
        return thisObject;
    }
    JSValueRef Sprite_MoveInFrontOf(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        Sprite* sprite = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef sprite_ = JSValueToObject(ctx, arguments[1 -1], exception);
            sprite = Sprite_getCppObject(sprite_);
        }
        if (!sprite)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Sprite"" (""sprite"")");
        self->moveInFrontOf(sprite);
        return thisObject;
    }
    JSValueRef Sprite_MoveToFront(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->moveToFront();
        return thisObject;
    }
    JSValueRef Sprite_MoveToBack(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->moveToBack();
        return thisObject;
    }
    JSValueRef Sprite_SetupFrameCollider(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""modeValue"")");
            double modeValue = (argumentCount<1) ? static_cast<double>(frameCollider_AlphaMask) : JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""threshold"")");
            double threshold = (argumentCount<2) ? 128 : JSValueToNumber(ctx, arguments[2 -1], exception);
            if(!std::isfinite(modeValue) || modeValue<0 || modeValue>std::numeric_limits<int>::max() || std::floor(modeValue)!=modeValue)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer frameCollider mode" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int mode=static_cast<int>(modeValue);
            if((mode!=frameCollider_Bounds && mode!=frameCollider_AlphaMask) || !std::isfinite(threshold) || threshold<1 || threshold>255 || std::floor(threshold)!=threshold)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected a frameCollider mode and an integer alpha threshold from 1 to 255" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto* result=&self->setupFrameCollider(mode,threshold); if (!result) return JSValueMakeNull(ctx);
            if (!result->mColliderScriptObj)
            {
                return Collider_newFromCpp(ctx, result);
            }
            else
            {
                return result->mColliderScriptObj;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_SetupAnimationCollider(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* result=&self->setupAnimationCollider(); if (!result) return JSValueMakeNull(ctx);
            if (!result->mColliderScriptObj)
            {
                return Collider_newFromCpp(ctx, result);
            }
            else
            {
                return result->mColliderScriptObj;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_SetFrameCollisionMask(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2); Image* image = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef image_ = JSValueToObject(ctx, arguments[1 -1], exception);
                image = Image_getCppObject(image_);
            }
            if (!image)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Image"" (""image"")"); Image* mask=nullptr; if(!JSValueIsNull(ctx, arguments[1]))
            {
                Image* value = 0;
                if (JSValueIsObject(ctx, arguments[2 -1]))
                {
                    JSObjectRef value_ = JSValueToObject(ctx, arguments[2 -1], exception);
                    value = Image_getCppObject(value_);
                }
                if (!value)
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "an object of type ""Image"" (""value"")"); mask=value;
            }
            self->setFrameCollisionMask(image,mask); return thisObject;
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
#ifndef PDG_NO_GUI
    JSValueRef Sprite_SetWantsMouseOverEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""wantsThem"")");
        bool wantsThem = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setWantsMouseOverEvents(wantsThem);
        return thisObject;
    }
    JSValueRef Sprite_SetWantsClickEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""wantsThem"")");
        bool wantsThem = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]);
        self->setWantsClickEvents(wantsThem);
        return thisObject;
    }
    JSValueRef Sprite_SetMouseDetectMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""collisionType"")");
        long collisionType = (argumentCount<1) ? Sprite::collide_BoundingBox : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->setMouseDetectMode(collisionType);
        return thisObject;
    }
#endif
    JSValueRef Sprite_GetLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        SpriteLayer* layer = self->getLayer();
        if (!layer) return JSValueMakeNull(ctx);
        if (!layer->mSpriteLayerScriptObj)
        {
            return SpriteLayer_newFromCpp(ctx, layer);
        }
        else
        {
            return layer->mSpriteLayerScriptObj;
        };
    }
    JSValueRef Sprite_On(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if(JSValueIsString(ctx, arguments[0]))
        {
            self->mAnimatedScriptObj = thisObject;
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""event"")");
            JSStringRef event_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock event_Mem(JSStringGetMaximumUTF8CStringSize(event_Str));
            JSStringGetUTF8CString(event_Str, event_Mem.ptr, event_Mem.bytes);
            const char* event = (const char*)event_Mem.ptr;
            JSStringRelease(event_Str);
            JSObjectRef handler = JSValueToObject(ctx, arguments[2 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a function (""handler"")");
            try { self->on(event,MakeAnimationEventHandler(handler)); return thisObject; }
            catch(const std::exception& error)
            {
                {
                    JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                    JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                    JSStringRelease(errorMessage);
                    *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                    return JSValueMakeNull(ctx);
                };
            }
        }
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""eventCode"")");
        int32 eventCode = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        JSObjectRef func = JSValueToObject(ctx, arguments[2 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a function (""func"")");
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) return JSValueMakeNull(ctx);
        long evtCode;
        if (eventCode <= pdg::Sprite::action_CollideWall)
        {
            evtCode = pdg::eventType_SpriteCollide;
        }
        else if (eventCode <= pdg::Sprite::action_FadeOutComplete)
        {
            evtCode = pdg::eventType_SpriteAnimate;
        }
        else
        {
            evtCode = pdg::eventType_SpriteTouch;
        }
        self->addHandler(handler, evtCode);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnCollideSprite(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler)
        {
            DEBUG_ONLY( OS::_DOUT("OnCollideSprite: failed to create handler"); )
                return JSValueMakeNull(ctx);
        }
        self->addHandler(handler, pdg::eventType_SpriteCollide);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnCollideWall(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteCollide);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnOffscreen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Offscreen);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnOnscreen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Onscreen);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnExitLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_ExitLayer);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnAnimationLoop(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnAnimationEnd(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationEnd);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnAnimationBlendComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationBlendComplete);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }
    JSValueRef Sprite_OnAnimationPhysicsRecoveryComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationPhysicsRecoveryComplete);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnFadeComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeComplete);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnFadeInComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeInComplete);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnFadeOutComplete(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeOutComplete);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnMouseEnter(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseEnter);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnMouseLeave(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseLeave);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnMouseDown(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseDown);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnMouseUp(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseUp);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

    JSValueRef Sprite_OnMouseClick(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!func || !JSObjectIsFunction(ctx, func) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseClick);
        if (!handler) return JSValueMakeNull(ctx);
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) return JSValueMakeNull(ctx);
        if (!handler->mIEventHandlerScriptObj)
        {
            return IEventHandler_newFromCpp(ctx, handler);
        }
        else
        {
            return handler->mIEventHandlerScriptObj;
        };
    }

#ifdef PDG_SPRITER_SUPPORT
    JSValueRef Sprite_GetSpriterCollisionBox(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""boxName"")");
        JSStringRef boxName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock boxName_Mem(JSStringGetMaximumUTF8CStringSize(boxName_Str));
        JSStringGetUTF8CString(boxName_Str, boxName_Mem.ptr, boxName_Mem.bytes);
        const char* boxName = (const char*)boxName_Mem.ptr;
        JSStringRelease(boxName_Str);
        pdg::RotatedRect rect = self->getSpriterCollisionBox(boxName);
        return JSC_RectToValue(ctx, rect, exception);
    }

    JSValueRef Sprite_IsSpriterCollisionActive(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""boxName"")");
        JSStringRef boxName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock boxName_Mem(JSStringGetMaximumUTF8CStringSize(boxName_Str));
        JSStringGetUTF8CString(boxName_Str, boxName_Mem.ptr, boxName_Mem.bytes);
        const char* boxName = (const char*)boxName_Mem.ptr;
        JSStringRelease(boxName_Str);
        bool active = self->isSpriterCollisionActive(boxName);
        return JSValueMakeBoolean(ctx, active);
    }

    JSValueRef Sprite_GetSpriterCollisionBoxCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int count = self->getSpriterCollisionBoxCount();
        return JSValueMakeNumber(ctx, count);
    }

    JSValueRef Sprite_GetSpriterCollisionBoxName(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
        int32 index = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        const char* name = self->getSpriterCollisionBoxName(index);
        if (name)
        {
            return JSC_MakeValueFromCString(ctx, name);
        }
        else
        {
            return JSValueMakeNull(ctx);
        }
    }
#endif

#ifdef PDG_SPRITER_SUPPORT
    JSValueRef Sprite_DisableAnimationPose(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->disableAnimationPose();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_ClearAnimationBoneTransforms(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->clearAnimationBoneTransforms();
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_SeekAnimation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2); if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""clip"")");
        JSStringRef clip_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock clip_Mem(JSStringGetMaximumUTF8CStringSize(clip_Str));
        JSStringGetUTF8CString(clip_Str, clip_Mem.ptr, clip_Mem.bytes);
        const char* clip = (const char*)clip_Mem.ptr;
        JSStringRelease(clip_Str); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""timeSeconds"")");
        double timeSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        try {self->seekAnimation(clip,timeSeconds);}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_TransitionToAnimation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3); if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""clip"")");
        JSStringRef clip_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock clip_Mem(JSStringGetMaximumUTF8CStringSize(clip_Str));
        JSStringGetUTF8CString(clip_Str, clip_Mem.ptr, clip_Mem.bytes);
        const char* clip = (const char*)clip_Mem.ptr;
        JSStringRelease(clip_Str); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""timeSeconds"")");
        double timeSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
        double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
        try {self->transitionToAnimation(clip,timeSeconds,durationSeconds);}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_IsAnimationTransitioning(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isAnimationTransitioning());
    }
    JSValueRef Sprite_GetAnimationTransitionProgress(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getAnimationTransitionProgress());
    }

    JSValueRef Sprite_SupportsAnimationPhysics(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);return JSValueMakeBoolean(ctx, self->supportsAnimationPhysics());
    }
    JSValueRef Sprite_IsAnimationPhysicsEnabled(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);return JSValueMakeBoolean(ctx, self->isAnimationPhysicsEnabled());
    }
    JSValueRef Sprite_SetupAnimationPhysics(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        try{self->setupAnimationPhysics(decodeAnimationPhysicsDefinition(animationPhysicsValues(PDG_POSE_SCRIPT_ARGUMENTS,arguments[0])));}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_SetupPhysicsFromAnimationRig(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""mass"")");
        double mass = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""units"")");
        double units = (argumentCount<2) ? 1 : JSValueToNumber(ctx, arguments[2 -1], exception);
        try { self->setupPhysicsFromAnimationRig(mass,units); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        return thisObject;
    }
    JSValueRef Sprite_AttachAnimationPhysicsPart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);Part* part = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef part_ = JSValueToObject(ctx, arguments[1 -1], exception);
            part = Part_getCppObject(part_);
        }
        if (!part)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Part"" (""part"")");
        Part* parent=nullptr;
        if(argumentCount>1 && !JSValueIsNull(ctx, arguments[1]))
        {
            Part* value = 0;
            if (JSValueIsObject(ctx, arguments[2 -1]))
            {
                JSObjectRef value_ = JSValueToObject(ctx, arguments[2 -1], exception);
                value = Part_getCppObject(value_);
            }
            if (!value)
                return JSC_ThrowArgTypeException(ctx, exception, 2, "an object of type ""Part"" (""value"")");parent=value;
        }
        try { self->attachAnimationPhysicsPart(part,parent); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        return thisObject;
    }
    JSValueRef Sprite_DetachAnimationPhysicsPart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);Part* part = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef part_ = JSValueToObject(ctx, arguments[1 -1], exception);
            part = Part_getCppObject(part_);
        }
        if (!part)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Part"" (""part"")");if (argumentCount >= 2 && !JSValueIsBoolean(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""descendants"")");
        bool descendants = (argumentCount<2) ? true : JSValueToBoolean(ctx, arguments[2 -1]);
        try { self->detachAnimationPhysicsPart(part,descendants); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        return thisObject;
    }
    JSValueRef Sprite_IsAnimationPhysicsPartAttached(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);Part* part = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef part_ = JSValueToObject(ctx, arguments[1 -1], exception);
            part = Part_getCppObject(part_);
        }
        if (!part)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Part"" (""part"")");return JSValueMakeBoolean(ctx, self->isAnimationPhysicsPartAttached(part));
    }
    JSValueRef Sprite_SetAnimationPhysicsRoot(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""bone"")");
        uint32 bone = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
        try { self->setAnimationPhysicsRoot(bone); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        return thisObject;
    }
    JSValueRef Sprite_GetAnimationPhysicsRoot(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try { return JSValueMakeNumber(ctx, self->getAnimationPhysicsRoot()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_ClearAnimationPhysicsRoot(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try { self->clearAnimationPhysicsRoot(); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        return thisObject;
    }
    JSValueRef Sprite_GetAnimationPhysicsSetupWarnings(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        auto names = self->getAnimationPhysicsSetupWarnings();
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t i = 0; i < names.size(); ++i) JSObjectSetPropertyAtIndex(ctx, result, i, JSC_MakeValueFromCString(ctx, names[i].c_str()), exception);
#else
        auto result = v8::Array::New(isolate);
        for (size_t i = 0; i < names.size(); ++i) (void)result->Set(isolate->GetCurrentContext(), i, JSC_MakeValueFromCString(ctx, names[i].c_str())).ToChecked();
#endif
        return result;
    }
    JSValueRef Sprite_SetAnimationPhysicsMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 5)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 5); if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""mode"")");
        int32 mode = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception)); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""bone"")");
        double bone = JSValueToNumber(ctx, arguments[2 -1], exception); if (!JSValueIsBoolean(ctx, arguments[3 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 3, "a boolean (""descendants"")");
        bool descendants = JSValueToBoolean(ctx, arguments[3 -1]); if (argumentCount < 4 || !JSValueIsNumber(ctx, arguments[4 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[4 -1], exception); if (!JSValueIsNumber(ctx, arguments[5 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""direction"")");
        int32 direction = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[5 -1], exception));
        try { if(bone<0)self->setAnimationPhysicsMode(mode,seconds,direction);else self->setAnimationPhysicsMode(mode,AnimationBoneId(bone),descendants,seconds,direction); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        } return thisObject;
    }
    JSValueRef Sprite_GetAnimationPhysicsMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""bone"")");
        double bone = JSValueToNumber(ctx, arguments[1 -1], exception); if (!JSValueIsBoolean(ctx, arguments[2 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""descendants"")");
        bool descendants = JSValueToBoolean(ctx, arguments[2 -1]);
        try { return JSValueMakeNumber(ctx, bone<0?self->getAnimationPhysicsMode():self->getAnimationPhysicsMode(AnimationBoneId(bone),descendants)); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_SetAnimationPhysicsDriveSettings(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 7)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 7); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""force"")");
        double force = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""torque"")");
        double torque = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""frequency"")");
        double frequency = JSValueToNumber(ctx, arguments[3 -1], exception); if (argumentCount < 4 || !JSValueIsNumber(ctx, arguments[4 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""damping"")");
        double damping = JSValueToNumber(ctx, arguments[4 -1], exception); if (!JSValueIsNumber(ctx, arguments[5 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""direction"")");
        int32 direction = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[5 -1], exception)); if (argumentCount < 6 || !JSValueIsNumber(ctx, arguments[6 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 6, "a number (""bone"")");
        double bone = JSValueToNumber(ctx, arguments[6 -1], exception); if (!JSValueIsBoolean(ctx, arguments[7 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 7, "a boolean (""descendants"")");
        bool descendants = JSValueToBoolean(ctx, arguments[7 -1]);
        try
        {
            AnimationPhysicsDriveSettings settings
            {
                force,torque,frequency,damping,int(direction)
            };
            if(bone<0)self->setAnimationPhysicsDriveSettings(settings);else self->setAnimationPhysicsDriveSettings(settings,AnimationBoneId(bone),descendants);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        } return thisObject;
    }
    JSValueRef Sprite_GetAnimationPhysicsDriveSettings(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""bone"")");
        uint32 bone = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
        try
        {
            const auto settings=self->getAnimationPhysicsDriveSettings(bone);
            if(!settings) return JSValueMakeNull(ctx);
            const double values[]={settings->maxForce,settings->maxTorque,settings->frequency,settings->dampingRatio,double(settings->direction)};
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto result=JSObjectMakeArray(ctx,0,nullptr,exception);
            for(unsigned i=0;i<5;++i)JSObjectSetPropertyAtIndex(ctx,result,i,JSValueMakeNumber(ctx, values[i]),exception);
#else
            auto result=v8::Array::New(isolate);
            for(unsigned i=0;i<5;++i)(void)result->Set(isolate->GetCurrentContext(),i,JSValueMakeNumber(ctx, values[i])).ToChecked();
#endif
            return result;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Sprite_DisableAnimationPhysics(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0, true);if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""seconds"")");
        double seconds = (argumentCount<1) ? 0.5 : JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""direction"")");
        long direction = (argumentCount<2) ? rotationDirection_AsSpecified : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        try{self->disableAnimationPhysics(seconds,direction);}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Sprite_AddAnimationDrawable(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3, true);if (!JSValueIsString(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a string (""slot"")");
        JSStringRef slot_Str = JSValueToStringCopy(ctx, arguments[3 -1], exception);
        MemBlock slot_Mem(JSStringGetMaximumUTF8CStringSize(slot_Str));
        JSStringGetUTF8CString(slot_Str, slot_Mem.ptr, slot_Mem.bytes);
        const char* slot = (const char*)slot_Mem.ptr;
        JSStringRelease(slot_Str);
        if(!JSC_ValueIsFunction(ctx, arguments[0], exception))
        {
            Drawing* drawing = 0;
            if (JSValueIsObject(ctx, arguments[0]))
            {
                JSObjectRef drawing_obj_ = JSValueToObject(ctx, arguments[0], exception);
                drawing = Drawing_getCppObject(drawing_obj_);
                if (!drawing)
                {
                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, drawing_obj_);
                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                    {
                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                        drawing = Drawing_getCppObject(protoObj_);
                    }
                }
            };
            if(!drawing)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Drawing or callback" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
            }
            try{auto options=decodeAnimationDrawableOptions(animationPhysicsValues(PDG_POSE_SCRIPT_ARGUMENTS,arguments[1]),slot);return JSValueMakeNumber(ctx, self->addAnimationDrawable(options,*drawing));}
            catch(const std::exception& error)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
            }
        }
        JSObjectRef callback = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!callback || !JSObjectIsFunction(ctx, callback) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""callback"")");
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto saved=std::make_shared<AnimationScriptDrawing>(ctx,callback);
#else
        auto saved=std::make_shared<AnimationScriptDrawing>(isolate,callback);
#endif
        try
        {
            auto options=decodeAnimationDrawableOptions(animationPhysicsValues(PDG_POSE_SCRIPT_ARGUMENTS,arguments[1]),slot);return JSValueMakeNumber(ctx, self->addAnimationDrawable(options,[saved](auto context)
            {
                return saved->draw(context);
            }
            ));
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_RemoveAnimationDrawable(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        double id = JSValueToNumber(ctx, arguments[1 -1], exception);
        if(!std::isfinite(id)||id<1||id>4294967295.0||id!=std::floor(id))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Invalid drawable ID" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
        self->removeAnimationDrawable(static_cast<uint32_t>(id));return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_ClearAnimationDrawables(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);self->clearAnimationDrawables();return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_SetAnimationDrawableEnabled(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        double id = JSValueToNumber(ctx, arguments[1 -1], exception);if (!JSValueIsBoolean(ctx, arguments[2 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""enabled"")");
        bool enabled = JSValueToBoolean(ctx, arguments[2 -1]);
        if(!std::isfinite(id)||id<1||id>4294967295.0||id!=std::floor(id))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Invalid drawable ID" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
        try{self->setAnimationDrawableEnabled(static_cast<uint32_t>(id),enabled);}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_GetAnimationDrawableError(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        double id = JSValueToNumber(ctx, arguments[1 -1], exception);
        if(!std::isfinite(id)||id<1||id>4294967295.0||id!=std::floor(id))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Invalid drawable ID" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
        try{const auto error=self->getAnimationDrawableError(static_cast<uint32_t>(id));return JSC_MakeValueFromCString(ctx, error.c_str());}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_GetAnimationDrawBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try{return animationDrawingBoundsValue(PDG_POSE_SCRIPT_ARGUMENTS,self->getAnimationDrawBounds());}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Sprite_ProceduralControl(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""operation"")");
        double operation = JSValueToNumber(ctx, arguments[1 -1], exception);
        try
        {
            if(!std::isfinite(operation)||operation!=std::floor(operation)||operation<1||operation>16) { throw std::invalid_argument("Invalid procedural operation"); }
            auto result=self->proceduralControl(int(operation),proceduralBindingValues(PROCEDURAL_ARGUMENTS,arguments[1]));
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto a=JSObjectMakeArray(ctx,0,nullptr,exception);for(unsigned i=0;i<result.size();++i)JSObjectSetPropertyAtIndex(ctx,a,i,JSValueMakeNumber(ctx, result[i]),exception);
#else
            auto a=v8::Array::New(isolate);for(unsigned i=0;i<result.size();++i)(void)a->Set(isolate->GetCurrentContext(),i,JSValueMakeNumber(ctx, result[i])).ToChecked();
#endif
            return a;
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Sprite_AddAnimationIK(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""order"")");
        double order = (argumentCount<2) ? 0 : JSValueToNumber(ctx, arguments[2 -1], exception);
        if (!std::isfinite(order) || order!=std::floor(order) || order<-2147483648.0 || order>2147483647.0)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Invalid IK order" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
        try { return JSValueMakeNumber(ctx, self->addAnimationIK(animationScriptIKConfig(PDG_POSE_SCRIPT_ARGUMENTS,arguments[0]),static_cast<int>(order))); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_SetAnimationIKTarget(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3, true); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        double id = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""x"")");
        double x = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""y"")");
        double y = JSValueToNumber(ctx, arguments[3 -1], exception); if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""space"")");
        double space = (argumentCount<4) ? 1 : JSValueToNumber(ctx, arguments[4 -1], exception);
        if (!std::isfinite(id) || id!=std::floor(id) || id<1 || id>4294967295.0 || !std::isfinite(space) || space!=std::floor(space) || space<0 || space>2)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Invalid IK ID or space" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
        try {self->setAnimationIKTarget(static_cast<uint32_t>(id),x,y,static_cast<int>(space));}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_GetAnimationIKResult(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        double id = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!std::isfinite(id) || id!=std::floor(id) || id<1 || id>4294967295.0)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Invalid IK ID" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
        try {return animationIKResultValue(PDG_POSE_SCRIPT_ARGUMENTS,self->getAnimationIKResult(static_cast<uint32_t>(id)));}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Sprite_AddAnimationModifier(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); JSObjectRef callback = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!callback || !JSObjectIsFunction(ctx, callback) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""callback"")");
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""stage"")");
        double stage = (argumentCount<2) ? 0 : JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""order"")");
        double order = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(stage) || stage != std::floor(stage) || stage < 0 || stage > 2 ||
            !std::isfinite(order) || order != std::floor(order) || order < -2147483648.0 || order > 2147483647.0)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected integer animation stage and order" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto saved=std::make_shared<AnimationScriptModifier>(ctx,callback);
#else
        auto saved=std::make_shared<AnimationScriptModifier>(isolate,callback);
#endif
        try
        {
            return JSValueMakeNumber(ctx, self->addAnimationModifier([saved](auto view,const auto& context)
            {
                saved->invoke(view,context);
            }
            ,static_cast<int>(stage),static_cast<int>(order)));
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_RemoveAnimationModifier(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        double id = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!std::isfinite(id) || id != std::floor(id) || id < 1 || id > 4294967295.0)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Invalid modifier ID" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        self->removeAnimationModifier(static_cast<uint32_t>(id)); return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_ClearAnimationModifiers(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->clearAnimationModifiers(); return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_GetAnimationModifierError(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        double id = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!std::isfinite(id) || id != std::floor(id) || id < 1 || id > 4294967295.0)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Invalid modifier ID" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { return JSC_MakeValueFromCString(ctx, self->getAnimationModifierError(static_cast<uint32_t>(id)).c_str()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_SetAnimationSource(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""source"")");
        double source = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!std::isfinite(source) || source != std::floor(source) || source < 0 || source > 2)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Invalid animation source" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->setAnimationSource(static_cast<int>(source)); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_GetAnimationSource(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getAnimationSource());
    }

    JSValueRef Sprite_IsAnimationDrawingSupported(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSValueMakeBoolean(ctx, self->isAnimationDrawingSupported());
    }
    JSValueRef Sprite_SetAnimationDebugDraw(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""flags"")");
        double flags = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!std::isfinite(flags) || flags < 0 || flags > static_cast<int>(animationDebug_All) || flags != std::floor(flags))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected animationDebug integer flag bits" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->setAnimationDebugDraw(static_cast<int>(flags)); }
        catch (const std::exception&)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Animation debug drawing requires GUI support and an enabled pose" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_GetAnimationDebugDraw(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSValueMakeNumber(ctx, self->getAnimationDebugDraw());
    }
    JSValueRef Sprite_EnableAnimationPose(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""referenceAnimation"")");
        JSStringRef referenceAnimation_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock referenceAnimation_Mem(JSStringGetMaximumUTF8CStringSize(referenceAnimation_Str));
        JSStringGetUTF8CString(referenceAnimation_Str, referenceAnimation_Mem.ptr, referenceAnimation_Mem.bytes);
        const char* referenceAnimation = (const char*)referenceAnimation_Mem.ptr;
        JSStringRelease(referenceAnimation_Str);
        return JSValueMakeBoolean(ctx, self->enableAnimationPose(referenceAnimation));
    }
    JSValueRef Sprite_IsAnimationPoseEnabled(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSValueMakeBoolean(ctx, self->isAnimationPoseEnabled());
    }
    JSValueRef Sprite_GetAnimationRigError(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSC_MakeValueFromCString(ctx, self->getAnimationRigError().c_str());
    }
    JSValueRef Sprite_GetBone(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        try
        {
            Bone* bone;
            if(JSValueIsString(ctx, arguments[0]))
            {
                if (!JSValueIsString(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
                JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
                MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
                JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
                const char* name = (const char*)name_Mem.ptr;
                JSStringRelease(name_Str);bone=self->getBone(name);
            }
            else
            {
                if (!JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
                uint32 id = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));bone=self->getBone(id);
            }
            if (!bone) return JSValueMakeNull(ctx);
            if (!bone->mBoneScriptObj)
            {
                return Bone_newFromCpp(ctx, bone);
            }
            else
            {
                return bone->mBoneScriptObj;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_GetAnimationBoneNames(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        auto names = self->getAnimationBoneNames();
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t i = 0; i < names.size(); ++i) JSObjectSetPropertyAtIndex(ctx, result, i, JSC_MakeValueFromCString(ctx, names[i].c_str()), exception);
#else
        auto result = v8::Array::New(isolate);
        for (size_t i = 0; i < names.size(); ++i) (void)result->Set(isolate->GetCurrentContext(), i, JSC_MakeValueFromCString(ctx, names[i].c_str())).ToChecked();
#endif
        return result;
    }
    JSValueRef Sprite_GetAnimationBoneTransform(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
        JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
        JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
        const char* name = (const char*)name_Mem.ptr;
        JSStringRelease(name_Str);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""space"")");
        double space = (argumentCount<2) ? static_cast<int>(animationSpace_Local) : JSValueToNumber(ctx, arguments[2 -1], exception);
        if (space != static_cast<int>(animationSpace_Local) && space != static_cast<int>(animationSpace_Rig) && space != static_cast<int>(animationSpace_World))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an animationSpace integer constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int coordinateSpace = static_cast<int>(space);
        try { return animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS, self->getAnimationBoneTransform(name, coordinateSpace)); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_GetAnimationBindingNames(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        auto names = self->getAnimationBindingNames();
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t i = 0; i < names.size(); ++i) JSObjectSetPropertyAtIndex(ctx, result, i, JSC_MakeValueFromCString(ctx, names[i].c_str()), exception);
#else
        auto result = v8::Array::New(isolate);
        for (size_t i = 0; i < names.size(); ++i) (void)result->Set(isolate->GetCurrentContext(), i, JSC_MakeValueFromCString(ctx, names[i].c_str())).ToChecked();
#endif
        return result;
    }
    JSValueRef Sprite_GetAnimationBindingTransform(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
        JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
        JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
        const char* name = (const char*)name_Mem.ptr;
        JSStringRelease(name_Str);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""space"")");
        double space = (argumentCount<2) ? static_cast<int>(animationSpace_Local) : JSValueToNumber(ctx, arguments[2 -1], exception);
        if (space != static_cast<int>(animationSpace_Local) && space != static_cast<int>(animationSpace_Rig) && space != static_cast<int>(animationSpace_World))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an animationSpace integer constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int coordinateSpace = static_cast<int>(space);
        try { return animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS, self->getAnimationBindingTransform(name, coordinateSpace)); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_SetAnimationBoneTransform(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
        JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
        JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
        const char* name = (const char*)name_Mem.ptr;
        JSStringRelease(name_Str);
        if (!JSValueIsObject(ctx, arguments[1]))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected an animation transform object" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        JSObjectRef object = JSValueToObject(ctx, arguments[1], exception);
        AnimationTransform transform;
        {
            JSValueRef value = JSObjectGetProperty(ctx, object, ((symbol_x) ? symbol_x : symbol_x = JSStringCreateWithUTF8CString("x")), exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception)) { return JSValueMakeNull(ctx); }
#else
            if (value.IsEmpty()) { return JSValueMakeNull(ctx); }
#endif
            if (!JSValueIsNumber(ctx, value))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Animation transform fields must all be numbers" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            transform.x = JSValueToNumber(ctx, value, exception);
        }
        {
            JSValueRef value = JSObjectGetProperty(ctx, object, ((symbol_y) ? symbol_y : symbol_y = JSStringCreateWithUTF8CString("y")), exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception)) { return JSValueMakeNull(ctx); }
#else
            if (value.IsEmpty()) { return JSValueMakeNull(ctx); }
#endif
            if (!JSValueIsNumber(ctx, value))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Animation transform fields must all be numbers" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            transform.y = JSValueToNumber(ctx, value, exception);
        }
        {
            JSValueRef value = JSObjectGetProperty(ctx, object, ((symbol_rotation) ? symbol_rotation : symbol_rotation = JSStringCreateWithUTF8CString("rotation")), exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception)) { return JSValueMakeNull(ctx); }
#else
            if (value.IsEmpty()) { return JSValueMakeNull(ctx); }
#endif
            if (!JSValueIsNumber(ctx, value))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Animation transform fields must all be numbers" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            transform.rotation = JSValueToNumber(ctx, value, exception);
        }
        {
            JSValueRef value = JSObjectGetProperty(ctx, object, ((symbol_scaleX) ? symbol_scaleX : symbol_scaleX = JSStringCreateWithUTF8CString("scaleX")), exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception)) { return JSValueMakeNull(ctx); }
#else
            if (value.IsEmpty()) { return JSValueMakeNull(ctx); }
#endif
            if (!JSValueIsNumber(ctx, value))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Animation transform fields must all be numbers" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            transform.scaleX = JSValueToNumber(ctx, value, exception);
        }
        {
            JSValueRef value = JSObjectGetProperty(ctx, object, ((symbol_scaleY) ? symbol_scaleY : symbol_scaleY = JSStringCreateWithUTF8CString("scaleY")), exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception)) { return JSValueMakeNull(ctx); }
#else
            if (value.IsEmpty()) { return JSValueMakeNull(ctx); }
#endif
            if (!JSValueIsNumber(ctx, value))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Animation transform fields must all be numbers" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            transform.scaleY = JSValueToNumber(ctx, value, exception);
        }
        {
            JSValueRef value = JSObjectGetProperty(ctx, object, ((symbol_alpha) ? symbol_alpha : symbol_alpha = JSStringCreateWithUTF8CString("alpha")), exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception)) { return JSValueMakeNull(ctx); }
#else
            if (value.IsEmpty()) { return JSValueMakeNull(ctx); }
#endif
            if (!JSValueIsNumber(ctx, value))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Animation transform fields must all be numbers" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            transform.alpha = JSValueToNumber(ctx, value, exception);
        }
        try { self->setAnimationBoneTransform(name, transform); }
        catch (const std::exception&)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Invalid animation bone transform or disabled pose" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sprite_GetAnimationPose(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try { return animationSnapshotValue(PDG_POSE_SCRIPT_ARGUMENTS, self->getAnimationPose()); }
        catch (const std::exception&)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Animation pose is not available" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_SampleAnimationPose(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""clip"")");
        JSStringRef clip_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock clip_Mem(JSStringGetMaximumUTF8CStringSize(clip_Str));
        JSStringGetUTF8CString(clip_Str, clip_Mem.ptr, clip_Mem.bytes);
        const char* clip = (const char*)clip_Mem.ptr;
        JSStringRelease(clip_Str);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""timeSeconds"")");
        double timeSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        try { return animationSnapshotValue(PDG_POSE_SCRIPT_ARGUMENTS, self->sampleAnimationPose(clip, timeSeconds)); }
        catch (const std::exception&)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Invalid animation pose sample, clip or time" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
    }
#undef PDG_POSE_SCRIPT_ARGUMENTS
#undef PDG_POSE_SCRIPT_PARAMETERS
#endif

    JSValueRef Sprite_GetAttachmentPart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* mount=self->getAttachmentPart(); if (!mount) return JSValueMakeNull(ctx);
        if (!mount->mPartScriptObj)
        {
            return Part_newFromCpp(ctx, mount);
        }
        else
        {
            return mount->mPartScriptObj;
        };
    }
    JSValueRef Sprite_CreatePart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
        JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
        JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
        const char* name = (const char*)name_Mem.ptr;
        JSStringRelease(name_Str);
        try
        {
            auto* part = self->createPart(name); if (!part) return JSValueMakeNull(ctx);
            if (!part->mPartScriptObj)
            {
                return Part_newFromCpp(ctx, part);
            }
            else
            {
                return part->mPartScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_TransferPart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); Part* part = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef part_ = JSValueToObject(ctx, arguments[1 -1], exception);
            part = Part_getCppObject(part_);
        }
        if (!part)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Part"" (""part"")"); if (argumentCount >= 2 && !JSValueIsBoolean(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""descendants"")");
        bool descendants = (argumentCount<2) ? true : JSValueToBoolean(ctx, arguments[2 -1]);
        try
        {
            auto* result=self->transferPart(part,descendants); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPartScriptObj)
            {
                return Part_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPartScriptObj;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_GetPart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        double id = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!std::isfinite(id) || id < 0 || id > partId_None || std::floor(id) != id)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected a Part ID" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        auto* part = self->getPart(static_cast<PartId>(id)); if (!part) return JSValueMakeNull(ctx);
        if (!part->mPartScriptObj)
        {
            return Part_newFromCpp(ctx, part);
        }
        else
        {
            return part->mPartScriptObj;
        };
    }

    JSValueRef Sprite_FindPart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
        JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
        JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
        const char* name = (const char*)name_Mem.ptr;
        JSStringRelease(name_Str);
        auto* part = self->findPart(name); if (!part) return JSValueMakeNull(ctx);
        if (!part->mPartScriptObj)
        {
            return Part_newFromCpp(ctx, part);
        }
        else
        {
            return part->mPartScriptObj;
        };
    }
    JSValueRef Sprite_GetPartCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ; if (argumentCount != 0)
        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSValueMakeNumber(ctx, self->getPartCount());
    }
    JSValueRef Sprite_GetPartNames(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ; if (argumentCount != 0)
        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        const auto names = self->getPartNames();
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t i = 0; i < names.size(); ++i) JSObjectSetPropertyAtIndex(ctx, result, i, JSC_MakeValueFromCString(ctx, names[i].c_str()), exception);
#else
        auto result = v8::Array::New(isolate);
        for (size_t i = 0; i < names.size(); ++i) result->Set(isolate->GetCurrentContext(), i, JSC_MakeValueFromCString(ctx, names[i].c_str())).ToChecked();
#endif
        return result;
    }
    JSValueRef Sprite_RemovePart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        double id = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!std::isfinite(id) || id < 0 || id > partId_None || std::floor(id) != id)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected a Part ID" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { return JSValueMakeBoolean(ctx, self->removePart(static_cast<PartId>(id))); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_ClearParts(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ; if (argumentCount != 0)
        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try { self->clearParts(); return JSValueMakeUndefined(ctx); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    void CleanupSpriteScriptObject(JSObjectRef obj) { }

#ifdef PDG_USING_JAVASCRIPT_CORE
    Sprite* New_Sprite(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return new Sprite(); }
#else
    SpriteWrap::SpriteWrap(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) : cppPtr_(New_Sprite(args)) {}
    SpriteWrap::~SpriteWrap()
    {
        if (cppPtr_)
        {
            cppPtr_->mSpriteScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset();
            cppPtr_->mEventEmitterScriptObj.Reset(); cppPtr_->mISerializableScriptObj.Reset();
            cppPtr_->release(); cppPtr_ = nullptr;
        }
    }
    Sprite* New_Sprite(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        if (s_Sprite_InNewFromCpp) return nullptr;
        auto* isolate = args.GetIsolate();
        auto* sprite = new Sprite();
        sprite->addRef();
        SPRITE_SAVE_WEAK(sprite, args.This());
        return sprite;
    }
#endif

    JSValueRef Sprite_ReadPhysics(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* body=&static_cast<PhysicsBody&>(self->physics); if (!body) return JSValueMakeNull(ctx);
            if (!body->mPhysicsBodyScriptObj)
            {
                return PhysicsBody_newFromCpp(ctx, body);
            }
            else
            {
                return body->mPhysicsBodyScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_SetupPhysicsBody(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""mass"")");
            double mass = (argumentCount<1) ? 1.0 : JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""inertia"")");
            double inertia = (argumentCount<2) ? 1.0 : JSValueToNumber(ctx, arguments[2 -1], exception); auto* body=&self->setupPhysicsBody(mass,inertia); if (!body) return JSValueMakeNull(ctx);
            if (!body->mPhysicsBodyScriptObj)
            {
                return PhysicsBody_newFromCpp(ctx, body);
            }
            else
            {
                return body->mPhysicsBodyScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_RemovePhysicsBody(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->removePhysicsBody(); return JSValueMakeUndefined(ctx);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_ReadCollider(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* result=&static_cast<Collider&>(self->collider); if (!result) return JSValueMakeNull(ctx);
            if (!result->mColliderScriptObj)
            {
                return Collider_newFromCpp(ctx, result);
            }
            else
            {
                return result->mColliderScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_SetupCollider(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* result=&self->setupCollider(); if (!result) return JSValueMakeNull(ctx);
            if (!result->mColliderScriptObj)
            {
                return Collider_newFromCpp(ctx, result);
            }
            else
            {
                return result->mColliderScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Sprite_RemoveCollider(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sprite* self = static_cast<Sprite*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->removeCollider(); return JSValueMakeUndefined(ctx);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

}
