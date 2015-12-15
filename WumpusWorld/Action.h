/*

file: Action.h
programmer: Don't know, found it from a class website. -Daylan Kelting
description: File defining actions that the agent can make in the Wumpus World game

*/
#ifndef ACTION_H
#define ACTION_H

#include <vector>

using namespace std;

enum Action {
	Action_GoForward, 
	Action_TurnLeft, 
	Action_TurnRight, 
	Action_Grab, 
	Action_Shoot, 
	Action_Climb
};

typedef vector<Action> ActionList;

void PrintAction (Action action);

#endif // ACTION_H
