//============================================================================
// Name        : MapLoader.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : Class that handles reading a ".map" file, and creates a map file from the data within. It also throws an exception and exits if the
//					  file has invalid data.
//============================================================================

#include "MapLoader.h"
#include <iostream>
#include <fstream>

using namespace std;

MapLoader::MapLoader()
{
	map = new Map();
}

Map* MapLoader::getMap() { return map; }

void MapLoader::ReadFile(string FileName)
{
	string currentLine;
	ifstream mapFile (FileName);

	try
	{
		if (mapFile.is_open())
		{
			// Grab [map] info:
			getline(mapFile, currentLine); // Skip the [MAP] line
			getline(mapFile, currentLine); // The author line
			author = ExtractValue(currentLine);
			getline(mapFile, currentLine); // The image line
			image = ExtractValue(currentLine);
			getline(mapFile, currentLine); // The wrap line
			wrap = ExtractValue(currentLine);
			getline(mapFile, currentLine); // The scroll line
			scroll = ExtractValue(currentLine);
			getline(mapFile, currentLine); // The warn line
			warn = ExtractValue(currentLine);

			// Debug printing
			cout << "Author is " << author << ", the image file is " << image << "; wrap is " << wrap << ", scroll is set to " << scroll << " and warnings are set to " << warn << endl;

			getline(mapFile, currentLine); // Skip the blank line

			// Get the continents data:
			getline(mapFile, currentLine); // Skip the [CONTINENTS] line
			if (currentLine != string("[Continents]")) throw MapLoaderException("Invalid map format: [Continents] tag is missing.");

			while (getline(mapFile, currentLine) && currentLine != "")
			{
				// Split string from the token "=":
				string continentName = currentLine.substr(0, currentLine.find('='));
				if (continentName == "") throw MapLoaderException("Continent with empty name was provided.");
				
				int continentValue = stoi(currentLine.substr(currentLine.find('=') + 1)); // Grabs string after the = and converts to an integer
				// The above line will throw std::invalid_argument if the continentValue contains text.
				if (continentValue < 0) throw MapLoaderException("Negative continent value was provided.");

				// Create objects!!!
				ContinentNode* cn = new ContinentNode(continentName, continentValue);
				map->addContinent(cn);
				// Debug printing
				cout << continentName << " was added to the map with a value of " << continentValue << endl;
			}
			cout << endl;

			// Get the territories data:
			getline(mapFile, currentLine); //skip the [territories] line
			if (currentLine != string("[Territories]")) throw MapLoaderException("Invalid map format: [Territories] tag is missing.");

			vector<string> territoryLines; // This vector will contain each line that contains information of each country.

			// Grab all the remaining lines, ignoring blank lines:
			while (getline(mapFile, currentLine))
			{
				if (currentLine != "")
				{
					territoryLines.push_back(currentLine);
				}
			}

			// Create all the country objects:
			for (string &tL : territoryLines)
			{
				// Split strings from token ",":
				string countryName = tL.substr(0, tL.find(','));
				tL = tL.substr(tL.find(',') + 1); // Clear data that was already parsed

				// Go through the position values:
				tL = tL.substr(tL.find(',') + 1);
				tL = tL.substr(tL.find(',') + 1);

				// Set continent name:
				string countryContinentName = tL.substr(0, tL.find(','));

				ContinentNode* countryContinent = findContinent(countryContinentName);
				if (findContinent(countryContinentName) == NULL)
				{
					string error = "The continent of the country " + countryName + " is invalid.";
					throw new MapLoaderException(error.c_str());
				}
				tL = tL.substr(tL.find(',') + 1); // Clear data that was already parsed

				// Create country object:
				CountryNode* country = new CountryNode(countryName, NULL);
				map->addCountry(country);

				country->setContinent(countryContinent);

				// Debug printing
				cout << "Country " << countryName << " was created and is in " << countryContinentName << endl;
			}
			cout << endl;

			// Create the neighbor links between countries:
			vector<CountryNode*> countryList = map->getCountryList();
			for (int i = 0; i < countryList.size(); ++i)
			{
				string current = territoryLines.at(i);
				// Get list of neighbors:
				vector<string> neighborList;
				while (current.find(',') != string::npos)
				{
					neighborList.push_back(current.substr(0, current.find(','))); // Add new neighbor to the list.
					current = current.substr(current.find(',') + 1);
				}

				for (string n : neighborList)
				{
					CountryNode* adjacentCountry = findCountry(n);
					if (adjacentCountry != NULL)
						countryList.at(i)->addAdjCount(adjacentCountry);
				}
			}
		}
		else
		{
			cout << "-------ERROR-------" << endl << "File couldn't be opened..." << endl;
			exit(EXIT_FAILURE);
		}
	}
	catch (MapLoaderException mle)
	{
		cout << "-------ERROR-------" << endl;
		cout << mle.what() << endl;
		exit(EXIT_FAILURE);
	}
	catch (std::invalid_argument ia)
	{
		cout << "-------ERROR-------" << endl << "Text/empty/invalid value was found when a numerical value was expected." << endl;
		exit(EXIT_FAILURE);
	}
}

// This function is used to facilitate returning v
string MapLoader::ExtractValue(string line)

{
	return line.substr(line.find('=')+1);
}

// This function searches for a given continent by its name.
// It will return a pointer to the ContinentNode if one is found.
// Otherwise, it will return null.
ContinentNode* MapLoader::findContinent(string continent)
{
	vector<ContinentNode*> continents = map->getContinentList();
	for (ContinentNode* x : continents)
	{
		if (x->getContName() == continent) return x;
	}
	return NULL;
}

CountryNode* MapLoader::findCountry(string country)
{
	vector<CountryNode*> countries = map->getCountryList();
	for (CountryNode* x : countries)
	{
		if (x->getCountName() == country) return x;
	}
	return NULL;
}

void MapLoader::printMap()
{
	vector<CountryNode*> countries = map->getCountryList();
	for (CountryNode* cn : countries)
	{
		cout << "Country: " << cn->getCountName() << endl;
		cout << "Neighbor List" << endl;
		
		vector<CountryNode*> neighbors = cn->getAdjCount();
		for (CountryNode* n : neighbors)
		{
			cout << n->getCountName() << ", ";
		}
		cout << endl << endl;
	}
}

MapLoader::~MapLoader()
{
	delete map;
}

MapLoaderException::MapLoaderException(char const* const message) throw() : std::runtime_error(message)
{

}
char const* MapLoaderException::what() const throw()
{
	return std::runtime_error::what();
}
