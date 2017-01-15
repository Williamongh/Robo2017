
#include "GUI.h"
#include "Font.h"


/*!
 *  @brief      ��ʾʵ�ľ���
 *  @param      site    ���Ͻ�����
 *  @param      size    ���δ�С
 *  @param      rgb565  ��ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        Size_t size = {50,60};  // W = 50 ,H = 60
                        LCD_rectangle(site, size, RED);
 */
void LCD_rectangle(Site_t site, Size_t size, uint16_t rgb565)
{ 
    uint32_t n, temp;

    LCD_ST7735R_ptlon(site, size);              //����

    temp = (uint32_t)size.W * size.H;
    Lcd_WriteIndex(0x2C);           //д�ڴ�
    for(n = 0; n < temp; n++)
    {
			LCD_WriteData_16Bit(rgb565);
    }
}

void LCD_clear(uint16_t rgb565)     //����
{
    Site_t site = {0,0};
    Size_t size;
    size.H = LCD_H;
    size.W = LCD_W;

    LCD_rectangle(site, size, rgb565);

}


//��ʮ����
void LCD_cross(Site_t site,uint16_t len,uint16_t Color)
{
    //������ֱ��
    Site_t sitetmp;
    Size_t size;
    int16_t  stmp,etmp;
    uint16_t w = LCD_W,h = LCD_H;


    stmp = site.x - len/2;                          //����ˮƽ�ߵ�x�����ͽ����㣬���Ʋ�����Һ����Χ
    if(stmp < 0)stmp = 0;
    etmp = site.x + len/2;
    if(etmp >= w)etmp= w-1;

    sitetmp.x = stmp;
    sitetmp.y = site.y;
    size.W = etmp - stmp +1;
    size.H = 1;
    LCD_rectangle(sitetmp,size, Color);

    stmp = site.y - len/2;                          //����ˮƽ�ߵ�x�����ͽ����㣬���Ʋ�����Һ����Χ
    if(stmp < 0)stmp = 0;
    etmp = site.y + len/2;
    if(etmp >= h)etmp= h-1;

    sitetmp.x = site.x;
    sitetmp.y = stmp;
    size.W = 1;
    size.H = etmp - stmp +1;
    LCD_rectangle(sitetmp,size, Color);

}

/*!
 *  @brief      ����
 *  @param      site    ���Ͻ�����
 *  @param      rgb565  ��ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_point(site, RED);
 */
void LCD_point(Site_t site, uint16_t rgb565)
{
    Size_t size = {1, 1};
    LCD_ST7735R_ptlon(site, size);
    Lcd_WriteIndex(0x2C);           //д�ڴ�
    LCD_WriteData_16Bit(rgb565);                //д����
}

/*!
 *  @brief      ��һ�ѵ�
 *  @param      site        ����������
 *  @param      point_num   �������
 *  @param      rgb565      ��ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site[3] = {{10,20},{11,21},{12,22}};   //3���㣬����ֱ���  {10,20},{11,21},{12,22}
                        LCD_points(site,3, RED);
 */
void LCD_points          (Site_t *site,uint32_t point_num, uint16_t rgb565)                 //��һ�ѵ�
{
    while(point_num--)
    {
        LCD_point(site[point_num],rgb565);                 //����
    }
}


/*!
 *  @brief      ��ʾ�ַ�
 *  @param      site    ���Ͻ�����
 *  @param      ascii   �ַ�
 *  @param      Color   ������ɫ
 *  @param      bkColor ������ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_char(site,'0', BLUE,RED);
 */
