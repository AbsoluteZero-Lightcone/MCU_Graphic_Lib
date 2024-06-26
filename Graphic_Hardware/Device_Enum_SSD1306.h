/**
  ******************************************************************************
  * @file    Device_Enum_SSD1306.h
  * @author  Lightcone
  * @version V1.1.5
  * @date    2024-03-25
  * @brief   图形设备枚举
  ******************************************************************************
  */

#ifndef __DEVICE_ENUM_SSD1306_H
#define __DEVICE_ENUM_SSD1306_H
#include "Graphic.h"
#include "Device_Driver_SSD1306.h"

extern SSD1306        Hardware_Graphic_Device_SSD1306[Enum_SSD1306_MAX]; // 硬件对象
extern Graphic_Object SSD1306_List[Enum_SSD1306_MAX];                    // 接口对象

void Graphic_SSD1306_Init(void);

void SSD1306_Hardware_UpdateArea_Callback(Device_Enum_Data Device_Enum,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void SSD1306_Hardware_Update_Callback(Device_Enum_Data Device_Enum);
void SSD1306_Hardware_Clear_Callback(Device_Enum_Data Device_Enum);

#endif /* __DEVICE_ENUM_SSD1306_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
