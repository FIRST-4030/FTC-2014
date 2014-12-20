#ifndef FTC_SONAR
#define FTC_SONAR

#define SONAR_DELAY (50)
#define SONAR_MIN (10)
#define SONAR_MAX (200)

#include "../Motors/lift.c"
#include "../drivers/lego-ultrasound.h"

tMUXSensor sonarLowDevice;
tMUXSensor sonarHighDevice;
void initSonar(tMUXSensor lowDevice, tMUXSensor highDevice) {
	sonarLowDevice = lowDevice;
	sonarHighDevice = highDevice;
}

// This MUXing should really live up one layer of abstraction with two different instances underlying
// But this is RobotC and globals are the order of the day, so this is what we get instead
int readSonar() {
	tMUXSensor active;
	tMUXSensor inactive;
	if(isLiftAboveRobot()) {
		active = sonarLowDevice;
		inactive = sonarHighDevice;
	} else {
		active = sonarHighDevice;
		inactive = sonarLowDevice;
	}
	USsetOff(inactive);
	USsetSingleMode(active);
	wait1Msec(SONAR_DELAY);
	int sonar = USreadDist(active);
	if (sonar < SONAR_MIN || sonar > SONAR_MAX) {
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
