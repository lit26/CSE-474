#include <tm4c123gh6pm.h>
#include <stdint.h>

void Switch_Init(void){ volatile unsigned long delay; //switch port PA5, PA6
  SYSCTL_RCGC2_R |= 0x00000001;
  delay = SYSCTL_RCGC2_R;
  
  GPIO_PORTA_AMSEL_R &= (~0x20) & (~0x40);
  GPIO_PORTA_PCTL_R &= ~0x0FF00000;
  GPIO_PORTA_DIR_R &= (~0x20) & (~0x40);
  GPIO_PORTA_AFSEL_R &= (~0x20) & (~0x40);
  GPIO_PORTA_DEN_R |= (0x20) | (0x40);
}
unsigned long System(void){
  return (GPIO_PORTA_DATA_R&0x20);
}
unsigned long ped_input(void){
  return (GPIO_PORTA_DATA_R&0x40);
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

void LED_Off(void){
  GPIO_PORTA_DATA_R &= (~0x04) & (~0x08) & (~0x10);
}
void LEDG_On(void){
  GPIO_PORTA_DATA_R = 0x04;
}
void LEDR_On(void){
  GPIO_PORTA_DATA_R = 0x10;
}
void LEDY_On(void){
  GPIO_PORTA_DATA_R = 0x08;
}
void SysCtlDelay(void){
  for(int i=0;i<1000000;i++){}
}

int main(){
  Switch_Init();
  LED_Init();
  int sys_start = 0;
  int state =0; //0-off, 1-red, 2-yellow, 3-green
  while(1){
    // checking whether the system start
    if(System()){
      SysCtlDelay();
      if(sys_start ==0){
        sys_start = 1;
        state = 1;
      }else if(sys_start ==1){
        sys_start = 0;
        state = 0;
      }
    }
    // checking the state and display LED 
    if(state == 0){
      LED_Off();
    } else if (state == 1){
      LEDR_On();
      state = 3;
      for (int i=0;i<1000000;i++){
        if(System()){
          sys_start = 0;
          state = 0;
          SysCtlDelay();
          break;
        }
      }
    } else if (state == 3){
      LEDG_On();
      state = 1;
      for (int i=0;i<1000000;i++){
        if(System()){
          sys_start = 0;
          state = 0;
          SysCtlDelay();
          break;
        }else if (ped_input()){
          state = 2;
          SysCtlDelay();
          break;
        }
      }
    } else if (state == 2){
      LEDY_On();
      state = 1;
      for (int i=0;i<1000000;i++){
        if(System()){
          sys_start = 0;
          state = 0;
          SysCtlDelay();
          break;
        }
      }
    }
  }
    
  return 0;
}