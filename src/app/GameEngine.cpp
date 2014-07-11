// -----------------------------------------------
//  GameEngine.cpp
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


#include "pdg/sys/global_types.h"
#include "pdg/sys/os.h"
#include "pdg/sys/deserializer.h"
#include "pdg/sys/serializer.h"

#include "pdg/app/GameEngine.h"

#include <limits.h>

#ifndef PDG_UNSAFE_SERIALIZATION
#define PDG_TAG_SERIALIZED_DATA
#define PDG_ACTION_MAGIC_NUMBER    0x03458343
#define PDG_REQUEST_MAGIC_NUMBER   0x52845295
#define PDG_UPDATE_MAGIC_NUMBER    0x24395801
#endif

#define PDG_GAME_ENGINE_NO_ACTION_TYPE	0xffff


namespace pdg {

// ==============================================
// Action class
// ==============================================

uint32 Action::getSerializedSize(ISerializer* serializer) const {
	uint32 totalSize = 0;
#ifdef PDG_TAG_SERIALIZED_DATA
	totalSize += 4;  // size of request magic number
#endif
	totalSize += 4; // size of action type (2), seat (1), and undoable (1)
	return totalSize;
}


void Action::serialize(ISerializer* serializer) const {
#ifdef PDG_TAG_SERIALIZED_DATA
	serializer->serialize_4(PDG_ACTION_MAGIC_NUMBER);
#endif
	serializer->serialize_2(mActionType);
	serializer->serialize_1(mSeat);
	serializer->serialize_1u(mUndoable);
}


void Action::deserialize(IDeserializer* deserializer) {
#ifdef PDG_TAG_SERIALIZED_DATA
	uint32 tag = deserializer->deserialize_4();
	DEBUG_ASSERT(tag == PDG_ACTION_MAGIC_NUMBER, "OUT OF SYNC: expected tag for Action object");
#endif
	mActionType = deserializer->deserialize_2();
	mSeat = deserializer->deserialize_1();
	mUndoable = deserializer->deserialize_1u();
}

// ==============================================
// Request class
// ==============================================

uint32 Request::getSerializedSize(ISerializer* serializer) const {
	uint32 totalSize = 0;
  #ifdef PDG_TAG_SERIALIZED_DATA
	totalSize += 4;  // size of request magic number
  #endif
	totalSize += 2; // size of action type
	totalSize += serializer->serializedSize(mAction);
	return totalSize;
}


void Request::serialize(ISerializer* serializer) const {
  #ifdef PDG_TAG_SERIALIZED_DATA
	serializer->serialize_4(PDG_REQUEST_MAGIC_NUMBER);
  #endif
	serializer->serialize_2(mAction ? mAction->getActionType() : PDG_GAME_ENGINE_NO_ACTION_TYPE);
	serializer->serialize_obj(mAction);
}


void Request::deserialize(IDeserializer* deserializer) {
#ifdef PDG_TAG_SERIALIZED_DATA
	uint32 tag = deserializer->deserialize_4();
	DEBUG_ASSERT(tag == PDG_REQUEST_MAGIC_NUMBER, "OUT OF SYNC: expected tag for Request object");
#endif
	uint16 actionType = deserializer->deserialize_2();
	mAction = dynamic_cast<Action*>( deserializer->deserialize_obj() );
	if (!mAction) {
		DEBUG_ASSERT(actionType == PDG_GAME_ENGINE_NO_ACTION_TYPE, "OUT OF SYNC: couldn't deserialize action");
	} else {
		DEBUG_ASSERT(actionType == mAction->getActionType(), "OUT OF SYNC: incorrect action type marshalled");
	}
}

Request::Request(Action& action)
: mAction(&action) {
	action.addRef();
}

Request::~Request() {
	if (mAction) mAction->release();
	mAction = 0;
}

// ==============================================
// Update class
// ==============================================

uint32 Update::getSerializedSize(ISerializer* serializer) const {
	uint32 totalSize = 0;
  #ifdef PDG_TAG_SERIALIZED_DATA
	totalSize += 4;  // size of update magic number
  #endif
	totalSize += 5; // size of action type (2) and result code (2) and seat (1)
	totalSize += serializer->serializedSize(mAction);
	return totalSize;
}


void Update::serialize(ISerializer* serializer) const {
  #ifdef PDG_TAG_SERIALIZED_DATA
	serializer->serialize_4(PDG_UPDATE_MAGIC_NUMBER);
  #endif
	serializer->serialize_2(mAction ? mAction->getActionType() : PDG_GAME_ENGINE_NO_ACTION_TYPE);
	serializer->serialize_2(mResult);
	serializer->serialize_1(mSeat);
	serializer->serialize_obj(mAction);
}


void Update::deserialize(IDeserializer* deserializer) {
  #ifdef PDG_TAG_SERIALIZED_DATA
	uint32 tag = deserializer->deserialize_4();
	DEBUG_ASSERT(tag == PDG_UPDATE_MAGIC_NUMBER, "OUT OF SYNC: expected tag for Update object");
  #endif
	uint16 actionType = deserializer->deserialize_2();
	mResult = deserializer->deserialize_2();
	mSeat = deserializer->deserialize_1();
	mAction = dynamic_cast<Action*>( deserializer->deserialize_obj() );
	if (!mAction) {
		DEBUG_ASSERT(actionType == PDG_GAME_ENGINE_NO_ACTION_TYPE, "OUT OF SYNC: couldn't deserialize action");
	} else {
		DEBUG_ASSERT(actionType == mAction->getActionType(), "OUT OF SYNC: incorrect action type marshalled");
	}
}

Update::Update(Action* action, int seat, int errorCode) 
: mAction(action), mResult(errorCode), mSeat(seat) {
	if (action) action->addRef();
}

Update::~Update() {
	if (mAction) mAction->release();
	mAction = 0;
}
	


} // end namespace pdg


