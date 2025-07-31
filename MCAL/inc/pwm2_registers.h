/*
 * pwm2_registers.h
 *
 * Created: 4/3/2025 7:22:27 AM
 *  Author: Ahmad abdullatif
 */


#ifndef PWM2_REGISTERS_H_
#define PWM2_REGISTERS_H_


#define TCCR2_REGISTER (*(volatile u8*)0x45)
#define FOC2_BIT  7
#define WGM20_BIT 6
#define COM21_BIT 5
#define COM20_BIT 4
#define WGM21_BIT 3
#define CS22_BIT  2
#define CS21_BIT  1
#define CS20_BIT  0

#define TCNT2_REGISTER (*(volatile u8*)0x44)

#define OCR2_REGISTER  (*(volatile u8*)0x43)

#define TIMSK_REGISTER (*(volatile u8*)0x59)
#define OCIE2_BIT 7
#define TOIE2_BIT 6

#define TIFR_REGISTER  (*(volatile u8*)0x58)
#define OCF2_BIT  7
#define TOV2_BIT  6

#define SFIOR_REGISTER (*(volatile u8*)0x50)
#define PSR2_BIT 1



#endif /* PWM2_REGISTERS_H_ */
