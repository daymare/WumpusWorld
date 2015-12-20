/*

	file: Action.h
	programmer: Don't know, found it from a class website. -Daylan Kelting
	description: File defining actions that the agent can make in the Wumpus World game

*/
#ifndef ACTION_H
#define ACTION_H

#define NUM_ACTIONS 6

#include <vector>

using namespace std;

enum Action {
	Action_GoForward = 0, 
	Action_TurnLeft = 1, 
	Action_TurnRight = 2, 
	Action_Grab = 3, 
	Action_Shoot = 4, 
	Action_Climb = 5
};

typedef vector<Action> ActionList;

void PrintAction (Action action);

#endif // ACTION_H
