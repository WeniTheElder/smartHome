/*
 * uart_interface.h
 *
 * Created: 3/8/2025 7:48:04 AM
 *  Author: Ahmad abdullatif
 */


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_voidInit    (void);
void UART_voidTxChar  (u8 copy_u8TxData);
void UART_voidRxChar  (u8* copy_pu8RxData);
void UART_voidTxString(const char* copy_pu8String);
void UART_voidRxString(u8* copy_pu8String);




#endif /* UART_INTERFACE_H_ */
