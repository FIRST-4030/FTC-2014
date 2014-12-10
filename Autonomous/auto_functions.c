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

void AutoScore() {

	setWaitLiftCmd(LOW);
	ClearTimer(T3);
	while (time1[T3] < 5 * 1000 && !readSonar()) {
		driveToEncoder(AUTO_DRIVE_SPEED_LOW, 100);
	}
	driveToEncoder(AUTO_DRIVE_SPEED_LOW, 1000);
	servoHookCapture();
	wait1Msec(1 * 1000);
	servoHookRelease();
	if (!driveToIR(-AUTO_DRIVE_SPEED, true, false, IR_MID)) {
		setWaitLiftCmd(MED);
		return;
	}
	ClearTimer(T3);
	while (time1[T3] < 3 * 1000 && readSonar() > 34) {
		driveToEncoder(AUTO_DRIVE_SPEED_LOW, 50);
	}
	driveToGyro(20, TURN_LEFT);
	ClearTimer(T3);
	while (time1[T3] < 3 * 1000 && readSonar() > 30) {
		driveToEncoder(AUTO_DRIVE_SPEED_LOW, 50);
	}

	// Put the lift up and dump
	setWaitLiftCmd(HIGH);
	servoHighDrop();
	wait1Msec(500);
	servoHighHold();

	// Return lift and back up slightly
	setLiftCmd(COLLECT);
	wait1Msec(500);
	driveToEncoder(-AUTO_DRIVE_SPEED_LOW, 500);
	waitLiftAtTarget();
}

void AutoKickstand() {
	// Turn to line up side sensor
	driveToGyro(50, !TURN_LEFT);

	// Move to the side, turn, move forward and hit kickstand
	driveToIR(AUTO_DRIVE_SPEED, false, false, IR_MID - 2);
	driveToGyro(180, TURN_LEFT);
	driveToEncoder(-AUTO_DRIVE_SPEED, 1000);
}

void AutoScoreAhead() {
	driveToEncoder(AUTO_DRIVE_SPEED, 1600);
	driveToIR(AUTO_DRIVE_SPEED, false, false, 4);
	driveToGyro(90, TURN_LEFT);

	// High goal and kickstand
	//AutoScore();
	//AutoKickstand();
}

void AutoScoreIntermediate() {

	// Align to IR
	driveToIR(AUTO_DRIVE_SPEED, true, false, IR_MID);

	// High goal and kickstand
	AutoScore();
	//AutoKickstand();
}

void AutoScoreSide() {

	// Turn left, drive past the beacon, turn back
	driveToGyro(45, TURN_LEFT);
	driveToEncoder(AUTO_DRIVE_SPEED, 4000);
	driveToGyro(130, !TURN_LEFT);

	// Turn to IR alignment, then tune with the gyro
	if (!driveToIR(-AUTO_DRIVE_SPEED, true, false, IR_MID)) {
		setWaitLiftCmd(MED);
		return;
	}

	// High goal and kickstand
	AutoScore();
	//AutoKickstand();
}

#endif
