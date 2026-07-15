// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/pdg_script_interface.h
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



#ifndef PDG_INTERFACES_H_INCLUDED
#define PDG_INTERFACES_H_INCLUDED

#include "pdg_project.h"

#include "pdg_script_impl.h"
#include "pdg_script.h"

#ifndef PDG_NO_APP_FRAMEWORK
#define PDG_NO_APP_FRAMEWORK
#endif
#include "pdg/framework.h"

#include <cstdlib>

#include "physics/physics_bindings.h"
#include "core/core_bindings.h"
#include "data/data_bindings.h"
#include "graphics/graphics_bindings.h"
#include "audio/audio_bindings.h"
#include "animation/animation_bindings.h"

namespace pdg
{

#ifndef PDG_NO_GUI
#endif

    extern void GetConfigManager(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void GetLogManager(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void GetEventManager(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void GetResourceManager(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void SetSerializationDebugMode(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void RegisterSerializableClass(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void RegisterSerializableObject(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void GetGraphicsManager(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void GetSoundManager(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void GetFileManager(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void GetTimerManager(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void CreateSpriteLayer(const v8::FunctionCallbackInfo<v8::Value>& args);
#ifdef PDG_SPRITER_SUPPORT
    extern void CreateSpriteLayerFromSpriterFile(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
    extern void CleanupLayer(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void CreateTileLayer(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void CreateDrawing(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void Rand(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void GameCriticalRandom(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void Srand(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void RegisterEasingFunction(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void Idle(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void Run(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void Quit(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void IsQuitting(const v8::FunctionCallbackInfo<v8::Value>& args);
    extern void FinishedScriptSetup(const v8::FunctionCallbackInfo<v8::Value>& args);

}
#endif
