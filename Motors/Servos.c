#ifndef FTC_SERVOS
#define FTC_SERVOS

#define HOOK_MIN (120)
#define HOOK_MAX (240)
#define HOOK_RATE 2
#define HOPPER_MAX (220)
#define HOPPER_MIN (50)
#define HOPPER_RATE 2

TServoIndex servoHook;
TServoIndex servoHopper;

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

void servosInit(TServoIndex hook, TServoIndex hopper) {
	servoHook = hook;
	servoChangeRate[servoHook] = HOOK_RATE;
	SetHookServo(HOOK_MIN);

	servoHopper = hopper;
	servoChangeRate[hopper] = HOPPER_RATE;
	SetHopperServo(HOPPER_MAX);
}

#endif
