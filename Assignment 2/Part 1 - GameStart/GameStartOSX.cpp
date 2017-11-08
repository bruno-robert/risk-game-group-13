#include "GameStart.h"

// The main constructors for GameStart.
GameStart::GameStart() {}

bool GameStart::setGameStart(string mapName) // Returns true if the GameStart is successfully initiated, or false if there was an error.
{
	try
	{
		loader.ReadFile(mapName);
	}

	catch (MapLoaderException mle)
	{
		cout << "-------ERROR-------" << endl;
		cout << mle.what() << endl;
		return false;
	}

	int noCountries = (int)getMap()->getCountryList().size();
	this->cardDeck = Deck(noCountries);
	return true;
}

// Returns true if the creation was successful; false otherwise.
bool GameStart::setPlayers(int noPlayers)
{
	if (noPlayers < 2 || noPlayers > 6)
	{
		cout << "ERROR: The player number is invalid. There must be between 2 and 6 players." << endl;
		return false;
	}
	else
	{
		for (int i = 0; i < noPlayers; ++i)
		{
			vector<CountryNode*> owned;

			Player* player = new Player(owned, Hand(), Dice(), NULL);

			players.push_back(player);
		}
	}
	return true;
}

Map* GameStart::getMap()
{
	return loader.getMap();
}

Deck* GameStart::getDeck()
{
	return &cardDeck;
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

