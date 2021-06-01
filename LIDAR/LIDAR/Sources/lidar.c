#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "derivative.h"
#include "lidar.h"


static unsigned int TOF; //global variable so that the interrupt and run_timer can both access it
volatile unsigned int edge1,edge1H;
volatile unsigned int edge2,edge2H;


//Interrupt based Lidar measurement function
int LIDAR_INTERRUPT(void)
  {
    int length;
    TOF = 0; //define overflow starting point
    
    edge1 = 0;  //rising edge TCNT count
    edge2 = 0;  //falling edge TCNT count
    edge1H = 0; //should be 0
    edge2H = 0; //should be the same as edge1
    
    TSCR1 = 0x90;               // enables timer and fast flag clearing
      
    DDRH = 0x01;   //PH0 set to output
    PTH = 0x01;   //Pull pin 0 of port H high
    
    ICSYS = 0b00000011;   
    DLYCT = 0x01;
    ICOVW = 0b00000010;
    
    TCTL4 = 0x04; //define rising edge trigger
    TIE = 0x02;   // enables interrupts for TC1
    PTH = 0x00;   //Pull pin 0 of port H low (generate falling edge)
    
    while(edge2 == 0) //Loop until edge2 has been set which can only be done by TC1 interrupt
      {
        asm("nop");// idle in loop while edge 1 and edge 2 are being set via interrupt, wont leave loop until edge2 is set
      };
      
    TIE = 0x00;   // Disables interrupts for TC1 
    PTH = 0x01;   //sets PH0 high stopping measurements
    
    
    if(TOF>0 || edge2<edge2H)
      {
        length = ((TOF*65536)+(edge2+edge2H-65536))/240; //converts to distance in cm
      }
      else
        {
          length = (edge2-edge2H)/240; //converts to distance in cm
        }
      
    return(length);
  }
  
//Simiar to LIDAR_INTERRUPT but TC1 interrupt is disabled and CPU polls TFLG1 register for when TC1 has been read  
int LIDAR(void)
  {
    int length;
    TOF = 0; //define overflow starting point
    
    edge1 = 0;  //rising edge TCNT count
    edge2 = 0;  //falling edge TCNT count
    edge1H = 0; //should be 0
    edge2H = 0; //should be the same as edge1
    
    TSCR1 = 0x90;               // enables timer and fast flag clearing
      
    DDRH = 0x01;   //PH0 set to output
    PTH = 0x01;   //Pull pin 0 of port H high
    
    TCTL4 = 0x04; //define rising edge trigger
    PTH = 0x00;   //Pull pin 0 of port H low (generate falling edge)
    
    TFLG1= 0x02;//clears first capture and waits for next one
    while(!TFLG1_C1F); //stays in while loop until C1F == 1
    
    TFLG2 = 0x80; //clears overflow flag
    TSCR2 = 0x80; // prescaler to 1:1, enable overflow interrupt
    
    edge1 = TC1;  //saves first edge and hold register SHOULD CLEAR TFLG1 BUT DOESNT???????
    edge1H = TC1H;
    
    TCTL4 = 0x08; //capture on falling edge
    while(!TFLG1_C1F); 
    edge2 = TC1;  //saves falling edge and hold register SHOULD CLEAR TFLG1 BUT ALSO DOESNT???????
    edge2H = TC1H;
  
  
    if(TOF>0 || edge2<edge2H)
     {
       length = ((TOF*65536)+(edge2+edge2H-65536))/240; //converts to distance in cm
     }
    else
     {
       length = (edge2-edge2H)/240; //converts to distance in cm
     }
      
    return(length);
  }

#pragma CODE_SEG __NEAR_SEG NON_BANKED  
interrupt 9 void TC1_ISR(void)
{
  if(TCTL4 == 0x04)
    {
      edge1 = TC1;  // read TC1 register for cycle count for when RISING edge flag was triggered
      edge1H = TC1H;// hopefully clears C1F flag
      MCCTL = 0b00010000; //forces TC1 into its holding register
      TFLG1_C1F = 1;
       
      TSCR2 = 0x80; // prescaler to 1:1, enable overflow interrupt 
      TCTL4 = 0x08; //define falling edge trigger
    }
    
    else if(TCTL4 == 0x08)
    {
      edge2 = TC1;
      edge2H = TC1H;
    }
}

interrupt 16 void TOF_ISR(void)
{
 
    TFLG2 = 0x80;    // Clear the timer overflow flag
    TOF++;
}
#pragma CODE_SEG DEFAULT
