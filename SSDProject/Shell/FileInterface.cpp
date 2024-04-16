#include <string>
using namespace std;

class FileInterface
{
public:
	virtual string ReadfromNAND(int LBA) = 0;
	virtual void WritetoNAND(int LBA, string data) = 0;
};