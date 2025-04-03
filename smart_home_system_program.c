/* 
 * smart_home_system_program.c
 *
 * Created: 3/13/2025 1:30:17 AM
 *  Author: Ahmad Abdullatif
 */


#define F_CPU 16000000UL
/*library stack*/
#include "std_types.h"
#include "bit_math.h"
#include <util/delay.h>
/*APP*/
#include "smart_home_system_private.h"
#include "smart_home_system_interface.h"
#include "smart_home_system_config.h"
/*HAL*/
#include "LCD_interface.h"
#include "eeprom_interface.h"
#include "keyPad_interface.h"
/*MCAL*/
#include "uart_interface.h"
#include "pwm1_interface.h"
#include "DIO_interface.h"
#include "Timer0_interface.h"
#include "ADC_interface.h"
#include "GI_interface.h"
#include "EXTI_interface.h"
#include "pwm2_interface.h"
//=========================//


void SmartHome_voidInitSystem(){
	GI_voidEnableGeneralInterrupt();
	EEPROM_voidInit();
	UART_voidInit();
	ADC_voidInit(ADC_AVCC);
	PWM1_voidInit();
	LCD_voidInit();
	KEYPAD_voidInit();
	EXTI_voidExternalInterruptInit(EXTI_EXTI0,EXTI_RISING_EDGE);
	EXTI_voidExternalInterruptEnable(EXTI_EXTI0);
	TIMER0_voidInit(TIMER0_CTC_MODE);
	TIMER0_voidSetCallBackFunction(priv_voidTempSensorSystem);
	TIMER0_voidStartTimer();
	PWM2_voidInit();
	priv_voidInitLightSystem();
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN0,DIO_OUTPUT);//fan control pin
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN0,DIO_HIGH);      //fan control pin
	EEPROM_voidWriteByte(USER_COUNTER_ADDRESSS,0);
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN4,DIO_OUTPUT);
}

void priv_voidInitLightSystem(){
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN3,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN4,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN5,DIO_OUTPUT);
}
void SmartHome_voidTerminalLoginMainMenu(){
	u8 local_u8Choice;
	UART_voidTxChar('\f');//clear display
	UART_voidTxString("Main Login Page\r\n");
	UART_voidTxString("1)Admin login   2)User login\r\n");
	UART_voidRxChar(&local_u8Choice);
	UART_voidTxString("\r\n");//new line
	switch(local_u8Choice){
		case '1':
		UART_voidTxChar('\f');//clear display
		UART_voidTxString("Admin login\r\n");
		priv_voidAdminLogin();
		break;
		case '2':
		UART_voidTxChar('\f');//clear display
		UART_voidTxString("user login\r\n");
		priv_voidUserLogin();
		break;
		default:
			UART_voidTxString("invalid choice!\r\n");
			_delay_ms(2000);
		}
}


