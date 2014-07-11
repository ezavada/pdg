// -----------------------------------------------
// FloodLock.h
// 
// DOS attack control objects
//   Temporal window establishment, operation and
//     functionality
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

// Caveat -- State cache not fully implemented, use at own risk!


#ifndef PDG_FLOODLOCK_H_INCLUDED
#define PDG_FLOODLOCK_H_INCLUDED

#include "pdg/sys/os.h"
#include "pdg/sys/global_types.h"

#include <vector>
#include <deque>

namespace pdg {

class FloodEvent {
public:
	int eVId;		// nominal identifier
	uint32 state;	// nominal state
	uint32 tmTag;	// time (in milliseconds) this event was added to the list

	FloodEvent( uint32 eState );
};

typedef std::deque<FloodEvent> FloodList;


class FloodLock {
public:
	enum floodResult { SUCCESS, QUEUE_FULL, ITEM_NOT_FOUND };
	enum floodOpts { DISCARD_OLDEST, DISCARD_NEWEST };
	enum floodState { STATELESS, KEEP_STATE };
	enum { NO_STATE = -2000000000 };
	int numQueued();				// get current number of items in queue
	int totalQueued();				// get total number of items queued since construction
	void clear();					// reset this flood lock to its initial state
	bool	floodCheck();			// if < flood limit, store time of this event & return true
	bool	floodCheck( uint32 eState );
	bool	isLocked();				// check the state of this flood lock
	void	lock();					// set the state of this flood lock to 'locked'.

	FloodLock( uint16 size = 10, uint32 timeWindowMs = 5000, int discardSetting = DISCARD_NEWEST );
protected:
	floodResult addEvent( FloodEvent& fEv );
	floodResult expireQueue();		// remove any items older than current_time - wSize;

	FloodList mFldLst;
	int discardOpt;
	uint16 maxSize;					// the max number of items to be queued
	bool locked;					// current state of this flood lock
	uint32 last_addition;			// time of newest record added
	uint32 wSize;					// window size in millisecs
	uint32 count;					// number of items queued since constructed
	uint32 rejected;				// number of items rejected since constructed
};

} // close namespace pdg

#endif // PDG_FLOODLOCK_H_INCLUDED

