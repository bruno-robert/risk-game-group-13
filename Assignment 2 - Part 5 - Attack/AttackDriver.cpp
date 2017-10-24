
#include <iostream>
#include "Attack.h"

using namespace std;


int main() { 
    
    Map map;
    
    //creating continents
    
    ContinentNode europe("Europe", 5);
    ContinentNode northAmerica("North America", 5);
    ContinentNode southAmerica("south America", 5);
    ContinentNode asia("Asia", 9);
    asia.addAdjCont(&europe);
    europe.addAdjCont(&asia);
    europe.addAdjCont(&northAmerica);
    northAmerica.addAdjCont(&europe);
    northAmerica.addAdjCont(&southAmerica);
    southAmerica.addAdjCont(&northAmerica);
    
    //creating countries
    
    CountryNode mongolia("Mongolia", &europe);
    CountryNode france("France", &europe);
    CountryNode uk("U.K.", &europe);
    CountryNode spain("Spain", &europe);
    CountryNode china ("China", &asia);
    
    china.addAdjCount(&mongolia);
    mongolia.addAdjCount(&china);
    mongolia.addAdjCount(&france);
    france.addAdjCount(&mongolia);
    france.addAdjCount(&uk);
    france.addAdjCount(&spain);
    uk.addAdjCount(&france);
    spain.addAdjCount(&france);
    
    //adding nodes to map
    map.addContinent(&europe);
    map.addContinent(&northAmerica);
    map.addContinent(&southAmerica);
    map.addContinent(&asia);
    map.addCountry(&mongolia);
    map.addCountry(&france);
    map.addCountry(&uk);
    map.addCountry(&spain);
    map.addCountry(&china);
    
    //Assigning countries to player 1
    vector<CountryNode *> player1Countries;
    player1Countries.push_back(&mongolia);
    player1Countries.push_back(&china);
    player1Countries.push_back(&france);
    
    //Assigning countries to player 2
    vector<CountryNode *> player2Countries;
    player2Countries.push_back(&uk);
    player2Countries.push_back(&spain);
    
    //Assigning army personnel to countries
    china.setNumberOfTroups(1);
    mongolia.setNumberOfTroups(5);
    france.setNumberOfTroups(2);
    spain.setNumberOfTroups(4);
    uk.setNumberOfTroups(10);
    
    //Creating dice for players
    Dice dice1, dice2;
    
    //Creating hand of cards for players
    Hand hand1, hand2;
    
    //Creating players
    Player player1 = Player (player1Countries, hand1, dice1);
    Player player2 = Player (player2Countries, hand2, dice2);
    
    //Adding players to list
    vector<Player> playerList;
    playerList.push_back(player1);
    playerList.push_back(player2);
    
    //Creating and attack object
    Attack game;
    
    
    //TESTING PHASE
    //Declarations
    cout << "Player one owns:" << endl;
    cout << "Mongolia which has "<< mongolia.getNumberOfTroups() << " armies" <<endl;
    cout << "China which has "<< china.getNumberOfTroups() << " armies" <<endl;
    cout << "France which has "<< france.getNumberOfTroups() << " armies\n" <<endl;
    
    cout << "Player two owns:" << endl;
    cout << "Spain which has "<< spain.getNumberOfTroups() << " armies" <<endl;
    cout << "U.K. which has "<< uk.getNumberOfTroups() << " armies\n" <<endl;
    
    cout << "\n -------------- \n" << endl;
    
    //Verify that country belongs to player
    cout << "Does player 1 own Mongolia?" << endl;
    bool question1 = game.verifyBelonging(player1, "Mongolia");
    cout << question1 << endl;
    
    cout << "Does player 1 own Canada?" << endl;
    bool question2 = game.verifyBelonging(player1, "Canada");
    cout << question2 <<endl;
    
    cout << "\n -------------- \n" << endl;
    
    //Testing AttackFrom
    cout << "Testing the that only valid attacks can be declared. Player1 is attacking." << endl;
    string question3 = game.attackFrom(player1, map);
    cout << "Attack from " << question3 << endl;
    
    cout << "\n -------------- \n" << endl;
    
    //Testing AttackTo
    CountryNode* countryQuestion4;
    countryQuestion4 = &spain;
    cout << "Testing the that only valid countries to attack can be declared" << endl;
    cout << "Note: Here we are attacking from Spain, which has France as a neighbour." << endl;
    string question4 = game.toAttack(playerList, player2, map, &spain);
    cout << "Attack " << question4 << endl; 
    
    cout << "\n -------------- \n" << endl;
    
    //Testing amount of dice when attacking from spain
    cout << "Testing how many dice can be requested when attacking from Spain" << endl;
    cout << "Note: Spain has " << spain.getNumberOfTroups() << " troops on the country." << endl;
    int question5 = game.attackerAmountOfDice(countryQuestion4);
    cout << "Roll " << question5 << " dice" << endl;
    
    cout << "\n -------------- \n" << endl;
    
    //Testing amount of dice when defending from spain
    cout << "Testing how many dice can be requested when defending Spain" << endl;
    cout << "Note: Spain has " << spain.getNumberOfTroups() << " troops on the country." << endl;
    int question6 = game.defenderAmountOfDice(countryQuestion4);
     cout << "Roll " << question6 << " dice" << endl;
    
    cout << "\n -------------- \n" << endl;
    
    //Testing attack loop
    game.attackLoop(playerList, player1, map);
    
    //Checking country updates
    vector<CountryNode *> player1CountriesAfterGame = player1.getCountry();
    vector<CountryNode *> player2CountriesAfterGame = player2.getCountry();
    
    cout << "\n -------------- \n" << endl;
    cout << "After running the attack loop:" << endl;
    
    cout << "Player one owns:" << endl;
    for(CountryNode* c : player1CountriesAfterGame)
        cout << c->getCountName() <<" which has "<< c->getNumberOfTroups() << " armies" <<endl;
    
    cout << "\nPlayer two owns:" << endl;
    for(CountryNode* c : player2CountriesAfterGame)
        cout << c->getCountName() <<" which has "<< c->getNumberOfTroups() << " armies" <<endl;
    
        
    return 0;
}