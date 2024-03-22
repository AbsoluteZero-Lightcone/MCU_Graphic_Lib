/**
  ******************************************************************************
  * @file    Device_Enum_Graphic.c
  * @author  Lightcone
  * @version V1.0.1
  * @date    2024-03-22
  * @brief   图形设备枚举
  ******************************************************************************
  */
#include "Graphic.h"
#include "SSD1306_Driver.h"
typedef enum{
	Graphic_Device_SSD1306,
	Graphic_Device_MAX
}Graphic_Device_Enum;
typedef enum{
	Enum_SSD1306_1,
	Enum_SSD1306_2,
	Enum_SSD1306_3,
	Enum_SSD1306_4,
	Enum_SSD1306_5,
	Enum_SSD1306_MAX
}Enum_SSD1306;

void Hardware_SetCursor_Callback(Device_Enum_Data Device_Enum,uint8_t x,uint8_t y);
void Hardware_Update_Callback(Device_Enum_Data Device_Enum);
void Hardware_UpdateArea_Callback(Device_Enum_Data Device_Enum,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);

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
