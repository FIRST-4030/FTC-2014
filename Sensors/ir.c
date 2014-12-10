#ifndef FTC_IR
#define FTC_IR

#include "../drivers/hitechnic-irseeker-v2.h"

int readIR() {
	int ir = HTIRS2readACDir(IRSeeker);
	nxtDisplayCenteredBigTextLine(1, "IR: %d", ir);
	return HTIRS2readACDir(ir);
}

int readMidIR() {
	return HTIRS2readACDir(MidIRSeeker);
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
