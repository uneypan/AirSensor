//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STC89C52RC,晶振12M  单片机工作电压3.3V或5V
//QDtech-OLED液晶驱动 for C51
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/9/14
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================电源接线================================================//
// OLED模块                C51单片机
//   VCC         接       DC 5V/3.3V      //OLED屏电源正
//   GND         接          GND          //OLED屏电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为IIC
// OLED模块                C51单片机
//   SDA        接           P15          //OLED屏SPI写信号
//=======================================液晶屏控制线接线==========================================//
// OLED模块                C51单片机
//   SCL        接           P17          //OLED屏SPI时钟信号
//=========================================触摸屏接线=========================================//
//本模块不带触摸功能，所以不需要触摸屏接线
****************************************************************************************************/	
/***************************************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
****************************************************************************************************/		
//#include "stdlib.h"
#include "stdio.h"
#include "oled.h"
#include "gui.h"
#include "test.h"
//#include "bmp.h"


/*****************************************************************************
 * @name       :void TEST_MainPage(void)
 * @date       :2018-08-27 
 * @function   :Drawing the main Interface of the Comprehensive Test Program
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
/*void TEST_MainPage(void)
{	
	GUI_ShowString(37,0,"OLED TEST",8,1);
	GUI_ShowString(25,1,"0.91\" SSD1306",8,1);
	GUI_ShowString(46,2,"32X128",8,1);
	GUI_ShowString(19,3,"www.lcdwiki.com",8,1);
	delay_ms(1500);		
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Test_Color(void)
 * @date       :2018-08-27 
 * @function   :Color fill test(white,black)
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
/*void Test_Color(void)
{
	 GUI_Fill(0,0,WIDTH-1,7,0);
	 GUI_ShowString(10,1,"BLACK",16,1);
	 delay_ms(1000);	
	 GUI_Fill(0,0,WIDTH-1,7,1);
	 GUI_ShowString(10,1,"WHITE",16,0);
	 delay_ms(1500);
}

/*****************************************************************************
 * @name       :void TEST_English(void)
 * @date       :2018-08-27 
 * @function   :English display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
/*void TEST_English(void)
{
	GUI_ShowString(0,1,"6x8:abcdefghijklmnopqrstuvwxyz",8,1);
	delay_ms(1000);
	GUI_ShowString(0,0,"8x16:abcdefghijklmnopqrstuvwxyz",16,1);
	delay_ms(1000);
	OLED_Clear(0); 
	GUI_ShowString(0,1,"6x8:ABCDEFGHIJKLMNOPQRSTUVWXYZ",8,1);
	delay_ms(1000);
	GUI_ShowString(0,0,"8x16:ABCDEFGHIJKLMNOPQRSTUVWXYZ",16,1);
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void TEST_Number_Character(void) 
 * @date       :2018-08-27 
 * @function   :number and character display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
/*void TEST_Number_Character(void) 
{
	GUI_Fill(0,0,WIDTH-1,1,0);
	GUI_ShowString(0,0,"6x8:!\"#$%&'()*+,-./:;<=>?@[]\\^_`~{}|",8,1);
	GUI_ShowNum(68,1,1234567890,10,8,1);
	GUI_Fill(0,2,WIDTH-1,3,1);
	GUI_ShowString(0,2,"6x8:!\"#$%&'()*+,-./:;<=>?@[]\\^_`~{}|",8,0);
	GUI_ShowNum(68,3,1234567890,10,8,0);
	delay_ms(1000);
	OLED_Clear(0); 
  GUI_ShowString(0,0,"8x16:!\"#$%&'()*+,-./:;<=>?@[]\\^_`~{}|",16,1);
	GUI_ShowNum(48,2,1234567890,10,16,1);
	delay_ms(1500);
	OLED_Clear(0);
}

/*****************************************************************************
 * @name       :void TEST_Chinese(void)
 * @date       :2018-08-27
 * @function   :chinese display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
/*void TEST_Chinese(void)
{	
	GUI_ShowString(45,0,"16x16",8,1);
	GUI_ShowCHinese(16,2,16,"全动电子技术",1);
	delay_ms(1000);
	GUI_Fill(0,0,WIDTH-1,3,1);
	GUI_ShowString(45,0,"16x16",8,0);
	GUI_ShowCHinese(16,2,16,"全动电子技术",0);
	delay_ms(1000);
	OLED_Clear(0);
	GUI_ShowString(45,0,"24x24",8,1);
	GUI_ShowCHinese(16,1,24,"全动电子",1);
	delay_ms(1000);
	OLED_Clear(0);
	GUI_ShowCHinese(0,0,32,"全动电子",1);	
  delay_ms(1000);
	OLED_Clear(0);
}*/

/*****************************************************************************
 * @name       :void TEST_BMP(void)
 * @date       :2018-08-27 
 * @function   :BMP monochromatic picture display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
//void TEST_BMP(void)
//{



//	GUI_DrawBMP(0,0,128,16, BMP2, 1);
//	delay_ms(1000);
//}
void TEST_Co2_Tvoc(void)
{
	GUI_ShowString(12,1,"TVOC/Ppb",8,1);//8+6*8+8	
	GUI_ShowString(71,1,"CO2/Ppm",8,1);//64+11+6*7+11
}
void TEST_Temp_Himi(void)
{
	GUI_ShowString(15,1,"TEMP/*C",8,1);//11+6*7+11	(*符号更改为°)
	GUI_ShowString(74,1,"HIMI/%",8,1);//64+14+6*6+14
}

//void TEST_CO2TVOC(void)
//{
//	GUI_DrawBMP(0,9,128,11, BMP7, 1);
//	delay_ms(1000);
//}
//void TEST_TEMPHIMI(void)
//{
//	GUI_DrawBMP(0,9,128,11, BMP8, 1);
//	delay_ms(1000);
//}
