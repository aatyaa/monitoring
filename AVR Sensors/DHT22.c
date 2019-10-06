#define F_CPU 12000000UL
#include"TYPES.h"
#include<util/delay.h>
#include"DIO.h"
#include"DHT22.h"
#include"LCD.h"
#include"TIMER1.h"

u8 Receive_Data=0b00000000;

//this function is give DHT22 pulse (start signal) to start work
void DHT22_VidRequest(void){

	//make pin output
	DIO_VidSetPinDirection(DHT22_PORT,DHT22_PIN,OUTPUT);

	//make the pin low for at least 500us
	DIO_VidSetPinValue(DHT22_PORT,DHT22_PIN,LOW);

	_delay_ms(1);

	//make pin high after 20ms
	DIO_VidSetPinValue(DHT22_PORT,DHT22_PIN,HIGH);

}

//this function is for the DHT22 response that the sensor response to you after give it start pulse
void DHT22_VidResponse(void){

	//make pin input
	DIO_VidSetPinDirection(DHT22_PORT,DHT22_PIN,INPUT);

	while(DIO_u8ReadPin(DHT22_PORT,DHT22_PIN));     //wait for high (20 ~ 40us)

	while(DIO_u8ReadPin(DHT22_PORT,DHT22_PIN)==0);	//wait for low pulse responsed from DHT22 (80us)

	while(DIO_u8ReadPin(DHT22_PORT,DHT22_PIN));  	//wait for high pulse responsed from DHT22 (80us)

}

//this function is for receive 8bit data only at a time
u8 DHT22_u8Receive_Data(void){

	for(u8 i=0;i<8;i++){

		while(DIO_u8ReadPin(DHT22_PORT,DHT22_PIN)==0);	//wait for the low pulse contained in data (50us)

		//_delay_us(28);								    //wait 28us

		for(u8 i=0;i<50;i++){

		}

		if(DIO_u8ReadPin(DHT22_PORT,DHT22_PIN)){       //check if data is logic 1

			Receive_Data=(Receive_Data<<1)|(0x01);

		}else{                                         //check if the data is logic 0

			Receive_Data=(Receive_Data<<1);

		}

		while(DIO_u8ReadPin(DHT22_PORT,DHT22_PIN));	   //wait for completing the high pulse if data is logic 1 (complete 70us)

	}

	return Receive_Data;
}


