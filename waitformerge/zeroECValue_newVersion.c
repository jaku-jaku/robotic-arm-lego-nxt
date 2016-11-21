void zeroZAxis()
{
	float minDist = 255;
	int targetEC = 0;
	int tolerance = 0;
	int power = 40;
	int currentEC = 0;
	int distSum = 0;

	zeroECValue();
	rotate (true, power);
	while (getECValue() <= FULL_ROTATION_EC_VALUE)
	{
		distSum = 0;
		currentEC = getECValue();
		int n = 1;
		//Calculates avg. of distances it reads on the span of 1 EC
		//This minimizes the error in readings from the U.S. sensor
		while (currentEC == getECValue ()){
			distSum += getDistance();
			n++;
		}
		distAvg = distSum/n;
		if (distAvg < minDist)
			{
				minDist = distAvg;
				targetEC = currentEC;
			}
	}
	rotate (true, 0);
	zeroECValue();
	moveToTarget(targetEC, tolerance);
	zeroECValue();
}
