// -----------------------------------------------
// timer_manager.cpp
//
// Implementation file for TimerManager bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "core_impl_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_impl.h"
%#include "pdg_script_interface.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>


namespace pdg {

// ========================================================================================
//MARK: TimerManager
// ========================================================================================

SINGLETON_MANAGER_INITIALIZER_IMPL(TimerManager, "tm")
    EXPORT_CLASS_SYMBOLS("TimerManager", TimerManager, , ,
    	// method section
		HAS_EMITTER_METHODS(TimerManager)
		HAS_METHOD(TimerManager, "startTimer", StartTimer)
		HAS_METHOD(TimerManager, "cancelTimer", CancelTimer)
		HAS_METHOD(TimerManager, "cancelAllTimers", CancelAllTimers)
		HAS_METHOD(TimerManager, "delayTimer", DelayTimer)
		HAS_METHOD(TimerManager, "delayTimerUntil", DelayTimerUntil)
		HAS_METHOD(TimerManager, "pause", Pause)
		HAS_METHOD(TimerManager, "unpause", Unpause)
		HAS_METHOD(TimerManager, "isPaused", IsPaused)
		HAS_METHOD(TimerManager, "pauseTimer", PauseTimer)
		HAS_METHOD(TimerManager, "unpauseTimer", UnpauseTimer)
		HAS_METHOD(TimerManager, "isTimerPaused", IsTimerPaused)
		HAS_METHOD(TimerManager, "getWhenTimerFiresNext", GetWhenTimerFiresNext)
		HAS_METHOD(TimerManager, "getMilliseconds", GetMilliseconds)
    );
	END
EMITTER_BASE_CLASS_IMPL(TimerManager)
METHOD_IMPL(TimerManager, StartTimer)
	METHOD_SIGNATURE("", undefined, 3, ([number int] id, [number uint] delay, boolean oneShot = true));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_INT32_ARG(1, id);
    REQUIRE_UINT32_ARG(2, delay);
    OPTIONAL_BOOL_ARG(3, oneShot, true);
    self->startTimer(id, delay, oneShot);  // userData
	NO_RETURN;
	END
METHOD_IMPL(TimerManager, CancelTimer)
	METHOD_SIGNATURE("", undefined, 1, ([number int] id));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_INT32_ARG(1, id);
    self->cancelTimer(id);
	NO_RETURN;
	END
METHOD_IMPL(TimerManager, CancelAllTimers)
	METHOD_SIGNATURE("", undefined, 0, ());
    REQUIRE_ARG_COUNT(0);
    self->cancelAllTimers();
	NO_RETURN;
	END
METHOD_IMPL(TimerManager, DelayTimer)
	METHOD_SIGNATURE("", undefined, 2, ([number int] id, [number uint] delay));
    REQUIRE_ARG_COUNT(2);
    REQUIRE_INT32_ARG(1, id);
    REQUIRE_UINT32_ARG(2, delay);
    self->delayTimer(id, delay);
	NO_RETURN;
	END
METHOD_IMPL(TimerManager, DelayTimerUntil)
	METHOD_SIGNATURE("", undefined, 2, ([number int] id, [number int] msTime));
    REQUIRE_ARG_COUNT(2);
    REQUIRE_INT32_ARG(1, id);
    REQUIRE_INT64_ARG(2, msTime);
    self->delayTimerUntil(id, msTime);
	NO_RETURN;
	END
METHOD_IMPL(TimerManager, Pause)
	METHOD_SIGNATURE("", undefined, 0, ());
    REQUIRE_ARG_COUNT(0);
    self->pause();
	NO_RETURN;
	END
METHOD_IMPL(TimerManager, Unpause)
	METHOD_SIGNATURE("", undefined, 0, ());
    REQUIRE_ARG_COUNT(0);
    self->unpause();
	NO_RETURN;
	END
METHOD_IMPL(TimerManager, IsPaused)
	METHOD_SIGNATURE("", boolean, 0, ());
    REQUIRE_ARG_COUNT(0);
    bool isPaused = self->isPaused();
    RETURN_BOOL(isPaused);
	END
METHOD_IMPL(TimerManager, PauseTimer)
	METHOD_SIGNATURE("", undefined, 1, ([number int] id));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_INT32_ARG(1, id);
    self->pauseTimer(id);
	NO_RETURN;
	END
METHOD_IMPL(TimerManager, UnpauseTimer)
	METHOD_SIGNATURE("", undefined, 1, ([number int] id));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_INT32_ARG(1, id);
    self->unpauseTimer(id);
	NO_RETURN;
	END
METHOD_IMPL(TimerManager, IsTimerPaused)
	METHOD_SIGNATURE("", boolean, 1, ([number int] id));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_INT32_ARG(1, id);
    bool isPaused = self->isTimerPaused(id);
    RETURN_BOOL(isPaused);
	END
METHOD_IMPL(TimerManager, GetWhenTimerFiresNext)
	METHOD_SIGNATURE("", number, 1, ([number int] id));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_INT32_ARG(1, id);
    ms_time when = self->getWhenTimerFiresNext(id);
    // Convert timer_Never (0xffffffff) to JavaScript timer_Never (-1)
    if (when == 0xffffffff) {
        RETURN_NUMBER(-1);
    } else {
        RETURN_NUMBER(when);
    }
	END
STATIC_METHOD_IMPL(TimerManager, GetMilliseconds)
	METHOD_SIGNATURE("", number, 0, ());
	RETURN_NUMBER( OS::getMilliseconds() );
	END

CPP_SINGLETON_CONSTRUCTOR_IMPL(TimerManager)

} // namespace pdg 