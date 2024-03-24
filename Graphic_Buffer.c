/**
  ******************************************************************************
  * @file    Graphic_Buffer.c
  * @author  Lightcone
  * @version V1.2.1
  * @date    2024-03-25
  * @brief   操作图形显示缓冲区数据结构的工具库
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

void Graphic_Buffer_WriteXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data X,Y_Data Y,bool val){
	Buffer_Point p = XY_toPointPage(X,Y);
	if(val)*(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) |= (1 << p.Bias);
	else *(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) &= (1 << p.Bias);
}
bool Graphic_Buffer_ReadXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data X,Y_Data Y){
	Buffer_Point p = XY_toPointPage(X,Y);
	return *(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) &= (0x01 << p.Bias);
}
bool isLegalXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data X,Y_Data Y){
	if(
		//X < 0 ||
		X >= Graphic_Buffer_ptr->Screen_X ||
		//Y < 0 ||
		Y >= Graphic_Buffer_ptr->Screen_Y
	)return 0;
	return 1;
}

void Graphic_Buffer_WritePoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY,bool val){
	Buffer_Point p = PointXY_to_PointPage(XY);
	if(val)*(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) |= (1 << p.Bias);
	else *(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) &= (1 << p.Bias);
}
bool Graphic_Buffer_ReadPoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY){
	Buffer_Point p = PointXY_to_PointPage(XY);
	return *(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) &= (0x01 << p.Bias);
}

bool isLegalPoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY){
	if(
		//XY.X < 0 ||
		XY.X >= Graphic_Buffer_ptr->Screen_X ||
		//XY.Y < 0 ||
		XY.Y >= Graphic_Buffer_ptr->Screen_Y
	)return 0;
	return 1;
}

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
