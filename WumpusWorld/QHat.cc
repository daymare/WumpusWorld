

#include "QHat.h"

/*

	function: Q Hat (default constructor)
	description: load the utility values from the default save file.
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
QHat::QHat()
{
	FILE* inFile = fopen(DEFAULT_SAVE_FILEPATH, "r");

	LoadQHat(inFile);

	fclose(inFile);
}

/*

function: constructor
description: initializes the utility values to all zeros
and sets the learning rate and gamma to the input values
input: learning rate, gamma

*/
/*

	function: Q Hat (constructor)
	description: starts a new QHat object.
	inputs: learning rate to learn at, gamma value to use
		(discount of future utility)
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
QHat::QHat(double _learningRate, double _gamma)
{
	memset(&utility, 0, sizeof(UtilityValues));

	learningRate = _learningRate;
	gamma = _gamma;
}

/*

	function: constructor
	descritpion: initializes the utility values using the specified
	file
	input: file to load from

*/
/*

	function: constructor (specific file constructor)
	description: loads utility values from the specific file.
	inputs: file to load from
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
QHat::QHat(FILE* loadFile)
{
	LoadQHat(loadFile);
}

/*

	function: Q Hat (default destructor)
	description: saves QHat to a file.
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
QHat::~QHat()
{
	FILE* outFile = fopen(DEFAULT_SAVE_FILEPATH, "w");

	SaveQHat(outFile);

	fclose(outFile);
}

/*

	function: update
	description: updates the state action pair in the utility values
		with the given transition information according to the formula:
		Q^(s, a) <-- alpha sub t -- r + gamma * max (a', Q^(s', a'))
		where max finds the a' that maximizes the value of Q^
		and alpha sub t is the learning rate, which should be any
		function that begins at 1 and becomes zero as we approach infinity.
		see documentation for more details.
	inputs: transition information.
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO write definition.
		TODO test.

*/
void QHat::Update(const Transition transition)
{


	int stateReward;
	
}

/// private get functions

/*

	function: get max
	description: get the maximum utility given that we were in the given state and took the given action.
	inputs: state, action
	outputs: utility value
	preconditions: N/A
	postconditions: N/A
	remarks:
		currently just gets the value from the function in utilityValues with the same name.
		TODO test.

*/
double QHat::GetMax(State state, Action action)
{
	return utility.GetMax(state, action);
}

/*

	function: get max
	description: get the maximum utility given that we are in the input state
	inputs: state
	outputs: maximum utility value
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO write definition.
		TODO test.

*/
double QHat::GetMax(State state)
{
	return utility.GetMax(state);
}

/*

	function: calculate alpha
	description: 
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO write definition.
		TODO test.

*/
double QHat::CalculateAlpha(int T)
{
	double x = T * learningRate;
	double a = 1.0 / x;

	return a;
}

/*

	function: get possible states
	description: gets the possible resulting states given a state action
		pair representing a state and an action the agent took in that
		state.
	inputs: state, action.
	outputs: vector of all possible states resulting from taking the given
		action in the given state.
	preconditions: N/A
	postconditions: N/A
	remarks:
		must deconstruct possible states.
		TODO write definition.
		TODO test.

*/
vector<State> GetPossibleStates(State state, Action action)
{
	vector<State> posStates = *new vector<State>();
	State newState;
	
	int statusIndex = 0;
	int breezeIndex = 0;
	int stenchIndex = 0;
	int glitterIndex = 0;

	switch (action)
	{
	case Action_GoForward:
		if (state.IsFacingWall())
		{
			// return just a copy of the input state
			posStates.push_back(state);
			break;
		}

		// not facing a wall
		// get a copy of the state except one space forward
		newState = state;
		newState.UpdateActionInfo(Action_GoForward);
		posStates.push_back(newState);

		// get all of the possible states
		
		newState.UpdateActionInfo(Action_GoForward);

		for (statusIndex = 0; statusIndex < 2; statusIndex++)
		{
			for (breezeIndex = 0; breezeIndex < 2; breezeIndex++)
			{
				for (stenchIndex = 0; stenchIndex < 2; stenchIndex++)
				{
					for (glitterIndex = 0; glitterIndex < 2; glitterIndex++)
					{
						newState.SetStatus((AgentStatus)statusIndex);
						newState.SetIsBreeze((bool)breezeIndex);
						newState.SetIsStench((bool)stenchIndex);
						newState.SetIsGlitter((bool)glitterIndex);

						posStates.push_back(newState);
					}
				}
			}
		}
		break;

	case Action_TurnLeft:
		newState = state;
		newState.UpdateActionInfo(Action_TurnLeft);
		posStates.push_back(newState);
		break;

	case Action_TurnRight:
		newState = state;
		newState.UpdateActionInfo(Action_TurnRight);
		posStates.push_back(newState);
		break;

	case Action_Grab:
		if (!state.GetIsGlitter())
		{
			posStates.push_back(state);
			break;
		}

		newState = state;

		newState.SetHasGold(true);
		newState.SetIsGlitter(false);

		posStates.push_back(newState);
		break;

	case Action_Shoot:

		newState = state;
		newState.SetHasArrow(false);
		posStates.push_back(newState);

		break;

	case Action_Climb:

		if (state.GetXPos() == 0 && state.GetYPos() == 0)
		{
			posStates.push_back(state);
		}

		newState = state;

		newState.SetStatus(AgentStatus_LeftCave);

		posStates.push_back(newState);
		break;
	}

	return posStates;
}

vector<State> QHat::GetPossibleStates(State state);

void SaveQHat(FILE* outFile);
void LoadQHat(FILE* inFile);

double QHat::GetValue(State state, Action action);
void QHat::SetValue(State state, Action action, int value);
void QHat::AddGame(vector<Transition> transitions);
Action QHat::GetPI(State state);