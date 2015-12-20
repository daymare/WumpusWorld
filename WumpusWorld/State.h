/*

	file: State.h
	programmer: Daylan Kelting
	description: Contains all data structures useful for representing
		states in the Wumpus World simulation.

*/


#ifndef STATE_H
#define STATE_H

#include "Action.h"
#include "Percept.h"

#define MAX_X 2;
#define MAX_Y 2;

using namespace std;

typedef enum Direction
{
	Direction_Up = 0,
	Direction_Right = 1,
	Direction_Down = 2,
	Direction_Left = 3
} Direction;

typedef enum AgentStatus
{
	AgentStatus_Alive = 0,
	AgentStatus_Dead = 1,
	AgentStatus_LeftCave = 2
} AgentStatus;

typedef bool History[2][2];

class State {
private:

	int xPos;
	int yPos;
	Direction direction;
	AgentStatus status;
	bool hasArrow;
	bool hasGold;
	bool isStench;
	bool isBreeze;
	bool isGlitter;
	bool hasScreamed;

	History history;

	// helper functions for updating action
	void Turn(bool right);
	void MoveForward();

public:

	/// Constructors
	State();
	
	// update functions
	void UpdateActionInfo(Action action);
	void UpdatePercept(Percept percept);
	void UpdateStatus(AgentStatus newStatus);

	// possible functions
	vector<State> GetPossibleStates(Action action);
	vector<State> GetPossibleStates();
	
	// status methods
	bool IsFacingWall();

	/// Accessor methods
	int GetXPos();
	int GetYPos();
	Direction GetDirection();
	AgentStatus GetStatus();
	bool GetHasArrow();
	bool GetHasGold();
	bool GetIsStench();
	bool GetIsBreeze();
	bool GetIsGlitter();
	bool GetHasScreamed();
	bool GetHistory(int x, int y);

	void SetXPos(int _x);
	void SetYPos(int _y);
	void SetDirection(Direction _direction);
	void SetStatus(AgentStatus _status);
	void SetHasArrow(bool _hasArrow);
	void SetHasGold(bool _hasGold);
	void SetIsStench(bool _isStench);
	void SetIsBreeze(bool _isBreeze);
	void SetIsGlitter(bool _isGlitter);
	void SetHasScreamed(bool _hasScreamed);
	void SetHistory(int x, int y, bool value);

};


#endif