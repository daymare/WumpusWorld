
#include <stdlib.h>

#include "RandomAgent.h"

RandomAgent::RandomAgent ()
{
}

RandomAgent::~RandomAgent()
{
}

void RandomAgent::Initialize()
{
}

Action RandomAgent::Process(Percept& percept)
{
	int randNum = rand() % 6;
	Action action = (Action) randNum;
	return action;
}

void RandomAgent::GameOver (int score, AgentStatus status)
{
}