#ifndef FTC_INIT_ROBOT
#define FTC_INIT_ROBOT

///// INITIALIZE ROBOT /////
void initializeRobot() {

	// Stop All Motors //
	motor[leftFrontMotor] = 0;
	motor[leftRearMotor] = 0;
	motor[rightFrontMotor] = 0;
	motor[rightRearMotor] = 0;
	motor[spinnerMotor] = 0;
	motor[liftMotor] = 0;

	// Put Servos to Default Position //
	SetHookServo(HOOK_MIN);
	servoChangeRate[goalHook] = 1;

	SetHopperServo(HOPPER_MIN);
	servoChangeRate[hopperTilt] = 2;

	// Initialize encoders
	resetDriveEncoder();
}

#endif
