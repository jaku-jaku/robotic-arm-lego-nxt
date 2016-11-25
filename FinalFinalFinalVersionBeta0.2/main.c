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

task main()
{

	//---initialization---//
	SensorType[S_TOUCH] = sensorTouch;
	SensorType[S_COLOR] = sensorColorNxtFULL;
	SensorType[S_ULTRA] = sensorSONAR;
	SensorType[S_SERVO] = sensorI2CCustom9V;

	//Declare Variables
	int QUANTITY;//from first line from input file
	int pointer=0;
	int cnt=0,QUANleft=0;
	Point listOfPoints[MAX];
	AngleSet listOfAngles[MAX];

		for (int i = 0; i < MAX; i++)
		{
			// account for (0,0,0) case
			listOfPoints[i].x = 1;
			listOfPoints[i].y = 1;
			listOfPoints[i].z = 1;
			listOfPoints[i].gP = 0;
			listOfPoints[i].isValid = false;
			listOfAngles[i].alpha = 0;
			listOfAngles[i].beta = 0;
			listOfAngles[i].theta = 0;
		}

	//Check IF File open
	TFileHandle fin;
	bool isFileOk = openReadPC(fin,"testfile.txt");
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
		playSoundFile("Warnning.rso");
		nxtDisplayCenteredTextLine(0, "Operating");
		wait1Msec(2000);
		displayString(2,"caution");//ex
		zeroZAxis();
		//-END- of auto-calibration


		//-BEGIN- start to performing
		nxtDisplayCenteredTextLine(0, "System Ready");
		displayString(2,"Press Any Button");
		displayString(3,"to begin the task");
		waitBtn();
		eraseDisplay();

		//---READY File input---//
		QUANleft=QUANTITY;
		while(cnt<QUANTITY)
		{
			pointer=0;
			for(int i=0;i<MAX&&i<QUANleft;i++)
			{
				readPoint(fin,listOfPoints[i]);
				pointer++;
				cnt++;
			}

			//---MASSAGE Input---//
			//Manipulating class - Converting points to joint angle and Validate if the point reachable
			for(int i=0;i<MAX&&i<QUANleft;i++)
			{
				listOfPoints[i].isValid = isPointValid(listOfPoints[i],listOfAngles[i]);
			}
			//--ACTION--//
			for(int i=0;i<MAX&&i<QUANleft;i++)
			{
				displayString(0,"%i",i);
				displayString(1,"x: %f",listOfPoints[i].x);
				displayString(2,"y: %f",listOfPoints[i].y);
				displayString(3,"z: %f",listOfPoints[i].z);
				if (listOfPoints[i].isValid)
				{
					moveRobot(listOfAngles[i]);
					displayString(4,"Alpha %d", listOfAngles[i].alpha);
					displayString(5,"Beta %d", listOfAngles[i].beta);
					displayString(6,"Theta %d", listOfAngles[i].theta);
					wait1Msec(listOfAngles[i].tMsDelay);
				}//END-if
				else{
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
				}//END-else
				gripperBalls();
			}//END-for
		 QUANleft-=MAX;
		}//END-while
	}

}
