#define F_CPU 12000000UL
#include"TYPES.h"
#include <util/delay.h>
#include"MACROS.h"
#include"DIO.h"
#include"LCD.h"
#include"REGISTERS.h"
#include"EXTERNAL_INTERRUPT.h"
#include"TIMER0.h"
#include"TIMER1.h"
#include"TIMER2.h"
#include"UART.h"
#include"ULTRASONIC.h"
#include"SPI.h"
#include"ADC.h"
#include"DHT22.h"



/*u8 volatile y=0;

void Blutooth_vidCallBack(void){

	u8 x=UART_u8GetMessage();

	if(x=='1'){
		DIO_VidSetPinValue(C,PIN7,LOW);
		DIO_VidSetPinValue(C,PIN6,HIGH);
		DIO_VidSetPinValue(C,PIN5,HIGH);
		DIO_VidSetPinValue(C,PIN4,LOW);
		y=1;
	}


	else if(x=='0'){

		DIO_VidSetPinValue(C,PIN7,LOW);
		DIO_VidSetPinValue(C,PIN6,LOW);
		DIO_VidSetPinValue(C,PIN5,LOW);
		DIO_VidSetPinValue(C,PIN4,LOW);

		y=0;

	}

}*/

/*u8 volatile flag=0;
u8 x;
void Hesham(void){

	flag=1;
}*/



/*u8 volatile flag=0;

void SPI_CallBack(void){

	flag=1;

}*/

/*//gas snesor main

	u8 x;

	LCD_VidInit();

	LCD_VidSetPosition(0,0);

	LCD_VidWriteString((u8 *)"Reading = ");

	ADC_VidInit(ADC_POLLING,ADC_SINGLE_CONVERSION,ADC_CHANNEL0,128);

	SPI_VidSetCallBack(SPI_CallBack);

	SPI_VidInit(SPI_INTERUPT,SLAVE,LSB,MODE0,NO_PRESCALLER);

	while(1){

		if(flag==1){

			ADC_u8StartConversion();

			x=ADC_u8GetResult();

			SPDR=x;

			LCD_VidSetPosition(0,10);

			LCD_VidWriteNumber(SPDR);

			LCD_VidWriteString((u8 *)"   ");

			flag=0;
		}
	}*/























/*u8 volatile flag=0;

void SPI_CallBack(void){

	if(flag==0){
		ADC_VidInit(ADC_POLLING,ADC_SINGLE_CONVERSION,ADC_CHANNEL0,128);
		ADC_u8StartConversion();
		SPDR=ADC_u8GetResult();
		flag++;

	}else if(flag==1){
		ADC_VidInit(ADC_POLLING,ADC_SINGLE_CONVERSION,ADC_CHANNEL1,128);
		ADC_u8StartConversion();
		SPDR=ADC_u8GetResult();
		flag=0;
	}

}*/

u8 volatile flag =0;
void CheckFalling_CallBack(void){

	flag++;

}

