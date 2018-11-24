#pragma once
#include <string>
using namespace std;
class handle
{
public:
	handle() noexcept;
	~handle();
	string getDefaultHex(int i) { return defaultCommands[i]; }
	string getReadHex(int i) { return newCommands[i]; }
	void setHex(int i, string hexValue) { newCommands[i] = hexValue; }

private:
	string defaultCommands[12];
	string newCommands[12] = {"0","1","2","3","4","5","6","7","8","9","10","11"};
};

