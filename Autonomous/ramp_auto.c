#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     motors,         sensorI2CMuxController)
#pragma config(Sensor, S2,     SMUX,           sensorI2CCustom9V)
#pragma config(Sensor, S3,     gyroSensor,     sensorI2CHiTechnicGyro)
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
#pragma config(Servo,  srvo_S1_C4_1,    goalHook,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    hopperTilt,           tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    highGoal,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    unusedS3C14,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    unusedS3C15,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    unusedS3C16,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma debuggerWindows("joystickGame");
#include "auto_includes.h"


//Comments that are written like this are by Ariel//
task main()
{
  initializeRobot();
  waitForStart();

  StartTask(Lift);
  StartTask(Hopper);

	//For all of these, they were written with brackets [] instead of parenthesis ()//
  //I changed this, as all method calls must be with parenthesis, not brackets//
  driveToEncoder(AUTO_DRIVE_SPEED, 5000);
	driveToGyro(180, TURN_LEFT);

	driveToEncoder(-AUTO_DRIVE_SPEED, 5000);
	servoHookCapture();

	driveToGyro(120, TURN_LEFT);
	driveToEncoder(AUTO_DRIVE_SPEED, 10000);

	setLiftCmd(MED);
	hopperAutoDump();
}
//Code for on ramp autonomous; moves off ramp, hooks med roll. goal, moves it to parking zone, scores 2 balls in possesion.
//Total 70 points
