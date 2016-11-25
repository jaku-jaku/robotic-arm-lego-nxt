
//PORT I/O assigning
const int S_COLOR = S2;
const int S_ULTRA = S3;
const int S_TOUCH = S1;
const int S_SERVO = S4;
const int J1 = motorA;
const int J2 = 1;
const int J3 = 2;
const int GRIPPER = 3;
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
	int tMsDelay;
	int gP;//Gripper Position
	bool isValid;
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
