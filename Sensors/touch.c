#ifndef FTC_IR
#define FTC_IR

#include "../drivers/lego-touch.h"

// For Kickstand Touch Sensor //
//Used if the program wants the sensor in its binary values
//0 being not pressed and 1 being pressed
int readKSTouch() {
	return SensorValue[ksTouch];
}

//Used if the program wants the raw boolean
bool isKSTouchPressed() {
	return TSReadState(ksTouch);
}

// For Lift Touch Sensor //
int readLTouch() {
	return SensorValue[lTouch];
}

bool isLTouchPressed() {
	return TSReadState(lTouch);
}

#endif
