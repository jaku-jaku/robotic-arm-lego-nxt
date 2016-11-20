/*+-----------------------------------------------------------------------------

ROBOTIC ARM
---------------
TEAM JADO - MTE100 && GENE Final Project

|+------------------------------------------------------------------------------
||
||           	Team:  		JADO   #51
||
||         	Author:  Jack(Jianxiang) Xu
||										 Ali Toyserkani
||										 Dustin Hu
||										 Oswaldo Ferro Hernandez
||
||        	Project:  Robotic Arm
||
||	 	 	Description:  ROBOTC
||
|+------------------------------------------------------------------------------
||
||        	Purpose:  [Main class description]
||
||    	 Interfaces:    1. Auto-Calibration
|| 										2. Beeping sound to give a feedback for user
||											3. Safety always first, Ultrasonic Sensor to make
||											sure workplace safe.
||
|+------------------------------------------------------------------------------
||
||	BASIC_WORK_FLOW:  AUTO-CALIBRATION -> READ_POINTS_FROM_FILE -> CHECK_BOUNDARY
||										 -> MASSAGE_IT!!! -> CHECK_VALIDITY -> OUTPUT_TO_MOTOR
||
||   	  Constants:  (NAME + BRIEF_DESCRIPTION)
||
||    	 	 Function:  [List the names and arguments of all defined
||                   constructors.]
||
++------------------------------------------------------------------------------*/

#include "definitions.c"

//Define the output Port
const int S_COLOR=S1;
const int S_ULTRA=S2;
const int S_TOUCH=S3;
const int S_SERVO=S4;
const int JOINT1=motorA;
const int JOINT2=1;
const int JOINT3=2;
const int GRIPPER=3;
//Size of data parsed at once
const int MAX=20;
const int FULLROTATION_EC_VALUE = 360*5;

////----------------------//
////---AUTO-CALIBRATION---//
////------zero axis-------//
////----------------------//
//int getECValue (){
//	return nMotorEncoder [JOINT1];
//}

//void zeroECValue (){
//	nMotorEncoder [JOINT1] = 0;
//}

//int getDistance (){
//	return SensorValue [S_ULTRA];
//}

////THIS HAS TO CHANGE!! USE THE FUNCTION THAT MOVES THE MOTORS!! moveToTarget() IS A PROVISIONAL FUNCTION
//void rotate (bool clockwise, int power){
//	if (!clockwise)
//		power*=-1;
//	motor [JOINT1] = power;
//}

////Rotating the Z axis
////EC == Encoder Value
//const int GEARREDUCTION = 5;

//int angleToEC (float angle){	//Returns the ec that it must move
//	return angle * GEARREDUCTION - getECValue();
//}

////New Version of moveToTarget
//void moveToTarget (int targetEC, int tolerance){
//	int moveSpeed = 75;
//	//sigmoid function , PD control
//	bool cw  = true;
//	if (targetEC > FULLROTATION_EC_VALUE/2.0){
//		cw = false;
//		targetEC= FULLROTATION_EC_VALUE/2.0-targetEC;
//	}

//	rotate (cw, moveSpeed);

//	while ((fabs(getECValue())-fabs(targetEC)) <= tolerance);

//	rotate (false, 0);
//	//It will not be using rotate(). We will use moveMotor () function
//}

////zeroAXIS
//void zeroZAxis (){
//	zeroECValue ();
//	float minDist = 255;
//	int targetEC = 0;
//	const int Tolerance = 0, power = 40;

//	rotate(true, power);

//	while (getECValue() <= FULLROTATION_EC_VALUE){
//		if (getDistance () < minDist){
//			minDist = getDistance ();
//			targetEC = getECValue();
//		}
//	}
//	displayString(2,"Position: %f", getDistance());
//  displayString(3,"Position: %f",targetEC);
//	rotate (true, 0);

//	zeroECValue ();
//	moveToTarget(targetEC,Tolerance);
//	zeroECValue ();
//}

////general btn function
void waitBtn(){
	while(nNxtButtonPressed==-1){}
	while(nNxtButtonPressed!=-1){}
}

//---------------------------//
//-----Read Point FileIO-----//
//---------------------------//
bool readNextPoint(Point &coor0){
	coor0.x=0;
	coor0.y=0;
	coor0.z=0;
	coor0.t=0;
	return false;
}
//----------------------//
//-----Main Program-----//
//----------------------//
task main()
{
	//---initialization---//
	SensorType[S_ULTRA]=sensorSONAR;
	SensorType[S4] = sensorI2CCustom9V;
	//Check IF File open

	//-BEGIN- Auto-Calibrating joint1
	nxtDisplayCenteredTextLine(0, "Calibrate!");
	displayString(2,"Press Any Button");
	displayString(3,"to begin");
	waitBtn();//Wait for starting the program
	eraseDisplay();
	nxtDisplayCenteredTextLine(0, "Caution");
	displayString(2,"Auto Calibration ");
	displayString(3,"Starts in 2 seconds");
	displayString(4,"Step back!");
	PlaySound(soundBlip);
	wait1Msec(2000);//Give 2 seconds for operator leaving the platform
	ClearSounds();
	//zeroZAxis();
	eraseDisplay();
	//-END- of auto-calibration

	//-BEGIN- start to performing
	Messages="System Ready";
	nxtDisplayCenteredTextLine(0, "System");
	Messages="Press Any Button to begin the task";
	screenAutoOutput(2, Messages);
	waitBtn();
	//Declare Variables
	int QUANTITY;//from first line from input file
	int pointer=0;
	int cnt=0;
	Point coor[MAX];
	AngleSet angle[MAX];
	//---READY---//
	//Ready, Screen Output, Wait for button pressed


	//ReadFile && Assign 20 coordinates
	//pointer=0;
	//for(int i=0;i<MAX;i++){
	//	if(!readNextPoint(coor[i])){
	//		i--;//skip this point
	//	}else{
	//		pointer++;
	//		cnt++;
	//	}
	//}
	//Manipulating class - MASSAGE IT!!!

	//--ACTION--//

	//--END--//
}
