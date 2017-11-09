//============================================================================
// Name        : Attack.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, C Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1
// Copyright   : GNU Public license 3
// Description : Attack class is responsible for players choosing from which country to attack from, choosing, which country to attack,
//               choosing how many dice to roll, comparing the rolled dice, and adding/removing troops as necessary 
//============================================================================

#ifndef ATTACK_H
#define ATTACK_H

#include "Player.h" 
#include "Subject.h"
#include "Map.h"    
#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>  
#include <sstream>
using namespace std;

class Attack : public Subject {
public:
    Attack();
    ~Attack();
    bool yesNoQuestion(string question);
    void attackLoop(vector<Player*> playerList, Player* attacker, Map* map);
    string attackFrom(Player* attacker, Map* map);
    string toAttack(vector<Player*> playerList, Player* attacker, Map* map, CountryNode* attackingCountry);
    bool verifyBelonging(Player* caller, string country);
    int attackerAmountOfDice(CountryNode* country);
    int defenderAmountOfDice(CountryNode* country);
    void compareDice(int attackerDice[], int defenderDice[], int attackerDiceAmount, int defenderDiceAmount);
    void printDiceResults(int results[], int amountOfDice);
    void reverseSortDiceResults(int diceResults[]);
    void conqueredCountry(CountryNode* attackingCountry, CountryNode* defendingCountry, Player* attacker, Player* defender);
    Player* getAssociatedPlayer(vector<Player*> playerList, string country);
    
    //Setters and getters
    void setPlayerListData(vector<Player*> playerListData);
    void setAttackingCountryData(CountryNode* attackingCountryData);
    void setDefendingCountryData(CountryNode* defendingCountryData);
    void setAttackingPlayerData(Player* attackingPlayerData);
    void setDefendingPlayerData(Player* defendingPlayerData);
    void setMapData(Map* map);
    
    vector<Player*> getPlayerListData();
    CountryNode* getAttackingCountryData();
    CountryNode* getDefendingCountryData();
    Player* getAttackingPlayerData();
    Player* getDefendingPlayerData();
    Map* getMapData();

	//Notify calls
	void attackNotify(CountryNode* attacker, CountryNode* defender, int numDiceAttack, int numDiceDefend);
	void attackNotifyConquering(CountryNode* attacker, CountryNode* defender, int unitsMoved);
	void attackNotifyStart(Player& user);
    
private:
    vector<Player*> playerListData;
    CountryNode* attackingCountryData;
    CountryNode* defendingCountryData;
    Player* attackingPlayerData;
    Player* defendingPlayerData; 
    Map* mapData;
};

#endif /* ATTACK_H */

