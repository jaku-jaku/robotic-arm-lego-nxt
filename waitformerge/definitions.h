

const int SHOULDER;
const int FOREARM;
const int Z_OFFSET;

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

float atan2(float x, float y);
void calcAngleSet(Point& input, AngleSet& output);
bool isPointValid(Point& input) const;

float calcL(Point& input) const;
float calcTheta(Point& input) const;

float calcBeta(Point& input, float L) const;
float calcAlpha(Point& input, float L) const;

float atan2(float x, float y) const;
