#ifndef UNICODE
#define UNICODE
#define ID_BUTTON1 0x8801
#define ID_BUTTON2 0x8802
#define ID_BUTTON3 0x8803
#define ID_BUTTON4 0X8804
#define ID_BUTTON5 0X8805
#define ID_BUTTON6 0X8806
#define IDC_COMBOBOX_TEXT 1000
#define IDC_COMBOBOX_TEXT2 1001
#define STATUS_PORT 0X9901
#define HANDLE_STATUS 0x9902
#define HANDLE_LINK 0X9903
#define QWERTY_KEYBOARD 0X9904
#define QWERTY_KEYBOARD2 0X9905
#define TEXT_ENTRY2 0X9906
#define GEST1 0X9907 
#define GEST2 0X9908
#define GEST3 0X9909
#define GEST4 0X9910
#define GEST5 0X9911
#define GEST6 0X9912
#define GEST7 0X9913
#define GEST8 0X9914
#define GEST9 0X9915
#define GEST10 0x9916
#define GEST11 0x9917
#define GEST12 0x9918
#define GEST13 0x9919
#define DONE_EDIT 0X9921

#pragma warning(disable : 4996)

#endif 

#include <Windows.h>
#include <WinUser.h>
#include "Cport.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include "mode.h"
#include "keyboard.h"
#include <commctrl.h>
#include "resource.h"
#include "MMsystem.h"
#include "tchar.h"
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "handle.h"
#include "CharCuSender.h"
using namespace std;






////------------Scan Code Data Base Display text--------///////
LPCWSTR alphaHexLstr[100]{
	L"Up Arrow",//UP ARROW 
	L"Down Arrow",//DOWN ARROW
	L"Left Arrow",//LEFT ARROW 
	L"Right Arrow",//RIGHT ARROW
	L"Q", L"W", L"E", L"R", L"T", L"Y", L"U", L"I", L"O", L"P", L"A", L"S", L"D", //ALPHABET
	L"F", L"G", L"H", L"J", L"K", L"L", L"Z", L"X", L"C", L"V", L"B", L"N", L"M", //ALPHABET
	L"ENTER",//ENTER
	L"SHIFT",//SHIFT L
	L"CTRL", //CTRL L
	L"Vol Up", //CUT
	L"Vol Down", //COPY
	L"PASTE", //PASTE
	L"UNDO", //UNDO
	L"REDO" //REDO

};
////------------Scan Code Data Base Display text--------///////



//**Variable Declarations for Port Connections**//
HANDLE hComm; //For Port
DCB dcbSerialParams; //port properties
COMMTIMEOUTS timeouts; //time out properties
string Status { 0 }; //used for error checking
bool errorCheck; bool change[12] = { false, false, false, false, false, false, false, false, false, false,false,false};
char comInput; bool portSelected = false;
int moveGUI = 0;
HBITMAP bitmap;
//=============================================//

//**Mouse Variables**//
int mouseSpeed; int num = 0;
INPUT mouse;
//=============================================//
//**Mode Variables**//
int ModeIndex, SubModeIndex = 0; int modeCount; int cmdIndex[12];
LPCTSTR modefound[10] = { L"mode 1", L"mode 2", L"mode 3", L"mode 4", L"mode 5", L"mode 6", L"mode 7", L"mode 8", L"mode 9", L"mode 10" };
LPCSTR modeSelected[10] = { "mode 1", "mode 2", "mode 3", "mode 4", "mode 5", "mode 6", "mode 7", "mode 8", "mode 9", "mode 10" };
string modeFiles[10] = { "mode1.txt", "mode2.txt", "mode3.txt", "mode4.txt", "mode5.txt", "mode6.txt", "mode7.txt", "mode8.txt", "mode9.txt", "mode10.txt" };

