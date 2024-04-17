#include "shell.h"
#include "SSDAdapter.h"

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
		else if (command == "testapp1")
		{
			string testData = "0x12345678";
			shell.fullWrite(testData);
			shell.fullRead();
		}
		else if (command == "testapp2")
		{
			string testData = "0xAAAABBBB";
			for (int i = 0; i < 30; i++)
				for (int j = 0; j <= 5; j++)
					shell.write(j, testData);

			string testData2 = "0x12345678";
			for (int i = 0; i <= 5; i++)
				shell.write(i, testData2);

			for (int i = 0; i <= 5; i++)
				shell.read(i);
		}
		else
		{
			cout << "INVALID COMMAND" << endl;
			shell.help();
		}
	}
}