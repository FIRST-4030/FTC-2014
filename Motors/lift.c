#ifndef FTC_LIFT
#define FTC_LIFT

#define LIFT_SPEED (100)
#define LIFT_DEAD_ZONE (100)
#define LIFT_FULL_ERR (100)

#define LIFT_HEIGHT_COLLECT (10)
#define LIFT_HEIGHT_DRIVE (1000)
#define LIFT_HEIGHT_LOW (5000)
#define LIFT_HEIGHT_MED (10000)
#define LIFT_HEIGHT_HIGH (13000)

// Define to use the Tetrix PID system
// Clear to use our local PID system
//#define LIFT_REMOTE_PID

bool liftReady = false;
bool liftAtTarget = false;
tMotor liftDrive;
tSensors liftTouch;
typedef enum {
        RESET,
        COLLECT,
        DRIVE,
        LOW,
        MED,
        HIGH
} LiftState;
LiftState liftCmd = RESET;

void driveLift(int speed) {
	motor[liftDrive] = speed;
	#ifdef LIFT_REMOTE_PID
		nMotorEncoderTarget[liftDrive] = 0;
	#endif
}

#ifdef LIFT_REMOTE_PID
	void driveLiftTarget(int speed, int target) {
		// The remote PID treats 0 as a special value, so use 1
		if (target == 0) {
			target = 1;
		}

		nMotorEncoderTarget[liftDrive] = target;
		motor[liftDrive] = speed;
	}

	TNxtRunState liftTargetState() {
		return nMotorRunState[liftDrive];
	}
#endif

void stopLift() {
	driveLift(0);
}

void initLift(tMotor lift, tSensors touch) {
	liftDrive = lift;
	liftTouch = touch;
	stopLift();
}

bool readLiftTouch() {
	if (SensorValue[liftTouch]) {
		return true;
	}
	return false;
}

void resetLiftEncoder() {
	nMotorEncoder[liftDrive] = 0;
}

int readLiftEncoder() {
	return nMotorEncoder[liftDrive];
}

void liftFatalErr() {
	hogCPU();
	stopLift();
	nxtDisplayCenteredBigTextLine(1, "Lift Err");
	wait1Msec(20*1000);
	StopAllTasks();
}

bool isLiftReady() {
	return liftReady;
}

void waitLiftReady() {
	while (!isLiftReady()) {
		wait1Msec(10);
	}
}

void liftReset() {
	liftReady = false;
	liftCmd = RESET;
	waitLiftReady();
}

LiftState getLiftCmd() {
	if (!isLiftReady()) {
		return RESET;
	}
	return liftCmd;
}

bool setLiftCmd(LiftState cmd) {
	if (!isLiftReady()) {
		return false;
	}
	liftAtTarget = false;
	liftCmd = cmd;
	return true;
}

bool isLiftAtTarget() {
	if (!isLiftReady()) {
		return false;
	}
	return liftAtTarget;
}

void waitLiftAtTarget() {
	while (!isLiftAtTarget()) {
		wait1Msec(10);
	}
}

bool setWaitLiftCmd(LiftState cmd) {
	if (!setLiftCmd(cmd)) {
		return false;
	}
	waitLiftAtTarget();
	return true;
}

task Lift() {

	// Run forever
	while (true) {

		nxtDisplayBigTextLine(1, "%d %d", (int)liftCmd, readLiftEncoder());

		// When reset is commanded ignore everything else until we are ready
		if (liftCmd == RESET) {
			while (!readLiftTouch()) {
				nxtDisplayBigTextLine(1, "Reset %d", readLiftTouch());
				driveLift(-LIFT_SPEED);
			}
			nxtDisplayBigTextLine(1, "Ready");
			stopLift();
			resetLiftEncoder();
			liftCmd = COLLECT;
			liftReady = true;
			continue;
		}

		// Determine the height we'd like the lift to be at
		int liftCmdHeight = 0;
		switch (liftCmd) {
			case COLLECT:
				liftCmdHeight = LIFT_HEIGHT_COLLECT;
				break;

			case DRIVE:
				liftCmdHeight = LIFT_HEIGHT_DRIVE;
				break;

			case LOW:
				liftCmdHeight = LIFT_HEIGHT_LOW;
				break;

			case MED:
				liftCmdHeight = LIFT_HEIGHT_MED;
				break;

			case HIGH:
				liftCmdHeight = LIFT_HEIGHT_HIGH;
				break;

			case RESET:
				break;

			// If we get here something bad happened
			// Stop the lift and exit the task
			default:
				liftFatalErr();
				// liftFatalErr should never return, but for clarity:
				break;
		}

		// Calculate the difference between the current lift height and the desired lift height
		int liftErr = liftCmdHeight - readLiftEncoder();
		int liftErrAbs = abs(liftErr);

		// In theory we can do this and let the motor controller deal with the details
		#ifdef LIFT_REMOTE_PID
			if (liftErrAbs >= LIFT_DEAD_ZONE) {
				driveLiftTarget(LIFT_SPEED, liftCmdHeight);
			}

			// Acknowledge remote PID completion
			if (liftTargetState() == runStateIdle) {
					stopLift();
			}

		// But in case that does not work
		#else

			// Calculate a lift speed based on the magnitude of the lift height error
			int liftSpeed = 0;
			if (liftErrAbs < LIFT_DEAD_ZONE) {
				// No motion when we're in the dead zone
				liftSpeed = 0;
			} else if (liftErrAbs >= LIFT_FULL_ERR) {
				// Full speed if we're more than LIFT_FULL_ERR away from the target
				liftSpeed = 100;
			} else {
				// More slowly as we approach the target
				// This is the "P" of PID. We may also need an "I".
				liftSpeed = ((LIFT_FULL_ERR - liftErrAbs) * LIFT_SPEED) / LIFT_FULL_ERR;
			}

			// Invert the lift speed if the lift should move down
			if (liftErr < 0) {
				liftSpeed *= -1;
			}

			// Drive the lift and loop
			driveLift(liftSpeed);

		#endif

		// Note when we're on-target for outside observers
		if (liftErrAbs < LIFT_DEAD_ZONE) {
			liftAtTarget = true;
		} else {
			liftAtTarget = false;
		}
	}
}

#endif
