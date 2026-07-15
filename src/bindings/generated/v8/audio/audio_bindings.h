// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/audio/audio_bindings.h
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



#ifndef PDG_AUDIO_BINDINGS_H_INCLUDED
#define PDG_AUDIO_BINDINGS_H_INCLUDED

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

#ifndef PDG_NO_SOUND
    Sound* New_Sound(const v8::FunctionCallbackInfo<v8::Value>& args);

    class SoundWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Sound* getCppObject() { return cppPtr_; }
        protected:
            Sound* cppPtr_;

            SoundWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~SoundWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Sound* cppObj);
            SoundWrap(Sound* obj) : cppPtr_(obj) {}

            static void AddHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Clear (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BlockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UnblockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetVolume (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetVolume (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Play (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Start (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Stop (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Pause (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Resume (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsPaused (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLooping (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsLooping (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetPitch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangePitch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetOffsetX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeOffsetX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FadeOut (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FadeIn (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeVolume (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Skip (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SkipTo (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    SoundManager* New_SoundManager(const v8::FunctionCallbackInfo<v8::Value>& args);

    class SoundManagerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            SoundManager* getCppObject() { return cppPtr_; }
        protected:
            SoundManager* cppPtr_;

            SoundManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~SoundManagerWrap();

        public:
            static SoundManager* getSingletonInstance();
        public:
            static v8::Local<v8::Object> GetScriptSingletonInstance(v8::Isolate* isolate);
        protected:
            static v8::Persistent<v8::Object> instance_;
            static bool instanced_;

            static void SetVolume (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMute (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Idle (const v8::FunctionCallbackInfo<v8::Value>& args);
    };
#endif
#endif

}
