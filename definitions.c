<<<<<<< HEAD
=======
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
||	    Description:  This file contains all the functions for developers
||
|+------------------------------------------------------------------------------
++------------------------------------------------------------------------------*/

>>>>>>> r1remote/master
#include "NXTServo-lib-UW.c"
#include "NXT_FileIO.c"
#include "definitions.h"

<<<<<<< HEAD
=======
//--FILE INPUT--//
>>>>>>> r1remote/master
void readPoint(TFileHandle & in, Point & p0)
{
	readFloatPC(in, p0.x);
	readFloatPC(in, p0.y);
	readFloatPC(in, p0.z);
	readIntPC(in, p0.gP);
<<<<<<< HEAD
		readIntPC(in, p0.tMsDelay);
}

bool isZValueValid (Point p0)
{
	return (p0.z > GROUND_HEIGHT);
}
=======
	readIntPC(in, p0.tMsDelay);
}//Main Author(s): Ali

//--ANGLE VALIDATION--//
bool isZValueValid (Point p0)
{
	return (p0.z > GROUND_HEIGHT);
}//Main Author(s): Dustin
>>>>>>> r1remote/master

bool isWithinRange (Point p0)
{
	return (sqrt(p0.x*p0.x + p0.y*p0.y + p0.z*p0.z))	< MAX_DIST;
<<<<<<< HEAD
}


float calcAlpha(Point & input, float distanceXY, float distancePlane)
{
	/*
	Author: DUstin Hu
	Date: November 20th 2016
	Purpose: To calculate the angle relative to the vertical
	Input: THe point to move to 
			DistanceXY: The hypotenuse of the XY; base of the triangle formed with the XY Plane
			DistancePlane: THe base of the triangle to calculate the angle with
	Output: The angle in degrees
	*/
=======
}//Main Author(s): Dustin, Ali, Oswaldo

bool isPointValid(Point & p0, AngleSet & a0)
{
	//is point close enough to be able to be reached
	//check z value above the grounnd isZValueValid fun
	bool output = false;
	if (isWithinRange (p0) && isZValueValid (p0))
	{
		calcAngleSet(p0,a0); // calculates all 3 angles

		if (anglesValid (a0))
		{
			output = true;
		}
		//is alpha within range
		//is beta within range
		//if all of the above are okay, then go ahead and move.
	}
	a0.gP=p0.gP;
	a0.tMsDelay=p0.tMsDelay;
	//passing time delay
	return output;
}//Main Author(s): Dustin, Ali, Oswaldo

bool anglesValid (AngleSet & a0)
{
	bool output = false;
	if (a0.alpha <=ALPHA_MAX && a0.alpha >= ALPHA_MIN)
	{

		if (!(a0.beta < calcMaxBeta(a0)))
		{
		}
		else
		{
			output = true;
		}
	}
	return output;
}//Main Author(s): Dustin

//--ANGLE CALCULATION--//
float calcAlpha(Point & input, float distanceXY, float distancePlane)
{
>>>>>>> r1remote/master
	float a1 = atan2(input.z,distanceXY);
	float num = (FOREARM*FOREARM) - (SHOULDER*SHOULDER) - (distancePlane*distancePlane);
	float denom = -2.0 * SHOULDER * distancePlane;
	float a2 = acos(num/denom);

	return (180.0/PI)*(a1 + a2 + PI/2.0);
<<<<<<< HEAD
}

float calcBeta(Point & input, float distancePlane)
{
	/*
	Author: Dusti nHu
	Date :Nvomebre 20th, 2016
	Purpose: To calculate the angle beta 
	Input: The input point, in xyz
			The distance plane, which represents the distance from the tip of the gripper to the origin
			Origin is at midponit of the servos
	Output: The angle beta, which is +/-90 relative to the shoulder
	*/
=======
}//Main Author(s): Dustin

