#include "File.cpp"
#include <string>

using namespace std;

class SSD 
{
public:
	void setFile(IFile* file_) 
	{
		file = file_;
	}

	void write(int lba, string data)
	{
		file->write(lba, data);
	}
private:
	IFile* file;
};