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
class Player;
#include "Player.h"
#include "Map.h"
#include "ReinforcePhase.h"
#include "Attack.h"


using namespace std;
//this is to be the parent class of Human Agressive and Benevolent
class PlayerStrategyPattern {
public:
    PlayerStrategyPattern();
    virtual ~PlayerStrategyPattern();

    
  
    virtual void executeFortify(Player& user)= 0;
    virtual void executeAttack(Player& user)= 0;
    virtual void executeReinforce(Player& user)= 0;
    bool isCountryInVector(int a, vector<CountryNode*> vect);
    vector<CountryNode*> getOwnedIsland(CountryNode* startCountry, vector<CountryNode*>& ownedCountryIsland, const Player& p);
    vector<CountryNode*> recursiveGetPathToBiggest(CountryNode* startingCountry, CountryNode* destinationCountry, const Player& p, vector<CountryNode*>& visitedCountries);
    void getPathToBiggest(CountryNode ** startingCountry, CountryNode ** destinationCountry, const Player& p);
};
//subclass of PlayerStrategyPattern
class Human : public PlayerStrategyPattern{
    static int countryNameToID(string countryName, Player& p);
    CountryNode* getCountryById(vector<CountryNode*> countryList, int id);
public:
    
    Human();
    ~Human();
    void executeFortify(Player& user);
    void executeAttack(Player& user);
    void executeReinforce(Player& user);
    
};
//subclass of PlayerStrategyPattern

class Aggressive : public PlayerStrategyPattern {

public:
	Aggressive();
    ~Aggressive();
	void executeReinforce(Player& user);
	void executeAttack(Player& user);
	void executeFortify(Player& user);
};

//subclass of PlayerStrategyPattern

//TODO: Change 'Benevolant' to 'Benevolent'
class Benevolant : public PlayerStrategyPattern {

public:
	Benevolant();
    ~Benevolant();
	void executeReinforce(Player& user);
	void executeAttack(Player& user);
	void executeFortify(Player& user);
};


#endif /* PSPatern_hpp */
