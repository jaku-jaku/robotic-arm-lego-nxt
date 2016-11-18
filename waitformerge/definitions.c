
#include "definitions.h"




void calcAngleSet(Point& input, AngleSet& output)
{
	// Author: Dustin Hu
	// Date: November 17th, 2016
	// Purpose: To calculate the set of angles
	// Disclaimer: I have done a similar project
	// where I had to calculate the angles of a limb before
	if (isPointValid(input))
	{
		float L = calcL(input);
		float theta = calcTheta(input);

	}

}

bool isPointValid(Point& input)
{
	// Author: Dustin Hu
	// Date: November 17th, 2016
	// Purpose: To validate the point
	bool output = false;

	return output;
}

float calcL(Point& input)
{
	// Author: Dustin Hu
	// Date: November 17th, 2016
	// Purpose: To calculate the length of the line
	// Connecting the end effector and the base
	return sqrt(input.x * input.x + input.y * input.y);
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
	// Note: For our purposes, beta has to be shifted a bit when we output it
	// How much? Don't ask me.
	float numerator = (L * L) - (SHOULDER * SHOULDER) - (FOREARM * FOREARM);
	float denominator = -2.0 * SHOULDER * FOREARM;
	return numerator/denominator;
}


bool isXValid(Point& input)
{
	// Author: Dustin Hu
// Date: November 18th, 2016
// Purpose: To check if X is valid
// Note: Checks if x is valid by taking the length of the arm, subtract 10%,
// And then compares it to the x value.
// Also checks if the x value is greater than the minimum distance
	bool output = false;
	// X less than max value
	if (input.x > (MIN_X * 1.1) && input.x < (MAX_DIST * 0.9))
		output = true;
	return output;
}

bool isYValid(Point & input)
{
	// Author: Dustin Hu
	// Date: November 18th, 2016
	// Purpoes: To validate the Y input

}
bool isAlphaValid(float alpha)
{
	// Author: Dustin Hu
// Daet: November 18th, 2016
// Purpose: to check if alpha is valid
// Note: Assumes that there is a range of motion of pi/2 rad
// With a pi/6 segment chopped off at the top
// And a pi/3 segment chopped of at the bottom
	bool output = false;
	if ((5.0 * PI / 6.0) > alpha)
	{
		if (alpha > PI/3.0)
			output = true;
	}
	return output;
}
