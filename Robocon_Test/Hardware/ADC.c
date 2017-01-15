/*!
 * @file       Robocon_ADC.c
 * @brief      Robocon����С��ADCģ��
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-29
 */
 
 #include "ADC.h"
 
 void ADC_Mode_Init(void)
 {
	//	��������GPIO��ADC��ʱ�ӣ�

		ADC_InitTypeDef  ADC_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);
		GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN;
		GPIO_Init(GPIOA,&GPIO_InitStructure); //Ĭ���ٶ�Ϊ����

	//	����ADC�����У�

		ADC_InitStructure.ADC_Mode              = ADC_Mode_Independent;  //����ģʽ
		ADC_InitStructure.ADC_ScanConvMode      =DISABLE;      //������ͨ��ģʽ
		ADC_InitStructure.ADC_ContinuousConvMode =ENABLE;      //����ת��
		ADC_InitStructure.ADC_ExternalTrigConv  = ADC_ExternalTrigConv_None; //ת������������
		ADC_InitStructure.ADC_DataAlign         =ADC_DataAlign_Right;   //�Ҷ���
		ADC_InitStructure.ADC_NbrOfChannel      =1;       //ɨ��ͨ����
		ADC_Init(ADC1,&ADC_InitStructure);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_3, 1,ADC_SampleTime_1Cycles5); //ͨ��X,����ʱ��Ϊ1.5����
		ADC_Cmd  (ADC1,ENABLE);             //ʹ�ܻ���ʧ��ָ����ADC

		
  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//ʹ�ܻ���ʧ��ָ����ADC�����ת����������ת��	

 }
uint16_t ADC_Get(void)
{
		uint16_t adc;
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET); //����ƶ�ADC��־λ��1��� ADC_FLAG_EOC ת��������־λ
		adc=(ADC_GetConversionValue(ADC1));

		return adc;//�������һ��ADCx�������ת�����
}
 
 float ADC_Val(void)
 {
		float adc = 0;
	  uint32_t adc_temp=0;
		uint8_t i=0;
		for(i=0;i<200;i++)
		{
				adc_temp+=ADC_Get();
		}
		adc = (float)adc_temp/200.0/4096*3.3;
	  return adc;
 }

 
 

