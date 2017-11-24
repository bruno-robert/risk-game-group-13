//============================================================================
// Name        : GameStatsObserver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.2
// Copyright   : GNU Public license 3
// Description : Prints update "players world domination view" as the state of the map changes
//============================================================================

#include "GameStatsObserver.h"
#include "GameStatsDecorator.h"
#include "GameLoop.h"
#include "Observer.h"
#include "Player.h"
#include "Attack.h"
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

bool GameStatsObserver::showMenu = true;
int GameStatsObserver::round = 1;
int GameStatsObserver::turn = 0;
vector<Player*> GameStatsObserver::subjectPlayers = null();
Attack*  GameStatsObserver::subjectAttack = NULL;
Map*  GameStatsObserver::map = NULL;

vector<Player*> GameStatsObserver::null(){
	Player player1;
	vector<Player*> dummyVector;
	dummyVector.push_back(&player1);
	return dummyVector;
}

GameStatsObserver::GameStatsObserver() {
	//Empty
}

void GameStatsObserver::setPlayerSubject(vector<Player*> playerList) {
	//Make the players the subjects
	subjectPlayers = playerList;

	//Attack observer to each each subject
	for (Player* p : subjectPlayers)
		p->attach(this);
}

void GameStatsObserver::setAttackSubject(Attack* attack) {
	subjectAttack = attack;
	subjectAttack->attach(this);
}

GameStatsObserver::~GameStatsObserver() { //DELETE
	for (Player* p : subjectPlayers)
		p->detach(this);

	//subjectAttack->detach(this);
}

void GameStatsObserver::setMap(Map* gameMap) {
	this->map = gameMap;
}

void GameStatsObserver::update(string message) {

	if (message == "GameStats" || message == "GameStats Turn"){
		if (message == "GameStats Turn")
			turn++;
		printTurn();
	}
	//Else do nothing, the notify is not directed to this observer

}

void GameStatsObserver::printTurn() {

	cout << "------------Turn: " << turn << "\n";

}


int GameStatsObserver::gameStatsObserverMenu() {

	if (showMenu) {

		//Menu display
		cout << "--- Games Statistics Observer/Decorator Menu ---" << endl;
		cout << "How much information do you want?" << endl;
		cout << "1. BASIC - Show turn number" << endl;
		cout << "2. PLAYER DOMINATION - Show percentage of map owned by each player" << endl;
		cout << "3. PLAYER HAND - Show the hand of each player" << endl;
		cout << "4. CONTINENT CONTROL - Show which continent(s) each player owns" << endl;

		int answer;
		string answerString = " ";

		bool done = false;
		do {
			//Ask question
			cout << "Please select an option number." << endl;
			cin >> answerString;

			done = true;    //assume input is correct

							//Verify if input is int
			stringstream convert(answerString);

			if (!(convert >> answer)) {
				cout << "Please input an integer." << endl;
				done = false;
				continue;
			}

			//Verify answer
			if (answer < 1 || answer > 4) {

				cout << "You must choose a number between 1 and 4" << endl;
				done = false;

			}

		} while (!done);

		showMenu = yesNoQuestion("Do you want to see this menu again?");

		return answer;
	}

	return 0;
}

bool GameStatsObserver::yesNoQuestion(string question)
{
	while (true)
	{
		cout << question << " y/n" << endl;

		string answer;
		cin >> answer;

		transform(answer.begin(), answer.end(), answer.begin(), ::toupper);

		if (answer == "Y" || answer == "YES")
		{
			return true;
		}

		else if (answer == "N" || answer == "NO")
		{
			return false;
		}

		else
		{
			cout << "Please input either Yes or No as your answer." << endl;
		}
	}
}

GameStatsObserver* GameStatsObserver::createObserver(GameStatsObserver* observer) {

	//Het user input for observer amount
	int answer = gameStatsObserverMenu();

	switch (answer) {
	case 1:
		//No action needed
		break;
	case 2:
		return new DominationObserver(observer);
		break;
	case 3:
		observer = new DominationObserver(observer);
		return new HandObserver(observer);
		break;
	case 4:
		observer = new DominationObserver(observer);
		observer = new HandObserver(observer);
		return new ControlObserver(observer);
		break;
	}

	return observer;
}
