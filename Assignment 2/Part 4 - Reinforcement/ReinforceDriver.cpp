//============================================================================
// Name        : ReinforceDriver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.1
// Copyright   : GNU Public license 3
// Description : concise description of the part you are working on
//============================================================================
#include "ReinforcePhase.h"

void main() {

	cout << "Testing the reinforcement phase for a player..." << endl;

	//Creating 2 ContinentNodes

	ContinentNode europe("Europe", 5);
	ContinentNode asia("Asia", 3);

	//Creating a few CountryNodes

	CountryNode france("France", &europe);
	CountryNode uk("U.K.", &europe);
	CountryNode spain("Spain", &europe);
	CountryNode china("China", &asia);
	CountryNode mongolia("Mongolia", &asia);

	//Checking if my continents are have the correct elements

	cout << "\nEurope has a bonus of 5 units and is composed of " << europe.getCountryList().size() << " countries" << endl;
	cout << "Europes's list of countries: " << endl;
	for (int i = 0; i < europe.getCountryList().size(); i++) {
		cout << europe.getCountryList().at(i)->getCountName() << endl;
	}


	cout << "\nAsia has a bonus of 3 units and is composed of " << asia.getCountryList().size() << " countries" << endl;
	cout << "Asia's list of countries: " << endl;
	for (int i = 0; i < asia.getCountryList().size(); i++) {
		cout << asia.getCountryList().at(i)->getCountName() << endl;
	}

	//Creating a vector of CountryNode pointers for my player

	vector<CountryNode*> player1Set;
	player1Set.push_back(&france);
	player1Set.push_back(&spain);
	player1Set.push_back(&uk);
	player1Set.push_back(&china);

	
	//Creating a hand object

	Hand hand1;
	hand1.add(Card(1));
	hand1.add(Card(2));
	hand1.add(Card(3));

	//Creating a dice object

	Dice dice1;

	//Creating a player object

	Player player1 = Player(player1Set, hand1, dice1);

	cout << "\nPlayer 1's list of countries and their units: " << endl;
	for (int i = 0; i < player1.getCountry().size(); i++) {
		cout << player1.getCountry().at(i)->getCountName() << " has " << player1.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
	}

	Reinforce reinforceObj;

	reinforceObj.reinforceDistributions(player1);

	cout << "\nPlayer 1's list of countries and their units: " <<endl;
	for (int i = 0; i < player1.getCountry().size(); i++) {
		cout << player1.getCountry().at(i)->getCountName() << " has " << player1.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
	}


	cout << "\nAdding mongolia to the player's country collection..." << endl;
	player1.getCountryByRef().push_back(&mongolia);

	cout << "\nPlayer 1's list of countries and their units: " << endl;
	for (int i = 0; i < player1.getCountry().size(); i++) {
		cout << player1.getCountry().at(i)->getCountName() << " has " << player1.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
	}

	reinforceObj.reinforceDistributions(player1);
	
	cout << "\nPlayer 1's list of countries and their units: " << endl;
	for (int i = 0; i < player1.getCountry().size(); i++) {
		cout << player1.getCountry().at(i)->getCountName() << " has " << player1.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
	}
}