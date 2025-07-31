/*
 * uart_registers.h
 *
 * Created: 3/8/2025 7:48:04 AM
 *  Author: Ahmad abdullatif
 */


#ifndef UART_REGISTERS_H_
#define UART_REGISTERS_H_

#define UDR_REG   (*(volatile u8*)0x2C)

#define UCSRA_REG (*(volatile u8*)0x2B)
#define RXC_BIT   7
#define TXC_BIT   6
#define UDRE_BIT  5
#define FE_BIT    4
#define DOR_BIT   3
#define PE_BIT    2
#define U2X_BIT   1
#define MPCM_BIT  0

#define UCSRB_REG (*(volatile u8*)0x2A)
#define RXCIE_BIT 7
#define TXCIE_BIT 6
#define UDRIE_BIT 5
#define RXEN_BIT  4
#define TXEN_BIT  3
#define UCSZ2_BIT 2
#define RXB8_BIT  1
#define TXB8_BIT  0

#define UCSRC_REG (*(volatile u8*)0x40)
#define URSEL_BIT 7
#define UMSEL_BIT 6
#define UPM1_BIT  5
#define UPM0_BIT  4
#define USBS_BIT  3
#define UCSZ1_BIT 2
#define UCSZ0_BIT 1
#define UCPOL_BIT 0

#define UBRRL_REG (*(volatile u8*)0x29)









#endif /* UART_REGISTERS_H_ */
