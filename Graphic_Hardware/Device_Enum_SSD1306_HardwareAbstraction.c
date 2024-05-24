/**
  ******************************************************************************
  * @file    Device_Enum_SSD1306_HardwareAbstraction.c
  * @author  Lightcone
  * @version V1.1.2
  * @date    2024-03-25
  * @brief   图形设备枚举
  ******************************************************************************
  */
#include "Device_Enum_SSD1306.h"
void SSD1306_Hardware_UpdateArea_Callback(Device_Enum_Data Device_Enum,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height){
		SSD1306_UpdateArea(&Hardware_Graphic_Device_SSD1306[Device_Enum],X,Y,Width,Height);
	}
void SSD1306_Hardware_Update_Callback(Device_Enum_Data Device_Enum){
	SSD1306_List[Device_Enum].Hardware_UpdateArea_Callback(Device_Enum,0,0,SSD1306_List[Device_Enum].Buffer.Screen_X,SSD1306_List[Device_Enum].Buffer.Screen_Y);
}
void SSD1306_Hardware_Clear_Callback(Device_Enum_Data Device_Enum){
	for(Page_Data i = 0 ;i < SSD1306_List[Device_Enum].Buffer.Buffer_Page;i++)
		for(Col_Data j = 0 ; j < SSD1306_List[Device_Enum].Buffer.Buffer_Col ; j++)
			SSD1306_List[Device_Enum].Buffer.DisplayBuf[i*SSD1306_List[Device_Enum].Buffer.Buffer_Col+j] = 0;
	SSD1306_List[Device_Enum].Hardware_Update_Callback(Device_Enum);
}
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
