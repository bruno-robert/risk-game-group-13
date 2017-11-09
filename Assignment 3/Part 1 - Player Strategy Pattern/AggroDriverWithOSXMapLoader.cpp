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
	//-----------------
    //   Introduction
    //-----------------

    cout << "\n\n\n\n\n\n\n" << endl;
    cout << "Hello and welcome to Assignment 3 Part 1's Demoing unit!" << endl;
    cout << "I will be explaaining what is going on so that you an I are on the same page." << endl;
    cout << "I have set up a game for you, it uses the classical map of risk that I have loaded from the World.map file my creators provided me." << endl;
    cout << "I have teken the liberty to create 3 players, each owning 1/3 of the countrie of the map (I ditributed them using a round robbin fashion)." << endl;
    cout << "I have set Player 1 to use the Agressive Player Strategy Pattern, Player 3 to be Benevolent and finaly, I will let you play player 2!" << endl;
    cout << "I will wait for you to get ready, just type 'r' or 'ready' when you are." << endl;
    
    while(true) {
        string usrInput;
        cin >> usrInput;
        if(usrInput == "r" || usrInput == "ready"){
            break;
        }
        cout << "Humm, I see you are trying to express yourself. I have been orded to stay polite, but there is no other way of saying this, I haven't understood your querry. Try again." << endl;
    }
    //---------------------
    //   Testing Starts
    //---------------------
    
    cout << "\n\n\n\nIt's your turn, so here is your list of countries:" << endl;
    for (int i = 0; i < playerList.at(1)->getCountry().size(); i++) {
        cout << playerList.at(1)->getCountry().at(i)->getCountName() << " has " << playerList.at(1)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    cout << "\n" << endl;
    
    //P2 reinforce
    playerList.at(1)->reinforce();
    
    //P2 attack
    playerList.at(1)->attack((*m), playerList);
    for (int i = 0; i < playerList.at(1)->getCountry().size(); i++) {
        cout << playerList.at(1)->getCountry().at(i)->getCountName() << " has " << playerList.at(1)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //P2 fortify
    playerList.at(1)->fortify();
    cout << "\nupdated list of countries for player 2" << endl;
    for (int i = 0; i < playerList.at(1)->getCountry().size(); i++) {
        cout << playerList.at(1)->getCountry().at(i)->getCountName() << " has " << playerList.at(1)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //P1 display count
    cout << "\n\n\n\nNow, lets let Player 1, the aggressive play have a turn" << endl;
    playerList.at(0)->topDownCountMergeSort();
    cout << "\nPlayer 1's list of countries and their units: " << endl;
    for (int i = 0; i < playerList.at(0)->getCountry().size(); i++) {
        cout << playerList.at(0)->getCountry().at(i)->getCountName() << " has " << playerList.at(0)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //P1 reinforce
    playerList.at(0)->reinforce();
    playerList.at(0)->topDownCountMergeSort();
    cout << "\nPlayer 1's list of countries and their units after reinforce: " << endl;
    for (int i = 0; i < playerList.at(0)->getCountry().size(); i++) {
        cout << playerList.at(0)->getCountry().at(i)->getCountName() << " has " << playerList.at(0)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //P1 attack
    playerList.at(0)->attack((*m), playerList);
    playerList.at(0)->topDownCountMergeSort();
    cout << "\nPlayer 1's list of countries and their units after attack: " << endl;
    for (int i = 0; i < playerList.at(0)->getCountry().size(); i++) {
        cout << playerList.at(0)->getCountry().at(i)->getCountName() << " has " << playerList.at(0)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //P1 fortify
    playerList.at(0)->fortify();
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
    playerList.at(2)->reinforce();
    playerList.at(2)->topDownCountMergeSort();
    cout << "\nPlayer 3's list of countries and their units after reinforce: " << endl;
    for (int i = 0; i < playerList.at(2)->getCountry().size(); i++) {
        cout << playerList.at(2)->getCountry().at(i)->getCountName() << " has " << playerList.at(2)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //P3 attack
    playerList.at(2)->attack((*m), playerList);
    playerList.at(2)->topDownCountMergeSort();
    cout << "\nPlayer 3's list of countries and their units after attack: " << endl;
    for (int i = 0; i < playerList.at(2)->getCountry().size(); i++) {
        cout << playerList.at(2)->getCountry().at(i)->getCountName() << " has " << playerList.at(2)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    //p3 fortify
    playerList.at(2)->fortify();
    playerList.at(2)->topDownCountMergeSort();
    cout << "\nPlayer 3's list of countries and their units after fortify: " << endl;
    for (int i = 0; i < playerList.at(2)->getCountry().size(); i++) {
        cout << playerList.at(2)->getCountry().at(i)->getCountName() << " has " << playerList.at(2)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
    }
    
    
    

   


    return 0;
}
