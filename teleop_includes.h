#ifndef FTC_TELEOP_INCLUDES
#define FTC_TELEOP_INCLUDES

///// Sensor Multiplexer Interface /////
#include "drivers/hitechnic-sensormux.h"
const tMUXSensor MidIRSeeker = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
const tMUXSensor sonarSensor = msensor_S2_3;
const tMUXSensor lightLeft = msensor_S2_4;

// Teleop Includes
#include "JoystickDriver.c"
#include "Sensors/gyro.c"
#include "Sensors/ir.c"
#include "Sensors/touch.c"
#include "Sensors/sonar.c"
#include "Sensors/light.c"
#include "Motors/servos.c"
#include "Motors/motors.c"
#include "Motors/hopper.c"
#include "Motors/lift.c"
#include "Drive/drive.c"
#include "Drive/drive_direct.c"
#include "Drive/drive_tank.c"
#include "Drive/drive_mec.c"

#include "init_robot.c";

#endif
