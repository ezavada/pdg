// -----------------------------------------------
// easing.h
// 
// easing functionality for animation
//
// Written by Ed Zavada, 2012
// Copyright (c) 2012, Dream Rock Studios, LLC
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


#ifndef PDG_EASING_H_INCLUDED
#define PDG_EASING_H_INCLUDED

#include "pdg_project.h"

#include "pdg/sys/global_types.h"

namespace pdg {

/** \addtogroup AnimationEasing
 * @{
 */

// -----------------------------------------------------------------------------------
// Easing Functions
//
// timeSeconds: current time offset since start of animation, 
// beginVal: beginning value at start of animation, 
// change: complete change in value over entire animation,
// durationSeconds: duration for entire animation
// returns new value as of current time offset

typedef float (*EasingFunc)(double timeOffsetSeconds, float beginVal, float change, double durationSeconds);

// Predefined Easing Functions:

// --- LINEAR EASING: basic linear motion --------------------------------------------

float linearTween(double ut, float b, float c, double ud);
// easeInX - accelerating from zero velocity
// easeOutX - decelerating to zero velocity
// easeInOutX - acceleration until halfway, then deceleration

// --- QUADRATIC EASING: t^2 ---------------------------------------------------------
float easeInQuad(double ut, float b, float c, double ud);
float easeOutQuad(double ut, float b, float c, double ud);
float easeInOutQuad(double ut, float b, float c, double ud);

// --- CUBIC EASING: t^3 -------------------------------------------------------------
float easeInCubic(double ut, float b, float c, double ud);
float easeOutCubic(double ut, float b, float c, double ud);
float easeInOutCubic(double ut, float b, float c, double ud);

// --- QUARTIC EASING: t^4 -----------------------------------------------------------
float easeInQuart(double ut, float b, float c, double ud);
float easeOutQuart(double ut, float b, float c, double ud);
float easeInOutQuart(double ut, float b, float c, double ud);

// --- QUINTIC EASING: t^5 -----------------------------------------------------------
float easeInQuint(double ut, float b, float c, double ud);
float easeOutQuint(double ut, float b, float c, double ud);
float easeInOutQuint(double ut, float b, float c, double ud);

// --- SINUSOIDAL EASING: sin(t) -----------------------------------------------------
float easeInSine(double ut, float b, float c, double ud);
float easeOutSine(double ut, float b, float c, double ud);
float easeInOutSine(double ut, float b, float c, double ud);

// --- EXPONENTIAL EASING: 2^t -------------------------------------------------------
float easeInExpo(double ut, float b, float c, double ud);
float easeOutExpo(double ut, float b, float c, double ud);
float easeInOutExpo(double ut, float b, float c, double ud);

// --- CIRCULAR EASING: sqrt(1-t^2) --------------------------------------------------
float easeInCirc(double ut, float b, float c, double ud);
float easeOutCirc(double ut, float b, float c, double ud);
float easeInOutCirc(double ut, float b, float c, double ud);

// --- BOUNCE EASING: exponentially decaying parabolic bounce ------------------------
float easeInBounce(double ut, float b, float c, double ud);
float easeOutBounce(double ut, float b, float c, double ud);
float easeInOutBounce(double ut, float b, float c, double ud);

// --- BACK EASING: overshooting cubic easing: (s+1)*t^3 - s*t^2 ---------------------
//     backtracking slightly, then reversing direction and moving to target
float easeInBack(double ut, float b, float c, double ud);
//     moving towards target, overshooting it slightly, then reversing and coming back to target
float easeOutBack(double ut, float b, float c, double ud);
//     backtracking slightly, then reversing direction and moving to target,
//     then overshooting target, reversing, and finally coming back to target
float easeInOutBack(double ut, float b, float c, double ud);


#define NUM_BUILTIN_EASINGS		28
#define MAX_CUSTOM_EASINGS		10
#define NUM_EASING_FUNCTIONS 	NUM_BUILTIN_EASINGS + MAX_CUSTOM_EASINGS

#define BUILTIN_EASING_FUNC_LIST linearTween,    \
	easeInQuad, easeOutQuad, easeInOutQuad,		 \
	easeInCubic, easeOutCubic, easeInOutCubic,	 \
	easeInQuart, easeOutQuart, easeInOutQuart,	 \
	easeInQuint, easeOutQuint, easeInOutQuint,	 \
	easeInSine, easeOutSine, easeInOutSine,		 \
	easeInExpo, easeOutExpo, easeInOutExpo,		 \
	easeInCirc, easeOutCirc, easeInOutCirc,		 \
	easeInBounce, easeOutBounce, easeInOutBounce,\
	easeInBack, easeOutBack, easeInOutBack

#define EASING_FUNC_LIST   \
	BUILTIN_EASING_FUNC_LIST,       \
	customEasing0, customEasing1, customEasing2,  \
	customEasing3, customEasing4, customEasing5,  \
	customEasing6, customEasing7, customEasing8,  \
	customEasing9

namespace EasingFuncIds {  // no confusion in the global namespace
	enum {
		EASING_FUNC_LIST
	};
}

extern EasingFunc gEasingFunctions[NUM_EASING_FUNCTIONS];
extern int gNumCustomEasings;

uint8 easingFuncToId(EasingFunc func);
EasingFunc easingIdToFunc(uint8 id);

/** @} */

} // end namespace pdg

#endif // PDG_EASING_H_INCLUDED

