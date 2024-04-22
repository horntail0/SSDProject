#include "File.cpp"
#include <string>
#include <vector>

using namespace std;

const int SUCCESS = 1;
const int FAIL = -1;

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

	void read(int lba)
	{
		if (lba < 0 || lba > 99)
			return;

		if (fastRead(lba) == SUCCESS)
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

		fastWrite(Buffer{ lba, lba, data });

	}

	void eraseBuffer(int lba, int size)
	{
		fastWrite(Buffer{ lba, (lba + size - 1) > 99 ? 99 : (lba + size - 1), DEFAULT_DATA });
	}

	void flush()
	{
		// do flush
		vector<string> output = RunCmdBuf(buf);

		file->writeBufToFile(NAND_FILE, output);
		
		cmdCnt = 0;
		buf.clear();
	}

private:
	IFile* file;
	vector<Buffer> buf;
	int cmdCnt = 0;
	const int DELETE = -1;

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

	vector<string> RunCmdBuf(vector<Buffer> cmdBuf)
	{
		vector<string> ret;

		ret = file->readFileToBuf(NAND_FILE);

		for (int j = 0; j < cmdBuf.size(); j++)
		{
			int s = cmdBuf[j].start;
			int e = cmdBuf[j].end;
			for (int k = s; k <= e; k++)
			{
				ret[k] = cmdBuf[j].data;
			}
		}

		return ret;
	}

	int fastRead(int lba)
	{
		for (int i = buf.size() - 1; i >= 0; --i)
		{
			if (buf[i].start <= lba && lba <= buf[i].end)
			{
				file->read(buf[i].data);
				return SUCCESS;
			}
		}

		return FAIL;
	}

	void fastWrite(Buffer buffer)
	{
		buf.push_back(buffer);
		if (buf.size() == 1)
			return;

		int last = buf.size() - 1;
		int prev = buf.size() - 2;

		if (isConsecutive(buf[prev], buf[last]))
			buf[prev].start = DELETE;
		for (int i = prev; i >= 0; --i)
		{
			if (isDuplicated(buf[i], buf[last]))
				buf[i].start = DELETE;
		}
		deleteCommand();

		cmdCnt++;
		if (cmdCnt >= 10)
			flush(); //do flush
	}

	bool isDuplicated(Buffer prev, Buffer last)
	{
		if (last.start <= prev.start && prev.end <= last.end)
			return true;
		return false;
	}

	bool isConsecutive(Buffer& prev, Buffer& last)
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

	void deleteCommand()
	{
		vector<Buffer> tmp;
		for (int i = 0; i < buf.size(); ++i)
		{
			if (buf[i].start != DELETE)
				tmp.push_back(buf[i]);
		}
		swap(tmp, buf);
	}
};