int main(void)
{
	u8 I_RH;
	u8 D_RH;
	u8 I_TEMP;
	u8 D_TEMP;
	u8 Check_Sum;

	LCD_VidInit();

	DIO_VidSetPinDirection(D,PIN3,OUTPUT);
	DIO_VidSetPinValue(D,PIN3,HIGH);

	SPI_VidInit(SPI_POLLING,SLAVE,LSB,MODE0,NO_PRESCALLER);

	EXTERNAL_INTERRUPT_VidSetCallbackINT0(CheckFalling_CallBack);
	EXTERNAL_INTERRUPT_VidInit(EXTERNAL_INTERRUPT_INT0,EXTERNAL_INTERRUPT_FALLING_EDGE);

	_delay_ms(100);

	while(1){

		DHT22_VidRequest();
		DHT22_VidResponse();

		I_RH=DHT22_u8Receive_Data();
		D_RH=DHT22_u8Receive_Data();

		I_TEMP=DHT22_u8Receive_Data();
		D_TEMP=DHT22_u8Receive_Data();

		Check_Sum=DHT22_u8Receive_Data();

		u16 x=(I_RH<<8)|(D_RH);
		u16 y=(I_TEMP<<8)|(D_TEMP);

		if(I_RH+D_RH+I_TEMP+D_TEMP!=Check_Sum){
			LCD_VidWriteCommand(LCD_CLEAR);
			LCD_VidWriteString((u8 *)"ERROOR");
		}
		else{

			SPDR=x/10;
			DIO_VidSetPinValue(D,PIN3,LOW);
			_delay_ms(10);
			DIO_VidSetPinValue(D,PIN3,HIGH);
			while(flag==0);
			SPDR=x%10;
			DIO_VidSetPinValue(D,PIN3,LOW);
			_delay_ms(10);
			DIO_VidSetPinValue(D,PIN3,HIGH);
			while(flag==1);
			SPDR=y/10;
			DIO_VidSetPinValue(D,PIN3,LOW);
			_delay_ms(10);
			DIO_VidSetPinValue(D,PIN3,HIGH);
			while(flag==2);
			SPDR=y%10;
			DIO_VidSetPinValue(D,PIN3,LOW);
			_delay_ms(10);
			DIO_VidSetPinValue(D,PIN3,HIGH);
			while(flag==3);
		}

		ADC_VidInit(ADC_POLLING,ADC_SINGLE_CONVERSION,ADC_CHANNEL0,128);
		ADC_u8StartConversion();
		SPDR=ADC_u8GetResult();
		DIO_VidSetPinValue(D,PIN3,LOW);
		_delay_ms(10);
		DIO_VidSetPinValue(D,PIN3,HIGH);
		while(flag==4);
		ADC_VidInit(ADC_POLLING,ADC_SINGLE_CONVERSION,ADC_CHANNEL1,128);
		ADC_u8StartConversion();
		SPDR=ADC_u8GetResult();
		DIO_VidSetPinValue(D,PIN3,LOW);
		_delay_ms(10);
		DIO_VidSetPinValue(D,PIN3,HIGH);
		while(flag==5);
		flag=0;

		_delay_ms(500);

	}

	return 0 ;


}











/*
 u8 I_RH;
	u8 D_RH;
	u8 I_TEMP;
	u8 D_TEMP;
	u8 Check_Sum;

	LCD_VidInit();
	LCD_VidSetPosition(0,0);
	LCD_VidWriteString((u8 *)"HUM = ");
	LCD_VidSetPosition(1,0);
	LCD_VidWriteString((u8 *)"TEMP = ");

	_delay_ms(100);

	while(1){

		DHT22_VidRequest();
		DHT22_VidResponse();

		I_RH=DHT22_u8Receive_Data();
		D_RH=DHT22_u8Receive_Data();

		I_TEMP=DHT22_u8Receive_Data();
		D_TEMP=DHT22_u8Receive_Data();

		Check_Sum=DHT22_u8Receive_Data();

		u16 x=(I_RH<<8)|(D_RH);
		u16 y=(I_TEMP<<8)|(D_TEMP);

		if(I_RH+D_RH+I_TEMP+D_TEMP!=Check_Sum){
			LCD_VidWriteCommand(LCD_CLEAR);
			LCD_VidWriteString((u8 *)"ERROOR");
		}
		else{

			LCD_VidSetPosition(0,6);
			LCD_VidWriteNumber(x/10);
			LCD_VidWriteChar('.');
			LCD_VidWriteNumber(x%10);

			LCD_VidSetPosition(1,7);
			LCD_VidWriteNumber(y/10);
			LCD_VidWriteChar('.');
			LCD_VidWriteNumber(y%10);
		}
		_delay_ms(500);

	}
 */























