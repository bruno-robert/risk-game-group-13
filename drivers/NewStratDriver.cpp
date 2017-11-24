//============================================================================
// Name        : TournamentDriver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, C Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.1
// Copyright   : GNU Public license 3
// Description : Checks to make sure that the Tournament class works correctly.
//               
//============================================================================

#include "../src/Player.h"
#include "../src/GameStart.h"
#include "../src/StartupPhase.h"
#include "../src/GameLoop.h"
#include "../src/PhaseObserver.h"
#include "../src/GameStatsObserver.h"

int main()
{
	GameStart gs;
	// Remember to add functionality for multiple maps!!
	// Ask user how many players wanted

	//if (gs.setGameStart("World.map"))
	if (gs.setGameStart("World.map"))
	{
		int players = 2;
		gs.setPlayers(2);

		Deck* deck = gs.getDeck();
		Map* map = gs.getMap();
		vector<Player*> playerList = gs.getPlayers();

		PlayerStrategyPattern* psp1 = new Random();
		PlayerStrategyPattern* psp2 = new Cheater();

		playerList.at(0)->setPSP(psp1);
		playerList.at(1)->setPSP(psp2);

		// Starting Startup Phase:

		Startup::playOrder(playerList);
		Startup::countryDistribution(map->getCountryList(), playerList);
		Startup::unitDistribution(playerList, playerList.size());

		// GameLoop:

		MainGameLoop theGame;
		//int firstPlayer = playerList.at(0)->getPlayerID();
		theGame.startGame(map, 2, playerList, 5);

		// To paste if needed for debugging (otherwise remove)
		cout << "\nPlayer " << playerList.at(0)->getPlayerID() << "'s list of countries and their units: " << endl;
		for (int i = 0; i < playerList.at(0)->getCountry().size(); i++) {
			cout << playerList.at(0)->getCountry().at(i)->getCountName() << " has " << playerList.at(0)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
		}

		cout << "\nPlayer " << playerList.at(1)->getPlayerID() << "'s list of countries and their units: " << endl;
		for (int i = 0; i < playerList.at(1)->getCountry().size(); i++) {
			cout << playerList.at(1)->getCountry().at(i)->getCountName() << " has " << playerList.at(1)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
		}
	}


	else
	{
		cout << "Map is invalid!" << endl;
	}
}