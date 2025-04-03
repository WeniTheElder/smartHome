/*
 * LCD_interface.h
 *
 * Created: 2/14/2025 5:32:08 AM
 *  Author: Ahmad abdullatif
 */


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include "std_types.h"

void LCD_voidInit            (void);
void LCD_voidDisplayCharacter(u8 copy_u8char);
void LCD_voidShiftDisplayLeft(u8 copy_u8NumberOfShits);
void LCD_voidDisplayString   (const char arr[]);
void LCD_voidMoveToSecondLine(void);
void LCD_voidClearDisplay    (void);
void LCD_voidDisplayNumber   (u32 copy_u32Number);




#endif /* LCD_INTERFACE_H_ */
