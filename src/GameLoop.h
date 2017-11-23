//============================================================================
// Name        : GameLoop.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : main loop of the game
//============================================================================

#ifndef GameLoop_h
#define GameLoop_h

#include "Player.h"

using namespace std;
class MainGameLoop : Subject {
private:
    vector <Player*> playerLsit;
    bool isGameEnd = false;
public:
    MainGameLoop();
    ~MainGameLoop();
	// Returns -1 if a draw, otherwise returns winning player ID.
    int startGame(Map* m ,int numberOfPlayers, vector<Player *>& playerList, int turnLimit); //starts the game loop
    
};


#endif /* GameLoop_h */


