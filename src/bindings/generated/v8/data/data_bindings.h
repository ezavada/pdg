// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/data_bindings.h
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

    MemBlock* New_MemBlock(const v8::FunctionCallbackInfo<v8::Value>& args);

    class MemBlockWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            MemBlock* getCppObject() { return cppPtr_; }
        protected:
            MemBlock* cppPtr_;

            MemBlockWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~MemBlockWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, MemBlock* cppObj);
            MemBlockWrap(MemBlock* obj) : cppPtr_(obj) {}

            static void GetData (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetDataSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetByte (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBytes (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    ResourceManager* New_ResourceManager(const v8::FunctionCallbackInfo<v8::Value>& args);

    class ResourceManagerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            ResourceManager* getCppObject() { return cppPtr_; }
        protected:
            ResourceManager* cppPtr_;

            ResourceManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~ResourceManagerWrap();

        public:
            static ResourceManager* getSingletonInstance();
        public:
            static v8::Local<v8::Object> GetScriptSingletonInstance(v8::Isolate* isolate);
        protected:
            static v8::Persistent<v8::Object> instance_;
            static bool instanced_;

            static void GetLanguage (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLanguage (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OpenResourceFile (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CloseResourceFile (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetImage (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetImageStrip (const v8::FunctionCallbackInfo<v8::Value>& args);
#ifndef PDG_NO_SOUND
            static void GetSound (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
            static void GetString (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetResourceSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetResource (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetResourcePaths (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    class FileManagerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;

            FileManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~FileManagerWrap();

        public:
            static v8::Local<v8::Object> GetScriptSingletonInstance(v8::Isolate* isolate);
        protected:
            static v8::Persistent<v8::Object> instance_;
            static bool instanced_;

            static void FindFirst (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FindNext (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FindClose (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetApplicationDataDirectory (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetApplicationDirectory (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetApplicationResourceDirectory (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    Serializer* New_Serializer(const v8::FunctionCallbackInfo<v8::Value>& args);

    class SerializerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Serializer* getCppObject() { return cppPtr_; }
        protected:
            Serializer* cppPtr_;

            SerializerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~SerializerWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Serializer* cppObj);
            SerializerWrap(Serializer* obj) : cppPtr_(obj) {}

#ifndef PDG_NO_64BIT
            static void Serialize_8 (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_8u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_8 (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_8u (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
            static void Serialize_d (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_f (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_4 (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_4u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_3u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_2 (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_2u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_1 (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_1u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_bool (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_uint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_color (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_offset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_point (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_vector (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_rect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_rotr (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_quad (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_str (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_mem (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_obj (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize_ref (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SerializedSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_d (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_f (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_4 (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_4u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_3u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_2 (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_2u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_1 (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_1u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_bool (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_uint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_color (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_offset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_point (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_vector (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_rect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_rotr (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_quad (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_str (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_mem (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_obj (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Sizeof_ref (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetDataSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetDataPtr (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    Deserializer* New_Deserializer(const v8::FunctionCallbackInfo<v8::Value>& args);

    class DeserializerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Deserializer* getCppObject() { return cppPtr_; }
        protected:
            Deserializer* cppPtr_;

            DeserializerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~DeserializerWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Deserializer* cppObj);
            DeserializerWrap(Deserializer* obj) : cppPtr_(obj) {}

#ifndef PDG_NO_64BIT
            static void Deserialize_8 (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_8u (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
            static void Deserialize_d (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_f (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_4 (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_4u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_3u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_2 (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_2u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_1 (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_1u (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_bool (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_uint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_color (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_offset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_point (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_vector (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_rect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_rotr (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_quad (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_str (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_strGetLen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_mem (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_memGetLen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_obj (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize_ref (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetDataPtr (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    ISerializable* New_ISerializable(const v8::FunctionCallbackInfo<v8::Value>& args);

    class ISerializableWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            ISerializable* getCppObject() { return cppPtr_; }
        protected:
            ISerializable* cppPtr_;

            ISerializableWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~ISerializableWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, ISerializable* cppObj);
            ISerializableWrap(ISerializable* obj) : cppPtr_(obj) {}

    };
#endif

}
