#include "LCD.h"



uint16_t  st7735r_h   = ST7735R_H;
uint16_t  st7735r_w   = ST7735R_W;
uint8_t   st7735r_dir = ST7735R_DIR_DEFAULT;

//液晶IO初始化配置
void LCD_GPIO_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
			
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB ,ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13| GPIO_Pin_15| GPIO_Pin_12| GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);


		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD ,ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
}

//向SPI总线传输一个8位数据
void  SPI_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
	  LCD_SDA_SET; //输出数据
      else LCD_SDA_CLR;
	   
      LCD_SCL_CLR;       
      LCD_SCL_SET;
      Data<<=1; 
	}
}

//向液晶屏写一个8位指令
void Lcd_WriteIndex(u8 Index)
{
   //SPI 写命令时序开始
   LCD_CS_CLR;
   LCD_RS_CLR;
	 SPI_WriteData(Index);
   LCD_CS_SET;
}

//向液晶屏写一个8位数据
void Lcd_WriteData(u8 Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   SPI_WriteData(Data);
   LCD_CS_SET; 
}
//向液晶屏写一个16位数据
void LCD_WriteData_16Bit(u16 Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
	 SPI_WriteData(Data>>8); 	//写入高8位数据
	 SPI_WriteData(Data); 			//写入低8位数据
   LCD_CS_SET; 
}

void Lcd_WriteReg(u8 Index,u8 Data)
{
	Lcd_WriteIndex(Index);
  Lcd_WriteData(Data);
}

void Lcd_Reset(void)
{
	LCD_RST_CLR;
	delay_ms(100);
	LCD_RST_SET;
	delay_ms(50);
}

/*!
 *  @brief      获取 ST7735R 高度
 *  @return     ILI9341 高度
 *  @since      v5.0
 */
uint16_t ST7735R_get_h()
{
    return st7735r_h;
}

/*!
 *  @brief      获取 ST7735R 宽度
 *  @return     ILI9341 宽度
 *  @since      v5.0
 */
uint16_t ST7735R_get_w()
{
    return st7735r_w;
}

/*!
 *  @brief      获取 ST7735R 显示方向
 *  @return     ST7735R 方向
 *  @since      v5.0
 */
uint16_t ST7735R_get_dir()
{
    return st7735r_dir;
}

//LCD Init For 1.44Inch LCD Panel with ST7735R.
void Lcd_Init(void)
{	
  Site_t site = {0, 0};
  Size_t size ;
//	
	
	LCD_GPIO_Init();
	Lcd_Reset(); //Reset before LCD Init.

	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	Lcd_WriteIndex(0x11);//Sleep exit 
	delay_ms (120);
		
	//ST7735R Frame Rate
	Lcd_WriteIndex(0xB1); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB2); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB3); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	
	Lcd_WriteIndex(0xB4); //Column inversion 
	Lcd_WriteData(0x07); 
	
	//ST7735R Power Sequence
	Lcd_WriteIndex(0xC0); 
	Lcd_WriteData(0xA2); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x84); 
	Lcd_WriteIndex(0xC1); 
	Lcd_WriteData(0xC5); 

	Lcd_WriteIndex(0xC2); 
	Lcd_WriteData(0x0A); 
	Lcd_WriteData(0x00); 

	Lcd_WriteIndex(0xC3); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0x2A); 
	Lcd_WriteIndex(0xC4); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0xEE); 
	
	Lcd_WriteIndex(0xC5); //VCOM 
	Lcd_WriteData(0x0E); 
	
	Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
	Lcd_WriteData(0xC8); 
	
	//ST7735R Gamma Sequence
	Lcd_WriteIndex(0xe0); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1a); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x18); 
	Lcd_WriteData(0x2f); 
	Lcd_WriteData(0x28); 
	Lcd_WriteData(0x20); 
	Lcd_WriteData(0x22); 
	Lcd_WriteData(0x1f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x23); 
	Lcd_WriteData(0x37); 
	Lcd_WriteData(0x00); 	
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x10); 

	Lcd_WriteIndex(0xe1); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x17); 
	Lcd_WriteData(0x33); 
	Lcd_WriteData(0x2c); 
	Lcd_WriteData(0x29); 
	Lcd_WriteData(0x2e); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x39); 
	Lcd_WriteData(0x3f); 
	Lcd_WriteData(0x00); 
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x03); 
	Lcd_WriteData(0x10);  
	
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x7f);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x9f);
	
	Lcd_WriteIndex(0xF0); //Enable test command  
	Lcd_WriteData(0x01); 
	Lcd_WriteIndex(0xF6); //Disable ram power save mode 
	Lcd_WriteData(0x00); 
	
	Lcd_WriteIndex(0x3A); //65k mode 
	Lcd_WriteData(0x05); 
	
	
	Lcd_WriteIndex(0x29);//Display on	 
  Lcd_WriteIndex(0x2c); //
	
  LCD_ST7735R_dir(st7735r_dir);	
	
    //由于初始化的时候进行 屏幕方向 选择，因而初始化完成后，才获取宽高
    size.W = LCD_W;
    size.H = LCD_H;

  LCD_rectangle(site, size, BLACK);     //初始化背景	
	LCD_LED_SET;//通过IO控制背光亮		
}

