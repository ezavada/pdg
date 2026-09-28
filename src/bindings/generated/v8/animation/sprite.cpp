// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/sprite.cpp
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
#include <cmath>

namespace pdg
{

#ifndef PDG_NO_GUI

    bool s_ISpriteDrawHelper_InNewFromCpp = false;

    void ISpriteDrawHelperWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ISpriteDrawHelperWrap* objWrapper = new ISpriteDrawHelperWrap(args);
        objWrapper->Wrap(args.This());
        ISpriteDrawHelper* cppObj = objWrapper->getCppObject();
        if (cppObj)
        {
            cppObj->mISpriteDrawHelperScriptObj.Reset(isolate, args.This());
        }
        objWrapper->Ref();
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }
    v8::Local<v8::Object> ISpriteDrawHelperWrap::NewFromCpp(v8::Isolate* isolate, ISpriteDrawHelper* cppObj)
    {
        s_ISpriteDrawHelper_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_ISpriteDrawHelper_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_ISpriteDrawHelper_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        ISpriteDrawHelperWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ISpriteDrawHelperWrap>(instance);
        {
            [[maybe_unused]] v8::Local<v8::Object> obj = instance;
            cppObj->mISpriteDrawHelperScriptObj.Reset(isolate, obj);
            objWrapper->Ref();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_ISpriteDrawHelper_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> ISpriteDrawHelperWrap::constructorTpl_;

    void ISpriteDrawHelperWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "ISpriteDrawHelper").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();
    }

    void CleanupISpriteDrawHelperScriptObject(v8::UniquePersistent<v8::Object> &obj) { }
#endif

#ifdef PDG_SPRITER_SUPPORT
#ifdef PDG_USING_JAVASCRIPT_CORE
#define PDG_POSE_SCRIPT_PARAMETERS JSContextRef ctx, JSValueRef* exception
#define PDG_POSE_SCRIPT_ARGUMENTS ctx, exception
#else
#define PDG_POSE_SCRIPT_PARAMETERS v8::Isolate* isolate
#define PDG_POSE_SCRIPT_ARGUMENTS isolate
#endif
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;

    static v8::Local<v8::Object> animationTransformValue(PDG_POSE_SCRIPT_PARAMETERS, const AnimationTransform& transform)
    {
        v8::Local<v8::Object> result = v8_ObjectCreateEmpty(isolate, 0);
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "x").ToLocalChecked(), v8::Number::New(isolate, transform.x)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "y").ToLocalChecked(), v8::Number::New(isolate, transform.y)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "rotation").ToLocalChecked(), v8::Number::New(isolate, transform.rotation)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "scaleX").ToLocalChecked(), v8::Number::New(isolate, transform.scaleX)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "scaleY").ToLocalChecked(), v8::Number::New(isolate, transform.scaleY)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "alpha").ToLocalChecked(), v8::Number::New(isolate, transform.alpha)).ToChecked();
        return result;
    }
    static v8::Local<v8::Object> animationSnapshotValue(PDG_POSE_SCRIPT_PARAMETERS, const AnimationPose& pose)
    {
        v8::Local<v8::Object> result = v8_ObjectCreateEmpty(isolate, 0);
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "rigRevision").ToLocalChecked(), v8::String::NewFromUtf8(isolate, std::to_string(pose.getRig()->getRevision()).c_str()).ToLocalChecked()).ToChecked();
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto bones = JSObjectMakeArray(ctx, 0, nullptr, exception);
#else
        auto bones = v8::Array::New(isolate);
#endif
        for (uint32_t id = 0; id < pose.getRig()->getBoneCount(); ++id)
        {
            const auto& definition = pose.getRig()->getBone(id);
            v8::Local<v8::Object> item = animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS, pose.getLocalTransform(id));
            (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "name").ToLocalChecked(), v8::String::NewFromUtf8(isolate, definition.name.c_str()).ToLocalChecked()).ToChecked();
            v8::Local<v8::Value> parentValue = v8::Number::New(isolate, definition.parent);
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (definition.parent == animation_NoBone) parentValue = JSValueMakeNull(ctx);
#else
            if (definition.parent == animation_NoBone) parentValue = v8::Null(isolate);
#endif
            (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "parent").ToLocalChecked(), parentValue).ToChecked();
#ifdef PDG_USING_JAVASCRIPT_CORE
            JSObjectSetPropertyAtIndex(ctx, bones, id, item, exception);
#else
            (void)bones->Set(isolate->GetCurrentContext(), id, item).ToChecked();
#endif
        }
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "bones").ToLocalChecked(), bones).ToChecked();
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto bindings = JSObjectMakeArray(ctx, 0, nullptr, exception);
#else
        auto bindings = v8::Array::New(isolate);
#endif
        for (uint32_t id = 0; id < pose.getRig()->getBindingCount(); ++id)
        {
            const auto& definition = pose.getRig()->getBinding(id);
            v8::Local<v8::Object> item = animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS, pose.getBindingLocalTransform(id));
            (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "name").ToLocalChecked(), v8::String::NewFromUtf8(isolate, definition.name.c_str()).ToLocalChecked()).ToChecked();
            v8::Local<v8::Value> parentValue = v8::Number::New(isolate, definition.bone);
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (definition.bone == animation_NoBone) parentValue = JSValueMakeNull(ctx);
#else
            if (definition.bone == animation_NoBone) parentValue = v8::Null(isolate);
#endif
            (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "parent").ToLocalChecked(), parentValue).ToChecked();
            (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "kind").ToLocalChecked(), v8::Integer::New(isolate, static_cast<int>(definition.kind))).ToChecked();
#ifdef PDG_USING_JAVASCRIPT_CORE
            JSObjectSetPropertyAtIndex(ctx, bindings, id, item, exception);
#else
            (void)bindings->Set(isolate->GetCurrentContext(), id, item).ToChecked();
#endif
        }
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "bindings").ToLocalChecked(), bindings).ToChecked();
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto variables = JSObjectMakeArray(ctx, 0, nullptr, exception);
#else
        auto variables = v8::Array::New(isolate);
#endif
        for (size_t id = 0; id < pose.getMetadata().variables.size(); ++id)
        {
            const auto& definition = pose.getMetadata().variables[id];
            v8::Local<v8::Object> item = v8_ObjectCreateEmpty(isolate, 0);
            (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "object").ToLocalChecked(), v8::String::NewFromUtf8(isolate, definition.object.c_str()).ToLocalChecked()).ToChecked();
            (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "name").ToLocalChecked(), v8::String::NewFromUtf8(isolate, definition.name.c_str()).ToLocalChecked()).ToChecked();
            if (const auto* number = std::get_if<double>(&definition.value))
            {
                (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type").ToLocalChecked(), v8::Integer::New(isolate, animationVariable_Float)).ToChecked();
                (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "value").ToLocalChecked(), v8::Number::New(isolate, *number)).ToChecked();
            }
            else if (const auto* integer = std::get_if<int>(&definition.value))
            {
                (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type").ToLocalChecked(), v8::Integer::New(isolate, animationVariable_Int)).ToChecked();
                (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "value").ToLocalChecked(), v8::Integer::New(isolate, *integer)).ToChecked();
            }
            else
            {
                (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "type").ToLocalChecked(), v8::Integer::New(isolate, animationVariable_String)).ToChecked();
                (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "value").ToLocalChecked(), v8::String::NewFromUtf8(isolate, std::get<std::string>(definition.value).c_str()).ToLocalChecked()).ToChecked();
            }
#ifdef PDG_USING_JAVASCRIPT_CORE
            JSObjectSetPropertyAtIndex(ctx, variables, id, item, exception);
#else
            (void)variables->Set(isolate->GetCurrentContext(), id, item).ToChecked();
#endif
        }
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "variables").ToLocalChecked(), variables).ToChecked();
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto tags = JSObjectMakeArray(ctx, 0, nullptr, exception);
#else
        auto tags = v8::Array::New(isolate);
#endif
        for (size_t id = 0; id < pose.getMetadata().tags.size(); ++id)
        {
            const auto& definition = pose.getMetadata().tags[id];
            v8::Local<v8::Object> item = v8_ObjectCreateEmpty(isolate, 0);
            (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "object").ToLocalChecked(), v8::String::NewFromUtf8(isolate, definition.object.c_str()).ToLocalChecked()).ToChecked();
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto names = JSObjectMakeArray(ctx, 0, nullptr, exception);
            for (size_t n = 0; n < definition.tags.size(); ++n) JSObjectSetPropertyAtIndex(ctx, names, n, v8::String::NewFromUtf8(isolate, definition.tags[n].c_str()).ToLocalChecked(), exception);
#else
            auto names = v8::Array::New(isolate);
            for (size_t n = 0; n < definition.tags.size(); ++n) (void)names->Set(isolate->GetCurrentContext(), n, v8::String::NewFromUtf8(isolate, definition.tags[n].c_str()).ToLocalChecked()).ToChecked();
#endif
            (void)item->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "tags").ToLocalChecked(), names).ToChecked();
#ifdef PDG_USING_JAVASCRIPT_CORE
            JSObjectSetPropertyAtIndex(ctx, tags, id, item, exception);
#else
            (void)tags->Set(isolate->GetCurrentContext(), id, item).ToChecked();
#endif
        }
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "tags").ToLocalChecked(), tags).ToChecked();
        return result;
    }

    static std::vector<double> animationPhysicsValues(PDG_POSE_SCRIPT_PARAMETERS,v8::Local<v8::Value> input)
    {
        std::vector<double> result;
#ifdef PDG_USING_JAVASCRIPT_CORE
        if(!JSValueIsArray(ctx,input))throw std::invalid_argument("Expected physical rig array");
        auto array=JSValueToObject(ctx,input,exception);auto key=JSStringCreateWithUTF8CString("length");
        const auto length=JSValueToNumber(ctx,JSObjectGetProperty(ctx,array,key,exception),exception);JSStringRelease(key);
        if(*exception||length>1500000)throw std::invalid_argument("Invalid physical rig array length");
        for(unsigned i=0;i<length;++i){auto value=JSObjectGetPropertyAtIndex(ctx,array,i,exception);if(*exception||!JSValueIsNumber(ctx,value))throw std::invalid_argument("Invalid physical rig number");result.push_back(JSValueToNumber(ctx,value,exception));}
#else
        if(!input->IsArray())throw std::invalid_argument("Expected physical rig array");
        auto array=input.As<v8::Array>();if(array->Length()>1500000)throw std::invalid_argument("Invalid physical rig array length");
        for(unsigned i=0;i<array->Length();++i){v8::Local<v8::Value> value;if(!array->Get(isolate->GetCurrentContext(),i).ToLocal(&value)||!value->IsNumber())throw std::invalid_argument("Invalid physical rig number");result.push_back(value.As<v8::Number>()->Value());}
#endif
        return result;
    }

    static AnimationTwoBoneIK animationScriptIKConfig(PDG_POSE_SCRIPT_PARAMETERS, v8::Local<v8::Value> value)
    {
        AnimationTwoBoneIK config;
        if (!value->IsObject()) throw std::invalid_argument("Expected IK configuration");
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto object=JSValueToObject(ctx,value,exception);
#else
        auto object=value.As<v8::Object>();
#endif
        auto read=[&](const char* name)
        {
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto key=JSStringCreateWithUTF8CString(name);auto item=JSObjectGetProperty(ctx,object,key,exception);JSStringRelease(key);
            if (*exception || !JSValueIsNumber(ctx,item)) throw std::invalid_argument("Invalid IK configuration field");
            double number=JSValueToNumber(ctx,item,exception);
#else
            v8::Local<v8::Value> item;
            if (!object->Get(isolate->GetCurrentContext(),v8::String::NewFromUtf8(isolate,name).ToLocalChecked()).ToLocal(&item) || !item->IsNumber()) throw std::invalid_argument("Invalid IK configuration field");
            double number=item.As<v8::Number>()->Value();
#endif
            if (!std::isfinite(number)) throw std::invalid_argument("Nonfinite IK configuration field");
            return number;
        };
        {double n=read("root");if(n<0 || n>=animation_NoBone || n!=std::floor(n))throw std::invalid_argument("Invalid IK bone ID");config.root=static_cast<AnimationBoneId>(n);}
        {double n=read("middle");if(n<0 || n>=animation_NoBone || n!=std::floor(n))throw std::invalid_argument("Invalid IK bone ID");config.middle=static_cast<AnimationBoneId>(n);}
        {double n=read("tip");if(n<0 || n>=animation_NoBone || n!=std::floor(n))throw std::invalid_argument("Invalid IK bone ID");config.tip=static_cast<AnimationBoneId>(n);}
        config.rootLength=read("rootLength");
        config.middleLength=read("middleLength");
        config.targetX=read("targetX");
        config.targetY=read("targetY");
        config.influence=read("influence");
        {double n=read("space");if(n<-1 || n>2 || n!=std::floor(n))throw std::invalid_argument("Invalid IK enum");config.space=static_cast<int>(n);}
        {double n=read("bendDirection");if(n<-1 || n>2 || n!=std::floor(n))throw std::invalid_argument("Invalid IK enum");config.bendDirection=static_cast<int>(n);}
        {double n=read("stretch");if(n<-1 || n>2 || n!=std::floor(n))throw std::invalid_argument("Invalid IK enum");config.stretch=static_cast<int>(n);}
        {double n=read("matchOrientation");if(n<-1 || n>2 || n!=std::floor(n))throw std::invalid_argument("Invalid IK enum");config.matchOrientation=static_cast<int>(n);}
        config.targetRotation=read("targetRotation");
        config.rootMin=read("rootMin");
        config.rootMax=read("rootMax");
        config.middleMin=read("middleMin");
        config.middleMax=read("middleMax");
        return config;
    }
    ;
    ;
    ;
    ;
    ;
    static v8::Local<v8::Object> animationIKResultValue(PDG_POSE_SCRIPT_PARAMETERS, const AnimationIKResult& value)
    {
        v8::Local<v8::Object> result=v8_ObjectCreateEmpty(isolate, 0);
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "reachError").ToLocalChecked(), v8::Number::New(isolate, value.reachError)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "reachable").ToLocalChecked(), v8::Boolean::New(isolate, value.reachable)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "clamped").ToLocalChecked(), v8::Boolean::New(isolate, value.clamped)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "limited").ToLocalChecked(), v8::Boolean::New(isolate, value.limited)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "stretched").ToLocalChecked(), v8::Boolean::New(isolate, value.stretched)).ToChecked();
        return result;
    }

    ;
    ;
    ;
    static v8::Local<v8::Object> animationModifierContextValue(PDG_POSE_SCRIPT_PARAMETERS, const AnimationModifierContext& context)
    {
        v8::Local<v8::Object> result = v8_ObjectCreateEmpty(isolate, 0);
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "deltaSeconds").ToLocalChecked(), v8::Number::New(isolate, context.deltaSeconds)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "root").ToLocalChecked(), animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS,context.root)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "revision").ToLocalChecked(), v8::String::NewFromUtf8(isolate, std::to_string(context.revision).c_str()).ToLocalChecked()).ToChecked();
        return result;
    }
    static void applyAnimationScriptEdits(PDG_POSE_SCRIPT_PARAMETERS, AnimationPoseView view, v8::Local<v8::Value> edits)
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
        if (!edits || !JSValueIsArray(ctx,edits)) throw std::invalid_argument("Modifier bridge must return bone transforms");
        auto array = JSValueToObject(ctx,edits,exception);
        auto lengthKey = JSStringCreateWithUTF8CString("length");
        auto lengthValue = JSObjectGetProperty(ctx,array,lengthKey,exception); JSStringRelease(lengthKey);
        if (*exception || JSValueToNumber(ctx,lengthValue,exception) != count) throw std::invalid_argument("Wrong modifier bone count");
#else
        if (edits.IsEmpty() || !edits->IsArray() || edits.As<v8::Array>()->Length() != count) throw std::invalid_argument("Wrong modifier bone count");
        auto array = edits.As<v8::Array>();
