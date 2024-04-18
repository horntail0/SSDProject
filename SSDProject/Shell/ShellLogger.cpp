#include "ShellLogger.h"

bool ShellLogger::recordLog(string functionName, string log)
{
	string logStr = getFormattedLog(functionName, log);

	if ((getSizeOfLatestLog() + logStr.length() * 2) > 10 * 1024)
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

		string newName = "until_" + getCurrentTimeString(timeFormatForFileName) + ".log";
		if (rename(nameOfLatestLog.c_str(), newName.c_str()) != 0)
		{
			cout << "Fail to Rename file (from:" << nameOfLatestLog << " to:" << newName << endl;
		}

		ofstream outFile(nameOfLogList, std::ios::app);
		if (outFile.is_open())
		{
			outFile << newName << endl;
			outFile.close();
		}
	}

	ofstream outFile(nameOfLatestLog, std::ios::app);
	if (outFile.is_open())
	{
		outFile << getCurrentTimeString(timeFormatForLogging) << " " << logStr << endl;
		outFile.close();
	}
	else
	{
		return false;
	}
	return true;
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
