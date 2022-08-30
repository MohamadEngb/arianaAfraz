#include "serial.h"


char usart1RxBuffer[40];
uint8_t usart1RxConter=0;

void bufferRefresh(void){
	for(int cont=0;cont<=119;cont++){
		usart1RxBuffer[cont]=' ';
	}
	usart1RxConter=0;
	IWDG->KR = 0x0000AAAA;
}

void USART1_IRQHandler(void){
	if(USART1->ISR&USART_ISR_ORE){
		USART1->ICR |= USART_ICR_ORECF;
	}
	if(usart1RxConter<119){
		usart1RxBuffer[usart1RxConter]=USART1->RDR;
		usart1RxConter++;		
	}else{
		usart1RxBuffer[39]=USART1->RDR;
	}
}
void serialInit(void){
	GPIOA->MODER |= GPIO_MODER_MODER9_1;
	GPIOA->MODER |= GPIO_MODER_MODER10_1;	
	GPIOA->AFR[1] |= (1<<GPIO_AFRH_AFRH1_Pos);
	GPIOA->AFR[1] |= (1<<GPIO_AFRH_AFRH2_Pos);
	
	USART1->CR1=0x0000;
	USART1->CR2=0x0000;
	USART1->CR3=0x0000;
	USART1->BRR=0x0000;
	USART1->ISR=0x00C0;
	USART1->ICR=0x00C0;
	USART1->BRR  = 5000;
	USART1->CR1 |= USART_CR1_RXNEIE;
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_RE;
	USART1->CR1 |= USART_CR1_UE;
	NVIC_EnableIRQ(USART1_IRQn);
}
