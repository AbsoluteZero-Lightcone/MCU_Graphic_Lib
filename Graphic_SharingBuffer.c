/**
  ******************************************************************************
  * @file    Graphic_SharingBuffer.c
  * @author  Lightcone
  * @version V1.0.2
  * @date    2024-03-22
  * @brief   共享显示缓冲区，用于内存不足时
  ******************************************************************************
  */
#include "Graphic.h"

// 缓冲区定义例程
uint8_t SharingBufferMem[8][128];
Graphic_Buffer SharingBuffer = {
	.DisplayBuf = (uint8_t **)SharingBufferMem,
	.Screen_X = 128,
	.Screen_Y = 64,
	.Buffer_Page = 64/BIT_PER_PAGE,
	.Buffer_Col = 128
};

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
