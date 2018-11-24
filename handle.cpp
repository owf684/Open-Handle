#include "handle.h"



handle::handle() noexcept
{
	defaultCommands[0] = "0x48"; //palm up    - UP ARROW KEY
	defaultCommands[1] = "0x50"; //palm down  - DOWN ARROW KEY
	defaultCommands[2] = "0x4B"; //palm right - LEFT ARROW KEY
	defaultCommands[3] = "0x4D"; //palm left  - RIGHT ARROW KEY
	defaultCommands[4] = "0x1C"; //index      - ENTER 
	defaultCommands[5] = "0x2A"; //middle     - SHIFT L
	defaultCommands[6] = "0x1D"; //thumb      - CRTL L
	defaultCommands[7] = "0x10";  //index + middle    - Q
	defaultCommands[8] = "0x11"; //index + palm right - W 
	defaultCommands[9] = "0x12"; //index + palm left  - E
	defaultCommands[10]= "0x13"; //middle + palm right- R
	defaultCommands[11]= "0x14"; //middle + palm left - T
	
}


handle::~handle()
{
}
