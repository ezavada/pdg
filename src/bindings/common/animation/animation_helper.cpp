// -----------------------------------------------
// animation_helper.cpp
//
// Class-specific JavaScript bindings.
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "animation_impl_macros.h"
#include "../core/core_impl_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_impl.h"
%#include "pdg_script_interface.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>

namespace pdg {

// The wrapper owns a reference independently of each AnimatedBase registration.
// Its callback is a JS property so inactive wrapper/callback cycles can be collected.
%#ifdef PDG_USING_JAVASCRIPT_CORE
static void IAnimationHelper_finalize(JSObjectRef object) {
    auto* helper = static_cast<IAnimationHelper*>(JSObjectGetPrivate(object));
    if (!helper) return;
    helper->mIAnimationHelperScriptObj = nullptr;
    JSObjectSetPrivate(object, nullptr);
    helper->release();
}
%#else
IAnimationHelper* New_IAnimationHelper(SCRIPT_ARGS);
IAnimationHelperWrap::IAnimationHelperWrap(SCRIPT_ARGS) : cppPtr_(New_IAnimationHelper(args)) {}
IAnimationHelperWrap::~IAnimationHelperWrap() {
    if (cppPtr_) {
        cppPtr_->mIAnimationHelperScriptObj.Reset();
        cppPtr_->release();
    }
}
%#endif
BINDING_INITIALIZER_IMPL_REFCOUNTED(IAnimationHelper,
    OBJECT_SAVE_WEAK(cppObj->mIAnimationHelperScriptObj, obj); cppObj->addRef();
    if (auto* script = dynamic_cast<ScriptAnimationHelper*>(cppObj)) script->initializeScriptObject())
    EXPORT_FINALIZED_CLASS_SYMBOLS("IAnimationHelper", IAnimationHelper, IAnimationHelper_finalize, , , );
	END

CLEANUP_IMPL(IAnimationHelper)

} // namespace pdg
