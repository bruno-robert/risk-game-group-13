//============================================================================
// Name        : Map.h
// Author      : Bruno Robert
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.3
// Copyright   : GNU Public license 3
// Description : Map Section of the Risk game
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

#ifndef __Map_H_INCLUDED__
#define __Map_H_INCLUDED__

#include <string>
#include <iostream>
#include <vector>
#include <list>

using namespace std;
class CountryNode;


/*
* Continents are represented as ContinentNode's
*/
class ContinentNode {
private:
	static int numOfCont;				//total number of continents
	string contName;					//name of the continent
	int continentID;					//each continent node has a unique ID
	vector <ContinentNode *> adjCont;	//list of pointers to adjacent contiennts
	vector <CountryNode *> countryList;
	int contScore;						//score of the continent (extra troups per turn)
	bool visited;						//visited bool (used during the connectivity check)
public:
	ContinentNode(string name, int contScore);	//construct
	ContinentNode();
	virtual ~ContinentNode();					//deconstruct
	void addAdjCont(ContinentNode* countNode);	//add adjacent continent

												//getters and setters
	vector<CountryNode*> getCountryList() const {
		return countryList;
	}

	void addCountry(CountryNode* country) {
		countryList.push_back(country);
	}

	//removes the given country from the Continent's list of countries
	void removeCountry(CountryNode* country) {
		int i = 0;
		for (vector<CountryNode *>::iterator iter = countryList.begin(); iter != countryList.end(); ++iter) {
			if (country == countryList.at(i)) {
				countryList.erase(iter);
			}
			i++;
		}
	}

	const vector<ContinentNode*>& getAdjCont() const {
		return adjCont;
	}

	bool isVisited() const {
		return visited;
	}

	void setVisited(bool visited) {
		this->visited = visited;
	}

	void setAdjCont(const vector<ContinentNode*>& adjCont) {
		this->adjCont = adjCont;
	}

	int getContinentId() const {
		return continentID;
	}

	void setContinentId(int continentId) {
		continentID = continentId;
	}

	string getContName() const {
		return contName;
	}

	void setContName(const string& contName) {
		this->contName = contName;
	}

	int getContScore() const {
		return contScore;
	}

	void setContScore(int contScore) {
		this->contScore = contScore;
	}

	static int getNumOfCont() {
		return numOfCont;
	}

};

/**
Countries are represented as CountryNode's.
*/
class CountryNode {
private:
	static int numOfCount;
	int countryID;					//each country has a unique ID
	string countName;				//name of the country
	vector<CountryNode *> adjCount;	//list of pointers to adjacent countries
	ContinentNode * continent;		//continent the country is part of
	int ownedBy;					//Id of the player who currently owns the country
	int numberOfTroups;			//number of troups in the country

	bool visited;					///visited bool (used during the connectivity check)
public:
	CountryNode(string name, ContinentNode* continent);	//construct
	CountryNode();  //default constructor
	virtual ~CountryNode();									//deconstruct
	void addAdjCount(CountryNode* countNode);				//add adjacent country
	bool isCountAdjacent(int countID) {
		for (vector<CountryNode *>::iterator country = adjCount.begin(); country != adjCount.end(); country++) {
			if ((*country)->getCountryId() == countID) {
				return true;
			}

		}

		return false;
	}

	//getters and setters
	//removes the country from it's previous continent then add's it to the given continent
	void setContinent(ContinentNode* continent) {
		if (this->continent != NULL) {
			this->continent->removeCountry(this);
		}
		this->continent = continent;
		if (continent != NULL) {
			continent->addCountry(this);
		}

	}

	ContinentNode* getContinent() {
		return continent;
	}

	const vector<CountryNode*>& getAdjCount() const {
		return adjCount;
	}

	bool isVisited() const {
		return visited;
	}

	void setVisited(bool visited) {
		this->visited = visited;
	}

	void setAdjCount(const vector<CountryNode*>& adjCount) {
		this->adjCount = adjCount;
	}

	string getCountName() const {
		return countName;
	}

	void setCountName(const string& countName) {
		this->countName = countName;
	}

	int getCountryId() const {
		return countryID;
	}

	void setCountryId(int countryId) {
		countryID = countryId;
	}

	void setNumberOfTroups(const int numberOfTroups) {
		this->numberOfTroups = numberOfTroups;
	}

	int getNumberOfTroups() const {
		return numberOfTroups;
	}

	static int getNumOfCount() {
		return numOfCount;
	}

	int getOwnedBy() const {
		return ownedBy;
	}

	void setOwnedBy(int ownedBy) {
		this->ownedBy = ownedBy;
	}
};

/*
* Map class
* A map contains a list of countries and continents (ultimatly a graph).
* A map can check if it's countries and continents respectivley form connected graphs
*/
class Map {
private:
	vector <CountryNode *> countryList;		//list of countries
	vector <ContinentNode *> continentList;	//list of continents
public:
	Map();				//constructor
	virtual ~Map();		//deconstructor
	void addCountry(CountryNode* c);	//add a country to the map
	void addContinent(ContinentNode* c);//add a continent to the map
	int checkConnectivity(ContinentNode* cn, int ctr);	//check if the continents are aconnected
	int checkConnectivity(CountryNode* cn, int ctr);	//check if countries are connected
	void resetNodes();					//resets each node's visited bool (country and continent)
										//after a check (either of the
										//two above methods) always do a reset

										//getters and setters
	const vector<ContinentNode*>& getContinentList() const {
		return continentList;
	}

	void setContinentList(const vector<ContinentNode*>& continentList) {
		this->continentList = continentList;
	}

	vector<CountryNode*>& getCountryList() {
		return countryList;
	}

	void setCountryList(const vector<CountryNode*>& countryList) {
		this->countryList = countryList;
	}

	CountryNode* getcoutryById(int ID) {
		for (vector<CountryNode*>::iterator iter = countryList.begin(); iter != countryList.end(); iter++) {
			if ((*iter)->getCountryId() == ID) {
				return *iter;
			}
		}
		return NULL;
	}

	CountryNode* getCountryByName(string name) {
		for (vector<CountryNode*>::iterator iter = countryList.begin(); iter != countryList.end(); iter++) {
			if ((*iter)->getCountName() == name) {
				return *iter;
			}
		}
		return NULL;
	}

	int getNumberOfcountriesOwnedById(int ID) {
		int ctr = 0;
		for (vector<CountryNode*>::iterator iter = countryList.begin(); iter != countryList.end(); iter++) {
			if ((*iter)->getOwnedBy() == ID) {
				ctr++;
			}
		}
		return ctr;
	}


};

#endif
