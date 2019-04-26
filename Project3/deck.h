#include "card.h"
#include <vector>
#include <cstdlib>

#ifndef DECK_H
#define DECK_H



class deck
{
private:

	card pile[52];
	int remaining;

	void swap(card &c1, card &c2);

public:
	static const int noCardException = -100;

	deck();

	int getRemaining();

	void shuffle();
	card deal();
	bool isEmpty();
	void reset();

};


#endif
