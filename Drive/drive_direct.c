#ifndef FTC_DRIVEDIRECT
#define FTC_DRIVEDIRECT

// Direct Drive Functions for drive_tank //
void DriveLeftSide(int power) {
	power = (float)power * 100.0/128.0;
	if (power > WHEEL_MAX) {
		power = WHEEL_MAX;
	}
  motor[leftFrontMotor] = power;
	motor[leftRearMotor] = power;
}

void DriveRightSide(int power) {
	power = (float)power * 100.0/128.0;
	if (power > WHEEL_MAX) {
		power = WHEEL_MAX;
	}
	motor[rightFrontMotor] = power;
	motor[rightRearMotor] = power;
}

#endif
