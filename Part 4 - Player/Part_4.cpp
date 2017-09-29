#include <iostream>
#include <vector>
#include "Part_4.h"


using namespace std;

// Player Class


Player::Player(vector<CountryNode *> ownedCountry, Hand hand, Dice dice, int playerID){
	this->ownedCountry = ownedCountry;
	this->hand = hand;
	this->dice = dice;
	this->playerID = playerID;
}


void Player::reinforce(int army, CountryNode countryNode){
	
	cout << "You are reinforcing " << countryNode.getCountName() << "by " << army << " units" << endl;
}

void Player::attack(CountryNode countryNode){

	cout << "You are attacking " << countryNode.getCountName() << endl;
}

void Player::fortify(CountryNode fromCountry, CountryNode toCountry){

	cout << "You are moving armies from " << fromCountry.getCountName() << " to " << toCountry.getCountName() << endl;
}

