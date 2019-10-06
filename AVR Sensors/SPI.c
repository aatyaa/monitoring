/*
 * SPI.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: jo
 */
#include"TYPES.h"
#include"REGISTERS.h"
#include"MACROS.h"
#include"DIO.h"
#include"SPI.h"

void (*SPI)(void);

void SPI_VidSetCallBack(void (*ptr)(void)){

	SPI=ptr;

}

#define __INTR_ATTRS used , externally_visible
void __vector_12(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_12(void)
{

	SPI();

}


void SPI_VidInit(u8 LOC_u8Communication_Status,u8 LOC_u8MasteOrSlave,u8 LOC_u8Data_Order,u8 LOC_u8CPOL_CPH, u8 LOC_u8Prescaller){

	SET_BIT(SPCR,6);	//enable SPI

	//check about data order MSB or LSB

	if(LOC_u8Data_Order==LSB){

		SET_BIT(SPCR,5);

	}
	else if(LOC_u8Data_Order==MSB){

		CLR_BIT(SPCR,5);

	}

	//switch case about clock phase and clock polarity

	switch(LOC_u8CPOL_CPH){

	case MODE0:

		CLR_BIT(SPCR,3);	//make clock polarity =0

		CLR_BIT(SPCR,2);	//make clock pahse =0

		break;

	case MODE1:

		CLR_BIT(SPCR,3);	//make clock polarity =0

		SET_BIT(SPCR,2);	//make clock pahse =1

		break;

	case MODE2:

		SET_BIT(SPCR,3);	//make clock polarity =1

		CLR_BIT(SPCR,2);	//make clock pahse =0

		break;

	case MODE3:

		SET_BIT(SPCR,3);	//make clock polarity =0

		SET_BIT(SPCR,2);	//make clock pahse =0

		break;

	default:break;

	}

	if(LOC_u8Communication_Status==SPI_INTERUPT){
		SET_BIT(SPCR,7);	// enable prepheral interupt

		SET_BIT(SREG,7);	//enable global interupt

	}

	else if(LOC_u8Communication_Status==SPI_POLLING){

		CLR_BIT(SPCR,7);	// clear prepheral interupt

	}

	if(LOC_u8MasteOrSlave==MASTER){

		DIO_VidSetPinDirection(B , PIN5 , OUTPUT);  //MOSI
		DIO_VidSetPinDirection(B , PIN6 , INPUT);   //MISO
		DIO_VidSetPinDirection(B , PIN4 , OUTPUT);   //SS
		DIO_VidSetPinDirection(B , PIN7 , OUTPUT);   //CLK

		SET_BIT(SPCR,4); //choose master mode

		// switch about prescaller

		switch(LOC_u8Prescaller){

		case 2:

			CLR_BIT(SPCR,0);

			CLR_BIT(SPCR,1);

			SET_BIT(SPSR,0);

			break;

		case 4:

			CLR_BIT(SPCR,0);

			CLR_BIT(SPCR,1);

			CLR_BIT(SPSR,0);

			break;

		case 8:

			SET_BIT(SPCR,0);

			CLR_BIT(SPCR,1);

			SET_BIT(SPSR,0);

			break;

		case 16:

			SET_BIT(SPCR,0);

			CLR_BIT(SPCR,1);

			CLR_BIT(SPSR,0);

			break;

		case 32:

			CLR_BIT(SPCR,0);

			SET_BIT(SPCR,1);

			SET_BIT(SPSR,0);

			break;

		case 64:

			SET_BIT(SPCR,0);

			SET_BIT(SPCR,1);

			SET_BIT(SPSR,0);

			break;

		case 128:

			SET_BIT(SPCR,0);

			SET_BIT(SPCR,1);

			CLR_BIT(SPSR,0);

			break;

		default:break;
		}

	}


	else if(LOC_u8MasteOrSlave==SLAVE){

		DIO_VidSetPinDirection(B , PIN5 , INPUT);  //MOSI
		DIO_VidSetPinDirection(B , PIN6 , OUTPUT); //MISO
		DIO_VidSetPinDirection(B , PIN4 , INPUT);   //SS
		DIO_VidSetPinDirection(B , PIN7 , INPUT);   //CLK

		CLR_BIT(SPCR,4); //choose master mode

	}

}

//if i work interupt

u8 SPI_u8SendToMaster(u8 LOC_u8Data){

	SPDR=LOC_u8Data;

	return SPDR;
}

//if i work interupt

u8 SPI_u8SendToSlave(u8 LOC_u8Data){

	DIO_VidSetPinValue(B , PIN4 , LOW); //choose the slave

	SPDR=LOC_u8Data;

	return SPDR;

}


/*void SPI_VidInitMaster(void)
{
	DIO_VidSetPinDirection(B , PIN5 , OUTPUT);  //MOSI
	DIO_VidSetPinDirection(B , PIN6 , INPUT);   //MISO
	DIO_VidSetPinDirection(B , PIN4 , OUTPUT);   //SS
	DIO_VidSetPinDirection(B , PIN7 , OUTPUT);   //CLK
	CLR_BIT(SPSR , 0);
	SPCR = 0b01111100;



}*/

/*void SPI_VidInitSlave(void)
{
	DIO_VidSetPinDirection(B , PIN5 , INPUT);  //MOSI
	DIO_VidSetPinDirection(B , PIN6 , OUTPUT); //MISO
	DIO_VidSetPinDirection(B , PIN4 , INPUT);   //SS
	DIO_VidSetPinDirection(B , PIN7 , INPUT);   //CLK

	CLR_BIT(SPCR,7); //clear interupt enable bit

	SET_BIT(SPCR,6); //enable spi

	SET_BIT(SPCR,5); //data order (LSB)

	CLR_BIT(SPCR,4); //choose slave channel

	SET_BIT(SPCR,3); //clock polarity =1

	SET_BIT(SPCR,2); //clock phase =1

	CLR_BIT(SPSR , 0);
	SPCR = 0b01101100;



}*/


u8 SPI_u8Transfer_Data_Master(u8 LOC_u8Data)
{

	DIO_VidSetPinValue(B , PIN4 , LOW); //choose the slave

	SPDR = LOC_u8Data ;

	while((GET_BIT(SPSR , 7)) == 0);

	return SPDR ;



}


u8 SPI_u8Transfer_Data_Slave(u8 LOC_u8Data)
{
	SPDR = LOC_u8Data ;

	while((GET_BIT(SPSR , 7)) == 0);

	return SPDR ;



}
