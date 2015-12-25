/*

	programmer: Daylan Kelting
	date created: 11/15/2015
	date last modified: 12/11/2015
	description: This class ties together all elements of the QLearning approach in Wumpus world.

*/

#include "QLearningAgent.h"
#include "QHat.h"
#include "Reward.h"

using namespace std;

QHat *QLearningAgent::Q = new QHat();
// TODO initialize performance logger.

/*

	function: q learning agent (default constructor)
	description: initializes QHat and the logger.
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
QLearningAgent::QLearningAgent()
{
	// TODO change Q and Performance logger away from being static variables.

	// initialize game transition and state variables
	currentTransition = Transition();
	lastTransition = Transition();
	lastState = State();
	currentState = State();
}

/*

	function: q learning agent (default deconstructor)
	description: frees all heap memory and finishes logging.
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
QLearningAgent::~QLearningAgent()
{
	// stop logging
	log.FinishLogging();

	delete Q;
} 

/*

	function: initialize
	description: initializes all of the variables used for the start of a 
		game of wumpus world.
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
void QLearningAgent::Initialize() 
{
	transitionList = vector<Transition>();
	currentTransition = Transition();
	lastTransition = Transition();
	lastState =  State();
	currentState = State();
	numRounds = 0;
	currentAction = Action_TurnRight;
	lastAction = Action_TurnRight;
}

/*

	function: process
	description: updates state and transition information and outputs the
		desired policy action.
	inputs: percept of the agent
	outputs: action for the agent to take on this turn
	preconditions: Initialize must have been called.
	postconditions: N/A
	remarks:
		TODO test.

*/
Action QLearningAgent::Process(Percept &percept)
{
	// generate this round state information
	currentState.UpdatePercept(percept);

	// calculate policy action based on state
	currentAction = Q->GetPI(currentState);

	// initialize this round transition information
	currentTransition = Transition(currentState, currentAction);

	// update history to reflect that we have been at this location
	int xPos = currentState.GetXPos();
	int yPos = currentState.GetYPos();
	
	currentState.SetHistory(xPos, yPos, true);

	// if this is not the first round
	if (numRounds != 0)
	{
		// calculate immediate reward for last transition
		int reward = GetReward(currentState, lastTransition.actionTaken);

		// complete last round transition information
		lastTransition.FinishTransitionInformation(reward, currentState);

		// update transitions
		transitionList.push_back(lastTransition);
		memcpy(&lastTransition, &currentTransition, sizeof(Transition)); // TODO BUG potential heap corruption here
	}

	// update this round state information based on action
	currentState.UpdateActionInfo(currentAction);
	
	// increment number of rounds we have had
	numRounds++;

	// output policy action
	return currentAction;
}

/*

	function: game over
	description: 
		updates the last state and transition info.
		Adds the game to QHat
		Loggs the game.
	inputs: score at the end of the game, agent status at the end of 
		the game
	outputs: N/A
	preconditions: initialize 
	postconditions: N/A
	remarks:
		TODO test.

*/
void QLearningAgent::GameOver(int score, AgentStatus agentStatus)
{
	// update state information
	currentState.UpdateStatus(agentStatus);

	// complete last round transition information
	int lastReward = GetReward(currentState, lastTransition.actionTaken);
	transitionList.push_back(lastTransition);

	// update Q^ with all of the transition information received from last game
	Q->AddGame(transitionList);

	// send game information to performance logger
	log.AddGame(1, score, numRounds);
}

/*

	function: finish
	description: save qhat
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		basically replaces our destructor. Not sure why our destructor is not getting called.
		TODO figure out why the destructor is not getting called.
		TODO test

*/
void QLearningAgent::Finish()
{
	ofstream outFile;
	outFile.open(DEFAULT_SAVE_FILEPATH);
	Q->SaveQHat(&outFile);
	outFile.close();
}