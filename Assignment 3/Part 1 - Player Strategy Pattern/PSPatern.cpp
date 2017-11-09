//
//  PSPatern.cpp
//  Risk-fresh-start
//
//  Created by Bruno Robert on 31/10/2017.
//  Copyright © 2017 Bruno Robert. All rights reserved.
//

#include "PSPatern.hpp"
using namespace std;

PlayerStrategyPattern::PlayerStrategyPattern() {

}

PlayerStrategyPattern::~PlayerStrategyPattern() {
    
}

/**
 Checks if there is a country with a given id in the given vector
 @param a the id of the give ncountry
 @param vect the vector of countries to be checked
 */
bool PlayerStrategyPattern::isCountryInVector(int a, vector<CountryNode*> vect) {
    for(CountryNode* country: vect) {
        if (country->getCountryId() == a) {
            return true;
        }
    }
    
    return false;
}

}

Human::Human() : PlayerStrategyPattern(){

}

Human::~Human() {

}

/**
 Takes a string and a Map and returns the Id of the country with the given name
 If the country doesn't exists, retursn -1
 @param countryName Name of the country
 @param p Player Object
 @return the ID of the country with name countryName. If the country doesn't exist, returns -1
 */
int Human::countryNameToID(string countryName, Player& p){
	vector<CountryNode*> cl = p.getCountryByRef();
	for (vector<CountryNode*>::iterator country = cl.begin(); country != cl.end(); country++) {
		if ((*country)->getCountName() == countryName) {
			return (*country)->getCountryId();
		}
	}

	return -1;//error, country not found
}
CountryNode * Human::getCountryById(vector<CountryNode*> countryList, int id) {
	for (CountryNode* country : countryList) {
		if (country->getCountryId() == id) {
			return country;
		}
	}
	return NULL;
}

void Human::executeFortify(Player& user) {
	bool troopsMoved = false;
	while (!troopsMoved) {
		CountryNode* startingCountry = NULL;
		CountryNode* destinationCountry = NULL;
		int numberOfTroopsToMove;

		//Getting and checking starting country
		cout << "please select a starting country" << endl;
		//temporary varibales
		string inputString;
		while (true) {
			getline(cin, inputString);
			cin.ignore();
			//cin >> inputString;
			int startingCountryID = countryNameToID(inputString, user);
			startingCountry = getCountryById(user.getCountryByRef(), startingCountryID);
			//checks if the starting coutry is valid
			if ((startingCountryID >= 1) && (startingCountry != NULL) && (startingCountry->getOwnedBy() == user.getPlayerID()) && (startingCountry->getNumberOfTroops() > 1)) {
				break;
			}
			if (startingCountryID == -1) {
				cout << "We couldn't find your country. Please try again." << endl;
			}
			else {
				cout << "Sorry, the value you entered is not valid, please try again (the country could have to few troops):" << endl;
			}

		}

		//Getting and checking the destination country
		cout << "please select the destination country" << endl;
		while (true) {
			getline(cin, inputString);
			cin.ignore();
			//cin >> inputString;
			int destinationCountryID = countryNameToID(inputString, user);

			destinationCountry = getCountryById(user.getCountryByRef(), destinationCountryID);
			if ((destinationCountryID >= 1) && (destinationCountry != NULL) && (destinationCountry->getOwnedBy() == user.getPlayerID())) {
				break;
			}

			if (destinationCountryID == -1) {
				cout << "We couldn't find your country. Please try again." << endl;
			}
			else {
				cout << "Sorry, the value you entered is not valid, please try again (the country could have to few troops):" << endl;
			}
		}

		//checks the adjacency of both countries and promtps user for number of troop to move
		if (startingCountry->isCountAdjacent(destinationCountry->getCountryId())) {
			cout << "please enter the number of troops you want to move (value between 1 and " << startingCountry->getNumberOfTroops() << ":" << endl;
			while (true) {

				cin >> numberOfTroopsToMove;
				//if the number of troop is between 1 and the the number of troop in starting country -1
				if ((numberOfTroopsToMove >= 1) &&
					(numberOfTroopsToMove < startingCountry->getNumberOfTroops())){

					//Removing troups from startingcountry
					startingCountry->setNumberOfTroops(startingCountry->getNumberOfTroops() - numberOfTroopsToMove);

					//Adding troups to destinationCountry
					destinationCountry->setNumberOfTroops(destinationCountry->getNumberOfTroops() + numberOfTroopsToMove);

					troopsMoved = true;
					break;
				}


				cout << "Sorry, the number you entered is invalid, please try again:" << endl;
			}
		}
		if (!troopsMoved) {
			cout << "Sorry the countries are not adjacent" << endl;
		}




	}
}

void Human::executeAttack(Player& user, Map& map, vector<Player*> playerList) {

}

void Human::executeReinforce(Player& user) {
	Reinforce rein;
	rein.reinforceDistributions(user);
}

Aggressive::Aggressive() : PlayerStrategyPattern()
{

}

