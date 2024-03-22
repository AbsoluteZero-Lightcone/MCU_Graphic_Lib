/**
  ******************************************************************************
  * @file    Graphic_Algorithm.h
  * @author  Lightcone
  * @version V1.0.1
  * @date    2024-03-22
  * @brief   基于显示缓冲区数据结构的图形显示算法层
  ******************************************************************************
  */

#ifndef __GRAPHIC_ALGORITHM_H
#define __GRAPHIC_ALGORITHM_H
#include "Graphic.h"

#define Graphic_Draw_Line(Graphic_ptr,P1,P2)\
        Graphic_Draw_Line_DDA(Graphic_ptr,P1,P2)// 默认直线实现算法选择
void Graphic_Draw_Line_DDA(Graphic_TypeDef*Graphic_ptr,Graphic_Point P1,Graphic_Point P2);
void Graphic_Draw_Line_TMP(Graphic_TypeDef*Graphic_ptr,Graphic_Point P1,Graphic_Point P2);
void Graphic_Draw_Line_Bresenham(Graphic_TypeDef*Graphic_ptr,Graphic_Point P1,Graphic_Point P2);

#endif /* __GRAPHIC_ALGORITHM_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
