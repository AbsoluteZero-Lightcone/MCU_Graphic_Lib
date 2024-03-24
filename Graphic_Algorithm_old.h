/**
  ******************************************************************************
  * @file    Graphic_Algorithm_old.h
  * @author  Lightcone & 江协科技
  * @version V1.0.6
  * @date    2024-03-22
  * @brief   江协科技图形显示算法层
  ******************************************************************************
  */

#ifndef __GRAPHIC_ALGORITHM_OLD_H
#define __GRAPHIC_ALGORITHM_OLD_H
#include "Graphic_old.h"

/*参数宏定义*********************/

/*FontSize参数取值*/
/*此参数值不仅用于判断，而且用于计算横向字符偏移，默认值为字体像素宽度*/
#define Graphic_8X16				8
#define Graphic_6X8				6

/*IsFilled参数数值*/
#define Graphic_UNFILLED			0
#define Graphic_FILLED				1



/*********************参数宏定义*/
/************读写私有显存*************/
/*区域控制函数*/
void Graphic_Clear(Graphic_TypeDef*Graphic_ptr);
void Graphic_ClearArea(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void Graphic_Reverse(Graphic_TypeDef*Graphic_ptr);
void Graphic_ReverseArea(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
/*显示函数*/
void Graphic_ShowChar(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, char Char, uint8_t FontSize);
void Graphic_ShowString(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, char *String, uint8_t FontSize);
void Graphic_ShowNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void Graphic_ShowSignedNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, int32_t Number, uint8_t Length, uint8_t FontSize);
void Graphic_ShowHexNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void Graphic_ShowBinNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void Graphic_ShowFloatNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
void Graphic_ShowChinese(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, char *Chinese);
void Graphic_ShowImage(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
void Graphic_Printf(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t FontSize, char *format, ...);
/*绘图函数*/
void Graphic_DrawPoint(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y);
uint8_t Graphic_GetPoint(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y);
void Graphic_DrawLine(Graphic_TypeDef*Graphic_ptr,uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1);
void Graphic_DrawRectangle(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled);
void Graphic_DrawTriangle(Graphic_TypeDef*Graphic_ptr,uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, uint8_t IsFilled);
void Graphic_DrawCircle(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Radius, uint8_t IsFilled);
void Graphic_DrawEllipse(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t A, uint8_t B, uint8_t IsFilled);
void Graphic_DrawArc(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled);


/************读写公共显存*************/
#endif /* __GRAPHIC_ALGORITHM_OLD_H */

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
