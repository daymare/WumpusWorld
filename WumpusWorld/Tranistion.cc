

#include "Transition.h"


Transition::Transition()
{
	initialState = *new State();
	actionTaken = Action_TurnLeft;
	reward = 0;
	resultantState = *new State();
}

Transition::Transition(State state, Action action)
{
	initialState = state;
	actionTaken = action;
	reward = 0;
	resultantState = *new State();
}


void Transition::CompleteTransitionInformation(int _reward, State state)
{
	reward = _reward;
	resultantState = state;
}