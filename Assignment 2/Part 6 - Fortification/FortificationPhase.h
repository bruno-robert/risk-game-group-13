//============================================================================
// Name        : FortificationPhase.hpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : Moves troups from one country to another during the fortification phase of a player's turn
//============================================================================

#ifndef FortificationPhase_hpp
#define FortificationPhase_hpp

#include <stdio.h>
#include "Player.h"
using namespace std;

class FortificationPhase : public Subject {
    vector <Player *> playerList;
	int inputCountry(Map &m);
public:
    FortificationPhase();
    ~FortificationPhase();
    void fortify(int player, Map& m );
};



#endif /* FortificationPhase_hpp */
