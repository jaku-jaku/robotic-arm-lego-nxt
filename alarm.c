#include "definitions.c"

void waitButtonPressRelease ()
{
	while (nNxtButtonPressed == -1){}
	while (nNxtButtonPressed !=-1) {}
}

void alarmSystem ()
{
	bool detected = false;
	int rotSpeed = 30;
	int USRange = 150;

	displayString (0, "Press any button");
	displayString (1, "to arm alarm.");

	waitButtonPressRelease ();

	motor [motorA] = rotSpeed;
	moveJoint3 (0);

	while (!detected)
	{
		if (sensorValue[S_ULTRA] > USRange)
			detected = true;
		else if (time1 [T1] %150 == 0){
			moveJoint2 (amplitude * sin (time1[T1]/1000.0));
			if (time1 [T1]/1000.0 >= 2*PI)
				resetTimer (T1);
		}
	}
	eraseDisplay();
	displayString (0, "Press any button");
	displayString (1, "to disarm.");

	resetTimer (T1);

	while (nNxtButtonPressed ==-1)
	{
		playSound (soundBeepBeep);
		wait1Msec (500);
	}
}
