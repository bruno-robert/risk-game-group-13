

#include "PassiveStrat.h"


Passive::Passive() : PlayerStrategyPattern()
{

}


void Passive::executeReinforce(Player& user) {


	//Getting the number of units for my player
	Reinforce unitsReinforced;
	int units = unitsReinforced.totalUnits(user);

	//Finding the country with the most units and a target to attack

	while (units = !0) {

		int leastUnit = user.getCountryByRef().at(0)->getNumberOfTroops();
		int leastIndex = 0;

		for (int i = 0; i < user.getCountryByRef().size(); i++) {

			if (user.getCountryByRef().at(i)->getNumberOfTroops() < leastUnit) {
				leastIndex = i;
				leastUnit = user.getCountryByRef().at(i)->getNumberOfTroops();
			}
		}
		user.getCountryByRef().at(leastIndex)->setNumberOfTroops(leastUnit + 1);
		units--;
	}
}


void Passive::executeAttack(Player& user) {


}


void Passive::executeFortify(Player& user) {


}