//library
#include "NXTServo-lib-UW.c"
//Constant
const int SColor=S1;
const int SUltra=S2;
const int STouch=S3;
const int SServo=S4;
const int Joint1=motorA;
const int Joint2=1;
const int Joint3=2;
const int Gripper=3;
const int MAX=20;
//Point Obj
typedef struct{
	float x;
	float y;
	float z;
	float t;
} Point;
typedef struct{
	float alpha;
	float beta;
	float thelta;
	float t;
} Angle;
//ReadCoordinateFromData
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
	//Check IF File open

	//Zero Axes

	//Declare Variables
	int QUANTITY;//first line from input file
	Point coor[MAX];
	Angle angle[MAX];
	//---READY---//
	//Ready, Screen Output, Wait for button pressed


	//ReadFile && Assign 20 coordinates
	for(int i=0;i<MAX;i++){
		if(!readNextPoint(coor[i])){
			i--;//skip this point
		}
	}
	//Manipulating class - MASSAGE IT!!!

	//--ACTION--//

	//--END--//
}