#endif
        for (uint32_t id=0;id<count;++id)
        {
            AnimationTransform transform;
            double* values[] = {&transform.x,&transform.y,&transform.rotation,&transform.scaleX,&transform.scaleY,&transform.alpha};
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto item=JSObjectGetPropertyAtIndex(ctx,array,id,exception);
            if (*exception || !JSValueIsObject(ctx,item)) throw std::invalid_argument("Invalid modifier transform");
            auto object=JSValueToObject(ctx,item,exception);
#else
            v8::Local<v8::Value> item;
            if (!array->Get(isolate->GetCurrentContext(),id).ToLocal(&item) || !item->IsObject()) throw std::invalid_argument("Invalid modifier transform");
            auto object=item.As<v8::Object>();
#endif
            for (int field=0;field<6;++field)
            {
#ifdef PDG_USING_JAVASCRIPT_CORE
                auto key=JSStringCreateWithUTF8CString(fields[field]);
                auto value=JSObjectGetProperty(ctx,object,key,exception);JSStringRelease(key);
                if (*exception || !JSValueIsNumber(ctx,value)) throw std::invalid_argument("Modifier transform fields must be numbers");
                *values[field]=JSValueToNumber(ctx,value,exception);
#else
                v8::Local<v8::Value> value;
                if (!object->Get(isolate->GetCurrentContext(),v8::String::NewFromUtf8(isolate,fields[field]).ToLocalChecked()).ToLocal(&value) || !value->IsNumber())
                    throw std::invalid_argument("Modifier transform fields must be numbers");
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

    static std::shared_ptr<Drawing> animationScriptDrawingValue(PDG_POSE_SCRIPT_PARAMETERS,v8::Local<v8::Value> input)
    {
        if(input->IsString())
        {
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto value=JSValueToStringCopy(ctx,input,exception);std::string message(JSStringGetMaximumUTF8CStringSize(value),'\0');JSStringGetUTF8CString(value,&message[0],message.size());JSStringRelease(value);throw std::runtime_error(message.c_str());
#else
            v8::String::Utf8Value message(isolate,input);throw std::runtime_error(*message?*message:"Drawing callback failed");
#endif
        }
        if(input->IsNull())return {};
        Drawing* result = 0;
        if ((input)->IsObject())
        {
            v8::Local<v8::Object> result_scriptObj_ = (input)->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
            DrawingWrap* result__ = dynamic_cast<DrawingWrap*>(pdg::v8script::safe_unwrap_object_wrap_or_prototype(isolate, input, &result_scriptObj_));
            if (result__)
            {
                result = result__->getCppObject();
            }
        };
        if(!result)throw std::invalid_argument("Animation drawing callback must return a Drawing or null");
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
    ;
    ;
    ;
    ;
    ;
    static v8::Local<v8::Object> animationDrawingBoundsValue(PDG_POSE_SCRIPT_PARAMETERS,const AnimationDrawBounds& bounds)
    {
        auto result=v8_ObjectCreateEmpty(isolate, 0);
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "left").ToLocalChecked(), v8::Number::New(isolate, bounds.left)).ToChecked();(void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "top").ToLocalChecked(), v8::Number::New(isolate, bounds.top)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "right").ToLocalChecked(), v8::Number::New(isolate, bounds.right)).ToChecked();(void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "bottom").ToLocalChecked(), v8::Number::New(isolate, bounds.bottom)).ToChecked();
        (void)result->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "uncullable").ToLocalChecked(), v8::Boolean::New(isolate, bounds.uncullable)).ToChecked();return result;
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
    static bool s_Sprite_InNewFromCpp = false;

    void SpriteWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = new SpriteWrap(args);
        objWrapper->Wrap(args.This());
        ;
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }
    v8::Local<v8::Object> SpriteWrap::NewFromCpp(v8::Isolate* isolate, Sprite* cppObj)
    {
        s_Sprite_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Sprite_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Sprite_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(instance);
        { [[maybe_unused]] v8::Local<v8::Object> obj = instance; SPRITE_SAVE_WEAK(cppObj, obj); cppObj->addRef(); }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) objWrapper->cppPtr_->release();
        objWrapper->cppPtr_ = cppObj;
        s_Sprite_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> SpriteWrap::constructorTpl_;

    void SpriteWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Sprite").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetAttachmentPart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAttachmentPart_Tpl =
            v8::FunctionTemplate::New(isolate, GetAttachmentPart, v8::Local<v8::Value>(), GetAttachmentPart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAttachmentPart").ToLocalChecked(), GetAttachmentPart_Tpl);
        v8::Local<v8::Signature> CreatePart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreatePart_Tpl =
            v8::FunctionTemplate::New(isolate, CreatePart, v8::Local<v8::Value>(), CreatePart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createPart").ToLocalChecked(), CreatePart_Tpl);
        v8::Local<v8::Signature> TransferPart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> TransferPart_Tpl =
            v8::FunctionTemplate::New(isolate, TransferPart, v8::Local<v8::Value>(), TransferPart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "transferPart").ToLocalChecked(), TransferPart_Tpl);
        v8::Local<v8::Signature> SetupFrameCollider_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetupFrameCollider_Tpl =
            v8::FunctionTemplate::New(isolate, SetupFrameCollider, v8::Local<v8::Value>(), SetupFrameCollider_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setupFrameCollider").ToLocalChecked(), SetupFrameCollider_Tpl);
        v8::Local<v8::Signature> SetupAnimationCollider_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetupAnimationCollider_Tpl =
            v8::FunctionTemplate::New(isolate, SetupAnimationCollider, v8::Local<v8::Value>(), SetupAnimationCollider_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setupAnimationCollider").ToLocalChecked(), SetupAnimationCollider_Tpl);
        v8::Local<v8::Signature> SetFrameCollisionMask_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFrameCollisionMask_Tpl =
            v8::FunctionTemplate::New(isolate, SetFrameCollisionMask, v8::Local<v8::Value>(), SetFrameCollisionMask_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFrameCollisionMask").ToLocalChecked(), SetFrameCollisionMask_Tpl);
        v8::Local<v8::Signature> GetPart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPart_Tpl =
            v8::FunctionTemplate::New(isolate, GetPart, v8::Local<v8::Value>(), GetPart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPart").ToLocalChecked(), GetPart_Tpl);
        v8::Local<v8::Signature> FindPart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FindPart_Tpl =
            v8::FunctionTemplate::New(isolate, FindPart, v8::Local<v8::Value>(), FindPart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "findPart").ToLocalChecked(), FindPart_Tpl);
        v8::Local<v8::Signature> GetPartCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPartCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetPartCount, v8::Local<v8::Value>(), GetPartCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPartCount").ToLocalChecked(), GetPartCount_Tpl);
        v8::Local<v8::Signature> GetPartNames_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPartNames_Tpl =
            v8::FunctionTemplate::New(isolate, GetPartNames, v8::Local<v8::Value>(), GetPartNames_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPartNames").ToLocalChecked(), GetPartNames_Tpl);
        v8::Local<v8::Signature> RemovePart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemovePart_Tpl =
            v8::FunctionTemplate::New(isolate, RemovePart, v8::Local<v8::Value>(), RemovePart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removePart").ToLocalChecked(), RemovePart_Tpl);
        v8::Local<v8::Signature> ClearParts_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearParts_Tpl =
            v8::FunctionTemplate::New(isolate, ClearParts, v8::Local<v8::Value>(), ClearParts_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearParts").ToLocalChecked(), ClearParts_Tpl);
        v8::Local<v8::Signature> AddHandler_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddHandler_Tpl =
            v8::FunctionTemplate::New(isolate, AddHandler, v8::Local<v8::Value>(), AddHandler_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addHandler").ToLocalChecked(), AddHandler_Tpl);
        v8::Local<v8::Signature> RemoveHandler_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveHandler_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveHandler, v8::Local<v8::Value>(), RemoveHandler_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeHandler").ToLocalChecked(), RemoveHandler_Tpl);
        v8::Local<v8::Signature> Clear_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Clear_Tpl =
            v8::FunctionTemplate::New(isolate, Clear, v8::Local<v8::Value>(), Clear_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clear").ToLocalChecked(), Clear_Tpl);
        v8::Local<v8::Signature> BlockEvent_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> BlockEvent_Tpl =
            v8::FunctionTemplate::New(isolate, BlockEvent, v8::Local<v8::Value>(), BlockEvent_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "blockEvent").ToLocalChecked(), BlockEvent_Tpl);
        v8::Local<v8::Signature> UnblockEvent_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> UnblockEvent_Tpl =
            v8::FunctionTemplate::New(isolate, UnblockEvent, v8::Local<v8::Value>(), UnblockEvent_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "unblockEvent").ToLocalChecked(), UnblockEvent_Tpl);
        v8::Local<v8::Signature> GetBoundingBox_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBoundingBox_Tpl =
            v8::FunctionTemplate::New(isolate, GetBoundingBox, v8::Local<v8::Value>(), GetBoundingBox_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBoundingBox").ToLocalChecked(), GetBoundingBox_Tpl);
        v8::Local<v8::Signature> GetRotatedBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRotatedBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetRotatedBounds, v8::Local<v8::Value>(), GetRotatedBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRotatedBounds").ToLocalChecked(), GetRotatedBounds_Tpl);
        v8::Local<v8::Signature> GetLocation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLocation_Tpl =
            v8::FunctionTemplate::New(isolate, GetLocation, v8::Local<v8::Value>(), GetLocation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLocation").ToLocalChecked(), GetLocation_Tpl);
        v8::Local<v8::Signature> GetMovement_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMovement_Tpl =
            v8::FunctionTemplate::New(isolate, GetMovement, v8::Local<v8::Value>(), GetMovement_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMovement").ToLocalChecked(), GetMovement_Tpl);
        v8::Local<v8::Signature> GetSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSize_Tpl =
            v8::FunctionTemplate::New(isolate, GetSize, v8::Local<v8::Value>(), GetSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSize").ToLocalChecked(), GetSize_Tpl);
        v8::Local<v8::Signature> GetWidth_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWidth_Tpl =
            v8::FunctionTemplate::New(isolate, GetWidth, v8::Local<v8::Value>(), GetWidth_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getWidth").ToLocalChecked(), GetWidth_Tpl);
        v8::Local<v8::Signature> GetHeight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetHeight_Tpl =
            v8::FunctionTemplate::New(isolate, GetHeight, v8::Local<v8::Value>(), GetHeight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getHeight").ToLocalChecked(), GetHeight_Tpl);
        v8::Local<v8::Signature> GetScale_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetScale_Tpl =
            v8::FunctionTemplate::New(isolate, GetScale, v8::Local<v8::Value>(), GetScale_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getScale").ToLocalChecked(), GetScale_Tpl);
        v8::Local<v8::Signature> GetStretching_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetStretching_Tpl =
            v8::FunctionTemplate::New(isolate, GetStretching, v8::Local<v8::Value>(), GetStretching_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getStretching").ToLocalChecked(), GetStretching_Tpl);
        v8::Local<v8::Signature> GetRotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRotation_Tpl =
            v8::FunctionTemplate::New(isolate, GetRotation, v8::Local<v8::Value>(), GetRotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRotation").ToLocalChecked(), GetRotation_Tpl);
        v8::Local<v8::Signature> GetCenterOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCenterOffset_Tpl =
            v8::FunctionTemplate::New(isolate, GetCenterOffset, v8::Local<v8::Value>(), GetCenterOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCenterOffset").ToLocalChecked(), GetCenterOffset_Tpl);
        v8::Local<v8::Signature> GetSpin_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpin_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpin, v8::Local<v8::Value>(), GetSpin_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSpin").ToLocalChecked(), GetSpin_Tpl);
        v8::Local<v8::Signature> SetLocation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetLocation_Tpl =
            v8::FunctionTemplate::New(isolate, SetLocation, v8::Local<v8::Value>(), SetLocation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setLocation").ToLocalChecked(), SetLocation_Tpl);
        v8::Local<v8::Signature> MoveTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveTo_Tpl =
            v8::FunctionTemplate::New(isolate, MoveTo, v8::Local<v8::Value>(), MoveTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveTo").ToLocalChecked(), MoveTo_Tpl);
        v8::Local<v8::Signature> MoveBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveBy_Tpl =
            v8::FunctionTemplate::New(isolate, MoveBy, v8::Local<v8::Value>(), MoveBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveBy").ToLocalChecked(), MoveBy_Tpl);
        v8::Local<v8::Signature> SetMovement_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMovement_Tpl =
            v8::FunctionTemplate::New(isolate, SetMovement, v8::Local<v8::Value>(), SetMovement_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setMovement").ToLocalChecked(), SetMovement_Tpl);
        v8::Local<v8::Signature> ChangeMovementTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeMovementTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeMovementTo, v8::Local<v8::Value>(), ChangeMovementTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeMovementTo").ToLocalChecked(), ChangeMovementTo_Tpl);
        v8::Local<v8::Signature> ChangeMovementBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeMovementBy_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeMovementBy, v8::Local<v8::Value>(), ChangeMovementBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeMovementBy").ToLocalChecked(), ChangeMovementBy_Tpl);
        v8::Local<v8::Signature> SetSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSize_Tpl =
            v8::FunctionTemplate::New(isolate, SetSize, v8::Local<v8::Value>(), SetSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setSize").ToLocalChecked(), SetSize_Tpl);
        v8::Local<v8::Signature> ChangeCenterOffsetTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeCenterOffsetTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeCenterOffsetTo, v8::Local<v8::Value>(), ChangeCenterOffsetTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeCenterOffsetTo").ToLocalChecked(), ChangeCenterOffsetTo_Tpl);
        v8::Local<v8::Signature> ChangeCenterOffsetBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeCenterOffsetBy_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeCenterOffsetBy, v8::Local<v8::Value>(), ChangeCenterOffsetBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeCenterOffsetBy").ToLocalChecked(), ChangeCenterOffsetBy_Tpl);
        v8::Local<v8::Signature> SetWidth_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWidth_Tpl =
            v8::FunctionTemplate::New(isolate, SetWidth, v8::Local<v8::Value>(), SetWidth_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setWidth").ToLocalChecked(), SetWidth_Tpl);
        v8::Local<v8::Signature> SetHeight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetHeight_Tpl =
            v8::FunctionTemplate::New(isolate, SetHeight, v8::Local<v8::Value>(), SetHeight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setHeight").ToLocalChecked(), SetHeight_Tpl);
        v8::Local<v8::Signature> SetRotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetRotation_Tpl =
            v8::FunctionTemplate::New(isolate, SetRotation, v8::Local<v8::Value>(), SetRotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setRotation").ToLocalChecked(), SetRotation_Tpl);
        v8::Local<v8::Signature> SetSpin_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSpin_Tpl =
            v8::FunctionTemplate::New(isolate, SetSpin, v8::Local<v8::Value>(), SetSpin_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setSpin").ToLocalChecked(), SetSpin_Tpl);
        v8::Local<v8::Signature> SetGrowing_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetGrowing_Tpl =
            v8::FunctionTemplate::New(isolate, SetGrowing, v8::Local<v8::Value>(), SetGrowing_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setGrowing").ToLocalChecked(), SetGrowing_Tpl);
        v8::Local<v8::Signature> SetStretching_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetStretching_Tpl =
            v8::FunctionTemplate::New(isolate, SetStretching, v8::Local<v8::Value>(), SetStretching_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setStretching").ToLocalChecked(), SetStretching_Tpl);
        v8::Local<v8::Signature> SetScale_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetScale_Tpl =
            v8::FunctionTemplate::New(isolate, SetScale, v8::Local<v8::Value>(), SetScale_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setScale").ToLocalChecked(), SetScale_Tpl);
        v8::Local<v8::Signature> ChangeSpinTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeSpinTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeSpinTo, v8::Local<v8::Value>(), ChangeSpinTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeSpinTo").ToLocalChecked(), ChangeSpinTo_Tpl);
        v8::Local<v8::Signature> ChangeSpinBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeSpinBy_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeSpinBy, v8::Local<v8::Value>(), ChangeSpinBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeSpinBy").ToLocalChecked(), ChangeSpinBy_Tpl);
        v8::Local<v8::Signature> ChangeGrowingTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeGrowingTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeGrowingTo, v8::Local<v8::Value>(), ChangeGrowingTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeGrowingTo").ToLocalChecked(), ChangeGrowingTo_Tpl);
        v8::Local<v8::Signature> ChangeGrowingBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeGrowingBy_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeGrowingBy, v8::Local<v8::Value>(), ChangeGrowingBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeGrowingBy").ToLocalChecked(), ChangeGrowingBy_Tpl);
        v8::Local<v8::Signature> ChangeStretchingTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeStretchingTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeStretchingTo, v8::Local<v8::Value>(), ChangeStretchingTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeStretchingTo").ToLocalChecked(), ChangeStretchingTo_Tpl);
        v8::Local<v8::Signature> ChangeStretchingBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeStretchingBy_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeStretchingBy, v8::Local<v8::Value>(), ChangeStretchingBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeStretchingBy").ToLocalChecked(), ChangeStretchingBy_Tpl);
        v8::Local<v8::Signature> ChangeScaleTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeScaleTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeScaleTo, v8::Local<v8::Value>(), ChangeScaleTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeScaleTo").ToLocalChecked(), ChangeScaleTo_Tpl);
        v8::Local<v8::Signature> ChangeScaleBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeScaleBy_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeScaleBy, v8::Local<v8::Value>(), ChangeScaleBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeScaleBy").ToLocalChecked(), ChangeScaleBy_Tpl);
        v8::Local<v8::Signature> Grow_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Grow_Tpl =
            v8::FunctionTemplate::New(isolate, Grow, v8::Local<v8::Value>(), Grow_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "grow").ToLocalChecked(), Grow_Tpl);
        v8::Local<v8::Signature> Stretch_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Stretch_Tpl =
            v8::FunctionTemplate::New(isolate, Stretch, v8::Local<v8::Value>(), Stretch_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stretch").ToLocalChecked(), Stretch_Tpl);
        v8::Local<v8::Signature> ResizeBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ResizeBy_Tpl =
            v8::FunctionTemplate::New(isolate, ResizeBy, v8::Local<v8::Value>(), ResizeBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resizeBy").ToLocalChecked(), ResizeBy_Tpl);
        v8::Local<v8::Signature> ResizeTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ResizeTo_Tpl =
            v8::FunctionTemplate::New(isolate, ResizeTo, v8::Local<v8::Value>(), ResizeTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resizeTo").ToLocalChecked(), ResizeTo_Tpl);
        v8::Local<v8::Signature> RotateBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RotateBy_Tpl =
            v8::FunctionTemplate::New(isolate, RotateBy, v8::Local<v8::Value>(), RotateBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "rotateBy").ToLocalChecked(), RotateBy_Tpl);
        v8::Local<v8::Signature> RotateTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RotateTo_Tpl =
            v8::FunctionTemplate::New(isolate, RotateTo, v8::Local<v8::Value>(), RotateTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "rotateTo").ToLocalChecked(), RotateTo_Tpl);
        v8::Local<v8::Signature> SetCenterOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCenterOffset_Tpl =
            v8::FunctionTemplate::New(isolate, SetCenterOffset, v8::Local<v8::Value>(), SetCenterOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCenterOffset").ToLocalChecked(), SetCenterOffset_Tpl);
        v8::Local<v8::Signature> SetFlipX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFlipX_Tpl =
            v8::FunctionTemplate::New(isolate, SetFlipX, v8::Local<v8::Value>(), SetFlipX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFlipX").ToLocalChecked(), SetFlipX_Tpl);
        v8::Local<v8::Signature> SetFlipY_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFlipY_Tpl =
            v8::FunctionTemplate::New(isolate, SetFlipY, v8::Local<v8::Value>(), SetFlipY_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFlipY").ToLocalChecked(), SetFlipY_Tpl);
        v8::Local<v8::Signature> StopMovement_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopMovement_Tpl =
            v8::FunctionTemplate::New(isolate, StopMovement, v8::Local<v8::Value>(), StopMovement_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopMovement").ToLocalChecked(), StopMovement_Tpl);
        v8::Local<v8::Signature> StopSpinning_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopSpinning_Tpl =
            v8::FunctionTemplate::New(isolate, StopSpinning, v8::Local<v8::Value>(), StopSpinning_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopSpinning").ToLocalChecked(), StopSpinning_Tpl);
        v8::Local<v8::Signature> StopGrowing_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopGrowing_Tpl =
            v8::FunctionTemplate::New(isolate, StopGrowing, v8::Local<v8::Value>(), StopGrowing_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopGrowing").ToLocalChecked(), StopGrowing_Tpl);
        v8::Local<v8::Signature> StopStretching_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopStretching_Tpl =
            v8::FunctionTemplate::New(isolate, StopStretching, v8::Local<v8::Value>(), StopStretching_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopStretching").ToLocalChecked(), StopStretching_Tpl);
        v8::Local<v8::Signature> PauseSchedule_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PauseSchedule_Tpl =
            v8::FunctionTemplate::New(isolate, PauseSchedule, v8::Local<v8::Value>(), PauseSchedule_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "pauseSchedule").ToLocalChecked(), PauseSchedule_Tpl);
        v8::Local<v8::Signature> ResumeSchedule_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ResumeSchedule_Tpl =
            v8::FunctionTemplate::New(isolate, ResumeSchedule, v8::Local<v8::Value>(), ResumeSchedule_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resumeSchedule").ToLocalChecked(), ResumeSchedule_Tpl);
        v8::Local<v8::Signature> CancelSchedule_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CancelSchedule_Tpl =
            v8::FunctionTemplate::New(isolate, CancelSchedule, v8::Local<v8::Value>(), CancelSchedule_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "cancelSchedule").ToLocalChecked(), CancelSchedule_Tpl);
        v8::Local<v8::Signature> FlipX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FlipX_Tpl =
            v8::FunctionTemplate::New(isolate, FlipX, v8::Local<v8::Value>(), FlipX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "flipX").ToLocalChecked(), FlipX_Tpl);
        v8::Local<v8::Signature> FlipY_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FlipY_Tpl =
            v8::FunctionTemplate::New(isolate, FlipY, v8::Local<v8::Value>(), FlipY_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "flipY").ToLocalChecked(), FlipY_Tpl);
        v8::Local<v8::Signature> AndThen_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AndThen_Tpl =
            v8::FunctionTemplate::New(isolate, AndThen, v8::Local<v8::Value>(), AndThen_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "andThen").ToLocalChecked(), AndThen_Tpl);
        v8::Local<v8::Signature> IsFlippedX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsFlippedX_Tpl =
            v8::FunctionTemplate::New(isolate, IsFlippedX, v8::Local<v8::Value>(), IsFlippedX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isFlippedX").ToLocalChecked(), IsFlippedX_Tpl);
        v8::Local<v8::Signature> IsFlippedY_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsFlippedY_Tpl =
            v8::FunctionTemplate::New(isolate, IsFlippedY, v8::Local<v8::Value>(), IsFlippedY_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isFlippedY").ToLocalChecked(), IsFlippedY_Tpl);
        v8::Local<v8::Signature> IsSchedulePaused_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsSchedulePaused_Tpl =
            v8::FunctionTemplate::New(isolate, IsSchedulePaused, v8::Local<v8::Value>(), IsSchedulePaused_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isSchedulePaused").ToLocalChecked(), IsSchedulePaused_Tpl);
        v8::Local<v8::Signature> HasScheduledAnimations_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> HasScheduledAnimations_Tpl =
            v8::FunctionTemplate::New(isolate, HasScheduledAnimations, v8::Local<v8::Value>(), HasScheduledAnimations_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "hasScheduledAnimations").ToLocalChecked(), HasScheduledAnimations_Tpl);
        v8::Local<v8::Signature> Wait_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Wait_Tpl =
            v8::FunctionTemplate::New(isolate, Wait, v8::Local<v8::Value>(), Wait_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "wait").ToLocalChecked(), Wait_Tpl);
        v8::Local<v8::Signature> AddAnimationHelper_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddAnimationHelper_Tpl =
            v8::FunctionTemplate::New(isolate, AddAnimationHelper, v8::Local<v8::Value>(), AddAnimationHelper_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addAnimationHelper").ToLocalChecked(), AddAnimationHelper_Tpl);
        v8::Local<v8::Signature> RemoveAnimationHelper_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveAnimationHelper_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveAnimationHelper, v8::Local<v8::Value>(), RemoveAnimationHelper_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeAnimationHelper").ToLocalChecked(), RemoveAnimationHelper_Tpl);
        v8::Local<v8::Signature> ClearAnimationHelpers_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearAnimationHelpers_Tpl =
            v8::FunctionTemplate::New(isolate, ClearAnimationHelpers, v8::Local<v8::Value>(), ClearAnimationHelpers_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearAnimationHelpers").ToLocalChecked(), ClearAnimationHelpers_Tpl);
        v8::Local<v8::Signature> ReadCollider_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ReadCollider_Tpl =
            v8::FunctionTemplate::New(isolate, ReadCollider, v8::Local<v8::Value>(), ReadCollider_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "_readCollider").ToLocalChecked(), ReadCollider_Tpl);
        v8::Local<v8::Signature> SetupCollider_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetupCollider_Tpl =
            v8::FunctionTemplate::New(isolate, SetupCollider, v8::Local<v8::Value>(), SetupCollider_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setupCollider").ToLocalChecked(), SetupCollider_Tpl);
        v8::Local<v8::Signature> RemoveCollider_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveCollider_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveCollider, v8::Local<v8::Value>(), RemoveCollider_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeCollider").ToLocalChecked(), RemoveCollider_Tpl);
        v8::Local<v8::Signature> ReadPhysics_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ReadPhysics_Tpl =
            v8::FunctionTemplate::New(isolate, ReadPhysics, v8::Local<v8::Value>(), ReadPhysics_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "_readPhysics").ToLocalChecked(), ReadPhysics_Tpl);
        v8::Local<v8::Signature> SetupPhysicsBody_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetupPhysicsBody_Tpl =
            v8::FunctionTemplate::New(isolate, SetupPhysicsBody, v8::Local<v8::Value>(), SetupPhysicsBody_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setupPhysicsBody").ToLocalChecked(), SetupPhysicsBody_Tpl);
        v8::Local<v8::Signature> RemovePhysicsBody_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemovePhysicsBody_Tpl =
            v8::FunctionTemplate::New(isolate, RemovePhysicsBody, v8::Local<v8::Value>(), RemovePhysicsBody_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removePhysicsBody").ToLocalChecked(), RemovePhysicsBody_Tpl);
        v8::Local<v8::Signature> GetMyClassTag_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMyClassTag_Tpl =
            v8::FunctionTemplate::New(isolate, GetMyClassTag, v8::Local<v8::Value>(), GetMyClassTag_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""MyClassTag").ToLocalChecked(), GetMyClassTag_Tpl);
        v8::Local<v8::Signature> GetSerializedSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSerializedSize_Tpl =
            v8::FunctionTemplate::New(isolate, GetSerializedSize, v8::Local<v8::Value>(), GetSerializedSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""SerializedSize").ToLocalChecked(), GetSerializedSize_Tpl);
        v8::Local<v8::Signature> Serialize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize, v8::Local<v8::Value>(), Serialize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize").ToLocalChecked(), Serialize_Tpl);
        v8::Local<v8::Signature> Deserialize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize, v8::Local<v8::Value>(), Deserialize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize").ToLocalChecked(), Deserialize_Tpl);
        v8::Local<v8::Signature> GetFrameRotatedBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFrameRotatedBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetFrameRotatedBounds, v8::Local<v8::Value>(), GetFrameRotatedBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFrameRotatedBounds").ToLocalChecked(), GetFrameRotatedBounds_Tpl);
        v8::Local<v8::Signature> SetFrame_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFrame_Tpl =
            v8::FunctionTemplate::New(isolate, SetFrame, v8::Local<v8::Value>(), SetFrame_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFrame").ToLocalChecked(), SetFrame_Tpl);
        v8::Local<v8::Signature> GetCurrentFrame_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCurrentFrame_Tpl =
            v8::FunctionTemplate::New(isolate, GetCurrentFrame, v8::Local<v8::Value>(), GetCurrentFrame_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCurrentFrame").ToLocalChecked(), GetCurrentFrame_Tpl);
        v8::Local<v8::Signature> GetFrameCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFrameCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetFrameCount, v8::Local<v8::Value>(), GetFrameCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFrameCount").ToLocalChecked(), GetFrameCount_Tpl);
        v8::Local<v8::Signature> StartFrameAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StartFrameAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, StartFrameAnimation, v8::Local<v8::Value>(), StartFrameAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "startFrameAnimation").ToLocalChecked(), StartFrameAnimation_Tpl);
        v8::Local<v8::Signature> StopFrameAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopFrameAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, StopFrameAnimation, v8::Local<v8::Value>(), StopFrameAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopFrameAnimation").ToLocalChecked(), StopFrameAnimation_Tpl);
        v8::Local<v8::Signature> GetWantsAnimLoopEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsAnimLoopEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsAnimLoopEvents, v8::Local<v8::Value>(), GetWantsAnimLoopEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WantsAnimLoopEvents").ToLocalChecked(), GetWantsAnimLoopEvents_Tpl);
        v8::Local<v8::Signature> SetWantsAnimLoopEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsAnimLoopEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsAnimLoopEvents, v8::Local<v8::Value>(), SetWantsAnimLoopEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WantsAnimLoopEvents").ToLocalChecked(), SetWantsAnimLoopEvents_Tpl);
        v8::Local<v8::Signature> GetWantsAnimEndEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsAnimEndEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsAnimEndEvents, v8::Local<v8::Value>(), GetWantsAnimEndEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WantsAnimEndEvents").ToLocalChecked(), GetWantsAnimEndEvents_Tpl);
        v8::Local<v8::Signature> SetWantsAnimEndEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsAnimEndEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsAnimEndEvents, v8::Local<v8::Value>(), SetWantsAnimEndEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WantsAnimEndEvents").ToLocalChecked(), SetWantsAnimEndEvents_Tpl);
        v8::Local<v8::Signature> GetWantsCollideWallEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsCollideWallEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsCollideWallEvents, v8::Local<v8::Value>(), GetWantsCollideWallEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WantsCollideWallEvents").ToLocalChecked(), GetWantsCollideWallEvents_Tpl);
        v8::Local<v8::Signature> SetWantsCollideWallEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsCollideWallEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsCollideWallEvents, v8::Local<v8::Value>(), SetWantsCollideWallEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WantsCollideWallEvents").ToLocalChecked(), SetWantsCollideWallEvents_Tpl);
        v8::Local<v8::Signature> AddFramesImage_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddFramesImage_Tpl =
            v8::FunctionTemplate::New(isolate, AddFramesImage, v8::Local<v8::Value>(), AddFramesImage_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addFramesImage").ToLocalChecked(), AddFramesImage_Tpl);
#ifdef PDG_SPRITER_SUPPORT
        v8::Local<v8::Signature> SeekAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SeekAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, SeekAnimation, v8::Local<v8::Value>(), SeekAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "seekAnimation").ToLocalChecked(), SeekAnimation_Tpl);
        v8::Local<v8::Signature> TransitionToAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> TransitionToAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, TransitionToAnimation, v8::Local<v8::Value>(), TransitionToAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "transitionToAnimation").ToLocalChecked(), TransitionToAnimation_Tpl);
        v8::Local<v8::Signature> IsAnimationTransitioning_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsAnimationTransitioning_Tpl =
            v8::FunctionTemplate::New(isolate, IsAnimationTransitioning, v8::Local<v8::Value>(), IsAnimationTransitioning_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isAnimationTransitioning").ToLocalChecked(), IsAnimationTransitioning_Tpl);
        v8::Local<v8::Signature> GetAnimationTransitionProgress_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationTransitionProgress_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationTransitionProgress, v8::Local<v8::Value>(), GetAnimationTransitionProgress_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationTransitionProgress").ToLocalChecked(), GetAnimationTransitionProgress_Tpl);
        v8::Local<v8::Signature> SupportsAnimationPhysics_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SupportsAnimationPhysics_Tpl =
            v8::FunctionTemplate::New(isolate, SupportsAnimationPhysics, v8::Local<v8::Value>(), SupportsAnimationPhysics_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "supportsAnimationPhysics").ToLocalChecked(), SupportsAnimationPhysics_Tpl);
        v8::Local<v8::Signature> SetupAnimationPhysics_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetupAnimationPhysics_Tpl =
            v8::FunctionTemplate::New(isolate, SetupAnimationPhysics, v8::Local<v8::Value>(), SetupAnimationPhysics_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setupAnimationPhysics").ToLocalChecked(), SetupAnimationPhysics_Tpl);
        v8::Local<v8::Signature> SetupPhysicsFromAnimationRig_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetupPhysicsFromAnimationRig_Tpl =
            v8::FunctionTemplate::New(isolate, SetupPhysicsFromAnimationRig, v8::Local<v8::Value>(), SetupPhysicsFromAnimationRig_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setupPhysicsFromAnimationRig").ToLocalChecked(), SetupPhysicsFromAnimationRig_Tpl);
        v8::Local<v8::Signature> AttachAnimationPhysicsPart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AttachAnimationPhysicsPart_Tpl =
            v8::FunctionTemplate::New(isolate, AttachAnimationPhysicsPart, v8::Local<v8::Value>(), AttachAnimationPhysicsPart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "attachAnimationPhysicsPart").ToLocalChecked(), AttachAnimationPhysicsPart_Tpl);
        v8::Local<v8::Signature> DetachAnimationPhysicsPart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DetachAnimationPhysicsPart_Tpl =
            v8::FunctionTemplate::New(isolate, DetachAnimationPhysicsPart, v8::Local<v8::Value>(), DetachAnimationPhysicsPart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "detachAnimationPhysicsPart").ToLocalChecked(), DetachAnimationPhysicsPart_Tpl);
        v8::Local<v8::Signature> IsAnimationPhysicsPartAttached_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsAnimationPhysicsPartAttached_Tpl =
            v8::FunctionTemplate::New(isolate, IsAnimationPhysicsPartAttached, v8::Local<v8::Value>(), IsAnimationPhysicsPartAttached_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isAnimationPhysicsPartAttached").ToLocalChecked(), IsAnimationPhysicsPartAttached_Tpl);
        v8::Local<v8::Signature> SetAnimationPhysicsRoot_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAnimationPhysicsRoot_Tpl =
            v8::FunctionTemplate::New(isolate, SetAnimationPhysicsRoot, v8::Local<v8::Value>(), SetAnimationPhysicsRoot_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAnimationPhysicsRoot").ToLocalChecked(), SetAnimationPhysicsRoot_Tpl);
        v8::Local<v8::Signature> GetAnimationPhysicsRoot_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationPhysicsRoot_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationPhysicsRoot, v8::Local<v8::Value>(), GetAnimationPhysicsRoot_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationPhysicsRoot").ToLocalChecked(), GetAnimationPhysicsRoot_Tpl);
        v8::Local<v8::Signature> ClearAnimationPhysicsRoot_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearAnimationPhysicsRoot_Tpl =
            v8::FunctionTemplate::New(isolate, ClearAnimationPhysicsRoot, v8::Local<v8::Value>(), ClearAnimationPhysicsRoot_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearAnimationPhysicsRoot").ToLocalChecked(), ClearAnimationPhysicsRoot_Tpl);
        v8::Local<v8::Signature> GetAnimationPhysicsSetupWarnings_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationPhysicsSetupWarnings_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationPhysicsSetupWarnings, v8::Local<v8::Value>(), GetAnimationPhysicsSetupWarnings_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationPhysicsSetupWarnings").ToLocalChecked(), GetAnimationPhysicsSetupWarnings_Tpl);
        v8::Local<v8::Signature> SetAnimationPhysicsMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAnimationPhysicsMode_Tpl =
            v8::FunctionTemplate::New(isolate, SetAnimationPhysicsMode, v8::Local<v8::Value>(), SetAnimationPhysicsMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAnimationPhysicsMode").ToLocalChecked(), SetAnimationPhysicsMode_Tpl);
        v8::Local<v8::Signature> GetAnimationPhysicsMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationPhysicsMode_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationPhysicsMode, v8::Local<v8::Value>(), GetAnimationPhysicsMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationPhysicsMode").ToLocalChecked(), GetAnimationPhysicsMode_Tpl);
        v8::Local<v8::Signature> SetAnimationPhysicsDriveSettings_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAnimationPhysicsDriveSettings_Tpl =
            v8::FunctionTemplate::New(isolate, SetAnimationPhysicsDriveSettings, v8::Local<v8::Value>(), SetAnimationPhysicsDriveSettings_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAnimationPhysicsDriveSettings").ToLocalChecked(), SetAnimationPhysicsDriveSettings_Tpl);
        v8::Local<v8::Signature> GetAnimationPhysicsDriveSettings_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationPhysicsDriveSettings_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationPhysicsDriveSettings, v8::Local<v8::Value>(), GetAnimationPhysicsDriveSettings_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationPhysicsDriveSettings").ToLocalChecked(), GetAnimationPhysicsDriveSettings_Tpl);
        v8::Local<v8::Signature> DisableAnimationPhysics_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DisableAnimationPhysics_Tpl =
            v8::FunctionTemplate::New(isolate, DisableAnimationPhysics, v8::Local<v8::Value>(), DisableAnimationPhysics_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "disableAnimationPhysics").ToLocalChecked(), DisableAnimationPhysics_Tpl);
        v8::Local<v8::Signature> IsAnimationPhysicsEnabled_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsAnimationPhysicsEnabled_Tpl =
            v8::FunctionTemplate::New(isolate, IsAnimationPhysicsEnabled, v8::Local<v8::Value>(), IsAnimationPhysicsEnabled_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isAnimationPhysicsEnabled").ToLocalChecked(), IsAnimationPhysicsEnabled_Tpl);
        v8::Local<v8::Signature> AddAnimationDrawable_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddAnimationDrawable_Tpl =
            v8::FunctionTemplate::New(isolate, AddAnimationDrawable, v8::Local<v8::Value>(), AddAnimationDrawable_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addAnimationDrawable").ToLocalChecked(), AddAnimationDrawable_Tpl);
        v8::Local<v8::Signature> RemoveAnimationDrawable_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveAnimationDrawable_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveAnimationDrawable, v8::Local<v8::Value>(), RemoveAnimationDrawable_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeAnimationDrawable").ToLocalChecked(), RemoveAnimationDrawable_Tpl);
        v8::Local<v8::Signature> ClearAnimationDrawables_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearAnimationDrawables_Tpl =
            v8::FunctionTemplate::New(isolate, ClearAnimationDrawables, v8::Local<v8::Value>(), ClearAnimationDrawables_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearAnimationDrawables").ToLocalChecked(), ClearAnimationDrawables_Tpl);
        v8::Local<v8::Signature> SetAnimationDrawableEnabled_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAnimationDrawableEnabled_Tpl =
            v8::FunctionTemplate::New(isolate, SetAnimationDrawableEnabled, v8::Local<v8::Value>(), SetAnimationDrawableEnabled_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAnimationDrawableEnabled").ToLocalChecked(), SetAnimationDrawableEnabled_Tpl);
        v8::Local<v8::Signature> GetAnimationDrawableError_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationDrawableError_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationDrawableError, v8::Local<v8::Value>(), GetAnimationDrawableError_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationDrawableError").ToLocalChecked(), GetAnimationDrawableError_Tpl);
        v8::Local<v8::Signature> GetAnimationDrawBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationDrawBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationDrawBounds, v8::Local<v8::Value>(), GetAnimationDrawBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationDrawBounds").ToLocalChecked(), GetAnimationDrawBounds_Tpl);
        v8::Local<v8::Signature> AddAnimationIK_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddAnimationIK_Tpl =
            v8::FunctionTemplate::New(isolate, AddAnimationIK, v8::Local<v8::Value>(), AddAnimationIK_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addAnimationIK").ToLocalChecked(), AddAnimationIK_Tpl);
        v8::Local<v8::Signature> SetAnimationIKTarget_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAnimationIKTarget_Tpl =
            v8::FunctionTemplate::New(isolate, SetAnimationIKTarget, v8::Local<v8::Value>(), SetAnimationIKTarget_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAnimationIKTarget").ToLocalChecked(), SetAnimationIKTarget_Tpl);
        v8::Local<v8::Signature> GetAnimationIKResult_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationIKResult_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationIKResult, v8::Local<v8::Value>(), GetAnimationIKResult_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationIKResult").ToLocalChecked(), GetAnimationIKResult_Tpl);
        v8::Local<v8::Signature> AddAnimationModifier_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddAnimationModifier_Tpl =
            v8::FunctionTemplate::New(isolate, AddAnimationModifier, v8::Local<v8::Value>(), AddAnimationModifier_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addAnimationModifier").ToLocalChecked(), AddAnimationModifier_Tpl);
        v8::Local<v8::Signature> RemoveAnimationModifier_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveAnimationModifier_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveAnimationModifier, v8::Local<v8::Value>(), RemoveAnimationModifier_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeAnimationModifier").ToLocalChecked(), RemoveAnimationModifier_Tpl);
        v8::Local<v8::Signature> ClearAnimationModifiers_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearAnimationModifiers_Tpl =
            v8::FunctionTemplate::New(isolate, ClearAnimationModifiers, v8::Local<v8::Value>(), ClearAnimationModifiers_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearAnimationModifiers").ToLocalChecked(), ClearAnimationModifiers_Tpl);
        v8::Local<v8::Signature> GetAnimationModifierError_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationModifierError_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationModifierError, v8::Local<v8::Value>(), GetAnimationModifierError_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationModifierError").ToLocalChecked(), GetAnimationModifierError_Tpl);
        v8::Local<v8::Signature> SetAnimationSource_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAnimationSource_Tpl =
            v8::FunctionTemplate::New(isolate, SetAnimationSource, v8::Local<v8::Value>(), SetAnimationSource_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAnimationSource").ToLocalChecked(), SetAnimationSource_Tpl);
        v8::Local<v8::Signature> GetAnimationSource_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationSource_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationSource, v8::Local<v8::Value>(), GetAnimationSource_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationSource").ToLocalChecked(), GetAnimationSource_Tpl);
        v8::Local<v8::Signature> IsAnimationDrawingSupported_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsAnimationDrawingSupported_Tpl =
            v8::FunctionTemplate::New(isolate, IsAnimationDrawingSupported, v8::Local<v8::Value>(), IsAnimationDrawingSupported_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isAnimationDrawingSupported").ToLocalChecked(), IsAnimationDrawingSupported_Tpl);
        v8::Local<v8::Signature> SetAnimationDebugDraw_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAnimationDebugDraw_Tpl =
            v8::FunctionTemplate::New(isolate, SetAnimationDebugDraw, v8::Local<v8::Value>(), SetAnimationDebugDraw_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAnimationDebugDraw").ToLocalChecked(), SetAnimationDebugDraw_Tpl);
        v8::Local<v8::Signature> GetAnimationDebugDraw_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationDebugDraw_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationDebugDraw, v8::Local<v8::Value>(), GetAnimationDebugDraw_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationDebugDraw").ToLocalChecked(), GetAnimationDebugDraw_Tpl);
        v8::Local<v8::Signature> EnableAnimationPose_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> EnableAnimationPose_Tpl =
            v8::FunctionTemplate::New(isolate, EnableAnimationPose, v8::Local<v8::Value>(), EnableAnimationPose_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "enableAnimationPose").ToLocalChecked(), EnableAnimationPose_Tpl);
        v8::Local<v8::Signature> DisableAnimationPose_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DisableAnimationPose_Tpl =
            v8::FunctionTemplate::New(isolate, DisableAnimationPose, v8::Local<v8::Value>(), DisableAnimationPose_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "disableAnimationPose").ToLocalChecked(), DisableAnimationPose_Tpl);
        v8::Local<v8::Signature> IsAnimationPoseEnabled_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsAnimationPoseEnabled_Tpl =
            v8::FunctionTemplate::New(isolate, IsAnimationPoseEnabled, v8::Local<v8::Value>(), IsAnimationPoseEnabled_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isAnimationPoseEnabled").ToLocalChecked(), IsAnimationPoseEnabled_Tpl);
        v8::Local<v8::Signature> GetAnimationRigError_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationRigError_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationRigError, v8::Local<v8::Value>(), GetAnimationRigError_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationRigError").ToLocalChecked(), GetAnimationRigError_Tpl);
        v8::Local<v8::Signature> GetAnimationBoneNames_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationBoneNames_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationBoneNames, v8::Local<v8::Value>(), GetAnimationBoneNames_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationBoneNames").ToLocalChecked(), GetAnimationBoneNames_Tpl);
        v8::Local<v8::Signature> GetAnimationBindingNames_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationBindingNames_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationBindingNames, v8::Local<v8::Value>(), GetAnimationBindingNames_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationBindingNames").ToLocalChecked(), GetAnimationBindingNames_Tpl);
        v8::Local<v8::Signature> GetAnimationBoneTransform_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationBoneTransform_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationBoneTransform, v8::Local<v8::Value>(), GetAnimationBoneTransform_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationBoneTransform").ToLocalChecked(), GetAnimationBoneTransform_Tpl);
        v8::Local<v8::Signature> GetAnimationBindingTransform_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationBindingTransform_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationBindingTransform, v8::Local<v8::Value>(), GetAnimationBindingTransform_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationBindingTransform").ToLocalChecked(), GetAnimationBindingTransform_Tpl);
        v8::Local<v8::Signature> SetAnimationBoneTransform_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAnimationBoneTransform_Tpl =
            v8::FunctionTemplate::New(isolate, SetAnimationBoneTransform, v8::Local<v8::Value>(), SetAnimationBoneTransform_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAnimationBoneTransform").ToLocalChecked(), SetAnimationBoneTransform_Tpl);
        v8::Local<v8::Signature> ClearAnimationBoneTransforms_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearAnimationBoneTransforms_Tpl =
            v8::FunctionTemplate::New(isolate, ClearAnimationBoneTransforms, v8::Local<v8::Value>(), ClearAnimationBoneTransforms_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearAnimationBoneTransforms").ToLocalChecked(), ClearAnimationBoneTransforms_Tpl);
        v8::Local<v8::Signature> GetAnimationPose_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationPose_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationPose, v8::Local<v8::Value>(), GetAnimationPose_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationPose").ToLocalChecked(), GetAnimationPose_Tpl);
        v8::Local<v8::Signature> SampleAnimationPose_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SampleAnimationPose_Tpl =
            v8::FunctionTemplate::New(isolate, SampleAnimationPose, v8::Local<v8::Value>(), SampleAnimationPose_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sampleAnimationPose").ToLocalChecked(), SampleAnimationPose_Tpl);
        v8::Local<v8::Signature> HasAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> HasAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, HasAnimation, v8::Local<v8::Value>(), HasAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "hasAnimation").ToLocalChecked(), HasAnimation_Tpl);
        v8::Local<v8::Signature> StartAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StartAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, StartAnimation, v8::Local<v8::Value>(), StartAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "startAnimation").ToLocalChecked(), StartAnimation_Tpl);
        v8::Local<v8::Signature> ApplyCharacterMap_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ApplyCharacterMap_Tpl =
            v8::FunctionTemplate::New(isolate, ApplyCharacterMap, v8::Local<v8::Value>(), ApplyCharacterMap_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "applyCharacterMap").ToLocalChecked(), ApplyCharacterMap_Tpl);
        v8::Local<v8::Signature> RemoveCharacterMap_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveCharacterMap_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveCharacterMap, v8::Local<v8::Value>(), RemoveCharacterMap_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeCharacterMap").ToLocalChecked(), RemoveCharacterMap_Tpl);
        v8::Local<v8::Signature> RemoveAllCharacterMaps_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveAllCharacterMaps_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveAllCharacterMaps, v8::Local<v8::Value>(), RemoveAllCharacterMaps_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeAllCharacterMaps").ToLocalChecked(), RemoveAllCharacterMaps_Tpl);
        v8::Local<v8::Signature> GetAppliedCharacterMaps_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAppliedCharacterMaps_Tpl =
            v8::FunctionTemplate::New(isolate, GetAppliedCharacterMaps, v8::Local<v8::Value>(), GetAppliedCharacterMaps_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAppliedCharacterMaps").ToLocalChecked(), GetAppliedCharacterMaps_Tpl);
        v8::Local<v8::Signature> EnableSpriterEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> EnableSpriterEvents_Tpl =
            v8::FunctionTemplate::New(isolate, EnableSpriterEvents, v8::Local<v8::Value>(), EnableSpriterEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "enableSpriterEvents").ToLocalChecked(), EnableSpriterEvents_Tpl);
        v8::Local<v8::Signature> AreSpriterEventsEnabled_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AreSpriterEventsEnabled_Tpl =
            v8::FunctionTemplate::New(isolate, AreSpriterEventsEnabled, v8::Local<v8::Value>(), AreSpriterEventsEnabled_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "areSpriterEventsEnabled").ToLocalChecked(), AreSpriterEventsEnabled_Tpl);
        v8::Local<v8::Signature> BlendToAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> BlendToAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, BlendToAnimation, v8::Local<v8::Value>(), BlendToAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "blendToAnimation").ToLocalChecked(), BlendToAnimation_Tpl);
        v8::Local<v8::Signature> IsBlending_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsBlending_Tpl =
            v8::FunctionTemplate::New(isolate, IsBlending, v8::Local<v8::Value>(), IsBlending_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isBlending").ToLocalChecked(), IsBlending_Tpl);
        v8::Local<v8::Signature> GetBlendProgress_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBlendProgress_Tpl =
            v8::FunctionTemplate::New(isolate, GetBlendProgress, v8::Local<v8::Value>(), GetBlendProgress_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBlendProgress").ToLocalChecked(), GetBlendProgress_Tpl);
        v8::Local<v8::Signature> PauseAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PauseAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, PauseAnimation, v8::Local<v8::Value>(), PauseAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "pauseAnimation").ToLocalChecked(), PauseAnimation_Tpl);
        v8::Local<v8::Signature> ResumeAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ResumeAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, ResumeAnimation, v8::Local<v8::Value>(), ResumeAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resumeAnimation").ToLocalChecked(), ResumeAnimation_Tpl);
        v8::Local<v8::Signature> StopAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, StopAnimation, v8::Local<v8::Value>(), StopAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopAnimation").ToLocalChecked(), StopAnimation_Tpl);
        v8::Local<v8::Signature> IsAnimationPlaying_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsAnimationPlaying_Tpl =
            v8::FunctionTemplate::New(isolate, IsAnimationPlaying, v8::Local<v8::Value>(), IsAnimationPlaying_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isAnimationPlaying").ToLocalChecked(), IsAnimationPlaying_Tpl);
        v8::Local<v8::Signature> IsAnimationPaused_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsAnimationPaused_Tpl =
            v8::FunctionTemplate::New(isolate, IsAnimationPaused, v8::Local<v8::Value>(), IsAnimationPaused_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isAnimationPaused").ToLocalChecked(), IsAnimationPaused_Tpl);
        v8::Local<v8::Signature> GetAnimationProgress_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationProgress_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationProgress, v8::Local<v8::Value>(), GetAnimationProgress_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationProgress").ToLocalChecked(), GetAnimationProgress_Tpl);
        v8::Local<v8::Signature> HasAttachPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> HasAttachPoint_Tpl =
            v8::FunctionTemplate::New(isolate, HasAttachPoint, v8::Local<v8::Value>(), HasAttachPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "hasAttachPoint").ToLocalChecked(), HasAttachPoint_Tpl);
        v8::Local<v8::Signature> GetAttachPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAttachPoint_Tpl =
            v8::FunctionTemplate::New(isolate, GetAttachPoint, v8::Local<v8::Value>(), GetAttachPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAttachPoint").ToLocalChecked(), GetAttachPoint_Tpl);
        v8::Local<v8::Signature> AttachSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AttachSprite_Tpl =
            v8::FunctionTemplate::New(isolate, AttachSprite, v8::Local<v8::Value>(), AttachSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "attachSprite").ToLocalChecked(), AttachSprite_Tpl);
        v8::Local<v8::Signature> ActivateSubEntity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ActivateSubEntity_Tpl =
            v8::FunctionTemplate::New(isolate, ActivateSubEntity, v8::Local<v8::Value>(), ActivateSubEntity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "activateSubEntity").ToLocalChecked(), ActivateSubEntity_Tpl);
        v8::Local<v8::Signature> DetachSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DetachSprite_Tpl =
            v8::FunctionTemplate::New(isolate, DetachSprite, v8::Local<v8::Value>(), DetachSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "detachSprite").ToLocalChecked(), DetachSprite_Tpl);
        v8::Local<v8::Signature> GetAttachedSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAttachedSprite_Tpl =
            v8::FunctionTemplate::New(isolate, GetAttachedSprite, v8::Local<v8::Value>(), GetAttachedSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAttachedSprite").ToLocalChecked(), GetAttachedSprite_Tpl);
        v8::Local<v8::Signature> GetSpriterCollisionBox_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpriterCollisionBox_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpriterCollisionBox, v8::Local<v8::Value>(), GetSpriterCollisionBox_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSpriterCollisionBox").ToLocalChecked(), GetSpriterCollisionBox_Tpl);
        v8::Local<v8::Signature> IsSpriterCollisionActive_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsSpriterCollisionActive_Tpl =
            v8::FunctionTemplate::New(isolate, IsSpriterCollisionActive, v8::Local<v8::Value>(), IsSpriterCollisionActive_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isSpriterCollisionActive").ToLocalChecked(), IsSpriterCollisionActive_Tpl);
        v8::Local<v8::Signature> GetSpriterCollisionBoxCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpriterCollisionBoxCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpriterCollisionBoxCount, v8::Local<v8::Value>(), GetSpriterCollisionBoxCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSpriterCollisionBoxCount").ToLocalChecked(), GetSpriterCollisionBoxCount_Tpl);
        v8::Local<v8::Signature> GetSpriterCollisionBoxName_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpriterCollisionBoxName_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpriterCollisionBoxName, v8::Local<v8::Value>(), GetSpriterCollisionBoxName_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSpriterCollisionBoxName").ToLocalChecked(), GetSpriterCollisionBoxName_Tpl);
#endif
        v8::Local<v8::Signature> ChangeFramesImage_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeFramesImage_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeFramesImage, v8::Local<v8::Value>(), ChangeFramesImage_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeFramesImage").ToLocalChecked(), ChangeFramesImage_Tpl);
        v8::Local<v8::Signature> OffsetFrameCenters_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OffsetFrameCenters_Tpl =
            v8::FunctionTemplate::New(isolate, OffsetFrameCenters, v8::Local<v8::Value>(), OffsetFrameCenters_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "offsetFrameCenters").ToLocalChecked(), OffsetFrameCenters_Tpl);
        v8::Local<v8::Signature> GetFrameCenterOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFrameCenterOffset_Tpl =
            v8::FunctionTemplate::New(isolate, GetFrameCenterOffset, v8::Local<v8::Value>(), GetFrameCenterOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFrameCenterOffset").ToLocalChecked(), GetFrameCenterOffset_Tpl);
        v8::Local<v8::Signature> GetOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, GetOpacity, v8::Local<v8::Value>(), GetOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Opacity").ToLocalChecked(), GetOpacity_Tpl);
        v8::Local<v8::Signature> SetOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, SetOpacity, v8::Local<v8::Value>(), SetOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Opacity").ToLocalChecked(), SetOpacity_Tpl);
        v8::Local<v8::Signature> FadeTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FadeTo_Tpl =
            v8::FunctionTemplate::New(isolate, FadeTo, v8::Local<v8::Value>(), FadeTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fadeTo").ToLocalChecked(), FadeTo_Tpl);
        v8::Local<v8::Signature> FadeIn_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FadeIn_Tpl =
            v8::FunctionTemplate::New(isolate, FadeIn, v8::Local<v8::Value>(), FadeIn_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fadeIn").ToLocalChecked(), FadeIn_Tpl);
        v8::Local<v8::Signature> FadeOut_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FadeOut_Tpl =
            v8::FunctionTemplate::New(isolate, FadeOut, v8::Local<v8::Value>(), FadeOut_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fadeOut").ToLocalChecked(), FadeOut_Tpl);
        v8::Local<v8::Signature> IsBehind_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsBehind_Tpl =
            v8::FunctionTemplate::New(isolate, IsBehind, v8::Local<v8::Value>(), IsBehind_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isBehind").ToLocalChecked(), IsBehind_Tpl);
        v8::Local<v8::Signature> GetZOrder_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetZOrder_Tpl =
            v8::FunctionTemplate::New(isolate, GetZOrder, v8::Local<v8::Value>(), GetZOrder_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getZOrder").ToLocalChecked(), GetZOrder_Tpl);
        v8::Local<v8::Signature> MoveBehind_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveBehind_Tpl =
            v8::FunctionTemplate::New(isolate, MoveBehind, v8::Local<v8::Value>(), MoveBehind_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveBehind").ToLocalChecked(), MoveBehind_Tpl);
        v8::Local<v8::Signature> MoveInFrontOf_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveInFrontOf_Tpl =
            v8::FunctionTemplate::New(isolate, MoveInFrontOf, v8::Local<v8::Value>(), MoveInFrontOf_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveInFrontOf").ToLocalChecked(), MoveInFrontOf_Tpl);
        v8::Local<v8::Signature> MoveToFront_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveToFront_Tpl =
            v8::FunctionTemplate::New(isolate, MoveToFront, v8::Local<v8::Value>(), MoveToFront_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveToFront").ToLocalChecked(), MoveToFront_Tpl);
        v8::Local<v8::Signature> MoveToBack_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveToBack_Tpl =
            v8::FunctionTemplate::New(isolate, MoveToBack, v8::Local<v8::Value>(), MoveToBack_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveToBack").ToLocalChecked(), MoveToBack_Tpl);
        v8::Local<v8::Signature> GetLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLayer_Tpl =
            v8::FunctionTemplate::New(isolate, GetLayer, v8::Local<v8::Value>(), GetLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLayer").ToLocalChecked(), GetLayer_Tpl);
#ifndef PDG_NO_GUI
        v8::Local<v8::Signature> SetDrawHelper_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetDrawHelper_Tpl =
            v8::FunctionTemplate::New(isolate, SetDrawHelper, v8::Local<v8::Value>(), SetDrawHelper_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setDrawHelper").ToLocalChecked(), SetDrawHelper_Tpl);
        v8::Local<v8::Signature> SetPostDrawHelper_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetPostDrawHelper_Tpl =
            v8::FunctionTemplate::New(isolate, SetPostDrawHelper, v8::Local<v8::Value>(), SetPostDrawHelper_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setPostDrawHelper").ToLocalChecked(), SetPostDrawHelper_Tpl);
        v8::Local<v8::Signature> GetWantsMouseOverEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsMouseOverEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsMouseOverEvents, v8::Local<v8::Value>(), GetWantsMouseOverEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WantsMouseOverEvents").ToLocalChecked(), GetWantsMouseOverEvents_Tpl);
        v8::Local<v8::Signature> SetWantsMouseOverEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsMouseOverEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsMouseOverEvents, v8::Local<v8::Value>(), SetWantsMouseOverEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WantsMouseOverEvents").ToLocalChecked(), SetWantsMouseOverEvents_Tpl);
        v8::Local<v8::Signature> GetWantsClickEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsClickEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsClickEvents, v8::Local<v8::Value>(), GetWantsClickEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WantsClickEvents").ToLocalChecked(), GetWantsClickEvents_Tpl);
        v8::Local<v8::Signature> SetWantsClickEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsClickEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsClickEvents, v8::Local<v8::Value>(), SetWantsClickEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WantsClickEvents").ToLocalChecked(), SetWantsClickEvents_Tpl);
        v8::Local<v8::Signature> GetMouseDetectMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMouseDetectMode_Tpl =
            v8::FunctionTemplate::New(isolate, GetMouseDetectMode, v8::Local<v8::Value>(), GetMouseDetectMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""MouseDetectMode").ToLocalChecked(), GetMouseDetectMode_Tpl);
        v8::Local<v8::Signature> SetMouseDetectMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMouseDetectMode_Tpl =
            v8::FunctionTemplate::New(isolate, SetMouseDetectMode, v8::Local<v8::Value>(), SetMouseDetectMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""MouseDetectMode").ToLocalChecked(), SetMouseDetectMode_Tpl);
        v8::Local<v8::Signature> GetWantsOffscreenEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsOffscreenEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsOffscreenEvents, v8::Local<v8::Value>(), GetWantsOffscreenEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WantsOffscreenEvents").ToLocalChecked(), GetWantsOffscreenEvents_Tpl);
        v8::Local<v8::Signature> SetWantsOffscreenEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsOffscreenEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsOffscreenEvents, v8::Local<v8::Value>(), SetWantsOffscreenEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WantsOffscreenEvents").ToLocalChecked(), SetWantsOffscreenEvents_Tpl);
#endif
        v8::Local<v8::Signature> On_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> On_Tpl =
            v8::FunctionTemplate::New(isolate, On, v8::Local<v8::Value>(), On_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "on").ToLocalChecked(), On_Tpl);
        v8::Local<v8::Signature> OnCollideSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnCollideSprite_Tpl =
            v8::FunctionTemplate::New(isolate, OnCollideSprite, v8::Local<v8::Value>(), OnCollideSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onCollideSprite").ToLocalChecked(), OnCollideSprite_Tpl);
        v8::Local<v8::Signature> OnCollideWall_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnCollideWall_Tpl =
            v8::FunctionTemplate::New(isolate, OnCollideWall, v8::Local<v8::Value>(), OnCollideWall_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onCollideWall").ToLocalChecked(), OnCollideWall_Tpl);
        v8::Local<v8::Signature> OnOffscreen_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnOffscreen_Tpl =
            v8::FunctionTemplate::New(isolate, OnOffscreen, v8::Local<v8::Value>(), OnOffscreen_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onOffscreen").ToLocalChecked(), OnOffscreen_Tpl);
        v8::Local<v8::Signature> OnOnscreen_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnOnscreen_Tpl =
            v8::FunctionTemplate::New(isolate, OnOnscreen, v8::Local<v8::Value>(), OnOnscreen_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onOnscreen").ToLocalChecked(), OnOnscreen_Tpl);
        v8::Local<v8::Signature> OnExitLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnExitLayer_Tpl =
            v8::FunctionTemplate::New(isolate, OnExitLayer, v8::Local<v8::Value>(), OnExitLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onExitLayer").ToLocalChecked(), OnExitLayer_Tpl);
        v8::Local<v8::Signature> OnAnimationLoop_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnAnimationLoop_Tpl =
            v8::FunctionTemplate::New(isolate, OnAnimationLoop, v8::Local<v8::Value>(), OnAnimationLoop_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onAnimationLoop").ToLocalChecked(), OnAnimationLoop_Tpl);
        v8::Local<v8::Signature> OnAnimationEnd_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnAnimationEnd_Tpl =
            v8::FunctionTemplate::New(isolate, OnAnimationEnd, v8::Local<v8::Value>(), OnAnimationEnd_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onAnimationEnd").ToLocalChecked(), OnAnimationEnd_Tpl);
        v8::Local<v8::Signature> OnAnimationPhysicsRecoveryComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnAnimationPhysicsRecoveryComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnAnimationPhysicsRecoveryComplete, v8::Local<v8::Value>(), OnAnimationPhysicsRecoveryComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onAnimationPhysicsRecoveryComplete").ToLocalChecked(), OnAnimationPhysicsRecoveryComplete_Tpl);
        v8::Local<v8::Signature> OnAnimationBlendComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnAnimationBlendComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnAnimationBlendComplete, v8::Local<v8::Value>(), OnAnimationBlendComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onAnimationBlendComplete").ToLocalChecked(), OnAnimationBlendComplete_Tpl);
        v8::Local<v8::Signature> OnFadeComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnFadeComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnFadeComplete, v8::Local<v8::Value>(), OnFadeComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onFadeComplete").ToLocalChecked(), OnFadeComplete_Tpl);
        v8::Local<v8::Signature> OnFadeInComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnFadeInComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnFadeInComplete, v8::Local<v8::Value>(), OnFadeInComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onFadeInComplete").ToLocalChecked(), OnFadeInComplete_Tpl);
        v8::Local<v8::Signature> OnFadeOutComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnFadeOutComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnFadeOutComplete, v8::Local<v8::Value>(), OnFadeOutComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onFadeOutComplete").ToLocalChecked(), OnFadeOutComplete_Tpl);
        v8::Local<v8::Signature> OnMouseEnter_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnMouseEnter_Tpl =
            v8::FunctionTemplate::New(isolate, OnMouseEnter, v8::Local<v8::Value>(), OnMouseEnter_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onMouseEnter").ToLocalChecked(), OnMouseEnter_Tpl);
        v8::Local<v8::Signature> OnMouseLeave_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnMouseLeave_Tpl =
            v8::FunctionTemplate::New(isolate, OnMouseLeave, v8::Local<v8::Value>(), OnMouseLeave_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onMouseLeave").ToLocalChecked(), OnMouseLeave_Tpl);
        v8::Local<v8::Signature> OnMouseDown_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnMouseDown_Tpl =
            v8::FunctionTemplate::New(isolate, OnMouseDown, v8::Local<v8::Value>(), OnMouseDown_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onMouseDown").ToLocalChecked(), OnMouseDown_Tpl);
        v8::Local<v8::Signature> OnMouseUp_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnMouseUp_Tpl =
            v8::FunctionTemplate::New(isolate, OnMouseUp, v8::Local<v8::Value>(), OnMouseUp_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onMouseUp").ToLocalChecked(), OnMouseUp_Tpl);
        v8::Local<v8::Signature> OnMouseClick_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnMouseClick_Tpl =
            v8::FunctionTemplate::New(isolate, OnMouseClick, v8::Local<v8::Value>(), OnMouseClick_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onMouseClick").ToLocalChecked(), OnMouseClick_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void SpriteWrap::AddHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            {
                args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object IEventHandler] inHandler, [number int] inEventType = all_events)" " - " "add a new handler for some event type, or for all events if no type specified. "
                    " \\param inHandler the object to handle events" " \\param inEventType the type of event to handle").ToLocalChecked() ); return;
            };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, inHandler, IEventHandler);
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 571 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 571 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
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
                    std::cout << __func__<<":"<< 571 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 571 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 571 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
            }
        } );
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""inType"")");
            return;
        }
        long inType = (args.Length()<2) ? pdg::all_events : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->addHandler(inHandler, inType);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::RemoveHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            {
                args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object IEventHandler] inHandler, [number int] inEventType = all_events)" " - " "remove a handler for some event type, or for all events (see note) if no type specified. "
                    "If the handler is listed multiple times it will only remove it once.\n"
                    "NOTE: inType == all_events doesn't work quite like you might expect. If "
                    "you have registered a handler for multiple events, but not with all_events, "
                    "doing removeHandler(handler, all_events) will do nothing. Basically, "
                    "all_events is a special event type that matches all event types when "
                    "considering whether to invoke a handler or not.\n"
                    "It is safe to call remove handler from within an event handler's handleEvent() call."
                    " \\param inHandler the object to handle events" " \\param inEventType the type of event to stop handling (see note)").ToLocalChecked() ); return;
            };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, inHandler, IEventHandler);
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""inType"")");
            return;
        }
        long inType = (args.Length()<2) ? pdg::all_events : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->removeHandler(inHandler, inType);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::Clear(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "remove all handlers").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->clear();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::BlockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            {
                args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] inEventType)" " - " "temporarily ignore all events of a particular type. "
                    "Events that are blocked are NOT cached for later, they are just dropped."
                    " \\param inEventType the type of event to block").ToLocalChecked() ); return;
            };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""inEventType"")");
            return;
        }
        long inEventType = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->blockEvent(inEventType);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::UnblockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            {
                args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] inEventType)" " - " "stop ignoring events of a particular type "
                    " \\param inEventType the type of event to unblock").ToLocalChecked() ); return;
            };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""inEventType"")");
            return;
        }
        long inEventType = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->unblockEvent(inEventType);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetBoundingBox(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Rect]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Rect theBoundingBox = self->getBoundingBox();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, theBoundingBox) ); return; };
    }

    void SpriteWrap::GetRotatedBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object RotatedRect]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::RotatedRect theRotatedBounds = self->getRotatedBounds();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, theRotatedBounds) ); return; };
    }

    void SpriteWrap::GetLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Point theLocation = self->getLocation();
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, theLocation) ); return; };
    }

    void SpriteWrap::GetMovement(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Offset theMovement = self->getMovement();
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, theMovement) ); return; };
    }

    void SpriteWrap::GetSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Offset theSize = self->getSize();
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, theSize) ); return; };
    }

    void SpriteWrap::GetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theWidth = self->getWidth();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theWidth) ); return; };
    }

    void SpriteWrap::GetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theHeight = self->getHeight();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theHeight) ); return; };
    }

    void SpriteWrap::GetScale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Offset theScale = self->getScale();
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, theScale) ); return; };
    }

    void SpriteWrap::GetStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Offset theStretching = self->getStretching();
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, theStretching) ); return; };
    }

    void SpriteWrap::GetRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theRotation = self->getRotation();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theRotation) ); return; };
    }

    void SpriteWrap::GetCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Offset theCenterOffset = self->getCenterOffset();
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, theCenterOffset) ); return; };
    }

    void SpriteWrap::GetSpin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theSpin = self->getSpin();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theSpin) ); return; };
    }

    void SpriteWrap::SetLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "({[object Point] value|number x, number y})" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Point value;
            auto isPoint = v8_ValueIsPoint(isolate, args[0], value);
            if (!isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*isPoint)
            {
                if (args.Length() != 1)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 1);
                    return;
                };
                self->setLocation(value); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                    return;
                }
                double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                    return;
                }
                double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() != 2)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 2);
                    return;
                };
                self->setLocation(x, y); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::MoveTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "({[object Point] value|number x, number y}, number durationSeconds = 0, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Point value;
            auto isPoint = v8_ValueIsPoint(isolate, args[0], value);
            if (!isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*isPoint)
            {
                if (args.Length() == 1)
                {
                    self->moveTo(value);
                    {
                        args.GetReturnValue().Set( args.This() ); return;
                    };
                }
                if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 3 && !args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                self->moveTo(value, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                    return;
                }
                double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                    return;
                }
                double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() == 2)
                {
                    self->moveTo(x, y);
                    {
                        args.GetReturnValue().Set( args.This() ); return;
                    };
                }
                if (!args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 4 && !args[4 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                self->moveTo(x, y, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::MoveBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "({[object Offset] value|number x, number y}, number durationSeconds = 0, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Offset value;
            auto converted = v8_ValueIsOffset(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (args.Length() == 1)
                {
                    self->moveBy(value);
                    {
                        args.GetReturnValue().Set( args.This() ); return;
                    };
                }
                if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 3 && !args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                self->moveBy(value, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                    return;
                }
                double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                    return;
                }
                double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() == 2)
                {
                    self->moveBy(x, y);
                    {
                        args.GetReturnValue().Set( args.This() ); return;
                    };
                }
                if (!args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 4 && !args[4 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                self->moveBy(x, y, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetMovement(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "({[object Vector] value|number xPerSecond, number yPerSecond})" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Vector value;
            auto converted = v8_ValueIsVector(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (args.Length() != 1)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 1);
                    return;
                };
                self->setMovement(value); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""xPerSecond"")");
                    return;
                }
                double xPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""yPerSecond"")");
                    return;
                }
                double yPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() != 2)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 2);
                    return;
                };
                self->setMovement(xPerSecond, yPerSecond); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ChangeMovementTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "({[object Vector] value|number xPerSecond, number yPerSecond}, number durationSeconds, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Vector value;
            auto converted = v8_ValueIsVector(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 3 && !args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                self->changeMovementTo(value, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""xPerSecond"")");
                    return;
                }
                double xPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""yPerSecond"")");
                    return;
                }
                double yPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (!args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 4 && !args[4 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::linearTween) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                self->changeMovementTo(xPerSecond, yPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ChangeMovementBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "({[object Vector] value|number xPerSecond, number yPerSecond}, number durationSeconds, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Vector value;
            auto converted = v8_ValueIsVector(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 3 && !args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                self->changeMovementBy(value, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""xPerSecond"")");
                    return;
                }
                double xPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""yPerSecond"")");
                    return;
                }
                double yPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (!args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 4 && !args[4 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::linearTween) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                self->changeMovementBy(xPerSecond, yPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "({[object Offset] value|number width, number height})" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Offset value;
            auto converted = v8_ValueIsOffset(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (args.Length() != 1)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 1);
                    return;
                };
                self->setSize(value); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""width"")");
                    return;
                }
                double width = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""height"")");
                    return;
                }
                double height = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() != 2)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 2);
                    return;
                };
                self->setSize(width, height); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ChangeCenterOffsetTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "({[object Offset] value|number x, number y}, number durationSeconds, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Offset value;
            auto converted = v8_ValueIsOffset(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 3 && !args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                self->changeCenterOffsetTo(value, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                    return;
                }
                double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                    return;
                }
                double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (!args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 4 && !args[4 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                self->changeCenterOffsetTo(x, y, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ChangeCenterOffsetBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "({[object Offset] value|number x, number y}, number durationSeconds, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Offset value;
            auto converted = v8_ValueIsOffset(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 3 && !args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                self->changeCenterOffsetBy(value, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                    return;
                }
                double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                    return;
                }
                double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (!args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 4 && !args[4 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
                    isolate->ThrowException( v8::Exception::RangeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }
                    ())));
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                self->changeCenterOffsetBy(x, y, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number value)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            self->setWidth(value); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number value)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            self->setHeight(value); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number value)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            self->setRotation(value); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetSpin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number value)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            self->setSpin(value); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetGrowing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number value)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            self->setGrowing(value); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number widthPerSecond, number heightPerSecond)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""widthPerSecond"")");
                return;
            }
            double widthPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""heightPerSecond"")");
                return;
            }
            double heightPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2);
                return;
            };
            self->setStretching(widthPerSecond, heightPerSecond); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetScale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number x, number y = x)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                return;
            }
            double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (args.Length() >= 2 && !args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                return;
            }
            double y = (args.Length()<2) ? x : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            self->setScale(x, y); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ChangeSpinTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number radiansPerSecond, number durationSeconds, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""radiansPerSecond"")");
                return;
            }
            double radiansPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->changeSpinTo(radiansPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ChangeSpinBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number radiansPerSecond, number durationSeconds, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""radiansPerSecond"")");
                return;
            }
            double radiansPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->changeSpinBy(radiansPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ChangeGrowingTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number amountPerSecond, number durationSeconds, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""amountPerSecond"")");
                return;
            }
            double amountPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->changeGrowingTo(amountPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ChangeGrowingBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number amountPerSecond, number durationSeconds, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""amountPerSecond"")");
                return;
            }
            double amountPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->changeGrowingBy(amountPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ChangeStretchingTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number widthPerSecond, number heightPerSecond, number durationSeconds, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""widthPerSecond"")");
                return;
            }
            double widthPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""heightPerSecond"")");
                return;
            }
            double heightPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::linearTween) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->changeStretchingTo(widthPerSecond, heightPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ChangeStretchingBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number widthPerSecond, number heightPerSecond, number durationSeconds, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""widthPerSecond"")");
                return;
            }
            double widthPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""heightPerSecond"")");
                return;
            }
            double heightPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::linearTween) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->changeStretchingBy(widthPerSecond, heightPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ChangeScaleTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number x, number y, number durationSeconds, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                return;
            }
            double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                return;
            }
            double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->changeScaleTo(x, y, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ChangeScaleBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number x, number y, number durationSeconds, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                return;
            }
            double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                return;
            }
            double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->changeScaleBy(x, y, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::Grow(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number factor, number durationSeconds = 0, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""factor"")");
                return;
            }
            double factor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() == 1)
            {
                self->grow(factor);
                {
                    args.GetReturnValue().Set( args.This() ); return;
                };
            }
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->grow(factor, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::Stretch(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number widthFactor, number heightFactor, number durationSeconds = 0, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""widthFactor"")");
                return;
            }
            double widthFactor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""heightFactor"")");
                return;
            }
            double heightFactor = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() == 2)
            {
                self->stretch(widthFactor, heightFactor);
                {
                    args.GetReturnValue().Set( args.This() ); return;
                };
            }
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->stretch(widthFactor, heightFactor, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ResizeBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number deltaWidth, number deltaHeight, number durationSeconds = 0, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""deltaWidth"")");
                return;
            }
            double deltaWidth = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""deltaHeight"")");
                return;
            }
            double deltaHeight = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() == 2)
            {
                self->resizeBy(deltaWidth, deltaHeight);
                {
                    args.GetReturnValue().Set( args.This() ); return;
                };
            }
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->resizeBy(deltaWidth, deltaHeight, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ResizeTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number width, number height, number durationSeconds, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
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
            double width = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""height"")");
                return;
            }
            double height = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->resizeTo(width, height, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::RotateBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number radians, number durationSeconds = 0, [number int] easing = easeInOutQuad, [number int] direction = rotationDirection_AsSpecified)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""radians"")");
                return;
            }
            double radians = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() == 1)
            {
                self->rotateBy(radians);
                {
                    args.GetReturnValue().Set( args.This() ); return;
                };
            }
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""directionValue"")");
                return;
            }
            double directionValue = (args.Length()<4) ? static_cast<int>(rotationDirection_AsSpecified) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue || directionValue < 0 || directionValue > 3)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer rotation direction";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int direction = static_cast<int>(directionValue);
            self->rotateBy(radians, durationSeconds, gEasingFunctions[easing], direction); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::RotateTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number radians, number durationSeconds = 0, [number int] easing = easeInOutQuad, [number int] direction = rotationDirection_AsSpecified)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""radians"")");
                return;
            }
            double radians = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() == 1)
            {
                self->rotateTo(radians);
                {
                    args.GetReturnValue().Set( args.This() ); return;
                };
            }
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""directionValue"")");
                return;
            }
            double directionValue = (args.Length()<4) ? static_cast<int>(rotationDirection_AsSpecified) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue || directionValue < 0 || directionValue > 3)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer rotation direction";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int direction = static_cast<int>(directionValue);
            self->rotateTo(radians, durationSeconds, gEasingFunctions[easing], direction); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "([object Offset] offset)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            }; pdg::Offset offset;
            auto offset_isOffset = v8_ValueIsOffset(isolate, args[1 -1], offset);
            if (!offset_isOffset.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*offset_isOffset)
            {
                v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
                return;
            };
            self->setCenterOffset(offset); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetFlipX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(boolean flip)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 1, "a boolean (""flip"")");
                return;
            }
            bool flip = args[1 -1]->BooleanValue(isolate);
            self->setFlipX(flip); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetFlipY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(boolean flip)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 1, "a boolean (""flip"")");
                return;
            }
            bool flip = args[1 -1]->BooleanValue(isolate);
            self->setFlipY(flip); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::StopMovement(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->stopMovement(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::StopSpinning(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->stopSpinning(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::StopGrowing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->stopGrowing(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::StopStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->stopStretching(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::PauseSchedule(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->pauseSchedule(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ResumeSchedule(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->resumeSchedule(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::CancelSchedule(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->cancelSchedule(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::FlipX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->flipX(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::FlipY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->flipY(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::AndThen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->andThen(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::IsFlippedX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isFlippedX()) ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::IsFlippedY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isFlippedY()) ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::IsSchedulePaused(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isSchedulePaused()) ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::HasScheduledAnimations(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->hasScheduledAnimations()) ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::Wait(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number durationSeconds)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            self->wait(durationSeconds); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::AddAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "([object IAnimationHelper] helper)" " - " "").ToLocalChecked() ); return; };
            };
            self->mAnimatedScriptObj.Reset(isolate, args.This()); self->mAnimatedScriptObj.SetWeak();
            SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
            {
                std::cerr << __func__<<":"<< 572 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
            }
            else if (!args[0]->IsObject())
            {
                std::cerr << __func__<<":"<< 572 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
            }
            else
            {
                v8::Local<v8::Object> obj_ = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
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
                        std::cout << __func__<<":"<< 572 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IAnimationHelper""\n";
                    }
                    else
                    {
                        std::cout << __func__<<":"<< 572 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IAnimationHelper""\n";
                    }
                }
                else
                {
                    IAnimationHelper* obj = dynamic_cast<IAnimationHelper*>(obj__->getCppObject());
                        std::cout << __func__<<":"<< 572 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IAnimationHelper"" ("<<(void*)obj<<")\n";
                }
            } );
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, helper, IAnimationHelper);
            self->addAnimationHelper(helper);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::RemoveAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "([object IAnimationHelper] helper)" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_ARG(1, helper, IAnimationHelper);
            self->removeAnimationHelper(helper);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ClearAnimationHelpers(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        try
        {
            if (args.Length() == 1 && args[0]->IsNull())
            {
                { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "").ToLocalChecked() ); return; };
            };
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->clearAnimationHelpers();
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::GetMyClassTag(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        uint32 theMyClassTag = self->getMyClassTag();
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, theMyClassTag) ); return; };
    }

    void SpriteWrap::GetSerializedSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR [number uint]" " function" "([object Serializer] serializer)" " - " "get size of this object's data for the given stream").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, serializer, Serializer);
        try
        {
            uint32 dataSize = self->getSerializedSize(serializer);
            { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, dataSize) ); return; };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::Serialize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR undefined" " function" "([object Serializer] serializer)" " - " "write this object's data into the given stream").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, serializer, Serializer);
        try { self->serialize(serializer); args.GetReturnValue().SetUndefined(); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::Deserialize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR undefined" " function" "([object Deserializer] deserializer)" " - " "read this object's data from the given stream").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, deserializer, Deserializer);
        try
        {
            self->deserialize(deserializer);
            args.GetReturnValue().SetUndefined();
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        catch(bad_tag& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        catch(sync_error& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        catch(unknown_object& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::GetWantsAnimLoopEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        bool theWantsAnimLoopEvents = self->getWantsAnimLoopEvents();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theWantsAnimLoopEvents) ); return; };
    }

    void SpriteWrap::GetWantsAnimEndEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        bool theWantsAnimEndEvents = self->getWantsAnimEndEvents();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theWantsAnimEndEvents) ); return; };
    }

    void SpriteWrap::GetWantsCollideWallEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        bool theWantsCollideWallEvents = self->getWantsCollideWallEvents();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theWantsCollideWallEvents) ); return; };
    }
