// -----------------------------------------------
// Cards.h
// 
// Definitions for Card objects
//
// Copyright (c) 2004, Pixel Dust Games, LLC. 
// All Rights Reserved.
// -----------------------------------------------

#ifndef PDG_CARDS_H_INCLUDED
#define PDG_CARDS_H_INCLUDED

#include "pdg/sys/global_types.h"

#include "Carddefs.h"   // include application specific defines
//
// Application defines (change these for your app)
//

#define HIGHEST_CARD_VALUE		(RANGE_SIZE - 1)
#define CARD_TABLE_SIZE			(RANGE_SIZE * ATTRIB_CHARS_PER_CARD)

//
// Fixed defines (don't change these)
//
#define MAX_DECK_SIZE			65534	// Maximum size of the deck array
#define MAX_HAND_SIZE			256		// Maximum size of the hand array
#define MAX_RANGE_SIZE			255		// Maximum number of unique cards in a hand

#define MARK_EMPTY				0x0		// An empty slot in the Hand
#define MARK_CARD				0x01	// This card slot has a card in it
#define MARK_DISCARD			0x02	// The card in this slot has been selected for discard
#define MARK_SELECTED			0x04	// This is the currently selected card in the hand

#define CARD_ERR_DECK_EMPTY		255		// Attempted draw from an empty deck

#define SHUFFLE         true
#define DONT_SHUFFLE    false

#define INCLUDE_DISCARDS      true
#define DONT_INCLUDE_DISCARDS false


namespace pdg {

typedef uint8 Card;

class Deck;
	
class CardInfo
{
public:
	void setCardAttributes( char* attr );
	char *getCardAttributes( Card card );
private:
	char *att_table;					// Fixed length card attribute text table
};

class Hand : public CardInfo
{
friend class Deck;  // give Deck access to our private stuff
public:
	Card cards[HAND_SIZE];		// Current cards in your hand
	Card marks[HAND_SIZE];		// Marks for subsequent action, i.e. discard, replace, etc..
    bool hasCard( Card card );
    int  getCardIndex( Card card ); // returns array index where card is located, -1 if not found
    int  getNumCards() { return num_cards; }
	void addCard( Card card, uint8 markval = 0 );
	void passCard( Hand& toHand, uint8 cardnum );
	void discardCard( Deck& toDeck, uint8 cardnum );
	void markCard( uint8 cardnum, uint8 markval );
	void unmarkCard( uint8 cardnum, uint8 markval );
	void markAllCards( uint8 markval );
	void unmarkAllCards( uint8 markval );
	void compress();
	void undoDiscardCard( Deck& toDeck);
	void setnumberOfCards(uint8 noCards){num_cards = noCards;}
	
	Hand();
private:
	uint8 num_cards;			// Current number of cards in hand
	void Debug_Hand();
};


class Deck : public CardInfo
{
public:
	void fill();
	void shuffle( bool use_discards = INCLUDE_DISCARDS );
	void addHand( Hand& hand, uint8 num_cards );
	int  addHandFromStackedDeck( Hand& hand, uint8 num_cards, Card* cards );
	Card drawCard();
	Card drawSpecificCard( Card card );
	void addDiscard( Card card );
	void discardHand( Hand& hand );
	// for scanning through the deck
	int  getNumCards();
	Card getNthCard(int i);
	// for setting up the deck
	void setNumCards(int n);
	void setNthCard(int n, Card card);
	Card returnCard();// for undo, to take back the last discarded card
	Deck();
protected:
	Card cards[DECK_SIZE];				// A card stack
	Card discards[DECK_SIZE];			// popped off cards
	uint16 card_top;					// Current top of card stack
	uint16 discard_top;					// Current top of discard stack
	void Debug_Deck();
};

} // close namespace pdg

#endif // PDG_CARDS_H_INCLUDED


