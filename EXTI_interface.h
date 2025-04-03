/*
 * EXTI_interface.h
 *
 * Created: 2/15/2025 11:34:31 AM
 *  Author: Ahmad abdullatif
 */


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


//EXTI macors
#define EXTI_EXTI0 0
#define EXTI_EXTI1 1
#define EXTI_EXTI2 2


//Sense control macros
#define EXTI_LOW_LEVEL          0
#define EXTI_ANY_LOGICAL_CHANGE 1
#define EXTI_FALLING_EDGE       2
#define EXTI_RISING_EDGE        3


//EXTI APIs

void EXTI_voidExternalInterruptInit   (u8 copy_u8ExtiId,u8 copy_u8SenseContolType);
void EXTI_voidExternalInterruptEnable (u8 copy_u8ExtiId);
void EXTI_voidExternalInterruptDisable(u8 copy_u8ExtiId);


#endif /* EXTI_INTERFACE_H_ */
