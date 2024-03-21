/**
  ******************************************************************************
  * @file    Graphic_Math.h
  * @author  Lightcone
  * @version V1.0.1
  * @date    2024-03-21
  * @brief   图形显示 内部数学库
  ******************************************************************************
  */
#ifndef __GRAPHIC_MATH_H
#define __GRAPHIC_MATH_H

#include <stdint.h>
uint32_t Graphic_Pow(uint32_t X, uint32_t Y);
uint8_t Graphic_pnpoly(uint8_t nvert, int16_t *vertx, int16_t *verty, int16_t testx, int16_t testy);
uint8_t Graphic_IsInAngle(int16_t X, int16_t Y, int16_t StartAngle, int16_t EndAngle);

#endif /* __GRAPHIC_MATH_H */

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
