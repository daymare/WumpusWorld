

#include "QHat.h"

using namespace std;

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
	// load from the default save file
	ifstream inFile;
	inFile.open(DEFAULT_SAVE_FILEPATH);
	LoadQHat(&inFile);
	inFile.close();

	InitRandom();
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
	// create a new qhat
	// set all values to something large and negative so the agent has
	// incentive to try new actions
	utility.SetAllUtilityValues(-1.0);
	learningRate = _learningRate;
	gamma = _gamma;

	InitRandom();
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
QHat::QHat(ifstream loadFile)
{
	LoadQHat(&loadFile);

	InitRandom();
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
	ofstream outFile;
	outFile.open(DEFAULT_SAVE_FILEPATH);
	SaveQHat(&outFile);
	outFile.close();
}

void QHat::InitRandom()
{
	srand((unsigned int)time(NULL));
}

/*

	function: update
	description: updates the state action pair in the utility values
		with the given transition information according to the formula:
		Q^(s, a) <-- alpha sub t -- r + gamma * max (a', Q^(s', a'))
		Q^ = (1-alpha sub t)(Q^(s, a)) + (alpha sub t)(r + gamma * max (a', Q^(s', a')))
		where max finds the a' that maximizes the value of Q^
		and alpha sub t is the learning rate, which should be any
		function that begins at 1 and becomes zero as we approach infinity.
		see documentation for more details.
	inputs: transition information.
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
void QHat::Update(const Transition transition)
{
	double currentValue; // (Q^(s, a)
	double currentMultiplier; // (1-alpha sub t)
	double newInfoMultiplier; // (alpha sub t)
	double newInfoValue; // (r + gamma * max (a', Q^(s', a')))

	int stateReward;
	double max;

	State transitionState = transition.initialState;
	Action transitionAction = transition.actionTaken;

	double updatedValue = 0.0;

	// calculate all the things
	stateReward = transition.reward;
	max = GetMax(transitionState, transitionAction);

	currentValue = GetValue(transitionState, transitionAction);
	newInfoMultiplier = CalculateAlpha((int)tValue);
	currentMultiplier = 1.0 - newInfoMultiplier;
	newInfoValue = stateReward + (gamma * max);

	updatedValue = currentValue * currentMultiplier + newInfoValue * newInfoMultiplier;

	SetValue(transitionState, transitionAction, updatedValue);
}


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
		TODO test.

*/
double QHat::CalculateAlpha(int T)
{
	double x = T * learningRate;
	double a = 1.0 / (1.0 + x);

	return a;
}

/*

	function: save qhat
	description: saves the current values of the utility function
		and qhat variables to the given file
	inputs: file to write to
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO write definition.
		TODO test.

*/
void QHat::SaveQHat(ofstream *outFile)
{
	*outFile << to_string(learningRate) + "\n";
	*outFile << to_string(gamma) + "\n";
	*outFile << to_string(tValue) + "\n";

	utility.SaveUtilityValues(outFile);
}

/*

	function: load qhat
	description: loads qhat from a file.
	inputs: file to load from.
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO write definition.
		TODO test.

*/
void QHat::LoadQHat(ifstream *inFile)
{
	*inFile >> learningRate;
	*inFile >> gamma;
	*inFile >> tValue;

	utility.LoadUtilityValues(inFile);
}

double QHat::GetValue(State state, Action action)
{
	UtilityCoordinate coordinate;
	coordinate.action = action;
	coordinate.state = state;

	// check for infinite actions of nothing
	if (coordinate.state.IsFacingWall() && coordinate.action == Action_GoForward)
	{
		return -999999;
	}
	else
	{
		return utility.GetUtilityValue(coordinate);
	}
}

void QHat::SetValue(State state, Action action, double value)
{
	UtilityCoordinate coordinate;
	coordinate.action = action;
	coordinate.state = state;

	utility.SetUtilityValue(coordinate, value);
}

/*

	function: add game
	description: adds a games information too the qhat function and increments t.
	inputs: list of transitions that describe the game.
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
void QHat::AddGame(vector<Transition> transitions)
{
	for (int i = ((int)transitions.size())-1; i >= 0 ; i--)
	{
		Update (transitions.at(i));
	}
	IncrementT();
}

/*

	function: increment t
	description: increments the t value. Indicating that another game has been added to qhat.
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
void QHat::IncrementT()
{
	tValue++;
}

/*

	function: get pi
	description: returns the best action according to our qhat function given the state we are in.
		takes a random action with probability epsilon.
	inputs: state the agent is in, probability that this function returns a random action.
	outputs: Action to take. (Or a random action)
	preconditions: N/A
	postconditions: N/A
	remarks:
		We want to take random actions every once and a while to ensure that we visit every state
		in the state space. There could always be a better way to do things.
		TODO test.

*/
Action QHat::GetPI(const State state, double epsilon)
{
	// find if we are taking a random action
	double randNum = rand() % 1000;
	randNum /= 1000;

	if (randNum <= epsilon)
	{
		// return a random action
		return (Action)(rand() % 6);
	}
	else
	{
		// otherwise find the best action and return it
		double maxValue = GetMax(state, Action_GoForward);
		Action maxAction = Action_GoForward;

		for (int i = 1; i < NUM_ACTIONS; i++)
		{
			Action currentAction = (Action)i;
			double currentValue = GetMax(state, currentAction);

			if (currentValue > maxValue)
			{
				maxValue = currentValue;
				maxAction = currentAction;
			}
		}

		return maxAction;
	}
}

/*

	function: get pi
	description: returns the best action according to our qhat function given the state we are in.
		takes a random action with calculated probability epsilon. Epsilon is calculated based on
		the tValue.
	inputs: state the agent is in.
	outputs: Best action according to our qhat function. (Or a random action)
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
Action QHat::GetPI(State state)
{
	double epsilon = 1 / (1 + (tValue * 0.000007)); // TODO replace magic number with a constant

	return GetPI(state, epsilon);
}