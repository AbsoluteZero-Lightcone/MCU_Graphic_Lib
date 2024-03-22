/**
  ******************************************************************************
  * @file    Graphic_BufferInterface.c
  * @author  Lightcone
  * @version V1.0.2
  * @date    2024-03-22
  * @brief   图形显示缓冲区数据结构抽象接口层
  ******************************************************************************
  */
#include "Graphic.h"
// 数据大小设置
typedef uint8_t X_Data;
typedef uint8_t Y_Data;
typedef uint8_t Col_Data;
typedef uint8_t Page_Data;
typedef uint8_t Bias_Data;
typedef uint8_t bool;
typedef uint8_t Count;

typedef struct{
	Col_Data Col;
	Page_Data Page;
	Bias_Data Bias;
}Buffer_Point;

typedef struct{
	X_Data X;
	Y_Data Y;
}Graphic_Point;

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
		X < 0 ||
		X >= Graphic_ptr->Screen_X ||
		Y < 0 ||
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
		XY.X < 0 ||
		XY.X >= Graphic_ptr->Screen_X ||
		XY.Y < 0 ||
		XY.Y >= Graphic_ptr->Screen_Y
	)return 0;
	return 1;
}

#define Graphic_Draw_Line(Graphic_ptr,P1,P2)\
        Graphic_Draw_Line_DDA(Graphic_ptr,P1,P2)// 默认直线实现算法选择
void Graphic_Draw_Line_DDA(Graphic_TypeDef*Graphic_ptr,Graphic_Point P1,Graphic_Point P2);
void Graphic_Draw_Line_TMP(Graphic_TypeDef*Graphic_ptr,Graphic_Point P1,Graphic_Point P2);
void Graphic_Draw_Line_Bresenham(Graphic_TypeDef*Graphic_ptr,Graphic_Point P1,Graphic_Point P2);

void Graphic_Draw_Line_DDA(Graphic_TypeDef*Graphic_ptr,Graphic_Point P1,Graphic_Point P2){
	
}
void Graphic_Draw_Line_TMP(Graphic_TypeDef*Graphic_ptr,Graphic_Point P1,Graphic_Point P2){
	
}
void Graphic_Draw_Line_Bresenham(Graphic_TypeDef*Graphic_ptr,Graphic_Point P1,Graphic_Point P2){
	
}
void Graphic_Draw_Polygon(Graphic_TypeDef*Graphic_ptr,Graphic_Point* Points,Count cnt){
	for(Count i = 0 ; i < cnt ; i++){
		Graphic_Draw_Line(Graphic_ptr,Points[i],Points[(i+1)%cnt]);
	}
}
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