float calcBeta(Point & input, float distancePlane)
{
>>>>>>> r1remote/master
	float num = (distancePlane*distancePlane) - (SHOULDER*SHOULDER) - (FOREARM*FOREARM);
	float denom = -2.0*SHOULDER*FOREARM;

	return (180.0/PI)*(acos(num/denom) - PI); //might inverst PI and acos
<<<<<<< HEAD
}

float calcTheta(Point & input)
{
	/*
	Author: DUstin HU
	Dathe: November 20th 2016
	Purpose: To calculate the angle theta, the angle on the XY plane
	Input: The point to calculate with
	OUtput: The angle theta
	*/

	return (180.0/PI)*(atan2(input.y,input.x));
}
=======
}//Main Author(s): Dustin

float calcTheta(Point & input)
{
	return (180.0/PI)*(atan2(input.y,input.x));
}//Main Author(s): Dustin
>>>>>>> r1remote/master


void calcAngleSet(Point & inputP, AngleSet & outputA)
{
<<<<<<< HEAD
	/*
	AUthor: Dustin Hu
	Date: November 20th, 2016
	Purpose: To calculate the set of angles
	*/
=======
>>>>>>> r1remote/master
	float distXY = sqrt(inputP.x*inputP.x + inputP.y*inputP.y);
	float distPlanar = sqrt(distXY*distXY + inputP.z*inputP.z);

	outputA.alpha = calcAlpha(inputP,distXY,distPlanar);
	outputA.beta = calcBeta(inputP,distPlanar);
	outputA.theta = calcTheta(inputP);
<<<<<<< HEAD
}
=======
}//Main Author(s): Dustin
>>>>>>> r1remote/master

float min (float a, float b)
{
	if (b < a)
	{
		return b;
	}

	return a;
<<<<<<< HEAD
}
=======
}//Main Author(s): Dustin
>>>>>>> r1remote/master

float calcMaxBeta (AngleSet & a0)
{
	float beta = 180-a0.alpha;
	displayString(0,"%0.2f", beta);
	return min(beta, J3_PHYS_LIM);
<<<<<<< HEAD
}

bool anglesValid (AngleSet & a0)
{
	bool output = false;
	if (a0.alpha <=ALPHA_MAX && a0.alpha >= ALPHA_MIN)
	{

		if (!(a0.beta < calcMaxBeta(a0)))
		{
		}
		else
		{
			output = true;
		}
	}
	return output;
}

bool isPointValid(Point & p0, AngleSet & a0)
{
	//is point close enough to be able to be reached
	//check z value above the grounnd isZValueValid fun
	bool output = false;
	if (isWithinRange (p0) && isZValueValid (p0))
	{
		calcAngleSet(p0,a0); // calculates all 3 angles

		if (anglesValid (a0))
		{
			output = true;
		}
		//is alpha within range
		//is beta within range
		//if all of the above are okay, then go ahead and move.
	}
	a0.gP=p0.gP;
	a0.tMsDelay=p0.tMsDelay;
	//passing time delay
	return output;
}

=======
}//Main Author(s): Dustin

//GetEC() return absolute position Encoder Value [0-360*5] of Joint1 relative to 0 position
>>>>>>> r1remote/master
int getEC(){
	int ECvalue=nMotorEncoder[motorA]%FULL_ROTATION_EC;
	//displayString(1,"%f",ECvalue);
	if(ECvalue<0){
		ECvalue+=FULL_ROTATION_EC;
	}
	//displayString(2,"%f",ECvalue);
	return ECvalue;
<<<<<<< HEAD
}
=======
}//Main Author(s): Jack, Oswaldo

