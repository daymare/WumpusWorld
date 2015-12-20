/*

	file: DebugLogger.cc
	programmer: Daylan Kelting
	description: file containing function definitions for the debug logger.

*/

#include "DebugLogger.h"

/*

	function: debug logger (default constructor)
	description: initializes the logger to the default debug filepath
	inputs: N/A
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
DebugLogger::DebugLogger()
{
	Logger(DEFAULT_DEBUG_FILEPATH);
}

/*

	function: print
	description: prints a message to the debug log folder.
	inputs: message to print
	outputs: N/A
	preconditions: N/A
	postconditions: N/A
	remarks:
		TODO test.

*/
void DebugLogger::Print(string message)
{
#ifdef DEBUG_ON_CONSOLE
	cout << "DEBUG " + message;
#endif
	outFile << message;
}