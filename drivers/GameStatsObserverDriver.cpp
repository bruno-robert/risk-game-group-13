////============================================================================
//// Name        : GameStatsObserverDriver.cpp
//// Team        : Group 13
//// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
//// Version     : 1.1
//// Copyright   : GNU Public license 3
//// Description : Tests GameStatsObserver Class
////============================================================================
//
//#include "GameStatsObserver.h"
//#include "Player.h"
//#include "Attack.h"
//#include "PSPatern.hpp"
//#include "GameStatsDecorator.h"
//#include <iostream>
//using namespace std;
//
//int main (){
//    
//    Map map;
//    
//    //creating continents
//    ContinentNode europe("Europe", 5);
//    ContinentNode northAmerica("North America", 5);
//    ContinentNode southAmerica("south America", 5);
//    ContinentNode asia("Asia", 9);
//    asia.addAdjCont(&europe);
//    europe.addAdjCont(&asia);
//    europe.addAdjCont(&northAmerica);
//    northAmerica.addAdjCont(&europe);
//    northAmerica.addAdjCont(&southAmerica);
//    southAmerica.addAdjCont(&northAmerica);
//    
//    //creating countries
//    CountryNode mongolia("Mongolia", &europe);
//    CountryNode france("France", &europe);
//    CountryNode uk("U.K.", &europe);
//    CountryNode spain("Spain", &europe);
//    CountryNode china ("China", &asia);
//    CountryNode canada("Canada", &northAmerica);
//    CountryNode usa("USA", &northAmerica);
//    CountryNode mexico("Mexico", &northAmerica);
//    
//    china.addAdjCount(&mongolia);
//    mongolia.addAdjCount(&china);
//    mongolia.addAdjCount(&france);
//    france.addAdjCount(&mongolia);
//    france.addAdjCount(&uk);
//    france.addAdjCount(&spain);
//    uk.addAdjCount(&france);
//    spain.addAdjCount(&france);
//    canada.addAdjCount(&usa);
//    usa.addAdjCount(&canada);
//    usa.addAdjCount(&mexico);
//    mexico.addAdjCount(&usa);
//    
//    //adding nodes to map
//    map.addContinent(&europe);
//    map.addContinent(&northAmerica);
//    map.addContinent(&southAmerica);
//    map.addContinent(&asia);
//    map.addCountry(&mongolia);
//    map.addCountry(&france);
//    map.addCountry(&uk);
//    map.addCountry(&spain);
//    map.addCountry(&china);
//    map.addCountry(&canada);
//    map.addCountry(&usa);
//    map.addCountry(&mexico);
//    
//    //Assigning army personnel to countries
//    china.setNumberOfTroops(1);
//    mongolia.setNumberOfTroops(5);
//    france.setNumberOfTroops(6);
//    spain.setNumberOfTroops(4);
//    uk.setNumberOfTroops(10);
//    canada.setNumberOfTroops(3);
//    usa.setNumberOfTroops(18);
//    
//    //Creating dice for players
//    Dice dice1, dice2, dice3;
//    
//    //Creating hand of cards for players
//    Hand hand1, hand2, hand3;
//
//	//Filling Hands
//	hand1.add(Card(1));
//	hand1.add(Card(2));
//	hand1.add(Card(3));
//	hand2.add(Card(2));
//	hand2.add(Card(2));
//	hand2.add(Card(3));
//	hand2.add(Card(3));
//	hand3.add(Card(2));
//	hand3.add(Card(3));
//
//    
//    //Assigning countries to player 1
//    vector<CountryNode *> player1Countries;
//    
//    //Assigning countries to player 2
//    vector<CountryNode *> player2Countries;
//    
//    //Assigning countries to player 3
//    vector<CountryNode *> player3Countries;
//    
//    //Creating Strategy pattern
//    Benevolant* ben = new Benevolant();
//	Random* ran = new Random();
//	Aggressive* agg = new Aggressive();
//    
//    //Creating players
//    Player player1 = Player (player1Countries, hand1, dice1, ben);
//    Player player2 = Player (player2Countries, hand2, dice2, ran);
//    Player player3 = Player (player3Countries, hand3, dice3, agg);
//    
//    //Adding players to list
//    vector<Player *> playerList;
//    playerList.push_back(&player1);
//    playerList.push_back(&player2);
//    playerList.push_back(&player3);
//    
//    //Assigning countries
//    player1Countries.push_back(&mongolia);
//    player1Countries.push_back(&china);
//    player1Countries.push_back(&france);
//    player2Countries.push_back(&mexico);
//    player2Countries.push_back(&uk);
//    player2Countries.push_back(&spain);
//    player3Countries.push_back(&canada);
//    player3Countries.push_back(&usa);
//
//	mongolia.setOwnedBy(2);
//	china.setOwnedBy(2);
//	france.setOwnedBy(2);
//	mexico.setOwnedBy(3);
//	uk.setOwnedBy(3);
//	spain.setOwnedBy(3);
//	canada.setOwnedBy(4);
//	usa.setOwnedBy(4);
//    
//    player1.setCountry(player1Countries);
//    player2.setCountry(player2Countries);
//    player3.setCountry(player3Countries);
//    
//    //creating Attack phase
//    Attack attack;
//    
//    //Creating observer
//	GameStatsObserver* dummyObserver = new GameStatsObserver();
//
//	GameStatsObserver* gameStatsObserver = dummyObserver->createObserver(dummyObserver);
//	gameStatsObserver->setPlayerSubject(playerList);
//	gameStatsObserver->setAttackSubject(&attack);
//	gameStatsObserver->setMap(&map);
//   
//    //Testing
//    cout << "Player 1 conquers a country"<<endl;
//	player1.addCountryToOwned(&spain, playerList);
//
//	cout << "Player 1 conquers a country" << endl;
//	player1.addCountryToOwned(&canada, playerList);
//
//	cout << "Player 1 conquers a country" << endl;
//	player1.addCountryToOwned(&usa, playerList);
//
//	cout << "Player 1 conquers a country" << endl;
//	player1.addCountryToOwned(&mexico, playerList);
//
//	cout << "Player 3 conquers a country" << endl;
//	player3.addCountryToOwned(&mexico, playerList);
//	
//	GameStatsObserver* test = NULL;
//
//	for (int i = 0; i <= 5; i++){
//		delete gameStatsObserver;
//		gameStatsObserver = dummyObserver->createObserver(dummyObserver);
//		gameStatsObserver->setPlayerSubject(playerList);
//		gameStatsObserver->setAttackSubject(&attack);
//		gameStatsObserver->setMap(&map);
//		string country;
//		cout << "Player 2 conquers a country (Spain, Canada, USA, Mexico)" << endl;
//		cin >> country;
//		CountryNode* countryNode = map.getCountryByName(country);
//		player2.addCountryToOwned(countryNode, playerList);
//
//	}
//    
//	system("pause");
//     
//}