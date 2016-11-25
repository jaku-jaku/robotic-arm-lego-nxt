//HARDMODE
#pragma debuggerWindows("joystickSimple");
#include "definitions.h"
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

void outputValuesToFile(TFileHandle & out, JoyStickInfo & j)
{
	writeLongPC(out, j.j1Ec);
	writeTextPC(out, "  ");
	writeLongPC(out, j.j1Speed);
	writeTextPC(out, "  ");
	writeLongPC(out, j.j2Ang);
	writeTextPC(out, "  ");
	writeLongPC(out, j.j3Ang);
	writeTextPC(out, "  ");
	writeLongPC(out, j.gPAng);
	writeEndlPC(out);
}


void moveWithJoystick()
{
	getJoystickSettings(joystick);

	motor[motorA] = (int)(joystick.joy1_x2/128.0 * 70);
	displayString(4, "%f", joystick.joy1_x2);

	float currAlpha = -(joystick.joy1_y1/128.0 * 90);
	float currBeta = joystick.joy1_x1/128.0 * 90;

	setServoPosition(S4,1,currAlpha);
	setServoPosition(S4,2,currBeta);

}

task main()
{
	SensorType[S_SERVO] = sensorI2CCustom9V;
	SensorType[S_COLOR] = sensorColorNxtFULL;
	SensorType[S_TOUCH]=sensorTouch;
	bool isRunning = true;

	TFileHandle fout;
	word fileSize = 10000;
	bool fileOK = openWritePC(fout,"angleValues.txt",fileSize);

	if (!fileOK)
	{
		displayString(0,"Error");
	}
	JoyStickInfo joy;
	joy.j1Ec = 0;
	joy.j1Speed = 0;
	joy.j2Ang = 0;
	joy.j3Ang = 0;
	joy.gPAng = 0;

	setServoPosition(S4,1,0);
	setServoPosition(S4,2,0);

	time1[T1] = 0;

	while(isRunning && fileOK)
	{

		moveWithJoystick();
		if(joy1Btn(05)==1)
			gripperController(20);
		if(joy1Btn(06)==1)
			gripperController(90);
		if (time1[T1] % 15 > 12 || time1[T1] % 15 < 2)
		{
			outputValuesToFile(fout, joy);
			// saving every 15 ms
		}

	}
}
