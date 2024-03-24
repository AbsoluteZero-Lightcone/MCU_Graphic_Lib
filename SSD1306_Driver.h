/**
  ******************************************************************************
  * @file    SSD1306_Driver.h
  * @author  Lightcone
  * @version V3.0.0
  * @date    2024-03-24
  * @brief   OLED SSD1306硬件驱动层 
  ******************************************************************************
  */
#ifndef __SSD1306_DRIVER_H
#define __SSD1306_DRIVER_H
#include "STM32Device.h"
#define SSD1306_PAGE 8
#define SSD1306_COL 128

typedef struct{
	GPIO_TypeDef* D0_GPIO;	uint16_t D0_Pin;
	GPIO_TypeDef* D1_GPIO;	uint16_t D1_Pin;
	GPIO_TypeDef* RES_GPIO;	uint16_t RES_Pin;
	GPIO_TypeDef* DC_GPIO;	uint16_t DC_Pin;
	GPIO_TypeDef* CS_GPIO;	uint16_t CS_Pin;
	uint8_t *DisplayBuf;
	void (*CS_Handler)(void);
} SSD1306;

void SSD1306_SetCursor_RAW(SSD1306* SSD1306_Struct_ptr,uint8_t Page, uint8_t X);
void SSD1306_Update_RAW(SSD1306* SSD1306_Struct_ptr);
void SSD1306_UpdateArea_RAW(SSD1306* SSD1306_Struct_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void SSD1306_Clear_RAW(SSD1306* SSD1306_Struct_ptr);

#endif /* __SSD1306_DRIVER_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
