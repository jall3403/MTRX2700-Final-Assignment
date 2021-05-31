#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <stdlib.h>

#include "derivative.h"      /* derivative-specific definitions */

#include "serial.h"

void main(void) {
  /* put your own code here */
  
  Serial_Port serial_port1;
  char string[10];
  int length[3];
  int i;
  
  set_serial(&serial_port1, 1, 9600, 0b01001100, 0b00101100); 

	EnableInterrupts;
	
	length[0]=200;
	length[1]=4;
	length[2]=4000;
	
  for(i=0;i<3;i++)
    {
  	  sprintf(string,"%u\n",length[i]);
  	  output_string(1,string); 
    }

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
