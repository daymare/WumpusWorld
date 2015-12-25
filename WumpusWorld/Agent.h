// Agent.h

#ifndef AGENT_H
#define AGENT_H

#include "Action.h"
#include "Percept.h"
#include "State.h"

class Agent
{
public:
	Agent ();
	~Agent ();
	virtual void Initialize ();
	virtual Action Process (Percept& percept);
	virtual void GameOver (int score, AgentStatus agentStatus);
	virtual void Finish();
};

#endif // AGENT_H
