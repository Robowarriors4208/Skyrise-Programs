// Configuration
float DefaultEase = 0.5;

const tMotor NoMotor = (tMotor) 'N';
const TVexJoysticks NoBypass = (TVexJoysticks) 100;

tMotor motorIndex[10] = {NoMotor, NoMotor, NoMotor, NoMotor, NoMotor, NoMotor, NoMotor, NoMotor, NoMotor, NoMotor};
float motorTarget[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float motorPower[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float motorEase[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
TVexJoysticks motorBypass[10] = {NoBypass, NoBypass, NoBypass, NoBypass, NoBypass, NoBypass, NoBypass, NoBypass, NoBypass, NoBypass};
bool motorBypassToggle[10] = {false, false, false, false, false, false, false, false, false, false};

void setMotorEase(tMotor Motor, float Ease) {
	unsigned int i;
	for (i = 0; i < 10; i++) {
		if (motorIndex[i] == NoMotor)
			motorIndex[i] = Motor;
		if (motorIndex[i] == Motor) {
			motorEase[i] = Ease;
			break;
		}
	}
}

float getMotorEase(tMotor Motor) {
	unsigned int i;
	for (i = 0; i < 10; i++) {
		if (motorIndex[i] == NoMotor) {
			setMotorEase(Motor, DefaultEase);
			motorPower[i] = motor[Motor];
		}
		if (motorIndex[i] == Motor)
			return motorEase[i];
	}
	return 0;
}

void setMotorBypass(tMotor Motor, TVexJoysticks Bypass) {
	unsigned int i;
	for (i = 0; i < 10; i++) {
		if (motorIndex[i] == NoMotor) {
			setMotorEase(Motor, DefaultEase);
			motorPower[i] = motor[Motor];
		}
		if (motorIndex[i] == Motor) {
			motorBypass[i] = Bypass;
			break;
		}
	}
}

TVexJoysticks getMotorBypass(tMotor Motor) {
	unsigned int i;
	for (i = 0; i < 10; i++) {
		if (motorIndex[i] == NoMotor) {
			setMotorEase(Motor, DefaultEase);
			motorPower[i] = motor[Motor];
		}
		if (motorIndex[i] == Motor)
			return motorBypass[i];
	}
	return NoBypass;
}

void bypassEase(tMotor Motor, bool Bypass) {
		unsigned int i;
	for (i = 0; i < 10; i++) {
		if (motorIndex[i] == NoMotor) {
			setMotorEase(Motor, DefaultEase);
			motorPower[i] = motor[Motor];
		}
		if (motorIndex[i] == Motor) {
			motorBypassToggle[i] = Bypass;
			break;
		}
	}
}

void easeMotor(tMotor Motor, float Power) {
	unsigned int i;
	for (i = 0; i < 10; i++) {
		if (motorIndex[i] == NoMotor) {
			setMotorEase(Motor, DefaultEase);
			motorPower[i] = motor[Motor];
		}
		if (motorIndex[i] == Motor) {
			motorTarget[i] = Power;
			break;
		}
	}
}

void runMotors() {
	unsigned int i;
	for (i = 0; i < 10; i++) {
		if (motorIndex[i] == NoMotor) {
			break;
		} else {
			if (motorBypassToggle[i])
				continue;
			if (motorBypass[i] != NoBypass && vexRT[motorBypass[i]] != 0) {
				motor[motorIndex[i]] = motorTarget[i];
				continue;
			}
			float direction = 0;
			if (motorPower[i] < motorTarget[i])
				direction = 1;
			else if (motorPower[i] > motorTarget[i])
				direction = -1;
			motorPower[i] = bounds(-127, 127, motorPower[i] + (direction * min(abs(motorPower[i] - motorTarget[i]), motorEase[i])));
			motor[motorIndex[i]] = motorPower[i];
		}
	}
}

task easeMotors() {
	while (true) {
		runMotors();
		wait1Msec(5);
	}
}
