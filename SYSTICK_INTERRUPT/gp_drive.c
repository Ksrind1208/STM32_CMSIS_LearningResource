#include "gp_drive.h"

void init_GP(unsigned short port,unsigned short pin, unsigned short dir, unsigned short opt){
	volatile unsigned long *CR;
	unsigned short tPIN=pin;
	unsigned short offset =0x00;
	
	if(pin >7){
		tPIN-=8;
		offset=0x01;//plus 0x01 actually plus 4 byte because unsigned int is 32bit
	}
	if(port==1){
		RCC_APB2ENR|=4;
		CR=(volatile unsigned long* )(&GPIO_A+offset);
	}else if(port==2){
		RCC_APB2ENR|=8;
		CR=(volatile unsigned long* )(&GPIO_B+offset);
	}else if(port==3){
		RCC_APB2ENR|=0x10;
		CR=(volatile unsigned long* )(&GPIO_C+offset);
	}
	
	*CR&=~(0xf <<(tPIN*4)); //reset target pin
	*CR|=(dir<<(tPIN*4)) | (opt<<(tPIN*4+2));
	
}
int R_GP(unsigned short port,unsigned short pin){
	volatile unsigned long *IDR;
	unsigned long offset=0x02;
	int state;
	
	if(port==1){
		IDR=(volatile unsigned long* )(&GPIO_A+offset);
	}else if(port==2){
		IDR=(volatile unsigned long* )(&GPIO_B+offset);
	}else if(port==3){
		IDR=(volatile unsigned long* )(&GPIO_C+offset);
	}
	state= ((*IDR) & 1<<(pin))>>pin;
	return state;
}
void W_GP(unsigned short port,unsigned short pin,unsigned short state){
	volatile unsigned long *ODR;
	unsigned long offset=0x03;
	if(port==1){
		ODR=(volatile unsigned long* )(&GPIO_A+offset);
	}else if(port==2){
		ODR=(volatile unsigned long* )(&GPIO_B+offset);
	}else if(port==3){
		ODR=(volatile unsigned long*)(&GPIO_C+offset);
	}
	
	state?(*ODR|=1<<pin):(*ODR &= ~(1<<pin));
}