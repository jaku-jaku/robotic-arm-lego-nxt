
#include "NXT_FileIO.c"

typedef struct {
	float x,y,z;
	bool isValid;
} Point;

const int L1 = 155;
const int L2 = 155;

bool isPointValid(Point p)
{
	float distBetween;
	bool isOk = false;
	if (p.z > (-(L1+L2)*sin(PI/6.0)) && p.z < (L1+L2)*cos(PI/6.0))
	{
		distBetween = sqrt(pow(p.x,2)+pow(p.y,2)+pow(p.z,2));
		if (distBetween > L1 && distBetween < (L1+L2))
		{
			isOk = true;
		}
	}
	else if (p.z < (-(L1+L2)*sin(PI/6.0)))
	{
		distBetween = sqrt(pow(p.x-L1*cos(PI/6.0),2)+ pow(p.z-sin(PI/6.0),2));
		if ((p.x >= 0 && p.x-L1*cos(PI/6.0) >= 0) || (p.x < 0 && p.x-L1*cos(PI/6.0) < 0))
		{
			if (distBetween < L2)
			{
				isOk = true;
			}
		}
	}
	else if (p.z > (L1+L2)*cos(PI/6.0))
	{
		distBetween = sqrt(pow(p.x-L1*sin(PI/6.0),2)+ pow(p.z-cos(PI/6.0),2));
		if ((p.x >= 0 && p.x-L1*sin(PI/6.0) >= 0) || (p.x < 0 && p.x-L1*sin(PI/6.0) < 0))
		{
			if (distBetween < L2)
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


	Point p1;
	readPoint(fin, p1);

	closeFilePC(fin);



}
