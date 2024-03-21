/**
  ******************************************************************************
  * @file    Graphic_Algorithm.c
  * @author  Lightcone
  * @version V1.0.5
  * @date    2024-03-21
  * @brief   图形显示算法层
  ******************************************************************************
  */
#include "Graphic.h"
#include "Graphic_Math.h"
#include "Graphic_Data.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
//Graphic_ptr->Screen_Y ->  Graphic_ptr->Screen_Y
//Graphic_ptr->Screen_Y-1 ->  Graphic_ptr->Screen_Y-1
//8 ->  Graphic_ptr->Screen_Page
//Graphic_ptr->Screen_Page-1 ->  Graphic_ptr->Screen_Page-1
//Graphic_ptr->Screen_X   Graphic_ptr->Screen_X
//Graphic_ptr->Screen_X-1   Graphic_ptr->Screen_X-1

#define BIT_PER_PAGE 8

/**
  * 函    数：将OLED显存数组全部清零
  * 参    数：无
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_Clear(Graphic_TypeDef*Graphic_ptr)
{
	uint8_t i, j;
	for (j = 0; j < Graphic_ptr->Screen_Page; j ++)				//遍历8页
	{
		for (i = 0; i < Graphic_ptr->Screen_X; i ++)			//遍历Graphic_ptr->Screen_X列
		{
			Graphic_ptr->DisplayBuf[j][i] = 0x00;	//将显存数组数据全部清零
		}
	}
}

/**
  * 函    数：将OLED显存数组部分清零
  * 参    数：X 指定区域左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定区域左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Width 指定区域的宽度，范围：0~Graphic_ptr->Screen_X
  * 参    数：Height 指定区域的高度，范围：0~Graphic_ptr->Screen_Y
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_ClearArea(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
	uint8_t i, j;
	
	/*参数检查，保证指定区域不会超出屏幕范围*/
	if (X > Graphic_ptr->Screen_X-1) {return;}
	if (Y > Graphic_ptr->Screen_Y-1) {return;}
	if (X + Width > Graphic_ptr->Screen_X) {Width = Graphic_ptr->Screen_X - X;}
	if (Y + Height > Graphic_ptr->Screen_Y) {Height = Graphic_ptr->Screen_Y - Y;}
	
	for (j = Y; j < Y + Height; j ++)		//遍历指定页
	{
		for (i = X; i < X + Width; i ++)	//遍历指定列
		{
			Graphic_ptr->DisplayBuf[j / BIT_PER_PAGE][i] &= ~(0x01 << (j % 8));	//将显存数组指定数据清零
		}
	}
}

/**
  * 函    数：将OLED显存数组全部取反
  * 参    数：无
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_Reverse(Graphic_TypeDef*Graphic_ptr)
{
	uint8_t i, j;
	for (j = 0; j < Graphic_ptr->Screen_Page; j ++)				//遍历8页
	{
		for (i = 0; i < Graphic_ptr->Screen_X; i ++)			//遍历Graphic_ptr->Screen_X列
		{
			Graphic_ptr->DisplayBuf[j][i] ^= 0xFF;	//将显存数组数据全部取反
		}
	}
}
	
/**
  * 函    数：将OLED显存数组部分取反
  * 参    数：X 指定区域左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定区域左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Width 指定区域的宽度，范围：0~Graphic_ptr->Screen_X
  * 参    数：Height 指定区域的高度，范围：0~Graphic_ptr->Screen_Y
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_ReverseArea(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
	uint8_t i, j;
	
	/*参数检查，保证指定区域不会超出屏幕范围*/
	if (X > Graphic_ptr->Screen_X-1) {return;}
	if (Y > Graphic_ptr->Screen_Y-1) {return;}
	if (X + Width > Graphic_ptr->Screen_X) {Width = Graphic_ptr->Screen_X - X;}
	if (Y + Height > Graphic_ptr->Screen_Y) {Height = Graphic_ptr->Screen_Y - Y;}
	
	for (j = Y; j < Y + Height; j ++)		//遍历指定页
	{
		for (i = X; i < X + Width; i ++)	//遍历指定列
		{
			Graphic_ptr->DisplayBuf[j / BIT_PER_PAGE][i] ^= 0x01 << (j % 8);	//将显存数组指定数据取反
		}
	}
}

