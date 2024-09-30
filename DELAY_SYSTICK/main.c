#include "stm32f10x.h"
void systick_init(void);
void delay_ms(uint32_t ms);
int main(void){
	systick_init();
	RCC->APB2ENR|=1<<4;
	GPIOC->CRH&=0xFF0FFFFF;
	GPIOC->CRH|=0x00300000;
	
	
	while(1){
		GPIOC->BSRR|=1<<29;
		delay_ms(1000);
		GPIOC->BSRR|=1<<13;
		delay_ms(1000);
	}
	return 0;
}

void systick_init(void){
	SysTick->CTRL=0;
	SysTick->LOAD=0x00FFFFFF;
	SysTick->VAL=0;
	SysTick->CTRL=5;
}

void delaymillis(){
	SysTick->LOAD=72000-1;
	SysTick->VAL=0;
	while((SysTick->CTRL & 0x00010000) ==0);
}
void delay_ms(uint32_t ms){
	for(volatile uint32_t i=0;i<ms;i++){
		delaymillis();
	}
}