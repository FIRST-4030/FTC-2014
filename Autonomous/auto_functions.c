#ifndef FTC_AUTO_FUNCTIONS
#define FTC_AUTO_FUNCTIONS

// Autonomous Mode Operational Functions //
// Put functions here which do specific actions on the robot. //

#define AUTO_DRIVE_SPEED (-100)
#define TURN_LEFT (false)
#define TURN_RIGHT (true)
#define IR_MID (5)
#define IR_LEFT_SIDE (1)
#define IR_RIGHT_SIDE (9)
#define AUTO_DRIVE_SPEED_LOW (AUTO_DRIVE_SPEED * 0.2)
#define AUTO_DRIVE_SPEED_CRAWL (AUTO_DRIVE_SPEED_LOW * 0.7)
#define SONAR_FAR (35)
#define SONAR_NEAR (SONAR_FAR - 3)

bool AutoScore() {
	// Move the lift so we get clear sonar readings
	setWaitLiftCmd(LOW);

	// Drive into sonar range
	if (!driveToSonarRange(AUTO_DRIVE_SPEED_CRAWL, 500)) {
		servoHookCapture();
		wait1Msec(1000);
		servoHookRelease();
		return false;
	}

	//Check to see if second approach is actually necessary
	if(readSonarMax(2) > SONAR_FAR) {

		// Approach the goal until we hit the SONAR_FAR target
		if (!driveToSonar(AUTO_DRIVE_SPEED_CRAWL, SONAR_FAR, false)) {
			servoHookCapture();
			servoHighDrop();
			wait1Msec(1000);
			servoHookRelease();
			servoHighHold();
			return false;
		}

	}

	driveToGyro(7, !TURN_LEFT);

	// Start the lift up and sungle in tight
	setLiftCmd(CENTER);

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
	driveToGyro(65, TURN_LEFT);
	driveToEncoder(-AUTO_DRIVE_SPEED, 1050);

	// Turn to face back to kickstand
	driveToGyro(100, TURN_LEFT);

	// Hit kickstand
	driveToEncoder(-AUTO_DRIVE_SPEED, 3500);
}

#endif
