/*
 * UART.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: jo
 */
#include"TYPES.h"
#include"MACROS.h"
#include"REGISTERS.h"
#include"DIO.h"
#include"UART.h"



void (*UART_ISR)(void);  //Global pointer to function







//ISR() for receive interrupt
#define __INTR_ATTRS used , externally_visible
void __vector_13(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_13(void)
{

	UART_ISR();

}






void UART_VidSetCallbackReceiveComplete(void ( *ptr) (void))
{


	UART_ISR = ptr ;

}








void UART_VidInit(u8 LOC_u8Type , u16 LOC_u16BoudRate)
{
	DIO_VidSetPinDirection(D , PIN0 , INPUT);
	DIO_VidSetPinDirection(D , PIN1 , OUTPUT);


	if(LOC_u8Type == UART_INTERRUPT)
	{

		UCSRB = 0b10011000;

		SET_BIT(SREG , 7 );

	}
	else if(LOC_u8Type == UART_POLLING)
	{
		UCSRB = 0b00011000;
	}



	UCSRC = 0b10000110;

	UBRRL = (750000/ LOC_u16BoudRate) - 1;
	UBRRH = 0;



}




u8 UART_u8GetMessage(void)
{

	return UDR ;

}





u8 UART_u8GetRecieveCompleteFlag(void)
{
	return GET_BIT(UCSRA , 7);
}







void UART_VidSend(u8 LOC_u8Data)
{
	while((GET_BIT(UCSRA , 5 )) == 0);
	UDR = LOC_u8Data ;

}


