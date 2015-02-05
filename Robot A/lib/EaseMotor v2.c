/*********************************************************\
 *                   Ease Motor Module                   *
 *                                                       *
 * This module adds the ability for motors to transition *
 *  from power to power, resulting in smoother movement  *
 *          and possibly reducing motor strain.          *
\*********************************************************/
/*
	How to use:
		At the top of the usercontrol and autonomous tasks, add the following line of code:
		startTask(runEaseMotors);

		To enable motor ease, use the following code:
		Ease[MotorNameOrPort].Enable = true;
		To disable motor else, substitute true for false.
		Ease[MotorNameOrPort].Enable = false;

		While motor ease is enabled, you can no longer use motor[MotorNameOrPort] to get/set
		the motor power. Instead, use EaseMotor[MotorNameOrPort]. For example:
		// Set the motor at port1 to 127
		EaseMotor[port1] = 127;

	Configuration:
		Each EaseMotor has the following properties:
		(Type)					Name		-		Description
		------------------------------------------------------------------------------------
		(tMotor)				Motor		-		An identifier to be used with the motor array
																(motor[EaseMotor[MotorNameOrPort]]). Changing this value
																may cause unexpected results!
		(float)					Power		-		The calculated power to set the motor power to. Changing
																this value may cause unexpected results!
		(float)					Ease		-		Controls the rate at which motor powers change. Greater
																values result in faster changes.
		(TVexJoysticks)	Bypass	-		A controller button or joystick channel to set as the
																bypass control.
		(bool)					Enable	-		Enables or disables ease motor functionality.

		These properties can be accessed from the Ease array. For example:
		// Change the amount of power added or subtracted per loop
		Ease[port1].Ease = 0.75;

	Advanced:
		If bStopTasksBetweenModes is set to false, you just need to call startTask(runEaseMotors)
		once, preferably in task main() or anywhere else that will run before you need to use the
		ease motor features.
*/

// Configuration
// The default value for motors' ease
float DefaultEase = 0.5;

// Normal TVexJoysticks are 0 - 43
const TVexJoysticks NoBypass = (TVexJoysticks) 100;
// Structure to store motor data
typedef struct {
	tMotor Motor;
	float Power;
	float Ease;
	TVexJoysticks Bypass;
	bool Enable;
} TEaseMotor;

// Array that stores the target powers of motors
float EaseMotor[10];
// Array that stores the rest of the motor data (array of structs)
TEaseMotor Ease[10];

task runEaseMotors() {
	// Register all motors
	unsigned int i;
	for (i = 0; i < 10; i++) {
		Ease[i].Motor = (tMotor) i;
		Ease[i].Power = motor[(tMotor) i];
		Ease[i].Ease = DefaultEase;
		Ease[i].Bypass = NoBypass;
		Ease[i].Enable = false;
	}
	// Run ease
	while (true) {
		unsigned int i;
		for (i = 0; i < 10; i++) {
			// Check if ease is disabled
			if (!Ease[i].Enable)
				continue;
			if (Ease[i].Bypass != NoBypass && vexRT[Ease[i].Bypass] != 0) {
				motor[Ease[i].Motor] = EaseMotor[i];
				Ease[i].Power = EaseMotor[i];
				continue;
			}
			float Direction = 0;
			if (Ease[i].Power < EaseMotor[i])
				Direction = 1;
			else if (Ease[i].Power > EaseMotor[i])
				Direction = -1;
			Ease[i].Power = bounds(-127, 127, Ease[i].Power + (Direction * min(abs(Ease[i].Power - EaseMotor[i]), Ease[i].Ease)));
			motor[Ease[i].Motor] = Ease[i].Power;
		}
		wait1Msec(5);
	}
}
