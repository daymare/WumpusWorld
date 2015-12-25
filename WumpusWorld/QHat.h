/*

	Class implementing Utility Estimate function

*/


#ifndef Q_HAT_H
#define Q_HAT_H

#define DEFAULT_LEARNING_RATE 0.1
#define DEFAULT_GAMMA 0.1

#define DEFAULT_SAVE_FILEPATH "DefaultSave.qdat"

#include <vector>
#include <string>
#include <random>
#include <time.h>
#include <fstream>
#include <iostream>

#include "Action.h"
#include "State.h"
#include "Transition.h"
#include "UtilityValues.h"


#define DEFAULT_LEARNING_RATE 0.1
#define DEFAULT_GAMMA 0.01

class QHat
{
private:
	/// state information

	double learningRate = DEFAULT_LEARNING_RATE;
	double gamma = DEFAULT_GAMMA; // discount of future reward.
	double tValue = 1;

	UtilityValues utility;

	/// behavior
	void Update(const Transition transition);
	double CalculateAlpha(int T);

	void InitRandom();

	// private get functions
	double GetMax(State state, Action action);
	double GetMax(State state);

public:

	QHat(); // load from default file
	QHat(double _learningRate, double _gamma); // initialize to nothing
	QHat(ifstream loadFile); // load from a file
	~QHat();

	void SaveQHat(ofstream *outFile);
	void LoadQHat(ifstream *inFile);

	double GetValue(State state, Action action);
	void SetValue(State state, Action action, double value);
	void AddGame(vector<Transition> transitions);
	void IncrementT();
	Action GetPI(State state);
	Action GetPI(State state, double epsilon); // solves Pi^... didn't want to make a whole new class for Pi^.
};


#endif