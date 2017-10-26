//============================================================================
// Name        : StartupDriver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.1
// Copyright   : GNU Public license 3
// Description : Driver to test the startup phase.
//============================================================================
#include "StartupPhase.h"


void main() {

	//Creating 2 ContinentNodes

	ContinentNode europe("Europe", 5);
	ContinentNode asia("Asia", 3);

	//Creating a few CountryNodes

	CountryNode france("France", &europe);
	CountryNode uk("U.K.", &europe);
	CountryNode spain("Spain", &europe);
	CountryNode china("China", &asia);
	CountryNode mongolia("Mongolia", &asia);
	CountryNode vietnam("Vietnam", &asia);

	//Adding all of my country to a vector. This could be the countrylist of the map

	vector<CountryNode*> countryList;
	countryList.push_back(&france);
	countryList.push_back(&spain);
	countryList.push_back(&uk);
	countryList.push_back(&china);
	countryList.push_back(&mongolia);
	countryList.push_back(&vietnam);

	cout << "Basic set of countries I will be using to demonstrate the random distribution..." << endl;

	for (int i = 0; i < countryList.size(); i++) {
		cout << countryList.at(i)->getCountName() << endl;
	}


	cout << "\nMaking 4 different players that I will rearrange in an order... " << endl;

	Player player1;
	Player player2;
	Player player3;
	Player player4;

	//Giving the players IDs to identify them

	player1.setPlayerID(1);
	player2.setPlayerID(2);
	player3.setPlayerID(3);
	player4.setPlayerID(4);

	vector<Player> playerSet;

	playerSet.push_back(player1);
	playerSet.push_back(player2);
	playerSet.push_back(player3);
	playerSet.push_back(player4);

	Startup startup(4);

	cout << "Printing out the ID's of my players..." << endl;

	for (int i = 0; i < playerSet.size();i++) {
		cout << "player " << playerSet.at(i).getPlayerID() << "," << endl;
	}

	startup.playOrder(playerSet);

	cout << "\nPrinting out the randomized order of my players..." << endl;

	for (int i = 0; i < playerSet.size();i++) {
		cout << "player " << playerSet.at(i).getPlayerID() << "," << endl;
	}

	startup.countryDistribution(countryList, playerSet);

	cout << "\nPrinting out the countries of my players..." << endl;


	for (auto player : playerSet) {
		cout << "player " << player.getPlayerID() << "," << endl;
		for (int i = 0; i < player.getCountry().size(); i++) {
			cout << player.getCountry().at(i)->getCountName() << " has " << player.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
		}
	}

	startup.unitDistribution(playerSet);

	for (auto player : playerSet) {
		cout << "player " << player.getPlayerID() << "," << endl;
		for (int i = 0; i < player.getCountry().size(); i++) {
			cout << player.getCountry().at(i)->getCountName() << " has " << player.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
		}
	}
}