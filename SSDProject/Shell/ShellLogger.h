#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

class ShellLogger {
public:
	void recordLog(string functionName, string log);
	static ShellLogger* getInstance();
private:
	string getCurrentTimeString(const string& timeFormat);
	int getSizeOfLatestLog();
	string getFormattedLog(const string& functionName, const string& log);
	string getLastLineOfFile(const string& filePath);
	void compressOldLogs();
	bool shouldAddNewLog(const string& logToRecord);
	void changeLatestLogNameToCurrentTime();
	void updateLogList(const string& newName);
	void recordLogToLatestLog(const string& logToRecord);

	const string timeFormatForLogging = "[%y.%m.%d %H:%M:%S]";
	const string timeFormatForFileName = "%y%m%d_%Hh_%M_%Ss";
	const string nameOfLatestLog = "latest.log";
	const string nameOfLogList = "logList.txt";
	const int MAX_LOG_FILE_SIZE = 10 * 1024; /* 10 KB */
};