/*
 *  GameEngine.h
 *
 *  Created by Ed Zavada on 3/16/10.
 *  Copyright 2010 Dream Rock Studios LLC. All rights reserved.
 *
 */

#ifndef GAME_ENGINE_H_INCLUDED
#define GAME_ENGINE_H_INCLUDED

#include "pdg/sys/serializable.h"
#include "pdg/sys/iserializer.h"
#include "pdg/sys/ideserializer.h"
#include "pdg/sys/log.h"


namespace pdg {
	
	const bool kCanUndo = true;
	const bool kCannotUndo = false;

	enum { 
		/*! No such seat exists, this is a result returned by some calls */
		NoSeat = 0,			
		/*! Same as passing in the seat number of the player whose turn it is */
		CurrentSeat = -1,	
		/*! Pass in for any spectator with no access to private player info */
		SpectatorSeat = -2 
	};
	
		
	// ==============================================
	// Action class
	// ==============================================
	
	
	//! Represents anything a player can do with the Engine
	
	/*! The GameEngine uses Action objects to perform players' game moves. There are
	 specific types of Action objects for specific actions. In many cases an
	 application that calls the GameEngine will only need to pass Action objects 
	 around -- for instance an all AI game with no User Interface could be
	 played that way. 
	 For a human to play, the application will need to create specific Action 
	 objects using the makeXxxRequest() calls, and pass them in to the Engine 
	 for execution.
	 User Interface code will most likely find it valuable or necessary to
	 peek at Action objects and extract information from them.
	 \sa Serializable, Request, Update, aiGetNextMove(), makeRequestFromSerializedData(), 
	 makeUpdateFromSerializedData()
	 */
	
	class Action : public Serializable<Action> {
	public:

		SERIALIZABLE_TAG( CLASSTAG_ACTION )
		SERIALIZABLE_METHODS()

		//!	Gets the specific type of this action
		/*! It must be guaranteed safe to perform a static_cast<> to the specific
		 Action subclass that corresponds to the result
		 \return the type, presumably matching a game specific enumeration value
		 */
		int         getActionType() { return mActionType; }
		
		//! Gets the seat number that did/will perform the action
		/*! \return seat number or 0 if no player or ai was responsible for this action
		 */
		int         getSeat() { return mSeat; }
		
		//! Can this action be undone?
		/*! This refers to whether the action is by nature one that can be undone. If it is
		 an undoable action it will return true even if the action hasn't been performed
		 yet. So a return value of true does not necessarily mean that calling the GameEngine
		 with an Undo Request for this action will succeed or not.
		 \return true if Action can be undone, false if by its very nature it cannot be undone
		 */
		bool        isUndoable() { return mUndoable; }

		Action() : mActionType(0), mSeat(0), mUndoable(false) {}
		virtual ~Action() {}
	protected: 
	/// @cond INTERNAL
		// actions should not be created directly, they should be created by specific class
		Action(int type, int seat, bool undoable = true) 
			: mActionType(type), mSeat(seat), mUndoable(undoable) {}
		// data members
		uint16  mActionType;
		uint8   mSeat;
		bool mUndoable;
	/// @endcond
	};

	
	// ==============================================
	// Request class
	// ==============================================
	
	//! Request class holds an Action that is being requested but is not yet performed
	
	/*! The Engine will transform Requests into Updates when the Action is 
	 performed or fails. Requests only contain public data that any player
	 or spectator can observe.
	 \sa Serializable, Action, Update, makeRequestFromSerializableData(),
	 makeUpdateFromSerializableData()
	 */
	
	class Request : public Serializable<Request> {
	public:
		SERIALIZABLE_TAG( CLASSTAG_REQUEST )
		SERIALIZABLE_METHODS()
		
		//! Get the action that has been requested
		/*! \return a reference to the Action requested
		 */
		Action& getActionRequested() { return *mAction; }
		
		
		Request(Action& mAction);
		Request() : mAction(0) {}
		virtual ~Request();
	protected:
		//! The Action that has been requested
		Action* mAction;
	};
	
	
	
	// ==============================================
	// Update class
	// ==============================================
	
	//! The Update class holds an Action that has been performed
	
	/*! The Engine will transform Requests into Updates when the Action is 
	 performed or fails. Updates include results of actions that may 
	 contain data private to a particular seat (such as the player's
	 cards in hand).
	 */
	
