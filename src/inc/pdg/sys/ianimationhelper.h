// -----------------------------------------------
// ianimationhelper.h
// 
// animation helper functionality
//
// Written by Ed Zavada, 2004-2012
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


#ifndef PDG_ANIMATION_HELPER_H_INCLUDED
#define PDG_ANIMATION_HELPER_H_INCLUDED

#include "pdg_project.h"

#include "pdg/sys/global_types.h"
#include "pdg/sys/serializable.h"

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
#include "pdg_script_bindings.h"
#endif

namespace pdg {

class AnimatedBase;

/* -----------------------------------------------------------------------------------
 * Animation Helper
 *
 * Implement this interface to do extra animation stuff for a specific AnimatedBase object
 * then add by calling the object's addAnimationHelper() method
 * You can have multiple Animation Helpers attached to the same object.
 *
 * For those coding in Javascript, there is an implementation of IAnimationHelper 
 * that maps a function definition to the animate call. So to create a helper:
 *
 *      var myHelper = new pdg.IAnimationHelper(function(what, deltaSeconds) {
 *            console.log("in my animation helper for " + what + " after " + deltaSeconds + "s" );
 *            return true; // not done, keep helping
 *      });
 *		myAnimatedObj.addAnimationHelper(myHelper);
 *
 * Declare a JavaScript subclass for a helper with its own methods or state.
 * The native constructor callback forwards to the subclass's animate() method:
 *
 * class MyAnimationHelperClass extends pdg.IAnimationHelper {
 *     constructor() {
 *         super(function(what, deltaSeconds) {
 *             return this.animate(what, deltaSeconds);
 *         });
 *     }
 *
 *     animate(what, deltaSeconds) {
 *         console.log("Animation step:", deltaSeconds, "seconds");
 *         return false; // finished; remove this helper from the object
 *     }
 * }
 *
 * myAnimatedObj.addAnimationHelper(new MyAnimationHelperClass());
 */

class IAnimationHelper : public ISerializable {
public: 
	
	SERIALIZABLE_TAG( CLASSTAG_ANIM_HELPER );

	// what is the AnimatedBase object for which normal animation has just completed
	// deltaSeconds is time (seconds) since last call to animate
	// return true if this helper should continue to be used, false
	// if it should be removed from the helper list
    virtual bool animate(AnimatedBase* what, double deltaSeconds) = 0;
    
    // Owned registrations retain a native reference until removed and no longer
    // executing. Return false only for borrowed helpers that outlive registration.
    virtual bool ownedByAnimated() { return true; }

/// @cond INTERNAL
    // Script implementations also retain their callback wrapper while registered.
    virtual void retainForAnimation() { addRef(); }
    virtual void releaseForAnimation() { release(); }
/// @endcond

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	SCRIPT_OBJECT_REF mIAnimationHelperScriptObj;
#endif

	IAnimationHelper() {
    	#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    		INIT_SCRIPT_OBJECT(mIAnimationHelperScriptObj);
    	#endif
	}

    virtual ~IAnimationHelper() {
				#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
					#ifndef PDG_NO_GUI
						CleanupIAnimationHelperScriptObject(mIAnimationHelperScriptObj);
					#endif
				#endif
			}

	// your helper will need to implement these if you are going to serialize or deserializer helpers
	virtual uint32 getSerializedSize(pdg::ISerializer* serializer) const { return 0; }
	virtual void serialize(pdg::ISerializer* serializer) const {}
	virtual void deserialize(pdg::IDeserializer* deserializer) {}

};



} // end namespace pdg

#endif // PDG_ANIMATION_HELPER_H_INCLUDED

