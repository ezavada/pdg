// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/collider.cpp
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

#include "pdg_script_impl.h"
#include "pdg_script_interface.h"

#include "internals.h"
#include "pdg-lib.h"

#include <cstdlib>
#include <cmath>
#include <limits>

namespace pdg
{

#ifdef PDG_USING_JAVASCRIPT_CORE
    static bool collisionArgumentIs(JSContextRef ctx, JSValueRef value, bool body)
    {
        return JSValueIsObjectOfClass(ctx, value, body ? PhysicsBody_class() : Collider_class());
    }
#define COLLISION_ARGUMENT_IS(value, body) collisionArgumentIs(ctx, value, body)
#else
    static bool collisionArgumentIs(v8::Isolate* isolate, v8::Local<v8::Value> value, bool body)
    {
        return (body ? PhysicsBodyWrap::GetTemplate(isolate) : ColliderWrap::GetTemplate(isolate))->HasInstance(value);
    }
#define COLLISION_ARGUMENT_IS(value, body) collisionArgumentIs(isolate, value, body)
#endif

#ifdef PDG_USING_JAVASCRIPT_CORE
    Collider* New_Collider(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return nullptr; }
    static void Collider_finalize(JSObjectRef object)
    {
        auto* body=static_cast<Collider*>(JSObjectGetPrivate(object));
        if(body) {body->mColliderScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);body->release();}
    }
#define COLLIDER_SAVE_WEAK(cppObj,obj) cppObj->mColliderScriptObj=obj
#else
#define COLLIDER_SAVE_WEAK(cppObj,obj) cppObj->mColliderScriptObj.Reset(isolate,obj);cppObj->mColliderScriptObj.SetWeak()
    ColliderWrap::ColliderWrap(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) : cppPtr_(nullptr) {}
    ColliderWrap::~ColliderWrap()
    {
        if(cppPtr_) {cppPtr_->mColliderScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}
    }
