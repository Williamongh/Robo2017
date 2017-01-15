#include "LCD.h"



uint16_t  st7735r_h   = ST7735R_H;
uint16_t  st7735r_w   = ST7735R_W;
uint8_t   st7735r_dir = ST7735R_DIR_DEFAULT;

//Һ��IO��ʼ������
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

//��SPI���ߴ���һ��8λ����
void  SPI_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
	  LCD_SDA_SET; //�������
      else LCD_SDA_CLR;
	   
      LCD_SCL_CLR;       
      LCD_SCL_SET;
      Data<<=1; 
	}
}

//��Һ����дһ��8λָ��
void Lcd_WriteIndex(u8 Index)
{
   //SPI д����ʱ��ʼ
   LCD_CS_CLR;
   LCD_RS_CLR;
	 SPI_WriteData(Index);
   LCD_CS_SET;
}

//��Һ����дһ��8λ����
void Lcd_WriteData(u8 Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   SPI_WriteData(Data);
   LCD_CS_SET; 
}
//��Һ����дһ��16λ����
void LCD_WriteData_16Bit(u16 Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
	 SPI_WriteData(Data>>8); 	//д���8λ����
	 SPI_WriteData(Data); 			//д���8λ����
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
 *  @brief      ��ȡ ST7735R �߶�
 *  @return     ILI9341 �߶�
 *  @since      v5.0
 */
uint16_t ST7735R_get_h()
{
    return st7735r_h;
}

/*!
 *  @brief      ��ȡ ST7735R ���
 *  @return     ILI9341 ���
 *  @since      v5.0
 */
uint16_t ST7735R_get_w()
{
    return st7735r_w;
}

/*!
 *  @brief      ��ȡ ST7735R ��ʾ����
 *  @return     ST7735R ����
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
	
    //���ڳ�ʼ����ʱ����� ��Ļ���� ѡ�������ʼ����ɺ󣬲Ż�ȡ���
    size.W = LCD_W;
    size.H = LCD_H;

  LCD_rectangle(site, size, BLACK);     //��ʼ������	
	LCD_LED_SET;//ͨ��IO���Ʊ�����		
}

/*!
 *  @brief      ����ST7735R GRAMָ��ɨ�跽��
 *  @param      option    ����ѡ���������������������棩 Ϊ 0 ��90��Ϊ1��180��Ϊ2��270��Ϊ2��
 *  @since      v5.0
 */
void LCD_ST7735R_dir(uint8_t option)
{

    st7735r_dir = option;
    switch(option)
    {
    case 0:
        Lcd_WriteIndex(0x36); // �ڴ����ݷ��ʿ���  MX �е�ַ˳��, MY �е�ַ˳�� ��MV ���н��� ��ML ��ֱˢ��˳�� ,RGB  RGB-BGA˳��
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
        Lcd_WriteIndex(0x36); // �ڴ����ݷ��ʿ���  MX �е�ַ˳��, MY �е�ַ˳�� ��MV ���н��� ��ML ��ֱˢ��˳�� ,RGB  RGB-BGA˳��
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
        Lcd_WriteIndex(0x36); // �ڴ����ݷ��ʿ���  MX �е�ַ˳��, MY �е�ַ˳�� ��MV ���н��� ��ML ��ֱˢ��˳�� ,RGB  RGB-BGA˳��
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
        Lcd_WriteIndex(0x36); // �ڴ����ݷ��ʿ���  MX �е�ַ˳��, MY �е�ַ˳�� ��MV ���н��� ��ML ��ֱˢ��˳�� ,RGB  RGB-BGA˳��
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
 *  @brief      ���� ST7735R ����
 *  @param      site        ���Ͻ�����λ��
 *  @param      size        ������С
 *  @since      v5.0
 */
void LCD_ST7735R_ptlon(Site_t site, Size_t size)
{

    if(st7735r_dir&0x01)
    {
        site.y += 2;
        site.x += 3;     //Һ����Ҫƫ��һ�£��������ܿ���������		
    }
    else
    {
        site.y += 3;
        site.x += 2;     //Һ����Ҫƫ��һ�£��������ܿ���������					
    }

    Lcd_WriteIndex(0x2a);   //Partial Mode On  �ֲ�ģʽ
    Lcd_WriteData((uint8_t)(site.x >> 8)); //��8λ Sx
    Lcd_WriteData((uint8_t)site.x);   //��8λ Sx
    Lcd_WriteData((uint8_t)((site.x + size.W - 1) >> 8));
    Lcd_WriteData((uint8_t)(site.x + size.W - 1));

    Lcd_WriteIndex(0x2B);//Row Address Set  �е�ַ����
    Lcd_WriteData((uint8_t)(site.y >> 8));
    Lcd_WriteData((uint8_t)site.y);
    Lcd_WriteData((uint8_t)((site.y + size.H - 1) >> 8));
    Lcd_WriteData((uint8_t)(site.y + size.H - 1));

}



/*************************************************
��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����
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
��������LCD_Set_XY
���ܣ�����lcd��ʾ��ʼ��
��ڲ�����xy����
����ֵ����
*************************************************/
void Lcd_SetXY(u16 x,u16 y)
{
  	Lcd_SetRegion(x,y,x,y);
}

	
/*************************************************
��������LCD_DrawPoint
���ܣ���һ����
��ڲ�������
����ֵ����
*************************************************/
void Gui_DrawPoint(u16 x,u16 y,u16 Data)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    

/*****************************************
 �������ܣ���TFTĳһ�����ɫ                          
 ���ڲ�����color  ����ɫֵ                                 
******************************************/
unsigned int Lcd_ReadPoint(u16 x,u16 y)
{
  unsigned int Data;
  Lcd_SetXY(x,y);

  //Lcd_ReadData();//���������ֽ�
  //Data=Lcd_ReadData();
  Lcd_WriteData(Data);
  return Data;
}
/*************************************************
��������Lcd_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����
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
