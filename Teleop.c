#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     motors,         sensorI2CMuxController)
#pragma config(Sensor, S2,     SMUX,           sensorI2CCustom9V)
#pragma config(Sensor, S3,     servos,         sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, reversed, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     leftFrontMotor, tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftRearMotor, tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     rightFrontMotor, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     rightRearMotor, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     spinnerMotor,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     liftMotor,     tmotorTetrix, openLoop, encoder)
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

	while(true)
	{
		getJoystickSettings(joystick);

		//Goal Hook Servo
		if(joy1Btn(7)==1||joy1Btn(8)==1) {
			SetHookServo(HOOK_MAX);
		} else if (joy1Btn(5)==1||joy1Btn(6)==1) {
			SetHookServo(HOOK_MIN);
		}

		//Spinner Motor
		if(joy2Btn(6)==1) {
			DriveSpinnerMotor(SPINNER_IN);
		} else if(joy2Btn(5)==1) {
			DriveSpinnerMotor(SPINNER_OUT);
		} else {
			StopSpinnerMotor();
		}

		//Tilting Hopper Servo
		if(joystick.joy2_TopHat == 0) {
			SetHopperServo(HOPPER_MIN);
		} else if(joystick.joy2_TopHat == 4) {
			SetHopperServo(HOPPER_MAX);
		}


	}
}
