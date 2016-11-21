
#include "NXT_FileIO.c"

typedef struct {
	float x,y,z;
	bool isValid;
} Point;

const int L1 = 157;
const int L2 = 197;

// Check
// (p.x >= 0 && p.x-L1*cos(PI/6.0) >= 0) || (p.x < 0 && p.x-L1*cos(PI/6.0) < 0)
// (p.x >= 0 && p.x-L1*sin(PI/6.0) >= 0) || (p.x < 0 && p.x-L1*sin(PI/6.0) < 0) greater than upper bound check

bool isUpperOrLowerInRange(bool isAbove, float x, ) {

	bool isInRange = false;
	if (isAbove)
	{
		if ((x >= 0 && x-L1*sin(PI/6.0) >= 0) || (x < 0 && x-L1*sin(PI/6.0) < 0))
			isInRange = true;
	}
	else
	{
		if ((x >= 0 && x-L1*cos(PI/6.0) >= 0) || (x < 0 && x-L1*cos(PI/6.0) < 0))
			isInRange = true;
	}

	return isInRange;


}
bool isPointValid(Point p)
{
	//Ali Toyserkani Nov 20
	//Addition still needed, account for hitting itself within middle bound!!!!!!

	const float lowerZBound = -(L1+L2)*sin(PI/6.0);
	const float upperZBound = (L1+L2)*cos(PI/6.0);

	float distJ3ToPoint;
	float distBetween = sqrt(pow(p.x,2)+pow(p.y,2)+pow(p.z,2));
	float pythoXY = sqrt(p.x*p.x + p.y*p.y);
	float pythoL1L2 = sqrt(L1*L1 + L2*L2);

	bool isUpper = false;

	bool isOk = false;

	if (p.z > lowerZBound && p.z < upperZBound)
	{
		//distBetween = sqrt(pow(p.x,2)+pow(p.y,2)+pow(p.z,2));
		if (distBetween > pythoL1L2 && distBetween < (L1+L2))
		{
			isOk = true;
		}
	}
	else if (p.z < lowerZBound)
	{
		distJ3ToPoint = sqrt(pow(pythoXY-L1*cos(PI/6.0),2)+ pow(p.z-sin(PI/6.0),2));

		if (isUpperOrLowerInRange(false, p.x))
		{
			if (distBetween > pythoL1L2 && distJ3ToPoint < L2)
			{
				isOk = true;
			}
		}
	}
	else if (p.z > upperZBound)
	{

		distJ3ToPoint = sqrt(pow(pythoXY-L1*sin(PI/6.0),2)+ pow(p.z-cos(PI/6.0),2));

		if (isUpperOrLowerInRange(true, p.x))
		{
			if (distBetween > pythoL1L2 && distJ3ToPoint < L2)
			{
				isOk = true;
			}
		}
	}
	return isOk;
}


void readPoint(TFileHandle & fin, Point p) {

	readFloatPC(fin, p.x);
	readFloatPC(fin, p.y);
	readFloatPC(fin, p.z);

	bool currPointValid = isPointValid(p);

	p.isValid = currPointValid;


}

task main()
{
	TFileHandle fin;
	bool isFileOk = openReadPC(fin,"test.txt");
	if (!isFileOk)
		displayString(0,"You fucked up");

	Point filePoints[10];

	for (int i =0; i < 5; i++) {
		readPoint(fin,filePoints[i]);
		displayString(0,"%d",filePoints[i].isValid);
		wait1Msec(2000);
	}

	closeFilePC(fin);

}
