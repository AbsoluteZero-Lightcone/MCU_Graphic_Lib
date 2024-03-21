/**
  ******************************************************************************
  * @file    Graphic_BufferInterface.c
  * @author  Lightcone
  * @version V1.0.1
  * @date    2024-03-22
  * @brief   图形显示缓冲区数据结构抽象接口层
  ******************************************************************************
  */
#include "Graphic.h"

typedef struct{
	uint8_t Col;
	uint8_t Page;
	uint8_t bias;
}Point_Page;
typedef struct{
	uint8_t X;
	uint8_t Y;
}Point_XY;
// 等效构造函数
Point_Page PointXY_to_PointPage(Point_XY XY){
	Point_Page p = {
		.Col = XY.X,
		.Page = XY.Y/BIT_PER_PAGE,
		.bias = XY.Y%BIT_PER_PAGE
	};
	return p;
}
Point_Page XY_toPointPage(uint8_t X,uint8_t Y){
	Point_Page p = {
		.Col = X,
		.Page = Y/BIT_PER_PAGE,
		.bias = Y%BIT_PER_PAGE
	};
	return p;
}
void Graphic_Buffer_WritePoint(Graphic_TypeDef*Graphic_ptr,uint8_t X,uint8_t Y,uint8_t val){
	Point_Page p = XY_toPointPage(X,Y);
	if(val)Graphic_ptr->DisplayBuf[p.Page][p.Col] |= (1 << p.bias);
	else Graphic_ptr->DisplayBuf[p.Page][p.Col] &= (1 << p.bias);
}
uint8_t Graphic_Buffer_ReadPoint(Graphic_TypeDef*Graphic_ptr,uint8_t X,uint8_t Y){
	Point_Page p = XY_toPointPage(X,Y);
	return Graphic_ptr->DisplayBuf[p.Page][p.Col] &= (0x01 << p.bias);
}
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
