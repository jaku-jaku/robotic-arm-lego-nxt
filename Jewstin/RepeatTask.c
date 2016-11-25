#pragma debuggerWindows("joystickSimple");
#include "NXT_FileIO.c"
#include "NXTServo-lib-UW.c"
#include "JoystickDriver.c"

typedef struct
{
	int j1Ec;
	int j1Speed;
	int j2Ang;
	int j3Ang;
	int gPAng;

} JoyStickInfo;

task main
{

	TFileHandle fin;
	bool fileOK = openReadPC(fin,"angleValues.txt");

	if (!fileOK)
	{
		displayString(0, "Error");
	}











}
