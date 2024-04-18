#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

class ShellLogger {
public:
	bool recordLog(string functionName, string log);

private:
	string getCurrentTimeString(const string& timeFormat);
	int getSizeOfLatestLog();
	string getFormattedLog(const string& functionName, const string& log);
	string getLastLineOfFile(const string& filePath);

	const string timeFormatForLogging = "[%y.%m.%d %H:%M:%S]";
	const string timeFormatForFileName = "%y%m%d_%Hh_%M_%Ss";
	const string nameOfLatestLog = "latest.log";
	const string nameOfLogList = "logList.txt";
};