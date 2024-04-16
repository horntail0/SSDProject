#include <string>
using namespace std;

class SSDInterface {
public:
	virtual string read(int LBA) = 0;
	virtual void write(int LBA, string data) = 0;
};