/**
  ******************************************************************************
  * @file    Graphic_Algorithm.h
  * @author  Lightcone
  * @version V1.1.0
  * @date    2024-03-25
  * @brief   图形显示算法层，操作显示缓冲区数据结构
  ******************************************************************************
  */
#ifndef __GRAPHIC_ALGORITHM_H
#define __GRAPHIC_ALGORITHM_H
#include "Graphic.h"
#include "Graphic_Buffer.h"

#define Buffer_Draw_Line(Graphic_Buffer_ptr,P1,P2)\
        Buffer_Draw_Line_Bresenham(Graphic_Buffer_ptr,P1,P2)// 默认直线实现算法选择
#define Graphic_Draw_Line(Graphic_ptr,P1,P2)\
        Graphic_Draw_Line_Bresenham(Graphic_ptr,P1,P2)// 默认直线实现算法选择
void Buffer_Draw_Line_DDA(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point P1,Graphic_Point P2);
void Buffer_Draw_Line_TMP(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point P1,Graphic_Point P2);
void Buffer_Draw_Line_Bresenham(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point P1,Graphic_Point P2);
void Buffer_Draw_Polygon(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point* Points,Count cnt);
void Graphic_Draw_Line_DDA(Graphic_Object*Graphic_ptr,Graphic_Point P1,Graphic_Point P2);
void Graphic_Draw_Line_TMP(Graphic_Object*Graphic_ptr,Graphic_Point P1,Graphic_Point P2);
void Graphic_Draw_Line_Bresenham(Graphic_Object*Graphic_ptr,Graphic_Point P1,Graphic_Point P2);
void Graphic_Draw_Polygon(Graphic_Object*Graphic_ptr,Graphic_Point* Points,Count cnt);
#endif /* __GRAPHIC_ALGORITHM_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
