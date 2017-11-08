
#include "PSPatern.hpp"
#include "Player.h"
#include "MapLoaderOSX.h"

int main(){

    MapLoader ml;
    string value = "World.map";
    ml.ReadFile(value);
    ml.printMap();
    Map *m = ml.getMap();
	//Creating a vector of CountryNode pointers for my player
    
    int ctr = 1;
    vector<CountryNode*> countryList = m->getCountryList();
	vector<CountryNode*> player1Set;
    vector<CountryNode*> player2Set;
    vector<CountryNode*> player3Set;
    for(vector<CountryNode*>::iterator country = countryList.begin(); country != countryList.end(); country++) {
        (*country)->setNumberOfTroops(5);
        switch (ctr) {
            case 1:
                player1Set.push_back(*country);
                break;
            case 2:
                player2Set.push_back(*country);
                break;
            case 3:
                player3Set.push_back(*country);
                break;
            default:
                break;
        }
        
        
        ctr++;
        if(ctr > 3) {
            ctr = 1;
        }
    }
	

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
    Player player2 = Player(player2Set, hand2, dice2, humanStrat);
    Player player3 = Player(player3Set, hand3, dice3, benevolentStrat);
    
    
    

//    cout << "\nPlayer 1's list of countries and their units: " << endl;
//    for (int i = 0; i < player1.getCountry().size(); i++) {
//        cout << player1.getCountry().at(i)->getCountName() << " has " << player1.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
//    }
    cout << "\nPlayer 2's list of countries and their units: " << endl;
    for (int i = 0; i < player2.getCountry().size(); i++) {
        cout << player2.getCountry().at(i)->getCountName() << " has " << player2.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
//    cout << "\nPlayer 3's list of countries and their units: " << endl;
//    for (int i = 0; i < player3.getCountry().size(); i++) {
//        cout << player3.getCountry().at(i)->getCountName() << " has " << player3.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
//    }

    player2.fortify();
//    aggressiveStrat->executeReinforce(player1);

//    cout << "\nPlayer 1's list of countries and their units: " << endl;
//    for (int i = 0; i < player1.getCountry().size(); i++) {
//        cout << player1.getCountry().at(i)->getCountName() << " has " << player1.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
//    }

    return 0;
}