//zeroing
void zeroZAxis()
{
	float minDist = 255;
	int targetEC = 0;
	int power = 30;
	int currentEC = 0;
	int distSum = 0;
	int distAvg = 0;

	moveJoint2(120);
	moveJoint3(-70);
	nMotorEncoder[J1]=0;
	motor[J1]=power;
	while (nMotorEncoder[J1] < FULL_ROTATION_EC)
	{
		distSum = 0;
		currentEC = nMotorEncoder[J1];
		int n = 1;
		//Calculates avg. of distances it reads on the span of 1 Degree
		while (fabs(currentEC-nMotorEncoder[J1])<=GEAR_REDUCTION ){
			distSum += SensorValue[S_ULTRA];
			n++;
		}
		distAvg=distSum*1.0/n;
		if (distAvg < minDist)
		{
			minDist = distAvg;
			targetEC = currentEC;
			displayString(7,"Found %f",targetEC);
		}
	}
	motor[J1]=0;
	//displayString(6,"Current %f",getEC());
	//wait1Msec(2000);
	moveJoint1(targetEC*1.0/GEAR_REDUCTION);
	nMotorEncoder[J1]=0;
}//Main Author(s): Oswaldo, Jack
>>>>>>> r1remote/master

int smoothMotionFunc(float index0, int MAXspeed0,int MINspeed0){
	float percent=0;
	if(index0>1){
		percent=1;
	}else
		percent=1/(1+pow(10,(2-4*index0));
	return ((int)((MAXspeed0-MINspeed0)*percent)+MINspeed0);
	//y=1/(1+10^(2-4x))
	//On theory accelerate 0-1 in 0-1
	//and after x=1, y->1
	//so for computation, we do not need to calculate input after x=1
<<<<<<< HEAD
}
=======
}//Main Author(s): Jack
>>>>>>> r1remote/master

int smoothMotion(int curECdif, int initialECDiff){
	int MAXspeed=70,MINspeed=10;
	float index=0, ANGLECHANGE=40;
<<<<<<< HEAD
	//20 degree for changing speed
=======
	//40 degree for changing speed
>>>>>>> r1remote/master
	index=curECdif;
	if(curECdif>initialECDiff/2.0){
		index=initialECDiff-index;
		//reverse at middle of the action to gain slow down in the end
	}
	index=index/(ANGLECHANGE*5);
		//displayString(2,"%f",index);
	return smoothMotionFunc(index, MAXspeed,MINspeed);
<<<<<<< HEAD
}
=======
}//Main Author(s): Jack
			   
>>>>>>> r1remote/master
void moveJoint1(float ang)
{
	int power=0;
	if(ang<0)
		ang+=360;
	int targetEC = (int)(ang*FULL_ROTATION_EC/360.0);
	int forward=1,cw=1;//1 f/ -1 b
	//displayString(6,"%i",targetEC);
	int diff=targetEC-getEC();
	int initDiff=diff;
		//displayString(7,"%i",getEC());
		//wait1Msec(2000);
	while(diff!=0){
		forward=1;
		cw=1;
		if(abs(diff)>FULL_ROTATION_EC/2.0){
			forward=-1;
		}
		if(diff>0){
			cw=-1;
		}
			//displayString(7,"%i",getEC())
			power=smoothMotion(fabs(initDiff-diff),fabs(initDiff));
		motor[J1] = -1*power*cw*forward;
  	diff=targetEC-getEC();
  	//displayString(7,"%i",getEC());
  	if(diff==0){
  			motor[J1] = 0;
  	}
  }
	motor[J1] = 0;
<<<<<<< HEAD
}

void moveJoint2(float ang)
{
	// AUthor: DUstin Hu
	// Date: November 24th 2016
	// Purpose: To move the second joint. 
	// Input: Angle between 60 and 150 degrees
	// Reasoning behind the quadratic: The servos don't seem to operate linearly. The motors don't help.
	// I'm guessing torque and gravity. Not sure. Will put method of obtaining it on report.
	setServoPosition(S_SERVO, J2, 0.0014*ang*ang +1.5288*ang - 173.79 );   // QUAD: 0.0014*ang*ang +1.5288*ang - 173.79
}

