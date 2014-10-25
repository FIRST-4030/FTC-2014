#ifndef FTC_IR
#define FTC_IR

#include "../drivers/lego-touch.h"

//Used if the program wants the sensor in its binary values
//0 being not pressed and 1 being pressed
int readTouch() {
	return SensorValue[touch];
}

//Used if the program wants the raw boolean
bool isTouchPressed() {
	return TSReadState(touch);
}

#endif