/*SPI_VidSetCallBack(Hesham);
	SPI_VidInit(SPI_INTERUPT,SLAVE,LSB,MODE0,NO_PRESCALLER);
	//LCD_VidInit();
	//ULTRASONIC_VidINT0Init();
	DIO_VidSetPinDirection(C,PIN0,OUTPUT);
	while(1){

		if(flag==1){
			SPDR=66;
			x=SPDR;
			if(x==100){
				DIO_VidSetPinValue(C,PIN0,HIGH);
			}
			else{
				DIO_VidSetPinValue(C,PIN0,LOW);
			}
			SPDR=ULTRASONIC_u8INT0GetDistance();
			LCD_VidSetPosition(0,0);
			LCD_VidWriteNumber(SPDR);
			LCD_VidWriteString((u8*)"   ");
			DIO_VidSetPinValue(C,PIN0,HIGH);
		}
		else{
			flag=0;
			LCD_VidWriteCommand(LCD_CLEAR);
			DIO_VidSetPinValue(C,PIN0,LOW);
		}

	}*/









/*	DIO_VidSetPinDirection(C,PIN7,OUTPUT);
	DIO_VidSetPinDirection(C,PIN6,OUTPUT);
	DIO_VidSetPinDirection(C,PIN5,OUTPUT);
	DIO_VidSetPinDirection(C,PIN4,OUTPUT);

	SERVO_SG90_VidInit();

	DCMOTOR_VidInit();

	DCMOTOR_VidSetSpeed(50);

	DIO_VidSetPinDirection(A,PIN0,OUTPUT);

	UART_VidSetCallbackReceiveComplete(Blutooth_vidCallBack);

	UART_VidInit(UART_INTERRUPT,9600);


	while(1){

		if(y==1){

			ULTRASONIC_VidINT1Init();


			while(ULTRASONIC_u8INT1GetDistance()<=30){


				DIO_VidSetPinValue(C,PIN7,LOW);
				DIO_VidSetPinValue(C,PIN6,LOW);
				DIO_VidSetPinValue(C,PIN5,LOW);
				DIO_VidSetPinValue(C,PIN4,LOW);

				_delay_ms(600);

				SERVO_SG90_VidSetAngle(180,TIMER1_CHANNELA);

				SERVO_SG90_VidSetAngle(180,TIMER1_CHANNELB);

				_delay_ms(600);


				DIO_VidSetPinValue(C,PIN7,LOW);
				DIO_VidSetPinValue(C,PIN6,HIGH);
				DIO_VidSetPinValue(C,PIN5,HIGH);
				DIO_VidSetPinValue(C,PIN4,LOW);

				_delay_ms(600);

				DIO_VidSetPinValue(C,PIN7,LOW);
				DIO_VidSetPinValue(C,PIN6,LOW);
				DIO_VidSetPinValue(C,PIN5,LOW);
				DIO_VidSetPinValue(C,PIN4,LOW);

				_delay_ms(600);

				SERVO_SG90_VidSetAngle(90,TIMER1_CHANNELA);

				SERVO_SG90_VidSetAngle(90,TIMER1_CHANNELB);

				_delay_ms(600);


				ULTRASONIC_VidINT0Init();

				while(ULTRASONIC_u8INT0GetDistance()<=30){

					DIO_VidSetPinValue(C,PIN7,LOW);
					DIO_VidSetPinValue(C,PIN6,HIGH);
					DIO_VidSetPinValue(C,PIN5,HIGH);
					DIO_VidSetPinValue(C,PIN4,LOW);

				}


				DIO_VidSetPinValue(C,PIN7,LOW);
				DIO_VidSetPinValue(C,PIN6,LOW);
				DIO_VidSetPinValue(C,PIN5,LOW);
				DIO_VidSetPinValue(C,PIN4,LOW);

				_delay_ms(600);

				SERVO_SG90_VidSetAngle(0,TIMER1_CHANNELA);

				SERVO_SG90_VidSetAngle(0,TIMER1_CHANNELB);

				_delay_ms(600);

				DIO_VidSetPinValue(C,PIN7,LOW);
				DIO_VidSetPinValue(C,PIN6,LOW);
				DIO_VidSetPinValue(C,PIN5,LOW);
				DIO_VidSetPinValue(C,PIN4,LOW);

				_delay_ms(600);

				DIO_VidSetPinValue(C,PIN7,LOW);
				DIO_VidSetPinValue(C,PIN6,HIGH);
				DIO_VidSetPinValue(C,PIN5,HIGH);
				DIO_VidSetPinValue(C,PIN4,LOW);

				_delay_ms(600);

				DIO_VidSetPinValue(C,PIN7,LOW);
				DIO_VidSetPinValue(C,PIN6,LOW);
				DIO_VidSetPinValue(C,PIN5,LOW);
				DIO_VidSetPinValue(C,PIN4,LOW);

				_delay_ms(600);

				SERVO_SG90_VidSetAngle(90,TIMER1_CHANNELA);

				SERVO_SG90_VidSetAngle(90,TIMER1_CHANNELB);

				_delay_ms(600);

				break;

			}


			DIO_VidSetPinValue(C,PIN7,LOW);
			DIO_VidSetPinValue(C,PIN6,HIGH);
			DIO_VidSetPinValue(C,PIN5,HIGH);
			DIO_VidSetPinValue(C,PIN4,LOW);


		}
		else if(y==0){
			DIO_VidSetPinValue(C,PIN7,LOW);
			DIO_VidSetPinValue(C,PIN6,LOW);
			DIO_VidSetPinValue(C,PIN5,LOW);
			DIO_VidSetPinValue(C,PIN4,LOW);
		}

	}*/









