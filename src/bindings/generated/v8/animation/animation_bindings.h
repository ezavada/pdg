// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/animation_bindings.h
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



#ifndef PDG_NO_GUI
#endif

#ifndef PDG_ANIMATION_BINDINGS_H_INCLUDED
#define PDG_ANIMATION_BINDINGS_H_INCLUDED

#include "pdg_project.h"

#include "pdg_script_impl.h"
#include "pdg_script_interface.h"

#ifndef PDG_NO_APP_FRAMEWORK
#define PDG_NO_APP_FRAMEWORK
#endif
#include "pdg/framework.h"

#include <cstdlib>

namespace pdg
{

    IAnimationHelper* New_IAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args);

    class IAnimationHelperWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::FunctionTemplate> GetTemplate(v8::Isolate* isolate) { return v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_); }
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            IAnimationHelper* getCppObject() { return cppPtr_; }
        protected:
            IAnimationHelper* cppPtr_;

            IAnimationHelperWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~IAnimationHelperWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, IAnimationHelper* cppObj);
            IAnimationHelperWrap(IAnimationHelper* obj) : cppPtr_(obj) {}

    };

    AnimatedBase* New_AnimatedBase(const v8::FunctionCallbackInfo<v8::Value>& args);

    class AnimatedBaseWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::FunctionTemplate> GetTemplate(v8::Isolate* isolate) { return v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_); }
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            AnimatedBase* getCppObject() { return cppPtr_; }
        protected:
            AnimatedBase* cppPtr_;

            AnimatedBaseWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~AnimatedBaseWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, AnimatedBase* cppObj);
            AnimatedBaseWrap(AnimatedBase* obj) : cppPtr_(obj) {}

            static void GetBoundingBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotatedBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Grow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Stretch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopSpinning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PauseSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResumeSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CancelSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AndThen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsSchedulePaused (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasScheduledAnimations (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Wait (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationHelpers (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Animate (const v8::FunctionCallbackInfo<v8::Value>& args);

    };

    Particle* New_Particle(const v8::FunctionCallbackInfo<v8::Value>& args);

    class ParticleWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::FunctionTemplate> GetTemplate(v8::Isolate* isolate) { return v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_); }
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Particle* getCppObject() { return cppPtr_; }
        protected:
            Particle* cppPtr_;

            ParticleWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~ParticleWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Particle* cppObj);
            ParticleWrap(Particle* obj) : cppPtr_(obj) {}

            static void GetBoundingBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotatedBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Grow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Stretch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopSpinning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PauseSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResumeSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CancelSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AndThen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsSchedulePaused (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasScheduledAnimations (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Wait (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationHelpers (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Clear (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BlockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UnblockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ReadPhysics (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupPhysicsBody (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemovePhysicsBody (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ReadCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupParticleEmitter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetParticleEmitter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveParticleEmitter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearContent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasContent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetOpacity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetOpacity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FadeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLifetime (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLifetime (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAge (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsAlive (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Expire (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Animate (const v8::FunctionCallbackInfo<v8::Value>& args);
#ifndef PDG_NO_GUI
            static void SetImage (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetDrawing (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
    };

    ParticleEmitter* New_ParticleEmitter(const v8::FunctionCallbackInfo<v8::Value>& args);

    class ParticleEmitterWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::FunctionTemplate> GetTemplate(v8::Isolate* isolate) { return v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_); }
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            ParticleEmitter* getCppObject() { return cppPtr_; }
        protected:
            ParticleEmitter* cppPtr_;

            ParticleEmitterWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~ParticleEmitterWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, ParticleEmitter* cppObj);
            ParticleEmitterWrap(ParticleEmitter* obj) : cppPtr_(obj) {}

            static void GetBoundingBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotatedBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Grow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Stretch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopSpinning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PauseSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResumeSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CancelSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AndThen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsSchedulePaused (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasScheduledAnimations (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Wait (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationHelpers (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetParticleTemplate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasParticleTemplate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetEmissionRate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetEmissionRate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetParticleSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMinParticleSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMaxParticleSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpread (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpread (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetVelocityInheritance (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetVelocityInheritance (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartEmitting (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopEmitting (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsEmitting (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Emit (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetParticle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Animate (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    Collider* New_Collider(const v8::FunctionCallbackInfo<v8::Value>& args);

    class ColliderWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::FunctionTemplate> GetTemplate(v8::Isolate* isolate) { return v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_); }
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Collider* getCppObject() { return cppPtr_; }
        protected:
            Collider* cppPtr_;

            ColliderWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~ColliderWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Collider* cppObj);
            ColliderWrap(Collider* obj) : cppPtr_(obj) {}

            static void SetFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRestitution (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRestitution (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UseBodyMaterial (const v8::FunctionCallbackInfo<v8::Value>& args);

            static void SetWantsContactEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWantsContactEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsPresent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsAttached (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsEnabled (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsSensor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetId (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCategory (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCollisionMask (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGroup (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetShapeCount (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetEnabled (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSensor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCategory (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCollisionMask (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGroup (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPhysicsBody (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCircle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddCircle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCapsule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddCapsule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCapsuleStart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCapsuleEnd (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCapsuleRadius (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearShapes (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UseOwnerPhysics (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetPhysicsBody (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Contains (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Overlaps (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveShape (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetShapeId (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetContactError (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddPolygon (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetPolygon (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetImageMask (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddImageMask (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGeometrySource (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsSourceShape (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetShapeName (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetShapeType (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCircleRadius (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetContactHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCollisionFilter (const v8::FunctionCallbackInfo<v8::Value>& args);

    };

    PhysicsConstraint* New_PhysicsConstraint(const v8::FunctionCallbackInfo<v8::Value>& args);

    class PhysicsConstraintWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::FunctionTemplate> GetTemplate(v8::Isolate* isolate) { return v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_); }
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            PhysicsConstraint* getCppObject() { return cppPtr_; }
        protected:
            PhysicsConstraint* cppPtr_;

            PhysicsConstraintWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~PhysicsConstraintWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, PhysicsConstraint* cppObj);
            PhysicsConstraintWrap(PhysicsConstraint* obj) : cppPtr_(obj) {}

            static void IsActive (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsBroken (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCollideBodies (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetType (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMaxForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBreakForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetImpulse (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCollideBodies (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMaxForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetBreakForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBodyA (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBodyB (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnchorA (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnchorB (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAnchorA (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAnchorB (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAnchors (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGrooveStart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGrooveEnd (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGroove (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMinAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMaxAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAngleLimits (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Disconnect (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    PhysicsBody* New_PhysicsBody(const v8::FunctionCallbackInfo<v8::Value>& args);

    class PhysicsBodyWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::FunctionTemplate> GetTemplate(v8::Isolate* isolate) { return v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_); }
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            PhysicsBody* getCppObject() { return cppPtr_; }
        protected:
            PhysicsBody* cppPtr_;

            PhysicsBodyWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~PhysicsBodyWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, PhysicsBody* cppObj);
            PhysicsBodyWrap(PhysicsBody* obj) : cppPtr_(obj) {}

            static void GetConstraintCount (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreatePinJoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreatePivotJoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateSlideJoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateGrooveJoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateSpring (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateRotarySpring (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateRotaryLimit (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateRatchet (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateGear (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateMotor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetConstraint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Disconnect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetDriveTarget (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearDrive (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsDriveEnabled (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetDriveState (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMass (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMass (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMomentOfInertia (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMomentOfInertia (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLinearDamping (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLinearDamping (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAngularDamping (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAngularDamping (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRestitution (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRestitution (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetBreakAngularSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBreakAngularSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBreakAngularSpeedReference (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAngularVelocity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAngularVelocity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSolver (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAngularMomentum (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMovementDirectionInRadians (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsPresent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsAttached (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetState (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetVelocity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetVelocity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetVelocityInRadians (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Teleport (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyImpulse (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyAngularImpulse (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyTorque (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddContinuousForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddContinuousTorque (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopAllForces (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopMoving (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopSpinning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Step (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    Part* New_Part(const v8::FunctionCallbackInfo<v8::Value>& args);

    class PartWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::FunctionTemplate> GetTemplate(v8::Isolate* isolate) { return v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_); }
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Part* getCppObject() { return cppPtr_; }
        protected:
            Part* cppPtr_;

            PartWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~PartWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Part* cppObj);
            PartWrap(Part* obj) : cppPtr_(obj) {}

            static void ReadCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupFrameCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupAnimationCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ReadPhysics (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupPhysicsBody (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemovePhysicsBody (const v8::FunctionCallbackInfo<v8::Value>& args);

            static void GetBoundingBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotatedBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Grow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Stretch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopSpinning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PauseSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResumeSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CancelSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AndThen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsSchedulePaused (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasScheduledAnimations (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Wait (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationHelpers (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Animate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetId (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetName (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsAttached (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBoneId (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsBoundToBone (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BindToBone (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UnbindFromBone (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetParentPart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetParentPart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetTransform (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SolveIK (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetIKTarget (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearIKTarget (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasIKTarget (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsIKTargetReached (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetIKError (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetIKLimits (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearIKLimits (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasIKLimits (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetIKMinAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetIKMaxAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetIKDriveTarget (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsIKDriven (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AttachSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAttachedSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DetachSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAttachmentError (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BindToAnimationBinding (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BindToAnimationSocket (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationBindingName (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationSocketName (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearContent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasContent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetContentBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
#ifndef PDG_NO_GUI
            static void SetDrawing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetImage (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
    };

#ifndef PDG_NO_GUI
    ISpriteDrawHelper* New_ISpriteDrawHelper(const v8::FunctionCallbackInfo<v8::Value>& args);

    class ISpriteDrawHelperWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::FunctionTemplate> GetTemplate(v8::Isolate* isolate) { return v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_); }
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            ISpriteDrawHelper* getCppObject() { return cppPtr_; }
        protected:
            ISpriteDrawHelper* cppPtr_;

            ISpriteDrawHelperWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~ISpriteDrawHelperWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, ISpriteDrawHelper* cppObj);
            ISpriteDrawHelperWrap(ISpriteDrawHelper* obj) : cppPtr_(obj) {}

    };
#endif

    Sprite* New_Sprite(const v8::FunctionCallbackInfo<v8::Value>& args);

    class SpriteWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::FunctionTemplate> GetTemplate(v8::Isolate* isolate) { return v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_); }
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Sprite* getCppObject() { return cppPtr_; }
        protected:
            Sprite* cppPtr_;

            SpriteWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~SpriteWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Sprite* cppObj);
            SpriteWrap(Sprite* obj) : cppPtr_(obj) {}

            static void ReadCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ReadPhysics (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupPhysicsBody (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemovePhysicsBody (const v8::FunctionCallbackInfo<v8::Value>& args);

            static void GetAttachmentPart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupFrameCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupAnimationCollider (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFrameCollisionMask (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreatePart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void TransferPart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FindPart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPartCount (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPartNames (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemovePart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearParts (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Clear (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BlockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UnblockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBoundingBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotatedBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Grow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Stretch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopSpinning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PauseSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResumeSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CancelSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AndThen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsSchedulePaused (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasScheduledAnimations (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Wait (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationHelpers (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSerializedSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMyClassTag (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWantsAnimLoopEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWantsAnimLoopEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWantsAnimEndEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWantsAnimEndEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetOpacity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetOpacity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWantsCollideWallEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWantsCollideWallEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFrameRotatedBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFrame (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCurrentFrame (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFrameCount (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartFrameAnimation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopFrameAnimation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddFramesImage (const v8::FunctionCallbackInfo<v8::Value>& args);
#ifdef PDG_SPRITER_SUPPORT
            static void SeekAnimation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void TransitionToAnimation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsAnimationTransitioning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationTransitionProgress (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationIK (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAnimationIKTarget (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationIKResult (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationModifier (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAnimationModifier (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationModifiers (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationModifierError (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAnimationSource (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationSource (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsAnimationDrawingSupported (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAnimationDebugDraw (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationDebugDraw (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SupportsAnimationPhysics (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupAnimationPhysics (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetupPhysicsFromAnimationRig (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AttachAnimationPhysicsPart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DetachAnimationPhysicsPart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsAnimationPhysicsPartAttached (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAnimationPhysicsRoot (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationPhysicsRoot (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationPhysicsRoot (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationPhysicsSetupWarnings (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAnimationPhysicsMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationPhysicsMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAnimationPhysicsDriveSettings (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationPhysicsDriveSettings (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DisableAnimationPhysics (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsAnimationPhysicsEnabled (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationDrawable (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAnimationDrawable (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationDrawables (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAnimationDrawableEnabled (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationDrawableError (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationDrawBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void EnableAnimationPose (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DisableAnimationPose (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsAnimationPoseEnabled (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationRigError (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationBoneNames (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationBindingNames (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationBoneTransform (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationBindingTransform (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAnimationBoneTransform (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationBoneTransforms (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationPose (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SampleAnimationPose (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasAnimation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartAnimation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyCharacterMap (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveCharacterMap (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAllCharacterMaps (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAppliedCharacterMaps (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void EnableSpriterEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AreSpriterEventsEnabled (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BlendToAnimation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsBlending (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBlendProgress (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PauseAnimation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResumeAnimation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopAnimation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsAnimationPlaying (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsAnimationPaused (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationProgress (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnimationName (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasAttachPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAttachPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AttachSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ActivateSubEntity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DetachSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAttachedSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpriterCollisionBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsSpriterCollisionActive (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpriterCollisionBoxCount (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpriterCollisionBoxName (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
#ifndef PDG_NO_GUI
            static void GetWantsMouseOverEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWantsMouseOverEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWantsClickEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWantsClickEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMouseDetectMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMouseDetectMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWantsOffscreenEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWantsOffscreenEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetDrawHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetPostDrawHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
            static void ChangeFramesImage (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OffsetFrameCenters (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFrameCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FadeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FadeIn (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FadeOut (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsBehind (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetZOrder (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveBehind (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveInFrontOf (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveToFront (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveToBack (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetUserData (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FreeUserData (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLayer (const v8::FunctionCallbackInfo<v8::Value>& args);

            static void On (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnCollideSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnCollideWall (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnOffscreen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnOnscreen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnExitLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationLoop (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationEnd (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationPhysicsRecoveryComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationBlendComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnFadeComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnFadeInComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnFadeOutComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseEnter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseLeave (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseDown (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseUp (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseClick (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    SpriteLayer* New_SpriteLayer(const v8::FunctionCallbackInfo<v8::Value>& args);

    class SpriteLayerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::FunctionTemplate> GetTemplate(v8::Isolate* isolate) { return v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_); }
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            SpriteLayer* getCppObject() { return cppPtr_; }
        protected:
            SpriteLayer* cppPtr_;

            SpriteLayerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~SpriteLayerWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, SpriteLayer* cppObj);
            SpriteLayerWrap(SpriteLayer* obj) : cppPtr_(obj) {}

            static void AddHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Clear (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BlockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UnblockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBoundingBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotatedBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Grow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Stretch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopSpinning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PauseSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResumeSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CancelSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AndThen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsSchedulePaused (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasScheduledAnimations (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Wait (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationHelpers (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSerializedSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMyClassTag (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateParticle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddParticle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveParticle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAllParticles (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetParticleCount (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetNthParticle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMaxParticles (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMaxParticles (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateParticleEmitter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveParticleEmitter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAllParticleEmitters (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSerializationFlags (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartAnimations (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopAnimations (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Hide (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Show (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsHidden (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FadeIn (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FadeOut (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveBehind (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveInFrontOf (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveToFront (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveToBack (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetZOrder (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveWith (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FindSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetNthSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpriteZOrder (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsSpriteBehind (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAllSprites (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void EnableCollisions (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DisableCollisions (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void EnableCollisionsWithLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DisableCollisionsWithLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
#ifndef PDG_NO_GUI
            static void GetSpritePort (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpritePort (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetOrigin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetOrigin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetZoom (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetZoom (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Zoom (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ZoomTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAutoCenter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFixedMoveAxis (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LayerToPortPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LayerToPortOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LayerToPortVector (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LayerToPortRect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LayerToPortQuad (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PortToLayerPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PortToLayerOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PortToLayerVector (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PortToLayerRect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PortToLayerQuad (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            static void SetUseChipmunkPhysics (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetStaticLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGravity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetKeepGravityDownward (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetDamping (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpace (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
#ifdef PDG_SPRITER_SUPPORT
            static void CreateSpriteFromSpriter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateSpriteFromSpriterFile (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateSpriteFromSpriterEntity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyCharacterMapToAll (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveCharacterMapFromAll (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void EnableSpriterEvents (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
            static void On (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnCollideSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnCollideWall (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnOffscreen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnOnscreen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnExitLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationLoop (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationEnd (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnFadeComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnFadeInComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnFadeOutComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseEnter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseLeave (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseDown (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseUp (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseClick (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnErasePort (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnPreDrawLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnPostDrawLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnDrawPortComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationStart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnPreAnimateLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnPostAnimateLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnZoomComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnLayerFadeInComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnLayerFadeOutComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    TileLayer* New_TileLayer(const v8::FunctionCallbackInfo<v8::Value>& args);

    class TileLayerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::FunctionTemplate> GetTemplate(v8::Isolate* isolate) { return v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_); }
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            TileLayer* getCppObject() { return cppPtr_; }
        protected:
            TileLayer* cppPtr_;

            TileLayerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~TileLayerWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, TileLayer* cppObj);
            TileLayerWrap(TileLayer* obj) : cppPtr_(obj) {}

            static void AddHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Clear (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BlockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UnblockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBoundingBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotatedBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeMovementBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterOffsetBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeSpinBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeGrowingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeStretchingBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeScaleBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Grow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Stretch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopMovement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopSpinning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PauseSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResumeSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CancelSchedule (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AndThen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsSchedulePaused (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasScheduledAnimations (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Wait (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationHelpers (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSerializedSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMyClassTag (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateParticle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddParticle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveParticle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAllParticles (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetParticleCount (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetNthParticle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMaxParticles (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMaxParticles (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateParticleEmitter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveParticleEmitter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAllParticleEmitters (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSerializationFlags (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartAnimations (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopAnimations (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Hide (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Show (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsHidden (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FadeIn (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FadeOut (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveBehind (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveInFrontOf (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveToFront (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveToBack (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetZOrder (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveWith (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FindSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetNthSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpriteZOrder (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsSpriteBehind (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HasSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAllSprites (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void EnableCollisions (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DisableCollisions (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void EnableCollisionsWithLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DisableCollisionsWithLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
#ifndef PDG_NO_GUI
            static void GetSpritePort (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpritePort (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetOrigin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetOrigin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetZoom (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetZoom (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Zoom (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ZoomTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAutoCenter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFixedMoveAxis (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LayerToPortPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LayerToPortOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LayerToPortVector (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LayerToPortRect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LayerToPortQuad (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PortToLayerPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PortToLayerOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PortToLayerVector (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PortToLayerRect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PortToLayerQuad (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            static void SetUseChipmunkPhysics (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetStaticLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGravity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetKeepGravityDownward (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetDamping (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpace (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
            static void GetWorldSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWorldSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWorldBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DefineTileSet (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LoadMapData (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMapData (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetTileSetImage (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetTileSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetTileTypeAt (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetTileTypeAndFacingAt (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetTileTypeAt (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CheckCollision (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void On (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnCollideSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnCollideWall (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnOffscreen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnOnscreen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnExitLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationLoop (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationEnd (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnFadeComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnFadeInComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnFadeOutComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseEnter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseLeave (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseDown (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseUp (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnMouseClick (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnErasePort (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnPreDrawLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnPostDrawLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnDrawPortComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationStart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnPreAnimateLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnPostAnimateLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnZoomComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnLayerFadeInComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnLayerFadeOutComplete (const v8::FunctionCallbackInfo<v8::Value>& args);
    };
#endif

}
