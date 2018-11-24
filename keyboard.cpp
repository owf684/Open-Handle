#include "keyboard.h"


void keyboard::stringtoHexScancode(handle& hexFromFile)
{
	int i = 0, c = 0;
	bool convertEnd = true;
	while (convertEnd)
	{
		if (hexFromFile.getReadHex(i) == alphaHexstr[c])
		{
			scanCodes[i] = alphaHex[c];
			hexCodes[i] = alphaHexstr[c];
			scanCodeComboBox[i] = alphaHexLstr[c];
			hexLocation[i] = c;
			i++;
			c++;
		}
		else { c++; }
 		if (i == 12 )
		{
			convertEnd = false;
		}
		if (c == 38)
		{
			c = 0; //reset search
		}

	}

	return;
}

void keyboard::setArrowkeys()
{
	uHex = 0x48; //Virtual Key Code for Up Arrow    vk = 0x26 Scan = 0x48
	dHex = 0x50; //Virtual Key Code for Down Arrow  vk = 0x28 Scan = 0x50
	lHex = 0x4B; //Virtual Key Code for Left Arrow  vk = 0x25 Scan = 0x4B
	rHex = 0x4D; //Virtual Key Code for Right Arrow vk = 0x27 Scan = 0x4D
	return;

}
void keyboard::setWASD()
{
	uHex = 0x11; //Virtual Key Code for W vk = 0x53  
	dHex = 0x1F; //Virtual Key Code for S vk = 0x57
	lHex = 0x1E; //Virtual Key Code for A vk = 0x41
	rHex = 0x20; //Virtual Key Code for D vk = 0x44
	return;

}
void keyboard::setMedia()
{
	uHex = 0x30; //Virtual Key Code for Volume UP	vk = 0xAF
	dHex = 0x2E; //Virtual Key Code for Volume DOWN vk = 0xAE 
	lHex = 0x39; //Virtual Key Code for Space Bar	vk = 0x20
	rHex = 0x4D; //Virtual Key Code for Right Arrow vk = 0x27
	return;

}

void keyboard::setMario()
{
	uHex = 0x48; //Up arrow key,48
	dHex = 0x50; //Down arrow key,50
	lHex = 0x4B; //Left Arrow,4b 
	rHex = 0x4D; //Right Arrow,4d
	cHex = 0x2C; //scan code for z       
	kHex = 0x2D; //scan code for x 
	return;

}

/*Macro Array Indicies Meaning
0: Palm Up 
1: Palm Down
2: Palm Right
3: Index Down
4: Middle Down
5: Thumb Down
6: Index Down + Palm Right
7: Index Down + Palm Left
8: Middle Down + Palm Right 
9: Middle Down + Palm Left 
10: Index Down + Middle Down 
*/



void keyboard::setMacro(int i, char hexValue)
{
	macro[i] = hexValue;
}
// u = 75, u = 72, l = 6b, r = 74

void keyboard::setWord()
{
	char *temp;
	int i=0;
	
	getAlpha(i);
	getAlpha(i + 1);
	getAlpha(i + 2);
	
	//period, spacebar, comma, tab, 
	return;
}
keyboard::~keyboard()
{
}
