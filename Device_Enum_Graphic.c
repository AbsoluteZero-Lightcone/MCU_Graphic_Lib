/**
  ******************************************************************************
  * @file    Device_Enum_Graphic.c
  * @author  Lightcone
  * @version V1.0.2
  * @date    2024-03-22
  * @brief   图形设备枚举
  ******************************************************************************
  */
#include "Graphic.h"
#include "SSD1306_Driver.h"
typedef enum{
	Graphic_Device_SSD1306,
	Graphic_Device_x,
	Graphic_Device_MAX
}Graphic_Device_Enum;
typedef enum{
	Enum_SSD1306_1,
	Enum_SSD1306_2,
	Enum_SSD1306_3,
	Enum_SSD1306_4,
	//Enum_SSD1306_x,
	Enum_SSD1306_MAX
}Enum_SSD1306;
typedef enum{
	Enum_x_1,
	Enum_x_2,
	Enum_x_3,
	Enum_x_4,
	//Enum_x_x,
	Enum_x_MAX
}Enum_x;
void Hardware_SetCursor_Callback(Device_Enum_Data Device_Enum,uint8_t x,uint8_t y);
void Hardware_Update_Callback(Device_Enum_Data Device_Enum);
void Hardware_UpdateArea_Callback(Device_Enum_Data Device_Enum,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);

// 开辟内存
uint8_t DisplayBuf_Graphic_Device_SSD1306[Enum_SSD1306_MAX][8][128];
uint8_t DisplayBuf_Graphic_Device_x[Enum_x_MAX][8][128];
// 问题：指针存储类型不能表征数据长度，从而不能使用下标访问
// 此处以及Buffer实现都需要改
uint8_t ***DisplayBuf_List[Graphic_Device_MAX] = {// 此处的语义为先读取[]表明是数组，再读取uint8_t *** 表示数组内容是指针
	[Graphic_Device_SSD1306] = (uint8_t***)DisplayBuf_Graphic_Device_SSD1306,
	[Graphic_Device_x] = (uint8_t***)DisplayBuf_Graphic_Device_x,
};

typedef struct{
	uint8_t **DisplayBuf; // 指向实际创建出的显示缓冲区的内存存储区域
	.Screen_X;
	.Screen_Y;
	.Buffer_Page;
	.Buffer_Col;
}Graphic_Buffer;
// 指向内存
Graphic_Buffer Buffer = {
	.DisplayBuf = (uint8_t***)DisplayBuf_List[Graphic_Device_SSD1306][Enum_SSD1306_1],
	.Screen_X    = 128,
	.Screen_Y    = 64,
	.Buffer_Page = 8,
	.Buffer_Col  = 128,
};
Graphic_Buffer Buffer_List[Graphic_Device_MAX] = {};

	
	
	
	
	
	
	
// 不同设备可能数目不同的分配空间问题，使用二级指针（指针数组）实现不同种设备不同数量内存的开辟
Graphic_Object (*Graphic_Object_List)[Graphic_Device_MAX];
Graphic_Object SSD1306_List[Enum_SSD1306_MAX] = {
	[Enum_SSD1306_1] = {
		.Device_Enum = Enum_SSD1306_1,
		.Hardware_SetCursor_Callback  = Hardware_SetCursor_Callback,
		.Hardware_Update_Callback     = Hardware_Update_Callback,
		.Hardware_UpdateArea_Callback = Hardware_UpdateArea_Callback,
		.Buffer = Buffer,
		
	}
};
// 若硬件抽象层未实现区域刷新功能，则使用下面的默认方案：
__weak void Hardware_UpdateArea_Callback(Device_Enum_Data Device_Enum,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);


/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
