//============================================================================
// Name        : Subject.h
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.2
// Copyright   : GNU Public license 3
// Description : Subject class
//============================================================================

#pragma once
#include "Observer.h"
#include <list>
using namespace std;

class Observer;

class Subject {
  public:
        Subject();
	virtual ~Subject();
	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void notify(string message);
	
  private:
	list<Observer*> *observers;
};
