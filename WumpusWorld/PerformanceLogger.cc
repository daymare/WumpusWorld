/*

	file: PerformanceLogger.cc
	programmer: Daylan Kelting
	description: file contianing function definitions for the performance logger class.

*/

#include "PerformanceLogger.h"

/*

	function: performance logger (default constructor)
	description: initializes the performance logger to the default log file with default variables.
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
PerformanceLogger::PerformanceLogger()
{
	PerformanceLogger(
		DEFAULT_PERFORMANCE_LOG_FILEPATH
		);
}

/*

	function: performance logger (specific constructor)
	description: initializes the performance logger with the given summary and performance filepaths
	inputs: path to summary file, path to performance file.
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
PerformanceLogger::PerformanceLogger(
	string _performanceFilepath
	)
{
	// performance file
	performanceFilepath = _performanceFilepath;
	performanceFile.open(performanceFilepath);

	// variables
	sumScoresSinceLastLog = 0;
}

/*

	function: performance logger (destructor)
	description: closes the files
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
PerformanceLogger::~PerformanceLogger()
{
	performanceFile.close();
}

/*

	function: add game
	description: adds a game to the log file
	inputs: time the game took in milliseconds, score of the game, number of moves taken in the game.
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO write definition.
		TODO test.

*/
void PerformanceLogger::AddGame (int score, int gameNumber)
{
	sumScoresSinceLastLog += score;
	
	// log the average score every so often
	if (gameNumber % GAMES_PER_LOG == 0)
	{
		int avgScore = sumScoresSinceLastLog / GAMES_PER_LOG;
		string output;

		 output =  to_string(gameNumber) + ", " + to_string(avgScore) + "\n";

		 performanceFile << output;

		sumScoresSinceLastLog = 0;
	}
}