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
#define GPIOF_IS_R         (*((volatile uint32_t *)0x40025404))
#define GPIOF_IBE_R        (*((volatile uint32_t *)0x40025408))
#define GPIOF_IEV_R        (*((volatile uint32_t *)0x4002540C))
#define GPIOF_ICR_R        (*((volatile uint32_t *)0x4002541C))
#define GPIOF_IM_R         (*((volatile uint32_t *)0x40025410))

#define SYS_RCGCTIMER_R       (*((volatile uint32_t *)0x400FE604)) //p338
#define T0_CTL                (*((volatile uint32_t *)0x4003000C))
#define T0_CFG                (*((volatile uint32_t *)0x40030000))
#define T0_TAMR               (*((volatile uint32_t *)0x40030004)) 
#define T0_TAILR              (*((volatile uint32_t *)0x40030028)) 
#define T0_RIS                (*((volatile uint32_t *)0x4003001C)) 
#define T0_ICR                (*((volatile uint32_t *)0x40030024))
#define T0_MIMR               (*((volatile uint32_t *)0x40030018))
#define T1_CTL                (*((volatile uint32_t *)0x4003100C))
#define T1_CFG                (*((volatile uint32_t *)0x40031000))
#define T1_TAMR               (*((volatile uint32_t *)0x40031004)) 
#define T1_TAILR              (*((volatile uint32_t *)0x40031028)) 
#define T1_RIS                (*((volatile uint32_t *)0x4003101C)) 
#define T1_ICR                (*((volatile uint32_t *)0x40031024))
#define T1_MIMR               (*((volatile uint32_t *)0x40031018))
#define EN0                   (*((volatile uint32_t *)0xE000E100))

