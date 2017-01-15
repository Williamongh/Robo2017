#include "UI_VAR.h"





#define VAR_VALUE(var_tab)      num_info[var_tab].val       //ָ����ŵı�����ֵ
#define VAR_OLDVALUE(var_tab)   num_info[var_tab].oldval    //ָ����ŵı��������ȷ��ֵ
#define VAR_MAXVALUE(var_tab)   num_info[var_tab].maxval
#define VAR_MINVALUE(var_tab)   num_info[var_tab].minval
#define VAR_SITE(var_tab)       num_info[var_tab].site
#define COM_LEN     2   //com����ռ�õ��ֽ�

uint8  car_ctrl = 0;

uint32 *var_addr[VAR_MAX] = {(uint32 *)&car_ctrl,(uint32 *)&var1, (uint32 *)&var2, (uint32 *)&var3, (uint32 *)&var4, (uint32 *)&var5, (uint32 *)&var6};


ui_var_info_t  num_info[VAR_MAX] =
{
    //  {val,oldval,minval,maxval,{x,y}}
    //val,oldval,���ڵ���key_event_init��ʱ������Ӧ�����︳ֵ���������������ֵ��������д
    //��Ҫ����minval,maxval,{x,y}
    //���ע����Сֵ��Ҫ�������ֵ
    {0, 0, 0, 200, {10,51}},      //���� car_ctrl��
    {0, 0, 0, 200, {10, 17}},                //���� SpeedStrt
    {0, 0, 0, 200, {10, 84}},               //���� SpeedCur
    {0, 0, 0, 9, {84, 17}},               //���� ServoDǧλ
    {0, 0, 0, 9, {93, 17}},               //���� ServoD��λ
    {0, 0, 0, 99, {102, 17}},             //���� ServoDʮλ
    {0, 0, 0, 999, {84, 51}}              //���� ServP
};

uint8   new_tab = 0;        //��ǰѡ��ı������
uint32  last_tab;           //�����յ��ı������



//ͬ��ָ����ֵ��tab Ϊ VAR_NUM ʱ��ʾȫ��ͬ����С����ͬ����Ӧ��
//������ͬ������ʾȫ������Ϊ�п���ͬ��ʧ�ܡ�
//static uint8 var_syn(uint8 tab);         //ͬ�����ݣ�1��ʾ�ɹ���0��ʾʧ��

void save_var2buff(var_tab_e var_num, uint8 *sendbuf);              //����Ҫ���͵ı���������д�뵽������

void var_init()
{
    uint8   var_num;
    uint32  vartemp;

    for(var_num = 0; var_num < VAR_MAX; var_num++)
    {
        get_var((var_tab_e)var_num, &vartemp);
        num_info[var_num].val       = vartemp;
        num_info[var_num].oldval    = vartemp;

        //�����Сֵ�����ֵ
        ASSERT(num_info[var_num].maxval  >=  num_info[var_num].minval );
    }
}

void save_var(var_tab_e var_tal, uint32 var_data)
{
    if(var_tal <= VAR_8BIT)
    {
        *((uint8 *)(var_addr[var_tal])) = var_data;
    }
    else if(var_tal <= VAR_16BIT)
    {
        *((uint16 *)(var_addr[var_tal])) = var_data;
    }
    else if(var_tal <= VAR_32BIT)
    {
        *((uint32 *)(var_addr[var_tal])) = var_data;
    }

    VAR_VALUE(var_tal) = var_data;
    VAR_OLDVALUE(var_tal) = var_data;
}

void get_var(var_tab_e var_tal, uint32 *var_data)
{
    if(var_tal <= VAR_8BIT)
    {
        *var_data = (uint32) * ((uint8 *)(var_addr[var_tal]));
    }
    else if(var_tal <= VAR_16BIT)
    {
        *var_data = (uint32) * ((uint16 *)(var_addr[var_tal])) ;
    }
    else if(var_tal <= VAR_32BIT)
    {
        *var_data = (uint32) * ((uint32 *)(var_addr[var_tal]));
    }
}


void updata_var(var_tab_e var_tal)
{
    uint32 vartemp;

    get_var(var_tal, &vartemp);

    VAR_VALUE(var_tal) = vartemp;
}

