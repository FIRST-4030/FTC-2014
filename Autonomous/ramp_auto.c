#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     motors,         sensorI2CMuxController)
#pragma config(Sensor, S2,     SMUX,           sensorI2CCustom9V)
#pragma config(Sensor, S3,     servos,         sensorI2CMuxController)
#pragma config(Sensor, S4,     liftTS,         sensorTouch)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, reversed, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     leftFrontMotor, tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftRearMotor, tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     rightFrontMotor, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     rightRearMotor, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     liftMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     spinnerMotor,  tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S3_C1_1,    goalHook,             tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    hopperTilt,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_3,    unusedS3C13,          tServoStandard)
#pragma config(Servo,  srvo_S3_C1_4,    unusedS3C14,          tServoStandard)
#pragma config(Servo,  srvo_S3_C1_5,    unusedS3C15,          tServoStandard)
#pragma config(Servo,  srvo_S3_C1_6,    unusedS3C16,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma debuggerWindows("joystickGame");
#include "auto_includes.h"

task main()
{
  initializeRobot();
  waitForStart();

	driveToEncoder[AUTO_DRIVE_SPEED,5000];
	driveToGyro[180, TURN_LEFT];
	driveToEncoder[-AUTO_DRIVE_SPEED,5000];
	servoHookCapture();
	driveToGyro[120, TURN_LEFT];
	driveToEncoder[AUTO_DRIVE_SPEED,10000];
	stopAndDump(MED);
}
