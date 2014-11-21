#ifndef FTC_AUTO_FUNCTIONS
#define FTC_AUTO_FUNCTIONS

// Autonomous Mode Operational Functions //
// Put functions here which do specific actions on the robot. //

#define AUTO_DRIVE_SPEED (-100)

void AutoScore() {
	//Drive forward into center goal
	initIR(MidIRSeeker);
	driveToIR(100, false, false, 0);
	resetDriveEncoder();
	driveToEncoder(100, 500); //Note: 500 is a guessed value

	//Back up
	resetDriveEncoder();
	driveToEncoder(-100, -500); //-500 is also a guessed value
}

void AutoKickstand() {
	//Turn to line up side sensor
	driveToGyro(90, false);

	//Move to the side, turn, move forward and hit kickstand
	initIR(MidIRSeeker);
	driveToIR(-100, false, false, 6);
	driveToGyro(90, true);
	driveToEncoder(100, 2000);
}

void AutoScoreAhead() {
	//Turn to line up side sensor
	driveToGyro(90, true);

	//Center on IR beacon
	initIR(MidIRSeeker);
	driveToIR(-100, false, false, 5);

	//Turn to line up with the goal
	driveToGyro(90, true);

	AutoScore();

	AutoKickstand();
}

void AutoScoreIntermediate() {
	//Center on IR beacon direction
	initIR(IRSeeker);
	driveToIR(-100, true, false, 5);

	//Turn to line up side sensor
	driveToGyro(90, true);

	//Center on IR beacon
	initIR(MidIRSeeker);
	driveToIR(100, false, false, 5);

	//Turn to line up with the goal
	driveToGyro(90, true);

	AutoScore();

	AutoKickstand();
}

void AutoScoreSide() {
	//Turn right, drive far out, and turn back
	driveToGyro(45, false);
	//Center on IR beacon
	initIR(IRSeeker);
	driveToIR(100, false, false, 1);

	//Turn out to determine direction
	initIR(MidIRSeeker);
	driveToIR(100, true, false, 5);

	//Knowing direction, reliably turn to face the goal
	driveToGyro(90, true);

	AutoScore();

	AutoKickstand();
}

/*
// Assuming a start position parallel to the goal, back up and score
void AutoScore() {
	//drive backwards until IR is in view
	driveToIR(AUTO_DRIVE_SPEED, false, false, 1);
	//drive backwards until we're at an angle we can score from
	driveToEncoder(-AUTO_DRIVE_SPEED, 200);
	//turn facing IR
	driveToIR(AUTO_DRIVE_SPEED, false, false, 5);
	//Drive until ball is in goal
	// Not implemented -- driveToTouch(AUTO_DRIVE_SPEED, TS_index);
}
*/

void AutoKickstandAhead() {
	// Hit the kickstand
	driveToEncoder(AUTO_DRIVE_SPEED, 4500);
	wait1Msec(1000 * 2);
	// Back up to avoid hitting the goal
	driveToEncoder(-AUTO_DRIVE_SPEED, -500);
	wait1Msec(1000 * 2);
	// Turn to align with the goal
	driveToGyro(90, false);

	// Disabled for the moment
	//AutoScore();
}

void AutoKickstandIntermediate() {
	//turn towards pole
	driveToGyro(45, true);
	//drive until pole is down
	driveToEncoder(AUTO_DRIVE_SPEED, 200);
	// Back up to avoid hitting the goal
	driveToEncoder(-AUTO_DRIVE_SPEED, 100);
	// Align parallel to the goal
	driveToGyro(90, false);

	AutoScore();
}

void AutoKickstandSide() {
		// Re-align to pole position
		driveToGyro(90, true);
		driveToEncoder(AUTO_DRIVE_SPEED, 50);
		driveToGyro(90, false);

		// Hit the kickstand
		driveToEncoder(AUTO_DRIVE_SPEED, 200);
		// Align parallel to the goal
		driveToGyro(90, false);

		AutoScore();
}

#endif
