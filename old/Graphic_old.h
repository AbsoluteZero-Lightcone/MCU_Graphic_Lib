/**
  ******************************************************************************
  * @file    Graphic_old.h
  * @author  Lightcone
  * @version V1.3.2
  * @date    2024-03-24
  * @brief   图形显示库
  ******************************************************************************
  */

#ifndef __GRAPHIC_OLD_H
#define __GRAPHIC_OLD_H

#include <stdint.h>
#define BIT_PER_PAGE 8

// old
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


#endif /* __GRAPHIC_OLD_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
