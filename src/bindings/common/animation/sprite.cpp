// -----------------------------------------------
// sprite.cpp
//
// Implementation file for Sprite bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "../core/core_impl_macros.h"
#include "../data/data_impl_macros.h"
#include "animation_impl_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_interface.h"
%#include "pdg_script_impl.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>
%#include <cmath>


namespace pdg {
    
// ========================================================================================
// ========================================================================================

%#ifndef PDG_NO_GUI
// ========================================================================================
//MARK: ISpriteDrawHelper
// ========================================================================================

BINDING_INITIALIZER_IMPL(ISpriteDrawHelper) 
    EXPORT_CLASS_SYMBOLS("ISpriteDrawHelper", ISpriteDrawHelper, , , );
	END

CLEANUP_IMPL(ISpriteDrawHelper)

%#endif // !PDG_NO_GUI


// ========================================================================================
//MARK: Sprite
// ========================================================================================


%#ifdef PDG_SPRITER_SUPPORT
%#ifdef PDG_USING_JAVASCRIPT_CORE
%#define PDG_POSE_SCRIPT_PARAMETERS JSContextRef ctx, JSValueRef* exception
%#define PDG_POSE_SCRIPT_ARGUMENTS ctx, exception
%#else
%#define PDG_POSE_SCRIPT_PARAMETERS v8::Isolate* isolate
%#define PDG_POSE_SCRIPT_ARGUMENTS isolate
%#endif
DECLARE_SYMBOL(x);
DECLARE_SYMBOL(y);
DECLARE_SYMBOL(rotation);
DECLARE_SYMBOL(scaleX);
DECLARE_SYMBOL(scaleY);
DECLARE_SYMBOL(alpha);
DECLARE_SYMBOL(name);
DECLARE_SYMBOL(parent);
DECLARE_SYMBOL(kind);
DECLARE_SYMBOL(bones);
DECLARE_SYMBOL(bindings);
DECLARE_SYMBOL(rigRevision);
DECLARE_SYMBOL(object);
DECLARE_SYMBOL(type);
DECLARE_SYMBOL(value);
DECLARE_SYMBOL(variables);
DECLARE_SYMBOL(tags);

static OBJECT_REF animationTransformValue(PDG_POSE_SCRIPT_PARAMETERS, const AnimationTransform& transform) {
    OBJECT_REF result = OBJECT_CREATE_EMPTY(0);
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(x), NUM2VAL(transform.x));
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(y), NUM2VAL(transform.y));
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(rotation), NUM2VAL(transform.rotation));
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(scaleX), NUM2VAL(transform.scaleX));
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(scaleY), NUM2VAL(transform.scaleY));
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(alpha), NUM2VAL(transform.alpha));
    return result;
}
static OBJECT_REF animationSnapshotValue(PDG_POSE_SCRIPT_PARAMETERS, const AnimationPose& pose) {
    OBJECT_REF result = OBJECT_CREATE_EMPTY(0);
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(rigRevision), STR2VAL(std::to_string(pose.getRig()->getRevision()).c_str()));
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    auto bones = JSObjectMakeArray(ctx, 0, nullptr, exception);
    %#else
    auto bones = v8::Array::New(isolate);
    %#endif
    for (uint32_t id = 0; id < pose.getRig()->getBoneCount(); ++id) {
        const auto& definition = pose.getRig()->getBone(id);
        OBJECT_REF item = animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS, pose.getLocalTransform(id));
        OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(name), STR2VAL(definition.name.c_str()));
        VALUE parentValue = NUM2VAL(definition.parent);
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        if (definition.parent == animation_NoBone) parentValue = JSValueMakeNull(ctx);
        %#else
        if (definition.parent == animation_NoBone) parentValue = v8::Null(isolate);
        %#endif
        OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(parent), parentValue);
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        JSObjectSetPropertyAtIndex(ctx, bones, id, item, exception);
        %#else
        (void)bones->Set(isolate->GetCurrentContext(), id, item).ToChecked();
        %#endif
    }
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(bones), bones);
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    auto bindings = JSObjectMakeArray(ctx, 0, nullptr, exception);
    %#else
    auto bindings = v8::Array::New(isolate);
    %#endif
    for (uint32_t id = 0; id < pose.getRig()->getBindingCount(); ++id) {
        const auto& definition = pose.getRig()->getBinding(id);
        OBJECT_REF item = animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS, pose.getBindingLocalTransform(id));
        OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(name), STR2VAL(definition.name.c_str()));
        VALUE parentValue = NUM2VAL(definition.bone);
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        if (definition.bone == animation_NoBone) parentValue = JSValueMakeNull(ctx);
        %#else
        if (definition.bone == animation_NoBone) parentValue = v8::Null(isolate);
        %#endif
        OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(parent), parentValue);
        OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(kind), INT2VAL(static_cast<int>(definition.kind)));
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        JSObjectSetPropertyAtIndex(ctx, bindings, id, item, exception);
        %#else
        (void)bindings->Set(isolate->GetCurrentContext(), id, item).ToChecked();
        %#endif
    }
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(bindings), bindings);
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    auto variables = JSObjectMakeArray(ctx, 0, nullptr, exception);
    %#else
    auto variables = v8::Array::New(isolate);
    %#endif
    for (size_t id = 0; id < pose.getMetadata().variables.size(); ++id) {
        const auto& definition = pose.getMetadata().variables[id];
        OBJECT_REF item = OBJECT_CREATE_EMPTY(0);
        OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(object), STR2VAL(definition.object.c_str()));
        OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(name), STR2VAL(definition.name.c_str()));
        if (const auto* number = std::get_if<double>(&definition.value)) {
            OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(type), INT2VAL(animationVariable_Float));
            OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(value), NUM2VAL(*number));
        } else if (const auto* integer = std::get_if<int>(&definition.value)) {
            OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(type), INT2VAL(animationVariable_Int));
            OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(value), INT2VAL(*integer));
        } else {
            OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(type), INT2VAL(animationVariable_String));
            OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(value), STR2VAL(std::get<std::string>(definition.value).c_str()));
        }
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        JSObjectSetPropertyAtIndex(ctx, variables, id, item, exception);
        %#else
        (void)variables->Set(isolate->GetCurrentContext(), id, item).ToChecked();
        %#endif
    }
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(variables), variables);
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    auto tags = JSObjectMakeArray(ctx, 0, nullptr, exception);
    %#else
    auto tags = v8::Array::New(isolate);
    %#endif
    for (size_t id = 0; id < pose.getMetadata().tags.size(); ++id) {
        const auto& definition = pose.getMetadata().tags[id];
        OBJECT_REF item = OBJECT_CREATE_EMPTY(0);
        OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(object), STR2VAL(definition.object.c_str()));
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        auto names = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t n = 0; n < definition.tags.size(); ++n) JSObjectSetPropertyAtIndex(ctx, names, n, STR2VAL(definition.tags[n].c_str()), exception);
        %#else
        auto names = v8::Array::New(isolate);
        for (size_t n = 0; n < definition.tags.size(); ++n) (void)names->Set(isolate->GetCurrentContext(), n, STR2VAL(definition.tags[n].c_str())).ToChecked();
        %#endif
        OBJECT_SET_PROPERTY_VALUE(item, SYMBOL(tags), names);
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        JSObjectSetPropertyAtIndex(ctx, tags, id, item, exception);
        %#else
        (void)tags->Set(isolate->GetCurrentContext(), id, item).ToChecked();
        %#endif
    }
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(tags), tags);
    return result;
}

static std::vector<double> animationPhysicsValues(PDG_POSE_SCRIPT_PARAMETERS,VALUE input){
    std::vector<double> result;
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    if(!JSValueIsArray(ctx,input))throw std::invalid_argument("Expected physical rig array");
    auto array=JSValueToObject(ctx,input,exception);auto key=JSStringCreateWithUTF8CString("length");
    const auto length=JSValueToNumber(ctx,JSObjectGetProperty(ctx,array,key,exception),exception);JSStringRelease(key);
    if(*exception||length>1500000)throw std::invalid_argument("Invalid physical rig array length");
    for(unsigned i=0;i<length;++i){auto value=JSObjectGetPropertyAtIndex(ctx,array,i,exception);if(*exception||!JSValueIsNumber(ctx,value))throw std::invalid_argument("Invalid physical rig number");result.push_back(JSValueToNumber(ctx,value,exception));}
    %#else
    if(!input->IsArray())throw std::invalid_argument("Expected physical rig array");
    auto array=input.As<v8::Array>();if(array->Length()>1500000)throw std::invalid_argument("Invalid physical rig array length");
    for(unsigned i=0;i<array->Length();++i){v8::Local<v8::Value> value;if(!array->Get(isolate->GetCurrentContext(),i).ToLocal(&value)||!value->IsNumber())throw std::invalid_argument("Invalid physical rig number");result.push_back(value.As<v8::Number>()->Value());}
    %#endif
    return result;
}

static AnimationTwoBoneIK animationScriptIKConfig(PDG_POSE_SCRIPT_PARAMETERS, VALUE value) {
    AnimationTwoBoneIK config;
    if (!VALUE_IS_OBJECT(value)) throw std::invalid_argument("Expected IK configuration");
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    auto object=JSValueToObject(ctx,value,exception);
    %#else
    auto object=value.As<v8::Object>();
    %#endif
    auto read=[&](const char* name) {
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        auto key=JSStringCreateWithUTF8CString(name);auto item=JSObjectGetProperty(ctx,object,key,exception);JSStringRelease(key);
        if (*exception || !JSValueIsNumber(ctx,item)) throw std::invalid_argument("Invalid IK configuration field");
        double number=JSValueToNumber(ctx,item,exception);
        %#else
        v8::Local<v8::Value> item;
        if (!object->Get(isolate->GetCurrentContext(),v8::String::NewFromUtf8(isolate,name).ToLocalChecked()).ToLocal(&item) || !item->IsNumber()) throw std::invalid_argument("Invalid IK configuration field");
        double number=item.As<v8::Number>()->Value();
        %#endif
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
DECLARE_SYMBOL(reachError);
DECLARE_SYMBOL(reachable);
DECLARE_SYMBOL(clamped);
DECLARE_SYMBOL(limited);
DECLARE_SYMBOL(stretched);
static OBJECT_REF animationIKResultValue(PDG_POSE_SCRIPT_PARAMETERS, const AnimationIKResult& value) {
    OBJECT_REF result=OBJECT_CREATE_EMPTY(0);
    OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(reachError),NUM2VAL(value.reachError));
    OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(reachable),BOOL2VAL(value.reachable));
    OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(clamped),BOOL2VAL(value.clamped));
    OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(limited),BOOL2VAL(value.limited));
    OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(stretched),BOOL2VAL(value.stretched));
    return result;
}

