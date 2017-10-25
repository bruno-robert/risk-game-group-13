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
#include "Map.h"    
#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>  
#include <sstream>
using namespace std;

class Attack {
public:
    Attack();
    bool yesNoQuestion(string question);
    void attackLoop(vector<Player> playerList, Player attacker, Map map);
    string attackFrom(Player attacker, Map map);
    string toAttack(vector<Player> playerList, Player attacker, Map map, CountryNode* attackingCountry);
    bool verifyBelonging(Player caller, string country);
    int attackerAmountOfDice(CountryNode* country);
    int defenderAmountOfDice(CountryNode* country);
    void compareDice(int attackerDice[], int defenderDice[], int attackerDiceAmount, int defenderDiceAmount);
    void printDiceResults(int results[], int amountOfDice);
    void reverseSortDiceResults(int diceResults[]);
    void conqueredCountry(CountryNode* attackingCountry, CountryNode* defendingCountry, Player attacker, Player defender);
    Player getAssociatedPlayer(vector<Player> playerList, string country);
            
};

#endif /* ATTACK_H */

