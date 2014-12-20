#ifndef FTC_Drive
#define FTC_Drive

// Motor Speeds
#define WHEEL_MAX (100)
#define SPINNER_IN (100)
#define SPINNER_OUT (-50)
#define LIFT_UP (100)
#define LIFT_DOWNF (100)
#define LIFT_DOWNS (75)
#define GYRO_SPEED (80)

#define IR_SIG_LOST (10)

//Sensors to Use in 'driveTo' functions in case of multiple sensors
tMUXSensor IR;

void initIR(tMUXSensor irSensor) {
	IR = irSensor;
}

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

// Motor Driving Methods for Non-Wheel Motors
void DriveSpinnerMotor(int power) {
	motor[spinnerMotor] = power;
}

void StopSpinnerMotor() {
	DriveSpinnerMotor(0);
}

// Drive until we hit any of the specified parameters
bool driveToParam(int speed, int distance = 0, int time = 5000, bool turn = false, bool horizontal = false, int ir = 0, int sonar = 0, int gyro = 0) {
	// Stop
	stopDriveMotors();

	// Ensure the time is less than 32k (16-bit timer limit)
	if (time > 32000) {
		time = 32000;
	}

	// Sanity checks -- we need a valid speed and at least one stop paramter (other than time)
	if (speed == 0) {
		return false;
	}

	// Assume the caller was reasonable in matching their signs
	distance = abs(distance);

	// Setup the gyro, if requested, and force the bools and signs to reasonable values
	if (gyro != 0) {
		turn = true;
		gyro = abs(gyro);
		gyro -= GYRO_OVERRUN;
		startGyro();
	}

	// Reset the encoder, gyro, and timer
	resetDriveEncoder();
	resetGyro();
	ClearTimer(T1);

	// Drive straight or turn
	if (turn) {
		runDriveMotors(-speed, speed);
	} else if(horizontal) {
		runDriveMotorsHorizontal(speed, speed);
	} else {
		runDriveMotors(speed, speed);
	}

	// Track sensor failures
	bool failed = false;

	// Loop until we hit a stop condition
	while (true) {
		if (distance != 0 && (abs(readDriveEncoder()) > distance)) {
			break;
		} else if (time != 0 && (time1[T1] > time)) {
			break;
		} else if (ir != 0) {
			int irVal = readIR(IR);

			// Stop if the IR reading is invalid
			if (!irValid(irVal)) {
				failed = true;
				break;
			}

			// Stop when we hit he IR target
			if (ir == irVal) {
				break;
			}
		} else if (sonar != 0) {
			int sonarVal = readSonar();

			// Stop if the sonar reading is invalid (i.e. 0)
			if (!sonarVal) {
				failed = true;
				break;
			}

			// Approach when sonar is > 0, recede with sonar < 0
			if (
				(sonar > 0 && (sonarVal < abs(sonar))) ||
				(sonar < 0 && (sonarVal > abs(sonar)))
			) {
				break;
			}
		} else if (gyro != 0) {
			// Stop if the gyro reading is invalid
			if (!gyroValid()) {
				failed = true;
				break;
			}

			// Turn until we exceed the requested (absolute) angle
			int angle = abs(readGyro());
			if (angle > gyro) {
				break;
			}
		}
	}

	// Always stop for just a moment when we're done
	stopDriveMotors();

	// Stop the gyro, if we started it
	if (gyro != 0) {
		StopTask(gyro);
	}

	// Return false if there was a sensor error
	return !failed;
}

// Shorthand for IR-based driving
bool driveToIR(int speed, bool turn, bool horizontal, int ir, int time = 5000) {
	return driveToParam(speed, 0, time, turn, horizontal, ir, 0, 0);
}

// Shorthand for sonar-based driving
bool driveToSonar(int speed, int sonar, bool horizontal, int time = 5000) {
	return driveToParam(speed, 0, time, false, horizontal, 0, sonar, 0);
}

// Shorthand for distance-based driving
void driveToEncoder(int speed, int distance, int time = 5000) {
	driveToParam(speed, distance, time, false, false, 0, 0, 0);
}

// Shorthand for gyro-based driving
bool driveToGyro(int degrees, bool left = true, int time = 5000) {
	// Turn right if requested
	int speed = GYRO_SPEED;
	if (!left) {
		speed *= -1;
		degrees *= -1;
	}
	return driveToParam(speed, 0, time, true, false, 0, 0, degrees);
}

// Drive until the sonar returns *something*
bool driveToSonarRange(int speed, int overdrive = 500, int timeout = 5000, int interval = 100) {
	ClearTimer(T3);
	while (time1[T3] < timeout && !readSonarMax()) {
		driveToEncoder(speed, interval);
	}
	driveToEncoder(speed, overdrive);
	return (bool)readSonarMax();
}

#endif
