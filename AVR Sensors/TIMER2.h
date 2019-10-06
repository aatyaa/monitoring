/*
 * TIMER2.h
 *
 *  Created on: Feb 7, 2019
 *      Author: Ahmadoh
 */

#ifndef TIMER2_H_
#define TIMER2_H_




/***************************************************************************************/
/* Description ! Driver for 8 - bit Timer2                                             */
/* Release Date! 5/2/2016                                                              */
/***************************************************************************************/


//Macros
#define TIMER2_INTERRUPT 0
#define TIMER2_POLLING  1











void TIMER2_VidOverFlowInit(u8 LOC_u8Timer2Type , u16 LOC_u8Timer2Prescaler );
/***************************************************************************************/
/* Description! Apply initialization sequence for Overflow mode (Normal mode)          */
/* Input      ! TimerType (Interrupt or  polling) , TimerPrscaler                      */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_VidOverFlowInit( ENTERRUPT , 256 );                             */
/***************************************************************************************/






void TIMER2_VidCTCInit(u8 LOC_u8Timer2Type , u8 LOC_u8TimerMax , u16 LOC_u8Timer2Prescaler );
/***************************************************************************************/
/* Description! Apply initialization sequence for CTC mode (Normal mode)               */
/* Input      ! TimerType (Interrupt or  polling) , TimerMax ,TimerPrscaler            */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_VidCTCInit(POLLING , 150 , 256 );                               */
/***************************************************************************************/






void TIMER2_VidSetOverFlowInitialValue(u8 LOC_u8InitialValue );
/***************************************************************************************/
/* Description! set initialize value in timer register                                 */
/* Input      ! initialize value                                                       */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_VidSetInitialValue(150);                                        */
/***************************************************************************************/







u8 TIMER2_u8GetOverflowFlag(void);
/***************************************************************************************/
/* Description! get overflow mode flag                                                 */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_u8GetOverflowFlag();                                            */
/***************************************************************************************/





u8 TIMER2_u8GetCTCFlag(void);
/***************************************************************************************/
/* Description! get CTC mode flag                                                      */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_u8GetCTCFlag();                                                 */
/***************************************************************************************/



void TIMER2_VidClrFlags(void);
/***************************************************************************************/
/* Description! Clear Overflow and CTC flag                                            */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_VidClrFlags();                                                  */
/***************************************************************************************/







void TIMER2_VidFastPWMSetT_totalOverFlow(u16 LOC_u16Timer0Prescaler  );
/***************************************************************************************/
/* Description! Interface to intialize the fast PWM (fixed size register)              */
/*              choosing the T(total)                                                  */
/* Input      ! Prescaler for the fixed size 8-bit register                            */
/* Output     ! Nothing                                                                */
/* Example    ! void TIMER2_VidFastPWMInit( 1024 );                                    */
/***************************************************************************************/





void TIMER2_VidSetT_on(u8 LOC_u8DutyCyle);
/***************************************************************************************/
/* Description! Interface to set the value of duty register                            */
/* Input      ! ratio of duty cycle from 0 to 255                                      */
/* Output     ! Nothing                                                                */
/* Example    ! void TIMER0_VidSetDutyCyle(128); //50% duty cycle                      */
/***************************************************************************************/







void TIMER2_VidSetCallbackOverflow(void ( *ptr) (void));
/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to overflow callback function           */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_VidSetCallbackOverflow( CallBack function name );               */
/***************************************************************************************/




void TIMER2_VidSetCallbackCTC(void (*ptr) (void));
/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to CTC callback function                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER2_VidSetCallbackCTC( CallBack function name );                    */
/***************************************************************************************/







u8 TIMER2_u8GetCounter(void);


void TIMER2_VidDisableOverFlowInterrupt(void);


void TIMER2_VidDisableCTCInterrupt(void);


#endif /* TIMER2_H_ */
