#ifndef FTC_TELEOP_INCLUDES
#define FTC_TELEOP_INCLUDES

///// Sensor Multiplexer Interface /////
#include "drivers/hitechnic-sensormux.h"
const tMUXSensor sonarLowSensor = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
const tMUXSensor sonarHighSensor = msensor_S2_3;
const tMUXSensor lightLeft = msensor_S2_4;

//Includes for General Hardware-Related files
#include "JoystickDriver.c"
#include "Sensors/gyro.c"
#include "Sensors/ir.c"
#include "Sensors/touch.c"
#include "Sensors/sonar.c"
#include "Sensors/light.c"
//#include "../Drive/lines.c"
#include "Motors/servos.c"
#include "Motors/motors.c"
#include "Drive/drive.c"
//#include "Drive/drive_direct.c"
//#include "Drive/drive_tank.c"
#include "Drive/drive_mec.c"
#include "Motors/lift.c"
#include "Motors/hopper.c"

//Include for the auto functions
#include "Autonomous/auto_functions.c"

//Include for robot initialization
#include "init_robot.c";

#endif
