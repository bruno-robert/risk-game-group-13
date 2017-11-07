//============================================================================
// Name        : FortificationPhase.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : Moves troups from one country to another during the fortification phase of a player's turn
//============================================================================

#include "FortificationPhase.h"

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

/**
 The fortify method takes 2 arguments:
 int player: the ID of the player that is fortifying
 Map& m: The Game map object that is being used this game
 
 The Fortify method will ask the player for input on a starting and destination country. It will check if the inputs are valid.
 It will then ask for a number of troups to move and check if that number is valid.
 It will then proceded to moving the right number of troups from the starting country to the destination coutry.
 */
void FortificationPhase::fortify(int player, Map& m ) {
    int startingCountry;
    int destinationCountry;
    int numberOfTroops;
    bool troupsMoved = false;//true once the troups are moved
    while(!troupsMoved) {
        //Getting and checking starting country
        cout << "please select a starting country" << endl;
        while(true) {
            startingCountry = inputCountry(m);
            
            //checks if the starting coutry is valid
            if((startingCountry >= 0) && (m.getcoutryById(startingCountry) != NULL)) {
                break;
            }
            
            cout << "Sorry, the value you entered is not valid, please try again:" << endl;
        }

        //Getting and checking the destination country
        cout << "please select the destination country" << endl;
        while(true) {
			destinationCountry = inputCountry(m);
            if((destinationCountry >= 1) && (m.getcoutryById(destinationCountry) != NULL)) {
                break;
            }
            
            cout << "Sorry, the value you entered is not valid, please try again:" << endl;
        }

        //checking if the countries are adjacent and if they are owned by the player
        if((m.getcoutryById(startingCountry)->getOwnedBy() == player) && m.getcoutryById(startingCountry)->isCountAdjacent(destinationCountry)) {
            cout << "please enter the number of troops you want to move:" << endl;
            while(true) {
                
                cin >> numberOfTroops;
                if((numberOfTroops >= 1) && (numberOfTroops < m.getcoutryById(startingCountry)->getNumberOfTroops() ) ){
                    //removing troups from starting country
                    m.getcoutryById(startingCountry)->setNumberOfTroops(m.getcoutryById(startingCountry)->getNumberOfTroops() - numberOfTroops);
                    //adding troups to destination country
                    m.getcoutryById(destinationCountry)->setNumberOfTroops(m.getcoutryById(destinationCountry)->getNumberOfTroops() + numberOfTroops);
                    cout << "troups moved!" << endl;
                    troupsMoved = true;
                    break;
                }
                
                
                cout << "Sorry, the number you entered is invalid, please try again:" << endl;
            }
        }
        
        if(!troupsMoved) {
            cout << "Sorry, the two countries are not adjacent" << endl;
        }

    }

	string message = "PHASE_OBSERVER|Moved " + to_string(numberOfTroops) + " troops from " 
												+ m.getcoutryById(startingCountry)->getCountName() + " to "
												+ m.getcoutryById(destinationCountry)->getCountName();
	notify(message);
}

int FortificationPhase::inputCountry(Map &m)
{
	string countryName;
	bool isInMap = false;
	CountryNode country;

	vector<CountryNode*> countryList = m.getCountryList();

	do
	{
		cin >> countryName;

		for (CountryNode* cn : countryList)
		{
			if (cn->getCountName() == countryName)
			{
				country = *cn;
				isInMap = true;
				break;
			}
		}
	}
	while (!isInMap);
	
	return country.getCountryId();
}