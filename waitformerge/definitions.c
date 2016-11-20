#include "NXTServo-lib-UW.c"
#include "definitions.h"

task main()
{
	SensorType[S4] = sensorI2CCustom9V;
	Point a;
	AngleSet b;
	a.x = 100;
	a.y = 100;
	a.z = 300;

	calcAngleSet(a, b);
	/*
	(-90, 39)
	(-20, 1)
	(45, 46)
	(90, 60)

	*/
	displayString(0, "%f , %f", MIN_Z, MIN_X);
	wait1Msec(100000);
}


bool calcAngleSet(Point& input, AngleSet& output)
{
	// Author: Dustin Hu
	// Date: November 17th, 2016
	// Purpose: To calculate the set of angles
	// Input: The point to calculate to and the output angle set to outpu to
	// Output: True if successfully calculated
	// Note: It is assumed that this is a valid point
	// But it is not assumed that the angles that will be produced
	// will be valid
	// Disclaimer: I have done a similar project
	// where I had to calculate the angles of a limb before
	bool output = false;
	float L = calcL(input)
	float alpha = calcAlpha(input, L);
	float beta = calcBeta(input, L);
	float theta = calcTheta(input);
	if (areAnglesValid(alpha, beta))
	{
		output = true;
		output.alpha = alpha;
		output.beta = beta;
		output.theta = theta;
	}
	return output;
}



float calcL(Point& input)
{
	// Author: Dustin Hu
	// Date: November 17th, 2016
	// Purpose: To calculate the length of the line
	// Connecting the end effector and the origin (Check diagrams)
	return sqrt(input.x * input.x + input.z * input.z);
}

float calcTheta(Point& input)
{
	// Author: Dusti nHu
	// Date: November 17th, 2016
	// Purpose: to calculate the theta (Base angle) of the point
	return atan2(input.y, input.z);
}

float calcAlpha(Point& input, float L)
{
	// Nov 17, 2016
	// Dustin Hu
	return calcAlpha1(input) + calcAlpha2(input, L);
}

float calcAlpha1(Point& input)
{
	// Author: Dustin Hu
	// Date: November 17th, 2016
	// Purpose: to calculate alpha1
	return atan2(input.z, input.x);
}


float calcAlpha2(Point& input, float L)
{
	// Author: Dustin Hu
	// Date: November 17th, 2016
	// Purpose: Calculate alpha2 using cosine law

	float numerator = (FOREARM * FOREARM) - (SHOULDER * SHOULDER) - (L * L);
	float denominator = -2.0 * SHOULDER * L;
	return acos(numerator/denominator);
}

float calcBeta(Point& input, float L)
{
	// Author: Dustin Hu
	// Date: November 18th, 2016
	// Purpose: To calculate beta, the angle between the shouder
	// and the forearm
	float numerator = (L * L) - (SHOULDER * SHOULDER) - (FOREARM * FOREARM);
	float denominator = -2.0 * SHOULDER * FOREARM;
	return acos(numerator/denominator);
}


bool isAlphaValid(float alpha)
{
	// Author: Dustin Hu
// Daet: November 18th, 2016
// Purpose: to check if alpha is valid
// Input: An angle Alpha in radians
// Note: Assumes that there is a range of motion of pi/2 rad
// With a pi/6 segment chopped off at the top
// And a pi/3 segment chopped of at the bottom

	bool output = false;
	// To make reading easier
	alpha = radToDeg(alpha);

	if (alpha > 60 && alpha < 150)
	{
		output = true;
	}
	return output;
}

bool isBetaValid(float beta)
{
	// Author: Dustin Hu
// Date: November 20th, 2016
// Purpose: To check if the beta angle is valid
// Input: The angle beta in radians
// Note: Beta must be between -pi/2 and pi/2, with
// 0 defined as being parallel with J2
	bool output = false;
	// To make reading easier
 	beta = radToDeg(beta);
 	if (beta > -90 && beta < 90)
 	{
 		output = true;
 	}
 	return output;
}

bool areAnglesValid(float alpha, float beta)
{
	// Author: Dustin Hu
// date: November 20th, 2016
// Purpose: To validate the angle set
// Input: The angle set to validate
// Note: Theta doesn't need to be valid because all thetas are valid
// The base can rotate to any angle
	bool output = false;
	if (isAlphaValid(alpha) && isBetaValid(beta))
	{
		output = true;
	}
	return output;
}

float radToDeg(float rad)
{
	return rad * (180.0/PI);
}
