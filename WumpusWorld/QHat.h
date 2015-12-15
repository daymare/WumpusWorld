/*

Class implementing Utility Estimate function

*/


#ifndef Q_HAT_H
#define Q_HAT_H

#define DEFAULT_LEARNING_RATE 0.1
#define DEFAULT_GAMMA 0.1

#define DEFAULT_SAVE_FILEPATH "DefaultSave.qdat"

#include <vector>
#include <string.h>

#include "Action.h"
#include "State.h"
#include "Transition.h"
#include "UtilityValues.h"


using namespace std;

class QHat
{
private:
	/// state information

	double learningRate;
	double gamma;
	double tValue;

	UtilityValues utility;

	/// behavior
	void Update(const Transition transition);
	double CalculateAlpha(int T);

	// private get functions
	double GetMax(State state, Action action);
	double GetMax(State state);
	vector<State> GetPossibleStates(State state, Action action);
	vector<State> GetPossibleStates(State state);

public:
	QHat(); // load from default file
	QHat(double _learningRate, double _gamma); // initialize to nothing
	QHat(FILE* loadFile); // load from a file
	~QHat();

	void SaveQHat(FILE* outFile);
	void LoadQHat(FILE* inFile);

	double GetValue(State state, Action action);
	void SetValue(State state, Action action, int value);
	void AddGame(vector<Transition> transitions);
	Action GetPI(State state); // solves Pi^... didn't want to make a whole new class for Pi^.
};


#endif