void priv_voidAddUser() {
	u8 local_u8NumberOfUsers = 0;
	u8 local_u8PasswordDigit;
	u8 local_u8userIdDigit;
	u16 local_u16userId = 0;
	bool validUserId = false;
	u8 local_u8StoredUserId;
	bool userIdExists = false;
	
	// get number of users in the system
	EEPROM_voidReadByte(USER_COUNTER_ADDRESSS, &local_u8NumberOfUsers);
	
	if (local_u8NumberOfUsers >= MAX_NUMBER_OF_USERS) {
		UART_voidTxString("Max number of users reached!\r\n");
		_delay_ms(2000);
		return;
	}
	
	// Get user ID and add it to memory
	while (!validUserId) { // Continue until valid user ID is entered
		userIdExists = false;
		local_u16userId = 0;
		UART_voidTxString("Enter new user ID: ");
		
		// Input user ID
		for (int i = 0; i < USER_ID_SIZE; ++i) {
			local_u16userId *= 10;
			UART_voidRxChar(&local_u8userIdDigit);
			local_u8userIdDigit -= '0';
			local_u16userId += local_u8userIdDigit;
		}
		
		UART_voidTxString("\r\n"); // New line
		
		// Validate user ID range
		if (local_u16userId > 255 || local_u16userId < 100) {
			UART_voidTxString("User ID isn't valid!\r\n");
			_delay_ms(2000);
			continue; // Ask for a new ID
		}

		// Check if the user ID already exists
		for (int i = 0; i < local_u8NumberOfUsers * (PASSWORD_LENGTH + 1); i += PASSWORD_LENGTH + 1) {
			EEPROM_voidReadByte(i, &local_u8StoredUserId);
			if (local_u8StoredUserId == local_u16userId) {
				UART_voidTxString("This user ID already exists.\r\n");
				_delay_ms(2000);
				userIdExists = true; // Mark as existing
				break;
			}
		}

		// If no conflict, set validUserId to true
		if (!userIdExists) {
			validUserId = true;
		}
	}

	// Store the user ID in memory
	EEPROM_voidWriteByte(local_u8NumberOfUsers * (PASSWORD_LENGTH + 1), local_u16userId);

	// Get password from user and store it
	UART_voidTxString("Set new user password: ");
	for (int i = 0; i < PASSWORD_LENGTH; ++i) {
		UART_voidRxChar(&local_u8PasswordDigit);
		EEPROM_voidWriteByte(local_u8NumberOfUsers * (PASSWORD_LENGTH + 1) + 1 + i, local_u8PasswordDigit);
	}

	UART_voidTxChar('\f'); // Clear display
	
	// Increment the number of users and update in memory
	local_u8NumberOfUsers++;
	EEPROM_voidWriteByte(USER_COUNTER_ADDRESSS, local_u8NumberOfUsers);
	
	UART_voidTxString("User added!\r\n");
}



void priv_voidUserLogin(){
	u8 local_u8NumberOfUsers;
	u8 local_u8UserPassword[PASSWORD_LENGTH];
	u8 local_u8userIdDigit;
	u8 local_u8EnteredUserId = 0;
	u8 local_u8StoredUserId;
	bool userIdFound = false;
	u8 local_u8userAddress;
	
	//get number of users
	EEPROM_voidReadByte(USER_COUNTER_ADDRESSS,&local_u8NumberOfUsers);
	
	//if there's no users return
	if(local_u8NumberOfUsers == 0){
		UART_voidTxString("Add users First!\r\n");
		_delay_ms(2000);
		return;
	}
	
	//get user id
	UART_voidTxString("enter user ID:");
	for(int i=0;i<USER_ID_SIZE;++i){
		local_u8EnteredUserId*= 10;
		UART_voidRxChar(&local_u8userIdDigit);
		local_u8userIdDigit -= '0';
		local_u8EnteredUserId += local_u8userIdDigit;
	}
	UART_voidTxString("\r\n");//new line
	
	//check if this user id exists
	for(int i = 0;i<local_u8NumberOfUsers*(PASSWORD_LENGTH+1);i += PASSWORD_LENGTH+1){
		EEPROM_voidReadByte(i,&local_u8StoredUserId);
		if(local_u8StoredUserId == local_u8EnteredUserId){
			userIdFound = true;
			local_u8userAddress = i;
			break;
		}	
	}
	
	if(!userIdFound){
		UART_voidTxString("user id not found\r\n");
		_delay_ms(2000);
		return;
	}
	
	//get user password form memory
	for(int i = 0;i<PASSWORD_LENGTH;++i){
		EEPROM_voidReadByte(local_u8userAddress+1+i,&local_u8UserPassword[i]);
	}
	
	//check password
	priv_voidCheckPassword(local_u8UserPassword);
	
	priv_voidUserPage();
}


void priv_voidAdminLogin(){
	u8 local_u8AdminPassword [PASSWORD_LENGTH]= ADMIN_PASSWORD;
	priv_voidCheckPassword(local_u8AdminPassword);
	priv_voidAdminPage();
}




