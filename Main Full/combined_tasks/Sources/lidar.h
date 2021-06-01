#ifndef TIMER
#define TIMER

int LIDAR_INTERRUPT(void);
int LIDAR(void);

#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt 9 void TC1_ISR(void);
interrupt 16 void TOF_ISR(void);
#pragma CODE_SEG DEFAULT

#endif