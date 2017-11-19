//============================================================================
// Name        : StartupPhase.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.1
// Copyright   : GNU Public license 3
// Description : contains the implementation for all of the startup phase methods
//============================================================================
#include <random>
#include <algorithm>
#include "StartupPhase.h"


//Rearranging  the players in a random order

void Startup::playOrder(vector<Player*>& players) {

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(players.begin(), players.end(), g);
}

//Going through all the countries in the map and giving them to the specific player

void Startup::countryDistribution(vector<CountryNode*>& countryList, vector<Player*>& players) {

	int countryIndex = 0;
	while (countryIndex < countryList.size()) {
		for (int i = 0; i < players.size() && countryIndex < countryList.size(); i++) {
			players.at(i)->addCountryToOwned(countryList.at(countryIndex), players);

			countryIndex++;
		}
	}
}

//Distribute the units of a player to all of his countries in a round-robin fashion

void Startup::unitDistribution(vector<Player*>& players, int numOfPlayers) {
	int units;
	switch (numOfPlayers)
	{
	case 2: units = 40;
		break;
	case 3: units = 35;
		break;
	case 4: units = 30;
		break;
	case 5: units = 25;
		break;
	case 6: units = 20;
		break;
	}
	cout << "\nSince we have " << numOfPlayers << " players, every player will receive " << units << " units." << endl;

	for (int i = 0; i < players.size();i++) {
		int tempUnits = units;
		while (tempUnits > 0) {
			for (int j = 0; j < players.at(i)->getCountry().size() && tempUnits > 0;j++) {
				players.at(i)->getCountryByRef().at(j)->setNumberOfTroops(players.at(i)->getCountryByRef().at(j)->getNumberOfTroops() + 1);
				tempUnits--;
			};
		}
	}
}


