#pragma once


#include "Player.h"
#include "Cards.h"
#include "dice.h"
#include "Map.h"
#include "ReinforcePhase.h"

class Passive : public PlayerStrategyPattern{

public:
	Passive();
	void executeReinforce(Player& user);
	void executeAttack(Player& user);
	void executeFortify(Player& user);
};