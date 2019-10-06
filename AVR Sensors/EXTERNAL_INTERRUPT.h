/*
 * EXTERNAL_INTERRUPT.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: jo
 */

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_


/***************************************************************************************/
/* Description ! Driver for external interrupt (INT0 , INT1)                           */
/* Release Date! 28/6/2016                                                             */
/***************************************************************************************/


#define EXTERNAL_INTERRUPT_INT0 0
#define EXTERNAL_INTERRUPT_INT1 1
#define EXTERNAL_INTERRUPT_RISING_EDGE 2
#define EXTERNAL_INTERRUPT_FALLING_EDGE 3
#define EXTERNAL_INTERRUPT_ONCHANGE 4



void EXTERNAL_INTERRUPT_VidInit(u8 LOC_u8IntNum , u8 LOC_u8IntState );
/***************************************************************************************/
/* Description! Apply initialization sequence External Interrupt                       */
/* Input      ! INT number , INT state                                                 */
/* Output     ! Nothing                                                                */
/* Example    ! EXTERNAL_INTERRUPT_VidInit(INT0 , RISING_EDGE );                       */
/***************************************************************************************/






void EXTERNAL_INTERRUPT_VidSetCallbackINT0(void ( *ptr) (void));
/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to INT0 callback function               */
/* Output     ! Nothing                                                                */
/* Example    ! EXTERNAL_INTERRUPT_VidSetCallbackINT0( CallBack function name );       */
/***************************************************************************************/





void EXTERNAL_INTERRUPT_VidSetCallbackINT1(void ( *ptr) (void));
/***************************************************************************************/
/* Description! Interface to take a copy from callback function                        */
/* Input      ! Pointer to function that point to INT0 callback function               */
/* Output     ! Nothing                                                                */
/* Example    ! EXTERNAL_INTERRUPT_VidSetCallbackINT0( CallBack function name );       */
/***************************************************************************************/



void EXTERNAL_INTERRUPT_VidDisableExternalInterrupt(u8 LOC_u8IntNum);


#endif /* EXTERNAL_INTERRUPT_H_ */
