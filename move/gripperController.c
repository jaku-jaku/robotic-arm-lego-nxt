#include "NXTServo-lib-UW.c"

const int S_SERVO = S4;
const int GRIPPER = 3;

void gripperController(int angle){	//0 closed, 180 open
	if (angle>=0||angle<=180)
		setServoPosition (S_SERVO, GRIPPER, angle);
}
task main (){
		SensorType [S_SERVO] = sensorI2CCustom9V;

		setServoPosition(S4,1,0);
}