DECLARE_SYMBOL(deltaSeconds);
DECLARE_SYMBOL(root);
DECLARE_SYMBOL(revision);
static OBJECT_REF animationModifierContextValue(PDG_POSE_SCRIPT_PARAMETERS, const AnimationModifierContext& context) {
    OBJECT_REF result = OBJECT_CREATE_EMPTY(0);
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(deltaSeconds), NUM2VAL(context.deltaSeconds));
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(root), animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS,context.root));
    OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(revision), STR2VAL(std::to_string(context.revision).c_str()));
    return result;
}
static void applyAnimationScriptEdits(PDG_POSE_SCRIPT_PARAMETERS, AnimationPoseView view, VALUE edits) {
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    if (edits && JSValueIsString(ctx,edits)) {
        auto text=JSValueToStringCopy(ctx,edits,exception);std::vector<char> message(JSStringGetMaximumUTF8CStringSize(text));
        JSStringGetUTF8CString(text,message.data(),message.size());JSStringRelease(text);throw std::runtime_error(message.data());
    }
    %#else
    if (!edits.IsEmpty() && edits->IsString()) {v8::String::Utf8Value message(isolate,edits);throw std::runtime_error(*message ? *message : "Animation modifier failed");}
    %#endif
    const auto count = view.copy().getRig()->getBoneCount();
    const char* fields[] = {"x","y","rotation","scaleX","scaleY","alpha"};
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    if (!edits || !JSValueIsArray(ctx,edits)) throw std::invalid_argument("Modifier bridge must return bone transforms");
    auto array = JSValueToObject(ctx,edits,exception);
    auto lengthKey = JSStringCreateWithUTF8CString("length");
    auto lengthValue = JSObjectGetProperty(ctx,array,lengthKey,exception); JSStringRelease(lengthKey);
    if (*exception || JSValueToNumber(ctx,lengthValue,exception) != count) throw std::invalid_argument("Wrong modifier bone count");
    %#else
    if (edits.IsEmpty() || !edits->IsArray() || edits.As<v8::Array>()->Length() != count) throw std::invalid_argument("Wrong modifier bone count");
    auto array = edits.As<v8::Array>();
    %#endif
    for (uint32_t id=0;id<count;++id) {
        AnimationTransform transform;
        double* values[] = {&transform.x,&transform.y,&transform.rotation,&transform.scaleX,&transform.scaleY,&transform.alpha};
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        auto item=JSObjectGetPropertyAtIndex(ctx,array,id,exception);
        if (*exception || !JSValueIsObject(ctx,item)) throw std::invalid_argument("Invalid modifier transform");
        auto object=JSValueToObject(ctx,item,exception);
        %#else
        v8::Local<v8::Value> item;
        if (!array->Get(isolate->GetCurrentContext(),id).ToLocal(&item) || !item->IsObject()) throw std::invalid_argument("Invalid modifier transform");
        auto object=item.As<v8::Object>();
        %#endif
        for (int field=0;field<6;++field) {
            %#ifdef PDG_USING_JAVASCRIPT_CORE
            auto key=JSStringCreateWithUTF8CString(fields[field]);
            auto value=JSObjectGetProperty(ctx,object,key,exception);JSStringRelease(key);
            if (*exception || !JSValueIsNumber(ctx,value)) throw std::invalid_argument("Modifier transform fields must be numbers");
            *values[field]=JSValueToNumber(ctx,value,exception);
            %#else
            v8::Local<v8::Value> value;
            if (!object->Get(isolate->GetCurrentContext(),v8::String::NewFromUtf8(isolate,fields[field]).ToLocalChecked()).ToLocal(&value) || !value->IsNumber())
                throw std::invalid_argument("Modifier transform fields must be numbers");
            *values[field]=value.As<v8::Number>()->Value();
            %#endif
        }
        view.setLocalTransform(id,transform);
    }
}
struct AnimationScriptModifier {
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    JSGlobalContextRef context;
    JSObjectRef function;
    AnimationScriptModifier(JSContextRef ctx,JSObjectRef callback) : context(JSGlobalContextRetain(JSContextGetGlobalContext(ctx))), function(callback) { JSValueProtect(context,function); }
    ~AnimationScriptModifier() { JSValueUnprotect(context,function); JSGlobalContextRelease(context); }
    void invoke(AnimationPoseView view,const AnimationModifierContext& info) {
        JSContextRef ctx=context;JSValueRef error=nullptr;JSValueRef* exception=&error;
        JSValueRef argv[]={animationSnapshotValue(ctx,exception,view.copy()),animationModifierContextValue(ctx,exception,info)};
        auto result=JSObjectCallAsFunction(ctx,function,nullptr,2,argv,exception);
        if (error) throw std::runtime_error("Animation modifier script failed");
        applyAnimationScriptEdits(ctx,exception,view,result);
    }
    %#else
    v8::Isolate* isolate;
    v8::Global<v8::Context> context;
    v8::Global<v8::Function> function;
    AnimationScriptModifier(v8::Isolate* engine,v8::Local<v8::Function> callback) : isolate(engine),context(engine,engine->GetCurrentContext()),function(engine,callback) {}
    void invoke(AnimationPoseView view,const AnimationModifierContext& info) {
        v8::HandleScope handles(isolate);auto ctx=context.Get(isolate);v8::Context::Scope scope(ctx);v8::TryCatch catcher(isolate);
        v8::Local<v8::Value> argv[]={animationSnapshotValue(isolate,view.copy()),animationModifierContextValue(isolate,info)},result;
        if (!function.Get(isolate)->Call(ctx,v8::Undefined(isolate),2,argv).ToLocal(&result)) {
            v8::String::Utf8Value message(isolate,catcher.Exception());
            throw std::runtime_error(*message ? *message : "Animation modifier script failed");
        }
        applyAnimationScriptEdits(isolate,view,result);
    }
    %#endif
};

static std::shared_ptr<Drawing> animationScriptDrawingValue(PDG_POSE_SCRIPT_PARAMETERS,VALUE input){
    if(VALUE_IS_STRING(input)){
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        auto value=JSValueToStringCopy(ctx,input,exception);std::string message(JSStringGetMaximumUTF8CStringSize(value),'\0');JSStringGetUTF8CString(value,&message[0],message.size());JSStringRelease(value);throw std::runtime_error(message.c_str());
        %#else
        v8::String::Utf8Value message(isolate,input);throw std::runtime_error(*message?*message:"Drawing callback failed");
        %#endif
    }
    if(VALUE_IS_NULL(input))return {};
    EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(input,result,Drawing);
    if(!result)throw std::invalid_argument("Animation drawing callback must return a Drawing or null");
    return result->share();
}
struct AnimationScriptDrawing : AnimationScriptModifier {
    using AnimationScriptModifier::AnimationScriptModifier;
    std::shared_ptr<Drawing> draw(AnimationDrawingContext drawing){
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        JSValueRef exceptionValue=nullptr;JSValueRef* exception=&exceptionValue;JSContextRef ctx=context;
        JSValueRef args[]={animationSnapshotValue(ctx,exception,drawing.copyPose()),animationTransformValue(ctx,exception,drawing.getTransform(animationSpace_Local)),animationTransformValue(ctx,exception,drawing.getTransform(animationSpace_Rig)),animationTransformValue(ctx,exception,drawing.getTransform(animationSpace_World))};
        auto result=JSObjectCallAsFunction(ctx,function,nullptr,4,args,exception);
        if(exceptionValue)throw std::runtime_error("Animation drawing script failed");return animationScriptDrawingValue(ctx,exception,result);
        %#else
        v8::HandleScope handles(isolate);auto ctx=context.Get(isolate);v8::Context::Scope scope(ctx);v8::TryCatch catcher(isolate);
        v8::Local<v8::Value> args[]={animationSnapshotValue(isolate,drawing.copyPose()),animationTransformValue(isolate,drawing.getTransform(animationSpace_Local)),animationTransformValue(isolate,drawing.getTransform(animationSpace_Rig)),animationTransformValue(isolate,drawing.getTransform(animationSpace_World))},result;
        if(!function.Get(isolate)->Call(ctx,v8::Undefined(isolate),4,args).ToLocal(&result)){v8::String::Utf8Value message(isolate,catcher.Exception());throw std::runtime_error(*message?*message:"Animation drawing script failed");}
        return animationScriptDrawingValue(isolate,result);
        %#endif
    }
};
DECLARE_SYMBOL(left);
DECLARE_SYMBOL(top);
DECLARE_SYMBOL(right);
DECLARE_SYMBOL(bottom);
DECLARE_SYMBOL(uncullable);
static OBJECT_REF animationDrawingBoundsValue(PDG_POSE_SCRIPT_PARAMETERS,const AnimationDrawBounds& bounds){
    auto result=OBJECT_CREATE_EMPTY(0);
    OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(left),NUM2VAL(bounds.left));OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(top),NUM2VAL(bounds.top));
    OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(right),NUM2VAL(bounds.right));OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(bottom),NUM2VAL(bounds.bottom));
    OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(uncullable),BOOL2VAL(bounds.uncullable));return result;
}

%#endif

