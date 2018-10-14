<<<<<<< HEAD

//PORT I/O assigning
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
||	    Description:  This header file contains all the functions for developers
||
|+------------------------------------------------------------------------------

++------------------------------------------------------------------------------*/

//PORT I/O 
>>>>>>> r1remote/master
const int S_COLOR = S2;
const int S_ULTRA = S3;
const int S_TOUCH = S1;
const int S_SERVO = S4;
const int J1 = motorA;
const int J2 = 1;
const int J3 = 2;
<<<<<<< HEAD
const int GRIPPER = 3;
=======
const int GRIPPER = 7;
>>>>>>> r1remote/master
const int MAX = 8;
//ROBOT MECHANICAL DATA
const int GROUND_HEIGHT = -230;
const int FOREARM = 197;
const int SHOULDER = 157;
const int MAX_DIST = SHOULDER + FOREARM;
const int ALPHA_MAX = 150;
const int J3_PHYS_LIM = 90;
const int ALPHA_MIN = 60;
const int NUM_POINTS = 10;
const int GEAR_REDUCTION = 5;
const int FULL_ROTATION_EC = 360 * GEAR_REDUCTION;
//colorSensorValue
const int Basketball=2;
const int Tennisball=3;
const int nothing=1;
const int football=6;

typedef struct
{
	float x;
	float y;
	float z;
<<<<<<< HEAD
	int tMsDelay;
	int gP;//Gripper Position
	bool isValid;
=======
	int tMsDelay;	//Timer Delay Ms
	int gP;		//Gripper Position
	bool isValid;	
>>>>>>> r1remote/master
} Point;

typedef struct
{
	float alpha;
	float beta;
	float theta;
	int tMsDelay;
	int gP;//Gripper Position
	bool isValid;
} AngleSet;

//FileIO
<<<<<<< HEAD
// Ali Toyserkani
void readPoint(TFileHandle & in, Point & p0);
//AngleValidation
// Oswaldo Ferro Hernandez
bool isZValueValid (Point p0);
bool isWithinRange (Point p0);
bool isPointValid(Point & p0, AngleSet & a0);

//AngleCalculation
//Dustin Hu
float calcAlpha(Point & input, float distanceXY, float distancePlane);
float calcBeta(Point & input, float distancePlane);
float calcTheta(Point & input);
void calcAngleSet(Point & inputP, AngleSet & outputA);

// Oswaldo Hernandez
float min (float a, float b);
float calcMaxBeta (AngleSet & a0);
bool anglesValid (AngleSet & a0);
int getEC();
// Jack Xu
int smoothMotionFunc(float index0, int MAXspeed0,int MINspeed0);
int smoothMotion(int curECdif, int initialECDiff);
void moveJoint1(float ang);

// Dustin Hu
void moveJoint2(float ang);
void moveJoint3(float ang);
void moveRobot(AngleSet & a0);

// Jack Xu
void gripperController(int angle);
void gripperBalls();
void waitBtn();
void waitAndContinue();
=======
void readPoint(TFileHandle & in, Point & p0); //Main Author(s): Ali
//AngleValidation
bool isZValueValid (Point p0); //Main Author(s): Dustin
bool isWithinRange (Point p0); //Main Author(s): Dustin, Ali, Oswaldo
bool isPointValid(Point & p0, AngleSet & a0); //Main Author(s): Dustin, Ali, Oswaldo
bool anglesValid (AngleSet & a0);//Main Author(s): Dustin
//AngleCalculation
float calcAlpha(Point & input, float distanceXY, float distancePlane); //Main Author(s): Dustin
float calcBeta(Point & input, float distancePlane);//Main Author(s): Dustin
float calcTheta(Point & input);//Main Author(s): Dustin
void calcAngleSet(Point & inputP, AngleSet & outputA);//Main Author(s): Dustin
float min (float a, float b);//Main Author(s): Dustin
float calcMaxBeta (AngleSet & a0);//Main Author(s): Dustin
int getEC();//Main Author(s): Jack, Oswaldo
void zeroZAxis();//Main Author(s): Oswaldo, Jack
int smoothMotionFunc(float index0, int MAXspeed0,int MINspeed0);//Main Author(s): Jack
int smoothMotion(int curECdif, int initialECDiff);//Main Author(s): Jack
void moveJoint1(float ang);//Main Author(s): Dustin
void moveJoint2(float ang);//Main Author(s): Dustin
void moveJoint3(float ang);//Main Author(s): Dustin
void moveRobot(AngleSet & a0);//Main Author(s): Dustin
void gripperController(int angle);//Main Author(s): Jack
void gripperBalls();//Main Author(s): Jack
//controller mapping
int map(int inputMin, int inputMax, int outputMin, int outputMax, int input);
//NOTES: MAIN CONTRIBUTORS SPECIFIED NEXT TO EACH FUNCTION. HOWEVER, EVERYONE[JACK, ALI, DUSTIN, OSWALDO] 
//	ON TEAM JADO FULLY UNDERSTANDS AND CONTRIBUTED TO THE ENTIRE PROGRAM.
>>>>>>> r1remote/master
