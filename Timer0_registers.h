/*
 * Timer0_registers.h
 *
 * Created: 2/17/2025 1:34:51 PM
 *  Author: Ahmad abdullatif
 */


#ifndef TIMER0_REGISTERS_H_
#define TIMER0_REGISTERS_H_

#define TCCR0_REGISTER (*(volatile u8*)0x53)  //timer/counter0 control register
#define FOC0_BIT  7
#define WGM00_BIT 6
#define COM01_BIT 5
#define COM00_BIT 4
#define WGM01_BIT 3
#define CS02_BIT  2
#define CS01_BIT  1
#define CS00_BIT  0

#define TCNT0_REGISTER (*(volatile u8*)0x52)  //timer/counter0 register

#define OCR0_REGISTER  (*(volatile u8*)0x5C)  //output compare register

#define TIMSK_REGISTER (*(volatile u8*)0x59)  //timer/counter interrupt mask register
#define TOIE0_BIT 0
#define OCIE0_BIT 1


#define TIFR_REGISTER  (*(volatile u8*)0x58)  //timer/counter interrupt flag register
#define TOV0_BIT  0
#define OCF0_BIT  1 






#endif /* TIMER0_REGISTERS_H_ */