// Each wrapper owns one native reference. Engine/layer/mount references are
// independent, and identity caches must not keep the wrapper alive indefinitely.
%#ifdef PDG_USING_JAVASCRIPT_CORE
static void Sprite_finalize(JSObjectRef object) {
    auto* sprite = static_cast<Sprite*>(JSObjectGetPrivate(object));
    if (!sprite) return;
    sprite->mSpriteScriptObj = sprite->mAnimatedScriptObj = nullptr;
    sprite->mEventEmitterScriptObj = sprite->mISerializableScriptObj = nullptr;
    JSObjectSetPrivate(object, nullptr);
    sprite->release();
}
%#define SPRITE_SAVE_WEAK(sprite, obj) sprite->mSpriteScriptObj=obj; sprite->mAnimatedScriptObj=obj; sprite->mEventEmitterScriptObj=obj; sprite->mISerializableScriptObj=obj
%#else
%#define SPRITE_SAVE_WEAK(sprite, obj) sprite->mSpriteScriptObj.Reset(isolate,obj); sprite->mSpriteScriptObj.SetWeak(); sprite->mAnimatedScriptObj.Reset(isolate,obj); sprite->mAnimatedScriptObj.SetWeak(); sprite->mEventEmitterScriptObj.Reset(isolate,obj); sprite->mEventEmitterScriptObj.SetWeak(); sprite->mISerializableScriptObj.Reset(isolate,obj); sprite->mISerializableScriptObj.SetWeak()
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(Sprite,
    SPRITE_SAVE_WEAK(cppObj, obj); cppObj->addRef())
    EXPORT_FINALIZED_CLASS_SYMBOLS("Sprite", Sprite, Sprite_finalize, , ,
    	// method section
        HAS_METHOD(Sprite, "getAttachmentPart", GetAttachmentPart)
        HAS_METHOD(Sprite, "createPart", CreatePart)
        HAS_METHOD(Sprite, "transferPart", TransferPart)
        HAS_METHOD(Sprite, "setupFrameCollider", SetupFrameCollider)
        HAS_METHOD(Sprite, "setupAnimationCollider", SetupAnimationCollider)
        HAS_METHOD(Sprite, "setFrameCollisionMask", SetFrameCollisionMask)

        HAS_METHOD(Sprite, "getPart", GetPart)
        HAS_METHOD(Sprite, "findPart", FindPart)
        HAS_METHOD(Sprite, "getPartCount", GetPartCount)
        HAS_METHOD(Sprite, "getPartNames", GetPartNames)
        HAS_METHOD(Sprite, "removePart", RemovePart)
        HAS_METHOD(Sprite, "clearParts", ClearParts)
		HAS_EMITTER_METHODS(Sprite)
		HAS_ANIMATED_METHODS(Sprite)
        HAS_METHOD(Sprite, "_readCollider", ReadCollider)
        HAS_METHOD(Sprite, "setupCollider", SetupCollider)
        HAS_METHOD(Sprite, "removeCollider", RemoveCollider)
        HAS_METHOD(Sprite, "_readPhysics", ReadPhysics)
        HAS_METHOD(Sprite, "setupPhysicsBody", SetupPhysicsBody)
        HAS_METHOD(Sprite, "removePhysicsBody", RemovePhysicsBody)

		HAS_SERIALIZABLE_METHODS(Sprite)
		HAS_METHOD(Sprite, "getFrameRotatedBounds", GetFrameRotatedBounds)
		HAS_METHOD(Sprite, "setFrame", SetFrame)
		HAS_METHOD(Sprite, "getCurrentFrame", GetCurrentFrame)
		HAS_METHOD(Sprite, "getFrameCount", GetFrameCount)
		HAS_METHOD(Sprite, "startFrameAnimation", StartFrameAnimation)
		HAS_METHOD(Sprite, "stopFrameAnimation", StopFrameAnimation)
		HAS_PROPERTY(Sprite, WantsAnimLoopEvents)
		HAS_PROPERTY(Sprite, WantsAnimEndEvents)
		HAS_PROPERTY(Sprite, WantsCollideWallEvents)
		HAS_METHOD(Sprite, "addFramesImage", AddFramesImage)
	%#ifdef PDG_SPRITER_SUPPORT CR
        HAS_METHOD(Sprite, "seekAnimation", SeekAnimation)
        HAS_METHOD(Sprite, "transitionToAnimation", TransitionToAnimation)
        HAS_METHOD(Sprite, "isAnimationTransitioning", IsAnimationTransitioning)
        HAS_METHOD(Sprite, "getAnimationTransitionProgress", GetAnimationTransitionProgress)
        HAS_METHOD(Sprite, "supportsAnimationPhysics", SupportsAnimationPhysics)
        HAS_METHOD(Sprite, "setupAnimationPhysics", SetupAnimationPhysics)
        HAS_METHOD(Sprite, "setupPhysicsFromAnimationRig", SetupPhysicsFromAnimationRig)
        HAS_METHOD(Sprite, "attachAnimationPhysicsPart", AttachAnimationPhysicsPart)
        HAS_METHOD(Sprite, "detachAnimationPhysicsPart", DetachAnimationPhysicsPart)
        HAS_METHOD(Sprite, "isAnimationPhysicsPartAttached", IsAnimationPhysicsPartAttached)
        HAS_METHOD(Sprite, "setAnimationPhysicsRoot", SetAnimationPhysicsRoot)
        HAS_METHOD(Sprite, "getAnimationPhysicsRoot", GetAnimationPhysicsRoot)
        HAS_METHOD(Sprite, "clearAnimationPhysicsRoot", ClearAnimationPhysicsRoot)
        HAS_METHOD(Sprite, "getAnimationPhysicsSetupWarnings", GetAnimationPhysicsSetupWarnings)
        HAS_METHOD(Sprite, "setAnimationPhysicsMode", SetAnimationPhysicsMode)
        HAS_METHOD(Sprite, "getAnimationPhysicsMode", GetAnimationPhysicsMode)
        HAS_METHOD(Sprite, "setAnimationPhysicsDriveSettings", SetAnimationPhysicsDriveSettings)
        HAS_METHOD(Sprite, "getAnimationPhysicsDriveSettings", GetAnimationPhysicsDriveSettings)
        HAS_METHOD(Sprite, "disableAnimationPhysics", DisableAnimationPhysics)
        HAS_METHOD(Sprite, "isAnimationPhysicsEnabled", IsAnimationPhysicsEnabled)
        HAS_METHOD(Sprite, "addAnimationDrawable", AddAnimationDrawable)
        HAS_METHOD(Sprite, "removeAnimationDrawable", RemoveAnimationDrawable)
        HAS_METHOD(Sprite, "clearAnimationDrawables", ClearAnimationDrawables)
        HAS_METHOD(Sprite, "setAnimationDrawableEnabled", SetAnimationDrawableEnabled)
        HAS_METHOD(Sprite, "getAnimationDrawableError", GetAnimationDrawableError)
        HAS_METHOD(Sprite, "getAnimationDrawBounds", GetAnimationDrawBounds)
        HAS_METHOD(Sprite, "addAnimationIK", AddAnimationIK)
        HAS_METHOD(Sprite, "setAnimationIKTarget", SetAnimationIKTarget)
        HAS_METHOD(Sprite, "getAnimationIKResult", GetAnimationIKResult)
        HAS_METHOD(Sprite, "addAnimationModifier", AddAnimationModifier)
        HAS_METHOD(Sprite, "removeAnimationModifier", RemoveAnimationModifier)
        HAS_METHOD(Sprite, "clearAnimationModifiers", ClearAnimationModifiers)
        HAS_METHOD(Sprite, "getAnimationModifierError", GetAnimationModifierError)
        HAS_METHOD(Sprite, "setAnimationSource", SetAnimationSource)
        HAS_METHOD(Sprite, "getAnimationSource", GetAnimationSource)
        HAS_METHOD(Sprite, "isAnimationDrawingSupported", IsAnimationDrawingSupported)
        HAS_METHOD(Sprite, "setAnimationDebugDraw", SetAnimationDebugDraw)
        HAS_METHOD(Sprite, "getAnimationDebugDraw", GetAnimationDebugDraw)
		HAS_METHOD(Sprite, "enableAnimationPose", EnableAnimationPose)
		HAS_METHOD(Sprite, "disableAnimationPose", DisableAnimationPose)
		HAS_METHOD(Sprite, "isAnimationPoseEnabled", IsAnimationPoseEnabled)
		HAS_METHOD(Sprite, "getAnimationRigError", GetAnimationRigError)
		HAS_METHOD(Sprite, "getAnimationBoneNames", GetAnimationBoneNames)
		HAS_METHOD(Sprite, "getAnimationBindingNames", GetAnimationBindingNames)
		HAS_METHOD(Sprite, "getAnimationBoneTransform", GetAnimationBoneTransform)
		HAS_METHOD(Sprite, "getAnimationBindingTransform", GetAnimationBindingTransform)
		HAS_METHOD(Sprite, "setAnimationBoneTransform", SetAnimationBoneTransform)
		HAS_METHOD(Sprite, "clearAnimationBoneTransforms", ClearAnimationBoneTransforms)
		HAS_METHOD(Sprite, "getAnimationPose", GetAnimationPose)
		HAS_METHOD(Sprite, "sampleAnimationPose", SampleAnimationPose)
		HAS_METHOD(Sprite, "hasAnimation", HasAnimation)
		HAS_METHOD(Sprite, "startAnimation", StartAnimation)
		HAS_METHOD(Sprite, "applyCharacterMap", ApplyCharacterMap)
		HAS_METHOD(Sprite, "removeCharacterMap", RemoveCharacterMap)
		HAS_METHOD(Sprite, "removeAllCharacterMaps", RemoveAllCharacterMaps)
		HAS_METHOD(Sprite, "getAppliedCharacterMaps", GetAppliedCharacterMaps)
		HAS_METHOD(Sprite, "enableSpriterEvents", EnableSpriterEvents)
		HAS_METHOD(Sprite, "areSpriterEventsEnabled", AreSpriterEventsEnabled)
		HAS_METHOD(Sprite, "blendToAnimation", BlendToAnimation)
		HAS_METHOD(Sprite, "isBlending", IsBlending)
		HAS_METHOD(Sprite, "getBlendProgress", GetBlendProgress)
		HAS_METHOD(Sprite, "pauseAnimation", PauseAnimation)
		HAS_METHOD(Sprite, "resumeAnimation", ResumeAnimation)
		HAS_METHOD(Sprite, "stopAnimation", StopAnimation)
		HAS_METHOD(Sprite, "isAnimationPlaying", IsAnimationPlaying)
		HAS_METHOD(Sprite, "isAnimationPaused", IsAnimationPaused)
		HAS_METHOD(Sprite, "getAnimationProgress", GetAnimationProgress)
		HAS_METHOD(Sprite, "hasAttachPoint", HasAttachPoint)
		HAS_METHOD(Sprite, "getAttachPoint", GetAttachPoint)
		HAS_METHOD(Sprite, "attachSprite", AttachSprite)
		HAS_METHOD(Sprite, "activateSubEntity", ActivateSubEntity)
		HAS_METHOD(Sprite, "detachSprite", DetachSprite)
		HAS_METHOD(Sprite, "getAttachedSprite", GetAttachedSprite)
		HAS_METHOD(Sprite, "getSpriterCollisionBox", GetSpriterCollisionBox)
		HAS_METHOD(Sprite, "isSpriterCollisionActive", IsSpriterCollisionActive)
		HAS_METHOD(Sprite, "getSpriterCollisionBoxCount", GetSpriterCollisionBoxCount)
		HAS_METHOD(Sprite, "getSpriterCollisionBoxName", GetSpriterCollisionBoxName)
	%#endif CR
		HAS_METHOD(Sprite, "changeFramesImage", ChangeFramesImage)
		HAS_METHOD(Sprite, "offsetFrameCenters", OffsetFrameCenters)
		HAS_METHOD(Sprite, "getFrameCenterOffset", GetFrameCenterOffset)
		HAS_PROPERTY(Sprite, Opacity)
		HAS_METHOD(Sprite, "fadeTo", FadeTo)
		HAS_METHOD(Sprite, "fadeIn", FadeIn)
		HAS_METHOD(Sprite, "fadeOut", FadeOut)
		HAS_METHOD(Sprite, "isBehind", IsBehind)
		HAS_METHOD(Sprite, "getZOrder", GetZOrder)
		HAS_METHOD(Sprite, "moveBehind", MoveBehind)
		HAS_METHOD(Sprite, "moveInFrontOf", MoveInFrontOf)
		HAS_METHOD(Sprite, "moveToFront", MoveToFront)
		HAS_METHOD(Sprite, "moveToBack", MoveToBack)
		HAS_METHOD(Sprite, "getLayer", GetLayer)
	%#ifndef PDG_NO_GUI  CR
		HAS_METHOD(Sprite, "setDrawHelper", SetDrawHelper)
		HAS_METHOD(Sprite, "setPostDrawHelper", SetPostDrawHelper)
		HAS_PROPERTY(Sprite, WantsMouseOverEvents)
		HAS_PROPERTY(Sprite, WantsClickEvents)
		HAS_PROPERTY(Sprite, MouseDetectMode)
		HAS_PROPERTY(Sprite, WantsOffscreenEvents)
	%#endif  CR // !PDG_NO_GUI

		HAS_METHOD(Sprite, "on", On)
		HAS_METHOD(Sprite, "onCollideSprite", OnCollideSprite)
		HAS_METHOD(Sprite, "onCollideWall", OnCollideWall)
		HAS_METHOD(Sprite, "onOffscreen", OnOffscreen)
		HAS_METHOD(Sprite, "onOnscreen", OnOnscreen)
		HAS_METHOD(Sprite, "onExitLayer", OnExitLayer)
		HAS_METHOD(Sprite, "onAnimationLoop", OnAnimationLoop)
		HAS_METHOD(Sprite, "onAnimationEnd", OnAnimationEnd)
		HAS_METHOD(Sprite, "onAnimationPhysicsRecoveryComplete", OnAnimationPhysicsRecoveryComplete)
        HAS_METHOD(Sprite, "onAnimationBlendComplete", OnAnimationBlendComplete)
		HAS_METHOD(Sprite, "onFadeComplete", OnFadeComplete)
		HAS_METHOD(Sprite, "onFadeInComplete", OnFadeInComplete)
		HAS_METHOD(Sprite, "onFadeOutComplete", OnFadeOutComplete)
		HAS_METHOD(Sprite, "onMouseEnter", OnMouseEnter)
		HAS_METHOD(Sprite, "onMouseLeave", OnMouseLeave)
		HAS_METHOD(Sprite, "onMouseDown", OnMouseDown)
		HAS_METHOD(Sprite, "onMouseUp", OnMouseUp)
		HAS_METHOD(Sprite, "onMouseClick", OnMouseClick)
    );
	END
EMITTER_BASE_CLASS_IMPL(Sprite)
ANIMATED_BASE_CLASS_IMPL(Sprite)
SERIALIZABLE_BASE_CLASS_IMPL(Sprite)
GETTER_IMPL(Sprite, WantsAnimLoopEvents, BOOL)
GETTER_IMPL(Sprite, WantsAnimEndEvents, BOOL)
GETTER_IMPL(Sprite, WantsCollideWallEvents, BOOL)
%#ifndef PDG_NO_GUI  CR
  GETTER_IMPL(Sprite, WantsMouseOverEvents, BOOL)
  GETTER_IMPL(Sprite, WantsClickEvents, BOOL)
  GETTER_IMPL(Sprite, MouseDetectMode, INTEGER)
  GETTER_IMPL(Sprite, WantsOffscreenEvents, BOOL)
%#endif  CR // !PDG_NO_GUI
METHOD_IMPL(Sprite, GetFrameRotatedBounds)
	METHOD_SIGNATURE("", [object RotatedRect], 0, ([number int] frameNum = -1));
    OPTIONAL_INT32_ARG(1, frameNum, -1);
    pdg::RotatedRect r = self->getFrameRotatedBounds(frameNum);
	RETURN( RECT2VAL(r) );
	END
METHOD_IMPL(Sprite, SetFrame)
	METHOD_SIGNATURE("", [object Sprite], 1, ([number int] frame));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_INT32_ARG(1, frame);
	self->setFrame(frame);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, GetCurrentFrame)
	METHOD_SIGNATURE("which frame of animation the sprite is currently showing", 
		number, 0, ());
    REQUIRE_ARG_COUNT(0);
	int frame = self->getCurrentFrame();
	RETURN_INTEGER(frame);
	END
METHOD_IMPL(Sprite, GetFrameCount)
	METHOD_SIGNATURE("total number of frames of animation for this sprite", 
		number, 0, ());
    REQUIRE_ARG_COUNT(0);
	int count = self->getFrameCount();
	RETURN_INTEGER(count);
	END
