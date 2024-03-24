/**
  ******************************************************************************
  * @file    Device_Enum_Graphic.c
  * @author  Lightcone
  * @version V1.0.7
  * @date    2024-03-24
  * @brief   图形设备枚举
  ******************************************************************************
  */
#include "Graphic.h"
#include "Device_Enum_Graphic.h"
#include "SSD1306_Driver.h"

// 开辟内存
uint8_t DisplayBuf_Graphic_Device_SSD1306[Enum_SSD1306_MAX][8][128];
uint8_t DisplayBuf_Graphic_Device_x[Enum_x_MAX][8][128];

void SSD1306_Hardware_UpdateArea_Callback(Device_Enum_Data Device_Enum,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void SSD1306_Hardware_Update_Callback(Device_Enum_Data Device_Enum);
void SSD1306_Hardware_Clear_Callback(Device_Enum_Data Device_Enum);

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
void SSD1306_Hardware_UpdateArea_Callback(Device_Enum_Data Device_Enum,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height){
}

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
