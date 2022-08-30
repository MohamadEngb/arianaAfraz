#ifndef  SOFTI2C_H
#define  SOFTI2C_H
#include "main.h"

#define i2cSCLPort GPIOA
#define i2cSDAPort GPIOA

#define i2cSCLPin 11
#define i2cSDAPin 12

typedef enum{
	ack
 ,nack
 ,i2cError
 ,i2cOk
}i2cRespons_t;
typedef enum{
	write
 ,read
}i2cRw_t;
void i2cInit(void);
void i2cAckGen(void);
i2cRespons_t i2cTransmit(uint8_t devAddr,uint16_t memAddr ,uint8_t *data,uint16_t nData);
i2cRespons_t i2cRecive(uint8_t addr,uint8_t *data,uint8_t ndata);
void i2cStart(void);
void i2cClk(void);
void i2cStop(void);
i2cRespons_t i2cAck(void);
void i2cWriteByte(uint8_t data);
#endif
