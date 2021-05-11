#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */



void main(void) {
  /* put your own code here */
  double period, pulse_length, duty_cycle;
  int i = 0;
  int j = 0;
  period = 0.02;     // period in seconds
  
  pulse_length = 0.001; // in seconds
  duty_cycle = pulse_length/period * 100;   // desired duty cycle
  
  PWMCLK = 0;        // Use clocks A and B
  PWMPRCLK = 0x44;   // prescale of 16 for clocks A & B.
  PWMPOL = 0xA0;     // sets output as high for beginning of period for PP7 and PP5
  PWMCAE = 0;        // left aligned output mode.
  PWMPER45 = 30000;  // period = 20 ms 
  PWMPER67 = 30000;  // period = 20 ms
  PWMDTY45 = 1350;   // 15ms pulse length
  PWMDTY67 = 1350;   // 15ms pulse length
  PWMCTL = 0xC0;     // concatenate to PP45 and PP67
  
  while(i < 10000){
    i++;
  }
  
  //PWME |= PWME_PWME5;
  
  //PWME_PWME5 = PWME_PWME5_MASK; // enable PP5
  PWME = 0xA0;
  // apply duty cycle
  // PWMDTY5 = PWMPER5 * (1 - (int)duty_cycle/100);
  
  for(j = 0;j<1800;j++) 
  {
    PWMDTY45 = 1350+j;
    PWMDTY67 = 1350+j;
   i=0; 
   while(i < 10000){
    i++;
    }
      
  }
	PWMDTY45 = 2250;
	PWMDTY67 = 2250;
	

  EnableInterrupts;
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
