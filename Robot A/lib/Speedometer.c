/*********************************************************\
 *                                                       *
 *                                                       *
 *                                                       *
\*********************************************************/

/*int SpeedPrev[2];
int SpeedDiff[2];

task speedometer() {
	while (true) {
		SpeedDiff[0] = SensorValue[leftLift] - SpeedPrev[0];
		SpeedDiff[1] = SensorValue[rightLift] - SpeedPrev[1];
		SpeedPrev[0] = SensorValue[leftLift];
		SpeedPrev[1] = SensorValue[rightLift];
		wait1Msec(50);
	}
}*/

int SpeedPrev[20];
int SpeedDiff[20];

task speedometer() {
	while (true) {
		unsigned int i;
		for (i = 8; i < 20; i++) {
			SpeedDiff[(tSensors) i] = SensorValue[(tSensors) i] - SpeedPrev[(tSensors) i];
			SpeedPrev[(tSensors) i] = SensorValue[(tSensors) i];
		}
		wait1Msec(50);
	}
}
