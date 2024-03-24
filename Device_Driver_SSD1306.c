/**
  ******************************************************************************
  * @file    Device_Driver_SSD1306.c
  * @author  Lightcone
  * @version V3.0.2
  * @date    2024-03-24
  * @brief   OLED SSD1306硬件驱动层
  ******************************************************************************
  */
#include "STM32Device.h"
#include "Device_Driver_SSD1306.h"

// Device_Driver_SSD1306.c文件内部使用宏函数
#define SSD1306_Write_D0(x)		GPIO_WriteBit(SSD1306_Struct_ptr->D0_GPIO, SSD1306_Struct_ptr->D0_Pin, (BitAction)(x))
#define SSD1306_Write_D1(x)		GPIO_WriteBit(SSD1306_Struct_ptr->D1_GPIO, SSD1306_Struct_ptr->D1_Pin, (BitAction)(x))
#define SSD1306_Write_RES(x)		GPIO_WriteBit(SSD1306_Struct_ptr->RES_GPIO, SSD1306_Struct_ptr->RES_Pin, (BitAction)(x))
#define SSD1306_Write_DC(x)		GPIO_WriteBit(SSD1306_Struct_ptr->DC_GPIO, SSD1306_Struct_ptr->DC_Pin, (BitAction)(x))
#define SSD1306_Write_CS(x)		SSD1306_Struct_ptr->CS_Handler(SSD1306_Struct_ptr->Device_Enum)

void SSD1306_Pin_Init(SSD1306* SSD1306_Struct_ptr){
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
	
	SSD1306_Write_D0(1);
	
	SSD1306_Write_D1(1);
	SSD1306_Write_RES(0);
	SSD1306_Write_RES(1);
	SSD1306_Write_DC(1);
	//SSD1306_Write_CS(SSD1306_Struct_ptr,(BitAction)1);
}



/**
  * 函    数：SPI发送一个字节
  * 参    数：Byte 要发送的一个字节数据，范围：0x00~0xFF
  * 返 回 值：无
  */
void SSD1306_SendByte(SSD1306* SSD1306_Struct_ptr,uint8_t Byte){
	uint8_t i;
	
	/*循环8次，主机依次发送数据的每一位*/
	for (i = 0; i < 8; i++)
	{
		/*使用掩码的方式取出Byte的指定一位数据并写入到D1线*/
		/*两个!的作用是，让所有非零的值变为1*/
		SSD1306_Write_D1(!!(Byte & (0x80 >> i)));
		SSD1306_Write_D0(1);	//拉高D0，从机在D0上升沿读取SDA
		SSD1306_Write_D0(0);	//拉低D0，主机开始发送下一位数据
	}
}

/**
  * 函    数：OLED写命令
  * 参    数：Command 要写入的命令值，范围：0x00~0xFF
  * 返 回 值：无
  */
void SSD1306_WriteCommand(SSD1306* SSD1306_Struct_ptr,uint8_t Command){
	SSD1306_Write_CS(0);					//拉低CS，开始通信
	SSD1306_Write_DC(0);					//拉低DC，表示即将发送命令
	SSD1306_SendByte(SSD1306_Struct_ptr,Command);		//写入指定命令
	SSD1306_Write_CS(1);					//拉高CS，结束通信
}

/**
  * 函    数：OLED写数据
  * 参    数：Data 要写入数据的起始地址
  * 参    数：Count 要写入数据的数量
  * 返 回 值：无
  */
void SSD1306_WriteData(SSD1306* SSD1306_Struct_ptr,uint8_t *Data, uint8_t Count){
	uint8_t i;
	
	SSD1306_Write_CS(0);					//拉低CS，开始通信
	SSD1306_Write_DC(1);					//拉高DC，表示即将发送数据
	/*循环Count次，进行连续的数据写入*/
	for (i = 0; i < Count; i ++)
	{
		SSD1306_SendByte(SSD1306_Struct_ptr,Data[i]);	//依次发送Data的每一个数据
	}
	SSD1306_Write_CS(1);					//拉高CS，结束通信
}


/**
  * 函    数：OLED设置显示光标位置
  * 参    数：Page 指定光标所在的页，范围：0~7
  * 参    数：X 指定光标所在的X轴坐标，范围：0~127
  * 返 回 值：无
  * 说    明：OLED默认的Y轴，只能8个Bit为一组写入，即1页等于8个Y轴坐标
  */
