//============================================================================
// Name        : Tournament.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.1
// Copyright   : GNU Public license 3
// Description : Handles the creation and running of a tournament.
//               
//============================================================================

#pragma once
#include "GameLoop.h"
#include "GameStart.h"
#include "StartupPhase.h"

class Tournament
{
	vector<Map*> mapList;
	vector<Player*> playerList;
	
	GameStart gameStart;
	MainGameLoop game;

	int numberOfGames = 1;
	int maxTurns = 10;

public:
	Tournament();
	void addMaps();
	void addPlayers();
	void setNoGamesAndTurns();
	void playGames();
};