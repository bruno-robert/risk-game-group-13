//============================================================================
// Name        : Part5_2.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.3
// Copyright   : GNU Public license 3
// Description : Header file for the Card, Hand and Deck class of Part5. 
//============================================================================
#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;


class Card{					//The type of the card is a integer used to identify between infantry, cavalry and artillery.

public:
	Card(int type);
	Card();
	int getType();

private:
	int type;				
};

class Deck {				//The deck is a vector of card.

public:
	Deck(int countries);
	Card draw();			//Allows the removal of a random card from the vector.
	int getSize();			//Returns the size of the vector

private:
	vector<Card> link;
};

class Hand {				//The deck is a vector of card.

public:
	int exchange();
	void add(Card card);	//Allows the addition of a card to the vector.
	int getSize();			//Returns the size of the vector

private:
	vector<Card> playerHand;
	int numOfExchange = 1;		//Keeps tab of the number of exchange through that hand
};