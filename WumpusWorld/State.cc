/*

See State.h

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
	xPos = 0;
	yPos = 0;
	direction = Direction_Up;
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
TODO write definition.
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
	iDirection = (int)iDirection;

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
		TODO write definition.
		TODO test.

*/
void State::MoveForward()
{
	switch (direction)
	{
	case Direction_Up:
		yPos++;
		yPos %= MAX_Y+1;
		break;
	case Direction_Down:
		yPos--;
		yPos = max(yPos, 0);
		break;
	case Direction_Left:
		xPos--;
		xPos = max(xPos, 0);
		break;
	case Direction_Right:
		xPos++;
		xPos %= MAX_X+1;
		break;
	}
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
	history[x - 1][y - 1] = value;
}