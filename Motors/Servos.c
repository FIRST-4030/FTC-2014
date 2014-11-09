#ifndef FTC_SERVOS
#define FTC_SERVOS

#define HOOK_MIN (0)
#define HOOK_MAX (255)
#define HOOK_RATE 2
#define HOPPER_MIN (0)
#define HOPPER_MAX (255)
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
	setServo(servoHook, position);
}
void SetHopperServo (int position, int min = HOPPER_MIN, int max = HOPPER_MAX) {
	setServo(servoHopper, position, min, max);
}

void servosInit(TServoIndex hook, TServoIndex hopper) {
	servoHook = hook;
	servoChangeRate[servoHopper] = HOOK_RATE;
	SetHookServo(HOOK_MIN);

	servoHopper = hopper;
	servoChangeRate[servoHopper] = HOPPER_RATE;
	SetHopperServo(HOPPER_MIN);
}

#endif