/**
  * 函    数：OLED显示一个字符
  * 参    数：X 指定字符左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定字符左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Char 指定要显示的字符，范围：ASCII码可见字符
  * 参    数：FontSize 指定字体大小
  *           范围：Graphic_8X16		宽8像素，高16像素
  *                 Graphic_6X8		宽6像素，高8像素
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_ShowChar(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, char Char, uint8_t FontSize)
{
	if (FontSize == Graphic_8X16)		//字体为宽8像素，高16像素
	{
		/*将ASCII字模库Graphic_F8x16的指定数据以8*16的图像格式显示*/
		Graphic_ShowImage(Graphic_ptr,X, Y, 8, 16, Graphic_F8x16[Char - ' ']);
	}
	else if(FontSize == Graphic_6X8)	//字体为宽6像素，高8像素
	{
		/*将ASCII字模库Graphic_F6x8的指定数据以6*8的图像格式显示*/
		Graphic_ShowImage(Graphic_ptr,X, Y, 6, 8, Graphic_F6x8[Char - ' ']);
	}
}

/**
  * 函    数：OLED显示字符串
  * 参    数：X 指定字符串左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定字符串左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：String 指定要显示的字符串，范围：ASCII码可见字符组成的字符串
  * 参    数：FontSize 指定字体大小
  *           范围：Graphic_8X16		宽8像素，高16像素
  *                 Graphic_6X8		宽6像素，高8像素
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_ShowString(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, char *String, uint8_t FontSize)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)		//遍历字符串的每个字符
	{
		/*调用Graphic_ShowChar函数，依次显示每个字符*/
		Graphic_ShowChar(Graphic_ptr,X + i * FontSize, Y, String[i], FontSize);
	}
}

/**
  * 函    数：OLED显示数字（十进制，正整数）
  * 参    数：X 指定数字左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定数字左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Number 指定要显示的数字，范围：0~4294967295
  * 参    数：Length 指定数字的长度，范围：0~10
  * 参    数：FontSize 指定字体大小
  *           范围：Graphic_8X16		宽8像素，高16像素
  *                 Graphic_6X8		宽6像素，高8像素
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_ShowNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
	uint8_t i;
	for (i = 0; i < Length; i++)		//遍历数字的每一位							
	{
		/*调用Graphic_ShowChar函数，依次显示每个数字*/
		/*Number / Graphic_Pow(10, Length - i - 1) % 10 可以十进制提取数字的每一位*/
		/*+ '0' 可将数字转换为字符格式*/
		Graphic_ShowChar(Graphic_ptr,X + i * FontSize, Y, Number / Graphic_Pow(10, Length - i - 1) % 10 + '0', FontSize);
	}
}

/**
  * 函    数：OLED显示有符号数字（十进制，整数）
  * 参    数：X 指定数字左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定数字左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Number 指定要显示的数字，范围：-2147483648~2147483647
  * 参    数：Length 指定数字的长度，范围：0~10
  * 参    数：FontSize 指定字体大小
  *           范围：Graphic_8X16		宽8像素，高16像素
  *                 Graphic_6X8		宽6像素，高8像素
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_ShowSignedNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, int32_t Number, uint8_t Length, uint8_t FontSize)
{
	uint8_t i;
	uint32_t Number1;
	
	if (Number >= 0)						//数字大于等于0
	{
		Graphic_ShowChar(Graphic_ptr,X, Y, '+', FontSize);	//显示+号
		Number1 = Number;					//Number1直接等于Number
	}
	else									//数字小于0
	{
		Graphic_ShowChar(Graphic_ptr,X, Y, '-', FontSize);	//显示-号
		Number1 = -Number;					//Number1等于Number取负
	}
	
	for (i = 0; i < Length; i++)			//遍历数字的每一位								
	{
		/*调用Graphic_ShowChar函数，依次显示每个数字*/
		/*Number1 / Graphic_Pow(10, Length - i - 1) % 10 可以十进制提取数字的每一位*/
		/*+ '0' 可将数字转换为字符格式*/
		Graphic_ShowChar(Graphic_ptr,X + (i + 1) * FontSize, Y, Number1 / Graphic_Pow(10, Length - i - 1) % 10 + '0', FontSize);
	}
}

/**
  * 函    数：OLED显示十六进制数字（十六进制，正整数）
  * 参    数：X 指定数字左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定数字左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Number 指定要显示的数字，范围：0x00000000~0xFFFFFFFF
  * 参    数：Length 指定数字的长度，范围：0~8
  * 参    数：FontSize 指定字体大小
  *           范围：Graphic_8X16		宽8像素，高16像素
  *                 Graphic_6X8		宽6像素，高8像素
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_ShowHexNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)		//遍历数字的每一位
	{
		/*以十六进制提取数字的每一位*/
		SingleNumber = Number / Graphic_Pow(16, Length - i - 1) % 16;
		
		if (SingleNumber < 10)			//单个数字小于10
		{
			/*调用Graphic_ShowChar函数，显示此数字*/
			/*+ '0' 可将数字转换为字符格式*/
			Graphic_ShowChar(Graphic_ptr,X + i * FontSize, Y, SingleNumber + '0', FontSize);
		}
		else							//单个数字大于10
		{
			/*调用Graphic_ShowChar函数，显示此数字*/
			/*+ 'A' 可将数字转换为从A开始的十六进制字符*/
			Graphic_ShowChar(Graphic_ptr,X + i * FontSize, Y, SingleNumber - 10 + 'A', FontSize);
		}
	}
}

