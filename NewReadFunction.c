
#include "NXT_FileIO.c"

typedef struct {
	float x,y,z;
	bool isValid;
} Point;

const int L1 = 157;
const int L2 = 197;

// Check 
bool isPointValid(Point p)
{
	//Ali Toyserkani Nov 20
	//Addition still needed, account for hitting itself within middle bound!!!!!!

	float distJ3ToPoint;
	float distBetween = sqrt(pow(p.x,2)+pow(p.y,2)+pow(p.z,2));
	float pythoXY = sqrt(p.x*p.x + p.y*p.y);
	float pythoL1L2 = sqrt(L1*L1 + L2*L2);
	bool isOk = false;
	if (p.z > (-(L1+L2)*sin(PI/6.0)) && p.z < (L1+L2)*cos(PI/6.0))
	{
		//distBetween = sqrt(pow(p.x,2)+pow(p.y,2)+pow(p.z,2));
		if (distBetween > pythoL1L2 && distBetween < (L1+L2))
		{
			isOk = true;
		}
	}
	else if (p.z < (-(L1+L2)*sin(PI/6.0)))
	{
		distJ3ToPoint = sqrt(pow(pythoXY-L1*cos(PI/6.0),2)+ pow(p.z-sin(PI/6.0),2));
		
		if ((p.x >= 0 && p.x-L1*cos(PI/6.0) >= 0) || (p.x < 0 && p.x-L1*cos(PI/6.0) < 0))
		{
			if (distBetween > pythoL1L2 && distJ2ToPoint < L2)
			{
				isOk = true;
			}
		}
	}
	else if (p.z > (L1+L2)*cos(PI/6.0))
	{
		
		distJ3ToPoint = sqrt(pow(pythoXY-L1*sin(PI/6.0),2)+ pow(p.z-cos(PI/6.0),2));
		
		if ((p.x >= 0 && p.x-L1*sin(PI/6.0) >= 0) || (p.x < 0 && p.x-L1*sin(PI/6.0) < 0))
		{
			if (distBetween > pythoL1L2 && distJ2ToPoint < L2)
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

	Point filePoints[3];
	
	for (int i =0; i < 3; i++) {
		readPoint(fin,filePoints[i]);
		displayString(0,"%f",filePoints[i].x);
		wait1Msec(2000);
	}

	closeFilePC(fin);

}
