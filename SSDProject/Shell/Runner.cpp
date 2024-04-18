#include "Runner.h"
#include "Windows.h"

string toLower(const string& str)
{
	string result = str;
	transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

Runner::Runner() {}

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
			cout << "Performing testapp1 " << endl;
		}
		else if (toLower(line) == "testapp2")
		{
			cout << "Performing testapp2 " << endl;
		}
	}
	file.close();
}
