// -----------------------------------------------
// Cards.cpp
// 
// Implementation of card playing classes
//
// Written by Ariel Butler and Ed Zavada, 2003-2012
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

#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include "pdg/sys/os.h"

#include "pdg/app/Cards.h"

namespace pdg {

//
// Set the attributes table of a given deck (make sure 'attr' is not volatile!)
//
void
CardInfo::setCardAttributes( char *attr )
{
	att_table = attr;
}

//
// Retrieve attributes of a given card
//
char *
CardInfo::getCardAttributes( Card card )
{
	char *aptr = att_table + (((uint16) card) * ATTRIB_CHARS_PER_CARD);
	return aptr;
}


//
// Deck constructor
//
Deck::Deck() {
	for (int i=0; i<DECK_SIZE; i++) {
		discards[i] = 0;
	}
	card_top = discard_top = 0;  // card_top = 0 means no cards
	fill();
}


//
// Fill the deck with cards, but don't shuffle
// NOTE: if there are hands already drawn from this deck, they should be thrown away
//
void
Deck::fill()
{
	for (int i=0; i < DECK_SIZE; i++) 
	{
      cards[i] = (Card) (i % RANGE_SIZE);  // constrain to unique card max
      // FIXME: this assumes that there are an equal number of all types of cards
      // in cases where there are non-unique cards. This isn't necessarily true.
      // filling a deck with non-unique cards will be tricky
	}
	card_top = DECK_SIZE; // card_top always points to array position after top card
}

//
// Shuffle an existing card deck, either as-is or first adding in discards
//
void
Deck::shuffle( bool use_discards )
{
	uint16 swapX = 0, swapY = 0, i, size;
	Card swaptmp;

	if ( use_discards ) 
	{
		for (i=0; i < discard_top; i++)	
		{	// Add all discards into main deck
		   cards[card_top++] = discards[i];
		   discards[i] = 0;
		}
		discard_top = 0;	   // cleanup the discard pile
	}
	size = card_top;   // card_top points to array position after last card

	// For as many cards as we have, randomly exchange two arbitrary cards with each other
	for (i=0; i<size; i++)
	{
		swapX = (uint16) (OS::gameCriticalRandom() % size);
		swapY = (uint16) (OS::gameCriticalRandom() % size);
		swaptmp = cards[swapX];
		cards[swapX] = cards[swapY];
		cards[swapY] = swaptmp;
	}
}

//
// Add a card to a deck's discard pile
//
void
Deck::addDiscard( Card card )
{
#ifdef DEBUG
   if (discard_top >= DECK_SIZE) 
   {
#ifdef LOG_ERRORS
		OS::_DOUT("AddDiscard: too many discards!");
#endif
		abort(); // make coding errors big and obvious      
   }
#endif // DEBUG
   discards[discard_top++] = card;
}
// return the last discarded card
// for undo, to take back the last discarded card
Card
Deck::returnCard()
{
	Card card;
	FIXME("Since Card is unsigned the following if() is always false");
#ifdef DEBUG
   if (discard_top < 0) 
   {
#ifdef LOG_ERRORS
		OS::_DOUT("returnDiscardedCard: no discarded cards!");
#endif
		abort(); // make coding errors big and obvious      
		return (Card)-1;
   }
#endif // DEBUG
   card = discards[--discard_top];
   discards[discard_top] =0;
   return card;
}
//
// Discard all marked cards from a hand into a deck's discard pile
//
void
Deck::discardHand( Hand& hand )
{
	int i;

	for (i=0; i<HAND_SIZE; i++) 
   {
		if (hand.marks[i] & MARK_DISCARD)
		{
			addDiscard( hand.cards[i] );
			hand.cards[i] = 0;
			hand.marks[i] = MARK_EMPTY;
			hand.num_cards--;
		}
	}
}

//
// Draw up to 'num_cards' cards from the deck, replacing discards and filling empty slots
//
void
Deck::addHand( Hand& hand, uint8 num_cards )
{
	uint16 i, wcard;

	for (i=0; i<num_cards; i++)
	{
		if (hand.marks[i] & MARK_DISCARD)		// Marked for discard, replace it
		{
			addDiscard( hand.cards[i] );
			hand.marks[i] = MARK_EMPTY;
		}
		if (!(hand.marks[i] & MARK_CARD))		// No current card in this slot
		{
			wcard = drawCard();
			if (wcard == CARD_ERR_DECK_EMPTY)	// oops, need to shuffle the discards
			{
				shuffle( true );
				wcard = drawCard();
			}
			hand.cards[i] = (uint8) wcard;
			hand.marks[i] = MARK_CARD;			// Clear all other bit flags, set mark to occupied
		}
	}
	hand.num_cards = num_cards;
}

//
// Draw up to 'num_cards' cards from the deck, replacing discards and filling empty slots
// In this case the deck is stacked, so the cards drawn will be the ones you pass in, but
// deck integrity will be maintained
// cards must always point to an array at least num_cards long of card numbers
// also, discards are shuffled into deck every time to ensure card desired is available
// return value is number of cards drawn, useful for advancing a point in a larger
// card values array for successive calls to this function
//
int
Deck::addHandFromStackedDeck( Hand& hand, uint8 num_cards, Card* cards )
{
	uint16 i, wcard;
	int count = 0;

	for (i=0; i<num_cards; i++)
	{
		if (hand.marks[i] & MARK_DISCARD)		// Marked for discard, replace it
		{
			addDiscard( hand.cards[i] );
			hand.marks[i] = MARK_EMPTY;
		}
	}
	shuffle( true );
	for (i=0; i<num_cards; i++)
	{
		if (!(hand.marks[i] & MARK_CARD))		// No current card in this slot
		{
			wcard = drawSpecificCard( cards[count] );
			hand.cards[i] = (uint8) wcard;
			hand.marks[i] = MARK_CARD;			// Clear all other bit flags, set mark to occupied
            count++;    // add one to count of cards drawn
		}
	}
	hand.num_cards = num_cards;
	return count;
}

//
// Draw a single card from a deck
//
Card
Deck::drawCard()
{
	Card card;
	if (card_top > 0) 
	{
		card = cards[--card_top];
		cards[card_top] = 255;
//		OS::_DOUT("Drew card [%d]", (int) card);
		return(card);
	} 
	else 
	{
		return (Card)CARD_ERR_DECK_EMPTY;		// deck is empty
	}
}

//
// Draw a single specific card from a deck, regardless of where in the deck that card is
// Returns CARD_ERR_DECK_EMPTY if the card is not found
//
Card
Deck::drawSpecificCard( Card whichCard )
{
	//uint8 card;
	if (card_top > 0)  {
	    bool found = false;
	    for (int i = 0; i < card_top; i++) {
	        if (cards[i] == whichCard) {
	            found = true;
	        }
	        if (found && (i >= 0) && (i < (card_top-1)) ) {
	            cards[i] = cards[i+1];
	        }
	    }
	    if (found) {
    		cards[--card_top] = 255;
//    		OS::_DOUT("Force drew card [%d]", (int) whichCard);
    		return whichCard;
    	} else {
#ifdef LOG_ERRORS
    		OS::_DOUT("Force draw failed for [%d]", (int) whichCard);
#endif
		    return (Card)CARD_ERR_DECK_EMPTY;
		}
	} else {
#ifdef LOG_ERRORS
    	OS::_DOUT("Force draw from Empty Deck for [%d]", (int) whichCard);
#endif
		return (Card)CARD_ERR_DECK_EMPTY;		// deck is empty
	}
}

int
Deck::getNumCards()
{
    return card_top;
}

Card
Deck::getNthCard(int i)
{
    if (i >= card_top) {
        return (Card)CARD_ERR_DECK_EMPTY;
    } else {
        return cards[card_top - i - 1];
    }
}

void 
Deck::setNumCards(int n) {
    if (n > DECK_SIZE) {
        n = DECK_SIZE;
    }
    card_top = n;
}

void
Deck::setNthCard(int n, Card card) {
    if (n<card_top) {
        cards[card_top - n - 1] = card;
    }
}

// ===================================== HAND =========================================

//
// Hand constructor
//
Hand::Hand() {
	num_cards = 0;
	for (int i=0; i<HAND_SIZE; i++) 
	{
		cards[i] = 0;
		marks[i] = MARK_EMPTY;
	}
}


//
// Compress empty slots out of hand
//
void
Hand::compress()
{
	int i, q;
	for (i=0, q=0; i<HAND_SIZE; i++) 
	{
		if (marks[i] & MARK_CARD)
		{
			if (q != i)
			{
   				cards[q] = cards[i];
   				marks[q] = marks[i];
				cards[i] = 0;
				marks[i] = MARK_EMPTY;
			}
			q++;
		}
	}
}

//
// returns array index where card is located, -1 if not foundint  
//
int
Hand::getCardIndex( Card card ) 
{
	for (int i=0; i<HAND_SIZE; i++)
	{
		if ((cards[i] == card) && (marks[i] & MARK_CARD))		// An empty slot, regardless of other bitflags
		{
		    return i;
		}
	}
	return -1;
}

//
// Add the given card to a hand in the first empty location
//
void
Hand::addCard( Card card, uint8 markval )
{
	uint16 i;

	for (i=0; i<HAND_SIZE; i++)					// Search for the first opportunity
	{
		if (!(marks[i] & MARK_CARD))		// An empty slot, regardless of other bitflags
		{
			cards[i] = card;
			marks[i] = MARK_CARD | markval;	// Clear all other bit flags, set mark to occupied
			break;								// Break 'for' loop
		}
	}
	num_cards++;
}

//
// Pass a specific card to a different hand
//
void 
Hand::passCard( Hand& toHand, uint8 cardnum )
{
    Card card = cards[cardnum];
    toHand.addCard(card);
    cards[cardnum] = 0;
    marks[cardnum] = MARK_EMPTY;
    num_cards--;
    compress();
}

//
// Return a specific card to a deck's discard pile
//
void 
Hand::discardCard( Deck& toDeck, uint8 cardnum )
{
    Card card = cards[cardnum];
    toDeck.addDiscard(card);
    cards[cardnum] = 0;
    marks[cardnum] = MARK_EMPTY;
    num_cards--;
    compress();
}
// returns the last discarded card
void 
Hand::undoDiscardCard( Deck& toDeck)
{
    Card card = toDeck.returnCard();
	addCard(card);
    compress();
}

//
// Mark a specific card
//
void
Hand::markCard( uint8 cardnum, uint8 markval )
{
   marks[cardnum] |= markval;
}

//
// Unmark a specific card
//
void
Hand::unmarkCard( uint8 cardnum, uint8 markval )
{
	marks[cardnum] &= ~((uint8)markval);
}


//
// Mark all cards
//
void
Hand::markAllCards( uint8 markval )
{
	int i;

	for (i=0; i<HAND_SIZE; i++)
		if (marks[i] & MARK_CARD)
			marks[i] |= markval;
}


//
// Unmark all cards
//
void
Hand::unmarkAllCards( uint8 markval )
{
	int i;

	for (i=0; i<HAND_SIZE; i++)
		if (marks[i] & MARK_CARD)
			marks[i] &= ~((uint8)markval);
}

//
// Debug a card hand
//
#ifdef DEBUG
void
Hand::Debug_Hand()
{
	OS::_DOUT("--- Hand Debug Start --- cnum [%d] ---\n", num_cards );
	for (int i=0; i<HAND_SIZE; i++) 
	{
		OS::_DOUT( "Card[%d] = [%d] [%c]\n", i, cards[i], ((marks[i] & MARK_CARD) ? '*' : ' ') );
	}
	OS::_DOUT( "--- Hand Debug End ---\n" );
}

//
// Debug a card deck
//
void
Deck::Debug_Deck()
{
	int tot = card_top + discard_top;

	if (tot > DECK_SIZE)
		OS::_DOUT( "ERROR ERROR ERROR ERROR -- DECK OVERFULL!\n" );

	OS::_DOUT( "--- Deck Debug Start --- ctop [%d] dtop [%d] tot [%d] ---\n", card_top, discard_top, tot);
	for (int i=0; i<DECK_SIZE; i++)
	{
		OS::_DOUT("Pos[%d] = Card[%d] Discard[%d]\n", i, cards[i], discards[i]);
	}
	OS::_DOUT( "-------- Deck Debug End --------\n" );
}

#endif //DEBUG

} // close namespace pdg