/**
  * 函    数：OLED显示二进制数字（二进制，正整数）
  * 参    数：X 指定数字左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定数字左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Number 指定要显示的数字，范围：0x00000000~0xFFFFFFFF
  * 参    数：Length 指定数字的长度，范围：0~16
  * 参    数：FontSize 指定字体大小
  *           范围：Graphic_8X16		宽8像素，高16像素
  *                 Graphic_6X8		宽6像素，高8像素
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_ShowBinNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
	uint8_t i;
	for (i = 0; i < Length; i++)		//遍历数字的每一位	
	{
		/*调用Graphic_ShowChar函数，依次显示每个数字*/
		/*Number / Graphic_Pow(2, Length - i - 1) % 2 可以二进制提取数字的每一位*/
		/*+ '0' 可将数字转换为字符格式*/
		Graphic_ShowChar(Graphic_ptr,X + i * FontSize, Y, Number / Graphic_Pow(2, Length - i - 1) % 2 + '0', FontSize);
	}
}

/**
  * 函    数：OLED显示浮点数字（十进制，小数）
  * 参    数：X 指定数字左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定数字左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Number 指定要显示的数字，范围：-4294967295.0~4294967295.0
  * 参    数：IntLength 指定数字的整数位长度，范围：0~10
  * 参    数：FraLength 指定数字的小数位长度，范围：0~9，小数进行四舍五入显示
  * 参    数：FontSize 指定字体大小
  *           范围：Graphic_8X16		宽8像素，高16像素
  *                 Graphic_6X8		宽6像素，高8像素
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_ShowFloatNum(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize)
{
	uint32_t PowNum, IntNum, FraNum;
	
	if (Number >= 0)						//数字大于等于0
	{
		Graphic_ShowChar(Graphic_ptr,X, Y, '+', FontSize);	//显示+号
	}
	else									//数字小于0
	{
		Graphic_ShowChar(Graphic_ptr,X, Y, '-', FontSize);	//显示-号
		Number = -Number;					//Number取负
	}
	
	/*提取整数部分和小数部分*/
	IntNum = Number;						//直接赋值给整型变量，提取整数
	Number -= IntNum;						//将Number的整数减掉，防止之后将小数乘到整数时因数过大造成错误
	PowNum = Graphic_Pow(10, FraLength);		//根据指定小数的位数，确定乘数
	FraNum = round(Number * PowNum);		//将小数乘到整数，同时四舍五入，避免显示误差
	IntNum += FraNum / PowNum;				//若四舍五入造成了进位，则需要再加给整数
	
	/*显示整数部分*/
	Graphic_ShowNum(Graphic_ptr,X + FontSize, Y, IntNum, IntLength, FontSize);
	
	/*显示小数点*/
	Graphic_ShowChar(Graphic_ptr,X + (IntLength + 1) * FontSize, Y, '.', FontSize);
	
	/*显示小数部分*/
	Graphic_ShowNum(Graphic_ptr,X + (IntLength + 2) * FontSize, Y, FraNum, FraLength, FontSize);
}

/**
  * 函    数：OLED显示汉字串
  * 参    数：X 指定汉字串左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定汉字串左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Chinese 指定要显示的汉字串，范围：必须全部为汉字或者全角字符，不要加入任何半角字符
  *           显示的汉字需要在Graphic_Data.c里的Graphic_CF16x16数组定义
  *           未找到指定汉字时，会显示默认图形（一个方框，内部一个问号）
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_ShowChinese(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, char *Chinese)
{
	uint8_t pChinese = 0;
	uint8_t pIndex;
	uint8_t i;
	char SingleChinese[Graphic_CHN_CHAR_WIDTH + 1] = {0};
	
	for (i = 0; Chinese[i] != '\0'; i ++)		//遍历汉字串
	{
		SingleChinese[pChinese] = Chinese[i];	//提取汉字串数据到单个汉字数组
		pChinese ++;							//计次自增
		
		/*当提取次数到达Graphic_CHN_CHAR_WIDTH时，即代表提取到了一个完整的汉字*/
		if (pChinese >= Graphic_CHN_CHAR_WIDTH)
		{
			pChinese = 0;		//计次归零
			
			/*遍历整个汉字字模库，寻找匹配的汉字*/
			/*如果找到最后一个汉字（定义为空字符串），则表示汉字未在字模库定义，停止寻找*/
			for (pIndex = 0; strcmp(Graphic_CF16x16[pIndex].Index, "") != 0; pIndex ++)
			{
				/*找到匹配的汉字*/
				if (strcmp(Graphic_CF16x16[pIndex].Index, SingleChinese) == 0)
				{
					break;		//跳出循环，此时pIndex的值为指定汉字的索引
				}
			}
			
			/*将汉字字模库Graphic_CF16x16的指定数据以16*16的图像格式显示*/
			Graphic_ShowImage(Graphic_ptr,X + ((i + 1) / Graphic_CHN_CHAR_WIDTH - 1) * 16, Y, 16, 16, Graphic_CF16x16[pIndex].Data);
		}
	}
}

