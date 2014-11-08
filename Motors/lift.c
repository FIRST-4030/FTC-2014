#ifndef FTC_LIFTTASK
#define FTC_LIFTTASK

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