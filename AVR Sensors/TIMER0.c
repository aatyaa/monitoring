/*
 * TIMER0.c
 *
 *  Created on: Feb 5, 2019
 *      Author: Ahmadoh
 */


#include"TYPES.h"
#include"REGISTERS.h"
#include"MACROS.h"
#include"TIMER0.h"
#include"DIO.h"



void (*TIMER0_ISR0)(void);  //Global pointer to function
void (*TIMER0_ISR1)(void);




//ISR() for Timer0 Overflow mode
#define __INTR_ATTRS used , externally_visible
void __vector_11(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_11(void)
{

	TIMER0_ISR0();
}



//ISR() for Timer0 CTC mode
#define __INTR_ATTRS used , externally_visible
void __vector_10(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_10(void)
{

	TIMER0_ISR1();
}







/***************************************************************************************/
/* Description! Apply initialization sequence for Overflow mode (Normal mode)          */
/* Input      ! TimerType (Interrupt or  polling) , TimerPrscaler                      */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidOverFlowInit( ENTERRUPT , 256 );                             */
/***************************************************************************************/
void TIMER0_VidOverFlowInit(u8 LOC_u8Timer0Type , u16 LOC_u8Timer0Prescaler )
{


	//check interrupt or polling
	if(LOC_u8Timer0Type == TIMER0_INTERRUPT)
	{
		SET_BIT(TIMSK , 0); //overflow interrupt
		SET_BIT(SREG , 7);  //global interrupt
	}



	//set prescaler
	switch(LOC_u8Timer0Prescaler)
	{

	case 1 :
		TCCR0 = 0b00000001 ;
		break;

	case 8 :
		TCCR0 = 0b00000010 ;
		break;

	case 64 :
		TCCR0 = 0b00000011 ;
		break;


	case 256 :
		TCCR0 = 0b00000100 ;
		break;


	case 1024 :
		TCCR0 = 0b00000101 ;
		break;


	default : break ;

	}

}









/***************************************************************************************/
/* Description! Apply initialization sequence for CTC mode (Normal mode)               */
/* Input      ! TimerType (Interrupt or  polling) , TimerMax ,TimerPrscaler            */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidCTCInit(POLLING , 150 , 256 );                               */
/***************************************************************************************/
void TIMER0_VidCTCInit(u8 LOC_u8Timer0Type , u8 LOC_u8TimerMax , u16 LOC_u8Timer0Prescaler )
{


	//check interrupt or polling
	if(LOC_u8Timer0Type == TIMER0_INTERRUPT)
	{
		SET_BIT(TIMSK , 1); //CTC interrupt
		SET_BIT(SREG , 7);  //global interrupt
	}


	//set prescaler
	switch(LOC_u8Timer0Prescaler)
	{

	case 1 :
		TCCR0 = 0b00000001 ;
		break;

	case 8 :
		TCCR0 = 0b00000010 ;
		break;

	case 64 :
		TCCR0 = 0b00000011 ;
		break;


	case 256 :
		TCCR0 = 0b00000100 ;
		break;


	case 1024 :
		TCCR0 = 0b00000101 ;
		break;


	default : break ;

	}


	//choosing CTC mode
	SET_BIT(TCCR0 , 3) ;


	//Putting timer max value

	OCR0 = LOC_u8TimerMax;

}







/***************************************************************************************/
/* Description! set initialize value in timer register                                 */
/* Input      ! initialize value                                                       */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidSetInitialValue(150);                                        */
/***************************************************************************************/
void TIMER0_VidSetOverFlowInitialValue(u8 LOC_u8InitialValue )
{

	TCNT0 = LOC_u8InitialValue ;

}






/***************************************************************************************/
/* Description! get overflow mode flag                                                 */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_u8GetOverflowFlag();                                            */
/***************************************************************************************/
u8 TIMER0_u8GetOverflowFlag(void)
{
	return GET_BIT(TIFR , 0);

}







/***************************************************************************************/
/* Description! Clear Overflow and CTC flag                                            */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidClrFlags();                                                  */
/***************************************************************************************/
void TIMER0_VidClrFlags(void)
{
	SET_BIT(TIFR , 0);
	SET_BIT(TIFR , 1);

}






/***************************************************************************************/
/* Description! get CTC mode flag                                                      */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_u8GetCTCFlag();                                                 */
/***************************************************************************************/
u8 TIMER0_u8GetCTCFlag(void)
{
	return GET_BIT(TIFR , 1);

}









/***************************************************************************************/
/* Description! Interface to intialize the fast PWM                                    */
/* Input      ! Prescaler for the fixed size 8-bit register                            */
/* Output     ! Nothing                                                                */
/* Example    ! void TIMER0_VidFastPWMInit( 1024 );                                    */
/***************************************************************************************/
void TIMER0_VidFastPWMSetT_totalOverFlow(u16 LOC_u16Timer0Prescaler  )
{

	DIO_VidSetPinDirection(B , PIN3 , OUTPUT);
	//set prescaler
	switch(LOC_u16Timer0Prescaler)
	{

	case 1 :
		TCCR0 = 0b00000001 ;
		break;

	case 8 :
		TCCR0 = 0b00000010 ;
		break;

	case 64 :
		TCCR0 = 0b00000011 ;
		break;


	case 256 :
		TCCR0 = 0b00000100 ;
		break;


	case 1024 :
		TCCR0 = 0b00000101 ;
		break;


	default : break ;

	}


	//Fast PWM
	SET_BIT(TCCR0 , 6);
	SET_BIT(TCCR0 , 5);
	SET_BIT(TCCR0 , 3);



}








/***************************************************************************************/
/* Description! Interface to set the value of duty register                            */
/* Input      ! ratio of duty cycle from 0 to 255                                      */
/* Output     ! Nothing                                                                */
/* Example    ! void TIMER0_VidSetDutyCyle(128); //50% duty cycle                      */
/***************************************************************************************/
void TIMER0_VidSetT_on(u8 LOC_u8DutyCyle)
{

	OCR0 = LOC_u8DutyCyle ;



}








/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to overflow callback function           */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidSetCallbackOverflow( CallBack function name );               */
/***************************************************************************************/
void TIMER0_VidSetCallbackOverflow(void ( *ptr) (void))
{


	TIMER0_ISR0 = ptr ;

}





/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to CTC callback function                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidSetCallbackCTC( CallBack function name );                    */
/***************************************************************************************/
void TIMER0_VidSetCallbackCTC(void ( *ptr) (void))
{


	TIMER0_ISR1 = ptr ;

}



u8 TIMER0_u8GetCounter(void)
{
	return TCNT0 ;
}





void TIMER0_VidDisableOverFlowInterrupt(void)
{
	CLR_BIT(TIMSK , 0);

}




void TIMER0_VidDisableCTCInterrupt(void)
{
	CLR_BIT(TIMSK , 1);

}


