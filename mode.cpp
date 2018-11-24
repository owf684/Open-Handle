#include "mode.h"


using namespace std;
int delay = 1;
char commandCombo[8];
char lastCommand;
char stable; //used for check to fix jump-run glitch (if stable only input click or shoot)
double accely = 0;

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/



/************************Key Board Functions*****************************/
/************************************************************************/
/************************************************************************/

void pressDown(INPUT& keys, char KeyCode)
{
	keys.ki.wScan = KeyCode;
	keys.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &keys, sizeof(INPUT));
	return;
}


void releaseKey(INPUT& keys)
{
	keys.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;
	SendInput(1, &keys, sizeof(INPUT));
	return;
}

/************************************************************************/
/************************************************************************/
/************************************************************************/

/**************stable check*******************/
char stableCheck(char &comInput)
{
	char stable = '_';
	if (comInput == '0' || comInput == '1')
	{
		stable = comInput;
	}
	return stable;
}


/*******************************Key Board Mode***************************/
/************************************************************************/
/************************************************************************/
void sendCommand(char& comInput, INPUT &keys, INPUT &secondKey, INPUT &thirdKey, keyboard& keyHex, HANDLE &hComm)
{
	bool charDetect = false;


	//---------------------------------------------------------------------------//
	/*****************************Up Down Left Right*****************************/
	//---------------------------------------------------------------------------//
	if (comInput == 'u')
	{
		lastCommand = comInput;
		charDetect = true;
		while (charDetect) //glove tilted up
		{
			pressDown(keys, keyHex.getU());
			readPort(hComm, comInput);
			if (comInput == 'c') { charDetect = false;  goto IndexFinger; } //save last command and go to index finger to execute command. No release leaves they key pressed
			if (comInput == 'k') { charDetect = false;  goto MiddleFinger; } //save last command and go to middle finger to execute command. No release leaves they key pressed

			if (comInput == 'U' || comInput == 'y' || comInput == 't' || comInput == 'l' || comInput == 'h' || comInput == 'g' || comInput == 'r' || comInput == 'd')
			{
				charDetect = false;
				releaseKey(keys);

			}

		}
	}


	if (comInput == 'd')
	{
		lastCommand = comInput;
		charDetect = true;
		while (charDetect) //glove tilted up
		{

			pressDown(keys, keyHex.getD());
			readPort(hComm, comInput);
			if (comInput == 'c') { charDetect = false;releaseKey(keys);goto IndexFinger; } //save last command and go to index finger to execute command. No release leaves they key pressed
			if (comInput == 'k') { charDetect = false;releaseKey(keys);goto MiddleFinger; } //save last command and go to middle finger to execute command. No release leaves they key pressed
			if (comInput == 'D' || comInput == 'y' || comInput == 't' || comInput == 'h' || comInput == 'g' || comInput == 'r' || comInput == 'l' || comInput == 'u')
			{
				charDetect = false;
				releaseKey(keys);
			}

		}
		
	}
	if (comInput == 'l')
	{
		lastCommand = comInput;
		charDetect = true;
		while (charDetect) //glove tilted up
		{

			pressDown(keys, keyHex.getL());
			readPort(hComm, comInput);

			if (comInput == 'c') { charDetect = false; releaseKey(keys); goto IndexFinger; } //save last command and go to index finger to execute command. No release leaves they key pressed
			if (comInput == 'k') { charDetect = false; releaseKey(keys); goto MiddleFinger; } //save last command and go to middle finger to execute command. No release leaves they key pressed
			if (comInput == 'L' || comInput == 'y' || comInput == 't' || comInput == 'u' || comInput == 'h' || comInput == 'g' || comInput == 'r' || comInput == 'd')
			{
				charDetect = false;
				releaseKey(keys);
			}

		}
		
	}
	if (comInput == 'r')
	{
		lastCommand = comInput;
		charDetect = true;
		while (charDetect) //glove tilted up
		{

			pressDown(keys, keyHex.getR());
			readPort(hComm, comInput);
			if (comInput == 'c') { charDetect = false; releaseKey(keys); goto IndexFinger; } //save last command and go to index finger to execute command. No release leaves they key pressed
			if (comInput == 'k') { charDetect = false; releaseKey(keys); goto MiddleFinger; } //save last command and go to middle finger to execute command. No release leaves they key pressed
			if (comInput == 'R' || comInput == 'y' || comInput == 't' || comInput == 'h' || comInput == 'g' || comInput == 'd' || comInput == 'l' || comInput == 'u')
			{
				charDetect = false;
				releaseKey(keys);
			}

		}
	
	}

	//---------------------------------------------------------------------------//
	/*****************************Up Down Left Right*****************************/
	//---------------------------------------------------------------------------//


	//---------------------------------------------------------------------------//
	/******************Up Left, Up Right, Down Left Down Right*******************/
	//---------------------------------------------------------------------------//
	if (comInput == 'h') //down right
	{
		lastCommand = comInput;
		charDetect = true;
		while (charDetect) //glove tilted up
		{

			pressDown(keys, keyHex.getD());
			pressDown(secondKey, keyHex.getR());
			readPort(hComm, comInput);
			if (comInput == 'c') { charDetect = false; releaseKey(keys); releaseKey(secondKey); goto IndexFinger; } //save last command and go to index finger to execute command. No release leaves they key pressed
			if (comInput == 'k') { charDetect = false; releaseKey(keys); releaseKey(secondKey); goto MiddleFinger; } //save last command and go to middle finger to execute command. No release leaves they key pressed
			if (comInput == 'H' || comInput == 'y' || comInput == 't' || comInput == 'd' || comInput == 'g' || comInput == 'r' || comInput == 'l' || comInput == 'u')
			{
				charDetect = false;
				releaseKey(keys);
				releaseKey(secondKey);
			}

		}
		
	}
	if (comInput == 'g') //down left
	{
		lastCommand = comInput;
		charDetect = true;
		while (charDetect)
		{

			pressDown(keys, keyHex.getD());
			pressDown(secondKey, keyHex.getL());
			readPort(hComm, comInput);
			if (comInput == 'c') { charDetect = false; releaseKey(keys); releaseKey(secondKey); goto IndexFinger; } //save last command and go to index finger to execute command. No release leaves they key pressed
			if (comInput == 'k') { charDetect = false; releaseKey(keys); releaseKey(secondKey); goto MiddleFinger; } //save last command and go to middle finger to execute command. No release leaves they key pressed
			if (comInput == 'G' || comInput == 'y' || comInput == 't' || comInput == 'h' || comInput == 'd' || comInput == 'r' || comInput == 'l' || comInput == 'u')
			{
				charDetect = false;
				releaseKey(keys);
				releaseKey(secondKey);
			}

		}
		
	}
	if (comInput == 't') //up left
	{
		lastCommand = comInput;
		charDetect = true;
		while (charDetect) //glove tilted up
		{

			pressDown(keys, keyHex.getU());
			pressDown(secondKey, keyHex.getL());
			readPort(hComm, comInput);
			if (comInput == 'c') { charDetect = false; releaseKey(keys); releaseKey(secondKey); goto IndexFinger; } //save last command and go to index finger to execute command. No release leaves they key pressed
			if (comInput == 'k') { charDetect = false; releaseKey(keys); releaseKey(secondKey); goto MiddleFinger; } //save last command and go to middle finger to execute command. No release leaves they key pressed
			if (comInput == 'T' || comInput == 'y' || comInput == 'd' || comInput == 'h' || comInput == 'g' || comInput == 'r' || comInput == 'l' || comInput == 'u')
			{
				charDetect = false;
				releaseKey(keys);
				releaseKey(secondKey);
			}

		}
	
	}
	if (comInput == 'y') //up right
	{
		lastCommand = comInput;
		charDetect = true;
		while (charDetect) //glove tilted up
		{

			pressDown(keys, keyHex.getU());
			pressDown(secondKey, keyHex.getR());
			readPort(hComm, comInput);
			if (comInput == 'c') { charDetect = false; releaseKey(keys); releaseKey(secondKey); goto IndexFinger; } //save last command and go to index finger to execute command. No release leaves they key pressed
			if (comInput == 'k') { charDetect = false; releaseKey(keys); releaseKey(secondKey); goto MiddleFinger; } //save last command and go to middle finger to execute command. No release leaves they key pressed
			if (comInput == 'Y' || comInput == 'd' || comInput == 't' || comInput == 'h' || comInput == 'g' || comInput == 'r' || comInput == 'l' || comInput == 'u')
			{
				charDetect = false;
				releaseKey(keys);
				releaseKey(secondKey);
			}

		}
		
	}
	//---------------------------------------------------------------------------//
	/******************Up Left, Up Right, Down Left Down Right*******************/
	//---------------------------------------------------------------------------//




	//---------------------------------------------------------------------------//
	/*******************************Finger Commands******************************/
	//---------------------------------------------------------------------------//

IndexFinger:

	if (comInput == 'c')
	{
		charDetect = true;
		while (charDetect) //glove tilted up
		{

			pressDown(keys, keyHex.getC());
			readPort(hComm, comInput);
			if (stableCheck(comInput) == '0')
			{
				if (lastCommand == 'l' || lastCommand == 't') { pressDown(secondKey, keyHex.getL()); } //continues the previeous press
				if (lastCommand == 'r' || lastCommand == 'y') { pressDown(secondKey, keyHex.getR()); }
			}
				if (comInput == 'j') { charDetect = false; releaseKey(keys); releaseKey(secondKey); goto TwoFingers; }
			if (comInput == 'C' || (comInput != lastCommand && comInput != 'c' && comInput == 'r') || (comInput != lastCommand && comInput != 'c' && comInput == 'l'))
			{
				charDetect = false;
				lastCommand = 's'; //s for stable 
				releaseKey(keys);
				releaseKey(secondKey);
			}


		}

		
	}


MiddleFinger:

	if (comInput == 'k')
	{
		charDetect = true;
		while (charDetect) //glove tilted up
		{

			pressDown(keys, keyHex.getK());
			readPort(hComm, comInput);
			if (stableCheck(comInput) == '0')
			{
				if (lastCommand == 'l' || lastCommand == 't') { pressDown(secondKey, keyHex.getL()); } //continues the previeous press
				if (lastCommand == 'r' || lastCommand == 'y') { pressDown(secondKey, keyHex.getR()); }
			}
				if (comInput == 'j') { charDetect = false; releaseKey(keys); releaseKey(secondKey); goto TwoFingers; }
			if (comInput == 'K' || (comInput != lastCommand && comInput != 'c' && comInput == 'r') || (comInput != lastCommand && comInput != 'c' && comInput == 'l'))
			{
				charDetect = false;
				releaseKey(keys);
				releaseKey(secondKey);

			}


		}

		//stable checking. fixing running, jumping, and moving issues

	

	}


TwoFingers:
	if (comInput == 'j')
	{
		charDetect = true;
		while (charDetect) //glove tilted up
		{

			pressDown(keys, keyHex.getC());
			pressDown(thirdKey, keyHex.getK());
			readPort(hComm, comInput);
			if (stableCheck(comInput) == '0')
			{
				if (lastCommand == 'l' || lastCommand == 't') { pressDown(secondKey, keyHex.getL()); } //continues the previeous press
				if (lastCommand == 'r' || lastCommand == 'y') { pressDown(secondKey, keyHex.getR()); }
			}
			if (comInput == 'C' || (comInput != lastCommand && comInput != 'c' && comInput == 'r') || (comInput != lastCommand && comInput != 'c' && comInput == 'l'))
			{
				charDetect = false;
				releaseKey(keys);
				releaseKey(secondKey);
				releaseKey(thirdKey);
			}


		}

		
	}









	return;
}



