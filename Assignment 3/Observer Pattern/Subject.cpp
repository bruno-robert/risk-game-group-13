//============================================================================
// Name        : Subject.cpp
// Team        : Group 13
// Team members: Bruno Robert 40003443, Jeffrey Maher 40018878, Sabrina Rieck 40032864, Simon Roy 40030996
// Version     : 1.2
// Copyright   : GNU Public license 3
// Description : Subject class
//============================================================================

#include "Subject.h"
#include "Observer.h"

Subject::Subject(){
	observers = new list<Observer*>;
}
Subject::~Subject(){ 
	delete observers;
}
void Subject::attach(Observer* o){
  observers->push_back(o);
};
void Subject::detach(Observer* o){
  observers->remove(o);
};
void Subject::notify(string message){
  list<Observer *>::iterator i = observers->begin();
  for (; i != observers->end(); ++i)
	(*i)->update(message); 
};