
#ifndef GAMESTATSDECORATOR_H
#define GAMESTATSDECORATOR_H

#include "GameStatsObserver.h"

class GameStatsDecorator : public GameStatsObserver {
public:
	GameStatsDecorator(GameStatsObserver *decoratedGameStats);
	virtual void update(string message);

protected:
	GameStatsObserver *decoratedGameStats;

};

class DominationObserver : public GameStatsDecorator{
public:
	DominationObserver(GameStatsObserver *decoratedGameStats);
	virtual void update(string message);
	void printDominationStats();
};

class HandObserver : public GameStatsDecorator{
public:
	HandObserver(GameStatsObserver *decoratedGameStats);
	virtual void update(string message);
	void printHandInfo();
};

class ControlObserver : public GameStatsDecorator{
public:
	ControlObserver(GameStatsObserver *decoratedGameStats);
	virtual void update(string message);
	void printContinentControlInfo();
};

#endif /* GAMESTATSDECORATOR_H */

