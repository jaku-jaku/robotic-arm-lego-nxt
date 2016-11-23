const float J3_PHYS_LIM = 90;

float min (float a, float b)
{
	if (b<a)
		return b;
	return a;
}

float calcMaxForearmAngle (AngleSet & angleSet)
{
	float beta = 180-angleSet.alpha;
	return min (beta, J3_PHYS_LIM);
}


void moveToTarget(int targetEC, int tolerance)
{
	int moveSpeed = 30;//, DIFF=0, angleDiff=0,MAXspeed=70,MINspeed=10;
	bool cw = true;

	if (targetEC > FULL_ROTATION_EC_VALUE/2.0)
		cw= false;
	else
		targetEC+=FULL_ROTATION_EC_VALUE;

	rotate (cw, moveSpeed);
	while (abs(targetEC-getECValue()) > 0){}
	rotate(false, 0);
}

	/*
	angleDiff= targetEC - getECValue();

	wait1Msec(5000);
	float x=0;

	DIFF=angleDiff;
	MAXspeed=(int)((MAXspeed-MINspeed)*DIFF*2.0/FULL_ROTATION_EC_VALUE/10.0)+MINspeed;
	moveSpeed=30;
	//MAXspeed depends on the rotation difference
	while (angleDiff!=0)
	{
		displayString(3,"%f",moveSpeed);
		rotate(cw, moveSpeed);
	  angleDiff=targetEC-getECValue();
	}
	*/
