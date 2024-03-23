/**
  ******************************************************************************
  * @file    Device_Enum_Graphic.c
  * @author  Lightcone
  * @version V1.0.5
  * @date    2024-03-22
  * @brief   图形设备枚举
  ******************************************************************************
  */
#include "Graphic.h"
#include "Device_Enum_Graphic.h"

// 开辟内存
uint8_t DisplayBuf_Graphic_Device_SSD1306[Enum_SSD1306_MAX][8][128];
uint8_t DisplayBuf_Graphic_Device_x[Enum_x_MAX][8][128];


// 指向内存
Graphic_Buffer Buffer_List_SSD1306[Enum_SSD1306_MAX];
Graphic_Buffer Buffer_List_x[Enum_SSD1306_MAX];

void Graphic_Buffer_Init(){
	for(uint8_t i = 0 ; i < Enum_SSD1306_MAX;i++){
		Buffer_List_SSD1306[i].DisplayBuf  = (uint8_t **)DisplayBuf_Graphic_Device_SSD1306[i],
		Buffer_List_SSD1306[i].Screen_X    = 128 ;
		Buffer_List_SSD1306[i].Screen_Y    = 64  ;
		Buffer_List_SSD1306[i].Buffer_Page = 8   ;
		Buffer_List_SSD1306[i].Buffer_Col  = 128 ;
	}
	for(uint8_t i = 0 ; i < Enum_x_MAX;i++){
		Buffer_List_x[i].DisplayBuf  = (uint8_t **)DisplayBuf_Graphic_Device_x[i],
		Buffer_List_x[i].Screen_X    = 128 ;
		Buffer_List_x[i].Screen_Y    = 64  ;
		Buffer_List_x[i].Buffer_Page = 8   ;
		Buffer_List_x[i].Buffer_Col  = 128 ;
	}
}

void Hardware_SetCursor_Callback(Device_Enum_Data Device_Enum,uint8_t x,uint8_t y);
void Hardware_Update_Callback(Device_Enum_Data Device_Enum);
void Hardware_UpdateArea_Callback(Device_Enum_Data Device_Enum,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void Hardware_Clear_Callback(Device_Enum_Data Device_Enum);

Graphic_Object SSD1306_List[Enum_SSD1306_MAX] = {
	[Enum_SSD1306_1] = {
		.Device_Enum = Enum_SSD1306_1,
		.Buffer = &Buffer_List_SSD1306[Enum_SSD1306_1],
		.Hardware_SetCursor_Callback  = Hardware_SetCursor_Callback,
		.Hardware_Update_Callback     = Hardware_Update_Callback,
		.Hardware_UpdateArea_Callback = Hardware_UpdateArea_Callback,
		.Hardware_Clear_Callback      = Hardware_Clear_Callback,
	}
};
// 若硬件抽象层未实现区域刷新功能，则使用下面的默认方案：
__weak void Hardware_UpdateArea_Callback(Device_Enum_Data Device_Enum,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
