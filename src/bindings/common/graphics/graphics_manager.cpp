// -----------------------------------------------
// graphics_manager.cpp
//
// Implementation file for GraphicsManager bindings
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
    //MARK: Graphics Manager
    // ========================================================================================
    
    SINGLETON_MANAGER_INITIALIZER_IMPL(GraphicsManager, "gfx")
        EXPORT_CLASS_SYMBOLS("GraphicsManager", GraphicsManager, , ,
            // method section
            HAS_GETTER(GraphicsManager, NumScreens)
            HAS_GETTER(GraphicsManager, FPS)
            HAS_PROPERTY(GraphicsManager, TargetFPS)
            HAS_GETTER(GraphicsManager, Mouse)
            HAS_METHOD(GraphicsManager, "getCurrentScreenMode", GetCurrentScreenMode)
            HAS_METHOD(GraphicsManager, "getScreenBounds", GetScreenBounds)
            HAS_METHOD(GraphicsManager, "getNumSupportedScreenModes", GetNumSupportedScreenModes)
            HAS_METHOD(GraphicsManager, "getNthSupportedScreenMode", GetNthSupportedScreenMode)
            HAS_METHOD(GraphicsManager, "setScreenMode", SetScreenMode)
            HAS_METHOD(GraphicsManager, "createWindowPort", CreateWindowPort)
            HAS_METHOD(GraphicsManager, "createFullScreenPort", CreateFullScreenPort)
            HAS_METHOD(GraphicsManager, "closeGraphicsPort", CloseGraphicsPort)
            HAS_METHOD(GraphicsManager, "closeAllGraphicsPorts", CloseAllGraphicsPorts)
            HAS_METHOD(GraphicsManager, "createFont", CreateFont)
            HAS_METHOD(GraphicsManager, "getMainPort", GetMainPort)
            HAS_METHOD(GraphicsManager, "switchToFullScreenMode", SwitchToFullScreenMode)
            HAS_METHOD(GraphicsManager, "switchToWindowMode", SwitchToWindowMode)
            HAS_METHOD(GraphicsManager, "inFullScreenMode", InFullScreenMode)
        );
        END
    GETTER_IMPL(GraphicsManager, NumScreens, INTEGER)
    GETTER_IMPL(GraphicsManager, FPS, NUMBER)
    PROPERTY_IMPL(GraphicsManager, TargetFPS, NUMBER)
    CUSTOM_GETTER_IMPL(GraphicsManager, Mouse, POINT, 0, MIN_,
        OPTIONAL_INT32_ARG(1, mouseNumber, 0); CR , 
        pdg::Point theMouse = self->getMouse(mouseNumber), ([number int] mouseNumber = 0) )
    CUSTOM_GETTER_IMPL(GraphicsManager, NumSupportedScreenModes, INTEGER, 0, MIN_,
        OPTIONAL_INT32_ARG(1, screenNum, screenNum_PrimaryScreen); CR ,
        int32 theNumSupportedScreenModes = self->getNumSupportedScreenModes(screenNum), ([number int] screen = PRIMARY_SCREEN) )
    METHOD_IMPL(GraphicsManager, SetScreenMode);
        METHOD_SIGNATURE("changes specified screen to closest matching mode", 
             undefined, 4, ([number int] width, [number int] height, [number int] screenNum = PRIMARY_SCREEN, [number int] bpp = 0));
        REQUIRE_ARG_MIN_COUNT(2);
        REQUIRE_INT32_ARG(1, width);
        REQUIRE_INT32_ARG(2, height);
        OPTIONAL_INT32_ARG(3, screenNum, screenNum_PrimaryScreen);
        OPTIONAL_INT32_ARG(4, bpp, 0);
        self->setScreenMode(width, height, screenNum, bpp);
        NO_RETURN;
        END
    METHOD_IMPL(GraphicsManager, CreateWindowPort)
        METHOD_SIGNATURE("create windowed drawing port with given dimensions, title and depth", 
            [object Port], 3, ([object Rect] rect, string windName = "", [number int] bpp = 0));
        REQUIRE_ARG_MIN_COUNT(1);
        REQUIRE_RECT_ARG(1, rect);
        OPTIONAL_STRING_ARG(2, windName, "");
        OPTIONAL_INT32_ARG(3, bpp, 0);
        Port* port = self->createWindowPort(rect, windName, bpp);
        RETURN_CPP_OBJECT(port, Port);
        END
    METHOD_IMPL(GraphicsManager, CreateFullScreenPort)
        METHOD_SIGNATURE("create full screen drawing port with given dimensions on given screen, optionally changing depth", 
            [object Port], 3, ([object Rect] rect, [number int] screenNum = PRIMARY_SCREEN, boolean allowResChange = true, [number int] bpp = 0));
        REQUIRE_ARG_MIN_COUNT(1);
        REQUIRE_RECT_ARG(1, rect);
        OPTIONAL_INT32_ARG(2, screenNum, screenNum_PrimaryScreen);
        OPTIONAL_BOOL_ARG(3, allowResChange, true);
        OPTIONAL_INT32_ARG(4, bpp, 0);
        Port* port = self->createFullScreenPort(rect, screenNum, allowResChange, bpp);
        RETURN_CPP_OBJECT(port, Port);
        END
    METHOD_IMPL(GraphicsManager, CloseGraphicsPort)
        METHOD_SIGNATURE("close given port, along with its window and restore screen mode if changed", 
            undefined, 1, ([object Port] port = MAIN_PORT));
        OPTIONAL_CPP_OBJECT_ARG(1, port, Port, 0);
        self->closeGraphicsPort(port);
        NO_RETURN;
        END
    METHOD_IMPL(GraphicsManager, CloseAllGraphicsPorts)
        METHOD_SIGNATURE("close all active graphics ports (e.g. for test cleanup)", undefined, 0, ());
        REQUIRE_ARG_COUNT(0);
        self->closeAllGraphicsPorts();
        NO_RETURN;
        END
    METHOD_IMPL(GraphicsManager, CreateFont)
        METHOD_SIGNATURE("get a font with optional scaling adjust", 
            [object Font], 2, (string fontName, number scalingFactor = 1.0));
        REQUIRE_ARG_MIN_COUNT(1);
        REQUIRE_STRING_ARG(1, fontName);
        OPTIONAL_NUMBER_ARG(2, scalingFactor, 1.0f);
        Font* font = self->createFont(fontName, scalingFactor);
        RETURN_CPP_OBJECT(font, Font);
        END
    METHOD_IMPL(GraphicsManager, GetMainPort)
        METHOD_SIGNATURE("return the primary graphics port", 
            [object Port], 0, ());
        REQUIRE_ARG_COUNT(0);
        Port* port = self->getMainPort();
        RETURN_CPP_OBJECT(port, Port);
        END
    METHOD_IMPL(GraphicsManager, SwitchToFullScreenMode)
        METHOD_SIGNATURE("change a port to fullscreen mode, return true on success", 
            boolean, 0, (boolean allowResChange = false, [object Port] port = MAIN_PORT));
        OPTIONAL_BOOL_ARG(1, allowResChange, 0);
        OPTIONAL_CPP_OBJECT_ARG(2, port, Port, 0);
        bool result = self->switchToFullScreenMode(allowResChange, port);
        RETURN_BOOL(result);
        END
    METHOD_IMPL(GraphicsManager, SwitchToWindowMode)
        METHOD_SIGNATURE("change a port to window mode, return true on success", 
            boolean, 0, ([object Port] port = MAIN_PORT, string windName = ""));
        OPTIONAL_CPP_OBJECT_ARG(1, port, Port, 0);
        OPTIONAL_STRING_ARG(2, windName, "");
        bool result = self->switchToWindowMode(port, windName);
        RETURN_BOOL(result);
        END
    METHOD_IMPL(GraphicsManager, InFullScreenMode)
        METHOD_SIGNATURE("return whether primary graphics port is fullscreen or not", 
            boolean, 0, ());
        REQUIRE_ARG_COUNT(0);
        bool fullscreen = self->inFullScreenMode();
        RETURN_BOOL(fullscreen);
        END

    METHOD_IMPL(GraphicsManager, GetScreenBounds);
        METHOD_SIGNATURE("returns the bounds (position and size) of a screen in the global coordinate space", 
            object Rect, 0, ([number int] screenNum = PRIMARY_SCREEN));
        OPTIONAL_INT32_ARG(1, screenNum, screenNum_PrimaryScreen);
        pdg::Rect bounds = self->getScreenBounds(screenNum);
        RETURN(RECT2VAL(bounds));
        END
        
    CPP_SINGLETON_CONSTRUCTOR_IMPL(GraphicsManager)

%#endif //!PDG_NO_GUI

} // pdg namespace
