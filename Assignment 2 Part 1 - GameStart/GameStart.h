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