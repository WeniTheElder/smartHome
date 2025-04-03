/*
 * i2c_registers.h
 *
 * Created: 11/3/2025 8:12:28 AM
 *  Author: Ahmad Abdullatif
 */


#ifndef I2C_REGISTERS_H_
#define I2C_REGISTERS_H_

#define TWBR_REG  (*(volatile u8*)0x20)

#define TWCR_REG  (*(volatile u8*)0x56)
#define TWINT_BIT 7
#define TWEA_BIT  6
#define TWSTA_BIT 5
#define TWSTO_BIT 4
#define TWWC_BIT  3
#define TWEN_BIT  2
#define TWIE_BIT  0

#define TWSR_REG  (*(volatile u8*)0x21)
#define TWS7_BIT  7
#define TWS6_BIT  6
#define TWS5_BIT  5
#define TWS4_BIT  4
#define TWS3_BIT  3
#define TWPS1_BIT 1
#define TWPS0_BIT 0

#define TWDR_REG  (*(volatile u8*)0x23)
#define TWD7_BIT  7
#define TWD6_BIT  6
#define TWD5_BIT  5
#define TWD4_BIT  4
#define TWD3_BIT  3
#define TWD2_BIT  2
#define TWD1_BIT  1
#define TWD0_BIT  0


#define TWAR_REG  (*(volatile u8*)0x22)
#define TWA6_BIT  7
#define TWA5_BIT  6
#define TWA4_BIT  5
#define TWA3_BIT  4
#define TWA2_BIT  3
#define TWA1_BIT  2
#define TWA0_BIT  1
#define TWGCE_BIT 0








#endif /* I2C_REGISTERS_H_ */
