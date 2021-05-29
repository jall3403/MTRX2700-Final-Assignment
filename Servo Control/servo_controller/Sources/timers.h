#ifndef TIMERS_HEADER
#define TIMERS_HEADER


// function to initialise the timer
void Init_TC7(void);

// delay function in 100ms increments. 1% absolute error
void delay_by_10ms(int x);

#endif