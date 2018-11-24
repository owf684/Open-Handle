#pragma once

#include <string>
#include "handle.h"
#include "windows.h"
#include <cstring>
#include <TCHAR.H>
#include <cstdlib>
#include <iostream>
#include "MMsystem.h"
#include "WinUser.h"
#include <commctrl.h>
#include "MMsystem.h"


using namespace std;
class keyboard
{
public:
	void setArrowkeys();
	void setWASD();
	void setMedia();
	void setMario();
	void setWord();
	void setMacro(int i, char hexValue);
	void stringtoHexScancode(handle& hexFromFile);

	char getU() { return uHex; }
	char getD() { return dHex; }
	char getL() { return lHex; }
	char getR() { return rHex; }
	char getC() { return cHex; }
	char getK() { return kHex; }
	char getMacro(int i) { return macro[i]; }
	char getAlpha(int Index) {
		return alphaHex[Index];
	}	
	
	string getHexString(int i) { return alphaHexstr[i]; }
	string getHexSet(int i) { return hexCodes[i]; }
	char getScanCodes(int i) { return scanCodes[i]; }
	LPCWSTR getLcmd(int HexVar) { return alphaHexLstr[HexVar]; }
	~keyboard();
	int getHexLocation(int index) { return hexLocation[index]; }
private:
	char uHex = '_', dHex = '_', lHex = '_', rHex = '_', cHex = '_', kHex = '_';
	char alphaHex[50] = {
						0x48,//UP ARROW 
						0x50,//DOWN ARROW
						0x4B,//LEFT ARROW 
						0x4D,//RIGHT ARROW
						0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1E, 0x1F, 0x20, //ALPHABET
						0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, //ALPHABET
						0x1C,//ENTER
						0x2A,//SHIFT L
						0x1D, //CTRL L
						0x33, //VOLUME UP
						0x21, //VOLUME DOWN
						0x7D, //PASTE
						0x7A, //UNDO
						0x36 //REDO
	}; //Expan to not just alphabet.
	LPCWSTR alphaHexLstr[50] {
		L"0x48",//UP ARROW 
			L"0x50",//DOWN ARROW
			L"0x4B",//LEFT ARROW 
			L"0x4D",//RIGHT ARROW
			L"0x10", L"0x11", L"0x12", L"0x13", L"0x14", L"0x15", L"0x16", L"0x17", L"0x18", L"0x19", L"0x1E", L"0x1F", L"0x20", //ALPHABET
			L"0x21", L"0x22", L"0x23", L"0x24", L"0x25", L"0x26", L"0x2C", L"0x2D", L"0x2E", L"0x2F", L"0x30", L"0x31", L"0x32", //ALPHABET
			L"0x1C",//ENTER
			L"0x2A",//SHIFT L
			L"0x1D", //CTRL L
			L"0x33", //VOLUME UP
			L"0x21", //VOLUME DOWN
			L"0x7D", //PASTE
			L"0x7A", //UNDO
			L"0x36" //REDO
};
	string alphaHexstr[50] = {
		"0x48",//UP ARROW 
		"0x50",//DOWN ARROW
		"0x4B",//LEFT ARROW 
		"0x4D",//RIGHT ARROW
		"0x10", "0x11", "0x12", "0x13", "0x14", "0x15", "0x16", "0x17", "0x18", "0x19", "0x1E", "0x1F", "0x20", //ALPHABET
		"0x21", "0x22", "0x23", "0x24", "0x25", "0x26", "0x2C", "0x2D", "0x2E", "0x2F", "0x30", "0x31", "0x32", //ALPHABET
		"0x1C",//ENTER
		"0x2A",//SHIFT L
		"0x1D", //CTRL L
		"0x33", //VOLUME UP
		"0x21", //VOLUME DOWN
		"0x7D", //PASTE
		"0x7A", //UNDO
		"0x36" //REDO
	};

	int hexLocation[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	
	LPCWSTR scanCodeComboBox[12] = { L"_",L"_",L"_",L"_",L"_",L"_", L"_",L"_",L"_",L"_",L"_",L"_" };
	char scanCodes[12] = {'_','_','_','_','_','_','_','_','_','_','_', '_' }; //scan codes used for gesture
	string hexCodes[12]{"_","_","_","_","_","_","_","_","_","_","_", "_"};
	char macro[40];
};

