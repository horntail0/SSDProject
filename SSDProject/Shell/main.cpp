#include "shell.h"
#include "SSDAdapter.h"
#include "Runner.h"
#include "../Util/util.h"

Shell* shell = Shell::getInstance();

void showHelp()
{
	cout << "INVALID COMMAND" << endl;
	shell->help();
}

void runShell(string command, string param1 = "", string param2 = "")
{
	if (command == "read")
	{
		if (param1 == "") cin >> param1;
		try
		{
			shell->read(stoi(param1));
		}
		catch (const std::invalid_argument& e)
		{
			showHelp();
		}
	}
	else if (command == "write")
	{
		if (param1 == "" && param2 == "") cin >> param1 >> param2;
		try
		{
			shell->write(stoi(param1), param2);
		}
		catch (const std::invalid_argument& e)
		{
			showHelp();
		}
	}
	else if (command == "flush")
	{
		shell->flush();
	}
	else if (command == "erase")
	{
		if (param1 == "" && param2 == "") cin >> param1 >> param2; // lba, size
		try
		{
			shell->erase(stoi(param1), stoi(param2));
		}
		catch (const std::invalid_argument& e)
		{
			showHelp();
		}
	}
	else if (command == "erase_range")
	{
		if (param1 == "" && param2 == "") cin >> param1 >> param2; // slba, elba
		try
		{
			int size = stoi(param2) - stoi(param1) + 1;
			shell->erase(stoi(param1), size);
		}
		catch (const std::invalid_argument& e)
		{
			showHelp();
		}
	}
	else if (command == "exit")
	{
		exit(0);
	}
	else if (command == "help")
	{
		shell->help();
	}
	else if (command == "fullread")
	{
		shell->fullRead();
	}
	else if (command == "fullwrite")
	{
		if (param1 == "") cin >> param1;
		shell->fullWrite(param1);
	}
	else if (command == "scenario_list")
	{
		shell->showAvaiableTestScenario();
	}
	else
	{
		string filePath = command;
		Runner runner(filePath);

		if (command.size() >= 4 && command.substr(command.size() - 4) == ".lst")
		{
			runner.runFile();
		}
		else
		{
			if (!runner.run(command))
			{
				showHelp();
			}
		}
	}
}

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		while (true)
		{
			string command;
			cin >> command;

			runShell(command);
		}
	}
	else if (argc >= 2 && argc <= 5)
	{
		string command, param1, param2;

		if (argc == 2)                             // exit, help, fullread, run_list.lst, {test scenario}
		{
			command = string(argv[1]);
			runShell(command);
		}
		else if (argc == 3)                        // read, fullwrite
		{
			command = string(argv[1]);
			param1 = string(argv[2]);

			if ((command == "read" || command == "fullwrite") && isNumber(param1))
			{
				runShell(command, param1);
			}
			else
			{
				showHelp();
			}
		}
		else if (argc == 4)                       // write, erase, erase_range
		{
			command = string(argv[1]);
			param1 = string(argv[2]);
			param2 = string(argv[3]);

			if ((command == "write" || command == "erase" || command == "erase_range") && isNumber(param1))
			{
				runShell(command, param1, param2);
			}
			else
			{
				showHelp();
			}
		}
	}
	else
	{
		showHelp();
	}
}