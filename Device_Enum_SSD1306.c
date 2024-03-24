/**
  ******************************************************************************
  * @file    Device_Enum_SSD1306.c
  * @author  Lightcone
  * @version V1.1.2
  * @date    2024-03-25
  * @brief   图形设备枚举
  ******************************************************************************
  */
#include "Graphic.h"
#include "Device_Enum_SSD1306.h"
#include "Device_Driver_SSD1306.h"

// 开辟内存
uint8_t DisplayBuf_Graphic_Device_SSD1306[Enum_SSD1306_MAX][8][128];

// 硬件层
#define Board_SPI_SCK_GPIO	GPIOA
#define Board_SPI_SCK_Pin	GPIO_Pin_7
#define Board_SPI_SDA_GPIO	GPIOA
#define Board_SPI_SDA_Pin	GPIO_Pin_5
#define Board_SPI_DC_GPIO	GPIOB
#define Board_SPI_DC_Pin	GPIO_Pin_10
const uint8_t Graphic_Device_SSD1306_CS_74HC138_Mapping[Enum_SSD1306_MAX] = {
	[Enum_SSD1306_1] = 1,
	[Enum_SSD1306_2] = 2,
	[Enum_SSD1306_3] = 3,
	[Enum_SSD1306_4] = 4,
	[Enum_SSD1306_x] = 5,
};
// 片选硬件实现
#include "74HC138.h"
_74HC138_TypeDef Graphic_Device_SSD1306_CS_74HC138 = {
		.A_GPIO=GPIOB,.A_Pin=GPIO_Pin_11,
		.B_GPIO=GPIOB,.B_Pin=GPIO_Pin_12,
		.C_GPIO=GPIOB,.C_Pin=GPIO_Pin_13
	};
