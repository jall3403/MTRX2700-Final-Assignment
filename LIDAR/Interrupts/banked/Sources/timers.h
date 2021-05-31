#ifndef TIMERS_HEADER
#define TIMERS_HEADER


// function to initialise the timer
void Init_TC1(void);

int LIDAR(void);

#pragma CODE_SEG __NEAR_SEG NON_BANKED
// Timer interrupt definition
__interrupt void TC1_ISR(void);
__interrupt void TOF_ISR(void);
#pragma CODE_SEG DEFAULT

#endif
