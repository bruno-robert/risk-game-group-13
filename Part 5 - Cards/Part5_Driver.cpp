//============================================================================
// Name        : Part5_Driver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.3
// Copyright   : GNU Public license 3
// Description : Driver for Part5 of A1. It's purpose is to test the Card, Deck and Hand class and their core functions(draw and exchange)
//============================================================================

#include "Cards.h"

using namespace std;

int main() {

	cout << "Testing the Card, Deck and Hand class...\n" << endl;


	//Testing Card class


	cout << "Testing the Card class:" << endl;

	cout << "Creating a card of each type... " << endl;

	Card c1(1);		//Creating three card of the 3 types
	Card c2(2);
	Card c3(3);

	cout << "\nValue of c1: " << c1.getType() << endl;
	cout << "Value of c2: " << c2.getType() << endl;
	cout << "Value of c3: " << c3.getType() << endl;


	//Testing the Deck class


	cout << "\nTesting the Deck class:" << endl;
	cout << " How many countries are in the map?\n" << endl;
	int countries;
	cin >> countries;
	Deck deck = Deck(countries);	//Building a deck from a user given size


	int infantry = 0, cavalry = 0, artillery = 0;

	for (int i = 0; i < countries;i++) {	//Draw all of the cards of my deck
		Card drew = deck.draw();

		switch (drew.getType()) {	//Checks each card in the deck to keep tabs of what has been drawn
		case 1:infantry++;
			break;
		case 2:cavalry++;
			break;
		case 3:artillery++;
			break;
		}
	}
	deck.draw();	//Calling the draw method after exhausting the deck

	cout << "\nNumber of infantry: " << infantry << endl;
	cout << "Number of cavalry: " << cavalry << endl;
	cout << "Number of artillery: " << artillery << endl;
	cout << "Size of the deck: " << deck.getSize() << endl;


	//Testing the Hand method


	cout << "How many countries are in the map?\n" << endl;
	int countries2;
	cin >> countries2;
	Deck deck2 = Deck(countries2);		//Building a deck from a user given size


	cout << "The hand will receive up to four cards from the deck then call the exchange method. This will be done a total of 4 times...\n" << endl;

	Hand player1Hand;
	for (int i = 0; i < 4;i++) {		//Calling the exchange method 4 time

		while (player1Hand.getSize() < 4 && deck2.getSize() > 0) {
			player1Hand.add(deck2.draw());
		}
		cout << "\nnumber of card in the players hand: " << player1Hand.getSize() << endl;
		cout << "number of unit returned: " << player1Hand.exchange() << "\n"<<endl;
	}
<<<<<<< HEAD
    return 0;
};
=======
};
>>>>>>> master