Aggressive::~Aggressive() {

}

void Aggressive::executeReinforce(Player& user) {


	//Finding the country with the most units and a target to attack
	int maxUnit = 0;
	int maxIndex = 0;

	for (int i = 0; i < user.getCountryByRef().size(); i++) {

		if (user.getCountryByRef().at(i)->getNumberOfTroops() > maxUnit) {

			vector<CountryNode*> AdjCountry = user.getCountryByRef().at(i)->getAdjCount();
			bool target = false;

			for (int j = 0; j < AdjCountry.size() && target == false; j++) {

				if (AdjCountry.at(j)->getOwnedBy() != user.getPlayerID()) {

					target = true;
					maxIndex = i;
					maxUnit = user.getCountryByRef().at(i)->getNumberOfTroops();
				}
			}
		}
	}
	Reinforce rein;
	int unitsReceived = rein.totalUnits(user);
	user.getCountryByRef().at(maxIndex)->setNumberOfTroops(maxUnit + unitsReceived);
	rein.reinforceNotify(user.getCountryByRef().at(maxIndex), unitsReceived);
}


void Aggressive::executeAttack(Player& user, Map& map, vector<Player*> playerList) {
	
	Attack attackObj;
	
	attackObj.attackNotifyStart(user);
	//Finds your strongest country

	int maxUnit = 0;
	int maxIndex = 0;

	for (int i = 0; i < user.getCountryByRef().size(); i++) {

		if (user.getCountryByRef().at(i)->getNumberOfTroops() > maxUnit) {

			vector<CountryNode*> AdjCountry = user.getCountryByRef().at(i)->getAdjCount();
			bool target = false;

			for (int j = 0; j < AdjCountry.size() && target == false; j++) {

				if (AdjCountry.at(j) != NULL && AdjCountry.at(j)->getOwnedBy() != user.getPlayerID()) {

					target = true;
					maxIndex = i;
					maxUnit = user.getCountryByRef().at(i)->getNumberOfTroops();
				}
			}
		}
	}
	CountryNode* attacker = user.getCountryByRef().at(maxIndex);

	cout << endl << attacker->getCountName() <<endl;

	for (int i = 0; i < attacker->getAdjCount().size() && attacker->getNumberOfTroops() > 1; i++) {
		
		CountryNode* defending = attacker->getAdjCount().at(i);

		if (defending->getCountryId() != attacker->getCountryId()){
			
			while (attacker->getNumberOfTroops() > 1 && defending->getNumberOfTroops() > 0) {
				
				int attackerDices = 0;

				if (attacker->getNumberOfTroops() > 3)
					attackerDices = 3;//FIXME: Value stored in attackerDices is never read...
				if (attacker->getNumberOfTroops() == 3)
					attackerDices = 2;//FIXME: Value stored in attackerDices is never read...
				if (attacker->getNumberOfTroops() == 2)
					attackerDices = 1;//FIXME: Value stored in attackerDices is never read...

				int defenderDices = attackObj.defenderAmountOfDice(defending);
				
				Player* defender = attackObj.getAssociatedPlayer(playerList,defending->getCountName());
				
				int attackerDiceResults[3];
				int defenderDiceResults[3];
				

				user.getDiceByRef().roll(attackerDiceResults, attackerDices);
				
				defender->getDiceByRef().roll(defenderDiceResults, defenderDices);

				
				//Print dice results
				cout << "Attacker rolled" << endl;
				attackObj.printDiceResults(attackerDiceResults, attackerDices);

				cout << "Defender rolled" << endl;
				attackObj.printDiceResults(defenderDiceResults, defenderDices);

				int mostRolled = defenderDices;
				if (mostRolled > attackerDices)
					mostRolled = attackerDices;

				attackObj.reverseSortDiceResults(attackerDiceResults);
				attackObj.reverseSortDiceResults(defenderDiceResults);


				int attackerLoses = 0;
				int defenderLoses = 0;

				for (int i = 0; i<mostRolled; i++){
					if (attackerDiceResults[i]>defenderDiceResults[i])
						defenderLoses++;
					else
						attackerLoses++;
				}
				attackObj.attackNotify(attacker, defending, attackerLoses, defenderLoses);
				cout << endl << attacker->getCountName() << " lost " << attackerLoses << " units and " << defending->getCountName() << " lost " << defenderLoses << " units." << endl;
				defending->setNumberOfTroops(defending->getNumberOfTroops() - defenderLoses);
				attacker->setNumberOfTroops(attacker->getNumberOfTroops() - attackerLoses);
			}
			if (defending->getNumberOfTroops() == 0 && attacker->getNumberOfTroops() > 1) {
				user.addCountryToOwned(defending, playerList);
				defending->setNumberOfTroops(1);
				attacker->setNumberOfTroops(attacker->getNumberOfTroops() - 1);
				attackObj.attackNotifyConquering(attacker, defending, 1);
				cout << endl << "The aggressive computer player conquered " << defending->getCountName() << "." << endl;
			}
		}

	}
}

