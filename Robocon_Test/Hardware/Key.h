#ifndef 	__KEY__H
#define		__KEY__H

#include "include.h"

//�����Ƕ��尴����ʱ�䣬��λΪ �� 10ms���ж�ʱ�䣩
#define KEY_DOWN_TIME           1       //����ȷ�ϰ���ʱ��
#define KEY_HOLD_TIME           50      //����holdȷ��ʱ�䣬���253��������Ҫ�޸� keytime ������
                                        //�������һֱ����ȥ����ÿ�� KEY_HOLD_TIME - KEY_DOWN_TIME ʱ��ᷢ��һ�� KEY_HOLD ��Ϣ

//���尴����ϢFIFO��С
#define KEY_MSG_FIFO_SIZE       20      //��� 255��������Ҫ�޸�key_msg_front/key_msg_rear����

//�����˿ڵ�ö��
typedef enum
{
    KEY_U,  //��   15
    KEY_D,  //��   11

    KEY_L,  //��   13
    KEY_R,  //��   12

    KEY_A,  //ѡ�� 14

    KEY_MAX,
} KEY_e;


//key״̬ö�ٶ���
typedef enum
{
    KEY_ON  =   0,         //��������ʱ��Ӧ��ƽ
    KEY_OFF    =   1,         //��������ʱ��Ӧ��ƽ

    KEY_HOLD,               //��������(���ڶ�ʱ����ɨ��)

} KEY_STATUS_e;


//������Ϣ�ṹ��
typedef struct
{
    KEY_e           key;        //�������
    KEY_STATUS_e    status;     //����״̬
} KEY_MSG_t;


void KEY_Init(void);
void deal_key_event(void);
void Key_IRQHandler(void);
#endif

