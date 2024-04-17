#include "SSDInterface.cpp"

#include<iostream>
#include<fstream>
using namespace std;

class SSDAdapter : public SSDInterface {
public:
	SSDAdapter() {}

	bool read(int LBA) override {
		string cmd = "SSD.exe R " + to_string(LBA);
		int result = system(cmd.c_str());

		string filePath = "result.txt";
		ifstream inputFile(filePath);

		if (inputFile.is_open()) {
			string line;
			while (getline(inputFile, line)) {
				cout << line << endl;
			}
			inputFile.close();
			return true;
		}

		return false;
	}

	bool write(int LBA, string data) override {
		string cmd = "SSD.exe W " + to_string(LBA) + " " + data;
		int result = system(cmd.c_str());
		return result == 0 ? true : false;
	}
};