#include "../Shell/shell.cpp"
#include "SSDInterface.cpp"

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
		else
		{
			cout << "INVALID COMMAND" << endl;
			shell.help();
		}
	}
}