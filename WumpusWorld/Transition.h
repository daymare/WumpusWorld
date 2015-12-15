/*

Contains all userful data structures for representing transitions

*/


#ifndef TRANSITION_H
#define TRANSITION_H

#include "State.h"
#include "Action.h"

class Transition
{
public:
	State initialState;
	Action actionTaken;
	int reward;
	State resultantState;

	Transition();
	Transition(State state, Action action);

	void FinishTransitionInformation(int reward, State state);
	
};


#endif