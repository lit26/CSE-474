#include <tm4c123gh6pm.h>
#include <stdint.h>
#include "lab2.h"

uint32_t T0_Flag = 0;
uint32_t T1_Flag = 0;
void delay(unsigned long val);
unsigned long Switch_Input(void);

void Switch_Init(void){ volatile unsigned long delay; //switch port PA5, PA6
  SYSCTL_RCGC2_R |= 0x00000001;
  delay = SYSCTL_RCGC2_R;
  
  GPIO_PORTA_AMSEL_R &= (~0x20) & (~0x40);
  GPIO_PORTA_PCTL_R &= ~0x0FF00000;
  GPIO_PORTA_DIR_R &= (~0x20) & (~0x40);
  GPIO_PORTA_AFSEL_R &= (~0x20) & (~0x40);
  GPIO_PORTA_DEN_R |= (0x20) | (0x40);
}

void LED_Init(void){ volatile unsigned long delay; // LED port PA2, PA3, PA4
  SYSCTL_RCGC2_R |= 0x01;
  delay = SYSCTL_RCGC2_R;
  
  GPIO_PORTA_PCTL_R &= ~0x000FFF00;
  GPIO_PORTA_AMSEL_R &= (~0x04) & (~0x08) & (~0x10);
  GPIO_PORTA_DIR_R |= 0x04 | 0x08 | 0x10;
  GPIO_PORTA_AFSEL_R &= (~0x04) & (~0x08) & (~0x10);
  GPIO_PORTA_DEN_R |= 0x04 | 0x08 | 0x10;
}
void Timer_Init(void){
  SYSCTL_RCGC2_R |= 0x21;
  SYS_RCGCTIMER_R |= 0x03; 
  T0_CTL &= ~(0x01);
  T0_CFG = 0x00;
  T0_TAMR  |= 0x2;
  T0_TAILR = 29000000; //2s
  T0_CTL |= 0x01; 
  T0_MIMR |= 0x01;
  EN0 |= (1<<19);
  T1_CTL &= ~(0x01);
  T1_CFG = 0x00;
  T1_TAMR  |= 0x2;
  T1_TAILR = 80000000; //5s
  T1_CTL |= 0x01; 
  T1_MIMR |= 0x01;
  EN0 |= (1<<21);
}
void hold(int state)
{
  if (state == 0){
    GPIO_PORTA_DATA_R &= (~0x04) & (~0x08) & (~0x10);
  }else if (state == 1){
    GPIO_PORTA_DATA_R = 0x10;//red
  }else if (state == 2){
    GPIO_PORTA_DATA_R = 0x08;//yellow
  }else if (state == 3){
    GPIO_PORTA_DATA_R = 0x04;//green
  }
  T1_Flag = 0;
  T1_ICR = 0x01; //clear flag
  while(T1_Flag ==0){}
  T1_Flag = 0;
}

int main()
{
  SYSCTL_RCGC2_R = 0x20;
  GPIO_PORTF_DATA_R = 0;
  Timer_Init();
  Switch_Init();
  LED_Init();
  int state = 0; 
  int next = 0 ;
  while(1) { 
    if (state == 0 && Switch_Input() == 0x20){       
        next = 1; 
    }else if (state == 1){
      if  (Switch_Input() == 0x20){
        next = 0;
      }else {
        next = 3;
     }
    }else if (state == 3){
      if  (Switch_Input() == 0x20){
        next = 0;
      }else if  (Switch_Input() == 0x40){
        next = 2;
      }else {
        next = 1;
      }
    }else if (state == 2){
      if  (Switch_Input() == 0x20){
        next = 0;
      }else {
        next = 1;
      }
    }
    state = next;
    hold(state);
  }
}
void TIMER0A_Handler(void){
  T0_Flag = 1;
  T0_ICR = 0x01; //clear flag
}
void TIMER1A_Handler(void){
  T1_Flag = 1;
  T1_ICR = 0x01; //clear flag
}

unsigned long Switch_Input(void){
  uint32_t input = GPIO_PORTA_DATA_R&0x60; 
  T0_ICR |= 0x01; //clear flag
  T0_Flag = 0;
  while(T0_Flag==0){ 
    if (GPIO_PORTA_DATA_R&0x0C != input){
      return 0x00; 
    }
  }
  T0_Flag=0;
  return input;
}



