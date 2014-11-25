#ifndef FTC_AUTO_FUNCTIONS
#define FTC_AUTO_FUNCTIONS

// Autonomous Mode Operational Functions //
// Put functions here which do specific actions on the robot. //

#define AUTO_DRIVE_SPEED (-100)
#define TURN_LEFT (false)
#define IR_MID (5)
#define IR_LEFT_SIDE (1)
#define IR_RIGHT_SIDE (9)

void AutoScore() {
	//Drive forward into center goal
	initIR(MidIRSeeker);
	driveToIR(AUTO_DRIVE_SPEED, false, false, 0);
	resetDriveEncoder();
	driveToEncoder(AUTO_DRIVE_SPEED, 500); //Note: 500 is a guessed value

	//Back up
	resetDriveEncoder();
	driveToEncoder(-AUTO_DRIVE_SPEED, 500); //also a guessed value
}

void AutoKickstand() {
	//Turn to line up side sensor
	driveToGyro(90, !TURN_LEFT);

	//Move to the side, turn, move forward and hit kickstand
	initIR(MidIRSeeker);
	driveToIR(AUTO_DRIVE_SPEED, false, false, IR_MID - 1);
	driveToGyro(90, TURN_LEFT);
	driveToEncoder(AUTO_DRIVE_SPEED, 2000);
}

void AutoScoreAhead() {
	//Turn to line up side sensor
	driveToGyro(90, !TURN_LEFT);

	//Center on IR beacon
	initIR(MidIRSeeker);
	driveToIR(AUTO_DRIVE_SPEED, false, false, IR_MID);

	//Turn to line up with the goal
	driveToGyro(90, TURN_LEFT);

	AutoScore();

	AutoKickstand();
}

void AutoScoreIntermediate() {
	//Turn to line up side sensor
	driveToGyro(135, !TURN_LEFT);

	//Center on IR beacon
	initIR(MidIRSeeker);
	driveToIR(-AUTO_DRIVE_SPEED, false, false, IR_MID);

	//Turn to line up with the goal
	driveToGyro(90, !TURN_LEFT);

	AutoScore();

	AutoKickstand();
}

void AutoScoreSide() {
	//Turn left, drive far out, and turn back
	driveToGyro(45, TURN_LEFT);
	//Center on IR beacon
	initIR(IRSeeker);
	driveToIR(AUTO_DRIVE_SPEED, false, false, IR_RIGHT_SIDE);

	//Turn out to determine direction
	initIR(IRSeeker);
	driveToIR(-AUTO_DRIVE_SPEED, true, false, IR_MID + 1);

	AutoScore();

	AutoKickstand();
}

#endif
