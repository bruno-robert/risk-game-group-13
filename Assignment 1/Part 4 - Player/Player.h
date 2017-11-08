//============================================================================
// Name        : Player.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1
// Copyright   : GNU Public license 3
// Description : Player class responsible for creating player object which owns a hand of cards, a dice rolling facility, and a collection of occupied countries.
//               Implementing reinforce(), attack(), fortify() player actions according to official game rule.
//============================================================================

#ifndef __Player_H_INCLUDED__
#define __Player_H_INCLUDED__

#include <iostream>
#include <vector>
#include "Map.h" //Part 1
#include "dice.h" //Part 3
#include "Cards.h" //Part 5
#include "Subject.h"
class PlayerStrategyPattern;
#include "PSPatern.hpp"


using namespace std;

class Player{
    vector<CountryNode *> ownedCountry; //Vector of player's occupied countries
    Hand hand;
    Dice dice;
    int playerID;
    static int numberOfPlayers;
    PlayerStrategyPattern * psp;
public:

	Player(); //Default Constructor
	~Player();
	Player(vector<CountryNode *> ownedCountry, Hand hand, Dice dice, PlayerStrategyPattern * psp); //Complete Constructor
	vector<CountryNode *> getCountry(); //Getters
	Hand getHand();
	Dice getDice();
	int getPlayerID();
	Hand& getHandByRef();
	Dice& getDiceByRef();
	vector<CountryNode *>& getCountryByRef();
	void reinforce();//Player action methods
	void attack();
	bool fortify(Map& m);
    void setCountry(vector<CountryNode *> ownedCountry);
	void setPlayerID(int id);
};

#endif
