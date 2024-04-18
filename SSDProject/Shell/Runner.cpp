#include "Runner.h"

string toLower(const string& str)
{
	string result = str;
	transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

Runner::Runner() {
	shell_ = Shell::getInstance();
}

void Runner::setRunList(string filePath)
{
	filePath_ = filePath;
}

void Runner::run()
{
	string line;
	ifstream file(filePath_);

	if (!file.is_open())
	{
		cerr << "Error opening file: " << filePath_ << endl;
		return;
	}

	while (getline(file, line))
	{
		if (toLower(line) == "testapp1")
		{
			cout << line << "\t---\tRun...";
			bool printout = false;
			if (shell_->testApp1(printout)) cout << "PASS" << endl;
			else
			{
				cout << "FAIL!" << endl;
				exit(0);
			}
		}
		else if (toLower(line) == "testapp2")
		{
			cout << line << "\t---\tRun...";
			bool printout = false;
			if (shell_->testApp2(printout)) cout << "PASS" << endl;
			else
			{
				cout << "FAIL!" << endl;
				exit(0);
			}
		}
		else if (toLower(line) == "write10andcompare")
		{
			cout << line << "\t---\tRun...";
			bool printout = false;
			if (shell_->testWrite10AndCompare(printout)) cout << "PASS" << endl;
			else
			{
				cout << "FAIL!" << endl;
				exit(0);
			}
		}
		else if (toLower(line) == "loopwriteandreadcompare")
		{
			cout << line << "\t---\tRun...";
			bool printout = false;
			if (shell_->testLoopWriteAndReadCompare(printout)) cout << "PASS" << endl;
			else
			{
				cout << "FAIL!" << endl;
				exit(0);
			}
		}
	}
	file.close();
}
