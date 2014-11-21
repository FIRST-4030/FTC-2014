#ifndef FTC_TELEOP_INCLUDES
#define FTC_TELEOP_INCLUDES

///// Sensor Multiplexer Interface /////
#include "drivers/hitechnic-sensormux.h"
const tMUXSensor sonarSensor = msensor_S2_1;
const tMUXSensor MidIRSeeker = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
//const tMUXSensor ksTouch = msensor_S2_3;
//const tMUXSensor lTouch = msensor_S2_4;
const tSensors gyroSensor = S4;

// Teleop Includes
#include "JoystickDriver.c"
#include "Motors/servos.c"
#include "Motors/motors.c"
#include "Motors/lift.c"
#include "Sensors/gyro.c"
#include "Sensors/ir.c"
#include "Sensors/touch.c"
#include "Sensors/sonar.c"
#include "Drive/drive.c"
#include "Drive/drive_direct.c"
#include "Drive/drive_tank.c"
#include "Drive/drive_mec.c"

#include "init_robot.c";

#endif
