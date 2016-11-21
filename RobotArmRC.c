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




//---------------------//
//---Button Function---//
//---------------------//
//general btn function
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
	displayString(3,"Starts in 5 seconds");
	displayString(4,"Step back!");
	//Give 5 seconds for operator leaving the platform
	for(int i=0;i<5;i++){
		PlaySound(soundBeepBeep);
		wait1Msec(1000);
  }
	ClearSounds();
	zeroZAxis();
	eraseDisplay();
	//-END- of auto-calibration

	//-BEGIN- start to performing
	nxtDisplayCenteredTextLine(0, "System Ready");
	displayString(2,"Press Any Button");
	displayString(3,"to begin the task");
	waitBtn();
	eraseDisplay();
	//Declare Variables
	int QUANTITY;//from first line from input file
	int pointer=0;
	int cnt=0;
	Point coor[MAX];
	AngleSet angle[MAX];
	//---READY---//
	//Ready, Screen Output, Wait for button pressed


	//ReadFile && Assign 20 coordinates
	pointer=0;
	for(int i=0;i<MAX;i++){
		if(!readNextPoint(coor[i])){
			i--;//skip this point
		}else{
			pointer++;
			cnt++;
		}
	}
	//Manipulating class - MASSAGE IT!!!

	//--ACTION--//

	//--END--//
}
