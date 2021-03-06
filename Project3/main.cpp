// Simeon Weatherby
//stw9
//Visual Studio

//This is a program that simulates the classic game "Five Card Draw"
//The computer generates 5 cards
//The user decides whether to keep or discard a card (up to 3)
//The computer evaluates the final hand and lets the user know the result.



#include "pch.h"
#include "hand.h"
#include <iostream>

//importing necessary libraries
using std::iostream;
using std::string;

int main()
{

	//initializing main() members
	deck pokerDeck = deck();
	Hand myHand = Hand();

	//initially shuffling the deck
	pokerDeck.shuffle();

	//greeting the user
	cout << "Welcome to 5-Card Draw" << endl;

	//creating a game loop that allows the user to play multiple hands
	//this will cause the user to have to close the window in order to exit
	while (true) {
		//printing house rules before every hand
		cout << "Max discard is 3 unless the one kept card is an Ace\n" << endl;

		//initializing int to hold the number of discarded cards
		//resets on every hand
		int discardedNum = 0;

		//dealing the user's hand
		myHand.Deal(pokerDeck);
		
		//sort the hand by rank so it is easier to view and evaluate
		myHand.sortRank();

		//displaying the hand to the screen
		myHand.displayHand(cout);
		
		//looping 5 times to allow the user to mark each card as keep or discard
		for (int i = 0; i < 5; i++) {

			//temp int to determine keep or discard
			int x;

			//prompting user to keep or discard card
			cout << "Enter 1 to keep card " << i + 1 << " or enter 0 to discard card " << i + 1 << endl;

			//accepting user input
			cin >> x;

			//calling either the keepCard or discardCard based on user input 
			if (x == 1) {
				myHand.keepCard(i);
			}
			else {
				myHand.discardCard(i);

				//incrementing the number of discarded cards
				discardedNum++;

			}
		}
		
		//calling the draw function to replace the discarded cards
		myHand.draw(pokerDeck, discardedNum);

		//display new hand after discard and draw
		myHand.displayHand(cout);

		//resort the hand
		myHand.sortRank();

		//evaluate the result then print the result to screen
		printResult(myHand.evaluate());

		//this holds the program so the user can view the result of the hand
		//once the user enters a char the screen is cleared and a new hand starts
		char c;
		cout << "Enter any key to play another hand" << endl;
		cin >> c;
		system("CLS");

	}
}


//method to print the results from the Hand class evaluate method
//keeps main() more concise
void printResult(int x) {

	if (x == 0) {
		cout << "You have a high card!" << endl;
	}else if (x == 1) {
		cout << "You have one pair!" << endl;
	}
	else if (x == 2) {
		cout << "You have two pair!" << endl;
	}
	else if (x == 3) {
		cout << "You have a three of a kind!" << endl;
	}
	else if (x == 4) {
		cout << "You have a straight!" << endl;
	}
	else if (x == 5) {
		cout << "You have a flush!" << endl;
	}
	else if (x == 6) {
		cout << "You have a full house!" << endl;
	}
	else if (x == 7) {
		cout << "You have four of a kind!" << endl;
	}
	else if (x == 8) {
		cout << "You have a straight flush!" << endl;
	}
	else if (x == 9) {
		cout << "You have a royal flush!" << endl;
	}
}
