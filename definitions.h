
// DO NOT USE RADIANSTODEGREES. IT CONVERTS IT TO A SHORT.
const int S_COLOR = S1;
const int S_ULTRA = S2;
const int S_TOUCH = S3;
const int S_SERVO = S4;
const int J1 = motorA;
const int J2 = 1;
const int J3 = 2;
const int GRIPPER = 3;
const int MAX = 8;
const int FULL_ROTATION_EC_VALUE = 360 * 5;
const int SHOULDER = 157; // First length, from J2-J3 in mm
const int FOREARM = 197; // Second length, from J3-End in mm
const int Z_OFFSET = 112; // J1-J3 height in mm
const int THICKNESS = 20; // Thickness of bars
const int MIN_DIST = sqrt(SHOULDER * SHOULDER + FOREARM * FOREARM);
const int MAX_DIST = SHOULDER + FOREARM;
const int MIN_Z = MIN_DIST * cos(PI/6.0);
const int MIN_X = MIN_DIST * sin(PI/6.0);


typedef struct
{
	float x;
	float y;
	float z;
	int tMs;
	int gP;//Gripper Position
	bool isValid;
} Point;

typedef struct
{
	float alpha;
	float beta;
	float theta;
	int tMs;
		int gP;//Gripper Position
	bool isValid;
} AngleSet;

// Dustin Hu
bool calcAngleSet(Point& input, AngleSet& outputAngles);

float calcL(Point& input);
float calcTheta(Point& input);
float calcAlpha(Point& input, float L);
float calcAlpha1(Point& input);
float calcAlpha2(Point& input, float L);
float calcBeta(Point& input, float L);

bool isAlphaValid(float alpha);
bool isBetaValid(float beta);
bool areAnglesValid(float alpha, float beta);
//servoOutput
void moveJ2(AngleSet& input);
void moveJ3(AngleSet& input);

float radToDeg(float rad);

// Oswaldo Ferro Hernandez
int getECValue();
int getDistance();
int angleToEC(float angle);

void zeroECValue();
void rotate(bool clockwise, int power);
void moveToTarget(int targetEC, int tolerance);
void zeroZAxis();
void gripperController(int angle);

// Ali Toyserkani
bool isUpperOrLowerInRange(bool isAbove, float x);
bool isPointValid(Point& p);
void readPoint(TFileHandle & fin, Point p);

//
float calcMaximumBeta(AngleSet& input);
float calcDist(Point& input);
float cosineLawAngle(float dist);
