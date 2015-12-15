// Action.cc

#include <iostream>
#include "Action.h"

void PrintAction (Action action)
{
	if (action == Action_GoForward)
	{
		cout << "GOFORWARD";
	}
	if (action == Action_TurnLeft)
	{
		cout << "TURNLEFT";
	}
	if (action == Action_TurnRight)
	{
		cout << "TURNRIGHT";
	}
	if (action == Action_Grab)
	{
		cout << "GRAB";
	}
	if (action == Action_Shoot)
	{
		cout << "SHOOT";
	}
	if (action == Action_Climb)
	{
		cout << "CLIMB";
	}
}
