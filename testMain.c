#include "definitions.c"

task main()
{
	SensorType[S_ULTRA]=sensorSONAR;
	SensorType[S4] = sensorI2CCustom9V;

	Point a;
	AngleSet b;
	a.x = 260;
	a.y = 150;
	a.z = 49;

	setServoPosition(S4, 1, 0);
	setServoPosition(S4, 2, 0);
	delay(1000);
	zeroECValue();
	calcAngleSet(a, b);

	//moveToTarget(b.theta*5, 3);
	moveJ2(b);
	moveJ3(b);
	//setServoPosition(S4, 1, -25);
	//setServoPosition(S4, 2, -50);

	moveToTarget(b.theta * 5, 3);
	//setServoPosition(S4, 2, 90);
	//setServoPosition(S4, 2, -55);
	//setServoPosition(S4, 1, 50);
	wait1Msec(100000);
}
