/*
 * ADC.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: jo
 */

#ifndef ADC_H_
#define ADC_H_


/***************************************************************************************/
/* Description ! Driver for Analog digital conventor                                   */
/* Release Date! 4/2/2019                                                             */
/***************************************************************************************/




//Channels in PORTA
#define ADC_CHANNEL0  0   //PIN0
#define ADC_CHANNEL1  1
#define ADC_CHANNEL2  2
#define ADC_CHANNEL3  3
#define ADC_CHANNEL4  4
#define ADC_CHANNEL5  5
#define ADC_CHANNEL6  6
#define ADC_CHANNEL7  7  //PIN7



//ADC type
#define ADC_INTERRUPT 8
#define ADC_POLLING 9



//ADC Modes
#define ADC_SINGLE_CONVERSION 10
#define ADC_FREE_RUNNING 11
#define ADC_EXTERNAL_INTERRUPT0 12





void ADC_VidInit(u8 LOC_u8AdcType , u8 LOC_u8AdcMode , u8 LOC_u8ChannelNum , u8 LOC_u8Prescaler);
/***************************************************************************************/
/* Description! Apply initialization sequence ADC                                      */
/* Input      ! ADC type  ,  ADC mode , Channel num  , Prescaler                       */
/* Output     ! Nothing                                                                */
/* Example    ! ADC_VidInit(INTERRUPT , SINGLE_CONVERSION , CHANNEL0 , 128 );          */
/***************************************************************************************/





void ADC_VidSetCallback(void ( *ptr) (void));
/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to ADC interrupt callback function      */
/* Output     ! Nothing                                                                */
/* Example    ! ADC_VidSetCallbackI( CallBack function name );                         */
/***************************************************************************************/




u8 ADC_u8GetResult(void);
/***************************************************************************************/
/* Description! Interface to get result of conversion                                  */
/* Input      ! Nothing                                                                */
/* Output     ! Result                                                                 */
/* Example    ! u16 result =  ADC_u8GetResult();                                       */
/***************************************************************************************/




void ADC_u8StartConversion(void);
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







#endif /* ADC_H_ */
