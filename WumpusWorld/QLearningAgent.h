/*

	This class ties together all elements of the QLearning approach in Wumpus World.
	It outputs the actions to the world and updates QHat

*/


#ifndef Q_LEARNING_AGENT_H
#define Q_LEARNING_AGENT_H

#include <vector>

#include "Percept.h"
#include "Agent.h"

#include "State.h"
#include "Action.h"
#include "Transition.h"
#include "QHat.h"

#include "PerformanceLogger.h"


class QLearningAgent : public Agent
{
private:
	/// State information
	static QHat *Q;
	static PerformanceLogger *log;
	int numRounds;

	vector<Transition> transitionList;
	Transition *currentTransition;
	Transition *lastTransition;

	State *lastState;
	State *currentState;

	Action lastAction;
	Action currentAction;

public:
	/// Behavior
	// constructors
	QLearningAgent();
	~QLearningAgent();

	// game methods
	void Initialize() override;
	Action Process(Percept &percept) override;
	void GameOver(int score, AgentStatus agentStatus) override;
};

#endif