/**
  ******************************************************************************
  * @file    Graphic_Buffer.h
  * @author  Lightcone
  * @version V1.2.3
  * @date    2024-03-25
  * @brief   操作图形显示缓冲区数据结构的工具库
  ******************************************************************************
  */

#ifndef __GRAPHIC_BUFFER_H
#define __GRAPHIC_BUFFER_H

#include "Graphic.h"

// 点对象存储结构
typedef struct{
	Col_Data Col;
	Page_Data Page;
	Bias_Data Bias; // 0~7
}Buffer_Point;

Buffer_Point PointXY_to_PointPage(Graphic_Point XY);
Buffer_Point XY_toPointPage(X_Data X,Y_Data Y);

void Graphic_Buffer_WriteXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data X,Y_Data Y,bool val);
void Graphic_Buffer_SetXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data X,Y_Data Y);
void Graphic_Buffer_ResetXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data X,Y_Data Y);
bool Graphic_Buffer_ReadXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data X,Y_Data Y);
bool isLegalXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data X,Y_Data Y);

void Graphic_Buffer_WritePoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY,bool val);
void Graphic_Buffer_SetPoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY);
void Graphic_Buffer_ResetPoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY);
bool Graphic_Buffer_ReadPoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY);
bool isLegalPoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY);
#endif /* __GRAPHIC_BUFFER_H */

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
