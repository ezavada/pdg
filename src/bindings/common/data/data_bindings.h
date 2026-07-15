// -----------------------------------------------
// data_bindings.h
//
// Header file that contains data-related interface declarations
// for pdg classes that are exposed to scripting languages
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

// Include the interface declarations for data classes

#ifdef PDG_GENERATING_DOCS
#include "../../tools/js_docs_macros.h"
namespace pdg {
#else

#undef THIS // eliminate warning about Windows duplicate Macro
#include "pdg_script_macros.h"

%#ifndef PDG_DATA_BINDINGS_H_INCLUDED
%#define PDG_DATA_BINDINGS_H_INCLUDED

%#include "pdg_project.h"

%#include "pdg_script_impl.h"
%#include "pdg_script.h"

%#ifndef PDG_NO_APP_FRAMEWORK
%#define PDG_NO_APP_FRAMEWORK
%#endif
%#include "pdg/framework.h"

%#include <cstdlib>

namespace pdg {

#endif //!PDG_GENERATING_DOCS

BINDING_CLASS(MemBlock)
  METHOD(MemBlock, GetData)
  METHOD(MemBlock, GetDataSize)
  METHOD(MemBlock, GetByte)
  METHOD(MemBlock, GetBytes)
DECL_END

SINGLETON_CLASS(ResourceManager)
  PROPERTY(ResourceManager, Language)
  METHOD(ResourceManager, OpenResourceFile)
  METHOD(ResourceManager, CloseResourceFile)
  METHOD(ResourceManager, GetImage)
  METHOD(ResourceManager, GetImageStrip)
%#ifndef PDG_NO_SOUND
  METHOD(ResourceManager, GetSound)
%#endif // !PDG_NO_SOUND
  METHOD(ResourceManager, GetString)
  METHOD(ResourceManager, GetResourceSize)
  METHOD(ResourceManager, GetResource)
  METHOD(ResourceManager, GetResourcePaths)
DECL_END

FACADE_CLASS(FileManager)
  METHOD(FileManager, FindFirst)
  METHOD(FileManager, FindNext)
  METHOD(FileManager, FindClose)
  METHOD(FileManager, GetApplicationDataDirectory)
  METHOD(FileManager, GetApplicationDirectory)
  METHOD(FileManager, GetApplicationResourceDirectory)
DECL_END


BINDING_CLASS(Serializer)
%#ifndef PDG_NO_64BIT
   METHOD(Serializer, Serialize_8)   // no 64 bit int in Javascript
   METHOD(Serializer, Serialize_8u)
   METHOD(Serializer, Sizeof_8)
   METHOD(Serializer, Sizeof_8u)
%#endif
  METHOD(Serializer, Serialize_d)
  METHOD(Serializer, Serialize_f)
  METHOD(Serializer, Serialize_4)
  METHOD(Serializer, Serialize_4u)
  METHOD(Serializer, Serialize_3u)
  METHOD(Serializer, Serialize_2)
  METHOD(Serializer, Serialize_2u)
  METHOD(Serializer, Serialize_1)
  METHOD(Serializer, Serialize_1u)
  METHOD(Serializer, Serialize_bool)
  METHOD(Serializer, Serialize_uint)
  METHOD(Serializer, Serialize_color)
  METHOD(Serializer, Serialize_offset)
  METHOD(Serializer, Serialize_point)
  METHOD(Serializer, Serialize_vector)
  METHOD(Serializer, Serialize_rect)
  METHOD(Serializer, Serialize_rotr)
  METHOD(Serializer, Serialize_quad)
  METHOD(Serializer, Serialize_str)
  METHOD(Serializer, Serialize_mem)
  METHOD(Serializer, Serialize_obj)
  METHOD(Serializer, Serialize_ref)
  METHOD(Serializer, SerializedSize)
  METHOD(Serializer, Sizeof_d)
  METHOD(Serializer, Sizeof_f)
  METHOD(Serializer, Sizeof_4)
  METHOD(Serializer, Sizeof_4u)
  METHOD(Serializer, Sizeof_3u)
  METHOD(Serializer, Sizeof_2)
  METHOD(Serializer, Sizeof_2u)
  METHOD(Serializer, Sizeof_1)
  METHOD(Serializer, Sizeof_1u)
  METHOD(Serializer, Sizeof_bool)
  METHOD(Serializer, Sizeof_uint)
  METHOD(Serializer, Sizeof_color)
  METHOD(Serializer, Sizeof_offset)
  METHOD(Serializer, Sizeof_point)
  METHOD(Serializer, Sizeof_vector)
  METHOD(Serializer, Sizeof_rect)
  METHOD(Serializer, Sizeof_rotr)
  METHOD(Serializer, Sizeof_quad)
  METHOD(Serializer, Sizeof_str)
  METHOD(Serializer, Sizeof_mem)
  METHOD(Serializer, Sizeof_obj)
  METHOD(Serializer, Sizeof_ref)
  METHOD(Serializer, GetDataSize)
  METHOD(Serializer, GetDataPtr)
DECL_END

BINDING_CLASS(Deserializer)
%#ifndef PDG_NO_64BIT
   METHOD(Deserializer, Deserialize_8)
   METHOD(Deserializer, Deserialize_8u)
%#endif
  METHOD(Deserializer, Deserialize_d)
  METHOD(Deserializer, Deserialize_f)
  METHOD(Deserializer, Deserialize_4)
  METHOD(Deserializer, Deserialize_4u)
  METHOD(Deserializer, Deserialize_3u)
  METHOD(Deserializer, Deserialize_2)
  METHOD(Deserializer, Deserialize_2u)
  METHOD(Deserializer, Deserialize_1)
  METHOD(Deserializer, Deserialize_1u)
  METHOD(Deserializer, Deserialize_bool)
  METHOD(Deserializer, Deserialize_uint)
  METHOD(Deserializer, Deserialize_color)
  METHOD(Deserializer, Deserialize_offset)
  METHOD(Deserializer, Deserialize_point)
  METHOD(Deserializer, Deserialize_vector)
  METHOD(Deserializer, Deserialize_rect)
  METHOD(Deserializer, Deserialize_rotr)
  METHOD(Deserializer, Deserialize_quad)
  METHOD(Deserializer, Deserialize_str)
  METHOD(Deserializer, Deserialize_strGetLen)
  METHOD(Deserializer, Deserialize_mem)
  METHOD(Deserializer, Deserialize_memGetLen)
  METHOD(Deserializer, Deserialize_obj)
  METHOD(Deserializer, Deserialize_ref)
  METHOD(Deserializer, SetDataPtr)
DECL_END

BINDING_CLASS(ISerializable)
DECL_END


%#endif // PDG_DATA_BINDINGS_H_INCLUDED 

} // namespace pdg
