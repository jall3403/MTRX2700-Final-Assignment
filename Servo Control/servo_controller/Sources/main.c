#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "servo_controller.h"
#include "timers.h"


void main(void) {
  /* put your own code here */
  volatile int delay = 100;
  servo_init();
  delay_by_10ms(delay);
  
  pan(0, 90, 1);
  delay_by_10ms(delay);
  
  pan(90, 0, 1);
  delay_by_10ms(delay);
  
  tilt(-90, 90, 1);
  delay_by_10ms(delay);
  
  tilt(90, 0, 1);
  delay_by_10ms(delay);
  
  servo_goto(45, 45);
  delay_by_10ms(delay);

	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
