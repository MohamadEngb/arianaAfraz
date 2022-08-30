#include "softI2c.h"

void i2cInit(void){
	i2cSCLPort->ODR   |= (1<<i2cSCLPin);
	i2cSDAPort->ODR   |= (1<<i2cSDAPin);
	i2cSCLPort->MODER |= (1<<(i2cSCLPin*2));
	i2cSDAPort->MODER |= (1<<(i2cSDAPin*2));
	i2cSCLPort->OTYPER |= (1<<(i2cSCLPin*2));
	i2cSDAPort->OTYPER |= (1<<(i2cSDAPin*2));
}
void i2cAckGen(void){
	i2cSDAPort->ODR &= ~(1<<i2cSDAPin);
	i2cSDAPort->MODER |= (1<<(i2cSDAPin*2));
	i2cClk();
}
i2cRespons_t i2cTransmit(uint8_t devAddr,uint16_t memAddr ,uint8_t *data,uint16_t nData){
	i2cStart();
	i2cWriteByte((devAddr<<1)&0xfe);
	if(i2cAck()==nack){
		return i2cError;
	}else{
		i2cWriteByte((uint8_t)(memAddr>>8));
		if(i2cAck()==nack){
			return i2cError;
		}else{
			i2cWriteByte((uint8_t)(memAddr&0x00ff));
			if(i2cAck()==nack){
				return i2cError;
			}else{
				for(uint16_t byteCont=0;byteCont<nData;byteCont++){
					i2cWriteByte(*data);
					if(i2cAck()==nack){
						return i2cError;
					}
					data++;
				}
			}				
			i2cStop();
			return i2cOk;
		}
	}
}
i2cRespons_t i2cRecive(uint8_t addr,uint8_t *data,uint8_t ndata){
	uint8_t h=0;
	i2cStart();
	i2cWriteByte((addr<<1)|0x01);
	if(i2cAck()==nack){
		return i2cError;
	}else{
		i2cSDAPort->MODER &=~(3<<(i2cSDAPin*2));
		for(int8_t byteCont=ndata;byteCont>=0;byteCont--){
			for(int8_t i2cCont=7;i2cCont>=0;i2cCont--){
				if(i2cSDAPort->IDR&(1<<i2cSDAPin)){
					h |= 1<<i2cCont;
				}
				i2cClk();
			}
			i2cAckGen();
		}
		i2cStop();
	}
	return i2cOk;
}
void i2cStart(void){
	
	i2cSDAPort->ODR &=~(1<<i2cSDAPin);
	delay_ms(5);
	i2cSCLPort->ODR &=~(1<<i2cSCLPin);
	delay_ms(5);
}
void i2cClk(void){
	i2cSCLPort->ODR |= (1<<i2cSCLPin);
	delay_ms(5);
	i2cSCLPort->ODR &=~(1<<i2cSCLPin);
	delay_ms(5);
}
void i2cStop(void){
	i2cSDAPort->ODR &= ~(1<<i2cSDAPin);
	delay_ms(5);
	i2cSCLPort->ODR |= (1<<i2cSCLPin);
	delay_ms(5);
	i2cSDAPort->ODR |= (1<<i2cSDAPin);
	delay_ms(5);
}
i2cRespons_t i2cAck(void){
	i2cSDAPort->MODER &=~(3<<(i2cSDAPin*2));
	i2cClk();
	if(i2cSDAPort->IDR&(1<<i2cSDAPin)){
		return nack;
	}else{
		return ack;
	}
}
void i2cWriteByte(uint8_t data){
	i2cSDAPort->MODER |= (1<<(i2cSDAPin*2));
	
	for(int8_t i2cBitCont=7;i2cBitCont>=0;i2cBitCont--){
		if((data>>i2cBitCont)&0x01){
			i2cSDAPort->ODR |= (1<<i2cSDAPin);
		}else{
			i2cSDAPort->ODR &=~(1<<i2cSDAPin);
		}
		i2cClk();
	}
}
