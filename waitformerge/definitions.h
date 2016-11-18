

const int SHOULDER; // First length, from J2-J3
const int FOREARM; // Second length, from J3-End
const int Z_OFFSET; // J1-J3 height

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
bool isPointValid(Point& input) const;

float calcL(Point& input) const;
float calcTheta(Point& input) const;
float calcAlpha(Point& input) const;
float calcAlpha1(Point& input) const;
float calcAlpha2(Point& input, float L) const;

float calcBeta(Point& input, float L) const;
float calcAlpha(Point& input, float L) const;

float atan2(float x, float y) const;