METHOD_IMPL(Sprite, StartFrameAnimation)
	METHOD_SIGNATURE("", undefined, 4, (number fps, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames, [number int] animateFlags = animate_Looping));
    REQUIRE_ARG_MIN_COUNT(1);
    REQUIRE_NUMBER_ARG(1, fps);
    OPTIONAL_INT32_ARG(2, startingFrame, Sprite::start_FromFirstFrame);
    OPTIONAL_INT32_ARG(3, numFrames, Sprite::all_Frames);
    OPTIONAL_INT32_ARG(4, animateFlags, Sprite::animate_Looping);
	self->startFrameAnimation(fps, startingFrame, numFrames, animateFlags);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, StopFrameAnimation)
	METHOD_SIGNATURE("", undefined, 0, ());
    REQUIRE_ARG_COUNT(0);
	self->stopFrameAnimation();
	NO_RETURN;
	END
METHOD_IMPL(Sprite, SetWantsAnimLoopEvents)
	METHOD_SIGNATURE("", [object Sprite], 0, (boolean wantsThem = true));
    OPTIONAL_BOOL_ARG(1, wantsThem, true);
	self->setWantsAnimLoopEvents(wantsThem);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, SetWantsAnimEndEvents)
	METHOD_SIGNATURE("", [object Sprite], 0, (boolean wantsThem = true));
    OPTIONAL_BOOL_ARG(1, wantsThem, true);
	self->setWantsAnimEndEvents(wantsThem);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, SetWantsCollideWallEvents)
	METHOD_SIGNATURE("", [object Sprite], 0, (boolean wantsThem = true));
    OPTIONAL_BOOL_ARG(1, wantsThem, true);
	self->setWantsCollideWallEvents(wantsThem);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, AddFramesImage)
	METHOD_SIGNATURE("", undefined, 3, ([object Image] image, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames));
    REQUIRE_ARG_MIN_COUNT(1);
    REQUIRE_CPP_OBJECT_ARG(1, image, Image);
    OPTIONAL_INT32_ARG(2, startingFrame, Sprite::start_FromFirstFrame);
    OPTIONAL_INT32_ARG(3, numFrames, Sprite::all_Frames);
	self->addFramesImage(image, startingFrame, numFrames);
	NO_RETURN;
	END
%#ifdef PDG_SPRITER_SUPPORT
METHOD_IMPL(Sprite, HasAnimation)
	METHOD_SIGNATURE("", boolean, 1, ({ [number int] animationId | string animationName }) );
	REQUIRE_ARG_COUNT(1);
	bool hasIt = false;
	if (VALUE_IS_STRING(ARGV[0])) {
		REQUIRE_STRING_ARG(1, animationName);
		hasIt = self->hasAnimation(animationName);
	} else {
        REQUIRE_NUMBER_ARG(1, animationId);
        hasIt = std::isfinite(animationId) && animationId >= 0 && animationId <= 4294967295.0
            && animationId == std::floor(animationId) && self->hasAnimation(static_cast<uint32>(animationId));
	}
	RETURN_BOOL(hasIt);
	END
METHOD_IMPL(Sprite, StartAnimation)
	METHOD_SIGNATURE("", undefined, 1, ({ [number int] animationId | string animationName }) );
	REQUIRE_ARG_COUNT(1);
	if (VALUE_IS_STRING(ARGV[0])) {
		REQUIRE_STRING_ARG(1, animationName);
		self->startAnimation(animationName);
	} else {
		REQUIRE_UINT32_ARG(1, animationId);
		self->startAnimation(animationId);
	}
	NO_RETURN;
	END
METHOD_IMPL(Sprite, ApplyCharacterMap)
	METHOD_SIGNATURE("", undefined, 1, (string mapName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, mapName);
	self->applyCharacterMap(mapName);
	NO_RETURN;
	END

METHOD_IMPL(Sprite, RemoveCharacterMap)
	METHOD_SIGNATURE("", undefined, 1, (string mapName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, mapName);
	self->removeCharacterMap(mapName);
	NO_RETURN;
	END

METHOD_IMPL(Sprite, RemoveAllCharacterMaps)
	METHOD_SIGNATURE("", undefined, 0, ());
	REQUIRE_ARG_COUNT(0);
	self->removeAllCharacterMaps();
	NO_RETURN;
	END

METHOD_IMPL(Sprite, GetAppliedCharacterMaps)
	METHOD_SIGNATURE("", [object Array], 0, ());
	REQUIRE_ARG_COUNT(0);
	std::vector<std::string> maps = self->getAppliedCharacterMaps();
	// Convert std::vector<std::string> to JavaScript array
	%#ifdef PDG_USING_JAVASCRIPT_CORE
	JSObjectRef arr = JSObjectMakeArray(ctx, 0, nullptr, exception);
	for (size_t i = 0; i < maps.size(); i++) {
		JSObjectSetPropertyAtIndex(ctx, arr, (unsigned)i, STR2VAL(maps[i].c_str()), exception);
	}
	%#else
	v8::Local<v8::Array> arr = v8::Array::New(isolate);
	for (size_t i = 0; i < maps.size(); i++) {
		arr->Set(isolate->GetCurrentContext(), v8::Integer::New(isolate, i), 
			v8::String::NewFromUtf8(isolate, maps[i].c_str()).ToLocalChecked()).ToChecked();
	}
	%#endif
	RETURN(arr);
	END

METHOD_IMPL(Sprite, EnableSpriterEvents)
	METHOD_SIGNATURE("", undefined, 1, (boolean enable = true));
	OPTIONAL_BOOL_ARG(1, enable, true);
	self->enableSpriterEvents(enable);
	NO_RETURN;
	END

METHOD_IMPL(Sprite, AreSpriterEventsEnabled)
	METHOD_SIGNATURE("", boolean, 0, ());
	REQUIRE_ARG_COUNT(0);
	bool enabled = self->areSpriterEventsEnabled();
	RETURN_BOOL(enabled);
	END

METHOD_IMPL(Sprite, BlendToAnimation)
	METHOD_SIGNATURE("", undefined, 2, ({ [number int] animationId | string animationName }, number blendTime));
	REQUIRE_ARG_COUNT(2);
	REQUIRE_NUMBER_ARG(2, blendTime);
	if (VALUE_IS_STRING(ARGV[0])) {
		REQUIRE_STRING_ARG(1, animationName);
		self->blendToAnimation(animationName, blendTime);
	} else {
		REQUIRE_UINT32_ARG(1, animationId);
		self->blendToAnimation(animationId, blendTime);
	}
	NO_RETURN;
	END

METHOD_IMPL(Sprite, IsBlending)
	METHOD_SIGNATURE("", boolean, 0, ());
	REQUIRE_ARG_COUNT(0);
	bool blending = self->isBlending();
	RETURN_BOOL(blending);
	END

METHOD_IMPL(Sprite, GetBlendProgress)
	METHOD_SIGNATURE("", number, 0, ());
	REQUIRE_ARG_COUNT(0);
	float progress = self->getBlendProgress();
	RETURN_NUMBER(progress);
	END

METHOD_IMPL(Sprite, PauseAnimation)
	METHOD_SIGNATURE("", undefined, 0, ());
	REQUIRE_ARG_COUNT(0);
	self->pauseAnimation();
	NO_RETURN;
	END

METHOD_IMPL(Sprite, ResumeAnimation)
	METHOD_SIGNATURE("", undefined, 0, ());
	REQUIRE_ARG_COUNT(0);
	self->resumeAnimation();
	NO_RETURN;
	END

METHOD_IMPL(Sprite, StopAnimation)
	METHOD_SIGNATURE("", undefined, 0, ());
	REQUIRE_ARG_COUNT(0);
	self->stopAnimation();
	NO_RETURN;
	END

METHOD_IMPL(Sprite, IsAnimationPlaying)
	METHOD_SIGNATURE("", boolean, 0, ());
	REQUIRE_ARG_COUNT(0);
	bool playing = self->isAnimationPlaying();
	RETURN_BOOL(playing);
	END

METHOD_IMPL(Sprite, IsAnimationPaused)
	METHOD_SIGNATURE("", boolean, 0, ());
	REQUIRE_ARG_COUNT(0);
	bool paused = self->isAnimationPaused();
	RETURN_BOOL(paused);
	END

METHOD_IMPL(Sprite, GetAnimationProgress)
	METHOD_SIGNATURE("", number, 0, ());
	REQUIRE_ARG_COUNT(0);
	float progress = self->getAnimationProgress();
	RETURN_NUMBER(progress);
	END

METHOD_IMPL(Sprite, HasAttachPoint)
	METHOD_SIGNATURE("", boolean, 1, (string attachPointName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, attachPointName);
	bool hasPoint = self->hasAttachPoint(attachPointName);
	RETURN_BOOL(hasPoint);
	END

METHOD_IMPL(Sprite, GetAttachPoint)
	METHOD_SIGNATURE("", [object Offset], 1, (string attachPointName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, attachPointName);
	pdg::Offset offset = self->getAttachPoint(attachPointName);
	RETURN_OFFSET(offset);
	END

METHOD_IMPL(Sprite, AttachSprite)
	METHOD_SIGNATURE("", undefined, 2, ([object Sprite] sprite, string attachPointName));
	REQUIRE_ARG_COUNT(2);
	REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
	REQUIRE_STRING_ARG(2, attachPointName);
	self->attachSprite(sprite, attachPointName);
	NO_RETURN;
	END

METHOD_IMPL(Sprite, DetachSprite)
	METHOD_SIGNATURE("", undefined, 1, ([object Sprite] sprite));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
	self->detachSprite(sprite);
	NO_RETURN;
	END

METHOD_IMPL(Sprite, GetAttachedSprite)
	METHOD_SIGNATURE("", [object Sprite], 1, (string attachPointName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, attachPointName);
	pdg::Sprite* attached = self->getAttachedSprite(attachPointName);
	if (attached) {
		RETURN_NEW_CPP_OBJECT(attached, Sprite);
	} else {
		RETURN_NULL;
	}
	END

METHOD_IMPL(Sprite, ActivateSubEntity)
	METHOD_SIGNATURE("", undefined, 2, (string entityName, string animationName = "idle"));
	REQUIRE_ARG_MIN_COUNT(1);
	REQUIRE_STRING_ARG(1, entityName);
	OPTIONAL_STRING_ARG(2, animationName, "idle");
	self->activateSubEntity(entityName, animationName);
	NO_RETURN;
	END

%#endif
%#ifndef PDG_NO_GUI
METHOD_IMPL(Sprite, SetWantsOffscreenEvents)
	METHOD_SIGNATURE("", [object Sprite], 0, (boolean wantsThem = true));
    OPTIONAL_BOOL_ARG(1, wantsThem, true);
	self->setWantsOffscreenEvents(wantsThem);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, SetDrawHelper)
	METHOD_SIGNATURE("", undefined, 1, ([object ISpriteDrawHelper] helper));
	OBJECT_SAVE(self->mSpriteScriptObj, THIS);
    REQUIRE_ARG_COUNT(1);
    REQUIRE_CPP_OBJECT_OR_SUBCLASS_OR_NULL_ARG(1, helper, ISpriteDrawHelper);
	DEBUG_DUMP_SCRIPT_OBJECT(ARGV[0], ISpriteDrawHelper)	
    self->setDrawHelper(helper);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, SetPostDrawHelper)
	METHOD_SIGNATURE("", undefined, 1, ([object ISpriteDrawHelper] helper));
	OBJECT_SAVE(self->mSpriteScriptObj, THIS);
    REQUIRE_ARG_COUNT(1);
    REQUIRE_CPP_OBJECT_OR_SUBCLASS_OR_NULL_ARG(1, helper, ISpriteDrawHelper);
	DEBUG_DUMP_SCRIPT_OBJECT(ARGV[0], ISpriteDrawHelper)	
    self->setPostDrawHelper(helper);
	NO_RETURN;
	END
%#endif // !PDG_NO_GUI
METHOD_IMPL(Sprite, ChangeFramesImage)
	METHOD_SIGNATURE("", undefined, 2, ([object Image] oldImage, [object Image] newImage));
    REQUIRE_ARG_COUNT(2);
    REQUIRE_CPP_OBJECT_ARG(1, oldImage, Image);
    REQUIRE_CPP_OBJECT_ARG(2, newImage, Image);
	self->changeFramesImage(oldImage, newImage);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, OffsetFrameCenters)
	METHOD_SIGNATURE("", undefined, 5, ([number int] offsetX, [number int] offsetY, [object Image] image = null, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_INT32_ARG(1, offsetX);
    REQUIRE_INT32_ARG(2, offsetY);
    OPTIONAL_CPP_OBJECT_ARG(3, image, Image, 0);
    OPTIONAL_INT32_ARG(4, startingFrame, Sprite::start_FromFirstFrame);
    OPTIONAL_INT32_ARG(5, numFrames, Sprite::all_Frames);
	self->offsetFrameCenters(offsetX, offsetY, image, startingFrame, numFrames);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, GetFrameCenterOffset)
	METHOD_SIGNATURE("", [object Offset], 2, ([object Image] image = null, [number int] frameNum = 0));
    OPTIONAL_CPP_OBJECT_ARG(1, image, Image, 0);
    OPTIONAL_INT32_ARG(2, frameNum, 0);
	pdg::Offset offset = self->getFrameCenterOffset(image, frameNum);
	RETURN_OFFSET(offset);
	END
METHOD_IMPL(Sprite, SetOpacity)
	METHOD_SIGNATURE("", [object Sprite], 1, (number opacity));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, opacity);
	self->setOpacity(opacity);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, GetOpacity)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	float opacity = self->getOpacity();
	RETURN_NUMBER(opacity);
	END
METHOD_IMPL(Sprite, FadeTo)
	METHOD_SIGNATURE("", undefined, 3, (number targetOpacity, number durationSeconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(1);
	REQUIRE_NUMBER_ARG(1, targetOpacity);
	REQUIRE_NUMBER_ARG(2, durationSeconds);
	OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::linearTween);
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) {
    	self->fadeTo(targetOpacity, durationSeconds, gEasingFunctions[easing]);
    } else {
		self->fadeTo(targetOpacity, durationSeconds);
	}
	NO_RETURN;
	END
METHOD_IMPL(Sprite, FadeIn)
	METHOD_SIGNATURE("", undefined, 2, (number durationSeconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(1);
	REQUIRE_NUMBER_ARG(1, durationSeconds);
	OPTIONAL_INT32_ARG(2, easing, EasingFuncRef::linearTween);
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) {
    	self->fadeIn(durationSeconds, gEasingFunctions[easing]);
    } else {
		self->fadeIn(durationSeconds);
	}
	NO_RETURN;
	END
METHOD_IMPL(Sprite, FadeOut)
	METHOD_SIGNATURE("", undefined, 2, (number durationSeconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(1);
	REQUIRE_NUMBER_ARG(1, durationSeconds);
	OPTIONAL_INT32_ARG(2, easing, EasingFuncRef::linearTween);
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) {
    	self->fadeOut(durationSeconds, gEasingFunctions[easing]);
    } else {
		self->fadeOut(durationSeconds);
	}
	NO_RETURN;
	END
METHOD_IMPL(Sprite, IsBehind)
	METHOD_SIGNATURE("", boolean, 1, ([object Sprite] sprite));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
	bool behind = self->isBehind(sprite);
	RETURN_BOOL(behind);
	END
METHOD_IMPL(Sprite, GetZOrder)
	METHOD_SIGNATURE("", [number int], 0, ());
    REQUIRE_ARG_COUNT(0);
	int zorder = self->getZOrder();
	RETURN_INTEGER(zorder);
	END
METHOD_IMPL(Sprite, MoveBehind)
	METHOD_SIGNATURE("", [object Sprite], 1, ([object Sprite] sprite));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
	self->moveBehind(sprite);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, MoveInFrontOf)
	METHOD_SIGNATURE("", [object Sprite], 1, ([object Sprite] sprite));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
	self->moveInFrontOf(sprite);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, MoveToFront)
	METHOD_SIGNATURE("put this sprite in front of all others in its layer", [object Sprite], 0, ());
    REQUIRE_ARG_COUNT(0);
	self->moveToFront();
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, MoveToBack)
	METHOD_SIGNATURE("put this sprite behind all others in its layer", [object Sprite], 0, ());
    REQUIRE_ARG_COUNT(0);
	self->moveToBack();
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, SetupFrameCollider)
    METHOD_SIGNATURE("Follow current frame collision geometry", [object Collider], 0, ([number int] mode = frameCollider_AlphaMask, [number int] alphaThreshold = 128));
    try {
        OPTIONAL_NUMBER_ARG(1,modeValue,static_cast<double>(frameCollider_AlphaMask));
        OPTIONAL_NUMBER_ARG(2,threshold,128);
        if(!std::isfinite(modeValue) || modeValue<0 || modeValue>std::numeric_limits<int>::max() || std::floor(modeValue)!=modeValue) {
            THROW_RANGE_ERR("Expected an integer frameCollider mode"); RETURN_NULL;
        }
        const int mode=static_cast<int>(modeValue);
        if((mode!=frameCollider_Bounds && mode!=frameCollider_AlphaMask) || !std::isfinite(threshold) || threshold<1 || threshold>255 || std::floor(threshold)!=threshold) {
            THROW_RANGE_ERR("Expected a frameCollider mode and an integer alpha threshold from 1 to 255"); RETURN_NULL;
        }
        auto* result=&self->setupFrameCollider(mode,threshold); RETURN_CPP_OBJECT(result,Collider);
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Sprite, SetupAnimationCollider)
    METHOD_SIGNATURE("Follow authored animation collision boxes", [object Collider], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->setupAnimationCollider(); RETURN_CPP_OBJECT(result,Collider); }
    catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Sprite, SetFrameCollisionMask)
    METHOD_SIGNATURE("Assign a mask to frames using an image", [object Sprite], 2, ([object Image] frameImage, [object Image] maskImage));
    try { REQUIRE_ARG_COUNT(2); REQUIRE_CPP_OBJECT_ARG(1,image,Image); Image* mask=nullptr; if(!VALUE_IS_NULL(ARGV[1])) { REQUIRE_CPP_OBJECT_ARG(2,value,Image); mask=value; }
        self->setFrameCollisionMask(image,mask); RETURN_THIS;
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
%#ifndef PDG_NO_GUI
METHOD_IMPL(Sprite, SetWantsMouseOverEvents)
	METHOD_SIGNATURE("", [object Sprite], 1, (boolean wantsThem = true));
    OPTIONAL_BOOL_ARG(1, wantsThem, true);
	self->setWantsMouseOverEvents(wantsThem);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, SetWantsClickEvents)
	METHOD_SIGNATURE("", [object Sprite], 1, (boolean wantsThem = true));
    OPTIONAL_BOOL_ARG(1, wantsThem, true);
	self->setWantsClickEvents(wantsThem);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, SetMouseDetectMode)
	METHOD_SIGNATURE("", [object Sprite], 1, ([number int] collisionType = collide_BoundingBox));
    OPTIONAL_INT32_ARG(1, collisionType, Sprite::collide_BoundingBox);
	self->setMouseDetectMode(collisionType);
	RETURN_THIS;
	END