#ifndef PDG_NO_GUI

    void SpriteWrap::GetWantsMouseOverEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        bool theWantsMouseOverEvents = self->getWantsMouseOverEvents();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theWantsMouseOverEvents) ); return; };
    }

    void SpriteWrap::GetWantsClickEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        bool theWantsClickEvents = self->getWantsClickEvents();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theWantsClickEvents) ); return; };
    }

    void SpriteWrap::GetMouseDetectMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        int theMouseDetectMode = self->getMouseDetectMode();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, theMouseDetectMode) ); return; };
    }

    void SpriteWrap::GetWantsOffscreenEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        bool theWantsOffscreenEvents = self->getWantsOffscreenEvents();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theWantsOffscreenEvents) ); return; };
    }
#endif

    void SpriteWrap::GetFrameRotatedBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object RotatedRect]" " function" "([number int] frameNum = -1)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""frameNum"")");
            return;
        }
        long frameNum = (args.Length()<1) ? -1 : args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        pdg::RotatedRect r = self->getFrameRotatedBounds(frameNum);
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, r) ); return; };
    }

    void SpriteWrap::SetFrame(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([number int] frame)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""frame"")");
            return;
        }
        long frame = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->setFrame(frame);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::GetCurrentFrame(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "which frame of animation the sprite is currently showing").ToLocalChecked() ); return; };
        };

        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        int frame = self->getCurrentFrame();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, frame) ); return; };
    }

    void SpriteWrap::GetFrameCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "total number of frames of animation for this sprite").ToLocalChecked() ); return; };
        };

        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        int count = self->getFrameCount();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, count) ); return; };
    }

    void SpriteWrap::StartFrameAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number fps, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames, [number int] animateFlags = animate_Looping)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""fps"")");
            return;
        }
        double fps = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""startingFrame"")");
            return;
        }
        long startingFrame = (args.Length()<2) ? Sprite::start_FromFirstFrame : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""numFrames"")");
            return;
        }
        long numFrames = (args.Length()<3) ? Sprite::all_Frames : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""animateFlags"")");
            return;
        }
        long animateFlags = (args.Length()<4) ? Sprite::animate_Looping : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->startFrameAnimation(fps, startingFrame, numFrames, animateFlags);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::StopFrameAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->stopFrameAnimation();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::SetWantsAnimLoopEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean wantsThem = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wantsThem"")");
            return;
        }
        bool wantsThem = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setWantsAnimLoopEvents(wantsThem);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::SetWantsAnimEndEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean wantsThem = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wantsThem"")");
            return;
        }
        bool wantsThem = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setWantsAnimEndEvents(wantsThem);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::SetWantsCollideWallEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean wantsThem = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wantsThem"")");
            return;
        }
        bool wantsThem = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setWantsCollideWallEvents(wantsThem);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::AddFramesImage(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Image] image, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, image, Image);
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""startingFrame"")");
            return;
        }
        long startingFrame = (args.Length()<2) ? Sprite::start_FromFirstFrame : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""numFrames"")");
            return;
        }
        long numFrames = (args.Length()<3) ? Sprite::all_Frames : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->addFramesImage(image, startingFrame, numFrames);
        args.GetReturnValue().SetUndefined();
    }
