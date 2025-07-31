/*
 * EXTI_registers.h
 *
 * Created: 2/15/2025 11:34:43 AM
 *  Author: Ahmad abdullatif
 */


#ifndef EXTI_REGISTERS_H_
#define EXTI_REGISTERS_H_

#define MCUCR_REGISTER  (*(volatile u8*)0x55) //micro controller unit control register
#define GICR_REGISTER   (*(volatile u8*)0x5B) //general interrupt control register
#define MCUCSR_REGISTER (*(volatile u8*)0x54) //micro controller unit control ans status register

//interrupt sense control bits numbers
#define EXTI_ISC00_BIT 0           
#define EXTI_ISC01_BIT 1      
#define EXTI_ISC10_BIT 2      
#define EXTI_ISC11_BIT 3      
#define EXTI_ISC2_BIT  6

//external interrupt enable bits number
#define EXTI_INT2_BIT  5   
#define EXTI_INT0_BIT  6
#define EXTI_INT1_BIT  7




#endif /* EXTI_REGISTERS_H_ */
