#include <tm4c123gh6pm.h>
#include <stdint.h>

#define RED 0x02
// This module will turn on the red LED on the board
int main(){
  SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF; // enable Port F GPIO

  GPIO_PORTF_DIR_R = RED; // set Port F as output
  GPIO_PORTF_DEN_R = RED; // enable digital Port F
  GPIO_PORTF_DATA_R = 0; // clear all Port F
  GPIO_PORTF_DATA_R = RED; // turn on the red LED
  while(1){}
  return 0;
}