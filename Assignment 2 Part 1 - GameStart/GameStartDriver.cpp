//============================================================================
// Name        : GameStartDriver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : The driver that tests the correct creation of a Map inside
//				 the GameStart, and tests whether the Players function correctly.
//============================================================================

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
			do
			{
				cin.clear();
				cin.ignore(10000, '\n'); // We skip everything up until the next newline character.
				cout << "Set the number of players: ";
				cin >> playerNo;
			}
			while (!game.setPlayers(playerNo));

			successfulRun = true; // If we get here, the Game Start is created correctly!
		}

		// Testing the players' functionality:
		cout << "Beginning tests!" << endl << "------" << endl;
		Deck deck = *game.getDeck();

		vector<Player*> players = game.getPlayers();
		int i = 1;
		// Testing the die for each player, and the deck:
		for (Player *p : players)
		{
			cout << "Player #" << i << endl;
			int rolls[] = { NULL, NULL, NULL };
			p->getDice().roll(rolls, 3);
			for (int i : rolls)
				cout << "Rolled a " << i << endl;
			cout << endl;
			
			Hand hand = p->getHand();
						
			Card c = deck.draw();
			hand.add(c);
			c = deck.draw();
			hand.add(c);
			c = deck.draw();
			hand.add(c);
			cout << "Player has " << hand.getSize() << " cards." << endl;
			cout << "------" << endl << endl;
			++i;
		}
	}
}