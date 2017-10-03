//============================================================================
// Name        : Part_4_Driver.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1
// Copyright   : GNU Public license 3
// Description : Demo driver for Part 4.
//============================================================================

#include "Part_4.h"
using namespace std;

void main(){

	cout << "This is the driver for Player object.\n\n" << endl;

	cout << "Creating 2 Player object using a complete and default constructor...\n" << endl;

	cout << "Giving player 1 two countries for initialization...\n" << endl;
	ContinentNode europe("Europe", 5);
	ContinentNode asia("Asia", 9);
	CountryNode mongolia("Mongolia", &europe);
	CountryNode china("China", &asia);

	vector<CountryNode *> ownedCountry;

	ownedCountry.push_back(&mongolia);
	ownedCountry.push_back(&china);
	cout << "Giving player 1 a hand composed of three infantry cards for initialization..." << endl;
	Hand hand;
	hand.add(Card (1));
	hand.add(Card (1));
	hand.add(Card (1));

	cout << "Giving player 1 a dice facility for initialization..." << endl;
	Dice dice;

	cout << "Creating player 1 using the complete constructor." << endl;
	Player player1 = Player (ownedCountry, hand, dice);

	cout << "Creating player 2 using the default constructor." << endl;
	Player player2;

	cout << "\nComparing the size of the country collection: \n" << endl;

	cout << "Player 1 owns " << player1.getCountry().size() << " countries." << endl;
	cout << "Player 2 owns " << player2.getCountry().size() << " countries.\n" << endl;

	cout << "Player 1 has " << player1.getHand().getSize() << " cards in his hand." << endl;
	cout << "Player 2 has " << player2.getHand().getSize() << " cards in his hand.\n" << endl;

	cout << "\nTesting Player hand actions...\n" << endl;

	player1.getHand().exchange();
	player2.getHand().exchange();

	cout << "Testing dice roll...\n" << endl;
	cout << "\nPlayer 1 and Player 2 each has their own dice which have identical functions.\n" << endl;

	int a[3], b[3];
	player1.getDice().roll(a, 1);
	player2.getDice().roll(b, 1);

	cout << "\nPlayer 1 has rolled a " << b[0] << endl;
	cout << "Player 2 has rolled a " << a[0] << endl;

	cout << "\nTesting Reinforce, Attack, and Fortify methods.\n" << endl;

	player1.reinforce();
	player1.attack();
	player1.fortify();

	system("pause");
}