/********************************************************************/
/********************Mouse Functions*********************************/
/********************************************************************/
void checkBoundaries(int &x, int &y, int &xBound, int &yBound)
{
	if (x <= 0) x = 0;
	if (x >= xBound) x = xBound;
	if (y <= 0) y = 0;
	if (y >= yBound) y = yBound;
	return;
}
void centerMouse(int &x, int &y)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow(); //Handle for the desktop window
	GetWindowRect(hDesktop, &desktop); //getting the size of the screen
	x = desktop.right;
	y = desktop.bottom;
	x = x / 2;
	y = y / 2;
	SetCursorPos( (int) x, (int) y);
	return;
}


void setupMouseEvent(INPUT& keys)
{
	//Set up a generic keyboard event
	keys.type = INPUT_KEYBOARD;
	keys.ki.wScan = 0;
	keys.ki.time = 0;
	keys.ki.dwExtraInfo = 0;
	return;
}



void leftClick(char comInput)
{
	INPUT Input = { 0 }; //Ussed For Left Click 
	INPUT Input2 = { 0 };//Used For Right Click 

	//----------Left Click 
	if (comInput == 'c')
	{
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &Input, sizeof(INPUT));
	} else if(comInput == 'C')
	{
		ZeroMemory(&Input, sizeof(INPUT));
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &Input, sizeof(INPUT));
	}
	return;
}

