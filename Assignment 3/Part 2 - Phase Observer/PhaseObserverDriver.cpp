//============================================================================
// Name        : PhaseObserverDriver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : Tests the PhaseObserver class
//============================================================================

#include "PhaseObserver.h"
#include "MapLoader.h"

int main()
{
	PhaseObserver observer;
	observer.update("PHASE_OBSERVER|TEST MESSAGE");

	Attack attackPhase;
	Reinforce reinforcePhase;
	FortificationPhase fortificationPhase;

	observer.setAttackPhaseSubject(&attackPhase);
	observer.setReinforcePhaseSubject(&reinforcePhase);
	observer.setFortifyPhaseSubject(&fortificationPhase);

	MapLoader ml;
	string value = "World.map";
	ml.ReadFile(value);
	ml.printMap();
	Map* map = ml.getMap();

	vector<CountryNode*> countryList = map->getCountryList();

	//Creating dice for players
	Dice dice1, dice2, dice3;

	//Creating hand of cards for players
	Hand hand1, hand2, hand3;

	//Creating a hand object
	hand1.add(Card(1));
	hand1.add(Card(2));
	hand1.add(Card(3));

	//Assigning countries to player 1
	vector<CountryNode *> player1Countries;

	//Assigning countries to player 2
	vector<CountryNode *> player2Countries;

	//Assigning countries to player 3
	vector<CountryNode *> player3Countries;

	//Creating players
	PlayerStrategyPattern* aggressiveStrat = new Aggressive();
	PlayerStrategyPattern* humanStrat = new Human();
	PlayerStrategyPattern* benevolentStrat = new Benevolant();

	Player player1 = Player(player1Countries, hand1, dice1, aggressiveStrat);
	Player player2 = Player(player2Countries, hand2, dice2, humanStrat);
	Player player3 = Player(player3Countries, hand3, dice3, benevolentStrat);

	//Adding players to list
	vector<Player *> playerList;
	playerList.push_back(&player1);
	playerList.push_back(&player2);
	playerList.push_back(&player3);

	int ctr = 1;

	for (vector<CountryNode*>::iterator country = countryList.begin(); country != countryList.end(); country++) {
		(*country)->setNumberOfTroops(rand() % 10 + 1);
		switch (ctr) {
		case 1:
			playerList.at(0)->addCountryToOwned(*country, playerList);

			break;
		case 2:
			playerList.at(1)->addCountryToOwned(*country, playerList);

			break;
		case 3:
			playerList.at(2)->addCountryToOwned(*country, playerList);

			break;
		default:
			break;
		}

		ctr++;
		if (ctr > 3) {
			ctr = 1;
		}
	}
	
	cout << "\nPlayer 1's list of countries and their units: " << endl;
	for (int i = 0; i < player1.getCountry().size(); i++) {
		cout << player1.getCountry().at(i)->getCountName() << " has " << player1.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
	}

	cout << "\nPlayer 2's list of countries and their units: " << endl;
	for (int i = 0; i < player2.getCountry().size(); i++) {
		cout << player2.getCountry().at(i)->getCountName() << " has " << player2.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
	}

	cout << "\nPlayer 3's list of countries and their units: " << endl;
	for (int i = 0; i < player3.getCountry().size(); i++) {
		cout << player3.getCountry().at(i)->getCountName() << " has " << player3.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
	}

	humanStrat->executeAttack(player1, *map, playerList, attackPhase);
	humanStrat->executeReinforce(player1, reinforcePhase);
	humanStrat->executeFortify(player1, fortificationPhase);

	cout << "End of program!" << endl;
}