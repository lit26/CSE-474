#include <stdint.h>
#include "lab2.h"

void init_GPIOF(){
  SYS_RCGC2_R = 0x20;                // Enable porf F GPIO
  GPIOF_DIR_R = 0x0E;                 // Set port F as output
  GPIOF_DEN_R = 0x0E;                 // Enable digital port F
  GPIOF_DATA_R = 0;                   // Clear all port F
}
void init_timer0(){
  SYS_RCGCTIMER_R |= 0x01;              // Enable the timer 0.
  T0_CTL &= ~0x01;               // Disable timer during configuarion
  T0_CFG   = 0x00000000;             // Choose 32-bit mode
  T0_TAMR = 0x2;              // Periodic mode
  T0_TAMR |= 0x00000000;             // Count down mode
  T0_TAILR = 0x00F42400;              // 16,000,000
  T0_ICR  |= 0x00000001;             // Clear timeout flag
  T0_CTL |= 0x00000001;              // Enable timer
}

int main()
{
  init_GPIOF();
  init_timer0();
  GPIOF_DATA_R =  RED; 
  while (1) {
    if ((T0_RIS & 0x00000001) == 1){
      if (GPIOF_DATA_R == RED) {
        GPIOF_DATA_R = GREEN;     
      }else if (GPIOF_DATA_R == GREEN) {
        GPIOF_DATA_R = BLUE;       
      }else if (GPIOF_DATA_R == BLUE) {
        GPIOF_DATA_R = RED;      
      }
      T0_ICR |= (1<<0);
    }
  }
}  
