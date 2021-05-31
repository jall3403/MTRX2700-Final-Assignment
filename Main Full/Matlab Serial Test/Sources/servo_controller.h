#ifndef SERVO_CONTROLLER_HEADER
#define SERVO_CONTROLLER_HEADER


// servo init (PP5 and PP7)
void servo_init(void);

// pan servo controller (PP67)
void pan(int start_angle, int end_angle, int angle_step);

// tilt servo controller (PP45)
void tilt(int start_angle, int end_angle, int angle_step);

// goes to specified servo position
void servo_goto(int pan_angle, int tilt_angle);

void servo_begin(void);

void delay_in_ms(int x);


#endif
