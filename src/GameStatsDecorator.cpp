
#include "GameStatsObserver.h"
#include "Cards.h"
#include "Map.h"
#include <vector>
#include <iostream>
using namespace std;

/* DELETE IF UNUSED
 cout::setf(ios::fixed);
 cout::setf(ios::showpoint);
 cout.precision(2);
 */

//#include "GameStatsDecorator.h" //COMMENT BACK IN


class GameStatsDecorator : public GameStatsObserver{ //for .h file
    
protected:
    GameStatsObserver *decoratedGameStats;
    
public:
    
    GameStatsDecorator(GameStatsObserver *decoratedGameStats){
        this->decoratedGameStats = decoratedGameStats;
    }
    
    void update(string message){
        return decoratedGameStats->update(message);
    }
    
};//End class To delete

class DominationObserver : public GameStatsDecorator{
    
    DominationObserver(GameStatsObserver *decoratedGameStats) : GameStatsDecorator(decoratedGameStats){
        //Empty body
    }
    
    void update(string message){
        return GameStatsDecorator::update(message); // + printDominationStats();
    }
    
    void printDominationStats(){
        
        //Get total amount of countries
        int total = 0;
        vector<CountryNode*> countries = map->getCountryList();
        for (CountryNode* c : countries)
        {
            total++;
        }
        
        cout << "------------Map Ownership: ";
        
        //Get an calculate individual ownership
        for (Player* p : subjectPlayers)
        {
            int playerID = p->getPlayerID();
            
            int amount = map->getNumberOfcountriesOwnedById(playerID);
            
            double percentage = (amount/(double)total) * 100.0;
            
            cout << "Player " << playerID << ": " << percentage << "%   ";  //<< setprecision(2)
        }
        
        cout << "\n";
    }
};

class HandObserver : public GameStatsDecorator{
    
    HandObserver(GameStatsObserver *decoratedGameStats) : GameStatsDecorator(decoratedGameStats){
        //Empty Body
    }
    
    void update(string message){
        return GameStatsDecorator::update(message); // + printHandInfo();
    }
    
    void printHandInfo(){
        
        cout << "------------Hand information: ";
        
        for(Player* p: subjectPlayers){
            
            int playerID = p->getPlayerID();
            
            //Get players hand an it's size
            Hand hand = p->getHandByRef();
            vector<Card> playerHand = hand.getPlayerHand();
     
            int infantry = 0, cavalry = 0, artillery = 0;
            
            //Get amount of cards of each type in hand
            for (Card c: playerHand) {	
                switch (c.getType()) {
                    case 1:infantry++;
                    break;
                    case 2:cavalry++;
                    break;
                    case 3:artillery++;
                    break;
                }
            }
            
            //printing the statement for each player
            cout << "Player " << playerID << ": " << infantry << " infantry, " << cavalry << " cavalry, " << artillery << " artillery" <<endl;
        }
        
    }
    
};

class ControlObserver : public GameStatsDecorator{
    
    ControlObserver(GameStatsObserver *decoratedGameStats) : GameStatsDecorator(decoratedGameStats){
        //Empty Body
    }
    
    void update(string message){
        return GameStatsDecorator::update(message); // + printContinentControlInfo();
    }
    
    void printContinentControlInfo(){
        
        cout << "------------Continent control: ";
        
        
        for(Player* player: subjectPlayers){
            vector<int> pastIndex;
            string owns = "";
            
            for (int i = 0; i < player->getCountry().size();i++) {
		if (std::find(pastIndex.begin(), pastIndex.end(), i) != pastIndex.end()) {
                    continue;
		}
		ContinentNode* currentContinent = player->getCountry().at(i)->getContinent();
		bool isEqual = true;
		for (int j = 0; j < currentContinent->getCountryList().size() && isEqual; j++) {
                    isEqual = false;
                    int k = 0;
                    while (!isEqual && k < player->getCountry().size()) {
                        if (std::find(pastIndex.begin(), pastIndex.end(), i) != pastIndex.end()) {
                            k++;
                            continue;
                        }
                        if (currentContinent->getCountryList().at(j) == player->getCountry().at(k)) {
                            isEqual = true;
                            pastIndex.push_back(k);
                        }
                        k++;
                    }
                    if (isEqual && j == currentContinent->getCountryList().size() - 1)
                        if(owns == "")
                            owns += currentContinent->getContName();
                        else
                            owns += ", " + currentContinent->getContName();
		}
            }
            
            if(owns == "")
                owns = "none";
            
            int playerID = player->getPlayerID(); 
            
            //printing the statement for each player
            cout << "Player " << playerID << ": " << owns << endl;
            
        }//end subjectPlayers iteration loop
        
    }
    
};


