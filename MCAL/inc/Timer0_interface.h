/*
 * Timer0_interface.h
 *
 * Created: 2/17/2025 1:34:40 PM
 *  Author: Ahmad abdullatif
 */


#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

//modes of operation options
#define TIMER0_NORMAL_MODE   0
#define TIMER0_CTC_MODE      1



//timer0 APIs
void TIMER0_voidInit               (u8 copy_u8ModeOfOperatino);
void TIMER0_voidStartTimer         (void);
void TIMER0_voidStopTimer          (void);
void TIMER0_voidSetCallBackFunction(void(*pf)(void));




#endif /* TIMER0_INTERFACE_H_ */
