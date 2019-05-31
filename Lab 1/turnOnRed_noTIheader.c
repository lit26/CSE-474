//#include <tm4c123gh6pm.h>
#include <stdint.h>
#include "lab1.h"

// This module will turn on the red LED on the board exclude the tm4c123gh6pm header file.
int main(){
  SYS_RCGC2_R = 0x20; // enable Port F GPIO

  GPIOF_DIR_R = RED; // set Port F as output
  GPIOF_DEN_R = RED; // enable digital Port F
  GPIOF_DATA_R = 0; // clear all Port F
  GPIOF_DATA_R = RED; // turn on the red LED
  while(1){}
  return 0;
}