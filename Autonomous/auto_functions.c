#ifndef FTC_AUTO_FUNCTIONS
#define FTC_AUTO_FUNCTIONS

// Autonomous Mode Operational Functions //
// Put functions here which do specific actions on the robot. //

//Note: Stop motors in between driving tasks

void autoKickStandWTurn() {
	//insert code here//
}

void autoKickStandWOTurn() {
	//Use Timer to determine if touch sensor is nonresponsive
	ClearTimer(T1);

	//Time maxes out at 10 seconds, after that assume that touch sensor is not returning proper values
	while(!isKSPressed() && time100[T1] < 100) {
		DriveForward(100);
	}
	StopWheelMotors();

	//Drive Left Until Certain We've Hit the Kickstand
	resetDriveEncoders();
	int leftDistance = 10; //To be replaced
	while(readAvgLeftDriveEncoder() < leftDistance) {
		DriveLeft();
	}
	StopWheelMotors();

	// Insert code to navigate to center field goal and score //
}

void autoParking() {
	if(irValid()) {
		if(readIR() == 5) {
			autoKickStandWTurn();
		} else {
			autoKickStandWOTurn();
		}
	}
}

#endif
