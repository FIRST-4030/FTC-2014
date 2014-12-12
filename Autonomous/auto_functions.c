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

bool AutoScore() {
	// Move the lift so we get clear sonar readings
	setWaitLiftCmd(LOW);

	// Drive into sonar range
	if (!driveToSonarRange(AUTO_DRIVE_SPEED_LOW)) {
		return false;
	}

	// Re-align to IR, just in case we drifted
	if (!driveToIR(-AUTO_DRIVE_SPEED, true, false, IR_MID)) {
		return false;
	}

	// Approach the goal and turn to correct for IR offset
	if (!driveToSonar(AUTO_DRIVE_SPEED_LOW, 34)) {
		return false;
	}
	driveToGyro(20, TURN_LEFT);

	// Start the lift up and sungle in tight
	setLiftCmd(HIGH);
	driveToSonar(AUTO_DRIVE_SPEED_CRAWL, 30, false, 1000);

	// Wait for the lift and dump
	waitLiftAtTarget();
	servoHighDrop();
	wait1Msec(500);
	servoHighHold();

	// Return lift and back up slightly
	setLiftCmd(COLLECT);
	wait1Msec(1 * 1000);
	driveToEncoder(-AUTO_DRIVE_SPEED_LOW, 500);
	waitLiftAtTarget();
	
	// IF we get here all was well
	return true;
}

void AutoKickstand() {
	// Turn to line up side sensor
	driveToGyro(50, !TURN_LEFT);

	// Move to the side, turn, move forward and hit kickstand
	driveToIR(AUTO_DRIVE_SPEED, false, false, IR_MID - 2);
	driveToGyro(180, TURN_LEFT);
	driveToEncoder(-AUTO_DRIVE_SPEED, 1000);
}

bool AutoScoreAhead() {
	driveToEncoder(AUTO_DRIVE_SPEED, 1600);
	driveToIR(AUTO_DRIVE_SPEED, false, false, 4);
	driveToGyro(90, TURN_LEFT);

	// Assume failure until we debug
	return false;
}

bool AutoScoreIntermediate() {
	// Align to IR
	driveToIR(AUTO_DRIVE_SPEED, true, false, IR_MID);
	
	// Assume failure until we debug
	return false;
}

bool AutoScoreSide() {

	// Turn left, drive past the beacon, turn back
	driveToGyro(45, TURN_LEFT);
	driveToEncoder(AUTO_DRIVE_SPEED, 4000);
	driveToGyro(130, !TURN_LEFT);

	// Turn to IR alignment
	if (!driveToIR(-AUTO_DRIVE_SPEED, true, false, IR_MID)) {
		return false;
	}
	
	// If we got here all is well
	return true;
}

#endif
