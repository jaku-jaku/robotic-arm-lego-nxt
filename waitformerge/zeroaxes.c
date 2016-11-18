//Constant
const int SColor=S1;
const int SUltra=S2;
const int STouch=S3;
const int SServo=S4;
const int Joint1=motorA;
const int Joint2=1;
const int Joint3=2;
const int Gripper=3;
const int MAX=20;
const int fullRotation = 360*5;
//----zeroing axes
int getECValue (){
	return nMotorEncoder [Joint1];
}

void zeroECValue (){
	nMotorEncoder [Joint1] = 0;
}

int getDistance (){
	return SensorValue [SUltra];
}

//THIS HAS TO CHANGE!! USE THE FUNCTION THAT MOVES THE MOTORS!! moveToTarget() IS A PROVISIONAL FUNCTION
void rotate (bool clockwise, int power){
	if (!clockwise)
		power*=-1;
	motor [Joint1] = power;
}

void moveToTarget (int targetEC, int tolerance){	//Provisional function for proof of concept
	int moveSpeed = 75;
	//sigmoid function , PD control
	bool cw  = true;
	if (targetEC > fullRotation/2.0){
		cw = false;
		targetEC= fullRotation/2.0-targetEC;
	}

	rotate (cw, moveSpeed);

	while ((fabs(getECValue())-fabs(targetEC)) <= tolerance);

	rotate (false, 0);
	//It will not be using rotate(). We will use moveMotor () function
}

void zeroZAxis (){
	zeroECValue ();
	float minDist = 255;
	int targetEC = 0;
	const int Tolerance = 0, power = 40;

	rotate(true, power);

	while (getECValue() <= fullRotation){
		if (getDistance () < minDist){
			minDist = getDistance ();
			targetEC = getECValue();
		}
	}
	displayString(2,"Position: %f", getDistance());
  displayString(3,"Position: %f",targetEC);
	rotate (true, 0);

	zeroECValue ();
	moveToTarget(targetEC,Tolerance);
	zeroECValue ();
}
void waitBtn(){
	while(nNxtButtonPressed==-1){}
	while(nNxtButtonPressed!=-1){}
}
//----------------------//
//-----Main Program-----//
//----------------------//
task main()
{
	SensorType[SUltra]=sensorSONAR;
	waitBtn();
	for(int i=0;i<3;i++){
		zeroZAxis();
		waitBtn();
	}
}
