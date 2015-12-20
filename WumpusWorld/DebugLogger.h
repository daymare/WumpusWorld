/*

	file: DebugLogger.h
	programmer: Daylan Kelting
	description: file containing the debug logger class. The purpose of which is hopefully obvious to you.

*/


#ifndef DEBUGLOGGER_H
#define DEBUGLOGGER_H

#define DEFAULT_DEBUG_FILEPATH "debug.txt"

#define DEBUG_ON_CONSOLE

#include <string>
#include <iostream>

#include "Logger.h"

using namespace std;

class DebugLogger : public Logger
{
public:
	DebugLogger();
	void Print(string message) override;
};


#endif