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
bool PlayerStrategyPattern::isCountryInVector(int a, vector<CountryNode*> vect) {
    for(CountryNode* country: vect) {
        if (country->getCountryId() == a) {
            return true;
        }
    }
    
    return false;
}

/**
 When given a country and a list, the function will populate the list with countries that have a path to the given country.
 The path must be of only owned countries
 (this can be used to check if there is a ownCountry path between two countries)
 
 @param startCountry the country at the center of island
 @param ownedCountryIsland the vector of CountryNodes you wish to populate
 */
vector<CountryNode*> PlayerStrategyPattern::getOwnedIsland(CountryNode* startCountry, vector<CountryNode*>& ownedCountryIsland, const Player& p) {
    ownedCountryIsland.push_back(startCountry);
    int ctr = 0;
    for (CountryNode* country : startCountry->getAdjCount()) {
        if (isCountryInVector(country->getCountryId(), ownedCountryIsland) || country->getCountryId() != p.getPlayerID()) {
            
        }
        else {
            ownedCountryIsland = getOwnedIsland(country, ownedCountryIsland, p);
        }
        ctr++;
    }
    return ownedCountryIsland;
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
        
        cout << "Would you like to fortify this turn ? (y/n)" << endl;
        while (true) {
            string yesOrNo;
            cin >> yesOrNo;
            if(yesOrNo == "y" || yesOrNo == "yes") {
                break;
            } else if (yesOrNo == "n" || yesOrNo == "no") {
                return;
            }
            
            cout << "sorry the value you entered is invalid, please try again." << endl;
        }
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
    int numberOfTroopsToMove = -1;
    
    //sort the user's countries
    user.topDownCountMergeSort();
    
    CountryNode* currentCheck;//the country we're checking out a the moment
    int ctr = 0;
    //loops throught the player's countries (from biggest to smallest)
    while (ctr < user.getCountryByRef().size()) {
        currentCheck = user.getCountryByRef().at(ctr);
        for(CountryNode * adjCountry: currentCheck->getAdjCount()) {
            if(adjCountry->getNumberOfTroops() > 1 && adjCountry->getOwnedBy() == user.getPlayerID()) {
                startingCountry = adjCountry;
                destinationCountry = currentCheck;
                numberOfTroopsToMove = (startingCountry->getNumberOfTroops()-1);
            }
        }
        
        ctr++;
    }
    
    for(CountryNode* currentBiggy : user.getCountryByRef()) {
        vector<CountryNode*> currentCountryisland;
        getOwnedIsland(currentBiggy, currentCountryisland, user);
        for(CountryNode* country : currentCountryisland) {
            
        }
    }
    //1 from Currentbiggest country, get the island of owned countrie in it
    //2 move troups in island towards biggy
    //once all the troups in the island have 1 Troop:
    //3 find next biggest country [if the next biggest coutry has 1 troop: return]
    //repeat from step 1
    
    
    
    
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



void Benevolant::executeAttack(Player& user) {


}


void Benevolant::executeFortify(Player& user) {
    //Not a very efficient Algorithm O(n2) or more
    CountryNode* startingCountry = NULL;
    CountryNode* destinationCountry = NULL;
    int numberOfTroopsToMove = -1;
    
    //sort the user's countries
    user.topDownCountMergeSort();
    
    //for each owned countries (starting by the weakest
    for(int i = (int)(user.getCountryByRef().size()-1); i != -1; i--) {
        CountryNode* currentCountry = user.getCountryByRef().at(i);
        
        //for each adjacent country to the currentCoutry check if it has much more troops than the current Country
        for(CountryNode* country : currentCountry->getAdjCount()) {
            int diff = (country->getNumberOfTroops() - currentCountry->getNumberOfTroops());//diff is the (difference in troops)^2
            diff = diff * diff; //square so we only get positive results
            if(diff >= 4) {//if diff ==1 then moving the troup will have no avail, if diff >= 4 then the difference in troops >= 2
                if(country->getNumberOfTroops() > currentCountry->getNumberOfTroops()) {
                    startingCountry = country;
                    destinationCountry = currentCountry;
                    numberOfTroopsToMove = ((country->getNumberOfTroops() - currentCountry->getNumberOfTroops()) /2);
                    
                    //Removing troups from startingcountry
                    startingCountry->setNumberOfTroops(startingCountry->getNumberOfTroops() - numberOfTroopsToMove);
                    
                    //Adding troups to destinationCountry
                    destinationCountry->setNumberOfTroops(destinationCountry->getNumberOfTroops() + numberOfTroopsToMove);
                    return;
                } else {
                    startingCountry = currentCountry;
                    destinationCountry = country;
                    numberOfTroopsToMove = ((currentCountry->getNumberOfTroops() - country->getNumberOfTroops()) /2);
                    
                    //Removing troups from startingcountry
                    startingCountry->setNumberOfTroops(startingCountry->getNumberOfTroops() - numberOfTroopsToMove);
                    
                    //Adding troups to destinationCountry
                    destinationCountry->setNumberOfTroops(destinationCountry->getNumberOfTroops() + numberOfTroopsToMove);
                    return;
                }
            }
        }
    }

}
