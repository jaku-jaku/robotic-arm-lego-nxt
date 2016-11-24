#include "NXTServo-lib-UW.c"
#include "NXT_FileIO.c"

const int GROUND_HEIGHT = -200;
const int FOREARM = 197;
const int SHOULDER = 157;
const int MAX_DIST = SHOULDER + FOREARM;
const int ALPHA_MAX = 150;
const int J3_PHYS_LIM = 90;
const int ALPHA_MIN = 60;
const int NUM_POINTS = 10;
const int GEAR_REDUCTION = 5;
const int FULL_ROTATION_EC = 360 * GEAR_REDUCTION;

typedef struct
{
	float x , y , z;
	int gP, timeDelay; // timer will be used to control how long arm stays at each point
	bool isValid;
} Point;

typedef struct
{
	float alpha;
	float beta;
	float theta;
} AngleSet;

void readPoint(TFileHandle & in, Point & p0)
{
	readFloatPC(in, p0.x);
	readFloatPC(in, p0.y);
	readFloatPC(in, p0.z);
	readIntPC(in, p0.gP);
}

bool isZValueValid (Point p0)
{
		return (p0.z > GROUND_HEIGHT);
}

bool isWithinRange (Point p0)
{
	return (sqrt(p0.x*p0.x + p0.y*p0.y + p0.z*p0.z))	< MAX_DIST;
}


float calcAlpha(Point & input, float distanceXY, float distancePlane)
{
	float a1 = atan2(input.z,distanceXY);
	float num = (FOREARM*FOREARM) - (SHOULDER*SHOULDER) - (distancePlane*distancePlane);
	float denom = -2.0 * SHOULDER * distancePlane;
	float a2 = acos(num/denom);

	return (180.0/PI)*(a1 + a2 + PI/2.0);
}

float calcBeta(Point & input, float distancePlane)
{
	float num = (distancePlane*distancePlane) - (SHOULDER*SHOULDER) - (FOREARM*FOREARM);
	float denom = -2.0*SHOULDER*FOREARM;

	return (180.0/PI)*(acos(num/denom) - PI); //might inverst PI and acos
}

float calcTheta(Point & input)
{
	return (180.0/PI)*(atan2(input.y,input.x));
}


void calcAngleSet(Point & inputP, AngleSet & outputA)
{
	float distXY = sqrt(inputP.x*inputP.x + inputP.y*inputP.y);
	float distPlanar = sqrt(distXY*distXY + inputP.z*inputP.z);

	outputA.alpha = calcAlpha(inputP,distXY,distPlanar);
	outputA.beta = calcBeta(inputP,distPlanar);
	outputA.theta = calcTheta(inputP);
}

float min (float a, float b)
{
		if (b < a)
		{
			return b;
		}

		return a;
}

float calcMaxBeta (AngleSet & a0)
{
	float beta = 180-a0.alpha;
	displayString(0,"%0.2f", beta);
	return min(beta, J3_PHYS_LIM);
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
	return output;
}
int getEC(){
 return nMotorEncoder[motorA]%FULL_ROTATION_EC;
}

void moveJoint1(float ang)
{
	// might need to fix for going backwards direction
	int targetEC = (ang*FULL_ROTATION_EC/360);

	if (targetEC < FULL_ROTATION_EC/2.0)
		motor[motorA] = 50;
	else
	{
		motor [motorA] = -50;
		targetEC = FULL_ROTATION_EC-targetEC;
	}

	while((abs(targetEC) - abs(getEC()))!= 0){}

	motor[motorA] = 0;



	//if (targetEC > nMotorEncoder[motorA])
	//{
	//	motor[motorA] = 40;
	//	while(nMotorEncoder[motorA] < targetEC) {}
	//}
	//else if (targetEC < nMotorEncoder[motorA])
	//{
	//	motor[motorA] = -40;
	//	while (targetEC > nMotor
	//}






	//motor[motorA] = 40;
	//while (nMotorRunState[motorA] != runStateIdle) {}
	//motor[motorA] = 0;
}

void moveJoint2(float ang)
{
	setServoPosition(S4, 1, 0.0014*ang*ang +1.5288*ang - 173.79 );   // QUAD: 0.0014*ang*ang +1.5288*ang - 173.79
}

void moveJoint3(float ang)
{
	setServoPosition(S4, 2, -0.0007*ang*ang + 0.9882*ang + 21.773); // -0.0007*ang*ang + 0.9882*ang + 21.773
}

void moveRobot(AngleSet & a0)
{
	moveJoint2(a0.alpha);
	moveJoint3(a0.beta);
	moveJoint1(a0.theta);

}

task main()
{
	// zero encoder as well after calibration

	SensorType[S1] = sensorTouch;
	SensorType[S2] = sensorColorNxtFULL;
	SensorType[S3] = sensorSONAR;
	SensorType[S4] = sensorI2CCustom9V;

	nMotorEncoder[motorA] = 0;
	moveJoint1(70);
	wait1Msec(1000);
	TFileHandle fin;
	bool isFileOk = openReadPC(fin,"testNov23.txt");
	if (!isFileOk)
	{
		displayString(0,"youre fucked");
		wait1Msec(5000);
	}
	else {

	Point listPoints[NUM_POINTS];
	AngleSet listAngles[NUM_POINTS];

	for (int i = 0; i < NUM_POINTS; i++)
	{
		// account for (0,0,0) case
		listPoints[i].x = 1;
		listPoints[i].y = 1;
		listPoints[i].z = 1;
		listPoints[i].gP = 0;
		listPoints[i].isValid = false;
		listAngles[i].alpha = 0;
		listAngles[i].beta = 0;
		listAngles[i].theta = 0;
	}

	for (int i = 0; i < NUM_POINTS; i++)
	{
		readPoint(fin,listPoints[i]);
	}

	for (int i = 0; i < NUM_POINTS; i++)
	{
		listPoints[i].isValid = isPointValid(listPoints[i],listAngles[i]);
	}
	for (int i = 0; i < NUM_POINTS; i++)
	{
		if (listPoints[i].isValid)
		{
			moveJoint2(90);
			moveJoint3(0);
			wait1Msec(1000);
			moveRobot(listAngles[i]);
			displayString(0,"X %d", listPoints[i].x);
			displayString(1,"Y %d", listPoints[i].y);
			displayString(2,"Z %d", listPoints[i].z);
			displayString(3,"Alpha %d", listAngles[i].alpha);
			displayString(4,"Beta %d", listAngles[i].beta);
			displayString(5,"Theta %d", listAngles[i].theta);
			wait1Msec(3000);
		}
		else{
			displayString(0, "Invalid");
			wait1Msec(5000);
			}
	}
}
}
