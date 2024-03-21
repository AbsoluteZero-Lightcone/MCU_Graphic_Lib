/**
  ******************************************************************************
  * @file    Graphic_Data.h
  * @author  Lightcone & 江协科技
  * @version V1.0.1
  * @date    2024-03-21
  * @brief   显示数据库
  ******************************************************************************
  */
#ifndef __GRAPHIC_DATA_H
#define __GRAPHIC_DATA_H

#include <stdint.h>

/*中文字符字节宽度*/
#define Graphic_CHN_CHAR_WIDTH			3		//UTF-8编码格式给3，GB2312编码格式给2

/*字模基本单元*/
typedef struct 
{
	char Index[Graphic_CHN_CHAR_WIDTH + 1];	//汉字索引
	uint8_t Data[32];						//字模数据
} ChineseCell_t;

/*ASCII字模数据声明*/
extern const uint8_t Graphic_F8x16[][16];
extern const uint8_t Graphic_F6x8[][6];

/*汉字字模数据声明*/
extern const ChineseCell_t Graphic_CF16x16[];

/*图像数据声明*/
extern const uint8_t Diode[];
/*按照上面的格式，在这个位置加入新的图像数据声明*/
//...

#endif /* __GRAPHIC_DATA_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
