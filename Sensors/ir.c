#ifndef FTC_IR
#define FTC_IR

#include "../drivers/hitechnic-irseeker-v2.h"

int readIR() {
	int ir = HTIRS2readACDir(IRSeeker);
	#ifdef IR_DEBUG
		nxtDisplayCenteredBigTextLine(1, "IR: %d", ir);
	#endif
	return ir;
}

int readIR(tSensors irSeeker) {
	return HTIRS2readACDir(irSeeker);
}

int readIR(tMUXSensor irSeeker) {
	return HTIRS2readACDir(irSeeker);
}

bool irValid(int seeker) {
	if (seeker < 1) {
		return false;
	} else if (seeker > 8) {
		return false;
	}
	return true;
}

#endif
