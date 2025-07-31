/*
 * eeprom_program.c
 *
 * Created: 12/3/2025 8:12:28 AM
 *  Author: Ahmad Abdullatif
 */
#define F_CPU 16000000UL
#include <util/delay.h>
#include "std_types.h"
#include "bit_math.h"
#include "i2c_interface.h"
#include "eeprom_interface.h"
#include "eeprom_private.h"

void EEPROM_voidInit(void){
	I2C_voidMasterInit();
}

void EEPROM_voidWriteByte(u16 copy_u16WordAddress,u8 copy_u8Data){
	u8 local_u8DeviceAddress = EEPROM_FIXED_ADDRESS;
	local_u8DeviceAddress |= (copy_u16WordAddress >> 8);
	
	//send start condition
	I2C_voidSendStartCondition();
	
	//send device address with write
	I2C_voidSendSlaveAddressWithWrite(local_u8DeviceAddress);
	
	//send word address
	I2C_voidMasterSendDataByte((u8)copy_u16WordAddress);
	
	//send data byte
	I2C_voidMasterSendDataByte(copy_u8Data);
	
	//send stop condition
	I2C_voidSendStopCondition();
	
	//self timed write cycle delay
	_delay_ms(5);
}

void EEPROM_voidReadByte (u16 copy_u16WordAddress,u8* copy_pu8Data){
	u8 local_u8DeviceAddress = EEPROM_FIXED_ADDRESS;
	local_u8DeviceAddress |= (copy_u16WordAddress >> 8);
	
	//send start condition
	I2C_voidSendStartCondition();
	
	//send device address with write
	I2C_voidSendSlaveAddressWithWrite(local_u8DeviceAddress);
	
	//send word address
	I2C_voidMasterSendDataByte((u8)copy_u16WordAddress);
	
	//send repeated start condition
	I2C_voidSendRepeatedStartCondition();
	
	//send device address with read
	I2C_voidSendSlaveAddressWithRead(local_u8DeviceAddress);
	
	//read data byte with NACK
	I2C_voidMasterReceiveDataByteWithoutACK(copy_pu8Data);
	
	//send stop condition
	I2C_voidSendStopCondition();
	
	//self timed write cycle delay
	_delay_ms(5);
}
