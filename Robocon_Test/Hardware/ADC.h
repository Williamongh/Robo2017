#ifndef __ROBOCON_ADC_H__
#define __ROBOCON_ADC_H__

#include "stm32f10x.h"

   void ADC_Mode_Init(void);
 
   uint16_t ADC_Get(void);
	 float ADC_Val(void);
#endif