//=============================================//
//**Keyboard Variables**//
INPUT keys, secondKeys, thirdKeys, firstKeys; bool keySelected = false;
keyboard Keymode; keyboard scanCodeDataBase; handle GestureScanCode;
//=============================================//
//*WIN API variables 
int userInput;
LPSTR *TextSave[20];
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND button, button1, button2, button3, button4, button5, button6; HWND TextEntry, TextEntry2, dropMenu, dropMenu2, portStatus, handleStatus, handleStatus1, qwertyKeyboard, qwertyKeyboard2;
HWND gesture[12]; HWND scDb[12]; HWND currentCmd[12]; HWND editButtons[12];
HWND handleLogo;
//=============================================//
//*stream variables 
string text;
char test2[256];
ifstream readMode;
ofstream writeMode;
string readCmd[12];
#pragma warning(suppress: 28251)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Open Handle";

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;				
	wc.lpszClassName = CLASS_NAME;
	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		10,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Open Handle",    // Window text
		WS_OVERLAPPED | WS_SYSMENU | SW_SHOWNORMAL,            // Window style

										// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT,600, 400,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);
	
	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow); //nCmdShow

	//Run the message loop.
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_CREATE:
	{
		bitmap = (HBITMAP) LoadImage(NULL,L"Bitmap2.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

	updateGUI:
		handleLogo = CreateWindowA("STATIC", NULL,
			WS_VISIBLE | WS_CHILD | SS_BITMAP,
			250 - moveGUI, -20, 100, 100,
			hwnd, NULL, NULL, NULL);
		button = CreateWindowA("BUTTON", "Open Handle",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			200-moveGUI, 250, 200, 20,
			hwnd, (HMENU)ID_BUTTON3, NULL, NULL);
		portStatus = CreateWindowA("STATIC", "link handle",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			250-moveGUI, 125, 100, 25,
			hwnd, (HMENU)HANDLE_LINK, NULL, NULL);
		handleStatus = CreateWindowA("STATIC", "handle not active",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			200-moveGUI, 275, 200, 20,
			hwnd, (HMENU)HANDLE_STATUS, NULL, NULL);
		button2 = CreateWindowA("BUTTON", "Select Port",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			200-moveGUI, 50, 200, 20,
			hwnd, (HMENU)ID_BUTTON1, NULL, NULL);
		button3 = CreateWindowA("BUTTON", "Close Port",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			200-moveGUI, 100, 200, 20,
			hwnd, (HMENU)ID_BUTTON2, NULL, NULL);
		TextEntry = CreateWindowA("EDIT", "\\\\.\\COM",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			260- moveGUI, 75, 75, 20,
			hwnd, (HMENU)2, NULL, NULL);
		dropMenu = CreateWindowA("COMBOBOX",NULL,
		WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_VSCROLL,
			200- moveGUI,150,100,100,
			hwnd,
			(HMENU)IDC_COMBOBOX_TEXT, NULL,
			NULL);
		dropMenu2 = CreateWindowA("COMBOBOX", NULL,
			WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_VSCROLL,
			300- moveGUI, 150, 100, 100,
			hwnd,
			(HMENU)IDC_COMBOBOX_TEXT2, NULL,
			NULL);

		SendMessage(handleLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);
		SendMessage(dropMenu, CB_ADDSTRING, 0, (LPARAM) L"Mouse Mode" );
		SendMessage(dropMenu, CB_ADDSTRING, 0, (LPARAM) L"KeyBoard Mode");
		SendMessage(dropMenu, CB_ADDSTRING, 0, (LPARAM) L"Macro Mode");
		SendMessage(dropMenu, CB_ADDSTRING, 0, (LPARAM) L"Custom Modes");
	}
	break;

	case WM_DESTROY:
	{
		if (portSelected == true) { CloseHandle(hComm);
		}

		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);	
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
	}
	return 0;
	case WM_COMMAND:
	{

		//--------------------Slection Change In Combo box1---------------------///
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == IDC_COMBOBOX_TEXT)
		{
			ModeIndex = (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);

			if (ModeIndex == 0)
			{
				for (int deleteString = 0; deleteString < 20; deleteString++)
				{
					SendMessage(dropMenu2, CB_DELETESTRING, 0, 0);
				}
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Speed: 2");
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Speed: 3");
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Speed: 5");
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Speed: 7");
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Speed: 10");
			}
			if (ModeIndex == 1)
			{
				for (int deleteString = 0; deleteString < 20; deleteString++)
				{
					SendMessage(dropMenu2, CB_DELETESTRING, 0, 0);
				}
				SendMessage(dropMenu2, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Arrow Keys");
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"WASD");
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Mario Mode");
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Media Mode");			
			}
			if (ModeIndex == 2)
			{
				for (int deleteString = 0; deleteString < 20; deleteString++)
				{
					SendMessage(dropMenu2, CB_DELETESTRING, 0, 0);
				}
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Visual Studio");
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Code Warrior");
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Fusion 360");
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Power Point");
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Fl Studio");
				SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM)L"Word Mode");
			}
			if (ModeIndex == 3) //CUSTOM MODES 
			{
				if (moveGUI == 0)
				{
					DestroyWindow(button5); DestroyWindow(button6);
					button5 = CreateWindowA("BUTTON", "EM",
						WS_VISIBLE | WS_CHILD | WS_BORDER,
						400 - moveGUI, 150, 30, 25,
						hwnd, (HMENU)ID_BUTTON5, NULL, NULL);
					button6 = CreateWindowA("BUTTON", "AM",
						WS_VISIBLE | WS_CHILD | WS_BORDER,
						170 - moveGUI, 150, 30, 25,
						hwnd, (HMENU)ID_BUTTON6, NULL, NULL);
				}
				for (int deleteString = 0; deleteString < 20; deleteString++)
				{
					SendMessage(dropMenu2, CB_DELETESTRING, 0, 0);
				}			
				//Open files untill error, which means file does not exist. Based on how many files are opened we can count the number of modes
				 modeCount = 0; //used for custom mode detection 
				bool open = true;
				while (open)
				{
					readMode.open(modeFiles[modeCount]);
					if (readMode.is_open() == true )
					{
						SendMessage(dropMenu2, CB_ADDSTRING, 0, (LPARAM) modefound[modeCount]);
						modeCount++;
						readMode.close();
					}
					else if (readMode.is_open() == false)
					{
						open = false;
						readMode.close();

					}					
				}			
			}
			if (ModeIndex != 3) { DestroyWindow(button5); DestroyWindow(button6); readMode.close(); }			
		}
		//--------------------Slection Change In Combo box1---------------------///		

		/////////////////////////////////////////////////////////////////////

		///---------------Track User Selection in Edit Mode--------------////
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == GEST1)
		{
			cmdIndex[0]=  (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
				change[0] = true;
		}
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == GEST2)
		{
			cmdIndex[1] = (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			change[1] = true;
		}
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == GEST3)
		{
			cmdIndex[2] = (int)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			change[2] = true;
		}
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == GEST4)
		{
			cmdIndex[3] = (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			change[3] = true;
		}
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == GEST5)
		{
			cmdIndex[4] = (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			change[4] = true;
		}
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == GEST6)
		{
			cmdIndex[5] = (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			change[5] = true;
		}
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == GEST7)
		{
			cmdIndex[6] = (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			change[6] = true;
		}
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == GEST8)
		{
			cmdIndex[7] = (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			change[7] = true;
		}
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == GEST9)
		{
			cmdIndex[8] = (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			change[8] = true;
		}
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == GEST10)
		{
			cmdIndex[9] = (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			change[9] = true;
		}
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == GEST11)
		{
			cmdIndex[10] = (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			change[10] = true;
		}
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == GEST12)
		{
			cmdIndex[11] = (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			change[11] = true;
		}
		//////////////////////////////////////////////////////////////////////


		/////////------------------Sub Mode Selection--------------//////////
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == IDC_COMBOBOX_TEXT2)
		{
			SubModeIndex = (int) SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			//Mouse mode, setting Speed of mouse cursos
			if (ModeIndex == 0) 
			{
				if      (SubModeIndex == 0) {mouseSpeed = 2;} 
				else if (SubModeIndex == 1) {mouseSpeed = 3;}
				else if (SubModeIndex == 2)	{mouseSpeed = 5;}
				else if (SubModeIndex == 3) {mouseSpeed = 7;}
				else if (SubModeIndex == 4) {mouseSpeed = 10;}
			}
			//Mouse mode, setting Speed of mouse cursos

			//Edit mode, reading appropriate data into variable
			if (ModeIndex == 3)
			{
		bool doneRead = true; int cmdCount = 0;
		readMode.close();readMode.open(modeFiles[SubModeIndex]);
					while (doneRead)
					{
						readMode >> text; //begin reading mode files 
						if (text!= "END")
						{							
							GestureScanCode.setHex(cmdCount, text);
							cmdCount++;
						}
						if (text == "END" || cmdCount == 12) //Every mode file ends with AN END. 12 == cmdCount safety for memory access violation
						{
							doneRead = false;
							readMode.close();
						}					
					}
					scanCodeDataBase.stringtoHexScancode(GestureScanCode); //Convert read strings into char variables 
					readMode.close();

			}
		}
		/////////------------------Sub Mode Selection--------------//////////


		////////------------------Button Actions------------------///////////
		switch (LOWORD(wParam))
		{
		case ID_BUTTON1: //Select Port Button 
		{
			int storePort = 0;
			storePort = GetWindowTextA(TextEntry, (LPSTR)&TextSave[0], 20); //Save Text
			comInitialize(hComm, (LPCSTR)&TextSave); //Used Save Text to open Desired port
			errorCheck = checkPort(hComm);
			if (errorCheck == true && portSelected == false)
			{

				SetDlgItemText(hwnd, HANDLE_LINK, L"Unable to Link"); //notify user
				portSelected = false;
				PlaySoundA("Unable to Link", NULL, SND_ASYNC); //change sound?

			}
			if (portSelected == false && errorCheck == false)
			{
				portSelected = true;
				PlaySoundA("Handle Linked", NULL, SND_ASYNC); //notify user
				SetDlgItemText(hwnd, HANDLE_LINK, L"Handle Linked");
				setupDCB(hComm, dcbSerialParams);
				setupTimeouts(timeouts);
			}
			if (errorCheck == true && portSelected == true)
			{
				CloseHandle(hComm);
				portSelected = false;
				setupDCB(hComm, dcbSerialParams);
				setupTimeouts(timeouts);
				SetDlgItemText(hwnd, HANDLE_LINK, L"Handle lbnb");

			}
		}
		break;


		case ID_BUTTON2: //Close Port Button 
		{	if (portSelected == false) {SetDlgItemText(hwnd, HANDLE_LINK, L"no link"); PlaySoundA("No Link", NULL, SND_ASYNC); }


		if (portSelected == true)
		{
			CloseHandle(hComm);
			//int storePort = 0;
			//storePort = GetWindowTextA(TextEntry, (LPSTR)&TextSave[0], 20);
			SetDlgItemText(hwnd, HANDLE_LINK, L"Unlinked");
			PlaySoundA("Unlinked", NULL, SND_ASYNC);

			portSelected = false;
		}
		}
		break;

		case ID_BUTTON5: //Edit Mode Button 
		{
			moveGUI = 150;
			//destroy old windows, build static text, comboboxes & populate them, recreate and move windows to the side
			DestroyWindow(button); DestroyWindow(portStatus);
			DestroyWindow(handleStatus); DestroyWindow(button2);
			DestroyWindow(button3); DestroyWindow(TextEntry);
			DestroyWindow(dropMenu); DestroyWindow(dropMenu2);
			DestroyWindow(button5); DestroyWindow(button6);
			DestroyWindow(handleLogo);
			gesture[0] = CreateWindowA("STATIC", "PALM UP",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				260, 0, 120, 25,
				hwnd, NULL, NULL, NULL);
			gesture[1] = CreateWindowA("STATIC", "PALM DOWN",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				260, 25, 120, 25,
				hwnd, NULL, NULL, NULL);
			gesture[2] = CreateWindowA("STATIC", "PALM LEFT",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				260, 50, 120, 25,
				hwnd, NULL, NULL, NULL);
			gesture[3] = CreateWindowA("STATIC", "PALM RIGHT",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				260, 75, 120, 25,
				hwnd, NULL, NULL, NULL);
			gesture[4] = CreateWindowA("STATIC", "INDEX",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				260, 100, 120, 25,
				hwnd, NULL, NULL, NULL);
			gesture[5] = CreateWindowA("STATIC", "MIDDLE",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				260, 125, 120, 25,
				hwnd, NULL, NULL, NULL);
			gesture[6] = CreateWindowA("STATIC", "THUMB",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				260, 150, 120, 25,
				hwnd, NULL, NULL, NULL);
			gesture[7] = CreateWindowA("STATIC", "INDEX+MIDDLE",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				260, 175, 120, 25,
				hwnd, NULL, NULL, NULL);
			gesture[8] = CreateWindowA("STATIC", "INDEX+THUMB",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				260, 200, 120, 25,
				hwnd, NULL, NULL, NULL);
			gesture[9] = CreateWindowA("STATIC", "THUMB+MIDDLE",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				260, 225, 120, 25,
				hwnd, NULL, NULL, NULL);
			gesture[10] = CreateWindowA("STATIC", "M+R",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				260, 250, 120, 25,
				hwnd, NULL, NULL, NULL);
			gesture[11] = CreateWindowA("STATIC", "M+L",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				260, 275, 120, 25,
				hwnd, NULL, NULL, NULL);


			editButtons[0] = CreateWindowA("STATIC", modeSelected[SubModeIndex],
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				395, 325, 60, 25,
				hwnd, NULL, NULL, NULL);
			editButtons[1] = CreateWindowA("BUTTON", "Done Editing", //Done Editing Button
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				290, 325, 100, 25,
				hwnd, (HMENU)DONE_EDIT, NULL, NULL);


			scDb[0] = CreateWindowA("COMBOBOX", NULL,
				WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | WS_VSCROLL,
				380, 0, 100, 100,
				hwnd,
				(HMENU)GEST1, NULL,
				NULL);

			scDb[1] = CreateWindowA("COMBOBOX", NULL,
				CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
				380, 25, 100, 100,
				hwnd,
				(HMENU)GEST2, NULL,
				NULL);
			scDb[2] = CreateWindowA("COMBOBOX", NULL,
				CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
				380, 50, 100, 100,
				hwnd,
				(HMENU)GEST3, NULL,
				NULL);
			scDb[3] = CreateWindowA("COMBOBOX", NULL,
				CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
				380, 75, 100, 100,
				hwnd,
				(HMENU)GEST4, NULL,
				NULL);
			scDb[4] = CreateWindowA("COMBOBOX", NULL,
				CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
				380, 100, 100, 100,
				hwnd,
				(HMENU)GEST5, NULL,
				NULL);
			scDb[5] = CreateWindowA("COMBOBOX", NULL,
				CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
				380, 125, 100, 100,
				hwnd,
				(HMENU)GEST6, NULL,
				NULL);
			scDb[6] = CreateWindowA("COMBOBOX", NULL,
				CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
				380, 150, 100, 100,
				hwnd,
				(HMENU)GEST7, NULL,
				NULL);
			scDb[7] = CreateWindowA("COMBOBOX", NULL,
				CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
				380, 175, 100, 100,
				hwnd,
				(HMENU)GEST8, NULL,
				NULL);
			scDb[8] = CreateWindowA("COMBOBOX", NULL,
				CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
				380, 200, 100, 100,
				hwnd,
				(HMENU)GEST9, NULL,
				NULL);
			scDb[9] = CreateWindowA("COMBOBOX", NULL,
				CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
				380, 225, 100, 100,
				hwnd,
				(HMENU)GEST10, NULL,
				NULL);
			scDb[10] = CreateWindowA("COMBOBOX", NULL,
				CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
				380, 250, 100, 100,
				hwnd,
				(HMENU)GEST11, NULL,
				NULL);
			scDb[11] = CreateWindowA("COMBOBOX", NULL,
				CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
				380, 275, 100, 100,
				hwnd,
				(HMENU)GEST12, NULL,
				NULL);
			int addCmd = 0, nextBox = 0; //Used to populate the comboboxes in edit commands
			for (nextBox = 0; nextBox < 12; nextBox++)
			{

				for (addCmd = 0; addCmd < 38; addCmd++)
				{
					SendMessage(scDb[nextBox], CB_ADDSTRING, 0, (WPARAM)alphaHexLstr[addCmd]);

				}

				SendMessage(scDb[nextBox], CB_SETCURSEL, scanCodeDataBase.getHexLocation(nextBox), 0);
			}



			goto updateGUI;

		}
		break;

		case DONE_EDIT: //Done Edit button
		{
			DestroyWindow(button); DestroyWindow(portStatus);
			DestroyWindow(handleStatus); DestroyWindow(button2);
			DestroyWindow(button3); DestroyWindow(TextEntry);
			DestroyWindow(dropMenu); DestroyWindow(dropMenu2);
			DestroyWindow(button5); DestroyWindow(button6);  DestroyWindow(handleLogo);
			for (int deleteBox = 0; deleteBox <= 11; deleteBox++)
			{
				DestroyWindow(scDb[deleteBox]);
				DestroyWindow(gesture[deleteBox]);

			}
			DestroyWindow(editButtons[0]); DestroyWindow(editButtons[1]);
			moveGUI = 0;
			int insertHex = 0; int changeCheck = 0;
			writeMode.open(modeFiles[SubModeIndex]);
			//need to set indicies for the file write.
			//do this by checking if there was a change in the combobox[n]
			//if there was a change then writeMODE FROM cmdIndex
			//if not then write mode from keyboardindex
			while (insertHex < 12)
			{
				if (change[changeCheck] == true) //Will overwrite old text in text box with new text
				{
					writeMode << scanCodeDataBase.getHexString(cmdIndex[insertHex]);
					insertHex++;
					writeMode << "\n";
				}
				if (change[changeCheck] == false)//If no change detected old text overwritten with the same text
				{
					writeMode << scanCodeDataBase.getHexSet(insertHex) << "\n";
					insertHex++;
				}
				changeCheck++;
			}
			writeMode << "END"; //END stamp
			writeMode.close(); //Close File			
			for (int reset = 0; reset < 12; reset++)
			{
				change[reset] = false;
			}
			goto updateGUI;
		}
		break;

		case ID_BUTTON3: //Open Handle Buton
		{

			switch (ModeIndex) //First ComboBox Selection
			{

				/////////////////////Mouse Mode///////////////////////////////////////////
			case 0:
			{
				if (portSelected == false) { SetDlgItemText(hwnd, HANDLE_STATUS, L"please link handle first"); 	PlaySoundA("Please Link Handle First", NULL, SND_ASYNC);
				}
				if (portSelected == true)
				{
					PlaySoundA("Mouse Mode Selected", NULL, SND_ASYNC);
				mouseMode:

					MSG msg = {};
					setupMouseEvent(mouse);
					int x;// x = (int *) malloc(sizeof(x)); 
					int y;// y = (int *) malloc(sizeof(y));
					int xBound;// xBound = (int *)malloc(sizeof(xBound)); xBound = 0;
					int yBound;// yBound = (int *)malloc(sizeof(yBound)); yBound = 0;
					//xBound, yBound;
					centerMouse(xBound, yBound);
					x = xBound; y = yBound;
					 xBound *=  2; 
					 yBound *=  2;
					SetDlgItemText(hwnd, HANDLE_STATUS, L"Mouse Selected");
					ShowWindow(hwnd, SW_HIDE);

					while (!GetAsyncKeyState(VK_ESCAPE)) //PRESS R to exit loop and use GUI again
					{
						readPort(hComm, comInput);
						if (comInput != 'k') { leftClick(comInput); }
						if (comInput != 'c') { rightClick(comInput); }
						movePointer(x, y, comInput, mouseSpeed, hComm);
						checkBoundaries(x, y, xBound, yBound);
						//if (comInput == 'j'&& keySelected == false) { keySelected = true; goto keyMode; }
					}


				
					SetDlgItemText(hwnd, HANDLE_STATUS, L"Mode Off");
					ShowWindow(hwnd, SW_RESTORE); //maximize window when mode is turned off
					PlaySoundA("Mode Off", NULL, SND_ASYNC);
					//free(x); free(y); free(xBound); free(yBound);

				}
			}
			break;

			/////////////////////Mouse Mode///////////////////////////////////////////

			////////////////////////KeyBoard Mode//////////////////////////////////////
			case 1:
			{	if (portSelected == false) { SetDlgItemText(hwnd, HANDLE_STATUS, L"please link handle first"); PlaySoundA("Please Link Handle FIrst", NULL, SND_ASYNC);
			}
			if (portSelected == true) {
				PlaySoundA("Keyboard Mode Selected", NULL, SND_ASYNC);

				//set-up keyboard events
				setupKeyboardEvent(keys);
				setupKeyboardEvent(secondKeys);
				setupKeyboardEvent(thirdKeys);

				/////////////Setting character set for  chosen SubMode///////////
				//Arrow Keys
				if (SubModeIndex == 0) { Keymode.setArrowkeys(); SetDlgItemText(hwnd, HANDLE_STATUS, L"Arrow Keys Selected"); }
				//WASD
				if (SubModeIndex == 1) { Keymode.setWASD(); SetDlgItemText(hwnd, HANDLE_STATUS, L"WASD Selected"); }
				//Mario Mode
				if (SubModeIndex == 2) { Keymode.setMario(); SetDlgItemText(hwnd, HANDLE_STATUS, L"Mario Selected");  ShellExecute(0, 0, L"http://www.arcadeprehacks.com/game/17771/Super-Mario-Crossover-2.html", 0, 0, SW_SHOW); }
				//Media Mode 
				if (SubModeIndex == 3) { Keymode.setMedia(); SetDlgItemText(hwnd, HANDLE_STATUS, L"Media Selected"); }

				readPort(hComm, comInput); //Jump Start the While Loop
				ShowWindow(hwnd, SW_HIDE); //Minmizes Window Once Selected

				/////Begin Reading and Sending
				while (!GetAsyncKeyState(VK_ESCAPE)) //ESC to exit loop
				{
					readPort(hComm, comInput);
					sendCommand(comInput, keys, secondKeys, thirdKeys, Keymode, hComm);
				}
				/////Begin Reading and Sending
				comInput = 'Z'; //for reset
			}
			//Mazimizes Windows
			if (portSelected == true && comInput == 'Z')
			{
				SetDlgItemText(hwnd, HANDLE_STATUS, L"Mode Off");
				ShowWindow(hwnd, SW_RESTORE); //maximize window when mode is turned off
				PlaySoundA("Mode Off", NULL, SND_ASYNC);

			}
			}
			break;
			////////////////////////KeyBoard Mode//////////////////////////////////////

			////////////////////////Macro Mode/////////////////////////////////////////
			case 2:
			{
				if (portSelected == false) { SetDlgItemText(hwnd, HANDLE_STATUS, L"please link handle first");PlaySoundA("Please Link Handle First", NULL, SND_ASYNC);}
				else {
					PlaySoundA("Macro Mode Selected", NULL, SND_ASYNC);

					///SubMode Events 
					switch (SubModeIndex)
					{

						//-------------------Visual Studio mode-----------------------// 
					case 0:
					{
						setupKeyboardEvent(keys); setupKeyboardEvent(firstKeys); setupKeyboardEvent(secondKeys);  setupKeyboardEvent(thirdKeys);//set-up events
						keyboard *keyHex; keyHex = (keyboard *)malloc(sizeof(keyHex));
						keyHex->setMacro(0, 0x1D); /*CTRL l*/  keyHex->setMacro(1, 0X25); /*K*/  keyHex->setMacro(2, 0X2E);/*C*/ keyHex->setMacro(3, 0X16); /*U*/
						
						bool *pointer; pointer = (bool *) malloc(sizeof(pointer));  pointer = false;
						bool *rightArrow; rightArrow = (bool *)malloc(sizeof(rightArrow)); rightArrow = false;
						bool *leftArrow; leftArrow = (bool *)malloc(sizeof(leftArrow)); leftArrow = false;
						char tilt = '_';


						//minimzie window
						ShowWindow(hwnd, SW_HIDE);
						SetDlgItemText(hwnd, HANDLE_STATUS, L"Visual Studio selected");
						while (!GetAsyncKeyState(VK_ESCAPE))
						{
							readPort(hComm, comInput); //grab tilt
													   //reading index finger and hand tilt gesture
							if (comInput == 'r' || comInput == 'l' || comInput == 'y' || comInput == 'h' || comInput == 't' || comInput == 'g') { tilt = comInput; }

							readPort(hComm, comInput); //grab index reading

							//Comment Code
							if (((comInput == 'c' && tilt == 'r') || (comInput == 'c' && tilt == 'h') || (comInput == 'c' && tilt == 'y')) && rightArrow == (bool *) false)
							{
								pressDown(firstKeys, keyHex->getMacro(0)); pressDown(secondKeys, keyHex->getMacro(1)); pressDown(thirdKeys, keyHex->getMacro(2)); //laser Macro
								rightArrow = (bool *) true;
								leftArrow = (bool *) false;
							}
							//Uncomment Code
							if (((comInput == 'c' && tilt == 'l') || (comInput == 'c' && tilt == 't') || (comInput == 'c' && tilt == 'g')) && leftArrow == (bool *) false)
							{
								pressDown(keys, keyHex->getL());
								leftArrow = (bool *) true;
								rightArrow = (bool *) false;
								pressDown(firstKeys, keyHex->getMacro(0)); pressDown(secondKeys, keyHex->getMacro(1)); pressDown(thirdKeys, keyHex->getMacro(3)); //laser Macro

							}
							readPort(hComm, comInput); //grab index reading 

							if (comInput == 'C') //release keys all no event
							{
								leftArrow = (bool *) false;
								rightArrow = (bool *) false;
								releaseKey(firstKeys); releaseKey(secondKeys); releaseKey(thirdKeys);
							}

						}
						free(leftArrow); free(rightArrow); free(pointer); free(keyHex);
						ShowWindow(hwnd, SW_RESTORE); //maximize window when mode is turned off
						SetDlgItemText(hwnd, HANDLE_STATUS, L"Mode Off");
						PlaySoundA("Mode Off", NULL, SND_ASYNC);

					}
					break;
					//-------------------Visual Studio mode-----------------------// 


					//--------------------Power Point Mode-----------------------//
					case 3:
					{
						//variable declarations
						setupMouseEvent(mouse);
						int x, y, xBound, yBound, mouseSpeed = 20;
						char tilt = '_', lastCommand = '_';
						keyboard keyHex; keyHex.setArrowkeys();
						bool pointer = false, rightArrow = false, leftArrow = false;

						//setup Key inputs
						setupKeyboardEvent(keys); setupKeyboardEvent(firstKeys); setupKeyboardEvent(secondKeys);  setupKeyboardEvent(thirdKeys);

						//minimzie window
						ShowWindow(hwnd, SW_HIDE);
						SetDlgItemText(hwnd, HANDLE_STATUS, L"Power Point selected");

						while (!GetAsyncKeyState(VK_ESCAPE)) //ESC press resets 
						{


							//reading index finger and hand tilt gesture	
							readPort(hComm, comInput); //grab tilt			
							if (
								comInput == 'r' || //-- OVERCOMPENSATE FOR GLOVE SENSITIVITY 			
								comInput == 'l' ||
								comInput == 'y' ||
								comInput == 'h' ||
								comInput == 't' ||
								comInput == 'g'
								)
							{
								tilt = comInput;
							}



							readPort(hComm, comInput); //grab index reading

							///
							if ((
								(comInput == 'c' && tilt == 'r') ||  //Move Slide Right 
								(comInput == 'c' && tilt == 'h') ||
								(comInput == 'c' && tilt == 'y')) &&
								rightArrow == false)
							{
								pressDown(keys, keyHex.getR());
								rightArrow = true;
								leftArrow = false;
							}


							if (((comInput == 'c' && tilt == 'l') ||  //Move Slide Left
								(comInput == 'c' && tilt == 't') ||
								(comInput == 'c' && tilt == 'g'))
								&& leftArrow == false)
							{
								pressDown(keys, keyHex.getL());
								leftArrow = true;
								rightArrow = false;
							}
							///		
							readPort(hComm, comInput); //grab index reading 

							if (comInput == 'C') //release keys all no event
							{
								leftArrow = false;
								rightArrow = false;
								releaseKey(keys);
							}
							//Turning Laser On 

							//reading middle finger and hand tilt gesture
							readPort(hComm, comInput); //grab hand tilt

							if (comInput == 'r' ||  //OverCompensating for Glove Sensitivity 
								comInput == 'l' ||
								comInput == 'y' ||
								comInput == 'h')
							{
								tilt = comInput;
							}

							readPort(hComm, comInput); //grab middle reading

							if ((comInput == 'k' && tilt == 'r') ||
								(comInput == 'k' && tilt == 'y') ||
								(comInput == 'k' && tilt == 'h') &&
								pointer == false)
							{
								centerMouse(xBound, yBound); //Center laser 
								x = xBound; y = yBound;
								xBound = 2 * xBound; yBound = 2 * yBound;
								pressDown(firstKeys, 0X1D); pressDown(secondKeys, 0X2A); pressDown(thirdKeys, 0X19); //laser Macro
								pointer = true;
								goto movePointer;
							}

						movePointer:
							releaseKey(firstKeys); releaseKey(secondKeys); releaseKey(thirdKeys); //release macro
							while (pointer == true || !(GetAsyncKeyState(VK_ESCAPE)))
							{
								readPort(hComm, comInput);
								movePointer(x, y, comInput, mouseSpeed, pointer);
								checkBoundaries(x, y, xBound, yBound);

								if (comInput == 'j') {
									pressDown(firstKeys, 0X1D); pressDown(secondKeys, 0X2A); pressDown(thirdKeys, 0X19); //laser Macro
									pointer = false; //exit laser mode
								}
							}
						}
						ShowWindow(hwnd, SW_RESTORE); //maximize window when mode is turned off
						SetDlgItemText(hwnd, HANDLE_STATUS, L"Mode Off");
						PlaySoundA("Mode Off", NULL, SND_ASYNC);


					}

					break;
					//---------------------------------Power Point Mode----------------------------//

					//---------------------------------Keyboard Mode------------------------------//
					case 5:
					{
					
						//variable declarations
						setupMouseEvent(mouse);
						int x, y, mouseSpeed = 110;
						char tilt = '_', lastCommand = '_';
						keyboard keyHex; keyHex.setArrowkeys();
						bool pointer = false, rightTilt = false, leftTilt = false, middle = false, index = false, thumb = false, firstRow = true, secondRow = false, thirdRow = false, fourthRow = false;
						//setup Key inputs
						setupKeyboardEvent(keys); setupKeyboardEvent(firstKeys); setupKeyboardEvent(secondKeys);  setupKeyboardEvent(thirdKeys);
						//open on screen keyboard				
						SetCursorPos(1233, 748);
						leftClick('c');
						leftClick('C');
						SetCursorPos(165, 524); //Figure out how to automatically get these maybe?
						x = 165;
						y = 524;
						ShowWindow(hwnd, SW_HIDE);
						SetDlgItemText(hwnd, HANDLE_STATUS, L"Keyboard Mode Selected");
						while (!GetAsyncKeyState(VK_ESCAPE))
						{
							readPort(hComm, comInput);
							if (comInput == 'j' && keySelected == true) { keySelected = false; goto mouseMode; }
							if (comInput == 'b' && thumb == false) //Thumb
							{
								thumb = true;
								SetCursorPos(x, y);
								leftClick('c');
								leftClick('C');
								index = false;
								middle = false;
							}
							else if (comInput == 'B') { thumb = false; }

							if (comInput == 'c' && index == false)  //Index
							{
								index = true;
								SetCursorPos(x + 100, y);
								leftClick('c');
								leftClick('C');
								thumb = false;
								middle = false;
							}
							else if (comInput == 'C') { index = false; }

							if (comInput == 'k' && middle == false) //Middle 
							{
								middle = true;
								SetCursorPos(x + 200, y);
								leftClick('c');
								leftClick('C');
								thumb = false;
								index = false;
							}
							else if (comInput == 'K') { middle = false; }


							if (comInput == 'm' && rightTilt == false) //right tilt to scroll through keyboard in the +x direction
							{
								x = x + 280; //move to new set of characters 

								if (x > 1005 && secondRow == false && firstRow == true) //moving from 1st row into the 2nd row 
								{
									secondRow = true;
									firstRow = false;
									x = 190; y = 594;
								}

								if (x > 1030 && thirdRow == false && secondRow == true) //moving from 2nd row into the 3rd row 
								{
									thirdRow = true;
									secondRow = false;
									x = 170; y = 664;
								}
								if (x > 1010 && fourthRow == false && thirdRow == true) //moving from 3rd row into the 4th row 
								{
									secondRow = false;
									thirdRow = false;
									fourthRow = true;
									x = 170; y = 734;
								}

								if (x > 1010 && fourthRow == true && firstRow == false)
								{
									fourthRow = false;
									firstRow = true;
									x = 165; y = 524;

								}


								SetCursorPos(x, y);
								rightTilt = true;
							}
							else if (comInput == 'M' && rightTilt == true) { rightTilt = false; }


							if (comInput == 'n' && leftTilt == false) //left tilt to scroll through keyboard in the -x direction
							{


								x = x - 280;
								if (x < 165 && firstRow == true && fourthRow == false)
								{
									firstRow = false; fourthRow = true;
									x = 170; y = 734;
								}


								if (x < 190 && secondRow == true && firstRow == false) //moving from 2ndRow row into the first row 
								{
									secondRow = false;
									firstRow = true;
									x = 160; y = 524;
								}

								if (x < 179 && thirdRow == true && secondRow == false) //moving from 3rd row into the 2nd row 
								{
									thirdRow = false;
									secondRow = true;
									x = 190; y = 594;
								}
								if (x < 170 && fourthRow == true && thirdRow == false) //moving from 4th row into the 3rd row 
								{
									secondRow = false;
									thirdRow = true;
									fourthRow = false;
									x = 170; y = 664;
								}



								SetCursorPos(x, y);
								leftTilt = true;

							}
							else if (comInput == 'N' && leftTilt == true) { leftTilt = false; }

						}
						//movePointer(x, y, comInput, mouseSpeed, pointer);


					}
					break;
					//---------------------------------Keyboard Mode------------------------------//
					}
				}
			}
			////////////////////////Macro Mode/////////////////////////////////////////

			////////////////////////Edit Mode//////////////////////////////////////////

			case 3: //custome mode
			{
				if (portSelected == false) { SetDlgItemText(hwnd, HANDLE_STATUS, L"please link handle first");PlaySoundA("Please Link Handle First", NULL, SND_ASYNC);
				}
				else {
					SetDlgItemText(hwnd, HANDLE_STATUS, L"Custom Mode Selected");
					PlaySoundA("Custom Mode Selected", NULL, SND_ASYNC);

					ShowWindow(hwnd, SW_HIDE);
					setupKeyboardEvent(keys); setupKeyboardEvent(firstKeys); setupKeyboardEvent(secondKeys);  setupKeyboardEvent(thirdKeys);//set-up events
					readPort(hComm, comInput);
					while (!GetAsyncKeyState(VK_ESCAPE))
					{
						readPort(hComm, comInput);
						//----------------Palm Commands------------------------//
						//Palm-up
						sendChar('u', comInput, keys, scanCodeDataBase, 0, hComm);

						//Palm-down
						sendChar('d', comInput, keys, scanCodeDataBase, 1, hComm);

						//Palm-left
						sendChar('l', comInput, keys, scanCodeDataBase, 2, hComm);

						//Palm-right
						sendChar('r', comInput, keys, scanCodeDataBase, 3, hComm);


						//-----------------Finger Commands---------------------//
						//Index-Flex
						sendChar('c', comInput, keys, scanCodeDataBase, 4, hComm);

						//Middle-Flex
						sendChar('k', comInput, keys, scanCodeDataBase, 5, hComm);

						//Thumb-Flex
						sendChar('b', comInput, keys, scanCodeDataBase, 6, hComm);

						//---------------------Diaganols---------------//
						//Palm-up with left tilt
						sendChar2('t', comInput, keys, firstKeys, scanCodeDataBase, 0, 2, hComm);

						//palm-up with right tilt
						sendChar2('y', comInput, keys, firstKeys, scanCodeDataBase, 0, 3, hComm);

						//palm-down with left tilt
						sendChar2('g', comInput, keys, firstKeys, scanCodeDataBase, 1, 2, hComm);

						//palm-down with right tilt
						sendChar2('h', comInput, keys, firstKeys, scanCodeDataBase, 1, 3, hComm);
					}
					ShowWindow(hwnd, SW_RESTORE);
					SetDlgItemText(hwnd, HANDLE_STATUS, L"Mode Off");
					PlaySoundA("Mode Off", NULL, SND_ASYNC);

				}
			}
			break;
			////////////////////////////Edit Mode//////////////////////////////////////////


			break;
			}
		
		}
		break;

		case ID_BUTTON6: //Add Mode Button
		{
			writeMode.open(modeFiles[modeCount]);
			for (int write = 0; write < 12; write++)
			{
				writeMode << GestureScanCode.getDefaultHex(write);
				writeMode << "\n";
			}
			writeMode << "END";
			writeMode.close();
			

		}
		break;
		}
		////////------------------Button Actions------------------///////////
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}