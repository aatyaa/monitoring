/*
 * ULTRASONIC.h
 *
 *  Created on: May 28, 2019
 *      Author: le
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


void ULTRASONIC_VidICUInit(void);
u8 ULTRASONIC_u8ICUGetDistance(void);




void ULTRASONIC_VidINT0Init(void);
u8 ULTRASONIC_u8INT0GetDistance(void);



void ULTRASONIC_VidINT1Init(void);
u8 ULTRASONIC_u8INT1GetDistance(void);


#endif /* ULTRASONIC_H_ */
