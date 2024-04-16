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

		if (data.length() != 10)
			return;

		if (data[0] != '0' || data[1] != 'x')
			return;

		for (int i = 2; i < 10; i++)
		{
			if (data[i] >= '0' && data[i] <= '9')  
				continue;
			if (data[i] >= 'A' && data[i] <= 'F')
				continue;
			return;
		}

		file->write(lba, data);
	}

private:
	IFile* file;
};