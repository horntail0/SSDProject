#include "ShellLogger.h"
static ShellLogger slogger;

ShellLogger* ShellLogger::getInstance()
{
	return &slogger;
}

void ShellLogger::recordLog(string functionName, string log)
{
	string logToRecord = getFormattedLog(functionName, log);

	if (shouldAddNewLog(logToRecord))
	{
		compressOldLogs();
		changeLatestLogNameToCurrentTime();
	}

	recordLogToLatestLog(logToRecord);
}


bool ShellLogger::shouldAddNewLog(const string& logToRecord)
{
	return ((getSizeOfLatestLog() + logToRecord.length() * 2) > MAX_LOG_FILE_SIZE);
}

void ShellLogger::compressOldLogs()
{
	string fileNameToCompress = getLastLineOfFile(nameOfLogList);
	if (!fileNameToCompress.empty())
	{
		string newNameOfOldLogs = fileNameToCompress.substr(0, fileNameToCompress.size() - 4) + ".zip";
		if (rename(fileNameToCompress.c_str(), newNameOfOldLogs.c_str()) != 0)
		{
			cout << "rename failure" << endl;
		}
	}
}

void ShellLogger::recordLogToLatestLog(const string& logToRecord)
{
	ofstream outFile(nameOfLatestLog, std::ios::app);
	if (outFile.is_open())
	{
		outFile << getCurrentTimeString(timeFormatForLogging) << " " << logToRecord << endl;
		outFile.close();
	}
}

void ShellLogger::changeLatestLogNameToCurrentTime()
{
	string newName = "until_" + getCurrentTimeString(timeFormatForFileName) + ".log";
	if (rename(nameOfLatestLog.c_str(), newName.c_str()) != 0)
	{
		cout << "Fail to Rename file (from:" << nameOfLatestLog << " to:" << newName << endl;
	}

	updateLogList(newName);
}

void ShellLogger::updateLogList(const string& newName)
{
	ofstream outFile(nameOfLogList, std::ios::app);
	if (outFile.is_open())
	{
		outFile << newName << endl;
		outFile.close();
	}
}

string ShellLogger::getLastLineOfFile(const string& filePath)
{
	ifstream file(filePath);
	if (!file.is_open())
	{
		return "";
	}

	string lastLine, line;
	while (getline(file, line))
	{
		lastLine = line;
	}
	file.close();
	return lastLine;
}

string ShellLogger::getFormattedLog(const string& functionName, const string& log)
{
	string formattedLog = functionName + "()";
	while (formattedLog.length() < 30)
	{
		formattedLog += " ";
	}
	formattedLog += ": " + log;

	return formattedLog;
}

string ShellLogger::getCurrentTimeString(const string& timeFormat)
{
	time_t now = time(nullptr);
	char buffer[20];
	string timeString;
	struct tm timeinfo;

	if (localtime_s(&timeinfo, &now) == 0)
	{
		if (strftime(buffer, sizeof(buffer), timeFormat.c_str(), &timeinfo) != 0)
		{
			timeString = buffer;
		}
	}

	return timeString;
}

int ShellLogger::getSizeOfLatestLog()
{
	int sizeOfCurrentFile = 0;
	ifstream currentFile("latest.log", std::ios::ate | std::ios::binary);
	if (currentFile)
	{
		sizeOfCurrentFile = currentFile.tellg();
		currentFile.close();
	}
	return sizeOfCurrentFile;
}
