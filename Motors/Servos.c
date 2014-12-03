#ifndef FTC_SERVOS
#define FTC_SERVOS

#define HOOK_MIN (75)
#define HOOK_MAX (160)
#define HOOK_RATE 0
#define HOPPER_MAX (220)
#define HOPPER_MIN (50)
#define HOPPER_RATE 0

TServoIndex servoHook;
TServoIndex servoHopper;
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

void SetHookServo (int position, int min = HOOK_MIN, int max = HOOK_MAX) {
	setServo(servoHook, position, min, max);
}
void SetHopperServo (int position, int min = HOPPER_MIN, int max = HOPPER_MAX) {
	setServo(servoHopper, position, min, max);
}

void servoHookCapture() {
	SetHookServo(HOOK_MIN);
	LSsetActive(servoLight);
}

void servoHookRelease() {
	SetHookServo(HOOK_MAX);
	LSsetInactive(servoLight);
}

void servosInit(TServoIndex hook, TServoIndex hopper, tMUXSensor light) {
	servoHook = hook;
	servoChangeRate[servoHook] = HOOK_RATE;
	servoLight = light;
	servoHookRelease();

	servoHopper = hopper;
	servoChangeRate[hopper] = HOPPER_RATE;
	SetHopperServo(HOPPER_MAX);
}

#endif
