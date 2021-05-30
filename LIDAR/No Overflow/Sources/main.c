#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */



void Init_TC1 (void) {
  volatile int x;
  // set up the timers for channel 1 to use the interrupt
  TSCR1 = 0x90;             // enables timer requies flag cleared
  TSCR2 = 0x80;             // prescaler to 1:1
  TIOS =  0x00;               // enables input capture for TC1
  //TCTL4 |= 0x0C;            // sets capture to any edge for PT1
  
  //TIE |= TIE_C1I_MASK;      // enables interrupts for TC1
  
  for(x = 0;x<1000;x++) {
  }
}


void main(void) {
  /* put your own code here */
  unsigned int overflow, edge1, edge2;
  unsigned int diff;
 // double pulse_width;
  Init_TC1();
  
  DDRH = 0x0;
  
  overflow = 0;
  TFLG1= 0x02;
  TCTL4 = 0x08;
                                         
  TFLG1= 0x02;
  while(TFLG1 != 0x02);
  TFLG2 = 0x80;
  edge1 = TC1;
  
  TCTL4 = 0x04;
  while(TFLG1 != 0x02);
  edge2 = TC1;
  
  diff = edge2-edge1;
  //pulse_width = (double)diff/24000000.0; 
  
  EnableInterrupts;



  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
