#ifndef POWER_H
#define POWER_H
#include "main.h"

#define buzzerPort GPIOF
#define buzzerPin  7

#define sht1PowerPort GPIOB
#define sht1PowerPin  2

#define sht2PowerPort GPIOB
#define sht2PowerPin  5

#define oledDisplayPowerPort GPIOA
#define oledDisplayPowerPin  15

#define spiFlashpowerPort GPIOA
#define spiFlashpowerPin 4

void powerInit(void);
void buzzerPower(enum_POWER_t pwr);
void sht1Power(enum_POWER_t pwr);
void sht2Power(enum_POWER_t pwr);
void oledDisplayPower(enum_POWER_t pwr);
void spiFlashPower(enum_POWER_t pwr);
#endif