void priv_voidCheckPassword(u8* copy_pu8UserPassword){
	u8 local_u8WrongPasswordCounter = 0;
	u8 local_u8InputPassword[PASSWORD_LENGTH];
	//loop to get input password and check if the input password is correct
	while(local_u8WrongPasswordCounter < MAX_NUMBER_OF_WRONG_ATTEMPTS){
		bool local_boolRightPassword    = true;
		UART_voidTxString("enter password:");
		
		//get user input
		for(int i = 0;i<PASSWORD_LENGTH;++i){
			UART_voidRxChar(&local_u8InputPassword[i]);
		}
		UART_voidTxString("\r\n");//new line
		
		//check input password
		for(int i = 0;i<PASSWORD_LENGTH;++i){
			if(local_u8InputPassword[i] != copy_pu8UserPassword[i]){
				local_u8WrongPasswordCounter++;
				local_boolRightPassword = false;
				UART_voidTxString("Wrong password, try again\r\n");
				_delay_ms(2000);
				break;
			}
		}
		
		//if right password, terminate function
		if(local_boolRightPassword) return;
	}
	
	//if we break due to wrong attempts, lock system
		UART_voidTxString("Wrong input limit reached. System locked.\r\n");
		priv_voidLockSystem();
		
}
void priv_voidAdminPage(){
	u8 local_u8Choice;
	while(1){
		UART_voidTxChar('\f');//clear display
		UART_voidTxString("1)add user 2)door 3)lights 4)exit\r\n");
		UART_voidRxChar(&local_u8Choice);
		UART_voidTxString("\r\n");//new line
		switch(local_u8Choice){
			case '1':
			priv_voidAddUser();
			break;
			case '2':
			priv_voidDoorControl();
			break;
			case '3':
			priv_voidLightSystem();
			break;
			case '4':
			return;
		}
	}
}
void priv_voidUserPage(){
	u8 local_u8Choice;
	while(1){
		UART_voidTxString("1)lights 2)exit\r\n");
		UART_voidRxChar(&local_u8Choice);
		UART_voidTxString("\r\n");//new line
		switch(local_u8Choice){
			case '1':
			priv_voidLightSystem();
			break;
			case '2':
			return;
			break;
		}
	}
}
void priv_voidLockSystem(){
	while(1){}
}
void priv_voidDoorControl(){
	UART_voidTxChar('\f');//clear display
	u8 local_u8Choice;
	UART_voidTxString("1)open door 2)close door\r\n");
	UART_voidRxChar(&local_u8Choice);
	switch(local_u8Choice){
		case '1':
		PWM1_voidStart(10,50);
		break;
		case '2':
		PWM1_voidStart(7.5,50);
		break;
	}
}
void priv_voidLightSystem(){
	UART_voidTxChar('\f');//clear display
	u8 local_u8Choice;
	UART_voidTxString("1)lamp1 2)lamp2\r\n");
	UART_voidTxString("3)lamp3 4)lamp4\r\n");
	
	UART_voidRxChar(&local_u8Choice);
	UART_voidTxString("\r\n");//new line
	UART_voidTxString("1)on 2)off\r\n");
	switch(local_u8Choice){
		case '1':
		UART_voidRxChar(&local_u8Choice);
		UART_voidTxString("\r\n");//new line
		switch(local_u8Choice){
			case '1':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_HIGH);
			break;
			case '2':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_LOW);
			break;
		}
		break;
		case '2':
		UART_voidRxChar(&local_u8Choice);
		UART_voidTxString("\r\n");//new line
		switch(local_u8Choice){
			case '1':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);
			break;
			case '2':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);
			break;
		}
		break;
		case '3':
		UART_voidRxChar(&local_u8Choice);
		UART_voidTxString("\r\n");//new line
		switch(local_u8Choice){
			case '1':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN4,DIO_HIGH);
			break;
			case '2':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN4,DIO_LOW);
			break;
		}
		break;
		case '4':
		UART_voidRxChar(&local_u8Choice);
		UART_voidTxString("\r\n");//new line
		switch(local_u8Choice){
			case '1':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN5,DIO_HIGH);
			break;
			case '2':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN5,DIO_LOW);
			break;
		}
		break;
	}
}

