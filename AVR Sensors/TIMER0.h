/*
 * TIMER0.h
 *
 *  Created on: Feb 5, 2019
 *      Author: Ahmadoh
 */

#ifndef TIMER0_H_
#define TIMER0_H_


/***************************************************************************************/
/* Description ! Driver for 8- bit Timer0                                              */
/* Release Date! 5/2/2016                                                              */
/***************************************************************************************/


//Macros
#define TIMER0_INTERRUPT 0
#define TIMER0_POLLING  1











void TIMER0_VidOverFlowInit(u8 LOC_u8Timer0Type , u16 LOC_u8Timer0Prescaler );
/***************************************************************************************/
/* Description! Apply initialization sequence for Overflow mode (Normal mode)          */
/* Input      ! TimerType (Interrupt or  polling) , TimerPrscaler                      */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidOverFlowInit( ENTERRUPT , 256 );                             */
/***************************************************************************************/






void TIMER0_VidCTCInit(u8 LOC_u8Timer0Type , u8 LOC_u8TimerMax , u16 LOC_u8Timer0Prescaler );
/***************************************************************************************/
/* Description! Apply initialization sequence for CTC mode (Normal mode)               */
/* Input      ! TimerType (Interrupt or  polling) , TimerMax ,TimerPrscaler            */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidCTCInit(POLLING , 150 , 256 );                               */
/***************************************************************************************/






void TIMER0_VidSetOverFlowInitialValue(u8 LOC_u8InitialValue );
/***************************************************************************************/
/* Description! set initialize value in timer register                                 */
/* Input      ! initialize value                                                       */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidSetInitialValue(150);                                        */
/***************************************************************************************/







u8 TIMER0_u8GetOverflowFlag(void);
/***************************************************************************************/
/* Description! get overflow mode flag                                                 */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_u8GetOverflowFlag();                                            */
/***************************************************************************************/





u8 TIMER0_u8GetCTCFlag(void);
/***************************************************************************************/
/* Description! get CTC mode flag                                                      */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_u8GetCTCFlag();                                                 */
/***************************************************************************************/



void TIMER0_VidClrFlags(void);
/***************************************************************************************/
/* Description! Clear Overflow and CTC flag                                            */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidClrFlags();                                                  */
/***************************************************************************************/






void TIMER0_VidFastPWMSetT_totalOverFlow(u16 LOC_u16Timer0Prescaler  );
/***************************************************************************************/
/* Description! Interface to intialize the fast PWM (fixed size register)              */
/*              choosing the T(total)                                                  */
/* Input      ! Prescaler for the fixed size 8-bit register                            */
/* Output     ! Nothing                                                                */
/* Example    ! void TIMER0_VidFastPWMInit( 1024 );                                    */
/***************************************************************************************/





void TIMER0_VidSetT_on(u8 LOC_u8DutyCyle);
/***************************************************************************************/
/* Description! Interface to set the value of duty register                            */
/* Input      ! ratio of duty cycle from 0 to 255                                      */
/* Output     ! Nothing                                                                */
/* Example    ! void TIMER0_VidSetDutyCyle(128); //50% duty cycle                      */
/***************************************************************************************/





void TIMER0_VidSetCallbackOverflow(void ( *ptr) (void));
/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to overflow callback function           */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidSetCallbackOverflow( CallBack function name );               */
/***************************************************************************************/




void TIMER0_VidSetCallbackCTC(void ( *ptr) (void));
/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to CTC callback function                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidSetCallbackCTC( CallBack function name );                    */
/***************************************************************************************/




u8 TIMER0_u8GetCounter(void);



void TIMER0_VidDisableOverFlowInterrupt(void);



void TIMER0_VidDisableCTCInterrupt(void);


#endif /* TIMER0_H_ */
