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


void moveWithJoystick(float & xValue, float & zValue)
{
	getJoystickSettings(joystick);

	// Joint 1

	motor[motorA] = (int)(joystick.joy1_x1/128.0 * 70);

	// Joint 2 and 3 (change dist , newX and z to move in plane) use some waiting to actually read in

	xValue += (joystick.joy1_x1/128.0 * 10);
	zValue += (joystick.joy1_y1/128.0 * 10 * -1);

	// following will be replaced with calcAngleSet function once merged

	float dist = sqrt(xValue*xValue + zValue*zValue);


}

task main()
{
	//a boolean will trigger this code if the user wants to use the joystick feature
	// there will be another feature for doing the last joystick task again
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
	float xPlane = 306.6;
	float zPlane = 177.0;

	//int j2Angle = 0;
	//int j3Angle = 0;
	//int j1Encoder = 0;
	//int j1Speed = 0;
	//int gripperAngle = 0;

	// during joystick movement, every 0.2 seconds, save data to file

	time1[T1] = 0;

	while(isRunning && fileOK)
	{
		// move the the robot joints using joystick;
		moveWithJoystick(xPlane, zPlane);

		if (time1[T1] % 15 > 12 || time1[T1] % 15 < 2)
		{
			outputValuesToFile(fout, joy);
			// saving every 15 ms
		}

	}
}
