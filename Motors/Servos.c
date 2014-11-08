#ifndef FTC_SERVOS
#define FTC_SERVOS

#define HOOK_MAX (127)
#define HOOK_MIN (0)
#define HOPPER_MAX (255)
#define HOPPER_MIN (0)

void SetHookServo (int loc) {
	servo[goalHook] = loc;
}
void SetHopperServo (int loc) {
	servo[hopperTilt] = loc;
}

#endif
