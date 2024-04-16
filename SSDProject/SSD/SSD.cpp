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

	void read(int lba) 
	{
		if (lba < 0 || lba > 99)
		{
			//error
			return;
		}
		file->read(lba);
	}

	void write(int lba, string data)
	{
		if (lba < 0 || lba > 99)
			return;

		file->write(lba, data);
	}

private:
	IFile* file;
};