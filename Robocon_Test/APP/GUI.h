#ifndef __GUI__H
#define __GUI__H

#include "include.h"
#define BINARY_BGCOLOR  WHITE       //定义二值化图像背景颜色
#define BINARY_COLOR    BLACK       //定义二值化图像前景颜色
#define GRAY_2_RGB565(gray)             ((uint16_t)((((uint8_t)(gray)>>3)<<11)|(((uint8_t)(gray)>>2)<<5)|((uint8_t)(gray)>>3)))

extern void LCD_point          (Site_t,                                        uint16_t rgb565);                 //画点
extern void LCD_points         (Site_t *site,  uint32_t point_num,               uint16_t rgb565);                 //画一堆点
extern void LCD_rectangle      (Site_t, Size_t,                                uint16_t rgb565);                 //画矩形
extern void LCD_char           (Site_t,        uint8_t ascii,                    uint16_t Color, uint16_t bkColor);  //显示8*16字符
extern void LCD_str            (Site_t,        uint8_t *Str,                     uint16_t Color, uint16_t bkColor);  //显示8*16字符串

extern void LCD_cross          (Site_t,uint16_t len,                              uint16_t rgb565);                 //画十字形

extern void LCD_clear          (uint16_t rgb565);     //清屏


extern void LCD_num            (Site_t,        uint32_t num,                     uint16_t Color, uint16_t bkColor);  //显示数字
#define MAX_NUM_BIT 4                                                                                   //数字的最大位数（用于清掉多余的屏幕残留数字）
#define LCD_num_C(site,num,color,bkColor)           LCD_num_BC(site, num,MAX_NUM_BIT,color,bkColor)     //显示数字（清掉多余的屏幕残留数字）
extern void LCD_num_BC         (Site_t,        uint32_t num, uint8_t max_num_bit,  uint16_t Color, uint16_t bkColor);  //显示数字（清掉多余的屏幕残留数字）

extern void LCD_Img_gray       (Site_t site, Size_t size, uint8_t *img);                   //显示灰度图像
extern void LCD_Img_gray_Z     (Site_t site, Size_t size, uint8_t *img, Size_t imgsize);   //显示灰度图像(可缩放)

#define BINARY_BGCOLOR  WHITE       //定义二值化图像背景颜色
#define BINARY_COLOR    BLACK       //定义二值化图像前景颜色
extern void LCD_Img_Binary     (Site_t site, Size_t size, uint8_t *img);                   //显示二值化图像
extern void LCD_Img_Binary_Z   (Site_t site, Size_t size, uint8_t *img, Size_t imgsize);   //显示二值化图像(可缩放)

extern void LCD_wave(Site_t site,Size_t size,uint8_t *img,uint8_t maxval,uint16_t Color ,uint16_t bkColor); //波形显示，带背景颜色（maxval 最大值表示超过此值的数都当作最大值处理）
extern void LCD_wave_display(Site_t site,Size_t size,uint8_t *img,uint8_t maxval,uint16_t Color);        //波形显示，不带背景颜色

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

