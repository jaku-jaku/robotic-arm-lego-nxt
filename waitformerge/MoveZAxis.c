//Moving the Z axis

const int GEARREDUCTION = 5;

int angleToEC (float angle){	//Returns the ec that it must move
	return angle * GEARREDUCTION - getECValue();
}

void moveToTarget (int targetEC, int tolerance){	//New Version of moveToTarget
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
