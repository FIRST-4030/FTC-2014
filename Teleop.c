#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     motors,         sensorNone)
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
#include "teleop_includes.h"

void stopAndDump(LiftState cmd) {
	setLiftCmd(cmd);
	hopperAutoDump();
}

task main()
{
	programPeriod = TELEOP;
  initializeRobot();
  waitForStart();

  StartTask(DriveMec);
  StartTask(Lift);
  StartTask(Hopper);

  servoHighDrop();
  wait1Msec(500);
  servoHighHold();
  DriveSpinnerMotor(SPINNER_IN);

	while(true)
	{
		getJoystickSettings(joystick);

		//Goal Hook Servo
		if(joy1Btn(5) || joy1Btn(7)) {
			servoHookCapture();
		} else if (joy1Btn(6) || joy1Btn(8)) {
			servoHookRelease();
		}

		if (joy2Btn(4)) {
			stopAndDump(HIGH);
		} else if(joy2Btn(7)) {
			setLiftCmd(COLLECT);
		} else if(joy2Btn(8)) {
			setLiftCmd(DRIVE);
		} else if(joy2Btn(2)) {
			stopAndDump(LOW);
		} else if(joy2Btn(1) || joy2Btn(3)) {
			stopAndDump(MED);
		}
	}
}
