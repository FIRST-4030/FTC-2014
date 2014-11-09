#ifndef FTC_LIFT
#define FTC_LIFT

tMotor liftPrimary;
void initLift(tMotor lift) {
	liftPrimary = lift;
	motor[liftPrimary] = 0;
}

runLiftMotor(int speed, const int duration = 0) {
	motor[liftPrimary] = speed;
	if (duration > 0) {
		wait1Msec(duration);
	}
}

void resetLiftEncoder() {
	nMotorEncoder[liftPrimary] = 0;
}

int readLiftEncoder() {
	return nMotorEncoder[liftPrimary];
}

task Lift()
{
	//All are just random, untested values, need to be changed
	int slowPoint = 100;
	int goal_Low = 30;
	int goal_Med = 60;
	int goal_High = 90;

	while(true) {
		if(joy2Btn(2) == 1) {
			while(SensorValue[lTouch] != 1) {

				if(readLiftEncoder < 100) {
					DriveLiftMotor[LIFT_DOWNS);
				} else {
					DriveLiftMotor(LIFT_DOWNF);
				}

			}
			StopLiftMotor();
			resetLiftEncoder();

		} else if(joy2Btn(1) == 1) {
			while(readLiftEncoder() < goal_Low) {
				DriveLiftMotor(LIFT_UP);
			}
			StopLiftMotor();

		} else if(joy2Btn(4) == 1) {
			while(readLiftEncoder() < goal_Med) {
				DriveLiftMotor(LIFT_UP);
			}
			StopLiftMotor();

		} else if(joy2Btn(3) == 1) {
			while(readLiftEncoder() < goal_High) {
				DriveLiftMotor(LIFT_UP);
			}
			StopLiftMotor();
		}
	}

}

#endif