void LCD_char(Site_t site, uint8_t ascii, uint16_t Color, uint16_t bkColor)
{
#define MAX_CHAR_POSX (LCD_W-8)
#define MAX_CHAR_POSY (LCD_H-16)

    uint8_t temp, t, pos;
    Size_t size = {8, 16};

    if(site.x > MAX_CHAR_POSX || site.y > MAX_CHAR_POSY)
    {
        return;
    }

    LCD_ST7735R_ptlon(site, size);

    Lcd_WriteIndex(0x2C);           //д�ڴ�

    for (pos = 0; pos < 16; pos++)
    {
        temp = ascii_8x16[((ascii-0x20)*16)+pos];

        for(t = 0; t < 8; t++)
        {

            if(temp & 0x80)
            {
                    LCD_WriteData_16Bit(Color);
            }
            else
            {
                LCD_WriteData_16Bit(bkColor);
            }
            temp <<= 1;
        }
    }
    return;
#undef MAX_CHAR_POSX
#undef MAX_CHAR_POSY
}

/*!
 *  @brief      ��ʾ�ַ���
 *  @param      site    ���Ͻ�����
 *  @param      Str     �ַ�����ַ
 *  @param      Color   ������ɫ
 *  @param      bkColor ������ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_str(site,"www.vcan123.com", BLUE,RED);
 */
void LCD_str(Site_t site, uint8_t *Str, uint16_t Color, uint16_t bkColor)
{
#define MAX_CHAR_POSX (LCD_W-8)
#define MAX_CHAR_POSY (LCD_H-16)
    while(*Str != '\0')
    {
        if(site.x > MAX_CHAR_POSX )
        {
            //����
            site.x = 0;
            site.y += 16;
        }
        if(site.y > MAX_CHAR_POSY )
        {
            //һ��
            site.y = 0;
            site.x = 0;
        }

        LCD_char(site, *Str, Color, bkColor);
        site.x += 8;
        Str ++ ;
    }
#undef MAX_CHAR_POSX
#undef MAX_CHAR_POSY
}

/*!
 *  @brief      ��ʾ����
 *  @param      site    ���Ͻ�����
 *  @param      num     ����
 *  @param      Color   ������ɫ
 *  @param      bkColor ������ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_num(site,123, BLUE,RED);
 */
void LCD_num(Site_t site, uint32_t num, uint16_t Color, uint16_t bkColor)
{
    uint32_t res = num;
    uint8_t t = 0;
    Site_t sitetemp;
    sitetemp.y = site.y;

    if( num == 0 )
    {
        LCD_char(site, '0', Color, bkColor);
        return;
    }
    while( res )  /*�õ����ֳ���t*/
    {
        res /= 10;
        t++;
    }

    while(num)
    {
        sitetemp.x = site.x + (8 * (t--) - 8);
        LCD_char(sitetemp, (num % 10) + '0', Color, bkColor);
        num /= 10 ;
    }
}

/*!
 *  @brief      ��ʾ���֣���ն����λ��
 *  @param      site            ���Ͻ�����
 *  @param      num             ����
 *  @param      max_num_bit     ����λ��
 *  @param      Color           ������ɫ
 *  @param      bkColor         ������ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_num_BC(site,123,5, BLUE,RED);
 */
void LCD_num_BC(Site_t site, uint32_t num, uint8_t max_num_bit, uint16_t Color, uint16_t bkColor)
{
    uint32_t res = num;
    uint8_t t = 0;
    Site_t sitetemp;
    Size_t size;

    sitetemp.y = site.y;

    if( num == 0 )
    {
        LCD_char(site, '0', Color, bkColor);

        site.x += 8;
        size.H  = 16;
        size.W  = 8 * (max_num_bit - 1);
        LCD_rectangle(site, size, bkColor);

        return;
    }
    while( res )            /*�õ����ֳ���t*/
    {
        res /= 10;
        t++;
    }
    if(t >= max_num_bit )    //������󳤶�
    {
        t = max_num_bit;
    }

    res = t;

    while( t != 0 )
    {
        sitetemp.x = site.x + (8 * (t--) - 8);
        LCD_char(sitetemp, (num % 10) + '0', Color, bkColor);
        num /= 10 ;
    }

    if(res != max_num_bit )
    {
        size.W = 8 * (max_num_bit - res);
        site.x += (8 * res);
        size.H  = 16;
        LCD_rectangle(site, size, bkColor);
    }
}

