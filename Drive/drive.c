#ifndef FTC_Drive
#define FTC_Drive

// Motor Speeds
#define WHEEL_MAX (100)

//Driving Method for Wheels, Called Directly in Tele-Op
//The params are naturally the joysticks, thus named after their axis
void DriveMecWheels(int Y1, int X1, int X2) {
	Y1 = -Y1;
	X1 = -X1;
	motor[leftRearMotor] = Y1 - X2 - X1;
	motor[leftFrontMotor] =  Y1 - X2 + X1;
	motor[rightRearMotor] = Y1 + X2 + X1;
	motor[rightFrontMotor] =  Y1 + X2 - X1;
}

//Basic Four Directions for Driving in Autonomous
//Should always be passed a positive number 0-100 inclusive for motor speed
void DriveForward(int power) {
	DriveMecWheels(power, 0, 0);
}

void DriveBackward(int power) {
	DriveMecWheels(-power, 0, 0);
}

void DriveLeft(int power) {
	DriveMecWheels(0, -power, 0);
}

void DriveRight(int power) {
	DriveMecWheels(0, power, 0);
}

//Basic Turning for Autonomous
//Should always be passed a positive number 0-100 inclusive for motor speed
void TurnLeft(int power) {
	DriveMecWheels(0, 0, -power);
}

void TurnRight(int power) {
	DriveMecWheels(0, 0, power);
}

//Stopping Motors

//Stopping wheels with this method is only necessary in auto
void StopWheelMotors() {
	DriveMecWheels(0, 0, 0);
}

#endif
