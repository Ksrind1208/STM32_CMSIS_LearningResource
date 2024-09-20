#include "stm32f10x.h"
#include "stdint.h"
void delay_ms(void){
	for(volatile uint32_t i=0;i<1900000;i++);
}
volatile uint8_t j=0;
int main(void ){
	RCC->APB2ENR|=(1<<3) | (1<<4);

	GPIOB->CRH&=0xFFF0FFFF;
	GPIOC->CRH&=0xFF0FFFFF;
	
	GPIOB->CRH|=0x00080000;
	GPIOB->ODR|=1<<12; // this line to set input pull-up mode by set ODR bit 1 respectively
	GPIOC->CRH|=0x00100000;
	while(1){
		if(GPIOB->IDR & 0x1000){
			GPIOC->BSRR=1<<29;
			j=5;
		}else{
			GPIOC->BSRR=1<<13;
			j=0;
		}
		
		/*GPIOB->BSRR=1<<12;
		delay_ms();
		GPIOB->BSRR=1<<28;
		delay_ms();*/
	}
	
	return 0;
}