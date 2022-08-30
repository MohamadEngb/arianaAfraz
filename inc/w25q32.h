#ifndef W25Q32_H
#define W25Q32_H
#include "main.h"

#define clk_port GPIOB
#define clk_pin  GPIO_ODR_6
#define mosi_port GPIOB
#define mosi_pin  GPIO_ODR_7
#define miso_port GPIOB
#define miso_pin  GPIO_ODR_8
#define cs_port GPIOA
#define cs_pin  GPIO_ODR_8


void w25q32clk(void);
void w25q32Cmd(uint8_t cmd);
uint8_t w25q32ReadByte(void);
uint32_t jedecId(void);
void w25q32WriteEnable(void);
void w25q32WriteDisble(void);
void w25q32SectorErase(uint32_t addr);
void w25q32WriteByte(uint32_t addr,uint8_t data);
void w25q32WritePage(uint32_t addr,uint8_t * dataBuffer);
char w25q32ReadDataByte(uint32_t addr);
void w25q32ReadPage(uint32_t pageNumber,uint8_t * dataBuffer);
char w25q32readStatusRegister1(void);
void w25q32WriteData(uint8_t *data);
status_t w25q32ReadData(uint8_t*data);
void w25q32ChipErase(void);
void w25q32Init(void);
#endif
