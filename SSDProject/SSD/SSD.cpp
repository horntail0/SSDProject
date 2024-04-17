#include "File.cpp"
#include <string>

using namespace std;

const int SUCCESS = 1;
const int FAIL = -1;

class SSD
{
public:
	void setFile(IFile* file_)
	{
		file = file_;
	}

	int checkInvalidHexData(string data)
	{
		if (data.length() != 10)
			return FAIL;

		if (data[0] != '0' || data[1] != 'x')
			return FAIL;

		for (int i = 2; i < 10; i++)
		{
			if (data[i] >= '0' && data[i] <= '9')
				continue;
			if (data[i] >= 'A' && data[i] <= 'F')
				continue;
			return FAIL;
		}

		return SUCCESS;
	}

	int checkInvalidWriteArg(int lba, string data)
	{
		if (lba < 0 || lba > 99)
			return FAIL;

		if (checkInvalidHexData(data) == FAIL)
			return FAIL;

		return SUCCESS;
	}

	void read(int lba)
	{
		if (lba < 0 || lba > 99)
			return;

		file->read(lba);
	}

	void write(int lba, string data)
	{
		if (checkInvalidWriteArg(lba, data) == FAIL)
			return;

		file->write(lba, data);
	}

private:
	IFile* file;
};