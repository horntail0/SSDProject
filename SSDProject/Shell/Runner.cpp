#include "Runner.h"

string toLower(string& str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

Runner::Runner()
{
	shell_ = Shell::getInstance();
}

Runner::Runner(string filePath)
	: filePath_(filePath)
{
	shell_ = Shell::getInstance();
}

bool Runner::run(string& line)
{
	if (checkValidCommand(toLower(line)) == true)
	{
		doCustomTest(line);
		return true;
	}
	return false;
}

void Runner::runFile()
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
		run(line);
	}

	file.close();
}

bool Runner::checkValidCommand(string command)
{
	if (shell_->checkValidCommand(command))
	{
		return true;
	}
	else
	{
		shell_->showAvaiableTestScenario();
		return false;
	}
}

void Runner::doCustomTest(string line)
{
	cout << line << "\t---\tRun...";
	bool printOut = false;
	if (shell_->customTest(toLower(line), printOut)) cout << "PASS" << endl;
	else
	{
		cout << "FAIL!" << endl;
		exit(0);
	}
}
