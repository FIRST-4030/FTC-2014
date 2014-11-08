#ifndef FTC_AUTO_INCLUDES
#define FTC_AUTO_INCLUDES

///// Sensor Multiplexer Interface /////
#include "../drivers/hitechnic-sensormux.h"
const tMUXSensor sonarSensor = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
const tMUXSensor lightRight = msensor_S2_3;
const tMUXSensor lightLeft = msensor_S2_4;

// Other Includes //
#include "../Sensors/ir.c"
#include "../Sensors/touch.c"
//#include "../Sensors/gyro.c"
#include "../Motors/motors.c"
#include "../Motors/servos.c"
#include "../Drive/drive.c"
//#include "../Drive/drive_auto.c" Needs to be written
#include "JoystickDriver.c"

//#include "auto_init.c" Needs to be written
//#include "auto_functions.c" Needs to be written

#endif