/*
int  main(void)
{

	ULTRASONIC_VidICUInit();
	ULTRASONIC_VidINT0Init();
	LCD_VidInit();

	DIO_VidSetPinDirection(A , PIN0 , OUTPUT);
	DIO_VidSetPinDirection(A , PIN1 , OUTPUT);
	DIO_VidSetPinDirection(A , PIN2 , OUTPUT);
	DIO_VidSetPinDirection(A , PIN3 , OUTPUT);



	DCMOTOR_VidInit();
	DCMOTOR_VidSetSpeed(80);


	DIO_VidSetPinValue(A , PIN0 , HIGH);
	DIO_VidSetPinValue(A , PIN1 , LOW);
	DIO_VidSetPinValue(A , PIN2 , LOW);
	DIO_VidSetPinValue(A , PIN3 , HIGH);



	while(1)
	{

		//_delay_ms(5);
		LCD_VidSetPosition(0,0);
		LCD_VidWriteNumber(ULTRASONIC_u8ICUGetDistance());
		LCD_VidWriteString((u8 *)"   ");

		LCD_VidSetPosition(1,0);
		LCD_VidWriteNumber(ULTRASONIC_u8INT0GetDistance());
		LCD_VidWriteString((u8 *)"   ");

		if(ULTRASONIC_u8ICUGetDistance() <= 20 )
		{
			DIO_VidSetPinValue(A , PIN0 , LOW);
			DIO_VidSetPinValue(A , PIN1 , LOW);
			DIO_VidSetPinValue(A , PIN2 , LOW);
			DIO_VidSetPinValue(A , PIN3 , LOW);
			_delay_ms(500);
			//DCMOTOR_VidSetSpeed(60);
			DIO_VidSetPinValue(A , PIN2 , LOW);
			DIO_VidSetPinValue(A , PIN3 , HIGH);
			_delay_ms(280);

			DIO_VidSetPinValue(A , PIN0 , LOW);
			DIO_VidSetPinValue(A , PIN1 , LOW);
			DIO_VidSetPinValue(A , PIN2 , LOW);
			DIO_VidSetPinValue(A , PIN3 , LOW);

			_delay_ms(500);

			DIO_VidSetPinValue(A , PIN0 , HIGH);
			DIO_VidSetPinValue(A , PIN1 , LOW);
			DIO_VidSetPinValue(A , PIN2 , LOW);
			DIO_VidSetPinValue(A , PIN3 , HIGH);

			_delay_ms(500);

			while(ULTRASONIC_u8INT0GetDistance() <= 60);

			DIO_VidSetPinValue(A , PIN0 , LOW);
			DIO_VidSetPinValue(A , PIN1 , LOW);
			DIO_VidSetPinValue(A , PIN2 , LOW);
			DIO_VidSetPinValue(A , PIN3 , LOW);
			_delay_ms(500);


			DIO_VidSetPinValue(A , PIN0 , HIGH);
			DIO_VidSetPinValue(A , PIN1 , LOW);
			DIO_VidSetPinValue(A , PIN2 , LOW);
			DIO_VidSetPinValue(A , PIN3 , LOW);

			_delay_ms(280);

			DIO_VidSetPinValue(A , PIN0 , LOW);
			DIO_VidSetPinValue(A , PIN1 , LOW);
			DIO_VidSetPinValue(A , PIN2 , LOW);
			DIO_VidSetPinValue(A , PIN3 , LOW);

			_delay_ms(500);


		}
		else{

			DIO_VidSetPinValue(A , PIN0 , HIGH);
			DIO_VidSetPinValue(A , PIN1 , LOW);
			DIO_VidSetPinValue(A , PIN2 , LOW);
			DIO_VidSetPinValue(A , PIN3 , HIGH);


		}

	}

	return 1 ;


}

 */




