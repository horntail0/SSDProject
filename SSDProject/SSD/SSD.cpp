#include "File.cpp"
#include <string>

using namespace std;

const int SUCCESS = 1;
const int FAIL = -1;
const string DEFAULT = "0x00000000";

struct Buffer
{
	int start;
	int end;
	string data;
};

class SSD
{
public:
	void setFile(IFile* file_)
	{
		file = file_;
	}

	int isHex(char ch)
	{
		if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F'))
			return SUCCESS;

		return FAIL;
	}

	int checkInvalidHexData(string data)
	{
		if (data.length() != 10)
			return FAIL;

		if (data[0] != '0' || data[1] != 'x')
			return FAIL;

		for (int i = 2; i < 10; i++)
		{
			if (isHex(data[i]) == FAIL)
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

	void fastRead(int lba)
	{

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

	void erase(int lba, int size)
	{
		file->erase(lba, size);
	}

	void writeBuffer(int lba, string data)
	{
		if (checkInvalidWriteArg(lba, data) == FAIL)
			return;

		buf.push_back(Buffer{ lba, lba, data });
	}

	void eraseBuffer(int lba, int size)
	{
		buf.push_back(Buffer{ lba, size, DEFAULT });
	}

	void flush()
	{
	}

//private:
	IFile* file;
	vector<Buffer> buf;
	
	void fastWrite(Buffer now)
	{
		buf.push_back(now);

		if (buf.size() == 1)
			return;

		const int DELETE = -1;
		int prev = buf.size() - 2;
		int last = buf.size() -1;

		if(isConsecutive(buf[prev], buf[last]))
			buf[prev].start = DELETE;
		for (int i = prev; i >= 0; --i)
		{
			if (isDuplicated(buf[i], buf[last]))
				buf[i].start = DELETE;
		}

		vector<Buffer> tmp;
		for (int i = 0; i < buf.size(); ++i)
		{
			if (buf[i].start != DELETE)
				tmp.push_back(buf[i]);
		}
		swap(tmp, buf);
	}

	bool isDuplicated(Buffer prev, Buffer last)
	{
		if (last.start <= prev.start && prev.end <= last.end)
			return true;
		return false;
	}

	bool isConsecutive(Buffer &prev, Buffer &last)
	{
		if (prev.data != last.data)
			return false;

		if (prev.end + 1 == last.start)
		{
			last.start = prev.start;
			return true;
		}
		if (last.end + 1 == prev.start)
		{
			last.end = prev.end;
			return true;
		}

		return false;
	}
};