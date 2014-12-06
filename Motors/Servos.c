#ifndef FTC_SERVOS
#define FTC_SERVOS

#define HOOK_MIN (75)
#define HOOK_MAX (160)
#define HOOK_RATE (0)
#define HOPPER_MAX (220)
#define HOPPER_MIN (50)
#define HOPPER_RATE (0)
#define HIGH_MIN (110)
#define HIGH_MAX (200)
#define HIGH_RATE (2)

TServoIndex servoHook;
TServoIndex servoHopper;
TServoIndex servoHigh;
tMUXSensor servoLight;

void setServo(TServoIndex s, int position, int min = 0, int max = 255) {
	if (position > max) {
		position = max;
	}
	if (position < min) {
		position = min;
	}
	servo[s] = position;
}

int getServo(TServoIndex s) {
	return ServoValue[s];
}

void SetHookServo (int position, int min = HOOK_MIN, int max = HOOK_MAX) {
	setServo(servoHook, position, min, max);
}
void SetHopperServo (int position, int min = HOPPER_MIN, int max = HOPPER_MAX) {
	setServo(servoHopper, position, min, max);
}

int getHopperServo() {
	return ServoValue[servoHopper];
}

void servoHookCapture() {
	SetHookServo(HOOK_MIN);
	LSsetActive(servoLight);
}

void servoHookRelease() {
	SetHookServo(HOOK_MAX);
	LSsetInactive(servoLight);
}

void servoSetHigh(int position) {
	setServo(servoHigh, position, HIGH_MIN, HIGH_MAX);
}

void servoHighHold() {
	servoSetHigh(HIGH_MAX);
}

void servoHighDrop() {
	servoSetHigh(HIGH_MIN);
}

void servosInit(TServoIndex hook, TServoIndex hopper, tMUXSensor light, TServoIndex high) {
	servoHook = hook;
	servoChangeRate[servoHook] = HOOK_RATE;
	servoLight = light;
	servoHookRelease();

	servoHopper = hopper;
	servoChangeRate[servoHopper] = HOPPER_RATE;
	SetHopperServo(HOPPER_MAX);

	servoHigh = high;
	servoChangeRate[servoHigh];
	servoHighHold();
}

#endif
