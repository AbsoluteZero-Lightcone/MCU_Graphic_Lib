/**
  ******************************************************************************
  * @file    Graphic_Interface.h
  * @author  Lightcone
  * @version V1.0.0
  * @date    2024-03-21
  * @brief   图形显示硬件接口层
  ******************************************************************************
  */
#include "stdint.h"
#define MAX_CACHE_X 150
#define MAX_CACHE_Y 70
#define COLOR_MODE 3
extern const uint8_t START_X;
extern const uint8_t START_Y;
extern const uint8_t _X;
extern const uint8_t START_Y;
extern const uint8_t COLOR;
extern uint8_t cache[MAX_CACHE_X][MAX_CACHE_Y][COLOR_MODE];

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
