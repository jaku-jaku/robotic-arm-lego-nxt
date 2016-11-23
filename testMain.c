#include "definitions.c"

task main()
{
	SensorType[S_ULTRA]=sensorSONAR;
	SensorType[S4] = sensorI2CCustom9V;

	Point a;
	AngleSet b;
	a.x = 100;
	a.y = 100;
	a.z = 100;

	zeroECValue();
	calcAngleSet(a, b);

	//moveToTarget(b.theta*5, 3);
	moveJ2(b);
	moveJ3(b);
	//setServoPosition(S4, 2, 90);


	delay(10000);
}
