//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//����Ӳ������Ƭ��STC89C52RC,����12M  ��Ƭ��������ѹ3.3V��5V
//QDtech-OLEDҺ������ for C51
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//����֧��QQ:3002773612  3002778157
//��������QQȺ:324828016
//��������:2018/9/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================��Դ����================================================//
// OLEDģ��                C51��Ƭ��
//   VCC         ��       DC 5V/3.3V      //OLED����Դ��
//   GND         ��          GND          //OLED����Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪIIC
// OLEDģ��                C51��Ƭ��
//   SDA        ��           P15          //OLED��SPIд�ź�
//=======================================Һ���������߽���==========================================//
// OLEDģ��                C51��Ƭ��
//   SCL        ��           P17          //OLED��SPIʱ���ź�
//=========================================����������=========================================//
//��ģ�鲻���������ܣ����Բ���Ҫ����������
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
#include "oled.h"
#include "stdlib.h"
#include "string.h" 	 
#include "iic.h"
#include "stdio.h"

//OLED�Դ��ܹ���Ϊ4ҳ
//ÿҳ8�У�һ��128�����ص�
//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127 (0~7)��	   
//[1]0 1 2 3 ... 127 (8~15)��	
//[2]0 1 2 3 ... 127 (16~23)��	
//[3]0 1 2 3 ... 127 (24~31)��				   

/*******************************************************************
 * @name       :void OLED_WR_Byte(unsigned dat,unsigned cmd)
 * @date       :2018-08-27
 * @function   :Write a byte of content to the OLED screen
 * @parameters :dat:Content to be written
                cmd:0-write command
								    1-write data
 * @retvalue   :None
********************************************************************/
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		Write_IIC_Data(dat);
	}
	else
	{
		Write_IIC_Command(dat);
	}
}

/*******************************************************************
 * @name       :void OLED_Set_Pos(unsigned char x, unsigned char y) 
 * @date       :2018-08-27
 * @function   :Set coordinates in the OLED screen
 * @parameters :x:x coordinates
                y:y coordinates
 * @retvalue   :None
********************************************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{
 	OLED_WR_Byte(YLevel+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}  

/*******************************************************************
 * @name       :void OLED_Display_On(void) 
 * @date       :2018-08-27
 * @function   :Turn on OLED display
 * @parameters :None
 * @retvalue   :None
********************************************************************/ 	  

void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}


/*******************************************************************
 * @name       :void OLED_Display_Off(void)
 * @date       :2018-08-27
 * @function   :Turn off OLED display
 * @parameters :None
 * @retvalue   :None
********************************************************************/    

void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

	   			
/*******************************************************************
 * @name       :void OLED_Clear(unsigned dat)  
 * @date       :2018-08-27
 * @function   :clear OLED screen
 * @parameters :dat:0-Display full black
                    1-Display full white
 * @retvalue   :None
********************************************************************/ 
void OLED_Clear(unsigned dat)  
{ 
	u8 i,n,color;	
	if(dat)
	{
		color = 0xff;
	}
	else
	{
		color = 0;
	}
	for(i=0;i<(PAGE_SIZE/2);i++)  
	{  
		OLED_WR_Byte(YLevel+i,OLED_CMD);    //����ҳ��ַ��0~3��
		OLED_WR_Byte(XLevelL,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte(XLevelH,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<WIDTH;n++)
		{
			OLED_WR_Byte(color,OLED_DATA); 
		}
	}   //������ʾ
}

/*******************************************************************
 * @name       :void OLED_Init(void)
 * @date       :2018-08-27
 * @function   :initialise OLED SSD1306 control IC
 * @parameters :None
 * @retvalue   :None
********************************************************************/ 				    
void OLED_Init(void)
{
/**************��ʼ��SSD1306*****************/	
	OLED_Display_Off(); //power off
	OLED_WR_Byte(0xAE,OLED_CMD);//--display off	
	OLED_WR_Byte(0x40,OLED_CMD);//---set low column address
	OLED_WR_Byte(0xB0,OLED_CMD);//---set high column address
	OLED_WR_Byte(0xC8,OLED_CMD);//-not offset
	OLED_WR_Byte(0x81,OLED_CMD);// contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128 
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse	
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x1F,OLED_CMD);	
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0xF0,OLED_CMD);	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0x22,OLED_CMD);	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x02,OLED_CMD);	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x49,OLED_CMD);	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	OLED_Display_On(); // power on
}  