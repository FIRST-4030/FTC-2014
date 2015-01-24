#ifndef FTC_HOPPER
#define FTC_HOPPER

#define HOPPER_MAX (220)
#define HOPPER_MIN (50)
#define HOPPER_RATE (0)

#define HOPPER_POS_DOWN (50)
#define HOPPER_POS_MID (110)
#define HOPPER_POS_UP (220)

bool dumpSignal = false;
typedef enum {
        DOWN,
        HALF,
        UP,
} HopperState;
HopperState hopperCmd = UP;
float DUMP_DELAYS[NUM_LIFT_STATES];

void SetHopperServo (HopperState cmd, int min = HOPPER_MIN, int max = HOPPER_MAX) {
	int position = HOPPER_POS_UP;
	switch (cmd) {

		case DOWN:
			position = HOPPER_POS_DOWN;
			break;

		case HALF:
			position = HOPPER_POS_MID;
			break;

		case UP:
			position = HOPPER_POS_UP;
			break;
	}
	setServo(servoHopper, position, min, max);
}

int getHopperServo() {
	return ServoValue[servoHopper];
}

void hopperInit(TServoIndex hopper) {
	servoHopper = hopper;
	servoChangeRate[servoHopper] = HOPPER_RATE;
	SetHopperServo(UP);

	DUMP_DELAYS[HIGH] = 2.25;
	DUMP_DELAYS[MED] = 2.75;
	DUMP_DELAYS[LOW] = 3.5;
}

void hopperFatalErr() {
	hogCPU();
	nxtDisplayCenteredBigTextLine(1, "Hopper Err");
	wait1Msec(20*1000);
	StopAllTasks();
}

HopperState getHopperCmd() {
	return hopperCmd;
}

bool hopperAutoDump() {
	//Safety check, can't dump for a lift below LOW
	if(getLiftCmd() < LOW) {
		return false;
	}

	//Raises dump signal
	dumpSignal = true;
	return true;
}

task Hopper() {
	// Run forever
	while (true) {
		LiftState liftCmd = getLiftCmd();

		// Clear the dump signal when the liftCmd goes to any non-scoring position
		if (dumpSignal && liftCmd < LOW) {
			dumpSignal = false;
		}

		// Dump when we're on-target and flagged for dump
		if (dumpSignal && isLiftAtTarget()) {
			SetHopperServo(DOWN);
			wait1Msec(1000 * DUMP_DELAYS[(int)liftCmd]);
			setLiftCmd(COLLECT);
		// Hopper at half when above the robot body
		} else if (isLiftAboveRobot()) {
			SetHopperServo(HALF);
		// Hopper upright when below robot body
		} else {
			SetHopperServo(UP);
		}
	}
}

#endif