void priv_voidTempSensorSystem(){
	u16 local_u16DigitalValue;
	u16 local_u16AnalogValue;
	local_u16DigitalValue = ADC_u16GetAdcResult(ADC_ADC0);
	local_u16AnalogValue = ((u32)local_u16DigitalValue*500)/1024;
	LCD_voidClearDisplay();
	LCD_voidDisplayString("Temperature:");
	LCD_voidDisplayNumber(local_u16AnalogValue);
	LCD_voidDisplayCharacter('C');
	if(local_u16AnalogValue >= 37){
		PWM2_voidStart(100);
	}
	else if(local_u16AnalogValue >= 34){
		PWM2_voidStart(75);
	}
	else if(local_u16AnalogValue >= 30){
		PWM2_voidStart(50);
	}
	else if(local_u16AnalogValue >= 27){
		PWM2_voidStart(25);
	}
	else{
		DIO_voidSetPinValue(DIO_PORTB,DIO_PIN0,DIO_HIGH);
		PWM2_voidStop();
	}
}

void priv_LCDcontrolMainTerminal(){
	LCD_voidClearDisplay();
	u8 key = KEY_NOT_PRESSED;
	LCD_voidDisplayString("1)lights 0)exit");
	while(key == KEY_NOT_PRESSED){
		KEYPAD_voidGetPressedKey(&key);
	}
	switch(key){
		case '1':
		priv_voidLCDLightSystemControl();
		break;
		case '0':
		return;
	}
}


void priv_voidLCDLightSystemControl(){
	u8 local_u8Choice = KEY_NOT_PRESSED;
	
	LCD_voidClearDisplay();
	LCD_voidDisplayString("1)lamp1 2)lamp2\r\n");
	LCD_voidMoveToSecondLine();
	LCD_voidDisplayString("3)lamp3 4)lamp4\r\n");
	
	while(local_u8Choice == KEY_NOT_PRESSED){
		KEYPAD_voidGetPressedKey(&local_u8Choice);
	}
	LCD_voidClearDisplay();
	LCD_voidDisplayString("1)on 2)off\r\n");
	switch(local_u8Choice){
		case '1':
		local_u8Choice = KEY_NOT_PRESSED;
		while(local_u8Choice == KEY_NOT_PRESSED){
			KEYPAD_voidGetPressedKey(&local_u8Choice);
		}
		switch(local_u8Choice){
			case '1':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_HIGH);
			break;
			case '2':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_LOW);
			break;
		}
		break;
		case '2':
		local_u8Choice = KEY_NOT_PRESSED;
		while(local_u8Choice == KEY_NOT_PRESSED){
			KEYPAD_voidGetPressedKey(&local_u8Choice);
		}
		switch(local_u8Choice){
			case '1':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);
			break;
			case '2':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);
			break;
		}
		break;
		case '3':
		local_u8Choice = KEY_NOT_PRESSED;
		while(local_u8Choice == KEY_NOT_PRESSED){
			KEYPAD_voidGetPressedKey(&local_u8Choice);
		}
		switch(local_u8Choice){
			case '1':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN4,DIO_HIGH);
			break;
			case '2':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN4,DIO_LOW);
			break;
		}
		break;
		case '4':
		local_u8Choice = KEY_NOT_PRESSED;
		while(local_u8Choice == KEY_NOT_PRESSED){
			KEYPAD_voidGetPressedKey(&local_u8Choice);
		}
		switch(local_u8Choice){
			case '1':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN5,DIO_HIGH);
			break;
			case '2':
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN5,DIO_LOW);
			break;
		}
		break;
	}
}


void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	priv_LCDcontrolMainTerminal();
}