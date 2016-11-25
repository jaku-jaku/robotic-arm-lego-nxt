//HARDMODE
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


void gripperController(int angle){
	if (angle>=0||angle<=180)
		setServoPosition(S4, 7, angle)
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
	writeLongPC(out, j.gPAng);
	writeEndlPC(out);
}


void moveWithJoystick(float & xAngle, float & zAngle)
{
	getJoystickSettings(joystick);

	// Joint 1

	motor[motorA] = (int)(joystick.joy1_x2/128.0 * 70);
	displayString(4, "%f", joystick.joy1_x2);

	// Joint 2 and 3 (change dist , newX and z to move in plane) use some waiting to actually read in

	float currAlpha = -(joystick.joy1_y1/128.0 * 90);
	float currBeta = joystick.joy1_x1/128.0 * 90;

	setServoPosition(S4,1,currAlpha);
	setServoPosition(S4,2,currBeta);


	//if (time1[T1] % 100 > 98 || time1[T1] < 2)
	//{

	//}
	//xValue += (joystick.joy1_x1/128.0 * 10);
	//zValue += (joystick.joy1_y1/128.0 * 10 * -1);

	// following will be replaced with calcAngleSet function once merged

	//float dist = sqrt(xValue*xValue + zValue*zValue);

	//float alpha = (180/PI) * (atan2(zValue,xValue) + acos((197*197 - 157*157 - dist*dist)/(-2.0*157*dist)) + PI/2);
	//float beta = (180/PI) * (acos((dist*dist - 197*197 - 157*157)/(-2.0*157*197)) - PI);

	//setServoPosition(S4, 1, 0.0014*alpha*alpha +1.5288*alpha - 173.79 );
	//setServoPosition(S4, 2, -0.0007*beta*beta + 0.9882*beta + 21.773);

}

task main()
{
	//a boolean will trigger this code if the user wants to use the joystick feature
	// there will be another feature for doing the last joystick task again

	SensorType[S4] = sensorI2CCustom9V;
	SensorType[S2] = sensorColorNxtFULL;
	SensorType[S1]=sensorTouch;
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
	//float xPlane = 306.6;
	//float zPlane = 177.0;
	float xA = 0, zA = 0;

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
		moveWithJoystick(xA, zA);
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
