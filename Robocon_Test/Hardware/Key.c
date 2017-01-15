
#include "Key.h"

/*
 * 定义 KEY 编号对应的管脚
 */
uint16_t KeyPort[KEY_MAX]={GPIO_Pin_15,GPIO_Pin_11,GPIO_Pin_13,GPIO_Pin_12,GPIO_Pin_14};
extern uint8  car_ctrl;
/**************************以下为普通按键*********************************/
/*************************************************************************/
void KEY_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure; 


	/* config the extiline(PC13) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
												
	/* EXTI line gpio config(PD11 12 13 14 15) */	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //Down      
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
  GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //Right      
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //Left      
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //Set      
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //Up      
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
    //初始化临时变量
    var_init();

    //同步全部数据并显示
    var_syn(VAR_MAX);       //同步全部 ,必须先同步再显示全部，因为有可能同步失败。
   
    save_var(VAR1,10);   
    save_var(VAR2,11);   
    save_var(VAR3,12);
    save_var(VAR4,13);
    save_var(VAR5,14);    
    save_var(VAR6,15);        
    save_var(car_ctrl,60);      
    var_display(VAR_MAX);   //显示全部
    	
	
}

/*!
 *  @brief      获取key状态（不带延时消抖）
 *  @param      KEY_e           KEY编号
 *  @return     KEY_STATUS_e    KEY状态（KEY_OFF、KEY_ON）
 *  @since      v5.0
 *  Sample usage:
                    if(key_get(KEY_U) ==  KEY_ON)
                    {
                        printf("\n按键按下")
                    }
 */
KEY_STATUS_e key_get(KEY_e key)
{
    if(GPIO_ReadInputDataBit(GPIOD,KeyPort[key]) == KEY_ON)
    {
        return KEY_ON;
    }
    return KEY_OFF;
}


/*!
 *  @brief      检测key状态（带延时消抖）
 *  @param      KEY_e           KEY编号
 *  @return     KEY_STATUS_e    KEY状态（KEY_ON、KEY_OFF）
 *  @since      v5.0
 *  Sample usage:
                    if(key_check(KEY_U) ==  KEY_ON)
                    {
                        printf("\n按键按下")
                    }
 */
KEY_STATUS_e key_check(KEY_e key)
{
    if(key_get(key) == KEY_ON)
    {
        delay_ms(10);
        if( key_get(key) == KEY_ON)
        {
            return KEY_ON;
        }
    }
    return KEY_OFF;
}


/*********************  如下代码是实现按键定时扫描，发送消息到FIFO  ********************/
/*
 * 定义按键消息FIFO状态
 */
typedef enum
{
    KEY_MSG_EMPTY,      //没有按键消息
    KEY_MSG_NORMAL,     //正常，有按键消息，但不满
    KEY_MSG_FULL,       //按键消息满
} key_msg_e;

/*
 * 定义按键消息FIFO相关的变量
 */
KEY_MSG_t           key_msg[KEY_MSG_FIFO_SIZE];             //按键消息FIFO
volatile uint8      key_msg_front = 0, key_msg_rear = 0;    //接收FIFO的指针
volatile uint8      key_msg_flag = KEY_MSG_EMPTY;           //按键消息FIFO状态


/*!
 *  @brief      发送按键消息到FIFO
 *  @param      KEY_MSG_t       按键消息
 *  @since      v5.0
 *  Sample usage:
                    KEY_MSG_t *keymsg;
                    keymsg.key      = KEY_U;
                    keymsg.status   = KEY_HOLD;
                    send_key_msg(keymsg);                   //发送
 */
void send_key_msg(KEY_MSG_t keymsg)
{
    uint8 tmp;
    //保存在FIFO里
    if(key_msg_flag == KEY_MSG_FULL)
    {
        //满了直接不处理
        return ;
    }
    key_msg[key_msg_rear].key = keymsg.key;
    key_msg[key_msg_rear].status = keymsg.status;

    key_msg_rear++;

    if(key_msg_rear >= KEY_MSG_FIFO_SIZE)
    {
        key_msg_rear = 0;                       //重头开始
    }

    tmp = key_msg_rear;
    if(tmp == key_msg_front)                   //追到屁股了，满了
    {
        key_msg_flag = KEY_MSG_FULL;
    }
    else
    {
        key_msg_flag = KEY_MSG_NORMAL;
    }
}


/*!
 *  @brief      从FIFO里获取按键消息
 *  @param      KEY_MSG_t       按键消息
 *  @return     是否获取按键消息（1为获取成功，0为没获取到按键消息）
 *  @since      v5.0
 *  Sample usage:
                    KEY_MSG_t keymsg;
                    if(get_key_msg(&keymsg) == 1)
                    {
                        printf("\n按下按键KEY%d,类型为%d（0为按下，1为弹起，2为长按）",keymsg.key,keymsg.status);
                    }
 */
