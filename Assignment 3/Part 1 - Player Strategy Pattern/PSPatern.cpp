//
//  PSPatern.cpp
//  Risk-fresh-start
//
//  Created by Bruno Robert on 31/10/2017.
//  Copyright © 2017 Bruno Robert. All rights reserved.
//

#include "PSPatern.hpp"
using namespace std;

Human::Human() {
    
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
int countryNameToID(string countryName, Map& m){
    vector<CountryNode*> cl = m.getCountryList();
    for (vector<CountryNode*>::iterator country = cl.begin(); country != cl.end(); country++) {
        if((*country)->getCountName() == countryName) {
            return (*country)->getCountryId();
        }
    }
    
    return -1;//error, country not found
}

void Human::getFortifyValues(int *startingCountry, int *destinationCountry, int *numberOftroupsToMove, Map& m) {
    
    
    //Getting and checking starting country
    cout << "please select a starting country" << endl;
    while(true) {
        cin >> *startingCountry;
        
        //checks if the starting coutry is valid
        if((*startingCountry >= 1) && (m.getcoutryById(*startingCountry) != NULL)) {
            break;
        }
        
        cout << "Sorry, the value you entered is not valid, please try again:" << endl;
    }

    //Getting and checking the destination country
    cout << "please select the destination country" << endl;
    while(true) {
        cin >> *destinationCountry;
        if((*destinationCountry >= 1) && (m.getcoutryById(*destinationCountry) != NULL)) {
            break;
        }
        
        cout << "Sorry, the value you entered is not valid, please try again:" << endl;
    }
    
}
