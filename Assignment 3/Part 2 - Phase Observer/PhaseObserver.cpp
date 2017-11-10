//============================================================================
// Name        : PhaseObserver.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.0
// Copyright   : GNU Public license 3
// Description : Prints the info of each phase as it happens.
//============================================================================

#include "PhaseObserver.h"
#include <iostream>

PhaseObserver::PhaseObserver()
{
	attackSubject = NULL;
	reinforceSubject = NULL;
	fortificationSubject = NULL;
}

PhaseObserver::~PhaseObserver()
{

}

void PhaseObserver::update(string message)
{
	{
		// The basic "print this message to the observer" message:
		if (message.find("PHASE_OBSERVER|") == 0) // If "PHASE_OBSERVER" is located at the very start of the string.
		{
			cout << "++++++++++++++++++++++++++++++++++++++++++" << message.substr(message.find_first_of("|") + 1) << endl;
		}

		else if (message == "Attack to/from set")
		{			
			string attackerName = attackSubject->getAttackingCountryData()->getCountName();
			string defenderName = attackSubject->getDefendingCountryData()->getCountName();
			cout << "++++++++++++++++++++++++++++++++++++++++++" << attackerName << " is attacking " << defenderName << endl;
		}

		else if (message.find("Troops lost calculated|") == 0) // If "Troops lost calculated" is located at the very start of the string.
		{
			string data = message.substr(message.find_first_of("|") + 1);
			string attackerLoss = data.substr(0, data.find_first_of("|"));
			string defenderLoss = data.substr(data.find_first_of("|")+1);

			cout << "++++++++++++++++++++++++++++++++++++++++++" << "Attacker loses " << attackerLoss << " army personnel" << endl;
			cout << "++++++++++++++++++++++++++++++++++++++++++" << "Defender loses " << defenderLoss << " army personnel" << endl;

		}

		else if (message == "Attack ended")
		{
			string defenderName = attackSubject->getDefendingCountryData()->getCountName();
			cout << "++++++++++++++++++++++++++++++++++++++++++" << "The attack on " + defenderName << " was ended." << endl;
		}

		else if (message == "Attacker conquered")
		{
			string attackerName = attackSubject->getAttackingCountryData()->getCountName();
			string defenderName = attackSubject->getDefendingCountryData()->getCountName();
			cout << "++++++++++++++++++++++++++++++++++++++++++" << "Player " << attackerName << " has conquered " << defenderName << "!" << endl;
		}

		else if (message == "Troop Loss")
		{
			int attackerAmountLost = attackSubject->getAttackerTroopLoss();
			int defenderAmountLost = attackSubject->getDefenderTroopLoss();
			cout << "++++++++++++++++++++++++++++++++++++++++++" << "Attacker lost " << attackerAmountLost << " units and Defender lost " << defenderAmountLost << " units" << endl;
		}

		else if (message == "Card Exchange")
		{
			string typeOfExchange = reinforceSubject->getExchangeType();
			cout << "++++++++++++++++++++++++++++++++++++++++++" << typeOfExchange << endl;
		}

		else if (message == "Troops Moved")
		{
			string toCountry = reinforceSubject->getReinforcedCountryData()->getCountName();
			int amount = reinforceSubject->getTroopsMoved();
			cout << "++++++++++++++++++++++++++++++++++++++++++" << "Player reinforced " << toCountry << " with " << amount << " troop(s)" << endl;
		}
		
		else if (message == "Fortification occured")
		{
			int troopsMoved = fortificationSubject->getAmountTroopsMoved();
			string destination = fortificationSubject->getDestinationCountry()->getCountName();
			string start = fortificationSubject->getStartingCountry()->getCountName();

			cout << "++++++++++++++++++++++++++++++++++++++++++" << "Player moved " << to_string(troopsMoved) << " troops from " << start << " to " << destination << endl;
		}

		// getFortifyingPLayer
		if (message == "Fortification Started")
		{
			int player = fortificationSubject->getFortifyingPlayer()->getPlayerID();
			cout << "++++++++++++++++++++++++++++++++++++++++++" << "Player " << to_string(player) << "'s Fortification Phase:" << endl;
		}

		//message == "Attack Started" getAttackingPLayer
		if (message == "Attack Started")
		{
			int player = attackSubject->getAttackingPlayerData()->getPlayerID();
			cout << "++++++++++++++++++++++++++++++++++++++++++" << "Player " << to_string(player) << "'s Attack Phase:" << endl;
		}

		//message == "Reiforce Started" getReinforcingPlayer
		if (message == "Reinforcing Started")
		{
			int player = reinforceSubject->getReinforcingPlayer()->getPlayerID();
			cout << "++++++++++++++++++++++++++++++++++++++++++" << "Player " << to_string(player) << "'s Reinforcement Phase:" << endl;
		}
	}
}

void PhaseObserver::setAttackPhaseSubject(Attack* attack)
{
	this->attackSubject = attack;
	attackSubject->attach(this);
}


void PhaseObserver::setReinforcePhaseSubject(Reinforce* reinforce)
{
	this->reinforceSubject = reinforce;
	reinforceSubject->attach(this);
}

void PhaseObserver::setFortifyPhaseSubject(FortificationPhase* fortify)
{
	this->fortificationSubject = fortify;
	fortificationSubject->attach(this);
}
