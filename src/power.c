#include "power.h"

void powerInit(void){
	buzzerPort->MODER           |= (1<<(buzzerPin*2));
	sht1PowerPort->MODER        |= (1<<(sht1PowerPin*2));
	sht2PowerPort->MODER 			  |= (1<<(sht2PowerPin*2));
	oledDisplayPowerPort->MODER |= (1<<(oledDisplayPowerPin*2));
	spiFlashpowerPort->MODER    |= (1<<(spiFlashpowerPin*2));
}
void buzzerPower(enum_POWER_t pwr){
	if(pwr==ON){
		buzzerPort->ODR |= (1<<buzzerPin);
	}else if(pwr==OFF){
		buzzerPort->ODR &= ~(1<<buzzerPin);
	}
}
void sht1Power(enum_POWER_t pwr){
	if(pwr==ON){
		sht1PowerPort->ODR |= (1<<sht1PowerPin);
	}else if(pwr==OFF){
		sht1PowerPort->ODR &= ~(1<<sht1PowerPin);
	}
}
void sht2Power(enum_POWER_t pwr){
	if(pwr==ON){
		sht2PowerPort->ODR |= (1<<sht2PowerPin);
	}else if(pwr==OFF){
		sht2PowerPort->ODR &= ~(1<<sht2PowerPin);
	}
}
void oledDisplayPower(enum_POWER_t pwr){
	if(pwr==ON){
		oledDisplayPowerPort->ODR |= (1<<oledDisplayPowerPin);
	}else if(pwr==OFF){
		oledDisplayPowerPort->ODR &= ~(1<<oledDisplayPowerPin);
	}
}
void spiFlashPower(enum_POWER_t pwr){
	if(pwr==ON){
		spiFlashpowerPort->ODR |= (1<<spiFlashpowerPin);
	}else if(pwr==OFF){
		spiFlashpowerPort->ODR &= ~(1<<spiFlashpowerPin);
	}
}
