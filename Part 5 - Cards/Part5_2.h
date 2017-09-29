//------------------------------------------------
//Comp 345-D
//Assignment 1 - Part 5 version 2
//Simon Roy - Team 13 - ID 40030996
//------------------------------------------------
#pragma once

#include <iostream>
#include <vector>
using namespace std;


class Card{

public:
	Card(int type);
	Card();
	int getType();

private:
	int type;
};

class Deck {

public:
	Deck(int countries);
	Card draw();
	int getSize();			//Returns the size of the vector

private:
	vector<Card> link;
};

class Hand {

public:
	int exchange();
	void add(Card card);
	int getSize();			//Returns the size of the vector

private:
	vector<Card> playerHand;
	int numOfExchange = 1;
};