#include "w25q32.h" 
void w25q32clk(void){
	clk_port->ODR |= clk_pin;
	for(int n=0;n<0xf;n++)n=n;
	clk_port->ODR &= ~clk_pin;
	for(int n=0;n<0xf;n++)n=n;
}
void w25q32Cmd(uint8_t cmd){
	int cmdCnt=0;
	for(cmdCnt=7;cmdCnt>=0;cmdCnt--){
		if((cmd>>cmdCnt)&0x01){
			mosi_port->ODR |= mosi_pin;
		}else{
			mosi_port->ODR &= ~mosi_pin;
		}
		w25q32clk();		
	}
	mosi_port->ODR &= ~mosi_pin;
}
uint8_t w25q32ReadByte(void){
	int readByteCnt=0;
	uint8_t buff=0;
	for(readByteCnt=7;readByteCnt>=0;readByteCnt--){	
		if(miso_port->IDR&miso_pin){
			buff |= (1<<readByteCnt);
		}
		w25q32clk();
	}
	return buff;
}
uint32_t jedecId(void){
	uint32_t jedec=0;
	cs_port->ODR &= ~cs_pin;
	w25q32Cmd(0x9f);
	jedec |= (w25q32ReadByte()<<16);
	jedec |= (w25q32ReadByte()<<8);
	jedec |= w25q32ReadByte();
	cs_port->ODR |=cs_pin;	
	return jedec;
}
void w25q32WriteEnable(void){
	cs_port->ODR &= ~cs_pin;
	w25q32Cmd(0x06);
	cs_port->ODR |=cs_pin;
}
void w25q32WriteDisble(void){
	cs_port->ODR &= ~cs_pin;
	w25q32Cmd(0x04);
	cs_port->ODR |=cs_pin;
}
void w25q32SectorErase(uint32_t addr){
	w25q32WriteEnable();
	cs_port->ODR &= ~cs_pin;
	w25q32Cmd(0x20);
	w25q32Cmd((uint8_t)(addr>>16));
	w25q32Cmd((uint8_t)(addr>>8));
	w25q32Cmd((uint8_t)addr);
	cs_port->ODR |=cs_pin;
}
void w25q32WriteByte(uint32_t addr,uint8_t data){
	w25q32WriteEnable();
	cs_port->ODR &= ~cs_pin;
	w25q32Cmd(0x02);
	w25q32Cmd((uint8_t)(addr>>16));
	w25q32Cmd((uint8_t)(addr>>8));
	w25q32Cmd((uint8_t)addr);
	w25q32Cmd(data);
	cs_port->ODR |=cs_pin;
	w25q32WriteDisble();
}
void w25q32WritePage(uint32_t addr,uint8_t * dataBuffer){
	
}
char w25q32ReadDataByte(uint32_t addr){
	char data;
	w25q32WriteEnable();
	cs_port->ODR &= ~cs_pin;	
	w25q32Cmd(0x03);
	w25q32Cmd((uint8_t)(addr>>16));
	w25q32Cmd((uint8_t)(addr>>8));
	w25q32Cmd((uint8_t)addr);	
	data = w25q32ReadByte();	
	cs_port->ODR |=cs_pin;
	w25q32WriteDisble();
	return data;	
}
void w25q32ReadPage(uint32_t pageNumber,uint8_t *dataBuffer){
	uint32_t add=pageNumber*256;
	for(uint16_t cont=0;cont<=255;cont++){
		*dataBuffer =	w25q32ReadDataByte(add);
		dataBuffer++;
		add++;
	}
}

char w25q32readStatusRegister1(void){
	char status=0;
	cs_port->ODR &= ~cs_pin;
	w25q32Cmd(0x05);
	status = w25q32ReadByte();
	cs_port->ODR |=cs_pin;
	return status;
}
void w25q32ChipErase(void){
	w25q32WriteEnable();
	w25q32Cmd(0x60);
}
void w25q32Init(void){
	w25q32ChipErase();
	delay_ms(1000);
}
status_t w25q32ReadData(uint8_t*data){
	union adr{
		uint32_t addr;
		uint8_t  addrbyte[3];
	}addrr,addrw;
	uint8_t cont0=0;
	addrr.addr=0;
	addrw.addr=0;
	addrr.addrbyte[0]=w25q32ReadDataByte(0x00000000);
	addrr.addrbyte[1]=w25q32ReadDataByte(0x00000001);
	addrr.addrbyte[2]=w25q32ReadDataByte(0x00000002);

	addrw.addrbyte[0]=w25q32ReadDataByte(0x00000003);
	addrw.addrbyte[1]=w25q32ReadDataByte(0x00000004);
	addrw.addrbyte[2]=w25q32ReadDataByte(0x00000005);
	
	if(addrr.addr<8192)addrr.addr+=8192;
	if(addrw.addr<8192)addrw.addr+=8192;
	if(addrr.addr>=addrw.addr)return Error;
	for(cont0=0;cont0<28;cont0++){
		*data=w25q32ReadDataByte(addrr.addr);
		data++;
		addrr.addr++;
	}
	w25q32SectorErase(0x00000000);
	delay_ms(500);
	w25q32WriteByte(0x00000000,addrr.addrbyte[0]);
	w25q32WriteByte(0x00000001,addrr.addrbyte[1]);
	w25q32WriteByte(0x00000002,addrr.addrbyte[2]);
	w25q32WriteByte(0x00000003,addrw.addrbyte[0]);
	w25q32WriteByte(0x00000004,addrw.addrbyte[1]);
	w25q32WriteByte(0x00000005,addrw.addrbyte[2]);
	w25q32WriteByte(0x00000006,0x00);
	return OK;
}
void w25q32WriteData(uint8_t *data){ 
	union adr{
		uint32_t addr;
		uint8_t addrbyte[3];
	}addrr,addrw;
	uint8_t cont0=0;
	addrr.addr=0;
	addrw.addr=0;
	addrr.addrbyte[0]=w25q32ReadDataByte(0x00000000);
	addrr.addrbyte[1]=w25q32ReadDataByte(0x00000001);
	addrr.addrbyte[2]=w25q32ReadDataByte(0x00000002);

	addrw.addrbyte[0]=w25q32ReadDataByte(0x00000003);
	addrw.addrbyte[1]=w25q32ReadDataByte(0x00000004);
	addrw.addrbyte[2]=w25q32ReadDataByte(0x00000005);
	
	if(addrw.addr<8192)addrw.addr+=8192;
	w25q32SectorErase(addrw.addr);
	delay_ms(500);
	for(cont0=0;cont0<28;cont0++){
		w25q32WriteByte(addrw.addr,*data);
		data++;
		addrw.addr++;
	}
	w25q32SectorErase(0x00000000);
	delay_ms(500);
	w25q32WriteByte(0x00000000,addrr.addrbyte[0]);
	w25q32WriteByte(0x00000001,addrr.addrbyte[1]);
	w25q32WriteByte(0x00000002,addrr.addrbyte[2]);
	w25q32WriteByte(0x00000003,addrw.addrbyte[0]);
	w25q32WriteByte(0x00000004,addrw.addrbyte[1]);
	w25q32WriteByte(0x00000005,addrw.addrbyte[2]);
	w25q32WriteByte(0x00000006,0x00);
}
