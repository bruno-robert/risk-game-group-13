#include <random>
#include <iostream>
#include <vector>
#include "Map.h"
#include "dice.h"
#include "Part5_Driver.h"

#ifndef __Part_4_H_INCLUDED__
#define __Part_4_H_INCLUDED__

using namespace std;

class Player{
public:

	Player();
	Player(vector<CountryNode *> ownedCountry, Hand hand, Dice dice, int playerID);
	void reinforce(int army, CountryNode countryNode);
	void attack(CountryNode countryNode);
	void fortify(CountryNode fromCountry, CountryNode toCountry);


private:
	vector<CountryNode *> ownedCountry;
	Hand hand;
	Dice dice;
	int playerID;
	void setOwnedCountry(Map map);
};

#endif