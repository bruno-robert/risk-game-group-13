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
 If the values are valid, it will prompt user for a number of troop to move and checks if that value is valid.
 If will then return (via given pointer parameters) the starting country id and destination coutry id as well as the number of troop to move.
 @param startingCountry startingCoutry pointer, used to return starting coutry ID
 @param destinationCountry destinationCountry pointer, used to return the destination country ID
 @param numberOfTroopsToMove numberOftroopToMove, used to return the number of troop to be moved from start to destination coutry
 @return returns true if the values given by the user are all correct, false if there was an error picking the values
 */
void Human::executeFortify(Player& user) {
        
}

void Human::executeAttack(Player& user){
    
}

void Human::executeReinforce(Player& user) {
    
}
