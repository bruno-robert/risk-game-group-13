//
//  PSPatern.cpp
//  Risk-fresh-start
//
//  Created by Bruno Robert on 31/10/2017.
//  Copyright © 2017 Bruno Robert. All rights reserved.
//

#include "PSPatern.hpp"
#include "FortificationPhase.hpp"
#include "Subject.h"
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
	for (CountryNode* country : vect) {
		if (country->getCountryId() == a) {
			return true;
		}
	}

	return false;
}


Human::Human() : PlayerStrategyPattern() {

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
int Human::countryNameToID(string countryName, Player& p) {
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

void Human::executeFortify(Player& user, FortificationPhase& fortification) {

	fortification.setFortifyingPlayer(&user);
	fortification.notify("Fortification Started");
	bool troopsMoved = false;
	while (!troopsMoved) {
		CountryNode* startingCountry = NULL;
		CountryNode* destinationCountry = NULL;
		int numberOfTroopsToMove;

		//asking if user wants to foritfy
		cout << "\nYou are now in the fortification Phase:\n" << endl;
		cout << "Would you like to fortify this turn ? (y/n)" << endl;
		while (true) {
			string yesOrNo;
			cin >> yesOrNo;
			if (yesOrNo == "y" || yesOrNo == "yes") {
				break;
			}
			else if (yesOrNo == "n" || yesOrNo == "no") {
				return;
			}

			cout << "sorry the value you entered is invalid, please try again." << endl;
		}

		cout << "\nHere is the list of you countries with their troops and friendly adjacent countries:" << endl;
		//Print out the list of coutries with friendly adjacent
		for (CountryNode* country : user.getCountryByRef()) {
			cout << country->getCountName() << " has " << country->getNumberOfTroops() << " troops. It's friendly adjacent countries are:" << endl;
			for (CountryNode* adjCountry : country->getAdjCount()) {
				if (adjCountry->getOwnedBy() == user.getPlayerID()) {
					cout << "        " << adjCountry->getCountName() << " with " << adjCountry->getNumberOfTroops() << " troops." << endl;
				}
			}
		}


		//Getting and checking starting country
		cout << "Please select a starting country" << endl;
		//temporary varibales
		string inputString;
		while (true) {
			cin >> inputString;
			replace(inputString.begin(), inputString.end(), '_', ' ');

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

		fortification.setStartingCountry(startingCountry);

		//Getting and checking the destination country
		cout << "please select the destination country" << endl;
		while (true) {
			cin >> inputString;
			replace(inputString.begin(), inputString.end(), '_', ' ');

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
				fortification.setDestinationCountry(destinationCountry);
				cin >> numberOfTroopsToMove;
				//if the number of troop is between 1 and the the number of troop in starting country -1
				if ((numberOfTroopsToMove >= 1) &&
					(numberOfTroopsToMove < startingCountry->getNumberOfTroops())) {

					//Removing troups from startingcountry
					startingCountry->setNumberOfTroops(startingCountry->getNumberOfTroops() - numberOfTroopsToMove);
					cout << "Moving " << numberOfTroopsToMove << " units from " << startingCountry->getCountName() << " to " << destinationCountry->getCountName() << endl;
					//Adding troups to destinationCountry
					destinationCountry->setNumberOfTroops(destinationCountry->getNumberOfTroops() + numberOfTroopsToMove);

					troopsMoved = true;
					fortification.setAmountTroopsMoved(numberOfTroopsToMove);
					fortification.notify("Fortification occured");
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

void Human::executeAttack(Player& user, Map& map, vector<Player*> playerList, Attack& attackObj) {

	//The other notify calls should be inside to attack loop
	attackObj.attackLoop(playerList, &user, &map);

}

void Human::executeReinforce(Player& user, Reinforce& rein) {

	rein.reinforceDistributions(user);
}

Aggressive::Aggressive() : PlayerStrategyPattern()
{

}

Aggressive::~Aggressive() {

}

void Aggressive::executeReinforce(Player& user, Reinforce& rein) {


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

	int unitsReceived = rein.totalUnits(user);
	user.getCountryByRef().at(maxIndex)->setNumberOfTroops(maxUnit + unitsReceived);
	rein.setTroopsMoved(unitsReceived);
	rein.setReinforcedCountryData(user.getCountryByRef().at(maxIndex));
	notify("Troops moved");
}


void Aggressive::executeAttack(Player& user, Map& map, vector<Player*> playerList, Attack &attackObj) {

	attackObj.setPlayerListData(playerList);
	attackObj.setAttackingPlayerData(&user);
	attackObj.setMapData(&map);

	notify("Attack Started");

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

	cout << endl <<"The attacking country will be " << attacker->getCountName() << ".\n"<< endl;

	for (int i = 0; i < attacker->getAdjCount().size() && attacker->getNumberOfTroops() > 1; i++) {

		CountryNode* defending = attacker->getAdjCount().at(i);
		attackObj.setDefendingCountryData(defending);
		notify("Attack to/from set");


		if (defending->getCountryId() != attacker->getCountryId()) {
			cout << "The current enemy target is " << defending->getCountName() << endl;
			while (attacker->getNumberOfTroops() > 1 && defending->getNumberOfTroops() > 0) {

				int attackerDices = 0;

				if (attacker->getNumberOfTroops() > 3)
					attackerDices = 3;//FIXME: Value stored in attackerDices is never read...
				if (attacker->getNumberOfTroops() == 3)
					attackerDices = 2;//FIXME: Value stored in attackerDices is never read...
				if (attacker->getNumberOfTroops() == 2)
					attackerDices = 1;//FIXME: Value stored in attackerDices is never read...

				int defenderDices = attackObj.defenderAmountOfDice(defending);

				Player* defender = attackObj.getAssociatedPlayer(playerList, defending->getCountName());
				attackObj.setDefendingPlayerData(defender);

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

				for (int i = 0; i < mostRolled; i++) {
					if (attackerDiceResults[i] > defenderDiceResults[i])
						defenderLoses++;
					else
						attackerLoses++;
				}
				attackObj.setAttackerTroopLoss(attackerLoses);
				attackObj.setDefenderTroopLoss(defenderLoses);

				notify("Troop Loss");

				cout << endl << attacker->getCountName() << " lost " << attackerLoses << " units and " << defending->getCountName() << " lost " << defenderLoses << " units." << endl;
				defending->setNumberOfTroops(defending->getNumberOfTroops() - defenderLoses);
				attacker->setNumberOfTroops(attacker->getNumberOfTroops() - attackerLoses);
			}
			if (defending->getNumberOfTroops() == 0 && attacker->getNumberOfTroops() > 1) {
				user.addCountryToOwned(defending, playerList);
				defending->setNumberOfTroops(1);
				attacker->setNumberOfTroops(attacker->getNumberOfTroops() - 1);

				notify("Attacker conquered");

				cout << endl << "The aggressive computer player conquered " << defending->getCountName() << "." << endl;
			}
		}

	}
}


/**
 the recursiveGetPathToBiggest country starts from the the startingCountry, and makes its way to the nearest country that is owned by p and has troops
 It then returns a 1 length path to move troops cloesr to the original starting country
 */
vector<CountryNode*> PlayerStrategyPattern::recursiveGetPathToBiggest(CountryNode* startingCountry, CountryNode* destinationCountry, const Player& p, vector<CountryNode*>& visitedCountries) {
	vector<CountryNode*> path;
	if (isCountryInVector(startingCountry->getCountryId(), visitedCountries)) {
		return path;
	}
	else {
		visitedCountries.push_back(startingCountry);
		for (CountryNode* adjCountry : startingCountry->getAdjCount()) {
			if (adjCountry->getOwnedBy() == p.getPlayerID() && adjCountry->getNumberOfTroops() > 1) {
				destinationCountry = adjCountry;
				path.push_back(startingCountry);
				path.push_back(destinationCountry);
				return path;
			}
		}
		for (CountryNode* adjCountry : startingCountry->getAdjCount()) {
			path = recursiveGetPathToBiggest(adjCountry, destinationCountry, p, visitedCountries);
			if (path.size() > 0) {
				return path;
			}
		}
	}

	return path;
}

/**

 @param destinationCountry ptr to the coutry to witch you want to move troups (the method will modify it's value so that if you move troop to this country, they will be closer to the original country)
 @param startingCountry the method will change this to the country you should send the troups from
 @param p player
 */
void PlayerStrategyPattern::getPathToBiggest(CountryNode ** destinationCountry, CountryNode ** startingCountry, const Player& p) {
	vector<CountryNode*> visitedCountries;
	vector<CountryNode*> path = recursiveGetPathToBiggest(*destinationCountry, *startingCountry, p, visitedCountries);

	if (path.size() >= 2) {
		*destinationCountry = path.at(0);
		*startingCountry = path.at(1);
	}
	else {
		*destinationCountry = NULL;
		*startingCountry = NULL;
	}


	return;
}

void Aggressive::executeFortify(Player& user, FortificationPhase& fortification) {
	CountryNode* startingCountry = NULL;
	CountryNode* destinationCountry = NULL;
	int numberOfTroopsToMove = -1;

	//sort the user's countries
	user.topDownCountMergeSort();

	for (CountryNode* currentCountry : user.getCountryByRef()) {
		bool hasEnemy = false;
		for (CountryNode* adjCountry : currentCountry->getAdjCount()) {
			if (adjCountry->getOwnedBy() != user.getPlayerID()) {
				hasEnemy = true;
				break;
			}
		}

		if (hasEnemy) {
			destinationCountry = currentCountry;
			user.topDownCountMergeSort();
			getPathToBiggest(&destinationCountry, &startingCountry, user);


			if (startingCountry != NULL && destinationCountry != NULL) {
				numberOfTroopsToMove = (startingCountry->getNumberOfTroops() - 1);
				//Removing troups from startingcountry
				startingCountry->setNumberOfTroops(startingCountry->getNumberOfTroops() - numberOfTroopsToMove);
				cout << "Moving " << numberOfTroopsToMove << " units from " << startingCountry->getCountName() << " to " << destinationCountry->getCountName() << endl;
				//Adding troups to destinationCountry
				destinationCountry->setNumberOfTroops(destinationCountry->getNumberOfTroops() + numberOfTroopsToMove);

				return;
			}
		}//else move to the next country
		hasEnemy = false;
		startingCountry = NULL;
	}

	fortification.setStartingCountry(startingCountry);
	fortification.setDestinationCountry(destinationCountry);

	//If the biggest country is not adjeacent to an enemy country, find closes enemy country and move troups towards that

	if (numberOfTroopsToMove >= 1) {
		fortification.setAmountTroopsMoved(numberOfTroopsToMove);

		//Removing troups from startingcountry
		startingCountry->setNumberOfTroops(startingCountry->getNumberOfTroops() - numberOfTroopsToMove);

		//Adding troups to destinationCountry
		destinationCountry->setNumberOfTroops(destinationCountry->getNumberOfTroops() + numberOfTroopsToMove);

		notify("Fortification occured");
	}

}


Benevolant::Benevolant() : PlayerStrategyPattern()
{

}

Benevolant::~Benevolant() {

}

void Benevolant::executeReinforce(Player& user, Reinforce& rein) {

	rein.setReinforcingPlayer(&user);
	notify("Reinforcing Started");
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
		//rein.set
		units--;
		notify("Troops Moved");
	}
}



void Benevolant::executeAttack(Player& user, Map& map, vector<Player*> playerList, Attack& attackObj) {

	attackObj.setAttackingPlayerData(&user);
	notify("Attack Started");
	cout << "Since the benevolant computer does not attack no action is taken during this phase..." << endl;

}

void Benevolant::executeFortify(Player& user, FortificationPhase& fortification) {
	//Not a very efficient Algorithm O(n2) or more
	CountryNode* startingCountry = NULL;
	CountryNode* destinationCountry = NULL;
	int numberOfTroopsToMove = -1;

	//sort the user's countries
	user.topDownCountMergeSort();

	//for each owned countries (starting by the weakest
	for (int i = (int)(user.getCountryByRef().size() - 1); i != -1; i--) {
		CountryNode* currentCountry = user.getCountryByRef().at(i);

		//for each adjacent country to the currentCoutry check if it has much more troops than the current Country
		for (CountryNode* country : currentCountry->getAdjCount()) {
			int diff = (country->getNumberOfTroops() - currentCountry->getNumberOfTroops());//diff is the (difference in troops)^2
			diff = diff * diff; //square so we only get positive results
			if (diff >= 4) {//if diff ==1 then moving the troup will have no avail, if diff >= 4 then the difference in troops >= 2
				if (country->getNumberOfTroops() > currentCountry->getNumberOfTroops()) {
					startingCountry = country;
					destinationCountry = currentCountry;

					fortification.setStartingCountry(startingCountry);
					fortification.setDestinationCountry(destinationCountry);

					numberOfTroopsToMove = ((country->getNumberOfTroops() - currentCountry->getNumberOfTroops()) / 2);

					//Removing troups from startingcountry
					startingCountry->setNumberOfTroops(startingCountry->getNumberOfTroops() - numberOfTroopsToMove);
					cout << "Moving " << numberOfTroopsToMove << " units from " << startingCountry->getCountName() << " to " << destinationCountry->getCountName() << endl;
					//Adding troups to destinationCountry
					destinationCountry->setNumberOfTroops(destinationCountry->getNumberOfTroops() + numberOfTroopsToMove);

					fortification.setAmountTroopsMoved(numberOfTroopsToMove);

					notify("Fortification occured");

					return;
				}
				else {
					startingCountry = currentCountry;
					destinationCountry = country;

					fortification.setStartingCountry(startingCountry);
					fortification.setDestinationCountry(destinationCountry);

					numberOfTroopsToMove = ((currentCountry->getNumberOfTroops() - country->getNumberOfTroops()) / 2);

					//Removing troups from startingcountry
					startingCountry->setNumberOfTroops(startingCountry->getNumberOfTroops() - numberOfTroopsToMove);

					//Adding troups to destinationCountry
					destinationCountry->setNumberOfTroops(destinationCountry->getNumberOfTroops() + numberOfTroopsToMove);

					fortification.setAmountTroopsMoved(numberOfTroopsToMove);

					notify("Fortification occured");

					return;
				}
			}
		}
	}

}

