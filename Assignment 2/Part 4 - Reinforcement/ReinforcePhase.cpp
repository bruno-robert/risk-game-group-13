//============================================================================
// Name        : ReinforcePhase.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.1
// Copyright   : GNU Public license 3
// Description : implementing all the methods for the reinforce phase 
//============================================================================

#include "Player.h"
#include "ReinforcePhase.h"
#include <algorithm>
#include "Subject.h"

int Reinforce::unitsForCountries(Player& player) {
	int units = player.getCountry().size() / 3;
	if (units < 3) {
		units = 3;
	}
	cout << "\nThe country bonus is of " << units << " units." << endl;
	return units;
}

int Reinforce::unitsForContinents(Player& player) {
	int units = 0;
	vector<int> pastIndex;
	for (int i = 0; i < player.getCountry().size();i++) {
		if (std::find(pastIndex.begin(), pastIndex.end(), i) != pastIndex.end()) {
			continue;
		}
		ContinentNode* currentContinent = player.getCountry().at(i)->getContinent();
		bool isEqual = true;
		for (int j = 0; j < currentContinent->getCountryList().size() && isEqual; j++) {
			isEqual = false;
			int k = 0;
			while (!isEqual && k < player.getCountry().size()) {			
				if (std::find(pastIndex.begin(), pastIndex.end(), i) != pastIndex.end()) {
					k++;
					continue;
				}
				if (currentContinent->getCountryList().at(j) == player.getCountry().at(k)) {
					isEqual = true;
					pastIndex.push_back(k);
				}
				k++;
			}
			if (isEqual && j == currentContinent->getCountryList().size() - 1)
				units += currentContinent->getContScore();
		}
	}
	cout << "The continent bonus is of " << units << " units." << endl;

return units;
}

int Reinforce::unitsForCards(Player& player) {
	int units = player.getHandByRef().exchange();
	string notifyString = "PHASE_OBSERVER|" + player.getHandByRef().getExchangeString();
	notify(notifyString);
	cout << "size of the hand: " << player.getHand().getSize() << endl;
	cout << "The card bonus is of " << units << " units." << endl;
	return units;
}

int Reinforce::totalUnits(Player& player) {
	int units = 0;
	units += unitsForCountries(player);
	units += unitsForContinents(player);
	units += unitsForCards(player);

	cout << "\ntotal number of units: " << units<<endl;
	return units;
}

void Reinforce::reinforceDistributions(Player& player) {
	cout << "\n\Calling the reinforcement phase..." << endl;
	int units = totalUnits(player);
	
	while(units != 0) {
		for (int i = 0; i < player.getCountry().size() && units != 0;i++) {
			player.getCountryByRef().at(i)->setNumberOfTroops(player.getCountryByRef().at(i)->getNumberOfTroops() + 1);
			units--;
		};
	}
}