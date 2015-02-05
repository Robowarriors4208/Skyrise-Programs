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
			waitSec(0.5);
			motor[rightWheelF] = 0;
			motor[rightWheelR] = 0;
			motor[leftWheelF] = 0;
			motor[leftWheelR] = 0;
			motor[leftIntake] = 127;
			motor[rightIntake] = 127;
			waitSec(1);
			motor[leftIntake] = 0;
			motor[rightIntake] = 0;
			motor[rightWheelF] = -100;
			motor[rightWheelR] = -100;
			motor[leftWheelF] = -100;
			motor[leftWheelR] = -100;
			waitSec(1);
			motor[rightWheelF] = 0;
			motor[rightWheelR] = 0;
			motor[leftWheelF] = 0;
			motor[leftWheelR] = 0;
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
