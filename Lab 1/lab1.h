#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08
#define RED_BLUE 0x06
#define RED_GREEN 0x0a
#define BLUE_GREEN 0x0c
#define WHITE 0x0e
#define SYS_RCGC2_R (*((volatile uint32_t *)0x400FE608)) 
#define GPIOF_DIR_R (*((volatile uint32_t *)0x40025400)) //p662
#define GPIOF_DEN_R (*((volatile uint32_t *)0x4002551C)) //p683
#define GPIOF_DATA_R (*((volatile uint32_t *)0x400253FC)) //p662
#define GPIOF_LOCK_R (*((volatile uint32_t *)0x40025520))
#define GPIOF_CR_R (*((volatile uint32_t *)0x40025524))
#define GPIOF_PUR_R (*((volatile uint32_t *)0x40025510))