//============================================================================
// Name        : Part2Driver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : Driver which handles testing of the MapLoader class and its map reading capacities.
//============================================================================

#include <iostream>
using namespace std;
#include "MapLoader.h"

int main()
{
	MapLoader ml;
	string value;
	
    bool mapFound = false;
    while(!mapFound) {
        cout << "Enter map name: ";
        cin >> value;
        try {
            
            ml.ReadFile(value);
            ml.printMap();
            mapFound = true;
        } catch (MapLoaderException) {
            cout << "The map name you entered couldn't be found" << endl;
        }
    }
    
	

	return 0;
}
