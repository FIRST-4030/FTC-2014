#ifndef FTC_AUTO_INCLUDES
#define FTC_AUTO_INCLUDES

///// Sensor Multiplexer Interface /////
#include "../drivers/hitechnic-sensormux.h"
const tMUXSensor sonarSensor = msensor_S2_1;
const tMUXSensor MidIRSeeker = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
//const tMUXSensor gyroSensor = msensor_S2_3;
const tMUXSensor lightRight = msensor_S2_3;
const tMUXSensor lightLeft = msensor_S2_4;

// Other Includes //
#include "JoystickDriver.c"
#include "../Sensors/light.c"
#include "../Sensors/ir.c"
#include "../Sensors/touch.c"
#include "../Sensors/sonar.c"
#include "../Sensors/gyro.c"
#include "../Motors/motors.c"
#include "../Motors/servos.c"
#include "../Motors/lift.c"
//#include "../Drive/lines.c"
#include "../Drive/drive.c"

#include "auto_functions.c"
#include "../init_robot.c";

#endif