/**
  * 函    数：OLED显示图像
  * 参    数：X 指定图像左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定图像左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Width 指定图像的宽度，范围：0~Graphic_ptr->Screen_X
  * 参    数：Height 指定图像的高度，范围：0~Graphic_ptr->Screen_Y
  * 参    数：Image 指定要显示的图像
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_ShowImage(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image)
{
	uint8_t i, j;
	
	/*参数检查，保证指定图像不会超出屏幕范围*/
	if (X > Graphic_ptr->Screen_X-1) {return;}
	if (Y > Graphic_ptr->Screen_Y-1) {return;}
	
	/*将图像所在区域清空*/
	Graphic_ClearArea(Graphic_ptr,X, Y, Width, Height);
	
	/*遍历指定图像涉及的相关页*/
	/*(Height - 1) / 8 + 1的目的是Height / 8并向上取整*/
	for (j = 0; j < (Height - 1) / 8 + 1; j ++)
	{
		/*遍历指定图像涉及的相关列*/
		for (i = 0; i < Width; i ++)
		{
			/*超出边界，则跳过显示*/
			if (X + i > Graphic_ptr->Screen_X-1) {break;}
			if (Y / 8 + j > Graphic_ptr->Screen_Page-1) {return;}
			
			/*显示图像在当前页的内容*/
			Graphic_ptr->DisplayBuf[Y / 8 + j][X + i] |= Image[j * Width + i] << (Y % 8);
			
			/*超出边界，则跳过显示*/
			/*使用continue的目的是，下一页超出边界时，上一页的后续内容还需要继续显示*/
			if (Y / 8 + j + 1 > Graphic_ptr->Screen_Page-1) {continue;}
			
			/*显示图像在下一页的内容*/
			Graphic_ptr->DisplayBuf[Y / 8 + j + 1][X + i] |= Image[j * Width + i] >> (8 - Y % 8);
		}
	}
}

/**
  * 函    数：OLED使用printf函数打印格式化字符串
  * 参    数：X 指定格式化字符串左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定格式化字符串左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：FontSize 指定字体大小
  *           范围：Graphic_8X16		宽8像素，高16像素
  *                 Graphic_6X8		宽6像素，高8像素
  * 参    数：format 指定要显示的格式化字符串，范围：ASCII码可见字符组成的字符串
  * 参    数：... 格式化字符串参数列表
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_Printf(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t FontSize, char *format, ...)
{
	char String[30];						//定义字符数组
	va_list arg;							//定义可变参数列表数据类型的变量arg
	va_start(arg, format);					//从format开始，接收参数列表到arg变量
	vsprintf(String, format, arg);			//使用vsprintf打印格式化字符串和参数列表到字符数组中
	va_end(arg);							//结束变量arg
	Graphic_ShowString(Graphic_ptr,X, Y, String, FontSize);//OLED显示字符数组（字符串）
}

/**
  * 函    数：OLED在指定位置画一个点
  * 参    数：X 指定点的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定点的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_DrawPoint(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y)
{
	/*参数检查，保证指定位置不会超出屏幕范围*/
	if (X > Graphic_ptr->Screen_X-1) {return;}
	if (Y > Graphic_ptr->Screen_Y-1) {return;}
	
	/*将显存数组指定位置的一个Bit数据置1*/
	Graphic_ptr->DisplayBuf[Y / 8][X] |= 0x01 << (Y % 8);
}

/**
  * 函    数：OLED获取指定位置点的值
  * 参    数：X 指定点的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定点的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 返 回 值：指定位置点是否处于点亮状态，1：点亮，0：熄灭
  */
uint8_t Graphic_GetPoint(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y)
{
	/*参数检查，保证指定位置不会超出屏幕范围*/
	if (X > Graphic_ptr->Screen_X-1) {return 0;}
	if (Y > Graphic_ptr->Screen_Y-1) {return 0;}
	
	/*判断指定位置的数据*/
	if (Graphic_ptr->DisplayBuf[Y / 8][X] & 0x01 << (Y % 8))
	{
		return 1;	//为1，返回1
	}
	
	return 0;		//否则，返回0
}

