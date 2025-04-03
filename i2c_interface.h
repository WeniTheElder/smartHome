/*
 * i2c_interface.h
 *
 * Created: 11/3/2025 8:12:28 AM
 *  Author: Ahmad Abdullatif
 */


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_


void I2C_voidMasterInit                     (void);
void I2C_voidSendStartCondition             (void);
void I2C_voidSendRepeatedStartCondition     (void);
void I2C_voidSendStopCondition              (void);
void I2C_voidSendSlaveAddressWithWrite      (u8 copy_u8SlaveAddress);
void I2C_voidSendSlaveAddressWithRead       (u8 copy_u8SlaveAddress);
void I2C_voidMasterSendDataByte             (u8 copy_u8Data);
void I2C_voidMasterReceiveDataByteWithACK   (u8* copy_pu8Data);
void I2C_voidMasterReceiveDataByteWithoutACK(u8* copy_pu8Data);


#endif /* I2C_INTERFACE_H_ */
