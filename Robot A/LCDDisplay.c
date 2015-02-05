// Number of menu options
const int LCDMenuCount = 8;
// All of the menu options
string LCDMenuList[LCDMenuCount] = {"Competition Mode", "Backlight", "Autonomous", "Control Mode", "Ease Values", "Motor Debug", "Sensor Debug", "Reset Sensors"};

// The current menu
int LCDMenu = 0;
// The current item
int LCDItem = 0;
// The previous state of nLCDButtons
int LCDLastButton = 0;
// Allow repeating if button is held down
bool LCDButtonRepeat = false;
bool LCDButtonCanRepeat = false;
bool LCDButtonHold = false;
// Possible values: "Home", "Menu", "Item", "Internal", "None"
string LCDMode = "Home";
string LCDLastMode = LCDMode;
// The battery to display info on
int LCDBatDisplay = 0;

task autonomous();
task usercontrol();

task LCDDisplay() {
	while (true) {
		clearLCDLine(0);
		clearLCDLine(1);

		bool LCDButttonUsed = false;

		// Main button/menu/item selection handling
		if (nLCDButtons != 0) {
			if (LCDMode == "Home") {
				if (LCDLastButton != nLCDButtons)
					if (nLCDButtons == 4) {
						LCDButttonUsed = true;
						LCDMode = "Menu";
					}
			} else if (LCDMode == "Menu") {
				switch (nLCDButtons) {
					case (TControllerButtons) 1:
						if (LCDLastButton != nLCDButtons) {
							LCDButttonUsed = true;
							LCDMenu--;
							if (LCDMenu < 0)
								LCDMenu = LCDMenuCount;
						}
						break;
					case (TControllerButtons) 2:
						if (LCDLastButton != nLCDButtons) {
							LCDButttonUsed = true;
							if (LCDMenu == LCDMenuCount) {
								LCDMode = "Home";
								LCDMenu = 0;
							} else
								/*if (LCDMenu != 0)
									LCDMode = "Home";
								else*/
									LCDMode = "Item";
						}
						break;
					case (TControllerButtons) 4:
						if (LCDLastButton != nLCDButtons) {
							LCDButttonUsed = true;
							LCDMenu++;
							if (LCDMenu > LCDMenuCount)
								LCDMenu = 0;
						}
						break;
				}
			/*} else if (LCDMode == "Item") {
				switch (nLCDButtons) {
					case 1:
						LCDItem--;
						if (LCDMenu < 0)
							LCDMenu = LCDMenuCount - 1;
						break;
					case 2:
						if (LCDLastButton != nLCDButtons) {
							if (LCDMenu == LCDMenuCount) {
								LCDMode = "Menu";
								LCDItem = 0;
							} else
								LCDMode = "Internal";
						}
						break;
					case 4:
						LCDItem++;
						if (LCDMenu >= LCDMenuCount)
							LCDMenu = 0;
						break;
				}*/
			} else if (LCDMode == "Internal") {
				switch (LCDItem) {
					case 1:
						break;
				}
			}
		}
		if (LCDButttonUsed) {
			clearTimer(T3);
			LCDLastButton = nLCDButtons;
		} else {
			if (LCDButtonRepeat) {
				// Button repetition
				if (LCDLastButton != nLCDButtons)
					LCDButtonCanRepeat = true;
				if (nLCDButtons == (TControllerButtons) 0)
					LCDButtonCanRepeat = false;
				if (LCDLastButton == nLCDButtons && LCDButtonCanRepeat) {
					if (!LCDButtonHold) {
						if (time1[T3] > 750) {
							LCDButtonHold = true;
							clearTimer(T3);
						}
					} else {
						if (time1[T3] > 100) {
							LCDLastButton = -1;
							clearTimer(T3);
						}
					}
				} else {
					LCDButtonHold = false;
					clearTimer(T3);
				}
			} else {
				LCDButtonHold = false;
				clearTimer(T3);
			}
		}

		// LCD display handling
		if (LCDMode == "Home") {
			LCDButtonRepeat = false;
			if (BackupBatteryLevel > 150) {
				if (LCDLastMode != "Home") {
					LCDBatDisplay = 0;
					clearTimer(T1);
				} else {
					if (time1[T1] > 3000) {
						if (LCDBatDisplay == 0)
							LCDBatDisplay = 1;
						else if (LCDBatDisplay == 1)
							LCDBatDisplay = 2;
						else
							LCDBatDisplay = 0;
						clearTimer(T1);
					}
				}
			} else
				LCDBatDisplay = 0;
			string battery;
			if (LCDBatDisplay == 0)
				sprintf(battery, "Main Bat.: %1.2f%c", nImmediateBatteryLevel / 1000.0, 'V');
			else if (LCDBatDisplay == 1)
				sprintf(battery, "Back Bat.: %1.2f%c", BackupBatteryLevel / 1000.0, 'V');
			else
				sprintf(battery, "Avg. Bat.: %1.2f%c", (nImmediateBatteryLevel + BackupBatteryLevel) / 2 / 1000.0, 'V');
			displayLCDCenteredString(0, battery);
			displayLCDString(1, 10, "[Menu]");
			if (bIfiRobotDisabled)
				displayLCDString(1, 0, "Disabled");
			else {
				if (bIfiAutonomousMode)
					displayLCDString(1, 0, "Autonomous");
				else
					displayLCDString(1, 0, "User Ctrl");
			}
		} else if (LCDMode == "Menu") {
			if (LCDLastMode != "Menu")
				clearTimer(T2);
			else
				if (time1[T2] > 60000) {
					LCDMode = "Home";
					break;
				}
			displayLCDString(1, 0, " <  [Select]  > ");
			// Back option
			if (LCDMenu == LCDMenuCount)
				displayLCDCenteredString(0, "Back");
			else
				displayLCDCenteredString(0, LCDMenuList[LCDMenu]);

		// Sub-menu handling
		} else if (LCDMode == "Item") {
			if (LCDMenuList[LCDMenu] == "Competition Mode") {
				displayLCDCenteredString(0, ModeNames[Mode]);
				displayLCDString(1, 0, " <    [OK]    > ");
				if (LCDLastButton != nLCDButtons) {
					switch (nLCDButtons) {
						case (TControllerButtons) 1:
							Mode--;
							if (Mode < 0)
								Mode = ModeCount - 1;
							break;
						case (TControllerButtons) 2:
							switch (Mode) {
								case 0:
									stopTask(autonomous);
									startTask(usercontrol);
									break;
								case 1:
									stopTask(usercontrol);
									clearLCDLine(0);
									clearLCDLine(1);
									displayLCDCenteredString(0, "Stand clear!");
									displayLCDCenteredString(1, "Starting in 3");
									waitSec(1);
									clearLCDLine(1);
									displayLCDCenteredString(1, "Starting in 2");
									waitSec(1);
									clearLCDLine(1);
									displayLCDCenteredString(1, "Starting in 1");
									waitSec(1);
									startTask(autonomous);
									break;
							}
							LCDMode = "Menu";
							break;
						case (TControllerButtons) 4:
							Mode++;
							if (Mode == ModeCount)
								Mode = 0;
							break;
					}
				}
			} else if (LCDMenuList[LCDMenu] == "Backlight") {
				if (bLCDBacklight)
					displayLCDCenteredString(0, "Backlight: On");
				else
					displayLCDCenteredString(0, "Backlight: Off");
				displayLCDString(1, 0, "[Toggle]    [OK]");
				if (LCDLastButton != nLCDButtons) {
					switch (nLCDButtons) {
						case (TControllerButtons) 1:
							if (bLCDBacklight)
								bLCDBacklight = false;
							else
								bLCDBacklight = true;
							break;
						case (TControllerButtons) 4:
							LCDMode = "Menu";
							break;
					}
				}
			} else if (LCDMenuList[LCDMenu] == "Autonomous") { // Autonomous selection
				LCDButtonRepeat = true;
				displayLCDCenteredString(0, AutonomousNames[AutonomousMode]);
				displayLCDString(1, 0, " <    [OK]    > ");
				if (LCDLastButton != nLCDButtons) {
					switch (nLCDButtons) {
						case (TControllerButtons) 1:
							AutonomousMode--;
							if (AutonomousMode < 0)
								AutonomousMode = AutonomousCount - 1;
							break;
						case (TControllerButtons) 2:
							LCDButtonRepeat = false;
							LCDMode = "Menu";
							break;
						case (TControllerButtons) 4:
							AutonomousMode++;
							if (AutonomousMode == AutonomousCount)
								AutonomousMode = 0;
							break;
					}
				}
			} else if (LCDMenuList[LCDMenu] == "Control Mode") { // Control mode
				LCDButtonRepeat = true;
				displayLCDCenteredString(0, ControlModes[ControlMode]);
				displayLCDString(1, 0, " <    [OK]    > ");
				if (LCDLastButton != nLCDButtons) {
					switch (nLCDButtons) {
						case (TControllerButtons) 1:
							ControlMode--;
							if (ControlMode < 0)
								ControlMode = 1;
							break;
						case (TControllerButtons) 2:
							LCDButtonRepeat = false;
							LCDMode = "Menu";
							break;
						case (TControllerButtons) 4:
							ControlMode++;
							if (ControlMode == 2)
								ControlMode = 0;
							break;
					}
				}
			} else if (LCDMenuList[LCDMenu] == "Ease Values") { // Ease values
				if (EaseSelect) {
					LCDButtonRepeat = false;
					displayLCDCenteredString(0, EaseSelection[EaseVariable]);
					displayLCDString(1, 0, "[Cg] [Back] [OK]");
					if (LCDLastButton != nLCDButtons) {
						switch (nLCDButtons) {
							case (TControllerButtons) 1:
								EaseVariable++;
								if (EaseVariable == EaseVariables)
									EaseVariable = 0;
								break;
							case (TControllerButtons) 2:
								LCDMode = "Menu";
								break;
							case (TControllerButtons) 4:
								EaseSelect = false;
								break;
						}
					}
				} else {
					LCDButtonRepeat = true;
					string EaseString;
					float EaseValue;
					if (EaseSelection[EaseVariable] == "Lift") {
						EaseValue = Ease[leftLift1].Ease;
						EaseValue = Ease[leftLift2].Ease;
						EaseValue = Ease[rightLift1].Ease;
						EaseValue = Ease[rightLift2].Ease;
					} else if (EaseSelection[EaseVariable] == "Drive") {
						EaseValue = Ease[leftWheelF].Ease;
						EaseValue = Ease[leftWheelR].Ease;
					}
					sprintf(EaseString, "%s: %1.2f", EaseSelection[EaseVariable], EaseValue);
					displayLCDCenteredString(0, EaseString);
					displayLCDString(1, 0, " -    [OK]    + ");
					if (LCDLastButton != nLCDButtons) {
						switch (nLCDButtons) {
							case (TControllerButtons) 1:
								EaseValue -= 0.01;
								break;
							case (TControllerButtons) 2:
								EaseSelect = true;
								break;
							case (TControllerButtons) 4:
								EaseValue += 0.01;
								break;
						}
					}
					if (EaseSelection[EaseVariable] == "Lift") {
						Ease[leftLift1].Ease = EaseValue;
						Ease[leftLift2].Ease = EaseValue;
						Ease[rightLift1].Ease = EaseValue;
						Ease[rightLift2].Ease = EaseValue;
					} else if (EaseSelection[EaseVariable] == "Drive") {
						Ease[leftWheelF].Ease = EaseValue;
						Ease[leftWheelR].Ease = EaseValue;
						Ease[rightWheelF].Ease = EaseValue;
						Ease[rightWheelR].Ease = EaseValue;
					}
				}
			} else if (LCDMenuList[LCDMenu] == "Motor Debug") { // Motor debug
				LCDButtonRepeat = true;
				string MotorString;
				sprintf(MotorString, "port%i: %i", MotorDebug + 1, motor[(tMotor) MotorDebug]);
				displayLCDCenteredString(0, MotorString);
				displayLCDString(1, 0, " <   [Back]   > ");
				if (LCDLastButton != nLCDButtons) {
					switch (nLCDButtons) {
						case (TControllerButtons) 1:
							MotorDebug--;
							if (MotorDebug < 0)
								MotorDebug = 9;
							break;
						case (TControllerButtons) 2:
							LCDButtonRepeat = false;
							LCDMode = "Menu";
							break;
						case (TControllerButtons) 4:
							MotorDebug++;
							if (MotorDebug > 9)
								MotorDebug = 0;
							break;
					}
				}
			} else if (LCDMenuList[LCDMenu] == "Sensor Debug") { // Sensor debug
				if (SensorDebugSelect) {
					LCDButtonRepeat = false;
					if (SensorMode == 0)
						displayLCDCenteredString(0, "Analog");
					else
						displayLCDCenteredString(0, "Digital");
					displayLCDString(1, 0, "[Cg] [Back] [OK]");
					if (LCDLastButton != nLCDButtons) {
						switch (nLCDButtons) {
							case (TControllerButtons) 1:
								if (SensorMode == 0)
									SensorMode = 1;
								else
									SensorMode = 0;
								break;
							case (TControllerButtons) 2:
								LCDMode = "Menu";
								break;
							case (TControllerButtons) 4:
								SensorDebugSelect = false;
								break;
						}
					}
				} else {
					LCDButtonRepeat = true;
					string SensorString;
					if (SensorMode == 0) {
						sprintf(SensorString, "in %i: %i", SensorDebug + 1, SensorValue[(tSensors) SensorDebug]);
						if (SensorDebug < 0)
							SensorDebug = 0;
						if (SensorDebug > 7)
							SensorDebug = 7;
					} else {
						sprintf(SensorString, "dgtl %i: %i", SensorDebug - 7, SensorValue[(tSensors) SensorDebug]);
						if (SensorDebug < 8)
							SensorDebug = 8;
						if (SensorDebug > 19)
							SensorDebug = 19;
					}
					displayLCDCenteredString(0, SensorString);
					displayLCDString(1, 0, " <   [Back]   > ");
					if (LCDLastButton != nLCDButtons) {
						switch (nLCDButtons) {
							case (TControllerButtons) 1:
								SensorDebug--;
								if (SensorMode == 0) {
									if (SensorDebug < 0)
										SensorDebug = 7;
								} else
									if (SensorDebug < 8)
										SensorDebug = 19;
								break;
							case (TControllerButtons) 2:
								SensorDebugSelect = true;
								break;
							case (TControllerButtons) 4:
								SensorDebug++;
								if (SensorMode == 0) {
									if (SensorDebug > 7)
										SensorDebug = 0;
								} else
									if (SensorDebug > 19)
										SensorDebug = 8;
								break;
						}
					}
				}
			} else if (LCDMenuList[LCDMenu] == "Reset Sensors") { // Reset Sensors
				displayLCDCenteredString(0, "Reset Sensors");
				displayLCDString(1, 0, "[Back]      [OK]");
				if (LCDLastButton != nLCDButtons) {
					switch (nLCDButtons) {
						case (TControllerButtons) 1:
							LCDMode = "Menu";
							break;
						case (TControllerButtons) 4:
							SensorValue[leftLift] = 0;
							SensorValue[rightLift] = 0;
							LCDMode = "Menu";
							break;
					}
				}
			}
		}

		LCDLastMode = LCDMode;
		LCDLastButton = nLCDButtons;
		wait1Msec(10);
		//EndTimeSlice();
	}
}
