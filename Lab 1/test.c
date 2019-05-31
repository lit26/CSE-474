#include <stdint.h>
#include "lab2.h"
#include <tm4c123gh6pm.h>

void PortF_init(void){
  SYS_RCGC2_R = 0x20;
  GPIOF_LOCK_R = 0x4C4F434B; //p684
  GPIOF_CR_R = 0xFF; //enable write to PUR
  GPIOF_PUR_R = 0x11; //enable PF0, PF4
  GPIOF_DIR_R = 0x0E; // 0b01110
  GPIOF_DEN_R = 0x1F; //enable PF0 to PF4
  GPIO_PORTF_IS_R &= ~0x11; // make bit 4, 0 edge sensitive
  GPIO_PORTF_IBE_R &= ~0x11; // trigger is controlled by IEV
  GPIO_PORTF_IEV_R  = ~0x11; // falling edge trigger
  GPIO_PORTF_ICR_R |= 0x11; // clear any prior interrupt
  GPIO_PORTF_IM_R  |= 0x11; // unmask interrupt
  EN0 |= (1<<30); // set interrupt priority 
  GPIOF_DATA_R = 0;
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
  T0_MIMR |= 0x01; //interrupt
  EN0 |= (1<<19); //NVIC
}
uint32_t color = 0;

int main()
{
  PortF_init();
  init_timer0();
  while(1) {
    
    if (color == 0) {
      GPIOF_DATA_R = BLUE;
    }else if (color ==1){
      GPIOF_DATA_R = 0;
    }else {
      GPIOF_DATA_R = RED;
    }
  }
}

void TIMER0A_Handler( void ){
  if(color == 0||color ==2){
    color = 1;
  }else if (color == 1){
    color = 0;
  }
  T0_ICR = 0x01; //clear bit
}
void PortF_Handler (void){
  
  if ((GPIOF_DATA_R & 0x01) == 0x00){
      color = 2;  
      T0_CTL = 0x00;      
    }
    else if ((GPIOF_DATA_R & 0x10) == 0x00){
      T0_ICR = 0x01;
      T0_CTL |= 0x01; 
    }
  GPIO_PORTF_ICR_R |= 0x11;
}

