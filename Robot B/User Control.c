bool fl = false;
bool PrevStab = false;
bool Stab = false;
float StabPower = LiftHoldPower;
float LDP = LiftDownPower;
bool LD = false;
bool LPD = false;
task usercontrol() {
	PrevStab = false;
	Stab = false;
	LDP = LiftDownPower;
	Ease[leftLift1].Enable = true;
	Ease[leftLift2].Enable = true;
	Ease[rightLift1].Enable = true;
	Ease[rightLift2].Enable = true;
	Ease[leftWheelF].Enable = true;
	Ease[leftWheelR].Enable = true;
	Ease[rightWheelF].Enable = true;
	Ease[rightWheelR].Enable = true;
	// Infinitely repeating loop
	while (true) {
		if (vexRT[Btn8D] == 1) {
			if (!fl) {
				fl = true;
				flip = !flip;
			}
		} else {
			fl = false;
		}

		// Claw
		if (vexRT[ClawOpen] == 1) {
			motor[claw] = 127;
		} else if (vexRT[ClawClose] == 1) {
			motor[claw] = -127;
		} else {
			motor[claw] = 0;
 		}

		// 6-bar lift
 		if (vexRT[LiftUp] == 0 && vexRT[LiftDown] == 1)
 			LD = true;
 		else
 			LD = false;
 		if (vexRT[LiftForceDown] == 1) {
 			Ease[leftLift1].Enable = false;
			Ease[leftLift2].Enable = false;
			Ease[rightLift1].Enable = false;
			Ease[rightLift2].Enable = false;
			motor[leftLift1] = -127;
			motor[leftLift2] = -127;
			motor[rightLift1] = -127;
			motor[rightLift2] = -127;
		} else {
			Ease[leftLift1].Enable = true;
			Ease[leftLift2].Enable = true;
			Ease[rightLift1].Enable = true;
			Ease[rightLift2].Enable = true;
		if (vexRT[LiftUp] == 1) {
			if (SensorValue[leftLift] > LiftMaxHeight) {
				EaseMotor[leftLift1] = 0;
				EaseMotor[leftLift2] = 0;
				EaseMotor[rightLift1] = 0;
				EaseMotor[rightLift2] = 0;
			} else {
				if (SensorValue[leftLift] < SensorValue[rightLift]) {
					EaseMotor[leftLift1] = LiftUpPower;
					EaseMotor[leftLift2] = LiftUpPower;
					EaseMotor[rightLift1] = LiftUpPower - AutoStraightPower;
					EaseMotor[rightLift2] = LiftUpPower - AutoStraightPower;
				} else if (SensorValue[leftLift] > SensorValue[rightLift]) {
					EaseMotor[leftLift1] = LiftUpPower - AutoStraightPower;
					EaseMotor[leftLift2] = LiftUpPower - AutoStraightPower;
					EaseMotor[rightLift1] = LiftUpPower;
					EaseMotor[rightLift2] = LiftUpPower;
				} else {
					EaseMotor[leftLift1] = LiftUpPower;
					EaseMotor[leftLift2] = LiftUpPower;
					EaseMotor[rightLift1] = LiftUpPower;
					EaseMotor[rightLift2] = LiftUpPower;
				}
			}
		} else if (vexRT[LiftDown] == 1) {
			if (SensorValue[leftLift] < LiftMinHeight) {
				EaseMotor[leftLift1] = 0;
				EaseMotor[leftLift2] = 0;
				EaseMotor[rightLift1] = 0;
				EaseMotor[rightLift2] = 0;
			} else {
				if (!LPD && LD)
					LDP = LiftDownPower;
				//else
					//if (SpeedDiff[leftLift]
				if (SensorValue[leftLift] < SensorValue[rightLift]) {
					EaseMotor[leftLift1] = LiftDownPower + AutoStraightPower;
					EaseMotor[leftLift2] = LiftDownPower + AutoStraightPower;
					EaseMotor[rightLift1] = LiftDownPower;
					EaseMotor[rightLift2] = LiftDownPower;
				} else if (SensorValue[leftLift] > SensorValue[rightLift]) {
					EaseMotor[leftLift1] = LiftDownPower;
					EaseMotor[leftLift2] = LiftDownPower;
					EaseMotor[rightLift1] = LiftDownPower + AutoStraightPower;
					EaseMotor[rightLift2] = LiftDownPower + AutoStraightPower;
				} else {
					EaseMotor[leftLift1] = LiftDownPower;
					EaseMotor[leftLift2] = LiftDownPower;
					EaseMotor[rightLift1] = LiftDownPower;
					EaseMotor[rightLift2] = LiftDownPower;
				}
			}
		} else {
			if (vexRT[LiftCorrect] == 1) {
				if (SensorValue[leftLift] != SensorValue[rightLift]) {
					Ease[leftLift1].Enable = false;
					Ease[leftLift2].Enable = false;
					Ease[rightLift1].Enable = false;
					Ease[rightLift2].Enable = false;
				} else {
					Ease[leftLift1].Enable = true;
					Ease[leftLift2].Enable = true;
					Ease[rightLift1].Enable = true;
					Ease[rightLift2].Enable = true;
				}
				if (SensorValue[leftLift] < SensorValue[rightLift]) {
					motor[leftLift1] = LiftCorrectUpPower;
					motor[leftLift2] = LiftCorrectUpPower;
					motor[rightLift1] = LiftCorrectDownPower;
					motor[rightLift2] = LiftCorrectDownPower;
				} else if (SensorValue[leftLift] > SensorValue[rightLift]) {
					motor[leftLift1] = LiftCorrectDownPower;
					motor[leftLift2] = LiftCorrectDownPower;
					motor[rightLift1] = LiftCorrectUpPower;
					motor[rightLift2] = LiftCorrectUpPower;
				}
			} else {
				Ease[leftLift1].Enable = true;
				Ease[leftLift2].Enable = true;
				Ease[rightLift1].Enable = true;
				Ease[rightLift2].Enable = true;
				//SUPER DUPER UBER TUBER MEGA IMPORTANT MESSAGE: COPY FROM DOMBOT IF IT DOESNT WORK
				if (LiftStabilize) {
					//if (LastSpeed)
					if (SensorValue[leftLift] >= LiftHoldHeight && SensorValue[rightLift] >= LiftHoldHeight) {
						Stab = true;
						// If stabilize just started
						if (!PrevStab) {
							StabPower = LiftHoldPower;
						} else {
							if (SpeedDiff[leftLift] < 0) {
								StabPower += 0.25;
							} else if (SpeedDiff[leftLift] > 0) {
								StabPower -= 0.25;
							} else
								StabPower = max(StabPower - 0.005, LiftHoldPower);
						}
						EaseMotor[leftLift1] = StabPower;
						EaseMotor[leftLift2] = StabPower;
						EaseMotor[rightLift1] = StabPower;
						EaseMotor[rightLift2] = StabPower;
					} else {
						EaseMotor[leftLift1] = 0;
						EaseMotor[leftLift2] = 0;
						EaseMotor[rightLift1] = 0;
						EaseMotor[rightLift2] = 0;
					}
				} else {
					EaseMotor[leftLift1] = 0;
					EaseMotor[leftLift2] = 0;
					EaseMotor[rightLift1] = 0;
					EaseMotor[rightLift2] = 0;
				}
			}
		}
		}
		PrevStab = Stab;

		if (vexRT[LiftStabilizeBtn] == 1) {
			if (!LiftStabilizeState) {
				LiftStabilizeState = true;
				LiftStabilize = !LiftStabilize;
			}
		} else {
			LiftStabilizeState = false;
		}

		//// If the 5 Up button is being pressed, and if it was not being pressed in the
		//// previous loop iteration
		//if (vexRT[Btn5U] == 1 && !Btn5UState) {
		//	// Remember that the button is being held down
		//	Btn5UState = true;
		//	// Change the control mode
		//	controlMode++;
		//	// Check if the control mode is greater than the maximum mode int
		//	if (controlMode > CONTROL_MAX) {
		//		controlMode = 1;
		//	}
		//}
		//// If the 5 Up button is not being pressed, and if it was being pressed in the
		//// previous loop iteration
		//if (vexRT[Btn5U] != 1 && Btn5UState) {
		//	// Remember that the button is not being held down
		//	Btn5UState = false;
		//}
		//switch (controlMode) {
		//	case CONTROL_ARCADE_OLD:
		//		// Old formula; maximum power is actually half power
		//		motor[leftWheels] = (vexRT[Ch2] + vexRT[Ch1]) / 2; // (y + x) / 2
		//		motor[rightWheels] = (vexRT[Ch2] - vexRT[Ch1]) / 2; // (y - x) / 2
		//		break;
		//	case CONTROL_ARCADE:
		//		// New formula to maximize power
		//		// Left wheels' motor power = Y position of joystick - X position of joystick
		//		// with a maximum of 127
		//		// Remember, left is a negative value
		//		// If the joystick is being held to the left, the left wheels' motor should
		//		// still be going at maximum power
		//		motor[leftWheels] = min(vexRT[Ch2] + vexRT[Ch1], 127) * motorScale;
		//		// Right wheels' motor power = Y position of joystick + X position of joystick
		//		// with a maximum of 127
		//		// Remember, right is a positive vamin
		//		// If the joystick is being held to the right, the right wheels' motor should
		//		// still be going at maximum power
		//		motor[rightWheels] = min(vexRT[Ch2] - vexRT[Ch1], 127) * motorScale;
		//		break;
		//	case CONTROL_TANK:
		//		// Left wheels' motor power = Y position of the left joystick
		//		motor[leftWheels] = vexRT[Ch3] * motorScale;
		//		// Right wheels' motor power = Y position of the right joystick
		//		motor[rightWheels] = vexRT[Ch2] * motorScale;
		//}

		switch (ControlMode) {
			case 0:
				// Left wheels' motor power = Y position of the left joystick
				//motor[leftWheels] = (abs(vexRT[Ch3]) < 15 ? 0 : vexRT[Ch3]) * motorScale;
				EaseMotor[leftWheelF] = (abs(vexRT[Ch3]) < 15 ? 0 : vexRT[Ch3]) * motorScale;
				EaseMotor[leftWheelR] = (abs(vexRT[Ch3]) < 15 ? 0 : vexRT[Ch3]) * motorScale;
				// Right wheels' motor power = Y position of the right joystick
				//motor[rightWheels] = (abs(vexRT[Ch2]) < 15 ? 0 : vexRT[Ch2]) * motorScale;
				EaseMotor[rightWheelF] = (abs(vexRT[Ch2]) < 15 ? 0 : vexRT[Ch2]) * motorScale;
				EaseMotor[rightWheelR] = (abs(vexRT[Ch2]) < 15 ? 0 : vexRT[Ch2]) * motorScale;
				break;
			case 1:
				// New formula to maximize power
				// Left wheels' motor power = Y position of joystick - X position of joystick
				// with a maximum of 127
				// Remember, left is a negative value
				// If the joystick is being held to the left, the left wheels' motor should
				// still be going at maximum power
				//motor[leftWheels] = min(vexRT[Ch2] + vexRT[Ch1], 127) * motorScale;
				EaseMotor[leftWheelF] = min(vexRT[Ch2] + vexRT[Ch1], 127) * motorScale;
				EaseMotor[leftWheelR] = min(vexRT[Ch2] + vexRT[Ch1], 127) * motorScale;
				// Right wheels' motor power = Y position of joystick + X position of joystick
				// with a maximum of 127
				// Remember, right is a positive vamin
				// If the joystick is being held to the right, the right wheels' motor should
				// still be going at maximum power
				//motor[rightWheels] = min(vexRT[Ch2] - vexRT[Ch1], 127) * motorScale;
				EaseMotor[rightWheelF] = min(vexRT[Ch2] - vexRT[Ch1], 127) * motorScale;
				EaseMotor[rightWheelR] = min(vexRT[Ch2] - vexRT[Ch1], 127) * motorScale;
				break;
		}

		// Relinquish CPU to other tasks
		wait1Msec(5);
		//EndTimeSlice();
	}
}
