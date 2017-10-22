//
//  FortificationPhase.cpp
//  Assignment 2 - part 6 - main game loop: fortification phase
//
//  Created by Bruno Robert on 12/10/2017.
//  Copyright © 2017 Bruno Robert. All rights reserved.
//

#include "FortificationPhase.hpp"

//Provide a group of C++ classes that implement the fortification phase following the official rules of the game of Risk.
//In the fortification phase, the player is allowed to move a number of armies (X) from one of its countries (the source country) to one of its neighbors that it also owns (the target country).
//X must be in the range [1 to (number of armies on the source country - 1)].
//You must deliver a driver that demonstrates that
//1) only valid countries can be selected as source/target;
//2) only a valid number of armies can be moved;
//3) the right number of armies is effectively moved.

using namespace std;

FortificationPhase::FortificationPhase() {
    
}

FortificationPhase::~FortificationPhase() {
    
}

void FortificationPhase::fortify(int player, Map& m ) {
    int startingCountry;
    int destinationCountry;
    int numberOfTroups;
    bool troupsMoved = false;
    while(!troupsMoved) {
        //Getting and checking starting country
        cout << "please select a starting country" << endl;
        while(true) {
            cin >> startingCountry;
            
            //checks if the starting coutry is valid
            if((startingCountry >= 1) && (m.getcoutryById(startingCountry) != NULL)) {
                break;
            }
            
            cout << "Sorry, the value you entered is not valid, please try again:" << endl;
        }

        //Getting and checking the destination country
        cout << "please select the destination country" << endl;
        while(true) {
            cin >> destinationCountry;
            if((destinationCountry >= 1) && (m.getcoutryById(destinationCountry) != NULL)) {
                break;
            }
            
            cout << "Sorry, the value you entered is not valid, please try again:" << endl;
        }

        //checking if the countries are adjacent and if they are owned by the player
        if((m.getcoutryById(startingCountry)->getOwnedBy() == player) && m.getcoutryById(startingCountry)->isCountAdjacent(destinationCountry)) {
            cout << "please enter the number of troups you want to move:" << endl;
            while(true) {
                
                cin >> numberOfTroups;
                if((numberOfTroups >= 1) && (numberOfTroups < m.getcoutryById(startingCountry)->getNumberOfTroups() ) ){
                    cout << "troups moved!" << endl;
                    troupsMoved = true;
                    break; // TODO:
                }
                
                
                cout << "Sorry, the number you entered is invalid, please try again:" << endl;
            }
        }
        
        if(!troupsMoved) {
            cout << "Sorry, the two countries are not adjacent" << endl;
        }

    }
    
}
