#include "Runner.h"

string toLower(const string& str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

Runner::Runner(string filePath) : filePath_(filePath) {}

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
			if (shell_.testApp1(printOut)) cout << "PASS" << endl;
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
			if (shell_.testApp2(printOut)) cout << "PASS" << endl;
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
			if (shell_.testWrite10AndCompare(printOut)) cout << "PASS" << endl;
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
			if (shell_.testLoopWriteAndReadCompare(printOut)) cout << "PASS" << endl;
			else
			{
				cout << "FAIL!" << endl;
				exit(0);
			}
		}
	}
	file.close();
}
