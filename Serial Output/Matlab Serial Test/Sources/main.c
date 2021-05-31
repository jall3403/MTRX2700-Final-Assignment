#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <stdlib.h>

#include "derivative.h"      /* derivative-specific definitions */

#include "serial.h"

void main(void) {
  /* put your own code here */
  
  Serial_Port serial_port1;
  char string[10];
  int i,x,y;
  
  set_serial(&serial_port1, 1, 9600, 0b01001100, 0b00101100);
	EnableInterrupts;
  x = 100;
  y = 100;
  
  sprintf(string,"%u\n",x);
  output_string(1,string);
  
  sprintf(string,"%u\n",y);
  output_string(1,string);  
  for(i=0;i<x*y;i++)
    {
  	  sprintf(string,"%u\n",i);
  	  output_string(1,string); 
    }

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
