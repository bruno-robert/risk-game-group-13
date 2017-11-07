#pragma once


#include "Player.h"
#include "Cards.h"
#include "dice.h"
#include "Map.h"
#include "ReinforcePhase.h"
#include "Attack.h"


class Aggressive : public PlayerStrategyPattern {

public:
	Aggressive();
	void executeReinforce(Player& user);
	void executeAttack(Player& user);
	void executeFortify(Player& user);
};