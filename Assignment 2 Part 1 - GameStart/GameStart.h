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
	GameStart(string mapName);
	void setGameStart(string mapName);
	Map* getMap();
	void setPlayers(int noPlayers);
	vector<Player*> getPlayers();
	~GameStart();
};