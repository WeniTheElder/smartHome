/*
 * GI_registers.h
 *
 * Created: 2/15/2025 12:55:32 PM
 *  Author: Ahmad abdullatif
 */


#ifndef GI_REGISTERS_H_
#define GI_REGISTERS_H_

#define SREG_REGISTER (*(volatile u8*)0x5F) //status register
#define GI_I_BIT      7                     //General interrupt enable bit



#endif /* GI_REGISTERS_H_ */
