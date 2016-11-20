
SensorType[S2] = sensorSONAR;
SensorTpye[S1] = sensorTouch;
SensorType[S3] = sensorColorNxtFULL;
SensorTpye[S4] = sensorCustom9V;

bool isSafe = true;


task SafetyMeasures()
{
	//account for statements while calibrating
	// dont check ultrasonic during this time


`	// this condition is DURING movement

	while (SensorValue[S1] > 15 && SensorValue[S1] == 0 && nNxtButtonPressed == -1 && ) {}
	isSafe = false;

}

task main() {

StartTask(SafetyMeasures);

// for all conditions, consider the global isSafe bool to stop the robot in
// any situation
}