#ifdef PDG_SPRITER_SUPPORT

    void SpriteWrap::HasAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "({ [number int] animationId | string animationName })" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        bool hasIt = false;
        if (args[0]->IsString())
        {
            if (!args[1 -1]->IsString())
            {
                v8_ThrowArgTypeException(isolate, 1, "a string  (""animationName"")");
                return;
            }
            v8::String::Utf8Value animationName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* animationName = *animationName_Str;;
            hasIt = self->hasAnimation(animationName);
        }
        else
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""animationId"")");
                return;
            }
            double animationId = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            hasIt = std::isfinite(animationId) && animationId >= 0 && animationId <= 4294967295.0
                && animationId == std::floor(animationId) && self->hasAnimation(static_cast<uint32>(animationId));
        }
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, hasIt) ); return; };
    }

    void SpriteWrap::StartAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "({ [number int] animationId | string animationName })" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (args[0]->IsString())
        {
            if (!args[1 -1]->IsString())
            {
                v8_ThrowArgTypeException(isolate, 1, "a string  (""animationName"")");
                return;
            }
            v8::String::Utf8Value animationName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* animationName = *animationName_Str;;
            self->startAnimation(animationName);
        }
        else
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""animationId"")");
                return;
            }
            unsigned long animationId = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
            self->startAnimation(animationId);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::ApplyCharacterMap(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string mapName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""mapName"")");
            return;
        }
        v8::String::Utf8Value mapName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* mapName = *mapName_Str;;
        self->applyCharacterMap(mapName);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::RemoveCharacterMap(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string mapName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""mapName"")");
            return;
        }
        v8::String::Utf8Value mapName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* mapName = *mapName_Str;;
        self->removeCharacterMap(mapName);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::RemoveAllCharacterMaps(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->removeAllCharacterMaps();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetAppliedCharacterMaps(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Array]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        std::vector<std::string> maps = self->getAppliedCharacterMaps();

#ifdef PDG_USING_JAVASCRIPT_CORE
        JSObjectRef arr = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t i = 0; i < maps.size(); i++)
        {
            JSObjectSetPropertyAtIndex(ctx, arr, (unsigned)i, v8::String::NewFromUtf8(isolate, maps[i].c_str()).ToLocalChecked(), exception);
        }
