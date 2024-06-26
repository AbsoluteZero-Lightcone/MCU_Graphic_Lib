#ifndef __74HC138_H
#define __74HC138_H
#include "STM32Device.h"


typedef struct{
	GPIO_TypeDef* A_GPIO;uint16_t A_Pin;
	GPIO_TypeDef* B_GPIO;uint16_t B_Pin;
	GPIO_TypeDef* C_GPIO;uint16_t C_Pin;
} _74HC138_TypeDef;

void _74HC138_Write(const _74HC138_TypeDef* _74HC138,uint8_t n);
void _74HC138_Init(const _74HC138_TypeDef* _74HC138_Struct);


#endif
