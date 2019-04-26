#include "deck.h"
#include <iostream>

#ifndef HAND_H
#define HAND_H

using namespace std;

class Hand
{
	//private members
private:
	//card array that holds the player's hand
	card cards[5];

	//public members
public:
	//storing the possible hands in ranking order
	static const int ROYALFLUSH = 9;
	static const int STRAIGHTFLUSH = 8;
	static const int FOUROFAKIND = 7;
	static const int FULLHOUSE = 6;
	static const int FLUSH = 5;
	static const int STRAIGHT = 4;
	static const int THREEOFAKIND = 3;
	static const int TWOPAIR = 2;
	static const int ONEPAIR = 1;
	static const int HIGHCARD = 0;


	//default Hand constructor
	Hand();


	//public methods
	void Deal(deck &d);
	void draw(deck &d, int x);
	void displayHand(ostream &os);
	void swap(card &c1, card &c2);
	void keepCard(int x);
	void discardCard(int x);
	void sortRank();
	int evaluate();

};

#endif

