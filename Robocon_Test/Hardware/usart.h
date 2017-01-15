#ifndef 	__USART_H__
#define 	__USART_H__

 #include "include.h"

void USART1_Init(u32 bound);
void UART4_Init(u32 bound);
void UART_PutBuff (USART_TypeDef* USARTx, uint8 *buff, uint32 len);
	
#endif