void Aggressive::executeFortify(Player& user) {//TODO: Implement this @Bruno
	CountryNode* startingCountry = NULL;
	CountryNode* destinationCountry = NULL;
	int numberOfTroopsToMove;
	CountryNode * biggest = NULL;
	CountryNode * secondBiggest = NULL;


	//loop thourgh owned countries and find the bigggest one in terms of troups
	for (vector<CountryNode*>::iterator country = user.getCountryByRef().begin(); country != user.getCountryByRef().end(); country++){

		//if this is the first country, it's the biggest for now
		if (biggest == NULL) {
			biggest = *country;

			//if the country has more troops than the current biggest, set it to the biggest
		}
		else if ((*country)->getNumberOfTroops() >= biggest->getNumberOfTroops()) {
			secondBiggest = biggest;
			biggest = *country;
		}
	}
}
vector<CountryNode*> PlayerStrategyPattern::recursiveGetPathToBiggest(CountryNode* startingCountry, CountryNode* destinationCountry, const Player& p, vector<CountryNode*>& visitedCountries) {
    vector<CountryNode*> path;
    if(isCountryInVector(startingCountry->getCountryId(), visitedCountries)) {
        return path;
    } else {
        visitedCountries.push_back(startingCountry);
        for (CountryNode* adjCountry : startingCountry->getAdjCount()) {
            if(adjCountry->getOwnedBy() == p.getPlayerID() && adjCountry->getNumberOfTroops() > 1) {
                destinationCountry = adjCountry;
                path.push_back(startingCountry);
                path.push_back(destinationCountry);
                return path;
            }
        }
        for (CountryNode* adjCountry : startingCountry->getAdjCount()) {
            path = recursiveGetPathToBiggest(adjCountry, destinationCountry, p, visitedCountries);
            if(path.size()>0) {
                return path;
            }
        }
    }
    
    return path;
}

void PlayerStrategyPattern::getPathToBiggest(CountryNode ** startingCountry, CountryNode ** destinationCountry, const Player& p) {
    
}

void Aggressive::executeFortify(Player& user) {//TODO: Implement this @Bruno
    CountryNode* startingCountry = NULL;
    CountryNode* destinationCountry = NULL;
    int numberOfTroopsToMove = -1;
    
    //sort the user's countries
    user.topDownCountMergeSort();
    
    for(CountryNode* currentCountry : user.getCountryByRef() ) {
        bool hasEnemy = false;
        for(CountryNode* adjCountry :currentCountry->getAdjCount()) {
            if(adjCountry->getOwnedBy() != user.getPlayerID()) {
                hasEnemy = true;
                break;
            }
        }
        
        if(hasEnemy) {
            startingCountry = currentCountry;
            getPathToBiggest(&startingCountry, &destinationCountry, user);
            
            if(startingCountry != NULL && destinationCountry != NULL) {
                //Removing troups from startingcountry
                startingCountry->setNumberOfTroops(startingCountry->getNumberOfTroops() - numberOfTroopsToMove);
                
                //Adding troups to destinationCountry
                destinationCountry->setNumberOfTroops(destinationCountry->getNumberOfTroops() + numberOfTroopsToMove);
                return;
            }
        }//else move to the next country
        startingCountry = NULL;
    }
    
    
    
    
    
    //If the biggest country is not adjeacent to an enemy country, find closes enemy country and move troups towards that

    if(numberOfTroopsToMove >= 1) {
        //Removing troups from startingcountry
        startingCountry->setNumberOfTroops(startingCountry->getNumberOfTroops() - numberOfTroopsToMove);
        
        //Adding troups to destinationCountry
        destinationCountry->setNumberOfTroops(destinationCountry->getNumberOfTroops() + numberOfTroopsToMove);
    }
    
}


Benevolant::Benevolant() : PlayerStrategyPattern()
{

}

Benevolant::~Benevolant() {

}

void Benevolant::executeReinforce(Player& user) {


	//Getting the number of units for my player
	Reinforce unitsReinforced;
	int units = unitsReinforced.totalUnits(user);

	//Finding the country with the most units and a target to attack

	while (units != 0) {

		int leastUnit = user.getCountryByRef().at(0)->getNumberOfTroops();
		int leastIndex = 0;

		for (int i = 0; i < user.getCountryByRef().size(); i++) {

			if (user.getCountryByRef().at(i)->getNumberOfTroops() < leastUnit) {
				leastIndex = i;
				leastUnit = user.getCountryByRef().at(i)->getNumberOfTroops();
			}
		}
		user.getCountryByRef().at(leastIndex)->setNumberOfTroops(leastUnit + 1);
		units--;
	}
}



void Benevolant::executeAttack(Player& user, Map& map, vector<Player*> playerList) {


}


void Benevolant::executeFortify(Player& user) {
	//TODO: Implement this @Bruno

}
