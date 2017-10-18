//
//  fortificationPhaseDriver.cpp
//  Assignment 2 - part 6 - main game loop: fortification phase
//
//  Created by Bruno Robert on 17/10/2017.
//  Copyright © 2017 Bruno Robert. All rights reserved.
//

#include "fortificationPhaseDriver.hpp"
using namespace std;

int main() {
    FortificationPhase fp;
    Map map;
    
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
    
    mongolia.setOwnedBy(1);
    france.setOwnedBy(1);
    uk.setOwnedBy(1);
    spain.setOwnedBy(1);
    china.setOwnedBy(1);
    
    mongolia.setNumberOfTroups(10);
    france.setNumberOfTroups(10);
    uk.setNumberOfTroups(10);
    spain.setNumberOfTroups(10);
    china.setNumberOfTroups(10);
    
    fp.fortify(1, map);
    return 0;
}