void LCD_wave(Site_t site,Size_t size,uint8_t *img,uint8_t maxval,uint16_t Color ,uint16_t bkColor)
{

    uint8_t h;
    uint16_t y = site.y + size.H - 1;

    LCD_rectangle(site, size,bkColor);
    site.x += size.W;
    img  += (size.W - 1);
    while(size.W --)
    {
        if(*img >= maxval )
        {
            h = size.H - 1;
        }
        else
        {
            h = ((*img )* size.H )/maxval;
        }
        site.y = y - h ;
        site.x--;
        img --;
        LCD_point(site, Color);
    }
}

void LCD_wave_display(Site_t site,Size_t size,uint8_t *img,uint8_t maxval,uint16_t Color)
{

    uint8_t h;
    uint16_t y = site.y + size.H - 1;

    site.x += size.W;
    img  += (size.W - 1);
    while(size.W --)
    {
        if(*img >= maxval )
        {
            h = size.H - 1;
        }
        else
        {
            h = ((*img )* size.H )/maxval;
        }
        site.y = y - h ;
        site.x--;
        img --;
        LCD_point(site, Color);
    }
}










/*!
 *  @brief      �Ҷ�ͼ����ʾ
 *  @param      site            ���Ͻ�����
 *  @param      size            ��ʾͼ���С
 *  @param      img             ͼ���ַ
 *  @since      v5.0
 *  Sample usage:       Site_t site = {10,20};      //x = 10 ,y = 20
                        Size_t size = {320,240};    //W = 320,H = 240
                        LCD_Img_gray(site, size, img);
 */
void LCD_Img_gray(Site_t site, Size_t size, uint8_t *img)
{
    uint32_t     total = (size.H * size.W);
    uint16_t     imgtemp;
    uint8_t     *pimg = (uint8_t *)img;

    LCD_ST7735R_ptlon(site, size);

    Lcd_WriteIndex(0x2C);           //д�ڴ�

    while(total--)
    {
        imgtemp     = (uint16_t) * (pimg++);
        imgtemp = GRAY_2_RGB565(imgtemp);
        LCD_WriteData_16Bit( imgtemp );               //дͼ������
    }
}

/*!
 *  @brief      ���ŻҶ�ͼ����ʾ
 *  @param      site            ���Ͻ�����
 *  @param      size            ��ʾͼ���С
 *  @param      img             ͼ���ַ
 *  @param      imgsize         ͼ���С
 *  @since      v5.0
 *  Sample usage:       Site_t site = {10,20};          //x = 10 ,y = 20
                        Size_t size = {80,60};          //W = 80,H = 60
                        Size_t imgsize = {320,240};     //W = 320,H = 240
                        LCD_Img_gray_Z(site, size, img,imgsize);
 */
void LCD_Img_gray_Z(Site_t site, Size_t size, uint8_t *img, Size_t imgsize)
{

    uint32_t temp, tempY;
    uint16_t x, y;
    uint16_t X, Y;
    uint8_t *pimg = (uint8_t *)img;
    uint16_t rgb;
	
    LCD_ST7735R_ptlon(site, size);

    Lcd_WriteIndex(0x2C);           //д�ڴ�

    for(y = 0; y < size.H; y++)
    {
        Y = ( (  y * imgsize.H   ) / size.H) ;
        tempY = Y * imgsize.W ;

        for(x = 0; x < size.W; x++)
        {
            X = ( x * imgsize.W  ) / size.W ;
            temp = tempY + X;
            rgb = GRAY_2_RGB565(pimg[temp]);    //
            LCD_WriteData_16Bit(rgb);
        }
    }
}



