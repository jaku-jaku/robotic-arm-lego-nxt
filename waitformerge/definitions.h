

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
	float t;
} Point;

typedef struct
{
	float alpha;
	float beta;
	float theta;
	float t;
} AngleSet;

void calcAngleSet(Point& input, AngleSet& output);
bool isPointValid(Point& input);

float calcL(Point& input);
float calcTheta(Point& input);
float calcAlpha(Point& input, float L);
float calcAlpha1(Point& input);
float calcAlpha2(Point& input, float L);
float calcBeta(Point& input, float L);

bool isXValid(Point& input);
bool isYValid(Point& input);

bool isAlphaValid(float alpha);