	class Update : public Serializable<Update> {
	public:
		
		SERIALIZABLE_TAG( CLASSTAG_UPDATE )
		SERIALIZABLE_METHODS()
		
		//! Get the action that was performed
		/*! \return a reference to the Action performed, or NULL if this is not related to an action
		 */
		Action* getActionPerformed() { return mAction; }
		
		
		//! Get the result of the Action being performed
		/*! Indicate whether the result succeeded or failed, and an error code if it failed.
		 \return the result code, zero (0) on success, or non-zero error code if it failed
		 \sa getResultString()
		 */
		int	getResultCode() { return mResult; }
		
		
		//! Gets the seat number that the update is intended for
		/*! The game engine will ignore updates that are not intended
		 for it based on the seat.
		 \return seat number 0 if it is not seat specific
		 */
		int getSeat() { return mSeat; }

		//! Get a string detailing the results of the Action being performed
		/*! \return the results "Success" on success, or "ERROR" followed by a code and 
		 explaination if it failed. This is for debugging purposes only, not for user
		 display. The results strings will be in English and are not localizable.
		 \sa getResultCode()
		 */
		virtual const char* getResultString() { return (mResult) ? "ERROR" : "Success"; }
		
		Update( Action* action, int seat = NoSeat, int errorCode = 0);
		
		Update() : mAction(0), mResult(0), mSeat(0) {}
		~Update();
	protected:
		//! The Action that has been performed
		Action* mAction;
		uint16	mResult;
		uint8	mSeat;
	};
	
	
	//! The ScenarioInfo class holds information specific to settng up a particular scenario or game rules variant
	class ScenarioInfo : public Serializable<ScenarioInfo> {
	public:
		SERIALIZABLE_TAG( CLASSTAG_SCENARIO_INFO )
		
	};
	
	//! The GameInfo class holds information options for a particular game
	class GameInfo : public Serializable<GameInfo> {
	public:
		SERIALIZABLE_TAG( CLASSTAG_GAME_INFO ) 
		
	};
	
	//! The PlayerInfo class holds information that would be needed for any player of the game, human or AI
	class PlayerInfo : public Serializable<PlayerInfo> {
	public:
		SERIALIZABLE_TAG( CLASSTAG_PLAYER_INFO )
				
	};
	
	//! The AIInfo class holds information that is unique to a computer controlled player
	class AIInfo : public Serializable<AIInfo> {
	public:
		SERIALIZABLE_TAG( CLASSTAG_AI_INFO )
		
	};
	
	// ==============================================
	// GameEngine class
	// ==============================================
	
	//! Primary base class for the %Game %Engine and AI functionality
	
	/*! 
	 
	 The %Game %Engine is has a number of methods organized by function.  
	 The categories are:
	 - <b>Game Command & Control</b>\n
	 These methods allow the application developer to initialize, configure and shutdown the 
	 engine.  Also here are methods to add/replace players and control the life cycle 
	 (start/stop/abort) of a game instance.
	 - <b>Game Actions</b>\n
	 These methods allow the communication of player actions to the engine.
	 - <b>Game Data Query</b>\n
	 These methods allow the application to retrieve game, player and board state from the 
	 engine. You will have to declare most of these yourself
	 - <b>AI Player</b>\n
	 These methods are called by the application during an AI player's turn.  They allow 
	 the AI player to perform all conventional player actions.
	 
	 Typical game application interaction with the %Game %Engine could be summarized as:
	 - Initialize the %Game %Engine
	 - Configure the %Game %Engine
	 - Setup the Scenario
	 - Add players
	 - Start the game
	 - Pass player actions to the game engine(s) and engine updates to the player(s)
	 - Call the AI Players for their actions as necessary
	 - Check for non-performing players, replace or abort as necessary
	 - Check for end game conditions
	 - End the game, display results
	 - Setup for next game or close the %Game %Engine
	 
	 <br>
	 
	 \image html engine_callflow.png
	 \sa initEngine(), configureEngine(), setupScenario(), setupGame(), setupFromSerializedGameData(),
	 addPlayer(), startGame(), handleUpdate(), handleRequest(), replacePlayer(), endGame(), 
	 abortGame(), replayGame(), resetEngine() and cleanupEngine()
	 
	 
	 <h2>Client/Server model</h2>
	 
	 \image html "Client Server.png"
	 \sa Request, Update, handleUpdate(), handleRequest() and aiGetNextMove()
	 <br><br>
	 
	 \image html "Client Server Failures.png"
	 \sa Request, Update, handleUpdate() and handleRequest()
	 */
	
