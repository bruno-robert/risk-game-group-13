//
//  newStratDriver.cpp
//  newStrat
//
//  Created by Bruno Robert on 16/11/2017.
//  Copyright © 2017 Bruno Robert. All rights reserved.
//

//used for random number generation
#include <ctime>
#include <cstdlib>


#include <stdio.h>

#include "GameStartOSX.h"

using namespace std;

int main() {
    
    srand((int)time(NULL));
    
    GameStart gs;
    gs.setPlayers(3);
    gs.setGameStart("World.map");
    
    return 0;
}
