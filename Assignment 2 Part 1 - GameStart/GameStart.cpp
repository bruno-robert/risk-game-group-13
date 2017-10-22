#include "GameStart.h"

// The main constructors for GameStart.
GameStart::GameStart() {}
GameStart::GameStart(string mapName)
{
	setGameStart(mapName);
}

void GameStart::setGameStart(string mapName)
{
	loader.ReadFile(mapName);

	int noCountries = getMap()->getCountryList().size();
	this->cardDeck = Deck(noCountries);
}

// Returns true if the creation was successful; false otherwise.
void GameStart::setPlayers(int noPlayers)
{
	if (noPlayers < 2 || noPlayers > 6) cout << "ERROR: The player number is invalid. There must be between 2 and 6 players." << endl
											 << "The players were not created successfully." << endl;
	else
	{
		for (int i = 0; i < noPlayers; ++i)
		{
			vector<CountryNode*> owned;

			Player* player = new Player(owned, Hand(), Dice());

			players.push_back(player);
		}
	}
}

Map* GameStart::getMap()
{
	return loader.getMap();
}

GameStart::~GameStart()
{
	for (Player* p : players)
		delete p;
}

vector<Player*> GameStart::getPlayers()
{
	return players;
}

