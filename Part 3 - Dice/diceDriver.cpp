//============================================================================
// Name        : DiceDriver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.3
// Copyright   : GNU Public license 3
// Description : Driver for the Dice class. Shows that all is working correctly.
//============================================================================

#include <cstdlib>
#include <iostream>
using namespace std;
#include "dice.h"

using namespace std;

int main() {

    /*Creating 3 dice objects*/
    Dice player1 = Dice();
    Dice player2 = Dice();
    Dice player3 = Dice();

    /*Testing amount of dice rolled from user input*/
    int diceAmountUser = player3.getDiceAmount();
    int results[3];
    player3.roll(results, diceAmountUser);
    int i = 1;
    for (int r : results) {
        if (r != 0)
            cout << "Dice " << i << ": " << r << endl;
        i++;
    }
    
    cout << "-----------------------------" << endl;

    /*Test if equal share of 1-6 values are returned by rolling dice a large amount of times*/
    int player1Results[3];
    int player2Results[3];
    for (int i = 0; i < 1000; i++) //Amount of times the dice are rolled by player x3 since each player roles 3 dice
    {
        player1.roll(player1Results, 3);
        player2.roll(player2Results, 3);
    }

    /*Return results of dice rolling to see compilation of the results*/
    cout << "Amount of times Player 1 rolled the dice: " << player1.getTotalRolls() << endl;
    cout << "Percentage of:" << endl;
    cout << "\tOnes: " << player1.getPercent1() << "%" << endl;
    cout << "\tTwos: " << player1.getPercent2() << "%" << endl;
    cout << "\tThrees: " << player1.getPercent3() << "%" << endl;
    cout << "\tFours: " << player1.getPercent4() << "%" << endl;
    cout << "\tFives: " << player1.getPercent5() << "%" << endl;
    cout << "\tSixes: " << player1.getPercent6() << "%" << endl;
    
    float player1PercentageTotal = player1.getPercent1() + player1.getPercent2() + player1.getPercent3() + player1.getPercent4() + player1.getPercent5() + player1.getPercent6();
    
    cout << "Percentage total :" << player1PercentageTotal << "%" << endl;
    cout << "A percentage total of 100% indicates that no other value than 1-6 was returned by the dice" << endl;
    
    cout << "-----------------------------" << endl;
    
    cout << "Amount of times Player 2 rolled the dice: " << player2.getTotalRolls() << endl;
    cout << "Percentage of:" << endl;
    cout << "\tOnes: " << player2.getPercent1() << "%" << endl;
    cout << "\tTwos: " << player2.getPercent2() << "%" << endl;
    cout << "\tThrees: " << player2.getPercent3() << "%" << endl;
    cout << "\tFours: " << player2.getPercent4() << "%" << endl;
    cout << "\tFives: " << player2.getPercent5() << "%" << endl;
    cout << "\tSixes: " << player2.getPercent6() << "%" << endl;

    float player2PercentageTotal = player2.getPercent1() + player2.getPercent2() + player2.getPercent3() + player2.getPercent4() + player2.getPercent5() + player2.getPercent6();
    
    cout << "Percentage total :" << player2PercentageTotal << "%" << endl;
    cout << "A percentage total of 100% indicates that no other value than 1-6 was returned by the dice" << endl;


    return 0;
}

