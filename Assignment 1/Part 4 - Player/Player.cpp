//============================================================================
// Name        : Player.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1
// Copyright   : GNU Public license 3
// Description : Player class responsible for creating player object which owns a hand of cards, a dice rolling facility, and a collection of occupied countries.
//               Implementing reinforce(), attack(), fortify() player actions according to official game rule.
//============================================================================

#include "Player.h"


using namespace std;

// Player Class


Player::Player(){ //Default constructor create empty players

}

Player::Player(vector<CountryNode *> ownedCountry, Hand hand, Dice dice, PlayerStrategyPattern *psp){
	this->ownedCountry = ownedCountry;
	this->hand = hand;
	this->dice = dice;
    this-> psp = psp;
}


void Player::reinforce(){
	
	cout << "You are reinforcing. " << endl;
}

void Player::attack(){

	cout << "You are attacking. " << endl;
}

void Player::fortify(){

	cout << "You are fortifying. " << endl;
}

vector<CountryNode *> Player::getCountry(){

	return ownedCountry;
}
Hand Player::getHand(){
	return this->hand;
}
Dice Player::getDice(){
	return this->dice;
}
int Player::getPlayerID() {
	return this->playerID;
}
Hand& Player::getHandByRef() {
	return this->hand;
}
Dice& Player::getDiceByRef() {
	return this->dice;
}
vector<CountryNode *>& Player::getCountryByRef() {

	return ownedCountry;
}
void Player::setCountry(vector<CountryNode *> ownedCountry){
	this->ownedCountry = ownedCountry;
}
void Player::setPlayerID(int id) {
	this->playerID = id;
}
