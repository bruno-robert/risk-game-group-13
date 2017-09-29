/* 
 * File:   dice.cpp
 * Author: Sabrina Rieck, 40032864
 * 
 * Created on September 23, 2017, 1:15 PM
 */


#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;
#include "dice.h"

/*To remove previously rolled values before each new turn to roll*/
void Dice::diceToZero() {
    dice1 = 0;
    dice2 = 0;
    dice3 = 0;
}

/*To roll one die and increase counter for amount rolled*/
int Dice::rollDie() {
    totalRolls++; //increase counter of total amount of rolls

    int result = rand() % 6 + 1;

    switch (result) //increase counter for appropriate number
    {
        case 1: one++;
            break;
        case 2: two++;
            break;
        case 3: three++;
            break;
        case 4: four++;
            break;
        case 5: five++;
            break;
        case 6: six++;
            break;
    }

    return result;
}

Dice::Dice() {
    dice1 = 0;
    dice2 = 0;
    dice3 = 0;
    totalRolls = 0;
    one = 0;
    two = 0;
    three = 0;
    four = 0;
    five = 0;
    six = 0;
    srand(time(NULL));
}

/*Dice getters*/
int Dice::getDice1() {
    return dice1;
}

int Dice::getDice2() {
    return dice2;
}

int Dice::getDice3() {
    return dice3;
}

int Dice::getTotalRolls() {
    return totalRolls;
}

/*To get the amount of times in percentage that each number has been rolled*/
float Dice::getPercent1() {
    return (one / totalRolls)*100;
}

float Dice::getPercent2() {
    return (two / totalRolls)*100;
}

float Dice::getPercent3() {
    return (three / totalRolls)*100;
}

float Dice::getPercent4() {
    return (four / totalRolls)*100;
}

float Dice::getPercent5() {
    return (five / totalRolls)*100;
}

float Dice::getPercent6() {
    return (six / totalRolls)*100;
}

//Get the amount of dice the player wants to role 

int Dice::getDiceAmount() {
    bool end = false;

    do {
        cout << "How many dice do you want to roll?" << endl;
        cin >> diceAmount;

        if (diceAmount < 1 || diceAmount > 3)
            cout << "You may only role 1, 2 or 3 dice." << endl;

        else
            end = true;
    } while (end != true);
    
    return diceAmount;
}

/*Roll function used*/
void Dice::roll(int arr[], int amountOfDice) {
    diceToZero(); //reset dice to null

    switch (amountOfDice) {
        case 3:
            dice3 = rollDie();
        case 2:
            dice2 = rollDie();
        case 1:
            dice1 = rollDie();
            arr[0] = dice1;
            arr[1] = dice2; //if only 1 die is rolled, die 2 and 3 are null
            arr[2] = dice3;
            break;
    }
}

