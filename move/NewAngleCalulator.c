#include "NXTServo-lib-UW.c"

typedef struct {
	float x,y,z;
	bool isValid;
}Point;

float cosineLawAngle(float a, float b, float c)
{
	return acos((b*b + c*c - a*a)/ (2*b*c))
}
int toDegrees(float x) {
	return x*180/PI;
}

task main()
{

	SensorType [S4] = sensorI2CCustom9V;
	Point p;
	// p.x p.y p.z
	float x = 100, y= 100, z = 100;

	float L1 = 157;
	float L2 = 197;

	float newX = sqrt(x*x + y*y);

	float distPlanar = sqrt(newX*newX + z*z);

	float alpha = PI - cosineLawAngle(distPlanar,L1,L2);
	float beta = (acos(newX/sqrt(newX*newX + z*z))) + cosineLawAngle(L2, distPlanar, L1);
	float theta = acos(x/sqrt(x*x + y*y));

	//setServoPosition(S4, 1, 0.0333 * input.alpha * input.alpha - 3 * input.alpha - 30 );
	setServoPosition(S4, 1, toDegrees(beta) - 15);








}
