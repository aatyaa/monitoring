/*
 * TIMER2.c
 *
 *  Created on: Feb 7, 2019
 *      Author: Ahmadoh
 */



#include"TYPES.h"
#include"REGISTERS.h"
#include"MACROS.h"
#include"TIMER2.h"
#include"DIO.h"



void (*TIMER2_ISR0)(void);  //Global pointer to function
void (*TIMER2_ISR1)(void);




//ISR() for Overflow mode
#define __INTR_ATTRS used , externally_visible
void __vector_5(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_5(void)
{

	TIMER2_ISR0();
}



//ISR() for CTC mode
#define __INTR_ATTRS used , externally_visible
void __vector_4(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_4(void)
{

	TIMER2_ISR1();
}







/***************************************************************************************/
/* Description! Apply initialization sequence for Overflow mode (Normal mode)          */
/* Input      ! TimerType (Interrupt or  polling) , TimerPrscaler                      */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_VidOverFlowInit( ENTERRUPT , 256 );                             */
/***************************************************************************************/
void TIMER2_VidOverFlowInit(u8 LOC_u8Timer2Type , u16 LOC_u8Timer2Prescaler )
{


	//check interrupt or polling
	if(LOC_u8Timer2Type == TIMER2_INTERRUPT)
	{
		SET_BIT(TIMSK , 6); //overflow interrupt
		SET_BIT(SREG , 7);  //global interrupt
	}



	//set prescaler
	switch(LOC_u8Timer2Prescaler)
	{

	case 1 :
		TCCR2 = 0b00000001 ;
		break;

	case 8 :
		TCCR2 = 0b00000010 ;
		break;

	case 32 :
		TCCR2 = 0b00000011 ;
		break;


	case 64 :
		TCCR2 = 0b00000100 ;
		break;


	case 128 :
		TCCR2 = 0b00000101 ;
		break;

	case 256 :
		TCCR2 = 0b00000110 ;
		break;


	case 1024 :
		TCCR2 = 0b00000111 ;
		break;



	default : break ;

	}

}






/***************************************************************************************/
/* Description! Apply initialization sequence for CTC mode (Normal mode)               */
/* Input      ! TimerType (Interrupt or  polling) , TimerMax ,TimerPrscaler            */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_VidCTCInit(POLLING , 150 , 256 );                               */
/***************************************************************************************/
void TIMER2_VidCTCInit(u8 LOC_u8Timer2Type , u8 LOC_u8TimerMax , u16 LOC_u8Timer2Prescaler )
{


	//check interrupt or polling
	if(LOC_u8Timer2Type == TIMER2_INTERRUPT)
	{
		SET_BIT(TIMSK , 7); //CTC interrupt
		SET_BIT(SREG , 7);  //global interrupt
	}


	//set prescaler
	switch(LOC_u8Timer2Prescaler)
	{
	case 1 :
		TCCR2 = 0b00000001 ;
		break;

	case 8 :
		TCCR2 = 0b00000010 ;
		break;

	case 32 :
		TCCR2 = 0b00000011 ;
		break;


	case 64 :
		TCCR2 = 0b00000100 ;
		break;


	case 128 :
		TCCR2 = 0b00000101 ;
		break;

	case 256 :
		TCCR2 = 0b00000110 ;
		break;


	case 1024 :
		TCCR2 = 0b00000111 ;
		break;



	default : break ;
	}


	//choosing CTC mode
	SET_BIT(TCCR2 , 3) ;


	//Putting timer max value

	OCR2 = LOC_u8TimerMax;

}








/***************************************************************************************/
/* Description! set initialize value in timer register                                 */
/* Input      ! initialize value                                                       */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_VidSetInitialValue(150);                                        */
/***************************************************************************************/
void TIMER2_VidSetOverFlowInitialValue(u8 LOC_u8InitialValue )
{

	TCNT2 = LOC_u8InitialValue ;

}






/***************************************************************************************/
/* Description! get overflow mode flag                                                 */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_u8GetOverflowFlag();                                            */
/***************************************************************************************/
u8 TIMER2_u8GetOverflowFlag(void)
{
	return GET_BIT(TIFR , 6);

}







/***************************************************************************************/
/* Description! get CTC mode flag                                                      */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_u8GetCTCFlag();                                                 */
/***************************************************************************************/
u8 TIMER2_u8GetCTCFlag(void)
{
	return GET_BIT(TIFR , 7);

}








/***************************************************************************************/
/* Description! Clear Overflow and CTC flag                                            */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_VidClrFlags();                                                  */
/***************************************************************************************/
void TIMER2_VidClrFlags(void)
{
	SET_BIT(TIFR , 6);
	SET_BIT(TIFR , 7);

}








/***************************************************************************************/
/* Description! Interface to intialize the fast PWM                                    */
/* Input      ! Prescaler for the fixed size 8-bit register                            */
/* Output     ! Nothing                                                                */
/* Example    ! void TIMER2_VidFastPWMInit( 1024 );                                    */
/***************************************************************************************/

void TIMER2_VidFastPWMSetT_totalOverFlow(u16 LOC_u16Timer0Prescaler  )
{

	DIO_VidSetPinDirection(D , PIN7 , OUTPUT);
	//set prescaler
	switch(LOC_u16Timer0Prescaler)
	{
	case 1 :
		TCCR2 = 0b00000001 ;
		break;

	case 8 :
		TCCR2 = 0b00000010 ;
		break;

	case 32 :
		TCCR2 = 0b00000011 ;
		break;


	case 64 :
		TCCR2 = 0b00000100 ;
		break;


	case 128 :
		TCCR2 = 0b00000101 ;
		break;

	case 256 :
		TCCR2 = 0b00000110 ;
		break;


	case 1024 :
		TCCR2 = 0b00000111 ;
		break;



	default : break ;

	}


	//Fast PWM
	SET_BIT(TCCR2 , 6);
	SET_BIT(TCCR2 , 5);
	SET_BIT(TCCR2 , 3);



}








/***************************************************************************************/
/* Description! Interface to set the value of duty register                            */
/* Input      ! ratio of duty cycle from 0 to 255                                      */
/* Output     ! Nothing                                                                */
/* Example    ! void TIMER0_VidSetDutyCyle(128); //50% duty cycle                      */
/***************************************************************************************/
void TIMER2_VidSetT_on(u8 LOC_u8DutyCyle)
{

	OCR2 = LOC_u8DutyCyle ;



}









/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to overflow callback function           */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidSetCallbackOverflow( CallBack function name );       */
/***************************************************************************************/
void TIMER2_VidSetCallbackOverflow(void ( *ptr) (void))
{

	TIMER2_ISR0 = ptr ;

}





/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to CTC callback function                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidSetCallbackCTC( CallBack function name );                    */
/***************************************************************************************/
void TIMER2_VidSetCallbackCTC(void ( *ptr) (void))
{

	TIMER2_ISR1 = ptr ;

}





u8 TIMER2_u8GetCounter(void)
{
	return TCNT2 ;
}



void TIMER2_VidDisableOverFlowInterrupt(void)
{
	CLR_BIT(TIMSK , 6);

}




void TIMER2_VidDisableCTCInterrupt(void)
{
	CLR_BIT(TIMSK , 7);

}



