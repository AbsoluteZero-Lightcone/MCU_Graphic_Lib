/**
  ******************************************************************************
  * @file    Graphic.h
  * @author  Lightcone
  * @version V1.0.7
  * @date    2024-03-22
  * @brief   图形显示库
  ******************************************************************************
  */

#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <stdint.h>

#define BIT_PER_PAGE 8

typedef struct{
	void (*Screen_SetCursor_Callback)(uint8_t x,uint8_t y);
	void (*Screen_Update_Callback)(void);
	void (*Screen_UpdateArea_Callback)(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
	uint8_t **DisplayBuf;
	uint8_t Screen_X;
	uint8_t Screen_Y;
	uint8_t Screen_Page;
}Graphic_TypeDef;
#define SetCursor(a,b) Graphic_ptr->Screen_SetCursor_Callback(a,b)
#define Update()       Graphic_ptr->Screen_Update_Callback(Graphic_ptr->Display_Buffer);


/************无显存模式*************/

#endif /* __GRAPHIC_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
