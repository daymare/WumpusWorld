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

/*

	function: get max
	description: gets the maximum utility value of the next state given the action that was taken in the previous state.
	inputs: state, action taken in that state.
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
double UtilityValues::GetMax(State state, Action action)
{
	// get the possible states
	vector<State> possStates = state.GetPossibleStates(action);

	// find the maximum utility value of the possible states.
	UtilityCoordinate coordinate;
	coordinate.state = possStates.at(0);
	coordinate.action = Action_GoForward;

	double max = GetUtilityValue(coordinate);
	double current = 0.0;

	// index through all possible states
	for (int stateIndex = 0; stateIndex < possStates.size(); stateIndex++)
	{
		coordinate.state = possStates.at(stateIndex);
		
		// and all possible actions for those states
		for (int actionIndex = 0; actionIndex < NUM_ACTIONS; actionIndex++)
		{
			coordinate.action = (Action)actionIndex;
			current = GetUtilityValue(coordinate);

			if (current > max)
			{
				max = current;
			}
		}
	}

	return max;
}

/*

	function: get max
	description: gets the maximum utility value of the given state.
	inputs: state
	outputs: maximum utility value of the given state.
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
double UtilityValues::GetMax(State state)
{
	double max = GetMax(state, Action_GoForward);
	double current = 0.0;

	for (int actionIndex = 1; actionIndex < NUM_ACTIONS; actionIndex++)
	{
		current = GetMax(state, (Action)actionIndex);

		if (current > max)
		{
			max = current;
		}
	}

	return max;
}