%#endif // !PDG_NO_GUI
METHOD_IMPL(Sprite, GetLayer)
	METHOD_SIGNATURE("get the layer that contains this sprite", [object SpriteLayer], 0, ());
    REQUIRE_ARG_COUNT(0);
	SpriteLayer* layer = self->getLayer();
	RETURN_CPP_OBJECT(layer, SpriteLayer);
	END
METHOD_IMPL(Sprite, On)
	METHOD_SIGNATURE("", [object IEventHandler], 2, ([number int] eventCode, function func));
	REQUIRE_ARG_COUNT(2);
	REQUIRE_INT32_ARG(1, eventCode);
	REQUIRE_FUNCTION_ARG(2, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	long evtCode;
	if (eventCode <= pdg::Sprite::action_CollideWall) {
		evtCode = pdg::eventType_SpriteCollide;
	} else if (eventCode <= pdg::Sprite::action_FadeOutComplete) {
		evtCode = pdg::eventType_SpriteAnimate;
	} else {
		evtCode = pdg::eventType_SpriteTouch;
	}
	self->addHandler(handler, evtCode);	
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

// Sprite convenience event methods
METHOD_IMPL(Sprite, OnCollideSprite)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) {
		DEBUG_ONLY( OS::_DOUT("OnCollideSprite: failed to create handler"); )
		RETURN_NULL;
	}
	self->addHandler(handler, pdg::eventType_SpriteCollide);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnCollideWall)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteCollide);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnOffscreen)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Offscreen);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnOnscreen)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Onscreen);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnExitLayer)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_ExitLayer);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnAnimationLoop)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnAnimationEnd)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationEnd);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnAnimationBlendComplete)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationBlendComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END
METHOD_IMPL(Sprite, OnAnimationPhysicsRecoveryComplete)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationPhysicsRecoveryComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnFadeComplete)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnFadeInComplete)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeInComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnFadeOutComplete)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeOutComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnMouseEnter)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseEnter);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnMouseLeave)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseLeave);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnMouseDown)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseDown);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnMouseUp)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseUp);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnMouseClick)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseClick);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

