#include "File.cpp"
#include <string>
#include <vector>

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
		cmdCnt++;

		// Do optimize cmd buf

		if (cmdCnt >= 10)
			flush(); //do flush


	}

	void eraseBuffer(int lba, int size)
	{
		buf.push_back(Buffer{ lba, (lba + size - 1) > 99 ? 99 : (lba + size - 1), DEFAULT });
		cmdCnt++;

		if (cmdCnt >= 10)
			flush(); //do flush

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
};