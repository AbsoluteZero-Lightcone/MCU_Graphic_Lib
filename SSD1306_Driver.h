/**
  ******************************************************************************
  * @file    SSD1306_Driver.h
  * @author  Lightcone & 江协科技
  * @version V2.0.1
  * @date    2024-03-21
  * @brief   OLED SSD1306硬件驱动层 
  ******************************************************************************
  */
#ifndef __OLED_H
#define __OLED_H
#include "STM32Device.h"

typedef struct{
	GPIO_TypeDef* D0_GPIO;	uint16_t D0_Pin;
	GPIO_TypeDef* D1_GPIO;	uint16_t D1_Pin;
	GPIO_TypeDef* RES_GPIO;	uint16_t RES_Pin;
	GPIO_TypeDef* DC_GPIO;	uint16_t DC_Pin;
	GPIO_TypeDef* CS_GPIO;	uint16_t CS_Pin;
	uint8_t DisplayBuf[128][8];
	void (*CS_Handler)(void);
} OLED_SPI;
#define OLED_DisplayBuf OLED_SPI_Struct_ptr->DisplayBuf

void OLED_SetCursor_RAW(OLED_SPI* OLED_SPI_Struct_ptr,uint8_t Page, uint8_t X);
void OLED_Update_RAW(OLED_SPI* OLED_SPI_Struct_ptr);
void OLED_UpdateArea_RAW(OLED_SPI* OLED_SPI_Struct_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void OLED_Clear_RAW(OLED_SPI* OLED_SPI_Struct_ptr);
#define OLED_SetCursor(Page,X) OLED_SetCursor_RAW(OLED_SPI_Struct_ptr,Page,X)
#define OLED_Update() OLED_Update_RAW(OLED_SPI_Struct_ptr)
#define OLED_UpdateArea(X,Y,Width,Height) OLED_UpdateArea_RAW(OLED_SPI_Struct_ptr,X,Y,Width,Height)
#define OLED_Clear() OLED_Clear_RAW(OLED_SPI_Struct_ptr)

#endif
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
