#pragma once
#include "Shell.h"
#include <string>
#include <algorithm>
using namespace std;

class Runner
{
public:
    Runner(string filePath);
	void run();

private:
	bool checkValidCommand(string command);
	void doCustomTest(string command);
	string filePath_;
	Shell* shell_;
};