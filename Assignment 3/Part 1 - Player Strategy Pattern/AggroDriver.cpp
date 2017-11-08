
#include "PSPatern.hpp"
#include "Player.h"

int main(){

	//Creating 2 ContinentNodes

	ContinentNode europe("Europe", 5);
	ContinentNode asia("Asia", 3);

	//Creating a few CountryNodes

	CountryNode france("France", &europe);
	CountryNode uk("U.K.", &europe);
	CountryNode spain("Spain", &europe);
	CountryNode china("China", &asia);
	CountryNode mongolia("Mongolia", &asia);

	france.setNumberOfTroops(7);
	uk.setNumberOfTroops(5);
	spain.setNumberOfTroops(3);
	china.setNumberOfTroops(2);
	mongolia.setNumberOfTroops(8);

	china.setOwnedBy(2);
	mongolia.setOwnedBy(2);

	uk.addAdjCount(&china);
	uk.addAdjCount(&mongolia);
	spain.addAdjCount(&mongolia);



	//Creating a vector of CountryNode pointers for my player

	vector<CountryNode*> player1Set;
	player1Set.push_back(&france);
	player1Set.push_back(&spain);
	player1Set.push_back(&uk);
	

	//Creating a hand object

	Hand hand1;
	hand1.add(Card(1));
	hand1.add(Card(2));
	hand1.add(Card(3));
    
    Hand hand2;
    hand2.add(Card(1));
    hand2.add(Card(2));
    hand2.add(Card(3));
    
    Hand hand3;
    hand3.add(Card(1));
    hand3.add(Card(2));
    hand3.add(Card(3));
    

	//Creating a dice object

	Dice dice1;
    Dice dice2;
    Dice dice3;

	//Creating a player object

	//Aggressive strat;

	PlayerStrategyPattern* aggressiveStrat = new Aggressive();
    PlayerStrategyPattern* humanStrat = new Human();
    PlayerStrategyPattern* benevolentStrat = new Benevolant();

	Player player1 = Player(player1Set, hand1, dice1, aggressiveStrat);
    Player player2 = Player(player1Set, hand2, dice2, humanStrat);
    Player player3 = Player(player1Set, hand3, dice3, benevolentStrat);
    
    

	cout << "\nPlayer 1's list of countries and their units: " << endl;
	for (int i = 0; i < player1.getCountry().size(); i++) {
		cout << player1.getCountry().at(i)->getCountName() << " has " << player1.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
	}

	aggressiveStrat->executeReinforce(player1);

	cout << "\nPlayer 1's list of countries and their units: " << endl;
	for (int i = 0; i < player1.getCountry().size(); i++) {
		cout << player1.getCountry().at(i)->getCountName() << " has " << player1.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
	}

    return 0;
}
