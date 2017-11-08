//
//  PSPatern.hpp
//  Risk-fresh-start
//
//  Created by Bruno Robert on 31/10/2017.
//  Copyright © 2017 Bruno Robert. All rights reserved.
//

#ifndef PSPatern_hpp
#define PSPatern_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Map.h"
#include "ReinforcePhase.h"
#include "Attack.h"
class Player;
#include "Player.h"

using namespace std;
//this is to be the parent class of Human Agressive and Benevolent
class PlayerStrategyPattern {
public:
    PlayerStrategyPattern();
    virtual ~PlayerStrategyPattern();

    virtual bool getFortifyValues(int * startingCountry, int * destinationCountry, int * numberOfTroopsToMove, Map& m, int player)= 0;
  
    virtual void executeFortify(Player& user)= 0;
    virtual void executeAttack(Player& user)= 0;
    virtual void executeReinforce(Player& user)= 0;

};
//subclass of PlayerStrategyPattern
class Human : public PlayerStrategyPattern{
    static int countryNameToID(string countryName, Map& m);
public:
    
    Human();
    ~Human();
    //Takes human input to changes the values of the given variables pointed to pointers. Before returning the function verifies that the given values are valid.
	bool getFortifyValues(int * startingCountry, int * destinationCountry, int * numberOftroopsToMove, Map& m, Player & player);//TODO: Finish Implementing
    void executeFortify(Player& user);
    void executeAttack(Player& user);
    void executeReinforce(Player& user);
    
};
//subclass of PlayerStrategyPattern

class Aggressive : public PlayerStrategyPattern {

public:
	Aggressive();
	bool getFortifyValues(int * startingCountry, int * destinationCountry, int * numberOftroopsToMove, Map& m, Player & player);//TODO: Finish Implementing
	void executeReinforce(Player& user);
	void executeAttack(Player& user);
	void executeFortify(Player& user);
};

//subclass of PlayerStrategyPattern

class Benevolant : public PlayerStrategyPattern {

public:
	Benevolant();
	bool getFortifyValues(int * startingCountry, int * destinationCountry, int * numberOftroopsToMove, Map& m, Player & player);//TODO: Finish Implementing
	void executeReinforce(Player& user);
	void executeAttack(Player& user);
	void executeFortify(Player& user);
};


#endif /* PSPatern_hpp */
