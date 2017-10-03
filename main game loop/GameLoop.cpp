//============================================================================
// Name        : GameLoop.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.1
// Copyright   : GNU Public license 3
// Description : main loop of the game
//============================================================================


/*
 Provide a group of C++ classes that implements the main game loop following the
 official rules of the game of Risk. During the main game loop, proceeding in a
 round-robin fashion as setup in the startup phase, every player is given the
 opportunity to do each of the following actions during their turn:
     1. Reinforcements phase
     2. Attack phase
     3. Fortification phase
 This loop shall continue until only one player controls all the countries in the map,
 at which point a winner is announced and the game ends. You must deliver a driver
 that demonstrates that 1) every player gets turns in a round-robin fashion and that
 their reinforcement(), attack() and fortification() methods are called 2) the game
 ends when a player controls all the countries (the driver should explicitly give all
 the countries to one player, i.e. no real code for battles needs to be executed).
 */
#include "GameLoop.h"
using namespace std;


