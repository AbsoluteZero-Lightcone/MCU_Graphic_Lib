/**
  ******************************************************************************
  * @file    Graphic_Buffer.c
  * @author  Lightcone
  * @version V1.2.3
  * @date    2024-03-25
  * @brief   操作图形显示缓冲区数据结构的工具库
  ******************************************************************************
  */
#include "Graphic.h"
#include "Graphic_Buffer.h"
// 等效构造函数
Buffer_Point PointXY_to_PointPage(Graphic_Point XY){
	Buffer_Point p = {
		.Col = XY.x,
		.Page = XY.y/BIT_PER_PAGE,
		.Bias = XY.y%BIT_PER_PAGE
	};
	return p;
}
Buffer_Point XY_toPointPage(X_Data x,Y_Data y){
	Buffer_Point p = {
		.Col = x,
		.Page = y/BIT_PER_PAGE,
		.Bias = y%BIT_PER_PAGE
	};
	return p;
}

void Graphic_Buffer_WriteXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data x,Y_Data y,bool val){
	Buffer_Point p = XY_toPointPage(x,y);
	if(val)*(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) |= (1 << p.Bias);
	else *(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) &= (1 << p.Bias);
}
void Graphic_Buffer_SetXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data x,Y_Data y){
	Buffer_Point p = XY_toPointPage(x,y);
	*(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) |= (1 << p.Bias);
}
void Graphic_Buffer_ResetXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data x,Y_Data y){
	Buffer_Point p = XY_toPointPage(x,y);
	*(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) &= (1 << p.Bias);
}
bool Graphic_Buffer_ReadXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data x,Y_Data y){
	Buffer_Point p = XY_toPointPage(x,y);
	return *(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) &= (0x01 << p.Bias);
}
bool isLegalXY(Graphic_Buffer*Graphic_Buffer_ptr,X_Data x,Y_Data y){
	if(
		//x < 0 ||
		x >= Graphic_Buffer_ptr->Screen_X ||
		//y < 0 ||
		y >= Graphic_Buffer_ptr->Screen_Y
	)return 0;
	return 1;
}

void Graphic_Buffer_WritePoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY,bool val){
	Buffer_Point p = PointXY_to_PointPage(XY);
	if(val)*(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) |= (1 << p.Bias);
	else *(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) &= (1 << p.Bias);
}
void Graphic_Buffer_SetPoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY){
	Buffer_Point p = PointXY_to_PointPage(XY);
	*(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) |= (1 << p.Bias);
}
void Graphic_Buffer_ResetPoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY){
	Buffer_Point p = PointXY_to_PointPage(XY);
	*(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) &= (1 << p.Bias);
}
bool Graphic_Buffer_ReadPoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY){
	Buffer_Point p = PointXY_to_PointPage(XY);
	return *(((uint8_t*)Graphic_Buffer_ptr->DisplayBuf) + p.Page*Graphic_Buffer_ptr->Buffer_Page + p.Col) &= (0x01 << p.Bias);
}

bool isLegalPoint(Graphic_Buffer*Graphic_Buffer_ptr,Graphic_Point XY){
	if(
		//XY.x < 0 ||
		XY.x >= Graphic_Buffer_ptr->Screen_X ||
		//XY.y < 0 ||
		XY.y >= Graphic_Buffer_ptr->Screen_Y
	)return 0;
	return 1;
}

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