void rightClick(char comInput)
{
	INPUT Input = { 0 }; //Ussed For Left Click 
	
	//--------Right Click 
	if (comInput == 'k')
	{
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &Input, sizeof(INPUT));
	
	ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &Input, sizeof(INPUT));
	}

	return;
}

/********************************************************************/
/********************Mouse Functions*********************************/
/********************************************************************/



/********************************************************************/
/************************Mouse Mode**********************************/
/********************************************************************/
void movePointer(int &x, int &y, char &comInput, int &mouseSpeed, HANDLE& hComm)
{
	bool charDetect;
	
	//---------------------------------------------------//
	/************Up Down Left66 Right Movements************/
	//---------------------------------------------------//
	if (comInput == 's')
	{
		centerMouse(x, y);

	}
	if (comInput == 'u') //u = up
	{
		y = y - mouseSpeed;
		SetCursorPos((int)x, (int)y);
	}


	//if (comInput == 'u')
	//{
	//	charDetect = true;
	//	while (charDetect) //glove tilted up
	//	{
	//		y = y - mouseSpeed2;
	//		SetCursorPos(x, y);
	//		readPort(hComm, comInput);
	//		if (comInput == 'U' || comInput == 'r' || comInput == 'l' || comInput == 'd')
	//		{
	//			charDetect = false;
	//			accely = 0;
	//		}
	//	}
	//}

	if (comInput == 'd') // d = down
	{
		y = y + mouseSpeed;
		SetCursorPos((int)x, (int)y);
	}

	//if (comInput == 'd')
	//{

	//	charDetect = true;
	//	while (charDetect) //glove tilted up
	//	{
	//		y = y + mouseSpeed2;
	//		SetCursorPos(x, y);
	//		readPort(hComm, comInput);
	//		if (comInput == 'D' || comInput == 'l' || comInput == 'r' || comInput == 'u')
	//		{
	//			charDetect = false;
	//			accely = 0;
	//		}
	//	}

	//}

	if (comInput == 'l') // l = left
	{
		x = x - mouseSpeed;
		SetCursorPos((int)x, (int)y);
	}

	//if (comInput == 'l')
	//{

	//	charDetect = true;
	//	while (charDetect) //glove tilted up
	//	{
	//		x = x - mouseSpeed2;
	//		SetCursorPos(x, y);
	//		readPort(hComm, comInput);
	//		if (comInput == 'L' || comInput == 'r' || comInput == 'd' || comInput == 'u')
	//		{
	//			charDetect = false;
	//			accely = 0;
	//		}
	//	}

	//}

	if (comInput == 'r') // r = right
	{
		x = x + mouseSpeed;
		SetCursorPos((int)x, (int)y);
	}

	//if (comInput == 'r')
	//{

	//	charDetect = true;
	//	while (charDetect) //glove tilted up
	//	{
	//		x = x + mouseSpeed2;
	//		SetCursorPos(x, y);
	//		readPort(hComm, comInput);
	//		if (comInput == 'R' || comInput == 'l' || comInput == 'd' || comInput == 'r')
	//		{
	//			charDetect = false;
	//			accely = 0;
	//		}
	//	}

	//}

	//---------------------------------------------------//
	/************Up Down Left Right Movements************/
	//---------------------------------------------------//



	//---------------------------------------------------//
	/*********************Diagonals**********************/
	//---------------------------------------------------//
	if (comInput == 't') //t= up left
	{
		y = y - mouseSpeed;
		x = x - mouseSpeed;
		SetCursorPos((int)x, (int)y);
	}

	//if (comInput == 't')
	//{
	//	charDetect = true;
	//	while (charDetect) //glove tilted up
	//	{
	//		y = y - mouseSpeed2;
	//		x = x - mouseSpeed2;
	//		SetCursorPos(x, y);
	//		readPort(hComm, comInput);
	//		if (comInput == 'T')
	//		{
	//			charDetect = false;
	//			accely = 0;
	//		}
	//	}
	//}


	if (comInput == 'h') // h = down right
	{
		y = y + mouseSpeed;
		x = x + mouseSpeed;
		SetCursorPos((int)x, (int)y);
	}

	//if (comInput == 'h')
	//{
	//	charDetect = true;
	//	while (charDetect) //glove tilted up
	//	{
	//		x = x + mouseSpeed2;
	//		y = y + mouseSpeed2;
	//		SetCursorPos(x, y);
	//		readPort(hComm, comInput);
	//		if (comInput == 'H')
	//		{
	//			charDetect = false;
	//			accely = 0;
	//		}
	//	}

	//}

	if (comInput == 'g') // g = down left
	{
		x = x - mouseSpeed;
		y = y + mouseSpeed;
		SetCursorPos((int)x, (int)y);
	}

	//if (comInput == 'g')
	//{

	//	charDetect = true;
	//	while (charDetect) //glove tilted up
	//	{
	//		x = x - mouseSpeed2;
	//		y = y + mouseSpeed2;
	//		SetCursorPos(x, y);
	//		readPort(hComm, comInput);
	//		if (comInput == 'G')
	//		{
	//			charDetect = false;
	//			accely = 0;
	//		}
	//	}

	//}

	if (comInput == 'y') // y = up right
	{
		x = x + mouseSpeed;
		y = y - mouseSpeed;
		SetCursorPos((int)x, (int)y);
	}

	//if (comInput == 'y')
	//{

	//	charDetect = true;
	//	while (charDetect) //glove tilted up
	//	{
	//		x = x + mouseSpeed2;
	//		y = y - mouseSpeed2;
	//		SetCursorPos(x, y);
	//		readPort(hComm, comInput);
	//		if (comInput == 'Y')
	//		{
	//			charDetect = false;
	//			accely = 0;
	//		}
	//	}

	//}
}
	//---------------------------------------------------//
	/*********************Diagonals**********************/
	//---------------------------------------------------//




	//---------------Macro---------------/

	void movePointer(int &x, int &y, char &comInput, int &mouseSpeed, bool& pointer)
	{
		if (pointer == true)
		{
			if (comInput == 'u') //u = up
			{
				y = y - mouseSpeed;
				SetCursorPos((int)x, (int)y);
			}
			if (comInput == 'd') // d = down
			{
				y = y + mouseSpeed;
				SetCursorPos((int)x, (int)y);
			}
			if (comInput == 'l') // l = left
			{
				x = x - mouseSpeed;
				SetCursorPos((int)x, (int)y);
			}
			if (comInput == 'r') // r = right
			{
				x = x + mouseSpeed;
				SetCursorPos((int)x, (int)y);
			}
		
			if (comInput == 't') //t= up left
			{
				y = y - mouseSpeed;
				x = x - mouseSpeed;
				SetCursorPos((int)x, (int)y);
			}
			if (comInput == 'h') // h = down right
			{
				y = y + mouseSpeed;
				x = x + mouseSpeed;
				SetCursorPos((int)x, (int)y);
			}
			if (comInput == 'g') // g = down left
			{
				x = x - mouseSpeed;
				y = y + mouseSpeed;
				SetCursorPos((int)x, (int)y);
			}
			if (comInput == 'y') // y = up right
			{
				x = x + mouseSpeed;
				y = y - mouseSpeed;
				SetCursorPos((int)x, (int)y);
			}
			//---------------------------------------------------//
			/*********************Diagonals**********************/
			//---------------------------------------------------//

		
		
		
		
		
		
		}
	}