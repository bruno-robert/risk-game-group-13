//============================================================================
// Name        : MapLoader.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : Class that handles reading a ".map" file, and creates a map file from the data within. It also throws an exception and exits if the
//					  file has invalid data.
//============================================================================

#pragma once
#include <string>
#include "Map.h"
using namespace std;

class MapLoader
{
	Map* map;
	string author;
	string image;
	string wrap;
	string scroll;
	string warn;

public:
	MapLoader();
	void ReadFile(string filename);
	string ExtractValue(string line);
	ContinentNode* findContinent(string continent);
	CountryNode* findCountry(string country);
	void printMap();
	Map* getMap();
	~MapLoader();
};

class MapLoaderException : public std::runtime_error
{
public:
	MapLoaderException(char const* const message) throw();
	virtual char const* what() const throw();
};