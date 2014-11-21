#ifndef FTC_INIT_ROBOT
#define FTC_INIT_ROBOT

///// INITIALIZE ROBOT /////
void initializeRobot() {

	// Stop all drive motors
	#ifdef FTC_MOTORS
	initMotors(leftFrontMotor, leftRearMotor, rightFrontMotor, rightRearMotor);
	#endif
	#ifdef FTC_LIFT
	initLift(liftMotor, liftTS);
	#endif

	// Stop the spinner
	#ifdef FTC_SPINNER
	// Not yet implemented
	//initSpinner(spinnerMotor);
	//motor[spinnerMotor] = 0;
	#endif FTC_SPINNER

	// Set servo rates and start positions
	#ifdef FTC_SERVOS
	servosInit(goalHook, hopperTilt);
	#endif
}

#endif
