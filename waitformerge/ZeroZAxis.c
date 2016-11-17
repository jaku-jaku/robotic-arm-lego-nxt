const int fullRotationEC = 360*4;

int getECValue (int port){
	return nMotorEncoder [port];
}

void zeroECValue (int port){
	nMotorEncoder [port] = 0;
}

int getDistance (){
	return SensorValue [S3];
}

//THIS HAS TO CHANGE!! USE THE FUNCTION THAT MOVES THE MOTORS!! moveToTarget() IS A PROVISIONAL FUNCTION
void rotate (bool clockwise, int port, int power){
	if (!clockwise)
		power*-1;
	motor [port] = power;
}

void moveToTarget (int targetEC, int tolerance){	//Provisional function for proof of concept
	int moveSpeed = 75;
	//sigmoid function , PD control
	bool cw  = false;
	if (targetEC < fullRotation/2)
		cw = true;

	rotate (cw, motorA, moveSpeed);

	while (fabs(getECValue()-target) > tolerance);

	rotate (false, motorA, 0);
	//It will not be using rotate(). We will use moveMotor () function
}

void zeroZAxis (){
	zeroECValue (motorA);
	float minDist = 255;
	int targetEC = 0;
	const int Tolerance = 3, power = 40;

	rotate(true, motorA, power);

	while (getECValue(motorA) < fullRotation){
		if (usValue () < minDist){
			minDist = usValue ();
			targetEC = getECValue(motorA);
		}
	}

	rotate (true, motorA, 0);


	moveToTarget(targetEC);
	zeroECValue (motorA);
}
