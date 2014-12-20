#ifndef FTC_SONAR
#define FTC_SONAR

#include "../Motors/lift.c"
#include "../drivers/lego-ultrasound.h"

tMUXSensor sonarLowDevice;
tMUXSensor sonarHighDevice;
void initSonar(tMUXSensor lowDevice, tMUXSensor highDevice) {
	sonarLowDevice = lowDevice;
	sonarHighDevice = highDevice;
}

int readSonar() {
	tMUXSensor toRead;
	if(isLiftAboveRobot()) {
		toRead = sonarLowDevice;
	} else {
		toRead = sonarHighDevice;
	}
	int sonar = USreadDist(toRead);
	if (sonar < 10 || sonar > 200) {
		sonar = 0;
	}
	#ifdef SONAR_DEBUG
		nxtDisplayCenteredBigTextLine(1, "S: %d", sonar);
	#endif
	return sonar;
}

int readSonarMax(int samples = 5) {
	int max = 0;
	for (int i = 0; i < samples; i++ ) {
		int reading = readSonar();
		if (reading > max) {
			max = reading;
		}
	}
	return max;
}

#endif
