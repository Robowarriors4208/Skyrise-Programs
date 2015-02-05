task autonomous() {
	Ease[leftWheelF].Enable = false;
	Ease[leftWheelR].Enable = false;
	Ease[rightWheelF].Enable = false;
	Ease[rightWheelR].Enable = false;
	SensorValue[rightWheel] = 0;
	SensorValue[leftWheel] = 0;
	// Select autonomous
	switch (AutonomousMode) {
		case 0:
			motor[rightWheelF] = -100;
			motor[rightWheelR] = -100;
			motor[leftWheelF] = -100;
			motor[leftWheelR] = -100;
			//EaseMotor[rightWheels] = -100;
			//EaseMotor[leftWheels] = -100;
			wait1Msec(1000);
			motor[rightWheelF] = 0;
			motor[rightWheelR] = 0;
			motor[leftWheelF] = 0;
			motor[leftWheelR] = 0;
			//EaseMotor[rightWheels] = 0;
			//EaseMotor[leftWheels] = 0;
			wait1Msec(750);
			break;
		case 1:
			motor[rightWheelF] = -127;
			motor[rightWheelR] = -127;
			motor[leftWheelF] = -127;
			motor[leftWheelR] = -127;
			//EaseMotor[rightWheels] = -127;
			//EaseMotor[leftWheels] = -127;
			wait1Msec(750);
			motor[rightWheelF] = -20;
			motor[rightWheelR] = -20;
			motor[leftWheelF] = -127;
			motor[leftWheelR] = -127;
			//EaseMotor[rightWheels] = -20;
			//EaseMotor[leftWheels] = -127;
			wait1Msec(500);
			motor[rightWheelF] = -127;
			motor[rightWheelR] = -127;
			motor[leftWheelF] = -127;
			motor[leftWheelR] = -127;
			//EaseMotor[rightWheels] = -127;
			//EaseMotor[leftWheels] = -127;
			break;
	}
}
