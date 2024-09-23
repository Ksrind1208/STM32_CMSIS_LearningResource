#include "stm32f10x.h"
#include "stdint.h"
#include "gp_drive.h"
int signal=0;
void delay_ms(){
	for(volatile uint32_t i=0;i<2500000;i++);// mapping variable for avoid optimization
}
int main(void){
	RCC->APB2ENR|=1<<0;// enable clock afio
	init_GP(PC,13,OUT10,O_GP_PP);
	init_GP(PB,5,IN,I_PP);
	GPIOB->ODR|=1<<5;
	/*RCC->APB2ENR|=(1<<3) | (1<<4) | (1<<0);
	GPIOB->CRL&=0xFF0FFFFF;
	GPIOB->CRL|=0x00800000;
	GPIOB->ODR|=1<<5;

	GPIOC->CRH&=0xFF0FFFFF;
	GPIOC->CRH|=0x00300000;*/
	
	__disable_irq();
	AFIO->EXTICR[1] &= 0xFF0F;// clear exti line 5 
	AFIO->EXTICR[1]=0x0010;
	EXTI->IMR|=1<<5;
	EXTI->FTSR|=1<<5;
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	__enable_irq();
	
	while(1){
		/*if(R_GP(PA,15)==0){
			W_GP(PC,13,0);
		}else{
			W_GP(PC,13,1);
		}*/
		if(signal){
			//W_GP(PC,13,0);
			GPIOC->BSRR=1<<29;
		}else{
			//W_GP(PC,13,1);
			GPIOC->BSRR=1<<13;
		}
	}
	return 0;
}

void EXTI9_5_IRQHandler(){
    EXTI->PR |= 1<<5 ;

    if(signal){
        signal = 0;
    } else {
        signal = 1;
    }
}