/**
  * 函    数：OLED画线
  * 参    数：X0 指定一个端点的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y0 指定一个端点的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：X1 指定另一个端点的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y1 指定另一个端点的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_DrawLine(Graphic_TypeDef*Graphic_ptr,uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1)
{
	int16_t x, y, dx, dy, d, incrE, incrNE, temp;
	int16_t x0 = X0, y0 = Y0, x1 = X1, y1 = Y1;
	uint8_t yflag = 0, xyflag = 0;
	
	if (y0 == y1)		//横线单独处理
	{
		/*0号点X坐标大于1号点X坐标，则交换两点X坐标*/
		if (x0 > x1) {temp = x0; x0 = x1; x1 = temp;}
		
		/*遍历X坐标*/
		for (x = x0; x <= x1; x ++)
		{
			Graphic_DrawPoint(Graphic_ptr,x, y0);	//依次画点
		}
	}
	else if (x0 == x1)	//竖线单独处理
	{
		/*0号点Y坐标大于1号点Y坐标，则交换两点Y坐标*/
		if (y0 > y1) {temp = y0; y0 = y1; y1 = temp;}
		
		/*遍历Y坐标*/
		for (y = y0; y <= y1; y ++)
		{
			Graphic_DrawPoint(Graphic_ptr,x0, y);	//依次画点
		}
	}
	else				//斜线
	{
		/*使用Bresenham算法画直线，可以避免耗时的浮点运算，效率更高*/
		/*参考文档：https://www.cs.montana.edu/courses/spring2009/425/dslectures/Bresenham.pdf*/
		/*参考教程：https://www.bilibili.com/video/BV1364y1d7Lo*/
		
		if (x0 > x1)	//0号点X坐标大于1号点X坐标
		{
			/*交换两点坐标*/
			/*交换后不影响画线，但是画线方向由第一、二、三、四象限变为第一、四象限*/
			temp = x0; x0 = x1; x1 = temp;
			temp = y0; y0 = y1; y1 = temp;
		}
		
		if (y0 > y1)	//0号点Y坐标大于1号点Y坐标
		{
			/*将Y坐标取负*/
			/*取负后影响画线，但是画线方向由第一、四象限变为第一象限*/
			y0 = -y0;
			y1 = -y1;
			
			/*置标志位yflag，记住当前变换，在后续实际画线时，再将坐标换回来*/
			yflag = 1;
		}
		
		if (y1 - y0 > x1 - x0)	//画线斜率大于1
		{
			/*将X坐标与Y坐标互换*/
			/*互换后影响画线，但是画线方向由第一象限0~90度范围变为第一象限0~45度范围*/
			temp = x0; x0 = y0; y0 = temp;
			temp = x1; x1 = y1; y1 = temp;
			
			/*置标志位xyflag，记住当前变换，在后续实际画线时，再将坐标换回来*/
			xyflag = 1;
		}
		
		/*以下为Bresenham算法画直线*/
		/*算法要求，画线方向必须为第一象限0~45度范围*/
		dx = x1 - x0;
		dy = y1 - y0;
		incrE = 2 * dy;
		incrNE = 2 * (dy - dx);
		d = 2 * dy - dx;
		x = x0;
		y = y0;
		
		/*画起始点，同时判断标志位，将坐标换回来*/
		if (yflag && xyflag){Graphic_DrawPoint(Graphic_ptr,y, -x);}
		else if (yflag)		{Graphic_DrawPoint(Graphic_ptr,x, -y);}
		else if (xyflag)	{Graphic_DrawPoint(Graphic_ptr,y, x);}
		else				{Graphic_DrawPoint(Graphic_ptr,x, y);}
		
		while (x < x1)		//遍历X轴的每个点
		{
			x ++;
			if (d < 0)		//下一个点在当前点东方
			{
				d += incrE;
			}
			else			//下一个点在当前点东北方
			{
				y ++;
				d += incrNE;
			}
			
			/*画每一个点，同时判断标志位，将坐标换回来*/
			if (yflag && xyflag){Graphic_DrawPoint(Graphic_ptr,y, -x);}
			else if (yflag)		{Graphic_DrawPoint(Graphic_ptr,x, -y);}
			else if (xyflag)	{Graphic_DrawPoint(Graphic_ptr,y, x);}
			else				{Graphic_DrawPoint(Graphic_ptr,x, y);}
		}	
	}
}

