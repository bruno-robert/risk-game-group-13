//
//  newStratDriver.cpp
//  newStrat
//
//  Created by Bruno Robert on 16/11/2017.
//  Copyright © 2017 Bruno Robert. All rights reserved.
//

//used for random number generation
#include <ctime>
#include <cstdlib>


#include <stdio.h>

#include "GameStartOSX.h"

using namespace std;

int main() {
    
    srand((int)time(NULL));
    
    PhaseObserver po;
    GameStatsObserver gso;
    
    GameStart gs;
    gs.setPlayers(3);
    gs.setGameStart("World.map");
    
    Map *m = gs.getMap();
    vector<Player*> playerList = gs.getPlayers();
    
    vector<CountryNode*> emptyCountryList;
    PlayerStrategyPattern* aggressiveStrat = new Aggressive();
    PlayerStrategyPattern* humanStrat = new Human();
    PlayerStrategyPattern* benevolentStrat = new Benevolant();
    PlayerStrategyPattern* random = new Random();
    
    playerList.at(0)->setPSP(aggressiveStrat);
    playerList.at(1)->setPSP(random);
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
    
    //P1 display count
    cout << "\n\n\n\nNow, lets let Player 1, the aggressive play have a turn" << endl;
    playerList.at(0)->topDownCountMergeSort();
    cout << "\nPlayer 1's list of countries and their units: " << endl;
    for (int i = 0; i < playerList.at(0)->getCountry().size(); i++) {
        cout << playerList.at(0)->getCountry().at(i)->getCountName() << " has " << playerList.at(0)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //P1 reinforce
    playerList.at(0)->reinforce(po);
    playerList.at(0)->topDownCountMergeSort();
    cout << "\nPlayer 1's list of countries and their units after reinforce: " << endl;
    for (int i = 0; i < playerList.at(0)->getCountry().size(); i++) {
        cout << playerList.at(0)->getCountry().at(i)->getCountName() << " has " << playerList.at(0)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //P1 attack
    playerList.at(0)->attack((*m), playerList, po, gso);
    playerList.at(0)->topDownCountMergeSort();
    cout << "\nPlayer 1's list of countries and their units after attack: " << endl;
    for (int i = 0; i < playerList.at(0)->getCountry().size(); i++) {
        cout << playerList.at(0)->getCountry().at(i)->getCountName() << " has " << playerList.at(0)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //P1 fortify
    playerList.at(0)->fortify(po);
    playerList.at(0)->topDownCountMergeSort();
    cout << "\nPlayer 1's list of countries and their units after fortify: " << endl;
    for (int i = 0; i < playerList.at(0)->getCountry().size(); i++) {
        cout << playerList.at(0)->getCountry().at(i)->getCountName() << " has " << playerList.at(0)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //Player 3 display count
    cout << "\n\n\n\nFinaly, Player 3 will play his turn in a more Benevolant way:" << endl;
    playerList.at(2)->topDownCountMergeSort();
    cout << "\nPlayer 3's list of countries and their units: " << endl;
    for (int i = 0; i < playerList.at(2)->getCountry().size(); i++) {
        cout << playerList.at(2)->getCountry().at(i)->getCountName() << " has " << playerList.at(2)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //P3 reinforce
    playerList.at(2)->reinforce(po);
    playerList.at(2)->topDownCountMergeSort();
    cout << "\nPlayer 3's list of countries and their units after reinforce: " << endl;
    for (int i = 0; i < playerList.at(2)->getCountry().size(); i++) {
        cout << playerList.at(2)->getCountry().at(i)->getCountName() << " has " << playerList.at(2)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //P3 attack
    playerList.at(2)->attack((*m), playerList, po, gso);
    playerList.at(2)->topDownCountMergeSort();
    cout << "\nPlayer 3's list of countries and their units after attack: " << endl;
    for (int i = 0; i < playerList.at(2)->getCountry().size(); i++) {
        cout << playerList.at(2)->getCountry().at(i)->getCountName() << " has " << playerList.at(2)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //p3 fortify
    playerList.at(2)->fortify(po);
    playerList.at(2)->topDownCountMergeSort();
    cout << "\nPlayer 3's list of countries and their units after fortify: " << endl;
    for (int i = 0; i < playerList.at(2)->getCountry().size(); i++) {
        cout << playerList.at(2)->getCountry().at(i)->getCountName() << " has " << playerList.at(2)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    return 0;
}
