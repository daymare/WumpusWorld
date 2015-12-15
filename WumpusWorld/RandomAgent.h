


#ifndef RANDOM_AGENT_H
#define ARANDOM_GENT_H

#include "Action.h"
#include "Percept.h"
#include "Agent.h"
#include "State.h"

class RandomAgent : public Agent
{
public:
	RandomAgent();
	~RandomAgent();
	void Initialize() override;
	Action Process(Percept& percept) override;
	void GameOver(int score, AgentStatus agentStatus) override;
};

#endif // RANDOM_AGENT_H