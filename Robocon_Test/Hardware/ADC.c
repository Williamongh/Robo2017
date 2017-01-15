/*!
 * @file       Robocon_ADC.c
 * @brief      Robocon测试小车ADC模块
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-29
 */
 
 #include "ADC.h"
 
 void ADC_Mode_Init(void)
 {
	//	首先配置GPIO与ADC的时钟：

		ADC_InitTypeDef  ADC_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);
		GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN;
		GPIO_Init(GPIOA,&GPIO_InitStructure); //默认速度为两兆

	//	配置ADC的运行：

		ADC_InitStructure.ADC_Mode              = ADC_Mode_Independent;  //独立模式
		ADC_InitStructure.ADC_ScanConvMode      =DISABLE;      //连续多通道模式
		ADC_InitStructure.ADC_ContinuousConvMode =ENABLE;      //连续转换
		ADC_InitStructure.ADC_ExternalTrigConv  = ADC_ExternalTrigConv_None; //转换不受外界决定
		ADC_InitStructure.ADC_DataAlign         =ADC_DataAlign_Right;   //右对齐
		ADC_InitStructure.ADC_NbrOfChannel      =1;       //扫描通道数
		ADC_Init(ADC1,&ADC_InitStructure);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_3, 1,ADC_SampleTime_1Cycles5); //通道X,采样时间为1.5周期
		ADC_Cmd  (ADC1,ENABLE);             //使能或者失能指定的ADC

		
  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//使能或者失能指定的ADC的软件转换启动功能转换	

 }
uint16_t ADC_Get(void)
{
		uint16_t adc;
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET); //检查制定ADC标志位置1与否 ADC_FLAG_EOC 转换结束标志位
		adc=(ADC_GetConversionValue(ADC1));

		return adc;//返回最近一次ADCx规则组的转换结果
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

 
 

