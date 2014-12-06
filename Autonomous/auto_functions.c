#ifndef FTC_AUTO_FUNCTIONS
#define FTC_AUTO_FUNCTIONS

// Autonomous Mode Operational Functions //
// Put functions here which do specific actions on the robot. //

#define AUTO_DRIVE_SPEED (-100)
#define TURN_LEFT (false)
#define IR_MID (5)
#define IR_LEFT_SIDE (1)
#define IR_RIGHT_SIDE (9)

void AutoScore(int encoder) {
	//Drive forward into center goal
	driveToEncoder(AUTO_DRIVE_SPEED, encoder);
	//driveToIR(AUTO_DRIVE_SPEED * 3/4, false, false, IR_SIG_LOST);
	//driveToEncoder(AUTO_DRIVE_SPEED, 1000);

	/*
	//Raise lift to high
	setWaitLiftCmd(HIGH);

	//Dump
	servoHighDrop();
	wait1Msec(1 * 1000);
	servoHighHold();

	//Lower lift
	setWaitLiftCmd(COLLECT);
	*/

	//Back up
	driveToEncoder(-AUTO_DRIVE_SPEED, 500);
}

void AutoKickstand() {
	//Turn to line up side sensor
	driveToGyro(50, !TURN_LEFT);

	//Move to the side, turn, move forward and hit kickstand
	driveToIR(AUTO_DRIVE_SPEED, false, false, IR_MID - 2);
	driveToGyro(180, TURN_LEFT);
	driveToEncoder(-AUTO_DRIVE_SPEED, 1000);
}

void AutoScoreAhead() {
	driveToEncoder(AUTO_DRIVE_SPEED, 1600);
	driveToIR(AUTO_DRIVE_SPEED, false, false, 4);
	driveToGyro(90, TURN_LEFT);

	//AutoScore();

	//AutoKickstand();
}

void AutoScoreIntermediate() {
	driveToIR(AUTO_DRIVE_SPEED, true, false, IR_MID);

	AutoScore(500);

	//AutoKickstand();
}

void AutoScoreSide() {
	//Turn left, drive far out, and turn back
	driveToGyro(45, TURN_LEFT);
	//Center on IR beacon
	driveToIR(AUTO_DRIVE_SPEED, false, false, IR_RIGHT_SIDE);

	driveToGyro(70, !TURN_LEFT);
	//Turn out to determine direction
	driveToIR(-AUTO_DRIVE_SPEED, true, false, IR_MID + 1);
	driveToGyro(10, !TURN_LEFT);

	AutoScore(750);

	AutoKickstand();
}

#endif
