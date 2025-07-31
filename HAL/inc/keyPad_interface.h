/*
 * keyPad_interface.h
 *
 * Created: 2/14/2025 7:44:36 AM
 *  Author: Ahmad abdullatif
 */


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#define KEY_NOT_PRESSED 0

void KEYPAD_voidInit         (void);
void KEYPAD_voidGetPressedKey(u8* copy_pu8pressedKey);
void priv_voidLCDLightSystem();



#endif /* KEYPAD_INTERFACE_H_ */
