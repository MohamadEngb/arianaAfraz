#include "main.h"

uint8_t buffer[10];
uint32_t data=0;
int main(void){
	clockInit();
	powerInit();	
	serialInit();
	buffer[0]=0x55;
	i2cInit();
	//i2cTransmit(0x7d,0xdfbc,buffer,1);
	spiFlashPower(ON);
	w25q32Init();
	w25q32SectorErase(0x00);
	w25q32WriteByte(0x00,0x55);
	data=w25q32ReadDataByte(0x00);
	while(1){

	}
}
