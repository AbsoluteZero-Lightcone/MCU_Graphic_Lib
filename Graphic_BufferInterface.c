/**
  ******************************************************************************
  * @file    Graphic_BufferInterface.c
  * @author  Lightcone
  * @version V1.0.4
  * @date    2024-03-22
  * @brief   图形显示缓冲区数据结构抽象接口层
  ******************************************************************************
  */
#include "Graphic.h"

// 等效构造函数
Buffer_Point PointXY_to_PointPage(Graphic_Point XY){
	Buffer_Point p = {
		.Col = XY.X,
		.Page = XY.Y/BIT_PER_PAGE,
		.Bias = XY.Y%BIT_PER_PAGE
	};
	return p;
}
Buffer_Point XY_toPointPage(X_Data X,Y_Data Y){
	Buffer_Point p = {
		.Col = X,
		.Page = Y/BIT_PER_PAGE,
		.Bias = Y%BIT_PER_PAGE
	};
	return p;
}
void Graphic_Buffer_WriteXY(Graphic_TypeDef*Graphic_ptr,X_Data X,Y_Data Y,bool val){
	Buffer_Point p = XY_toPointPage(X,Y);
	if(val)Graphic_ptr->DisplayBuf[p.Page][p.Col] |= (1 << p.Bias);
	else Graphic_ptr->DisplayBuf[p.Page][p.Col] &= (1 << p.Bias);
}
bool Graphic_Buffer_ReadXY(Graphic_TypeDef*Graphic_ptr,X_Data X,Y_Data Y){
	Buffer_Point p = XY_toPointPage(X,Y);
	return Graphic_ptr->DisplayBuf[p.Page][p.Col] &= (0x01 << p.Bias);
}
bool isLegalXY(Graphic_TypeDef*Graphic_ptr,X_Data X,Y_Data Y){
	if(
		//X < 0 ||
		X >= Graphic_ptr->Screen_X ||
		//Y < 0 ||
		Y >= Graphic_ptr->Screen_Y
	)return 0;
	return 1;
}

void Graphic_Buffer_WritePoint(Graphic_TypeDef*Graphic_ptr,Graphic_Point XY,bool val){
	Buffer_Point p = PointXY_to_PointPage(XY);
	if(val)Graphic_ptr->DisplayBuf[p.Page][p.Col] |= (1 << p.Bias);
	else Graphic_ptr->DisplayBuf[p.Page][p.Col] &= (1 << p.Bias);
}
bool Graphic_Buffer_ReadPoint(Graphic_TypeDef*Graphic_ptr,Graphic_Point XY){
	Buffer_Point p = PointXY_to_PointPage(XY);
	return Graphic_ptr->DisplayBuf[p.Page][p.Col] &= (0x01 << p.Bias);
}

bool isLegalPoint(Graphic_TypeDef*Graphic_ptr,Graphic_Point XY){
	if(
		//XY.X < 0 ||
		XY.X >= Graphic_ptr->Screen_X ||
		//XY.Y < 0 ||
		XY.Y >= Graphic_ptr->Screen_Y
	)return 0;
	return 1;
}

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
