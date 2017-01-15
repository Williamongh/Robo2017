
#include "Key.h"

/*
 * ���� KEY ��Ŷ�Ӧ�Ĺܽ�
 */
uint16_t KeyPort[KEY_MAX]={GPIO_Pin_15,GPIO_Pin_11,GPIO_Pin_13,GPIO_Pin_12,GPIO_Pin_14};
extern uint8  car_ctrl;
/**************************����Ϊ��ͨ����*********************************/
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
	
    //��ʼ����ʱ����
    var_init();

    //ͬ��ȫ�����ݲ���ʾ
    var_syn(VAR_MAX);       //ͬ��ȫ�� ,������ͬ������ʾȫ������Ϊ�п���ͬ��ʧ�ܡ�
   
    save_var(VAR1,10);   
    save_var(VAR2,11);   
    save_var(VAR3,12);
    save_var(VAR4,13);
    save_var(VAR5,14);    
    save_var(VAR6,15);        
    save_var(car_ctrl,60);      
    var_display(VAR_MAX);   //��ʾȫ��
    	
	
}

/*!
 *  @brief      ��ȡkey״̬��������ʱ������
 *  @param      KEY_e           KEY���
 *  @return     KEY_STATUS_e    KEY״̬��KEY_OFF��KEY_ON��
 *  @since      v5.0
 *  Sample usage:
                    if(key_get(KEY_U) ==  KEY_ON)
                    {
                        printf("\n��������")
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
 *  @brief      ���key״̬������ʱ������
 *  @param      KEY_e           KEY���
 *  @return     KEY_STATUS_e    KEY״̬��KEY_ON��KEY_OFF��
 *  @since      v5.0
 *  Sample usage:
                    if(key_check(KEY_U) ==  KEY_ON)
                    {
                        printf("\n��������")
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


/*********************  ���´�����ʵ�ְ�����ʱɨ�裬������Ϣ��FIFO  ********************/
/*
 * ���尴����ϢFIFO״̬
 */
typedef enum
{
    KEY_MSG_EMPTY,      //û�а�����Ϣ
    KEY_MSG_NORMAL,     //�������а�����Ϣ��������
    KEY_MSG_FULL,       //������Ϣ��
} key_msg_e;

/*
 * ���尴����ϢFIFO��صı���
 */
KEY_MSG_t           key_msg[KEY_MSG_FIFO_SIZE];             //������ϢFIFO
volatile uint8      key_msg_front = 0, key_msg_rear = 0;    //����FIFO��ָ��
volatile uint8      key_msg_flag = KEY_MSG_EMPTY;           //������ϢFIFO״̬


/*!
 *  @brief      ���Ͱ�����Ϣ��FIFO
 *  @param      KEY_MSG_t       ������Ϣ
 *  @since      v5.0
 *  Sample usage:
                    KEY_MSG_t *keymsg;
                    keymsg.key      = KEY_U;
                    keymsg.status   = KEY_HOLD;
                    send_key_msg(keymsg);                   //����
 */
void send_key_msg(KEY_MSG_t keymsg)
{
    uint8 tmp;
    //������FIFO��
    if(key_msg_flag == KEY_MSG_FULL)
    {
        //����ֱ�Ӳ�����
        return ;
    }
    key_msg[key_msg_rear].key = keymsg.key;
    key_msg[key_msg_rear].status = keymsg.status;

    key_msg_rear++;

    if(key_msg_rear >= KEY_MSG_FIFO_SIZE)
    {
        key_msg_rear = 0;                       //��ͷ��ʼ
    }

    tmp = key_msg_rear;
    if(tmp == key_msg_front)                   //׷��ƨ���ˣ�����
    {
        key_msg_flag = KEY_MSG_FULL;
    }
    else
    {
        key_msg_flag = KEY_MSG_NORMAL;
    }
}


/*!
 *  @brief      ��FIFO���ȡ������Ϣ
 *  @param      KEY_MSG_t       ������Ϣ
 *  @return     �Ƿ��ȡ������Ϣ��1Ϊ��ȡ�ɹ���0Ϊû��ȡ��������Ϣ��
 *  @since      v5.0
 *  Sample usage:
                    KEY_MSG_t keymsg;
                    if(get_key_msg(&keymsg) == 1)
                    {
                        printf("\n���°���KEY%d,����Ϊ%d��0Ϊ���£�1Ϊ����2Ϊ������",keymsg.key,keymsg.status);
                    }
 */
