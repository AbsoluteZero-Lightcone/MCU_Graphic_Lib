/**
  ******************************************************************************
  * @file    Graphic.h
  * @author  Lightcone
  * @version V1.3.1
  * @date    2024-03-24
  * @brief   图形显示库
  ******************************************************************************
  */

#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <stdint.h>
#include "Device_Enum_Graphic.h"

#define BIT_PER_PAGE 8

// 数据大小设置
typedef uint8_t X_Data;
typedef uint8_t Y_Data;
typedef uint8_t Col_Data;
typedef uint8_t Page_Data;
typedef uint8_t Bias_Data;
typedef uint8_t bool;
typedef uint8_t Count;
typedef uint8_t Device_Enum_Data;

// 点对象存储结构
typedef struct{
	Col_Data Col;
	Page_Data Page;
	Bias_Data Bias; // 0~7
}Buffer_Point;

// 实际画布点对象
typedef struct{
	X_Data X;
	Y_Data Y;
}Graphic_Point;


/** 
  * @brief  显示缓冲区结构体
  */
typedef struct{
	uint8_t * DisplayBuf; // 指向实际创建出的显示缓冲区的内存存储区域
	X_Data Screen_X;
	Y_Data Screen_Y;
	Page_Data Buffer_Page;
	Col_Data Buffer_Col;
}Graphic_Buffer;

// 前后端分离
typedef struct{
	Device_Enum_Data Device_Enum; // 设备枚举
	Graphic_Buffer Buffer;
	/*
	直接解决了共享显存问题，
	动态更改buffer的指向即可切换哪些屏幕需要共享显示内容，
	甚至使用额外的Buffer，
	能实现类似后台渲染多任务（后台任务）/多个桌面的效果
	但是这要求前后端绝对分离，绘图函数对Buffer操作，
	而非传入Graphic指针再访问其中的buffer
	这是降低代码耦合性的好处
*/
// 必要硬件抽象接口函数：
	void (*Hardware_UpdateArea_Callback)(Device_Enum_Data Device_Enum,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
// 可选功能接口函数：
	void (*Hardware_Update_Callback)(Device_Enum_Data Device_Enum);
	void (*Hardware_Clear_Callback)(Device_Enum_Data Device_Enum);
	// 还可扩展更多基本接口
	}Graphic_Object;









// old
typedef struct{
	void (*Screen_SetCursor_Callback)(uint8_t x,uint8_t y);
	void (*Screen_Update_Callback)(void);
	void (*Screen_UpdateArea_Callback)(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
	uint8_t **DisplayBuf;
	uint8_t Screen_X;
	uint8_t Screen_Y;
	uint8_t Screen_Page;
}Graphic_TypeDef;

#define SetCursor(a,b) Graphic_ptr->Screen_SetCursor_Callback(a,b)
#define Update()       Graphic_ptr->Screen_Update_Callback(Graphic_ptr->Display_Buffer);


#endif /* __GRAPHIC_H */
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
