//============================================================================
// Name        : GameStatsObserver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.2
// Copyright   : GNU Public license 3
// Description : Prints update "players world domination view" as the state of the map changes
//============================================================================

#include "GameStatsObserver.h"
#include "Observer.h"
#include "Player.h"
#include "Attack.h"
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

GameStatsObserver::GameStatsObserver(){
    //Empty
}

void GameStatsObserver::setPlayerSubject(vector<Player*> playerList) {
    //Make the players the subjects
    subjectPlayers = playerList;
    
    //Attack observer to each each subject
    for (Player* p : subjectPlayers)
        p->attach(this);   
}

void GameStatsObserver::setAttackSubject(Attack* attack) {
    subjectAttack = attack;
    subjectAttack->attach(this);
}

GameStatsObserver::~GameStatsObserver() { //DELETE
    for (Player* p : subjectPlayers)
        p->detach(this);
    
    //subjectAttack->detach(this);
}

void GameStatsObserver::update(string message){
    
    if(message == "Map Change")
        printMapStats();
    
    //Else do nothing, the notify is not directed to this observer
    
}

void GameStatsObserver::printMapStats(){
    
    int i = 1;
    
    cout << "-------------------------------------------------------------------Map Ownership: ";
    
    for (Player* p : subjectPlayers)
    {
        vector<CountryNode*> ownedCountries = p->getCountry();
        
        for(CountryNode* c : ownedCountries)
            cout << i;
        
        i++;
    }
    
    cout << "\n";
}







