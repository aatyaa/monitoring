/*
 * DHT22.h
 *
 *  Created on: Jul 11, 2019
 *      Author: le
 */

#ifndef DHT22_H_
#define DHT22_H_


#define DHT22_PORT D
#define DHT22_PIN  PIN0

void DHT22_VidRequest(void);

void DHT22_VidResponse(void);

u8 DHT22_u8Receive_Data(void);


#endif /* DHT22_H_ */
