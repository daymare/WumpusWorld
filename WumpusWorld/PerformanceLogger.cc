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
	
}

/*

	function: performance logger (specific constructor with regard to the summary file)
	description: 
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO write definition.
		TODO test.

*/
PerformanceLogger::PerformanceLogger(string _summaryFilepath)
{

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
PerformanceLogger::PerformanceLogger(string _summaryFilepath, string _performanceFilepath)
{
	// summary file
	summaryFilepath = _summaryFilepath;
	summaryFile.open(summaryFilepath);

	// performance file
	performanceFilepath = _performanceFilepath;
	performanceFile.open(performanceFilepath);

	// variables
	gamesSinceLastLog = 0;
	totalGameTime = 0;
	numGames = 0;
	sumGameScores = 0;
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
	summaryFile.close();
	performanceFile.close();
}

/*

	function: print
	description: prints a message to the summary file
	inputs: message to print
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
void PerformanceLogger::Print(string message)
{
	summaryFile << message;
}

/*

	function: finish logging
	description: finishes a logging session for a given agent.
		prints the summary for the agents performance in the summary file.
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO write definition.
		TODO test.

*/
void PerformanceLogger::FinishLogging()
{
	double averageScore = (double)sumGameScores / (double)numGames;

	// total game time
	summaryFile << "Total game time in milliseconds:\n";
	summaryFile << totalGameTime + "\n";

	// total games
	summaryFile << "Total number of games:\n";
	summaryFile << numGames + "\n";

	// average game score
	summaryFile << "Average game score:\n";
	//summaryFile << averageScore + "\n";
	// TODO figure out how to convert from double to string

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
void PerformanceLogger::AddGame(int gameTime, int score, int numMoves)
{

}