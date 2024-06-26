#include "File.cpp"
#include <string>
#include <vector>

using namespace std;

const int SUCCESS = 1;
const int FAIL = -1;
const int DELETE = -2;
const int BUFFER_FLUSH_CNT = 10;

struct CmdBuffer
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
		openCmdBuffer();
	}

	void saveFile()
	{
		saveCmdBuffer();
	}

	void read(int lba)
	{
		if (checkLba(lba) == FAIL)
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

		fastWrite(CmdBuffer{ lba, lba, data });
		cmdCnt++;

		if (cmdCnt >= BUFFER_FLUSH_CNT)
			flush();
	}

	void eraseBuffer(int lba, int size)
	{
		fastWrite(CmdBuffer{ lba, (lba + size - 1) > 99 ? 99 : (lba + size - 1), DEFAULT_DATA });
		cmdCnt++;

		if (cmdCnt >= BUFFER_FLUSH_CNT)
			flush();
	}

	void flush()
	{
		vector<string> output = RunCmdBuf();
		file->writeBufToFile(NAND_FILE, output);
		cmdCnt = 0;
		cmdBuf.clear();
	}

private:
	IFile* file;
	vector<CmdBuffer> cmdBuf;
	int cmdCnt = 0;

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
		if (checkLba(lba) == FAIL)
			return FAIL;

		if (checkInvalidHexData(data) == FAIL)
			return FAIL;

		return SUCCESS;
	}

	int checkLba(int lba)
	{
		if (lba < 0 || lba >= DISK_SIZE)
			return FAIL;
		return SUCCESS;
	}

	vector<string> RunCmdBuf()
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
		for (int i = (int)cmdBuf.size() - 1; i >= 0; --i)
		{
			if (cmdBuf[i].start <= lba && lba <= cmdBuf[i].end)
			{
				file->read(cmdBuf[i].data);
				return SUCCESS;
			}
		}

		return FAIL;
	}

	void fastWrite(CmdBuffer buffer)
	{
		cmdBuf.push_back(buffer);

		if (cmdBuf.size() == 1)
			return;

		int last = (int)cmdBuf.size() - 1;
		int prev = (int)cmdBuf.size() - 2;

		if (isConsecutive(cmdBuf[prev], cmdBuf[last]))
			cmdBuf[prev].start = DELETE;
		for (int i = prev; i >= 0; --i)
		{
			if (isDuplicated(cmdBuf[i], cmdBuf[last]))
				cmdBuf[i].start = DELETE;
		}
    
		deleteCommand();
	}

	bool isDuplicated(CmdBuffer prev, CmdBuffer last)
	{
		if (last.start <= prev.start && prev.end <= last.end)
			return true;
		return false;
	}

	bool isConsecutive(CmdBuffer& prev, CmdBuffer& last)
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
		vector<CmdBuffer> tmp;
		for (int i = 0; i < cmdBuf.size(); ++i)
		{
			if (cmdBuf[i].start != DELETE)
				tmp.push_back(cmdBuf[i]);
		}
		swap(tmp, cmdBuf);
	}

	vector<string> splitBySpace(const string& str)
	{
		vector<string> words;
		string word;
		for (char ch : str)
		{
			if (ch == ' ')
			{
				if (!word.empty())
				{
					words.push_back(word);
					word.clear();
				}
			}
			else
			{
				word += ch;
			}
		}
		if (!word.empty())
		{
			words.push_back(word);
		}
		return words;
	}

	void openCmdBuffer()
	{
		ifstream file("CmdBuffer.txt");
		string line;
		if (file.is_open())
		{
			if (getline(file, line))
				cmdCnt = stoi(line);

			while (getline(file, line))
			{
				vector<string> words = splitBySpace(line);
				cmdBuf.push_back(CmdBuffer{ stoi(words[0]), stoi(words[1]), words[2]});
			}
			file.close();
		}
	}

	void saveCmdBuffer()
	{
		string data = to_string(cmdCnt) + "\n";
		for (int i = 0; i < cmdBuf.size(); ++i)
		{
			data = data + to_string(cmdBuf[i].start) + " " + to_string(cmdBuf[i].end) + " " + cmdBuf[i].data + "\n";
		}
		file->writeFile("CmdBuffer.txt", data);
	}
};