/*!
 *  @brief      设置ST7735R GRAM指针扫描方向
 *  @param      option    方向选择（正看（焊接排线在下面） 为 0 ，90度为1，180度为2，270度为2）
 *  @since      v5.0
 */
void LCD_ST7735R_dir(uint8_t option)
{

    st7735r_dir = option;
    switch(option)
    {
    case 0:
        Lcd_WriteIndex(0x36); // 内存数据访问控制  MX 列地址顺序, MY 行地址顺序 ，MV 行列交换 ，ML 垂直刷新顺序 ,RGB  RGB-BGA顺序
        Lcd_WriteData(0xc8);//0xc8  0xA8 0x08 0x68

        Lcd_WriteIndex(0x2a);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x00);
        Lcd_WriteData(128);

        Lcd_WriteIndex(0x2B);
        Lcd_WriteData(0x00);
        Lcd_WriteData(50);
        Lcd_WriteData(0x00);
        Lcd_WriteData(128+50);

        st7735r_h   = ST7735R_H;
        st7735r_w   = ST7735R_W;
        break;
    case 1:
        Lcd_WriteIndex(0x36); // 内存数据访问控制  MX 列地址顺序, MY 行地址顺序 ，MV 行列交换 ，ML 垂直刷新顺序 ,RGB  RGB-BGA顺序
        Lcd_WriteData(0xA8);//0xc8  0xA8 0x08 0x68

        Lcd_WriteIndex(0x2a);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x03);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x82);

        Lcd_WriteIndex(0x2B);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x02);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x81);

        st7735r_h   = ST7735R_W;
        st7735r_w   = ST7735R_H;
        break;
    case 2:
        Lcd_WriteIndex(0x36); // 内存数据访问控制  MX 列地址顺序, MY 行地址顺序 ，MV 行列交换 ，ML 垂直刷新顺序 ,RGB  RGB-BGA顺序
        Lcd_WriteData(0x08);//0xc8  0xA8 0x08 0x68

        Lcd_WriteIndex(0x2a);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x02);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x81);

        Lcd_WriteIndex(0x2B);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x03);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x82);

        st7735r_h   = ST7735R_H;
        st7735r_w   = ST7735R_W;
        break;
    case 3:
        Lcd_WriteIndex(0x36); // 内存数据访问控制  MX 列地址顺序, MY 行地址顺序 ，MV 行列交换 ，ML 垂直刷新顺序 ,RGB  RGB-BGA顺序
        Lcd_WriteData(0x68);//0xc8  0xA8 0x08 0x68

        Lcd_WriteIndex(0x2a);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x03);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x82);

        Lcd_WriteIndex(0x2B);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x00);
        Lcd_WriteData(0x00);
        Lcd_WriteData(128);

        st7735r_h   = ST7735R_W;
        st7735r_w   = ST7735R_H;
        break;
    default:
        break;
    }

}

/*!
 *  @brief      设置 ST7735R 开窗
 *  @param      site        左上角坐标位置
 *  @param      size        开窗大小
 *  @since      v5.0
 */
void LCD_ST7735R_ptlon(Site_t site, Size_t size)
{

    if(st7735r_dir&0x01)
    {
        site.y += 2;
        site.x += 3;     //液晶需要偏移一下，避免四周看不到的行		
    }
    else
    {
        site.y += 3;
        site.x += 2;     //液晶需要偏移一下，避免四周看不到的行					
    }

    Lcd_WriteIndex(0x2a);   //Partial Mode On  局部模式
    Lcd_WriteData((uint8_t)(site.x >> 8)); //高8位 Sx
    Lcd_WriteData((uint8_t)site.x);   //低8位 Sx
    Lcd_WriteData((uint8_t)((site.x + size.W - 1) >> 8));
    Lcd_WriteData((uint8_t)(site.x + size.W - 1));

    Lcd_WriteIndex(0x2B);//Row Address Set  行地址设置
    Lcd_WriteData((uint8_t)(site.y >> 8));
    Lcd_WriteData((uint8_t)site.y);
    Lcd_WriteData((uint8_t)((site.y + size.H - 1) >> 8));
    Lcd_WriteData((uint8_t)(site.y + size.H - 1));

}



/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end)
{		
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+3);
	
	Lcd_WriteIndex(0x2c);

}

/*************************************************
函数名：LCD_Set_XY
功能：设置lcd显示起始点
入口参数：xy坐标
返回值：无
*************************************************/
void Lcd_SetXY(u16 x,u16 y)
{
  	Lcd_SetRegion(x,y,x,y);
}

	
/*************************************************
函数名：LCD_DrawPoint
功能：画一个点
入口参数：无
返回值：无
*************************************************/
void Gui_DrawPoint(u16 x,u16 y,u16 Data)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    

/*****************************************
 函数功能：读TFT某一点的颜色                          
 出口参数：color  点颜色值                                 
******************************************/
unsigned int Lcd_ReadPoint(u16 x,u16 y)
{
  unsigned int Data;
  Lcd_SetXY(x,y);

  //Lcd_ReadData();//丢掉无用字节
  //Data=Lcd_ReadData();
  Lcd_WriteData(Data);
  return Data;
}
/*************************************************
函数名：Lcd_Clear
功能：全屏清屏函数
入口参数：填充颜色COLOR
返回值：无
*************************************************/
void Lcd_Clear(u16 Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   Lcd_WriteIndex(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	LCD_WriteData_16Bit(Color);
    }   
}
