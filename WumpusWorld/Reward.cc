

#include "Reward.h"

#include "State.h"
#include "Action.h"


int GetReward(State s, Action a)
{
	if (a == Action_Shoot)
	{
		return -10; // shooting the arrow is -10
	} 
	else if(s.GetStatus() == AgentStatus_Dead)
	{
		return -1001; // dying is -1000
	}
	else if (s.GetHasGold() && s.GetStatus() == AgentStatus_LeftCave)
	{
		return 999; // leaving with the gold is +1000
	}
	else 
	{
		return -1; // all actions are -1 by default
	}
}