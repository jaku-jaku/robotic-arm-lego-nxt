#include <math.h>
#include "definitions.h"



void calcAngleSet(Point& input, AngleSet& output)
{
	if (isPointValid(input))
	{
		float L = calcL(input);
		
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

float 