#ifndef FTC_AUTO_FUNCTIONS
#define FTC_AUTO_FUNCTIONS

// Autonomous Mode Operational Functions //
// Put functions here which do specific actions on the robot. //

#define AUTO_DRIVE_SPEED (100)

// Assuming a start position parallel to the goal, back up and score
void AutoScore() {
	//drive backwards until IR is in view
	driveToIR(AUTO_DRIVE_SPEED, 1);
	//drive backwards until we're at an angle we can score from
	driveToEncoder(-AUTO_DRIVE_SPEED, 200);
	//turn facing IR
	driveToIR(AUTO_DRIVE_SPEED, 5);
	//Drive until ball is in goal
	// Not implemented -- driveToTouch(AUTO_DRIVE_SPEED, TS_index);
}

void AutoKickstandAhead() {
	// Hit the kickstand
	driveToEncoder(AUTO_DRIVE_SPEED, 400);
	// Back up to avoid hitting the goal
	driveToEncoder(-AUTO_DRIVE_SPEED, -100);
	// Turn to align with the goal
	driveToGyro(90, false);

	AutoScore();
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
