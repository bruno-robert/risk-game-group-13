//============================================================================
// Name        : GameStart.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : The file containing the GameStart object, which handles creating the elements
//				 for a game of Risk.
//============================================================================

#pragma once
#include <vector>
#include "Player.h"
#include "Dice.h"
#include "Cards.h"
#include "MapLoader.h"
using namespace std;

class GameStart
{
private:
	MapLoader loader;
	vector<Player*> players;
	Deck cardDeck;
public:
	GameStart();
	bool setGameStart(string mapName);
	Map* getMap();
	bool setPlayers(int noPlayers);
	vector<Player*> getPlayers();
	Deck* getDeck();
	~GameStart();
};