void LCD_Img_Binary(Site_t site, Size_t size, uint8_t *img)
{
    uint32_t     total = (size.H * size.W) / 8;
    uint8_t     imgtemp;
    uint8_t       bitindex;
    uint8_t     *pimg = (uint8_t *)img;

    LCD_ST7735R_ptlon(site, size);

    Lcd_WriteIndex(0x2C);           //д�ڴ�

    while(total--)
    {
        imgtemp     = *(pimg++);
        bitindex    = 8;
        while(bitindex--)
        {
            if( imgtemp & (0x01 << bitindex) )
            {
                LCD_WriteData_16Bit( BINARY_COLOR );      //дͼ������
            }
            else
            {
                LCD_WriteData_16Bit(  BINARY_BGCOLOR  );      //дͼ������
            }
        }
    }
}

void LCD_Img_Binary_Z(Site_t site, Size_t size, uint8_t *img, Size_t imgsize)
{

    uint32_t temp, tempY;
    uint16_t x, y;
    uint16_t X, Y;
    uint8_t *pimg = (uint8_t *)img;

    LCD_ST7735R_ptlon(site, size);

    Lcd_WriteIndex(0x2C);           //д�ڴ�

    for(y = 0; y < size.H; y++)
    {
        Y = ( (  y * imgsize.H  ) / size.H) ;
        tempY = Y * imgsize.W ;

        for(x = 0; x < size.W; x++)
        {
            X = (( x * imgsize.W  ) / size.W) ;
            temp = tempY + X;
            if( (pimg[temp>>3] & (1 << (7 - (temp & 0x07))) ) == 0  )
            {
                LCD_WriteData_16Bit( BINARY_BGCOLOR );        //дͼ������
            }
            else
            {
                LCD_WriteData_16Bit( BINARY_COLOR );      //дͼ������
            }
        }
    }
}




//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
u16 LCD_BGR2RGB(u16 c)
{
  u16  r,g,b,rgb;   
  b=(c>>0)&0x1f;
  g=(c>>5)&0x3f;
  r=(c>>11)&0x1f;	 
  rgb=(b<<11)+(g<<5)+(r<<0);		 
  return(rgb);

}

