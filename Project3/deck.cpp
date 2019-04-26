#include "pch.h"
#include "deck.h"
#include "time.h"

int deck::getRemaining()
{
	return remaining;

}

deck::deck()
{
	reset();
}

void deck::reset()
{
	remaining = 0;
	for (short suit = card::CLUBS; suit <= card::SPADES; suit++)
	{
		for (short rank = card::ACE; rank <= card::KING; rank++)
		{
			pile[remaining].setSuit(suit);
			pile[remaining].setRank(rank);
			pile[remaining].setFaceUp(true);
			remaining += 1;
		}
	}
}

bool deck::isEmpty()
{
	return remaining == 0; // !remaining 
}

card deck::deal()
{
	if (isEmpty()) { throw noCardException; }
	return pile[--remaining];
}

void deck::shuffle() {
	srand((unsigned)time(NULL));
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 27; i++) {
			int r1 = rand() % 52;
			int r2 = rand() % 52;
			deck::swap(pile[r1], pile[r2]);
		}
	}

}

void deck::swap(card &c1, card &c2) {
	card tempCard;
	tempCard = c1;
	c1 = c2;
	c2 = tempCard;
}
