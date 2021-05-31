#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <stdlib.h>

#include "derivative.h"      /* derivative-specific definitions */

#include "servo_controller.h"
#include "serial.h"

void main(void) {
  /* put your own code here */
  Serial_Port serial_port1;
  char string[10];  
  
  // start and end tilt angles
  int tilt_start = 30, tilt_end = -30;
  
  // start and ent pan angles
  int pan_start = 60, pan_end = -60;
  
  // increment angle
  int step_angle = 10;
  
  // current pan and tilt angles
  int pan_current = pan_start, tilt_current = tilt_start;
  
  // distance measured by lidar
  int distance = 0;
  
  int x,y;
  
  set_serial(&serial_port1, 1, 9600, 0b01001100, 0b00101100);
  EnableInterrupts;
  
  x = 7;
  y = 13;
  
  /*sprintf(string,"%u\n",x);
  output_string(1,string);
  
  sprintf(string,"%u\n",y);
  output_string(1,string);
  */
  servo_init();
  
  servo_goto(pan_current, tilt_current);
  
  delay_in_ms(1);
  
  servo_goto(pan_end, tilt_end);
   
  
 /*// goes to starting position
  servo_goto(pan_current, tilt_current);
  delay_in_ms(100);
  
  // main loop
  while(pan_current >= pan_end)
  {
    
    // tilts down until reached bottom
    while(tilt_current >= tilt_end)
    {
      
      // get lidar measurement here while tilting down
      // **** distance = "lidar function"  ****
      
      distance = tilt_current;
      
      //sprintf(string,"%u\n",x);
      //output_string(1,string);
      
      // doesn't continue tilting if no measurement receieved 
      if(distance == 0)
      { 
        continue;
      }
      // next tilt angle
      tilt_current -= step_angle;
      
      // goes to new tilt position
      servo_goto(pan_current, tilt_current);
      delay_in_ms(100);
    }
  
    // repositions lidar for tilting upward
    pan_current -= step_angle;
    tilt_current += step_angle;
    servo_goto(pan_current, tilt_current);
    delay_in_ms(100);
    
    // tilts up until reached top
    while(tilt_current <= tilt_start)
    {
  
      // get lidar measurement here while tilting up
      // **** distance = "lidar function" ****
      
      distance = tilt_current;
      
      //sprintf(string,"%u\n",x);
      //output_string(1,string);
      
      // doesn't continue tilting if no measurement receieved 
      if(distance == 0)
      { 
        continue;
      }
      // next tilt angle
      tilt_current += step_angle;
      
      // goes to new tilt position
      servo_goto(pan_current, tilt_current);
      delay_in_ms(100);
    }
  }
  */ 

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
