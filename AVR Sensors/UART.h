/*
 * UART.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: jo
 */

#ifndef UART_H_
#define UART_H_





#define UART_POLLING 0
#define UART_INTERRUPT 1



void UART_VidSend(u8 LOC_u8Data);
u8 UART_u8GetMessage(void);
u8 UART_u8GetRecieveCompleteFlag(void);
void UART_VidInit(u8 LOC_u8Type , u16 LOC_u16BoudRate);
void UART_VidSetCallbackReceiveComplete(void ( *ptr) (void));




#endif /* UART_H_ */
