/**
  ******************************************************************************
  * @file    Graphic_test.c
  * @author  Lightcone
  * @version V1.0.1
  * @date    2024-03-21
  * @brief   图形显示库测试环境
  ******************************************************************************
  */
#include "Graphic.h"
#include "SSD1306_Driver.h"
#include "74HC138.h"

/** @defgroup STM32F103C_Dev_Board_V1 Pin Config
  * @{
  */ 
#define Board_SPI_SCK_GPIO	GPIOA
#define Board_SPI_SCK_Pin	GPIO_Pin_7
#define Board_SPI_SDA_GPIO	GPIOA
#define Board_SPI_SDA_Pin	GPIO_Pin_5
#define Board_SPI_DC_GPIO	GPIOB
#define Board_SPI_DC_Pin	GPIO_Pin_10
/**
  * @}
  */
/** @defgroup SPI_CS 74HC138 config
  * @{
  */ 
_74HC138_TypeDef Device_CS_74HC138 = {
		.A_GPIO=GPIOB,.A_Pin=GPIO_Pin_11,
		.B_GPIO=GPIOB,.B_Pin=GPIO_Pin_12,
		.C_GPIO=GPIOB,.C_Pin=GPIO_Pin_13
	};
/**
  * @}
  */

/** @defgroup OLED Devices config
  * @{
  */ 
enum{
	Enum_OLED1,
	Enum_OLED2,
	Enum_OLED3,
	Enum_OLED4,
	Enum_OLED5,
	Enum_OLED_MAX
};

/** @defgroup OLED Devices config
  * @{
  */ 
void Enum_OLED1_CS_Callback(){_74HC138_Write(&Device_CS_74HC138,1);}
void Enum_OLED2_CS_Callback(){_74HC138_Write(&Device_CS_74HC138,2);}
void Enum_OLED3_CS_Callback(){_74HC138_Write(&Device_CS_74HC138,3);}
void Enum_OLED4_CS_Callback(){_74HC138_Write(&Device_CS_74HC138,4);}
void Enum_OLED5_CS_Callback(){_74HC138_Write(&Device_CS_74HC138,5);}
SSD1306 Screen[Enum_OLED_MAX] = {
	[Enum_OLED1] = {
		.D0_GPIO  = Board_SPI_SCK_GPIO,.D0_Pin = Board_SPI_SCK_Pin,
		.D1_GPIO  = Board_SPI_SDA_GPIO,.D1_Pin = Board_SPI_SDA_Pin,
		.DC_GPIO  = Board_SPI_DC_GPIO ,.DC_Pin = Board_SPI_DC_Pin,
		.RES_GPIO = GPIOG             ,.RES_Pin = GPIO_Pin_0,
		.CS_Handler = Enum_OLED1_CS_Callback,
		.DisplayBuf = {0}
	},
	[Enum_OLED2] = {
		.D0_GPIO  = Board_SPI_SCK_GPIO,.D0_Pin = Board_SPI_SCK_Pin,
		.D1_GPIO  = Board_SPI_SDA_GPIO,.D1_Pin = Board_SPI_SDA_Pin,
		.DC_GPIO  = Board_SPI_DC_GPIO ,.DC_Pin = Board_SPI_DC_Pin,
		.RES_GPIO = GPIOG             ,.RES_Pin = GPIO_Pin_0,
		.CS_Handler = Enum_OLED2_CS_Callback,
		.DisplayBuf = {0}
	},
	[Enum_OLED3] = {
		.D0_GPIO  = Board_SPI_SCK_GPIO,.D0_Pin = Board_SPI_SCK_Pin,
		.D1_GPIO  = Board_SPI_SDA_GPIO,.D1_Pin = Board_SPI_SDA_Pin,
		.DC_GPIO  = Board_SPI_DC_GPIO ,.DC_Pin = Board_SPI_DC_Pin,
		.RES_GPIO = GPIOG             ,.RES_Pin = GPIO_Pin_0,
		.CS_Handler = Enum_OLED3_CS_Callback,
		.DisplayBuf = {0}
	},
	[Enum_OLED4] = {
		.D0_GPIO  = Board_SPI_SCK_GPIO,.D0_Pin = Board_SPI_SCK_Pin,
		.D1_GPIO  = Board_SPI_SDA_GPIO,.D1_Pin = Board_SPI_SDA_Pin,
		.DC_GPIO  = Board_SPI_DC_GPIO ,.DC_Pin = Board_SPI_DC_Pin,
		.RES_GPIO = GPIOG             ,.RES_Pin = GPIO_Pin_0,
		.CS_Handler = Enum_OLED4_CS_Callback,
		.DisplayBuf = {0}
	},
	[Enum_OLED5] = {
		.D0_GPIO  = Board_SPI_SCK_GPIO,.D0_Pin = Board_SPI_SCK_Pin,
		.D1_GPIO  = Board_SPI_SDA_GPIO,.D1_Pin = Board_SPI_SDA_Pin,
		.DC_GPIO  = Board_SPI_DC_GPIO ,.DC_Pin = Board_SPI_DC_Pin,
		.RES_GPIO = GPIOB             ,.RES_Pin = GPIO_Pin_9,
		.CS_Handler = Enum_OLED5_CS_Callback,
		.DisplayBuf = {0}
	},
};
/**
  * @}
  */