void Gui_Circle(u16 X,u16 Y,u16 R,u16 fc) 
{//Bresenham�㷨 
    unsigned short  a,b; 
    int c; 
    a=0; 
    b=R; 
    c=3-2*R; 
    while (a<b) 
    { 
        Gui_DrawPoint(X+a,Y+b,fc);     //        7 
        Gui_DrawPoint(X-a,Y+b,fc);     //        6 
        Gui_DrawPoint(X+a,Y-b,fc);     //        2 
        Gui_DrawPoint(X-a,Y-b,fc);     //        3 
        Gui_DrawPoint(X+b,Y+a,fc);     //        8 
        Gui_DrawPoint(X-b,Y+a,fc);     //        5 
        Gui_DrawPoint(X+b,Y-a,fc);     //        1 
        Gui_DrawPoint(X-b,Y-a,fc);     //        4 

        if(c<0) c=c+4*a+6; 
        else 
        { 
            c=c+4*(a-b)+10; 
            b-=1; 
        } 
       a+=1; 
    } 
    if (a==b) 
    { 
        Gui_DrawPoint(X+a,Y+b,fc); 
        Gui_DrawPoint(X+a,Y+b,fc); 
        Gui_DrawPoint(X+a,Y-b,fc); 
        Gui_DrawPoint(X-a,Y-b,fc); 
        Gui_DrawPoint(X+b,Y+a,fc); 
        Gui_DrawPoint(X-b,Y+a,fc); 
        Gui_DrawPoint(X+b,Y-a,fc); 
        Gui_DrawPoint(X-b,Y-a,fc); 
    } 
	
} 
//���ߺ�����ʹ��Bresenham �����㷨
void Gui_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color)   
{
int dx,             // difference in x's
    dy,             // difference in y's
    dx2,            // dx,dy * 2
    dy2, 
    x_inc,          // amount in pixel space to move during drawing
    y_inc,          // amount in pixel space to move during drawing
    error,          // the discriminant i.e. error i.e. decision variable
    index;          // used for looping	


	Lcd_SetXY(x0,y0);
	dx = x1-x0;//����x����
	dy = y1-y0;//����y����

	if (dx>=0)
	{
		x_inc = 1;
	}
	else
	{
		x_inc = -1;
		dx    = -dx;  
	} 
	
	if (dy>=0)
	{
		y_inc = 1;
	} 
	else
	{
		y_inc = -1;
		dy    = -dy; 
	} 

	dx2 = dx << 1;
	dy2 = dy << 1;

	if (dx > dy)//x�������y���룬��ôÿ��x����ֻ��һ���㣬ÿ��y���������ɸ���
	{//���ߵĵ�������x���룬��x���������
		// initialize error term
		error = dy2 - dx; 

		// draw the line
		for (index=0; index <= dx; index++)//Ҫ���ĵ������ᳬ��x����
		{
			//����
			Gui_DrawPoint(x0,y0,Color);
			
			// test if error has overflowed
			if (error >= 0) //�Ƿ���Ҫ����y����ֵ
			{
				error-=dx2;

				// move to next line
				y0+=y_inc;//����y����ֵ
			} // end if error overflowed

			// adjust the error term
			error+=dy2;

			// move to the next pixel
			x0+=x_inc;//x����ֵÿ�λ���󶼵���1
		} // end for
	} // end if |slope| <= 1
	else//y�����x�ᣬ��ÿ��y����ֻ��һ���㣬x�����ɸ���
	{//��y��Ϊ��������
		// initialize error term
		error = dx2 - dy; 

		// draw the line
		for (index=0; index <= dy; index++)
		{
			// set the pixel
			Gui_DrawPoint(x0,y0,Color);

			// test if error overflowed
			if (error >= 0)
			{
				error-=dy2;

				// move to next line
				x0+=x_inc;
			} // end if error overflowed

			// adjust the error term
			error+=dx2;

			// move to the next pixel
			y0+=y_inc;
		} // end for
	} // end else |slope| > 1
}



void Gui_box(u16 x, u16 y, u16 w, u16 h,u16 bc)
{
	Gui_DrawLine(x,y,x+w,y,0xEF7D);
	Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0x2965);
	Gui_DrawLine(x,y+h,x+w,y+h,0x2965);
	Gui_DrawLine(x,y,x,y+h,0xEF7D);
    Gui_DrawLine(x+1,y+1,x+1+w-2,y+1+h-2,bc);
}
void Gui_box2(u16 x,u16 y,u16 w,u16 h, u8 mode)
{
	if (mode==0)	{
		Gui_DrawLine(x,y,x+w,y,0xEF7D);
		Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0x2965);
		Gui_DrawLine(x,y+h,x+w,y+h,0x2965);
		Gui_DrawLine(x,y,x,y+h,0xEF7D);
		}
	if (mode==1)	{
		Gui_DrawLine(x,y,x+w,y,0x2965);
		Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0xEF7D);
		Gui_DrawLine(x,y+h,x+w,y+h,0xEF7D);
		Gui_DrawLine(x,y,x,y+h,0x2965);
	}
	if (mode==2)	{
		Gui_DrawLine(x,y,x+w,y,0xffff);
		Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0xffff);
		Gui_DrawLine(x,y+h,x+w,y+h,0xffff);
		Gui_DrawLine(x,y,x,y+h,0xffff);
	}
}


/**************************************************************************************
��������: ����Ļ��ʾһ͹��İ�ť��
��    ��: u16 x1,y1,x2,y2 ��ť�����ϽǺ����½�����
��    ��: ��
**************************************************************************************/
void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2)
{
	Gui_DrawLine(x1,  y1,  x2,y1, GRAY2);  //H
	Gui_DrawLine(x1+1,y1+1,x2,y1+1, GRAY1);  //H
	Gui_DrawLine(x1,  y1,  x1,y2, GRAY2);  //V
	Gui_DrawLine(x1+1,y1+1,x1+1,y2, GRAY1);  //V
	Gui_DrawLine(x1,  y2,  x2,y2, WHITE);  //H
	Gui_DrawLine(x2,  y1,  x2,y2, WHITE);  //V
}

