//#include <tm4c123gh6pm.h>
#include <stdint.h>
#include "lab1.h"

//This module will light LED according to the switch input
int main() {
  SYS_RCGC2_R = 0x20;
  GPIOF_LOCK_R = 0x4C4F434B; //p684
  GPIOF_CR_R = 0xFF; //enable write to PUR
  GPIOF_PUR_R = 0x11; //enable PF0, PF4
  GPIOF_DIR_R = 0x0E; // 0b01110
  GPIOF_DEN_R = 0x1F; //enable PF0 to PF4
  GPIOF_DATA_R = 0;

  while (1) {
    int switchs = GPIOF_DATA_R & 0x11; 
    if (switchs == 0x01) {           
      GPIOF_DATA_R = RED;
    }else if (switchs == 0x10) {      
      GPIOF_DATA_R = GREEN;
    }else {
      GPIOF_DATA_R = 0;              
    }
  }
}

