#include <ctime>
#include <cstdlib>
#include "PSPatern.hpp"
#include "Player.h"
#include "MapLoaderOSX.h"
#include "GameStartOSX.h"


int main(){
    srand((int)time(NULL));
    
    GameStart gs;
    gs.setPlayers(3);
    gs.setGameStart("World.map");
    
    Map *m = gs.getMap();
    vector<Player*> playerList = gs.getPlayers();
    
    //Aggressive strat;
    vector<CountryNode*> emptyCountryList;
    PlayerStrategyPattern* aggressiveStrat = new Aggressive();
    PlayerStrategyPattern* humanStrat = new Human();
    PlayerStrategyPattern* benevolentStrat = new Benevolant();
    
    playerList.at(0)->setPSP(aggressiveStrat);
    playerList.at(1)->setPSP(humanStrat);
    playerList.at(2)->setPSP(benevolentStrat);
    
    
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
                playerList.at(0)->addCountryToOwned(*country, playerList);
                
                break;
            case 2:
                playerList.at(1)->addCountryToOwned(*country, playerList);
                
                break;
            case 3:
                playerList.at(2)->addCountryToOwned(*country, playerList);
                
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
//    for (int i = 0; i < playerList.at(0).getCountry().size(); i++) {
//        cout << playerList.at(0).getCountry().at(i)->getCountName() << " has " << playerList.at(0).getCountry().at(i)->getNumberOfTroops() << " units." << endl;
//    }
//    cout << "\nPlayer 2's list of countries and their units: " << endl;
//    for (int i = 0; i < playerList.at(1).getCountry().size(); i++) {
//        cout << playerList.at(1).getCountry().at(i)->getCountName() << " has " << playerList.at(1).getCountry().at(i)->getNumberOfTroops() << " units." << endl;
//    }
    
    cout << "\nPlayer 3's list of countries and their units: " << endl;
    for (int i = 0; i < playerList.at(2)->getCountry().size(); i++) {
        cout << playerList.at(2)->getCountry().at(i)->getCountName() << " has " << playerList.at(2)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }

    for(int i = 0; i <= 100; i++) {
        cout << "\nPlayer 3, of type Benevolent is fortifying." << endl;
        playerList.at(2)->fortify();
        
        cout << "\nPlayer 3's list of countries and their units: " << endl;
        for (int i = 0; i < playerList.at(2)->getCountry().size(); i++) {
            cout << playerList.at(2)->getCountry().at(i)->getCountName() << " has " << playerList.at(2)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
        }
    }
    
    
    
//    aggressiveStrat->executeReinforce(playerList.at(0));

//    cout << "\nPlayer 1's list of countries and their units: " << endl;
//    for (int i = 0; i < playerList.at(0).getCountry().size(); i++) {
//        cout << playerList.at(0).getCountry().at(i)->getCountName() << " has " << playerList.at(0).getCountry().at(i)->getNumberOfTroops() << " units." << endl;
//    }

    return 0;
}
