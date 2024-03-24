/**
  ******************************************************************************
  * @file    Graphic_Algorithm.c
  * @author  Lightcone
  * @version V1.0.5
  * @date    2024-03-25
  * @brief   图形显示算法层，操作图形接口Graphic_Object的显示缓冲区数据结构
  ******************************************************************************
  */
#include "Graphic.h"
#include "Graphic_Algorithm.h"
#include "Graphic_Algorithm_Math.h"
#include "Graphic_Buffer.h"

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

#define DrawPoint(x,y) Graphic_Buffer_SetXY(&Graphic_ptr->Buffer,x,y)
#define ErasePoint(x,y) Graphic_Buffer_ResetXY(&Graphic_ptr->Buffer,x,y)
#define Draw(xy) Graphic_Buffer_SetPoint(&Graphic_ptr->Buffer,xy)
#define Erase(xy) Graphic_Buffer_ResetPoint(&Graphic_ptr->Buffer,xy)

void Graphic_Draw_Line_DDA(Graphic_Object*Graphic_ptr,Graphic_Point P1,Graphic_Point P2){
	
}
void Graphic_Draw_Line_TMP(Graphic_Object*Graphic_ptr,Graphic_Point P1,Graphic_Point P2){
	
}
void Graphic_Draw_Line_Bresenham(Graphic_Object*Graphic_ptr,Graphic_Point P1,Graphic_Point P2){
	if (P1.y == P2.y){//横线
		if (P1.x < P2.x) for(X_Data x = P1.x; x <= P2.x; x++)DrawPoint(x,P1.y);
		else             for(X_Data x = P2.x; x <= P1.x; x++)DrawPoint(x,P1.y);
	}
	if (P1.x == P2.x){//竖线
		if (P1.y < P2.y) for(Y_Data y = P1.y; y <= P2.y; y++)DrawPoint(P1.x,y);
		else             for(Y_Data y = P2.y; y <= P1.y; y++)DrawPoint(P1.x,y);
	}
	//斜线
	int16_t x, y, dx, dy, d, incrE, incrNE, temp;	
	uint8_t yflag = 0, xyflag = 0;
	if (P1.x > P2.x){//0号点x坐标大于1号点x坐标
		/*交换两点坐标*/
		/*交换后不影响画线，但是画线方向由第一、二、三、四象限变为第一、四象限*/
		temp = P1.x; P1.x = P2.x; P2.x = temp;
		temp = P1.y; P1.y = P2.y; P2.y = temp;
	}
	
	if (P1.y > P2.y){//0号点y坐标大于1号点y坐标
		/*将y坐标取负*/
		/*取负后影响画线，但是画线方向由第一、四象限变为第一象限*/
		P1.y = -P1.y;
		P2.y = -P2.y;
		
		/*置标志位yflag，记住当前变换，在后续实际画线时，再将坐标换回来*/
		yflag = 1;
	}
	
	if (P2.y - P1.y > P2.x - P1.x){//画线斜率大于1
		/*将x坐标与y坐标互换*/
		/*互换后影响画线，但是画线方向由第一象限0~90度范围变为第一象限0~45度范围*/
		temp = P1.x; P1.x = P1.y; P1.y = temp;
		temp = P2.x; P2.x = P2.y; P2.y = temp;
		
		/*置标志位xyflag，记住当前变换，在后续实际画线时，再将坐标换回来*/
		xyflag = 1;
	}
	
	/*以下为Bresenham算法画直线*/
	/*算法要求，画线方向必须为第一象限0~45度范围*/
	dx = P2.x - P1.x;
	dy = P2.y - P1.y;
	incrE = 2 * dy;
	incrNE = 2 * (dy - dx);
	d = 2 * dy - dx;
	x = P1.x;
	y = P1.y;
	
	/*画起始点，同时判断标志位，将坐标换回来*/
	if      (yflag && xyflag) DrawPoint(y, -x);
	else if (yflag)           DrawPoint(x, -y);
	else if (xyflag)          DrawPoint(y, x);
	else                      DrawPoint(x, y);
	
	while (x < P2.x){//遍历x轴的每个点
		x ++;
		if (d < 0){//下一个点在当前点东方
			d += incrE;
		}
		else{//下一个点在当前点东北方
			y ++;
			d += incrNE;
		}
		
		/*画每一个点，同时判断标志位，将坐标换回来*/
		if      (yflag && xyflag) DrawPoint(y, -x);
		else if (yflag)           DrawPoint(x, -y);
		else if (xyflag)          DrawPoint(y, x);
		else                      DrawPoint(x, y);
	}	
}



void Graphic_Draw_Polygon(Graphic_Object*Graphic_ptr,Graphic_Point* Points,Count cnt){
	for(Count i = 0 ; i < cnt ; i++){
		Graphic_Draw_Line(Graphic_ptr,Points[i],Points[(i+1)%cnt]);
	}
}
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
