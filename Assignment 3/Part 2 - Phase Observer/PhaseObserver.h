//============================================================================
// Name        : PhaseObserver.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : Prints the info of each phase as it happens.
//============================================================================

#pragma once

#include "Observer.h"
#include "Attack.h"
#include "FortificationPhase.h"
#include "ReinforcePhase.h"
#include <iostream>
#include <vector>

class PhaseObserver : public Observer
{
	Attack* attackSubject;
	Reinforce* reinforceSubject;
	FortificationPhase* fortificationSubject;
public:
	PhaseObserver();
	~PhaseObserver();

	void update(string message);
	void setAttackPhaseSubject(Attack* attack);
	void setReinforcePhaseSubject(Reinforce* reinforce);
	void setFortifyPhaseSubject(FortificationPhase* fortify);
};

