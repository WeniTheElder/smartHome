/*
 * pwm2_program.c
 *
 * Created: 4/3/2025 7:22:36 AM
 *  Author: Ahmad abdullatif
 */
#include "std_types.h"
#include "bit_math.h"
#include "DIO_interface.h"
#include "pwm2_interface.h"
#include "pwm2_registers.h"


void PWM2_voidInit (){
	//set fast PWM mode
	SET_BIT(TCCR2_REGISTER,WGM20_BIT);
	SET_BIT(TCCR2_REGISTER,WGM21_BIT);
	//set PWM mode to non inverting
	SET_BIT  (TCCR2_REGISTER,COM21_BIT);
	CLEAR_BIT(TCCR2_REGISTER,COM20_BIT);
	//set oc2 pin as output
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN7,DIO_OUTPUT);
}
void PWM2_voidStart(u8 copy_u8DutyCycle){
	OCR2_REGISTER = (((copy_u8DutyCycle*256)/100)-1);
	
	//set prescaller to 64 & start timer
	SET_BIT  (TCCR2_REGISTER,CS20_BIT);
	SET_BIT  (TCCR2_REGISTER,CS21_BIT);
	CLEAR_BIT(TCCR2_REGISTER,CS22_BIT);
}
void PWM2_voidStop (){
	CLEAR_BIT(TCCR2_REGISTER,CS20_BIT);
	CLEAR_BIT(TCCR2_REGISTER,CS21_BIT);
	CLEAR_BIT(TCCR2_REGISTER,CS22_BIT);
}