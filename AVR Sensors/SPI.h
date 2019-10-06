/*
 * SPI.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: jo
 */

#ifndef SPI_H_
#define SPI_H_

void SPI_VidInit(u8 LOC_u8Communication_Status,u8 LOC_u8MasteOrSlave,u8 LOC_u8Data_Order,u8 LOC_u8CPOL_CPH, u8 LOC_u8Prescaller);

void SPI_VidSetCallBack(void (*ptr)(void));

u8 SPI_u8Transfer_Data_Master(u8 LOC_u8Data);

void SPI_VidInitMaster(void);

void SPI_VidInitSlave(void);

u8 SPI_u8Transfer_Data_Slave(u8 LOC_u8Data);

u8 SPI_u8SendToMaster(u8 LOC_u8Data);

u8 SPI_u8SendToSlave(u8 LOC_u8Data);

/////////////////////////////////////////

#define SPI_INTERUPT 0

#define SPI_POLLING 1

///////////////////////////////////////
#define MASTER 0

#define SLAVE 1

//////////////////////////////////////

#define LSB 0

#define MSB 1

/////////////////////////////////////

#define MODE0 0

#define MODE1 1

#define MODE2 2

#define MODE3 3

//////////////////////////////////////////

#define NO_PRESCALLER 0

#endif /* SPI_H_ */
