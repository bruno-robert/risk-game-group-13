//
//  PSPatern.cpp
//  Risk-fresh-start
//
//  Created by Bruno Robert on 31/10/2017.
//  Copyright © 2017 Bruno Robert. All rights reserved.
//

#include "PSPatern.hpp"
using namespace std;

PlayerStrategyPattern::PlayerStrategyPattern() {
    
}

PlayerStrategyPattern::~PlayerStrategyPattern() {
    
}

Human::Human() : PlayerStrategyPattern(){
    
}

Human::~Human() {
    
}

/**
 Takes a string and a Map and returns the Id of the country with the given name
 If the country doesn't exists, retursn -1
 @param countryName Name of the country
 @param m Map Object
 @return the ID of the country with name countryName. If the country doesn't exist, returns -1
 */
int Human::countryNameToID(string countryName, Map& m){// TODO: test functionality
    vector<CountryNode*> cl = m.getCountryList();
    for (vector<CountryNode*>::iterator country = cl.begin(); country != cl.end(); country++) {
        if((*country)->getCountName() == countryName) {
            return (*country)->getCountryId();
        }
    }
    
    return -1;//error, country not found
}

/**
 Human fortification method, asks for starting and destiantion countries. Checks if the entered coutries are valid.
 If the values are valid, it will prompt user for a number of troups to move and checks if that value is valid.
 If will then return (via given pointer parameters) the starting country id and destination coutry id as well as the number of troups to move.
 @param startingCountry startingCoutry pointer, used to return starting coutry ID
 @param destinationCountry destinationCountry pointer, used to return the destination country ID
 @param numberOftroupsToMove numberOftroupsToMove, used to return the number of troups to be moved from start to destination coutry
 @return returns true if the values given by the user are all correct, false if there was an error picking the values
 */
bool Human::getFortifyValues(int *startingCountry, int *destinationCountry, int *numberOftroupsToMove, Map& m, int player) {
    while (true) {
        
        //Getting and checking starting country
        cout << "please select a starting country" << endl;
        //temporary varibales
        string inputString;
        int tempInt= 0;
        int tempInt2= 0;
        while(true) {
            cin >> inputString;
            tempInt = countryNameToID(inputString, m);
            
            //checks if the starting coutry is valid
            if((tempInt >= 1) && (m.getcoutryById(tempInt) != NULL) && (m.getcoutryById(tempInt)->getOwnedBy() == player) && (m.getcoutryById(tempInt)->getNumberOfTroops() > 1)) {
                *startingCountry = tempInt;//setting starting country
                break;
            }
            
            cout << "Sorry, the value you entered is not valid, please try again (the country could have to few troups):" << endl;
        }
        
        //Getting and checking the destination country
        cout << "please select the destination country" << endl;
        while(true) {
            cin >> inputString;
            tempInt2 = countryNameToID(inputString, m);
            
            if((tempInt2 >= 1) && (m.getcoutryById(tempInt2) != NULL)&& (m.getcoutryById(tempInt)->getOwnedBy() == player)) {
                *destinationCountry = tempInt2;//settings destinationCountry
                break;
            }
            
            cout << "Sorry, the value you entered is not valid, please try again:" << endl;
        }
        
        //checks the adjacency of both countries and promtps user for number of troups to move
        if (m.getcoutryById(*startingCountry)->isCountAdjacent(*destinationCountry)) {
            cout << "please enter the number of troops you want to move (value between 1 and " << m.getcoutryById(*startingCountry)->getNumberOfTroops() << ":" << endl;
            while(true) {
                
                cin >> *numberOftroupsToMove;
                //if the number of troups is between 1 and the the number of troups in starting country -1
                if((*numberOftroupsToMove >= 1) &&
                   (*numberOftroupsToMove < m.getcoutryById(*startingCountry)->getNumberOfTroops() ) ){
                    return true;
                }
                
                
                cout << "Sorry, the number you entered is invalid, please try again:" << endl;
            }
        }
        
        cout << "Sorry the countries are not adjacent" << endl;
    }
    
    
    
    return false;
}

void Human::getAttackValues() {
    
}

void Human::getReinforceValues() {
    
}
