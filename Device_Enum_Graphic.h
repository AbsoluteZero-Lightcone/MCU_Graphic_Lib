/**
  ******************************************************************************
  * @file    Device_Enum_Graphic.h
  * @author  Lightcone
  * @version V1.0.2
  * @date    2024-03-22
  * @brief   图形设备枚举
  ******************************************************************************
  */

#ifndef __DEVICE_ENUM_GRAPHIC_H
#define __DEVICE_ENUM_GRAPHIC_H
#include "Graphic.h"
#include "SSD1306_Driver.h"
#include "74HC138.h"

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
	//Enum_x_x,
	Enum_x_MAX
}Enum_x;
#endif /* __DEVICE_ENUM_GRAPHIC_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
