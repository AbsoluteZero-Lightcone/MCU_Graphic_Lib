/**
  ******************************************************************************
  * @file    SSD1306_Driver_old.c
  * @author  Lightcone & 江协科技
  * @version V2.0.4
  * @date    2024-03-24
  * @brief   OLED SSD1306硬件驱动层
  ******************************************************************************
  */
#include "STM32Device.h"
#include "SSD1306_Driver.h"

// SSD1306_Driver.c文件内部使用宏函数
#define OLED_W_D0(x)		GPIO_WriteBit(SSD1306_Struct_ptr->D0_GPIO, SSD1306_Struct_ptr->D0_Pin, (BitAction)(x))
#define OLED_W_D1(x)		GPIO_WriteBit(SSD1306_Struct_ptr->D1_GPIO, SSD1306_Struct_ptr->D1_Pin, (BitAction)(x))
#define OLED_W_RES(x)		GPIO_WriteBit(SSD1306_Struct_ptr->RES_GPIO, SSD1306_Struct_ptr->RES_Pin, (BitAction)(x))
#define OLED_W_DC(x)		GPIO_WriteBit(SSD1306_Struct_ptr->DC_GPIO, SSD1306_Struct_ptr->DC_Pin, (BitAction)(x))
#define OLED_W_CS(x)		SSD1306_Struct_ptr->CS_Handler()

#define SSD1306_SendByte(Byte) SSD1306_SendByte_RAW(SSD1306_Struct_ptr,Byte)
#define OLED_WriteCommand(Command) OLED_WriteCommand_RAW(SSD1306_Struct_ptr,Command)
#define OLED_WriteData(Data_ptr,Count) OLED_WriteData_RAW(SSD1306_Struct_ptr,Data_ptr,Count)
#define OLED_SetCursor(Page,X) OLED_SetCursor_RAW(SSD1306_Struct_ptr,Page,X)
#define OLED_Update() OLED_Update_RAW(SSD1306_Struct_ptr)
#define OLED_UpdateArea(X,Y,Width,Height) OLED_UpdateArea_RAW(SSD1306_Struct_ptr,X,Y,Width,Height)
#define OLED_Clear() OLED_Clear_RAW(SSD1306_Struct_ptr)

#define OLED_DisplayBuf SSD1306_Struct_ptr->DisplayBuf


