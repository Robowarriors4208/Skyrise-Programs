// Autonomous
const int AutonomousCount = 2;
string AutonomousNames[AutonomousCount] = {"1 pt Drop", "Drop and Push"};

// The fraction of power to send to the wheel motors
float motorScale = 1.0;

// Auto straightening power
int AutoStraightPower = 10;
// Lift variables
int LiftUpPower = 127;
int LiftDownPower = -50;
float LiftEase = 10;
int LiftMaxHeight = 900;
int LiftMinHeight = 10;
int LiftHoldPower = 5;
int LiftCorrectUpPower = 25;
int LiftCorrectDownPower = 0;
int LiftHoldHeight = 115;

// Wheel ease
float WheelEase = 5;

// Control mapping

const TVexJoysticks LiftUp = Btn5U;
const TVexJoysticks LiftDown = Btn7D;
const TVexJoysticks LiftBypass = Btn7L;
const TVexJoysticks LiftStabilizeBtn = Btn7R;
const TVexJoysticks LiftCorrect = Btn8L;
const TVexJoysticks LiftForceDown = Btn5D;
const TVexJoysticks ClawOpen = Btn6U;
const TVexJoysticks ClawClose = Btn6D;
const TVexJoysticks IntakeIn = Btn6D;
const TVexJoysticks IntakeOut = Btn5D;

// Drive control names
string ControlModes[2] = {"Tank", "Arcade"};

// Determines initial control mode
int ControlMode = 0;

// Internal
// Autonomous
int AutonomousMode = 0;
