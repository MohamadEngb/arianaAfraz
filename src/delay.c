#include "delay.h"

uint16_t tickConter=0;

void SysTick_Handler(void){
	tickConter++;
}
void sysTickInit(void){
	SysTick->LOAD =CPUFrq/1000;
	SysTick->VAL=0;
	tickConter=0;
	SysTick->CTRL =0x07;
}
void delay_us(uint16_t delayUS){


}
void delay_ms(uint16_t delayMS){
	sysTickInit();
	while(tickConter<delayMS);
	SysTick->CTRL =0x04;
}
void delay_s(uint16_t delayS){

}
