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
void waitAndContinue(){
	displayString(3,"Starts in 5 seconds");
	displayString(4,"Step back!");
	//Give 5 seconds for operator leaving the platform
	for(int i=0;i<5;i++){
		PlaySound(soundBeepBeep);
		wait1Msec(1000);
	}
	ClearSounds();
	eraseDisplay();
}
//----------------------//
//-----Main Program-----//
//----------------------//
task main()
{
	//---initialization---//
	SensorType[S_ULTRA]=sensorSONAR;
	SensorType[S4] = sensorI2CCustom9V;
	//Declare Variables
	int QUANTITY;//from first line from input file
	int pointer=0;
	int cnt=0,itr=0;
	Point listOfPoints[MAX];
	AngleSet listOfAngles[MAX];

	//Check IF File open
	TFileHandle fin;
	bool isFileOk = openReadPC(fin,"test.txt");
	//ReadFile && Assign 20 coordinates
	if(isFileOk)
		readIntPC(fin, QUANTITY);
	if (!isFileOk&&QUANTITY<=0)
		displayString(0,"ERROR! File");
	else{//whole program
		//-BEGIN- Auto-Calibrating joint1
		nxtDisplayCenteredTextLine(0, "Calibrate!");
		displayString(2,"Press Any Button");
		displayString(3,"to begin");
		waitBtn();//Wait for starting the program
		eraseDisplay();
		nxtDisplayCenteredTextLine(0, "Caution");
		waitAndContinue();//safe waiting function
		zeroZAxis();
		//-END- of auto-calibration

		//-BEGIN- start to performing
		nxtDisplayCenteredTextLine(0, "System Ready");
		displayString(2,"Press Any Button");
		displayString(3,"to begin the task");
		waitBtn();
		eraseDisplay();

		//---READY File input---//
		itr=QUANTITY;
		while(cnt<QUANTITY)
		{
			pointer=0;
			for(int i=0;i<MAX&&i<itr;i++)
			{
				readPoint(fin,listOfPoints[i]);
				pointer++;
				cnt++;
			}
			//---MASSAGE Input---//
			//Manipulating class - MASSAGE IT!!!
			for(int i=0;i<MAX&&i<itr;i++)
			{
				if(listOfPoints[i].isValid)
				{
					//if point is valid , calculate the angle
					listOfAngles[i].tMs=listOfPoints[i].tMs;
					listOfAngles[i].gP=listOfPoints[i].gP;
					calcAngleSet(listOfPoints[i], listOfAngles[i]);
				}
				listOfAngles[i].isValid=listOfPoints[i].isValid;
			}
			//--ACTION--//
			for(int i=0;i<MAX&&i<itr;i++)
			{
				displayString(4,"%f",listOfPoints[i].x);
				displayString(5,"%f",listOfPoints[i].y);
				displayString(6,"%f",listOfPoints[i].z);
				displayString(7,"%i",i);
				if(listOfAngles[i].isValid)
				{
					moveJ2(listOfAngles[i]);
					moveJ3(listOfAngles[i]);
					moveToTarget((int)(listOfAngles[i].theta*5.0),0);
					gripperController(listOfAngles[i].gP);
					wait1Msec(listOfAngles[i].tMs);
				}
				else
				{
					nxtDisplayCenteredTextLine(0, "ERROR");
					displayString(2,"Do you want to");
					displayString(3,"skip and continue");
					//displayString(4,"??? Any Button");
					PlaySound(soundBeepBeep);
					while(nNxtButtonPressed==-1){}//END while-bt
					ClearSounds();
					while(nNxtButtonPressed!=-1){}
					wait1Msec(500);
					eraseDisplay();
					displayString(4,"NEXT");
					//waitAndContinue();
				}//END else
			}//END for loop
			itr-=MAX;
		}//END while loop
	}//END else statement
	//--END--//
	closeFilePC(fin);
}