	class GameEngine : public Serializable<GameEngine> {
	public:
		SERIALIZABLE_TAG( CLASSTAG_GAME_ENGINE )
		
		//! Seat definitions
		
		
		// ==============================================
		// Game Command & Control
		// ==============================================
		
		// following return error codes if failure
		
		//! Initialize the %Engine and specify log manager
		/*! Initializes the Engine and specifies the LogManager which
		 the Game Engine will use for logging. This is the first thing that
		 must be done after the Engine is constructed, and it should only
		 be done once during the lifecycle of the Engine.
		 \param logMgr the LogManager that should be used for logging.
		 Pass in NULL for console logging via stdout.
		 \sa configureEngine() and cleanupEngine()
		 */
		virtual void initEngine(LogManager* logMgr) = 0;
		
		//! Configure the %Engine with its static data
		/*! Configures the Engine with static data. Some examples of static data
		 include general game board structure, AI decision constants and other 
		 data that does not change at runtime. This allows the engine to be 
		 tuned without recompilation.\n\n
		 This should be done once during the lifecycle of the Engine, right after
		 calling initEngine.
		 \param config NUL terminated C string with the static configuration 
		 and tuning data for the engine
		 \return zero on success, or a non-zero error code if an error occurs.
		 */
		virtual int configureEngine(const char* config) = 0;
		
		//! Setup scenario options
		/*! A scenario is a particular set of game rules and board/map arrangement.
		 Typically, this would be done when the user chooses which scenario they
		 want to play before starting a game.\n\n
		 This call is not needed if a game is loaded via 
		 setupFromSerializedGameData().
		 \return zero on success, or a non-zero error code if an error occurs.
		 \sa setupFromSerializedGameData()
		 */
		virtual int setupScenario(ScenarioInfo* info) = 0;
		
		//! Setup game options
		/*! This call is not needed if a game is loaded via 
		 setupFromSerializedGameData().
		 \return zero on success, or a non-zero error code if an error occurs.
		 */
		virtual int setupGame(GameInfo* info) = 0;	
		
		//! Add a player to the game before starting
		/*! Call this to add a player to the game. Both normal players and AI players
		 must be added <b>in turn order</b> before the game is started.
		 \param playerInfo is a pointer to the info for the player
		 \param aiInfo should be passed in if a computer player will control this seat,
		 or leave it off (pass null) if the seat will be controlled by a human player.
		 \return zero on success, or a non-zero error code if an error occurs.
		 */
		virtual int addPlayer(PlayerInfo* playerInfo, AIInfo* aiInfo = 0) = 0; 
		
		//! 
		/*!
		 \return zero on success, or a non-zero error code if an error occurs.
		 */
		virtual int replacePlayer(int seat, PlayerInfo* playerInfo, AIInfo* aiInfo = 0) = 0;
		
		
		//! Start the game
		/*!
		 */
		virtual void startGame() = 0;
		
		
		//! End the game normally
		/*!
		 */
		virtual void endGame() = 0;
		
		//! End the game abnormally
		/*!
		 */
		virtual void abortGame() = 0;
		
		
		//! Change one or more scenario options
		/*! This is used to change scenario options for a game in progress, 
		 although not all scenario options can be changed during play.
		 It can also be called after setupFromSerializedGameData() to change
		 the options of a newly loaded game.
		 \return zero on success, or a non-zero error code if an error occurs.
		 */
		virtual int changeScenarioOptions(ScenarioInfo* info) = 0;
		
		//! Change one or more game options
		/*! This is used to change game options for a game in progress, 
		 although not all game options can be changed during play.
		 It can also be called after setupFromSerializedGameData() to change
		 the options of a newly loaded game.
		 \return zero on success, or a non-zero error code if an error occurs.
		 */
		virtual int changeGameOptions(GameInfo* info) = 0;
		
		
		//! Start a game over from the beginning with same options
		/*!
		 \return zero on success, or a non-zero error code if an error occurs.
		 */
		virtual int replayGame() = 0;	//! must be called after end or abort
		