void moveJoint3(float ang)
{
		// AUthor: DUstin Hu	
	// Date: November 24th 2016
	// Purpose: To move the second joint. 
	// Input: Angle between 60 and 150 degrees
	// Reasoning behind the quadratic: The servos don't seem to operate linearly. The motors don't help.
	// I'm guessing torque and gravity. Not sure. Will put method of obtaining it on report.
	setServoPosition(S_SERVO, J3, -0.0007*ang*ang + 0.9882*ang + 21.773); // -0.0007*ang*ang + 0.9882*ang + 21.773
}

void moveRobot(AngleSet & a0)
{
	// AUthor: Dustin Hu
	// Date: November 24th 2016
	// Purpose: To move the whole robot
	// Input: the angle set to move to
	moveJoint2(a0.alpha);
	moveJoint3(a0.beta);
	moveJoint1(a0.theta);
}

//zeroing
void zeroZAxis()
{
	float minDist = 255;
	int targetEC = 0;
	int power = 30;
	int currentEC = 0;
	int distSum = 0;
	int distAvg = 0;

	moveJoint2(120);
	moveJoint3(-70);
	nMotorEncoder[J1]=0;
	motor[J1]=power;
	while (nMotorEncoder[J1] < FULL_ROTATION_EC)
	{
		distSum = 0;
		currentEC = nMotorEncoder[J1];
		int n = 1;
		//Calculates avg. of distances it reads on the span of 1 Degree
		while (fabs(currentEC-nMotorEncoder[J1])<=GEAR_REDUCTION ){
			distSum += SensorValue[S_ULTRA];
			n++;
		}
		distAvg=distSum*1.0/n;
		if (distAvg < minDist)
		{
			minDist = distAvg;
			targetEC = currentEC;
			displayString(7,"Found %f",targetEC);
		}
	}
	motor[J1]=0;
	//displayString(6,"Current %f",getEC());
	//wait1Msec(2000);
	moveJoint1(targetEC*1.0/GEAR_REDUCTION);
	nMotorEncoder[J1]=0;
}


void gripperController(int angle){
	if (angle>=0||angle<=180)
		setServoPosition(S_SERVO, GRIPPER, angle)
}
=======
}//Main Author(s): Dustin

void moveJoint2(float ang)
{
	setServoPosition(S_SERVO, J2, 0.0014*ang*ang +1.5288*ang - 173.79 );   // QUAD: 0.0014*ang*ang +1.5288*ang - 173.79
}//Main Author(s): Dustin

void moveJoint3(float ang)
{
	setServoPosition(S_SERVO, J3, 0.0012*ang*ang + 0.9262*ang - 14.1); // -0.0007*ang*ang + 0.9882*ang + 21.773
}//Main Author(s): Dustin

void moveRobot(AngleSet & a0)
{
	moveJoint2(a0.alpha);
	moveJoint3(a0.beta);
	moveJoint1(a0.theta);
}//Main Author(s): Dustin

void gripperController(int angle){
	if (angle>=0||angle<=180)
		setServoPosition(S4,7, angle)
}//Main Author(s): Jack
			   
>>>>>>> r1remote/master
void gripperBalls(){
	//nxtDisplayCenteredTextLine(3, "%f",SensorValue[S2] );
	if(SensorValue[S_COLOR]==nothing||SensorValue[S_TOUCH]==1)
		gripperController(90);
	else{
		gripperController(20);
	}
<<<<<<< HEAD
}


=======
}//Main Author(s): Jack

//controller mapping
>>>>>>> r1remote/master
int map(int inputMin, int inputMax, int outputMin, int outputMax, int input)
{
	//https://www.arduino.cc/en/Reference/Map
	return (input - inputMin) * (outputMax - outputMin) / (inputMax - inputMin) + outputMin;
<<<<<<< HEAD
}
=======
}//Main Author(s): Dustin, Ali
			   
//NOTES: MAIN CONTRIBUTORS SPECIFIED NEXT TO EACH FUNCTION. HOWEVER, EVERYONE[JACK, ALI, DUSTIN, OSWALDO] 
//	ON TEAM JADO FULLY UNDERSTANDS AND CONTRIBUTED TO THE ENTIRE PROGRAM.
>>>>>>> r1remote/master