void Enum_OLED1_SetCursor_Callback(uint8_t x,uint8_t y){OLED_SetCursor_RAW(&Screen[Enum_OLED1],x,y);}
void Enum_OLED2_SetCursor_Callback(uint8_t x,uint8_t y){OLED_SetCursor_RAW(&Screen[Enum_OLED2],x,y);}
void Enum_OLED3_SetCursor_Callback(uint8_t x,uint8_t y){OLED_SetCursor_RAW(&Screen[Enum_OLED3],x,y);}
void Enum_OLED4_SetCursor_Callback(uint8_t x,uint8_t y){OLED_SetCursor_RAW(&Screen[Enum_OLED4],x,y);}
void Enum_OLED5_SetCursor_Callback(uint8_t x,uint8_t y){OLED_SetCursor_RAW(&Screen[Enum_OLED5],x,y);}
void Enum_OLED1_Update_Callback(void){OLED_Update_RAW(&Screen[Enum_OLED1]);}
void Enum_OLED2_Update_Callback(void){OLED_Update_RAW(&Screen[Enum_OLED2]);}
void Enum_OLED3_Update_Callback(void){OLED_Update_RAW(&Screen[Enum_OLED3]);}
void Enum_OLED4_Update_Callback(void){OLED_Update_RAW(&Screen[Enum_OLED4]);}
void Enum_OLED5_Update_Callback(void){OLED_Update_RAW(&Screen[Enum_OLED5]);}
void Enum_OLED1_UpdateArea_Callback(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height){OLED_UpdateArea_RAW(&Screen[Enum_OLED1],X,Y,Width,Height);}
void Enum_OLED2_UpdateArea_Callback(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height){OLED_UpdateArea_RAW(&Screen[Enum_OLED2],X,Y,Width,Height);}
void Enum_OLED3_UpdateArea_Callback(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height){OLED_UpdateArea_RAW(&Screen[Enum_OLED3],X,Y,Width,Height);}
void Enum_OLED4_UpdateArea_Callback(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height){OLED_UpdateArea_RAW(&Screen[Enum_OLED4],X,Y,Width,Height);}
void Enum_OLED5_UpdateArea_Callback(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height){OLED_UpdateArea_RAW(&Screen[Enum_OLED5],X,Y,Width,Height);}
// 硬件抽象层和显示应用层分离，能够同时驱动不同种芯片的屏幕
Graphic_InitTypeDef Display[Enum_OLED_MAX] = {
	[Enum_OLED1] = {
		.Screen_SetCursor_Callback = Enum_OLED1_SetCursor_Callback,
		.Screen_Update_Callback = Enum_OLED1_Update_Callback,
		.Screen_UpdateArea_Callback = Enum_OLED1_UpdateArea_Callback,
		.DisplayBuf = (uint8_t **)Screen[Enum_OLED1].DisplayBuf,
		.Screen_X = 128,
		.Screen_Y = 64,
	},
	[Enum_OLED2] = {
		.Screen_SetCursor_Callback = Enum_OLED2_SetCursor_Callback,
		.Screen_Update_Callback = Enum_OLED2_Update_Callback,
		.Screen_UpdateArea_Callback = Enum_OLED2_UpdateArea_Callback,
		.DisplayBuf = (uint8_t **)Screen[Enum_OLED2].DisplayBuf,
		.Screen_X = 128,
		.Screen_Y = 64,
	},
	[Enum_OLED3] = {
		.Screen_SetCursor_Callback = Enum_OLED3_SetCursor_Callback,
		.Screen_Update_Callback = Enum_OLED3_Update_Callback,
		.Screen_UpdateArea_Callback = Enum_OLED3_UpdateArea_Callback,
		.DisplayBuf = (uint8_t **)Screen[Enum_OLED3].DisplayBuf,
		.Screen_X = 128,
		.Screen_Y = 64,
	},
	[Enum_OLED4] = {
		.Screen_SetCursor_Callback = Enum_OLED4_SetCursor_Callback,
		.Screen_Update_Callback = Enum_OLED4_Update_Callback,
		.Screen_UpdateArea_Callback = Enum_OLED4_UpdateArea_Callback,
		.DisplayBuf = (uint8_t **)Screen[Enum_OLED4].DisplayBuf,
		.Screen_X = 128,
		.Screen_Y = 64,
	},
	[Enum_OLED5] = {
		.Screen_SetCursor_Callback = Enum_OLED5_SetCursor_Callback,
		.Screen_Update_Callback = Enum_OLED5_Update_Callback,
		.Screen_UpdateArea_Callback = Enum_OLED5_UpdateArea_Callback,
		.DisplayBuf = (uint8_t **)Screen[Enum_OLED5].DisplayBuf,
		.Screen_X = 128,
		.Screen_Y = 64,
	},
};

void Graphic_test(){
	
}
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
