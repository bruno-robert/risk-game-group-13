//============================================================================
// Name        : GameLoop.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.1
// Copyright   : GNU Public license 3
// Description : main loop of the game
//============================================================================

#ifndef GameLoop_h
#define GameLoop_h

#include "Part_4.h"

using namespace std;
class MainGameLoop {
private:
    vector <Player*> playerLsit;
    bool isGameEnd = false;
public:
    MainGameLoop();
    ~MainGameLoop();
    void startGame(Map* m ,int numberOfPlayers, int playerTurn, bool test); //starts the game loop
    
};


#endif /* GameLoop_h */
