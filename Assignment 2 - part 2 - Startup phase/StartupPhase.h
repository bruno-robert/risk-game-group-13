//============================================================================
// Name        : StartupPhase.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.1
// Copyright   : GNU Public license 3
// Description : Contains the delcaration for all of the Startup class methods
//============================================================================
#pragma once

#include "../Part 4 - Player/Player.h"

class Startup {

public:
	Startup(int numOfPlayers);
	void playOrder(vector<Player>& players);
	void countryDistribution(vector<CountryNode*>& countryList, vector<Player>& players);
	void unitDistribution(vector<Player>& players);
	int getNumOfPlayers();
private:
	int numOfPlayers;
};