#else
        v8::Local<v8::Array> arr = v8::Array::New(isolate);
        for (size_t i = 0; i < maps.size(); i++)
        {
            arr->Set(isolate->GetCurrentContext(), v8::Integer::New(isolate, i),
                v8::String::NewFromUtf8(isolate, maps[i].c_str()).ToLocalChecked()).ToChecked();
        }
#endif
        { args.GetReturnValue().Set( arr ); return; };
    }

    void SpriteWrap::EnableSpriterEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(boolean enable = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""enable"")");
            return;
        }
        bool enable = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->enableSpriterEvents(enable);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::AreSpriterEventsEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool enabled = self->areSpriterEventsEnabled();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, enabled) ); return; };
    }

    void SpriteWrap::BlendToAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "({ [number int] animationId | string animationName }, number blendTime)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""blendTime"")");
            return;
        }
        double blendTime = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args[0]->IsString())
        {
            if (!args[1 -1]->IsString())
            {
                v8_ThrowArgTypeException(isolate, 1, "a string  (""animationName"")");
                return;
            }
            v8::String::Utf8Value animationName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* animationName = *animationName_Str;;
            self->blendToAnimation(animationName, blendTime);
        }
        else
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""animationId"")");
                return;
            }
            unsigned long animationId = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
            self->blendToAnimation(animationId, blendTime);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::IsBlending(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool blending = self->isBlending();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, blending) ); return; };
    }

    void SpriteWrap::GetBlendProgress(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float progress = self->getBlendProgress();
        { args.GetReturnValue().Set( v8::Number::New(isolate, progress) ); return; };
    }

    void SpriteWrap::PauseAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->pauseAnimation();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::ResumeAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->resumeAnimation();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::StopAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->stopAnimation();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::IsAnimationPlaying(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool playing = self->isAnimationPlaying();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, playing) ); return; };
    }

    void SpriteWrap::IsAnimationPaused(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool paused = self->isAnimationPaused();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, paused) ); return; };
    }

    void SpriteWrap::GetAnimationProgress(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float progress = self->getAnimationProgress();
        { args.GetReturnValue().Set( v8::Number::New(isolate, progress) ); return; };
    }

    void SpriteWrap::HasAttachPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "(string attachPointName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""attachPointName"")");
            return;
        }
        v8::String::Utf8Value attachPointName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* attachPointName = *attachPointName_Str;;
        bool hasPoint = self->hasAttachPoint(attachPointName);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, hasPoint) ); return; };
    }

    void SpriteWrap::GetAttachPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "(string attachPointName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""attachPointName"")");
            return;
        }
        v8::String::Utf8Value attachPointName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* attachPointName = *attachPointName_Str;;
        pdg::Offset offset = self->getAttachPoint(attachPointName);
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, offset) ); return; };
    }

    void SpriteWrap::AttachSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Sprite] sprite, string attachPointName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
        if (!args[2 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 2, "a string  (""attachPointName"")");
            return;
        }
        v8::String::Utf8Value attachPointName_Str(isolate, args[2 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* attachPointName = *attachPointName_Str;;
        self->attachSprite(sprite, attachPointName);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::DetachSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Sprite] sprite)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
        self->detachSprite(sprite);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetAttachedSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(string attachPointName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""attachPointName"")");
            return;
        }
        v8::String::Utf8Value attachPointName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* attachPointName = *attachPointName_Str;;
        pdg::Sprite* attached = self->getAttachedSprite(attachPointName);
        if (attached)
        {
            if (!attached) { args.GetReturnValue().SetNull(); return; };
            { args.GetReturnValue().Set( SpriteWrap::NewFromCpp(isolate, attached) ); return; };
            ;
        }
        else
        {
            { args.GetReturnValue().SetNull(); return; };
        }
    }

    void SpriteWrap::ActivateSubEntity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string entityName, string animationName = \"idle\")" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""entityName"")");
            return;
        }
        v8::String::Utf8Value entityName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* entityName = *entityName_Str;;
        if (args.Length() >= 2 && !args[2 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 2, "a string  (""animationName"")");
            return;
        }
        v8::String::Utf8Value _animationName_String( isolate, (args.Length()<2) ? v8::String::NewFromUtf8(isolate, "").ToLocalChecked() : args[2 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked() );
        const char* animationName = (args.Length()<2) ? "idle" : *_animationName_String;;
        self->activateSubEntity(entityName, animationName);
        args.GetReturnValue().SetUndefined();
    }
