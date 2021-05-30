#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

static unsigned int timer_overflow; //Declare overflow variable

void Init_TC1 (void) {
  // set up the timers for channel 1 to use the interrupt
volatile int x;
  TSCR1 = 0x90;               // enables timer and fast flag clearing
  TSCR2 = 0x80;               // prescaler to 1:1, enable overflow interrupt
  TIOS = 0x00;                // enables input capture for TC1 
  //TIE |= TIE_C1I_MASK;        // enables interrupts for TC1
  
  // Delay to allow prescaler to come into effect
  for(x = 0;x<1000;x++) {
  }
}

interrupt 16 void TOF_ISR(void)
{
 
    TFLG2 = 0x80;    // Clear the timer overflow flag
    timer_overflow++;
}

void main(void) {
  /* put your own code here */
  unsigned int edge1, edge2;
  unsigned int diff;
 // double pulse_width;
  Init_TC1();
  timer_overflow = 0; //define overflow starting point
  
  DDRH = 0x0;
  
  TCTL4 = 0x08; //define falling edge trigger
  TFLG1=TFLG1 | TFLG1_C1F_MASK; //Clear C1F flag
  while(TFLG1 != 0x02); //waitng for C1F to trigger interrupt condition flag (falling edge) 
  TFLG2 = 0x80; //Clear TOF flag
  edge1 = TC1;  // read TC1 register for cycle count for when FALLING edge flag was triggered
  
  TCTL4 = 0x04; //define rising edge trigger
  //TFLG1=TFLG1 | TFLG1_C1F_MASK;
  while(TFLG1 != 0x02)  ;//waitng for C1F to trigger interrupt condition flag (rising edge)
  edge2 = TC1; // read TC1 register for cycle count for when RISING edge flag was triggered
  diff = edge2-edge1;

  EnableInterrupts;

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
