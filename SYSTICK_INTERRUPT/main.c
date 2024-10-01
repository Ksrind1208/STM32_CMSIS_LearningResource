#include "stm32f10x.h"
#include "gp_drive.h"
#include "stdbool.h"

volatile static bool flag=false;
int main(void){
	init_GP(PA,0,IN,I_PP);
	init_GP(PC,13,OUT50,O_GP_PP);

	__disable_irq();
	SysTick->CTRL=0;
	SysTick->LOAD=16777216-1; //24 bit max is 16777216-1 (16777216 ticks)
	SysTick->VAL=0;
	SysTick->CTRL=7;
	__enable_irq();
	
	while(1){
	}
	return 0;
}

void SysTick_Handler(void){
	if(flag==false){
		W_GP(PC,13,1);
		flag=true;
	}else{
		W_GP(PC,13,0);
		flag=false;
	}
}