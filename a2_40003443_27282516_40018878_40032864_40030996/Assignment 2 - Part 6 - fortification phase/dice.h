//============================================================================
// Name        : Dice.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.3
// Copyright   : GNU Public license 3
// Description : Header file for the Dice class
//============================================================================

#ifndef DICE_H
#define DICE_H

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

class Dice {
public:
    Dice();
    int getDice1();
    int getDice2();
    int getDice3();
    float getPercent1();
    float getPercent2();
    float getPercent3();
    float getPercent4();
    float getPercent5();
    float getPercent6();
    int getDiceAmount();
    void roll(int arr[], int amountOfDice); //takes array of min size 3
    int getTotalRolls();
    
private:
    int dice1, dice2, dice3;
    int diceAmount;
    float totalRolls, one, two, three, four, five, six;
    void diceToZero();
    int rollDie();
    
};

#endif /* DICE_H */

