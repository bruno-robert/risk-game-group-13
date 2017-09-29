//============================================================================
// Name        : Part1Driver.cpp
// Author      : Bruno Robert
// Team        : Group 13
// Team members: Bruno Robert 40003443, Chao Yue 27282516, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 0.3
// Copyright   : GNU Public license 3
// Description : Map Section of the Risk game
//============================================================================

#include "Part1Driver.h"

using namespace std;
//Part1Driver.cpp
int main() {
    
    Map map;
    Map map2;
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
    
    
    //map2 is the same as map but without France, meaning that the countryList is not a connected graph
    map2.addContinent(&europe);
    map2.addContinent(&northAmerica);
    map2.addContinent(&southAmerica);
    map2.addContinent(&asia);
    map2.addCountry(&mongolia);
    map2.addCountry(&uk);
    map2.addCountry(&spain);
    map2.addCountry(&china);

  
    cout << "is the continent map Connected? ";
    map.resetNodes();
    if((map.getContinentList().size()) == (map.checkConnectivity(&europe, 0))) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    
    map.resetNodes();
    cout << "is the country map Connected? ";
    if((map.getCountryList().size()) == (map.checkConnectivity(&france, 0))) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    
    cout << "is the continent map2 Connected? ";
    map.resetNodes();
    if((map2.getContinentList().size()) == (map2.checkConnectivity(&europe, 0))) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    
    map.resetNodes();
    cout << "is the country map2 Connected? ";
    if((map2.getCountryList().size()) == (map2.checkConnectivity(&france, 0))) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    
    cout << "We will now check taht a country can only be in one continent" << endl;
    cout << "We create 2 continents c1 and c2 and two country cc1 and cc2 that are both in c1" << endl;
    ContinentNode c1("c1", 5);
    ContinentNode c2("c2", 5);
    
    CountryNode cc1("cc1", &c1);
    CountryNode cc2("cc2", &c1);
    
    
    cout << "c1 has: "<< c1.getCountryList().size() << " countries" << endl;
    cout << "c1's list of countries: " << c1.getCountryList().at(0)->getCountName() << ", " << c1.getCountryList().at(1)->getCountName() << endl;
    cout << "we now change country cc1 to continent c2" << endl;
    cc1.setContinent(&c2);
    cout << "c1 has: "<< c1.getCountryList().size() << " countries" << endl;
    cout << "c1's list of countries: " << c1.getCountryList().at(0)->getCountName() << endl;
    cout << "c2 has: "<< c2.getCountryList().size() << " countries" << endl;
    cout << "c2's list of countries: " << c2.getCountryList().at(0)->getCountName() << endl;
    cout << "success, the country has been moved!" << endl;
    
	return 0;
}

