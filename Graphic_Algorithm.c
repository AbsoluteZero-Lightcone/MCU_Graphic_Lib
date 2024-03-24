/**
  ******************************************************************************
  * @file    Graphic_Algorithm.c
  * @author  Lightcone
  * @version V1.0.3
  * @date    2024-03-25
  * @brief   图形显示算法层，操作图形接口Graphic_Object的显示缓冲区数据结构
  ******************************************************************************
  */
#include "Graphic.h"
#include "Graphic_Algorithm.h"
#include "Graphic_Buffer.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

void Graphic_Draw_Line_DDA(Graphic_Object*Graphic_ptr,Graphic_Point P1,Graphic_Point P2){
	
}
void Graphic_Draw_Line_TMP(Graphic_Object*Graphic_ptr,Graphic_Point P1,Graphic_Point P2){
	
}
void Graphic_Draw_Line_Bresenham(Graphic_Object*Graphic_ptr,Graphic_Point P1,Graphic_Point P2){
	
}
void Graphic_Draw_Polygon(Graphic_Object*Graphic_ptr,Graphic_Point* Points,Count cnt){
	for(Count i = 0 ; i < cnt ; i++){
		Graphic_Draw_Line(Graphic_ptr,Points[i],Points[(i+1)%cnt]);
	}
}
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
