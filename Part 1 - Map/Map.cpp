//============================================================================
// Name        : Map.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.3
// Copyright   : GNU Public license 3
// Description : concise description of the part you are working on
//============================================================================

/*
 *Part 1: Map
 *Provide a group of C++ classes that implement a map for the game of Risk.
 *The map class must be implemented as a connected graph, where each node
 *represents a country. Edges between nodes represent adjacency between
 *countries. Each country can have any number of adjacent countries.
 *Continents must also be connected subgraphs, where each country belongs to
 *one and only one continent. Each country is owned by a player and contain a
 *number of armies. The map class can be used to represent any map
 *configuration (i.e. not only the “Risk” map). You must deliver a driver that
 *creates a map and demonstrates that the map class implements the following
 *verifications: 1) the map is a connected graph, 2) continents are connected
 *subgraphs and 3) each country belongs to one and only one continent.
 *The driver must provide test cases for various valid/invalid maps.
 */

#include "Map.h"
using namespace std;

//continent class
int ContinentNode::numOfCont = 0;
//constructor
ContinentNode::ContinentNode(string name, int contScore) {
	this->contName = name;
	this->contScore = contScore;
	continentID = numOfCont;
	numOfCont++;
}

ContinentNode::ContinentNode() {
    continentID = numOfCont;
    numOfCont++;
}

//deconstructor
ContinentNode::~ContinentNode() {
}


//add adjacent continent
void ContinentNode::addAdjCont(ContinentNode* contNode) {
	adjCont.push_back(contNode);
}

//country class
int CountryNode::numOfCount = 0;

//constructor
CountryNode::CountryNode(string name, ContinentNode* continent) {
	this->countName = name;
    if(continent != NULL) {
        this->continent = continent;
        continent->addCountry(this);  //adding a pointer ->> this country to the Continent the country is part of
    }
    
	countryID = numOfCount;
	ownedBy = -1;
	numOfCount++;
}

//default constructor
CountryNode::CountryNode() {
    countryID = numOfCount;
    ownedBy = -1;
    numOfCount++;
}


//deconstructor
CountryNode::~CountryNode() {
    //the vectors of Countries are not deleted as the countries might still be in use
    //the continent vector is automatically cleared but not deleted (as the continent might still be in use)
}

//add adjacent country
void CountryNode::addAdjCount(CountryNode* countNode){
	adjCount.push_back(countNode);
}

//map Class
//constructor
Map::Map() {

}

//deconstructor
Map::~Map() {
//    for (int i = 0; i < countryList.size(); i++) {
//        delete *countryList.end();
//        countryList.pop_back();
//        
//    }
//    countryList.clear();
	cout << "map destroyed" << endl;
}

//add a country to the map
void Map::addCountry(CountryNode* c){
	countryList.push_back(c);
}

//add a continent to the map
void Map::addContinent(ContinentNode* c){
	continentList.push_back(c);
}

//check if the continents are aconnected
int Map::checkConnectivity(ContinentNode* cn, int ctr){
	
	cn -> setVisited(true);

	for (int i = 0; i < (cn -> getAdjCont().size()); i++) {
		if (cn -> getAdjCont().at(i) -> isVisited()){
			
		} else {
			ctr  = checkConnectivity(cn -> getAdjCont().at(i), ctr);
		}
	}
	
	return ++ctr;

}

//check if countries are connected
int Map::checkConnectivity(CountryNode* cn, int ctr){
	
	cn -> setVisited(true);

	for (int i = 0; i != (cn -> getAdjCount().size()); i++) {
		if (cn -> getAdjCount().at(i) -> isVisited()){
			
		} else {
			ctr  = checkConnectivity(cn -> getAdjCount().at(i), ctr);
		}
	}
	
	return ++ctr;

}

//resets each node's visited bool (country and continent)
//after a check (either of the two above methods) always do a reset!
void Map::resetNodes(){
	for (int i = 0; i < continentList.size(); i++){
		continentList.at(i) -> setVisited(false);
	}
	for (int i = 0; i < countryList.size(); i++){
		countryList.at(i) -> setVisited(false);
	}
}

