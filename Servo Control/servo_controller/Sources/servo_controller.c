#include "servo_controller.h"

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


// consider modularising code (ie. remove hard code)
void servo_init(void) {
  PWMCLK = 0;        // Use clocks A and B
  PWMPRCLK = 0x44;   // prescale of 16 for clocks A & B.
  PWMPOL = 0xA0;     // sets output as high for beginning of period for PP7 and PP5
  PWMCAE = 0;        // left aligned output mode.
  PWMPER45 = 30000;  // period = 20 ms 
  PWMPER67 = 30000;  // period = 20 ms
  PWMDTY45 = 2250;   // 1.5ms pulse length (centered)
  PWMDTY67 = 2250;   // 1.5ms pulse length (centered)
  PWMCTL = 0xC0;     // concatenate to PP45 and PP67 
}


void pan(int start_angle, int end_angle, int angle_step) {
  // convert angles to duty cycles
  double start_dty, end_dty, dty_step;
  int i, p;
  start_dty = start_angle*10 + 2250;
  end_dty = end_angle*10 + 2250;
  dty_step = angle_step*10;
  
  // pan loop
  for(p = start_dty; p < end_dty; p+=dty_step){
    PWMDTY67 += dty_step;
    // Delay function
    i=0; 
    while(i < 10000){
      i++;
    }
  }    
}


void tilt(int start_angle, int end_angle, int angle_step) {
  // convert angles to duty cycles
  double start_dty, end_dty, dty_step;
  int i, p;
  start_dty = start_angle*10 + 2250;
  end_dty = end_angle*10 + 2250;
  dty_step = angle_step*10;
  
  // tilt loop
  for(p = start_dty; p < end_dty; p+=dty_step){
    PWMDTY45 += dty_step;
    // Delay function
    i=0; 
    while(i < 10000){
      i++;
    }
  }      
}


void servo_goto(int pan_angle, int tilt_angle){
  // convert angles to duty cycles
  double pan_dty, tilt_dty;
  pan_dty = pan_angle*10 + 2250;
  tilt_dty = tilt_angle*10 + 2250; 
  
  // update servo duty cycle (position)
  PWMDTY45 = tilt_dty;
  PWMDTY67 = pan_dty; 
}