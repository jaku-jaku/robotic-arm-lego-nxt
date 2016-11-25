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
	bool gpAng;

} JoyStickInfo;

void gripperController(int angle){	//0 closed, 180 open
	if (angle>=0||angle<=180)
		setServoPosition (S4, 3, angle);
}

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
	writeLongPC(out, j.gpAng);
	writeEndlPC(out);
}


void moveWithJoystick(float & joint2, float & joint3, bool & closedGP)
{
	getJoystickSettings(joystick);

	motor[motorA] = (int)(joystick.joy2_x1/128.0 * 70);

	joint2 += joy1Btn(02) -  joy1Btn(04);
	joint3 += joy1Btn(01) - joy1Btn(03);

	if (joint2 >= 90 || joint2 <= -90)
		joint2 = 90;
	if (joint3 >= 90 || joint3 <= -90)
		joint3 = 90;

	setServoPosition(S4, 1, joint2);
	setServoPosition(S4, 2, joint3);

	if (joy1Btn(06) == 1)
	{
		gripperController(20);
		closedGP = true;
	}

	if (joy1Btn(05) == 1)
	{
		gripperController(90);
		closedGP = false;
	}

}

task main()
{
	SensorType[S4] = sensorI2CCustom9V;
	bool isRunning = true;
	nMotorEncoder[motorA] = 0;

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
	joy.gpAng = false;

	setServoPosition(S4,1,0);
	setServoPosition(S4,2,0);
	gripperController(90);
	float j2A = 0, j3A = 0;


	time1[T1] = 0;
	bool isMoving = false;
	bool gpClosed = false;

	while(isRunning)
	{
		moveWithJoystick(j2A, j3A, gpClosed);

		if ((time1[T1] % 120 > 117 || time1[T1] % 120 < 2) && isMoving)
		{
			joy.j1Ec = nMotorEncoder[motorA];
			joy.j1Speed = motor[motorA];
			joy.j2Ang = j2A;
			joy.j3Ang = j3A;
			joy.gpAng = gpClosed;

			outputValuesToFile(fout, joy);
			// saving every 15 ms
		}

	}
}
