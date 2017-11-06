//============================================================================
// Name        : PhaseObserverDriver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : Tests the PhaseObserver class
//============================================================================

#include "PhaseObserver.h"

int main()
{
	PhaseObserver observer;
	observer.update("PHASE_OBSERVER|TEST MESSAGE");

	Attack attackPhase;
	Reinforce reinforcePhase;
	FortificationPhase fortificationPhase;

	observer.setAttackPhaseSubject(&attackPhase);
	observer.setReinforcePhaseSubject(&reinforcePhase);
	//observer.setFortifyPhaseSubject(&fortificationPhase);

	Map map;

	//creating continents
	ContinentNode europe("Europe", 5);
	ContinentNode northAmerica("North America", 5);
	ContinentNode southAmerica("south America", 5);
	ContinentNode asia("Asia", 9);
	asia.addAdjCont(&europe);
	europe.addAdjCont(&asia);
	europe.addAdjCont(&northAmerica);
	northAmerica.addAdjCont(&europe);
	northAmerica.addAdjCont(&southAmerica);
	southAmerica.addAdjCont(&northAmerica);

	//creating countries
	CountryNode mongolia("Mongolia", &europe);
	CountryNode france("France", &europe);
	CountryNode uk("U.K.", &europe);
	CountryNode spain("Spain", &europe);
	CountryNode china("China", &asia);
	CountryNode canada("Canada", &northAmerica);
	CountryNode usa("USA", &northAmerica);
	CountryNode mexico("Mexico", &northAmerica);

	china.addAdjCount(&mongolia);
	mongolia.addAdjCount(&china);
	mongolia.addAdjCount(&france);
	france.addAdjCount(&mongolia);
	france.addAdjCount(&uk);
	france.addAdjCount(&spain);
	uk.addAdjCount(&france);
	spain.addAdjCount(&france);
	canada.addAdjCount(&usa);
	usa.addAdjCount(&canada);
	usa.addAdjCount(&mexico);
	mexico.addAdjCount(&usa);

	//adding nodes to map
	map.addContinent(&europe);
	map.addContinent(&northAmerica);
	map.addContinent(&southAmerica);
	map.addContinent(&asia);
	map.addCountry(&mongolia);
	map.addCountry(&france);
	map.addCountry(&uk);
	map.addCountry(&spain);
	map.addCountry(&china);
	map.addCountry(&canada);
	map.addCountry(&usa);
	map.addCountry(&mexico);

	//Assigning army personnel to countries
	china.setNumberOfTroops(1);
	mongolia.setNumberOfTroops(5);
	france.setNumberOfTroops(6);
	spain.setNumberOfTroops(4);
	uk.setNumberOfTroops(10);
	canada.setNumberOfTroops(3);
	usa.setNumberOfTroops(18);

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
	Player player1 = Player(player1Countries, hand1, dice1);
	Player player2 = Player(player2Countries, hand2, dice2);
	Player player3 = Player(player3Countries, hand3, dice3);

	//Adding players to list
	vector<Player *> playerList;
	playerList.push_back(&player1);
	playerList.push_back(&player2);
	playerList.push_back(&player3);

	//Assigning countries
	player1Countries.push_back(&mongolia);
	player1Countries.push_back(&china);
	player1Countries.push_back(&france);
	player2Countries.push_back(&mexico);
	player2Countries.push_back(&uk);
	player2Countries.push_back(&spain);
	player3Countries.push_back(&canada);
	player3Countries.push_back(&usa);

	player1.setCountry(player1Countries);
	player2.setCountry(player2Countries);
	player3.setCountry(player3Countries);
		
	attackPhase.attackLoop(playerList, &player1, &map);
	reinforcePhase.reinforceDistributions(player1);
	cout << "End of program!" << endl;
}