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

task main()
{
	bool valid = false;
	initializeRobot();
	waitForStart();

	// Get the lift going
	StartTask(Lift);

	// Pull ahead and read the IR position
	driveToEncoder(AUTO_DRIVE_SPEED, 2500);
	if (readIR() == 5) {
		valid = AutoScoreSide();
	} else {
		// If the beacon isn't straight ahead, turn, backup and take a second reading
		driveToGyro(90, !TURN_LEFT);
		driveToEncoder(-AUTO_DRIVE_SPEED, 1100);

		switch (readIR()) {
	  		case 4:
				valid = AutoScoreAhead();
				break;

			case 3:
				valid = AutoScoreIntermediate();
				break;

			default:
				valid = false;
				break;
		}
	}
	
	// Score if we are aligned
	if (valid) {
		valid = AutoScore();
	}
	// Kick if we scored
	if (valid) {
		AutoKickstand();
	}

	// Wiggle and flash if something went wrong
	if (!valid) {
		servoHookCapture();
		wait1Msec(0.5 * 1000);
		servoHookRelease();
	}
	
	// Always return the lift to COLLECT, even if we failed
	setWaitLiftCmd(COLLECT);
}