//�Ա����ļӼ����д���
void var_value(ui_var_event_e ctrl)
{
    ASSERT(new_tab < VAR_MAX);


    //�޸ĵ�ǰ������ֵ
    switch(ctrl)
    {
    case VAR_ADD:
        if(VAR_VALUE(new_tab) < VAR_MAXVALUE(new_tab))
        {
            VAR_VALUE(new_tab)++;
        }
        else
        {
            VAR_VALUE(new_tab) = VAR_MINVALUE(new_tab);
        }
        break;

    case VAR_SUB:
        if(VAR_VALUE(new_tab) > VAR_MINVALUE(new_tab))
        {
            VAR_VALUE(new_tab)--;
        }
        else
        {
            VAR_VALUE(new_tab) = VAR_MAXVALUE(new_tab) ;//��Сֵ��һΪ���ֵ
        }
        break;

    case VAR_ADD_HOLD:
        if(   (VAR_MAXVALUE(new_tab) - VAR_VALUE(new_tab))  >  VAR_VALUE_HOLE_OFFSET )
        {
            VAR_VALUE(new_tab) += VAR_VALUE_HOLE_OFFSET;
        }
        else
        {
            VAR_VALUE(new_tab) = VAR_MINVALUE(new_tab);
        }
        break;

    case VAR_SUB_HOLD:
        if( ( VAR_VALUE(new_tab) - VAR_MINVALUE(new_tab)) > VAR_VALUE_HOLE_OFFSET  )
        {
            VAR_VALUE(new_tab) -= VAR_VALUE_HOLE_OFFSET;
        }
        else
        {
            VAR_VALUE(new_tab) = VAR_MAXVALUE(new_tab) ;//��Сֵ��һΪ���ֵ
        }
        break;

    default:                        //��Чѡ�񣬲���Ҫ�л�
        break;
    }

    var_display(new_tab);
}

//�Ա�������ѡ��
void var_select(ui_var_event_e  ctrl)
{
    ASSERT(new_tab < VAR_MAX);

    uint8 old_tab = new_tab;       //�ȱ��ݵ�ǰ�������

    //�л�����һ������
    switch(ctrl)
    {
    case VAR_NEXT:                      //��һ��
        new_tab++;
        if(new_tab >= (VAR_MAX) )
        {
            new_tab = 0;               //��ͷ��ʼ
        }
        break;

    case VAR_PREV:                      //��һ��
        new_tab--;
        if(new_tab >= (VAR_MAX) )
        {
            new_tab = VAR_MAX - 1;     //��β��ʼ
        }
        break;

    case VAR_NEXT_HOLD:                 //����
        new_tab += VAR_SELECT_HOLD_OFFSET;
        if(new_tab >= (VAR_MAX) )
        {
            new_tab = 0;               //��ͷ��ʼ
        }
        break;

    case VAR_PREV_HOLD:                 //����
        new_tab -= VAR_SELECT_HOLD_OFFSET;
        if(new_tab >= (VAR_MAX) )
        {
            new_tab = VAR_MAX - 1;     //��β��ʼ
        }
        break;

    default:                        //��Чѡ�񣬲���Ҫ�л�
        return;
    }

    var_display(old_tab);               //������һ������

    var_display(new_tab);              //����ǰ������

}


//ȷ�ϵ�ǰѡ���
void var_ok()
{
    ASSERT(new_tab < VAR_MAX);

    //�Ƚ��Ƿ��иı�ֵ
    if(VAR_VALUE(new_tab) != VAR_OLDVALUE(new_tab))   //ֵ�ı��ˣ�����Ҫ����
    {
        var_syn(new_tab);          //ͬ���µ�ֵ       
    }
//    speed.Set=var1;
//    pid.MotorP=var2;
//    pid.ServoD=var3*1000+var4*100+var5;    
//    pid.ServoP=(float)var6/100;
    
    var_display(new_tab);
}

//ȡ����ǰѡ���ֵ  OK
void val_cancel()
{
    ASSERT(new_tab < VAR_MAX);

    //ֱ�ӻ�ԭ��ǰֵ
    VAR_VALUE(new_tab) = VAR_OLDVALUE(new_tab);

    var_display(new_tab);
}



//��ʾָ����ֵ��tab Ϊ VAR_MAX ʱ��ʾȫ����ʾ��С������ʾ��Ӧ��

