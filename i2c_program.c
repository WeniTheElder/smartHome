/*
 * i2c_program.c
 *
 * Created: 11/3/2025 8:12:28 AM
 *  Author: Ahmad Abdullatif
 */

#include "std_types.h"
#include "bit_math.h"
#include "i2c_interface.h"
#include "i2c_registers.h"
#include "i2c_private.h"

void I2C_voidMasterInit(void){
	//set transfer speed to 400khz
	CLEAR_BIT(TWSR_REG,TWPS1_BIT);
	CLEAR_BIT(TWSR_REG,TWPS0_BIT);
	TWBR_REG = 12;

	//enable TWI (I2C)
	SET_BIT  (TWCR_REG,TWEN_BIT);

	//disable I2C interrupt
	CLEAR_BIT(TWCR_REG,TWIE_BIT);
}
void I2C_voidSendStartCondition(void){
	//sending a start bit on the SDA
	SET_BIT(TWCR_REG,TWSTA_BIT);

	//clear flag to send the stop bit
	SET_BIT(TWCR_REG,TWINT_BIT);

	//waiting for the start condition to be sent
	while(GET_BIT(TWCR_REG,TWINT_BIT) == 0);

	//checking if the status code = start condition has been sent
	while(I2C_STATUS_CODE_VALUE != I2C_STATUS_CODE_START_CONDITION_SENT);
}
void I2C_voidSendRepeatedStartCondition(void){
	//sending a start bit on the SDA
	SET_BIT(TWCR_REG,TWSTA_BIT);

	//clearing TWI flag
	SET_BIT(TWCR_REG,TWINT_BIT);

	//checking if the start bit has been sent
	while(GET_BIT(TWCR_REG,TWINT_BIT) == 0);

	//checking if the status code = start condition has been sent
	while(I2C_STATUS_CODE_VALUE != I2C_STATUS_CODE_REPEATED_START_CONDITION_SENT);
}
void I2C_voidSendStopCondition(void){
	//send stop condition on the SDA
	SET_BIT(TWCR_REG,TWSTO_BIT);

	//clear flag to send the stop bit
	SET_BIT(TWCR_REG,TWINT_BIT);
}
void I2C_voidSendSlaveAddressWithWrite(u8 copy_u8SlaveAddress){
	if(copy_u8SlaveAddress < 128){
		//shifting the address to be MSB
		copy_u8SlaveAddress <<= 1;
		//write the slave address on the data register
		TWDR_REG = copy_u8SlaveAddress;

		//mark the data register as write(clear the LSB)
		CLEAR_BIT(TWDR_REG,TWD0_BIT);

		//clearing start condition bit
		CLEAR_BIT(TWCR_REG,TWSTA_BIT);

		//clearing TWI flag
		SET_BIT(TWCR_REG,TWINT_BIT);

		//wait for the address to be sent on the SDA
		while(GET_BIT(TWCR_REG,TWINT_BIT) == 0);

		//wait for the right status code to be generated
		while(I2C_STATUS_CODE_VALUE != I2C_STATUS_CODE_SLAVE_ADDRESS_WRITE_SENT_WITH_ACK);
	}
}
void I2C_voidSendSlaveAddressWithRead(u8 copy_u8SlaveAddress){
	if(copy_u8SlaveAddress < 128){
		//shifting the address to be MSB
		copy_u8SlaveAddress <<= 1;
		//write the slave address on the data register
		TWDR_REG = copy_u8SlaveAddress;

		//mark the data register as read(set the LSB)
		SET_BIT  (TWDR_REG,TWD0_BIT);

		//clearing start condition bit
		CLEAR_BIT(TWCR_REG,TWSTA_BIT);

		//clearing TWI flag
		SET_BIT  (TWCR_REG,TWINT_BIT);

		//wait for the address to be sent on the SDA
		while(GET_BIT(TWCR_REG,TWINT_BIT) == 0);

		//wait for the right status code to be generated
		while(I2C_STATUS_CODE_VALUE != I2C_STATUS_CODE_SLAVE_ADDRESS_READ_SENT_WITH_ACK);
	}
}
void I2C_voidMasterSendDataByte(u8 copy_u8Data){
	//writing the data in the data register
	TWDR_REG = copy_u8Data;

	//clearing TWI flag
	SET_BIT(TWCR_REG,TWINT_BIT);

	//wait for the address to be sent on the SDA
	while(GET_BIT(TWCR_REG,TWINT_BIT) == 0);

	//wait for the right status code to be generated
	while(I2C_STATUS_CODE_VALUE != I2C_STATUS_CODE_BYTE_DATA_SENT_WITH_ACK);

}
void I2C_voidMasterReceiveDataByteWithACK(u8* copy_pu8Data){
	//enable ACK pulse generation
	SET_BIT  (TWCR_REG,TWEA_BIT);

	//clearing TWI flag
	SET_BIT(TWCR_REG,TWINT_BIT);

	//waiting for the data to be received
	while(GET_BIT(TWCR_REG,TWINT_BIT) == 0);

	//waiting for the right status code to be generated
	while(I2C_STATUS_CODE_VALUE != I2C_STATUS_CODE_BYTE_DATA_RECEIVED_WITH_ACK);

	//get the data from the data register
	*copy_pu8Data = TWDR_REG;

	//disable ACK pulse generation
	CLEAR_BIT  (TWCR_REG,TWEA_BIT);
}
void I2C_voidMasterReceiveDataByteWithoutACK(u8* copy_pu8Data){
	//clearing TWI flag
	SET_BIT(TWCR_REG,TWINT_BIT);

	//waiting for the data to be received
	while(GET_BIT(TWCR_REG,TWINT_BIT) == 0);

	//waiting for the right status code to be generated
	while(I2C_STATUS_CODE_VALUE != I2C_STATUS_CODE_BYTE_DATA_RECEIVED_WITHOUT_ACK);

	//get the data from the data register
	*copy_pu8Data = TWDR_REG;
}