//EEprom
/*
_delay_ms(2000);
LCD_VidInit();

eeprom_init();


u8 x= eeprom_read_byte(100);
LCD_VidWriteNumber(x);

 */


/*
volatile u32 counter = 0 ;
volatile u8 seconds = 0 ;
#define __INTR_ATTRS used , externally_visible
void __vector_10(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_10(void)
{
	counter ++ ;



	if(counter == 10000)
	{   seconds++ ;
		TOG_BIT(PORTA , PIN0);
		if(seconds % 2 == 0 )
		{
			TOG_BIT(PORTA , PIN1);
		}
		if(seconds % 3 == 0)
		{
			TOG_BIT(PORTA , PIN2);
		}
	counter = 0 ;
	}



}

 */

//ultrasonic sensor code

/*
u64 volatile counter = 0 ;
u64 volatile flag  = 0;
u64 volatile snap1  = 0;
u64 volatile snap2  = 0;
u64 volatile snap3  = 0;
u64 freq ;
u64 duty ;

//timer1
#define __INTR_ATTRS used , externally_visible
void __vector_9(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_9(void)
{

	counter ++ ;
}




void __vector_6(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_6(void)
{
if(flag == 0)
{
	snap1 = ICR1A ;
	//LCD_VidWriteNumber(snap1);
	counter = 0 ;
	CLR_BIT(TCCR1B , 6);

}
else if(flag == 1)
{
snap2 = ICR1A  + (counter * 65536);
SET_BIT(TCCR1B , 6);
}
else if (flag == 2)
{
	snap3 = ICR1A  + (counter * 65536);

	CLR_BIT(TIMSK , 5);
	CLR_BIT(TIMSK , 2);

}

flag++ ;

}

int main()
{

	LCD_VidInit();

DIO_VidSetPinDirection(B , PIN3 , OUTPUT);
DIO_VidSetPinDirection(D , PIN6  , INPUT);
TCCR0 = 0b01101101;
OCR0 = 128 ;


TCCR1A = 0b00000000;
TCCR1B = 0b01000001;

SET_BIT(TIMSK , 5);
SET_BIT(TIMSK , 2);

SET_BIT(SREG , 7);

while(1)
{

if(flag == 3)
{

freq = 12000000/(snap3 - snap1);
duty = (snap2 - snap1)*100/(snap3 - snap1);
LCD_VidSetPosition(0 , 0);
LCD_VidWriteNumber(freq);
LCD_VidSetPosition(1 , 0 );
LCD_VidWriteNumber(duty);


flag = 0 ;
SET_BIT(TIFR , 5);
SET_BIT(TIFR , 2);


SET_BIT(TIMSK , 5);
SET_BIT(TIMSK , 2);



}


}




}

 */