void var_display(uint8 tab)
{
#if UI_VAR_USE_LCD

    //���屳����ʱ
#define SELECT_NO_CHANGE_BG         WHITE   //��ǰѡ�У�����û�иı�
#define SELECT_CHANGE_BG            WHITE   //��ǰѡ�У����Ҹı���
#define NO_SELECT_NO_CHANGE_BG      BLACK     //û��ѡ�У�����û�иı䣨��ͨ�ľ���������
#define NO_SELECT_CHANGE_BG         BLACK     //û��ѡ�У����Ҹı���

    //����������ɫ
#define SELECT_NO_CHANGE            BLUE    //��ǰѡ�У�����û�иı�
#define SELECT_CHANGE               GREEN   //��ǰѡ�У����Ҹı���
#define NO_SELECT_NO_CHANGE         BLUE    //û��ѡ�У�����û�иı䣨��ͨ�ľ���������
#define NO_SELECT_CHANGE            GREEN   //û��ѡ�У����Ҹı���

    uint8  i = 0;
    uint16 bkColor;
    uint16 Color;

    ASSERT((new_tab < VAR_MAX) && (tab <= VAR_MAX));

    if(tab == VAR_MAX)      //��ʾȫ��
    {
        i = VAR_MAX - 1;    //ѭ���Ĵ���
        tab = 0;
    }

    do
    {
        if(tab == new_tab)
        {
            //��ʾ��ǰ��ֵ���ж�ֵ�Ƿ�ı�
            if(VAR_VALUE(tab) == VAR_OLDVALUE(tab)) //ֵû�ı䣬����Ҫ����
            {
                Color   =  SELECT_NO_CHANGE;
                bkColor =  SELECT_NO_CHANGE_BG;
            }
            else
            {
                Color   =  SELECT_CHANGE;
                bkColor =  SELECT_CHANGE_BG;
            }
        }
        else
        {
            //��ʾ�ǵ�ǰ��ֵ
            if(VAR_VALUE(tab) == VAR_OLDVALUE(tab)) //ֵû�ı䣬����Ҫ����
            {
                Color   =  NO_SELECT_NO_CHANGE;
                bkColor =  NO_SELECT_NO_CHANGE_BG;

            }
            else
            {
                Color   =  NO_SELECT_CHANGE;
                bkColor =  NO_SELECT_CHANGE_BG;
            }
        }

        //��ʾ����
        LCD_num_C(VAR_SITE(tab), VAR_VALUE(tab), Color, bkColor);

        tab++;
    }
    while(i--);         //tab != VAR_MAX ��ʱ��ִ��һ�ξ�����
    
    LCD_str((Site_t){0,0}, "SpdSet", YELLOW, BLACK) ;   
    LCD_str((Site_t){0,34}, "SpdCur", YELLOW, BLACK) ;       
    LCD_str((Site_t){0,68},"MotorP", YELLOW,BLACK) ; 
    LCD_str((Site_t){74,0},"ServoD", YELLOW, BLACK) ;  
    LCD_str((Site_t){74,34},"ServoP", YELLOW, BLACK) ;      
    
#else
    tab = tab;          //�������뾯��
#endif
}

void save_var2buff(var_tab_e var_num, uint8 *sendbuf)
{
    uint32 temp;
    get_var(var_num, &temp);
    *((uint32 *)&sendbuf[COM_LEN]) = (uint32)var_num;
    *((uint32 *)&sendbuf[COM_LEN + sizeof(uint32)]) = temp;
}

//ͬ��ָ����ֵ��tab Ϊ VAR_MAX ʱ��ʾȫ��ͬ����С����ͬ����Ӧ��
uint8 var_syn(uint8 tab)
{
    ASSERT((new_tab < VAR_MAX) && (tab <= VAR_MAX));

    uint8  i = 0;
    uint32 oldvalue;

    if(tab == VAR_MAX)
    {
        i = VAR_MAX - 1;
        tab = 0;
    }

    do
    {
        oldvalue = VAR_OLDVALUE(tab);                   //���ݾɵ�ֵ

        //��ֵ���Ƶ���Ӧ�ı���
        save_var((var_tab_e)tab, VAR_VALUE(tab));
    
        tab++;
    }
    while(i--);

    return 1;
}

uint8    car_ctrl_get()
{
    return  car_ctrl;
}


//��״̬����
uint8 car_ctrl_syn(CAR_CTRL_MODE_e mode)
{
    uint8 ret;
    ASSERT(mode < CAR_CTRL_MAX);

    VAR_VALUE(CAR_CTRL) =  mode;

    ret =  var_syn(CAR_CTRL);

    var_display(CAR_CTRL);

    return ret;
};



