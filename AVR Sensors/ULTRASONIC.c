/*
 * ULTRASONIC.c
 *
 *  Created on: May 28, 2019
 *      Author: le
 */



#include"TYPES.h"
#include"DIO.h"
#include"TIMER1.h"
#include"TIMER0.h"
#include"TIMER2.h"
#include"EXTERNAL_INTERRUPT.h"
#include"ULTRASONIC_CFG.h"
#include"util/delay.h"
#include"LCD.h"


u32 volatile u32Timer0OverFlowCounter = 0 ;
u8 volatile u8Timer1OverFlowCounter = 0 ;
u32 volatile u32Timer2OverFlowCounter = 0 ;


u8 volatile u8flag = 0 ;
u32 volatile u32snap1 = 0 ;
u32 volatile u32snap2 = 0 ;

u8 u8CheckICU=0;
void ULTRASONIC_VidTimer1Callback(void)
{
	u8Timer1OverFlowCounter ++ ;

}



void ULTRASONIC_VidTimer0Callback(void)
{
	u32Timer0OverFlowCounter ++ ;
	u32Timer2OverFlowCounter ++ ;

}



/*void ULTRASONIC_VidTimer2Callback(void)
{
	u32Timer2OverFlowCounter ++ ;

}*/



void ULTRASONIC_VidICUCallback(void)
{
	if(u8flag == 0)
	{
		u32snap1 = TIMER1_u16GetInputCaptureUnitRegister();
		u8Timer1OverFlowCounter = 0 ;
		TIMER1_VidInputCaptureUnitInit(TIMER1_FALLING_EDGE);

	}else if(u8flag == 1)
	{
		u32snap2 = TIMER1_u16GetInputCaptureUnitRegister() + (u8Timer1OverFlowCounter * 65536);
		TIMER1_VidInputCaptureUnitInit(TIMER1_RISING_EDGE);

	}


	u8flag ++ ;
}






void ULTRASONIC_VidINT0Callback(void)
{
	if(u8flag == 0)
	{
		u32snap1 = TIMER0_u8GetCounter();
		u32Timer0OverFlowCounter = 0 ;
		EXTERNAL_INTERRUPT_VidInit(EXTERNAL_INTERRUPT_INT0 , EXTERNAL_INTERRUPT_FALLING_EDGE);

	}else if(u8flag == 1)
	{
		u32snap2 = TIMER0_u8GetCounter() + (u32Timer0OverFlowCounter * 256);
		EXTERNAL_INTERRUPT_VidInit(EXTERNAL_INTERRUPT_INT0 , EXTERNAL_INTERRUPT_RISING_EDGE);

	}


	u8flag ++ ;
}





void ULTRASONIC_VidINT1Callback(void)
{
	if(u8flag == 0)
	{
		u32snap1 = TIMER0_u8GetCounter();
		u32Timer2OverFlowCounter = 0 ;
		EXTERNAL_INTERRUPT_VidInit(EXTERNAL_INTERRUPT_INT1 , EXTERNAL_INTERRUPT_FALLING_EDGE);

	}else if(u8flag == 1)
	{
		u32snap2 = TIMER0_u8GetCounter() + (u32Timer2OverFlowCounter * 256);
		EXTERNAL_INTERRUPT_VidInit(EXTERNAL_INTERRUPT_INT1 , EXTERNAL_INTERRUPT_RISING_EDGE);

	}


	u8flag ++ ;
}









void ULTRASONIC_VidINT0Init(void)
{
	//Power pin output
	DIO_VidSetPinDirection(ULTRASONIC_INT0_POWER_PORT , ULTRASONIC_INT0_POWER_PIN , OUTPUT );


	//timer0
	TIMER0_VidSetCallbackOverflow(ULTRASONIC_VidTimer0Callback);
	TIMER0_VidOverFlowInit(TIMER0_INTERRUPT , 1);

	//INT0
	EXTERNAL_INTERRUPT_VidSetCallbackINT0(ULTRASONIC_VidINT0Callback);
	EXTERNAL_INTERRUPT_VidInit(EXTERNAL_INTERRUPT_INT0 , EXTERNAL_INTERRUPT_RISING_EDGE);


	_delay_ms(5);// the delay that ultrasonic need it to work


}





u8 ULTRASONIC_u8INT0GetDistance(void)
{


	DIO_VidSetPinValue(ULTRASONIC_INT0_POWER_PORT , ULTRASONIC_INT0_POWER_PIN , HIGH);
	_delay_us(10);
	DIO_VidSetPinValue(ULTRASONIC_INT0_POWER_PORT , ULTRASONIC_INT0_POWER_PIN , LOW );


	while(u8flag != 2);

	u32snap2 = u32snap2 - u32snap1 ;
	u32snap2 = ((f32)u32snap2/706);



	u8flag = 0 ;


	return (u8)u32snap2 ;
}




void ULTRASONIC_VidICUInit(void)
{
	//Power pin output
	DIO_VidSetPinDirection(ULTRASONIC_ICU_POWER_PORT , ULTRASONIC_ICU_POWER_PIN , OUTPUT );


	//timer1
	TIMER1_VidSetCallbackOverflow(ULTRASONIC_VidTimer1Callback);
	TIMER1_VidOverFlowInit(TIMER1_INTERRUPT , 1);

	//ICU
	TIMER1_VidSetCallbackInputCaptureUnit(ULTRASONIC_VidICUCallback);
	TIMER1_VidInputCaptureUnitInit(TIMER1_RISING_EDGE);

}


u8 ULTRASONIC_u8ICUGetDistance(void)
{

	DIO_VidSetPinValue(ULTRASONIC_ICU_POWER_PORT , ULTRASONIC_ICU_POWER_PIN , HIGH);
	_delay_us(10);
	DIO_VidSetPinValue(ULTRASONIC_ICU_POWER_PORT , ULTRASONIC_ICU_POWER_PIN , LOW );


	while(u8flag != 2){
		if(u8CheckICU==0){
			break;

		}
	}

	u32snap2 = u32snap2 - u32snap1 ;
	u32snap2 = ((f32)u32snap2/706);



	u8flag = 0 ;
	u8CheckICU=1;
	return (u8)u32snap2 ;
}








void ULTRASONIC_VidINT1Init(void)
{
	//Power pin output
	DIO_VidSetPinDirection(ULTRASONIC_INT1_POWER_PORT , ULTRASONIC_INT1_POWER_PIN , OUTPUT );


	//timer0
	TIMER0_VidSetCallbackOverflow(ULTRASONIC_VidTimer0Callback);
	TIMER0_VidOverFlowInit(TIMER0_INTERRUPT , 1);

	//INT0
	EXTERNAL_INTERRUPT_VidSetCallbackINT1(ULTRASONIC_VidINT1Callback);
	EXTERNAL_INTERRUPT_VidInit(EXTERNAL_INTERRUPT_INT1 , EXTERNAL_INTERRUPT_RISING_EDGE);
	_delay_ms(5);


}










u8 ULTRASONIC_u8INT1GetDistance(void)
{

	//u8 LOC_u8result = 0 ;
	DIO_VidSetPinValue(ULTRASONIC_INT1_POWER_PORT , ULTRASONIC_INT1_POWER_PIN , HIGH);
	_delay_us(10);
	DIO_VidSetPinValue(ULTRASONIC_INT1_POWER_PORT , ULTRASONIC_INT1_POWER_PIN , LOW );


	while(u8flag != 2);

	u32snap2 = u32snap2 - u32snap1 ;
	u32snap2 = ((f32)u32snap2/706);



	u8flag = 0 ;


	return u32snap2 ;
}











