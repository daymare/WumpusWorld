// wumpsim.cc
//
// Main Wumpus Simulator procedure.

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include "Percept.h"
#include "Action.h"
#include "WumpusWorld.h"
#include "Agent.h"
#include "RandomAgent.h"
#include "QLearningAgent.h"
#include "wumpsim.h"


using namespace std;

int main (int argc, char *argv[])
{
	int worldSize = 2;
	int numTrials = 1;
	int numTries = 1;
	unsigned seed;
	char* worldFile;
	bool seedSet = false;
	bool worldSet = false;

	// tell cout to suppress output to speed up training.
	//cout.setstate(ios_base::failbit);

	// set training parameters
	worldSize = 2;
	numTrials = 100000;
	numTries = 1;
	seedSet = false;
	worldSet = false;

	// Set random number generator seed
	if (! seedSet)
	{
		seed = (unsigned) time (0);
	}
	srand (seed);

	// Print welcome
	cout << "Welcome to the Wumpus World Simulator v";
        cout << WUMPSIM_VERSION << ".  Happy hunting!" << endl << endl;

	// Run trials
	WumpusWorld* wumpusWorld;
	Agent* agent;
	Percept percept;
	Action action;
	int score;
	int trialScore;
	int totalScore = 0;
	double averageScore;
	int numMoves;

	// print a loading indication.
	printf("loading from file...\n");

	agent = new QLearningAgent();

	printf("Done loading\n");
	printf("Starting training\n");

	for (int trial = 1; trial <= numTrials; trial++)
	{
		// print an indication every 500 trials
		if (trial % 500 == 0)
		{
			printf("trial: %d\n", trial);
		}

		if (worldSet)
		{
			wumpusWorld = new WumpusWorld (worldFile);
		} else {
			wumpusWorld = new WumpusWorld (worldSize);
		}

		//wumpusWorld->Write (".world");
		trialScore = 0;

		for (int tries = 1; tries <= numTries; tries++)
		{
			wumpusWorld->Initialize();
			agent->Initialize ();
			numMoves = 0;
			cout << "Trial " << trial << ", Try " << tries << " begin" << endl << endl;
			while ((!wumpusWorld->GameOver()) && (numMoves < MAX_MOVES_PER_GAME))
			{
				wumpusWorld->Print();
				percept = wumpusWorld->GetPercept();
				action = agent->Process (percept);
				cout << "Action = ";
				PrintAction (action);
				cout << endl << endl;
				wumpusWorld->ExecuteAction (action);
				numMoves++;
			}
			score = wumpusWorld->GetScore();
			agent->GameOver (score, wumpusWorld->GetAgentStatus()); // need to feed the agent it's status info at the end of the game
			trialScore = trialScore + score;
			cout << "Trial " << trial << ", Try " << tries << " complete: Score = " << score << endl << endl;
		}
		delete wumpusWorld;
		averageScore = ((float) trialScore) / ((float) numTries);
		cout << "Trial " << trial << " complete: Average score for trial = " << averageScore << endl << endl;
		totalScore = totalScore + trialScore;
	}

	printf("Saving to file\n");
	agent->Finish();
	delete agent;

	averageScore = ((double) totalScore) / ((double) (numTrials * numTries));
	cout << "All trials completed: Average score for all trials = " << averageScore << endl;
	cout << "Thanks for playing!" << endl << endl;

	return 0;
}
