/*
 * TIMER1.c
 *
 *  Created on: Feb 10, 2019
 *      Author: Ahmadoh
 */
/*
 * TIMER1.c
 *
 *  Created on: Feb 6, 2019
 *      Author: Ahmadoh
 */
#include"TYPES.h"
#include"REGISTERS.h"
#include"MACROS.h"
#include"TIMER1.h"
#include"LCD.h"
#include"DIO.h"



void (*TIMER1_ISR0)(void);  //Global pointer to function
void (*TIMER1_ISR1)(void);
void (*TIMER1_ISR2)(void);



//ISR() for Overflow mode
#define __INTR_ATTRS used , externally_visible
void __vector_9(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_9(void)
{

	TIMER1_ISR0();
}




//ISR() for CTC mode for channel A
#define __INTR_ATTRS used , externally_visible
void __vector_7(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_7(void)
{

	TIMER1_ISR1();
}







//ISR() for ICU Feature
#define __INTR_ATTRS used , externally_visible
void __vector_6(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_6(void)
{

	TIMER1_ISR2();
}





/***************************************************************************************/
/* Description! Apply initialization sequence for Overflow mode (Normal mode)          */
/* Input      ! TimerType (Interrupt or  polling) , TimerPrscaler                      */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_VidOverFlowInit( ENTERRUPT , 256 );                             */
/***************************************************************************************/
void TIMER1_VidOverFlowInit(u8 LOC_u8Timer1Type  , u16 LOC_u8Timer1Prescaler )
{


	//check interrupt or polling
	if(LOC_u8Timer1Type == TIMER1_INTERRUPT)
	{
		SET_BIT(TIMSK , 2); //overflow interrupt
		SET_BIT(SREG , 7);  //global interrupt
	}



	//set prescaler
	switch(LOC_u8Timer1Prescaler)
	{

	case 1 :
		TCCR1B = 0b00000001 ;
		break;

	case 8 :
		TCCR1B = 0b00000010 ;
		break;

	case 64 :
		TCCR1B = 0b00000011 ;
		break;


	case 256 :
		TCCR1B = 0b00000100 ;
		break;


	case 1024 :
		TCCR1B = 0b00000101 ;
		break;


	default : break ;

	}

	//overFlow mode
	TCCR1A = 0 ;

}









/***************************************************************************************/
/* Description! Apply initialization sequence for CTC mode (Normal mode)               */
/* Input      ! TimerType (Interrupt or  polling) , TimerMax ,TimerPrscaler            */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_VidCTCInit(POLLING , 150 , 256 );                               */
/***************************************************************************************/
void TIMER1_VidCTCInit(u8 LOC_u8Timer1Type , u16 LOC_u16TimerMax , u16 LOC_u8Timer1Prescaler )
{


	//check interrupt or polling
	if(LOC_u8Timer1Type == TIMER1_INTERRUPT)
	{
		SET_BIT(TIMSK , 4);
		SET_BIT(SREG , 7);  //global interrupt
	}


	//set prescaler
	switch(LOC_u8Timer1Prescaler)
	{

	case 1 :
		TCCR1B = 0b00000001 ;
		break;

	case 8 :
		TCCR1B = 0b00000010 ;
		break;

	case 64 :
		TCCR1B = 0b00000011 ;
		break;


	case 256 :
		TCCR1B = 0b00000100 ;
		break;


	case 1024 :
		TCCR1B = 0b00000101 ;
		break;


	default : break ;

	}


	TCCR1A = 0 ;

	//CTC mode
	OCR1A = LOC_u16TimerMax ;
	SET_BIT(TCCR1B , 3);


}










/***************************************************************************************/
/* Description! set initialize value in timer register                                 */
/* Input      ! initialize value                                                       */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_VidSetInitialValue(150);                                        */
/***************************************************************************************/
void TIMER1_VidSetOverFlowInitialValue(u16 LOC_u8InitialValue )
{

	TCNT1 = LOC_u8InitialValue ;

}








/***************************************************************************************/
/* Description! get overflow mode flag                                                 */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_u8GetOverflowFlag();                                            */
/***************************************************************************************/
u8 TIMER1_u8GetOverflowFlag(void)
{
	return GET_BIT(TIFR , 2);

}







/***************************************************************************************/
/* Description! get CTC mode flag                                                      */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_u8GetCTCFlag();                                                 */
/***************************************************************************************/
u8 TIMER1_u8GetCTCFlag(void)
{
	return GET_BIT(TIFR , 4);

}









/***************************************************************************************/
/* Description! Clear Overflow and CTC flag                                            */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidClrFlags();                                                  */
/***************************************************************************************/
void TIMER1_VidClrFlags(void)
{
	SET_BIT(TIFR , 2);
	SET_BIT(TIFR , 4);
}












//in PWM you can use the two channel  together but must by the same T(total)
/****************************************************************************************/
/* Description! Interface to intialize the fast PWM(not fixed register , can change top)*/
/*              choosing the channel and the T(total)                                   */
/* Input      ! Prescaler for the non fixed size 16-bit register                        */
/* Output     ! Nothing                                                                 */
/* Example    ! void TIMER0_VidFastPWMInit(PWMCHANNELA ,  ,  1024 );                    */
/****************************************************************************************/
void TIMER1_VidFastPWMSetT_totalCTC( u16 LOC_u16Timer1Max  ,u16 LOC_u16Timer1Prescaler  )
{


	SET_BIT(TCCR1A , 1);
	ICR1 = LOC_u16Timer1Max ;


	//set prescaler
	switch(LOC_u16Timer1Prescaler)
	{

	case 1 :
		TCCR1B = 0b00000001 ;
		break;

	case 8 :
		TCCR1B = 0b00000010 ;
		break;

	case 64 :
		TCCR1B = 0b00000011 ;
		break;


	case 256 :
		TCCR1B = 0b00000100 ;
		break;


	case 1024 :
		TCCR1B = 0b00000101 ;
		break;


	default : break ;

	}


	//Fast PWM
	SET_BIT(TCCR1B , 3);
	SET_BIT(TCCR1B , 4);


}









/***************************************************************************************/
/* Description! Interface to set the value of duty register                            */
/* Input      ! ratio of the top (duty cycle from 0 to 65536)                          */
/* Output     ! Nothing                                                                */
/* Example    ! void TIMER1_VidSetDutyCyle(200); //50% duty cycle of the top 400       */
/***************************************************************************************/
void TIMER1_VidSetT_on(u8 LOC_u8PWMChannel , u16 LOC_u16DutyCyle)
{

	if(LOC_u8PWMChannel == TIMER1_CHANNELA)
	{
		SET_BIT(TCCR1A , 7);
		DIO_VidSetPinDirection(D , PIN5 , OUTPUT);
		OCR1A = LOC_u16DutyCyle;

	}else if (LOC_u8PWMChannel == TIMER1_CHANNELB)
	{
		SET_BIT(TCCR1A , 5);
		DIO_VidSetPinDirection(D , PIN4 , OUTPUT);
		OCR1B = LOC_u16DutyCyle;
	}



}











/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to overflow callback function           */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_VidSetCallbackOverflow( CallBack function name );               */
/***************************************************************************************/
void TIMER1_VidSetCallbackOverflow(void ( *ptr) (void))
{


	TIMER1_ISR0 = ptr ;

}





/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to CTC callback function                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_VidSetCallbackCTC( CallBack function name );                    */
/***************************************************************************************/
void TIMER1_VidSetCallbackCTC(void ( *ptr) (void))
{


	TIMER1_ISR1 = ptr ;

}







/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to CTC callback function                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_VidSetCallbackCTC( CallBack function name );                    */
/***************************************************************************************/
void TIMER1_VidSetCallbackInputCaptureUnit(void ( *ptr) (void))
{


	TIMER1_ISR2 = ptr ;

}









u16 TIMER1_u16GetCounter(void)
{

	return TCNT1 ;

}







void TIMER1_VidInputCaptureUnitInit(u8 LOC_u8ICPState)
{

	DIO_VidSetPinDirection(D , PIN6 , INPUT);
	SET_BIT(TIMSK , 5);
	SET_BIT(SREG , 7);  //global interrupt
	if(LOC_u8ICPState == TIMER1_RISING_EDGE)
	{
		SET_BIT(TCCR1B , 6);
	}
	else if (LOC_u8ICPState == TIMER1_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B , 6);
	}


}





void TIMER1_VidClrInputCaptureUnitFlag(void)
{
	SET_BIT(TIFR , 5);
}


u16 TIMER1_u16GetInputCaptureUnitRegister(void)
{

	return ICR1 ;

}


void TIMER1_VidDisableInputCaptureUnitInterrupt(void)
{
	CLR_BIT(TIMSK , 5);

}


void TIMER1_VidDisableOverFlowInterrupt(void)
{
	CLR_BIT(TIMSK , 2);

}




void TIMER1_VidDisableCTCInterrupt(void)
{
	CLR_BIT(TIMSK , 3);

}



void TIMER1_VidSetInputCaptureUnitPrepheralInterupt(void)
{
	SET_BIT(TIMSK , 5);
}



void TIMER1_VidSetOverFlowPrepheralInterupt(void)
{
	SET_BIT(TIMSK , 2);
}




void TIMER1_VidSetCtcPrepheralInterupt(void)
{
	SET_BIT(TIMSK , 4);
}
