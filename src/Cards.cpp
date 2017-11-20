//============================================================================
// Name        : Cards.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.3
// Copyright   : GNU Public license 3
// Description : Source file for the Card, Hand and Deck class of Part5.
//============================================================================
//Library usage

#include "Cards.h"

/* Card class */

//constructors

Card::Card() {};

Card::Card(int type) { this->type = type; }



int Card::getType() {
	return type;
}


/* Deck class and Draw() method */


	//Constructor for Deck

Deck::Deck(int countries) {
	fillDeck(countries);
}

Deck::Deck() {}

void Deck::fillDeck(int countries)
{
	cout << "\nCreating a deck of size " << countries << " using my defined constructor..." << endl;

	if (countries % 3 == 1) {
		link.push_back(Card(1));
	}
	if (countries % 3 == 2) {
		link.push_back(Card(1));
		link.push_back(Card(2));
	}

	for (int i = 0; i < (countries / 3); i++) {		//Splits the deck 3 way for the 3 types of card
		link.push_back(Card(1));
		link.push_back(Card(2));
		link.push_back(Card(3));
	}
}

//Draw method

Card Deck::draw() {
	Card drew;
	int size = (int)link.size();
	if (size > 0) {

		srand((int)time(NULL));		//Random generation part. Gets me a random adress in my vector
        //rand() % size;// FIXME: un-used expression result
		int luck = rand() % size;

		drew = link.at(luck);
		//std::cout << "Value of luck: " << luck << endl;		Add this line if you to get the random value generated
		int value = link.at(luck).getType();
		link.erase(link.begin() + luck);

		switch (value) {
		case 1: cout << "The player drew a infantry card." << endl;
			break;
		case 2:cout << "The player drew a cavalry card." << endl;
			break;
		case 3:cout << "The player drew a artillery card." << endl;
			break;
		}
	}
	else
		cout << "The deck is empty.\n";
	return drew;
}

//getSize method for Deck

int Deck::getSize() { return (int)link.size(); };


/* Hand class methods and the exchange method */

int Hand::exchange() {
	int unitReceived;
	int size = getSize();
	if (size > 2) {				//Makes sure that I have enough card to try an exchange

		int infantry = 0, cavalry = 0, artillery = 0;

		for (int i = 0;i < size;i++) {					//Gathers what kind of card is my hand made of
			switch (playerHand.at(i).getType()) {
			case 1:infantry++;
				break;
			case 2:cavalry++;
				break;
			case 3:artillery++;
				break;
			}
		}

		//The following list of if/else statements are here to select what kind of exchange will be made.


		//Infantry check

		if (infantry >= 3) {
			cout << "\nThe player traded 3 infantry cards for " << (numOfExchange * 5) << " units." << endl;		// 3 infantry

			exchangeString = ("The player traded 3 infantry cards for " + to_string(numOfExchange * 5) + " units.");
			int num = 0;
			while (num < 3) {
				int i = 0;
				while (playerHand.at(i).getType() != 1)
					i++;
				playerHand.erase(playerHand.begin() + i);
				num++;
			}
			return unitReceived = numOfExchange++ * 5;
		}

		//Cavalry check

		else if (cavalry >= 3) {
			exchangeString = ("The player traded 3 cavalry cards for " + to_string(numOfExchange * 5) + " units.");
			cout << "\nThe player traded 3 cavalry cards for " << (numOfExchange * 5) << " units." << endl;		// 3 cavalry
			int num = 0;
			while (num < 3) {
				int i = 0;
				while (playerHand.at(i).getType() != 2)
					i++;
				playerHand.erase(playerHand.begin() + i);
				num++;
			}
			return unitReceived = numOfExchange++ * 5;
		}

		//Artillery check

		else if (artillery >= 3) {
			exchangeString = ("The player traded 3 artillery cards for " + to_string(numOfExchange * 5) + " units.");
			cout << "\nThe player traded 3 artillery cards for " << (numOfExchange * 5) << " units." << endl;		// 3 artillery
			int num = 0;
			while (num < 3) {
				int i = 0;
				while (playerHand.at(i).getType() != 3)
					i++;
				playerHand.erase(playerHand.begin() + i);
				num++;
			}
			return unitReceived = numOfExchange++ * 5;
		}

		//One of each check

		else if (infantry >= 1 && cavalry >= 1 && artillery >= 1) {
			exchangeString = ("The player traded 1 card of each type for " + to_string(numOfExchange * 5) + " units.");
			cout << "\nThe player traded 1 card of each type for " << (numOfExchange * 5) << " units." << endl;		// 1 of each
			int num = 0;
			int type[3] = { 0,0,0 };

			while (num < 3) {
				int i = 0;
				while (playerHand.at(i).getType() == type[0] || playerHand.at(i).getType() == type[1])
					i++;
				type[num] = playerHand.at(i).getType();
				playerHand.erase(playerHand.begin() + i);
				num++;
			}
			return unitReceived = numOfExchange++ * 5;
		}

		//If none of the combination worked

		else
			cout << "you do not have the right combination of cards to make an exchange." << endl;
		return 0;

	}
	else
		cout << "you do not have enough card to make an exchange." << endl;		//If I do not have enough cards to make an exchange
	return 0;
}

//Add() and getSize() methods

void Hand::add(Card card) { playerHand.push_back(card); };		//Allows for the adition of a card to the hand

int Hand::getSize() { return (int)playerHand.size(); };

string Hand::getExchangeString()
{
	return exchangeString;
}

vector<Card> Hand::getPlayerHand()
{
    return playerHand;
}
