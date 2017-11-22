//============================================================================
// Name        : GameStatsObserver.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.1
// Copyright   : GNU Public license 3
// Description : Prints update "players world domination view" as the state of the map changes
//============================================================================

#pragma once
#include "Observer.h"
#include "Attack.h"
#include "Map.h"
#include <vector>


class GameStatsObserver : public Observer {
public:
	GameStatsObserver();
	~GameStatsObserver();
	void setPlayerSubject(vector<Player*> playerList);
	void setAttackSubject(Attack* attack);
	void setMap(Map* map);
	void update(string message);
	void printTurn();
	int gameStatsObserverMenu();
	bool yesNoQuestion(string question);
	GameStatsObserver* createObserver(GameStatsObserver* observer);

protected:
	vector<Player*> subjectPlayers;
	Attack* subjectAttack;
	Map* map;
	int turn = 0;
	int round = 0;
	string view;
	static bool showMenu;
};
