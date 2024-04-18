#include "shell.h"
#include "SSDAdapter.h"
#include "Runner.h"

int main()
{
	Shell shell;

	while (true)
	{
		string command, param1, param2;
		cin >> command;

		if (command == "read")
		{
			cin >> param1;
			shell.read(stoi(param1));
		}
		else if (command == "write")
		{
			cin >> param1 >> param2;
			shell.write(stoi(param1), param2);
		}
		else if (command == "erase")
		{
			cin >> param1 >> param2; // lba, size
			shell.erase(stoi(param1), stoi(param2));
		}
		else if (command == "erase_range")
		{
			cin >> param1 >> param2; // slba, elba
			int size = stoi(param2) - stoi(param1) + 1;
			shell.erase(stoi(param1), size);
		}
		else if (command == "exit")
		{
			break;
		}
		else if (command == "help")
		{
			shell.help();
		}
		else if (command == "fullread")
		{
			shell.fullRead();
		}
		else if (command == "fullwrite")
		{
			cin >> param1;
			shell.fullWrite(param1);
		}
		else if (command == "testapp1" || command == "testapp2")
		{
			shell.customTest(command);
		}
		else
		{
			if (command.size() >= 4 && command.substr(command.size() - 4) == ".lst")
			{
				Runner runner;
				runner.setRunList(command);
				runner.run();
			}
			else
			{
				cout << "INVALID COMMAND" << endl;
				shell.help();
			}
		}
	}
}