#endif
#ifndef PDG_NO_GUI

    void SpriteWrap::SetWantsOffscreenEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean wantsThem = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wantsThem"")");
            return;
        }
        bool wantsThem = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setWantsOffscreenEvents(wantsThem);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::SetDrawHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object ISpriteDrawHelper] helper)" " - " "").ToLocalChecked() ); return; };
        };
        self->mSpriteScriptObj.Reset(isolate, args.This());
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_OR_NULL_ARG(1, helper, ISpriteDrawHelper);
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 874 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 874 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
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
                    std::cout << __func__<<":"<< 874 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""ISpriteDrawHelper""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 874 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""ISpriteDrawHelper""\n";
                }
            }
            else
            {
                ISpriteDrawHelper* obj = dynamic_cast<ISpriteDrawHelper*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 874 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""ISpriteDrawHelper"" ("<<(void*)obj<<")\n";
            }
        } )
            self->setDrawHelper(helper);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::SetPostDrawHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object ISpriteDrawHelper] helper)" " - " "").ToLocalChecked() ); return; };
        };
        self->mSpriteScriptObj.Reset(isolate, args.This());
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_OR_NULL_ARG(1, helper, ISpriteDrawHelper);
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 883 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 883 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
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
                    std::cout << __func__<<":"<< 883 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""ISpriteDrawHelper""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 883 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""ISpriteDrawHelper""\n";
                }
            }
            else
            {
                ISpriteDrawHelper* obj = dynamic_cast<ISpriteDrawHelper*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 883 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""ISpriteDrawHelper"" ("<<(void*)obj<<")\n";
            }
        } )
            self->setPostDrawHelper(helper);
        args.GetReturnValue().SetUndefined();
    }
