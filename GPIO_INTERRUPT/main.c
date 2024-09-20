#include "stm32f10x.h"
#include "stdint.h"
#include "gp_drive.h"
int signal=0;
void delay_ms(){
	for(volatile uint32_t i=0;i<2500000;i++);// mapping variable for avoid optimization
}
int main(void){
	
	/*RCC_APB2ENR|=1<<4;
	GPIOC->CRH&=0xFF0FFFFF; //reset CRH port B
	GPIOC->CRH|=0x00300000; //output max 50Mhz*/
	
	init_GP(PC,13,OUT10,O_GP_PP);
	init_GP(PB,5,IN,I_PP);
	GPIOB->ODR|=1<<5;
	
	__disable_irq();
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
			W_GP(PC,13,0);
		}else{
			W_GP(PC,13,1);
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