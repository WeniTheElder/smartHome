/*
 * keypad_config.h
 *
 * Created: 2/14/2025 7:47:59 AM
 *  Author: Ahmad abdullatif
 */


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

//macros for columns
#define KEYPAD_COLUMN0_PORT DIO_PORTB
#define KEYPAD_COLUMN0_PIN  DIO_PIN1 
#define KEYPAD_COLUMN1_PORT DIO_PORTB
#define KEYPAD_COLUMN1_PIN  DIO_PIN2
#define KEYPAD_COLUMN2_PORT DIO_PORTB
#define KEYPAD_COLUMN2_PIN  DIO_PIN3

//macros for rows
#define KEYPAD_ROW0_PORT DIO_PORTB
#define KEYPAD_ROW0_PIN  DIO_PIN4
#define KEYPAD_ROW1_PORT DIO_PORTB
#define KEYPAD_ROW1_PIN  DIO_PIN5
#define KEYPAD_ROW2_PORT DIO_PORTB
#define KEYPAD_ROW2_PIN  DIO_PIN6
#define KEYPAD_ROW3_PORT DIO_PORTB
#define KEYPAD_ROW3_PIN  DIO_PIN7

#define KEYPAD_KEYS  {{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}}



#endif /* KEYPAD_CONFIG_H_ */
