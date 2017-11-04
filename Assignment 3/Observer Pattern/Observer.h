//============================================================================
// Name        : Observer.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.2
// Copyright   : GNU Public license 3
// Description : Virtual observer class
//============================================================================
#pragma once
#include <string>
using namespace std;

class Observer {
public:
	~Observer();
	virtual void update(string str) = 0;
protected:
	Observer();
};
