#ifndef FTC_AUTO_FUNCTIONS
#define FTC_AUTO_FUNCTIONS

// Autonomous Mode Operational Functions //
// Put functions here which do specific actions on the robot. //

#define AUTO_DRIVE_SPEED (-100)
#define TURN_LEFT (false)
#define IR_MID (5)
#define IR_LEFT_SIDE (1)
#define IR_RIGHT_SIDE (9)
#define AUTO_DRIVE_SPEED_LOW (AUTO_DRIVE_SPEED * 0.2)
#define AUTO_DRIVE_SPEED_CRAWL (AUTO_DRIVE_SPEED_LOW * 0.5)
#define SONAR_FAR (36)
#define SONAR_NEAR (SONAR_FAR - 4)

bool AutoScore() {
	// Move the lift so we get clear sonar readings
	setWaitLiftCmd(LOW);

	// Drive into sonar range
	if (!driveToSonarRange(AUTO_DRIVE_SPEED_LOW, 500)) {
		servoHookCapture();
		wait1Msec(1000);
		servoHookRelease();
		return false;
	}

	// Approach the goal until we hit the SONAR_FAR target
	if (!driveToSonar(AUTO_DRIVE_SPEED_LOW, SONAR_FAR, false)) {
		servoHookCapture();
		servoHighDrop();
		wait1Msec(1000);
		servoHookRelease();
		servoHighHold();
		return false;
	}
	driveToGyro(20, TURN_LEFT);

	// Start the lift up and sungle in tight
	setLiftCmd(HIGH);
	driveToSonar(AUTO_DRIVE_SPEED_CRAWL, SONAR_NEAR, false, 1000);

	// Wait for the lift and dump
	waitLiftAtTarget();
	servoHighDrop();
	wait1Msec(750);
	servoHighHold();

	// Return lift and back up slightly
	setLiftCmd(DRIVE);
	driveToEncoder(-AUTO_DRIVE_SPEED_CRAWL, 500);
	while (isLiftAboveRobot()) {
		abortTimeslice();
	}

	// If we get here all was well
	return true;
}

void AutoKickstand() {
	// Turn and drive to clear center goal
	driveToGyro(60, TURN_LEFT);
	driveToEncoder(-AUTO_DRIVE_SPEED, 1000);

	// Turn to face back to kickstand
	driveToGyro(90, TURN_LEFT);

	// Hit kickstand
	driveToEncoder(-AUTO_DRIVE_SPEED, 3000);
}

bool AutoScoreAhead() {
	driveToEncoder(AUTO_DRIVE_SPEED, 2000);

	/*
	if(!driveToIR(AUTO_DRIVE_SPEED, true, false, IR_MID)) {
		return false;
	}
	*/
	driveToGyro(85, TURN_LEFT);

	// Assume failure until we debug
	return true;
}

bool AutoScoreIntermediate() {
	// Align to IR
	if(!driveToIR(AUTO_DRIVE_SPEED, true, false, IR_MID)) {
		return false;
	}

	return true;
}

bool AutoScoreSide() {

	// Turn left, drive past the beacon, turn back
	driveToGyro(30, TURN_LEFT);
	driveToEncoder(AUTO_DRIVE_SPEED, 4000);
	driveToGyro(130, !TURN_LEFT);

	// Turn to IR alignment
	if (!driveToIR(-AUTO_DRIVE_SPEED, true, false, IR_MID + 1)) {
		return false;
	}
	wait1Msec(500);
	driveToGyro(20, !TURN_LEFT);

	// If we got here all is well
	return true;
}

#endif
