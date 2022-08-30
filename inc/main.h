#ifndef MAIN_H
#define MAIN_H
#include "stm32f0xx.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "stdio.h"


typedef enum{
	ON
 ,OFF
}enum_POWER_t;
typedef enum{
	OK
 ,Error
}status_t;


#include "clock.h"
#include "delay.h"
#include "display.h"
#include "power.h"
#include "serial.h"
#include "softI2c.h"
#include "w25q32.h"
#endif
