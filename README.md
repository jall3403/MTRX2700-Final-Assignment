# MTRX2700: Major Project

## Members:
Matthew Ford, James Allen, Shigita Aje

## Roles and Responsibilities
Each group member had responisibility on a module while still helping with other modules when needed. Thus, each group member contributed roughly equally to the major project as a whole.
> - Matthew Ford: Worked primarily on servo controller module.
> - James Allen: Worked primarily on LiDAR module.
> - Shigita Aje: Worked primarily on MATLAB lidar processing module.

## Project Overview
This project involved using the HCS12 microcontroller and a short-ranged LiDAR technology to create a proof-of-concept assistive technology. Its purpose was to assist vision-impared people with being able identify possible obstactle ahead of them. This was achieved by using LiDAR attached to a tilt-pan servo unit, with the raw LiDAR data transmitted through serial connection to a data processing module that could present the data as needed to the user. 

## Servo Controller Module

### Summary
This module was designed with the purpose of being able to control the positioning of the LiDAR device in order for it to be able to scan the environment ahead of it. 

### Valid input
This module requires angles for both tilt and pan directions to determine the require motion and final position of the tilt-pan unit.

### Functions
The module contains the following functions:
> - servo initialisation: `servo_init`
> - panning motion: `pan`
> - tilting motion: `tilt`
> - goto specified angle: `servo_goto`
> - delay function: `delay_by_10ms`

### How to Operate
First, to use the servo controller module, the `servo_init` function must be called to initialise the specific registers of the HCS12 microcontroller. Once the function returns, any function pertaining the the motion of the pan-tilt unit servos can be called at any time. To ensure each function has enough time for the servo motors to complete the motion required, the delay function `delay_by_10ms` should be used to create a buffer period where the servo can finish its operation. The larger the motion a function is called to do, the longer buffer period should be. The functions `pan` and `tilt` require an initial and final angle relative to the servo's center position as well as an increment angle that the servo increments by as it motions from the initial to final position. For the function `servo_goto`, the pan and tilt angles are all that are required.  

### Testing
This code was tested by providing dummy code that simulates possible servo postioning maneuvers that might be required during actual operation of the software. This allowed correct for determining appropriate buffer periods and speeds for which the LiDAR module can effectively operate in. 

## LiDAR Module

### Summary
The LiDAR module deals with the measurement and transmission of the LiDAR data. 

### Valid input
This module requires a trigger input that activates the LiDAR for the module to receive the measurement data. The LiDAR data is automatically sent as the termination of the measurement process.

### Functions

### How to Operate

### Testing

## MATLAB LiDAR Processing Module

### Summary
The MATLAB module deals with the processing of the LiDAR measurements into a plot that is useful for the user, allowing them to identify and assess obstacles ahead of them. 

### Valid input
The only input this module requires is the serial receiving of the LiDAR measurements. The correct COM port and baud rate must be selected for successful serial communication. 

### Functions

### How to Operate

### Testing
