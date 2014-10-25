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
	while(!isPressed() && time100[T1] < 100) {
		DriveForward(100);
	}
	StopWheelMotors();

	//insert code to drive left until a certain encoder value is hit here//
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
