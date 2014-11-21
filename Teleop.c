#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     motors,         sensorNone)
#pragma config(Sensor, S2,     SMUX,           sensorI2CCustom9V)
#pragma config(Sensor, S3,     servos,         sensorNone)
#pragma config(Sensor, S4,     liftTS,         sensorTouch)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, reversed, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     leftFrontMotor, tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftRearMotor, tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     rightFrontMotor, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     rightRearMotor, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     liftMotor,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     spinnerMotor,  tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S3_C1_1,    goalHook,             tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    hopperTilt,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_3,    unusedS3C13,          tServoStandard)
#pragma config(Servo,  srvo_S3_C1_4,    unusedS3C14,          tServoStandard)
#pragma config(Servo,  srvo_S3_C1_5,    unusedS3C15,          tServoStandard)
#pragma config(Servo,  srvo_S3_C1_6,    unusedS3C16,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma debuggerWindows("joystickGame");
#include "teleop_includes.h"

task main()
{
  initializeRobot();
  waitForStart();

  StartTask(DriveMec);
  StartTask(Lift);

  bool pressedSix = false;
  bool spinnerIn = false;

	while(true)
	{
		getJoystickSettings(joystick);
		//int encoder = readDriveEncoder();
		//int ir = readIR();

		//Goal Hook Servo
		if(joy1Btn(7) || joy1Btn(8)) {
			SetHookServo(HOOK_MAX);
		} else if (joy1Btn(5) || joy1Btn(6)) {
			SetHookServo(HOOK_MIN);
		}

		//Spinner Motor
		if(joy2Btn(6))
			pressedSix = true;

		if(pressedSix && !joy2Btn(6)) {
			pressedSix = false;
			spinnerIn = !spinnerIn;
		}
		if(spinnerIn) {
			DriveSpinnerMotor(SPINNER_IN);
		} else {
			StopSpinnerMotor();
		}

		if (joy2Btn(1) && joy2Btn(2)) {
			liftReset();
		} else if (joy2Btn(3) && joy2Btn(4)) {
			setLiftCmd(HIGH);
		} else if(joy2Btn(1)) {
			setLiftCmd(COLLECT);
		} else if(joy2Btn(2)) {
			setLiftCmd(DRIVE);
		} else if(joy2Btn(3)) {
			setLiftCmd(LOW);
		} else if(joy2Btn(4)) {
			setLiftCmd(MED);
		}

		//Tilting Hopper Servo
		if(joystick.joy2_TopHat == 0) {
			SetHopperServo(HOPPER_MIN);
		} else if(joystick.joy2_TopHat == 4) {
			SetHopperServo(HOPPER_MAX);
		}
	}
}
