// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/data_bindings.h
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



#ifndef PDG_DATA_BINDINGS_H_INCLUDED
#define PDG_DATA_BINDINGS_H_INCLUDED

#include "pdg_project.h"

#include "pdg_script_impl.h"
#include "pdg_script.h"

#ifndef PDG_NO_APP_FRAMEWORK
#define PDG_NO_APP_FRAMEWORK
#endif
#include "pdg/framework.h"

#include <cstdlib>

namespace pdg
{

    extern MemBlock* New_MemBlock(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef MemBlock_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef MemBlock_class();
    extern JSObjectRef MemBlock_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline MemBlock* MemBlock_getCppObject(JSObjectRef obj)
    {
        return static_cast<MemBlock*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef MemBlock_newFromCpp(JSContextRef, MemBlock*);

    extern JSValueRef MemBlock_GetData(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef MemBlock_GetDataSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef MemBlock_GetByte(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef MemBlock_GetBytes(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern ResourceManager* New_ResourceManager(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef ResourceManager_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef ResourceManager_class();
    extern JSObjectRef ResourceManager_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline ResourceManager* ResourceManager_getCppObject(JSObjectRef obj)
    {
        return static_cast<ResourceManager*>(JSObjectGetPrivate(obj));
    }
    extern ResourceManager* ResourceManager_getSingletonInstance();
    extern JSObjectRef ResourceManager_getScriptSingletonInstance();

    extern JSValueRef ResourceManager_GetLanguage(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ResourceManager_SetLanguage(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ResourceManager_OpenResourceFile(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ResourceManager_CloseResourceFile(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ResourceManager_GetImage(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ResourceManager_GetImageStrip(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#ifndef PDG_NO_SOUND
    extern JSValueRef ResourceManager_GetSound(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
    extern JSValueRef ResourceManager_GetString(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ResourceManager_GetResourceSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ResourceManager_GetResource(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ResourceManager_GetResourcePaths(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef FileManager_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef FileManager_class();
    extern JSObjectRef FileManager_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSObjectRef FileManager_getScriptSingletonInstance();
    extern JSValueRef FileManager_FindFirst(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef FileManager_FindNext(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef FileManager_FindClose(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef FileManager_GetApplicationDataDirectory(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef FileManager_GetApplicationDirectory(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef FileManager_GetApplicationResourceDirectory(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern Serializer* New_Serializer(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Serializer_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Serializer_class();
    extern JSObjectRef Serializer_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Serializer* Serializer_getCppObject(JSObjectRef obj)
    {
        return static_cast<Serializer*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Serializer_newFromCpp(JSContextRef, Serializer*);

    extern JSValueRef Serializer_SetResourceMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_GetResourceMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_8(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_8u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_8(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_8u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_d(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_f(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_4(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_4u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_3u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_2(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_2u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_1(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_1u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_bool(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_uint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_color(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_offset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_point(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_vector(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_rect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_rotr(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_quad(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_str(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_mem(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_obj(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Serialize_ref(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_SerializedSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_d(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_f(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_4(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_4u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_3u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_2(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_2u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_1(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_1u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_bool(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_uint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_color(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_offset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_point(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_vector(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_rect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_rotr(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_quad(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_str(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_mem(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_obj(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_Sizeof_ref(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_GetDataSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Serializer_GetDataPtr(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern Deserializer* New_Deserializer(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Deserializer_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Deserializer_class();
    extern JSObjectRef Deserializer_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Deserializer* Deserializer_getCppObject(JSObjectRef obj)
    {
        return static_cast<Deserializer*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Deserializer_newFromCpp(JSContextRef, Deserializer*);

    extern JSValueRef Deserializer_Deserialize_8(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_8u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_d(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_f(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_4(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_4u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_3u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_2(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_2u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_1(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_1u(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_bool(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_uint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_color(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_offset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_point(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_vector(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_rect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_rotr(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_quad(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_str(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_strGetLen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_mem(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_memGetLen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_obj(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_Deserialize_ref(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Deserializer_SetDataPtr(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern ISerializable* New_ISerializable(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef ISerializable_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef ISerializable_class();
    extern JSObjectRef ISerializable_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline ISerializable* ISerializable_getCppObject(JSObjectRef obj)
    {
        return static_cast<ISerializable*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef ISerializable_newFromCpp(JSContextRef, ISerializable*);
#endif

}
