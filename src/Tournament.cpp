//============================================================================
// Name        : Tournament.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.1
// Copyright   : GNU Public license 3
// Description : Handles the creation and running of a tournament.
//               
//============================================================================

#include "Tournament.h"

Tournament::Tournament() {}

void Tournament::addMaps()
{
	int number;
	cout << "Set the number of maps: ";
	cin >> number;

	while (number < 1 || number > 5)
	{
		cin.clear();
		cin.ignore(10000, '\n'); // We skip everything up until the next newline character.
		cout << "Set the number of maps: ";
		cin >> number;
	} 

	for (int i = 0; i < number; ++i)
	{
		string mapName;
		do
		{
			cout << "Enter the map name: ";
			cin >> mapName;
		} while (!gameStart.setGameStart(mapName));

		mapList.push_back(gameStart.getMap()); // WARNING: THIS LINE MIGHT CAUSE REFERENCE ISSUES
	}
}

void Tournament::addPlayers()
{
	int number;
	cout << "Set the number of players: ";
	cin >> number;

	while (!gameStart.setPlayers(number))
	{
		cin.clear();
		cin.ignore(10000, '\n'); // We skip everything up until the next newline character.
		cout << "Set the number of players: ";
		cin >> number;
	} 

	playerList = gameStart.getPlayers();

	for (int i = 0; i < number; ++i)
	{
		string computerType;
		bool validValue = false;
		do
		{
			cout << "Select computer type for player " << playerList.at(i)->getPlayerID() << " (write benevolent/aggressive/random/cheater)" << endl;
			cin >> computerType;
			(computerType);
			if (computerType == "benevolent")
			{
				playerList.at(i)->setPSP(new Benevolant());
				validValue = true;
			}
			else if (computerType == "aggressive")
			{
				playerList.at(i)->setPSP(new Aggressive());
				validValue = true;
			}
			/* //TO UNCOMMENT ONCE COMPUTER PLAYERS ARE SET
			else if (computerType == "random")
			{
				playerList.at(i)->setPSP(new Random());				
			}
			else if (computerType == "cheater")
			{
				playerList.at(i)->setPSP(new Cheater());				
			}*/
		}
		while (!validValue);
	}
}

void Tournament::setNoGamesAndTurns()
{
	int number;
	cout << "Enter the number of games to play (between 1 and 5): ";
	cin >> number;

	while (number < 1 || number > 5)
	{
		cin.clear();
		cin.ignore(10000, '\n'); // We skip everything up until the next newline character.
		cout << "Enter the number of games to play (between 1 and 5): ";
		cin >> number;
	} 

	numberOfGames = number;
	number = 0;

	while (number < 1 || number > 50) // replace 1 with 10
	{
		cin.clear();
		cin.ignore(10000, '\n'); // We skip everything up until the next newline character.
		cout << "Enter the number of maximum turns (between 10 and 50): ";
		cin >> number;
	}

	maxTurns = number;
}

void Tournament::playGames()
{
	for (int i = 0; i < mapList.size(); ++i)
	{
		for (Player* p : playerList)
		{
			if (!p->getCountry().empty())
			{
				vector<CountryNode*> newCountryList = p->getCountry();
				newCountryList.clear();
				p->setCountry(newCountryList);
			}
		}
		for (int g = 0; g < numberOfGames; ++g)
		{
			// Starting Startup Phase:

			Startup::playOrder(playerList);
			Startup::countryDistribution(mapList.at(i)->getCountryList(), playerList);
			Startup::unitDistribution(playerList, playerList.size());

			// GameLoop:

			int firstPlayer = playerList.at(0)->getPlayerID();
			game.startGame(mapList.at(i), 2, firstPlayer, playerList, maxTurns);
		}
		
	}
}