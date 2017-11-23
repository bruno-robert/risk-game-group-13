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
#include "Subject.h"
#include "PhaseObserver.h"
#include "GameStatsObserver.h"

using namespace std;

// Player Class

int Player::numberOfPlayers = 0;

Player::Player(){ //Default constructor create empty players
    playerID = ++numberOfPlayers;
}

Player::~Player()
{
    
}

Player::Player(vector<CountryNode *> ownedCountry, Hand hand, Dice dice, PlayerStrategyPattern *psp){
    this->ownedCountry = ownedCountry;
    this->hand = hand;
    this->dice = dice;
    this-> psp = psp;
    playerID = ++numberOfPlayers;
}

/**
 Adds the given country to the players list of owned countries and adjusts the countries OwnedBy variable.
 The function also checks if the country was previously owned by a Player in the given list. If yes, then if will remove the country from that players list of owned countries
 
 @param country the country to add
 @param playerList list of players in the game
 */
void Player::addCountryToOwned(CountryNode* country, vector<Player*> playerList) {
    
    Player* playerLost = NULL;
    for (Player* p : playerList) {
        if (p->getPlayerID() == country->getOwnedBy()) {
            playerLost = p;
        }
    }
    if (playerLost != NULL) {
        vector<CountryNode *> defendersCountries = playerLost->getCountryByRef();
        defendersCountries.erase(remove(defendersCountries.begin(), defendersCountries.end(), country), defendersCountries.end());
        playerLost->setCountry(defendersCountries);
    }
    ownedCountry.push_back(country);
    country->setOwnedBy(this->getPlayerID());
    notify("Map Change");
	notify("Game Stats");

}

void Player::reinforce(PhaseObserver &po){
	Reinforce reinforcementObj;
	po.setReinforcePhaseSubject(&reinforcementObj);
    psp->executeReinforce((*this),reinforcementObj);
}

void Player::attack(Map& m, vector<Player*> playerList, PhaseObserver &po, GameStatsObserver &gso){
	Attack attackObj;
	po.setAttackPhaseSubject(&attackObj);
	gso.setAttackSubject(&attackObj);
    psp->executeAttack((*this), m, playerList,attackObj);
}

/**
 Players fortify method. Call the appropriate PSP.fortify method to get values, then it moves the troups.
 
 */
void Player::fortify(PhaseObserver &po){
	FortificationPhase fortificationObj;
	po.setFortifyPhaseSubject(&fortificationObj);
    psp->executeFortify((*this),fortificationObj);
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
const int Player::getPlayerID() const{
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

PlayerStrategyPattern* Player::getStrategy() {

    return psp;
}

void Player::setCountry(vector<CountryNode *> ownedCountry){
    this->ownedCountry = ownedCountry;
}
void Player::setPlayerID(int id) {
    this->playerID = id;
}

//----------------
//country Sorting
//----------------


void Player::copyCountList(vector<CountryNode *>& a, int iBegin, int iEnd, vector<CountryNode *>& b)
{
    b.clear();//empties out vecotr
    for(int k = iBegin; k < iEnd; k++) {
        b.push_back(a.at(k));
    }
    
}

// Left source half is a[ iBegin:iMiddle-1].
// Right source half is a[iMiddle:iEnd-1   ].
// Result is            b[ iBegin:iEnd-1   ].
void Player::topDownCountMerge(vector<CountryNode*>& a, int iBegin, int iMiddle, int iEnd, vector<CountryNode*>& b)
{
    int i = iBegin;
    int j = iMiddle;
    
    // While there are elements in the left or right runs...
    for (int k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || (*a.at(i)).getNumberOfTroops() <= (*a.at(j)).getNumberOfTroops())) {
            b.at(k) = a.at(i);
            i++;
        } else {
            b.at(k) = a.at(j);
            j++;
        }
    }
}

// Sort the given run of vet a using vect b as a source.
// iBegin is inclusive; iEnd is exclusive (a.at(iEnd) is not in the set).
void Player::topDownCountSplitMerge(vector<CountryNode*>& b, int iBegin, int iEnd, vector<CountryNode*>& a)
{
    if(iEnd - iBegin < 2) {// if run size == 1
        return;//   consider it sorted
    }
    
    // split the run longer than 1 item into halves
    int iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from vector a into b
    topDownCountSplitMerge(a, iBegin,  iMiddle, b);  // sort the left  run
    topDownCountSplitMerge(a, iMiddle,    iEnd, b);  // sort the right run
    // merge the resulting runs from vector b into a
    topDownCountMerge(b, iBegin, iMiddle, iEnd, a);
}

void Player::inverseOwnedCountries() {
    vector<CountryNode*> temp = ownedCountry;
    ownedCountry.clear();
    for(int i = (int)(temp.size()-1); i >= 0;i--) {
        ownedCountry.push_back(temp.at(i));
    }
}

// vector a has the items to sort; vect b is a work array.
void Player::topDownCountMergeSort()
{
    vector<CountryNode*>& a = ownedCountry;
    vector<CountryNode*> temp;
    vector<CountryNode*>& b = temp;//just setting it to an empty vect
    int n = (int)a.size();
    copyCountList(a, 0, n, b);           // duplicate vect a into b
    topDownCountSplitMerge(b, 0, n, a);   // sort data from b into a
    inverseOwnedCountries();
}
