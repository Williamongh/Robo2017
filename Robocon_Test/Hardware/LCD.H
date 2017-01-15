#ifndef 	__LCD__H
#define 	__LCD__H

#include "include.h"



/******************************************************************************
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PB13（SCL）
//              SDA   接PB15（SDA）
//              RES   接PD9
//              DC    接PD8
//              CS    接PB12 
//							BL		接PB14
*******************************************************************************/
/*********************** API接口 ******************************/
//提供API接口给LCD调用
uint16_t ST7735R_get_h(void);
uint16_t ST7735R_get_w(void);
#define LCD_H                   ST7735R_get_h()                 //高
#define LCD_W                   ST7735R_get_w()                 //宽
#define ST7735R_H       128
#define ST7735R_W       128
#define ST7735R_DIR_DEFAULT       0

#define LCD_DIR                 ST7735R_get_dir()               //获取方向


//通过函数调用，速度太慢了，改成宏定义调用
//#define LCD_WR_8DATA(data)      LCD_ST7735R_wr_data(data)       //写数据
//#define LCD_WR_8CMD(cmd)        LCD_ST7735R_wr_cmd(cmd)         //命令


#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        128

#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   			//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111
#define BRED    0XF81F
#define GRED    0XFFE0    //灰色
#define GBLUE   0X07FF    //




#define LCD_CTRLD   	  	GPIOD		//定义TFT数据端口
#define LCD_CTRLB   	  	GPIOB		//定义TFT数据端口



#define LCD_SCL        	GPIO_Pin_13	//PB13--->>TFT --SCL/SCK
#define LCD_SDA        	GPIO_Pin_15	//PB15 MOSI--->>TFT --SDA/DIN
#define LCD_CS        	GPIO_Pin_12  //MCU_PB12--->>TFT --CS/CE
#define LCD_LED        	GPIO_Pin_14  //MCU_PB14--->>TFT --BL

#define LCD_RS         	GPIO_Pin_8	//PD8--->>TFT --RS/DC
#define LCD_RST     		GPIO_Pin_9	//PD9--->>TFT --RST

//#define LCD_CS_SET(x) LCD_CTRL->ODR=(LCD_CTRL->ODR&~LCD_CS)|(x ? LCD_CS:0)

//液晶控制口置1操作语句宏定义
#define	LCD_SCL_SET  	LCD_CTRLB->BSRR=LCD_SCL    
#define	LCD_SDA_SET  	LCD_CTRLB->BSRR=LCD_SDA   
#define	LCD_CS_SET  	LCD_CTRLB->BSRR=LCD_CS  
#define	LCD_LED_SET  	LCD_CTRLB->BSRR=LCD_LED 

#define	LCD_RS_SET  	LCD_CTRLD->BSRR=LCD_RS 
#define	LCD_RST_SET  	LCD_CTRLD->BSRR=LCD_RST 
//液晶控制口置0操作语句宏定义
#define	LCD_SCL_CLR  	LCD_CTRLB->BRR=LCD_SCL  
#define	LCD_SDA_CLR  	LCD_CTRLB->BRR=LCD_SDA 
#define	LCD_CS_CLR  	LCD_CTRLB->BRR=LCD_CS 
#define	LCD_LED_CLR  	LCD_CTRLB->BRR=LCD_LED 

#define	LCD_RST_CLR  	LCD_CTRLD->BRR=LCD_RST
#define	LCD_RS_CLR  	LCD_CTRLD->BRR=LCD_RS 

#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //数据输出
#define LCD_DATAIN     LCD_DATA->IDR;   //数据输入

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 
void LCD_ST7735R_ptlon(Site_t site, Size_t size);
void LCD_ST7735R_dir(uint8_t option);
void LCD_GPIO_Init(void);
void Lcd_WriteIndex(uint8_t Index);
void Lcd_WriteData(uint8_t Data);
void Lcd_WriteReg(uint8_t Index,uint8_t Data);
uint16_t Lcd_ReadReg(uint8_t LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(uint16_t Color);
void Lcd_SetXY(uint16_t x,uint16_t y);
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data);
unsigned int Lcd_ReadPoint(uint16_t x,uint16_t y);
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void LCD_WriteData_16Bit(uint16_t Data);

#endif

