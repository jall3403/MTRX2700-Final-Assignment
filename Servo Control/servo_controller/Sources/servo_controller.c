#include "servo_controller.h"
#include "timers.h"
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
  PWME = 0xA0;       // enables PP45 and PP67
  TSCR1 = 0x90;
  TSCR2 = 0x80;
}


void pan(int start_angle, int end_angle, int angle_step) {
  // convert angles to duty cycles
  int start_dty, end_dty, dty_step;
  int p;
  start_dty = start_angle*10 + 2250;
  end_dty = end_angle*10 + 2250;
  dty_step = angle_step*10;
  
  // pan loop
  for(p = start_dty; p < end_dty; p+=dty_step){
    PWMDTY67 += dty_step;
    // Delay function
    delay_by_10ms(10);
  }    
}


void tilt(int start_angle, int end_angle, int angle_step) {
  // convert angles to duty cycles
  int start_dty, end_dty, dty_step;
  int p;
  start_dty = start_angle*10 + 2250;
  end_dty = end_angle*10 + 2250;
  dty_step = angle_step*10;
  
  // tilt loop
  for(p = start_dty; p < end_dty; p+=dty_step){
    PWMDTY45 += dty_step;
    // Delay function
    delay_by_10ms(10);
  }      
}


void servo_goto(int pan_angle, int tilt_angle){
  // convert angles to duty cycles
  int pan_dty, tilt_dty;
  pan_dty = pan_angle*10 + 2250;
  tilt_dty = tilt_angle*10 + 2250; 
  
  // update servo duty cycle (position)
  PWMDTY45 = tilt_dty;
  PWMDTY67 = pan_dty; 
}


void servo_begin(void){
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
  
  // goes to starting position
  servo_goto(pan_current, tilt_current);
  delay_by_10ms(100);
  
  // main loop
  while(pan_current >= pan_end){
    
    // tilts down until reached bottom
    while(tilt_current >= tilt_end){
      
      // get lidar measurement here while tilting down
      // **** distance = "lidar function"  ****
      
      // doesn't continue tilting if no measurement receieved 
      if(distance == 0){ 
        continue;
      }
      // next tilt angle
      tilt_current -= step_angle;
      
      // goes to new tilt position
      servo_goto(pan_current, tilt_current);
      delay_by_10ms(10);
    }
  
    // repositions lidar for tilting upward
    pan_current -= step_angle;
    tilt_current += step_angle;
    servo_goto(pan_current, tilt_current);
    delay_by_10ms(10);
    
    // tilts up until reached top
    while(tilt_current <= tilt_start){
  
      // get lidar measurement here while tilting up
      // **** distance = "lidar function" ****
      
      // doesn't continue tilting if no measurement receieved 
      if(distance == 0){ 
        continue;
      }
      // next tilt angle
      tilt_current += step_angle;
      
      // goes to new tilt position
      servo_goto(pan_current, tilt_current);
      delay_by_10ms(10);
    }
    
    // repositions lidar for tilting downwards
    pan_current -= step_angle;
    tilt_current -= step_angle;
    servo_goto(pan_current, tilt_current);
    delay_by_10ms(10);
    
  }
  
}