#endif

    static bool s_Collider_InNewFromCpp = false;

    JSObjectRef Collider_newFromCpp(JSContextRef ctx, Collider* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Collider_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Collider_class());
        COLLIDER_SAVE_WEAK(cppObj,obj);cppObj->addRef();
        return obj;
    }

    JSObjectRef Collider_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {

        if (!s_Collider_InNewFromCpp)
        {
            std::ostringstream excpt_;
            excpt_ << "throw TypeError('" "Collider" " cannot be instantiated with \\'new\\'. Use the factory function: pdg." "Sprite.setupCollider or Part.setupCollider" "()')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        }

        Collider* cppObj = New_Collider(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to create C++ native " "Collider" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Collider_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Collider_class());
        return obj;
    }

    JSClassRef Collider_class()
    {

        static JSStaticValue Collider_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Collider_staticFunctions[] =
        {
            { "setWantsContactEvents", Collider_SetWantsContactEvents, kJSPropertyAttributeDontDelete },
            { "getWantsContactEvents", Collider_GetWantsContactEvents, kJSPropertyAttributeDontDelete },
            { "setFriction", Collider_SetFriction, kJSPropertyAttributeDontDelete },
            { "setRestitution", Collider_SetRestitution, kJSPropertyAttributeDontDelete },
            { "getFriction", Collider_GetFriction, kJSPropertyAttributeDontDelete },
            { "getRestitution", Collider_GetRestitution, kJSPropertyAttributeDontDelete },
            { "useBodyMaterial", Collider_UseBodyMaterial, kJSPropertyAttributeDontDelete },
            { "isPresent", Collider_IsPresent, kJSPropertyAttributeDontDelete },
            { "isAttached", Collider_IsAttached, kJSPropertyAttributeDontDelete },
            { "isEnabled", Collider_IsEnabled, kJSPropertyAttributeDontDelete },
            { "isSensor", Collider_IsSensor, kJSPropertyAttributeDontDelete },
            { "getId", Collider_GetId, kJSPropertyAttributeDontDelete },
            { "getCategory", Collider_GetCategory, kJSPropertyAttributeDontDelete },
            { "getCollisionMask", Collider_GetCollisionMask, kJSPropertyAttributeDontDelete },
            { "getGroup", Collider_GetGroup, kJSPropertyAttributeDontDelete },
            { "getShapeCount", Collider_GetShapeCount, kJSPropertyAttributeDontDelete },
            { "setEnabled", Collider_SetEnabled, kJSPropertyAttributeDontDelete },
            { "setSensor", Collider_SetSensor, kJSPropertyAttributeDontDelete },
            { "setCategory", Collider_SetCategory, kJSPropertyAttributeDontDelete },
            { "setCollisionMask", Collider_SetCollisionMask, kJSPropertyAttributeDontDelete },
            { "setGroup", Collider_SetGroup, kJSPropertyAttributeDontDelete },
            { "getPhysicsBody", Collider_GetPhysicsBody, kJSPropertyAttributeDontDelete },
            { "setCircle", Collider_SetCircle, kJSPropertyAttributeDontDelete },
            { "addCircle", Collider_AddCircle, kJSPropertyAttributeDontDelete },
            { "setCapsule", Collider_SetCapsule, kJSPropertyAttributeDontDelete },
            { "addCapsule", Collider_AddCapsule, kJSPropertyAttributeDontDelete },
            { "getCapsuleStart", Collider_GetCapsuleStart, kJSPropertyAttributeDontDelete },
            { "getCapsuleEnd", Collider_GetCapsuleEnd, kJSPropertyAttributeDontDelete },
            { "getCapsuleRadius", Collider_GetCapsuleRadius, kJSPropertyAttributeDontDelete },
            { "setBox", Collider_SetBox, kJSPropertyAttributeDontDelete },
            { "addBox", Collider_AddBox, kJSPropertyAttributeDontDelete },
            { "clearShapes", Collider_ClearShapes, kJSPropertyAttributeDontDelete },
            { "useOwnerPhysics", Collider_UseOwnerPhysics, kJSPropertyAttributeDontDelete },
            { "setPhysicsBody", Collider_SetPhysicsBody, kJSPropertyAttributeDontDelete },
            { "getBounds", Collider_GetBounds, kJSPropertyAttributeDontDelete },
            { "contains", Collider_Contains, kJSPropertyAttributeDontDelete },
            { "overlaps", Collider_Overlaps, kJSPropertyAttributeDontDelete },
            { "removeShape", Collider_RemoveShape, kJSPropertyAttributeDontDelete },
            { "getShapeId", Collider_GetShapeId, kJSPropertyAttributeDontDelete },
            { "getContactError", Collider_GetContactError, kJSPropertyAttributeDontDelete },
            { "addPolygon", Collider_AddPolygon, kJSPropertyAttributeDontDelete },
            { "setPolygon", Collider_SetPolygon, kJSPropertyAttributeDontDelete },
            { "setImageMask", Collider_SetImageMask, kJSPropertyAttributeDontDelete },
            { "addImageMask", Collider_AddImageMask, kJSPropertyAttributeDontDelete },
            { "getGeometrySource", Collider_GetGeometrySource, kJSPropertyAttributeDontDelete },
            { "isSourceShape", Collider_IsSourceShape, kJSPropertyAttributeDontDelete },
            { "getShapeName", Collider_GetShapeName, kJSPropertyAttributeDontDelete },
            { "getShapeType", Collider_GetShapeType, kJSPropertyAttributeDontDelete },
            { "getCircleRadius", Collider_GetCircleRadius, kJSPropertyAttributeDontDelete },
            { "setContactHandler", Collider_SetContactHandler, kJSPropertyAttributeDontDelete },
            { "setCollisionFilter", Collider_SetCollisionFilter, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.finalize = Collider_finalize;
            definition.className = "Collider";
            definition.staticFunctions = Collider_staticFunctions;
            definition.staticValues = Collider_staticValues;
            definition.callAsConstructor = Collider_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
#undef COLLIDER_SAVE_WEAK

    JSValueRef Collider_IsPresent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isPresent());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_IsAttached(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isAttached());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_IsEnabled(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isEnabled());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_IsSensor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isSensor());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetId(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getId());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetCategory(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getCategory());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetCollisionMask(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getCollisionMask());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetGroup(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getGroup());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetShapeCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getShapeCount());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_SetEnabled(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""value"")");
            bool value = JSValueToBoolean(ctx, arguments[1 -1]); self->setEnabled(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_SetSensor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""value"")");
            bool value = JSValueToBoolean(ctx, arguments[1 -1]); self->setSensor(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_SetCategory(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned 32-bit integer" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->setCategory(uint32_t(value)); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_SetCollisionMask(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned 32-bit integer" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->setCollisionMask(uint32_t(value)); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_SetGroup(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned 32-bit integer" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->setGroup(uint32_t(value)); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetPhysicsBody(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* result=&self->getPhysicsBody(); if (!result) return JSValueMakeNull(ctx);
            if (!result->mPhysicsBodyScriptObj)
            {
                return PhysicsBody_newFromCpp(ctx, result);
            }
            else
            {
                return result->mPhysicsBodyScriptObj;
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
    JSValueRef Collider_SetCircle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radius"")");
            double radius = JSValueToNumber(ctx, arguments[1 -1], exception); pdg::Point center;
            if (argumentCount < 2)
            {
                center = Point();
            }
            else
            {
                auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], center, exception);
                if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
                if (!*center_isPoint)
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
                }
            };
            self->setCircle(radius,center); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_AddCircle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radius"")");
            double radius = JSValueToNumber(ctx, arguments[1 -1], exception); pdg::Point center;
            if (argumentCount < 2)
            {
                center = Point();
            }
            else
            {
                auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], center, exception);
                if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
                if (!*center_isPoint)
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
                }
            };
            return JSValueMakeNumber(ctx, self->addCircle(radius,center));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_SetCapsule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 3)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3); pdg::Point start;
            auto start_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], start, exception);
            if (!start_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*start_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            }; pdg::Point end;
            auto end_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], end, exception);
            if (!end_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*end_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
            }; if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""radius"")");
            double radius = JSValueToNumber(ctx, arguments[3 -1], exception); self->setCapsule(start,end,radius); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_AddCapsule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 3)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3); pdg::Point start;
            auto start_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], start, exception);
            if (!start_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*start_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            }; pdg::Point end;
            auto end_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], end, exception);
            if (!end_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*end_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
            }; if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""radius"")");
            double radius = JSValueToNumber(ctx, arguments[3 -1], exception); return JSValueMakeNumber(ctx, self->addCapsule(start,end,radius));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetCapsuleStart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned shape ID" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto result=self->getCapsuleStart(uint32_t(value)); return JSC_PointToValue(ctx, result, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetCapsuleEnd(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned shape ID" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto result=self->getCapsuleEnd(uint32_t(value)); return JSC_PointToValue(ctx, result, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetCapsuleRadius(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned shape ID" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            return JSValueMakeNumber(ctx, self->getCapsuleRadius(uint32_t(value)));
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_SetBox(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Rect bounds;
            auto bounds_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], bounds, exception);
            if (!bounds_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*bounds_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
            };
            self->setBox(bounds); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_AddBox(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Rect bounds;
            auto bounds_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], bounds, exception);
            if (!bounds_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*bounds_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
            };
            return JSValueMakeNumber(ctx, self->addBox(bounds));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_ClearShapes(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->clearShapes(); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_UseOwnerPhysics(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->useOwnerPhysics(); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_SetPhysicsBody(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if(!COLLISION_ARGUMENT_IS(arguments[0],true))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a PhysicsBody" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } PhysicsBody* body = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef body_ = JSValueToObject(ctx, arguments[1 -1], exception);
                body = PhysicsBody_getCppObject(body_);
            }
            if (!body)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""body"")"); self->setPhysicsBody(*body); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto bounds=self->getBounds(); return JSC_RectToValue(ctx, bounds, exception);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_Contains(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Point point;
            auto point_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], point, exception);
            if (!point_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*point_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            return JSValueMakeBoolean(ctx, self->contains(point));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_Overlaps(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if(!COLLISION_ARGUMENT_IS(arguments[0],false))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Collider" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } Collider* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = Collider_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Collider"" (""other"")"); return JSValueMakeBoolean(ctx, self->overlaps(*other));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_RemoveShape(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
            double id = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(id)||id<0||id>4294967295.0||id!=std::floor(id))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned 32-bit integer" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            return JSValueMakeBoolean(ctx, self->removeShape(uint32_t(id)));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetShapeId(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
            double id = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(id)||id<0||id>4294967295.0||id!=std::floor(id))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned 32-bit integer" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            return JSValueMakeNumber(ctx, self->getShapeId(uint32_t(id)));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetContactError(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSC_MakeValueFromCString(ctx, self->getContactError().c_str());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_AddPolygon(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); std::vector<Point> points;