uint8 get_key_msg(KEY_MSG_t *keymsg)
{
    uint8 tmp;

    if(key_msg_flag == KEY_MSG_EMPTY)               //按键消息FIFO为空，直接返回0
    {
        return 0;
    }

    keymsg->key = key_msg[key_msg_front].key;       //从FIFO队首中获取按键值
    keymsg->status = key_msg[key_msg_front].status; //从FIFO队首中获取按键类型

    key_msg_front++;                                //FIFO队首指针加1，指向下一个消息

    if(key_msg_front >= KEY_MSG_FIFO_SIZE)          //FIFO指针队首溢出则从0开始计数
    {
        key_msg_front = 0;                          //重头开始计数（循环利用数组）
    }

    tmp = key_msg_rear;
    if(key_msg_front == tmp)                        //比较队首和队尾是否一样，一样则表示FIFO已空了
    {
        key_msg_flag = KEY_MSG_EMPTY;
    }
    else
    {
        key_msg_flag = KEY_MSG_NORMAL;
    }

    return 1;
}



/*!
 *  @brief      定时检测key状态
 *  @since      v5.0
 *  @note       此函数需要放入 定时中断服务函数里，定时10ms执行一次
 */
void Key_IRQHandler(void)
{

    KEY_e   keynum;
    static uint8 keytime[KEY_MAX];                          //静态数组，保存各数组按下时间

    KEY_MSG_t keymsg;                                       //按键消息

    for(keynum = (KEY_e)0 ; keynum < KEY_MAX; keynum ++)    //每个按键轮询
    {
        if(key_get(keynum) == KEY_ON)                     //判断按键是否按下
        {
            keytime[keynum]++;                              //按下时间累加

            if(keytime[keynum] <= KEY_DOWN_TIME)            //判断时间是否没超过消抖确认按下时间
            {
                continue;                                   //没达到，则继续等待
            }
            else if(keytime[keynum] == KEY_DOWN_TIME + 1 )  //判断时间是否为消抖确认按下时间
            {
                //确认按键按下
                keymsg.key = keynum;
                keymsg.status = KEY_ON;
                send_key_msg(keymsg);                       //把按键值和按键类型发送消息到FIFO
            }
            else if(keytime[keynum] <= KEY_HOLD_TIME)       //是否没超过长按HOLD按键确认时间
            {
                continue;                                   //没超过，则继续等待
            }
            else if(keytime[keynum]  == KEY_HOLD_TIME + 1)  //是否为长按hold确认时间
            {
                //确认长按HOLD
                keymsg.key = keynum;
                keymsg.status = KEY_HOLD;
                send_key_msg(keymsg);                       //发送
                keytime[keynum] = KEY_DOWN_TIME + 1;
            }
            else
            {
                keytime[keynum] = KEY_DOWN_TIME + 1;        //继续重复检测 hold 状态
            }
        }
        else
        {
            if(keytime[keynum] > KEY_DOWN_TIME)             //如果确认过按下按键
            {
                keymsg.key = keynum;
                keymsg.status = KEY_OFF;
                send_key_msg(keymsg);                       //发送按键弹起消息
            }

            keytime[keynum] = 0;                            //时间累计清0
        }
    }
}

void deal_key_event()
{
    KEY_MSG_t keymsg;

    while(get_key_msg(& keymsg))     //获得按键就进行处理
    {
        if(keymsg.status == KEY_ON)
        {
            switch(keymsg.key)
            {
            case KEY_R:
                var_value(VAR_ADD);
                break;

            case KEY_L:
                var_value(VAR_SUB);
                break;

            case KEY_U:
                var_select(VAR_PREV);
                break;

            case KEY_D:
                var_select(VAR_NEXT);
                break;

            case KEY_A:
                var_ok();
                break;

            default:
                break;
            }
        }
        else if(keymsg.status == KEY_HOLD)
        {
            switch(keymsg.key)
            {
            case KEY_R:
                var_value(VAR_ADD_HOLD);
                break;

            case KEY_L:
                var_value(VAR_SUB_HOLD);
                break;

            case KEY_U:
                var_select(VAR_PREV_HOLD);
                break;

            case KEY_D:
                var_select(VAR_NEXT_HOLD);
                break;

            case KEY_A:                //长按 OK 键 同步全部数据并显示
                var_syn(VAR_MAX);       //同步全部 ,必须先同步再显示全部，因为有可能同步失败。
                var_display(VAR_MAX);   //显示全部
                break;


            default:            //不需要处理 cancel
                break;
            }
        }
        else
        {
            //KEY_UP ,不进行处理
        }
    }
}
