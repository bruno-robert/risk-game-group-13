//============================================================================
// Name        : Attack.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, C Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.2
// Copyright   : GNU Public license 3
// Description : Attack class is responsible for players choosing from which country to attack from, choosing, which country to attack,
//               choosing how many dice to roll, comparing the rolled dice, and adding/removing troops as necessary 
//============================================================================

#include "Attack.h"

Attack::Attack(){
	attackingCountryData = NULL;
	defendingCountryData = NULL;
	attackingPlayerData = NULL;
	defendingPlayerData = NULL;
	mapData = NULL;
}

Attack::~Attack(){

}

bool Attack::yesNoQuestion(string question)
{
	while (true)
	{
		cout << question << "y/n" << endl;

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

void Attack::attackLoop(vector<Player*> playerList, Player* attacker, Map* map){

	setPlayerListData(playerList);
	setAttackingPlayerData(attacker);
	setMapData(map);

	notify("Attack Started");

	bool wantsToAttack = yesNoQuestion("Do you wish to attack?");

	while (wantsToAttack){
		bool continueAttack = true;

		//Get country to attack from
		string attackingCountry = attackFrom(attacker, map);
		CountryNode* attackFrom = map->getCountryByName(attackingCountry);
		setAttackingCountryData(attackFrom);

		//Get country to attack
		string defendingCountry = toAttack(playerList, attacker, map, attackFrom);
		CountryNode* attackTo = map->getCountryByName(defendingCountry);
		setDefendingCountryData(attackTo);

		notify("Attack to/from set");

		Player* defender = getAssociatedPlayer(playerList, defendingCountry);
		setDefendingPlayerData(defender);

		while (continueAttack){
			//Get attacker's dice amount
			int attackerDiceAmount = attackerAmountOfDice(attackFrom);

			//Get defender's dice amount
			int defenderDiceAmount = defenderAmountOfDice(attackTo);

			//players role dice
			int attackerDiceResults[3];
			int defenderDiceResults[3];
			attacker->getDice().roll(attackerDiceResults, attackerDiceAmount);
			defender->getDice().roll(defenderDiceResults, defenderDiceAmount);

			//Print dice results
			cout << "Attacker rolled" << endl;
			printDiceResults(attackerDiceResults, attackerDiceAmount);

			cout << "Defender rolled" << endl;
			printDiceResults(defenderDiceResults, defenderDiceAmount);

			//Compare dice
			//Determine who rolled the least amount of dice
			int mostRolled = defenderDiceAmount;   //assume defender rolled the least amount of dice
			if (mostRolled > attackerDiceAmount)     //Verify and change min if necessary
				mostRolled = attackerDiceAmount;

			//Reverse sort the arrays
			reverseSortDiceResults(attackerDiceResults);
			reverseSortDiceResults(defenderDiceResults);

			//Compare pairwise
			int attackerLoses = 0;
			int defenderLoses = 0;

			for (int i = 0; i<mostRolled; i++){
				if (attackerDiceResults[i]>defenderDiceResults[i])
					defenderLoses++;
				else
					attackerLoses++;
			}

			//Output results of comparing dice
			setAttackerTroopLoss(attackerLoses);
			setDefenderTroopLoss(defenderLoses);
			notify("Troop Loss");
			cout << "Attacker loses " << attackerLoses << " army personnel" << endl;
			cout << "Defender loses " << defenderLoses << " army personnel" << endl;

			//Remove appropriate amount of troops from countries according to results of the attack
			attackFrom->setNumberOfTroops(attackFrom->getNumberOfTroops() - attackerLoses);
			attackTo->setNumberOfTroops(attackTo->getNumberOfTroops() - defenderLoses);

			if (attackFrom->getNumberOfTroops() == 1){
				cout << "Attacker has only one troop left on attacking country" << endl;
				cout << "You cannot continue this attack" << endl;
				continueAttack = false;
				notify("Attack ended");
			}
			else if (attackTo->getNumberOfTroops() < 1){
				cout << "Defender has no more troops left" << endl;
				cout << "Country has been conquered by attacker!" << endl;
				conqueredCountry(attackFrom, attackTo, attacker, defender);
				continueAttack = false;
				notify("Attacker conquered");
			}
			else
			{
				continueAttack = yesNoQuestion("Do you wish to continue this attack?");
				if (!continueAttack) notify("Attack ended");
			}
		}

		wantsToAttack = yesNoQuestion("Do you wish to launch another attack?");
	}
}

string Attack::attackFrom(Player* attacker, Map* map){
	bool done = false;
	string answer;

	while (!done)
	{
		//Ask player where he wants to attack from
		cout << "What country do you want to launch your attack from?\nNote: Spaces should be an underscore." << endl;
		cin >> answer;
		replace(answer.begin(), answer.end(), '_', ' ');
		//Verify that request country belongs to player
		bool belongs = verifyBelonging(attacker, answer);

		if (!belongs){
			cout << "The country " << answer << " doesn't belong to you" << endl;
			cout << "Please input a valid country." << endl;
		}

		//Verify that request country has more than 1 army personnel on it
		else {
			//Get CountryNode from answer
			CountryNode* attackTo = map->getCountryByName(answer);

			//Verify that request country has more than 1 army personnel on it
			int amountOfArmies = attackTo->getNumberOfTroops();

			if (amountOfArmies < 2){
				cout << answer << " doesn't have enough army personnel to launch an attack" << endl;
				cout << "Please input a country that has 2 or more army personnel on it." << endl;
			}

			//If the country belongs to the attacker and there is more than 1 army personnel on the country, then input country is valid
			else
				done = true;
		}
	}
	return answer;
}

string Attack::toAttack(vector<Player*> playerList, Player* attacker, Map* map, CountryNode* attackingCountry){

	string answer;

	bool validCountry = false;

	do{
		//Ask player where he wants to attack from
		cout << "Which country do you want to attack?\nNote: Spaces should be an underscore." << endl;
		cin >> answer;
		replace(answer.begin(), answer.end(), '_', ' ');
		//Verify that the input country is a valid country
		for (Player* p : playerList){
			bool check = verifyBelonging(p, answer);
			if (check == true)
				validCountry = true;
		}

		//If input isn't a valid country
		if (!validCountry){
			cout << answer << " isn't a valid country." << endl;
			validCountry = false;
			continue;   // restart loop
		}

		//Verify that request country doesn't belong to calling player
		bool belongs = verifyBelonging(attacker, answer);

		if (belongs){ //If input country belongs to attacker
			cout << "The country " << answer << " belongs to you" << endl;
			cout << "Please input a valid country that doesn't belong to you." << endl;
			validCountry = false;
			continue;   // restart loop
		}

		//Get CountryNode from answer
		CountryNode* defendingCountry = map->getCountryByName(answer);

		//Verify that country is a neighbour of the country being attacked from
		bool neighbours = attackingCountry->isCountAdjacent(defendingCountry->getCountryId());

		//If they aren't neighbours
		if (!neighbours){
			cout << answer << " isn't a neighbouring country of " << attackingCountry->getCountName() << "." << endl;
			validCountry = false;
			continue;
		}

	} while (!validCountry);

	return answer;
}

bool Attack::verifyBelonging(Player* caller, string country)
{
	bool belongs = false;
	
	vector<CountryNode *> ownedCountries = caller->getCountry();
	
	for (CountryNode* c : ownedCountries)
		if (c->getCountName() == country)
			belongs = true;

	return belongs;
}

int Attack::attackerAmountOfDice(CountryNode* country){
	//Get amount of armies on the country
	int armyAmount = country->getNumberOfTroops();

	//Set possible answers
	string possibilities;

	switch (armyAmount){
	case 2: possibilities = " 1"; break;
	case 3: possibilities = " 1 or 2"; break;
	default: possibilities = " 1, 2 or 3"; break;   //3 or more armies on country
	}

	int answer;
	string answerString = " ";

	bool done = false;
	do{
		//Ask question
		cout << "Attacker, how many dice to you want to roll?" << possibilities << endl;
		cin >> answerString;

		done = true;    //assume input is correct

		//Verify if input is int
		stringstream convert(answerString);

		if (!(convert >> answer)){
			cout << "Please input an integer." << endl;
			done = false;
			continue;
		}

		//Verify answer
		if (armyAmount == 2){
			if (answer != 1){
				cout << "You may role only one die" << endl;
				done = false;
			}
		}

		else if (armyAmount == 3){
			if (!(answer == 1 || answer == 2)){
				cout << "Please enter either 1 or 2." << endl;
				done = false;
			}
		}

		else if (armyAmount > 3){
			if (answer < 1 || answer>3){
				cout << "Please enter either 1, 2 or 3." << endl;
				done = false;
			}
		}

	} while (!done);

	return answer;
}

int Attack::defenderAmountOfDice(CountryNode* country){
	//Get amount of armies on the country
	int armyAmount = country->getNumberOfTroops();

	//Set possible answers
	string possibilities;

	switch (armyAmount){
	case 1: possibilities = " 1"; break;
	default: possibilities = " 1 or 2"; break;   //2 or more armies on country
	}

	int answer = 0;
	string answerString = " ";

	bool done = false;
	do{
		//Ask question
		cout << "Defender, how many dice to you want to roll?" << possibilities << endl;
		cin >> answerString;

		done = true;    //assume input is correct

		//Verify if input is int
		stringstream convert(answerString);

		if (!(convert >> answer)){
			cout << "Please input an integer." << endl;
			done = false;
			continue;
		}

		//Verify answer
		if (armyAmount == 1){
			if (answer != 1){
				cout << "You may role only one die" << endl;
				done = false;
			}
		}

		else if (armyAmount >= 2){
			if (!(answer == 1 || answer == 2)){
				cout << "Please enter either 1 or 2." << endl;
				done = false;
			}
		}

	} while (!done);

	return answer;
}

void Attack::compareDice(int attackerDice[], int defenderDice[], int attackerDiceAmount, int defenderDiceAmount){
	//Determine who rolled the least amount of dice
	int index = defenderDiceAmount;   //assume defender rolled the least amount of dice
	if (index > attackerDiceAmount)     //Verify and change min if necessary
		index = attackerDiceAmount;

	//Reverse sort the arrays
	reverseSortDiceResults(attackerDice);
	reverseSortDiceResults(defenderDice);

	//Compare pairwise
	int attackerLoses = 0;
	int defenderLoses = 0;

	for (int i = 0; i<index; i++){
		if (attackerDice[i]>defenderDice[i])
			defenderLoses++;
		else
			attackerLoses++;
	}

	cout << "Attacker loses " << attackerLoses << " army personnel" << endl;
	cout << "Defender loses " << defenderLoses << " army personnel" << endl;
}

void Attack::printDiceResults(int results[], int amountOfDice){
	int i;
	for (i = 0; i < amountOfDice; i++)
		if (results[i] != 0)
			cout << "Dice " << i + 1 << ": " << results[i] << endl;
}

void Attack::reverseSortDiceResults(int diceResults[]){ //Size of input array is always 3

	int max = 0;
	for (int i = 1; i<3; i++)
		if (diceResults[i]>diceResults[max])
			max = i;

	int min = 2;
	for (int i = 0; i < 2; i++)
		if (diceResults[i] < diceResults[min])
			min = i;

	int mid = -1;
	if (!(max == 0 || min == 0))
		mid = 0;
	if (!(max == 1 || min == 1))
		mid = 1;
	if (!(max == 2 || min == 2))
		mid = 2;

	int temp1 = diceResults[max];
	int temp2 = diceResults[mid];
	int temp3 = diceResults[min];

	diceResults[0] = temp1;
	diceResults[1] = temp2;
	diceResults[2] = temp3;
}

void Attack::conqueredCountry(CountryNode* attackingCountry, CountryNode* defendingCountry, Player* attacker, Player* defender){

	//get amount of troops left on attacking country
	int amountOfTroops = attackingCountry->getNumberOfTroops();
	int max = amountOfTroops - 1;
	int answer;
	string answerString = " ";

	bool done = false;
	do{
		//ask question (how many troops to move?)
		cout << "How many troops do you want to move from " << attackingCountry->getCountName() << " to " << defendingCountry->getCountName() << "?" << endl;
		cout << "You can move a maximum of " << max << " troops" << endl;
		cin >> answerString;

		done = true;    //assume input is correct

		//Verify if input is int
		stringstream convert(answerString);

		if (!(convert >> answer)){
			cout << "Please input an integer." << endl;
			done = false;
			continue;
		}

		if (answer > max){ //too large a number was entered
			cout << "You don't have enough troops. Please input an amount equal or lower than " << max << "." << endl;
			done = false;
			continue;
		}

		if (answer <= 0){  //0 was entered
			cout << "You must move at least one soldier" << endl;
			done = false;
			continue;
		}
	} while (!done);

	//remove troops from attacking country
	attackingCountry->setNumberOfTroops(amountOfTroops - answer);

	//Add troops to conquered country
	defendingCountry->setNumberOfTroops(answer);

	//Change country ownership
	//Remove country from defender's ownership
	vector<CountryNode *> defendersCountries = defender->getCountry();
	defendersCountries.erase(remove(defendersCountries.begin(), defendersCountries.end(), defendingCountry), defendersCountries.end());
	defender->setCountry(defendersCountries);

	//Add country to attacker's ownership
	vector<CountryNode *> attackersCountries = attacker->getCountry();
	attackersCountries.push_back(defendingCountry);
	attacker->setCountry(attackersCountries);

	notify("Map Change"); //message to observer(s)
}

Player* Attack::getAssociatedPlayer(vector<Player*> playerList, string country){

	for (Player* p : playerList)
		if (verifyBelonging(p, country))
			return p;

	return NULL;
}

//Notify calls used in the strategies

void Attack::attackNotify(CountryNode* attacker, CountryNode* defender, int attackerLoses, int defenderLoses) {

	string troopsLost = "PHASE_OBSERVER|" + attacker->getCountName() + " lost " + to_string(attackerLoses) + " units and " + defender->getCountName() + " lost " + to_string(defenderLoses) + " units.\n";
	notify(troopsLost);
}

void Attack::attackNotifyConquering(CountryNode* attacker, CountryNode* defender, int unitsMoved) {

	string troopsLost = "PHASE_OBSERVER| Player " + to_string(attacker->getCountryId()) + " conquered " + defender->getCountName() + 
						" and moved " + to_string(unitsMoved) + " units  from " + attacker->getCountName() + ".\n";
	notify(troopsLost);
}

void Attack::attackNotifyStart(Player& user) {

	string starting = "PHASE_OBSERVER| Beginning the attack phase for player " + to_string(user.getPlayerID()) + "...";
	notify(starting);
}


//SETTERS and GETTERS
void Attack::setPlayerListData(vector<Player*> playerListData){
	this->playerListData = playerListData;
}

void Attack::setAttackingCountryData(CountryNode* attackingCountryData){
	this->attackingCountryData = attackingCountryData;
}

void Attack::setDefendingCountryData(CountryNode* defendingCountryData){
	this->defendingCountryData = defendingCountryData;
}

void Attack::setAttackingPlayerData(Player* attackingPlayer){
	this->attackingPlayerData = attackingPlayer;
}

void Attack::setDefendingPlayerData(Player* defendingPlayerData){
	this->defendingPlayerData = defendingPlayerData;
}
void Attack::setMapData(Map* map){
	this->mapData = map;
}

vector<Player*> Attack::getPlayerListData(){
	return this->playerListData;
}

CountryNode* Attack::getAttackingCountryData(){
	return this->attackingCountryData;
}

CountryNode* Attack::getDefendingCountryData(){
	return this->defendingCountryData;
}

Player* Attack::getAttackingPlayerData(){
	return this->attackingPlayerData;
}

Player* Attack::getDefendingPlayerData(){
	return this->defendingPlayerData;
}

Map* Attack::getMapData(){
	return this->mapData;
}

void Attack::setAttackerTroopLoss(int amountLost){
	attackerTroopLoss = amountLost;
}
int Attack::getAttackerTroopLoss(){
	return attackerTroopLoss;
}
void Attack::setDefenderTroopLoss(int amountLost){
	defenderTroopLoss = amountLost;
}
int Attack::getDefenderTroopLoss(){
	return defenderTroopLoss;
}