#ifdef PDG_USING_JAVASCRIPT_CORE
            if(!JSValueIsArray(ctx,arguments[0]))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected an array of Points" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto array=JSValueToObject(ctx, arguments[0], exception); auto lengthName=JSStringCreateWithUTF8CString("length");
            auto lengthValue=JSObjectGetProperty(ctx,array,lengthName,exception);JSStringRelease(lengthName);
            const double length=JSValueToNumber(ctx, lengthValue, exception);
            if(length<3||length>4096)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected 3 to 4096 vertices" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            for(unsigned i=0;i<unsigned(length);++i)
            {
                auto value=JSObjectGetPropertyAtIndex(ctx,array,i,exception); Point point; auto isPoint = JSC_ValueIsPoint(ctx, value, point, exception); if (!isPoint.has_value())
                {
                    return JSValueMakeNull(ctx);
                }
                if (!*isPoint)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Point vertex" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                points.push_back(point);
            }
#else
            if(!arguments[0]->IsArray())
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected an array of Points" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto array=arguments[0].As<v8::Array>();
            if(array->Length()<3||array->Length()>4096)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected 3 to 4096 vertices" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            for(unsigned i=0;i<array->Length();++i)
            {
                v8::Local<v8::Value> value; if(!array->Get(isolate->GetCurrentContext(),i).ToLocal(&value)) return; Point point; auto isPoint = JSC_ValueIsPoint(ctx, value, point, exception); if (!isPoint.has_value())
                {
                    return JSValueMakeNull(ctx);
                }
                if (!*isPoint)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Point vertex" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                points.push_back(point);
            }