void Graphic_Device_SSD1306_CS_Callback(Enum_SSD1306 Device_Enum){
	_74HC138_Write(&Graphic_Device_SSD1306_CS_74HC138,Graphic_Device_SSD1306_CS_74HC138_Mapping[Device_Enum]);
}
void SSD1306_Hardware_UpdateArea_Callback(Device_Enum_Data Device_Enum,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void SSD1306_Hardware_Update_Callback(Device_Enum_Data Device_Enum);
void SSD1306_Hardware_Clear_Callback(Device_Enum_Data Device_Enum);
// 设备硬件对象
SSD1306 Hardware_Graphic_Device_SSD1306[Enum_SSD1306_MAX] = {
	[Enum_SSD1306_1] = {
		.D0_GPIO  = Board_SPI_SCK_GPIO,.D0_Pin = Board_SPI_SCK_Pin,
		.D1_GPIO  = Board_SPI_SDA_GPIO,.D1_Pin = Board_SPI_SDA_Pin,
		.DC_GPIO  = Board_SPI_DC_GPIO ,.DC_Pin = Board_SPI_DC_Pin,
		.RES_GPIO = GPIOG             ,.RES_Pin = GPIO_Pin_0,
		.CS_Handler = Graphic_Device_SSD1306_CS_Callback,
		.DisplayBuf = (uint8_t *)DisplayBuf_Graphic_Device_SSD1306[Enum_SSD1306_1]
	},
	[Enum_SSD1306_2] = {
		.D0_GPIO  = Board_SPI_SCK_GPIO,.D0_Pin = Board_SPI_SCK_Pin,
		.D1_GPIO  = Board_SPI_SDA_GPIO,.D1_Pin = Board_SPI_SDA_Pin,
		.DC_GPIO  = Board_SPI_DC_GPIO ,.DC_Pin = Board_SPI_DC_Pin,
		.RES_GPIO = GPIOG             ,.RES_Pin = GPIO_Pin_0,
		.CS_Handler = Graphic_Device_SSD1306_CS_Callback,
		.DisplayBuf = (uint8_t *)DisplayBuf_Graphic_Device_SSD1306[Enum_SSD1306_2]
	},
	[Enum_SSD1306_3] = {
		.D0_GPIO  = Board_SPI_SCK_GPIO,.D0_Pin = Board_SPI_SCK_Pin,
		.D1_GPIO  = Board_SPI_SDA_GPIO,.D1_Pin = Board_SPI_SDA_Pin,
		.DC_GPIO  = Board_SPI_DC_GPIO ,.DC_Pin = Board_SPI_DC_Pin,
		.RES_GPIO = GPIOG             ,.RES_Pin = GPIO_Pin_0,
		.CS_Handler = Graphic_Device_SSD1306_CS_Callback,
		.DisplayBuf = (uint8_t *)DisplayBuf_Graphic_Device_SSD1306[Enum_SSD1306_3]
	},
	[Enum_SSD1306_4] = {
		.D0_GPIO  = Board_SPI_SCK_GPIO,.D0_Pin = Board_SPI_SCK_Pin,
		.D1_GPIO  = Board_SPI_SDA_GPIO,.D1_Pin = Board_SPI_SDA_Pin,
		.DC_GPIO  = Board_SPI_DC_GPIO ,.DC_Pin = Board_SPI_DC_Pin,
		.RES_GPIO = GPIOG             ,.RES_Pin = GPIO_Pin_0,
		.CS_Handler = Graphic_Device_SSD1306_CS_Callback,
		.DisplayBuf = (uint8_t *)DisplayBuf_Graphic_Device_SSD1306[Enum_SSD1306_4]
	},
	[Enum_SSD1306_x] = {
		.D0_GPIO  = Board_SPI_SCK_GPIO,.D0_Pin = Board_SPI_SCK_Pin,
		.D1_GPIO  = Board_SPI_SDA_GPIO,.D1_Pin = Board_SPI_SDA_Pin,
		.DC_GPIO  = Board_SPI_DC_GPIO ,.DC_Pin = Board_SPI_DC_Pin,
		.RES_GPIO = GPIOB             ,.RES_Pin = GPIO_Pin_9,
		.CS_Handler = Graphic_Device_SSD1306_CS_Callback,
		.DisplayBuf = (uint8_t *)DisplayBuf_Graphic_Device_SSD1306[Enum_SSD1306_x]
	}
};
// 图形设备抽象结果
Graphic_Object SSD1306_List[Enum_SSD1306_MAX] = {
	[Enum_SSD1306_1] = {
		.Device_Enum = Enum_SSD1306_1,
		.Buffer = {
			.DisplayBuf  = (uint8_t *)DisplayBuf_Graphic_Device_SSD1306[Enum_SSD1306_1],
			.Screen_X    = 128 ,
			.Screen_Y    = 64  ,
			.Buffer_Page = 8   ,
			.Buffer_Col  = 128 ,
		},
		.Hardware_UpdateArea_Callback = SSD1306_Hardware_UpdateArea_Callback,
		// Optional:
		.Hardware_Update_Callback     = SSD1306_Hardware_Update_Callback,
		.Hardware_Clear_Callback      = SSD1306_Hardware_Clear_Callback,
	}
};


// 若硬件抽象层未实现全局刷新功能，则使用下面的默认方案：
__weak void SSD1306_Hardware_Update_Callback(Device_Enum_Data Device_Enum){
	SSD1306_List[Device_Enum].Hardware_UpdateArea_Callback(Device_Enum,0,0,SSD1306_List[Device_Enum].Buffer.Screen_X,SSD1306_List[Device_Enum].Buffer.Screen_Y);
}
// 若硬件抽象层未实现硬件清屏功能，则使用下面的默认方案：
__weak void SSD1306_Hardware_Clear_Callback(Device_Enum_Data Device_Enum){
	for(Page_Data i = 0 ;i < SSD1306_List[Device_Enum].Buffer.Buffer_Page;i++)
		for(Col_Data j = 0 ; j < SSD1306_List[Device_Enum].Buffer.Buffer_Col ; j++)
			SSD1306_List[Device_Enum].Buffer.DisplayBuf[i*SSD1306_List[Device_Enum].Buffer.Buffer_Col+j] = 0;
	SSD1306_List[Device_Enum].Hardware_Update_Callback(Device_Enum);
}

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
