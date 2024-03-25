/**
  ******************************************************************************
  * @file    Graphic_test.c
  * @author  Lightcone
  * @version V1.1.0
  * @date    2024-03-22
  * @brief   图形显示库测试环境
  ******************************************************************************
  */
#include "Graphic.h"
void graphic_test(){
	Graphic_SSD1306_Init();
	Graphic_Point point[3] = {
		[0] = {.x = 1,.y = 1},
		[1] = {.x = 10,.y = 10},
		[2] = {.x = 20,.y = 50},
	};
	Graphic_Draw_Polygon(&SSD1306_List[Enum_SSD1306_1],point,3);
	Graphic_Point point2[3] = {
		[0] = {.x = 15,.y = 1},
		[1] = {.x = 17,.y = 89},
		[2] = {.x = 69,.y = 30},
	};
	Buffer_Draw_Polygon(&SSD1306_List[Enum_SSD1306_1].Buffer,point2,3);
	SSD1306_Hardware_Update_Callback(Enum_SSD1306_1);
}
/******************* Absolute Zero Studio - Lightcone **********END OF FILE****/
