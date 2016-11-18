#include <math.h>
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
		theta = calcTheta(input);

	}

}

bool isPointValid(Point& input) const
{
	// Author: Dustin Hu
	// Date: November 17th, 2016
	// Purpose: To validate the point
	bool output = false;

	return output;
}

float calcL(Point& input) const
{
	// Author: Dustin Hu
	// Date: November 17th, 2016
	// Purpose: To calculate the length of the line
	// Connecting the end effector and the base
	return sqrt(input.x * input.x + input.y * input.y);
}

float calcTheta(Point& input) const
{
	// Author: Dusti nHu
	// Date: November 17th, 2016
	// Purpose: to calculate the theta (Base angle) of the point
	return atan2(input.y, input.z);
}

float calcAlpha(Point& input, float L) const
{
	// Nov 17, 2016
	// Dustin Hu
	float alpha = calcAlpha1(input) + calcAlpha2(input, L);
}

float calcAlpha1(Point& input) const
{
	// Author: Dustin Hu
	// Date: November 17th, 2016
	// Purpose: to calculate alpha1
	return atan2(input.z, input.x);
}


float calcAlpha2(Point& input, float L) const
{
	// Author: Dustin Hu
	// Date: November 17th, 2016
	// Purpose: Calculate alpha2 using cosine law

	float numerator = FOREARM * FOREARM - SHOULDER * SHOULDER - L * L;
	float denominator = -2.0 * SHOULDER * L;
	return acos(numerator/denominator);
}
