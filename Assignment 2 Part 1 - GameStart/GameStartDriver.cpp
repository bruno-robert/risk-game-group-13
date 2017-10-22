#include "GameStart.h"

int main()
{
	string mapName;
	cout << "Enter the name of the world map: ";
	cin >> mapName;

	int playerNo;
	cout << "Set the number of players: ";
	cin >> playerNo;

	GameStart game(mapName);
	game.setPlayers(playerNo);

}