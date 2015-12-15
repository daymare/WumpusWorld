/*

Logging and printing debug information to the console and files.

*/


#ifndef DEBUGLOGGER_H
#define DEBUGLOGGER_H

#define DEFAULT_DEBUG_FILEPATH "debug.txt"


#include <string>
#include <stdio.h>

#include "Logger.h"

using namespace std;

class DebugLogger : public Logger
{
public:
	int Print(string message) override;
	int PrintNoConsole(string message);
};



#endif