#endif

    void SpriteWrap::ChangeFramesImage(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Image] oldImage, [object Image] newImage)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, oldImage, Image);
        REQUIRE_CPP_OBJECT_ARG(2, newImage, Image);
        self->changeFramesImage(oldImage, newImage);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::OffsetFrameCenters(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] offsetX, [number int] offsetY, [object Image] image = null, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""offsetX"")");
            return;
        }
        long offsetX = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""offsetY"")");
            return;
        }
        long offsetY = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        Image* image = 0;
        if (args.Length() >= 3)
        {
            if (!args[3 -1]->IsObject())
            {
                v8_ThrowArgTypeException(isolate, 3, "an object of type ""Image"" (""image"")");
                return;
            }
            else
            {
                v8::Local<v8::Object> image_ = args[3 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                ImageWrap* image__ = jswrap::ObjectWrap::Unwrap<ImageWrap>(image_);
                image = image__->getCppObject();
            }
        };
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""startingFrame"")");
            return;
        }
        long startingFrame = (args.Length()<4) ? Sprite::start_FromFirstFrame : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 5 && !args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""numFrames"")");
            return;
        }
        long numFrames = (args.Length()<5) ? Sprite::all_Frames : args[5 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->offsetFrameCenters(offsetX, offsetY, image, startingFrame, numFrames);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetFrameCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "([object Image] image = null, [number int] frameNum = 0)" " - " "").ToLocalChecked() ); return; };
        };
        Image* image = 0;
        if (args.Length() >= 1)
        {
            if (!args[1 -1]->IsObject())
            {
                v8_ThrowArgTypeException(isolate, 1, "an object of type ""Image"" (""image"")");
                return;
            }
            else
            {
                v8::Local<v8::Object> image_ = args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                ImageWrap* image__ = jswrap::ObjectWrap::Unwrap<ImageWrap>(image_);
                image = image__->getCppObject();
            }
        };
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""frameNum"")");
            return;
        }
        long frameNum = (args.Length()<2) ? 0 : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        pdg::Offset offset = self->getFrameCenterOffset(image, frameNum);
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, offset) ); return; };
    }

    void SpriteWrap::SetOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number opacity)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""opacity"")");
            return;
        }
        double opacity = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->setOpacity(opacity);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::GetOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float opacity = self->getOpacity();
        { args.GetReturnValue().Set( v8::Number::New(isolate, opacity) ); return; };
    }

    void SpriteWrap::FadeTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number targetOpacity, number durationSeconds, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""targetOpacity"")");
            return;
        }
        double targetOpacity = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
            return;
        }
        double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<3) ? EasingFuncRef::linearTween : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeTo(targetOpacity, durationSeconds, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeTo(targetOpacity, durationSeconds);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::FadeIn(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number durationSeconds, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""durationSeconds"")");
            return;
        }
        double durationSeconds = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<2) ? EasingFuncRef::linearTween : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeIn(durationSeconds, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeIn(durationSeconds);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::FadeOut(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number durationSeconds, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""durationSeconds"")");
            return;
        }
        double durationSeconds = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<2) ? EasingFuncRef::linearTween : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeOut(durationSeconds, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeOut(durationSeconds);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::IsBehind(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "([object Sprite] sprite)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
        bool behind = self->isBehind(sprite);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, behind) ); return; };
    }

    void SpriteWrap::GetZOrder(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number int]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        int zorder = self->getZOrder();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, zorder) ); return; };
    }

    void SpriteWrap::MoveBehind(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([object Sprite] sprite)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
        self->moveBehind(sprite);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::MoveInFrontOf(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([object Sprite] sprite)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
        self->moveInFrontOf(sprite);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::MoveToFront(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "()" " - " "put this sprite in front of all others in its layer").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->moveToFront();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::MoveToBack(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "()" " - " "put this sprite behind all others in its layer").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->moveToBack();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::SetupFrameCollider(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Collider]" " function" "([number int] mode = frameCollider_AlphaMask, [number int] alphaThreshold = 128)" " - " "Follow current frame collision geometry").ToLocalChecked() ); return; };
        };
        try
        {
            if (args.Length() >= 1 && !args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""modeValue"")");
                return;
            }
            double modeValue = (args.Length()<1) ? static_cast<double>(frameCollider_AlphaMask) : args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (args.Length() >= 2 && !args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""threshold"")");
                return;
            }
            double threshold = (args.Length()<2) ? 128 : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if(!std::isfinite(modeValue) || modeValue<0 || modeValue>std::numeric_limits<int>::max() || std::floor(modeValue)!=modeValue)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer frameCollider mode";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const int mode=static_cast<int>(modeValue);
            if((mode!=frameCollider_Bounds && mode!=frameCollider_AlphaMask) || !std::isfinite(threshold) || threshold<1 || threshold>255 || std::floor(threshold)!=threshold)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected a frameCollider mode and an integer alpha threshold from 1 to 255";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            auto* result=&self->setupFrameCollider(mode,threshold); if (!result) { args.GetReturnValue().SetNull(); return; };
            if (result->mColliderScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( ColliderWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mColliderScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetupAnimationCollider(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Collider]" " function" "()" " - " "Follow authored animation collision boxes").ToLocalChecked() ); return; };
        };
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* result=&self->setupAnimationCollider(); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mColliderScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( ColliderWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mColliderScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetFrameCollisionMask(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([object Image] frameImage, [object Image] maskImage)" " - " "Assign a mask to frames using an image").ToLocalChecked() ); return; };
        };
        try
        {
            if (args.Length() != 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2);
                return;
            };
            REQUIRE_CPP_OBJECT_ARG(1,image,Image); Image* mask=nullptr; if(!args[1]->IsNull())
            {
                REQUIRE_CPP_OBJECT_ARG(2,value,Image); mask=value;
            }
            self->setFrameCollisionMask(image,mask); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }
#ifndef PDG_NO_GUI

    void SpriteWrap::SetWantsMouseOverEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean wantsThem = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wantsThem"")");
            return;
        }
        bool wantsThem = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setWantsMouseOverEvents(wantsThem);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::SetWantsClickEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean wantsThem = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wantsThem"")");
            return;
        }
        bool wantsThem = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setWantsClickEvents(wantsThem);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::SetMouseDetectMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([number int] collisionType = collide_BoundingBox)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""collisionType"")");
            return;
        }
        long collisionType = (args.Length()<1) ? Sprite::collide_BoundingBox : args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->setMouseDetectMode(collisionType);
        { args.GetReturnValue().Set( args.This() ); return; };
    }
#endif

    void SpriteWrap::GetLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object SpriteLayer]" " function" "()" " - " "get the layer that contains this sprite").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        SpriteLayer* layer = self->getLayer();
        if (!layer) { args.GetReturnValue().SetNull(); return; };
        if (layer->mSpriteLayerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( SpriteLayerWrap::NewFromCpp(isolate, layer) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, layer->mSpriteLayerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::On(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "([number int] eventCode, function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""eventCode"")");
            return;
        }
        long eventCode = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 2, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[2 -1]);;
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
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
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnCollideSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler)
        {
            DEBUG_ONLY( OS::_DOUT("OnCollideSprite: failed to create handler"); )
                { args.GetReturnValue().SetNull(); return; };
        }
        self->addHandler(handler, pdg::eventType_SpriteCollide);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnCollideWall(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteCollide);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnOffscreen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Offscreen);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnOnscreen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Onscreen);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnExitLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_ExitLayer);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnAnimationLoop(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnAnimationEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationEnd);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnAnimationBlendComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationBlendComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnAnimationPhysicsRecoveryComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationPhysicsRecoveryComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnFadeComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnFadeInComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeInComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnFadeOutComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeOutComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnMouseEnter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseEnter);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnMouseLeave(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseLeave);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnMouseDown(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseDown);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnMouseUp(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseUp);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnMouseClick(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseClick);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

#ifdef PDG_SPRITER_SUPPORT

    void SpriteWrap::GetSpriterCollisionBox(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object RotatedRect]" " function" "(string boxName)" " - " "get a Spriter collision box by name").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""boxName"")");
            return;
        }
        v8::String::Utf8Value boxName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* boxName = *boxName_Str;;
        pdg::RotatedRect rect = self->getSpriterCollisionBox(boxName);
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, rect) ); return; };
    }

    void SpriteWrap::IsSpriterCollisionActive(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "(string boxName)" " - " "check if a Spriter collision box is active").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""boxName"")");
            return;
        }
        v8::String::Utf8Value boxName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* boxName = *boxName_Str;;
        bool active = self->isSpriterCollisionActive(boxName);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, active) ); return; };
    }

    void SpriteWrap::GetSpriterCollisionBoxCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "get the number of active Spriter collision boxes").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        int count = self->getSpriterCollisionBoxCount();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, count) ); return; };
    }

    void SpriteWrap::GetSpriterCollisionBoxName(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "(number index)" " - " "get the name of a Spriter collision box by index").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""index"")");
            return;
        }
        long index = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        const char* name = self->getSpriterCollisionBoxName(index);
        if (name)
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, name).ToLocalChecked() ); return; };
        }
        else
        {
            { args.GetReturnValue().SetNull(); return; };
        }
    }
#endif

#ifdef PDG_SPRITER_SUPPORT

    void SpriteWrap::DisableAnimationPose(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->disableAnimationPose();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::ClearAnimationBoneTransforms(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->clearAnimationBoneTransforms();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::SeekAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string clip, number timeSeconds)" " - " "select an independent clip time in floating-point seconds").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""clip"")");
            return;
        }
        v8::String::Utf8Value clip_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* clip = *clip_Str;; if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""timeSeconds"")");
            return;
        }
        double timeSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        try {self->seekAnimation(clip,timeSeconds);}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::TransitionToAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string clip, number timeSeconds, number durationSeconds)" " - " "select an independent clip time in floating-point seconds").ToLocalChecked() ); return; };
        };
        if (args.Length() != 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""clip"")");
            return;
        }
        v8::String::Utf8Value clip_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* clip = *clip_Str;; if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""timeSeconds"")");
            return;
        }
        double timeSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
            return;
        }
        double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        try {self->transitionToAnimation(clip,timeSeconds,durationSeconds);}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::IsAnimationTransitioning(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "test independently timed crossfade state").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        {
            args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isAnimationTransitioning()) ); return;
        };
    }

    void SpriteWrap::GetAnimationTransitionProgress(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "read normalized independently timed crossfade progress").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        {
            args.GetReturnValue().Set( v8::Number::New(isolate, self->getAnimationTransitionProgress()) ); return;
        };
    }

    void SpriteWrap::SupportsAnimationPhysics(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "test physical animation capability").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        {
            args.GetReturnValue().Set( v8::Boolean::New(isolate, self->supportsAnimationPhysics()) ); return;
        };
    }

    void SpriteWrap::IsAnimationPhysicsEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "test physical animation state").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        {
            args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isAnimationPhysicsEnabled()) ); return;
        };
    }

    void SpriteWrap::SetupAnimationPhysics(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(object definition)" " - " "create a versioned physical rig").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        try{self->setupAnimationPhysics(decodeAnimationPhysicsDefinition(animationPhysicsValues(PDG_POSE_SCRIPT_ARGUMENTS,args[0])));}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::SetupPhysicsFromAnimationRig(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number totalMass, number unitsPerMeter = 1)" " - " "generate a dynamic rig from the reference skeleton").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""mass"")");
            return;
        }
        double mass = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""units"")");
            return;
        }
        double units = (args.Length()<2) ? 1 : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        try { self->setupPhysicsFromAnimationRig(mass,units); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::AttachAnimationPhysicsPart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([object Part] part, [object Part] parent = null)" " - " "register a physical Part in the generated rig assembly").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };REQUIRE_CPP_OBJECT_ARG(1,part,Part);
        Part* parent=nullptr;
        if(args.Length()>1 && !args[1]->IsNull()) { REQUIRE_CPP_OBJECT_ARG(2,value,Part);parent=value; }
        try { self->attachAnimationPhysicsPart(part,parent); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::DetachAnimationPhysicsPart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([object Part] part, boolean includeDescendants = true)" " - " "release rig membership and disconnect boundary joints").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1,part,Part);if (args.Length() >= 2 && !args[2 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 2, "a boolean (""descendants"")");
            return;
        }
        bool descendants = (args.Length()<2) ? true : args[2 -1]->BooleanValue(isolate);;
        try { self->detachAnimationPhysicsPart(part,descendants); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::IsAnimationPhysicsPartAttached(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "([object Part] part)" " - " "test whether a Part contributes to this generated rig assembly").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1,part,Part);
        {
            args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isAnimationPhysicsPartAttached(part)) ); return;
        };
    }

    void SpriteWrap::SetAnimationPhysicsRoot(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "({number bone | string bone})" " - " "select the physical root bone").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""bone"")");
            return;
        }
        unsigned long bone = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        try { self->setAnimationPhysicsRoot(bone); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::GetAnimationPhysicsRoot(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint]" " function" "()" " - " "get the selected physical root bone ID").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getAnimationPhysicsRoot()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::ClearAnimationPhysicsRoot(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "()" " - " "restore automatic physical root selection").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try { self->clearAnimationPhysicsRoot(); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::GetAnimationPhysicsSetupWarnings(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Array]" " function" "()" " - " "copy setup geometry diagnostics").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        auto names = self->getAnimationPhysicsSetupWarnings();
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t i = 0; i < names.size(); ++i) JSObjectSetPropertyAtIndex(ctx, result, i, v8::String::NewFromUtf8(isolate, names[i].c_str()).ToLocalChecked(), exception);
#else
        auto result = v8::Array::New(isolate);
        for (size_t i = 0; i < names.size(); ++i) (void)result->Set(isolate->GetCurrentContext(), i, v8::String::NewFromUtf8(isolate, names[i].c_str()).ToLocalChecked()).ToChecked();
#endif
        { args.GetReturnValue().Set( result ); return; };
    }

    void SpriteWrap::SetAnimationPhysicsMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([number int] mode, {string bone = undefined | [number uint] bone = undefined}, boolean includeDescendants = false, number recoveryTime = 0.5, [number int] direction = rotationDirection_AsSpecified)" " - " "change whole-rig or selected bone control").ToLocalChecked() ); return; };
        };
        if (args.Length() != 5)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 5);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""mode"")");
            return;
        }
        long mode = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""bone"")");
            return;
        }
        double bone = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[3 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 3, "a boolean (""descendants"")");
            return;
        }
        bool descendants = args[3 -1]->BooleanValue(isolate); if (!args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""seconds"")");
            return;
        }
        double seconds = args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""direction"")");
            return;
        }
        long direction = args[5 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        try { if(bone<0)self->setAnimationPhysicsMode(mode,seconds,direction);else self->setAnimationPhysicsMode(mode,AnimationBoneId(bone),descendants,seconds,direction); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        {
            args.GetReturnValue().Set( args.This() ); return;
        };
    }

    void SpriteWrap::GetAnimationPhysicsMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number int]" " function" "({string bone = undefined | [number uint] bone = undefined}, boolean includeDescendants = false)" " - " "query actual whole-rig or selected bone control").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""bone"")");
            return;
        }
        double bone = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 2, "a boolean (""descendants"")");
            return;
        }
        bool descendants = args[2 -1]->BooleanValue(isolate);
        try
        {
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, bone<0?self->getAnimationPhysicsMode():self->getAnimationPhysicsMode(AnimationBoneId(bone),descendants)) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::SetAnimationPhysicsDriveSettings(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(object settings, {string bone = undefined | [number uint] bone = undefined}, boolean includeDescendants = false)" " - " "configure selected animation drive force and response").ToLocalChecked() ); return; };
        };
        if (args.Length() != 7)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 7);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""force"")");
            return;
        }
        double force = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""torque"")");
            return;
        }
        double torque = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""frequency"")");
            return;
        }
        double frequency = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""damping"")");
            return;
        }
        double damping = args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""direction"")");
            return;
        }
        long direction = args[5 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked(); if (!args[6 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 6, "a number (""bone"")");
            return;
        }
        double bone = args[6 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[7 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 7, "a boolean (""descendants"")");
            return;
        }
        bool descendants = args[7 -1]->BooleanValue(isolate);
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
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        {
            args.GetReturnValue().Set( args.This() ); return;
        };
    }

    void SpriteWrap::GetAnimationPhysicsDriveSettings(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "({string bone | [number uint] bone})" " - " "copy a bone's configured drive settings or return null").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""bone"")");
            return;
        }
        unsigned long bone = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        try
        {
            const auto settings=self->getAnimationPhysicsDriveSettings(bone);
            if(!settings) { args.GetReturnValue().SetNull(); return; };
            const double values[]={settings->maxForce,settings->maxTorque,settings->frequency,settings->dampingRatio,double(settings->direction)};
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto result=JSObjectMakeArray(ctx,0,nullptr,exception);
            for(unsigned i=0;i<5;++i)JSObjectSetPropertyAtIndex(ctx,result,i,v8::Number::New(isolate, values[i]),exception);
#else
            auto result=v8::Array::New(isolate);
            for(unsigned i=0;i<5;++i)(void)result->Set(isolate->GetCurrentContext(),i,v8::Number::New(isolate, values[i])).ToChecked();
#endif
            { args.GetReturnValue().Set( result ); return; };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::DisableAnimationPhysics(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number recoveryTime = 0.5, [number int] direction = rotationDirection_AsSpecified)" " - " "recover animation control and remove the physical rig").ToLocalChecked() ); return; };
        };
        if (args.Length() < 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0, true);
            return;
        };
        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""seconds"")");
            return;
        }
        double seconds = (args.Length()<1) ? 0.5 : args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""direction"")");
            return;
        }
        long direction = (args.Length()<2) ? rotationDirection_AsSpecified : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        try{self->disableAnimationPhysics(seconds,direction);}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::AddAnimationDrawable(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint]" " function" "({ [object Drawing] drawing | function callback }, object options)" " - " "attach artwork to an animation bone").ToLocalChecked() ); return; };
        };
        if (args.Length() < 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3, true);
            return;
        };
        if (!args[3 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 3, "a string  (""slot"")");
            return;
        }
        v8::String::Utf8Value slot_Str(isolate, args[3 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* slot = *slot_Str;;
        if(!args[0]->IsFunction())
        {
            Drawing* drawing = 0;
            if ((args[0])->IsObject())
            {
                v8::Local<v8::Object> drawing_scriptObj_ = (args[0])->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                DrawingWrap* drawing__ = dynamic_cast<DrawingWrap*>(pdg::v8script::safe_unwrap_object_wrap_or_prototype(isolate, args[0], &drawing_scriptObj_));
                if (drawing__)
                {
                    drawing = drawing__->getCppObject();
                }
            };
            if(!drawing)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected a Drawing or callback";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            try
            {
                auto options=decodeAnimationDrawableOptions(animationPhysicsValues(PDG_POSE_SCRIPT_ARGUMENTS,args[1]),slot);
                {
                    args.GetReturnValue().Set( v8::Number::New(isolate, self->addAnimationDrawable(options,*drawing)) ); return;
                };
            }
            catch(const std::exception& error)
            {
                std::ostringstream excpt_;
                excpt_ << error.what();
                isolate->ThrowException( v8::Exception::Error( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
        }
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""callback"")");
            return;
        }
        v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(args[1 -1]);;
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto saved=std::make_shared<AnimationScriptDrawing>(ctx,callback);
#else
        auto saved=std::make_shared<AnimationScriptDrawing>(isolate,callback);
#endif
        try
        {
            auto options=decodeAnimationDrawableOptions(animationPhysicsValues(PDG_POSE_SCRIPT_ARGUMENTS,args[1]),slot);
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->addAnimationDrawable(options,[saved](auto context)
                {
                    return saved->draw(context);
                }
                )) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::RemoveAnimationDrawable(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] id)" " - " "remove a drawing registration at a safe frame boundary").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        double id = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if(!std::isfinite(id)||id<1||id>4294967295.0||id!=std::floor(id))
        {
            std::ostringstream excpt_;
            excpt_ << "Invalid drawable ID";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        self->removeAnimationDrawable(static_cast<uint32_t>(id));args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::ClearAnimationDrawables(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "release all drawing callbacks").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };self->clearAnimationDrawables();args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::SetAnimationDrawableEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] id, boolean enabled)" " - " "enable or disable a drawing registration").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        double id = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();if (!args[2 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 2, "a boolean (""enabled"")");
            return;
        }
        bool enabled = args[2 -1]->BooleanValue(isolate);
        if(!std::isfinite(id)||id<1||id>4294967295.0||id!=std::floor(id))
        {
            std::ostringstream excpt_;
            excpt_ << "Invalid drawable ID";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        try{self->setAnimationDrawableEnabled(static_cast<uint32_t>(id),enabled);}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetAnimationDrawableError(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "([number uint] id)" " - " "read a disabled drawable failure").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        double id = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if(!std::isfinite(id)||id<1||id>4294967295.0||id!=std::floor(id))
        {
            std::ostringstream excpt_;
            excpt_ << "Invalid drawable ID";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        try
        {
            const auto error=self->getAnimationDrawableError(static_cast<uint32_t>(id));
            {
                args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, error.c_str()).ToLocalChecked() ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::GetAnimationDrawBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "()" " - " "read conservative visual bounds in owning-layer coordinates").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            {
                args.GetReturnValue().Set( animationDrawingBoundsValue(PDG_POSE_SCRIPT_ARGUMENTS,self->getAnimationDrawBounds()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::AddAnimationIK(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint]" " function" "(object config, [number int] order = 0)" " - " "register a two-bone IK constraint").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""order"")");
            return;
        }
        double order = (args.Length()<2) ? 0 : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(order) || order!=std::floor(order) || order<-2147483648.0 || order>2147483647.0)
        {
            std::ostringstream excpt_;
            excpt_ << "Invalid IK order";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        try
        {
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->addAnimationIK(animationScriptIKConfig(PDG_POSE_SCRIPT_ARGUMENTS,args[0]),static_cast<int>(order))) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::SetAnimationIKTarget(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] id, number x, number y, [number int] space = animationSpace_Rig)" " - " "update an IK target in explicit owning-layer coordinates").ToLocalChecked() ); return; };
        };
        if (args.Length() < 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        double id = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""x"")");
            return;
        }
        double x = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""y"")");
            return;
        }
        double y = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""space"")");
            return;
        }
        double space = (args.Length()<4) ? 1 : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(id) || id!=std::floor(id) || id<1 || id>4294967295.0 || !std::isfinite(space) || space!=std::floor(space) || space<0 || space>2)
        {
            std::ostringstream excpt_;
            excpt_ << "Invalid IK ID or space";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        try {self->setAnimationIKTarget(static_cast<uint32_t>(id),x,y,static_cast<int>(space));}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetAnimationIKResult(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "([number uint] id)" " - " "read reach, clamp, stretch, and limit diagnostics").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        double id = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!std::isfinite(id) || id!=std::floor(id) || id<1 || id>4294967295.0)
        {
            std::ostringstream excpt_;
            excpt_ << "Invalid IK ID";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        try
        {
            {
                args.GetReturnValue().Set( animationIKResultValue(PDG_POSE_SCRIPT_ARGUMENTS,self->getAnimationIKResult(static_cast<uint32_t>(id))) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::AddAnimationModifier(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint]" " function" "(function callback, [number int] stage = animationStage_PreConstraint, [number int] order = 0)" " - " "register a synchronous borrowed-pose callback").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""callback"")");
            return;
        }
        v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(args[1 -1]);;
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""stage"")");
            return;
        }
        double stage = (args.Length()<2) ? 0 : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""order"")");
            return;
        }
        double order = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(stage) || stage != std::floor(stage) || stage < 0 || stage > 2 ||
            !std::isfinite(order) || order != std::floor(order) || order < -2147483648.0 || order > 2147483647.0)
        {
            std::ostringstream excpt_;
            excpt_ << "Expected integer animation stage and order";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto saved=std::make_shared<AnimationScriptModifier>(ctx,callback);
#else
        auto saved=std::make_shared<AnimationScriptModifier>(isolate,callback);
#endif
        try
        {
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->addAnimationModifier([saved](auto view,const auto& context)
                {
                    saved->invoke(view,context);
                }
                ,static_cast<int>(stage),static_cast<int>(order))) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::RemoveAnimationModifier(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] id)" " - " "remove a modifier at the next evaluation boundary").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        double id = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!std::isfinite(id) || id != std::floor(id) || id < 1 || id > 4294967295.0)
        {
            std::ostringstream excpt_;
            excpt_ << "Invalid modifier ID";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        self->removeAnimationModifier(static_cast<uint32_t>(id)); args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::ClearAnimationModifiers(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "remove all pose callbacks at the next evaluation boundary").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        }; self->clearAnimationModifiers(); args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetAnimationModifierError(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "([number uint] id)" " - " "read a disabled callback's diagnostic").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        double id = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!std::isfinite(id) || id != std::floor(id) || id < 1 || id > 4294967295.0)
        {
            std::ostringstream excpt_;
            excpt_ << "Invalid modifier ID";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        try
        {
            {
                args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, self->getAnimationModifierError(static_cast<uint32_t>(id)).c_str()).ToLocalChecked() ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::SetAnimationSource(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] source)" " - " "select a clip, reference, or procedural base").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""source"")");
            return;
        }
        double source = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!std::isfinite(source) || source != std::floor(source) || source < 0 || source > 2)
        {
            std::ostringstream excpt_;
            excpt_ << "Invalid animation source";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        try { self->setAnimationSource(static_cast<int>(source)); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetAnimationSource(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number int]" " function" "()" " - " "read the animation source integer constant").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        {
            args.GetReturnValue().Set( v8::Integer::New(isolate, self->getAnimationSource()) ); return;
        };
    }

    void SpriteWrap::IsAnimationDrawingSupported(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "test GUI drawing capability without changing pose state").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isAnimationDrawingSupported()) ); return; };
    }

    void SpriteWrap::SetAnimationDebugDraw(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] flags)" " - " "select per-instance animationDebug flag bits").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""flags"")");
            return;
        }
        double flags = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!std::isfinite(flags) || flags < 0 || flags > static_cast<int>(animationDebug_All) || flags != std::floor(flags))
        {
            std::ostringstream excpt_;
            excpt_ << "Expected animationDebug integer flag bits";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        try { self->setAnimationDebugDraw(static_cast<int>(flags)); }
        catch (const std::exception&)
        {
            std::ostringstream excpt_;
            excpt_ << "Animation debug drawing requires GUI support and an enabled pose";
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetAnimationDebugDraw(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number int]" " function" "()" " - " "read per-instance animationDebug flag bits").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        { args.GetReturnValue().Set( v8::Integer::New(isolate, self->getAnimationDebugDraw()) ); return; };
    }

    void SpriteWrap::EnableAnimationPose(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "(string referenceAnimation)" " - " "enable fixed-hierarchy poses using a reference clip at time zero").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""referenceAnimation"")");
            return;
        }
        v8::String::Utf8Value referenceAnimation_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* referenceAnimation = *referenceAnimation_Str;;
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->enableAnimationPose(referenceAnimation)) ); return; };
    }

    void SpriteWrap::IsAnimationPoseEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isAnimationPoseEnabled()) ); return; };
    }

    void SpriteWrap::GetAnimationRigError(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, self->getAnimationRigError().c_str()).ToLocalChecked() ); return; };
    }

    void SpriteWrap::GetAnimationBoneNames(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Array]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        auto names = self->getAnimationBoneNames();
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t i = 0; i < names.size(); ++i) JSObjectSetPropertyAtIndex(ctx, result, i, v8::String::NewFromUtf8(isolate, names[i].c_str()).ToLocalChecked(), exception);
#else
        auto result = v8::Array::New(isolate);
        for (size_t i = 0; i < names.size(); ++i) (void)result->Set(isolate->GetCurrentContext(), i, v8::String::NewFromUtf8(isolate, names[i].c_str()).ToLocalChecked()).ToChecked();
