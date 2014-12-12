#ifndef FTC_HOPPER
#define FTC_HOPPER

#define HOPPER_MAX (220)
#define HOPPER_MIN (50)
#define HOPPER_RATE (0)

#define HOPPER_POS_DOWN (50)
#define HOPPER_POS_MID (135)
#define HOPPER_POS_UP (220)

bool hopperAtTarget = false;
int hopperDumpTime = 3.5 * 1000;
typedef enum {
        DOWN,
        HALF,
        UP,
} HopperState;
HopperState hopperCmd = UP;

void SetHopperServo (int position, int min = HOPPER_MIN, int max = HOPPER_MAX) {
	setServo(servoHopper, position, min, max);
}

int getHopperServo() {
	return ServoValue[servoHopper];
}

void hopperInit(TServoIndex hopper) {
	servoHopper = hopper;
	servoChangeRate[servoHopper] = HOPPER_RATE;
	SetHopperServo(HOPPER_MAX);
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

void setHopperCmd(HopperState cmd) {
	hopperAtTarget = false;
	hopperCmd = cmd;
}

bool isHopperAtTarget() {
	return hopperAtTarget;
}

void setWaitHopperCmd(HopperState cmd) {
	setHopperCmd(cmd);
	if(cmd == DOWN) {
		wait1Msec(hopperDumpTime);
	}
}

bool isHopperAtTarget() {
	return hopperAtTarget;
}

task Hopper() {
	// Run forever
	while (true) {
		// Determine the position the hopper should be at
		int hopperCmdPos = 0;
		switch (hopperCmd) {
			case DOWN:
				hopperCmdPos = HOPPER_POS_DOWN;
				break;

			case HALF:
				hopperCmdPos = HOPPER_POS_MID;
				break;

			case UP:
				hopperCmdPos = HOPPER_POS_UP;
				break;

			// If we get here something bad happened
			// Stop the hopper and exit the task
			default:
				hopperFatalErr();
				// hopperFatalErr should never return, but for clarity:
				break;
		}

		//Change position to the inputted one
		SetHopperServo(hopperCmdPos);

		// Note when we're on-target for outside observers
		if (getHopperServo() == hopperCmdPos) {
			hopperAtTarget = true;
		} else {
			hopperAtTarget = false;
		}

	}
}

#endif