/**
  * 函    数：OLED矩形
  * 参    数：X 指定矩形左上角的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定矩形左上角的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Width 指定矩形的宽度，范围：0~Graphic_ptr->Screen_X
  * 参    数：Height 指定矩形的高度，范围：0~Graphic_ptr->Screen_Y
  * 参    数：IsFilled 指定矩形是否填充
  *           范围：Graphic_UNFILLED		不填充
  *                 Graphic_FILLED			填充
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_DrawRectangle(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled)
{
	uint8_t i, j;
	if (!IsFilled)		//指定矩形不填充
	{
		/*遍历上下X坐标，画矩形上下两条线*/
		for (i = X; i < X + Width; i ++)
		{
			Graphic_DrawPoint(Graphic_ptr,i, Y);
			Graphic_DrawPoint(Graphic_ptr,i, Y + Height - 1);
		}
		/*遍历左右Y坐标，画矩形左右两条线*/
		for (i = Y; i < Y + Height; i ++)
		{
			Graphic_DrawPoint(Graphic_ptr,X, i);
			Graphic_DrawPoint(Graphic_ptr,X + Width - 1, i);
		}
	}
	else				//指定矩形填充
	{
		/*遍历X坐标*/
		for (i = X; i < X + Width; i ++)
		{
			/*遍历Y坐标*/
			for (j = Y; j < Y + Height; j ++)
			{
				/*在指定区域画点，填充满矩形*/
				Graphic_DrawPoint(Graphic_ptr,i, j);
			}
		}
	}
}

/**
  * 函    数：OLED三角形
  * 参    数：X0 指定第一个端点的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y0 指定第一个端点的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：X1 指定第二个端点的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y1 指定第二个端点的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：X2 指定第三个端点的横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y2 指定第三个端点的纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：IsFilled 指定三角形是否填充
  *           范围：Graphic_UNFILLED		不填充
  *                 Graphic_FILLED			填充
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_DrawTriangle(Graphic_TypeDef*Graphic_ptr,uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, uint8_t IsFilled)
{
	uint8_t minx = X0, miny = Y0, maxx = X0, maxy = Y0;
	uint8_t i, j;
	int16_t vx[] = {X0, X1, X2};
	int16_t vy[] = {Y0, Y1, Y2};
	
	if (!IsFilled)			//指定三角形不填充
	{
		/*调用画线函数，将三个点用直线连接*/
		Graphic_DrawLine(Graphic_ptr,X0, Y0, X1, Y1);
		Graphic_DrawLine(Graphic_ptr,X0, Y0, X2, Y2);
		Graphic_DrawLine(Graphic_ptr,X1, Y1, X2, Y2);
	}
	else					//指定三角形填充
	{
		/*找到三个点最小的X、Y坐标*/
		if (X1 < minx) {minx = X1;}
		if (X2 < minx) {minx = X2;}
		if (Y1 < miny) {miny = Y1;}
		if (Y2 < miny) {miny = Y2;}
		
		/*找到三个点最大的X、Y坐标*/
		if (X1 > maxx) {maxx = X1;}
		if (X2 > maxx) {maxx = X2;}
		if (Y1 > maxy) {maxy = Y1;}
		if (Y2 > maxy) {maxy = Y2;}
		
		/*最小最大坐标之间的矩形为可能需要填充的区域*/
		/*遍历此区域中所有的点*/
		/*遍历X坐标*/		
		for (i = minx; i <= maxx; i ++)
		{
			/*遍历Y坐标*/	
			for (j = miny; j <= maxy; j ++)
			{
				/*调用Graphic_pnpoly，判断指定点是否在指定三角形之中*/
				/*如果在，则画点，如果不在，则不做处理*/
				if (Graphic_pnpoly(3, vx, vy, i, j)) {Graphic_DrawPoint(Graphic_ptr,i, j);}
			}
		}
	}
}

