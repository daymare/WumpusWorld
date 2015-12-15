/*

Logging the performance of our algorithms

*/

#ifndef PERFORMANCE_LOGGER_H
#define PERFORMANCE_LOGGER_H


#include <string>
#include <stdio.h>

#include "Logger.h"

using namespace std;

class PerformanceLogger : public Logger
{
private:
	const int GAMES_PER_LOG;
	int gamesSinceLastLog;
	int totalGameTime;
	int numGames;
	int sumGameScores;

	string performanceFilepath;
	FILE* performanceFile;

public:
	PerformanceLogger();
	PerformanceLogger(string _summaryFilepath);
	PerformanceLogger(string _summaryFilepath, string _performanceFilepath);
	~PerformanceLogger();

	int Print(string message);

	int FinishLogging();

	int AddGame(int gameTime, int score, int numMoves);

};


#endif