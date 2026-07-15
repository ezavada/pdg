// -----------------------------------------------
// font.cpp
//
// Implementation file for Font bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_interface.h"
%#include "pdg_script_impl.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>


namespace pdg {
    
%#ifndef PDG_NO_GUI


// ========================================================================================
//MARK: Font
// ========================================================================================

#define FONT_GETTER_IMPL(prop) \
CUSTOM_GETTER_IMPL(Font, prop, NUMBER, 1, MIN_,                		\
	REQUIRE_INT32_ARG(1, size); CR                             		\
    OPTIONAL_UINT32_ARG(2, style, textStyle_Plain); CR ,	\
    float the##prop = self->get##prop(size, style),                 \
    (number size, [number int] style = textStyle_Plain) )

WRAPPER_INITIALIZER_IMPL(Font)
    EXPORT_CLASS_SYMBOLS("Font", Font, , ,
    	// method section
		HAS_GETTER(Font, FontName)
		HAS_GETTER(Font, FontHeight)
		HAS_GETTER(Font, FontLeading)
		HAS_GETTER(Font, FontAscent)
		HAS_GETTER(Font, FontDescent)
    );
	END
GETTER_IMPL(Font, FontName, STRING)
FONT_GETTER_IMPL(FontHeight)
FONT_GETTER_IMPL(FontLeading)
FONT_GETTER_IMPL(FontAscent)
FONT_GETTER_IMPL(FontDescent)

CLEANUP_IMPL(Font)

CPP_UNMANAGED_CONSTRUCTOR_IMPL(Font, cppPtr_ = nullptr; CR )
    SAVE_ERR("Font cannot be created directly, use pdg.gfx.createFont()");
    return 0;
    END

%#endif //!PDG_NO_GUI

} // pdg namespace
