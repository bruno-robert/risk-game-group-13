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

Human::Human() : PlayerStrategyPattern() {

}

Human::~Human() {

}

/**
 Takes a string and a Map and returns the Id of the country with the given name
 If the country doesn't exists, retursn -1
 @param countryName Name of the country
 @param m Map Object
 @return the ID of the country with name countryName. If the country doesn't exist, returns -1
 */
int Human::countryNameToID(string countryName, Map& m) {// TODO: test functionality
	vector<CountryNode*> cl = m.getCountryList();
	for (vector<CountryNode*>::iterator country = cl.begin(); country != cl.end(); country++) {
		if ((*country)->getCountName() == countryName) {
			return (*country)->getCountryId();
		}
	}

	return -1;//error, country not found
}

/**
 Human fortification method, asks for starting and destiantion countries. Checks if the entered coutries are valid.
 If the values are valid, it will prompt user for a number of troop to move and checks if that value is valid.
 If will then return (via given pointer parameters) the starting country id and destination coutry id as well as the number of troop to move.
 @param startingCountry startingCoutry pointer, used to return starting coutry ID
 @param destinationCountry destinationCountry pointer, used to return the destination country ID
 @param numberOfTroopsToMove numberOftroopToMove, used to return the number of troop to be moved from start to destination coutry
 @return returns true if the values given by the user are all correct, false if there was an error picking the values
 */
void Human::executeFortify(Player& user) {

}

void Human::executeAttack(Player& user) {

}

void Human::executeReinforce(Player& user) {

}

Aggressive::Aggressive() : PlayerStrategyPattern()
{

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

				if (AdjCountry.at(j)->getCountryId() != NULL && AdjCountry.at(j)->getOwnedBy() != user.getPlayerID()) {

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
				attackerDices = 3;
			if (attacker->getNumberOfTroops() == 3)
				attackerDices = 2;
			if (attacker->getNumberOfTroops() == 2)
				attackerDices = 1;

			//int defenderDices = Attack::defenderAmountOfDice(defender);
		}
	}
}

void Aggressive::executeFortify(Player& user) {


}


Benevolant::Benevolant() : PlayerStrategyPattern()
{

}


void Benevolant::executeReinforce(Player& user) {


	//Getting the number of units for my player
	Reinforce unitsReinforced;
	int units = unitsReinforced.totalUnits(user);

	//Finding the country with the most units and a target to attack

	while (units = !0) {

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


}
