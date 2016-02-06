// Agent.cc

#include <iostream>
#include "Agent.h"

using namespace std;

Agent::Agent ()
{

}

Agent::~Agent ()
{

}

void Agent::Initialize ()
{

}

Action Agent::Process (Percept& percept)
{
	char c;
	Action action;
	bool validAction = false;

	while (! validAction)
	{
		validAction = true;
		cout << "Action? ";
		cin >> c;
		if (c == 'f') {
			action = Action_GoForward;
		} else if (c == 'l') {
			action = Action_TurnLeft;
		} else if (c == 'r') {
			action = Action_TurnRight;
		} else if (c == 'g') {
			action = Action_Grab;
		} else if (c == 's') {
			action = Action_Shoot;
		} else if (c == 'c') {
			action = Action_Climb;
		} else {
			cout << "Huh?" << endl;
			validAction = false;
		}
	}
	return action;
}

void Agent::GameOver (int score, AgentStatus agentStatus)
{
	score = score;
	agentStatus = agentStatus;
}

void Agent::Finish(void)
{}