/*引脚初始化*/
void SSD1306_Pin_Init(SSD1306* SSD1306_Struct_ptr)
{
	RCC_APB2PeriphClockCmd(to_RCC_APB2Periph(SSD1306_Struct_ptr->D0_GPIO), ENABLE);
	RCC_APB2PeriphClockCmd(to_RCC_APB2Periph(SSD1306_Struct_ptr->D1_GPIO), ENABLE);
	RCC_APB2PeriphClockCmd(to_RCC_APB2Periph(SSD1306_Struct_ptr->RES_GPIO), ENABLE);
	RCC_APB2PeriphClockCmd(to_RCC_APB2Periph(SSD1306_Struct_ptr->DC_GPIO), ENABLE);
	//RCC_APB2PeriphClockCmd(to_RCC_APB2Periph(SSD1306_Struct_ptr->CS_GPIO), ENABLE);

	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = SSD1306_Struct_ptr->D0_Pin;
 	GPIO_Init(SSD1306_Struct_ptr->D0_GPIO, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = SSD1306_Struct_ptr->D1_Pin;
 	GPIO_Init(SSD1306_Struct_ptr->D1_GPIO, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = SSD1306_Struct_ptr->DC_Pin;
 	GPIO_Init(SSD1306_Struct_ptr->DC_GPIO, &GPIO_InitStructure);
	/*
	GPIO_InitStructure.GPIO_Pin = SSD1306_Struct_ptr->CS_Pin;
 	GPIO_Init(SSD1306_Struct_ptr->CS_GPIO, &GPIO_InitStructure);
	*/
	GPIO_InitStructure.GPIO_Pin = SSD1306_Struct_ptr->RES_Pin;
 	GPIO_Init(SSD1306_Struct_ptr->RES_GPIO, &GPIO_InitStructure);
	
	OLED_W_D0(1);
	
	OLED_W_D1(1);
	OLED_W_RES(0);
	OLED_W_RES(1);
	OLED_W_DC(1);
	//OLED_W_CS(SSD1306_Struct_ptr,(BitAction)1);
}

/*通信协议*********************/

/**
  * 函    数：SPI发送一个字节
  * 参    数：Byte 要发送的一个字节数据，范围：0x00~0xFF
  * 返 回 值：无
  */
void SSD1306_SendByte_RAW(SSD1306* SSD1306_Struct_ptr,uint8_t Byte)
{
	uint8_t i;
	
	/*循环8次，主机依次发送数据的每一位*/
	for (i = 0; i < 8; i++)
	{
		/*使用掩码的方式取出Byte的指定一位数据并写入到D1线*/
		/*两个!的作用是，让所有非零的值变为1*/
		OLED_W_D1(!!(Byte & (0x80 >> i)));
		OLED_W_D0(1);	//拉高D0，从机在D0上升沿读取SDA
		OLED_W_D0(0);	//拉低D0，主机开始发送下一位数据
	}
}

/**
  * 函    数：OLED写命令
  * 参    数：Command 要写入的命令值，范围：0x00~0xFF
  * 返 回 值：无
  */
void OLED_WriteCommand_RAW(SSD1306* SSD1306_Struct_ptr,uint8_t Command)
{
	OLED_W_CS(0);					//拉低CS，开始通信
	OLED_W_DC(0);					//拉低DC，表示即将发送命令
	SSD1306_SendByte(Command);		//写入指定命令
	OLED_W_CS(1);					//拉高CS，结束通信
}

/**
  * 函    数：OLED写数据
  * 参    数：Data 要写入数据的起始地址
  * 参    数：Count 要写入数据的数量
  * 返 回 值：无
  */
void OLED_WriteData_RAW(SSD1306* SSD1306_Struct_ptr,uint8_t *Data, uint8_t Count)
{
	uint8_t i;
	
	OLED_W_CS(0);					//拉低CS，开始通信
	OLED_W_DC(1);					//拉高DC，表示即将发送数据
	/*循环Count次，进行连续的数据写入*/
	for (i = 0; i < Count; i ++)
	{
		SSD1306_SendByte(Data[i]);	//依次发送Data的每一个数据
	}
	OLED_W_CS(1);					//拉高CS，结束通信
}

/*********************通信协议*/

/*功能函数*********************/

/**
  * 函    数：OLED设置显示光标位置
  * 参    数：Page 指定光标所在的页，范围：0~7
  * 参    数：X 指定光标所在的X轴坐标，范围：0~127
  * 返 回 值：无
  * 说    明：OLED默认的Y轴，只能8个Bit为一组写入，即1页等于8个Y轴坐标
  */
void OLED_SetCursor_RAW(SSD1306* SSD1306_Struct_ptr,uint8_t Page, uint8_t X)
{
	/*如果使用此程序驱动1.3寸的OLED显示屏，则需要解除此注释*/
	/*因为1.3寸的OLED驱动芯片（SH1106）有132列*/
	/*屏幕的起始列接在了第2列，而不是第0列*/
	/*所以需要将X加2，才能正常显示*/
//	X += 2;
	
	/*通过指令设置页地址和列地址*/
	OLED_WriteCommand(0xB0 | Page);					//设置页位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X位置高4位
	OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X位置低4位
}

/**
  * 函    数：将OLED显存数组更新到OLED屏幕
  * 参    数：无
  * 返 回 值：无
  * 说    明：所有的显示函数，都只是对OLED显存数组进行读写
  *           随后调用OLED_Update函数或OLED_UpdateArea函数
  *           才会将显存数组的数据发送到OLED硬件，进行显示
  *           故调用显示函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void OLED_Update_RAW(SSD1306* SSD1306_Struct_ptr)
{
	uint8_t j;
	/*遍历每一页*/
	for (j = 0; j < 8; j ++)
	{
		/*设置光标位置为每一页的第一列*/
		OLED_SetCursor(j, 0);
		/*连续写入128个数据，将显存数组的数据写入到OLED硬件*/
		OLED_WriteData(OLED_DisplayBuf[j], 128);
	}
}

/**
  * 函    数：将OLED显存数组部分更新到OLED屏幕
  * 参    数：X 指定区域左上角的横坐标，范围：0~127
  * 参    数：Y 指定区域左上角的纵坐标，范围：0~63
  * 参    数：Width 指定区域的宽度，范围：0~128
  * 参    数：Height 指定区域的高度，范围：0~64
  * 返 回 值：无
  * 说    明：此函数会至少更新参数指定的区域
  *           如果更新区域Y轴只包含部分页，则同一页的剩余部分会跟随一起更新
  * 说    明：所有的显示函数，都只是对OLED显存数组进行读写
  *           随后调用OLED_Update函数或OLED_UpdateArea函数
  *           才会将显存数组的数据发送到OLED硬件，进行显示
  *           故调用显示函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void OLED_UpdateArea_RAW(SSD1306* SSD1306_Struct_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
	uint8_t j;
	
	/*参数检查，保证指定区域不会超出屏幕范围*/
	if (X > 127) {return;}
	if (Y > 63) {return;}
	if (X + Width > 128) {Width = 128 - X;}
	if (Y + Height > 64) {Height = 64 - Y;}
	
	/*遍历指定区域涉及的相关页*/
	/*(Y + Height - 1) / 8 + 1的目的是(Y + Height) / 8并向上取整*/
	for (j = Y / 8; j < (Y + Height - 1) / 8 + 1; j ++)
	{
		/*设置光标位置为相关页的指定列*/
		OLED_SetCursor(j, X);
		/*连续写入Width个数据，将显存数组的数据写入到OLED硬件*/
		OLED_WriteData(&OLED_DisplayBuf[j][X], Width);
	}
}

