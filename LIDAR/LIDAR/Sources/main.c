#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "lidar.h"


void main(void) {
  /* put your own code here */
  unsigned int diff;
  
  EnableInterrupts;
  
  diff = LIDAR();
 
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
