/*
 * ADC.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: jo
 */
#include"TYPES.h"
#include"MACROS.h"
#include"REGISTERS.h"
#include"DIO.h"
#include"ADC.h"


void (*ADC_ISR)(void);  //Global pointer to function




//ISR() for ADC Interrupt
#define __INTR_ATTRS used , externally_visible
void __vector_16(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_16(void)
{

	ADC_ISR();
}






/***************************************************************************************/
/* Description! Apply initialization sequence ADC                                      */
/* Input      ! ADC type  ,  ADC mode , Channel num  , Prescaler                       */
/* Output     ! Nothing                                                                */
/* Example    ! ADC_VidInit(INTERRUPT , SINGLE_CONVERSION , CHANNEL0 , 128 );          */
/***************************************************************************************/

void ADC_VidInit(u8 LOC_u8AdcType , u8 LOC_u8AdcMode , u8 LOC_u8ChannelNum , u8 LOC_u8Prescaler)
{
	DIO_VidSetPinDirection(A ,  LOC_u8ChannelNum , 0) ;



	// Configure the channel
	switch(LOC_u8ChannelNum)
	{
	case ADC_CHANNEL0 :
		ADMUX = 0b01000000 ;
		break ;

	case ADC_CHANNEL1 :
		ADMUX = 0b01000001 ;
		break ;

	case ADC_CHANNEL2 :
		ADMUX = 0b01000010 ;
		break ;

	case ADC_CHANNEL3 :
		ADMUX = 0b01000011 ;
		break ;

	case ADC_CHANNEL4 :
		ADMUX = 0b01000100 ;
		break ;

	case ADC_CHANNEL5 :
		ADMUX = 0b01000101 ;
		break ;

	case ADC_CHANNEL6 :
		ADMUX = 0b01000110 ;
		break ;

	case ADC_CHANNEL7 :
		ADMUX = 0b01000111 ;
		break ;

	}


	SET_BIT(ADMUX,5);  //adjust left



	// configure the Prescaler
	switch(LOC_u8Prescaler)
	{
	case 2 :
		ADCSRA = 0b00000000 ;
		break;

	case 4 :
		ADCSRA = 0b00000010 ;
		break;

	case 8 :
		ADCSRA = 0b00000011 ;
		break;

	case 16 :
		ADCSRA = 0b00000100 ;
		break;

	case 32 :
		ADCSRA = 0b00000101 ;
		break;

	case 64 :
		ADCSRA = 0b00000110 ;
		break;

	case 128 :
		ADCSRA = 0b00000111 ;
		break;


	default: ADCSRA = 0b00000110 ;

	}



	SET_BIT(ADCSRA , 7); //enable ADC



	// Configure Polling or Interrupt
	if(LOC_u8AdcType == ADC_POLLING)
	{
		CLR_BIT(ADCSRA , 3);
	}
	else if(LOC_u8AdcType == ADC_INTERRUPT)
	{
		SET_BIT(ADCSRA , 3);
		SET_BIT(SREG , 7);
	}



	//Configure the ADC mode
	switch(LOC_u8AdcMode)
	{
	case ADC_SINGLE_CONVERSION :
		CLR_BIT(ADCSRA , 5);
		break;

	case ADC_FREE_RUNNING :
		SET_BIT(ADCSRA , 5);  //enable Auto Trigger Source

		CLR_BIT(SFIOR , 5);
		CLR_BIT(SFIOR , 6);
		CLR_BIT(SFIOR , 7);
		break;


	case ADC_EXTERNAL_INTERRUPT0 :
		SET_BIT(ADCSRA , 5);  //enable Auto Trigger Source

		CLR_BIT(SFIOR , 5);
		SET_BIT(SFIOR , 6);
		CLR_BIT(SFIOR , 7);
		break;


	}



}







/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to ADC interrupt callback function      */
/* Output     ! Nothing                                                                */
/* Example    ! ADC_VidSetCallbackI( CallBack function name );       */
/***************************************************************************************/
void ADC_VidSetCallback(void ( *ptr) (void))
{
	ADC_ISR = ptr ;
}







/***************************************************************************************/
/* Description! Interface to get result of conversion                                  */
/* Input      ! Nothing                                                                */
/* Output     ! Result                                                                 */
/* Example    ! u16 result =  ADC_u8GetResult();                                       */
/***************************************************************************************/
u8 ADC_u8GetResult(void)
{
	//u16 LOC_u16Result ;

	u8 LOC_u8Result ;

	//LOC_u16Result = (ADCL | (ADCH<<8)) ;

	LOC_u8Result = ADCH ;


	SET_BIT(ADCSRA , 4);

	return LOC_u8Result ;

}







/**********************************************************************************************/
/* Description! - Interface to start a single conversion , start source trigger               */
/*                  conversion for the first time like FREE_RUNNING , EXTERNAL_ENTERRUPT0     */
/*              - start conversion for every mode                                             */
/*              - we use it in the the SINGLE_CONVERSION in every time we want to convert     */
/*              - we use it in the SOURCE_TRIGGER only one time to start the first conversion */
/* Input      ! Nothing                                                                       */
/* Output     ! Nothing                                                                       */
/* Example    ! ADC_u8StartConversion();                                                      */
/**********************************************************************************************/
void ADC_u8StartConversion(void)
{
	SET_BIT(ADCSRA , 6);
	while((GET_BIT(ADCSRA , 4)) == 0);
}
