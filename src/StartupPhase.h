//============================================================================
// Name        : StartupPhase.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.1
// Copyright   : GNU Public license 3
// Description : Contains the delcaration for all of the Startup class methods
//============================================================================
#pragma once

#include "Player.h"

static class Startup {

public:
	// Takes vector of players and shuffles the players around.
	static void playOrder(vector<Player*>& players);

	// Distributes countries
	static void countryDistribution(vector<CountryNode*>& countryList, vector<Player*>& players);

	static void unitDistribution(vector<Player*>& players, int numOfPlayers);
};