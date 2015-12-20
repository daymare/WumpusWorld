/*

	file: Logger.h
	programmer: Daylan Kelting
	description: file containing the abstract logger class.

*/


#ifndef LOGGER_H
#define LOGGER_H

#define DEFAULT_LOG_FILEPATH "someLog.txt"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Logger
{
protected:
	string filepath;
	ofstream outFile;

public:
	Logger();
	Logger(string _filepath);
	~Logger();
	virtual void Print(string message);
};

#endif