%#ifdef PDG_SPRITER_SUPPORT
METHOD_IMPL(Sprite, GetSpriterCollisionBox)
	METHOD_SIGNATURE("get a Spriter collision box by name", [object RotatedRect], 1, (string boxName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, boxName);
	pdg::RotatedRect rect = self->getSpriterCollisionBox(boxName);
	RETURN( RECT2VAL(rect) );
	END

METHOD_IMPL(Sprite, IsSpriterCollisionActive)
	METHOD_SIGNATURE("check if a Spriter collision box is active", boolean, 1, (string boxName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, boxName);
	bool active = self->isSpriterCollisionActive(boxName);
	RETURN_BOOL(active);
	END

METHOD_IMPL(Sprite, GetSpriterCollisionBoxCount)
	METHOD_SIGNATURE("get the number of active Spriter collision boxes", number, 0, ());
	REQUIRE_ARG_COUNT(0);
	int count = self->getSpriterCollisionBoxCount();
	RETURN_INTEGER(count);
	END

METHOD_IMPL(Sprite, GetSpriterCollisionBoxName)
	METHOD_SIGNATURE("get the name of a Spriter collision box by index", string, 1, (number index));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_INT32_ARG(1, index);
	const char* name = self->getSpriterCollisionBoxName(index);
	if (name) {
		RETURN_STRING(name);
	} else {
		RETURN_NULL;
	}
	END


%#endif // PDG_SPRITER_SUPPORT


%#ifdef PDG_SPRITER_SUPPORT
METHOD_IMPL(Sprite, DisableAnimationPose)
    METHOD_SIGNATURE("", undefined, 0, ());
    REQUIRE_ARG_COUNT(0);
    self->disableAnimationPose();
    NO_RETURN;
    END
METHOD_IMPL(Sprite, ClearAnimationBoneTransforms)
    METHOD_SIGNATURE("", undefined, 0, ());
    REQUIRE_ARG_COUNT(0);
    self->clearAnimationBoneTransforms();
    NO_RETURN;
    END

METHOD_IMPL(Sprite, SeekAnimation)
    METHOD_SIGNATURE("select an independent clip time in floating-point seconds", undefined, 2, (string clip, number timeSeconds));
    REQUIRE_ARG_COUNT(2); REQUIRE_STRING_ARG(1,clip); REQUIRE_NUMBER_ARG(2,timeSeconds);
    try {self->seekAnimation(clip,timeSeconds);} catch(const std::exception& error) {THROW_ERR(error.what());RETURN_NULL;}
    NO_RETURN;
    END
METHOD_IMPL(Sprite, TransitionToAnimation)
    METHOD_SIGNATURE("select an independent clip time in floating-point seconds", undefined, 3, (string clip, number timeSeconds, number durationSeconds));
    REQUIRE_ARG_COUNT(3); REQUIRE_STRING_ARG(1,clip); REQUIRE_NUMBER_ARG(2,timeSeconds);
    REQUIRE_NUMBER_ARG(3,durationSeconds);
    try {self->transitionToAnimation(clip,timeSeconds,durationSeconds);} catch(const std::exception& error) {THROW_ERR(error.what());RETURN_NULL;}
    NO_RETURN;
    END
METHOD_IMPL(Sprite, IsAnimationTransitioning)
    METHOD_SIGNATURE("test independently timed crossfade state", boolean, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isAnimationTransitioning());
    END
METHOD_IMPL(Sprite, GetAnimationTransitionProgress)
    METHOD_SIGNATURE("read normalized independently timed crossfade progress", number, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getAnimationTransitionProgress());
    END

METHOD_IMPL(Sprite, SupportsAnimationPhysics)
    METHOD_SIGNATURE("test physical animation capability", boolean, 0, ());
    REQUIRE_ARG_COUNT(0);RETURN_BOOL(self->supportsAnimationPhysics());
    END
METHOD_IMPL(Sprite, IsAnimationPhysicsEnabled)
    METHOD_SIGNATURE("test physical animation state", boolean, 0, ());
    REQUIRE_ARG_COUNT(0);RETURN_BOOL(self->isAnimationPhysicsEnabled());
    END
METHOD_IMPL(Sprite, SetupAnimationPhysics)
    METHOD_SIGNATURE("create a versioned physical rig", undefined, 1, (object definition));
    REQUIRE_ARG_COUNT(1);
    try{self->setupAnimationPhysics(decodeAnimationPhysicsDefinition(animationPhysicsValues(PDG_POSE_SCRIPT_ARGUMENTS,ARGV[0])));}catch(const std::exception& error){THROW_ERR(error.what());RETURN_NULL;}
    NO_RETURN;
    END
METHOD_IMPL(Sprite, SetupPhysicsFromAnimationRig)
    METHOD_SIGNATURE("generate a dynamic rig from the reference skeleton", [object Sprite], 1, (number totalMass, number unitsPerMeter = 1));
    REQUIRE_ARG_MIN_COUNT(1); REQUIRE_NUMBER_ARG(1,mass); OPTIONAL_NUMBER_ARG(2,units,1);
    try { self->setupPhysicsFromAnimationRig(mass,units); } catch(const std::exception& error) { THROW_ERR(error.what()); RETURN_NULL; }
    RETURN_THIS;
    END
METHOD_IMPL(Sprite, AttachAnimationPhysicsPart)
    METHOD_SIGNATURE("register a physical Part in the generated rig assembly", [object Sprite], 1, ([object Part] part, [object Part] parent = null));
    REQUIRE_ARG_MIN_COUNT(1);REQUIRE_CPP_OBJECT_ARG(1,part,Part);
    Part* parent=nullptr;
    if(ARGC>1 && !VALUE_IS_NULL(ARGV[1])) { REQUIRE_CPP_OBJECT_ARG(2,value,Part);parent=value; }
    try { self->attachAnimationPhysicsPart(part,parent); } catch(const std::exception& error) { THROW_ERR(error.what()); RETURN_NULL; }
    RETURN_THIS;
    END
METHOD_IMPL(Sprite, DetachAnimationPhysicsPart)
    METHOD_SIGNATURE("release rig membership and disconnect boundary joints", [object Sprite], 1, ([object Part] part, boolean includeDescendants = true));
    REQUIRE_ARG_MIN_COUNT(1);REQUIRE_CPP_OBJECT_ARG(1,part,Part);OPTIONAL_BOOL_ARG(2,descendants,true);
    try { self->detachAnimationPhysicsPart(part,descendants); } catch(const std::exception& error) { THROW_ERR(error.what()); RETURN_NULL; }
    RETURN_THIS;
    END
METHOD_IMPL(Sprite, IsAnimationPhysicsPartAttached)
    METHOD_SIGNATURE("test whether a Part contributes to this generated rig assembly", boolean, 1, ([object Part] part));
    REQUIRE_ARG_COUNT(1);REQUIRE_CPP_OBJECT_ARG(1,part,Part);RETURN_BOOL(self->isAnimationPhysicsPartAttached(part));
    END
METHOD_IMPL(Sprite, SetAnimationPhysicsRoot)
    METHOD_SIGNATURE("select the physical root bone", [object Sprite], 1, ({number bone | string bone}));
    REQUIRE_ARG_COUNT(1); REQUIRE_UINT32_ARG(1,bone);
    try { self->setAnimationPhysicsRoot(bone); } catch(const std::exception& error) { THROW_ERR(error.what()); RETURN_NULL; }
    RETURN_THIS;
    END
METHOD_IMPL(Sprite, GetAnimationPhysicsRoot)
    METHOD_SIGNATURE("get the selected physical root bone ID", [number uint], 0, ());
    REQUIRE_ARG_COUNT(0);
    try { RETURN_NUMBER(self->getAnimationPhysicsRoot()); } catch(const std::exception& error) { THROW_ERR(error.what()); RETURN_NULL; }
    END
METHOD_IMPL(Sprite, ClearAnimationPhysicsRoot)
    METHOD_SIGNATURE("restore automatic physical root selection", [object Sprite], 0, ());
    REQUIRE_ARG_COUNT(0);
    try { self->clearAnimationPhysicsRoot(); } catch(const std::exception& error) { THROW_ERR(error.what()); RETURN_NULL; }
    RETURN_THIS;
    END
METHOD_IMPL(Sprite, GetAnimationPhysicsSetupWarnings)
    METHOD_SIGNATURE("copy setup geometry diagnostics", [object Array], 0, ());
    REQUIRE_ARG_COUNT(0);
    auto names = self->getAnimationPhysicsSetupWarnings();
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    auto result = JSObjectMakeArray(ctx, 0, nullptr, exception);
    for (size_t i = 0; i < names.size(); ++i) JSObjectSetPropertyAtIndex(ctx, result, i, STR2VAL(names[i].c_str()), exception);
    %#else
    auto result = v8::Array::New(isolate);
    for (size_t i = 0; i < names.size(); ++i) (void)result->Set(isolate->GetCurrentContext(), i, STR2VAL(names[i].c_str())).ToChecked();
    %#endif
    RETURN_OBJECT(result);
    END
METHOD_IMPL(Sprite, SetAnimationPhysicsMode)
    METHOD_SIGNATURE("change whole-rig or selected bone control", [object Sprite], 1, ([number int] mode, {string bone = undefined | [number uint] bone = undefined}, boolean includeDescendants = false, number recoveryTime = 0.5, [number int] direction = rotationDirection_AsSpecified));
    REQUIRE_ARG_COUNT(5); REQUIRE_INT32_ARG(1,mode); REQUIRE_NUMBER_ARG(2,bone); REQUIRE_BOOL_ARG(3,descendants); REQUIRE_NUMBER_ARG(4,seconds); REQUIRE_INT32_ARG(5,direction);
    try { if(bone<0)self->setAnimationPhysicsMode(mode,seconds,direction);else self->setAnimationPhysicsMode(mode,AnimationBoneId(bone),descendants,seconds,direction); }
    catch(const std::exception& error){THROW_ERR(error.what());RETURN_NULL;} RETURN_THIS;
    END
METHOD_IMPL(Sprite, GetAnimationPhysicsMode)
    METHOD_SIGNATURE("query actual whole-rig or selected bone control", [number int], 0, ({string bone = undefined | [number uint] bone = undefined}, boolean includeDescendants = false));
    REQUIRE_ARG_COUNT(2); REQUIRE_NUMBER_ARG(1,bone); REQUIRE_BOOL_ARG(2,descendants);
    try { RETURN_NUMBER(bone<0?self->getAnimationPhysicsMode():self->getAnimationPhysicsMode(AnimationBoneId(bone),descendants)); }
    catch(const std::exception& error){THROW_ERR(error.what());RETURN_NULL;}
    END
METHOD_IMPL(Sprite, SetAnimationPhysicsDriveSettings)
    METHOD_SIGNATURE("configure selected animation drive force and response", [object Sprite], 1, (object settings, {string bone = undefined | [number uint] bone = undefined}, boolean includeDescendants = false));
    REQUIRE_ARG_COUNT(7); REQUIRE_NUMBER_ARG(1,force); REQUIRE_NUMBER_ARG(2,torque); REQUIRE_NUMBER_ARG(3,frequency); REQUIRE_NUMBER_ARG(4,damping); REQUIRE_INT32_ARG(5,direction); REQUIRE_NUMBER_ARG(6,bone); REQUIRE_BOOL_ARG(7,descendants);
    try { AnimationPhysicsDriveSettings settings{force,torque,frequency,damping,int(direction)}; if(bone<0)self->setAnimationPhysicsDriveSettings(settings);else self->setAnimationPhysicsDriveSettings(settings,AnimationBoneId(bone),descendants); }
    catch(const std::exception& error){THROW_ERR(error.what());RETURN_NULL;} RETURN_THIS;
    END
METHOD_IMPL(Sprite, GetAnimationPhysicsDriveSettings)
    METHOD_SIGNATURE("copy a bone's configured drive settings or return null", object, 1, ({string bone | [number uint] bone}));
    REQUIRE_ARG_COUNT(1); REQUIRE_UINT32_ARG(1,bone);
    try {
        const auto settings=self->getAnimationPhysicsDriveSettings(bone);
        if(!settings) RETURN_NULL;
        const double values[]={settings->maxForce,settings->maxTorque,settings->frequency,settings->dampingRatio,double(settings->direction)};
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        auto result=JSObjectMakeArray(ctx,0,nullptr,exception);
        for(unsigned i=0;i<5;++i)JSObjectSetPropertyAtIndex(ctx,result,i,NUM2VAL(values[i]),exception);
        %#else
        auto result=v8::Array::New(isolate);
        for(unsigned i=0;i<5;++i)(void)result->Set(isolate->GetCurrentContext(),i,NUM2VAL(values[i])).ToChecked();
        %#endif
        RETURN_OBJECT(result);
    } catch(const std::exception& error){THROW_ERR(error.what());RETURN_NULL;}
    END

METHOD_IMPL(Sprite, DisableAnimationPhysics)
    METHOD_SIGNATURE("recover animation control and remove the physical rig", undefined, 0, (number recoveryTime = 0.5, [number int] direction = rotationDirection_AsSpecified));
    REQUIRE_ARG_MIN_COUNT(0);OPTIONAL_NUMBER_ARG(1,seconds,0.5); OPTIONAL_INT32_ARG(2,direction,rotationDirection_AsSpecified);
    try{self->disableAnimationPhysics(seconds,direction);}catch(const std::exception& error){THROW_ERR(error.what());RETURN_NULL;}
    NO_RETURN;
    END

METHOD_IMPL(Sprite, AddAnimationDrawable)
    METHOD_SIGNATURE("attach artwork to an animation bone", [number uint], 2, ({ [object Drawing] drawing | function callback }, object options));
    REQUIRE_ARG_MIN_COUNT(3);REQUIRE_STRING_ARG(3,slot);
    if(!VALUE_IS_FUNCTION(ARGV[0])){
        EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(ARGV[0],drawing,Drawing);
        if(!drawing){THROW_TYPE_ERR("Expected a Drawing or callback");RETURN_NULL;}
        try{auto options=decodeAnimationDrawableOptions(animationPhysicsValues(PDG_POSE_SCRIPT_ARGUMENTS,ARGV[1]),slot);RETURN_NUMBER(self->addAnimationDrawable(options,*drawing));}
        catch(const std::exception& error){THROW_ERR(error.what());RETURN_NULL;}
    }
    REQUIRE_FUNCTION_ARG(1,callback);
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    auto saved=std::make_shared<AnimationScriptDrawing>(ctx,callback);
    %#else
    auto saved=std::make_shared<AnimationScriptDrawing>(isolate,callback);
    %#endif
    try{auto options=decodeAnimationDrawableOptions(animationPhysicsValues(PDG_POSE_SCRIPT_ARGUMENTS,ARGV[1]),slot);RETURN_NUMBER(self->addAnimationDrawable(options,[saved](auto context){return saved->draw(context);}));}
    catch(const std::exception& error){THROW_ERR(error.what());RETURN_NULL;}
    END
METHOD_IMPL(Sprite, RemoveAnimationDrawable)
    METHOD_SIGNATURE("remove a drawing registration at a safe frame boundary", undefined, 1, ([number uint] id));
    REQUIRE_ARG_COUNT(1);REQUIRE_NUMBER_ARG(1,id);
    if(!std::isfinite(id)||id<1||id>4294967295.0||id!=std::floor(id)){THROW_RANGE_ERR("Invalid drawable ID");RETURN_NULL;}
    self->removeAnimationDrawable(static_cast<uint32_t>(id));NO_RETURN;
    END
METHOD_IMPL(Sprite, ClearAnimationDrawables)
    METHOD_SIGNATURE("release all drawing callbacks", undefined, 0, ());
    REQUIRE_ARG_COUNT(0);self->clearAnimationDrawables();NO_RETURN;
    END
METHOD_IMPL(Sprite, SetAnimationDrawableEnabled)
    METHOD_SIGNATURE("enable or disable a drawing registration", undefined, 2, ([number uint] id, boolean enabled));
    REQUIRE_ARG_COUNT(2);REQUIRE_NUMBER_ARG(1,id);REQUIRE_BOOL_ARG(2,enabled);
    if(!std::isfinite(id)||id<1||id>4294967295.0||id!=std::floor(id)){THROW_RANGE_ERR("Invalid drawable ID");RETURN_NULL;}
    try{self->setAnimationDrawableEnabled(static_cast<uint32_t>(id),enabled);}catch(const std::exception& error){THROW_ERR(error.what());RETURN_NULL;}NO_RETURN;
    END
METHOD_IMPL(Sprite, GetAnimationDrawableError)
    METHOD_SIGNATURE("read a disabled drawable failure", string, 1, ([number uint] id));
    REQUIRE_ARG_COUNT(1);REQUIRE_NUMBER_ARG(1,id);
    if(!std::isfinite(id)||id<1||id>4294967295.0||id!=std::floor(id)){THROW_RANGE_ERR("Invalid drawable ID");RETURN_NULL;}
    try{const auto error=self->getAnimationDrawableError(static_cast<uint32_t>(id));RETURN_STRING(error.c_str());}catch(const std::exception& error){THROW_ERR(error.what());RETURN_NULL;}
    END
METHOD_IMPL(Sprite, GetAnimationDrawBounds)
    METHOD_SIGNATURE("read conservative visual bounds in owning-layer coordinates", object, 0, ());
    REQUIRE_ARG_COUNT(0);
    try{RETURN_OBJECT(animationDrawingBoundsValue(PDG_POSE_SCRIPT_ARGUMENTS,self->getAnimationDrawBounds()));}catch(const std::exception& error){THROW_ERR(error.what());RETURN_NULL;}
    END

METHOD_IMPL(Sprite, AddAnimationIK)
    METHOD_SIGNATURE("register a two-bone IK constraint", [number uint], 1, (object config, [number int] order = 0));
    REQUIRE_ARG_MIN_COUNT(1); OPTIONAL_NUMBER_ARG(2,order,0);
    if (!std::isfinite(order) || order!=std::floor(order) || order<-2147483648.0 || order>2147483647.0) {THROW_RANGE_ERR("Invalid IK order");RETURN_NULL;}
    try { RETURN_NUMBER(self->addAnimationIK(animationScriptIKConfig(PDG_POSE_SCRIPT_ARGUMENTS,ARGV[0]),static_cast<int>(order))); }
    catch(const std::exception& error) {THROW_ERR(error.what());RETURN_NULL;}
    END
METHOD_IMPL(Sprite, SetAnimationIKTarget)
    METHOD_SIGNATURE("update an IK target in explicit owning-layer coordinates", undefined, 3, ([number uint] id, number x, number y, [number int] space = animationSpace_Rig));
    REQUIRE_ARG_MIN_COUNT(3); REQUIRE_NUMBER_ARG(1,id); REQUIRE_NUMBER_ARG(2,x); REQUIRE_NUMBER_ARG(3,y); OPTIONAL_NUMBER_ARG(4,space,1);
    if (!std::isfinite(id) || id!=std::floor(id) || id<1 || id>4294967295.0 || !std::isfinite(space) || space!=std::floor(space) || space<0 || space>2) {THROW_RANGE_ERR("Invalid IK ID or space");RETURN_NULL;}
    try {self->setAnimationIKTarget(static_cast<uint32_t>(id),x,y,static_cast<int>(space));}
    catch(const std::exception& error) {THROW_ERR(error.what());RETURN_NULL;}
    NO_RETURN;
    END
METHOD_IMPL(Sprite, GetAnimationIKResult)
    METHOD_SIGNATURE("read reach, clamp, stretch, and limit diagnostics", object, 1, ([number uint] id));
    REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,id);
    if (!std::isfinite(id) || id!=std::floor(id) || id<1 || id>4294967295.0) {THROW_RANGE_ERR("Invalid IK ID");RETURN_NULL;}
    try {RETURN_OBJECT(animationIKResultValue(PDG_POSE_SCRIPT_ARGUMENTS,self->getAnimationIKResult(static_cast<uint32_t>(id))));}
    catch(const std::exception& error) {THROW_ERR(error.what());RETURN_NULL;}
    END

METHOD_IMPL(Sprite, AddAnimationModifier)
    METHOD_SIGNATURE("register a synchronous borrowed-pose callback", [number uint], 1, (function callback, [number int] stage = animationStage_PreConstraint, [number int] order = 0));
    REQUIRE_ARG_MIN_COUNT(1); REQUIRE_FUNCTION_ARG(1,callback);
    OPTIONAL_NUMBER_ARG(2,stage,0); OPTIONAL_NUMBER_ARG(3,order,0);
    if (!std::isfinite(stage) || stage != std::floor(stage) || stage < 0 || stage > 2 ||
        !std::isfinite(order) || order != std::floor(order) || order < -2147483648.0 || order > 2147483647.0) {
        THROW_RANGE_ERR("Expected integer animation stage and order"); RETURN_NULL;
    }
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    auto saved=std::make_shared<AnimationScriptModifier>(ctx,callback);
    %#else
    auto saved=std::make_shared<AnimationScriptModifier>(isolate,callback);
    %#endif
    try { RETURN_NUMBER(self->addAnimationModifier([saved](auto view,const auto& context){saved->invoke(view,context);},static_cast<int>(stage),static_cast<int>(order))); }
    catch(const std::exception& error) { THROW_ERR(error.what()); RETURN_NULL; }
    END
METHOD_IMPL(Sprite, RemoveAnimationModifier)
    METHOD_SIGNATURE("remove a modifier at the next evaluation boundary", undefined, 1, ([number uint] id));
    REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,id);
    if (!std::isfinite(id) || id != std::floor(id) || id < 1 || id > 4294967295.0) { THROW_RANGE_ERR("Invalid modifier ID"); RETURN_NULL; }
    self->removeAnimationModifier(static_cast<uint32_t>(id)); NO_RETURN;
    END
