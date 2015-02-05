/*********************************************************\
 *                  Extra Timers Module                  *
 *                                                       *
 *        This module adds five timers to RobotC.        *
\*********************************************************/

const int TimerCount = 5;
long Timer[TimerCount] = {0, 0, 0, 0, 0};
int TimerIncrement = 5;

task extraTimers() {
	while (true) {
		unsigned int i;
		for (i = 0; i < TimerCount; i++) {
			Timer[i] += TimerIncrement;
		}
		wait1Msec(TimerIncrement);
	}
}
