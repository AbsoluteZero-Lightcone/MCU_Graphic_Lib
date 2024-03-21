/**
  ******************************************************************************
  * @file    Graphic_Algorithm.h
  * @author  Lightcone
  * @version V1.0.3
  * @date    2024-03-21
  * @brief   图形显示算法层
  ******************************************************************************
  */

#ifndef __GRAPHIC_ALGORITHM_H
#define __GRAPHIC_ALGORITHM_H
#include "Graphic.h"

/*显存控制函数*/
void OLED_Clear(Graphic_TypeDef*Graphic_ptr);
void OLED_ClearArea(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void OLED_Reverse(Graphic_TypeDef*Graphic_ptr);
void OLED_ReverseArea(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);

/*显示函数*/
void OLED_ShowChar(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, char Char, uint8_t FontSize);
void OLED_ShowString(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, char *String, uint8_t FontSize);
void OLED_ShowNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowSignedNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, int32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowHexNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowBinNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowFloatNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
void OLED_ShowChinese(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, char *Chinese);
void OLED_ShowImage(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
void OLED_Printf(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t FontSize, char *format, ...);

/*绘图函数*/
void OLED_DrawPoint(uint8_t X, uint8_t Y);
uint8_t OLED_GetPoint(uint8_t X, uint8_t Y);
void OLED_DrawLine(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1);
void OLED_DrawRectangle(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled);
void OLED_DrawTriangle(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, uint8_t IsFilled);
void OLED_DrawCircle(uint8_t X, uint8_t Y, uint8_t Radius, uint8_t IsFilled);
void OLED_DrawEllipse(uint8_t X, uint8_t Y, uint8_t A, uint8_t B, uint8_t IsFilled);
void OLED_DrawArc(uint8_t X, uint8_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled);

#endif /* __GRAPHIC_ALGORITHM_H */

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
