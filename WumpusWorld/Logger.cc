/*
	
	file: Logger.cc
	programmer: Daylan Kelting
	description: file defining functions for the abstract logger class.

*/


#include "Logger.h"

/*

	function: logger (default constructor)
	description: initializes the logger to the default log file.
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
Logger::Logger()
{
	Logger(DEFAULT_LOG_FILEPATH);
}

/*

	function: logger (specific constructor)
	description: initializes the logger to the given log filepath
	inputs: filepath to log to.
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
Logger::Logger(string _filepath)
{
	filepath = _filepath;
	outFile.open(filepath);
}

/*

	function: logger (destructor)
	description: 
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
Logger::~Logger()
{
	outFile.close();
}

void Logger::Print(string message)
{
	outFile << message;
}