#endif
        { args.GetReturnValue().Set( result ); return; };
    }

    void SpriteWrap::GetAnimationBoneTransform(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "(string name, [number int] space = animationSpace_Local)" " - " "read an owned transform in local, rig or world coordinates").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""name"")");
            return;
        }
        v8::String::Utf8Value name_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* name = *name_Str;;
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""space"")");
            return;
        }
        double space = (args.Length()<2) ? static_cast<int>(animationSpace_Local) : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (space != static_cast<int>(animationSpace_Local) && space != static_cast<int>(animationSpace_Rig) && space != static_cast<int>(animationSpace_World))
        {
            std::ostringstream excpt_;
            excpt_ << "Expected an animationSpace integer constant";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        const int coordinateSpace = static_cast<int>(space);
        try
        {
            {
                args.GetReturnValue().Set( animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS, self->getAnimationBoneTransform(name, coordinateSpace)) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::GetAnimationBindingNames(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Array]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        auto names = self->getAnimationBindingNames();
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t i = 0; i < names.size(); ++i) JSObjectSetPropertyAtIndex(ctx, result, i, v8::String::NewFromUtf8(isolate, names[i].c_str()).ToLocalChecked(), exception);
#else
        auto result = v8::Array::New(isolate);
        for (size_t i = 0; i < names.size(); ++i) (void)result->Set(isolate->GetCurrentContext(), i, v8::String::NewFromUtf8(isolate, names[i].c_str()).ToLocalChecked()).ToChecked();
#endif
        { args.GetReturnValue().Set( result ); return; };
    }

    void SpriteWrap::GetAnimationBindingTransform(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "(string name, [number int] space = animationSpace_Local)" " - " "read an owned transform in local, rig or world coordinates").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""name"")");
            return;
        }
        v8::String::Utf8Value name_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* name = *name_Str;;
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""space"")");
            return;
        }
        double space = (args.Length()<2) ? static_cast<int>(animationSpace_Local) : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (space != static_cast<int>(animationSpace_Local) && space != static_cast<int>(animationSpace_Rig) && space != static_cast<int>(animationSpace_World))
        {
            std::ostringstream excpt_;
            excpt_ << "Expected an animationSpace integer constant";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        const int coordinateSpace = static_cast<int>(space);
        try
        {
            {
                args.GetReturnValue().Set( animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS, self->getAnimationBindingTransform(name, coordinateSpace)) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::SetAnimationBoneTransform(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string name, object transform)" " - " "set a persistent absolute local bone override").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""name"")");
            return;
        }
        v8::String::Utf8Value name_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* name = *name_Str;;
        if (!args[1]->IsObject())
        {
            std::ostringstream excpt_;
            excpt_ << "Expected an animation transform object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        v8::Local<v8::Object> object = args[1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
        AnimationTransform transform;
        {
            v8::Local<v8::Value> value = ([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "x").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }());
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
#else
            if (value.IsEmpty())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
#endif
            if (!value->IsNumber())
            {
                std::ostringstream excpt_;
                excpt_ << "Animation transform fields must all be numbers";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            transform.x = value->NumberValue(isolate->GetCurrentContext()).ToChecked();
        }
        {
            v8::Local<v8::Value> value = ([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "y").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }());
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
#else
            if (value.IsEmpty())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
#endif
            if (!value->IsNumber())
            {
                std::ostringstream excpt_;
                excpt_ << "Animation transform fields must all be numbers";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            transform.y = value->NumberValue(isolate->GetCurrentContext()).ToChecked();
        }
        {
            v8::Local<v8::Value> value = ([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "rotation").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }());
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
#else
            if (value.IsEmpty())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
#endif
            if (!value->IsNumber())
            {
                std::ostringstream excpt_;
                excpt_ << "Animation transform fields must all be numbers";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            transform.rotation = value->NumberValue(isolate->GetCurrentContext()).ToChecked();
        }
        {
            v8::Local<v8::Value> value = ([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "scaleX").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }());
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
#else
            if (value.IsEmpty())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
#endif
            if (!value->IsNumber())
            {
                std::ostringstream excpt_;
                excpt_ << "Animation transform fields must all be numbers";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            transform.scaleX = value->NumberValue(isolate->GetCurrentContext()).ToChecked();
        }
        {
            v8::Local<v8::Value> value = ([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "scaleY").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }());
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
#else
            if (value.IsEmpty())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
#endif
            if (!value->IsNumber())
            {
                std::ostringstream excpt_;
                excpt_ << "Animation transform fields must all be numbers";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            transform.scaleY = value->NumberValue(isolate->GetCurrentContext()).ToChecked();
        }
        {
            v8::Local<v8::Value> value = ([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = object->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "alpha").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }());
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception))
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
#else
            if (value.IsEmpty())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
#endif
            if (!value->IsNumber())
            {
                std::ostringstream excpt_;
                excpt_ << "Animation transform fields must all be numbers";
                isolate->ThrowException( v8::Exception::TypeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            transform.alpha = value->NumberValue(isolate->GetCurrentContext()).ToChecked();
        }
        try { self->setAnimationBoneTransform(name, transform); }
        catch (const std::exception&)
        {
            std::ostringstream excpt_;
            excpt_ << "Invalid animation bone transform or disabled pose";
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetAnimationPose(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "()" " - " "copy the final local pose into an owned snapshot").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            {
                args.GetReturnValue().Set( animationSnapshotValue(PDG_POSE_SCRIPT_ARGUMENTS, self->getAnimationPose()) ); return;
            };
        }
        catch (const std::exception&)
        {
            std::ostringstream excpt_;
            excpt_ << "Animation pose is not available";
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }

    void SpriteWrap::SampleAnimationPose(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "(string clip, number timeSeconds)" " - " "sample an independent pose at a floating-point seconds timestamp").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""clip"")");
            return;
        }
        v8::String::Utf8Value clip_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* clip = *clip_Str;;
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""timeSeconds"")");
            return;
        }
        double timeSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        try
        {
            {
                args.GetReturnValue().Set( animationSnapshotValue(PDG_POSE_SCRIPT_ARGUMENTS, self->sampleAnimationPose(clip, timeSeconds)) ); return;
            };
        }
        catch (const std::exception&)
        {
            std::ostringstream excpt_;
            excpt_ << "Invalid animation pose sample, clip or time";
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
    }
#undef PDG_POSE_SCRIPT_ARGUMENTS
#undef PDG_POSE_SCRIPT_PARAMETERS
#endif

    void SpriteWrap::GetAttachmentPart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Part]" " function" "()" " - " "mounting Part controlling this Sprite root, or null").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        auto* mount=self->getAttachmentPart(); if (!mount)
        {
            args.GetReturnValue().SetNull(); return;
        };
        if (mount->mPartScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( PartWrap::NewFromCpp(isolate, mount) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, mount->mPartScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::CreatePart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Part]" " function" "(string name)" " - " "create an independently animated Part owned by this Sprite").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""name"")");
            return;
        }
        v8::String::Utf8Value name_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* name = *name_Str;;
        try
        {
            auto* part = self->createPart(name); if (!part)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (part->mPartScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PartWrap::NewFromCpp(isolate, part) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, part->mPartScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::TransferPart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Part]" " function" "(Part part, boolean includeDescendants = true)" " - " "move a Part and optional subtree into this Sprite").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, part, Part); if (args.Length() >= 2 && !args[2 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 2, "a boolean (""descendants"")");
            return;
        }
        bool descendants = (args.Length()<2) ? true : args[2 -1]->BooleanValue(isolate);;
        try
        {
            auto* result=self->transferPart(part,descendants); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mPartScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PartWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPartScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::GetPart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Part]" " function" "([number uint] id)" " - " "get a Part by its per-Sprite ID, or null").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        double id = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!std::isfinite(id) || id < 0 || id > partId_None || std::floor(id) != id)
        {
            std::ostringstream excpt_;
            excpt_ << "Expected a Part ID";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        auto* part = self->getPart(static_cast<PartId>(id)); if (!part) { args.GetReturnValue().SetNull(); return; };
        if (part->mPartScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( PartWrap::NewFromCpp(isolate, part) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, part->mPartScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::FindPart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Part]" " function" "(string name)" " - " "find a Part by its unique name, or null").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""name"")");
            return;
        }
        v8::String::Utf8Value name_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* name = *name_Str;;
        auto* part = self->findPart(name); if (!part) { args.GetReturnValue().SetNull(); return; };
        if (part->mPartScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( PartWrap::NewFromCpp(isolate, part) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, part->mPartScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::GetPartCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, self->getPartCount()) ); return; };
    }

    void SpriteWrap::GetPartNames(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Array]" " function" "()" " - " "owned names in creation order").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        const auto names = self->getPartNames();
#ifdef PDG_USING_JAVASCRIPT_CORE
        auto result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t i = 0; i < names.size(); ++i) JSObjectSetPropertyAtIndex(ctx, result, i, v8::String::NewFromUtf8(isolate, names[i].c_str()).ToLocalChecked(), exception);
#else
        auto result = v8::Array::New(isolate);
        for (size_t i = 0; i < names.size(); ++i) result->Set(isolate->GetCurrentContext(), i, v8::String::NewFromUtf8(isolate, names[i].c_str()).ToLocalChecked()).ToChecked();
#endif
        { args.GetReturnValue().Set( result ); return; };
    }

    void SpriteWrap::RemovePart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "([number uint] id)" " - " "detach a Part; retained references keep their local state").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        double id = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!std::isfinite(id) || id < 0 || id > partId_None || std::floor(id) != id)
        {
            std::ostringstream excpt_;
            excpt_ << "Expected a Part ID";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        try
        {
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->removePart(static_cast<PartId>(id))) ); return;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::ClearParts(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "detach all Parts").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try { self->clearParts(); args.GetReturnValue().SetUndefined(); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CleanupSpriteScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

#ifdef PDG_USING_JAVASCRIPT_CORE
    Sprite* New_Sprite(const v8::FunctionCallbackInfo<v8::Value>& args) { return new Sprite(); }
#else
    SpriteWrap::SpriteWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(New_Sprite(args)) {}
    SpriteWrap::~SpriteWrap()
    {
        if (cppPtr_)
        {
            cppPtr_->mSpriteScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset();
            cppPtr_->mEventEmitterScriptObj.Reset(); cppPtr_->mISerializableScriptObj.Reset();
            cppPtr_->release(); cppPtr_ = nullptr;
        }
    }
    Sprite* New_Sprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Sprite_InNewFromCpp) return nullptr;
        auto* isolate = args.GetIsolate();
        auto* sprite = new Sprite();
        sprite->addRef();
        SPRITE_SAVE_WEAK(sprite, args.This());
        return sprite;
    }
#endif

    void SpriteWrap::ReadPhysics(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object PhysicsBody]" " function" "()" " - " "optional body or shared NoPhysics; this never creates a body").ToLocalChecked() ); return; };
        };
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* body=&static_cast<PhysicsBody&>(self->physics); if (!body)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (body->mPhysicsBodyScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsBodyWrap::NewFromCpp(isolate, body) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, body->mPhysicsBodyScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::SetupPhysicsBody(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object PhysicsBody]" " function" "(number mass = 1, number momentOfInertia = 1)" " - " "set up the body, applying mass and inertia on every call").ToLocalChecked() ); return; };
        };
        try
        {
            if (args.Length() >= 1 && !args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""mass"")");
                return;
            }
            double mass = (args.Length()<1) ? 1.0 : args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; if (args.Length() >= 2 && !args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""inertia"")");
                return;
            }
            double inertia = (args.Length()<2) ? 1.0 : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; auto* body=&self->setupPhysicsBody(mass,inertia); if (!body) { args.GetReturnValue().SetNull(); return; };
            if (body->mPhysicsBodyScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsBodyWrap::NewFromCpp(isolate, body) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, body->mPhysicsBodyScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SpriteWrap::RemovePhysicsBody(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "detach the body; retained references keep their state").ToLocalChecked() ); return; };
        };
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            }; self->removePhysicsBody(); args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }
}
