#include <ctime>
#include <cstdlib>
#include "PSPatern.hpp"
#include "Player.h"
#include "MapLoaderOSX.h"
#include "GameStart.h"


int main(){
    
    srand((int)time(NULL));
    MapLoader ml;
    string value = "World.map";
    ml.ReadFile(value);
    ml.printMap();
    Map *m = ml.getMap();
    
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
    vector<CountryNode*> emptyCountryList;
    PlayerStrategyPattern* aggressiveStrat = new Aggressive();
    PlayerStrategyPattern* humanStrat = new Human();
    PlayerStrategyPattern* benevolentStrat = new Benevolant();
    
    Player player1 = Player(emptyCountryList, hand1, dice1, aggressiveStrat);
    Player player2 = Player(emptyCountryList, hand2, dice2, humanStrat);
    Player player3 = Player(emptyCountryList, hand3, dice3, benevolentStrat);
    
    vector<Player *> playerList;
    playerList.push_back(&player1);
    playerList.push_back(&player2);
    playerList.push_back(&player3);
    
	//Creating a vector of CountryNode pointers for my player

    int ctr = 1;
    vector<CountryNode*> countryList = m->getCountryList();
	vector<CountryNode*> player1Set;
    vector<CountryNode*> player2Set;
    vector<CountryNode*> player3Set;
    for(vector<CountryNode*>::iterator country = countryList.begin(); country != countryList.end(); country++) {
        (*country)->setNumberOfTroops(rand() % 10 + 1);
        switch (ctr) {
            case 1:
                player1.addCountryToOwned(*country, playerList);
                
                break;
            case 2:
                player2.addCountryToOwned(*country, playerList);
                
                break;
            case 3:
                player3.addCountryToOwned(*country, playerList);
                
                break;
            default:
                break;
        }
        
        
        ctr++;
        if(ctr > 3) {
            ctr = 1;
        }
    }
	

	
    
    
    

//    cout << "\nPlayer 1's list of countries and their units: " << endl;
//    for (int i = 0; i < player1.getCountry().size(); i++) {
//        cout << player1.getCountry().at(i)->getCountName() << " has " << player1.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
//    }
//    cout << "\nPlayer 2's list of countries and their units: " << endl;
//    for (int i = 0; i < player2.getCountry().size(); i++) {
//        cout << player2.getCountry().at(i)->getCountName() << " has " << player2.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
//    }
    
    cout << "\nPlayer 3's list of countries and their units: " << endl;
    for (int i = 0; i < player3.getCountry().size(); i++) {
        cout << player3.getCountry().at(i)->getCountName() << " has " << player3.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }

    for(int i = 0; i <= 100; i++) {
        cout << "\nPlayer 3, of type Benevolent is fortifying." << endl;
        player3.fortify();
        
        cout << "\nPlayer 3's list of countries and their units: " << endl;
        for (int i = 0; i < player3.getCountry().size(); i++) {
            cout << player3.getCountry().at(i)->getCountName() << " has " << player3.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
        }
    }
    
    
    
//    aggressiveStrat->executeReinforce(player1);

//    cout << "\nPlayer 1's list of countries and their units: " << endl;
//    for (int i = 0; i < player1.getCountry().size(); i++) {
//        cout << player1.getCountry().at(i)->getCountName() << " has " << player1.getCountry().at(i)->getNumberOfTroops() << " units." << endl;
//    }

    return 0;
}
