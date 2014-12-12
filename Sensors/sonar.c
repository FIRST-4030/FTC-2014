#ifndef FTC_SONAR
#define FTC_SONAR

#include "../drivers/lego-ultrasound.h"

tMUXSensor sonarDevice;
void initSonar(tMUXSensor device) {
	sonarDevice = device;
}

int readSonar() {
	int sonar = USreadDist(sonarDevice);
	#ifdef SONAR_DEBUG
		nxtDisplayCenteredBigTextLine(1, "S: %d", sonar);
	#endif
	if (sonar < 10 || sonar > 250) {
		sonar = 0;
	}
	return sonar;
}

#endif
