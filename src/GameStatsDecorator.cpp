
#include "GameStatsObserver.h"
#include "GameStatsDecorator.h"
#include "Cards.h"
#include "Map.h"
#include <vector>
#include <iostream>
using namespace std;

/* DELETE IF UNUSED
 cout::setf(ios::fixed);
 cout::setf(ios::showpoint);
 cout.precision(2);
 */


GameStatsDecorator::GameStatsObserver *decoratedGameStats;

GameStatsDecorator::GameStatsDecorator(GameStatsObserver *decoratedGameStats){
	this->decoratedGameStats = decoratedGameStats;
}

void GameStatsDecorator::update(string message){
	return decoratedGameStats->update(message);
}






DominationObserver::DominationObserver(GameStatsObserver *decoratedGameStats) : GameStatsDecorator(decoratedGameStats){
	//Empty body
}

void DominationObserver::update(string message){
	if (message == "GameStats" || message == "GameStats Turn"){
		printDominationStats();
		GameStatsDecorator::update(message); // + printDominationStats();
	}
}

void DominationObserver::printDominationStats(){

	//Get total amount of countries
	int total = 0;
	vector<CountryNode*> countries = map->getCountryList();
	for (CountryNode* c : countries)
	{
		total++;
	}

	cout << "------------Map Ownership: ";

	//Get an calculate individual ownership
	for (Player* p : subjectPlayers)
	{
		int playerID = p->getPlayerID();
		int amount = 0;

			vector<CountryNode*> countryList = p->getCountry();
			for (CountryNode* c : countryList)
				amount++;

		double percentage = (amount / (double)total) * 100.0;

		cout << "Player " << playerID << ": " << percentage << "%   ";  
	}

	cout << "\n";
}




HandObserver::HandObserver(GameStatsObserver *decoratedGameStats) : GameStatsDecorator(decoratedGameStats){
	//Empty Body
}

void HandObserver::update(string message){
	if (message == "GameStats" || message == "GameStats Turn"){
		printHandInfo();
		GameStatsDecorator::update(message); // + printHandInfo();
	}
}

void HandObserver::printHandInfo(){

	cout << "------------Hand information: " << endl;

	for(Player* player : subjectPlayers){
		int playerID = player->getPlayerID();

		//Get players hand an it's size
		Hand hand = player->getHand();
		vector<Card> playerHand = hand.getPlayerHand();

		int infantry = 0, cavalry = 0, artillery = 0;

		//Get amount of cards of each type in hand
		for (Card c : playerHand) {
			switch (c.getType()) {
			case 1:infantry++;
				break;
			case 2:cavalry++;
				break;
			case 3:artillery++;
				break;
			}
		}

		//printing the statement for each player
		cout << "------------\tPlayer " << playerID << ": " << infantry << " infantry, " << cavalry << " cavalry, " << artillery << " artillery" << endl;
	}

}





ControlObserver::ControlObserver(GameStatsObserver *decoratedGameStats) : GameStatsDecorator(decoratedGameStats){
	//Empty Body
}

void ControlObserver::update(string message){
	if (message == "GameStats" || message == "GameStats Turn"){
		printContinentControlInfo();
		GameStatsDecorator::update(message); // + printContinentControlInfo();
	}
}

void ControlObserver::printContinentControlInfo(){

	cout << "------------Continent control: " << endl;


	for (Player* player : subjectPlayers){
		vector<int> pastIndex;
		string owns = "";

		for (int i = 0; i < player->getCountry().size(); i++) {
			if (std::find(pastIndex.begin(), pastIndex.end(), i) != pastIndex.end()) {
				continue;
			}
			ContinentNode* currentContinent = player->getCountry().at(i)->getContinent();
			bool isEqual = true;
			for (int j = 0; j < currentContinent->getCountryList().size() && isEqual; j++) {
				isEqual = false;
				int k = 0;
				while (!isEqual && k < player->getCountry().size()) {
					if (std::find(pastIndex.begin(), pastIndex.end(), i) != pastIndex.end()) {
						k++;
						continue;
					}
					if (currentContinent->getCountryList().at(j) == player->getCountry().at(k)) {
						isEqual = true;
						pastIndex.push_back(k);
					}
					k++;
				}
				if (isEqual && j == currentContinent->getCountryList().size() - 1)
					if (owns == "")
						owns += currentContinent->getContName();
					else
						owns += ", " + currentContinent->getContName();
			}
		}

		if (owns == "")
			owns = "none";

		int playerID = player->getPlayerID();

		//printing the statement for each player
		cout << "------------\tPlayer " << playerID << ": " << owns << endl;

	}//end subjectPlayers iteration loop

}




