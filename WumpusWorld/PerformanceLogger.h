/*

	file: PerformanceLogger.h
	programmer: Daylan Kelting
	description: file containing the performance logger class.
		the performance logger is for logging the change in performance of our agents over time.

*/

#ifndef PERFORMANCE_LOGGER_H
#define PERFORMANCE_LOGGER_H

#define DEFAULT_PERFORMANCE_LOG_FILEPATH "performance.txt"
#define DEFAULT_SUMMARY_LOG_FILEPATH "performanceSummary.txt"

#define GAMES_PER_LOG 2

#include <string>
#include <iostream>
#include <fstream>

#include "Logger.h"

using namespace std;

class PerformanceLogger
{
private:
	int gamesSinceLastLog;
	int totalGameTime;
	int numGames;
	int sumGameScores;

	string performanceFilepath;
	ofstream performanceFile;
	string summaryFilepath;
	ofstream summaryFile;

public:
	PerformanceLogger();
	PerformanceLogger(string _summaryFilepath);
	PerformanceLogger(string _summaryFilepath, string _performanceFilepath);
	~PerformanceLogger();

	void Print(string message);

	void FinishLogging();

	void AddGame(int gameTime, int score, int numMoves);

};


#endif