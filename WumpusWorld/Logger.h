/*

abstract base class for loggers

*/


#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <stdio.h>

using namespace std;

class Logger
{
private:
	string filepath;
	FILE* outFile;

public:
	Logger();
	Logger(string _filepath);
	~Logger();
	virtual int Print(string message);
};




#endif

