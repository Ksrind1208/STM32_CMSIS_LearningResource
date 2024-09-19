#include "stm32f10x.h"
#include "stdint.h"

void delay_ms(){
	for(volatile uint32_t i=0;i<2500000;i++);// mapping variable for avoid optimization
}
int main(void){
	
	RCC->APB2ENR|=1<<3;
	GPIOB->CRH&=0xFFF0FFFF; //reset CRH port B
	GPIOB->CRH|=0x00030000; //output max 50Mhz
	while(1){			
		GPIOB->BSRR|=1<<12;
		delay_ms();
		GPIOB->BSRR|=1<<28;
		delay_ms();
	}
	return 0;
}