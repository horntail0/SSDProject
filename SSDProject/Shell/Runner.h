#pragma once
#include "Shell.h"
#include <string>
#include <algorithm>
using namespace std;

class Runner
{
public:
	Runner(string filePath);
	bool run(string& line);
	void runFile();

private:
	bool checkValidCommand(string command);
	void doCustomTest(string command);
	string filePath_;
	Shell* shell_;
};