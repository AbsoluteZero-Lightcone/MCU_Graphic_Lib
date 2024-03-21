/**
  ******************************************************************************
  * @file    SSD1306_Driver.h
  * @author  Lightcone & 江协科技
  * @version V2.0.4
  * @date    2024-03-21
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
	uint8_t DisplayBuf[SSD1306_PAGE][SSD1306_COL];
	void (*CS_Handler)(void);
} SSD1306;

void OLED_SetCursor_RAW(SSD1306* SSD1306_Struct_ptr,uint8_t Page, uint8_t X);
void OLED_Update_RAW(SSD1306* SSD1306_Struct_ptr);
void OLED_UpdateArea_RAW(SSD1306* SSD1306_Struct_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void OLED_Clear_RAW(SSD1306* SSD1306_Struct_ptr);

#endif /* __SSD1306_DRIVER_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
