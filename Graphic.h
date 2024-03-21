/**
  ******************************************************************************
  * @file    Graphic.h
  * @author  Lightcone
  * @version V1.0.3
  * @date    2024-03-21
  * @brief   图形显示库
  ******************************************************************************
  */

#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <stdint.h>

/*参数宏定义*********************/

/*FontSize参数取值*/
/*此参数值不仅用于判断，而且用于计算横向字符偏移，默认值为字体像素宽度*/
#define OLED_8X16				8
#define OLED_6X8				6

/*IsFilled参数数值*/
#define OLED_UNFILLED			0
#define OLED_FILLED				1

/*********************参数宏定义*/
typedef struct{
	void (*Screen_SetCursor_Callback)(uint8_t x,uint8_t y);
	void (*Screen_Update_Callback)(void);
	void (*Screen_UpdateArea_Callback)(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
	uint8_t **DisplayBuf;
	uint8_t Screen_X;
	uint8_t Screen_Y;
}Graphic_TypeDef;
#define SetCursor(a,b) Graphic_ptr->Screen_SetCursor_Callback(a,b)
#define Update()       Graphic_ptr->Screen_Update_Callback(Graphic_ptr->Display_Buffer);



#endif /* __GRAPHIC_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