		//! Prepare the engine for a new scenario and game
		/*!
		 \return zero on success, or a non-zero error code if an error occurs.
		 */
		virtual int resetEngine() = 0;
		
		
		//! Final shutdown and cleanup of engine before it is destroyed
		/*! Releases the logger object passed in to initEngine()
		 */
		virtual void cleanupEngine() = 0;
		
		
		
		//! Undo the last Action (not all actions are undoable)
		/*!
		 \return a Request object for the particular action, or NULL if an error occurs. 
		 */
		virtual Request*	makeUndoRequest(Action* actionToBeUndone, int seat = CurrentSeat) = 0;
		
		//! 
		/*!
		 \return a Request object for the particular action, or NULL if an error occurs. 
		 */
		virtual Request*	makeCheatRequest(int cheatCode, int seat = CurrentSeat) = 0;
		
		
		// ==============================================
		// general action handling
		// ==============================================
		
		//! Attempt to perform a specific Action
		/*! Given a Request object that expresses an Action to be taken by a player,
		 this method evaluates whether it can be performed or not. If is a legal and
		 allowable action for the current game and player state, it will create an
		 Update object reflecting the execution of that Action. If not, it will
		 create an Update object containing the error info.\n\n
		 You must call handleUpdate() with the update from an authoritive engine
		 before the Action is committed. Until then, further calls to handleRequest()
		 will fail because an Action is still in progress. This is only a significant
		 issue in the case of a client/server game, where the client does not have
		 an authoritative engine. Instead, the Request must be sent to the server as
		 well as being handled locally. The server's authoritative engine will produce
		 an Update object that can actually commit the Action. The time delay due to
		 network round trips means the application developer must pay attention to the
		 sequence of operations and build a UI that prevents the user from attempting
		 another Action before the prior one has been commited. \n\n
		 A client's non-authoritative engine will still produce Update objects, but
		 they will not commit the action to the engine if passed to handleUpdate().
		 It is perfectly safe to call handleRequest() followed immediately by handleUpdate()
		 on a non-authoritative engine, but you must still call handleUpdate() with the
		 authoritative Update once that is received from the authoritative engine.
		 \param inRequest a specific Request object that expresses an Action to be taken by a player
		 \return an Update object, reflecting execution of the particular action 
		 or the reason for failure if the request failed.
		 \sa handleUpdate() and makeRequestFromSerializedData()
		 */
		virtual Update*	handleRequest(Request* inRequest) = 0;
		
		//! Commit a specific Action performed by a player
		/*! Given an Update produced by a call to handleRequest(), update the game engine.
		 This commits the Action and once again allows calls to handleRequest() to succeed,
		 unless this was an Update produced by a non-authoritative engine (see handleRequest()
		 for details).\n\n
		 This is also used in client/server games for actions performed by a remote client
		 or an AI, in which case the client never sees a Request for the Action, but is
		 simply informed that it happened via an Update.\n\n
		 If this was a failure reported back from a server to a client, then the effects of
		 the handleRequest() will be reversed and game start restored as if the handleRequest()
		 for that Action had never been called.
		 \param inUpdate an Update produced by a call to handleRequest() or 
		 makeUpdateFromSerializedData()
		 \sa handleRequest() and makeUpdateFromSerializedData()
		 */
		virtual void	handleUpdate(Update* inUpdate) = 0;
		
		
		// ==============================================
		// Game Data Query (state & map/board)
		// ==============================================
		
		
		//! Get the number of players in the game
		/*!
		 */
		virtual int getNumPlayers() = 0;
		
		//! 
		/*!
		 */
		virtual bool isClient() = 0;
		
		//! 
		/*!
		 */
		virtual bool isServer() = 0;
		
		//! 
		/*!
		 */
		virtual bool isStandalone() = 0;
		
				
		//! Is seat controlled by an AI?
		/*!
		 */
		virtual bool seatIsAI(int seat) = 0;
		
		
		//! ==============================================
		//! AI methods
		//! ==============================================
		
		//! Called repeatedly during an AI player's turn until the AI returns 'done'.
		
		//! Get the next move an AI player wants to make
		/*! Call this repeatedly while it is an AI player's turn to get the AI player's moves.\n\n
		 Delay between moves to simulate human response times is the responsibility of the 
		 application.
		 */
		virtual Request* aiGetNextMove(int aiSeat = CurrentSeat) = 0;
		
		
	};
	
	
} // end namespace pdg

#endif // GAME_ENGINE_H_INCLUDED

