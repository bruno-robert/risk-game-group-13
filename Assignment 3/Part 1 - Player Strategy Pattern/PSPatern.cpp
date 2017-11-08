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
        if((*country)->getCountName() == countryName) {
            return (*country)->getCountryId();
        }
    }
    
    return -1;//error, country not found
}
CountryNode * Human::getCountryById(vector<CountryNode*> countryList, int id) {
    for(CountryNode* country : countryList) {
        if (country->getCountryId() == id) {
            return country;
        }
    }
    return NULL;
}

void Human::executeFortify(Player& user) {
    bool troopsMoved = false;
    while(!troopsMoved) {
        CountryNode* startingCountry = NULL;
        CountryNode* destinationCountry = NULL;
        int numberOfTroopsToMove;
        
        //Getting and checking starting country
        cout << "please select a starting country" << endl;
        //temporary varibales
        string inputString;
        while(true) {
            getline( cin, inputString );
            cin.ignore();
            //cin >> inputString;
            int startingCountryID = countryNameToID(inputString, user);
            startingCountry = getCountryById(user.getCountryByRef(), startingCountryID);
            //checks if the starting coutry is valid
            if((startingCountryID >= 1) && (startingCountry != NULL) && (startingCountry->getOwnedBy() == user.getPlayerID()) && (startingCountry->getNumberOfTroops() > 1)) {
                break;
            }
            if (startingCountryID == -1) {
                cout << "We couldn't find your country. Please try again." << endl;
            } else {
                cout << "Sorry, the value you entered is not valid, please try again (the country could have to few troops):" << endl;
            }
            
        }
        
        //Getting and checking the destination country
        cout << "please select the destination country" << endl;
        while(true) {
            getline( cin, inputString );
            cin.ignore();
            //cin >> inputString;
            int destinationCountryID = countryNameToID(inputString, user);
            
            destinationCountry = getCountryById(user.getCountryByRef(), destinationCountryID);
            if((destinationCountryID >= 1) && (destinationCountry != NULL)&& (destinationCountry->getOwnedBy() == user.getPlayerID())) {
                break;
            }
            
            if (destinationCountryID == -1) {
                cout << "We couldn't find your country. Please try again." << endl;
            } else {
                cout << "Sorry, the value you entered is not valid, please try again (the country could have to few troops):" << endl;
            }
        }
        
        //checks the adjacency of both countries and promtps user for number of troop to move
        if (startingCountry->isCountAdjacent(destinationCountry->getCountryId())) {
            cout << "please enter the number of troops you want to move (value between 1 and " << startingCountry->getNumberOfTroops() << ":" << endl;
            while(true) {
                
                cin >> numberOfTroopsToMove;
                //if the number of troop is between 1 and the the number of troop in starting country -1
                if((numberOfTroopsToMove >= 1) &&
                   (numberOfTroopsToMove < startingCountry->getNumberOfTroops() ) ){
                    
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
        if(!troopsMoved) {
            cout << "Sorry the countries are not adjacent" << endl;
        }
        

        
        
    }
}

void Human::executeAttack(Player& user) {

}

void Human::executeReinforce(Player& user) {

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

			for (int j = 0; j < AdjCountry.size() && target == false;j++) {

				if (AdjCountry.at(j)->getOwnedBy() != user.getPlayerID()) {

					target = true;
					maxIndex = i;
					maxUnit = user.getCountryByRef().at(i)->getNumberOfTroops();
				}
			}
		}
	}
	Reinforce units;
	user.getCountryByRef().at(maxIndex)->setNumberOfTroops(maxUnit + units.totalUnits(user));
}


void Aggressive::executeAttack(Player& user) {

	//Finds your strongest country

	int maxUnit = 0;
	int maxIndex = 0;

	for (int i = 0; i < user.getCountryByRef().size(); i++) {

		if (user.getCountryByRef().at(i)->getNumberOfTroops() > maxUnit) {

			vector<CountryNode*> AdjCountry = user.getCountryByRef().at(i)->getAdjCount();
			bool target = false;

			for (int j = 0; j < AdjCountry.size() && target == false;j++) {

				if (AdjCountry.at(j) != NULL && AdjCountry.at(j)->getOwnedBy() != user.getPlayerID()) {

					target = true;
					maxIndex = i;
					maxUnit = user.getCountryByRef().at(i)->getNumberOfTroops();
				}
			}
		}
	}
	CountryNode* attacker = user.getCountryByRef().at(maxIndex);

	for (int i = 0; i < attacker->getAdjCount().size() && attacker->getNumberOfTroops() > 1; i++) {

		CountryNode* defender = attacker->getAdjCount().at(i);

		while (attacker->getNumberOfTroops() > 1 && defender->getOwnedBy() != attacker->getOwnedBy()) {

			int attackerDices;

			if (attacker->getNumberOfTroops() > 3)
				attackerDices = 3;//FIXME: Value stored in attackerDices is never read...
			if (attacker->getNumberOfTroops() == 3)
				attackerDices = 2;//FIXME: Value stored in attackerDices is never read...
			if (attacker->getNumberOfTroops() == 2)
                attackerDices = 1;//FIXME: Value stored in attackerDices is never read...

			//int defenderDices = Attack::defenderAmountOfDice(defender);
		}
	}
}

void Aggressive::executeFortify(Player& user) {//TODO: Implement this @Bruno
    CountryNode* startingCountry = NULL;
    CountryNode* destinationCountry = NULL;
    int numberOfTroopsToMove;
    
    //sort the user's countries
    user.topDownCountMergeSort();
    
    CountryNode* currentCheck;//the country we're checking out a the moment
    int ctr = 0;
    //loops throught the player's countries (from biggest to smallest)
    while (ctr < user.getCountryByRef().size()) {
        currentCheck = user.getCountryByRef().at(ctr);
        
        ctr++;
    }
    
    //looks at all adjeacent countries to the biggest to check if one or more of them is owned
        //if yes, move troops from that country to biggest
        //else, set biggest to second biggest and try again
    
    //If the biggest country is adjacent to an enemy country -> find second biggest owned country
    // and move troups towards biggest country
    
    
    
    //If the biggest country is not adjeacent to an enemy country, find closes enemy country and move troups towards that

    

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



void Benevolant::executeAttack(Player& user) {


}


void Benevolant::executeFortify(Player& user) {
    //TODO: Implement this @Bruno

}
