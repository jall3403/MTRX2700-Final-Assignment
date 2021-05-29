#include "timers.h"
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */ 



void Init_TC7 (void) {
  // set up the timers for channel 5 to use the interrupt
  TSCR1 = 0x80;             // enables timer requies flag cleared
  TSCR2 = 0x00;             // prescaler to 1:1
  TIOS |= TIOS_IOS7_MASK;   // enables output compare for TC7
  
  TCTL1=0x40;               // sets output to toggle
  TIE |= TIE_C7I_MASK;      // enables interrupts for TC57
}

void delay_by_10ms(int x){
  volatile int i;
  volatile int tick_num = x * 4;     // approx. 4 overflows every 10ms
  
  for(i=0;i<tick_num;i++){
    TFLG2 = 0x80;                     // resets counter
    while(!(TFLG2 & TFLG2_TOF_MASK)); // waits until overflow occurs
  }
}

