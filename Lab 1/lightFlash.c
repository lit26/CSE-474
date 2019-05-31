//#include <tm4c123gh6pm.h>
#include <stdint.h>
#include "lab1.h"

//This module will create 8 LED light flashing
int main(){
  SYS_RCGC2_R = 0x20; // enable Port F GPIO
  GPIOF_DIR_R = 0xE; //0b1110
  GPIOF_DEN_R = 0xE; //0b1110
  int delay = 5000000;
  while(1){
    int i;
    // Switch LED color
    GPIOF_DATA_R = 0;
    for (i=0;i<delay;i++){}
    GPIOF_DATA_R = RED;
    for (i=0;i<delay;i++){}
    GPIOF_DATA_R = GREEN;
    for (i=0;i<delay;i++){}
    GPIOF_DATA_R = BLUE;
    for (i=0;i<delay;i++){}
    GPIOF_DATA_R = RED_BLUE;
    for (i=0;i<delay;i++){}
    GPIOF_DATA_R = RED_GREEN;
    for (i=0;i<delay;i++){}
    GPIOF_DATA_R = BLUE_GREEN;
    for (i=0;i<delay;i++){}
    GPIOF_DATA_R = WHITE;
    for (i=0;i<delay;i++){}    
  }
  return 0;
}