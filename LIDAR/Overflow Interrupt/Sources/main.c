#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

static unsigned int timer_overflow; //Declare overflow variable
unsigned int edge1, edge2;

void Init_TC1 (void) {
  // set up the timers for channel 1 to use the interrupt
  TSCR1 = 0x90;               // enables timer and fast flag clearing
  TIOS = 0x00;                // enables input capture for TC1
  TSCR2 = 0x00;               // prescaler to 1:1, no overflow interrupt 
  TIE = 0x02;                 // enables interrupts for TC1
  
  ICSYS = 0x00;
  DLYCT = 0x01;
  ICOVW = 0x02;
}

interrupt 16 void TOF_ISR(void)
{
 
    TFLG2 = 0x80;    // Clear the timer overflow flag
    timer_overflow++;
}

interrupt 9 void PT1_ISR(void)
{
  if(TCTL4 == 0x08)
        {
          edge1 = TC1;  // read TC1 register for cycle count for when FALLING edge flag was triggered
          TFLG2 = 0x80; //Clear TOF flag
          TSCR2 = 0x80; // prescaler to 1:1, enable overflow interrupt
          TCTL4 = 0x04; //define rising edge trigger
  
          while(TFLG1 == 0)
            {
            };
          edge2 = TC1; // read TC1 register for cycle count for when RISING edge flag was triggered
          PTH = 0x01;  
        }
}

void main(void) {
  /* put your own code here */
  unsigned int diff;
  
  Init_TC1();
  
  timer_overflow = 0; //define overflow starting point
  edge1 = 0;
  edge2 = 0;

  EnableInterrupts;
  
  DDRT = 0x00;
  DDRH = 0x01;
  
  TCTL4 = 0x00;
  PTH = 0x01;   //Pull pin 0 of port H high
  PTH = 0x00;   //Pull pin 0 of port H low (generate falling edge)
  TCTL4 = 0x08; //define falling edge trigger
  //TFLG1 = 0x02;
  //while(TFLG1 != 0x02); //waitng for C1F to trigger interrupt condition flag (falling 
  //edge1 = TC1;
  
  //DLYCT = 0x00; 
  //TFLG2 = 0x80; //Clear TOF flag
  //TSCR2 = 0x80;
  
  //edge1 = TC1;  // read TC1 register for cycle count for when FALLING edge flag was triggered
  //edge1 = TC1H;
  
  //TCTL4 = 0x04; //define rising edge trigger
  //while(TFLG1 != 0x02)  ;//waitng for C1F to trigger interrupt condition flag (rising edge)
  //edge2 = TC1; // read TC1 register for cycle count for when RISING edge flag was triggered
  while(edge2 == 0)
    {
    };
  diff = edge2-edge1;

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
