#ifndef 	__KEY__H
#define		__KEY__H

#include "include.h"

//下面是定义按键的时间，单位为 ： 10ms（中断时间）
#define KEY_DOWN_TIME           1       //消抖确认按下时间
#define KEY_HOLD_TIME           50      //长按hold确认时间，最多253，否则需要修改 keytime 的类型
                                        //如果按键一直按下去，则每隔 KEY_HOLD_TIME - KEY_DOWN_TIME 时间会发送一个 KEY_HOLD 消息

//定义按键消息FIFO大小
#define KEY_MSG_FIFO_SIZE       20      //最多 255，否则需要修改key_msg_front/key_msg_rear类型

//按键端口的枚举
typedef enum
{
    KEY_U,  //上   15
    KEY_D,  //下   11

    KEY_L,  //左   13
    KEY_R,  //右   12

    KEY_A,  //选择 14

    KEY_MAX,
} KEY_e;


//key状态枚举定义
typedef enum
{
    KEY_ON  =   0,         //按键按下时对应电平
    KEY_OFF    =   1,         //按键弹起时对应电平

    KEY_HOLD,               //长按按键(用于定时按键扫描)

} KEY_STATUS_e;


//按键消息结构体
typedef struct
{
    KEY_e           key;        //按键编号
    KEY_STATUS_e    status;     //按键状态
} KEY_MSG_t;


void KEY_Init(void);
void deal_key_event(void);
void Key_IRQHandler(void);
#endif

