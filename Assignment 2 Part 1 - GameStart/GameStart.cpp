//============================================================================
// Name        : GameStart.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : The implementation of the GameStart class.
//============================================================================

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

	int noCountries = getMap()->getCountryList().size();
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
		// Player creation loop
		for (int i = 0; i < noPlayers; ++i)
		{
			vector<CountryNode*> owned;

			Player* player = new Player(owned, Hand(), Dice());

			players.push_back(player);
		}
	}
	return true;
}

// Getters
Map* GameStart::getMap()
{
	return loader.getMap();
}

Deck* GameStart::getDeck()
{
	return &cardDeck;
}

// Destructor
GameStart::~GameStart()
{
	for (Player* p : players)
		delete p;
}
// Getter
vector<Player*> GameStart::getPlayers()
{
	return players;
}

