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

    Animated* New_Animated(const v8::FunctionCallbackInfo<v8::Value>& args);

    class AnimatedWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Animated* getCppObject() { return cppPtr_; }
        protected:
            Animated* cppPtr_;

            AnimatedWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~AnimatedWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Animated* cppObj);
            AnimatedWrap(Animated* obj) : cppPtr_(obj) {}

            static void GetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetVelocity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetVelocity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMass (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMass (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMoveFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMoveFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpinFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpinFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSizeFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSizeFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBoundingBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotatedBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Move (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetVelocityInRadians (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMovementDirectionInRadians (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopMoving (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Accelerate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AccelerateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Grow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Stretch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Resize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Rotate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopSpinning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Wait (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyTorque (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopAllForces (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationHelpers (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Animate (const v8::FunctionCallbackInfo<v8::Value>& args);

    };

    ISpriteCollideHelper* New_ISpriteCollideHelper(const v8::FunctionCallbackInfo<v8::Value>& args);

    class ISpriteCollideHelperWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            ISpriteCollideHelper* getCppObject() { return cppPtr_; }
        protected:
            ISpriteCollideHelper* cppPtr_;

            ISpriteCollideHelperWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~ISpriteCollideHelperWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, ISpriteCollideHelper* cppObj);
            ISpriteCollideHelperWrap(ISpriteCollideHelper* obj) : cppPtr_(obj) {}

    };

#ifndef PDG_NO_GUI
    ISpriteDrawHelper* New_ISpriteDrawHelper(const v8::FunctionCallbackInfo<v8::Value>& args);

    class ISpriteDrawHelperWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
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

            static void AddHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveHandler (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Clear (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void BlockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UnblockEvent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetVelocity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetVelocity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMass (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMass (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMoveFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMoveFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpinFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpinFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSizeFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSizeFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBoundingBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotatedBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Move (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetVelocityInRadians (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMovementDirectionInRadians (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopMoving (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Accelerate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AccelerateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Grow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Stretch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Resize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Rotate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopSpinning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Wait (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyTorque (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopAllForces (const v8::FunctionCallbackInfo<v8::Value>& args);
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
            static void GetCollisionRadius (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCollisionRadius (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetElasticity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetElasticity (const v8::FunctionCallbackInfo<v8::Value>& args);
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
            static void HasAnimation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartAnimation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetEntityScale (const v8::FunctionCallbackInfo<v8::Value>& args);
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
            static void EnableCollisions (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DisableCollisions (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCollisionType (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UseCollisionMask (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCollisionHelper (const v8::FunctionCallbackInfo<v8::Value>& args);;
            static void SetUserData (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FreeUserData (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            static void GetCollideGroup (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCollideGroup (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MakeStatic (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PinJoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SlideJoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PivotJoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GrooveJoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SpringJoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotarySpring (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotaryLimit (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Ratchet (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Gear (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Motor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveJoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Disconnect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MakeJointBreakable (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MakeJointUnbreakable (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
            static void On (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnCollideSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnCollideWall (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnOffscreen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnOnscreen (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnExitLayer (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationLoop (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void OnAnimationEnd (const v8::FunctionCallbackInfo<v8::Value>& args);
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
            static void GetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetVelocity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetVelocity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMass (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMass (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMoveFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMoveFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpinFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpinFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSizeFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSizeFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBoundingBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotatedBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Move (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetVelocityInRadians (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMovementDirectionInRadians (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopMoving (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Accelerate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AccelerateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Grow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Stretch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Resize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Rotate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopSpinning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Wait (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyTorque (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopAllForces (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationHelpers (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSerializedSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMyClassTag (const v8::FunctionCallbackInfo<v8::Value>& args);
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
            static void GetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLocation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpeed (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetVelocity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetVelocity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCenterOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpin (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMass (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMass (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMoveFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMoveFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpinFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpinFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSizeFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSizeFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBoundingBox (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotatedBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Move (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetVelocityInRadians (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMovementDirectionInRadians (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopMoving (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Accelerate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AccelerateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Grow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Stretch (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopGrowing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopStretching (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Resize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResizeTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FlipY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedX (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void IsFlippedY (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Rotate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopSpinning (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeCenterTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Wait (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFriction (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ApplyTorque (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopAllForces (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemoveAnimationHelper (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearAnimationHelpers (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSerializedSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Serialize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Deserialize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMyClassTag (const v8::FunctionCallbackInfo<v8::Value>& args);
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
