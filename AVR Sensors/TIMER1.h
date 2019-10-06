/*
 * TIMER1.h
 *
 *  Created on: Feb 6, 2019
 *      Author: Ahmadoh
 */

#ifndef TIMER1_H_
#define TIMER1_H_



/***************************************************************************************/
/* Description ! Driver for 16 - bit Timer1                                            */
/* Release Date! 5/2/2016                                                              */
/***************************************************************************************/



//Macros
#define TIMER1_INTERRUPT 0
#define TIMER1_POLLING  1
#define TIMER1_CHANNELA 2
#define TIMER1_CHANNELB 3
#define TIMER1_RISING_EDGE 4
#define TIMER1_FALLING_EDGE 5









void TIMER1_VidOverFlowInit(u8 LOC_u8Timer1Type  , u16 LOC_u8Timer1Prescaler );
/***************************************************************************************/
/* Description! Apply initialization sequence for Overflow mode (Normal mode)          */
/* Input      ! TimerType (Interrupt or  polling) , TimerPrscaler                      */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_VidOverFlowInit( ENTERRUPT , 256 );                             */
/***************************************************************************************/







void TIMER1_VidCTCInit(u8 LOC_u8Timer1Type ,  u16 LOC_u16TimerMax , u16 LOC_u8Timer1Prescaler );
/***************************************************************************************/
/* Description! Apply initialization sequence for CTC mode (Normal mode)               */
/* Input      ! TimerType (Interrupt or  polling) , TimerMax ,TimerPrscaler            */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_VidCTCInit(POLLING , 150 , 256 );                               */
/***************************************************************************************/






void TIMER1_VidSetOverFlowInitialValue(u16 LOC_u8InitialValue );
/***************************************************************************************/
/* Description! set initialize value in timer register                                 */
/* Input      ! initialize value                                                       */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_VidSetInitialValue(150);                                        */
/***************************************************************************************/







u8 TIMER1_u8GetOverflowFlag(void);
/***************************************************************************************/
/* Description! get overflow mode flag                                                 */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_u8GetOverflowFlag();                                            */
/***************************************************************************************/





u8 TIMER1_u8GetCTCFlag(void);
/***************************************************************************************/
/* Description! get CTC mode flag                                                      */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_u8GetCTCFlag();                                                 */
/***************************************************************************************/





void TIMER1_VidClrFlags(void);
/***************************************************************************************/
/* Description! Clear Overflow and CTC flag                                            */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER0_VidClrFlags();                                                  */
/***************************************************************************************/





//in PWM you can use the two channel  together but must by the same T(total)
void TIMER1_VidFastPWMSetT_totalCTC( u16 LOC_u16Timer1Max  ,u16 LOC_u16Timer1Prescaler  );
/****************************************************************************************/
/* Description! Interface to intialize the fast PWM(not fixed register , can change top)*/
/*              choosing the channel and the T(total)                                   */
/* Input      ! Prescaler for the non fixed size 16-bit register                        */
/* Output     ! Nothing                                                                 */
/* Example    ! void TIMER0_VidFastPWMInit(PWMCHANNELA ,  ,  1024 );                    */
/****************************************************************************************/




void TIMER1_VidSetT_on(u8 LOC_u8PWMChannel , u16 LOC_u16DutyCyle);
/***************************************************************************************/
/* Description! Interface to set the value of duty register                            */
/* Input      ! ratio of the top (duty cycle from 0 to 65536)                          */
/* Output     ! Nothing                                                                */
/* Example    ! void TIMER1_VidSetDutyCyle(200); //50% duty cycle of the top 400       */
/***************************************************************************************/





void TIMER1_VidSetCallbackOverflow(void ( *ptr) (void));
/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to overflow callback function           */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_VidSetCallbackOverflow( CallBack function name );               */
/***************************************************************************************/




void TIMER1_VidSetCallbackCTC(void ( *ptr) (void));
/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to CTC callback function                */
/* Output     ! Nothing                                                                */
/* Example    ! TIMER1_VidSetCallbackCTC( CallBack function name );                    */
/***************************************************************************************/




u16 TIMER1_u16GetCounter(void);


void TIMER1_VidInputCaptureUnitInit(u8 LOC_u8ICPState);


void TIMER1_VidClrInputCaptureUnitFlag(void);


u16 TIMER1_u16GetInputCaptureUnitRegister(void);


void TIMER1_VidDisableInputCaptureUnitInterrupt(void);


void TIMER1_VidDisableOverFlowInterrupt(void);


void TIMER1_VidDisableCTCInterrupt(void);


void TIMER1_VidSetCallbackInputCaptureUnit(void ( *ptr) (void));



void TIMER1_VidSetInputCaptureUnitPrepheralInterupt(void);


void TIMER1_VidSetOverFlowPrepheralInterupt(void);


void TIMER1_VidSetCtcPrepheralInterupt(void);

#endif /* TIMER1_H_ */