/**************************************************************************************
��������: ����Ļ��ʾһ���µİ�ť��
��    ��: u16 x1,y1,x2,y2 ��ť�����ϽǺ����½�����
��    ��: ��
**************************************************************************************/
void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2)
{
	Gui_DrawLine(x1,  y1,  x2,y1, WHITE); //H
	Gui_DrawLine(x1,  y1,  x1,y2, WHITE); //V
	
	Gui_DrawLine(x1+1,y2-1,x2,y2-1, GRAY1);  //H
	Gui_DrawLine(x1,  y2,  x2,y2, GRAY2);  //H
	Gui_DrawLine(x2-1,y1+1,x2-1,y2, GRAY1);  //V
    Gui_DrawLine(x2  ,y1  ,x2,y2, GRAY2); //V
}


void Gui_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
	unsigned char i,j;
	unsigned short k,x0;
	x0=x;

	while(*s) 
	{	
		if((*s) < 128) 
		{
			k=*s;
			if (k==13) 
			{
				x=x0;
				y+=16;
			}
			else 
			{
				if (k>32) k-=32; else k=0;
	
			    for(i=0;i<16;i++)
				for(j=0;j<8;j++) 
					{
				    	if(asc16[k*16+i]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
						else 
						{
							if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
						}
					}
				x+=8;
			}
			s++;
		}
			
		else 
		{
		

			for (k=0;k<hz16_num;k++) 
			{
			  if ((hz16[k].Index[0]==*(s))&&(hz16[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<16;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
								else {
									if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2+1]&(0x80>>j))	Gui_DrawPoint(x+j+8,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j+8,y+i,bc);
								}
							}
				    }
				}
			  }
			s+=2;x+=16;
		} 
		
	}
}

void Gui_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
	unsigned char i,j;
	unsigned short k;

	while(*s) 
	{
		if( *s < 0x80 ) 
		{
			k=*s;
			if (k>32) k-=32; else k=0;

		    for(i=0;i<16;i++)
			for(j=0;j<8;j++) 
				{
			    	if(asc16[k*16+i]&(0x80>>j))	
					Gui_DrawPoint(x+j,y+i,fc);
					else 
					{
						if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
					}
				}
			s++;x+=8;
		}
		else 
		{

			for (k=0;k<hz24_num;k++) 
			{
			  if ((hz24[k].Index[0]==*(s))&&(hz24[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<24;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3]&(0x80>>j))
								Gui_DrawPoint(x+j,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3+1]&(0x80>>j))	Gui_DrawPoint(x+j+8,y+i,fc);
								else {
									if (fc!=bc) Gui_DrawPoint(x+j+8,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3+2]&(0x80>>j))	
								Gui_DrawPoint(x+j+16,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j+16,y+i,bc);
								}
							}
				    }
			  }
			}
			s+=2;x+=24;
		}
	}
}
void Gui_DrawFont_Num32(u16 x, u16 y, u16 fc, u16 bc, u16 num)
{
	unsigned char i,j,k,c;
	//lcd_text_any(x+94+i*42,y+34,32,32,0x7E8,0x0,sz32,knum[i]);
//	w=w/8;

    for(i=0;i<32;i++)
	{
		for(j=0;j<4;j++) 
		{
			c=*(sz32+num*32*4+i*4+j);
			for (k=0;k<8;k++)	
			{
	
		    	if(c&(0x80>>k))	Gui_DrawPoint(x+j*8+k,y+i,fc);
				else {
					if (fc!=bc) Gui_DrawPoint(x+j*8+k,y+i,bc);
				}
			}
		}
	}
}