METHOD_IMPL(Sprite, ClearAnimationModifiers)
    METHOD_SIGNATURE("remove all pose callbacks at the next evaluation boundary", undefined, 0, ());
    REQUIRE_ARG_COUNT(0); self->clearAnimationModifiers(); NO_RETURN;
    END
METHOD_IMPL(Sprite, GetAnimationModifierError)
    METHOD_SIGNATURE("read a disabled callback's diagnostic", string, 1, ([number uint] id));
    REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,id);
    if (!std::isfinite(id) || id != std::floor(id) || id < 1 || id > 4294967295.0) { THROW_RANGE_ERR("Invalid modifier ID"); RETURN_NULL; }
    try { RETURN_STRING(self->getAnimationModifierError(static_cast<uint32_t>(id)).c_str()); }
    catch(const std::exception& error) { THROW_ERR(error.what()); RETURN_NULL; }
    END
METHOD_IMPL(Sprite, SetAnimationSource)
    METHOD_SIGNATURE("select a clip, reference, or procedural base", undefined, 1, ([number int] source));
    REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,source);
    if (!std::isfinite(source) || source != std::floor(source) || source < 0 || source > 2) { THROW_RANGE_ERR("Invalid animation source"); RETURN_NULL; }
    try { self->setAnimationSource(static_cast<int>(source)); }
    catch(const std::exception& error) { THROW_ERR(error.what()); RETURN_NULL; }
    NO_RETURN;
    END
METHOD_IMPL(Sprite, GetAnimationSource)
    METHOD_SIGNATURE("read the animation source integer constant", [number int], 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_INTEGER(self->getAnimationSource());
    END

METHOD_IMPL(Sprite, IsAnimationDrawingSupported)
    METHOD_SIGNATURE("test GUI drawing capability without changing pose state", boolean, 0, ());
    REQUIRE_ARG_COUNT(0);
    RETURN_BOOL(self->isAnimationDrawingSupported());
    END
METHOD_IMPL(Sprite, SetAnimationDebugDraw)
    METHOD_SIGNATURE("select per-instance animationDebug flag bits", undefined, 1, ([number int] flags));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, flags);
    if (!std::isfinite(flags) || flags < 0 || flags > static_cast<int>(animationDebug_All) || flags != std::floor(flags)) {
        THROW_RANGE_ERR("Expected animationDebug integer flag bits"); RETURN_NULL;
    }
    try { self->setAnimationDebugDraw(static_cast<int>(flags)); }
    catch (const std::exception&) { THROW_ERR("Animation debug drawing requires GUI support and an enabled pose"); RETURN_NULL; }
    NO_RETURN;
    END
METHOD_IMPL(Sprite, GetAnimationDebugDraw)
    METHOD_SIGNATURE("read per-instance animationDebug flag bits", [number int], 0, ());
    REQUIRE_ARG_COUNT(0);
    RETURN_INTEGER(self->getAnimationDebugDraw());
    END
METHOD_IMPL(Sprite, EnableAnimationPose)
    METHOD_SIGNATURE("enable fixed-hierarchy poses using a reference clip at time zero", boolean, 1, (string referenceAnimation));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_STRING_ARG(1, referenceAnimation);
    RETURN_BOOL(self->enableAnimationPose(referenceAnimation));
    END
METHOD_IMPL(Sprite, IsAnimationPoseEnabled)
    METHOD_SIGNATURE("", boolean, 0, ());
    REQUIRE_ARG_COUNT(0);
    RETURN_BOOL(self->isAnimationPoseEnabled());
    END
METHOD_IMPL(Sprite, GetAnimationRigError)
    METHOD_SIGNATURE("", string, 0, ());
    REQUIRE_ARG_COUNT(0);
    RETURN_STRING(self->getAnimationRigError().c_str());
    END
METHOD_IMPL(Sprite, GetAnimationBoneNames)
    METHOD_SIGNATURE("", [object Array], 0, ());
    REQUIRE_ARG_COUNT(0);
    auto names = self->getAnimationBoneNames();
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    auto result = JSObjectMakeArray(ctx, 0, nullptr, exception);
    for (size_t i = 0; i < names.size(); ++i) JSObjectSetPropertyAtIndex(ctx, result, i, STR2VAL(names[i].c_str()), exception);
    %#else
    auto result = v8::Array::New(isolate);
    for (size_t i = 0; i < names.size(); ++i) (void)result->Set(isolate->GetCurrentContext(), i, STR2VAL(names[i].c_str())).ToChecked();
    %#endif
    RETURN_OBJECT(result);
    END
METHOD_IMPL(Sprite, GetAnimationBoneTransform)
    METHOD_SIGNATURE("read an owned transform in local, rig or world coordinates", object, 1, (string name, [number int] space = animationSpace_Local));
    REQUIRE_ARG_MIN_COUNT(1);
    REQUIRE_STRING_ARG(1, name);
    OPTIONAL_NUMBER_ARG(2, space, static_cast<int>(animationSpace_Local));
    if (space != static_cast<int>(animationSpace_Local) && space != static_cast<int>(animationSpace_Rig) && space != static_cast<int>(animationSpace_World)) {
        THROW_RANGE_ERR("Expected an animationSpace integer constant"); RETURN_NULL;
    }
    const int coordinateSpace = static_cast<int>(space);
    try { RETURN_OBJECT(animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS, self->getAnimationBoneTransform(name, coordinateSpace))); }
    catch (const std::exception& error) { THROW_ERR(error.what()); RETURN_NULL; }
    END
