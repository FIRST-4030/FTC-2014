#ifndef FTC_MOTORS
#define FTC_MOTORS

// Store the motor ports for use in drive functions
tMotor driveLeftFront;
tMotor driveLeftRear;
tMotor driveRightFront;
tMotor driveRightRear;

// Run motors at the specified speed indefinately
void runDriveMotors(int left, int right) {
	motor[driveLeftFront]  = left;
	motor[driveLeftRear]  = left;
	motor[driveRightFront] = right;
	motor[driveRightRear] = right;
}

// Stop all drive motion
void stopDriveMotors() {
	runDriveMotors(0, 0);
	wait1Msec(100);
}

// Run motors at the specified speed, stopping after DURATION milliseconds
void driveMotors(int left, int right, const int duration = 0) {
	runDriveMotors(left, right);
	if (duration > 0) {
		wait1Msec(duration);
	}
}

// Encoder methods for wheels
void resetDriveEncoders() {
	nMotorEncoder[driveLeftFront] = 0;
	nMotorEncoder[driveLeftRear] = 0;
	nMotorEncoder[driveRightFront] = 0;
	nMotorEncoder[driveRightRear] = 0;
}

int readAvgLeftDriveEncoder() {
	return (nMotorEncoder[driveLeftRear] + nMotorEncoder[driveRightFront]) * -1 / 2;
}

int readAvgRightDriveEncoder() {
	return (nMotorEncoder[driveLeftFront] + nMotorEncoder[driveRightRear]) * -1 / 2;
}

int readAvgDriveEncoder() {
	return (nMotorEncoder[driveLeftFront] + nMotorEncoder[driveLeftRear]
	+ nMotorEncoder[driveRightFront] +	nMotorEncoder[driveRightRear]) * -1 / 4;
}

void initMotors(tMotor leftF, tMotor leftR, tMotor rightF, tMotor rightR) {
	driveLeftFront = leftF;
	driveLeftRear = leftR;
	driveRightFront = rightF;
	driveRightRear = rightR;
	stopDriveMotors();
	resetDriveEncoders();
}

#endif
