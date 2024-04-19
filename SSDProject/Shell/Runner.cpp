#include "Runner.h"

string toLower(string& str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

Runner::Runner(string filePath) 
	: filePath_(filePath) 
{
	shell_ = Shell::getInstance();
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

			bool printOut = false;
			if (shell_->customTest("testapp1", printOut)) cout << "PASS" << endl;
			else
			{
				cout << "FAIL!" << endl;
				exit(0);
			}
		}
		else if (toLower(line) == "testapp2")
		{
			cout << line << "\t---\tRun...";

			bool printOut = false;
			if (shell_->customTest("testapp2", printOut)) cout << "PASS" << endl;
			else
			{
				cout << "FAIL!" << endl;
				exit(0);
			}
		}
		else if (toLower(line) == "write10andcompare")
		{
			cout << line << "\t---\tRun...";

			bool printOut = false;
			if (shell_->testWrite10AndCompare(printOut)) cout << "PASS" << endl;
			else
			{
				cout << "FAIL!" << endl;
				exit(0);
			}
		}
		else if (toLower(line) == "loopwriteandreadcompare")
		{
			cout << line << "\t---\tRun...";
			bool printOut = false;
			if (shell_->testLoopWriteAndReadCompare(printOut)) cout << "PASS" << endl;
			else
			{
				cout << "FAIL!" << endl;
				exit(0);
			}
		}
	}
	file.close();
}
