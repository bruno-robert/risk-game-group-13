//============================================================================
// Name        : TournamentDriver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.1
// Copyright   : GNU Public license 3
// Description : Checks to make sure that the Tournament class works correctly.
//               
//============================================================================

#include "Tournament.h"
#include "GameLoop.h"
#include "GameStart.h"
#include "StartupPhase.h"
#include "Player.h"
#include "PhaseObserver.h"
#include "GameStatsObserver.h"

int main()
{
	Tournament tournament;

	tournament.addMaps();
	tournament.addPlayers();
	tournament.setNoGamesAndTurns();
	tournament.playGames();

	
	GameStart gs;
	// Remember to add functionality for multiple maps!!
	// Ask user how many players wanted
	
	if (gs.setGameStart("World.map"))
	{
		int players = 2;
		gs.setPlayers(2);

		Deck* deck = gs.getDeck();
		Map* map = gs.getMap();
		vector<Player*> playerList = gs.getPlayers();

		PlayerStrategyPattern* psp1 = new Aggressive();
		PlayerStrategyPattern* psp2 = new Benevolant();

		playerList.at(0)->setPSP(psp1);
		playerList.at(1)->setPSP(psp2);

		// Starting Startup Phase:

		Startup::playOrder(playerList);
		Startup::countryDistribution(map->getCountryList(), playerList);
		Startup::unitDistribution(playerList, playerList.size());

		// GameLoop:

		MainGameLoop theGame;
		int firstPlayer = playerList.at(0)->getPlayerID();
		theGame.startGame(map, 2, playerList, 1);
	}
	else
	{
		cout << "Map is invalid!" << endl;
	}
	
}