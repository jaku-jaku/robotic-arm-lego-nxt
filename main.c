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
||        	Purpose:  THIS CLASS AIM TO PERFORM AS AN INDUSTRIAL ROBOT ARM
|| 			  DESIGN, WITH STRONG FOCUS ON PERFORMANCE, ACCURACY, AND 
||			  SAFETY.
||
||    	 Interfaces:    1. Auto-Calibration
|| 			2. Beeping sound and voice feedback for user
||			3. Safety protocol
||			4. Easy to use library [definitions.c]
||
|+------------------------------------------------------------------------------
||
||	BASIC_WORK_FLOW:  AUTO-CALIBRATION -> READ_POINTS_FROM_FILE -> CHECK_BOUNDARY
||				-> CONVERTION!!! -> CHECK_VALIDITY -> OUTPUT_TO_MOTOR
||
++------------------------------------------------------------------------------*/

#include "definitions.c"

//general btn function
void waitBtn() {
    while (nNxtButtonPressed == -1) {
    }
    while (nNxtButtonPressed != -1) {
    }
}//AUTHOR:JACK 

//Safety Visual and Sound Feedback 
void waitAndContinue() {
    displayString(3, "Starts in 5 seconds");
    displayString(4, "Step back!");
    //Give 5 seconds for operator leaving the platform
    for (int i = 0; i < 5; i++) {
        PlaySound(soundBeepBeep);
        wait1Msec(1000);
    }
    ClearSounds();
    playSoundFile("Warnning.rso");
    wait1Msec(1000);
    eraseDisplay();
}//AUTHOR:JACK 

//Safety Protocol
task stopIfUnsafe() {
    while (SensorValue[S_TOUCH] == 0) {
        gripperController(90);
        EndTimeSlice();
    }
    stopAllTasks();
}//AUTHOR:DUSTIN

task main() {
    gripperController(-20);
    //---initialization---//
    SensorType[S_TOUCH] = sensorTouch;
    SensorType[S_COLOR] = sensorColorNxtFULL;
    SensorType[S_ULTRA] = sensorSONAR;
    SensorType[S_SERVO] = sensorI2CCustom9V;

    StartTask(stopIfUnsafe);
    //Declare Variables & INITIALIZATION
    int QUANTITY; //TOTAL POINTS IN THE INPUT FILE
    int pointer = 0;
    int cnt = 0, QUANleft = 0;
    Point listOfPoints[MAX];
    AngleSet listOfAngles[MAX];

    for (int i = 0; i < MAX; i++) {
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
    bool isFileOk = openReadPC(fin, "test.txt");
    //ReadFile && Assign 20 coordinates
    if (isFileOk)
        readIntPC(fin, QUANTITY);
    if (!isFileOk && QUANTITY <= 0)
        displayString(0, "ERROR! File");
    else {
	//whole program
        //-BEGIN- Auto-Calibrating joint1
        nxtDisplayCenteredTextLine(0, "Calibrate!");
        displayString(2, "Press Any Button");
        displayString(3, "to begin");
        waitBtn(); //Wait for starting the program
        eraseDisplay();
        nxtDisplayCenteredTextLine(0, "Caution");
        waitAndContinue(); //safe waiting function
        nxtDisplayCenteredTextLine(0, "Operating");
        wait1Msec(2000);
        displayString(2, "caution"); //ex
        zeroZAxis();
        //-END- of auto-calibration


        //-BEGIN- start to performing
        PlaySound(soundBeepBeep);
        nxtDisplayCenteredTextLine(0, "System Ready");
        displayString(2, "GIVE THE BALL");
        displayString(3, "TO THE ROBOT!");
        gripperController(90);
        while (SensorValue[S_COLOR] == nothing) {}
        gripperController(20);
        eraseDisplay();
        waitAndContinue();
	    
        //---OPERATION---//
        QUANleft = QUANTITY;
        while (cnt < QUANTITY) {
            pointer = 0;
		
	    //---READ POINTS [INPUT]---//
            for (int i = 0; i < MAX && i < QUANleft; i++) {
                readPoint(fin, listOfPoints[i]);
                pointer++;
                cnt++;
            }
		
            //---POINTS CONVERTION AND VALIDATION---//
            //Manipulating class - Converting points to joint angle and Validate if the point reachable
            for (int i = 0; i < MAX && i < QUANleft; i++) {
                listOfPoints[i].isValid = isPointValid(listOfPoints[i], listOfAngles[i]);
            }
		
            //--MOTOR OUTPUT [OUTPUT]--//
            for (int i = 0; i < MAX && i < QUANleft; i++) {
                displayString(0, "%i", i);
                displayString(1, "x: %f", listOfPoints[i].x);
                displayString(2, "y: %f", listOfPoints[i].y);
                displayString(3, "z: %f", listOfPoints[i].z);
                if (listOfPoints[i].isValid) {
                    moveRobot(listOfAngles[i]);
                    displayString(4, "Alpha %d", listOfAngles[i].alpha);
                    displayString(5, "Beta %d", listOfAngles[i].beta);
                    displayString(6, "Theta %d", listOfAngles[i].theta);
                    wait1Msec(listOfAngles[i].tMsDelay);
                }//END-if
                else {
		    //--HANDLER FOR INVALID POINTS--//
		    //ASK USER IF SKIP AND CONTINUE NEXT OPERATION OR EXIT
                    eraseDisplay();
                    nxtDisplayCenteredTextLine(0, "ERROR");
                    displayString(2, "Do you want to");
                    displayString(3, "skip and continue");
                    displayString(4,"??? Any Button");
                    PlaySound(soundBeepBeep);
                    while (nNxtButtonPressed == -1) {}
                    ClearSounds();
                    while (nNxtButtonPressed != -1) {}
                    wait1Msec(500);
                    eraseDisplay();
                    displayString(4, "NEXT");
                }//END-else
            }//END-for
            QUANleft -= MAX;
        }//END-while
    }//END-else
}//AUTHOR:JACK 
