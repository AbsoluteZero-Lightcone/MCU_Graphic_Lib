/**
  ******************************************************************************
  * @file    Device_Enum_SSD1306.h
  * @author  Lightcone
  * @version V1.1.0
  * @date    2024-03-25
  * @brief   图形设备枚举
  ******************************************************************************
  */

#ifndef __DEVICE_ENUM_SSD1306_H
#define __DEVICE_ENUM_SSD1306_H
#include "Graphic.h"
#include "SSD1306_Driver.h"

typedef enum{
	Enum_SSD1306_1,
	Enum_SSD1306_2,
	Enum_SSD1306_3,
	Enum_SSD1306_4,
	Enum_SSD1306_x,
	Enum_SSD1306_MAX
}Enum_SSD1306;

extern SSD1306 Hardware_Graphic_Device_SSD1306[Enum_SSD1306_MAX];
extern Graphic_Object SSD1306_List[Enum_SSD1306_MAX];


#endif /* __DEVICE_ENUM_SSD1306_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