/**
  * 函    数：OLED画圆
  * 参    数：X 指定圆的圆心横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定圆的圆心纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Radius 指定圆的半径，范围：0~255
  * 参    数：IsFilled 指定圆是否填充
  *           范围：Graphic_UNFILLED		不填充
  *                 Graphic_FILLED			填充
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_DrawCircle(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Radius, uint8_t IsFilled)
{
	int16_t x, y, d, j;
	
	/*使用Bresenham算法画圆，可以避免耗时的浮点运算，效率更高*/
	/*参考文档：https://www.cs.montana.edu/courses/spring2009/425/dslectures/Bresenham.pdf*/
	/*参考教程：https://www.bilibili.com/video/BV1VM4y1u7wJ*/
	
	d = 1 - Radius;
	x = 0;
	y = Radius;
	
	/*画每个八分之一圆弧的起始点*/
	Graphic_DrawPoint(Graphic_ptr,X + x, Y + y);
	Graphic_DrawPoint(Graphic_ptr,X - x, Y - y);
	Graphic_DrawPoint(Graphic_ptr,X + y, Y + x);
	Graphic_DrawPoint(Graphic_ptr,X - y, Y - x);
	
	if (IsFilled)		//指定圆填充
	{
		/*遍历起始点Y坐标*/
		for (j = -y; j < y; j ++)
		{
			/*在指定区域画点，填充部分圆*/
			Graphic_DrawPoint(Graphic_ptr,X, Y + j);
		}
	}
	
	while (x < y)		//遍历X轴的每个点
	{
		x ++;
		if (d < 0)		//下一个点在当前点东方
		{
			d += 2 * x + 1;
		}
		else			//下一个点在当前点东南方
		{
			y --;
			d += 2 * (x - y) + 1;
		}
		
		/*画每个八分之一圆弧的点*/
		Graphic_DrawPoint(Graphic_ptr,X + x, Y + y);
		Graphic_DrawPoint(Graphic_ptr,X + y, Y + x);
		Graphic_DrawPoint(Graphic_ptr,X - x, Y - y);
		Graphic_DrawPoint(Graphic_ptr,X - y, Y - x);
		Graphic_DrawPoint(Graphic_ptr,X + x, Y - y);
		Graphic_DrawPoint(Graphic_ptr,X + y, Y - x);
		Graphic_DrawPoint(Graphic_ptr,X - x, Y + y);
		Graphic_DrawPoint(Graphic_ptr,X - y, Y + x);
		
		if (IsFilled)	//指定圆填充
		{
			/*遍历中间部分*/
			for (j = -y; j < y; j ++)
			{
				/*在指定区域画点，填充部分圆*/
				Graphic_DrawPoint(Graphic_ptr,X + x, Y + j);
				Graphic_DrawPoint(Graphic_ptr,X - x, Y + j);
			}
			
			/*遍历两侧部分*/
			for (j = -x; j < x; j ++)
			{
				/*在指定区域画点，填充部分圆*/
				Graphic_DrawPoint(Graphic_ptr,X - y, Y + j);
				Graphic_DrawPoint(Graphic_ptr,X + y, Y + j);
			}
		}
	}
}

/**
  * 函    数：OLED画椭圆
  * 参    数：X 指定椭圆的圆心横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定椭圆的圆心纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：A 指定椭圆的横向半轴长度，范围：0~255
  * 参    数：B 指定椭圆的纵向半轴长度，范围：0~255
  * 参    数：IsFilled 指定椭圆是否填充
  *           范围：Graphic_UNFILLED		不填充
  *                 Graphic_FILLED			填充
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_DrawEllipse(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t A, uint8_t B, uint8_t IsFilled)
{
	int16_t x, y, j;
	int16_t a = A, b = B;
	float d1, d2;
	
	/*使用Bresenham算法画椭圆，可以避免部分耗时的浮点运算，效率更高*/
	/*参考链接：https://blog.csdn.net/myf_666/article/details/128167392*/
	
	x = 0;
	y = b;
	d1 = b * b + a * a * (-b + 0.5);
	
	if (IsFilled)	//指定椭圆填充
	{
		/*遍历起始点Y坐标*/
		for (j = -y; j < y; j ++)
		{
			/*在指定区域画点，填充部分椭圆*/
			Graphic_DrawPoint(Graphic_ptr,X, Y + j);
			Graphic_DrawPoint(Graphic_ptr,X, Y + j);
		}
	}
	
	/*画椭圆弧的起始点*/
	Graphic_DrawPoint(Graphic_ptr,X + x, Y + y);
	Graphic_DrawPoint(Graphic_ptr,X - x, Y - y);
	Graphic_DrawPoint(Graphic_ptr,X - x, Y + y);
	Graphic_DrawPoint(Graphic_ptr,X + x, Y - y);
	
	/*画椭圆中间部分*/
	while (b * b * (x + 1) < a * a * (y - 0.5))
	{
		if (d1 <= 0)		//下一个点在当前点东方
		{
			d1 += b * b * (2 * x + 3);
		}
		else				//下一个点在当前点东南方
		{
			d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
			y --;
		}
		x ++;
		
		if (IsFilled)	//指定椭圆填充
		{
			/*遍历中间部分*/
			for (j = -y; j < y; j ++)
			{
				/*在指定区域画点，填充部分椭圆*/
				Graphic_DrawPoint(Graphic_ptr,X + x, Y + j);
				Graphic_DrawPoint(Graphic_ptr,X - x, Y + j);
			}
		}
		
		/*画椭圆中间部分圆弧*/
		Graphic_DrawPoint(Graphic_ptr,X + x, Y + y);
		Graphic_DrawPoint(Graphic_ptr,X - x, Y - y);
		Graphic_DrawPoint(Graphic_ptr,X - x, Y + y);
		Graphic_DrawPoint(Graphic_ptr,X + x, Y - y);
	}
	
	/*画椭圆两侧部分*/
	d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
	
	while (y > 0)
	{
		if (d2 <= 0)		//下一个点在当前点东方
		{
			d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
			x ++;
			
		}
		else				//下一个点在当前点东南方
		{
			d2 += a * a * (-2 * y + 3);
		}
		y --;
		
		if (IsFilled)	//指定椭圆填充
		{
			/*遍历两侧部分*/
			for (j = -y; j < y; j ++)
			{
				/*在指定区域画点，填充部分椭圆*/
				Graphic_DrawPoint(Graphic_ptr,X + x, Y + j);
				Graphic_DrawPoint(Graphic_ptr,X - x, Y + j);
			}
		}
		
		/*画椭圆两侧部分圆弧*/
		Graphic_DrawPoint(Graphic_ptr,X + x, Y + y);
		Graphic_DrawPoint(Graphic_ptr,X - x, Y - y);
		Graphic_DrawPoint(Graphic_ptr,X - x, Y + y);
		Graphic_DrawPoint(Graphic_ptr,X + x, Y - y);
	}
}

