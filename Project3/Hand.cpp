#include "pch.h"
#include "Hand.h"


//default constructor
Hand::Hand()
{
	
}

//Deal method that deals 5 cards to the player's hand
//resets and shuffles the deck when the number of cards is below 9
void Hand::Deal(deck &d)
{
	if (d.getRemaining() <= 9) {
		d.reset();
		d.shuffle();
	}
	for (int i = 0; i < 5; i++) {
		cards[i] = d.deal();
	}
}

//draw method that draws x number of cards to replace the discarded cards
void Hand::draw(deck &d, int x) {
	for (int i = 0; i < x; i++) {

		if (cards[i].getFaceUp() == false) {
			cards[i] = d.deal();
		}

		
	}
}

//displayHand method that prints the cards to the screen using Card::printCard()
void Hand::displayHand(ostream &os) {
	//a little formatting for clarification
	cout << "Current Hand\n";
	for (int i = 0; i < 5; i++) {
		cout << "[" << i + 1 << "]  ";
		cards[i].printCard(os);
	}
	cout << "\n";
}


//keepCard method that marks a card to keep
void Hand::keepCard(int x) {
	cards[x].setFaceUp(true);
}

//discardCard method that marks a card to discard
//then sets the card as facedown
void Hand::discardCard(int x) {
	cards[x].setFaceUp(false);
}

//sortRank method that sorts the hand by rank so the
//data is easier to use
void Hand::sortRank() {
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 0; i < 5; i++) {
			int temp = cards[i].getRank();
			for (int j = i + 1; j < 5; j++) {
				if (cards[j].getRank() < temp) {
					swap(cards[i], cards[j]);
					sorted = false;
				}
			}
		}
	}



}

//evaluate method that check the user's hand for a winning poker hand
int Hand::evaluate() {

	//all of these evaluations assume that the hand has been sorted
	//by rank from lowest to highest


	//checking for an ace to know to check for an ace high straight
	bool ace = false;
	for (int i = 0; i < 5; i++){
		if (cards[i].getRank() == 1) {
			ace = true;
		}
	}

	//checking for a flush
	//if all suits are not the same then flush is false
	bool flush = true;
	for (int i = 1; i < 5; i++) {
		if (cards[0].getSuit() != cards[i].getSuit()) {
			flush = false;
		}
	}

	//checking for a straight
	bool straight = true;
	bool royalStraight = false;

	//if there is an ace in the last 
	if (ace && cards[1].getRank() > 2) {
		short adjustment = 0;
		for (int i = 4; i > 0; i--) {
			adjustment++;
			if (14 != (cards[i].getRank() +  adjustment)) {
				straight = false;
			}
		}
		//if straight is still true then it has to be a royal straight
		if (straight) {
			royalStraight = true;

		}
	}
	else {
		for (int i = 1; i < 5; i++) {
			if (cards[0].getRank() != (cards[i].getRank() - i)) {
				straight = false;
			}
		}
	}


	bool fourOfAKind = false;
	for (int i = 0; i < 2; i++) {
		if (cards[i].getRank() == cards[i + 1].getRank()) {
			if (cards[i].getRank() == cards[i + 2].getRank()) {
				if (cards[i].getRank() == cards[i + 3].getRank()) {
					fourOfAKind = true;
					
				}
			}
		}
	}

	//checking for three of a kind and a full house
	bool threeOfAKind = false;
	bool fullHouse = false;
	//if we know that we have four of a kind then we do not check
	//for three of a kind bc it will always be true
	if (!fourOfAKind) {
		//with a sorted hand three of a kind can only be in three different positions
		for (int i = 0; i < 3; i++) {
			//checking if the three consecutive cards are all the same
			if (cards[i].getRank() == cards[i + 1].getRank()) {
				if (cards[i].getRank() == cards[i + 2].getRank()) {
					//flip three of a kind on
					threeOfAKind = true;


				}
			}
		}
		//if we have three of a kind we now check for a full house
		if (threeOfAKind) {
			//with a sorted hand the three of a kind will either be at the front or the back every time
			//checking for a pair
			if (cards[0].getRank() == cards[1].getRank() && cards[0].getRank() != cards[2].getRank()) {
				fullHouse = true;
			}else if (cards[3].getRank() == cards[4].getRank() && cards[3].getRank() != cards[2].getRank()) {
				fullHouse = true;
			}
		}
	}

	//checking for one and two pair
	bool twoPair = false;
	bool onePair = false;

	//keeping track of the number of pairs found
	int pairCount = 0;

	//if any better hand has been found then we do not check for pairs
	if (!threeOfAKind && !fourOfAKind && !straight && !flush) {
		//looping through the pairs in order to check all permutations
		for (int i = 0; i < 4; i++) {
			for (int j = i+1; j < 5; j++) {

				//if there are two of a kind make onePair true
				//then add one to pairCount
				if (cards[i].getRank() == cards[j].getRank()) {
					onePair = true;
					pairCount++;
				}
			}
		}
		//if there are multiple pairs turn onePair off and twoPair on
		//it is impossible to have three pair with 5 cards
		if (pairCount > 1) {
			twoPair = true;
			onePair = false;
		}
	}


	//using bools to return the best hand as an int
	if (royalStraight && flush) {
		return ROYALFLUSH;
	}
	else if (straight && flush) {
		return STRAIGHTFLUSH;
	}
	else if (fourOfAKind) {
		return FOUROFAKIND;
	}
	else if (fullHouse) {
		return FULLHOUSE;
	}
	else if (flush) {
		return FLUSH;
	}
	else if (straight) {
		return STRAIGHT;
	}
	else if (threeOfAKind) {
		return THREEOFAKIND;
	}
	else if (twoPair) {
		return TWOPAIR;
	}
	else if (onePair) {
		return ONEPAIR;
	}
	else {
		return HIGHCARD;
	}
}


void Hand::swap(card &c1, card &c2) {
	card tempCard;
	tempCard = c1;
	c1 = c2;
	c2 = tempCard;
}



