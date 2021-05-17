#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "servo_controller.h"


void main(void) {
  /* put your own code here */
  
  servo_init();
  pan(0, 90, 1);
  pan(90, 0, 1);
  tilt(-90, 90, 1);
  tilt(90, 0, 1);
  servo_goto(45, 45);

	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
