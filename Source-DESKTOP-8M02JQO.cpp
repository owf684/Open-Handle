#ifndef UNICODE
#define UNICODE
#define ID_BUTTON1 0x8801
#define ID_BUTTON2 0x8802
#define ID_BUTTON3 0x8803
#define IDC_COMBOBOX_TEXT 1000
#define IDC_COMBOBOX_TEXT2 1001
#define STATUS_PORT 0X9901
#define HANDLE_STATUS 0x9902
#define HANDLE_LINK 0X9903
#define HELP_MENU 0X9904
#define HELP_MENU2 0X9905
#define CreateWindowA(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)
#endif 

#include <Windows.h>
#include <WinUser.h>
#include "Cport.h"
#include "string.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include "mode.h"
#include "keyboard.h"
#include <commctrl.h>
#include "resource.h"
#include "MMsystem.h"
#include "tchar.h"

using namespace std;




//**Variable Declarations for Port Connections**//
HANDLE hComm; //For Port
DCB dcbSerialParams; //port properties
COMMTIMEOUTS timeouts; //time out properties
string Status { 0 }; //used for error checking
bool errorCheck;
char comInput; bool portSelected = false;
//=============================================//

//**Mouse Variables**//
int mouseSpeed; int num = 0;
INPUT mouse;
//=============================================//
//**Mode Variables**//
int ModeIndex, SubModeIndex;
//=============================================//
//**Keyboard Variables**//
INPUT keys, secondKeys, thirdKeys;
keyboard Keymode;
//=============================================//
int userInput;
LPSTR *TextSave[20];
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND button, button1, button2, button3; HWND TextEntry, dropMenu, dropMenu2, portStatus, handleStatus, handleStatus1, helpMenu, helpMenu2;

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
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Open Handle",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

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

	ShowWindow(hwnd, nCmdShow);

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
		button = CreateWindowA("BUTTON", "Open Handle",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			200, 250, 200, 20,
			hwnd, (HMENU)ID_BUTTON3, NULL, NULL);
		portStatus = CreateWindowA("STATIC", "link handle",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			250, 125, 100, 25,
			hwnd, (HMENU)HANDLE_LINK, NULL, NULL);
		handleStatus = CreateWindowA("STATIC", "handle not active",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			200, 275, 200, 20,
			hwnd, (HMENU)HANDLE_STATUS, NULL, NULL);
		button2 = CreateWindowA("BUTTON", "Select Port",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			200, 50, 200, 20,
			hwnd, (HMENU)ID_BUTTON1, NULL, NULL);
		button3 = CreateWindowA("BUTTON", "Close Port",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			200, 100, 200, 20,
			hwnd, (HMENU)ID_BUTTON2, NULL, NULL);
		TextEntry = CreateWindowA("EDIT", "\\\\.\\COM",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			260, 75, 75, 20,
			hwnd, (HMENU)2, NULL, NULL);
		dropMenu = CreateWindowA("COMBOBOX", NULL,
			WS_VISIBLE | WS_CHILD | WS_TABSTOP,
			200, 150, 100, 100,
			hwnd,
			(HMENU)IDC_COMBOBOX_TEXT, NULL,
			NULL);
		dropMenu2 = CreateWindowA("COMBOBOX", NULL,
			WS_VISIBLE | WS_CHILD | WS_TABSTOP,
			300, 150, 100, 100,
			hwnd,
			(HMENU)IDC_COMBOBOX_TEXT2, NULL,
			NULL);
		
		SendMessage(dropMenu, CB_ADDSTRING, (WPARAM) 0, (LPARAM) L"Mouse Mode" );
		SendMessage(dropMenu, CB_ADDSTRING, 0, (LPARAM) L"KeyBoard Mode");
		SendMessage(dropMenu, CB_ADDSTRING, 0, (LPARAM) L"Macro Mode");
	

	}

	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

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

		///Slection Change In Combo box1
		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == IDC_COMBOBOX_TEXT)
		{
			 ModeIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
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

			 }
			
		
		}

		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == IDC_COMBOBOX_TEXT2)
		{
			SubModeIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);

			if (ModeIndex == 0)
			{
				if (SubModeIndex == 0)
				{
					mouseSpeed = 2;

				}
				else if (SubModeIndex == 1)
				{
					mouseSpeed = 3;
				}
				else if (SubModeIndex == 2)
				{
					mouseSpeed = 5;
				}
				else if (SubModeIndex == 3)
				{
					mouseSpeed = 7;
				}
				else if (SubModeIndex == 4)
				{
					mouseSpeed = 10;
				}
				
			}

			
		}

		switch (LOWORD(wParam))
		{
		case ID_BUTTON1:
		{
			int storePort = 0;
			storePort = GetWindowTextA(TextEntry, (LPSTR)&TextSave[0], 20);
			//::MessageBoxA(hwnd, (LPCSTR)& TextSave, "Port Selcected", MB_OK);
			comInitialize(hComm, (LPCSTR)&TextSave);
			errorCheck = checkPort(hComm);
			if (errorCheck == true && portSelected == false)
			{
				
				SetDlgItemText(hwnd, HANDLE_LINK, L"Unable to Link");
				portSelected = false;
				PlaySoundA("nolinkfound", NULL, SND_ASYNC);

			}
			if (portSelected == false && errorCheck == false)
			{
				portSelected = true;
				PlaySoundA("linked", NULL, SND_ASYNC);
				SetDlgItemText(hwnd, HANDLE_LINK, L"Handle Linked");
				setupDCB(hComm, dcbSerialParams);
				setupTimeouts(timeouts);
				
			}

			break;
		}
		
		case ID_BUTTON2:
		{	if (portSelected == false) SetDlgItemText(hwnd, HANDLE_LINK, L"no link");

			if (portSelected == true)
			{
				CloseHandle(hComm);
				int storePort = 0;
				storePort = GetWindowTextA(TextEntry, (LPSTR)&TextSave[0], 20);
				SetDlgItemText(hwnd, HANDLE_LINK, L"Unlinked");
				PlaySoundA("unlink3", NULL, SND_ASYNC);
				getchar();
				portSelected = false;
			}
			break;
		}
		
		
		case ID_BUTTON3:
		{
				switch (ModeIndex)
			{
			case 0: //Mouse Mode
			{
				if (portSelected == false) 	SetDlgItemText(hwnd, HANDLE_STATUS, L"please link handle first");
				if (portSelected == true)
				{
					MSG msg = {};
					setupMouseEvent(mouse);
					int x, y, xBound, yBound;
					centerMouse(xBound, yBound);
					x = xBound; y = yBound;
					xBound = 2 * xBound; yBound = 2 * yBound;
					SetDlgItemText(hwnd, HANDLE_STATUS, L"Mouse Selected");
					while (!GetAsyncKeyState(0X52)) //PRESS R to exit loop and use GUI again
					{
						readPort(hComm, comInput);
						clickMouse(comInput);
						movePointer(x, y, comInput, mouseSpeed, hComm);
						checkBoundaries(x, y, xBound, yBound);
					}
					comInput = 'Z'; //R for reset
				}
					if (portSelected == true && comInput == 'Z')
					{
						SetDlgItemText(hwnd, HANDLE_STATUS, L"Mode Off");
					}
			break;
			}
				
			
			
			case 1: //KeyBoard Mode
			{	if (portSelected == false) 	SetDlgItemText(hwnd, HANDLE_STATUS, L"please link handle first");
				if (portSelected == true) {
					
					//set-up keyboard events
					setupKeyboardEvent(keys);
					setupKeyboardEvent(secondKeys);
					setupKeyboardEvent(thirdKeys);
					//sub switch statement to deal with the different sub modes
					//Arrow Keys
					if (SubModeIndex == 0) { Keymode.setArrowkeys(); SetDlgItemText(hwnd, HANDLE_STATUS, L"Arrow Keys Selected"); }
					//WASD
					if (SubModeIndex == 1) { Keymode.setWASD(); SetDlgItemText(hwnd, HANDLE_STATUS, L"WASD Selected"); }
					//Mario Mode
					if (SubModeIndex == 2) { Keymode.setMario(); SetDlgItemText(hwnd, HANDLE_STATUS, L"Mario Selected"); }
					//Media Mode 
					if (SubModeIndex == 3) { Keymode.setMedia(); SetDlgItemText(hwnd, HANDLE_STATUS, L"Media Selected"); }
					readPort(hComm, comInput);
					
					while (!GetAsyncKeyState(0X52)) //r to exit loop
					{
						readPort(hComm, comInput);
						sendCommand(comInput, keys, secondKeys, thirdKeys, Keymode, hComm);
					}
					comInput = 'Z'; //R for reset
				}
					if (portSelected == true && comInput == 'Z')
					{
						SetDlgItemText(hwnd, HANDLE_STATUS, L"Mode Off");
					}
				
				break;
			}
			

			case 2:
			{
			}
			break;
			

			
			
			
			
			}

		}
		break;
		}

	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}