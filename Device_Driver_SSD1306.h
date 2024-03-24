/**
  ******************************************************************************
  * @file    Device_Driver_SSD1306.h
  * @author  Lightcone
  * @version V3.0.3
  * @date    2024-03-25
  * @brief   OLED SSD1306硬件驱动层 
  ******************************************************************************
  */
#ifndef __DEVICE_DRIVER_SSD1306_H
#define __DEVICE_DRIVER_SSD1306_H
#include "STM32Device.h"
//#define SSD1306_PAGE 8
//#define SSD1306_COL 128

typedef uint8_t enum_data;

typedef struct{
	enum_data Device_Enum;
	GPIO_TypeDef* D0_GPIO;	uint16_t D0_Pin;
	GPIO_TypeDef* D1_GPIO;	uint16_t D1_Pin;
	GPIO_TypeDef* RES_GPIO;	uint16_t RES_Pin;
	GPIO_TypeDef* DC_GPIO;	uint16_t DC_Pin;
	GPIO_TypeDef* CS_GPIO;	uint16_t CS_Pin;
	uint8_t *DisplayBuf;
	void (*CS_Handler)(enum_data Device_Enum);
} SSD1306;

void SSD1306_Init(SSD1306* SSD1306_Struct_ptr);

void SSD1306_SetCursor(SSD1306* SSD1306_Struct_ptr,uint8_t Page, uint8_t X);
void SSD1306_UpdateArea(SSD1306* SSD1306_Struct_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void SSD1306_Update(SSD1306* SSD1306_Struct_ptr);
void SSD1306_Clear(SSD1306* SSD1306_Struct_ptr);

#endif /* __DEVICE_DRIVER_SSD1306_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
