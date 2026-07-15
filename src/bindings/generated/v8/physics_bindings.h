// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/physics_bindings.h
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



#ifndef PDG_PHYSICS_BINDINGS_H_INCLUDED
#define PDG_PHYSICS_BINDINGS_H_INCLUDED

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

#ifdef PDG_USE_CHIPMUNK_PHYSICS

    class cpArbiterWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            cpArbiter* getCppObject() { return cppPtr_; }
        protected:
            cpArbiter* cppPtr_;

            cpArbiterWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~cpArbiterWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, cpArbiter* cppObj);
            cpArbiterWrap(cpArbiter* obj) : cppPtr_(obj) {}

            static void IsFirstContact (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCount (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetNormal (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPointA (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPointB (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetDepth (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    class cpConstraintWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            cpConstraint* getCppObject() { return cppPtr_; }
        protected:
            cpConstraint* cppPtr_;

            cpConstraintWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~cpConstraintWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, cpConstraint* cppObj);
            cpConstraintWrap(cpConstraint* obj) : cppPtr_(obj) {}

            static void GetMaxForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMaxForce (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetErrorBias (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetErrorBias (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMaxBias (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMaxBias (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAnchor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAnchor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetOtherAnchor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetOtherAnchor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPinDist (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetPinDist (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSlideMinDist (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSlideMinDist (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSlideMaxDist (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSlideMaxDist (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGrooveStart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGrooveStart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGrooveEnd (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGrooveEnd (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpringRestLength (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpringRestLength (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpringStiffness (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpringStiffness (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSpringDamping (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSpringDamping (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRotarySpringRestAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRotarySpringRestAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMinAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMinAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMaxAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMaxAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRatchetAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRatchetAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRatchetPhase (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRatchetPhase (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRatchetInterval (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetRatchetInterval (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGearRatio (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGearRatio (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGearInitialAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetGearInitialAngle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMotorSpinRate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetMotorSpinRate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetType (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ActivateBodies (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetImpulse (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetOtherSprite (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    class cpSpaceWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            cpSpace* getCppObject() { return cppPtr_; }
        protected:
            cpSpace* cppPtr_;

            cpSpaceWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~cpSpaceWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, cpSpace* cppObj);
            cpSpaceWrap(cpSpace* obj) : cppPtr_(obj) {}

            static void GetIdleSpeedThreshold (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetIdleSpeedThreshold (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSleepTimeThreshold (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetSleepTimeThreshold (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCollisionSlop (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCollisionSlop (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCollisionBias (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCollisionBias (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCollisionPersistence (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCollisionPersistence (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UseSpatialHash (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ReindexStatic (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Step (const v8::FunctionCallbackInfo<v8::Value>& args);
    };
#endif

}
#endif
