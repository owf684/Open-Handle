#pragma once
#ifndef MODE_H
#define MODE_H
#include <iostream>
#include "windows.h"
#include "keyboard.h"
#include "Cport.h"
#include "string.h"


#pragma once

void modeMenu();



//Keyboard
void pressDown(INPUT& keys, char KeyCode);

void releaseKey(INPUT& keys);

void sendCommand(char& comInput, INPUT &keys, INPUT &secondKey, INPUT &thirdKey, keyboard& keyHex, HANDLE& hComm);

//Mouse
void centerMouse(int &x,int &y);

void movePointer(int &x, int &y, char &comInput, int &mouseSpeed, HANDLE& hComm);

void checkBoundaries(int &x, int &y, int &xBound, int &yBound);

void leftClick(char comInput);

void rightClick(char comInput);

void setupMouseEvent(INPUT& keys);

char stableCheck(char &comInput);

//Macro

void movePointer(int &x, int &y, char &comInput, int &mouseSpeed, bool &pointer); 

#endif