#ifndef FTC_INIT_ROBOT
#define FTC_INIT_ROBOT

///// INITIALIZE ROBOT /////
void initializeRobot() {

	// Stop all drive motors
	#ifdef FTC_MOTORS
	initMotors(leftFrontMotor, leftRearMotor, rightFrontMotor, rightRearMotor);
	#endif
	#ifdef FTC_LIFT
	initLift(liftMotor, liftTS, programPeriod);
	#endif

	// Stop the spinner
	#ifdef FTC_SPINNER
	// Not yet implemented
	//initSpinner(spinnerMotor);
	//motor[spinnerMotor] = 0;
	#endif FTC_SPINNER

	// Set servo rates and start positions
	#ifdef FTC_SERVOS
	servosInit(goalHook, lightLeft, highGoal);
	#endif

	#ifdef FTC_HOPPER
	hopperInit(hopperTilt);
	#endif

	//Set the IR sensor to be used
	#ifdef FTC_Drive
	initIR(IRSeeker);
	#endif

	// Set the sonar sensor to be used
	#ifdef FTC_SONAR
	initSonar(sonarLowSensor, sonarHighSensor);
	#endif
}

#endif
