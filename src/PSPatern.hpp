//
//  PSPatern.hpp
//  Risk-fresh-start
//
//  Created by Bruno Robert on 31/10/2017.
//  Copyright © 2017 Bruno Robert. All rights reserved.
//

#ifndef PSPatern_hpp
#define PSPatern_hpp

//used for generating random numbers
#include <ctime>
#include <cstdlib>

#include <stdio.h>
#include <vector>
#include <iostream>
class Player;
#include "Player.h"
#include "Map.h"
class FortificationPhase;
class Attack;
class Reinforce;
#include "ReinforcePhase.h"
#include "Attack.h"
#include "Subject.h"
#include "FortificationPhase.hpp"


using namespace std;
//this is to be the parent class of Human Agressive and Benevolent
class PlayerStrategyPattern : public Subject {

	string name;
public:
	virtual string getName() = 0;
	
	PlayerStrategyPattern();
	virtual ~PlayerStrategyPattern();

	virtual void executeFortify(Player& user, FortificationPhase& fortificationObj) = 0;
	virtual void executeAttack(Player& user, Map& map, vector<Player*> playerList, Attack& attackObj) = 0;
	virtual void executeReinforce(Player& user, Reinforce& reinforceObj) = 0;
	bool isCountryInVector(int a, vector<CountryNode*> vect);
	vector<CountryNode*> recursiveGetPathToBiggest(CountryNode* startingCountry, CountryNode* destinationCountry, const Player& p, vector<CountryNode*>& visitedCountries);
	vector<CountryNode*> getOwnedIsland(CountryNode* startCountry, vector<CountryNode*>& ownedCountryIsland, const Player& p);
	void getPathToBiggest(CountryNode ** startingCountry, CountryNode ** destinationCountry, const Player& p);
};
//subclass of PlayerStrategyPattern
class Human : public PlayerStrategyPattern {
	static int countryNameToID(string countryName, Player& p);
	CountryNode* getCountryById(vector<CountryNode*> countryList, int id);
public:

	Human();
	~Human();
	void executeFortify(Player& user, FortificationPhase& fortificationObj);
	void executeAttack(Player& user, Map& map, vector<Player*> playerList, Attack& attackObj);
	void executeReinforce(Player& user, Reinforce& reinforceObj);

};
//subclass of PlayerStrategyPattern

class Aggressive : public PlayerStrategyPattern {

	string name = "aggressive";
public:
	 string getName() {
		return "aggressive";
	}

	Aggressive();
	~Aggressive();
	void executeReinforce(Player& user, Reinforce& reinforceObj);
	void executeAttack(Player& user, Map& map, vector<Player*> playerList, Attack& attackObj);
	void executeFortify(Player& user, FortificationPhase& fortificationObj);
};

//subclass of PlayerStrategyPattern

class Benevolant : public PlayerStrategyPattern {

	string name = "benevolant";
public:
	 string getName() {
		return "benevolant";
	}
	Benevolant();
	~Benevolant();
	void executeReinforce(Player& user, Reinforce& reinforceObj);
	void executeAttack(Player& user, Map& map, vector<Player*> playerList, Attack& attackObj);
	void executeFortify(Player& user, FortificationPhase& fortificationObj);
};

class Random : public PlayerStrategyPattern {
    
	string name = "random";
public:
	 string getName() {
		return "random";
	}

    Random();
    ~Random();
    void executeReinforce(Player& user, Reinforce& reinforceObj);
    void executeAttack(Player& user, Map& map, vector<Player*> playerList, Attack& attackObj);
    void executeFortify(Player& user, FortificationPhase& fortificationObj);
};

class Cheater : public PlayerStrategyPattern {

	string name = "cheater";
public:
	 string getName() {
		return "cheater";
	}
    Cheater();
    ~Cheater();
    void executeReinforce(Player& user, Reinforce& reinforceObj);
    void executeAttack(Player& user, Map& map, vector<Player*> playerList, Attack& attackObj);
    void executeFortify(Player& user, FortificationPhase& fortificationObj);
};

#endif /* PSPatern_hpp */