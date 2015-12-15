/*
	
	file: UtilityValues.cc
	programmer: Daylan Kelting
	description: Class implementing the ridiculous array containing all of our utility values.

*/

#include "UtilityValues.h"

/*

	function: utility coordinate (default constructor)
	description: constructs the coordinate to default values
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
UtilityCoordinate::UtilityCoordinate()
{
	state = *new State();
	action = Action_GoForward;
}

/*

	function: utility coordinates (constructor)
	description: sets the state and action to the input state and action
	inputs: state, action
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
UtilityCoordinate::UtilityCoordinate(State state, Action action)
{
	this->state = state;
	this->action = action;
}

/*

	function: get utility value
	description: gets the utility value at the particular coordinate
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
double UtilityValues::GetUtilityValue(UtilityCoordinate coordinate)
{
	int x = coordinate.state.GetXPos();
	int y = coordinate.state.GetYPos();
	Direction dir = coordinate.state.GetDirection();
	AgentStatus status = coordinate.state.GetStatus();
	bool arrow = coordinate.state.GetHasArrow();
	bool gold = coordinate.state.GetHasGold();
	bool stench = coordinate.state.GetIsStench();
	bool breeze = coordinate.state.GetIsBreeze();
	bool glitter = coordinate.state.GetIsGlitter();
	bool scream = coordinate.state.GetHasScreamed();
	Action action = coordinate.action;
	bool history11 = coordinate.state.GetHistory(1, 1);
	bool history12 = coordinate.state.GetHistory(1, 2);
	bool history21 = coordinate.state.GetHistory(2, 1);
	bool history22 = coordinate.state.GetHistory(2, 2);

	return utilityValues[x][y][dir][status][arrow][gold][stench][breeze][glitter][scream][action][history11][history12][history21][history22];
}

/*

	function: set utility value
	description: set the utility value in the utility coordinate to the input value
	inputs: coordinate of index to set the value, value to set
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO write definition.
		TODO test.

*/
void UtilityValues::SetUtilityValue(UtilityCoordinate coordinate, double value)
{
	int x = coordinate.state.GetXPos();
	int y = coordinate.state.GetYPos();
	Direction dir = coordinate.state.GetDirection();
	AgentStatus status = coordinate.state.GetStatus();
	bool arrow = coordinate.state.GetHasArrow();
	bool gold = coordinate.state.GetHasGold();
	bool stench = coordinate.state.GetIsStench();
	bool breeze = coordinate.state.GetIsBreeze();
	bool glitter = coordinate.state.GetIsGlitter();
	bool scream = coordinate.state.GetHasScreamed();
	Action action = coordinate.action;
	bool history11 = coordinate.state.GetHistory(1, 1);
	bool history12 = coordinate.state.GetHistory(1, 2);
	bool history21 = coordinate.state.GetHistory(2, 1);
	bool history22 = coordinate.state.GetHistory(2, 2);

	utilityValues[x][y][dir][status][arrow][gold][stench][breeze][glitter][scream][action][history11][history12][history21][history22] = value;
}
