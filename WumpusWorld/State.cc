/*

	file: State.cc
	programmer: Daylan Kelting
	description: Contains all of the definitions for functions in the state class

*/


#include <algorithm>

#include "State.h"
#include "Action.h"
#include "Percept.h"

using namespace std;

/*

	function: State (default constructor)
	description: initializes all variables in state to what they should be
		at the start of a game of Wumpus World.
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
State::State()
{
	xPos = 1;
	yPos = 1;
	direction = Direction_Right;
	status = AgentStatus_Alive;
	hasArrow = true;
	hasGold = false;
	isStench = false;
	isBreeze = false;
	isGlitter = false;
	hasScreamed = false;
	memset(&history, 0, sizeof(History));
}

/*

	function: turn
	description: updates the state to reflect turning either left or right
	inputs: boolean to tell if we are turning right. (true = right, false = left);
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
void State::Turn(bool right)
{
	int iDirection;
	iDirection = (int)direction;

	if (right)
	{
		iDirection++;
		iDirection %= 4;
	}
	else
	{
		iDirection--;
		iDirection = iDirection >= 0 ? iDirection : 3;
	}
	direction = (Direction)iDirection;
}

/*

	function: move forward
	description: updates the state to reflect moving forward
	in the direction facing by one space.
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
void State::MoveForward()
{
	switch (direction)
	{
	case Direction_Up:
		yPos++;
		yPos = min(yPos, MAX_Y);
		break;
	case Direction_Down:
		yPos--;
		yPos = max(yPos, 1);
		break;
	case Direction_Left:
		xPos--;
		xPos = max(xPos, 1);
		break;
	case Direction_Right:
		xPos++;
		xPos = min(xPos, MAX_X);
		break;
	}
}

/*

	function: update action info
	description: updates the action info of a state
		based on whatever action is passed in
	inputs: action value to update for
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
void State::UpdateActionInfo(Action action)
{
	switch (action)
	{
	case Action_GoForward:
		MoveForward();
		break;

	case Action_TurnLeft:
		Turn(false);
		break;

	case Action_TurnRight:
		Turn(true);
		break;

	case Action_Grab:
		if (isGlitter)
		{
			hasGold = true;
		}
		break;

	case Action_Shoot:
		hasArrow = false;
		break;
	
	case Action_Climb:
		if (xPos == 0 && yPos == 0)
		{
			status = AgentStatus_LeftCave;
		}
		break;
	}
}

/*

	function: update percept (perception information)
	description: updates the state perception information
	inputs: perception info (what our agent can sense)
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
void State::UpdatePercept(Percept percept)
{
	isStench = percept.Stench;
	isBreeze = percept.Breeze;
	isGlitter = percept.Glitter;
	hasScreamed = percept.Scream;
}

/*

	function: update status
	description: updates the information about our agents status
	inputs: new status to update to
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
void State::UpdateStatus(AgentStatus newStatus)
{
	status = newStatus;
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
		TODO test.

*/
vector<State> State::GetPossibleStates(Action action)
{
	vector<State> posStates(5);
	State newState;
	
	int statusIndex = 0;
	int breezeIndex = 0;
	int stenchIndex = 0;
	int glitterIndex = 0;

	switch (action)
	{
	case Action_GoForward:
		if (this->IsFacingWall())
		{
			// return just a copy of the input state
			posStates.push_back(*this);
			break;
		}

		// not facing a wall
		// get a copy of the state except one space forward
		newState = *this;
		newState.UpdateActionInfo(Action_GoForward);
		posStates.push_back(newState);

		// get all of the possible states given that we took a step forward.
		
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
					}// TODO fix bug: heap is apparently corrupted around here.
				}
			}
		}
		break;

	case Action_TurnLeft:
		newState = *this;
		newState.UpdateActionInfo(Action_TurnLeft);
		posStates.push_back(newState);
		break;

	case Action_TurnRight:
		newState = *this;
		newState.UpdateActionInfo(Action_TurnRight);
		posStates.push_back(newState);
		break;

	case Action_Grab:
		if (!this->GetIsGlitter())
		{
			posStates.push_back(*this);
			break;
		}
		else
		{
			newState = *this;

			newState.SetHasGold(true);
			newState.SetIsGlitter(false);

			posStates.push_back(newState);
			break;
		}
	case Action_Shoot:

		newState = *this;
		newState.SetHasArrow(false);
		posStates.push_back(newState);

		break;

	case Action_Climb:

		if (this->GetXPos() == 0 && this->GetYPos() == 0)
		{
			posStates.push_back(*this);
		}

		newState = *this;

		newState.SetStatus(AgentStatus_LeftCave);

		posStates.push_back(newState);
		break;
	}

	return posStates;
}

/*

	function: is facing wall
	description: returns whether the agent is facing a wall or not
	inputs: N/A
	outputs: 
		returns true if the agent is facing a wall
		false otherwise
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
bool State::IsFacingWall()
{
	switch (direction)
	{
	case Direction_Down:
		return yPos == 0;

	case Direction_Left:
		return xPos == 0;

	case Direction_Right:
		return xPos == 2;

	case Direction_Up:
		return yPos == 2;
	}
}

/// Accessor methods
int State::GetXPos()
{
	return xPos;
}
int State::GetYPos()
{
	return yPos;
}
Direction State::GetDirection()
{
	return direction;
}
AgentStatus State::GetStatus()
{
	return status;
}
bool State::GetHasArrow()
{
	return hasArrow;
}
bool State::GetHasGold()
{
	return hasGold;
}
bool State::GetIsStench()
{
	return isStench;
}
bool State::GetIsBreeze()
{
	return isBreeze;
}
bool State::GetIsGlitter()
{
	return isGlitter;
}
bool State::GetHasScreamed()
{
	return hasScreamed;
}
bool State::GetHistory(int x, int y)
{
	// TODO change based on if we are using x y or array indexing
	return history[x - 1][y - 1];
}

void State::SetXPos(int _x)
{
	xPos = _x;
}
void State::SetYPos(int _y)
{
	yPos = _y;
}
void State::SetDirection(Direction _direction)
{
	direction = _direction;
}
void State::SetStatus(AgentStatus _status)
{
	status = _status;
}
void State::SetHasArrow(bool _hasArrow)
{
	hasArrow = _hasArrow;
}
void State::SetHasGold(bool _hasGold)
{
	hasGold = _hasGold;
}
void State::SetIsStench(bool _isStench)
{
	isStench = _isStench;
}
void State::SetIsBreeze(bool _isBreeze)
{
	isBreeze = _isBreeze;
}
void State::SetIsGlitter(bool _isGlitter)
{
	isGlitter = _isGlitter;
}
void State::SetHasScreamed(bool _hasScreamed)
{
	hasScreamed = _hasScreamed;
}
void State::SetHistory(int x, int y, bool value)
{
	// TODO change based on if we are using x y or array indexing
	history[x - 1][y - 1] = value; // TODO access violation writing location
	// x and y seem to be ridiculous values. Maybe not initialized?
}