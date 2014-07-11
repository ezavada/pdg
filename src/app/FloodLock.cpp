// -----------------------------------------------
// floodlock.cpp
// 
// DOS attack control objects
//   Temporal window establishment, operation and
//     functionality
//
// Written by Ariel Butler and Ed Zavada, 2004-2012
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


#include "pdg/msvcfix.h"  // fix non-standard MSVC

#include "pdg/sys/os.h"
#include "pdg/app/FloodLock.h"

//#define FLOOD_DEBUG

namespace pdg {

FloodEvent::FloodEvent( uint32 eState )
{
	state = eState;
}

FloodLock::FloodLock( uint16 size, uint32 timeWindowMs, int discardSetting )
: maxSize(0), locked(false), last_addition(0), count(0), rejected(0)
{
	// mFldLst.reserve( size );		// Only useful in the std::vector implementation
	maxSize = size;
	wSize = timeWindowMs;
	discardOpt = discardSetting;
}

int
FloodLock::numQueued()
{
	return static_cast<int>(mFldLst.size());
}

int
FloodLock::totalQueued()
{
	return count;
}

void
FloodLock::clear()
{
	mFldLst.clear();
	last_addition = 0;
	count = 0;
	rejected = 0;
	locked = false;
}

bool
FloodLock::floodCheck()
{
	return floodCheck( FloodLock::NO_STATE );
}

bool
FloodLock::floodCheck( uint32 evState )
{
	bool result = false;

	if (!locked) {
		FloodEvent fEv( evState );

		if (expireQueue() == FloodLock::SUCCESS) {
			fEv.eVId = count;
			if (addEvent( fEv ) == FloodLock::SUCCESS) {
				result = true;
			}
		}

		if (!result) {
			locked = true;
		}
	}
#ifdef FLOOD_DEBUG
	OS::_DOUT( "+++ floodCheck: time[%ld] queue[%d] result[%d] locked[%d]", OS::getMilliseconds(),
		numQueued(), result, locked );
#endif

	return result;
}

bool
FloodLock::isLocked()
{
	return locked;
}

void
FloodLock::lock()
{
	locked = true;
}

FloodLock::floodResult
FloodLock::addEvent( FloodEvent& fEv )
{
	if (mFldLst.size() < maxSize) {
		fEv.tmTag = OS::getMilliseconds();
		last_addition = fEv.tmTag;
		mFldLst.push_back( fEv );
		++count;
		return FloodLock::SUCCESS;
	}
	++rejected;
	return FloodLock::QUEUE_FULL;
}

FloodLock::floodResult
FloodLock::expireQueue()		// remove any items older than current_time - wSize;
{
	FloodLock::floodResult fR = FloodLock::SUCCESS;

	uint32 cutOff = OS::getMilliseconds() - wSize;
	if (last_addition >= cutOff) {		// Some of the entries are within the window
		for (bool keepGoing=true; keepGoing && (mFldLst.size() > 0); ) {
			FloodEvent& fEv = mFldLst.front();
			if (fEv.tmTag < cutOff) {		// this item is older than the cutoff time
				mFldLst.pop_front();		// erase it
			} else {
				keepGoing = false;
			}
		}
	} else {							// None of the entries are within the window (optimization)
		mFldLst.clear();
	}

	if (mFldLst.size() == maxSize) {
		fR = FloodLock::QUEUE_FULL;
	}
	return fR;
}

} // namespace pdg