#endif
            return JSValueMakeNumber(ctx, self->addPolygon(points));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_SetPolygon(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); std::vector<Point> points;
#ifdef PDG_USING_JAVASCRIPT_CORE
            if(!JSValueIsArray(ctx,arguments[0]))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected an array of Points" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto array=JSValueToObject(ctx, arguments[0], exception); auto lengthName=JSStringCreateWithUTF8CString("length");
            auto lengthValue=JSObjectGetProperty(ctx,array,lengthName,exception);JSStringRelease(lengthName);
            const double length=JSValueToNumber(ctx, lengthValue, exception);
            if(length<3||length>4096)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected 3 to 4096 vertices" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            for(unsigned i=0;i<unsigned(length);++i)
            {
                auto value=JSObjectGetPropertyAtIndex(ctx,array,i,exception); Point point; auto isPoint = JSC_ValueIsPoint(ctx, value, point, exception); if (!isPoint.has_value())
                {
                    return JSValueMakeNull(ctx);
                }
                if (!*isPoint)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Point vertex" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                points.push_back(point);
            }
#else
            if(!arguments[0]->IsArray())
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected an array of Points" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            auto array=arguments[0].As<v8::Array>();
            if(array->Length()<3||array->Length()>4096)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected 3 to 4096 vertices" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            for(unsigned i=0;i<array->Length();++i)
            {
                v8::Local<v8::Value> value; if(!array->Get(isolate->GetCurrentContext(),i).ToLocal(&value)) return; Point point; auto isPoint = JSC_ValueIsPoint(ctx, value, point, exception); if (!isPoint.has_value())
                {
                    return JSValueMakeNull(ctx);
                }
                if (!*isPoint)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a Point vertex" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                points.push_back(point);
            }
