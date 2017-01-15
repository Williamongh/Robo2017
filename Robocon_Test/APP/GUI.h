#ifndef __GUI__H
#define __GUI__H

#include "include.h"
#define BINARY_BGCOLOR  WHITE       //�����ֵ��ͼ�񱳾���ɫ
#define BINARY_COLOR    BLACK       //�����ֵ��ͼ��ǰ����ɫ
#define GRAY_2_RGB565(gray)             ((uint16_t)((((uint8_t)(gray)>>3)<<11)|(((uint8_t)(gray)>>2)<<5)|((uint8_t)(gray)>>3)))

extern void LCD_point          (Site_t,                                        uint16_t rgb565);                 //����
extern void LCD_points         (Site_t *site,  uint32_t point_num,               uint16_t rgb565);                 //��һ�ѵ�
extern void LCD_rectangle      (Site_t, Size_t,                                uint16_t rgb565);                 //������
extern void LCD_char           (Site_t,        uint8_t ascii,                    uint16_t Color, uint16_t bkColor);  //��ʾ8*16�ַ�
extern void LCD_str            (Site_t,        uint8_t *Str,                     uint16_t Color, uint16_t bkColor);  //��ʾ8*16�ַ���

extern void LCD_cross          (Site_t,uint16_t len,                              uint16_t rgb565);                 //��ʮ����

extern void LCD_clear          (uint16_t rgb565);     //����


extern void LCD_num            (Site_t,        uint32_t num,                     uint16_t Color, uint16_t bkColor);  //��ʾ����
#define MAX_NUM_BIT 4                                                                                   //���ֵ����λ������������������Ļ�������֣�
#define LCD_num_C(site,num,color,bkColor)           LCD_num_BC(site, num,MAX_NUM_BIT,color,bkColor)     //��ʾ���֣�����������Ļ�������֣�
extern void LCD_num_BC         (Site_t,        uint32_t num, uint8_t max_num_bit,  uint16_t Color, uint16_t bkColor);  //��ʾ���֣�����������Ļ�������֣�

extern void LCD_Img_gray       (Site_t site, Size_t size, uint8_t *img);                   //��ʾ�Ҷ�ͼ��
extern void LCD_Img_gray_Z     (Site_t site, Size_t size, uint8_t *img, Size_t imgsize);   //��ʾ�Ҷ�ͼ��(������)

#define BINARY_BGCOLOR  WHITE       //�����ֵ��ͼ�񱳾���ɫ
#define BINARY_COLOR    BLACK       //�����ֵ��ͼ��ǰ����ɫ
extern void LCD_Img_Binary     (Site_t site, Size_t size, uint8_t *img);                   //��ʾ��ֵ��ͼ��
extern void LCD_Img_Binary_Z   (Site_t site, Size_t size, uint8_t *img, Size_t imgsize);   //��ʾ��ֵ��ͼ��(������)

extern void LCD_wave(Site_t site,Size_t size,uint8_t *img,uint8_t maxval,uint16_t Color ,uint16_t bkColor); //������ʾ����������ɫ��maxval ���ֵ��ʾ������ֵ�������������ֵ����
extern void LCD_wave_display(Site_t site,Size_t size,uint8_t *img,uint8_t maxval,uint16_t Color);        //������ʾ������������ɫ

u16 LCD_BGR2RGB(u16 c);
void Gui_Circle(u16 X,u16 Y,u16 R,u16 fc); 
void Gui_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color);  
void Gui_box(u16 x, u16 y, u16 w, u16 h,u16 bc);
void Gui_box2(u16 x,u16 y,u16 w,u16 h, u8 mode);
void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2);
void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2);
void Gui_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void Gui_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void Gui_DrawFont_Num32(u16 x, u16 y, u16 fc, u16 bc, u16 num) ;

#endif