/**
  * 函    数：将OLED显存数组全部清零
  * 参    数：无
  * 返 回 值：无
  * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void OLED_Clear_RAW(SSD1306* SSD1306_Struct_ptr)
{
	uint8_t i, j;
	for (j = 0; j < 8; j ++)				//遍历8页
	{
		for (i = 0; i < 128; i ++)			//遍历128列
		{
			OLED_DisplayBuf[j][i] = 0x00;	//将显存数组数据全部清零
		}
	}
}

/*********************功能函数*/
/*硬件配置*********************/

/**
  * 函    数：OLED初始化
  * 参    数：无
  * 返 回 值：无
  * 说    明：使用前，需要调用此初始化函数
  */
void SSD1306_Init(SSD1306* SSD1306_Struct_ptr)
{
	SSD1306_Pin_Init(SSD1306_Struct_ptr);			//先调用底层的端口初始化
	
	/*写入一系列的命令，对OLED进行初始化配置*/
	OLED_WriteCommand(0xAE);	//设置显示开启/关闭，0xAE关闭，0xAF开启
	
	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);	//0x00~0xFF
	
	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);	//0x0E~0x3F
	
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);	//0x00~0x7F
	
	OLED_WriteCommand(0x40);	//设置显示开始行，0x40~0x7F
	
	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常，0xA0左右反置
	
	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常，0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//设置对比度
	OLED_WriteCommand(0xCF);	//0x00~0xFF

	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/反色显示，0xA6正常，0xA7反色

	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//开启显示
	
	OLED_Clear();				//清空显存数组
	OLED_Update();				//更新显示，清屏，防止初始化后未显示内容时花屏
}


/*********************硬件配置*/
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
