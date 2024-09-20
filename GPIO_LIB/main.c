#include "stm32f10x.h"
#include "stdint.h"
#include "gp_drive.h"

void delay_ms(){
	for(volatile uint32_t i=0;i<2500000;i++);// mapping variable for avoid optimization
}
int main(void){
	
	/*RCC_APB2ENR|=1<<4;
	GPIOC->CRH&=0xFF0FFFFF; //reset CRH port B
	GPIOC->CRH|=0x00300000; //output max 50Mhz*/
	
	init_GP(PC,13,OUT10,O_GP_PP);
	init_GP(PB,12,IN,I_PP);
	GPIOB->ODR|=1<<12;
	while(1){
		if(R_GP(PB,12)==0){
			W_GP(PC,13,0);
		}else{
			W_GP(PC,13,1);
		}
	}
	return 0;
}