#endif
            self->setPolygon(points); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    static JSStringRef symbol_collider = 0; static JSStringRef symbol_other = 0; static JSStringRef symbol_shape = 0; static JSStringRef symbol_otherShape = 0;
    static JSStringRef symbol_phase = 0; static JSStringRef symbol_penetration = 0; static JSStringRef symbol_point = 0; static JSStringRef symbol_normal = 0;
    static JSStringRef symbol_impulse = 0; static JSStringRef symbol_sensor = 0;
    struct ColliderScriptCallback
    {
#ifdef PDG_USING_JAVASCRIPT_CORE
        JSGlobalContextRef context;
        JSObjectRef function;
        ColliderScriptCallback(JSContextRef ctx, JSObjectRef callback)
            : context(JSGlobalContextRetain(JSContextGetGlobalContext(ctx))),function(callback) { JSValueProtect(context,function); }
        ~ColliderScriptCallback() { JSValueUnprotect(context,function);JSGlobalContextRelease(context); }
#else
        v8::Isolate* isolate;
        v8::Global<v8::Context> context;
        v8::Global<v8::Function> function;
        ColliderScriptCallback(v8::Isolate* engine,v8::Local<v8::Function> callback)
            : isolate(engine),context(engine,engine->GetCurrentContext()),function(engine,callback) {}
#endif
        bool invoke(const Collider& a,const Collider& b,const ColliderContact* contact)
        {
#ifdef PDG_USING_JAVASCRIPT_CORE
            JSContextRef ctx=context;JSValueRef error=nullptr;JSValueRef* exception=&error;
            auto object=[&](const Collider& value) { auto* c=const_cast<Collider*>(&value);return c->mColliderScriptObj?c->mColliderScriptObj:Collider_newFromCpp(ctx,c); };
            auto event=JSObjectMake(ctx,nullptr,nullptr);
#else
            v8::HandleScope handles(isolate);auto ctx=context.Get(isolate);v8::Context::Scope scope(ctx);v8::TryCatch catcher(isolate);
            auto object=[&](const Collider& value) { auto* c=const_cast<Collider*>(&value);return c->mColliderScriptObj.IsEmpty()?ColliderWrap::NewFromCpp(isolate,c):v8::Local<v8::Object>::New(isolate,c->mColliderScriptObj); };
            auto event=v8::Object::New(isolate);
#endif
            JSValueRef argv[2]={object(a),object(b)};
            if(contact)
            {
                Point point=contact->point;Vector normal=contact->normal,impulse=contact->impulse;
                JSObjectSetProperty(ctx, event, ((symbol_collider) ? symbol_collider : symbol_collider = JSStringCreateWithUTF8CString("collider")), argv[0], kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, event, ((symbol_other) ? symbol_other : symbol_other = JSStringCreateWithUTF8CString("other")), argv[1], kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, event, ((symbol_shape) ? symbol_shape : symbol_shape = JSStringCreateWithUTF8CString("shape")), JSValueMakeNumber(ctx, contact->shape), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, event, ((symbol_otherShape) ? symbol_otherShape : symbol_otherShape = JSStringCreateWithUTF8CString("otherShape")), JSValueMakeNumber(ctx, contact->otherShape), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, event, ((symbol_phase) ? symbol_phase : symbol_phase = JSStringCreateWithUTF8CString("phase")), JSValueMakeNumber(ctx, contact->phase), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, event, ((symbol_penetration) ? symbol_penetration : symbol_penetration = JSStringCreateWithUTF8CString("penetration")), JSValueMakeNumber(ctx, contact->penetration), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, event, ((symbol_point) ? symbol_point : symbol_point = JSStringCreateWithUTF8CString("point")), JSC_PointToValue(ctx, point, exception), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, event, ((symbol_normal) ? symbol_normal : symbol_normal = JSStringCreateWithUTF8CString("normal")), JSC_VectorToValue(ctx, normal, exception), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, event, ((symbol_impulse) ? symbol_impulse : symbol_impulse = JSStringCreateWithUTF8CString("impulse")), JSC_VectorToValue(ctx, impulse, exception), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, event, ((symbol_sensor) ? symbol_sensor : symbol_sensor = JSStringCreateWithUTF8CString("sensor")), JSValueMakeBoolean(ctx, contact->sensor), kJSPropertyAttributeNone, exception);
                argv[0]=event;
            }
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto result=JSObjectCallAsFunction(ctx,function,nullptr,contact?1:2,argv,exception);
            if(error) throw std::runtime_error("Collider callback failed");
            if(!contact&&!JSValueIsBoolean(ctx,result)) throw std::runtime_error("Collision filter must return a boolean");
            return contact || JSValueToBoolean(ctx,result);
#else
            v8::Local<v8::Value> result;
            if(!function.Get(isolate)->Call(ctx,v8::Undefined(isolate),contact?1:2,argv).ToLocal(&result))
            {
                v8::String::Utf8Value message(isolate,catcher.Exception());
                throw std::runtime_error(*message?*message:"Collider callback failed");
            }
            if(!contact&&!result->IsBoolean()) throw std::runtime_error("Collision filter must return a boolean");
            return contact || result->BooleanValue(isolate);
#endif
        }
    };
    JSValueRef Collider_SetContactHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if(JSValueIsNull(ctx, arguments[0]))
            {
                self->setContactHandler(
                {
                }
                ); return thisObject;
            }
            JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!func || !JSObjectIsFunction(ctx, func) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto callback=std::make_shared<ColliderScriptCallback>(ctx,func);
