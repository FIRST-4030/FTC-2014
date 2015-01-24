#ifndef FTC_LIFT
#define FTC_LIFT
#define LIFT_DEBUG

#define LIFT_SPEED (100)
#define LIFT_DEAD_ZONE (50)
#define LIFT_FULL_ERR (LIFT_DEAD_ZONE * 2)
#define LIFT_HEIGHT_ROBOT (5200)

//To calibrate the lift height high
int calibration = 0;
#define LIFT_HEIGHT_CHANGE (150)

#define LIFT_RESET_TIMEOUT (4)
#define LIFT_RESET_OFFSET (25)
#define LIFT_RESET_SPEED (0.2)

#define LIFT_HEIGHT_COLLECT (1)
#define LIFT_HEIGHT_DRIVE (1250)
#define LIFT_HEIGHT_LOW (5900)
#define LIFT_HEIGHT_MED (9600)
#define LIFT_HEIGHT_HIGH (13000)
#define LIFT_HEIGHT_CENTER (LIFT_HEIGHT_HIGH + 100)

// Define to use the Tetrix PID system
// Clear to use our local PID system
//#define LIFT_REMOTE_PID

bool liftReady = false;
bool liftAtTarget = false;
int lastLiftErr = 0;
tMotor liftDrive;
tSensors liftTouch;
typedef enum {
        RESET,
        COLLECT,
        DRIVE,
        LOW,
        MED,
        HIGH,
        CENTER
} LiftState;
LiftState liftCmd = RESET;
#define NUM_LIFT_STATES (7)
typedef enum {
				AUTONOMOUS,
				TELEOP
} LiftPeriod;
LiftPeriod liftPeriod;
#define NUM_LIFT_PERIODS (2)

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

void initLift(tMotor lift, tSensors touch, LiftPeriod period) {
	liftDrive = lift;
	liftTouch = touch;
	liftPeriod = period;
	stopLift();
}

void incrLiftHeightHigh() {
	calibration += LIFT_HEIGHT_CHANGE + lastLiftErr;
}

void decrLiftHeightHigh() {
	calibration -= LIFT_HEIGHT_CHANGE - lastLiftErr;
}

bool readLiftTouch() {
	if (SensorValue[liftTouch]) {
		return true;
	}
	return false;
}

void resetLiftEncoder(int offset = 0) {
	stopLift();
	wait1Msec(100);
	nMotorEncoder[liftDrive] = offset;
}

int readLiftEncoder() {
	return nMotorEncoder[liftDrive];
}

void liftFatalErr() {
	hogCPU();
	stopLift();
	nxtDisplayCenteredBigTextLine(1, "Lift Err");
	wait1Msec(20 * 1000);
	StopAllTasks();
}

bool isLiftAboveRobot() {
	return (readLiftEncoder() > LIFT_HEIGHT_ROBOT);
}

bool isLiftReady() {
	return liftReady;
}

void waitLiftReady() {
	while (!isLiftReady()) {
		abortTimeslice();
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

void waitLiftAboveRobot() {
	while(!isLiftAboveRobot()) {
		abortTimeslice();
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
	//For fail-safe code, may be inverted if needed
	int liftSpeed = LIFT_SPEED;

	// Track when we disable teleop drive
	bool driveStopped = false;

	// Run forever
	while (true) {

		#ifdef LIFT_DEBUG
			nxtDisplayBigTextLine(1, "%d %d", (int)liftCmd, readLiftEncoder());
		#endif

		// When reset is commanded ignore everything else until we are ready
		if (liftCmd == RESET && liftSpeed != 0) {

			// Try to get the lift down. Give if it doesn't happen promptly.
			ClearTimer(T1);
			while (!readLiftTouch()) {
				#ifdef LIFT_DEBUG
					nxtDisplayBigTextLine(1, "Reset %d", readLiftTouch());
				#endif
				driveLift(-liftSpeed);
				if(time1[T1] > 1000 * LIFT_RESET_TIMEOUT) {
					liftSpeed = 0;
				}
			}
			resetLiftEncoder();

			// If the lift is down, nudge it up to find the switch release point
			while (readLiftTouch()) {
				driveLift(liftSpeed * LIFT_RESET_SPEED);
			}
			resetLiftEncoder(LIFT_RESET_OFFSET);

			// Announce our completion status (or keep the RESET status if we failed)
			if (liftSpeed != 0) {
				liftCmd = COLLECT;
				liftReady = true;
				#ifdef LIFT_DEBUG
					nxtDisplayBigTextLine(1, "Ready");
				#endif
			} else {
				liftCmd = RESET;
				liftReady = false;
				#ifdef LIFT_DEBUG
					nxtDisplayBigTextLine(1, "Reset Failed");
					wait1Msec(1000 * LIFT_RESET_TIMEOUT);
				#endif
			}

			// Jump back to the top of the loop once the lift is ready
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
				liftCmdHeight = LIFT_HEIGHT_HIGH + calibration;
				break;

			case CENTER:
				liftCmdHeight = LIFT_HEIGHT_CENTER;
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
				driveLiftTarget(liftSpeed, liftCmdHeight);
			}

			// Acknowledge remote PID completion
			if (liftTargetState() == runStateIdle) {
					stopLift();
			}

		// But in case that does not work
		#else

			// Calculate a lift speed based on the magnitude of the lift height error
			int driveSpeed = 0;
			if (liftErrAbs < LIFT_DEAD_ZONE) {
				// No motion when we're in the dead zone
				driveSpeed = 0;
			} else if (liftErrAbs >= LIFT_FULL_ERR) {
				// Full speed if we're more than LIFT_FULL_ERR away from the target
				driveSpeed = liftSpeed;
			} else {
				// More slowly as we approach the target
				// This is the "P" of PID. We may also need an "I".
				driveSpeed = ((LIFT_FULL_ERR - liftErrAbs) * driveSpeed) / LIFT_FULL_ERR;
			}

			// Invert the lift speed if the lift should move down
			if (liftErr < 0) {
				driveSpeed *= -1;
			}

			// Drive the lift and loop
			driveLift(driveSpeed);

		#endif

		// Note when we're on-target for outside observers
		if (liftErrAbs < LIFT_DEAD_ZONE) {
			liftAtTarget = true;
			lastLiftErr = liftErr;
		} else {
			liftAtTarget = false;
		}

		//Start/Stop DriveMec based on if it's safe with the lift
		if(isLiftAboveRobot()) {
			driveStopped = true;
			if(liftPeriod == TELEOP) {
					StopTask(DriveMec);
					stopDriveMotors();
			}
		} else if (driveStopped) {
			driveStopped = false;
			#ifdef FTC_DRIVETASK
				if(liftPeriod == TELEOP) {
					StartTask(DriveMec);
				}
			#endif
		}

		// Surrender some time to other tasks
		EndTimeSlice();
	}
}

#endif
