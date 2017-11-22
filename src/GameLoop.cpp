//============================================================================
// Name        : GameLoop.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : main loop of the game
//============================================================================


/*
 Provide a group of C++ classes that implements the main game loop following the
 official rules of the game of Risk. During the main game loop, proceeding in a
 round-robin fashion as setup in the startup phase, every player is given the
 opportunity to do each of the following actions during their turn:
     1. Reinforcements phase
     2. Attack phase
     3. Fortification phase
 This loop shall continue until only one player controls all the countries in the map,
 at which point a winner is announced and the game ends. You must deliver a driver
 that demonstrates that 1) every player gets turns in a round-robin fashion and that
 their reinforcement(), attack() and fortification() methods are called 2) the game
 ends when a player controls all the countries (the driver should explicitly give all
 the countries to one player, i.e. no real code for battles needs to be executed).
 */
#include "GameLoop.h"
using namespace std;

MainGameLoop::MainGameLoop() {
    
}

MainGameLoop::~MainGameLoop() {
    
}

//checks if


void MainGameLoop::startGame(Map* m ,int numberOfPlayers, int playerTurn, vector<Player *>& playerList, int turnLimit) {
    const int FIRST_PLAYER =  playerTurn;
    vector<bool> eliminationList;
    int turnCounter = 0;
    
	PhaseObserver po;
	GameStatsObserver* gso = new GameStatsObserver();
	gso->setPlayerSubject(playerList);

    //give ownership to players if this is a demo
	/*
    if(test){
        vector<CountryNode *> countryList = m->getCountryList();
        int i = 0;
        for(vector<CountryNode *>::iterator iter = countryList.begin(); iter != countryList.end(); iter++, i++) {
            (*iter)->setOwnedBy((i%2) + 1);
        }
    }
    */
    
    //initialising the elimination list to to false
    for(int i = 0; i < numberOfPlayers; i++) {
        eliminationList.push_back(false);
    }
    
    //game loop
    while (!isGameEnd) {
		gso = gso->createObserver(gso);
		notify("GameStats");

        turnCounter++; //incrementing the turn counter
        //if player isn't elliminated then let him/her play turn
        if(m->getNumberOfcountriesOwnedById(playerTurn) == 0) {
            eliminationList.at(playerTurn-1) = true;
            cout << "player " << playerTurn << " is elliminated" << endl;
        }
        if(eliminationList.at(playerTurn-1) == false) {
            
            cout << "player " << playerTurn << "'s turn:" << endl;
            cout << "reinforce stage \nattack stage \nfortify stage\n\n" << endl;

			// To paste if needed for debugging (otherwise remove)
			cout << "\nPlayer " << playerList.at(0)->getPlayerID() << "'s list of countries and their units: " << endl;
			for (int i = 0; i < playerList.at(0)->getCountry().size(); i++) {
				cout << playerList.at(0)->getCountry().at(i)->getCountName() << " has " << playerList.at(0)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
			}

			cout << "\nPlayer " << playerList.at(1)->getPlayerID() << "'s list of countries and their units: " << endl;
			for (int i = 0; i < playerList.at(1)->getCountry().size(); i++) {
				cout << playerList.at(1)->getCountry().at(i)->getCountName() << " has " << playerList.at(1)->getCountry().at(i)->getNumberOfTroops() << " units." << endl;
			}

			cout << "--------------------------REINFORCEMENT---------------------------" << endl << endl;

            playerList.at(playerTurn - 1)->reinforce(po);

			cout << "--------------------------ATTACK---------------------------" << endl << endl;
			playerList.at(playerTurn - 1)->attack(*m, playerList, po, *gso);
			
			cout << "--------------------------FORTIFY---------------------------" << endl << endl;
            playerList.at(playerTurn - 1)->fortify(po);
            
        }
        
        //incrementing the player turn
        playerTurn++;
        if(playerTurn > numberOfPlayers) {
            playerTurn = 1;
        }
        
        //checks if there are more than 1 player that are still not elliminated
        int ctr = 0;
        for(vector<bool>::iterator iter = eliminationList.begin(); iter != eliminationList.end(); iter++) {
            if (*iter == false){
                ctr++;
            }
        }
        if( ctr <= 1) {
            //1 player left, the game is over
            isGameEnd = true;
            int i = 1;
            for(vector<bool>::iterator iter = eliminationList.begin(); iter != eliminationList.end(); iter++, i++) {
                if(!(*iter)){
                    cout << "player " << i << " wins the game!!!" << endl;
                }
            }
        }
        
        //sets the ownership of all countries to player 1
        //warning this part should be removed after the demo
        if(turnCounter >= turnLimit) {
			cout << "The game has reached " << turnLimit << " turns. Therefore, it is a draw." << endl;
			// Return winning player?
			break;

			/*
            vector<CountryNode *> countryList = m->getCountryList();
            for(vector<CountryNode *>::iterator iter = countryList.begin(); iter != countryList.end(); iter++) {
                (*iter)->setOwnedBy(1);
            }
			*/
        }
        
        
        
        
    }
}