void SSD1306_SetCursor(SSD1306* SSD1306_Struct_ptr,uint8_t Page, uint8_t X){
	/*如果使用此程序驱动1.3寸的OLED显示屏，则需要解除此注释*/
	/*因为1.3寸的OLED驱动芯片（SH1106）有132列*/
	/*屏幕的起始列接在了第2列，而不是第0列*/
	/*所以需要将X加2，才能正常显示*/
//	X += 2;
	
	/*通过指令设置页地址和列地址*/
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xB0 | Page);					//设置页位置
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0x10 | ((X & 0xF0) >> 4));	//设置X位置高4位
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0x00 | (X & 0x0F));			//设置X位置低4位
}

/**
  * 函    数：将OLED显存数组更新到OLED屏幕
  * 参    数：无
  * 返 回 值：无
  * 说    明：所有的显示函数，都只是对OLED显存数组进行读写
  *           随后调用SSD1306_Update函数或SSD1306_UpdateArea函数
  *           才会将显存数组的数据发送到OLED硬件，进行显示
  *           故调用显示函数后，要想真正地呈现在屏幕上，还需调用更新函数
  */
void SSD1306_Update(SSD1306* SSD1306_Struct_ptr){
	/*遍历每一页*/
	for(uint8_t j = 0; j < 8; j ++)
	{
		/*设置光标位置为每一页的第一列*/
		SSD1306_SetCursor(SSD1306_Struct_ptr,j, 0);
		/*连续写入128个数据，将显存数组的数据写入到OLED硬件*/
		SSD1306_WriteData(SSD1306_Struct_ptr,SSD1306_Struct_ptr->DisplayBuf+j*128, 128);
	}
}

/**
  * 如果更新区域Y轴只包含部分页，则同一页的剩余部分会跟随一起更新
  */
void SSD1306_UpdateArea(SSD1306* SSD1306_Struct_ptr,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height){
	if (X > 127) {return;}
	if (Y > 63) {return;}
	if (X + Width > 128) {Width = 128 - X;}// 超出裁切
	if (Y + Height > 64) {Height = 64 - Y;}// 超出裁切
	
	/*遍历指定区域涉及的相关页*/
	/*(Y + Height - 1) / 8 + 1的目的是(Y + Height) / 8并向上取整*/
	for (uint8_t j = Y / 8; j < (Y + Height - 1) / 8 + 1; j ++)
	{
		/*设置光标位置为相关页的指定列*/
		SSD1306_SetCursor(SSD1306_Struct_ptr,j, X);
		/*连续写入Width个数据，将显存数组的数据写入到OLED硬件*/
		SSD1306_WriteData(SSD1306_Struct_ptr,SSD1306_Struct_ptr->DisplayBuf+j*128+X, Width);
	}
}

void SSD1306_Clear(SSD1306* SSD1306_Struct_ptr){
	for(uint8_t i = 0; i < 8; i ++)
		for(uint8_t j = 0; j < 128; j ++)
			*(SSD1306_Struct_ptr->DisplayBuf + i*128 + j)= 0x00;	//将显存数组数据全部清零

}

void SSD1306_Init(SSD1306* SSD1306_Struct_ptr){
	SSD1306_Pin_Init(SSD1306_Struct_ptr);
	
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xAE);	//设置显示开启/关闭，0xAE关闭，0xAF开启
	
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xD5);	//设置显示时钟分频比/振荡器频率
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0x80);	//0x00~0xFF
	
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xA8);	//设置多路复用率
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0x3F);	//0x0E~0x3F
	
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xD3);	//设置显示偏移
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0x00);	//0x00~0x7F
	
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0x40);	//设置显示开始行，0x40~0x7F
	
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xA1);	//设置左右方向，0xA1正常，0xA0左右反置
	
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xC8);	//设置上下方向，0xC8正常，0xC0上下反置

	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xDA);	//设置COM引脚硬件配置
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0x12);
	
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0x81);	//设置对比度
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xCF);	//0x00~0xFF

	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xD9);	//设置预充电周期
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xF1);

	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xDB);	//设置VCOMH取消选择级别
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0x30);

	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xA4);	//设置整个显示打开/关闭

	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xA6);	//设置正常/反色显示，0xA6正常，0xA7反色

	SSD1306_WriteCommand(SSD1306_Struct_ptr,0x8D);	//设置充电泵
	SSD1306_WriteCommand(SSD1306_Struct_ptr,0x14);

	SSD1306_WriteCommand(SSD1306_Struct_ptr,0xAF);	//开启显示
	
	SSD1306_Clear(SSD1306_Struct_ptr);				//清空显存数组，防止初始化后未显示内容时花屏
	SSD1306_Update(SSD1306_Struct_ptr);				//更新显示，清屏
}

/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
