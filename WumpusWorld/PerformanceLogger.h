/*

	file: PerformanceLogger.h
	programmer: Daylan Kelting
	description: file containing the performance logger class.
		the performance logger is for logging the change in performance of our agents over time.

*/

#ifndef PERFORMANCE_LOGGER_H
#define PERFORMANCE_LOGGER_H

#define DEFAULT_PERFORMANCE_LOG_FILEPATH "performance.dat"

#define GAMES_PER_LOG 500

#include <string>
#include <iostream>
#include <fstream>

#include "Logger.h"

class PerformanceLogger
{
private:
	int sumScoresSinceLastLog;

	string performanceFilepath;
	ofstream performanceFile;

public:

	PerformanceLogger();
	PerformanceLogger(string _performanceFilepath);
	~PerformanceLogger();

	void AddGame(int score, int gameNumber);

};


#endif