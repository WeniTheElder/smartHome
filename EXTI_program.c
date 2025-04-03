/*
 * EXTI_program.c
 *
 * Created: 2/15/2025 11:34:54 AM
 *  Author: Ahmad abdullatif
 */
#include "std_types.h"
#include "bit_math.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "EXTI_registers.h"

void EXTI_voidExternalInterruptInit(u8 copy_u8ExtiId,u8 copy_u8SenseContolType){
	switch(copy_u8ExtiId){
		
		case EXTI_EXTI0:
		switch(copy_u8SenseContolType){
			case EXTI_LOW_LEVEL:
			CLEAR_BIT(MCUCR_REGISTER,EXTI_ISC00_BIT);
			CLEAR_BIT(MCUCR_REGISTER,EXTI_ISC01_BIT);
			break;
			case EXTI_ANY_LOGICAL_CHANGE:
			SET_BIT  (MCUCR_REGISTER,EXTI_ISC00_BIT);
			CLEAR_BIT(MCUCR_REGISTER,EXTI_ISC01_BIT);
			break;
			case EXTI_FALLING_EDGE:
			CLEAR_BIT(MCUCR_REGISTER,EXTI_ISC00_BIT);
			SET_BIT  (MCUCR_REGISTER,EXTI_ISC01_BIT);
			break;
			case EXTI_RISING_EDGE:
			SET_BIT  (MCUCR_REGISTER,EXTI_ISC00_BIT);
			SET_BIT  (MCUCR_REGISTER,EXTI_ISC01_BIT);
			break;
		}
		break;
		
		case EXTI_EXTI1:
		switch(copy_u8SenseContolType){
			case EXTI_LOW_LEVEL:
			CLEAR_BIT(MCUCR_REGISTER,EXTI_ISC10_BIT);
			CLEAR_BIT(MCUCR_REGISTER,EXTI_ISC11_BIT);
			break;
			case EXTI_ANY_LOGICAL_CHANGE:
			SET_BIT  (MCUCR_REGISTER,EXTI_ISC10_BIT);
			CLEAR_BIT(MCUCR_REGISTER,EXTI_ISC11_BIT);
			break;
			case EXTI_FALLING_EDGE:
			CLEAR_BIT(MCUCR_REGISTER,EXTI_ISC10_BIT);
			SET_BIT  (MCUCR_REGISTER,EXTI_ISC11_BIT);
			break;
			case EXTI_RISING_EDGE:
			SET_BIT  (MCUCR_REGISTER,EXTI_ISC10_BIT);
			SET_BIT  (MCUCR_REGISTER,EXTI_ISC11_BIT);
			break;
		}
		break;
		
		case EXTI_EXTI2:
		switch(copy_u8SenseContolType){
			case EXTI_FALLING_EDGE:
			CLEAR_BIT(MCUCSR_REGISTER,EXTI_ISC2_BIT);
			break;
			case EXTI_RISING_EDGE:
			SET_BIT  (MCUCSR_REGISTER,EXTI_ISC2_BIT);
			break;
		}
		break;
	}
}
void EXTI_voidExternalInterruptEnable(u8 copy_u8ExtiId){
	switch(copy_u8ExtiId){
		case EXTI_EXTI0:
		SET_BIT(GICR_REGISTER,EXTI_INT0_BIT);
		break;
		case EXTI_EXTI1:
		SET_BIT(GICR_REGISTER,EXTI_INT1_BIT);
		break;
		case EXTI_EXTI2:
		SET_BIT(GICR_REGISTER,EXTI_INT2_BIT);
		break;
	}
}
void EXTI_voidExternalInterruptDisable(u8 copy_u8ExtiId){
	switch(copy_u8ExtiId){
		case EXTI_EXTI0:
		CLEAR_BIT(GICR_REGISTER,EXTI_INT0_BIT);
		break;
		case EXTI_EXTI1:
		CLEAR_BIT(GICR_REGISTER,EXTI_INT1_BIT);
		break;
		case EXTI_EXTI2:
		CLEAR_BIT(GICR_REGISTER,EXTI_INT2_BIT);
		break;
	}
}