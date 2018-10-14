/*+-----------------------------------------------------------------------------
ROBOTIC ARM
---------------
TEAM JADO - MTE100 && GENE Final Project
|+------------------------------------------------------------------------------
||
||           	Team:  		JADO   #51
||
||         	Author:   Jack(Jianxiang) Xu
||			  Ali Toyserkani
||			  Dustin Hu
|| 			  Oswaldo Ferro Hernandez
||
||        	Project:  Robotic Arm
||
|+------------------------------------------------------------------------------
||
||        	Purpose:  THIS CLASS AIM TO PERFORM AS AN ENTERTAINMENT ROBOTIC
|| 			  ARM, WITH STRONG FOCUS ON FLEXIBILITY, LEISURE, AND 
||			  EXTENSIBILITY. THIS IS A DEMO PROGRAM TO SHOW POTENTIAL
||			  DEVELOPMENT WITH OTHER CONTROL SYSTEM. 
||
||    	   Features:    1. Operation recording system in order to perform exact task
||			   again and again. 
|| 			2. Leisurely claw game
||			3. Automatically zeroes itself when idle
||			4. Wireless control (Bluetooth communication)
||
++------------------------------------------------------------------------------*/


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
}//Main Author(s): Oswaldo

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
}//Main Author(s): Dustin, Ali


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
}//Main Author(s): Dustin, Ali

task main()
{
	//a boolean will trigger this code if the user wants to use the joystick feature
	// there will be another feature for doing the last joystick task again
	//-Initialization-//
	SensorType[S4] = sensorI2CCustom9V;
	SensorType[S2] = sensorColorNxtFULL;
	SensorType[S1]=sensorTouch;
	bool isRunning = true;
	//Setting up recording system [File out]
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

	float xA = 0, zA = 0;

	time1[T1] = 0;

	//-Performing-//
	while(isRunning && fileOK)
	{
		// move the the robot joints using joystick;
		moveWithJoystick(xA, zA);
		if(joy1Btn(05)==1)
			gripperController(20);
		if(joy1Btn(06)==1)
			gripperController(90);
		//saving data points to a text file every 15ms
		if (time1[T1] % 15 > 12 || time1[T1] % 15 < 2)
		{
			outputValuesToFile(fout, joy);
			// saving every 15 ms
		}
	}
}//Main Author(s): Dustin, Ali, Jack