METHOD_IMPL(Sprite, GetAnimationBindingNames)
    METHOD_SIGNATURE("", [object Array], 0, ());
    REQUIRE_ARG_COUNT(0);
    auto names = self->getAnimationBindingNames();
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    auto result = JSObjectMakeArray(ctx, 0, nullptr, exception);
    for (size_t i = 0; i < names.size(); ++i) JSObjectSetPropertyAtIndex(ctx, result, i, STR2VAL(names[i].c_str()), exception);
    %#else
    auto result = v8::Array::New(isolate);
    for (size_t i = 0; i < names.size(); ++i) (void)result->Set(isolate->GetCurrentContext(), i, STR2VAL(names[i].c_str())).ToChecked();
    %#endif
    RETURN_OBJECT(result);
    END
METHOD_IMPL(Sprite, GetAnimationBindingTransform)
    METHOD_SIGNATURE("read an owned transform in local, rig or world coordinates", object, 1, (string name, [number int] space = animationSpace_Local));
    REQUIRE_ARG_MIN_COUNT(1);
    REQUIRE_STRING_ARG(1, name);
    OPTIONAL_NUMBER_ARG(2, space, static_cast<int>(animationSpace_Local));
    if (space != static_cast<int>(animationSpace_Local) && space != static_cast<int>(animationSpace_Rig) && space != static_cast<int>(animationSpace_World)) {
        THROW_RANGE_ERR("Expected an animationSpace integer constant"); RETURN_NULL;
    }
    const int coordinateSpace = static_cast<int>(space);
    try { RETURN_OBJECT(animationTransformValue(PDG_POSE_SCRIPT_ARGUMENTS, self->getAnimationBindingTransform(name, coordinateSpace))); }
    catch (const std::exception& error) { THROW_ERR(error.what()); RETURN_NULL; }
    END
METHOD_IMPL(Sprite, SetAnimationBoneTransform)
    METHOD_SIGNATURE("set a persistent absolute local bone override", undefined, 2, (string name, object transform));
    REQUIRE_ARG_COUNT(2);
    REQUIRE_STRING_ARG(1, name);
    if (!VALUE_IS_OBJECT(ARGV[1])) { THROW_TYPE_ERR("Expected an animation transform object"); RETURN_NULL; }
    OBJECT_REF object = VAL2OBJ(ARGV[1]);
    AnimationTransform transform;
    {
        VALUE value = OBJECT_GET_PROPERTY(object, SYMBOL(x));
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        if (!value || (exception && *exception)) { RETURN_NULL; }
        %#else
        if (value.IsEmpty()) { RETURN_NULL; }
        %#endif
        if (!VALUE_IS_NUMBER(value)) { THROW_TYPE_ERR("Animation transform fields must all be numbers"); RETURN_NULL; }
        transform.x = VAL2NUM(value);
    }
    {
        VALUE value = OBJECT_GET_PROPERTY(object, SYMBOL(y));
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        if (!value || (exception && *exception)) { RETURN_NULL; }
        %#else
        if (value.IsEmpty()) { RETURN_NULL; }
        %#endif
        if (!VALUE_IS_NUMBER(value)) { THROW_TYPE_ERR("Animation transform fields must all be numbers"); RETURN_NULL; }
        transform.y = VAL2NUM(value);
    }
    {
        VALUE value = OBJECT_GET_PROPERTY(object, SYMBOL(rotation));
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        if (!value || (exception && *exception)) { RETURN_NULL; }
        %#else
        if (value.IsEmpty()) { RETURN_NULL; }
        %#endif
        if (!VALUE_IS_NUMBER(value)) { THROW_TYPE_ERR("Animation transform fields must all be numbers"); RETURN_NULL; }
        transform.rotation = VAL2NUM(value);
    }
    {
        VALUE value = OBJECT_GET_PROPERTY(object, SYMBOL(scaleX));
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        if (!value || (exception && *exception)) { RETURN_NULL; }
        %#else
        if (value.IsEmpty()) { RETURN_NULL; }
        %#endif
        if (!VALUE_IS_NUMBER(value)) { THROW_TYPE_ERR("Animation transform fields must all be numbers"); RETURN_NULL; }
        transform.scaleX = VAL2NUM(value);
    }
    {
        VALUE value = OBJECT_GET_PROPERTY(object, SYMBOL(scaleY));
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        if (!value || (exception && *exception)) { RETURN_NULL; }
        %#else
        if (value.IsEmpty()) { RETURN_NULL; }
        %#endif
        if (!VALUE_IS_NUMBER(value)) { THROW_TYPE_ERR("Animation transform fields must all be numbers"); RETURN_NULL; }
        transform.scaleY = VAL2NUM(value);
    }
    {
        VALUE value = OBJECT_GET_PROPERTY(object, SYMBOL(alpha));
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        if (!value || (exception && *exception)) { RETURN_NULL; }
        %#else
        if (value.IsEmpty()) { RETURN_NULL; }
        %#endif
        if (!VALUE_IS_NUMBER(value)) { THROW_TYPE_ERR("Animation transform fields must all be numbers"); RETURN_NULL; }
        transform.alpha = VAL2NUM(value);
    }
    try { self->setAnimationBoneTransform(name, transform); }
    catch (const std::exception&) { THROW_ERR("Invalid animation bone transform or disabled pose"); RETURN_NULL; }
    NO_RETURN;
    END
METHOD_IMPL(Sprite, GetAnimationPose)
    METHOD_SIGNATURE("copy the final local pose into an owned snapshot", object, 0, ());
    REQUIRE_ARG_COUNT(0);
    try { RETURN_OBJECT(animationSnapshotValue(PDG_POSE_SCRIPT_ARGUMENTS, self->getAnimationPose())); }
    catch (const std::exception&) { THROW_ERR("Animation pose is not available"); RETURN_NULL; }
    END
METHOD_IMPL(Sprite, SampleAnimationPose)
    METHOD_SIGNATURE("sample an independent pose at a floating-point seconds timestamp", object, 2, (string clip, number timeSeconds));
    REQUIRE_ARG_COUNT(2);
    REQUIRE_STRING_ARG(1, clip);
    REQUIRE_NUMBER_ARG(2, timeSeconds);
    try { RETURN_OBJECT(animationSnapshotValue(PDG_POSE_SCRIPT_ARGUMENTS, self->sampleAnimationPose(clip, timeSeconds))); }
    catch (const std::exception&) { THROW_ERR("Invalid animation pose sample, clip or time"); RETURN_NULL; }
    END
%#undef PDG_POSE_SCRIPT_ARGUMENTS
%#undef PDG_POSE_SCRIPT_PARAMETERS
%#endif


METHOD_IMPL(Sprite, GetAttachmentPart)
    METHOD_SIGNATURE("mounting Part controlling this Sprite root, or null", [object Part], 0, ());
    REQUIRE_ARG_COUNT(0); auto* mount=self->getAttachmentPart(); RETURN_CPP_OBJECT(mount,Part);
    END
METHOD_IMPL(Sprite, CreatePart)
    METHOD_SIGNATURE("create an independently animated Part owned by this Sprite", [object Part], 1, (string name));
    REQUIRE_ARG_COUNT(1); REQUIRE_STRING_ARG(1, name);
    try { auto* part = self->createPart(name); RETURN_CPP_OBJECT(part, Part); }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Sprite, TransferPart)
    METHOD_SIGNATURE("move a Part and optional subtree into this Sprite", [object Part], 1, (Part part, boolean includeDescendants = true));
    REQUIRE_ARG_MIN_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1, part, Part); OPTIONAL_BOOL_ARG(2, descendants, true);
    try { auto* result=self->transferPart(part,descendants); RETURN_CPP_OBJECT(result,Part); }
    catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Sprite, GetPart)
    METHOD_SIGNATURE("get a Part by its per-Sprite ID, or null", [object Part], 1, ([number uint] id));
    REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1, id);
    if (!std::isfinite(id) || id < 0 || id > partId_None || std::floor(id) != id) { THROW_RANGE_ERR("Expected a Part ID"); RETURN_NULL; }
    auto* part = self->getPart(static_cast<PartId>(id)); RETURN_CPP_OBJECT(part, Part);
    END
METHOD_IMPL(Sprite, FindPart)
    METHOD_SIGNATURE("find a Part by its unique name, or null", [object Part], 1, (string name));
    REQUIRE_ARG_COUNT(1); REQUIRE_STRING_ARG(1, name);
    auto* part = self->findPart(name); RETURN_CPP_OBJECT(part, Part);
    END
METHOD_IMPL(Sprite, GetPartCount)
    METHOD_SIGNATURE("", [number uint], 0, ()); REQUIRE_ARG_COUNT(0);
    RETURN_UINT32(self->getPartCount());
    END
METHOD_IMPL(Sprite, GetPartNames)
    METHOD_SIGNATURE("owned names in creation order", [object Array], 0, ()); REQUIRE_ARG_COUNT(0);
    const auto names = self->getPartNames();
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    auto result = JSObjectMakeArray(ctx, 0, nullptr, exception);
    for (size_t i = 0; i < names.size(); ++i) JSObjectSetPropertyAtIndex(ctx, result, i, STR2VAL(names[i].c_str()), exception);
    %#else
    auto result = v8::Array::New(isolate);
    for (size_t i = 0; i < names.size(); ++i) result->Set(isolate->GetCurrentContext(), i, STR2VAL(names[i].c_str())).ToChecked();
    %#endif
    RETURN_OBJECT(result);
    END
METHOD_IMPL(Sprite, RemovePart)
    METHOD_SIGNATURE("detach a Part; retained references keep their local state", boolean, 1, ([number uint] id));
    REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1, id);
    if (!std::isfinite(id) || id < 0 || id > partId_None || std::floor(id) != id) { THROW_RANGE_ERR("Expected a Part ID"); RETURN_NULL; }
    try { RETURN_BOOL(self->removePart(static_cast<PartId>(id))); }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Sprite, ClearParts)
    METHOD_SIGNATURE("detach all Parts", undefined, 0, ()); REQUIRE_ARG_COUNT(0);
    try { self->clearParts(); NO_RETURN; }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END

CLEANUP_IMPL(Sprite)

%#ifdef PDG_USING_JAVASCRIPT_CORE
Sprite* New_Sprite(SCRIPT_ARGS) { return new Sprite(); }
%#else
SpriteWrap::SpriteWrap(SCRIPT_ARGS) : cppPtr_(New_Sprite(args)) {}
SpriteWrap::~SpriteWrap() {
    if (cppPtr_) {
        cppPtr_->mSpriteScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset();
        cppPtr_->mEventEmitterScriptObj.Reset(); cppPtr_->mISerializableScriptObj.Reset();
        cppPtr_->release(); cppPtr_ = nullptr;
    }
}
Sprite* New_Sprite(SCRIPT_ARGS) {
    if (s_Sprite_InNewFromCpp) return nullptr;
    auto* isolate = args.GetIsolate();
    auto* sprite = new Sprite();
    sprite->addRef();
    SPRITE_SAVE_WEAK(sprite, args.This());
    return sprite;
}
%#endif


METHOD_IMPL(Sprite, ReadPhysics)
    METHOD_SIGNATURE("optional body or shared NoPhysics; this never creates a body", [object PhysicsBody], 0, ());
    try {
        REQUIRE_ARG_COUNT(0); auto* body=&static_cast<PhysicsBody&>(self->physics); RETURN_CPP_OBJECT(body,PhysicsBody);
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Sprite, SetupPhysicsBody)
    METHOD_SIGNATURE("set up the body, applying mass and inertia on every call", [object PhysicsBody], 0, (number mass = 1, number momentOfInertia = 1));
    try {
        OPTIONAL_NUMBER_ARG(1,mass,1.0); OPTIONAL_NUMBER_ARG(2,inertia,1.0); auto* body=&self->setupPhysicsBody(mass,inertia); RETURN_CPP_OBJECT(body,PhysicsBody);
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Sprite, RemovePhysicsBody)
    METHOD_SIGNATURE("detach the body; retained references keep their state", undefined, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); self->removePhysicsBody(); NO_RETURN;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
} // pdg namespace
