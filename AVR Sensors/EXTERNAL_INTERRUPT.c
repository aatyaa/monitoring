#include"TYPES.h"
#include"REGISTERS.h"
#include"DIO.h"
#include"MACROS.h"
#include"EXTERNAL_INTERRUPT.h"


void (*EXTERNAL_INTERRUPTI_ISR0)(void);  //Global pointer to function
void (*EXTERNAL_INTERRUPTI_ISR1)(void);




//ISR() for INT0
#define __INTR_ATTRS used , externally_visible
void __vector_1(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_1(void)
{

	EXTERNAL_INTERRUPTI_ISR0();
}




//ISR() for INT1
#define __INTR_ATTRS used , externally_visible
void __vector_2(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_2(void)
{

	EXTERNAL_INTERRUPTI_ISR1();
}






/***************************************************************************************/
/* Description! Apply initialization sequence External Interrupt                       */
/* Input      ! INT number , INT state                                                 */
/* Output     ! Nothing                                                                */
/* Example    ! EXTERNAL_INTERRUPT_VidInit(INT0 , RISING_EDGE );                       */
/***************************************************************************************/
void EXTERNAL_INTERRUPT_VidInit(u8 LOC_u8IntNum , u8 LOC_u8IntState )
{


	if(LOC_u8IntNum == EXTERNAL_INTERRUPT_INT0 )
	{
		DIO_VidSetPinDirection(D , PIN2 , INPUT);
		DIO_VidSetPinValue(D , PIN2 , HIGH);
		SET_BIT(GICR , 6);
		switch(LOC_u8IntState)
		{
		case EXTERNAL_INTERRUPT_RISING_EDGE :
			SET_BIT(MCUCR , 0);
			SET_BIT(MCUCR , 1);
			break ;
		case EXTERNAL_INTERRUPT_FALLING_EDGE :
			CLR_BIT(MCUCR , 0);
			SET_BIT(MCUCR , 1);
			break ;
		case EXTERNAL_INTERRUPT_ONCHANGE :
			SET_BIT(MCUCR , 0);
			CLR_BIT(MCUCR , 1);
			break ;



		}

		SET_BIT(SREG , 7);
	}


	else if(LOC_u8IntNum == EXTERNAL_INTERRUPT_INT1)
	{
		DIO_VidSetPinDirection(D , PIN3 , INPUT);
		DIO_VidSetPinValue(D , PIN3 , HIGH);
		SET_BIT(GICR , 7);

		switch(LOC_u8IntState)
		{
		case EXTERNAL_INTERRUPT_RISING_EDGE :
			SET_BIT(MCUCR , 2);
			SET_BIT(MCUCR , 3);
			break ;
		case EXTERNAL_INTERRUPT_FALLING_EDGE :
			CLR_BIT(MCUCR , 2);
			SET_BIT(MCUCR , 3);
			break ;
		case EXTERNAL_INTERRUPT_ONCHANGE :
			SET_BIT(MCUCR , 2);
			CLR_BIT(MCUCR , 3);
			break ;


		}

		SET_BIT(SREG , 7);

	}

	else{}
}









/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to INT0 callback function               */
/* Output     ! Nothing                                                                */
/* Example    ! EXTERNAL_INTERRUPT_VidSetCallbackINT0( CallBack function name );       */
/***************************************************************************************/
void EXTERNAL_INTERRUPT_VidSetCallbackINT0(void ( *ptr) (void))
{


	EXTERNAL_INTERRUPTI_ISR0 = ptr ;

}




/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to INT0 callback function               */
/* Output     ! Nothing                                                                */
/* Example    ! EXTERNAL_INTERRUPT_VidSetCallbackINT0( CallBack function name );       */
/***************************************************************************************/
void EXTERNAL_INTERRUPT_VidSetCallbackINT1(void ( *ptr) (void))
{


	EXTERNAL_INTERRUPTI_ISR1 = ptr ;

}




void EXTERNAL_INTERRUPT_VidDisableExternalInterrupt(u8 LOC_u8IntNum)
{
	if(LOC_u8IntNum == EXTERNAL_INTERRUPT_INT0)
	{
		CLR_BIT(GICR , 6);
	}else if(LOC_u8IntNum == EXTERNAL_INTERRUPT_INT1)
	{
		CLR_BIT(GICR , 7);
	}

}


