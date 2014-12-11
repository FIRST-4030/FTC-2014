#ifndef FTC_HOPPER
#define FTC_HOPPER

#define HOPPER_POS_DOWN (50)
#define HOPPER_POS_MID (135)
#define HOPPER_POS_UP (220)

bool hopperReady = false;
bool hopperAtTarget = false;
int hopperDumpTime = 3.5 * 1000;
typedef enum {
        DOWN,
        HALF,
        UP,
} HopperState;
HopperState hopperCmd = UP;

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

void waitHopperAtTarget() {
	while (!isHopperAtTarget()) {
		wait1Msec(10);
	}
}

void setWaitHopperCmd(HopperState cmd) {
	setHopperCmd(cmd);
	waitHopperAtTarget();
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