/*
	DIO_VidSetPinDirection(A , PIN0 , OUTPUT);
	DIO_VidSetPinValue(A , PIN0 , LOW);

	DIO_VidSetPinDirection(A , PIN1 , OUTPUT);
	DIO_VidSetPinValue(A , PIN1 , LOW);


	DIO_VidSetPinDirection(A , PIN2 , OUTPUT);
	DIO_VidSetPinValue(A , PIN2 , LOW);




	//DIO_VidSetPortDirection(A , 255);

	while(1)
	{
		DIO_VidSetPortValue(A , 0b00000001);
		_delay_ms(3);
		DIO_VidSetPortValue(A , 0b00000010);
		_delay_ms(3);
		DIO_VidSetPortValue(A , 0b00000100);
		_delay_ms(3);
		DIO_VidSetPortValue(A , 0b00001000);
		_delay_ms(3);




	}
	//

	TCCR0 = 0b00001010 ;
	OCR0 = 150 ;
	CLR_BIT(TIMSK , 0);
	SET_BIT(TIMSK , 1);
	SET_BIT(SREG , 7);


	while(1);


	return 1;

 */

//pwm
/*
DIO_VidSetPinDirection(D , PIN5 , OUTPUT);
ICR1A = 3750;
TCCR1A = 0b10000010;
TCCR1B = 0b00011011;



while(1)
{
	OCR1A = 90 ;
	_delay_ms(1000);
	OCR1A = 3375 ;
	_delay_ms(1000);
}

 */






//H-bridge
/*

DIO_VidSetPinDirection(A , PIN0 , OUTPUT);
DIO_VidSetPinDirection(A , PIN1 , OUTPUT);
DIO_VidSetPinDirection(A , PIN2 , OUTPUT);
DIO_VidSetPinDirection(A , PIN3 , OUTPUT);
DIO_VidSetPinValue(A , PIN0 , LOW);
DIO_VidSetPinValue(A , PIN1 , LOW);
DIO_VidSetPinValue(A , PIN2 , LOW);
DIO_VidSetPinValue(A , PIN3 , LOW);
while(1)
{
	DIO_VidSetPinValue(A, PIN0 , HIGH);
	DIO_VidSetPinValue(A , PIN3 ,HIGH);
	_delay_ms(2000);
	DIO_VidSetPinValue(A , PIN0 , LOW);
	DIO_VidSetPinValue(A , PIN1 , LOW);
	DIO_VidSetPinValue(A , PIN2 , LOW);
	DIO_VidSetPinValue(A , PIN3 , LOW);
	_delay_ms(2000);
	DIO_VidSetPinValue(A, PIN1 , HIGH);
	DIO_VidSetPinValue(A, PIN2 , HIGH);
	_delay_ms(2000);

	DIO_VidSetPinValue(A , PIN0 , HIGH);
	DIO_VidSetPinValue(A , PIN1 , HIGH);
	DIO_VidSetPinValue(A , PIN2 , HIGH);
	DIO_VidSetPinValue(A , PIN3 , HIGH);
	_delay_ms(2000);

	DIO_VidSetPinValue(A , PIN0 , LOW);
	DIO_VidSetPinValue(A , PIN1 , LOW);
	DIO_VidSetPinValue(A , PIN2 , LOW);
	DIO_VidSetPinValue(A , PIN3 , LOW);


}


 */