uint8 get_key_msg(KEY_MSG_t *keymsg)
{
    uint8 tmp;

    if(key_msg_flag == KEY_MSG_EMPTY)               //������ϢFIFOΪ�գ�ֱ�ӷ���0
    {
        return 0;
    }

    keymsg->key = key_msg[key_msg_front].key;       //��FIFO�����л�ȡ����ֵ
    keymsg->status = key_msg[key_msg_front].status; //��FIFO�����л�ȡ��������

    key_msg_front++;                                //FIFO����ָ���1��ָ����һ����Ϣ

    if(key_msg_front >= KEY_MSG_FIFO_SIZE)          //FIFOָ�����������0��ʼ����
    {
        key_msg_front = 0;                          //��ͷ��ʼ������ѭ���������飩
    }

    tmp = key_msg_rear;
    if(key_msg_front == tmp)                        //�Ƚ϶��׺Ͷ�β�Ƿ�һ����һ�����ʾFIFO�ѿ���
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
 *  @brief      ��ʱ���key״̬
 *  @since      v5.0
 *  @note       �˺�����Ҫ���� ��ʱ�жϷ��������ʱ10msִ��һ��
 */
void Key_IRQHandler(void)
{

    KEY_e   keynum;
    static uint8 keytime[KEY_MAX];                          //��̬���飬��������鰴��ʱ��

    KEY_MSG_t keymsg;                                       //������Ϣ

    for(keynum = (KEY_e)0 ; keynum < KEY_MAX; keynum ++)    //ÿ��������ѯ
    {
        if(key_get(keynum) == KEY_ON)                     //�жϰ����Ƿ���
        {
            keytime[keynum]++;                              //����ʱ���ۼ�

            if(keytime[keynum] <= KEY_DOWN_TIME)            //�ж�ʱ���Ƿ�û��������ȷ�ϰ���ʱ��
            {
                continue;                                   //û�ﵽ��������ȴ�
            }
            else if(keytime[keynum] == KEY_DOWN_TIME + 1 )  //�ж�ʱ���Ƿ�Ϊ����ȷ�ϰ���ʱ��
            {
                //ȷ�ϰ�������
                keymsg.key = keynum;
                keymsg.status = KEY_ON;
                send_key_msg(keymsg);                       //�Ѱ���ֵ�Ͱ������ͷ�����Ϣ��FIFO
            }
            else if(keytime[keynum] <= KEY_HOLD_TIME)       //�Ƿ�û��������HOLD����ȷ��ʱ��
            {
                continue;                                   //û������������ȴ�
            }
            else if(keytime[keynum]  == KEY_HOLD_TIME + 1)  //�Ƿ�Ϊ����holdȷ��ʱ��
            {
                //ȷ�ϳ���HOLD
                keymsg.key = keynum;
                keymsg.status = KEY_HOLD;
                send_key_msg(keymsg);                       //����
                keytime[keynum] = KEY_DOWN_TIME + 1;
            }
            else
            {
                keytime[keynum] = KEY_DOWN_TIME + 1;        //�����ظ���� hold ״̬
            }
        }
        else
        {
            if(keytime[keynum] > KEY_DOWN_TIME)             //���ȷ�Ϲ����°���
            {
                keymsg.key = keynum;
                keymsg.status = KEY_OFF;
                send_key_msg(keymsg);                       //���Ͱ���������Ϣ
            }

            keytime[keynum] = 0;                            //ʱ���ۼ���0
        }
    }
}

void deal_key_event()
{
    KEY_MSG_t keymsg;

    while(get_key_msg(& keymsg))     //��ð����ͽ��д���
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

            case KEY_A:                //���� OK �� ͬ��ȫ�����ݲ���ʾ
                var_syn(VAR_MAX);       //ͬ��ȫ�� ,������ͬ������ʾȫ������Ϊ�п���ͬ��ʧ�ܡ�
                var_display(VAR_MAX);   //��ʾȫ��
                break;


            default:            //����Ҫ���� cancel
                break;
            }
        }
        else
        {
            //KEY_UP ,�����д���
        }
    }
}
