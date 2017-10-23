#include "GameStart.h"

int main()
{
	bool successfulRun = false;
	GameStart game;
	while (!successfulRun)
	{
		string mapName;
		int playerNo;

		cout << "Enter the name of the world map: ";
		cin >> mapName;

		// Checking if the GameStart was properly initiated
		if (game.setGameStart(mapName))
		{
			cout << "Set the number of players: ";
			cin >> playerNo;
			game.setPlayers(playerNo);
			successfulRun = true; // If we get here, we were able to create a Map file correctly!!
		}
	}
}