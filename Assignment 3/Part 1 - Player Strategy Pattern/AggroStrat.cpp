

#include "AggroStrat.h"

Aggressive::Aggressive() : PlayerStrategyPattern()
{

}

void Aggressive::executeReinforce(Player& user) {


	//Finding the country with the most units and a target to attack
	int maxUnit = 0;
	int maxIndex = 0;

	for (int i = 0; i < user.getCountryByRef().size(); i++) {

		if (user.getCountryByRef().at(i)->getNumberOfTroops() > maxUnit) {

			vector<CountryNode*> AdjCountry = user.getCountryByRef().at(i)->getAdjCount();
			bool target = false;

			for (int j = 0; j < AdjCountry.size() && target == false;j++) {

				if (AdjCountry.at(j)->getOwnedBy() != user.getPlayerID()) {

					target = true;
					maxIndex = i;
					maxUnit = user.getCountryByRef().at(i)->getNumberOfTroops();
				}
			}
		}
	}
	Reinforce units;
	user.getCountryByRef().at(maxIndex)->setNumberOfTroops(maxUnit + units.totalUnits(user));
}


void Aggressive::executeAttack(Player& user) {

	//Finds your strongest country

	int maxUnit = 0;
	int maxIndex = 0;

	for (int i = 0; i < user.getCountryByRef().size(); i++) {

		if (user.getCountryByRef().at(i)->getNumberOfTroops() > maxUnit) {

			vector<CountryNode*> AdjCountry = user.getCountryByRef().at(i)->getAdjCount();
			bool target = false;

			for (int j = 0; j < AdjCountry.size() && target == false;j++) {

				if (AdjCountry.at(j)->getCountryId() != NULL && AdjCountry.at(j)->getOwnedBy() != user.getPlayerID()) {

					target = true;
					maxIndex = i;
					maxUnit = user.getCountryByRef().at(i)->getNumberOfTroops();
				}
			}
		}
	}
	CountryNode* attacker = user.getCountryByRef().at(maxIndex);
		
	for (int i = 0; i < attacker->getAdjCount().size() && attacker->getNumberOfTroops() > 1; i++) {
	
		CountryNode* defender = attacker->getAdjCount().at(i);
		
			while (attacker->getNumberOfTroops() > 1 && defender->getOwnedBy() != attacker->getOwnedBy()) {
				
				int attackerDices;
				
				if (attacker->getNumberOfTroops() > 3)
					attackerDices = 3;
				if (attacker->getNumberOfTroops() == 3)
					attackerDices = 2;
				if (attacker->getNumberOfTroops() == 2)
					attackerDices = 1;

				//int defenderDices = Attack::defenderAmountOfDice(defender);

			}
		
	
	}
	

}


void Aggressive::executeFortify(Player& user) {


}