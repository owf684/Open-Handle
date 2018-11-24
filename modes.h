#ifndef MODES_H
#define MODES_H
#include <iostream>
#include "windows.h"
#include "keyboard.h"
#include "Cport.h"
#pragma once





//Keyboard
void pressDown(INPUT& keys, char KeyCode);

void releaseKey(INPUT& keys);

void sendCommand(char& comInput, INPUT &keys, INPUT &secondKey, INPUT &thirdKey, keyboard& keyHex, HANDLE& hComm);

//Mouse
void centerMouse(int &x, int &y);

void movePointer(int &x, int &y, char &comInput, int &mouseSpeed);

void checkBoundaries(int &x, int &y, int &xBound, int &yBound);

void clickMouse(char comInput);

void setupMouseEvent(INPUT& keys);

char stableCheck(char &comInput);

#endif