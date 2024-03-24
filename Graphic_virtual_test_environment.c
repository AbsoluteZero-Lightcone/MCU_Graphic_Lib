/**
  ******************************************************************************
  * @file    Graphic_virtual_test_environment.c
  * @author  Lightcone
  * @version V1.0.1
  * @date    2024-03-24
  * @brief   图形显示库测试环境
  ******************************************************************************
  */
#include "Graphic.h"
#include <stdio.h>
// 显存调试
void Debug_Show_Graphic_Buffer(Graphic_Buffer buffer){
	uint8_t screen[128][64] = {0};
	for(Page_Data i = 0 ;i < buffer.Buffer_Page;i++)
		for(Col_Data j = 0 ; j < buffer.Buffer_Col ; j++)
			for(Bias_Data k = 0 ; k < BIT_PER_PAGE ; k++){
				screen[j][i*BIT_PER_PAGE+k] = (*((uint8_t*)buffer.DisplayBuf + i*BIT_PER_PAGE + j)) & (0x01<<k);
			}
	for(X_Data i = 0 ;i < buffer.Screen_X;i++){
		for(Y_Data j = 0 ; j < buffer.Screen_Y ; j++){
			printf(screen[i][j]?"*":" ");
		}
		printf("\n");
	}
}
// 模拟SSD1306设备

void Virtual_SSD1306_Hardware_SetCursor_Callback(Device_Enum_Data Device_Enum,uint8_t x,uint8_t y){
	
}
void Virtual_SSD1306_Hardware_Update_Callback(Device_Enum_Data Device_Enum){
	
}
void Virtual_SSD1306_Hardware_UpdateArea_Callback(Device_Enum_Data Device_Enum,uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height){
	
}
void Virtual_SSD1306_Hardware_Clear_Callback(Device_Enum_Data Device_Enum){
	
}
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