#else
            auto callback=std::make_shared<ColliderScriptCallback>(isolate,func);
#endif
            self->setContactHandler([callback](const ColliderContact& c) { callback->invoke(*c.collider,*c.other,&c); }
            ); return thisObject;
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_SetCollisionFilter(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if(JSValueIsNull(ctx, arguments[0]))
            {
                self->setCollisionFilter(
                {
                }
                ); return thisObject;
            }
            JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!func || !JSObjectIsFunction(ctx, func) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto callback=std::make_shared<ColliderScriptCallback>(ctx,func);
#else
            auto callback=std::make_shared<ColliderScriptCallback>(isolate,func);
#endif
            self->setCollisionFilter([callback](const Collider& a,const Collider& b) { return callback->invoke(a,b,nullptr); }
            ); return thisObject;
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetGeometrySource(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getGeometrySource());
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_IsSourceShape(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned shape ID" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const auto id=uint32_t(value); return JSValueMakeBoolean(ctx, self->isSourceShape(id));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetShapeName(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned shape ID" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const auto id=uint32_t(value); auto name=self->getShapeName(id); return JSC_MakeValueFromCString(ctx, name.c_str());
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetShapeType(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned shape ID" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const auto id=uint32_t(value); return JSValueMakeNumber(ctx, self->getShapeType(id));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetCircleRadius(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an unsigned shape ID" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const auto id=uint32_t(value); return JSValueMakeNumber(ctx, self->getCircleRadius(id));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_SetImageMask(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true); Image* image = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef image_ = JSValueToObject(ctx, arguments[1 -1], exception);
                image = Image_getCppObject(image_);
            }
            if (!image)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Image"" (""image"")"); pdg::Rect bounds;
            auto bounds_isRect = JSC_ValueIsRect(ctx, arguments[2 -1], bounds, exception);
            if (!bounds_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*bounds_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Rect", arguments[2 -1]);
            }; if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""threshold"")");
            double threshold = (argumentCount<3) ? 128 : JSValueToNumber(ctx, arguments[3 -1], exception); if(!std::isfinite(threshold)||threshold<1||threshold>255||std::floor(threshold)!=threshold)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer alpha threshold from 1 to 255" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->setImageMask(*image,bounds,threshold); return thisObject;
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_AddImageMask(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true); Image* image = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef image_ = JSValueToObject(ctx, arguments[1 -1], exception);
                image = Image_getCppObject(image_);
            }
            if (!image)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Image"" (""image"")"); pdg::Rect bounds;
            auto bounds_isRect = JSC_ValueIsRect(ctx, arguments[2 -1], bounds, exception);
            if (!bounds_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*bounds_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Rect", arguments[2 -1]);
            }; if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""threshold"")");
            double threshold = (argumentCount<3) ? 128 : JSValueToNumber(ctx, arguments[3 -1], exception); if(!std::isfinite(threshold)||threshold<1||threshold>255||std::floor(threshold)!=threshold)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer alpha threshold from 1 to 255" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            return JSValueMakeNumber(ctx, self->addImageMask(*image,bounds,threshold));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Collider_SetWantsContactEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""wanted"")");
        bool wanted = JSValueToBoolean(ctx, arguments[1 -1]); self->setWantsContactEvents(wanted); return thisObject;
    }
    JSValueRef Collider_GetWantsContactEvents(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->getWantsContactEvents());
    }
    JSValueRef Collider_SetFriction(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); self->setFriction(value); return thisObject;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_SetRestitution(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); self->setRestitution(value); return thisObject;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetFriction(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getFriction());
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_GetRestitution(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getRestitution());
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Collider_UseBodyMaterial(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Collider* self = static_cast<Collider*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->useBodyMaterial(); return thisObject;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

}
