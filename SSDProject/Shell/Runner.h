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
	string filePath_;
	Shell* shell_;
};