/**
  * 函    数：OLED画圆弧
  * 参    数：X 指定圆弧的圆心横坐标，范围：0~Graphic_ptr->Screen_X-1
  * 参    数：Y 指定圆弧的圆心纵坐标，范围：0~Graphic_ptr->Screen_Y-1
  * 参    数：Radius 指定圆弧的半径，范围：0~255
  * 参    数：StartAngle 指定圆弧的起始角度，范围：-180~180
  *           水平向右为0度，水平向左为180度或-180度，下方为正数，上方为负数，顺时针旋转
  * 参    数：EndAngle 指定圆弧的终止角度，范围：-180~180
  *           水平向右为0度，水平向左为180度或-180度，下方为正数，上方为负数，顺时针旋转
  * 参    数：IsFilled 指定圆弧是否填充，填充后为扇形
  *           范围：Graphic_UNFILLED		不填充
  *                 Graphic_FILLED			填充
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void Graphic_DrawArc(Graphic_TypeDef*Graphic_ptr,uint8_t X, uint8_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled)
{
	int16_t x, y, d, j;
	
	/*此函数借用Bresenham算法画圆的方法*/
	
	d = 1 - Radius;
	x = 0;
	y = Radius;
	
	/*在画圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
	if (Graphic_IsInAngle(x, y, StartAngle, EndAngle))	{Graphic_DrawPoint(Graphic_ptr,X + x, Y + y);}
	if (Graphic_IsInAngle(-x, -y, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X - x, Y - y);}
	if (Graphic_IsInAngle(y, x, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X + y, Y + x);}
	if (Graphic_IsInAngle(-y, -x, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X - y, Y - x);}
	
	if (IsFilled)	//指定圆弧填充
	{
		/*遍历起始点Y坐标*/
		for (j = -y; j < y; j ++)
		{
			/*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
			if (Graphic_IsInAngle(0, j, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X, Y + j);}
		}
	}
	
	while (x < y)		//遍历X轴的每个点
	{
		x ++;
		if (d < 0)		//下一个点在当前点东方
		{
			d += 2 * x + 1;
		}
		else			//下一个点在当前点东南方
		{
			y --;
			d += 2 * (x - y) + 1;
		}
		
		/*在画圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
		if (Graphic_IsInAngle(x, y, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X + x, Y + y);}
		if (Graphic_IsInAngle(y, x, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X + y, Y + x);}
		if (Graphic_IsInAngle(-x, -y, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X - x, Y - y);}
		if (Graphic_IsInAngle(-y, -x, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X - y, Y - x);}
		if (Graphic_IsInAngle(x, -y, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X + x, Y - y);}
		if (Graphic_IsInAngle(y, -x, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X + y, Y - x);}
		if (Graphic_IsInAngle(-x, y, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X - x, Y + y);}
		if (Graphic_IsInAngle(-y, x, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X - y, Y + x);}
		
		if (IsFilled)	//指定圆弧填充
		{
			/*遍历中间部分*/
			for (j = -y; j < y; j ++)
			{
				/*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
				if (Graphic_IsInAngle(x, j, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X + x, Y + j);}
				if (Graphic_IsInAngle(-x, j, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X - x, Y + j);}
			}
			
			/*遍历两侧部分*/
			for (j = -x; j < x; j ++)
			{
				/*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
				if (Graphic_IsInAngle(-y, j, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X - y, Y + j);}
				if (Graphic_IsInAngle(y, j, StartAngle, EndAngle)) {Graphic_DrawPoint(Graphic_ptr,X + y, Y + j);}
			}
		}
	}
}

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
