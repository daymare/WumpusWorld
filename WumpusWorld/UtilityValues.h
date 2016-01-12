/*

	file: UtilityValues.h
	programmer: Daylan Kelting
	description: Class implementing the ridiculous array containing all of our utility values

*/

#ifndef UTILITYVALUES_H
#define UTILITYVALUES_H

#include <iostream>
#include <fstream>
#include <string>

#include "State.h"
#include "Action.h"

class UtilityCoordinate
{
public:
	State state = State();
	Action action = Action_GoForward;

	// constructors
	UtilityCoordinate();
	UtilityCoordinate(State state, Action action);
};

class UtilityValues
{
public:
	// Array containing all state action pair values
	// index order is as follows:
	// xPos, yPos, direction, status, hasArrow, hasGold,
	// isStench, isBreeze, isGlitter, hasScreamed, action
	// history value for 1, 1
	// history value for 1, 2
	// etc...
	double utilityValues[2][2][4][3][2][2][2][2][2][2][6][2][2][2][2] = { 0 };

	UtilityValues();

	// utility Methods
	int GetSize();

	// get max methods
	double GetMax(State state, Action action);
	double GetMax(State state);

	// file methods
	void SaveUtilityValues(ofstream *outFile);
	void LoadUtilityValues(ifstream *inFile);

	// accessor methods
	double* GetStartPtr();
	double GetUtilityValue(UtilityCoordinate coordinate);
	void SetUtilityValue(UtilityCoordinate coordinate, double value);
	void SetAllUtilityValues(double value);

	
};

#endif