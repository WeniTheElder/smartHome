/*
 * uart_program.c
 *
 * Created: 3/8/2025 7:48:04 AM
 *  Author: Ahmad abdullatif
 */

#include "std_types.h"
#include "bit_math.h"
#include "uart_interface.h"
#include "uart_private.h"
#include "uart_registers.h"



void UART_voidInit(void)
{
	//set baud rate value to 9600
	UBRRL_REG = UBRR_VALUE;
	//disable double speed mode
	CLEAR_BIT(UCSRA_REG, U2X_BIT);
	
	// Disable UART interrupts
	CLEAR_BIT(UCSRB_REG, RXCIE_BIT);
	CLEAR_BIT(UCSRB_REG, TXCIE_BIT);
	CLEAR_BIT(UCSRB_REG, UDRIE_BIT);
	
	//configuring UART to standard configurations(8n1 9600)
	UCSRC_REG = 0x86; //0b10000110;
	CLEAR_BIT(UCSRB_REG, UCSZ2_BIT);
	
	// Enable UART Rx
	SET_BIT(UCSRB_REG, RXEN_BIT);
	
	// Enable UART Tx
	SET_BIT(UCSRB_REG, TXEN_BIT);
}
void UART_voidTxChar(u8 copy_u8TxData){
	//busy wait for UDE empty flag
	while(GET_BIT(UCSRA_REG,UDRE_BIT) == 0);
	//putting data in UDR
	UDR_REG = copy_u8TxData;
}
void UART_voidRxChar(u8* copy_pu8RxData){
	while(GET_BIT(UCSRA_REG,RXC_BIT) == 0);
	*copy_pu8RxData = UDR_REG;
}
void UART_voidTxString(const char* copy_pu8String){
	u8 local_u8Counter = 0;
	u8 local_u8currentChar = copy_pu8String[0];
	while(local_u8currentChar != '\0'){
		UART_voidTxChar(local_u8currentChar);
		++local_u8Counter;
		local_u8currentChar = copy_pu8String[local_u8Counter];
	}
}
void UART_voidRxString(u8* copy_pu8String){
	u8 local_u8Counter = 0;
	while(1){
		//receiving the char in the array
		UART_voidRxChar(&copy_pu8String[local_u8Counter]);
		//checking if the last received char is '$'
		if(copy_pu8String[local_u8Counter] == '$'){
			//stop receiving
			break;
		}
		else{
			//increment the counter and keep receiving
			++local_u8Counter;
		}
	}
	//changing '$' to '\0'
	copy_pu8String[local_u8Counter] = '\0';
}