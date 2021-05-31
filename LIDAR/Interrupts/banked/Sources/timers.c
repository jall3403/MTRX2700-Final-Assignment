#include "timers.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */
#include <hidef.h>

static unsigned int timer_overflow;
static unsigned int edge1,edge1H;
static unsigned int edge2,edge2H;

void Init_TC1 (void) {
  // set up the timers for channel 7 to use the interrupt
  TSCR1 = 0x90;               // enables timer and fast flag clearing
  TIOS = 0x00;                // enables input capture for TC1
  TSCR2 = 0x00;               // prescaler to 1:1, no overflow interrupt 
  
  ICSYS = 0b00000011;   
  DLYCT = 0x01;
  ICOVW = 0b00000010;;
  
  DDRH = 0x01;   //PH0 set to output
  PTH = 0x01;   //Pull pin 0 of port H high
  
}

int LIDAR(void)
  {
    timer_overflow = 0;
    edge1 = 0;
    edge2 = 0;
    edge1H = 0;
    edge2H = 0;
    
    TFLG1 = 0x00;
    TIE = 0x02;   // enables interrupts for TC1
    TCTL4 = 0x04; //define rising edge trigger
    PTH = 0x00;   //Pull pin 0 of port H low (generate falling edge)
 
    
    while(edge2 == 0) //Loop until edge2 has been set
      {
      };
      
    TIE = 0x00;   // Disables interrupts for TC1 
    PTH = 0x01;
      
    return(edge2-edge1); 
  }


// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void TC1_ISR(void)
{ 
      
    edge1 = TC1;  // read TC1 register for cycle count for when RISING edge flag was triggered
    //edge1H = TC1H;
    MCCTL = 0b00010000; //Latches TC1 into its holding register
    TFLG1_C1F = 1;
     
    TSCR2 = 0x80; // prescaler to 1:1, enable overflow interrupt 
    TCTL4 = 0x08; //define falling edge trigger
    
    while(!TFLG1_C1F);
    edge2 = TC1;
    edge2H = TC1H;   
}

__interrupt void TOF_ISR(void) 
{
    TFLG2 = 0x80;    // Clear the timer overflow flag
    timer_overflow++;
}
#pragma CODE_SEG DEFAULT